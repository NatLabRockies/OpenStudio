/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirTemperaturePatternUserDefined.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirTemperaturePatternUserDefined_DefaultConstructor) {
  Model model;
  RoomAirTemperaturePatternUserDefined pattern(model);
  EXPECT_EQ(RoomAirTemperaturePatternUserDefined::iddObjectType(), pattern.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirTemperaturePatternUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirTemperaturePatternUserDefined pattern(model);

  // This class has no class-specific simple scalar fields; inherited ModelObject name scalar is roundtrip coverage.
  EXPECT_TRUE(pattern.setName("Room Air Pattern User Defined"));
  EXPECT_EQ("Room Air Pattern User Defined", pattern.nameString());
}
