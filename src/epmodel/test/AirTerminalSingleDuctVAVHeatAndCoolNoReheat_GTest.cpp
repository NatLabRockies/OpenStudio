/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVHeatAndCoolNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());
}
