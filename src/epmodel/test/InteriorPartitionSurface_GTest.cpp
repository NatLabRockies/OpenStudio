/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlanarSurface/InteriorPartitionSurface.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, InteriorPartitionSurface_DefaultConstructor) {
  Model model;
  InteriorPartitionSurface interiorPartitionSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);
  EXPECT_EQ(InteriorPartitionSurface::iddObjectType(), interiorPartitionSurface.iddObject().type());
  EXPECT_FALSE(interiorPartitionSurface.nameString().empty());
}

TEST_F(EPModelFixture, InteriorPartitionSurface_ScalarAccessors_RoundTrip) {
  Model model;
  InteriorPartitionSurface interiorPartitionSurface({{0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}}, model);

  EXPECT_TRUE(interiorPartitionSurface.converttoInternalMass());
  EXPECT_TRUE(interiorPartitionSurface.isConverttoInternalMassDefaulted());
  EXPECT_FALSE(interiorPartitionSurface.setConverttoInternalMass(false));
  EXPECT_TRUE(interiorPartitionSurface.setConverttoInternalMass(true));
  interiorPartitionSurface.resetConverttoInternalMass();
  EXPECT_TRUE(interiorPartitionSurface.converttoInternalMass());

  EXPECT_FALSE(interiorPartitionSurface.surfaceArea());
  EXPECT_TRUE(interiorPartitionSurface.setSurfaceArea(6.5));
  ASSERT_TRUE(interiorPartitionSurface.surfaceArea());
  EXPECT_DOUBLE_EQ(6.5, *interiorPartitionSurface.surfaceArea());
  EXPECT_TRUE(interiorPartitionSurface.setSurfaceArea(boost::optional<double>{}));
  EXPECT_FALSE(interiorPartitionSurface.surfaceArea());
  interiorPartitionSurface.resetSurfaceArea();
  EXPECT_FALSE(interiorPartitionSurface.surfaceArea());

  EXPECT_FALSE(interiorPartitionSurface.numberofVertices());
  EXPECT_TRUE(interiorPartitionSurface.isNumberofVerticesDefaulted());
  EXPECT_FALSE(interiorPartitionSurface.isNumberofVerticesAutocalculated());
  EXPECT_FALSE(interiorPartitionSurface.setNumberofVertices(4.0));
  EXPECT_TRUE(interiorPartitionSurface.setNumberofVertices(boost::optional<double>{}));
  interiorPartitionSurface.autocalculateNumberofVertices();
  interiorPartitionSurface.resetNumberofVertices();
}
