/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilWaterHeatingDesuperheater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_DefaultConstructor) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);
  EXPECT_EQ(CoilWaterHeatingDesuperheater::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_DOUBLE_EQ(5.0, coil.deadBandTemperatureDifference());
  EXPECT_FALSE(coil.isDeadBandTemperatureDifferenceDefaulted());
  EXPECT_FALSE(coil.ratedHeatReclaimRecoveryEfficiency());

  EXPECT_DOUBLE_EQ(50.0, coil.ratedInletWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, coil.ratedOutdoorAirTemperature());
  EXPECT_DOUBLE_EQ(60.0, coil.maximumInletWaterTemperatureforHeatReclaim());
  EXPECT_DOUBLE_EQ(0.0001, coil.waterFlowRate());

  EXPECT_DOUBLE_EQ(100.0, coil.waterPumpPower());
  EXPECT_FALSE(coil.isWaterPumpPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofPumpHeattoWater());
  EXPECT_FALSE(coil.isFractionofPumpHeattoWaterDefaulted());

  EXPECT_DOUBLE_EQ(0.0, coil.onCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_DOUBLE_EQ(0.0, coil.offCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOffCycleParasiticElectricLoadDefaulted());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);

  EXPECT_TRUE(coil.setDeadBandTemperatureDifference(3.3));
  EXPECT_DOUBLE_EQ(3.3, coil.deadBandTemperatureDifference());
  EXPECT_FALSE(coil.isDeadBandTemperatureDifferenceDefaulted());
  coil.resetDeadBandTemperatureDifference();
  EXPECT_TRUE(coil.isDeadBandTemperatureDifferenceDefaulted());

  EXPECT_TRUE(coil.setRatedHeatReclaimRecoveryEfficiency(0.27));
  ASSERT_TRUE(coil.ratedHeatReclaimRecoveryEfficiency());
  EXPECT_DOUBLE_EQ(0.27, *coil.ratedHeatReclaimRecoveryEfficiency());
  coil.resetRatedHeatReclaimRecoveryEfficiency();
  EXPECT_FALSE(coil.ratedHeatReclaimRecoveryEfficiency());

  EXPECT_TRUE(coil.setRatedInletWaterTemperature(48.0));
  EXPECT_DOUBLE_EQ(48.0, coil.ratedInletWaterTemperature());
  EXPECT_TRUE(coil.setRatedOutdoorAirTemperature(30.0));
  EXPECT_DOUBLE_EQ(30.0, coil.ratedOutdoorAirTemperature());
  EXPECT_TRUE(coil.setMaximumInletWaterTemperatureforHeatReclaim(58.0));
  EXPECT_DOUBLE_EQ(58.0, coil.maximumInletWaterTemperatureforHeatReclaim());
  EXPECT_TRUE(coil.setWaterFlowRate(0.00023));
  EXPECT_DOUBLE_EQ(0.00023, coil.waterFlowRate());

  EXPECT_TRUE(coil.setWaterPumpPower(333.0));
  EXPECT_DOUBLE_EQ(333.0, coil.waterPumpPower());
  EXPECT_FALSE(coil.isWaterPumpPowerDefaulted());
  coil.resetWaterPumpPower();
  EXPECT_TRUE(coil.isWaterPumpPowerDefaulted());

  EXPECT_TRUE(coil.setFractionofPumpHeattoWater(0.61));
  EXPECT_DOUBLE_EQ(0.61, coil.fractionofPumpHeattoWater());
  EXPECT_FALSE(coil.isFractionofPumpHeattoWaterDefaulted());
  coil.resetFractionofPumpHeattoWater();
  EXPECT_TRUE(coil.isFractionofPumpHeattoWaterDefaulted());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(125.0));
  EXPECT_DOUBLE_EQ(125.0, coil.onCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  coil.resetOnCycleParasiticElectricLoad();
  EXPECT_TRUE(coil.isOnCycleParasiticElectricLoadDefaulted());

  EXPECT_TRUE(coil.setOffCycleParasiticElectricLoad(44.0));
  EXPECT_DOUBLE_EQ(44.0, coil.offCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOffCycleParasiticElectricLoadDefaulted());
  coil.resetOffCycleParasiticElectricLoad();
  EXPECT_TRUE(coil.isOffCycleParasiticElectricLoadDefaulted());
}
