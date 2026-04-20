/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneCoolTowerShower.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneCoolTowerShower_DefaultConstructor) {
  Model model;
  ZoneCoolTowerShower shower(model);

  EXPECT_EQ(ZoneCoolTowerShower::iddObjectType(), shower.iddObject().type());
  EXPECT_DOUBLE_EQ(0.01, shower.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(10.0, shower.effectiveTowerHeight());
  EXPECT_DOUBLE_EQ(1.0, shower.airflowOutletArea());
  EXPECT_DOUBLE_EQ(0.5, shower.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(20.0, shower.minimumIndoorTemperature());
  EXPECT_EQ("WindDrivenFlow", shower.flowControlType());
  EXPECT_DOUBLE_EQ(1200.0, shower.ratedPowerConsumption());
  EXPECT_FALSE(shower.fractionofWaterLoss());
  EXPECT_FALSE(shower.fractionofFlowSchedule());
}

TEST_F(EPModelFixture, ZoneCoolTowerShower_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneCoolTowerShower shower(model);

  EXPECT_TRUE(shower.setFlowControlType("WaterFlowSchedule"));
  EXPECT_TRUE(shower.setMaximumWaterFlowRate(0.02));
  EXPECT_TRUE(shower.setEffectiveTowerHeight(11.0));
  EXPECT_TRUE(shower.setAirflowOutletArea(1.5));
  EXPECT_TRUE(shower.setMaximumAirFlowRate(0.6));
  EXPECT_TRUE(shower.setMinimumIndoorTemperature(18.0));
  EXPECT_TRUE(shower.setFractionofWaterLoss(0.12));
  EXPECT_TRUE(shower.setFractionofFlowSchedule(0.33));
  EXPECT_TRUE(shower.setRatedPowerConsumption(1400.0));

  EXPECT_EQ("WaterFlowSchedule", shower.flowControlType());
  EXPECT_DOUBLE_EQ(0.02, shower.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(11.0, shower.effectiveTowerHeight());
  EXPECT_DOUBLE_EQ(1.5, shower.airflowOutletArea());
  EXPECT_DOUBLE_EQ(0.6, shower.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(18.0, shower.minimumIndoorTemperature());
  ASSERT_TRUE(shower.fractionofWaterLoss());
  EXPECT_DOUBLE_EQ(0.12, *shower.fractionofWaterLoss());
  ASSERT_TRUE(shower.fractionofFlowSchedule());
  EXPECT_DOUBLE_EQ(0.33, *shower.fractionofFlowSchedule());
  EXPECT_DOUBLE_EQ(1400.0, shower.ratedPowerConsumption());
}
