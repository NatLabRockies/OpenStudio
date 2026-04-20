/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowMaterialComplexShade.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialComplexShade_DefaultConstructor) {
  Model model;
  WindowMaterialComplexShade shade(model);
  EXPECT_EQ(WindowMaterialComplexShade::iddObjectType(), shade.iddObject().type());
  EXPECT_EQ("OtherShadingType", shade.layerType());
  EXPECT_DOUBLE_EQ(0.002, shade.thickness());
  EXPECT_DOUBLE_EQ(0.05, shade.frontOpeningMultiplier());
}

TEST_F(EPModelFixture, WindowMaterialComplexShade_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialComplexShade shade(model);

  EXPECT_TRUE(shade.setLayerType("Perforated"));
  EXPECT_TRUE(shade.setTopOpeningMultiplier(0.25));
  EXPECT_TRUE(shade.setSlatCurve(0.007));

  EXPECT_EQ("Perforated", shade.layerType());
  EXPECT_DOUBLE_EQ(0.25, shade.topOpeningMultiplier());
  EXPECT_DOUBLE_EQ(0.007, shade.slatCurve());
  EXPECT_FALSE(shade.isLayerTypeDefaulted());
  EXPECT_FALSE(shade.isTopOpeningMultiplierDefaulted());
  EXPECT_FALSE(shade.isSlatCurveDefaulted());

  shade.resetTopOpeningMultiplier();
  EXPECT_TRUE(shade.isTopOpeningMultiplierDefaulted());
  shade.resetLayerType();
  EXPECT_TRUE(shade.isLayerTypeDefaulted());
  shade.resetSlatCurve();
  EXPECT_TRUE(shade.isSlatCurveDefaulted());
}
