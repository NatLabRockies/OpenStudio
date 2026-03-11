/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlanarSurface/Surface.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Surface_DefaultConstructor) {
  Model model;
  Surface surface(model);
  EXPECT_EQ(Surface::iddObjectType(), surface.iddObject().type());
  EXPECT_FALSE(surface.nameString().empty());
}

TEST_F(EPModelFixture, Surface_ScalarAccessors_RoundTrip) {
  Model model;
  Surface surface(model);

  EXPECT_TRUE(surface.setSurfaceType("Wall"));
  EXPECT_EQ("Wall", surface.surfaceType());

  EXPECT_TRUE(surface.setOutsideBoundaryCondition("Outdoors"));
  EXPECT_EQ("Outdoors", surface.outsideBoundaryCondition());

  EXPECT_TRUE(surface.setSunExposure("NoSun"));
  EXPECT_EQ("NoSun", surface.sunExposure());
  EXPECT_FALSE(surface.isSunExposureDefaulted());
  surface.resetSunExposure();
  EXPECT_TRUE(surface.isSunExposureDefaulted());

  EXPECT_TRUE(surface.setWindExposure("NoWind"));
  EXPECT_EQ("NoWind", surface.windExposure());
  EXPECT_FALSE(surface.isWindExposureDefaulted());
  surface.resetWindExposure();
  EXPECT_TRUE(surface.isWindExposureDefaulted());

  EXPECT_TRUE(surface.setViewFactortoGround(0.42));
  ASSERT_TRUE(surface.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.42, *surface.viewFactortoGround());
  EXPECT_FALSE(surface.isViewFactortoGroundAutocalculated());
  surface.autocalculateViewFactortoGround();
  EXPECT_TRUE(surface.isViewFactortoGroundAutocalculated());
  EXPECT_TRUE(surface.setViewFactortoGround(boost::optional<double>{}));
  EXPECT_TRUE(surface.isViewFactortoGroundDefaulted());

  EXPECT_TRUE(surface.setNumberofVertices(4.0));
  ASSERT_TRUE(surface.numberofVertices());
  EXPECT_DOUBLE_EQ(4.0, *surface.numberofVertices());
  EXPECT_FALSE(surface.isNumberofVerticesAutocalculated());
  surface.autocalculateNumberofVertices();
  EXPECT_TRUE(surface.isNumberofVerticesAutocalculated());
  EXPECT_TRUE(surface.setNumberofVertices(boost::optional<double>{}));
  EXPECT_TRUE(surface.isNumberofVerticesDefaulted());
}
