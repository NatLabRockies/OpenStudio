/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/FanPerformanceNightVentilation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanPerformanceNightVentilation_DefaultConstructor) {
  Model model;
  FanPerformanceNightVentilation fan(model);
  EXPECT_EQ(FanPerformanceNightVentilation::iddObjectType(), fan.iddObject().type());
}

TEST_F(EPModelFixture, FanPerformanceNightVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  FanPerformanceNightVentilation fan(model);

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, fan.fanTotalEfficiency());

  EXPECT_TRUE(fan.setPressureRise(180.0));
  EXPECT_DOUBLE_EQ(180.0, fan.pressureRise());

  EXPECT_FALSE(fan.maximumFlowRate());
  EXPECT_TRUE(fan.setMaximumFlowRate(0.72));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(0.72, fan.maximumFlowRate().get());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());
  fan.autosizeMaximumFlowRate();
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());
  fan.resetMaximumFlowRate();
  EXPECT_FALSE(fan.maximumFlowRate());

  EXPECT_TRUE(fan.setMotorEfficiency(0.89));
  EXPECT_DOUBLE_EQ(0.89, fan.motorEfficiency());

  EXPECT_TRUE(fan.isMotorinAirstreamFractionDefaulted());
  EXPECT_TRUE(fan.setMotorinAirstreamFraction(0.55));
  EXPECT_DOUBLE_EQ(0.55, fan.motorinAirstreamFraction());
  EXPECT_FALSE(fan.isMotorinAirstreamFractionDefaulted());
  fan.resetMotorinAirstreamFraction();
  EXPECT_TRUE(fan.isMotorinAirstreamFractionDefaulted());
}
