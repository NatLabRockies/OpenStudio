/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Glazing/SimpleGlazing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SimpleGlazing_DefaultConstructor) {
  Model model;
  SimpleGlazing glazing(model);

  EXPECT_EQ(SimpleGlazing::iddObjectType(), glazing.iddObject().type());
  EXPECT_DOUBLE_EQ(0.1, glazing.uFactor());
  EXPECT_DOUBLE_EQ(0.1, glazing.solarHeatGainCoefficient());
  EXPECT_FALSE(glazing.visibleTransmittance());
}

TEST_F(EPModelFixture, SimpleGlazing_ScalarAccessors_RoundTrip) {
  Model model;
  SimpleGlazing glazing(model);

  EXPECT_TRUE(glazing.setUFactor(0.22));
  EXPECT_DOUBLE_EQ(0.22, glazing.uFactor());

  EXPECT_TRUE(glazing.setSolarHeatGainCoefficient(0.32));
  EXPECT_DOUBLE_EQ(0.32, glazing.solarHeatGainCoefficient());

  EXPECT_TRUE(glazing.setVisibleTransmittance(0.45));
  ASSERT_TRUE(glazing.visibleTransmittance());
  EXPECT_DOUBLE_EQ(0.45, glazing.visibleTransmittance().get());

  glazing.resetVisibleTransmittance();
  EXPECT_FALSE(glazing.visibleTransmittance());

  EXPECT_TRUE(glazing.setVisibleTransmittance(0.78));
  ASSERT_TRUE(glazing.visibleTransmittance());
  EXPECT_DOUBLE_EQ(0.78, glazing.visibleTransmittance().get());
}
