/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ShadingMaterial/Blind.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Blind_DefaultConstructor) {
  Model model;
  Blind blind(model);
  EXPECT_EQ(Blind::iddObjectType(), blind.iddObject().type());
  EXPECT_FALSE(blind.nameString().empty());
}

TEST_F(EPModelFixture, Blind_ScalarAccessors_RoundTrip) {
  Model model;
  Blind blind(model);

  EXPECT_TRUE(blind.setSlatOrientation("Vertical"));
  EXPECT_EQ("Vertical", blind.slatOrientation());

  blind.resetSlatOrientation();
  EXPECT_TRUE(blind.isSlatOrientationDefaulted());
  EXPECT_EQ("Horizontal", blind.slatOrientation());

  EXPECT_TRUE(blind.setSlatWidth(0.05));
  EXPECT_DOUBLE_EQ(0.05, blind.slatWidth());

  EXPECT_TRUE(blind.isSlatCurveDefaulted());
  EXPECT_TRUE(blind.setSlatCurve(0.003));
  EXPECT_DOUBLE_EQ(0.003, blind.slatCurve());
  EXPECT_FALSE(blind.isSlatCurveDefaulted());
  blind.resetSlatCurve();
  EXPECT_TRUE(blind.isSlatCurveDefaulted());

  EXPECT_TRUE(blind.setFrontSideSlatBeamVisibleReflectance(0.6));
  ASSERT_TRUE(blind.frontSideSlatBeamVisibleReflectance());
  EXPECT_DOUBLE_EQ(0.6, blind.frontSideSlatBeamVisibleReflectance().get());

  blind.resetFrontSideSlatBeamVisibleReflectance();
  EXPECT_FALSE(blind.frontSideSlatBeamVisibleReflectance());

  EXPECT_TRUE(blind.setMinimumSlatAngle(10.0));
  EXPECT_DOUBLE_EQ(10.0, blind.minimumSlatAngle());
}
