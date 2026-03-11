/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
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
