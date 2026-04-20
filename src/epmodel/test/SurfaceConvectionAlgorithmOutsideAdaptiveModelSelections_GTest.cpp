/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_DefaultConstructor) {
  Model model;
  SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections obj(model);
  EXPECT_EQ(SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections obj(model);

  // All 6 choice fields have defaults, so they should start as defaulted
  EXPECT_TRUE(obj.isWindConvectionWindwardVerticalWallEquationSourceDefaulted());
  EXPECT_FALSE(obj.windConvectionWindwardVerticalWallEquationSource().empty());

  // Test set / get / isDefaulted / reset cycle on Wind Convection Windward
  EXPECT_TRUE(obj.setWindConvectionWindwardVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.windConvectionWindwardVerticalWallEquationSource());
  EXPECT_FALSE(obj.isWindConvectionWindwardVerticalWallEquationSourceDefaulted());
  obj.resetWindConvectionWindwardVerticalWallEquationSource();
  EXPECT_TRUE(obj.isWindConvectionWindwardVerticalWallEquationSourceDefaulted());

  // Test Wind Convection Leeward
  EXPECT_TRUE(obj.isWindConvectionLeewardVerticalWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setWindConvectionLeewardVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.windConvectionLeewardVerticalWallEquationSource());
  obj.resetWindConvectionLeewardVerticalWallEquationSource();
  EXPECT_TRUE(obj.isWindConvectionLeewardVerticalWallEquationSourceDefaulted());

  // Test Wind Convection Horizontal Roof
  EXPECT_TRUE(obj.isWindConvectionHorizontalRoofEquationSourceDefaulted());
  EXPECT_TRUE(obj.setWindConvectionHorizontalRoofEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.windConvectionHorizontalRoofEquationSource());
  obj.resetWindConvectionHorizontalRoofEquationSource();
  EXPECT_TRUE(obj.isWindConvectionHorizontalRoofEquationSourceDefaulted());

  // Test Natural Convection Vertical Wall
  EXPECT_TRUE(obj.isNaturalConvectionVerticalWallEquationSourceDefaulted());
  EXPECT_TRUE(obj.setNaturalConvectionVerticalWallEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.naturalConvectionVerticalWallEquationSource());
  obj.resetNaturalConvectionVerticalWallEquationSource();
  EXPECT_TRUE(obj.isNaturalConvectionVerticalWallEquationSourceDefaulted());

  // Test Natural Convection Stable Horizontal
  EXPECT_TRUE(obj.isNaturalConvectionStableHorizontalEquationSourceDefaulted());
  EXPECT_TRUE(obj.setNaturalConvectionStableHorizontalEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.naturalConvectionStableHorizontalEquationSource());
  obj.resetNaturalConvectionStableHorizontalEquationSource();
  EXPECT_TRUE(obj.isNaturalConvectionStableHorizontalEquationSourceDefaulted());

  // Test Natural Convection Unstable Horizontal
  EXPECT_TRUE(obj.isNaturalConvectionUnstableHorizontalEquationSourceDefaulted());
  EXPECT_TRUE(obj.setNaturalConvectionUnstableHorizontalEquationSource("UserCurve"));
  EXPECT_EQ("UserCurve", obj.naturalConvectionUnstableHorizontalEquationSource());
  obj.resetNaturalConvectionUnstableHorizontalEquationSource();
  EXPECT_TRUE(obj.isNaturalConvectionUnstableHorizontalEquationSourceDefaulted());

  // Test invalid choice is rejected
  EXPECT_FALSE(obj.setWindConvectionWindwardVerticalWallEquationSource("InvalidChoice"));

  // Test Values helper returns non-empty
  auto values = SurfaceConvectionAlgorithmOutsideAdaptiveModelSelections::windConvectionWindwardVerticalWallEquationSourceValues();
  EXPECT_FALSE(values.empty());
}
