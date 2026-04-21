/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"

#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_DefaultConstructor) {
  Model model;
  ZoneHVACEquipmentConnections equipmentConnections(model);
  EXPECT_EQ(ZoneHVACEquipmentConnections::iddObjectType(), equipmentConnections.iddObject().type());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_SettersAndGetters) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACEquipmentList equipmentList(model);
  ZoneHVACEquipmentConnections equipmentConnections(model);
  auto zoneAirNode = model.getOrCreateTransientByName<Node>("Zone Air Node");
  auto zoneInletNode = model.getOrCreateTransientByName<Node>("Zone Inlet Node");
  auto zoneExhaustNode = model.getOrCreateTransientByName<Node>("Zone Exhaust Node");
  auto zoneReturnNode = model.getOrCreateTransientByName<Node>("Zone Return Node");

  auto equipmentConnectionsImpl = equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(equipmentConnectionsImpl);

  ASSERT_TRUE(equipmentConnectionsImpl->setThermalZone(zone));
  ASSERT_TRUE(equipmentConnectionsImpl->setZoneHVACEquipmentList(equipmentList));
  ASSERT_TRUE(equipmentConnectionsImpl->setZoneAirNode(zoneAirNode));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirInletNode(zoneInletNode));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirExhaustNode(zoneExhaustNode));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneReturnAirNode(zoneReturnNode));

  auto linkedZone = equipmentConnections.thermalZone();
  ASSERT_TRUE(linkedZone);
  EXPECT_EQ(zone, linkedZone.get());

  auto linkedEquipmentList = equipmentConnections.zoneHVACEquipmentList();
  ASSERT_TRUE(linkedEquipmentList);
  EXPECT_EQ(equipmentList, linkedEquipmentList.get());

  auto linkedZoneAirNode = equipmentConnections.zoneAirNode();
  ASSERT_TRUE(linkedZoneAirNode);
  EXPECT_EQ(zoneAirNode, linkedZoneAirNode.get());

  const auto zoneAirInletNodes = equipmentConnections.zoneAirInletNodes();
  ASSERT_EQ(1u, zoneAirInletNodes.size());
  EXPECT_EQ(zoneInletNode, zoneAirInletNodes.front());

  const auto inletTarget = equipmentConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
  ASSERT_TRUE(inletTarget);
  EXPECT_TRUE(inletTarget->optionalCast<NodeList>());

  const auto zoneAirExhaustNodes = equipmentConnections.zoneAirExhaustNodes();
  ASSERT_EQ(1u, zoneAirExhaustNodes.size());
  EXPECT_EQ(zoneExhaustNode, zoneAirExhaustNodes.front());

  const auto zoneReturnAirNodes = equipmentConnections.zoneReturnAirNodes();
  ASSERT_EQ(1u, zoneReturnAirNodes.size());
  EXPECT_EQ(zoneReturnNode, zoneReturnAirNodes.front());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_MultipleAggregateNodesUseNodeList) {
  Model model;
  ZoneHVACEquipmentConnections equipmentConnections(model);
  auto inlet1 = model.getOrCreateTransientByName<Node>("Zone Inlet 1");
  auto inlet2 = model.getOrCreateTransientByName<Node>("Zone Inlet 2");

  auto equipmentConnectionsImpl = equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(equipmentConnectionsImpl);
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirInletNode(inlet1));
  ASSERT_TRUE(equipmentConnectionsImpl->addZoneAirInletNode(inlet2));

  const auto inletNodes = equipmentConnections.zoneAirInletNodes();
  ASSERT_EQ(2u, inletNodes.size());
  EXPECT_EQ(inlet1, inletNodes[0]);
  EXPECT_EQ(inlet2, inletNodes[1]);

  const auto inletTarget = equipmentConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
  ASSERT_TRUE(inletTarget);
  auto inletNodeList = inletTarget->optionalCast<NodeList>();
  ASSERT_TRUE(inletNodeList);
  EXPECT_EQ(2u, inletNodeList->nodes().size());

  ASSERT_TRUE(equipmentConnectionsImpl->removeZoneAirInletNode(inlet1));
  ASSERT_TRUE(equipmentConnectionsImpl->removeZoneAirInletNode(inlet2));
  EXPECT_TRUE(equipmentConnections.zoneAirInletNodes().empty());
}
