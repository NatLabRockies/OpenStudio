/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/AirLoopHVACUnitaryHeatPumpWaterToAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpWaterToAir_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatPumpWaterToAir unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatPumpWaterToAir::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpWaterToAir_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpWaterToAir unitary(model);

  EXPECT_TRUE(unitary.setSupplyAirFlowRate(1.2));
  ASSERT_TRUE(unitary.supplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, unitary.supplyAirFlowRate().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateAutosized());
  unitary.autosizeSupplyAirFlowRate();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFanObjectType("Fan:OnOff"));
  EXPECT_EQ("Fan:OnOff", unitary.supplyAirFanObjectType());

  EXPECT_TRUE(unitary.setHeatingCoilObjectType("Coil:Heating:WaterToAirHeatPump:EquationFit"));
  EXPECT_EQ("Coil:Heating:WaterToAirHeatPump:EquationFit", unitary.heatingCoilObjectType());

  EXPECT_TRUE(unitary.setHeatingConvergence(0.002));
  EXPECT_DOUBLE_EQ(0.002, unitary.heatingConvergence());
  EXPECT_FALSE(unitary.isHeatingConvergenceDefaulted());
  unitary.resetHeatingConvergence();
  EXPECT_TRUE(unitary.isHeatingConvergenceDefaulted());

  EXPECT_TRUE(unitary.setCoolingCoilObjectType("Coil:Cooling:WaterToAirHeatPump:EquationFit"));
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:EquationFit", unitary.coolingCoilObjectType());

  EXPECT_TRUE(unitary.setCoolingConvergence(0.003));
  EXPECT_DOUBLE_EQ(0.003, unitary.coolingConvergence());
  EXPECT_FALSE(unitary.isCoolingConvergenceDefaulted());
  unitary.resetCoolingConvergence();
  EXPECT_TRUE(unitary.isCoolingConvergenceDefaulted());

  EXPECT_TRUE(unitary.setSupplementalHeatingCoilObjectType("Coil:Heating:Electric"));
  EXPECT_EQ("Coil:Heating:Electric", unitary.supplementalHeatingCoilObjectType());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperaturefromSupplementalHeater(45.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(45.0, unitary.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  unitary.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.0));
  EXPECT_DOUBLE_EQ(18.0, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  EXPECT_FALSE(unitary.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());
  unitary.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(unitary.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(unitary.setFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.fanPlacement());
  EXPECT_FALSE(unitary.isFanPlacementDefaulted());
  unitary.resetFanPlacement();
  EXPECT_TRUE(unitary.isFanPlacementDefaulted());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());
  EXPECT_FALSE(unitary.isDehumidificationControlTypeDefaulted());
  unitary.resetDehumidificationControlType();
  EXPECT_TRUE(unitary.isDehumidificationControlTypeDefaulted());

  EXPECT_TRUE(unitary.setHeatPumpCoilWaterFlowMode("ConstantOnDemand"));
  EXPECT_EQ("ConstantOnDemand", unitary.heatPumpCoilWaterFlowMode());
  EXPECT_FALSE(unitary.isHeatPumpCoilWaterFlowModeDefaulted());
  unitary.resetHeatPumpCoilWaterFlowMode();
  EXPECT_TRUE(unitary.isHeatPumpCoilWaterFlowModeDefaulted());

  EXPECT_TRUE(unitary.setDXHeatingCoilSizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, unitary.dXHeatingCoilSizingRatio());
  EXPECT_FALSE(unitary.isDXHeatingCoilSizingRatioDefaulted());
  unitary.resetDXHeatingCoilSizingRatio();
  EXPECT_TRUE(unitary.isDXHeatingCoilSizingRatioDefaulted());
}
