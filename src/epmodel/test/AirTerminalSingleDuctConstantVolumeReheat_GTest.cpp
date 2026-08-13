/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ScheduleAndCoilConstructor_Parity) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();

  CoilHeatingElectric electricCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat electricTerminal(model, alwaysOn, electricCoil);
  EXPECT_EQ(alwaysOn.handle(), electricTerminal.availabilitySchedule().handle());
  EXPECT_EQ(electricCoil.handle(), electricTerminal.reheatCoil().handle());

  CoilHeatingGas gasCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat gasTerminal(model, alwaysOn, gasCoil);
  EXPECT_EQ(gasCoil.handle(), gasTerminal.reheatCoil().handle());

  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat waterTerminal(model, alwaysOn, waterCoil);
  EXPECT_EQ(waterCoil.handle(), waterTerminal.reheatCoil().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_Remove_DisconnectedDeletesOwnedReheatCoil) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, reheatCoil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = reheatCoil.handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

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

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.convergenceTolerance());
  EXPECT_FALSE(terminal.isConvergenceToleranceDefaulted());
  terminal.resetConvergenceTolerance();
  EXPECT_TRUE(terminal.isConvergenceToleranceDefaulted());

  EXPECT_TRUE(terminal.setMaximumReheatAirTemperature(41.2));
  EXPECT_DOUBLE_EQ(41.2, terminal.maximumReheatAirTemperature());
  EXPECT_FALSE(terminal.isMaximumReheatAirTemperatureDefaulted());
  terminal.resetMaximumReheatAirTemperature();
  EXPECT_TRUE(terminal.isMaximumReheatAirTemperatureDefaulted());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.7));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.handle(), terminal.availabilitySchedule().handle());

  CoilHeatingElectric reheatCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ReheatCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, reheatCoil);

  CoilHeatingGas gasCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(gasCoil));
  EXPECT_EQ(gasCoil.handle(), terminal.reheatCoil().handle());

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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AvailabilityScheduleGetter_RepairsMissingReference) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, reheatCoil);

  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName));

  const auto repairedSchedule = terminal.availabilitySchedule();
  EXPECT_EQ(alwaysOn, repairedSchedule);
  const auto storedSchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(alwaysOn, *storedSchedule);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_ResolvesAirLoopHVACAndADUOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
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
  EXPECT_EQ(reheatCoil.iddObject().name(),
            terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, true).get());
  EXPECT_EQ(*inletNode, reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName).get());
  EXPECT_EQ(*outletNode, reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName).get());

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zoneAirNode, resolvedOutletNode.get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_RegistersSecondBranchZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_RequiredCoilPreflightIsAtomicAndRetryable) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();
  const auto splitterOutletBefore = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBefore);
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  const auto splitterOutletAfter = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfter);
  EXPECT_EQ(splitterOutletBefore->handle(), splitterOutletAfter->handle());
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone.equipment().front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_LateFailureRestoresExactStateAndIsRetryable) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  const std::string staleOutletName = "Imported Missing CV Reheat Outlet";
  ASSERT_TRUE(aduImpl->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, staleOutletName, false));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(staleOutletName));

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();
  const auto splitterOutletBefore = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBefore);
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  auto terminalImpl = terminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
  ASSERT_TRUE(terminalImpl);
  EXPECT_FALSE(terminalImpl->addToNode(
    zoneAirNode, detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration));

  const auto splitterOutletAfter = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfter);
  EXPECT_EQ(splitterOutletBefore->handle(), splitterOutletAfter->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  auto aduWorkspaceImpl = adu.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(aduWorkspaceImpl);
  const auto restoredRawOutlet = aduWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(
    openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
  ASSERT_TRUE(restoredRawOutlet);
  EXPECT_EQ(staleOutletName, *restoredRawOutlet);
  EXPECT_FALSE(adu.getField(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(staleOutletName));

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(zoneAirNode, *adu.outletNode());
  ASSERT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone.equipment().front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_LateFailureRestoresAuthoritativeADUTarget) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  Node originalOutlet(model);
  ASSERT_TRUE(originalOutlet.setName("Authoritative CV Reheat ADU Outlet"));
  ASSERT_TRUE(aduImpl->setOutletNode(originalOutlet));
  const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
  const std::string shadowRawText = "Non-authoritative CV Reheat Backing Text";
  ASSERT_TRUE(aduImpl->openstudio::detail::IdfObject_Impl::setString(outletField, shadowRawText, false));

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();
  const auto splitterOutletBefore = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBefore);
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  auto terminalImpl = terminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
  ASSERT_TRUE(terminalImpl);
  EXPECT_FALSE(terminalImpl->addToNode(
    zoneAirNode, detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration));

  ASSERT_TRUE(adu.getTarget(outletField));
  EXPECT_EQ(originalOutlet.handle(), adu.getTarget(outletField)->handle());
  auto aduWorkspaceImpl = adu.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(aduWorkspaceImpl);
  const auto restoredRawText = aduWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
  ASSERT_TRUE(restoredRawText);
  EXPECT_EQ(shadowRawText, *restoredRawText);
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  const auto splitterOutletAfter = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfter);
  EXPECT_EQ(splitterOutletBefore->handle(), splitterOutletAfter->handle());

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(zoneAirNode.handle(), adu.outletNode()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_Remove_ReconnectsZoneBranchAndCleansZoneAndPlantReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, waterCoil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = waterCoil.handle();
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_FALSE(waterCoil.controllerWaterCoil());
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
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_EQ(7u, airLoop.demandComponents().size());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_Remove_MalformedPlantPreservesAirZoneAndPlantState) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater waterCoil(model);
  CoilHeatingWater neighboringCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, waterCoil);
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(neighboringCoil));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalInletHandle = terminal.inletModelObject()->handle();
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();
  const auto splitterOutletBefore = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBefore);
  ASSERT_TRUE(adu.outletNode());
  const auto aduOutletHandle = adu.outletNode()->handle();

  auto waterCoilImpl = waterCoil.getImpl<detail::CoilHeatingWater_Impl>();
  ASSERT_TRUE(waterCoilImpl);
  ASSERT_TRUE(neighboringCoil.waterInletModelObject());
  ASSERT_TRUE(waterCoilImpl->setPointer(waterCoil.waterOutletPort(), neighboringCoil.waterInletModelObject()->handle(), false));
  ASSERT_TRUE(waterCoil.plantLoop());

  EXPECT_TRUE(terminal.remove().empty());

  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(waterCoil.handle()));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  EXPECT_EQ(terminalOutletHandle, terminal.outletModelObject()->handle());
  const auto splitterOutletAfter = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfter);
  EXPECT_EQ(splitterOutletBefore->handle(), splitterOutletAfter->handle());
  ASSERT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(terminal.handle(), zone.equipment().front().handle());
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(aduOutletHandle, adu.outletNode()->handle());
  ASSERT_TRUE(adu.airTerminal());
  EXPECT_EQ(terminal.handle(), adu.airTerminal()->handle());
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCoil.plantLoop()->handle());
  EXPECT_EQ(2u, plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_RemoveFromLoop_HalfConnectedRefusesAndPreservesState) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, waterCoil);
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  auto terminalImpl = terminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
  ASSERT_TRUE(terminalImpl);
  ASSERT_TRUE(terminalImpl->setPointer(terminal.inletPort(), openstudio::Handle(), false));
  ASSERT_TRUE(terminal.outletModelObject());
  const auto outletHandle = terminal.outletModelObject()->handle();
  const auto splitterOutletBefore = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBefore);
  ASSERT_TRUE(adu.outletNode());
  const auto aduOutletHandle = adu.outletNode()->handle();
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();
  const auto plantComponentsBefore = plantLoop.demandComponents();

  EXPECT_FALSE(terminal.removeFromLoop());

  EXPECT_FALSE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletHandle, terminal.outletModelObject()->handle());
  ASSERT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(terminal.handle(), zone.equipment().front().handle());
  ASSERT_TRUE(adu.airTerminal());
  EXPECT_EQ(terminal.handle(), adu.airTerminal()->handle());
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(aduOutletHandle, adu.outletNode()->handle());
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCoil.plantLoop()->handle());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  const auto splitterOutletAfter = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfter);
  EXPECT_EQ(splitterOutletBefore->handle(), splitterOutletAfter->handle());
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_TRUE(model.getObject(terminal.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_Remove_CleansPlantBranchWhenTerminalIsNotAirLoopConnected) {
  Model model;
  PlantLoop plantLoop(model);
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, waterCoil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = waterCoil.handle();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_RemoveFromLoop_CleansPlantBranchWhenTerminalIsNotAirLoopConnected) {
  Model model;
  PlantLoop plantLoop(model);
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, waterCoil);

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(waterCoil.handle()));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, waterCoil);
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
  EXPECT_TRUE(model.getObject(waterCoil.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ConnectedCoilReplacementAndReloadMaintainAirPath) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-constant-volume-reheat-path.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingElectric originalCoil(model);
  CoilHeatingElectric replacementCoil(model);
  ASSERT_TRUE(replacementCoil.setName("Replacement Constant Volume Reheat Coil"));
  auto availability = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, availability, originalCoil);
  ASSERT_TRUE(terminal.setName("Reloaded Constant Volume Reheat Terminal"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));

  const auto terminalInlet = terminal.inletModelObject()->cast<Node>();
  const auto terminalOutlet = terminal.outletModelObject()->cast<Node>();
  ASSERT_TRUE(terminal.setReheatCoil(replacementCoil));
  EXPECT_FALSE(originalCoil.getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName));
  EXPECT_FALSE(originalCoil.getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));
  EXPECT_EQ(terminalInlet, replacementCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName).get());
  EXPECT_EQ(terminalOutlet, replacementCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName).get());

  Node wrongInlet(model);
  Node wrongOutlet(model);
  ASSERT_TRUE(wrongInlet.setName("Discarded CV Reheat Wrong Inlet"));
  ASSERT_TRUE(wrongOutlet.setName("Discarded CV Reheat Wrong Outlet"));
  ASSERT_TRUE(replacementCoil.setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, wrongInlet.handle()));
  ASSERT_TRUE(replacementCoil.setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, wrongOutlet.handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedTerminal =
    loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeReheat>("Reloaded Constant Volume Reheat Terminal");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Replacement Constant Volume Reheat Coil");
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedCoil);
  EXPECT_EQ(loadedTerminal->inletModelObject()->cast<Node>(),
            loadedCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName).get());
  EXPECT_EQ(loadedTerminal->outletModelObject()->cast<Node>(),
            loadedCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName).get());
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded CV Reheat Wrong Inlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded CV Reheat Wrong Outlet"));

  auto loadedTerminalWorkspaceImpl = loadedTerminal->getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(loadedTerminalWorkspaceImpl);
  const auto reheatCoilField = openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName;
  ASSERT_TRUE(loadedTerminalWorkspaceImpl->setPointer(reheatCoilField, openstudio::Handle(), false));
  ASSERT_TRUE(loadedTerminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(reheatCoilField, "Missing CV Reheat Coil", false));
  EXPECT_FALSE(loadedTerminal->getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName));
  ASSERT_TRUE(
    loadedTerminal->setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, "Coil:Heating:Electric"));
  loadedModel->canonicalize();
  EXPECT_TRUE(
    loadedTerminal->getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, true).value_or("").empty());
  EXPECT_TRUE(
    loadedTerminal->getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, false, true).value_or("").empty());
  EXPECT_FALSE(loadedTerminal->inletModelObject());
  EXPECT_FALSE(loadedTerminal->outletModelObject());
  EXPECT_FALSE(loadedTerminal->airLoopHVAC());
  EXPECT_FALSE(loadedCoil->inletModelObject());
  EXPECT_FALSE(loadedCoil->outletModelObject());

  openstudio::filesystem::remove(idfPath);
}
