/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoad/SpaceInfiltrationEffectiveLeakageArea.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceInfiltrationEffectiveLeakageArea_DefaultConstructor) {
  Model model;
  SpaceInfiltrationEffectiveLeakageArea infiltration(model);

  EXPECT_EQ(SpaceInfiltrationEffectiveLeakageArea::iddObjectType(), infiltration.iddObject().type());
  EXPECT_DOUBLE_EQ(0.1, infiltration.effectiveAirLeakageArea());
  EXPECT_DOUBLE_EQ(0.1, infiltration.stackCoefficient());
  EXPECT_DOUBLE_EQ(0.1, infiltration.windCoefficient());
}

TEST_F(EPModelFixture, SpaceInfiltrationEffectiveLeakageArea_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceInfiltrationEffectiveLeakageArea infiltration(model);

  EXPECT_TRUE(infiltration.setEffectiveAirLeakageArea(0.25));
  EXPECT_DOUBLE_EQ(0.25, infiltration.effectiveAirLeakageArea());

  EXPECT_TRUE(infiltration.setStackCoefficient(0.35));
  EXPECT_DOUBLE_EQ(0.35, infiltration.stackCoefficient());

  EXPECT_TRUE(infiltration.setWindCoefficient(0.45));
  EXPECT_DOUBLE_EQ(0.45, infiltration.windCoefficient());
}
