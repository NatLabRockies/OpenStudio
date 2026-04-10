/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_FALSE(radiant.hydronicTubingLength());
  EXPECT_FALSE(radiant.ratedFlowRate());
  EXPECT_EQ(0u, radiant.inletPort());
  EXPECT_EQ(0u, radiant.outletPort());
  ASSERT_EQ(2u, radiant.children().size());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_TRUE(radiant.setHydronicTubingLength(200.0));
  ASSERT_TRUE(radiant.hydronicTubingLength());
  EXPECT_DOUBLE_EQ(200.0, radiant.hydronicTubingLength().get());
  radiant.autosizeHydronicTubingLength();
  EXPECT_TRUE(radiant.isHydronicTubingLengthAutosized());

  EXPECT_TRUE(radiant.setRatedFlowRate(0.25));
  ASSERT_TRUE(radiant.ratedFlowRate());
  EXPECT_DOUBLE_EQ(0.25, radiant.ratedFlowRate().get());
  radiant.autosizeRatedFlowRate();
  EXPECT_TRUE(radiant.isRatedFlowRateAutosized());

  EXPECT_TRUE(radiant.setRatedPumpHead(150000));
  EXPECT_DOUBLE_EQ(150000, radiant.ratedPumpHead());
  radiant.resetRatedPumpHead();
  EXPECT_TRUE(radiant.isRatedPumpHeadDefaulted());

  EXPECT_TRUE(radiant.setRatedPowerConsumption(1200));
  ASSERT_TRUE(radiant.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(1200, radiant.ratedPowerConsumption().get());
  radiant.resetRatedPowerConsumption();
  EXPECT_FALSE(radiant.ratedPowerConsumption());

  EXPECT_TRUE(radiant.setFluidtoRadiantSurfaceHeatTransferModel("ISOStandard"));
  EXPECT_EQ("ISOStandard", radiant.fluidtoRadiantSurfaceHeatTransferModel());
  radiant.resetFluidtoRadiantSurfaceHeatTransferModel();
  EXPECT_TRUE(radiant.isFluidtoRadiantSurfaceHeatTransferModelDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingInsideDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, radiant.hydronicTubingInsideDiameter());
  radiant.resetHydronicTubingInsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingInsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingOutsideDiameter(0.024));
  EXPECT_DOUBLE_EQ(0.024, radiant.hydronicTubingOutsideDiameter());
  radiant.resetHydronicTubingOutsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingOutsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingConductivity(0.45));
  EXPECT_DOUBLE_EQ(0.45, radiant.hydronicTubingConductivity());
  radiant.resetHydronicTubingConductivity();
  EXPECT_TRUE(radiant.isHydronicTubingConductivityDefaulted());

  EXPECT_TRUE(radiant.setTemperatureControlType("SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(0.5));
  EXPECT_DOUBLE_EQ(0.5, radiant.runningMeanOutdoorDryBulbTemperatureWeightingFactor());
  radiant.resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
  EXPECT_TRUE(radiant.isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted());

  EXPECT_TRUE(radiant.setMotorEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, radiant.motorEfficiency());
  radiant.resetMotorEfficiency();
  EXPECT_TRUE(radiant.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(radiant.setFractionofMotorInefficienciestoFluidStream(0.1));
  EXPECT_DOUBLE_EQ(0.1, radiant.fractionofMotorInefficienciestoFluidStream());
  radiant.resetFractionofMotorInefficienciestoFluidStream();
  EXPECT_TRUE(radiant.isFractionofMotorInefficienciestoFluidStreamDefaulted());

  EXPECT_TRUE(radiant.setNumberofCircuits("CalculateFromCircuitLength"));
  EXPECT_EQ("CalculateFromCircuitLength", radiant.numberofCircuits());
  radiant.resetNumberofCircuits();
  EXPECT_TRUE(radiant.isNumberofCircuitsDefaulted());

  EXPECT_TRUE(radiant.setCircuitLength(200.0));
  EXPECT_DOUBLE_EQ(200.0, radiant.circuitLength());
  radiant.resetCircuitLength();
  EXPECT_TRUE(radiant.isCircuitLengthDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  EXPECT_TRUE(radiant.addToThermalZone(zone));
  ASSERT_TRUE(radiant.thermalZone());
  EXPECT_EQ(zone, radiant.thermalZone().get());
  EXPECT_FALSE(radiant.inletNode());
  EXPECT_FALSE(radiant.outletNode());

  radiant.removeFromThermalZone();
  EXPECT_FALSE(radiant.thermalZone());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_TransientCompanionCoils_WriteThroughParentStorage) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  ScheduleConstant availability(model);
  ScheduleConstant pump(model);
  ScheduleConstant changeover(model);
  ScheduleConstant heatingHighWater(model);
  ScheduleConstant heatingLowWater(model);
  ScheduleConstant heatingHighControl(model);
  ScheduleConstant heatingLowControl(model);
  ScheduleConstant coolingHighWater(model);
  ScheduleConstant coolingLowWater(model);
  ScheduleConstant coolingHighControl(model);
  ScheduleConstant coolingLowControl(model);

  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(pump.setValue(0.5));
  ASSERT_TRUE(changeover.setValue(2.0));
  ASSERT_TRUE(heatingHighWater.setValue(60.0));
  ASSERT_TRUE(heatingLowWater.setValue(35.0));
  ASSERT_TRUE(heatingHighControl.setValue(23.0));
  ASSERT_TRUE(heatingLowControl.setValue(20.0));
  ASSERT_TRUE(coolingHighWater.setValue(18.0));
  ASSERT_TRUE(coolingLowWater.setValue(12.0));
  ASSERT_TRUE(coolingHighControl.setValue(26.0));
  ASSERT_TRUE(coolingLowControl.setValue(22.0));

  EXPECT_TRUE(radiant.setAvailabilitySchedule(availability));
  EXPECT_TRUE(radiant.setPumpFlowRateSchedule(pump));
  EXPECT_TRUE(radiant.setChangeoverDelayTimePeriodSchedule(changeover));

  auto heatingCoil = radiant.heatingCoil();
  auto coolingCoil = radiant.coolingCoil();

  EXPECT_TRUE(heatingCoil.setHeatingHighWaterTemperatureSchedule(heatingHighWater));
  EXPECT_TRUE(heatingCoil.setHeatingLowWaterTemperatureSchedule(heatingLowWater));
  EXPECT_TRUE(heatingCoil.setHeatingHighControlTemperatureSchedule(heatingHighControl));
  EXPECT_TRUE(heatingCoil.setHeatingLowControlTemperatureSchedule(heatingLowControl));

  EXPECT_TRUE(coolingCoil.setCoolingHighWaterTemperatureSchedule(coolingHighWater));
  EXPECT_TRUE(coolingCoil.setCoolingLowWaterTemperatureSchedule(coolingLowWater));
  EXPECT_TRUE(coolingCoil.setCoolingHighControlTemperatureSchedule(coolingHighControl));
  EXPECT_TRUE(coolingCoil.setCoolingLowControlTemperatureSchedule(coolingLowControl));
  EXPECT_TRUE(coolingCoil.setCondensationControlType("VariableOff"));
  EXPECT_TRUE(coolingCoil.setCondensationControlDewpointOffset(1.5));

  ASSERT_TRUE(radiant.availabilitySchedule());
  EXPECT_EQ(availability.handle(), radiant.availabilitySchedule()->handle());
  ASSERT_TRUE(radiant.pumpFlowRateSchedule());
  EXPECT_EQ(pump.handle(), radiant.pumpFlowRateSchedule()->handle());
  ASSERT_TRUE(radiant.changeoverDelayTimePeriodSchedule());
  EXPECT_EQ(changeover.handle(), radiant.changeoverDelayTimePeriodSchedule()->handle());

  ASSERT_TRUE(heatingCoil.heatingHighWaterTemperatureSchedule());
  EXPECT_EQ(heatingHighWater.handle(), heatingCoil.heatingHighWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(heatingCoil.heatingLowWaterTemperatureSchedule());
  EXPECT_EQ(heatingLowWater.handle(), heatingCoil.heatingLowWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(heatingCoil.heatingHighControlTemperatureSchedule());
  EXPECT_EQ(heatingHighControl.handle(), heatingCoil.heatingHighControlTemperatureSchedule()->handle());
  ASSERT_TRUE(heatingCoil.heatingLowControlTemperatureSchedule());
  EXPECT_EQ(heatingLowControl.handle(), heatingCoil.heatingLowControlTemperatureSchedule()->handle());

  ASSERT_TRUE(coolingCoil.coolingHighWaterTemperatureSchedule());
  EXPECT_EQ(coolingHighWater.handle(), coolingCoil.coolingHighWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(coolingCoil.coolingLowWaterTemperatureSchedule());
  EXPECT_EQ(coolingLowWater.handle(), coolingCoil.coolingLowWaterTemperatureSchedule()->handle());
  ASSERT_TRUE(coolingCoil.coolingHighControlTemperatureSchedule());
  EXPECT_EQ(coolingHighControl.handle(), coolingCoil.coolingHighControlTemperatureSchedule()->handle());
  ASSERT_TRUE(coolingCoil.coolingLowControlTemperatureSchedule());
  EXPECT_EQ(coolingLowControl.handle(), coolingCoil.coolingLowControlTemperatureSchedule()->handle());
  EXPECT_EQ("VariableOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, coolingCoil.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantConstFlow_TransientCompanionCoils_ResolveParentWaterNodes) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);

  Node heatingInlet = model.getOrCreateTransientByName<Node>("Radiant Heating Inlet");
  Node heatingOutlet = model.getOrCreateTransientByName<Node>("Radiant Heating Outlet");
  Node coolingInlet = model.getOrCreateTransientByName<Node>("Radiant Cooling Inlet");
  Node coolingOutlet = model.getOrCreateTransientByName<Node>("Radiant Cooling Outlet");

  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName, heatingInlet.handle()));
  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, heatingOutlet.handle()));
  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName, coolingInlet.handle()));
  ASSERT_TRUE(
    radiant.setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName, coolingOutlet.handle()));

  auto heatingCoil = radiant.heatingCoil();
  auto coolingCoil = radiant.coolingCoil();

  ASSERT_TRUE(heatingCoil.inletModelObject());
  EXPECT_EQ(heatingInlet.handle(), heatingCoil.inletModelObject()->handle());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  EXPECT_EQ(heatingOutlet.handle(), heatingCoil.outletModelObject()->handle());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(coolingInlet.handle(), coolingCoil.inletModelObject()->handle());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  EXPECT_EQ(coolingOutlet.handle(), coolingCoil.outletModelObject()->handle());

  EXPECT_FALSE(heatingCoil.addToNode(heatingInlet));
  EXPECT_FALSE(coolingCoil.addToNode(coolingInlet));
}
