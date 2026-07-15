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
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"
#include "../StraightComponent/CoilCoolingFourPipeBeam.hpp"
#include "../StraightComponent/CoilHeatingFourPipeBeam.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam airTerminal(model);

  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), airTerminal.iddObject().type());
  EXPECT_FALSE(airTerminal.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.primaryAirAvailabilitySchedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.coolingAvailabilitySchedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.heatingAvailabilitySchedule());
  EXPECT_TRUE(airTerminal.isDesignPrimaryAirVolumeFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isDesignChilledWaterVolumeFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isDesignHotWaterVolumeFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isZoneTotalBeamLengthAutosized());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_CoilConstructor_Parity) {
  Model model;
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);

  AirTerminalSingleDuctConstantVolumeFourPipeBeam airTerminal(model, coolingCoil, heatingCoil);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.primaryAirAvailabilitySchedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.coolingAvailabilitySchedule());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), airTerminal.heatingAvailabilitySchedule());
  ASSERT_TRUE(airTerminal.coolingCoil());
  ASSERT_TRUE(airTerminal.heatingCoil());
  EXPECT_EQ(coolingCoil.handle(), airTerminal.coolingCoil()->handle());
  EXPECT_EQ(heatingCoil.handle(), airTerminal.heatingCoil()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam airTerminal(model);

  EXPECT_TRUE(airTerminal.setDesignPrimaryAirVolumeFlowRate(0.61));
  ASSERT_TRUE(airTerminal.designPrimaryAirVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.61, airTerminal.designPrimaryAirVolumeFlowRate().get());
  EXPECT_FALSE(airTerminal.isDesignPrimaryAirVolumeFlowRateAutosized());
  airTerminal.autosizeDesignPrimaryAirVolumeFlowRate();
  EXPECT_TRUE(airTerminal.isDesignPrimaryAirVolumeFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setDesignChilledWaterVolumeFlowRate(0.11));
  ASSERT_TRUE(airTerminal.designChilledWaterVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.11, airTerminal.designChilledWaterVolumeFlowRate().get());
  EXPECT_FALSE(airTerminal.isDesignChilledWaterVolumeFlowRateAutosized());
  airTerminal.autosizeDesignChilledWaterVolumeFlowRate();
  EXPECT_TRUE(airTerminal.isDesignChilledWaterVolumeFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setDesignHotWaterVolumeFlowRate(0.09));
  ASSERT_TRUE(airTerminal.designHotWaterVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.09, airTerminal.designHotWaterVolumeFlowRate().get());
  EXPECT_FALSE(airTerminal.isDesignHotWaterVolumeFlowRateAutosized());
  airTerminal.autosizeDesignHotWaterVolumeFlowRate();
  EXPECT_TRUE(airTerminal.isDesignHotWaterVolumeFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setZoneTotalBeamLength(4.3));
  ASSERT_TRUE(airTerminal.zoneTotalBeamLength());
  EXPECT_DOUBLE_EQ(4.3, airTerminal.zoneTotalBeamLength().get());
  EXPECT_FALSE(airTerminal.isZoneTotalBeamLengthAutosized());
  airTerminal.autosizeZoneTotalBeamLength();
  EXPECT_TRUE(airTerminal.isZoneTotalBeamLengthAutosized());

  EXPECT_TRUE(airTerminal.setRatedPrimaryAirFlowRateperBeamLength(0.047));
  EXPECT_DOUBLE_EQ(0.047, airTerminal.ratedPrimaryAirFlowRateperBeamLength());
  EXPECT_FALSE(airTerminal.isRatedPrimaryAirFlowRateperBeamLengthDefaulted());
  airTerminal.resetRatedPrimaryAirFlowRateperBeamLength();
  EXPECT_TRUE(airTerminal.isRatedPrimaryAirFlowRateperBeamLengthDefaulted());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model);

  ScheduleConstant primarySchedule(model);
  ASSERT_TRUE(primarySchedule.setValue(1.0));
  EXPECT_TRUE(terminal.setPrimaryAirAvailabilitySchedule(primarySchedule));
  EXPECT_EQ(primarySchedule.handle(), terminal.primaryAirAvailabilitySchedule().handle());

  ScheduleConstant coolingSchedule(model);
  ASSERT_TRUE(coolingSchedule.setValue(0.5));
  EXPECT_TRUE(terminal.setCoolingAvailabilitySchedule(coolingSchedule));
  EXPECT_EQ(coolingSchedule.handle(), terminal.coolingAvailabilitySchedule().handle());

  ScheduleConstant heatingSchedule(model);
  ASSERT_TRUE(heatingSchedule.setValue(0.25));
  EXPECT_TRUE(terminal.setHeatingAvailabilitySchedule(heatingSchedule));
  EXPECT_EQ(heatingSchedule.handle(), terminal.heatingAvailabilitySchedule().handle());

  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  EXPECT_TRUE(terminal.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.coolingCoil());
  ASSERT_TRUE(terminal.heatingCoil());
  EXPECT_EQ(coolingCoil.handle(), terminal.coolingCoil()->handle());
  EXPECT_EQ(heatingCoil.handle(), terminal.heatingCoil()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_ScheduleGetter_RepairsMissingReferences) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model);

  ASSERT_TRUE(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName, ""));
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName,
                                  openstudio::Handle()));
  ASSERT_TRUE(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName, ""));
  ASSERT_TRUE(
    terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName, openstudio::Handle()));
  ASSERT_TRUE(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName, ""));
  ASSERT_TRUE(
    terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName, openstudio::Handle()));

  const auto primary = terminal.primaryAirAvailabilitySchedule();
  const auto cooling = terminal.coolingAvailabilitySchedule();
  const auto heating = terminal.heatingAvailabilitySchedule();

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), primary);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), cooling);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), heating);

  auto storedPrimary =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName);
  auto storedCooling =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName);
  auto storedHeating =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName);

  ASSERT_TRUE(storedPrimary);
  ASSERT_TRUE(storedCooling);
  ASSERT_TRUE(storedHeating);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedPrimary);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedCooling);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedHeating);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_CoolingAndHeatingCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model);
  CoilHeatingElectric heatingElectric(model);
  EXPECT_FALSE(terminal.setCoolingCoil(heatingElectric));
  EXPECT_FALSE(terminal.coolingCoil());

  auto wrongCooling = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  EXPECT_FALSE(terminal.setCoolingCoil(wrongCooling));
  EXPECT_FALSE(terminal.coolingCoil());

  auto wrongHeating = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  EXPECT_FALSE(terminal.setHeatingCoil(wrongHeating));
  EXPECT_FALSE(terminal.heatingCoil());

  Model otherModel;
  auto foreignCooling = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, otherModel);
  auto foreignHeating = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, otherModel);
  EXPECT_FALSE(terminal.setCoolingCoil(foreignCooling));
  EXPECT_FALSE(terminal.setHeatingCoil(foreignHeating));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_AddToNode_ResolvesAirLoopHVACAndRegistersZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);

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

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_AddToNode_RespectsSecondBranchOrdering) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, dummyTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal));

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  ASSERT_EQ(2u, splitterOutlets.size());
  auto firstBranch = splitterOutlets[0].optionalCast<Node>();
  ASSERT_TRUE(firstBranch);
  auto secondBranch = splitterOutlets[1].optionalCast<Node>();
  ASSERT_TRUE(secondBranch);
  EXPECT_NE(*firstBranch, *secondBranch);

  auto terminalInlet = terminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalInlet);
  EXPECT_EQ(*secondBranch, *terminalInlet);

  auto terminalOutlet = terminal.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalOutlet);
  EXPECT_EQ(zone2.zoneAirNode(), *terminalOutlet);

  const auto zone2Equipment = zone2.equipment();
  ASSERT_EQ(1u, zone2Equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone2Equipment.front());

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);

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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_AddToNode_RejectsAlreadyConnectedTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, terminal));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto originalInlet = terminal.inletModelObject()->handle();
  const auto originalOutlet = terminal.outletModelObject()->handle();

  auto zone2AirNode = zone2.zoneAirNode();
  EXPECT_FALSE(terminal.addToNode(zone2AirNode));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(originalInlet, terminal.inletModelObject()->handle());
  EXPECT_EQ(originalOutlet, terminal.outletModelObject()->handle());

  ASSERT_EQ(1u, zone1.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone1.equipment().front());
  EXPECT_TRUE(zone2.equipment().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);
  ASSERT_TRUE(terminal.name());

  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, terminal.iddObject().name()));
  ASSERT_TRUE(adu.setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, terminal.handle()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto zoneAirNode = zone.zoneAirNode();
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(zoneAirNode, *adu.outletNode());

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_Remove_ReconnectsZoneBranchAndCleansZoneReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  auto coolingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam, model);
  auto heatingCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam, model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto zoneAirNode = zone.zoneAirNode();

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
  EXPECT_EQ(6u, airLoop.demandComponents().size());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_TRUE(model.getObject(coolingCoil.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_CoilFourPipeBeam_PlantDemandBranchLifecycle) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop hotWaterLoop(model);
  AirLoopHVAC airLoop(model);
  CoilCoolingFourPipeBeam coolingCoil1(model);
  CoilCoolingFourPipeBeam coolingCoil2(model);
  CoilHeatingFourPipeBeam heatingCoil1(model);
  CoilHeatingFourPipeBeam heatingCoil2(model);
  Node standaloneNode(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();

  EXPECT_FALSE(coolingCoil1.addToNode(standaloneNode));
  EXPECT_FALSE(coolingCoil1.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(coolingCoil1.plantLoop());
  EXPECT_FALSE(heatingCoil1.addToNode(standaloneNode));
  EXPECT_FALSE(heatingCoil1.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(heatingCoil1.plantLoop());

  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil1));
  ASSERT_TRUE(coolingCoil1.plantLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), coolingCoil1.plantLoop()->handle());
  ASSERT_TRUE(coolingCoil1.inletModelObject());
  ASSERT_TRUE(coolingCoil1.outletModelObject());

  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil2));
  ASSERT_TRUE(coolingCoil2.plantLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), coolingCoil2.plantLoop()->handle());
  ASSERT_TRUE(coolingCoil2.inletModelObject());
  ASSERT_TRUE(coolingCoil2.outletModelObject());
  EXPECT_NE(coolingCoil1.inletModelObject()->handle(), coolingCoil2.inletModelObject()->handle());

  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil1));
  ASSERT_TRUE(heatingCoil1.plantLoop());
  EXPECT_EQ(hotWaterLoop.handle(), heatingCoil1.plantLoop()->handle());
  ASSERT_TRUE(heatingCoil1.inletModelObject());
  ASSERT_TRUE(heatingCoil1.outletModelObject());

  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil2));
  ASSERT_TRUE(heatingCoil2.plantLoop());
  EXPECT_EQ(hotWaterLoop.handle(), heatingCoil2.plantLoop()->handle());
  ASSERT_TRUE(heatingCoil2.inletModelObject());
  ASSERT_TRUE(heatingCoil2.outletModelObject());
  EXPECT_NE(heatingCoil1.inletModelObject()->handle(), heatingCoil2.inletModelObject()->handle());

  ASSERT_TRUE(chilledWaterLoop.removeDemandBranchWithComponent(coolingCoil1));
  EXPECT_FALSE(coolingCoil1.inletModelObject());
  EXPECT_FALSE(coolingCoil1.outletModelObject());
  EXPECT_FALSE(coolingCoil1.plantLoop());
  ASSERT_TRUE(coolingCoil2.plantLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), coolingCoil2.plantLoop()->handle());
  EXPECT_TRUE(coolingCoil2.inletModelObject());
  EXPECT_TRUE(coolingCoil2.outletModelObject());

  ASSERT_TRUE(hotWaterLoop.removeDemandBranchWithComponent(heatingCoil1));
  EXPECT_FALSE(heatingCoil1.inletModelObject());
  EXPECT_FALSE(heatingCoil1.outletModelObject());
  EXPECT_FALSE(heatingCoil1.plantLoop());
  ASSERT_TRUE(heatingCoil2.plantLoop());
  EXPECT_EQ(hotWaterLoop.handle(), heatingCoil2.plantLoop()->handle());
  EXPECT_TRUE(heatingCoil2.inletModelObject());
  EXPECT_TRUE(heatingCoil2.outletModelObject());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_Remove_CleansCoilPlantDemandBranches) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop chilledWaterLoop(model);
  PlantLoop hotWaterLoop(model);
  CoilCoolingFourPipeBeam coolingCoil(model);
  CoilHeatingFourPipeBeam heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model, coolingCoil, heatingCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), coolingCoil.plantLoop()->handle());
  EXPECT_EQ(hotWaterLoop.handle(), heatingCoil.plantLoop()->handle());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  EXPECT_TRUE(chilledWaterLoop.demandComponents(CoilCoolingFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(hotWaterLoop.demandComponents(CoilHeatingFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_Remove_CleansCoolingOnlyCoilPlantDemandBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop chilledWaterLoop(model);
  CoilCoolingFourPipeBeam coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_FALSE(terminal.heatingCoil());

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  EXPECT_TRUE(chilledWaterLoop.demandComponents(CoilCoolingFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_Remove_CleansHeatingOnlyCoilPlantDemandBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop hotWaterLoop(model);
  CoilHeatingFourPipeBeam heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam terminal(model);
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_FALSE(terminal.coolingCoil());

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  EXPECT_TRUE(hotWaterLoop.demandComponents(CoilHeatingFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
}
