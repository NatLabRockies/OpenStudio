/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/FanSystemModel.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanSystemModel_DefaultConstructor) {
  Model model;
  FanSystemModel fan(model);
  EXPECT_EQ(FanSystemModel::iddObjectType(), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
}

TEST_F(EPModelFixture, FanSystemModel_ScalarAccessors_RoundTrip) {
  Model model;
  FanSystemModel fan(model);

  EXPECT_TRUE(fan.setDesignMaximumAirFlowRate(1.33));
  ASSERT_TRUE(fan.designMaximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.33, fan.designMaximumAirFlowRate().get());
  EXPECT_FALSE(fan.isDesignMaximumAirFlowRateAutosized());

  fan.autosizeDesignMaximumAirFlowRate();
  EXPECT_TRUE(fan.isDesignMaximumAirFlowRateAutosized());

  const auto speedControlMethods = FanSystemModel::speedControlMethodValues();
  ASSERT_FALSE(speedControlMethods.empty());
  EXPECT_TRUE(fan.setSpeedControlMethod(speedControlMethods.front()));
  EXPECT_EQ(speedControlMethods.front(), fan.speedControlMethod());

  EXPECT_TRUE(fan.setElectricPowerMinimumFlowRateFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, fan.electricPowerMinimumFlowRateFraction());

  EXPECT_TRUE(fan.setDesignPressureRise(640.0));
  EXPECT_DOUBLE_EQ(640.0, fan.designPressureRise());

  EXPECT_TRUE(fan.setMotorEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, fan.motorEfficiency());

  EXPECT_TRUE(fan.setMotorInAirStreamFraction(1.0));
  EXPECT_DOUBLE_EQ(1.0, fan.motorInAirStreamFraction());

  EXPECT_TRUE(fan.setDesignElectricPowerConsumption(520.0));
  ASSERT_TRUE(fan.designElectricPowerConsumption());
  EXPECT_DOUBLE_EQ(520.0, fan.designElectricPowerConsumption().get());
  EXPECT_FALSE(fan.isDesignElectricPowerConsumptionAutosized());

  fan.autosizeDesignElectricPowerConsumption();
  EXPECT_TRUE(fan.isDesignElectricPowerConsumptionAutosized());

  const auto designPowerSizingMethods = FanSystemModel::designPowerSizingMethodValues();
  ASSERT_FALSE(designPowerSizingMethods.empty());
  EXPECT_TRUE(fan.setDesignPowerSizingMethod(designPowerSizingMethods.front()));
  EXPECT_EQ(designPowerSizingMethods.front(), fan.designPowerSizingMethod());

  EXPECT_TRUE(fan.setElectricPowerPerUnitFlowRate(840.0));
  EXPECT_DOUBLE_EQ(840.0, fan.electricPowerPerUnitFlowRate());

  EXPECT_TRUE(fan.setElectricPowerPerUnitFlowRatePerUnitPressure(1.68));
  EXPECT_DOUBLE_EQ(1.68, fan.electricPowerPerUnitFlowRatePerUnitPressure());

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.74));
  EXPECT_DOUBLE_EQ(0.74, fan.fanTotalEfficiency());

  EXPECT_FALSE(fan.nightVentilationModePressureRise());
  EXPECT_TRUE(fan.setNightVentilationModePressureRise(120.0));
  ASSERT_TRUE(fan.nightVentilationModePressureRise());
  EXPECT_DOUBLE_EQ(120.0, fan.nightVentilationModePressureRise().get());
  fan.resetNightVentilationModePressureRise();
  EXPECT_FALSE(fan.nightVentilationModePressureRise());

  EXPECT_FALSE(fan.nightVentilationModeFlowFraction());
  EXPECT_TRUE(fan.setNightVentilationModeFlowFraction(0.55));
  ASSERT_TRUE(fan.nightVentilationModeFlowFraction());
  EXPECT_DOUBLE_EQ(0.55, fan.nightVentilationModeFlowFraction().get());
  fan.resetNightVentilationModeFlowFraction();
  EXPECT_FALSE(fan.nightVentilationModeFlowFraction());

  EXPECT_TRUE(fan.setMotorLossRadiativeFraction(0.0));
  EXPECT_DOUBLE_EQ(0.0, fan.motorLossRadiativeFraction());

  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
}
