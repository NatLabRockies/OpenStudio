/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../PhotovoltaicPerformance/PhotovoltaicPerformanceSandia.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PhotovoltaicPerformanceSandia_DefaultConstructor) {
  Model model;
  PhotovoltaicPerformanceSandia perf(model);
  EXPECT_EQ(PhotovoltaicPerformanceSandia::iddObjectType(), perf.iddObject().type());
}

TEST_F(EPModelFixture, PhotovoltaicPerformanceSandia_ScalarAccessors_RoundTrip) {
  Model model;
  PhotovoltaicPerformanceSandia perf(model);

  EXPECT_TRUE(perf.setActiveArea(0.606));
  EXPECT_DOUBLE_EQ(0.606, perf.activeArea());

  EXPECT_TRUE(perf.setNumberofCellsinSeries(36));
  EXPECT_EQ(36, perf.numberofCellsinSeries());

  EXPECT_TRUE(perf.setNumberofCellsinParallel(1));
  EXPECT_EQ(1, perf.numberofCellsinParallel());

  EXPECT_TRUE(perf.setShortCircuitCurrent(3.87));
  EXPECT_DOUBLE_EQ(3.87, perf.shortCircuitCurrent());

  EXPECT_TRUE(perf.setOpenCircuitVoltage(21.0));
  EXPECT_DOUBLE_EQ(21.0, perf.openCircuitVoltage());

  EXPECT_TRUE(perf.setSandiaDatabaseParameterDeltaTc(3.0));
  EXPECT_DOUBLE_EQ(3.0, perf.sandiaDatabaseParameterDeltaTc());
}
