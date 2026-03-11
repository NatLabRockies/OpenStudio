/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirTemperaturePatternTwoGradient.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirTemperaturePatternTwoGradient_DefaultConstructor) {
  Model model;
  RoomAirTemperaturePatternTwoGradient pattern(model);
  EXPECT_EQ(RoomAirTemperaturePatternTwoGradient::iddObjectType(), pattern.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirTemperaturePatternTwoGradient_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirTemperaturePatternTwoGradient pattern(model);

  EXPECT_TRUE(pattern.setControlIntegerforPatternControlScheduleName(7));
  EXPECT_EQ(7, pattern.controlIntegerforPatternControlScheduleName());

  EXPECT_FALSE(pattern.thermostatHeight());
  EXPECT_FALSE(pattern.returnAirHeight());
  EXPECT_FALSE(pattern.exhaustAirHeight());
  EXPECT_FALSE(pattern.temperatureGradientLowerBound());
  EXPECT_FALSE(pattern.temperatureGradientUpperBound());
  EXPECT_FALSE(pattern.gradientInterpolationMode());
  EXPECT_FALSE(pattern.upperTemperatureBound());
  EXPECT_FALSE(pattern.lowerTemperatureBound());
  EXPECT_FALSE(pattern.upperHeatRateBound());
  EXPECT_FALSE(pattern.lowerHeatRateBound());

  EXPECT_TRUE(pattern.setThermostatHeight(1.1));
  ASSERT_TRUE(pattern.thermostatHeight());
  EXPECT_DOUBLE_EQ(1.1, pattern.thermostatHeight().get());
  pattern.resetThermostatHeight();
  EXPECT_FALSE(pattern.thermostatHeight());

  EXPECT_TRUE(pattern.setReturnAirHeight(2.2));
  ASSERT_TRUE(pattern.returnAirHeight());
  EXPECT_DOUBLE_EQ(2.2, pattern.returnAirHeight().get());
  pattern.resetReturnAirHeight();
  EXPECT_FALSE(pattern.returnAirHeight());

  EXPECT_TRUE(pattern.setExhaustAirHeight(3.3));
  ASSERT_TRUE(pattern.exhaustAirHeight());
  EXPECT_DOUBLE_EQ(3.3, pattern.exhaustAirHeight().get());
  pattern.resetExhaustAirHeight();
  EXPECT_FALSE(pattern.exhaustAirHeight());

  EXPECT_TRUE(pattern.setTemperatureGradientLowerBound(0.4));
  ASSERT_TRUE(pattern.temperatureGradientLowerBound());
  EXPECT_DOUBLE_EQ(0.4, pattern.temperatureGradientLowerBound().get());
  pattern.resetTemperatureGradientLowerBound();
  EXPECT_FALSE(pattern.temperatureGradientLowerBound());

  EXPECT_TRUE(pattern.setTemperatureGradientUpperBound(0.9));
  ASSERT_TRUE(pattern.temperatureGradientUpperBound());
  EXPECT_DOUBLE_EQ(0.9, pattern.temperatureGradientUpperBound().get());
  pattern.resetTemperatureGradientUpperBound();
  EXPECT_FALSE(pattern.temperatureGradientUpperBound());

  ASSERT_FALSE(RoomAirTemperaturePatternTwoGradient::gradientInterpolationModeValues().empty());
  EXPECT_TRUE(pattern.setGradientInterpolationMode("SensibleCoolingLoad"));
  ASSERT_TRUE(pattern.gradientInterpolationMode());
  EXPECT_EQ("SensibleCoolingLoad", pattern.gradientInterpolationMode().get());
  pattern.resetGradientInterpolationMode();
  EXPECT_FALSE(pattern.gradientInterpolationMode());

  EXPECT_TRUE(pattern.setUpperTemperatureBound(29.0));
  ASSERT_TRUE(pattern.upperTemperatureBound());
  EXPECT_DOUBLE_EQ(29.0, pattern.upperTemperatureBound().get());
  pattern.resetUpperTemperatureBound();
  EXPECT_FALSE(pattern.upperTemperatureBound());

  EXPECT_TRUE(pattern.setLowerTemperatureBound(17.0));
  ASSERT_TRUE(pattern.lowerTemperatureBound());
  EXPECT_DOUBLE_EQ(17.0, pattern.lowerTemperatureBound().get());
  pattern.resetLowerTemperatureBound();
  EXPECT_FALSE(pattern.lowerTemperatureBound());

  EXPECT_TRUE(pattern.setUpperHeatRateBound(1500.0));
  ASSERT_TRUE(pattern.upperHeatRateBound());
  EXPECT_DOUBLE_EQ(1500.0, pattern.upperHeatRateBound().get());
  pattern.resetUpperHeatRateBound();
  EXPECT_FALSE(pattern.upperHeatRateBound());

  EXPECT_TRUE(pattern.setLowerHeatRateBound(-1500.0));
  ASSERT_TRUE(pattern.lowerHeatRateBound());
  EXPECT_DOUBLE_EQ(-1500.0, pattern.lowerHeatRateBound().get());
  pattern.resetLowerHeatRateBound();
  EXPECT_FALSE(pattern.lowerHeatRateBound());
}
