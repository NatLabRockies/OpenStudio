/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  (void)baseboard;
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
  EXPECT_EQ("HeatingDesignCapacity", baseboard.heatingDesignCapacityMethod());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(1500.0));
  ASSERT_TRUE(baseboard.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1500.0, baseboard.heatingDesignCapacity().get());
  baseboard.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityPerFloorArea(0.6));
  EXPECT_DOUBLE_EQ(0.6, baseboard.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(baseboard.setFractionofAutosizedHeatingDesignCapacity(0.4));
  EXPECT_DOUBLE_EQ(0.4, baseboard.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(baseboard.setUFactorTimesAreaValue(2.1));
  ASSERT_TRUE(baseboard.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2.1, baseboard.uFactorTimesAreaValue().get());
  baseboard.resetUFactorTimesAreaValue();
  EXPECT_TRUE(baseboard.isUFactorTimesAreaValueDefaulted());
  EXPECT_FALSE(baseboard.uFactorTimesAreaValue());

  EXPECT_TRUE(baseboard.setMaximumWaterFlowRate(0.012));
  ASSERT_TRUE(baseboard.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, baseboard.maximumWaterFlowRate().get());
  baseboard.resetMaximumWaterFlowRate();
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateDefaulted());
  EXPECT_FALSE(baseboard.maximumWaterFlowRate());
  baseboard.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateAutosized());

  EXPECT_TRUE(baseboard.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, baseboard.convergenceTolerance());
  baseboard.resetConvergenceTolerance();
  EXPECT_TRUE(baseboard.isConvergenceToleranceDefaulted());
  EXPECT_DOUBLE_EQ(0.001, baseboard.convergenceTolerance());
}
