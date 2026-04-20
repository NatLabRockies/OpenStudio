/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfacePropertyHeatTransferAlgorithmSurfaceList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithmSurfaceList_DefaultConstructor) {
  Model model;
  SurfacePropertyHeatTransferAlgorithmSurfaceList surfaceList(model);
  EXPECT_EQ(SurfacePropertyHeatTransferAlgorithmSurfaceList::iddObjectType(), surfaceList.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithmSurfaceList_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyHeatTransferAlgorithmSurfaceList surfaceList(model);

  EXPECT_TRUE(surfaceList.isAlgorithmDefaulted());
  EXPECT_TRUE(surfaceList.setAlgorithm("MoisturePenetrationDepthConductionTransferFunction"));
  EXPECT_EQ("MoisturePenetrationDepthConductionTransferFunction", surfaceList.algorithm());
  surfaceList.resetAlgorithm();
  EXPECT_TRUE(surfaceList.isAlgorithmDefaulted());
}
