/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../scaffolds/AirTerminalSingleDuctVAVReheatVariableSpeedFan.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  ASSERT_TRUE(terminal.availabilitySchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_ScalarAndRelationshipAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);

  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());

  FanSystemModel fan(model);
  CoilHeatingElectric heatingCoil(model);
  EXPECT_TRUE(terminal.setFan(fan));
  EXPECT_TRUE(terminal.setHeatingCoil(heatingCoil));
  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(heatingCoil.handle(), terminal.heatingCoil().handle());

  EXPECT_TRUE(terminal.isMaximumCoolingAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumCoolingAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumCoolingAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumCoolingAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumCoolingAirFlowRateAutosized());
  terminal.autosizeMaximumCoolingAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumCoolingAirFlowRateAutosized());

  EXPECT_TRUE(terminal.isMaximumHeatingAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHeatingAirFlowRate(0.987));
  ASSERT_TRUE(terminal.maximumHeatingAirFlowRate());
  EXPECT_DOUBLE_EQ(0.987, terminal.maximumHeatingAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHeatingAirFlowRateAutosized());
  terminal.autosizeMaximumHeatingAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumHeatingAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.22));
  EXPECT_DOUBLE_EQ(0.22, terminal.zoneMinimumAirFlowFraction());

  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterorSteamFlowRate());
  EXPECT_FALSE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());
  terminal.resetMinimumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());

  EXPECT_TRUE(terminal.setHeatingConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.heatingConvergenceTolerance());
  EXPECT_FALSE(terminal.isHeatingConvergenceToleranceDefaulted());
  terminal.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(terminal.isHeatingConvergenceToleranceDefaulted());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  Node standaloneNode(model);
  Model otherModel;
  Node foreignNode(otherModel);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_AddToNode_ResolvesAirLoopHVACAndADUOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  FanSystemModel fan(model);
  CoilHeatingElectric heatingCoil(model);
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  EXPECT_NE(zoneAirNode, *inletNode);

  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zoneAirNode, *outletNode);

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zoneAirNode, resolvedOutletNode.get());
  const auto inletHandleBeforeRejectedAdd = terminal.inletModelObject()->handle();
  const auto outletHandleBeforeRejectedAdd = terminal.outletModelObject()->handle();
  const auto aduOutletHandleBeforeRejectedAdd = resolvedOutletNode->handle();

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletHandleBeforeRejectedAdd, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletHandleBeforeRejectedAdd, terminal.outletModelObject()->handle());
  resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(aduOutletHandleBeforeRejectedAdd, resolvedOutletNode->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);

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
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_Remove_ReconnectsZoneBranchAndCleansZoneAndPlantReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  FanSystemModel fan(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setHeatingCoil(waterCoil));
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  auto zoneAirNode = zone.zoneAirNode();

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  EXPECT_NE(zoneAirNode, *inletNode);

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
  ASSERT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_Remove_DirectAddToNodeWithoutADU_CleansConnectivityAndPlant) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  FanSystemModel fan(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setHeatingCoil(waterCoil));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
  ASSERT_EQ(1u, zone.equipment().size());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(model.getObject(terminal.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_RemoveFromLoop_CleansStaleADUOnlyReference) {
  Model model;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(adu.airTerminal());

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_RemoveFromLoop_PlantOnlyConnectionReturnsTrueAndCleansPlant) {
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater waterCoil(model);
  FanSystemModel fan(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setHeatingCoil(waterCoil));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  FanSystemModel fan(model);
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setHeatingCoil(waterCoil));
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  const auto zoneAirNode = zone.zoneAirNode();
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.removeFromLoop());
}
