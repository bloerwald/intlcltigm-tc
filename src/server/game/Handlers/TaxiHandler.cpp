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
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "TaxiPackets.h"
#include "TaxiPathGraph.h"

void WorldSession::HandleEnableTaxiNodeOpcode(WorldPackets::Taxi::EnableTaxiNode& packet)
{
    Creature* unit = GetPlayer()->GetMap()->GetCreature(packet.Unit);
    SendLearnNewTaxiNode(unit);
}


void WorldSession::HandleTaxiNodeStatusQueryOpcode(WorldPackets::Taxi::TaxiNodeStatusQuery& packet)
{
    SendTaxiStatus(packet.UnitGUID);
}

void WorldSession::SendTaxiStatus(ObjectGuid guid)
{
    // cheating checks
    Creature* unit = GetPlayer()->GetMap()->GetCreature(guid);
    if (!unit)
    {
        TC_LOG_DEBUG("network", "WorldSession::SendTaxiStatus - %s not found.", guid.ToString().c_str());
        return;
    }

    uint32 curloc = sObjectMgr->GetNearestTaxiNode(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), unit->GetMapId(), GetPlayer()->GetTeam());

    WorldPackets::Taxi::TaxiNodeStatus data;
    data.Unit = guid;

    if (!curloc)
        data.Status = TAXISTATUS_NONE;
    else if (unit->GetReactionTo(GetPlayer()) >= REP_NEUTRAL)
        data.Status = GetPlayer()->m_taxi.IsTaximaskNodeKnown(curloc) ? TAXISTATUS_LEARNED : TAXISTATUS_UNLEARNED;
    else
        data.Status = TAXISTATUS_NOT_ELIGIBLE;
    
    SendPacket(data.Write());

    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_TAXI_NODE_STATUS");
}

void WorldSession::HandleTaxiQueryAvailableNodesOpcode(WorldPackets::Taxi::TaxiQueryAvailableNodes& packet)
{
    // cheating checks
    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(packet.Unit, UNIT_NPC_FLAG_FLIGHTMASTER);
    if (!unit)
    {
        TC_LOG_DEBUG("network", "WORLD: HandleTaxiQueryAvailableNodes - %s not found or you can't interact with him.", packet.Unit.ToString().c_str());
        return;
    }
    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    // unknown taxi node case
    if (SendLearnNewTaxiNode(unit))
        return;

    // known taxi node case
    SendTaxiMenu(unit);
}

void WorldSession::SendTaxiMenu(Creature* unit)
{
    // find current node
    uint32 curloc = sObjectMgr->GetNearestTaxiNode(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), unit->GetMapId(), GetPlayer()->GetTeam());
    if (!curloc)
        return;

    bool lastTaxiCheaterState = GetPlayer()->isTaxiCheater();
    if (unit->GetEntry() == 29480)
        GetPlayer()->SetTaxiCheater(true); // Grimwing in Ebon Hold, special case. NOTE: Not perfect, Zul'Aman should not be included according to WoWhead, and I think taxicheat includes it.

    TC_LOG_DEBUG("network", "WORLD: CMSG_TAXINODE_STATUS_QUERY %u ", curloc);

    WorldPackets::Taxi::ShowTaxiNodes data;
    data.WindowInfo = boost::in_place();
    data.WindowInfo->UnitGUID = unit->GetGUID();
    data.WindowInfo->CurrentNode = curloc;
    
    GetPlayer()->m_taxi.AppendTaximaskTo(data, lastTaxiCheaterState);
 
    SendPacket(data.Write());

    GetPlayer()->SetTaxiCheater(lastTaxiCheaterState);
}

void WorldSession::SendDoFlight(uint32 mountDisplayId, uint32 path, uint32 pathNode)
{
    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    while (GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        GetPlayer()->GetMotionMaster()->MovementExpired(false);

    if (mountDisplayId)
        GetPlayer()->Mount(mountDisplayId);

    GetPlayer()->GetMotionMaster()->MoveTaxiFlight(path, pathNode);
}

bool WorldSession::SendLearnNewTaxiNode(Creature* unit)
{
    // find current node
    uint32 curloc = sObjectMgr->GetNearestTaxiNode(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), unit->GetMapId(), GetPlayer()->GetTeam());

    if (curloc == 0)
        return true;                                        // `true` send to avoid WorldSession::SendTaxiMenu call with one more curlock seartch with same false result.

    if (GetPlayer()->m_taxi.SetTaximaskNode(curloc))
    {
        SendPacket(WorldPackets::Taxi::NewTaxiPath().Write());

        WorldPackets::Taxi::TaxiNodeStatus data;
        data.Unit = unit->GetGUID();
        data.Status = TAXISTATUS_LEARNED;
        SendPacket(data.Write());

        return true;
    }
    else
        return false;
}

void WorldSession::SendDiscoverNewTaxiNode(uint32 nodeid)
{
    if (GetPlayer()->m_taxi.SetTaximaskNode(nodeid))
        SendPacket(WorldPackets::Taxi::NewTaxiPath().Write());
}

void WorldSession::HandleActivateTaxiOpcode(WorldPackets::Taxi::ActivateTaxi& packet)
{
    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(packet.Vendor, UNIT_NPC_FLAG_FLIGHTMASTER);
    if (!unit)
    {
        TC_LOG_DEBUG("network", "WORLD: HandleActivateTaxiOpcode - %s not found or you can't interact with it.", packet.Vendor.ToString().c_str());
        return;
    }

    uint32 curloc = sObjectMgr->GetNearestTaxiNode(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), unit->GetMapId(), GetPlayer()->GetTeam());
    
    if (!curloc)
        return;
    
    if (!GetPlayer()->isTaxiCheater())
    {
        if (!GetPlayer()->m_taxi.IsTaximaskNodeKnown(curloc) || !GetPlayer()->m_taxi.IsTaximaskNodeKnown(packet.Node))
        {
            SendActivateTaxiReply(ERR_TAXINOTVISITED);
            return;
        }
    }
    
    std::vector<uint32> nodes;
    TaxiPathGraph::GetCompleteNodeRoute(curloc, packet.Node, nodes);
    GetPlayer()->ActivateTaxiPathTo(nodes, unit);
}

void WorldSession::SendActivateTaxiReply(ActivateTaxiReply reply)
{
    WorldPackets::Taxi::ActivateTaxiReply data;
    data.Reply = reply;
    SendPacket(data.Write());
    TC_LOG_DEBUG("network", "WORLD: Sent SMSG_ACTIVATETAXIREPLY");
}

void WorldSession::HandleTaxiRequestEarlyLanding(WorldPackets::Taxi::TaxiRequestEarlyLanding& /* packet */)
{
    GetPlayer()->m_taxi.RequestEarlyLanding();
}
