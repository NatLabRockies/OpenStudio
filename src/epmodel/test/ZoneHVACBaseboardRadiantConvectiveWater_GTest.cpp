/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);
  (void)baseboard;
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveWater baseboard(model);

  EXPECT_TRUE(baseboard.setRatedAverageWaterTemperature(70.0));
  ASSERT_TRUE(baseboard.ratedAverageWaterTemperature());
  EXPECT_DOUBLE_EQ(70.0, baseboard.ratedAverageWaterTemperature().get());
  EXPECT_TRUE(baseboard.setRatedWaterMassFlowRate(0.15));
  ASSERT_TRUE(baseboard.ratedWaterMassFlowRate());
  EXPECT_DOUBLE_EQ(0.15, baseboard.ratedWaterMassFlowRate().get());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(2500.0));
  ASSERT_TRUE(baseboard.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(2500.0, baseboard.heatingDesignCapacity().get());
  baseboard.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());

  EXPECT_TRUE(baseboard.setMaximumWaterFlowRate(0.12));
  ASSERT_TRUE(baseboard.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, baseboard.maximumWaterFlowRate().get());
  baseboard.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateAutosized());
}
