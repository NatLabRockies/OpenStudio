/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirTemperaturePatternNondimensionalHeight.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirTemperaturePatternNondimensionalHeight_DefaultConstructor) {
  Model model;
  RoomAirTemperaturePatternNondimensionalHeight pattern(model);
  EXPECT_EQ(RoomAirTemperaturePatternNondimensionalHeight::iddObjectType(), pattern.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirTemperaturePatternNondimensionalHeight_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirTemperaturePatternNondimensionalHeight pattern(model);

  EXPECT_TRUE(pattern.setControlIntegerforPatternControlScheduleName(5));
  EXPECT_EQ(5, pattern.controlIntegerforPatternControlScheduleName());

  EXPECT_FALSE(pattern.thermostatOffset());
  EXPECT_FALSE(pattern.returnAirOffset());
  EXPECT_FALSE(pattern.exhaustAirOffset());

  EXPECT_TRUE(pattern.setThermostatOffset(0.3));
  ASSERT_TRUE(pattern.thermostatOffset());
  EXPECT_DOUBLE_EQ(0.3, pattern.thermostatOffset().get());
  pattern.resetThermostatOffset();
  EXPECT_FALSE(pattern.thermostatOffset());

  EXPECT_TRUE(pattern.setReturnAirOffset(0.5));
  ASSERT_TRUE(pattern.returnAirOffset());
  EXPECT_DOUBLE_EQ(0.5, pattern.returnAirOffset().get());
  pattern.resetReturnAirOffset();
  EXPECT_FALSE(pattern.returnAirOffset());

  EXPECT_TRUE(pattern.setExhaustAirOffset(0.7));
  ASSERT_TRUE(pattern.exhaustAirOffset());
  EXPECT_DOUBLE_EQ(0.7, pattern.exhaustAirOffset().get());
  pattern.resetExhaustAirOffset();
  EXPECT_FALSE(pattern.exhaustAirOffset());
}
