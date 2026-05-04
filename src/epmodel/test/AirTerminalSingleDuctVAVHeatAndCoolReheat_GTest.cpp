/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.zoneMinimumAirFlowFraction());
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.minimumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.001, terminal.convergenceTolerance());
  EXPECT_DOUBLE_EQ(1000.0, terminal.maximumReheatAirTemperature());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());

  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterorSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.convergenceTolerance());

  EXPECT_TRUE(terminal.setMaximumReheatAirTemperature(41.2));
  EXPECT_DOUBLE_EQ(41.2, terminal.maximumReheatAirTemperature());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);

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

  CoilHeatingElectric reheatCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());

  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_AddToNode_RejectsInvalidNodesAndDuplicateZoneInsertion) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_AddToNode_RejectsAlreadyConnectedTerminalOnDifferentValidZoneNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);

  auto firstBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(firstBranchObject);
  auto firstBranchNode = firstBranchObject->optionalCast<Node>();
  ASSERT_TRUE(firstBranchNode);
  ASSERT_TRUE(zone1.addToNode(*firstBranchNode));
  auto firstZoneAirNode = zone1.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(firstZoneAirNode));

  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  auto secondZoneAirNode = zone2.zoneAirNode();
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  const auto inletHandle = inletObject->handle();
  const auto outletHandle = outletObject->handle();

  EXPECT_FALSE(terminal.addToNode(secondZoneAirNode));
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletHandle, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletHandle, terminal.outletModelObject()->handle());

  const auto zone1Equipment = zone1.equipment();
  ASSERT_EQ(1u, zone1Equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone1Equipment.front());
  EXPECT_TRUE(zone2.equipment().empty());
  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_AddToNode_RollsBackLateFailure) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
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
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  auto terminalImpl = terminal.getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>();
  ASSERT_TRUE(terminalImpl);
  EXPECT_FALSE(terminalImpl->addToNode(
    zoneAirNode, detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration));

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_AddToNode_RegistersSecondBranchZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);

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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_Remove_ReconnectsZoneBranchAndCleansZoneAndPlantReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));
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
  EXPECT_NE(zoneAirNode, *inletNode);

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
  ASSERT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());
  auto plantWaterCoils = plantLoop.demandComponents(CoilHeatingWater::iddObjectType());
  EXPECT_NE(plantWaterCoils.end(), std::ranges::find(plantWaterCoils, waterCoil.cast<ModelObject>()));

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_RemoveFromLoop_CleansPlantBranchWhenTerminalIsNotAirLoopConnected) {
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  auto plantWaterCoils = plantLoop.demandComponents(CoilHeatingWater::iddObjectType());
  EXPECT_NE(plantWaterCoils.end(), std::ranges::find(plantWaterCoils, waterCoil.cast<ModelObject>()));

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_RemoveFromLoop_CleansStaleADUOnlyReference) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_RemoveFromLoop_CleansStaleZoneEquipmentOnlyReference) {
  Model model;
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  ASSERT_TRUE(zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal.cast<ModelObject>()));
  ASSERT_EQ(1u, zone.equipment().size());

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_RemoveFromLoop_CleansStalePartiallyDisconnectedReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());

  auto terminalImpl = terminal.getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>();
  ASSERT_TRUE(terminalImpl);
  ASSERT_TRUE(terminalImpl->setPointer(terminal.inletPort(), openstudio::Handle(), false));

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_Remove_RemovesDetachedTerminalAndPlantBranch) {
  Model model;
  ThermalZone zone(model);
  PlantLoop plantLoop(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));
  ZoneHVACAirDistributionUnit adu(model);

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  ASSERT_TRUE(zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal.cast<ModelObject>()));

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(adu.airTerminal());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolReheat_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVHeatAndCoolReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));
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
