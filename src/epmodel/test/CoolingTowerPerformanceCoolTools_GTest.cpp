/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoolingTowerPerformanceCoolTools.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerPerformanceCoolTools_DefaultConstructor) {
  Model model;
  CoolingTowerPerformanceCoolTools perf(model);
  EXPECT_EQ(CoolingTowerPerformanceCoolTools::iddObjectType(), perf.iddObject().type());
  EXPECT_FALSE(perf.nameString().empty());
}

TEST_F(EPModelFixture, CoolingTowerPerformanceCoolTools_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerPerformanceCoolTools perf(model);

  EXPECT_TRUE(perf.setMinimumInletAirWetBulbTemperature(-2.3));
  EXPECT_DOUBLE_EQ(-2.3, perf.minimumInletAirWetBulbTemperature());

  EXPECT_TRUE(perf.setMaximumApproachTemperature(9.4));
  EXPECT_DOUBLE_EQ(9.4, perf.maximumApproachTemperature());

  EXPECT_TRUE(perf.setCoefficient1(0.11));
  EXPECT_DOUBLE_EQ(0.11, perf.coefficient1());

  EXPECT_TRUE(perf.setCoefficient18(-0.022));
  EXPECT_DOUBLE_EQ(-0.022, perf.coefficient18());

  EXPECT_TRUE(perf.setCoefficient35(0.00091));
  EXPECT_DOUBLE_EQ(0.00091, perf.coefficient35());
}
