/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PhotovoltaicPerformance/PhotovoltaicPerformanceSimple.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PhotovoltaicPerformanceSimple_DefaultConstructor) {
  Model model;
  PhotovoltaicPerformanceSimple perf(model);
  EXPECT_EQ(PhotovoltaicPerformanceSimple::iddObjectType(), perf.iddObject().type());
}

TEST_F(EPModelFixture, PhotovoltaicPerformanceSimple_ScalarAccessors_RoundTrip) {
  Model model;
  PhotovoltaicPerformanceSimple perf(model);

  EXPECT_TRUE(perf.isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted());
  EXPECT_TRUE(perf.setFractionOfSurfaceAreaWithActiveSolarCells(0.85));
  EXPECT_DOUBLE_EQ(0.85, perf.fractionOfSurfaceAreaWithActiveSolarCells());
  EXPECT_FALSE(perf.isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted());
  perf.resetFractionOfSurfaceAreaWithActiveSolarCells();
  EXPECT_TRUE(perf.isfractionOfSurfaceAreaWithActiveSolarCellsDefaulted());

  EXPECT_TRUE(perf.setConversionEfficiencyInputMode("Scheduled"));
  EXPECT_EQ("Scheduled", perf.conversionEfficiencyInputMode());
  EXPECT_FALSE(PhotovoltaicPerformanceSimple::conversionEfficiencyInputModeValues().empty());

  EXPECT_TRUE(perf.fixedEfficiency());
  EXPECT_DOUBLE_EQ(0.12, *perf.fixedEfficiency());
  EXPECT_TRUE(perf.setFixedEfficiency(0.18));
  ASSERT_TRUE(perf.fixedEfficiency());
  EXPECT_DOUBLE_EQ(0.18, *perf.fixedEfficiency());
  EXPECT_EQ("Fixed", perf.conversionEfficiencyInputMode());
  perf.resetFixedEfficiency();
  ASSERT_TRUE(perf.fixedEfficiency());
  EXPECT_DOUBLE_EQ(0.12, *perf.fixedEfficiency());
}
