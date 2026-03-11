/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../SizingPeriod/DesignDay.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DesignDay_DefaultConstructor) {
  Model model;
  DesignDay designDay(model);

  EXPECT_EQ(DesignDay::iddObjectType(), designDay.iddObject().type());

  ASSERT_TRUE(designDay.wetBulbOrDewPointAtMaximumDryBulb());
  EXPECT_DOUBLE_EQ(23.0, *designDay.wetBulbOrDewPointAtMaximumDryBulb());
}

TEST_F(EPModelFixture, DesignDay_ScalarAccessors_RoundTrip) {
  Model model;
  DesignDay designDay(model);

  EXPECT_FALSE(DesignDay::validDayTypeValues().empty());
  EXPECT_FALSE(DesignDay::validHumidityConditionTypeValues().empty());
  EXPECT_FALSE(DesignDay::validDryBulbTemperatureRangeModifierTypeValues().empty());
  EXPECT_FALSE(DesignDay::validSolarModelIndicatorValues().empty());
  EXPECT_FALSE(DesignDay::validBeginEnvironmentResetModeValues().empty());

  EXPECT_TRUE(designDay.setMaximumDryBulbTemperature(34.5));
  EXPECT_DOUBLE_EQ(34.5, designDay.maximumDryBulbTemperature());

  EXPECT_TRUE(designDay.setDailyDryBulbTemperatureRange(12.1));
  EXPECT_DOUBLE_EQ(12.1, designDay.dailyDryBulbTemperatureRange());

  EXPECT_TRUE(designDay.setBarometricPressure(100100.0));
  EXPECT_DOUBLE_EQ(100100.0, designDay.barometricPressure());

  EXPECT_TRUE(designDay.setWindSpeed(5.5));
  EXPECT_DOUBLE_EQ(5.5, designDay.windSpeed());

  EXPECT_TRUE(designDay.setWindDirection(170.0));
  EXPECT_DOUBLE_EQ(170.0, designDay.windDirection());

  EXPECT_TRUE(designDay.setRainIndicator(true));
  EXPECT_TRUE(designDay.rainIndicator());

  EXPECT_TRUE(designDay.setSnowIndicator(false));
  EXPECT_FALSE(designDay.snowIndicator());

  EXPECT_TRUE(designDay.setDayOfMonth(21));
  EXPECT_EQ(21, designDay.dayOfMonth());

  EXPECT_TRUE(designDay.setMonth(7));
  EXPECT_EQ(7, designDay.month());

  EXPECT_TRUE(designDay.setDayType("SummerDesignDay"));
  EXPECT_EQ("SummerDesignDay", designDay.dayType());

  EXPECT_TRUE(designDay.setHumidityConditionType("Enthalpy"));
  EXPECT_EQ("Enthalpy", designDay.humidityConditionType());

  EXPECT_TRUE(designDay.setEnthalpyAtMaximumDryBulb(62000.0));
  ASSERT_TRUE(designDay.enthalpyAtMaximumDryBulb());
  EXPECT_DOUBLE_EQ(62000.0, *designDay.enthalpyAtMaximumDryBulb());
  EXPECT_DOUBLE_EQ(62000.0, designDay.humidityIndicatingConditionsAtMaximumDryBulb());

  EXPECT_TRUE(designDay.setDryBulbTemperatureRangeModifierType("DefaultMultipliers"));
  EXPECT_EQ("DefaultMultipliers", designDay.dryBulbTemperatureRangeModifierType());

  EXPECT_TRUE(designDay.setSolarModelIndicator("ASHRAETau"));
  EXPECT_EQ("ASHRAETau", designDay.solarModelIndicator());

  EXPECT_TRUE(designDay.setAshraeTaub(0.42));
  EXPECT_DOUBLE_EQ(0.42, designDay.ashraeTaub());
  EXPECT_DOUBLE_EQ(0.42, designDay.ashraeClearSkyOpticalDepthForBeamIrradiance());

  EXPECT_TRUE(designDay.setAshraeTaud(1.91));
  EXPECT_DOUBLE_EQ(1.91, designDay.ashraeTaud());
  EXPECT_DOUBLE_EQ(1.91, designDay.ashraeClearSkyOpticalDepthForDiffuseIrradiance());

  EXPECT_TRUE(designDay.setDailyWetBulbTemperatureRange(6.0));
  ASSERT_TRUE(designDay.dailyWetBulbTemperatureRange());
  EXPECT_DOUBLE_EQ(6.0, *designDay.dailyWetBulbTemperatureRange());

  EXPECT_TRUE(designDay.setMaximumNumberWarmupDays(18));
  ASSERT_TRUE(designDay.maximumNumberWarmupDays());
  EXPECT_EQ(18, *designDay.maximumNumberWarmupDays());

  std::string beginEnvironmentResetMode = designDay.beginEnvironmentResetMode();
  for (const auto& value : DesignDay::validBeginEnvironmentResetModeValues()) {
    if (value != beginEnvironmentResetMode) {
      beginEnvironmentResetMode = value;
      break;
    }
  }
  EXPECT_TRUE(designDay.setBeginEnvironmentResetMode(beginEnvironmentResetMode));
  EXPECT_EQ(beginEnvironmentResetMode, designDay.beginEnvironmentResetMode());

  designDay.resetMaximumNumberWarmupDays();
  EXPECT_FALSE(designDay.maximumNumberWarmupDays());

  designDay.resetDailyWetBulbTemperatureRange();
  EXPECT_FALSE(designDay.dailyWetBulbTemperatureRange());

  designDay.resetWetBulbOrDewPointAtMaximumDryBulb();
  EXPECT_FALSE(designDay.wetBulbOrDewPointAtMaximumDryBulb());

  designDay.resetHumidityRatioAtMaximumDryBulb();
  EXPECT_FALSE(designDay.humidityRatioAtMaximumDryBulb());

  designDay.resetEnthalpyAtMaximumDryBulb();
  EXPECT_FALSE(designDay.enthalpyAtMaximumDryBulb());
}
