/*
 * Copyright (C) 2008 - 2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005 - 2009 MaNGOS <http://getmangos.com/>
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

#ifndef _UPDATEFIELDS_H
#define _UPDATEFIELDS_H

// Auto generated for version 6, 0, 2, 19034

enum ObjectFields
{
    OBJECT_FIELD_GUID                                      = 0x000, // Size: 2, Flags: PUBLIC
    OBJECT_FIELD_DATA                                      = 0x002, // Size: 2, Flags: PUBLIC
    OBJECT_FIELD_TYPE                                      = 0x004, // Size: 1, Flags: PUBLIC
    OBJECT_FIELD_ENTRY                                     = 0x005, // Size: 1, Flags: DYNAMIC
    OBJECT_DYNAMIC_FLAGS                                   = 0x006, // Size: 1, Flags: DYNAMIC, URGENT
    OBJECT_FIELD_SCALE_X                                   = 0x007, // Size: 1, Flags: PUBLIC
    OBJECT_END                                             = 0x008,
};

enum ObjectDynamicFields
{
    OBJECT_DYNAMIC_END                                     = 0x000,
};

enum ItemFields
{
    ITEM_FIELD_OWNER                                       = OBJECT_END + 0x000, // Size: 2, Flags: PUBLIC
    ITEM_FIELD_CONTAINED                                   = OBJECT_END + 0x004 - 2, // Size: 2, Flags: PUBLIC
    ITEM_FIELD_CREATOR                                     = OBJECT_END + 0x008 - 2 - 2, // Size: 2, Flags: PUBLIC
    ITEM_FIELD_GIFTCREATOR                                 = OBJECT_END + 0x00C - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    ITEM_FIELD_STACK_COUNT                                 = OBJECT_END + 0x010 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    ITEM_FIELD_DURATION                                    = OBJECT_END + 0x011 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    ITEM_FIELD_SPELL_CHARGES                               = OBJECT_END + 0x012 - 2 - 2 - 2 - 2, // Size: 5, Flags: OWNER
    ITEM_FIELD_FLAGS                                       = OBJECT_END + 0x017 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    ITEM_FIELD_ENCHANTMENT                                 = OBJECT_END + 0x018 - 2 - 2 - 2 - 2, // Size: 39, Flags: PUBLIC
    ITEM_FIELD_PROPERTY_SEED                               = OBJECT_END + 0x03F - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    ITEM_FIELD_RANDOM_PROPERTIES_ID                        = OBJECT_END + 0x040 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    ITEM_FIELD_DURABILITY                                  = OBJECT_END + 0x041 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    ITEM_FIELD_MAXDURABILITY                               = OBJECT_END + 0x042 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    ITEM_FIELD_CREATE_PLAYED_TIME                          = OBJECT_END + 0x043 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    ITEM_FIELD_MODIFIERS_MASK                              = OBJECT_END + 0x044 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    ITEM_FIELD_CONTEXT                                     = OBJECT_END + 0x045 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    ITEM_END                                               = OBJECT_END + 0x046 - 2 - 2 - 2 - 2,
};

enum ItemDynamicFields
{
    ITEM_DYNAMIC_FIELD_MODIFIERS                           = OBJECT_DYNAMIC_END + 0x000, //  Flags: OWNER
    ITEM_DYNAMIC_FIELD_BONUSLIST_IDS                       = OBJECT_DYNAMIC_END + 0x001, //  Flags: OWNER
    ITEM_DYNAMIC_END                                       = OBJECT_DYNAMIC_END + 0x002,
};

enum ContainerFields
{
    //! \todo only 72?
    CONTAINER_FIELD_SLOT_1                                 = ITEM_END + 0x000, // Size: 72, Flags: PUBLIC
    CONTAINER_FIELD_NUM_SLOTS                              = ITEM_END + 0x090 - 72, // Size: 1, Flags: PUBLIC
    CONTAINER_END                                          = ITEM_END + 0x091 - 72,
};

enum ContainerDynamicFields
{
    CONTAINER_DYNAMIC_END                                  = ITEM_DYNAMIC_END + 0x000,
};

enum UnitFields
{
    UNIT_FIELD_CHARM                                       = OBJECT_END + 0x000, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_SUMMON                                      = OBJECT_END + 0x004 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_CRITTER                                     = OBJECT_END + 0x008 - 2 - 2, // Size: 2, Flags: PRIVATE
    UNIT_FIELD_CHARMEDBY                                   = OBJECT_END + 0x00C - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_SUMMONEDBY                                  = OBJECT_END + 0x010 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_CREATEDBY                                   = OBJECT_END + 0x014 - 2 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_DEMON_CREATOR                               = OBJECT_END + 0x018 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_TARGET                                      = OBJECT_END + 0x01C - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_BATTLE_PET_COMPANION_GUID                   = OBJECT_END + 0x020 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_CHANNEL_OBJECT                              = OBJECT_END + 0x026 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC, URGENT
    UNIT_CHANNEL_SPELL                                     = OBJECT_END + 0x02A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC, URGENT
    UNIT_FIELD_SUMMONED_BY_HOME_REALM                      = OBJECT_END + 0x02B - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_BYTES_0                                     = OBJECT_END + 0x02C - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_DISPLAY_POWER                               = OBJECT_END + 0x02D - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_OVERRIDE_DISPLAY_POWER_ID                   = OBJECT_END + 0x02E - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_HEALTH                                      = OBJECT_END + 0x02F - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_POWER                                       = OBJECT_END + 0x030 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 6, Flags: PUBLIC, URGENT_SELF_ONLY
    UNIT_FIELD_MAXHEALTH                                   = OBJECT_END + 0x036 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_MAXPOWER                                    = OBJECT_END + 0x037 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 6, Flags: PUBLIC
    UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER                   = OBJECT_END + 0x03D - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 6, Flags: PRIVATE, OWNER, UNIT_ALL
    UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER       = OBJECT_END + 0x043 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 6, Flags: PRIVATE, OWNER, UNIT_ALL
    UNIT_FIELD_LEVEL                                       = OBJECT_END + 0x049 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_EFFECTIVE_LEVEL                             = OBJECT_END + 0x04A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_FACTIONTEMPLATE                             = OBJECT_END + 0x04B - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_VIRTUAL_ITEM_SLOT_ID                              = OBJECT_END + 0x04C - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 3, Flags: PUBLIC
    UNIT_FIELD_FLAGS                                       = OBJECT_END + 0x04F - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_FLAGS_2                                     = OBJECT_END + 0x050 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_FLAGS_3                                     = OBJECT_END + 0x051 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_AURASTATE                                   = OBJECT_END + 0x052 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_BASEATTACKTIME                              = OBJECT_END + 0x053 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 2, Flags: PUBLIC
    UNIT_FIELD_RANGEDATTACKTIME                            = OBJECT_END + 0x055 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PRIVATE
    UNIT_FIELD_BOUNDINGRADIUS                              = OBJECT_END + 0x056 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_COMBATREACH                                 = OBJECT_END + 0x057 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_DISPLAYID                                   = OBJECT_END + 0x058 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: DYNAMIC, URGENT
    UNIT_FIELD_NATIVEDISPLAYID                             = OBJECT_END + 0x059 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC, URGENT
    UNIT_FIELD_MOUNTDISPLAYID                              = OBJECT_END + 0x05A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC, URGENT
    UNIT_FIELD_MINDAMAGE                                   = OBJECT_END + 0x05B - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PRIVATE, OWNER, SPECIAL_INFO
    UNIT_FIELD_MAXDAMAGE                                   = OBJECT_END + 0x05C - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PRIVATE, OWNER, SPECIAL_INFO
    UNIT_FIELD_MINOFFHANDDAMAGE                            = OBJECT_END + 0x05D - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PRIVATE, OWNER, SPECIAL_INFO
    UNIT_FIELD_MAXOFFHANDDAMAGE                            = OBJECT_END + 0x05E - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PRIVATE, OWNER, SPECIAL_INFO
    UNIT_FIELD_BYTES_1                                     = OBJECT_END + 0x05F - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_PETNUMBER                                   = OBJECT_END + 0x060 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_PET_NAME_TIMESTAMP                          = OBJECT_END + 0x061 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_PETEXPERIENCE                               = OBJECT_END + 0x062 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    UNIT_FIELD_PETNEXTLEVELEXP                             = OBJECT_END + 0x063 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: OWNER
    UNIT_MOD_CAST_SPEED                                    = OBJECT_END + 0x064 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_MOD_CAST_HASTE                                    = OBJECT_END + 0x065 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_MOD_HASTE                                   = OBJECT_END + 0x066 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_MOD_RANGED_HASTE                            = OBJECT_END + 0x067 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_MOD_HASTE_REGEN                             = OBJECT_END + 0x068 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_CREATED_BY_SPELL                                  = OBJECT_END + 0x069 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC
    UNIT_NPC_FLAGS_UMNWO0                                         = OBJECT_END + 0x06A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2, // Size: 1, Flags: PUBLIC, DYNAMIC
    UNIT_NPC_FLAGS                                         = OBJECT_END + 0x06A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 2, Flags: PUBLIC, DYNAMIC
    UNIT_NPC_EMOTESTATE                                    = OBJECT_END + 0x06C - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_STAT                                        = OBJECT_END + 0x06D - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 5, Flags: PRIVATE, OWNER
    UNIT_FIELD_POSSTAT                                     = OBJECT_END + 0x072 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 5, Flags: PRIVATE, OWNER
    UNIT_FIELD_NEGSTAT                                     = OBJECT_END + 0x077 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 5, Flags: PRIVATE, OWNER
    UNIT_FIELD_RESISTANCES                                 = OBJECT_END + 0x07C - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 7, Flags: PRIVATE, OWNER, SPECIAL_INFO
    UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE                  = OBJECT_END + 0x083 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 7, Flags: PRIVATE, OWNER
    UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE                  = OBJECT_END + 0x08A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1, // Size: 7, Flags: PRIVATE, OWNER
    UNIT_FIELD_BASE_MANA                                   = OBJECT_END + 0x092 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_BASE_HEALTH                                 = OBJECT_END + 0x093 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_BYTES_2                                     = OBJECT_END + 0x094 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_ATTACK_POWER                                = OBJECT_END + 0x095 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_ATTACK_POWER_MOD_POS                        = OBJECT_END + 0x096 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_ATTACK_POWER_MOD_NEG                        = OBJECT_END + 0x097 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_ATTACK_POWER_MULTIPLIER                     = OBJECT_END + 0x098 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_RANGED_ATTACK_POWER                         = OBJECT_END + 0x099 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_RANGED_ATTACK_POWER_MOD_POS                 = OBJECT_END + 0x09A - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_RANGED_ATTACK_POWER_MOD_NEG                 = OBJECT_END + 0x09B - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER              = OBJECT_END + 0x09C - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_MINRANGEDDAMAGE                             = OBJECT_END + 0x09D - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_MAXRANGEDDAMAGE                             = OBJECT_END + 0x09E - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_POWER_COST_MODIFIER                         = OBJECT_END + 0x09F - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 7, Flags: PRIVATE, OWNER
    UNIT_FIELD_POWER_COST_MULTIPLIER                       = OBJECT_END + 0x0A6 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 7, Flags: PRIVATE, OWNER
    UNIT_FIELD_MAXHEALTHMODIFIER                           = OBJECT_END + 0x0AD - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PRIVATE, OWNER
    UNIT_FIELD_HOVERHEIGHT                                 = OBJECT_END + 0x0AE - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_MIN_ITEM_LEVEL                              = OBJECT_END + 0x0B0 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_MAXITEMLEVEL                                = OBJECT_END + 0x0B1 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_WILD_BATTLEPET_LEVEL                        = OBJECT_END + 0x0B2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_BATTLEPET_COMPANION_NAME_TIMESTAMP          = OBJECT_END + 0x0B3 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_INTERACT_SPELLID                            = OBJECT_END + 0x0B4 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: PUBLIC
    UNIT_FIELD_STATE_SPELL_VISUAL_ID                       = OBJECT_END + 0x0B5 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: DYNAMIC, URGENT
    UNIT_FIELD_STATE_ANIM_ID                               = OBJECT_END + 0x0B6 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: DYNAMIC, URGENT
    UNIT_FIELD_STATE_ANIM_KIT_ID                           = OBJECT_END + 0x0B7 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 1, Flags: DYNAMIC, URGENT
    UNIT_FIELD_STATE_WORLD_EFFECT_ID                       = OBJECT_END + 0x0B8 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1, // Size: 4, Flags: DYNAMIC, URGENT
    UNIT_FIELD_garrisonFollowerGivenNameID = OBJECT_END + 0x0B8 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1 + 1, // Size: 1
    UNIT_FIELD_garrisonFollowerFamilyNameID = OBJECT_END + 0x0B8 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1 + 1 + 1, // Size: 1
    UNIT_FIELD_SCALE_DURATION                              = OBJECT_END + 0x0BC - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1+1+1, // Size: 1, Flags: PUBLIC
    UNIT_END                                               = OBJECT_END + 0x0BF - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2+1 - 1 - 1+1+1 - 1 - 1,
};

enum UnitDynamicFields
{
    UNIT_DYNAMIC_FIELD_PASSIVE_SPELLS                      = OBJECT_DYNAMIC_END + 0x000, //  Flags: PUBLIC, URGENT
    UNIT_DYNAMIC_FIELD_WORLD_EFFECTS                       = OBJECT_DYNAMIC_END + 0x001, //  Flags: PUBLIC, URGENT
    UNIT_DYNAMIC_END                                       = OBJECT_DYNAMIC_END + 0x002,
};

enum PlayerFields
{
    PLAYER_DUEL_ARBITER                                    = UNIT_END + 0x000, // Size: 2, Flags: PUBLIC
    PLAYER_FLAGS                                           = UNIT_END + 0x00C - 2 - 4 - 4, // Size: 1, Flags: PUBLIC
    PLAYER_GUILDRANK                                       = UNIT_END + 0x00E - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_GUILDDELETE_DATE                                = UNIT_END + 0x00F - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_GUILDLEVEL                                      = UNIT_END + 0x010 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_BYTES                                           = UNIT_END + 0x011 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_BYTES_2                                         = UNIT_END + 0x012 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_BYTES_3                                         = UNIT_END + 0x013 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_DUEL_TEAM                                       = UNIT_END + 0x014 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_GUILD_TIMESTAMP                                 = UNIT_END + 0x015 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_QUEST_LOG                                       = UNIT_END + 0x016 - 2 - 4 - 4 - 1, // Size: 750, Flags: PARTY_MEMBER
    PLAYER_VISIBLE_ITEM                                    = UNIT_END + 0x304 - 2 - 4 - 4 - 1, // Size: 57, Flags: PUBLIC
    PLAYER_CHOSEN_TITLE                                    = UNIT_END + 0x33D - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_FAKE_INEBRIATION                                = UNIT_END + 0x33E - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_FIELD_VIRTUAL_PLAYER_REALM                      = UNIT_END + 0x33F - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_FIELD_CURRENT_SPEC_ID                           = UNIT_END + 0x340 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_FIELD_TAXI_MOUNT_ANIM_KIT_ID                    = UNIT_END + 0x341 - 2 - 4 - 4 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_FIELD_CURRENT_BATTLE_PET_BREED_QUALITY          = UNIT_END + 0x344 - 2 - 4 - 4 - 1 - 1 - 1, // Size: 1, Flags: PUBLIC
    PLAYER_END_NOT_SELF                                    = UNIT_END + 0x345 - 2 - 4 - 4 - 1 - 1 - 1,
    PLAYER_FIELD_INV_SLOT_HEAD                             = UNIT_END + 0x345 - 2 - 4 - 4 - 1 - 1 - 1, // Size: 172, Flags: PRIVATE
    PLAYER_FARSIGHT                                        = UNIT_END + 0x625 - 2 - 4 - 4 - 1 - 1 - 1 - 564, // Size: 2, Flags: PRIVATE
    PLAYER__FIELD_KNOWN_TITLES                             = UNIT_END + 0x629 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 10, Flags: PRIVATE
    PLAYER_FIELD_COINAGE                                   = UNIT_END + 0x633 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 2, Flags: PRIVATE
    PLAYER_XP                                              = UNIT_END + 0x635 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_NEXT_LEVEL_XP                                   = UNIT_END + 0x636 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_SKILL_LINEID                                    = UNIT_END + 0x637 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 448, Flags: PRIVATE
    PLAYER_CHARACTER_POINTS                                = UNIT_END + 0x7F7 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MAX_TALENT_TIERS                          = UNIT_END + 0x7F8 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_TRACK_CREATURES                                 = UNIT_END + 0x7F9 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_TRACK_RESOURCES                                 = UNIT_END + 0x7FA - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_EXPERTISE                                       = UNIT_END + 0x7FB - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_OFFHAND_EXPERTISE                               = UNIT_END + 0x7FC - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_RANGED_EXPERTISE                          = UNIT_END + 0x7FD - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_COMBAT_RATING_EXPERTISE                   = UNIT_END + 0x7FE - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_BLOCK_PERCENTAGE                                = UNIT_END + 0x7FF - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_DODGE_PERCENTAGE                                = UNIT_END + 0x800 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_PARRY_PERCENTAGE                                = UNIT_END + 0x801 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_CRIT_PERCENTAGE                                 = UNIT_END + 0x802 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_RANGED_CRIT_PERCENTAGE                          = UNIT_END + 0x803 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_OFFHAND_CRIT_PERCENTAGE                         = UNIT_END + 0x804 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_SPELL_CRIT_PERCENTAGE1                          = UNIT_END + 0x805 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 7, Flags: PRIVATE
    PLAYER_SHIELD_BLOCK                                    = UNIT_END + 0x80C - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_SHIELD_BLOCK_CRIT_PERCENTAGE                    = UNIT_END + 0x80D - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_MASTERY                                         = UNIT_END + 0x80E - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_AMPLIFY                                         = UNIT_END + 0x80F - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_MULTISTRIKE                                     = UNIT_END + 0x810 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_MULTISTRIKE_EFFECT                              = UNIT_END + 0x811 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_READINESS                                       = UNIT_END + 0x812 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_SPEED                                           = UNIT_END + 0x813 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_LIFESTEAL                                       = UNIT_END + 0x814 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_AVOIDANCE                                       = UNIT_END + 0x815 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_STURDINESS                                      = UNIT_END + 0x816 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_CLEAVE                                          = UNIT_END + 0x817 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_PVP_POWER_DAMAGE                          = UNIT_END + 0x81A - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_PVP_POWER_HEALING                         = UNIT_END + 0x81B - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_EXPLORED_ZONES_1                                = UNIT_END + 0x81C - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 200, Flags: PRIVATE
    PLAYER_REST_STATE_EXPERIENCE                           = UNIT_END + 0x8E4 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_DAMAGE_DONE_POS                       = UNIT_END + 0x8E5 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 7, Flags: PRIVATE
    PLAYER_FIELD_MOD_DAMAGE_DONE_NEG                       = UNIT_END + 0x8EC - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 7, Flags: PRIVATE
    PLAYER_FIELD_MOD_DAMAGE_DONE_PCT                       = UNIT_END + 0x8F3 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 7, Flags: PRIVATE
    PLAYER_FIELD_MOD_HEALING_DONE_POS                      = UNIT_END + 0x8FA - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_HEALING_PCT                           = UNIT_END + 0x8FB - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_HEALING_DONE_PCT                      = UNIT_END + 0x8FC - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_PERIODIC_HEALING_DONE_PERCENT         = UNIT_END + 0x8FD - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_WEAPON_DMG_MULTIPLIERS                    = UNIT_END + 0x8FE - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1, // Size: 3, Flags: PRIVATE
    PLAYER_FIELD_MOD_SPELL_POWER_PCT                       = UNIT_END + 0x904 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_RESILIENCE_PERCENT                    = UNIT_END + 0x905 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_OVERRIDE_SPELL_POWER_BY_AP_PCT            = UNIT_END + 0x906 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_OVERRIDE_AP_BY_SPELL_POWER_PERCENT        = UNIT_END + 0x907 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_TARGET_RESISTANCE                     = UNIT_END + 0x908 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_TARGET_PHYSICAL_RESISTANCE            = UNIT_END + 0x909 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_BYTES                                     = UNIT_END + 0x90B - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3, // Size: 1, Flags: PRIVATE
    PLAYER_SELF_RES_SPELL                                  = UNIT_END + 0x90C - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_PVP_MEDALS                                = UNIT_END + 0x90D - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_BUYBACK_PRICE_1                           = UNIT_END + 0x90E - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 12, Flags: PRIVATE
    PLAYER_FIELD_BUYBACK_TIMESTAMP_1                       = UNIT_END + 0x91A - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 12, Flags: PRIVATE
    PLAYER_FIELD_KILLS                                     = UNIT_END + 0x926 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_LIFETIME_HONORABLE_KILLS                  = UNIT_END + 0x927 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_WATCHED_FACTION_INDEX                     = UNIT_END + 0x928 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_COMBAT_RATING_1                           = UNIT_END + 0x929 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 32, Flags: PRIVATE
    PLAYER_FIELD_ARENA_TEAM_INFO_1_1                       = UNIT_END + 0x949 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 36, Flags: PRIVATE
    PLAYER_FIELD_MAX_LEVEL                                 = UNIT_END + 0x96D - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_RUNE_REGEN_1                                    = UNIT_END + 0x96E - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 4, Flags: PRIVATE
    PLAYER_NO_REAGENT_COST_1                               = UNIT_END + 0x972 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 4, Flags: PRIVATE
    PLAYER_FIELD_GLYPH_SLOTS_1                             = UNIT_END + 0x976 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 6, Flags: PRIVATE
    PLAYER_FIELD_GLYPHS_1                                  = UNIT_END + 0x97C - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 6, Flags: PRIVATE
    PLAYER_GLYPHS_ENABLED                                  = UNIT_END + 0x982 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_PET_SPELL_POWER                                 = UNIT_END + 0x983 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_RESEARCHING_1                             = UNIT_END + 0x984 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1, // Size: 8, Flags: PRIVATE
    PLAYER_PROFESSION_SKILL_LINE_1                         = UNIT_END + 0x98E - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2, // Size: 2, Flags: PRIVATE
    PLAYER_FIELD_UI_HIT_MODIFIER                           = UNIT_END + 0x990 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_UI_SPELL_HIT_MODIFIER                     = UNIT_END + 0x991 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_HOME_REALM_TIME_OFFSET                    = UNIT_END + 0x992 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_MOD_PET_HASTE                             = UNIT_END + 0x993 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_SUMMONED_BATTLE_PET_ID                    = UNIT_END + 0x994 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2, // Size: 2, Flags: PRIVATE
    //!\ override spells id?
    PLAYER_FIELD_BYTES2                                    = UNIT_END + 0x998 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2, // Size: 1, Flags: PRIVATE, URGENT_SELF_ONLY
    PLAYER_FIELD_LFG_BONUS_FACTION_ID                      = UNIT_END + 0x999 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_LOOT_SPEC_ID                              = UNIT_END + 0x99A - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_OVERRIDE_ZONE_PVP_TYPE                    = UNIT_END + 0x99B - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2, // Size: 1, Flags: PRIVATE, URGENT_SELF_ONLY
    PLAYER_FIELD_ITEM_LEVEL_DELTA                          = UNIT_END + 0x99C - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2, // Size: 1, Flags: PRIVATE
    PLAYER_FIELD_BAG_SLOT_FLAGS                            = UNIT_END + 0x99D - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2, // Size: 4, Flags: PRIVATE
    PLAYER_LOCAL_bankAutoSortDisabled                      = UNIT_END + 0x99D - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2+4,// Size: 1
    PLAYER_local_bankBagSlotAutoSortDisabled               = UNIT_END + 0x99D - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2+4+1,// Size: 1
    PLAYER_END                                             = UNIT_END + 2473 - 2 - 4 - 4 - 1 - 1 - 1 - 564 - 2 - 1 - 1 - 3 - 1 - 2 - 2 - 7 - 1+1+1,
};

enum PlayerDynamicFields
{
    PLAYER_DYNAMIC_FIELD_RESERACH_SITE                     = UNIT_DYNAMIC_END + 0x000, //  Flags: PRIVATE
    PLAYER_DYNAMIC_FIELD_RESEARCH_SITE_PROGRESS            = UNIT_DYNAMIC_END + 0x001, //  Flags: PRIVATE
    PLAYER_DYNAMIC_FIELD_DAILY_QUESTS                      = UNIT_DYNAMIC_END + 0x002, //  Flags: PRIVATE
    PLAYER_DYNAMIC_FIELD_AVAILABLE_QUEST_LINE_X_QUEST_ID   = UNIT_DYNAMIC_END + 0x003, //  Flags: PRIVATE
    PLAYER_DYNAMIC_FIELD_HEIRLOOMS                         = UNIT_DYNAMIC_END + 0x004, //  Flags: PRIVATE
    PLAYER_DYNAMIC_FIELD_TOYS                              = UNIT_DYNAMIC_END + 0x005, //  Flags: PRIVATE
    PLAYER_DYNAMIC_END                                     = UNIT_DYNAMIC_END + 0x006,
};

enum GameObjectFields
{
    GAMEOBJECT_FIELD_CREATED_BY                            = OBJECT_END + 0x000, // Size: 2, Flags: PUBLIC
    GAMEOBJECT_DISPLAYID                                   = OBJECT_END + 0x004 - 2, // Size: 1, Flags: DYNAMIC, URGENT
    GAMEOBJECT_FLAGS                                       = OBJECT_END + 0x005 - 2, // Size: 1, Flags: PUBLIC, URGENT
    GAMEOBJECT_PARENTROTATION                              = OBJECT_END + 0x006 - 2, // Size: 4, Flags: PUBLIC
    GAMEOBJECT_FACTION                                     = OBJECT_END + 0x00A - 2, // Size: 1, Flags: PUBLIC
    GAMEOBJECT_LEVEL                                       = OBJECT_END + 0x00B - 2, // Size: 1, Flags: PUBLIC
    GAMEOBJECT_BYTES_1                                     = OBJECT_END + 0x00C - 2, // Size: 1, Flags: PUBLIC, URGENT
    GAMEOBJECT_SPELL_VISUAL_ID                             = OBJECT_END + 0x00D - 2, // Size: 1, Flags: PUBLIC, URGENT
    GAMEOBJECT_STATE_SPELL_VISUAL_ID                       = OBJECT_END + 0x00E - 2, // Size: 1, Flags: DYNAMIC, URGENT
    GAMEOBJECT_STATE_ANIM_ID                               = OBJECT_END + 0x00F - 2, // Size: 1, Flags: DYNAMIC, URGENT
    GAMEOBJECT_STATE_ANIM_KIT_ID                           = OBJECT_END + 0x010 - 2, // Size: 1, Flags: DYNAMIC, URGENT
    GAMEOBJECT_STATE_WORLD_EFFECT_ID                       = OBJECT_END + 0x011 - 2, // Size: 4, Flags: DYNAMIC, URGENT
    GAMEOBJECT_END                                         = OBJECT_END + 0x015 - 2,
};

enum GameObjectDynamicFields
{
    GAMEOBJECT_DYNAMIC_END                                 = OBJECT_DYNAMIC_END + 0x000,
};

enum DynamicObjectFields
{
    DYNAMICOBJECT_CASTER                                   = OBJECT_END + 0x000, // Size: 2, Flags: PUBLIC
    DYNAMICOBJECT_BYTES                                    = OBJECT_END + 0x004 - 2, // Size: 1, Flags: DYNAMIC
    DYNAMICOBJECT_SPELLID                                  = OBJECT_END + 0x005 - 2, // Size: 1, Flags: PUBLIC
    DYNAMICOBJECT_RADIUS                                   = OBJECT_END + 0x006 - 2, // Size: 1, Flags: PUBLIC
    DYNAMICOBJECT_CASTTIME                                 = OBJECT_END + 0x007 - 2, // Size: 1, Flags: PUBLIC
    DYNAMICOBJECT_END                                      = OBJECT_END + 0x008 - 2,
};

enum DynamicObjectDynamicFields
{
    DYNAMICOBJECT_DYNAMIC_END                              = OBJECT_DYNAMIC_END + 0x000,
};

enum CorpseFields
{
    CORPSE_FIELD_OWNER                                     = OBJECT_END + 0x000, // Size: 2, Flags: PUBLIC
    CORPSE_FIELD_PARTY                                     = OBJECT_END + 0x004 - 2, // Size: 2, Flags: PUBLIC
    CORPSE_FIELD_DISPLAY_ID                                = OBJECT_END + 0x008 - 2 - 2, // Size: 1, Flags: PUBLIC
    CORPSE_FIELD_ITEM                                      = OBJECT_END + 0x009 - 2 - 2, // Size: 19, Flags: PUBLIC
    CORPSE_FIELD_BYTES_1                                   = OBJECT_END + 0x01C - 2 - 2, // Size: 1, Flags: PUBLIC
    CORPSE_FIELD_BYTES_2                                   = OBJECT_END + 0x01D - 2 - 2, // Size: 1, Flags: PUBLIC
    CORPSE_FIELD_FLAGS                                     = OBJECT_END + 0x01E - 2 - 2, // Size: 1, Flags: PUBLIC
    CORPSE_FIELD_DYNAMIC_FLAGS                             = OBJECT_END + 0x01F - 2 - 2, // Size: 1, Flags: DYNAMIC
    CORPSE_FIELD_FACTIONTEMPLATE                           = OBJECT_END + 0x020 - 2 - 2, // Size: 1, Flags: PUBLIC
    CORPSE_END                                             = OBJECT_END + 0x021 - 2 - 2,
};

enum CorpseDynamicFields
{
    CORPSE_DYNAMIC_END                                     = OBJECT_DYNAMIC_END + 0x000,
};

enum AreaTriggerFields
{
    AREATRIGGER_CASTER                                     = OBJECT_END + 0x000, // Size: 2, Flags: PUBLIC
    AREATRIGGER_DURATION                                   = OBJECT_END + 0x004 - 2, // Size: 1, Flags: PUBLIC
    AREATRIGGER_SPELLID                                    = OBJECT_END + 0x005 - 2, // Size: 1, Flags: PUBLIC
    AREATRIGGER_SPELLVISUALID                              = OBJECT_END + 0x006 - 2, // Size: 1, Flags: DYNAMIC
    AREATRIGGER_EXPLICIT_SCALE                             = OBJECT_END + 0x007 - 2, // Size: 1, Flags: PUBLIC, URGENT
    AREATRIGGER_END                                        = OBJECT_END + 0x008 - 2,
};

enum AreaTriggerDynamicFields
{
    AREATRIGGER_DYNAMIC_END                                = OBJECT_DYNAMIC_END + 0x000,
};

enum SceneObjectFields
{
    SCENEOBJECT_FIELD_SCRIPT_PACKAGE_ID                    = OBJECT_END + 0x000, // Size: 1, Flags: PUBLIC
    SCENEOBJECT_FIELD_RND_SEED_VAL                         = OBJECT_END + 0x001, // Size: 1, Flags: PUBLIC
    SCENEOBJECT_FIELD_CREATEDBY                            = OBJECT_END + 0x002, // Size: 2, Flags: PUBLIC
    SCENEOBJECT_FIELD_SCENE_TYPE                           = OBJECT_END + 0x006 - 2, // Size: 1, Flags: PUBLIC
    SCENEOBJECT_END                                        = OBJECT_END + 0x007 - 2,
};

enum SceneObjectDynamicFields
{
    SCENEOBJECT_DYNAMIC_END                                = OBJECT_DYNAMIC_END + 0x000,
};

enum ConversationField
{
    CONVERSATION_FIELD_DUMMY                               = OBJECT_END + 0x000, // Size: 1, Flags: PRIVATE
    CONVERSATION_END                                       = OBJECT_END + 0x001,
};

enum ConversationDynamicField
{
    CONVERSATION_DYNAMIC_FIELD_ACTORS                      = OBJECT_DYNAMIC_END + 0x000, //  Flags: PUBLIC
    CONVERSATION_DYNAMIC_FIELD_LINES                       = OBJECT_DYNAMIC_END + 0x001, //  Flags: 0x100
    CONVERSATION_DYNAMIC_END                               = OBJECT_DYNAMIC_END + 0x002,
};

#endif // _UPDATEFIELDS_H
