/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertySurroundingSurfaces.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertySurroundingSurfaces_DefaultConstructor) {
  Model model;
  SurfacePropertySurroundingSurfaces surfacePropertySurroundingSurfaces(model);
  EXPECT_EQ(SurfacePropertySurroundingSurfaces::iddObjectType(), surfacePropertySurroundingSurfaces.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertySurroundingSurfaces_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertySurroundingSurfaces surfacePropertySurroundingSurfaces(model);

  EXPECT_TRUE(surfacePropertySurroundingSurfaces.setSkyViewFactor(0.5));
  ASSERT_TRUE(surfacePropertySurroundingSurfaces.skyViewFactor());
  EXPECT_DOUBLE_EQ(0.5, surfacePropertySurroundingSurfaces.skyViewFactor().get());
  EXPECT_FALSE(surfacePropertySurroundingSurfaces.isSkyViewFactorAutocalculated());

  surfacePropertySurroundingSurfaces.autocalculateSkyViewFactor();
  EXPECT_TRUE(surfacePropertySurroundingSurfaces.isSkyViewFactorAutocalculated());

  EXPECT_TRUE(surfacePropertySurroundingSurfaces.setGroundViewFactor(0.37));
  ASSERT_TRUE(surfacePropertySurroundingSurfaces.groundViewFactor());
  EXPECT_DOUBLE_EQ(0.37, surfacePropertySurroundingSurfaces.groundViewFactor().get());
  EXPECT_FALSE(surfacePropertySurroundingSurfaces.isGroundViewFactorAutocalculated());

  surfacePropertySurroundingSurfaces.autocalculateGroundViewFactor();
  EXPECT_TRUE(surfacePropertySurroundingSurfaces.isGroundViewFactorAutocalculated());
}
