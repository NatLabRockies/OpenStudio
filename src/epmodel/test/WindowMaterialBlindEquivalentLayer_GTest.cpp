/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowMaterialBlindEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialBlindEquivalentLayer_DefaultConstructor) {
  Model model;
  WindowMaterialBlindEquivalentLayer blind(model);
  EXPECT_EQ(WindowMaterialBlindEquivalentLayer::iddObjectType(), blind.iddObject().type());
  EXPECT_DOUBLE_EQ(0.01, blind.slatWidth());
  EXPECT_DOUBLE_EQ(0.02, blind.slatSeparation());
  EXPECT_EQ("Horizontal", blind.slatOrientation());
}

TEST_F(EPModelFixture, WindowMaterialBlindEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialBlindEquivalentLayer blind(model);

  EXPECT_TRUE(blind.setSlatOrientation("Vertical"));
  EXPECT_TRUE(blind.setFrontSideSlatBeamDiffuseVisibleReflectance(0.3));
  EXPECT_TRUE(blind.setSlatDiffuseDiffuseVisibleTransmittance(0.4));
  EXPECT_TRUE(blind.setSlatAngleControl("BlockBeamSolar"));

  EXPECT_EQ("Vertical", blind.slatOrientation());
  ASSERT_TRUE(blind.frontSideSlatBeamDiffuseVisibleReflectance());
  EXPECT_DOUBLE_EQ(0.3, blind.frontSideSlatBeamDiffuseVisibleReflectance().get());
  ASSERT_TRUE(blind.slatDiffuseDiffuseVisibleTransmittance());
  EXPECT_DOUBLE_EQ(0.4, blind.slatDiffuseDiffuseVisibleTransmittance().get());
  EXPECT_EQ("BlockBeamSolar", blind.slatAngleControl());

  blind.resetFrontSideSlatBeamDiffuseVisibleReflectance();
  EXPECT_FALSE(blind.frontSideSlatBeamDiffuseVisibleReflectance());
  blind.resetSlatDiffuseDiffuseVisibleTransmittance();
  EXPECT_FALSE(blind.slatDiffuseDiffuseVisibleTransmittance());
  blind.resetSlatOrientation();
  EXPECT_TRUE(blind.isSlatOrientationDefaulted());
  blind.resetSlatAngleControl();
  EXPECT_TRUE(blind.isSlatAngleControlDefaulted());
}
