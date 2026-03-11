/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctParallelPIUReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctParallelPIUReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumPrimaryAirFlowRate(1.25));
  ASSERT_TRUE(terminal.maximumPrimaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, terminal.maximumPrimaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumPrimaryAirFlowRateAutosized());
  terminal.autosizeMaximumPrimaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumPrimaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMaximumSecondaryAirFlowRate(1.10));
  ASSERT_TRUE(terminal.maximumSecondaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.10, terminal.maximumSecondaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumSecondaryAirFlowRateAutosized());
  terminal.autosizeMaximumSecondaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumSecondaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumPrimaryAirFlowFraction(0.42));
  ASSERT_TRUE(terminal.minimumPrimaryAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.42, terminal.minimumPrimaryAirFlowFraction().get());
  EXPECT_FALSE(terminal.isMinimumPrimaryAirFlowFractionAutosized());
  terminal.autosizeMinimumPrimaryAirFlowFraction();
  EXPECT_TRUE(terminal.isMinimumPrimaryAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setFanOnFlowFraction(0.58));
  ASSERT_TRUE(terminal.fanOnFlowFraction());
  EXPECT_DOUBLE_EQ(0.58, terminal.fanOnFlowFraction().get());
  EXPECT_FALSE(terminal.isFanOnFlowFractionAutosized());
  terminal.autosizeFanOnFlowFraction();
  EXPECT_TRUE(terminal.isFanOnFlowFractionAutosized());

  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.004));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.004, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.resetMaximumHotWaterorSteamFlowRate();
  EXPECT_FALSE(terminal.maximumHotWaterorSteamFlowRate());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.0011));
  EXPECT_DOUBLE_EQ(0.0011, terminal.minimumHotWaterorSteamFlowRate());
  EXPECT_FALSE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());
  terminal.resetMinimumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.006));
  EXPECT_DOUBLE_EQ(0.006, terminal.convergenceTolerance());
  EXPECT_FALSE(terminal.isConvergenceToleranceDefaulted());
  terminal.resetConvergenceTolerance();
  EXPECT_TRUE(terminal.isConvergenceToleranceDefaulted());

  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  EXPECT_TRUE(terminal.setMinimumFanTurnDownRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, terminal.minimumFanTurnDownRatio());

  EXPECT_EQ("Staged", terminal.heatingControlType());
  EXPECT_TRUE(terminal.setHeatingControlType("Modulated"));
  EXPECT_EQ("Modulated", terminal.heatingControlType());

  EXPECT_TRUE(terminal.setDesignHeatingDischargeAirTemperature(34.0));
  EXPECT_DOUBLE_EQ(34.0, terminal.designHeatingDischargeAirTemperature());

  EXPECT_TRUE(terminal.setHighLimitHeatingDischargeAirTemperature(40.0));
  EXPECT_DOUBLE_EQ(40.0, terminal.highLimitHeatingDischargeAirTemperature());

  const auto fanControlTypeValues = AirTerminalSingleDuctParallelPIUReheat::fanControlTypeValues();
  EXPECT_FALSE(fanControlTypeValues.empty());
  EXPECT_TRUE(std::find(fanControlTypeValues.begin(), fanControlTypeValues.end(), "ConstantSpeed") != fanControlTypeValues.end());

  const auto heatingControlTypeValues = AirTerminalSingleDuctParallelPIUReheat::heatingControlTypeValues();
  EXPECT_FALSE(heatingControlTypeValues.empty());
  EXPECT_TRUE(std::find(heatingControlTypeValues.begin(), heatingControlTypeValues.end(), "Staged") != heatingControlTypeValues.end());
}
