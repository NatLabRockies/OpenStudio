/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoolingTowerPerformanceYorkCalc.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerPerformanceYorkCalc_DefaultConstructor) {
  Model model;
  CoolingTowerPerformanceYorkCalc perf(model);
  EXPECT_EQ(CoolingTowerPerformanceYorkCalc::iddObjectType(), perf.iddObject().type());
  EXPECT_FALSE(perf.nameString().empty());
}

TEST_F(EPModelFixture, CoolingTowerPerformanceYorkCalc_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerPerformanceYorkCalc perf(model);

  EXPECT_TRUE(perf.setMinimumInletAirWetBulbTemperature(-2.3));
  EXPECT_DOUBLE_EQ(-2.3, perf.minimumInletAirWetBulbTemperature());

  EXPECT_TRUE(perf.setMaximumLiquidtoGasRatio(7.25));
  EXPECT_DOUBLE_EQ(7.25, perf.maximumLiquidtoGasRatio());

  EXPECT_TRUE(perf.setCoefficient1(-0.31));
  EXPECT_DOUBLE_EQ(-0.31, perf.coefficient1());

  EXPECT_TRUE(perf.setCoefficient14(0.015));
  EXPECT_DOUBLE_EQ(0.015, perf.coefficient14());

  EXPECT_TRUE(perf.setCoefficient27(-1.2e-6));
  EXPECT_DOUBLE_EQ(-1.2e-6, perf.coefficient27());
}
