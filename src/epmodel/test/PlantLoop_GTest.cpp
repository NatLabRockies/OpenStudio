/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantLoop_DefaultConstructor) {
  Model model;
  PlantLoop plantLoop(model);
  EXPECT_EQ(PlantLoop::iddObjectType(), plantLoop.iddObject().type());
}

TEST_F(EPModelFixture, PlantLoop_ScalarAccessors_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);

  EXPECT_TRUE(plantLoop.setName("Main Plant Loop"));
  EXPECT_EQ("Main Plant Loop", plantLoop.nameString());

  EXPECT_TRUE(plantLoop.setMaximumLoopTemperature(108.5));
  EXPECT_DOUBLE_EQ(108.5, plantLoop.maximumLoopTemperature());

  EXPECT_TRUE(plantLoop.setMinimumLoopTemperature(30.25));
  EXPECT_DOUBLE_EQ(30.25, plantLoop.minimumLoopTemperature());

  EXPECT_TRUE(plantLoop.setPlantLoopVolume(0.45));
  ASSERT_TRUE(plantLoop.plantLoopVolume());
  EXPECT_DOUBLE_EQ(0.45, plantLoop.plantLoopVolume().get());

  plantLoop.autocalculatePlantLoopVolume();
  EXPECT_TRUE(plantLoop.isPlantLoopVolumeAutocalculated());

  EXPECT_TRUE(plantLoop.setCommonPipeSimulation("CommonPipe"));
  EXPECT_EQ("CommonPipe", plantLoop.commonPipeSimulation());
  EXPECT_FALSE(plantLoop.isCommonPipeSimulationDefaulted());
  plantLoop.resetCommonPipeSimulation();
  EXPECT_TRUE(plantLoop.isCommonPipeSimulationDefaulted());
}
