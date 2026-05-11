/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlanarSurface/SubSurface.hpp"

#include <utilities/geometry/Point3d.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SubSurface_DefaultConstructor) {
  Model model;

  SubSurface subSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);
  EXPECT_EQ(SubSurface::iddObjectType(), subSurface.iddObject().type());
  EXPECT_FALSE(subSurface.nameString().empty());
}

TEST_F(EPModelFixture, SubSurface_ScalarAccessors_RoundTrip) {
  Model model;
  SubSurface subSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);

  EXPECT_TRUE(subSurface.setSubSurfaceType("Window"));
  EXPECT_EQ("Window", subSurface.subSurfaceType());
  EXPECT_FALSE(subSurface.isSubSurfaceTypeDefaulted());
  subSurface.resetSubSurfaceType();
  EXPECT_TRUE(subSurface.isSubSurfaceTypeDefaulted());

  EXPECT_TRUE(subSurface.setViewFactortoGround(0.37));
  ASSERT_TRUE(subSurface.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.37, *subSurface.viewFactortoGround());
  EXPECT_FALSE(subSurface.isViewFactortoGroundAutocalculated());
  subSurface.autocalculateViewFactortoGround();
  EXPECT_TRUE(subSurface.isViewFactortoGroundAutocalculated());
  EXPECT_TRUE(subSurface.setViewFactortoGround(boost::optional<double>{}));
  EXPECT_TRUE(subSurface.isViewFactortoGroundDefaulted());

  EXPECT_TRUE(subSurface.setMultiplier(1.25));
  EXPECT_DOUBLE_EQ(1.25, subSurface.multiplier());
  EXPECT_FALSE(subSurface.isMultiplierDefaulted());
  subSurface.resetMultiplier();
  EXPECT_TRUE(subSurface.isMultiplierDefaulted());

  EXPECT_TRUE(subSurface.setNumberofVertices(4.0));
  ASSERT_TRUE(subSurface.numberofVertices());
  EXPECT_DOUBLE_EQ(4.0, *subSurface.numberofVertices());
  EXPECT_FALSE(subSurface.isNumberofVerticesAutocalculated());
  subSurface.autocalculateNumberofVertices();
  EXPECT_TRUE(subSurface.isNumberofVerticesAutocalculated());
  EXPECT_TRUE(subSurface.setNumberofVertices(boost::optional<double>{}));
  EXPECT_TRUE(subSurface.isNumberofVerticesDefaulted());
}
