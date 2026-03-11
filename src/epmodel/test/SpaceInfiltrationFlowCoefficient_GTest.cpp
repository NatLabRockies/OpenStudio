/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoad/SpaceInfiltrationFlowCoefficient.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceInfiltrationFlowCoefficient_DefaultConstructor) {
  Model model;
  SpaceInfiltrationFlowCoefficient infiltration(model);

  EXPECT_EQ(SpaceInfiltrationFlowCoefficient::iddObjectType(), infiltration.iddObject().type());
  EXPECT_DOUBLE_EQ(0.2, infiltration.flowCoefficient());
  EXPECT_DOUBLE_EQ(0.2, infiltration.stackCoefficient());
  EXPECT_DOUBLE_EQ(0.67, infiltration.pressureExponent());
  EXPECT_FALSE(infiltration.isPressureExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.4, infiltration.windCoefficient());
  EXPECT_DOUBLE_EQ(1.0, infiltration.shelterFactor());
}

TEST_F(EPModelFixture, SpaceInfiltrationFlowCoefficient_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceInfiltrationFlowCoefficient infiltration(model);

  EXPECT_TRUE(infiltration.setFlowCoefficient(0.5));
  EXPECT_DOUBLE_EQ(0.5, infiltration.flowCoefficient());

  EXPECT_TRUE(infiltration.setStackCoefficient(0.7));
  EXPECT_DOUBLE_EQ(0.7, infiltration.stackCoefficient());

  EXPECT_TRUE(infiltration.setPressureExponent(0.9));
  EXPECT_DOUBLE_EQ(0.9, infiltration.pressureExponent());
  infiltration.resetPressureExponent();
  EXPECT_TRUE(infiltration.isPressureExponentDefaulted());

  EXPECT_TRUE(infiltration.setWindCoefficient(2.4));
  EXPECT_DOUBLE_EQ(2.4, infiltration.windCoefficient());

  EXPECT_TRUE(infiltration.setShelterFactor(1.3));
  EXPECT_DOUBLE_EQ(1.3, infiltration.shelterFactor());
}
