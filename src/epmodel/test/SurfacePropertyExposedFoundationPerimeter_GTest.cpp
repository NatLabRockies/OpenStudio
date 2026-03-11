/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyExposedFoundationPerimeter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyExposedFoundationPerimeter_DefaultConstructor) {
  Model model;
  SurfacePropertyExposedFoundationPerimeter sp(model);
  EXPECT_EQ(SurfacePropertyExposedFoundationPerimeter::iddObjectType(), sp.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyExposedFoundationPerimeter_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyExposedFoundationPerimeter sp(model);

  // exposedPerimeterCalculationMethod - required choice, no default in IDD
  EXPECT_TRUE(sp.setExposedPerimeterCalculationMethod("TotalExposedPerimeter"));
  EXPECT_EQ("TotalExposedPerimeter", sp.exposedPerimeterCalculationMethod());
  EXPECT_TRUE(sp.setExposedPerimeterCalculationMethod("ExposedPerimeterFraction"));
  EXPECT_EQ("ExposedPerimeterFraction", sp.exposedPerimeterCalculationMethod());
  EXPECT_TRUE(sp.setExposedPerimeterCalculationMethod("BySegment"));
  EXPECT_EQ("BySegment", sp.exposedPerimeterCalculationMethod());
  // Invalid choice should fail
  EXPECT_FALSE(sp.setExposedPerimeterCalculationMethod("InvalidChoice"));

  // totalExposedPerimeter - optional real, min 0
  EXPECT_FALSE(sp.totalExposedPerimeter());
  EXPECT_TRUE(sp.setTotalExposedPerimeter(12.5));
  ASSERT_TRUE(sp.totalExposedPerimeter());
  EXPECT_DOUBLE_EQ(12.5, sp.totalExposedPerimeter().get());
  // Negative should fail (min 0)
  EXPECT_FALSE(sp.setTotalExposedPerimeter(-1.0));

  // exposedPerimeterFraction - default 1.0, min 0, max 1
  EXPECT_TRUE(sp.isExposedPerimeterFractionDefaulted());
  EXPECT_DOUBLE_EQ(1.0, sp.exposedPerimeterFraction());
  EXPECT_TRUE(sp.setExposedPerimeterFraction(0.75));
  EXPECT_FALSE(sp.isExposedPerimeterFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.75, sp.exposedPerimeterFraction());
  // Out of range should fail
  EXPECT_FALSE(sp.setExposedPerimeterFraction(1.5));
  EXPECT_FALSE(sp.setExposedPerimeterFraction(-0.1));
  // Reset restores default
  sp.resetExposedPerimeterFraction();
  EXPECT_TRUE(sp.isExposedPerimeterFractionDefaulted());
  EXPECT_DOUBLE_EQ(1.0, sp.exposedPerimeterFraction());
}

TEST_F(EPModelFixture, SurfacePropertyExposedFoundationPerimeter_ChoiceValues) {
  auto methodValues = SurfacePropertyExposedFoundationPerimeter::exposedPerimeterCalculationMethodValues();
  EXPECT_FALSE(methodValues.empty());
  EXPECT_EQ(3u, methodValues.size());
}
