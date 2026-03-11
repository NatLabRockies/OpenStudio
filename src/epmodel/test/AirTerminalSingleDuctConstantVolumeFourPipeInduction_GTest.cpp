/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeInduction airTerminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), airTerminal.iddObject().type());
  EXPECT_FALSE(airTerminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeInduction airTerminal(model);

  EXPECT_TRUE(airTerminal.isMaximumTotalAirFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isMaximumHotWaterFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isMaximumColdWaterFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setMaximumTotalAirFlowRate(0.52));
  ASSERT_TRUE(airTerminal.maximumTotalAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, airTerminal.maximumTotalAirFlowRate().get());
  EXPECT_FALSE(airTerminal.isMaximumTotalAirFlowRateAutosized());
  airTerminal.autosizeMaximumTotalAirFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumTotalAirFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setInductionRatio(2.7));
  EXPECT_DOUBLE_EQ(2.7, airTerminal.inductionRatio());
  EXPECT_FALSE(airTerminal.isInductionRatioDefaulted());
  airTerminal.resetInductionRatio();
  EXPECT_TRUE(airTerminal.isInductionRatioDefaulted());

  EXPECT_TRUE(airTerminal.setMaximumHotWaterFlowRate(0.04));
  ASSERT_TRUE(airTerminal.maximumHotWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.04, airTerminal.maximumHotWaterFlowRate().get());
  EXPECT_FALSE(airTerminal.isMaximumHotWaterFlowRateAutosized());
  airTerminal.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumHotWaterFlowRateAutosized());
  airTerminal.resetMaximumHotWaterFlowRate();
  EXPECT_FALSE(airTerminal.maximumHotWaterFlowRate());

  EXPECT_TRUE(airTerminal.setMinimumHotWaterFlowRate(0.003));
  EXPECT_DOUBLE_EQ(0.003, airTerminal.minimumHotWaterFlowRate());
  EXPECT_FALSE(airTerminal.isMinimumHotWaterFlowRateDefaulted());
  airTerminal.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(airTerminal.isMinimumHotWaterFlowRateDefaulted());

  EXPECT_TRUE(airTerminal.setHeatingConvergenceTolerance(0.0018));
  EXPECT_DOUBLE_EQ(0.0018, airTerminal.heatingConvergenceTolerance());
  EXPECT_FALSE(airTerminal.isHeatingConvergenceToleranceDefaulted());
  airTerminal.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(airTerminal.isHeatingConvergenceToleranceDefaulted());

  EXPECT_TRUE(airTerminal.setMaximumColdWaterFlowRate(0.03));
  ASSERT_TRUE(airTerminal.maximumColdWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.03, airTerminal.maximumColdWaterFlowRate().get());
  EXPECT_FALSE(airTerminal.isMaximumColdWaterFlowRateAutosized());
  airTerminal.autosizeMaximumColdWaterFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumColdWaterFlowRateAutosized());
  airTerminal.resetMaximumColdWaterFlowRate();
  EXPECT_FALSE(airTerminal.maximumColdWaterFlowRate());

  EXPECT_TRUE(airTerminal.setMinimumColdWaterFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, airTerminal.minimumColdWaterFlowRate());
  EXPECT_FALSE(airTerminal.isMinimumColdWaterFlowRateDefaulted());
  airTerminal.resetMinimumColdWaterFlowRate();
  EXPECT_TRUE(airTerminal.isMinimumColdWaterFlowRateDefaulted());

  EXPECT_TRUE(airTerminal.setCoolingConvergenceTolerance(0.0012));
  EXPECT_DOUBLE_EQ(0.0012, airTerminal.coolingConvergenceTolerance());
  EXPECT_FALSE(airTerminal.isCoolingConvergenceToleranceDefaulted());
  airTerminal.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(airTerminal.isCoolingConvergenceToleranceDefaulted());
}
