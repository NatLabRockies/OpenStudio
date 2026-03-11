/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <algorithm>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorMicroCHPNonNormalizedParameters.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorMicroCHPNonNormalizedParameters_DefaultConstructor) {
  Model model;
  GeneratorMicroCHPNonNormalizedParameters object(model);
  EXPECT_EQ(GeneratorMicroCHPNonNormalizedParameters::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorMicroCHPNonNormalizedParameters_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorMicroCHPNonNormalizedParameters object(model);

  EXPECT_TRUE(object.setMaximumElectricPower(5500.0));
  ASSERT_TRUE(object.maximumElectricPower());
  EXPECT_DOUBLE_EQ(5500.0, object.maximumElectricPower().get());

  EXPECT_TRUE(object.setMinimumElectricPower(1650.0));
  ASSERT_TRUE(object.minimumElectricPower());
  EXPECT_DOUBLE_EQ(1650.0, object.minimumElectricPower().get());

  const auto coolingModes = GeneratorMicroCHPNonNormalizedParameters::coolingWaterFlowRateModeValues();
  EXPECT_FALSE(coolingModes.empty());
  EXPECT_NE(std::find(coolingModes.begin(), coolingModes.end(), "PlantControl"), coolingModes.end());
  EXPECT_TRUE(object.setCoolingWaterFlowRateMode("InternalControl"));
  ASSERT_TRUE(object.coolingWaterFlowRateMode());
  EXPECT_EQ("InternalControl", object.coolingWaterFlowRateMode().get());
  object.resetCoolingWaterFlowRateMode();
  ASSERT_TRUE(object.coolingWaterFlowRateMode());
  EXPECT_TRUE(object.coolingWaterFlowRateMode()->empty());

  EXPECT_TRUE(object.setAggregatedThermalMassofEnergyConversionPortionofGenerator(17000.0));
  ASSERT_TRUE(object.aggregatedThermalMassofEnergyConversionPortionofGenerator());
  EXPECT_DOUBLE_EQ(17000.0, object.aggregatedThermalMassofEnergyConversionPortionofGenerator().get());

  EXPECT_TRUE(object.setAggregatedThermalMassofHeatRecoveryPortionofGenerator(6000.0));
  ASSERT_TRUE(object.aggregatedThermalMassofHeatRecoveryPortionofGenerator());
  EXPECT_DOUBLE_EQ(6000.0, object.aggregatedThermalMassofHeatRecoveryPortionofGenerator().get());

  const auto warmUpModes = GeneratorMicroCHPNonNormalizedParameters::warmUpModeValues();
  EXPECT_FALSE(warmUpModes.empty());
  EXPECT_NE(std::find(warmUpModes.begin(), warmUpModes.end(), "TimeDelay"), warmUpModes.end());
  EXPECT_TRUE(object.setWarmUpMode("TimeDelay"));
  ASSERT_TRUE(object.warmUpMode());
  EXPECT_EQ("TimeDelay", object.warmUpMode().get());

  EXPECT_TRUE(object.setWarmUpDelayTime(60.0));
  ASSERT_TRUE(object.warmUpDelayTime());
  EXPECT_DOUBLE_EQ(60.0, object.warmUpDelayTime().get());
  object.resetWarmUpDelayTime();
  EXPECT_FALSE(object.warmUpDelayTime());

  const auto restartModes = GeneratorMicroCHPNonNormalizedParameters::restartModeValues();
  EXPECT_FALSE(restartModes.empty());
  EXPECT_NE(std::find(restartModes.begin(), restartModes.end(), "OptionalCoolDown"), restartModes.end());
  EXPECT_TRUE(object.setRestartMode("MandatoryCoolDown"));
  ASSERT_TRUE(object.restartMode());
  EXPECT_EQ("MandatoryCoolDown", object.restartMode().get());

  EXPECT_TRUE(object.setCoolDownDelayTime(120.0));
  ASSERT_TRUE(object.coolDownDelayTime());
  EXPECT_DOUBLE_EQ(120.0, object.coolDownDelayTime().get());
  object.resetCoolDownDelayTime();
  EXPECT_FALSE(object.coolDownDelayTime());
}
