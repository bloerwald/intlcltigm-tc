/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "WorldPacket.h"
#include "SpellPackets.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "Pet.h"
#include "Formulas.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "CreatureAI.h"
#include "Unit.h"
#include "Util.h"
#include "Group.h"
#include "Opcodes.h"
#include "WorldSession.h"

#define PET_XP_FACTOR 0.05f

Pet::Pet(Player* owner, PetType type) :
    Guardian(NULL, owner, true), m_usedTalentCount(0), m_removed(false),
    m_petType(type), m_duration(0), m_auraRaidUpdateMask(0), m_loading(false),
    m_declinedname(NULL)
{
    ASSERT(GetOwner());

    m_unitTypeMask |= UNIT_MASK_PET;
    if (type == HUNTER_PET)
        m_unitTypeMask |= UNIT_MASK_HUNTER_PET;

    if (!(m_unitTypeMask & UNIT_MASK_CONTROLABLE_GUARDIAN))
    {
        m_unitTypeMask |= UNIT_MASK_CONTROLABLE_GUARDIAN;
        InitCharmInfo();
    }

    m_name = "Pet";
    m_regenTimer = PET_FOCUS_REGEN_INTERVAL;
}

Pet::~Pet()
{
    delete m_declinedname;
}

void Pet::AddToWorld()
{
    ///- Register the pet for guid lookup
    if (!IsInWorld())
    {
        ///- Register the pet for guid lookup
        sObjectAccessor->AddObject(this);
        Unit::AddToWorld();
        AIM_Initialize();
    }

    // Prevent stuck pets when zoning. Pets default to "follow" when added to world
    // so we'll reset flags and let the AI handle things
    if (GetCharmInfo() && GetCharmInfo()->HasCommandState(COMMAND_FOLLOW))
    {
        GetCharmInfo()->SetIsCommandAttack(false);
        GetCharmInfo()->SetIsCommandFollow(false);
        GetCharmInfo()->SetIsAtStay(false);
        GetCharmInfo()->SetIsFollowing(false);
        GetCharmInfo()->SetIsReturning(false);
    }
}

void Pet::RemoveFromWorld()
{
    ///- Remove the pet from the accessor
    if (IsInWorld())
    {
        ///- Don't call the function for Creature, normal mobs + totems go in a different storage
        Unit::RemoveFromWorld();
        sObjectAccessor->RemoveObject(this);
    }
}

bool Pet::LoadPetFromDB(Player* owner, uint32 petEntry, uint32 petnumber, bool current)
{
    m_loading = true;

    ObjectGuid::LowType ownerid = owner->GetGUID().GetCounter();

    PreparedStatement* stmt;
    PreparedQueryResult result;

    if (petnumber)
    {
        // Known petnumber entry
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PET_BY_ENTRY);
        stmt->setUInt64(0, ownerid);
        stmt->setUInt32(1, petnumber);
    }
    else if (current)
    {
        // Current pet (slot 0)
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PET_BY_ENTRY_AND_SLOT);
        stmt->setUInt64(0, ownerid);
        stmt->setUInt8(1, uint8(PET_SAVE_AS_CURRENT));
    }
    else if (petEntry)
    {
        // known petEntry entry (unique for summoned pet, but non unique for hunter pet (only from current or not stabled pets)
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PET_BY_ENTRY_AND_SLOT_2);
        stmt->setUInt64(0, ownerid);
        stmt->setUInt32(1, petEntry);
        stmt->setUInt8(2, uint8(PET_SAVE_AS_CURRENT));
        stmt->setUInt8(3, uint8(PET_SAVE_LAST_STABLE_SLOT));
    }
    else
    {
        // Any current or other non-stabled pet (for hunter "call pet")
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PET_BY_SLOT);
        stmt->setUInt64(0, ownerid);
        stmt->setUInt8(1, uint8(PET_SAVE_AS_CURRENT));
        stmt->setUInt8(2, uint8(PET_SAVE_LAST_STABLE_SLOT));
    }

    result = CharacterDatabase.Query(stmt);

    if (!result)
    {
        m_loading = false;
        return false;
    }

    Field* fields = result->Fetch();

    // update for case of current pet "slot = 0"
    petEntry = fields[1].GetUInt32();
    if (!petEntry)
        return false;

    uint32 summonSpellId = fields[14].GetUInt32();
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(summonSpellId);

    bool isTemporarySummon = spellInfo && spellInfo->GetDuration() > 0;
    if (current && isTemporarySummon)
        return false;

    PetType petType = PetType(fields[15].GetUInt8());
    if (petType == HUNTER_PET)
    {
        CreatureTemplate const* creatureInfo = sObjectMgr->GetCreatureTemplate(petEntry);
        if (!creatureInfo || !creatureInfo->IsTameable(owner->CanTameExoticPets()))
            return false;
    }

    uint32 petId = fields[0].GetUInt32();

    if (current && owner->IsPetNeedBeTemporaryUnsummoned())
    {
        owner->SetTemporaryUnsummonedPetNumber(petId);
        return false;
    }

    Map* map = owner->GetMap();
    if (!Create(sObjectMgr->GetGenerator<HighGuid::Pet>()->Generate(), map, petEntry))
        return false;

    CopyPhaseFrom(owner);

    setPetType(petType);
    setFaction(owner->getFaction());
    SetUInt32Value(UNIT_CREATED_BY_SPELL, summonSpellId);

    if (IsCritter())
    {
        float px, py, pz;
        owner->GetClosePoint(px, py, pz, GetObjectSize(), PET_FOLLOW_DIST, GetFollowAngle());
        Relocate(px, py, pz, owner->GetOrientation());

        if (!IsPositionValid())
        {
            TC_LOG_ERROR("entities.pet", "Pet (%s, entry %d) not loaded. Suggested coordinates isn't valid (X: %f Y: %f)",
                GetGUID().ToString().c_str(), GetEntry(), GetPositionX(), GetPositionY());
            return false;
        }

        map->AddToMap(this->ToCreature());
        return true;
    }

    m_charmInfo->SetPetNumber(petId, IsPermanentPetFor(owner));

    SetDisplayId(fields[3].GetUInt32());
    SetNativeDisplayId(fields[3].GetUInt32());
    uint32 petlevel = fields[4].GetUInt16();
    SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
    SetName(fields[8].GetString());

    switch (getPetType())
    {
        case SUMMON_PET:
            petlevel = owner->getLevel();
            SetByteValue(UNIT_FIELD_BYTES_0, UNIT_BYTES_0_OFFSET_CLASS, CLASS_MAGE);
            SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE); // this enables popup window (pet dismiss, cancel)
            break;
        case HUNTER_PET:
            SetByteValue(UNIT_FIELD_BYTES_0, UNIT_BYTES_0_OFFSET_CLASS, CLASS_WARRIOR);
            SetByteValue(UNIT_FIELD_BYTES_0, UNIT_BYTES_0_OFFSET_GENDER, GENDER_NONE);
            SetSheath(SHEATH_STATE_MELEE);
            SetByteFlag(UNIT_FIELD_BYTES_2, 2, fields[9].GetBool() ? UNIT_CAN_BE_ABANDONED : UNIT_CAN_BE_RENAMED | UNIT_CAN_BE_ABANDONED);
            SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE); // this enables popup window (pet abandon, cancel)
            setPowerType(POWER_FOCUS);
            break;
        default:
            if (!IsPetGhoul())
                TC_LOG_ERROR("entities.pet", "Pet have incorrect type (%u) for pet loading.", getPetType());
            break;
    }

    SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, uint32(time(NULL))); // cast can't be helped here
    SetCreatorGUID(owner->GetGUID());

    InitStatsForLevel(petlevel);
    SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, fields[5].GetUInt32());

    SynchronizeLevelWithOwner();

    // Set pet's position after setting level, its size depends on it
    float px, py, pz;
    owner->GetClosePoint(px, py, pz, GetObjectSize(), PET_FOLLOW_DIST, GetFollowAngle());
    Relocate(px, py, pz, owner->GetOrientation());
    if (!IsPositionValid())
    {
        TC_LOG_ERROR("entities.pet", "Pet (%s, entry %d) not loaded. Suggested coordinates isn't valid (X: %f Y: %f)",
            GetGUID().ToString().c_str(), GetEntry(), GetPositionX(), GetPositionY());
        return false;
    }

    SetReactState(ReactStates(fields[6].GetUInt8()));
    SetCanModifyStats(true);

    if (getPetType() == SUMMON_PET && !current)              //all (?) summon pets come with full health when called, but not when they are current
        SetPower(POWER_MANA, GetMaxPower(POWER_MANA));
    else
    {
        uint32 savedhealth = fields[10].GetUInt32();
        uint32 savedmana = fields[11].GetUInt32();
        if (!savedhealth && getPetType() == HUNTER_PET)
            setDeathState(JUST_DIED);
        else
        {
            SetHealth(savedhealth > GetMaxHealth() ? GetMaxHealth() : savedhealth);
            SetPower(POWER_MANA, savedmana > uint32(GetMaxPower(POWER_MANA)) ? GetMaxPower(POWER_MANA) : savedmana);
        }
    }

    // set current pet as current
    // 0=current
    // 1..MAX_PET_STABLES in stable slot
    // PET_SAVE_NOT_IN_SLOT(100) = not stable slot (summoning))
    if (fields[7].GetUInt8())
    {
        SQLTransaction trans = CharacterDatabase.BeginTransaction();

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_PET_SLOT_BY_SLOT_EXCLUDE_ID);
        stmt->setUInt8(0, uint8(PET_SAVE_NOT_IN_SLOT));
        stmt->setUInt64(1, ownerid);
        stmt->setUInt8(2, uint8(PET_SAVE_AS_CURRENT));
        stmt->setUInt32(3, m_charmInfo->GetPetNumber());
        trans->Append(stmt);

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_PET_SLOT_BY_ID);
        stmt->setUInt8(0, uint8(PET_SAVE_AS_CURRENT));
        stmt->setUInt64(1, ownerid);
        stmt->setUInt32(2, m_charmInfo->GetPetNumber());
        trans->Append(stmt);

        CharacterDatabase.CommitTransaction(trans);
    }

    // Send fake summon spell cast - this is needed for correct cooldown application for spells
    // Example: 46584 - without this cooldown (which should be set always when pet is loaded) isn't set clientside
    /// @todo pets should be summoned from real cast instead of just faking it?
    if (summonSpellId)
    {
        WorldPackets::Spells::SpellGo spellGo;
        WorldPackets::Spells::SpellCastData& castData = spellGo.Cast;

        castData.CasterGUID = owner->GetGUID();
        castData.CasterUnit = owner->GetGUID();
        castData.SpellID = summonSpellId;
        castData.CastFlags = CAST_FLAG_UNKNOWN_9;
        castData.CastTime = getMSTime();

        owner->SendMessageToSet(spellGo.Write(), true);
    }

    owner->SetMinion(this, true);
    map->AddToMap(this->ToCreature());

    InitTalentForLevel();                                   // set original talents points before spell loading

    uint32 timediff = uint32(time(NULL) - fields[13].GetUInt32());
    _LoadAuras(timediff);

    // load action bar, if data broken will fill later by default spells.
    if (!isTemporarySummon)
    {
        m_charmInfo->LoadPetActionBar(fields[12].GetString());

        _LoadSpells();
        InitTalentForLevel();                               // re-init to check talent count
        _LoadSpellCooldowns();
        LearnPetPassives();
        InitLevelupSpellsForLevel();
        CastPetAuras(current);
    }

    CleanupActionBar();                                     // remove unknown spells from action bar after load

    TC_LOG_DEBUG("entities.pet", "New Pet has %s", GetGUID().ToString().c_str());

    owner->PetSpellInitialize();

    if (owner->GetGroup())
        owner->SetGroupUpdateFlag(GROUP_UPDATE_PET);

    // TODO: 6.x remove/update pet talents
    //owner->SendTalentsInfoData(true);

    if (getPetType() == HUNTER_PET)
    {
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_DECLINED_NAME);
        stmt->setUInt64(0, owner->GetGUID().GetCounter());
        stmt->setUInt32(1, GetCharmInfo()->GetPetNumber());
        PreparedQueryResult result = CharacterDatabase.Query(stmt);

        if (result)
        {
            delete m_declinedname;
            m_declinedname = new DeclinedName;
            Field* fields2 = result->Fetch();
            for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
            {
                m_declinedname->name[i] = fields2[i].GetString();
            }
        }
    }

    //set last used pet number (for use in BG's)
    if (owner->GetTypeId() == TYPEID_PLAYER && isControlled() && !isTemporarySummoned() && (getPetType() == SUMMON_PET || getPetType() == HUNTER_PET))
        owner->ToPlayer()->SetLastPetNumber(petId);

    m_loading = false;

    return true;
}

void Pet::SavePetToDB(PetSaveMode mode)
{
    if (!GetEntry())
        return;

    // save only fully controlled creature
    if (!isControlled())
        return;

    // not save not player pets
    if (!GetOwnerGUID().IsPlayer())
        return;

    Player* owner = GetOwner();

    // not save pet as current if another pet temporary unsummoned
    if (mode == PET_SAVE_AS_CURRENT && owner->GetTemporaryUnsummonedPetNumber() &&
        owner->GetTemporaryUnsummonedPetNumber() != m_charmInfo->GetPetNumber())
    {
        // pet will lost anyway at restore temporary unsummoned
        if (getPetType() == HUNTER_PET)
            return;

        // for warlock case
        mode = PET_SAVE_NOT_IN_SLOT;
    }

    uint32 curhealth = GetHealth();
    uint32 curmana = GetPower(POWER_MANA);

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    // save auras before possibly removing them
    _SaveAuras(trans);

    // stable and not in slot saves
    if (mode > PET_SAVE_AS_CURRENT)
        RemoveAllAuras();

    _SaveSpells(trans);
    GetSpellHistory()->SaveToDB<Pet>(trans);
    CharacterDatabase.CommitTransaction(trans);

    // current/stable/not_in_slot
    if (mode >= PET_SAVE_AS_CURRENT)
    {
        ObjectGuid::LowType ownerLowGUID = GetOwnerGUID().GetCounter();
        std::string name = m_name;
        CharacterDatabase.EscapeString(name);
        trans = CharacterDatabase.BeginTransaction();
        // remove current data

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_PET_BY_ID);
        stmt->setUInt32(0, m_charmInfo->GetPetNumber());
        trans->Append(stmt);

        // prevent duplicate using slot (except PET_SAVE_NOT_IN_SLOT)
        if (mode <= PET_SAVE_LAST_STABLE_SLOT)
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_PET_SLOT_BY_SLOT);
            stmt->setUInt8(0, uint8(PET_SAVE_NOT_IN_SLOT));
            stmt->setUInt64(1, ownerLowGUID);
            stmt->setUInt8(2, uint8(mode));
            trans->Append(stmt);
        }

        // prevent existence another hunter pet in PET_SAVE_AS_CURRENT and PET_SAVE_NOT_IN_SLOT
        if (getPetType() == HUNTER_PET && (mode == PET_SAVE_AS_CURRENT || mode > PET_SAVE_LAST_STABLE_SLOT))
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_PET_BY_SLOT);
            stmt->setUInt64(0, ownerLowGUID);
            stmt->setUInt8(1, uint8(PET_SAVE_AS_CURRENT));
            stmt->setUInt8(2, uint8(PET_SAVE_LAST_STABLE_SLOT));
            trans->Append(stmt);
        }

        // save pet
        std::ostringstream ss;
        ss  << "INSERT INTO character_pet (id, entry,  owner, modelid, level, exp, Reactstate, slot, name, renamed, curhealth, curmana, abdata, savetime, CreatedBySpell, PetType) "
            << "VALUES ("
            << m_charmInfo->GetPetNumber() << ','
            << GetEntry() << ','
            << ownerLowGUID << ','
            << GetNativeDisplayId() << ','
            << uint32(getLevel()) << ','
            << GetUInt32Value(UNIT_FIELD_PETEXPERIENCE) << ','
            << uint32(GetReactState()) << ','
            << uint32(mode) << ", '"
            << name.c_str() << "', "
            << uint32(HasByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED) ? 0 : 1) << ','
            << curhealth << ','
            << curmana << ", '";

        for (uint32 i = ACTION_BAR_INDEX_START; i < ACTION_BAR_INDEX_END; ++i)
        {
            ss << uint32(m_charmInfo->GetActionBarEntry(i)->GetType()) << ' '
               << uint32(m_charmInfo->GetActionBarEntry(i)->GetAction()) << ' ';
        };

        ss  << "', "
            << time(NULL) << ','
            << GetUInt32Value(UNIT_CREATED_BY_SPELL) << ','
            << uint32(getPetType()) << ')';

        trans->Append(ss.str().c_str());
        CharacterDatabase.CommitTransaction(trans);
    }
    // delete
    else
    {
        RemoveAllAuras();
        DeleteFromDB(m_charmInfo->GetPetNumber());
    }
}

void Pet::DeleteFromDB(uint32 guidlow)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_PET_BY_ID);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_CHAR_PET_DECLINEDNAME);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_AURA_EFFECTS);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_AURAS);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_SPELLS);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_SPELL_COOLDOWNS);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_SPELL_CHARGES);
    stmt->setUInt32(0, guidlow);
    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);
}

void Pet::setDeathState(DeathState s)                       // overwrite virtual Creature::setDeathState and Unit::setDeathState
{
    Creature::setDeathState(s);
    if (getDeathState() == CORPSE)
    {
        if (getPetType() == HUNTER_PET)
        {
            // pet corpse non lootable and non skinnable
            SetUInt32Value(OBJECT_DYNAMIC_FLAGS, UNIT_DYNFLAG_NONE);
            RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);

            //SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        }
    }
    else if (getDeathState() == ALIVE)
    {
        //RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        CastPetAuras(true);
    }
}

void Pet::Update(uint32 diff)
{
    if (m_removed)                                           // pet already removed, just wait in remove queue, no updates
        return;

    if (m_loading)
        return;

    switch (m_deathState)
    {
        case CORPSE:
        {
            if (getPetType() != HUNTER_PET || m_corpseRemoveTime <= time(NULL))
            {
                Remove(PET_SAVE_NOT_IN_SLOT);               //hunters' pets never get removed because of death, NEVER!
                return;
            }
            break;
        }
        case ALIVE:
        {
            // unsummon pet that lost owner
            Player* owner = GetOwner();
            if ((!IsWithinDistInMap(owner, GetMap()->GetVisibilityRange()) && !isPossessed()) || (isControlled() && !owner->GetPetGUID()))
            //if (!owner || (!IsWithinDistInMap(owner, GetMap()->GetVisibilityDistance()) && (owner->GetCharmGUID() && (owner->GetCharmGUID() != GetGUID()))) || (isControlled() && !owner->GetPetGUID()))
            {
                Remove(PET_SAVE_NOT_IN_SLOT, true);
                return;
            }

            if (isControlled())
            {
                if (owner->GetPetGUID() != GetGUID())
                {
                    TC_LOG_ERROR("entities.pet", "Pet %u is not pet of owner %s, removed", GetEntry(), GetOwner()->GetName().c_str());
                    Remove(getPetType() == HUNTER_PET?PET_SAVE_AS_DELETED:PET_SAVE_NOT_IN_SLOT);
                    return;
                }
            }

            if (m_duration > 0)
            {
                if (uint32(m_duration) > diff)
                    m_duration -= diff;
                else
                {
                    Remove(getPetType() != SUMMON_PET ? PET_SAVE_AS_DELETED:PET_SAVE_NOT_IN_SLOT);
                    return;
                }
            }

            //regenerate focus for hunter pets or energy for deathknight's ghoul
            if (m_regenTimer)
            {
                if (m_regenTimer > diff)
                    m_regenTimer -= diff;
                else
                {
                    switch (getPowerType())
                    {
                        case POWER_FOCUS:
                            Regenerate(POWER_FOCUS);
                            m_regenTimer += PET_FOCUS_REGEN_INTERVAL - diff;
                            if (!m_regenTimer) ++m_regenTimer;

                            // Reset if large diff (lag) causes focus to get 'stuck'
                            if (m_regenTimer > PET_FOCUS_REGEN_INTERVAL)
                                m_regenTimer = PET_FOCUS_REGEN_INTERVAL;

                            break;

                        // in creature::update
                        //case POWER_ENERGY:
                        //    Regenerate(POWER_ENERGY);
                        //    m_regenTimer += CREATURE_REGEN_INTERVAL - diff;
                        //    if (!m_regenTimer) ++m_regenTimer;
                        //    break;
                        default:
                            m_regenTimer = 0;
                            break;
                    }
                }
            }
            break;
        }
        default:
            break;
    }
    Creature::Update(diff);
}

void Creature::Regenerate(Powers power)
{
    uint32 curValue = GetPower(power);
    uint32 maxValue = GetMaxPower(power);

    if (curValue >= maxValue)
        return;

    float addvalue = 0.0f;

    switch (power)
    {
        case POWER_FOCUS:
        {
            // For hunter pets.
            addvalue = 24 * sWorld->getRate(RATE_POWER_FOCUS);
            break;
        }
        case POWER_ENERGY:
        {
            // For deathknight's ghoul.
            addvalue = 20;
            break;
        }
        default:
            return;
    }

    // Apply modifiers (if any).
    AuraEffectList const& ModPowerRegenPCTAuras = GetAuraEffectsByType(SPELL_AURA_MOD_POWER_REGEN_PERCENT);
    for (AuraEffectList::const_iterator i = ModPowerRegenPCTAuras.begin(); i != ModPowerRegenPCTAuras.end(); ++i)
        if (Powers((*i)->GetMiscValue()) == power)
            AddPct(addvalue, (*i)->GetAmount());

    addvalue += GetTotalAuraModifierByMiscValue(SPELL_AURA_MOD_POWER_REGEN, power) * (IsHunterPet()? PET_FOCUS_REGEN_INTERVAL : CREATURE_REGEN_INTERVAL) / (5 * IN_MILLISECONDS);

    ModifyPower(power, int32(addvalue));
}

void Pet::Remove(PetSaveMode mode, bool returnreagent)
{
    GetOwner()->RemovePet(this, mode, returnreagent);
}

void Pet::GivePetXP(uint32 xp)
{
    if (getPetType() != HUNTER_PET)
        return;

    if (xp < 1)
        return;

    if (!IsAlive())
        return;

    uint8 maxlevel = std::min((uint8)sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL), GetOwner()->getLevel());
    uint8 petlevel = getLevel();

    // If pet is detected to be at, or above(?) the players level, don't hand out XP
    if (petlevel >= maxlevel)
       return;

    uint32 nextLvlXP = GetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP);
    uint32 curXP = GetUInt32Value(UNIT_FIELD_PETEXPERIENCE);
    uint32 newXP = curXP + xp;

    // Check how much XP the pet should receive, and hand off have any left from previous levelups
    while (newXP >= nextLvlXP && petlevel < maxlevel)
    {
        // Subtract newXP from amount needed for nextlevel, and give pet the level
        newXP -= nextLvlXP;
        ++petlevel;

        GivePetLevel(petlevel);

        nextLvlXP = GetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP);
    }
    // Not affected by special conditions - give it new XP
    SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, petlevel < maxlevel ? newXP : 0);
}

void Pet::GivePetLevel(uint8 level)
{
    if (!level || level == getLevel())
        return;

    if (getPetType()==HUNTER_PET)
    {
        SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, 0);
        SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, uint32(sObjectMgr->GetXPForLevel(level)*PET_XP_FACTOR));
    }

    InitStatsForLevel(level);
    InitLevelupSpellsForLevel();
    InitTalentForLevel();
}

bool Pet::CreateBaseAtCreature(Creature* creature)
{
    ASSERT(creature);

    if (!CreateBaseAtTamed(creature->GetCreatureTemplate(), creature->GetMap()))
        return false;

    Relocate(creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation());

    if (!IsPositionValid())
    {
        TC_LOG_ERROR("entities.pet", "Pet (%s, entry %d) not created base at creature. Suggested coordinates isn't valid (X: %f Y: %f)",
            GetGUID().ToString().c_str(), GetEntry(), GetPositionX(), GetPositionY());
        return false;
    }

    CreatureTemplate const* cinfo = GetCreatureTemplate();
    if (!cinfo)
    {
        TC_LOG_ERROR("entities.pet", "CreateBaseAtCreature() failed, creatureInfo is missing!");
        return false;
    }

    SetDisplayId(creature->GetDisplayId());

    if (CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cinfo->family))
        SetName(cFamily->Name_lang);
    else
        SetName(creature->GetNameForLocaleIdx(sObjectMgr->GetDBCLocaleIndex()));

    return true;
}

bool Pet::CreateBaseAtCreatureInfo(CreatureTemplate const* cinfo, Unit* owner)
{
    if (!CreateBaseAtTamed(cinfo, owner->GetMap()))
        return false;

    if (CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cinfo->family))
        SetName(cFamily->Name_lang);

    Relocate(owner->GetPositionX(), owner->GetPositionY(), owner->GetPositionZ(), owner->GetOrientation());

    return true;
}

bool Pet::CreateBaseAtTamed(CreatureTemplate const* cinfo, Map* map)
{
    TC_LOG_DEBUG("entities.pet", "Pet::CreateBaseForTamed");
    if (!Create(sObjectMgr->GetGenerator<HighGuid::Pet>()->Generate(), map, cinfo->Entry))
        return false;

    setPowerType(POWER_FOCUS);
    SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, 0);
    SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, 0);
    SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, uint32(sObjectMgr->GetXPForLevel(getLevel()+1)*PET_XP_FACTOR));
    SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);

    if (cinfo->type == CREATURE_TYPE_BEAST)
    {
        SetByteValue(UNIT_FIELD_BYTES_0, UNIT_BYTES_0_OFFSET_CLASS, CLASS_WARRIOR);
        SetByteValue(UNIT_FIELD_BYTES_0, UNIT_BYTES_0_OFFSET_GENDER, GENDER_NONE);
        SetUInt32Value(UNIT_FIELD_DISPLAY_POWER, POWER_FOCUS);
        SetSheath(SHEATH_STATE_MELEE);
        SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED | UNIT_CAN_BE_ABANDONED);
    }

    return true;
}

/// @todo Move stat mods code to pet passive auras
bool Guardian::InitStatsForLevel(uint8 petlevel)
{
    CreatureTemplate const* cinfo = GetCreatureTemplate();
    ASSERT(cinfo);

    SetLevel(petlevel);

    //Determine pet type
    PetType petType = MAX_PET_TYPE;
    if (IsPet() && GetOwner()->GetTypeId() == TYPEID_PLAYER)
    {
        if (GetOwner()->getClass() == CLASS_WARLOCK
            || GetOwner()->getClass() == CLASS_SHAMAN        // Fire Elemental
            || GetOwner()->getClass() == CLASS_DEATH_KNIGHT) // Risen Ghoul
        {
            petType = SUMMON_PET;
        }
        else if (GetOwner()->getClass() == CLASS_HUNTER)
        {
            petType = HUNTER_PET;
            m_unitTypeMask |= UNIT_MASK_HUNTER_PET;
        }
        else
        {
            TC_LOG_ERROR("entities.pet", "Unknown type pet %u is summoned by player class %u",
                           GetEntry(), GetOwner()->getClass());
        }
    }

    uint32 creature_ID = (petType == HUNTER_PET) ? 1 : cinfo->Entry;

    SetMeleeDamageSchool(SpellSchools(cinfo->dmgschool));

    SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, float(petlevel*50));

    SetAttackTime(BASE_ATTACK, BASE_ATTACK_TIME);
    SetAttackTime(OFF_ATTACK, BASE_ATTACK_TIME);
    SetAttackTime(RANGED_ATTACK, BASE_ATTACK_TIME);

    SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
    SetFloatValue(UNIT_MOD_CAST_HASTE, 1.0f);

    //scale
    CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cinfo->family);
    if (cFamily && cFamily->MinScale > 0.0f && petType == HUNTER_PET)
    {
        float scale;
        if (getLevel() >= cFamily->MaxScaleLevel)
            scale = cFamily->MaxScale;
        else if (getLevel() <= cFamily->MinScaleLevel)
            scale = cFamily->MinScale;
        else
            scale = cFamily->MinScale + float(getLevel() - cFamily->MinScaleLevel) / cFamily->MaxScaleLevel * (cFamily->MaxScale - cFamily->MinScale);

        SetObjectScale(scale);
    }

    // Resistance
    for (uint8 i = SPELL_SCHOOL_HOLY; i < MAX_SPELL_SCHOOL; ++i)
        SetModifierValue(UnitMods(UNIT_MOD_RESISTANCE_START + i), BASE_VALUE, float(cinfo->resistance[i]));

    //health, mana, armor and resistance
    PetLevelInfo const* pInfo = sObjectMgr->GetPetLevelInfo(creature_ID, petlevel);
    if (pInfo)                                      // exist in DB
    {
        SetCreateHealth(pInfo->health);
        if (petType != HUNTER_PET) //hunter pet use focus
            SetCreateMana(pInfo->mana);

        if (pInfo->armor > 0)
            SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, float(pInfo->armor));

        for (uint8 stat = 0; stat < MAX_STATS; ++stat)
            SetCreateStat(Stats(stat), float(pInfo->stats[stat]));
    }
    else                                            // not exist in DB, use some default fake data
    {
        // remove elite bonuses included in DB values
        CreatureBaseStats const* stats = sObjectMgr->GetCreatureBaseStats(petlevel, cinfo->unit_class);
        SetCreateHealth(stats->BaseHealth[cinfo->expansion]);
        SetCreateMana(stats->BaseMana);

        SetCreateStat(STAT_STRENGTH, 22);
        SetCreateStat(STAT_AGILITY, 22);
        SetCreateStat(STAT_STAMINA, 25);
        SetCreateStat(STAT_INTELLECT, 28);
        SetCreateStat(STAT_SPIRIT, 27);
    }

    SetBonusDamage(0);
    switch (petType)
    {
        case SUMMON_PET:
        {
            // the damage bonus used for pets is either fire or shadow damage, whatever is higher
            int32 fire = GetOwner()->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_FIRE);
            int32 shadow = GetOwner()->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            int32 val = (fire > shadow) ? fire : shadow;
            if (val < 0)
                val = 0;

            SetBonusDamage(val * 0.15f);

            SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel - (petlevel / 4)));
            SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel + (petlevel / 4)));

            //SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, float(cinfo->attackpower));
            break;
        }
        case HUNTER_PET:
        {
            SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, uint32(sObjectMgr->GetXPForLevel(petlevel)*PET_XP_FACTOR));
            //these formula may not be correct; however, it is designed to be close to what it should be
            //this makes dps 0.5 of pets level
            SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel - (petlevel / 4)));
            //damage range is then petlevel / 2
            SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel + (petlevel / 4)));
            //damage is increased afterwards as strength and pet scaling modify attack power
            break;
        }
        default:
        {
            switch (GetEntry())
            {
                case 510: // mage Water Elemental
                {
                    SetBonusDamage(int32(GetOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FROST) * 0.33f));
                    break;
                }
                case 1964: //force of nature
                {
                    if (!pInfo)
                        SetCreateHealth(30 + 30*petlevel);
                    float bonusDmg = GetOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_NATURE) * 0.15f;
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel * 2.5f - (petlevel / 2) + bonusDmg));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel * 2.5f + (petlevel / 2) + bonusDmg));
                    break;
                }
                case 15352: //earth elemental 36213
                {
                    if (!pInfo)
                        SetCreateHealth(100 + 120*petlevel);
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel - (petlevel / 4)));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel + (petlevel / 4)));
                    break;
                }
                case 15438: //fire elemental
                {
                    if (!pInfo)
                    {
                        SetCreateHealth(40*petlevel);
                        SetCreateMana(28 + 10*petlevel);
                    }
                    SetBonusDamage(int32(GetOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE) * 0.5f));
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel * 4 - petlevel));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel * 4 + petlevel));
                    break;
                }
                case 19668: // Shadowfiend
                {
                    if (!pInfo)
                    {
                        SetCreateMana(28 + 10*petlevel);
                        SetCreateHealth(28 + 30*petlevel);
                    }
                    int32 bonus_dmg = int32(GetOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW)* 0.3f);
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((petlevel * 4 - petlevel) + bonus_dmg));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((petlevel * 4 + petlevel) + bonus_dmg));

                    break;
                }
                case 19833: //Snake Trap - Venomous Snake
                {
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((petlevel / 2) - 25));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((petlevel / 2) - 18));
                    break;
                }
                case 19921: //Snake Trap - Viper
                {
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel / 2 - 10));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel / 2));
                    break;
                }
                case 29264: // Feral Spirit
                {
                    if (!pInfo)
                        SetCreateHealth(30*petlevel);

                    // wolf attack speed is 1.5s
                    SetAttackTime(BASE_ATTACK, cinfo->BaseAttackTime);

                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float((petlevel * 4 - petlevel)));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float((petlevel * 4 + petlevel)));

                    SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, float(GetOwner()->GetArmor()) * 0.35f);  // Bonus Armor (35% of player armor)
                    SetModifierValue(UNIT_MOD_STAT_STAMINA, BASE_VALUE, float(GetOwner()->GetStat(STAT_STAMINA)) * 0.3f);  // Bonus Stamina (30% of player stamina)
                    if (!HasAura(58877))//prevent apply twice for the 2 wolves
                        AddAura(58877, this);//Spirit Hunt, passive, Spirit Wolves' attacks heal them and their master for 150% of damage done.
                    break;
                }
                case 31216: // Mirror Image
                {
                    SetBonusDamage(int32(GetOwner()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FROST) * 0.33f));
                    SetDisplayId(GetOwner()->GetDisplayId());
                    if (!pInfo)
                    {
                        SetCreateMana(28 + 30*petlevel);
                        SetCreateHealth(28 + 10*petlevel);
                    }
                    break;
                }
                case 27829: // Ebon Gargoyle
                {
                    if (!pInfo)
                    {
                        SetCreateMana(28 + 10*petlevel);
                        SetCreateHealth(28 + 30*petlevel);
                    }
                    SetBonusDamage(int32(GetOwner()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.5f));
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel - (petlevel / 4)));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel + (petlevel / 4)));
                    break;
                }
                case 28017: // Bloodworms
                {
                    SetCreateHealth(4 * petlevel);
                    SetBonusDamage(int32(GetOwner()->GetTotalAttackPowerValue(BASE_ATTACK) * 0.006f));
                    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(petlevel - 30 - (petlevel / 4)));
                    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(petlevel - 30 + (petlevel / 4)));
                }
            }
            break;
        }
    }

    UpdateAllStats();

    SetFullHealth();
    SetPower(POWER_MANA, GetMaxPower(POWER_MANA));
    return true;
}

bool Pet::HaveInDiet(ItemTemplate const* item) const
{
    if (!item->FoodType)
        return false;

    CreatureTemplate const* cInfo = GetCreatureTemplate();
    if (!cInfo)
        return false;

    CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cInfo->family);
    if (!cFamily)
        return false;

    uint32 diet = cFamily->PetFoodMask;
    uint32 FoodMask = 1 << (item->FoodType-1);
    return (diet & FoodMask) != 0;
}

uint32 Pet::GetCurrentFoodBenefitLevel(uint32 itemlevel) const
{
    // -5 or greater food level
    if (getLevel() <= itemlevel + 5)                         //possible to feed level 60 pet with level 55 level food for full effect
        return 35000;
    // -10..-6
    else if (getLevel() <= itemlevel + 10)                   //pure guess, but sounds good
        return 17000;
    // -14..-11
    else if (getLevel() <= itemlevel + 14)                   //level 55 food gets green on 70, makes sense to me
        return 8000;
    // -15 or less
    else
        return 0;                                           //food too low level
}

void Pet::_LoadSpellCooldowns()
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_SPELL_COOLDOWN);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());
    PreparedQueryResult cooldownsResult = CharacterDatabase.Query(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_SPELL_CHARGES);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());
    PreparedQueryResult chargesResult = CharacterDatabase.Query(stmt);

    GetSpellHistory()->LoadFromDB<Pet>(cooldownsResult, chargesResult);
}

void Pet::_LoadSpells()
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_SPELL);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            addSpell(fields[0].GetUInt32(), ActiveStates(fields[1].GetUInt8()), PETSPELL_UNCHANGED);
        }
        while (result->NextRow());
    }
}

void Pet::_SaveSpells(SQLTransaction& trans)
{
    for (PetSpellMap::iterator itr = m_spells.begin(), next = m_spells.begin(); itr != m_spells.end(); itr = next)
    {
        ++next;

        // prevent saving family passives to DB
        if (itr->second.type == PETSPELL_FAMILY)
            continue;

        PreparedStatement* stmt;

        switch (itr->second.state)
        {
            case PETSPELL_REMOVED:
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_SPELL_BY_SPELL);
                stmt->setUInt32(0, m_charmInfo->GetPetNumber());
                stmt->setUInt32(1, itr->first);
                trans->Append(stmt);

                m_spells.erase(itr);
                continue;
            case PETSPELL_CHANGED:
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_SPELL_BY_SPELL);
                stmt->setUInt32(0, m_charmInfo->GetPetNumber());
                stmt->setUInt32(1, itr->first);
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PET_SPELL);
                stmt->setUInt32(0, m_charmInfo->GetPetNumber());
                stmt->setUInt32(1, itr->first);
                stmt->setUInt8(2, itr->second.active);
                trans->Append(stmt);

                break;
            case PETSPELL_NEW:
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PET_SPELL);
                stmt->setUInt32(0, m_charmInfo->GetPetNumber());
                stmt->setUInt32(1, itr->first);
                stmt->setUInt8(2, itr->second.active);
                trans->Append(stmt);
                break;
            case PETSPELL_UNCHANGED:
                continue;
        }
        itr->second.state = PETSPELL_UNCHANGED;
    }
}

void Pet::_LoadAuras(uint32 timediff)
{
    TC_LOG_DEBUG("entities.pet", "Loading auras for %s", GetGUID().ToString().c_str());

    /*
                    0      1           2            3       4           5
    SELECT casterGuid, spell, effectMask, effectIndex, amount, baseAmount FROM pet_aura_effect WHERE guid = ?
    */

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_AURA_EFFECT);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());

    ObjectGuid casterGuid, itemGuid;
    std::map<AuraKey, AuraLoadEffectInfo> effectInfo;
    if (PreparedQueryResult effectResult = CharacterDatabase.Query(stmt))
    {
        do
        {
            Field* fields = effectResult->Fetch();
            uint32 effectIndex = fields[3].GetUInt8();
            if (effectIndex < MAX_SPELL_EFFECTS)
            {
                casterGuid.SetRawValue(fields[0].GetBinary());
                if (casterGuid.IsEmpty())
                    casterGuid = GetGUID();

                AuraKey key{ casterGuid, itemGuid, fields[1].GetUInt32(), fields[2].GetUInt32() };
                AuraLoadEffectInfo& info = effectInfo[key];
                info.Amounts[effectIndex] = fields[4].GetInt32();
                info.BaseAmounts[effectIndex] = fields[5].GetInt32();
            }
        } while (effectResult->NextRow());
    }

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_AURA);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());

    /*
                    0      1           2                3           4            5           6              7
    SELECT casterGuid, spell, effectMask, recalculateMask, stackCount, maxDuration, remainTime, remainCharges FROM pet_aura WHERE guid = ?
    */
    if (PreparedQueryResult auraResult = CharacterDatabase.Query(stmt))
    {
        do
        {
            Field* fields = auraResult->Fetch();
            // NULL guid stored - pet is the caster of the spell - see Pet::_SaveAuras
            casterGuid.SetRawValue(fields[0].GetBinary());
            if (casterGuid.IsEmpty())
                casterGuid = GetGUID();

            AuraKey key{ casterGuid, itemGuid, fields[1].GetUInt32(), fields[2].GetUInt32() };
            uint32 recalculateMask = fields[3].GetUInt32();
            uint8 stackCount = fields[4].GetUInt8();
            int32 maxDuration = fields[5].GetInt32();
            int32 remainTime = fields[6].GetInt32();
            uint8 remainCharges = fields[7].GetUInt8();

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(key.SpellId);
            if (!spellInfo)
            {
                TC_LOG_ERROR("entities.pet", "Unknown aura (spellid %u), ignore.", key.SpellId);
                continue;
            }

            // negative effects should continue counting down after logout
            if (remainTime != -1 && !spellInfo->IsPositive())
            {
                if (remainTime/IN_MILLISECONDS <= int32(timediff))
                    continue;

                remainTime -= timediff*IN_MILLISECONDS;
            }

            // prevent wrong values of remainCharges
            if (spellInfo->ProcCharges)
            {
                // we have no control over the order of applying auras and modifiers allow auras
                // to have more charges than value in SpellInfo
                if (remainCharges <= 0/* || remainCharges > spellproto->procCharges*/)
                    remainCharges = spellInfo->ProcCharges;
            }
            else
                remainCharges = 0;

            AuraLoadEffectInfo& info = effectInfo[key];
            if (Aura* aura = Aura::TryCreate(spellInfo, key.EffectMask, this, NULL, info.BaseAmounts.data(), NULL, casterGuid))
            {
                if (!aura->CanBeSaved())
                {
                    aura->Remove();
                    continue;
                }

                aura->SetLoadedState(maxDuration, remainTime, remainCharges, stackCount, recalculateMask, info.Amounts.data());
                aura->ApplyForTargets();
                TC_LOG_DEBUG("entities.pet", "Added aura spellid %u, effectmask %u", spellInfo->Id, key.EffectMask);
            }
        }
        while (auraResult->NextRow());
    }
}

void Pet::_SaveAuras(SQLTransaction& trans)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_AURA_EFFECTS);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PET_AURAS);
    stmt->setUInt32(0, m_charmInfo->GetPetNumber());
    trans->Append(stmt);

    uint8 index;
    for (AuraMap::const_iterator itr = m_ownedAuras.begin(); itr != m_ownedAuras.end(); ++itr)
    {
        // check if the aura has to be saved
        if (!itr->second->CanBeSaved() || IsPetAura(itr->second))
            continue;

        Aura* aura = itr->second;
        uint32 recalculateMask = 0;
        AuraKey key = aura->GenerateKey(recalculateMask);

        // don't save guid of caster in case we are caster of the spell - guid for pet is generated every pet load, so it won't match saved guid anyways
        if (key.Caster == GetGUID())
            key.Caster.Clear();

        index = 0;
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PET_AURA);
        stmt->setUInt32(index++, m_charmInfo->GetPetNumber());
        stmt->setBinary(index++, key.Caster.GetRawValue());
        stmt->setUInt32(index++, key.SpellId);
        stmt->setUInt32(index++, key.EffectMask);
        stmt->setUInt32(index++, recalculateMask);
        stmt->setUInt8(index++, aura->GetStackAmount());
        stmt->setInt32(index++, aura->GetMaxDuration());
        stmt->setInt32(index++, aura->GetDuration());
        stmt->setUInt8(index++, aura->GetCharges());
        trans->Append(stmt);

        for (AuraEffect const* effect : aura->GetAuraEffects())
        {
            if (effect)
            {
                index = 0;
                stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PET_AURA_EFFECT);
                stmt->setUInt32(index++, m_charmInfo->GetPetNumber());
                stmt->setBinary(index++, key.Caster.GetRawValue());
                stmt->setUInt32(index++, key.SpellId);
                stmt->setUInt32(index++, key.EffectMask);
                stmt->setUInt8(index++, effect->GetEffIndex());
                stmt->setInt32(index++, effect->GetAmount());
                stmt->setInt32(index++, effect->GetBaseAmount());
                trans->Append(stmt);
            }
        }
    }
}

bool Pet::addSpell(uint32 spellId, ActiveStates active /*= ACT_DECIDE*/, PetSpellState state /*= PETSPELL_NEW*/, PetSpellType type /*= PETSPELL_NORMAL*/)
{
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!spellInfo)
    {
        // do pet spell book cleanup
        if (state == PETSPELL_UNCHANGED)                    // spell load case
        {
            TC_LOG_ERROR("entities.pet", "Pet::addSpell: Non-existed in SpellStore spell #%u request, deleting for all pets in `pet_spell`.", spellId);

            PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_INVALID_PET_SPELL);

            stmt->setUInt32(0, spellId);

            CharacterDatabase.Execute(stmt);
        }
        else
            TC_LOG_ERROR("entities.pet", "Pet::addSpell: Non-existed in SpellStore spell #%u request.", spellId);

        return false;
    }

    PetSpellMap::iterator itr = m_spells.find(spellId);
    if (itr != m_spells.end())
    {
        if (itr->second.state == PETSPELL_REMOVED)
        {
            m_spells.erase(itr);
            state = PETSPELL_CHANGED;
        }
        else if (state == PETSPELL_UNCHANGED && itr->second.state != PETSPELL_UNCHANGED)
        {
            // can be in case spell loading but learned at some previous spell loading
            itr->second.state = PETSPELL_UNCHANGED;

            if (active == ACT_ENABLED)
                ToggleAutocast(spellInfo, true);
            else if (active == ACT_DISABLED)
                ToggleAutocast(spellInfo, false);

            return false;
        }
        else
            return false;
    }

    PetSpell newspell;
    newspell.state = state;
    newspell.type = type;

    if (active == ACT_DECIDE)                               // active was not used before, so we save it's autocast/passive state here
    {
        if (spellInfo->IsAutocastable())
            newspell.active = ACT_DISABLED;
        else
            newspell.active = ACT_PASSIVE;
    }
    else
        newspell.active = active;

    // talent: unlearn all other talent ranks (high and low)
    if (spellInfo->IsRanked())
    {
        for (PetSpellMap::const_iterator itr2 = m_spells.begin(); itr2 != m_spells.end(); ++itr2)
        {
            if (itr2->second.state == PETSPELL_REMOVED)
                continue;

            SpellInfo const* oldRankSpellInfo = sSpellMgr->GetSpellInfo(itr2->first);

            if (!oldRankSpellInfo)
                continue;

            if (spellInfo->IsDifferentRankOf(oldRankSpellInfo))
            {
                // replace by new high rank
                if (spellInfo->IsHighRankOf(oldRankSpellInfo))
                {
                    newspell.active = itr2->second.active;

                    if (newspell.active == ACT_ENABLED)
                        ToggleAutocast(oldRankSpellInfo, false);

                    unlearnSpell(itr2->first, false, false);
                    break;
                }
                // ignore new lesser rank
                else
                    return false;
            }
        }
    }

    m_spells[spellId] = newspell;

    if (spellInfo->IsPassive() && (!spellInfo->CasterAuraState || HasAuraState(AuraStateType(spellInfo->CasterAuraState))))
        CastSpell(this, spellId, true);
    else
        m_charmInfo->AddSpellToActionBar(spellInfo);

    if (newspell.active == ACT_ENABLED)
        ToggleAutocast(spellInfo, true);

    return true;
}

bool Pet::learnSpell(uint32 spell_id)
{
    // prevent duplicated entires in spell book
    if (!addSpell(spell_id))
        return false;

    if (!m_loading)
    {
        WorldPacket data(SMSG_PET_LEARNED_SPELLS, 4);
        data << uint32(spell_id);
        GetOwner()->GetSession()->SendPacket(&data);
        GetOwner()->PetSpellInitialize();
    }
    return true;
}

void Pet::InitLevelupSpellsForLevel()
{
    uint8 level = getLevel();

    if (PetLevelupSpellSet const* levelupSpells = GetCreatureTemplate()->family ? sSpellMgr->GetPetLevelupSpellList(GetCreatureTemplate()->family) : NULL)
    {
        // PetLevelupSpellSet ordered by levels, process in reversed order
        for (PetLevelupSpellSet::const_reverse_iterator itr = levelupSpells->rbegin(); itr != levelupSpells->rend(); ++itr)
        {
            // will called first if level down
            if (itr->first > level)
                unlearnSpell(itr->second, true);                 // will learn prev rank if any
            // will called if level up
            else
                learnSpell(itr->second);                        // will unlearn prev rank if any
        }
    }

    int32 petSpellsId = GetCreatureTemplate()->PetSpellDataId ? -(int32)GetCreatureTemplate()->PetSpellDataId : GetEntry();

    // default spells (can be not learned if pet level (as owner level decrease result for example) less first possible in normal game)
    if (PetDefaultSpellsEntry const* defSpells = sSpellMgr->GetPetDefaultSpellsEntry(petSpellsId))
    {
        for (uint8 i = 0; i < MAX_CREATURE_SPELL_DATA_SLOT; ++i)
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(defSpells->spellid[i]);
            if (!spellInfo)
                continue;

            // will called first if level down
            if (spellInfo->SpellLevel > level)
                unlearnSpell(spellInfo->Id, true);
            // will called if level up
            else
                learnSpell(spellInfo->Id);
        }
    }
}

bool Pet::unlearnSpell(uint32 spell_id, bool learn_prev, bool clear_ab)
{
    if (removeSpell(spell_id, learn_prev, clear_ab))
    {
        if (!m_loading)
        {
            WorldPacket data(SMSG_PET_UNLEARNED_SPELLS, 4);
            data << uint32(spell_id);
            GetOwner()->GetSession()->SendPacket(&data);
        }
        return true;
    }
    return false;
}

bool Pet::removeSpell(uint32 spell_id, bool learn_prev, bool clear_ab)
{
    PetSpellMap::iterator itr = m_spells.find(spell_id);
    if (itr == m_spells.end())
        return false;

    if (itr->second.state == PETSPELL_REMOVED)
        return false;

    if (itr->second.state == PETSPELL_NEW)
        m_spells.erase(itr);
    else
        itr->second.state = PETSPELL_REMOVED;

    RemoveAurasDueToSpell(spell_id);

    if (learn_prev)
    {
        if (uint32 prev_id = sSpellMgr->GetPrevSpellInChain (spell_id))
            learnSpell(prev_id);
        else
            learn_prev = false;
    }

    // if remove last rank or non-ranked then update action bar at server and client if need
    if (clear_ab && !learn_prev && m_charmInfo->RemoveSpellFromActionBar(spell_id))
    {
        if (!m_loading)
            GetOwner()->PetSpellInitialize(); // need update action bar for last removed rank
    }

    return true;
}

void Pet::CleanupActionBar()
{
    for (uint8 i = 0; i < MAX_UNIT_ACTION_BAR_INDEX; ++i)
        if (UnitActionBarEntry const* ab = m_charmInfo->GetActionBarEntry(i))
            if (ab->GetAction() && ab->IsActionBarForSpell())
            {
                if (!HasSpell(ab->GetAction()))
                    m_charmInfo->SetActionBar(i, 0, ACT_PASSIVE);
                else if (ab->GetType() == ACT_ENABLED)
                {
                    if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(ab->GetAction()))
                        ToggleAutocast(spellInfo, true);
                }
            }
}

void Pet::InitPetCreateSpells()
{
    m_charmInfo->InitPetActionBar();
    m_spells.clear();

    LearnPetPassives();
    InitLevelupSpellsForLevel();

    CastPetAuras(false);
}

bool Pet::resetTalents()
{
    /* TODO: 6.x remove pet talents
    Player* player = GetOwner();

    // not need after this call
    if (player->HasAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS))
        player->RemoveAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS, true);

    CreatureTemplate const* ci = GetCreatureTemplate();
    if (!ci)
        return false;
    // Check pet talent type
    CreatureFamilyEntry const* pet_family = sCreatureFamilyStore.LookupEntry(ci->family);
    if (!pet_family || pet_family->PetTalentType < 0)
        return false;

    uint8 level = getLevel();
    uint32 talentPointsForLevel = GetMaxTalentPointsForLevel(level);

    if (m_usedTalentCount == 0)
    {
        SetFreeTalentPoints(talentPointsForLevel);
        return false;
    }

    for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);

        if (!talentInfo)
            continue;

        TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);

        if (!talentTabInfo)
            continue;

        // unlearn only talents for pets family talent type
        if (!((1 << pet_family->PetTalentType) & talentTabInfo->petTalentMask))
            continue;

        for (uint8 j = 0; j < MAX_TALENT_RANK; ++j)
        {
            for (PetSpellMap::const_iterator itr = m_spells.begin(); itr != m_spells.end();)
            {
                if (itr->second.state == PETSPELL_REMOVED)
                {
                    ++itr;
                    continue;
                }
                // remove learned spells (all ranks)
                uint32 itrFirstId = sSpellMgr->GetFirstSpellInChain(itr->first);

                // unlearn if first rank is talent or learned by talent
                if (itrFirstId == talentInfo->RankID[j] || sSpellMgr->IsSpellLearnToSpell(talentInfo->RankID[j], itrFirstId))
                {
                    unlearnSpell(itr->first, false);
                    itr = m_spells.begin();
                    continue;
                }
                else
                    ++itr;
            }
        }
    }

    SetFreeTalentPoints(talentPointsForLevel);

    if (!m_loading)
        player->PetSpellInitialize();*/
    return true;
}

void Pet::resetTalentsForAllPetsOf(Player* /*owner*/, Pet* /*onlinePet*/ /*= NULL*/)
{
    /* TODO: 6.x remove pet talents
    // not need after this call
    if (owner->HasAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS))
        owner->RemoveAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS, true);

    // reset for online
    if (onlinePet)
        onlinePet->resetTalents();

    // now need only reset for offline pets (all pets except online case)
    uint32 exceptPetNumber = onlinePet ? onlinePet->GetCharmInfo()->GetPetNumber() : 0;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PET);
    stmt->setUInt64(0, owner->GetGUID().GetCounter());
    stmt->setUInt32(1, exceptPetNumber);
    PreparedQueryResult resultPets = CharacterDatabase.Query(stmt);

    // no offline pets
    if (!resultPets)
        return;

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_SPELL_LIST);
    stmt->setUInt64(0, owner->GetGUID().GetCounter());
    stmt->setUInt32(1, exceptPetNumber);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
        return;

    bool need_comma = false;
    std::ostringstream ss;
    ss << "DELETE FROM pet_spell WHERE guid IN (";

    do
    {
        Field* fields = resultPets->Fetch();

        uint32 id = fields[0].GetUInt32();

        if (need_comma)
            ss << ',';

        ss << id;

        need_comma = true;
    } while (resultPets->NextRow());

    ss << ") AND spell IN (";

    bool need_execute = false;
    do
    {
        Field* fields = result->Fetch();

        uint32 spell = fields[0].GetUInt32();

        if (!GetTalentSpellCost(spell))
            continue;

        if (need_execute)
            ss << ',';

        ss << spell;

        need_execute = true;
    }
    while (result->NextRow());

    if (!need_execute)
        return;

    ss << ')';

    CharacterDatabase.Execute(ss.str().c_str());*/
}

void Pet::InitTalentForLevel()
{
    /* TODO: 6.x remove/update pet talents
    uint8 level = getLevel();
    uint32 talentPointsForLevel = GetMaxTalentPointsForLevel(level);
    // Reset talents in case low level (on level down) or wrong points for level (hunter can unlearn TP increase talent)
    if (talentPointsForLevel == 0 || m_usedTalentCount > talentPointsForLevel)
        resetTalents(); // Remove all talent points

    SetFreeTalentPoints(talentPointsForLevel - m_usedTalentCount);

    if (!m_loading)
        GetOwner()->SendTalentsInfoData(true);
    */
}

uint8 Pet::GetMaxTalentPointsForLevel(uint8 level)
{
    uint8 points = (level >= 20) ? ((level - 16) / 4) : 0;
    // Mod points from owner SPELL_AURA_MOD_PET_TALENT_POINTS
    points += GetOwner()->GetTotalAuraModifier(SPELL_AURA_MOD_PET_TALENT_POINTS);
    return points;
}

void Pet::ToggleAutocast(SpellInfo const* spellInfo, bool apply)
{
    if (!spellInfo->IsAutocastable())
        return;

    uint32 spellid = spellInfo->Id;

    PetSpellMap::iterator itr = m_spells.find(spellid);
    if (itr == m_spells.end())
        return;

    uint32 i;

    if (apply)
    {
        for (i = 0; i < m_autospells.size() && m_autospells[i] != spellid; ++i)
            ;                                               // just search

        if (i == m_autospells.size())
        {
            m_autospells.push_back(spellid);

            if (itr->second.active != ACT_ENABLED)
            {
                itr->second.active = ACT_ENABLED;
                if (itr->second.state != PETSPELL_NEW)
                    itr->second.state = PETSPELL_CHANGED;
            }
        }
    }
    else
    {
        AutoSpellList::iterator itr2 = m_autospells.begin();
        for (i = 0; i < m_autospells.size() && m_autospells[i] != spellid; ++i, ++itr2)
            ;                                               // just search

        if (i < m_autospells.size())
        {
            m_autospells.erase(itr2);
            if (itr->second.active != ACT_DISABLED)
            {
                itr->second.active = ACT_DISABLED;
                if (itr->second.state != PETSPELL_NEW)
                    itr->second.state = PETSPELL_CHANGED;
            }
        }
    }
}

bool Pet::IsPermanentPetFor(Player* owner) const
{
    switch (getPetType())
    {
        case SUMMON_PET:
            switch (owner->getClass())
            {
                case CLASS_WARLOCK:
                    return GetCreatureTemplate()->type == CREATURE_TYPE_DEMON;
                case CLASS_DEATH_KNIGHT:
                    return GetCreatureTemplate()->type == CREATURE_TYPE_UNDEAD;
                case CLASS_MAGE:
                    return GetCreatureTemplate()->type == CREATURE_TYPE_ELEMENTAL;
                default:
                    return false;
            }
        case HUNTER_PET:
            return true;
        default:
            return false;
    }
}

bool Pet::Create(ObjectGuid::LowType guidlow, Map* map, uint32 Entry)
{
    ASSERT(map);
    SetMap(map);

    Object::_Create(ObjectGuid::Create<HighGuid::Pet>(map->GetId(), Entry, guidlow));

    m_DBTableGuid = guidlow;
    m_originalEntry = Entry;

    if (!InitEntry(Entry))
        return false;

    // Force regen flag for player pets, just like we do for players themselves
    SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_REGENERATE_POWER);
    SetSheath(SHEATH_STATE_MELEE);

    return true;
}

bool Pet::HasSpell(uint32 spell) const
{
    PetSpellMap::const_iterator itr = m_spells.find(spell);
    return itr != m_spells.end() && itr->second.state != PETSPELL_REMOVED;
}

// Get all passive spells in our skill line
void Pet::LearnPetPassives()
{
    CreatureTemplate const* cInfo = GetCreatureTemplate();
    if (!cInfo)
        return;

    CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cInfo->family);
    if (!cFamily)
        return;

    PetFamilySpellsStore::const_iterator petStore = sPetFamilySpellsStore.find(cFamily->ID);
    if (petStore != sPetFamilySpellsStore.end())
    {
        // For general hunter pets skill 270
        // Passive 01~10, Passive 00 (20782, not used), Ferocious Inspiration (34457)
        // Scale 01~03 (34902~34904, bonus from owner, not used)
        for (PetFamilySpellsSet::const_iterator petSet = petStore->second.begin(); petSet != petStore->second.end(); ++petSet)
            addSpell(*petSet, ACT_DECIDE, PETSPELL_NEW, PETSPELL_FAMILY);
    }
}

void Pet::CastPetAuras(bool current)
{
    Player* owner = GetOwner();

    if (!IsPermanentPetFor(owner))
        return;

    for (PetAuraSet::const_iterator itr = owner->m_petAuras.begin(); itr != owner->m_petAuras.end();)
    {
        PetAura const* pa = *itr;
        ++itr;

        if (!current && pa->IsRemovedOnChangePet())
            owner->RemovePetAura(pa);
        else
            CastPetAura(pa);
    }
}

void Pet::CastPetAura(PetAura const* aura)
{
    uint32 auraId = aura->GetAura(GetEntry());
    if (!auraId)
        return;

    if (auraId == 35696)                                      // Demonic Knowledge
    {
        int32 basePoints = CalculatePct(aura->GetDamage(), GetStat(STAT_STAMINA) + GetStat(STAT_INTELLECT));
        CastCustomSpell(this, auraId, &basePoints, NULL, NULL, true);
    }
    else
        CastSpell(this, auraId, true);
}

bool Pet::IsPetAura(Aura const* aura)
{
    Player* owner = GetOwner();

    // if the owner has that pet aura, return true
    for (PetAuraSet::const_iterator itr = owner->m_petAuras.begin(); itr != owner->m_petAuras.end(); ++itr)
    {
        if ((*itr)->GetAura(GetEntry()) == aura->GetId())
            return true;
    }
    return false;
}

void Pet::learnSpellHighRank(uint32 spellid)
{
    learnSpell(spellid);

    if (uint32 next = sSpellMgr->GetNextSpellInChain(spellid))
        learnSpellHighRank(next);
}

void Pet::SynchronizeLevelWithOwner()
{
    Player* owner = GetOwner();

    switch (getPetType())
    {
        // always same level
        case SUMMON_PET:
            GivePetLevel(owner->getLevel());
            break;
        // can't be greater owner level
        case HUNTER_PET:
            if (getLevel() > owner->getLevel())
                GivePetLevel(owner->getLevel());
            else if (getLevel() + 5 < owner->getLevel())
                GivePetLevel(owner->getLevel() - 5);
            break;
        default:
            break;
    }
}

Player* Pet::GetOwner() const
{
    return Minion::GetOwner()->ToPlayer();
}

void Pet::SetDisplayId(uint32 modelId)
{
    Guardian::SetDisplayId(modelId);

    if (!isControlled())
        return;

    if (GetOwner()->GetGroup())
        GetOwner()->SetGroupUpdateFlag(GROUP_UPDATE_FLAG_PET_MODEL_ID);
}
