/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyUnderwater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyUnderwater_DefaultConstructor) {
  Model model;
  SurfacePropertyUnderwater underwater(model);
  EXPECT_EQ(SurfacePropertyUnderwater::iddObjectType(), underwater.iddObject().type());
  EXPECT_DOUBLE_EQ(0.5, underwater.distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer());
}

TEST_F(EPModelFixture, SurfacePropertyUnderwater_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyUnderwater underwater(model);

  EXPECT_TRUE(underwater.setDistanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer(0.25));
  EXPECT_DOUBLE_EQ(0.25, underwater.distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer());
}
