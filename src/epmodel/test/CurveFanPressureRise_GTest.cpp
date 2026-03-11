/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveFanPressureRise.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CurveFanPressureRise_DefaultConstructor) {
  Model model;
  CurveFanPressureRise curve(model);
  EXPECT_EQ(CurveFanPressureRise::iddObjectType(), curve.iddObject().type());

  EXPECT_DOUBLE_EQ(1.0, curve.coefficient1C1());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient2C2());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient3C3());
  EXPECT_DOUBLE_EQ(1.0, curve.coefficient4C4());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofQfan());
  EXPECT_DOUBLE_EQ(10.0, curve.maximumValueofQfan());
  EXPECT_DOUBLE_EQ(0.0, curve.minimumValueofPsm());
  EXPECT_DOUBLE_EQ(500.0, curve.maximumValueofPsm());
  EXPECT_FALSE(curve.minimumCurveOutput());
  EXPECT_FALSE(curve.maximumCurveOutput());
}

TEST_F(EPModelFixture, CurveFanPressureRise_ScalarAccessors_RoundTrip) {
  Model model;
  CurveFanPressureRise curve(model);

  EXPECT_TRUE(curve.setCoefficient1C1(1.1));
  EXPECT_TRUE(curve.setCoefficient2C2(2.2));
  EXPECT_TRUE(curve.setCoefficient3C3(3.3));
  EXPECT_TRUE(curve.setCoefficient4C4(4.4));
  EXPECT_TRUE(curve.setMinimumValueofQfan(5.5));
  EXPECT_TRUE(curve.setMaximumValueofQfan(6.6));
  EXPECT_TRUE(curve.setMinimumValueofPsm(7.7));
  EXPECT_TRUE(curve.setMaximumValueofPsm(8.8));

  EXPECT_DOUBLE_EQ(1.1, curve.coefficient1C1());
  EXPECT_DOUBLE_EQ(2.2, curve.coefficient2C2());
  EXPECT_DOUBLE_EQ(3.3, curve.coefficient3C3());
  EXPECT_DOUBLE_EQ(4.4, curve.coefficient4C4());
  EXPECT_DOUBLE_EQ(5.5, curve.minimumValueofQfan());
  EXPECT_DOUBLE_EQ(6.6, curve.maximumValueofQfan());
  EXPECT_DOUBLE_EQ(7.7, curve.minimumValueofPsm());
  EXPECT_DOUBLE_EQ(8.8, curve.maximumValueofPsm());

  EXPECT_TRUE(curve.setMinimumCurveOutput(-1.0));
  ASSERT_TRUE(curve.minimumCurveOutput());
  EXPECT_DOUBLE_EQ(-1.0, *curve.minimumCurveOutput());
  curve.resetMinimumCurveOutput();
  EXPECT_FALSE(curve.minimumCurveOutput());

  EXPECT_TRUE(curve.setMaximumCurveOutput(1.0));
  ASSERT_TRUE(curve.maximumCurveOutput());
  EXPECT_DOUBLE_EQ(1.0, *curve.maximumCurveOutput());
  curve.resetMaximumCurveOutput();
  EXPECT_FALSE(curve.maximumCurveOutput());
}
