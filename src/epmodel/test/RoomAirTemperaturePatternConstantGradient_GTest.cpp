/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirTemperaturePatternConstantGradient.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirTemperaturePatternConstantGradient_DefaultConstructor) {
  Model model;
  RoomAirTemperaturePatternConstantGradient pattern(model);
  EXPECT_EQ(RoomAirTemperaturePatternConstantGradient::iddObjectType(), pattern.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirTemperaturePatternConstantGradient_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirTemperaturePatternConstantGradient pattern(model);

  EXPECT_TRUE(pattern.setControlIntegerforPatternControlScheduleName(4));
  EXPECT_EQ(4, pattern.controlIntegerforPatternControlScheduleName());

  EXPECT_FALSE(pattern.thermostatOffset());
  EXPECT_FALSE(pattern.returnAirOffset());
  EXPECT_FALSE(pattern.exhaustAirOffset());
  EXPECT_FALSE(pattern.temperatureGradient());

  EXPECT_TRUE(pattern.setThermostatOffset(0.2));
  ASSERT_TRUE(pattern.thermostatOffset());
  EXPECT_DOUBLE_EQ(0.2, pattern.thermostatOffset().get());
  pattern.resetThermostatOffset();
  EXPECT_FALSE(pattern.thermostatOffset());

  EXPECT_TRUE(pattern.setReturnAirOffset(0.4));
  ASSERT_TRUE(pattern.returnAirOffset());
  EXPECT_DOUBLE_EQ(0.4, pattern.returnAirOffset().get());
  pattern.resetReturnAirOffset();
  EXPECT_FALSE(pattern.returnAirOffset());

  EXPECT_TRUE(pattern.setExhaustAirOffset(0.6));
  ASSERT_TRUE(pattern.exhaustAirOffset());
  EXPECT_DOUBLE_EQ(0.6, pattern.exhaustAirOffset().get());
  pattern.resetExhaustAirOffset();
  EXPECT_FALSE(pattern.exhaustAirOffset());

  EXPECT_TRUE(pattern.setTemperatureGradient(1.1));
  ASSERT_TRUE(pattern.temperatureGradient());
  EXPECT_DOUBLE_EQ(1.1, pattern.temperatureGradient().get());
  pattern.resetTemperatureGradient();
  EXPECT_FALSE(pattern.temperatureGradient());
}
