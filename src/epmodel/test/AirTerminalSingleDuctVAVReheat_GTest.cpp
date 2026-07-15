/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowMethod());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowInputMethod("Scheduled"));
  EXPECT_EQ("Scheduled", terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowMethod("FixedFlowRate"));
  EXPECT_EQ("FixedFlowRate", terminal.zoneMinimumAirFlowInputMethod());

  EXPECT_TRUE(terminal.setConstantMinimumAirFlowFraction(0.42));
  ASSERT_TRUE(terminal.constantMinimumAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.42, terminal.constantMinimumAirFlowFraction().get());
  terminal.autosizeConstantMinimumAirFlowFraction();
  EXPECT_TRUE(terminal.isConstantMinimumAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setFixedMinimumAirFlowRate(0.5));
  ASSERT_TRUE(terminal.fixedMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, terminal.fixedMinimumAirFlowRate().get());
  terminal.autosizeFixedMinimumAirFlowRate();
  EXPECT_TRUE(terminal.isFixedMinimumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.isMaximumHotWaterOrSteamFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHotWaterOrSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterOrSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterOrSteamFlowRate().get());
  terminal.autosizeMaximumHotWaterOrSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterOrSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterOrStreamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterOrSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.convergenceTolerance());

  EXPECT_EQ("Normal", terminal.damperHeatingAction());
  EXPECT_TRUE(terminal.setDamperHeatingAction("Reverse"));
  EXPECT_EQ("Reverse", terminal.damperHeatingAction());

  EXPECT_TRUE(terminal.isMaximumFlowPerZoneFloorAreaDuringReheatAutosized());
  EXPECT_TRUE(terminal.setMaximumFlowPerZoneFloorAreaDuringReheat(0.25));
  ASSERT_TRUE(terminal.maximumFlowPerZoneFloorAreaDuringReheat());
  EXPECT_DOUBLE_EQ(0.25, terminal.maximumFlowPerZoneFloorAreaDuringReheat().get());
  terminal.autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
  EXPECT_TRUE(terminal.isMaximumFlowPerZoneFloorAreaDuringReheatAutosized());
  terminal.resetMaximumFlowPerZoneFloorAreaDuringReheat();
  EXPECT_FALSE(terminal.maximumFlowPerZoneFloorAreaDuringReheat());

  EXPECT_TRUE(terminal.isMaximumFlowFractionDuringReheatAutosized());
  EXPECT_TRUE(terminal.setMaximumFlowFractionDuringReheat(0.35));
  ASSERT_TRUE(terminal.maximumFlowFractionDuringReheat());
  EXPECT_DOUBLE_EQ(0.35, terminal.maximumFlowFractionDuringReheat().get());
  terminal.autosizeMaximumFlowFractionDuringReheat();
  EXPECT_TRUE(terminal.isMaximumFlowFractionDuringReheatAutosized());
  terminal.resetMaximumFlowFractionDuringReheat();
  EXPECT_FALSE(terminal.maximumFlowFractionDuringReheat());

  EXPECT_TRUE(terminal.setMaximumReheatAirTemperature(41.2));
  EXPECT_DOUBLE_EQ(41.2, terminal.maximumReheatAirTemperature());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact minimumFraction(model);
  ScheduleCompact turndown(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(minimumFraction.setToConstantValue(0.2));
  ASSERT_TRUE(turndown.setToConstantValue(0.4));

  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_TRUE(terminal.setMinimumAirFlowFractionSchedule(minimumFraction));
  EXPECT_TRUE(terminal.setMinimumAirFlowTurndownSchedule(turndown));
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  ASSERT_TRUE(terminal.minimumAirFlowFractionSchedule());
  EXPECT_EQ(minimumFraction.handle(), terminal.minimumAirFlowFractionSchedule()->handle());
  ASSERT_TRUE(terminal.minimumAirFlowTurndownSchedule());
  EXPECT_EQ(turndown.handle(), terminal.minimumAirFlowTurndownSchedule()->handle());

  CoilHeatingElectric reheatCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());

  terminal.resetMinimumAirFlowFractionSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowFractionSchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_ReheatCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  CoilHeatingElectric electricCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(electricCoil));
  EXPECT_EQ(electricCoil.handle(), terminal.reheatCoil().handle());

  CoilHeatingWater waterCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(waterCoil));
  EXPECT_EQ(waterCoil.handle(), terminal.reheatCoil().handle());

  FanConstantVolume fan(model);
  EXPECT_FALSE(terminal.setReheatCoil(fan));
  EXPECT_EQ(waterCoil.handle(), terminal.reheatCoil().handle());

  Model otherModel;
  CoilHeatingElectric foreignCoil(otherModel);
  EXPECT_FALSE(terminal.setReheatCoil(foreignCoil));
  EXPECT_EQ(waterCoil.handle(), terminal.reheatCoil().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_ResolvesAirLoopHVACAndADUOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletHandleBeforeRejectedAdd, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletHandleBeforeRejectedAdd, terminal.outletModelObject()->handle());
  resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(aduOutletHandleBeforeRejectedAdd, resolvedOutletNode->handle());
  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_PopulatesDirectReheatCoilAirPathFields) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);

  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  const std::string damperOutletNodeName = terminal.nameString() + " Damper Outlet";
  EXPECT_EQ(damperOutletNodeName, terminal.getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName, true).get());
  EXPECT_EQ(reheatCoil.iddObject().name(), terminal.getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilObjectType, true).get());
  EXPECT_EQ(damperOutletNodeName, reheatCoil.getString(openstudio::Coil_Heating_WaterFields::AirInletNodeName, true).get());
  ASSERT_TRUE(reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
  EXPECT_EQ(zoneAirNode, reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName).get());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_RegistersSecondBranchZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheat terminal(model);

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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Remove_ReconnectsZoneBranchAndCleansZoneAndPlantReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctVAVReheat::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansPlantBranchWhenTerminalIsNotAirLoopConnected) {
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansStaleADUOnlyReference) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansConnectivityWithoutADU) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));

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
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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
