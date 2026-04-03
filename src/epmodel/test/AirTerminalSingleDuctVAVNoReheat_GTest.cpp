/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVNoReheat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVNoReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVNoReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  terminal.resetMaximumAirFlowRate();
  EXPECT_FALSE(terminal.maximumAirFlowRate());

  ASSERT_TRUE(terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowInputMethod().get());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowInputMethod("FixedFlowRate"));
  ASSERT_TRUE(terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_EQ("FixedFlowRate", terminal.zoneMinimumAirFlowInputMethod().get());
  terminal.resetZoneMinimumAirFlowInputMethod();
  ASSERT_TRUE(terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowInputMethod().get());

  ASSERT_TRUE(terminal.constantMinimumAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.3, terminal.constantMinimumAirFlowFraction().get());
  EXPECT_FALSE(terminal.isConstantMinimumAirFlowFractionAutosized());
  EXPECT_FALSE(terminal.isConstantMinimumAirFlowFractionDefaulted());
  EXPECT_TRUE(terminal.setConstantMinimumAirFlowFraction(0.42));
  ASSERT_TRUE(terminal.constantMinimumAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.42, terminal.constantMinimumAirFlowFraction().get());
  terminal.autosizeConstantMinimumAirFlowFraction();
  EXPECT_TRUE(terminal.isConstantMinimumAirFlowFractionAutosized());
  terminal.resetConstantMinimumAirFlowFraction();
  EXPECT_TRUE(terminal.isConstantMinimumAirFlowFractionDefaulted());
  EXPECT_FALSE(terminal.constantMinimumAirFlowFraction());

  EXPECT_TRUE(terminal.isFixedMinimumAirFlowRateDefaulted());
  EXPECT_FALSE(terminal.fixedMinimumAirFlowRate());
  EXPECT_TRUE(terminal.setFixedMinimumAirFlowRate(0.5));
  ASSERT_TRUE(terminal.fixedMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, terminal.fixedMinimumAirFlowRate().get());
  terminal.autosizeFixedMinimumAirFlowRate();
  EXPECT_TRUE(terminal.isFixedMinimumAirFlowRateAutosized());
  terminal.resetFixedMinimumAirFlowRate();
  EXPECT_TRUE(terminal.isFixedMinimumAirFlowRateDefaulted());
  EXPECT_FALSE(terminal.fixedMinimumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVNoReheat_ScheduleRelationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVNoReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact minimumFraction(model);
  ScheduleCompact turndown(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(minimumFraction.setToConstantValue(0.2));
  ASSERT_TRUE(turndown.setToConstantValue(0.4));

  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_TRUE(terminal.setMinimumAirFlowFractionSchedule(minimumFraction));
  EXPECT_TRUE(terminal.setMinimumAirFlowTurndownSchedule(turndown));
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  ASSERT_TRUE(terminal.minimumAirFlowFractionSchedule());
  EXPECT_EQ(minimumFraction.handle(), terminal.minimumAirFlowFractionSchedule()->handle());
  ASSERT_TRUE(terminal.minimumAirFlowTurndownSchedule());
  EXPECT_EQ(turndown.handle(), terminal.minimumAirFlowTurndownSchedule()->handle());

  terminal.resetMinimumAirFlowFractionSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowFractionSchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}
