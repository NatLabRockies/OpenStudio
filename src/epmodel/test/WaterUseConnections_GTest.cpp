/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/WaterUseConnections.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterUseConnections_DefaultConstructor) {
  Model model;
  WaterUseConnections connections(model);
  EXPECT_EQ("None", connections.drainWaterHeatExchangerType());
  EXPECT_EQ("Plant", connections.drainWaterHeatExchangerDestination());
}

TEST_F(EPModelFixture, WaterUseConnections_ScalarAccessors_RoundTrip) {
  Model model;
  WaterUseConnections connections(model);

  EXPECT_TRUE(connections.setDrainWaterHeatExchangerType("CounterFlow"));
  EXPECT_EQ("CounterFlow", connections.drainWaterHeatExchangerType());

  EXPECT_TRUE(connections.setDrainWaterHeatExchangerDestination("Equipment"));
  EXPECT_EQ("Equipment", connections.drainWaterHeatExchangerDestination());

  EXPECT_TRUE(connections.setDrainWaterHeatExchangerUFactorTimesArea(123.0));
  ASSERT_TRUE(connections.drainWaterHeatExchangerUFactorTimesArea());
  EXPECT_DOUBLE_EQ(123.0, connections.drainWaterHeatExchangerUFactorTimesArea().get());
  connections.resetDrainWaterHeatExchangerUFactorTimesArea();
  EXPECT_FALSE(connections.drainWaterHeatExchangerUFactorTimesArea());
}
