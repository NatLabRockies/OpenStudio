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
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeam_FieldEnums.hxx>

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
  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);

  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);
  EXPECT_EQ(schedule.handle(), terminal.availabilitySchedule().handle());
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());
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

  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);
  EXPECT_TRUE(terminal.setCoolingCoil(coil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_CoolingCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

  CoilHeatingElectric heatingCoil(model);
  EXPECT_FALSE(terminal.setCoolingCoil(heatingCoil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());

  Model otherModel;
  auto foreignCoil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, otherModel);
  EXPECT_FALSE(terminal.setCoolingCoil(foreignCoil));
  EXPECT_EQ(coil.handle(), terminal.coilCoolingCooledBeam().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AvailabilityScheduleGetter_RepairsMissingReference) {
  Model model;
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);
  AirTerminalSingleDuctConstantVolumeCooledBeam terminal(model, schedule, coil);

  ASSERT_TRUE(terminal.setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName, openstudio::Handle()));
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
  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);
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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_AddToNode_ResolvesAirLoopHVACAndRegistersZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ScheduleConstant schedule(model);
  schedule.setValue(1.0);
  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);
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
  EXPECT_EQ(zoneAirNode, *outletNode);

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
  auto coil = ModelObject::create(openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam, model);
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
  EXPECT_EQ(zone2.zoneAirNode(), *terminalOutlet);

  const auto zone2Equipment = zone2.equipment();
  ASSERT_EQ(1u, zone2Equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone2Equipment.front());

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);
}
