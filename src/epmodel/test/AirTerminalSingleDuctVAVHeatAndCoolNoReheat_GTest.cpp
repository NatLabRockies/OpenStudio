/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVHeatAndCoolNoReheat_ScheduleRelationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat terminal(model);

  EXPECT_FALSE(terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());

  ScheduleCompact availability(model);
  ScheduleCompact turndown(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(turndown.setToConstantValue(0.4));

  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_TRUE(terminal.setMinimumAirFlowTurndownSchedule(turndown));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());
  ASSERT_TRUE(terminal.minimumAirFlowTurndownSchedule());
  EXPECT_EQ(turndown.handle(), terminal.minimumAirFlowTurndownSchedule()->handle());

  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}
