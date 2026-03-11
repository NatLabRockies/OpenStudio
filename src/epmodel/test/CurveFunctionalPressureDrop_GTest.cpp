/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveFunctionalPressureDrop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CurveFunctionalPressureDrop_DefaultConstructor) {
  Model model;
  CurveFunctionalPressureDrop curve(model);
  EXPECT_EQ(CurveFunctionalPressureDrop::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(0.05, curve.diameter());
  EXPECT_FALSE(curve.minorLossCoefficient());
  EXPECT_FALSE(curve.length());
  EXPECT_FALSE(curve.roughness());
  EXPECT_FALSE(curve.fixedFrictionFactor());
}

TEST_F(EPModelFixture, CurveFunctionalPressureDrop_ScalarAccessors_RoundTrip) {
  Model model;
  CurveFunctionalPressureDrop curve(model);

  EXPECT_TRUE(curve.setDiameter(0.08));
  EXPECT_DOUBLE_EQ(0.08, curve.diameter());

  EXPECT_TRUE(curve.setMinorLossCoefficient(0.7));
  ASSERT_TRUE(curve.minorLossCoefficient());
  EXPECT_DOUBLE_EQ(0.7, *curve.minorLossCoefficient());
  curve.resetMinorLossCoefficient();
  EXPECT_FALSE(curve.minorLossCoefficient());

  EXPECT_TRUE(curve.setLength(7.2));
  ASSERT_TRUE(curve.length());
  EXPECT_DOUBLE_EQ(7.2, *curve.length());
  curve.resetLength();
  EXPECT_FALSE(curve.length());

  EXPECT_TRUE(curve.setRoughness(2.3e-4));
  ASSERT_TRUE(curve.roughness());
  EXPECT_DOUBLE_EQ(2.3e-4, *curve.roughness());
  curve.resetRoughness();
  EXPECT_FALSE(curve.roughness());

  EXPECT_TRUE(curve.setFixedFrictionFactor(0.03));
  ASSERT_TRUE(curve.fixedFrictionFactor());
  EXPECT_DOUBLE_EQ(0.03, *curve.fixedFrictionFactor());
  curve.resetFixedFrictionFactor();
  EXPECT_FALSE(curve.fixedFrictionFactor());
}
