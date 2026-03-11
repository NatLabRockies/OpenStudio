/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneEarthtubeParameters.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneEarthtubeParameters_DefaultConstructor) {
  Model model;
  ZoneEarthtubeParameters parameters(model);
  EXPECT_EQ(ZoneEarthtubeParameters::iddObjectType(), parameters.iddObject().type());
}

TEST_F(EPModelFixture, ZoneEarthtubeParameters_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneEarthtubeParameters parameters(model);

  EXPECT_TRUE(parameters.isNodesAboveEarthTubeDefaulted());
  EXPECT_TRUE(parameters.setNodesAboveEarthTube(7));
  EXPECT_EQ(7, parameters.nodesAboveEarthTube());
  EXPECT_FALSE(parameters.isNodesAboveEarthTubeDefaulted());
  parameters.resetNodesAboveEarthTube();
  EXPECT_TRUE(parameters.isNodesAboveEarthTubeDefaulted());
  EXPECT_EQ(5, parameters.nodesAboveEarthTube());

  EXPECT_TRUE(parameters.isNodesBelowEarthTubeDefaulted());
  EXPECT_TRUE(parameters.setNodesBelowEarthTube(4));
  EXPECT_EQ(4, parameters.nodesBelowEarthTube());
  EXPECT_FALSE(parameters.isNodesBelowEarthTubeDefaulted());
  parameters.resetNodesBelowEarthTube();
  EXPECT_TRUE(parameters.isNodesBelowEarthTubeDefaulted());
  EXPECT_EQ(3, parameters.nodesBelowEarthTube());

  EXPECT_TRUE(parameters.isEarthTubeDimensionlessBoundaryAboveDefaulted());
  EXPECT_TRUE(parameters.setEarthTubeDimensionlessBoundaryAbove(0.8));
  EXPECT_DOUBLE_EQ(0.8, parameters.earthTubeDimensionlessBoundaryAbove());
  EXPECT_FALSE(parameters.isEarthTubeDimensionlessBoundaryAboveDefaulted());
  parameters.resetEarthTubeDimensionlessBoundaryAbove();
  EXPECT_TRUE(parameters.isEarthTubeDimensionlessBoundaryAboveDefaulted());
  EXPECT_DOUBLE_EQ(1.0, parameters.earthTubeDimensionlessBoundaryAbove());

  EXPECT_TRUE(parameters.isEarthTubeDimensionlessBoundaryBelowDefaulted());
  EXPECT_TRUE(parameters.setEarthTubeDimensionlessBoundaryBelow(0.3));
  EXPECT_DOUBLE_EQ(0.3, parameters.earthTubeDimensionlessBoundaryBelow());
  EXPECT_FALSE(parameters.isEarthTubeDimensionlessBoundaryBelowDefaulted());
  parameters.resetEarthTubeDimensionlessBoundaryBelow();
  EXPECT_TRUE(parameters.isEarthTubeDimensionlessBoundaryBelowDefaulted());
  EXPECT_DOUBLE_EQ(0.25, parameters.earthTubeDimensionlessBoundaryBelow());

  EXPECT_TRUE(parameters.isEarthTubeSolutionSpaceWidthDefaulted());
  EXPECT_TRUE(parameters.setEarthTubeSolutionSpaceWidth(5.5));
  EXPECT_DOUBLE_EQ(5.5, parameters.earthTubeSolutionSpaceWidth());
  EXPECT_FALSE(parameters.isEarthTubeSolutionSpaceWidthDefaulted());
  parameters.resetEarthTubeSolutionSpaceWidth();
  EXPECT_TRUE(parameters.isEarthTubeSolutionSpaceWidthDefaulted());
  EXPECT_DOUBLE_EQ(4.0, parameters.earthTubeSolutionSpaceWidth());
}
