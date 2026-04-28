/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ThermalStorageSizing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageSizing_DefaultConstructor) {
  Model model;
  ThermalStorageSizing sizing(model);
  EXPECT_EQ(ThermalStorageSizing::iddObjectType(), sizing.iddObject().type());
}

TEST_F(EPModelFixture, ThermalStorageSizing_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageSizing sizing(model);

  EXPECT_TRUE(sizing.setOnPeakPeriodStartTime(1.5));
  EXPECT_DOUBLE_EQ(1.5, sizing.onPeakPeriodStartTime());

  EXPECT_TRUE(sizing.setOnPeakPeriodEndTime(4.25));
  EXPECT_DOUBLE_EQ(4.25, sizing.onPeakPeriodEndTime());

  EXPECT_TRUE(sizing.isSizingFactorDefaulted());
  EXPECT_TRUE(sizing.setSizingFactor(1.75));
  EXPECT_DOUBLE_EQ(1.75, sizing.sizingFactor());
  EXPECT_FALSE(sizing.isSizingFactorDefaulted());

  sizing.resetSizingFactor();
  EXPECT_TRUE(sizing.isSizingFactorDefaulted());
}
