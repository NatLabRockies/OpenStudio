/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/CoilCoolingCooledBeam.hpp"
#include "../StraightComponent/CoilCoolingCooledBeam_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/ExtensibleIndex.hpp>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeam_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <set>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeCooledBeam airTerminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType(), airTerminal.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.availabilitySchedule());
  EXPECT_EQ("Passive", airTerminal.cooledBeamType());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_ScheduleAndCoilConstructor_Parity) {
  Model model;
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);

  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  EXPECT_EQ(schedule.handle(), terminal.availabilitySchedule().handle());
  HVACComponent returnedCoil = terminal.coilCoolingCooledBeam();
  EXPECT_EQ(coil.handle(), returnedCoil.handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_Remove_DisconnectedDeletesOwnedCoolingCoil) {
  Model model;
  ScheduleConstant schedule(model);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = coil.handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeCooledBeam airTerminal(model);

  EXPECT_TRUE(airTerminal.setCooledBeamType("Active"));
  EXPECT_EQ("Active", airTerminal.cooledBeamType());

  EXPECT_TRUE(airTerminal.setSupplyAirVolumetricFlowRate(0.65));
  ASSERT_TRUE(airTerminal.supplyAirVolumetricFlowRate());
  EXPECT_DOUBLE_EQ(0.65, airTerminal.supplyAirVolumetricFlowRate().get());
  EXPECT_FALSE(airTerminal.isSupplyAirVolumetricFlowRateDefaulted());
  EXPECT_FALSE(airTerminal.isSupplyAirVolumetricFlowRateAutosized());
  airTerminal.autosizeSupplyAirVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isSupplyAirVolumetricFlowRateAutosized());
  airTerminal.resetSupplyAirVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isSupplyAirVolumetricFlowRateDefaulted());

  EXPECT_TRUE(airTerminal.setMaximumTotalChilledWaterVolumetricFlowRate(0.20));
  ASSERT_TRUE(airTerminal.maximumTotalChilledWaterVolumetricFlowRate());
  EXPECT_DOUBLE_EQ(0.20, airTerminal.maximumTotalChilledWaterVolumetricFlowRate().get());
  EXPECT_FALSE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateDefaulted());
  EXPECT_FALSE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateAutosized());
  airTerminal.autosizeMaximumTotalChilledWaterVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateAutosized());
  airTerminal.resetMaximumTotalChilledWaterVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateDefaulted());

  EXPECT_TRUE(airTerminal.setNumberofBeams(6));
  ASSERT_TRUE(airTerminal.numberofBeams());
  EXPECT_EQ(6, airTerminal.numberofBeams().get());
  EXPECT_FALSE(airTerminal.isNumberofBeamsDefaulted());
  EXPECT_FALSE(airTerminal.isNumberofBeamsAutosized());
  airTerminal.autosizeNumberofBeams();
  EXPECT_TRUE(airTerminal.isNumberofBeamsAutosized());
  airTerminal.resetNumberofBeams();
  EXPECT_TRUE(airTerminal.isNumberofBeamsDefaulted());

  EXPECT_TRUE(airTerminal.setBeamLength(3.8));
  ASSERT_TRUE(airTerminal.beamLength());
  EXPECT_DOUBLE_EQ(3.8, airTerminal.beamLength().get());
  EXPECT_FALSE(airTerminal.isBeamLengthDefaulted());
  EXPECT_FALSE(airTerminal.isBeamLengthAutosized());
  airTerminal.autosizeBeamLength();
  EXPECT_TRUE(airTerminal.isBeamLengthAutosized());
  airTerminal.resetBeamLength();
  EXPECT_TRUE(airTerminal.isBeamLengthDefaulted());

  EXPECT_TRUE(airTerminal.setDesignInletWaterTemperature(14.2));
  EXPECT_DOUBLE_EQ(14.2, airTerminal.designInletWaterTemperature());
  EXPECT_FALSE(airTerminal.isDesignInletWaterTemperatureDefaulted());
  airTerminal.resetDesignInletWaterTemperature();
  EXPECT_TRUE(airTerminal.isDesignInletWaterTemperatureDefaulted());

  EXPECT_TRUE(airTerminal.setDesignOutletWaterTemperature(16.4));
  EXPECT_DOUBLE_EQ(16.4, airTerminal.designOutletWaterTemperature());
  EXPECT_FALSE(airTerminal.isDesignOutletWaterTemperatureDefaulted());
  airTerminal.resetDesignOutletWaterTemperature();
  EXPECT_TRUE(airTerminal.isDesignOutletWaterTemperatureDefaulted());

  EXPECT_TRUE(airTerminal.setCoefficientofInductionKin(0.35));
  ASSERT_TRUE(airTerminal.coefficientofInductionKin());
  EXPECT_DOUBLE_EQ(0.35, airTerminal.coefficientofInductionKin().get());
  EXPECT_FALSE(airTerminal.isCoefficientofInductionKinDefaulted());
  EXPECT_FALSE(airTerminal.isCoefficientofInductionKinAutocalculated());
  airTerminal.autocalculateCoefficientofInductionKin();
  EXPECT_TRUE(airTerminal.isCoefficientofInductionKinAutocalculated());
  airTerminal.resetCoefficientofInductionKin();
  EXPECT_TRUE(airTerminal.isCoefficientofInductionKinDefaulted());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model);

  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(0.75));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), terminal.availabilitySchedule().handle());

  CoilCoolingCooledBeam coil(model);
  EXPECT_TRUE(terminal.setCoolingCoil(coil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_CoolingCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

  CoilHeatingElectric heatingCoil(model);
  EXPECT_FALSE(terminal.setCoolingCoil(heatingCoil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());

  Model otherModel;
  CoilCoolingCooledBeam foreignCoil(otherModel);
  EXPECT_FALSE(terminal.setCoolingCoil(foreignCoil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());

  AirTerminalSingleDuctConstantVolumeCooledBeam otherTerminal(model);
  EXPECT_FALSE(otherTerminal.setCoolingCoil(coil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AvailabilityScheduleGetter_RepairsMissingReference) {
  Model model;
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

  ASSERT_TRUE(
    terminal.setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    terminal.getModelObjectTarget<Schedule>(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName));

  const auto repairedSchedule = terminal.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), repairedSchedule);
  const auto storedSchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedSchedule);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_RequiredCoilPreflightPreservesTopologyAndRetries) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model);

  const auto originalSplitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto originalMixerInlets = airLoop.zoneMixer().inletModelObjects();
  const auto originalNodeCount = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_EQ(originalSplitterOutlets, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(originalMixerInlets, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(originalNodeCount, model.getConcreteModelObjects<Node>().size());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  CoilCoolingCooledBeam coil(model);
  ASSERT_TRUE(terminal.setCoolingCoil(coil));
  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_TRUE(terminal.inletModelObject());
  EXPECT_TRUE(terminal.outletModelObject());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AddToNode_ResolvesAirLoopHVACAndRegistersZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

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
  EXPECT_NE(zoneAirNode, *outletNode);

  const auto connections = model.getConcreteModelObjects<ZoneHVACEquipmentConnections>();
  ASSERT_EQ(1u, connections.size());
  EXPECT_EQ(zone, connections.front().thermalZone());
  ASSERT_EQ(1u, connections.front().zoneAirInletNodes().size());
  EXPECT_EQ(connections.front().zoneAirInletNodes().front(), *outletNode);

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AddToNode_RespectsSecondBranchOrdering) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, dummyTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal));

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  ASSERT_EQ(2u, splitterOutlets.size());
  auto firstBranch = splitterOutlets[0].optionalCast<Node>();
  ASSERT_TRUE(firstBranch);
  auto secondBranch = splitterOutlets[1].optionalCast<Node>();
  ASSERT_TRUE(secondBranch);

  auto terminalInlet = terminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalInlet);
  EXPECT_EQ(*secondBranch, *terminalInlet);

  auto terminalOutlet = terminal.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalOutlet);
  EXPECT_NE(zone2.zoneAirNode(), *terminalOutlet);
  const auto connections = model.getConcreteModelObjects<ZoneHVACEquipmentConnections>();
  const auto connectionsIt = std::ranges::find_if(connections, [&zone2](const auto& candidate) { return candidate.thermalZone() == zone2; });
  ASSERT_NE(connections.end(), connectionsIt);
  ASSERT_EQ(1u, connectionsIt->zoneAirInletNodes().size());
  EXPECT_EQ(connectionsIt->zoneAirInletNodes().front(), *terminalOutlet);

  const auto zone2Equipment = zone2.equipment();
  ASSERT_EQ(1u, zone2Equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone2Equipment.front());

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();
  const auto connections = model.getConcreteModelObjects<ZoneHVACEquipmentConnections>();
  ASSERT_EQ(1u, connections.size());
  ASSERT_EQ(1u, connections.front().zoneAirInletNodes().size());
  const auto zoneInletNode = connections.front().zoneAirInletNodes().front();

  Node mismatchedMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_NE(zoneAirNode, zoneInletNode);
  EXPECT_EQ(zoneInletNode.cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_Remove_ReconnectsZoneBranchAndCleansZoneReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coilObject(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coilObject);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto zoneAirNode = zone.zoneAirNode();

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  EXPECT_NE(zoneAirNode, *inletNode);
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto zoneInletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(zoneInletNode);
  EXPECT_NE(zoneAirNode, *zoneInletNode);

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
  ASSERT_EQ(1u, zone.equipment().size());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneInletNode->cast<ModelObject>(), *splitterOutlet);
  EXPECT_EQ(7u, airLoop.demandComponents().size());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coilObject(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coilObject);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coilObject));
  const auto zoneAirNode = zone.zoneAirNode();
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto zoneInletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(zoneInletNode);
  EXPECT_NE(zoneAirNode, *zoneInletNode);

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneInletNode->cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(coilObject.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(coilObject.inletModelObject());
  EXPECT_FALSE(coilObject.outletModelObject());
  EXPECT_TRUE(plantLoop.demandComponents(CoilCoolingCooledBeam::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_CoilCoolingCooledBeam_PlantDemandBranchLifecycle) {
  Model model;
  PlantLoop plantLoop(model);
  AirLoopHVAC airLoop(model);
  CoilCoolingCooledBeam coil1(model);
  CoilCoolingCooledBeam coil2(model);
  Node standaloneNode(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();

  EXPECT_FALSE(coil1.addToNode(standaloneNode));
  EXPECT_FALSE(coil1.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(coil1.plantLoop());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil1));
  ASSERT_TRUE(coil1.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil1.plantLoop()->handle());
  ASSERT_TRUE(coil1.inletModelObject());
  ASSERT_TRUE(coil1.outletModelObject());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil2));
  ASSERT_TRUE(coil2.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil2.plantLoop()->handle());
  ASSERT_TRUE(coil2.inletModelObject());
  ASSERT_TRUE(coil2.outletModelObject());
  EXPECT_NE(coil1.inletModelObject()->handle(), coil2.inletModelObject()->handle());

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(coil1));
  EXPECT_FALSE(coil1.inletModelObject());
  EXPECT_FALSE(coil1.outletModelObject());
  EXPECT_FALSE(coil1.plantLoop());
  ASSERT_TRUE(coil2.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil2.plantLoop()->handle());
  EXPECT_TRUE(coil2.inletModelObject());
  EXPECT_TRUE(coil2.outletModelObject());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_Remove_CleansCoolingCoilPlantDemandBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = coil.handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil.plantLoop()->handle());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  EXPECT_TRUE(plantLoop.demandComponents(CoilCoolingCooledBeam::iddObjectType()).empty());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_Remove_MalformedPlantReferencePreservesParentAndChild) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);
  ScheduleConstant schedule(model);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = coil.handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.inletModelObject());
  const auto terminalInletHandle = terminal.inletModelObject()->handle();

  // Deliberately point the coil at plant endpoint nodes without placing it on
  // a demand-equipment branch. plantLoop() resolves, but branch removal is invalid.
  auto coilImpl = coil.getImpl<openstudio::epmodel::detail::CoilCoolingCooledBeam_Impl>();
  ASSERT_TRUE(coilImpl);
  ASSERT_TRUE(coilImpl->setPointer(coil.inletPort(), plantLoop.demandInletNode().handle(), false));
  ASSERT_TRUE(coilImpl->setPointer(coil.outletPort(), plantLoop.demandOutletNode().handle(), false));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_FALSE(plantLoop.demandComponent(coilHandle));

  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_FALSE(terminal.removeFromLoop());
  EXPECT_TRUE(terminal.remove().empty());
  EXPECT_FALSE(airLoop.removeBranchForZone(zone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }

  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_TRUE(model.getObject(terminalHandle));
  EXPECT_TRUE(model.getObject(coilHandle));
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType()).size());
  EXPECT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil.plantLoop()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_MalformedAirPathPreservesPlantAndZoneTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());

  const auto terminalInletHandle = terminal.inletModelObject()->handle();
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();
  const auto coilInletHandle = coil.inletModelObject()->handle();
  const auto coilOutletHandle = coil.outletModelObject()->handle();
  const auto plantComponentsBefore = plantLoop.demandComponents();
  const auto zoneEquipmentBefore = zone.equipment();

  Node wrongSplitterOutlet(model);
  ASSERT_TRUE(airLoop.zoneSplitter().setOutletModelObject(0u, wrongSplitterOutlet.cast<ModelObject>()));
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_FALSE(terminal.removeFromLoop());
  EXPECT_TRUE(terminal.remove().empty());
  EXPECT_FALSE(airLoop.removeBranchForZone(zone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminalOutletHandle, terminal.outletModelObject()->handle());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(coilInletHandle, coil.inletModelObject()->handle());
  EXPECT_EQ(coilOutletHandle, coil.outletModelObject()->handle());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_ContainedRemovalPreservesAllTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  AirTerminalSingleDuctConstantVolumeCooledBeam owner(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  // Use the owner's relationship field directly to construct a containment
  // case that the typed cooled-beam setter correctly refuses.
  auto ownerImpl = owner.getImpl<openstudio::epmodel::detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>();
  ASSERT_TRUE(ownerImpl);
  ASSERT_TRUE(
    ownerImpl->setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName, terminal.handle(), false));
  ASSERT_TRUE(terminal.containingHVACComponent());
  EXPECT_EQ(owner.handle(), terminal.containingHVACComponent()->handle());

  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto plantComponentsBefore = plantLoop.demandComponents();
  const auto zoneEquipmentBefore = zone.equipment();
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());
  const auto terminalInletBefore = terminal.inletModelObject()->handle();
  const auto terminalOutletBefore = terminal.outletModelObject()->handle();
  const auto coilInletBefore = coil.inletModelObject()->handle();
  const auto coilOutletBefore = coil.outletModelObject()->handle();
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_TRUE(terminal.remove().empty());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(terminalInletBefore, terminal.inletModelObject()->handle());
  EXPECT_EQ(terminalOutletBefore, terminal.outletModelObject()->handle());
  EXPECT_EQ(coilInletBefore, coil.inletModelObject()->handle());
  EXPECT_EQ(coilOutletBefore, coil.outletModelObject()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_RawPlantNodePreflightIsReadOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  CoilCoolingCooledBeam coil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(coil.inletModelObject());
  const auto coilInlet = coil.inletModelObject()->cast<Node>();

  auto plantLoopImpl = plantLoop.getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
  ASSERT_TRUE(plantLoopImpl);
  const auto equipmentBranches = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, equipmentBranches.size());
  auto branch = equipmentBranches.front();
  ASSERT_EQ(1u, branch.extensibleGroups().size());
  const auto inletField = branch.iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentInletNodeName));
  ASSERT_TRUE(branch.setPointer(inletField, openstudio::Handle()));
  auto branchImpl = branch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(branchImpl);
  ASSERT_TRUE(branchImpl->openstudio::detail::IdfObject_Impl::setString(inletField, coilInlet.nameString(), false));
  const auto inletSourcesBefore = coilInlet.sources();
  EXPECT_EQ(inletSourcesBefore.end(),
            std::ranges::find_if(inletSourcesBefore, [&](const auto& source) { return source.handle() == branch.handle(); }));
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_FALSE(terminal.removeFromLoop());
  EXPECT_TRUE(terminal.remove().empty());
  EXPECT_FALSE(airLoop.removeBranchForZone(zone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(inletSourcesBefore, coilInlet.sources());
  ASSERT_TRUE(branchImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true));
  EXPECT_EQ(coilInlet.nameString(), *branchImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true));
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(coil.handle()));
  EXPECT_EQ(1u, zone.equipment().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_SharedPlenumRemovalPreservesSibling) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone siblingZone(model);
  ThermalZone targetZone(model);
  ThermalZone supplyPlenumZone(model);
  ThermalZone returnPlenumZone(model);
  ScheduleConstant schedule(model);
  CoilCoolingCooledBeam siblingCoil(model);
  CoilCoolingCooledBeam targetCoil(model);
  AirTerminalSingleDuctConstantVolumeCooledBeam siblingTerminal(model, schedule, siblingCoil);
  AirTerminalSingleDuctConstantVolumeCooledBeam targetTerminal(model, schedule, targetCoil);
  ASSERT_TRUE(airLoop.addBranchForZone(siblingZone, siblingTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(targetZone, targetTerminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(siblingCoil));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(targetCoil));
  ASSERT_TRUE(siblingZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(targetZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(siblingZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(targetZone.setReturnPlenum(returnPlenumZone));
  ASSERT_EQ(2u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().outletModelObjects().size());
  ASSERT_EQ(2u, model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().front().inletModelObjects().size());
  const auto targetTerminalHandle = targetTerminal.handle();
  const auto targetCoilHandle = targetCoil.handle();

  ASSERT_TRUE(targetTerminal.isRemovable());
  ASSERT_TRUE(airLoop.removeBranchForZone(targetZone));

  EXPECT_FALSE(model.getObject(targetTerminalHandle));
  EXPECT_FALSE(model.getObject(targetCoilHandle));
  EXPECT_TRUE(model.getObject(siblingTerminal.handle()));
  EXPECT_TRUE(model.getObject(siblingCoil.handle()));
  EXPECT_TRUE(siblingTerminal.airLoopHVAC());
  ASSERT_TRUE(siblingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), siblingCoil.plantLoop()->handle());
  EXPECT_TRUE(siblingCoil.inletModelObject());
  EXPECT_TRUE(siblingCoil.outletModelObject());
  auto plantLoopImpl = plantLoop.getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
  ASSERT_TRUE(plantLoopImpl);
  EXPECT_EQ(1u, plantLoopImpl->demandEquipmentBranches().size());
  EXPECT_EQ(1u, siblingZone.equipment().size());
  EXPECT_TRUE(targetZone.equipment().empty());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().outletModelObjects().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().front().inletModelObjects().size());
}
