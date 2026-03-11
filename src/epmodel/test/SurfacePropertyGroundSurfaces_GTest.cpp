/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyGroundSurfaces.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyGroundSurfaces_DefaultConstructor) {
  Model model;
  SurfacePropertyGroundSurfaces surfacePropertyGroundSurfaces(model);
  EXPECT_EQ(SurfacePropertyGroundSurfaces::iddObjectType(), surfacePropertyGroundSurfaces.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyGroundSurfaces_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyGroundSurfaces surfacePropertyGroundSurfaces(model);

  EXPECT_TRUE(surfacePropertyGroundSurfaces.setName("Ground Surface Group"));
  EXPECT_EQ("Ground Surface Group", surfacePropertyGroundSurfaces.nameString());
}
