/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/AirTerminalSingleDuctVAVReheatVariableSpeedFan.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheatVariableSpeedFan_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan terminal(model);

  EXPECT_TRUE(terminal.isMaximumCoolingAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumCoolingAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumCoolingAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumCoolingAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumCoolingAirFlowRateAutosized());
  terminal.autosizeMaximumCoolingAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumCoolingAirFlowRateAutosized());

  EXPECT_TRUE(terminal.isMaximumHeatingAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHeatingAirFlowRate(0.987));
  ASSERT_TRUE(terminal.maximumHeatingAirFlowRate());
  EXPECT_DOUBLE_EQ(0.987, terminal.maximumHeatingAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHeatingAirFlowRateAutosized());
  terminal.autosizeMaximumHeatingAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumHeatingAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.22));
  EXPECT_DOUBLE_EQ(0.22, terminal.zoneMinimumAirFlowFraction());

  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterorSteamFlowRate());
  EXPECT_FALSE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());
  terminal.resetMinimumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());

  EXPECT_TRUE(terminal.setHeatingConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.heatingConvergenceTolerance());
  EXPECT_FALSE(terminal.isHeatingConvergenceToleranceDefaulted());
  terminal.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(terminal.isHeatingConvergenceToleranceDefaulted());
}
