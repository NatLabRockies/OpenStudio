/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirLoopHVAC.hpp"
#include "../AirLoopHVACZoneMixer.hpp"
#include "../AirLoopHVACZoneSplitter.hpp"
#include "../Node.hpp"
#include "../ThermalZone.hpp"
#include "../ThermalZone_Impl.hpp"
#include "../ZoneHVACEquipmentConnections.hpp"
#include "../ZoneHVACEquipmentConnections_Impl.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ThermalZone_DefaultConstructor) {
  Model model;
  ThermalZone zone(model);
  EXPECT_EQ(ThermalZone::iddObjectType(), zone.iddObject().type());
  EXPECT_FALSE(zone.nameString().empty());
}

TEST_F(EPModelFixture, API_ThermalZone_ModelLookupByTypeAndName) {
  Model model;
  ThermalZone zone(model);

  auto object = model.getObjectByTypeAndName(ThermalZone::iddObjectType(), zone.nameString());
  ASSERT_TRUE(object);
  EXPECT_EQ(zone.cast<ModelObject>(), object->cast<ModelObject>());
}

TEST_F(EPModelFixture, ThermalZone_AddToNode_DemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  EXPECT_TRUE(zone.addToNode(*branchNode));

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(splitterOutlets.size(), mixerInlets.size());
  ASSERT_EQ(1u, splitterOutlets.size());
  EXPECT_EQ(splitterOutlets[0], mixerInlets[0]);

  auto updatedNode = splitterOutlets[0].cast<Node>();
  EXPECT_EQ(zone.nameString() + " Demand Branch Node", updatedNode.nameString());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  auto inletNode = zoneConnections->zoneAirInletNode();
  ASSERT_TRUE(inletNode);
  auto returnNode = zoneConnections->zoneReturnAirNode();
  ASSERT_TRUE(returnNode);
  EXPECT_EQ(updatedNode.cast<ModelObject>(), inletNode->cast<ModelObject>());
  EXPECT_EQ(updatedNode.cast<ModelObject>(), returnNode->cast<ModelObject>());

  const auto demandComps = airLoop.demandComponents();
  ASSERT_EQ(6u, demandComps.size());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[0].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter), demandComps[1].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[2].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Zone), demandComps[3].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneMixer), demandComps[4].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[5].iddObject().type());
}

TEST_F(EPModelFixture, ThermalZone_AddToNode_FailsOnSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_FALSE(zone.addToNode(supplyInletNode));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(zone.addToNode(supplyOutletNode));

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(zone.addToNode(demandInletNode));

  auto demandOutletNode = airLoop.demandOutletNode();
  EXPECT_FALSE(zone.addToNode(demandOutletNode));
}
