/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfacePropertyHeatTransferAlgorithmMultipleSurface.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithmMultipleSurface_DefaultConstructor) {
  Model model;
  SurfacePropertyHeatTransferAlgorithmMultipleSurface heatTransferAlgorithmMultipleSurface(model);
  EXPECT_EQ(SurfacePropertyHeatTransferAlgorithmMultipleSurface::iddObjectType(), heatTransferAlgorithmMultipleSurface.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithmMultipleSurface_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyHeatTransferAlgorithmMultipleSurface heatTransferAlgorithmMultipleSurface(model);

  EXPECT_TRUE(heatTransferAlgorithmMultipleSurface.setSurfaceType("AllExteriorFloors"));
  EXPECT_EQ("AllExteriorFloors", heatTransferAlgorithmMultipleSurface.surfaceType());

  EXPECT_TRUE(heatTransferAlgorithmMultipleSurface.isAlgorithmDefaulted());
  EXPECT_TRUE(heatTransferAlgorithmMultipleSurface.setAlgorithm("CombinedHeatAndMoistureFiniteElement"));
  EXPECT_EQ("CombinedHeatAndMoistureFiniteElement", heatTransferAlgorithmMultipleSurface.algorithm());
  EXPECT_FALSE(heatTransferAlgorithmMultipleSurface.isAlgorithmDefaulted());
  heatTransferAlgorithmMultipleSurface.resetAlgorithm();
  EXPECT_TRUE(heatTransferAlgorithmMultipleSurface.isAlgorithmDefaulted());
}
