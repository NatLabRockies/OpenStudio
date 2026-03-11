/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirTemperaturePatternSurfaceMapping.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirTemperaturePatternSurfaceMapping_DefaultConstructor) {
  Model model;
  RoomAirTemperaturePatternSurfaceMapping pattern(model);
  EXPECT_EQ(RoomAirTemperaturePatternSurfaceMapping::iddObjectType(), pattern.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirTemperaturePatternSurfaceMapping_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirTemperaturePatternSurfaceMapping pattern(model);

  EXPECT_TRUE(pattern.setControlIntegerforPatternControlScheduleName(6));
  EXPECT_EQ(6, pattern.controlIntegerforPatternControlScheduleName());

  EXPECT_FALSE(pattern.thermostatOffset());
  EXPECT_FALSE(pattern.returnAirOffset());
  EXPECT_FALSE(pattern.exhaustAirOffset());

  EXPECT_TRUE(pattern.setThermostatOffset(0.9));
  ASSERT_TRUE(pattern.thermostatOffset());
  EXPECT_DOUBLE_EQ(0.9, pattern.thermostatOffset().get());
  pattern.resetThermostatOffset();
  EXPECT_FALSE(pattern.thermostatOffset());

  EXPECT_TRUE(pattern.setReturnAirOffset(1.2));
  ASSERT_TRUE(pattern.returnAirOffset());
  EXPECT_DOUBLE_EQ(1.2, pattern.returnAirOffset().get());
  pattern.resetReturnAirOffset();
  EXPECT_FALSE(pattern.returnAirOffset());

  EXPECT_TRUE(pattern.setExhaustAirOffset(1.5));
  ASSERT_TRUE(pattern.exhaustAirOffset());
  EXPECT_DOUBLE_EQ(1.5, pattern.exhaustAirOffset().get());
  pattern.resetExhaustAirOffset();
  EXPECT_FALSE(pattern.exhaustAirOffset());
}
