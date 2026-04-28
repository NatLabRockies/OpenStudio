/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>

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
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName, openstudio::Handle()));
  ASSERT_TRUE(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName, ""));
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName, openstudio::Handle()));
  ASSERT_TRUE(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName, ""));
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName, openstudio::Handle()));

  const auto primary = terminal.primaryAirAvailabilitySchedule();
  const auto cooling = terminal.coolingAvailabilitySchedule();
  const auto heating = terminal.heatingAvailabilitySchedule();

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), primary);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), cooling);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), heating);

  auto storedPrimary = terminal.getModelObjectTarget<Schedule>(
    openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName);
  auto storedCooling = terminal.getModelObjectTarget<Schedule>(
    openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName);
  auto storedHeating = terminal.getModelObjectTarget<Schedule>(
    openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName);

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
