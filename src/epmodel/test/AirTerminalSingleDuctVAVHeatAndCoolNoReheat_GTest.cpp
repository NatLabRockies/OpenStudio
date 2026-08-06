/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.zoneMinimumAirFlowFraction());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_ScheduleRelationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);

  EXPECT_FALSE(terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());

  ScheduleCompact availability(model);
  ScheduleCompact turndown(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(turndown.setToConstantValue(0.4));

  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_TRUE(terminal.setMinimumAirFlowTurndownSchedule(turndown));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());
  ASSERT_TRUE(terminal.minimumAirFlowTurndownSchedule());
  EXPECT_EQ(turndown.handle(), terminal.minimumAirFlowTurndownSchedule()->handle());

  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_AddToNode_RejectsInvalidNodesAndDuplicateZoneInsertion) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);
  Node standaloneNode(model);
  Model otherModel;
  Node foreignNode(otherModel);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto terminalInletObject = terminal.inletModelObject();
  ASSERT_TRUE(terminalInletObject);
  auto terminalInletNode = terminalInletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalInletNode);
  EXPECT_NE(zoneAirNode, *terminalInletNode);

  auto terminalOutletObject = terminal.outletModelObject();
  ASSERT_TRUE(terminalOutletObject);
  auto terminalOutletNode = terminalOutletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalOutletNode);
  EXPECT_EQ(zoneAirNode, *terminalOutletNode);

  const auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zoneAirNode, resolvedOutletNode.get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  const auto inletHandleBeforeRejectedAdd = terminalInletNode->handle();
  const auto outletHandleBeforeRejectedAdd = terminalOutletNode->handle();
  const auto aduOutletHandleBeforeRejectedAdd = resolvedOutletNode->handle();

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletHandleBeforeRejectedAdd, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletHandleBeforeRejectedAdd, terminal.outletModelObject()->handle());
  const auto resolvedOutletNodeAfterRejectedAdd = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNodeAfterRejectedAdd);
  EXPECT_EQ(aduOutletHandleBeforeRejectedAdd, resolvedOutletNodeAfterRejectedAdd->handle());
  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(terminalInletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_AddToNode_RegistersSecondBranchZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, dummyTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal));

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  ASSERT_EQ(2u, splitterOutlets.size());
  auto firstBranch = splitterOutlets[0].optionalCast<Node>();
  ASSERT_TRUE(firstBranch);
  auto secondBranch = splitterOutlets[1].optionalCast<Node>();
  ASSERT_TRUE(secondBranch);
  auto dummyInlet = dummyTerminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(dummyInlet);
  EXPECT_EQ(*firstBranch, *dummyInlet);

  auto terminalInlet = terminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalInlet);
  EXPECT_EQ(*secondBranch, *terminalInlet);

  auto terminalOutlet = terminal.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalOutlet);
  EXPECT_EQ(zone2.zoneAirNode(), *terminalOutlet);

  const auto zone1Equipment = zone1.equipment();
  ASSERT_EQ(1u, zone1Equipment.size());
  EXPECT_EQ(dummyTerminal.cast<ModelObject>(), zone1Equipment.front());

  const auto zone2Equipment = zone2.equipment();
  ASSERT_EQ(1u, zone2Equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone2Equipment.front());

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zone2.zoneAirNode(), resolvedOutletNode.get());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();

  Node mismatchedMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  EXPECT_EQ(mismatchedMixerNode.cast<ModelObject>(), *mixerInlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Remove_ReconnectsZoneBranchAndCleansZoneReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ZoneHVACAirDistributionUnit adu(model);

  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminalForRemoveFromLoop(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminalForRemoveFromLoop.cast<ModelObject>()));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminalForRemoveFromLoop));

  const auto zoneAirNode = zone.zoneAirNode();
  auto inletObject = terminalForRemoveFromLoop.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  EXPECT_NE(zoneAirNode, *inletNode);

  ASSERT_TRUE(terminalForRemoveFromLoop.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(terminalForRemoveFromLoop.inletModelObject());
  EXPECT_FALSE(terminalForRemoveFromLoop.outletModelObject());
  EXPECT_TRUE(model.getObject(terminalForRemoveFromLoop.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(terminalForRemoveFromLoop.removeFromLoop());

  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminalForRemove(model);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminalForRemove.cast<ModelObject>()));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminalForRemove));

  inletObject = terminalForRemove.inletModelObject();
  ASSERT_TRUE(inletObject);
  inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto removeInletNodeHandle = inletNode->handle();

  const auto removedObjects = terminalForRemove.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getObject(terminalForRemove.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(removeInletNodeHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_TerminalOnlyBranchSupportsRemoveFromLoopAndReuse) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_TRUE(airLoop.thermalZones().empty());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());

  ASSERT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  ASSERT_TRUE(airLoop.zoneSplitter().outletModelObject(0u));
  ASSERT_TRUE(airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_EQ(*airLoop.zoneSplitter().outletModelObject(0u), *airLoop.zoneMixer().inletModelObject(0u));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_TRUE(terminal.airLoopHVAC());
  EXPECT_TRUE(airLoop.thermalZones().empty());
}
