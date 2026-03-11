/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  EXPECT_EQ(AirTerminalDualDuctVAVOutdoorAir::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());

  EXPECT_TRUE(terminal.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("CurrentOccupancy", terminal.perPersonVentilationRateMode());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  EXPECT_TRUE(terminal.setMaximumTerminalAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumTerminalAirFlowRateAutosized());

  terminal.autosizeMaximumTerminalAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumTerminalAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());

  EXPECT_FALSE(terminal.setPerPersonVentilationRateMode("InvalidChoice"));

  const auto values = AirTerminalDualDuctVAVOutdoorAir::perPersonVentilationRateModeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "CurrentOccupancy"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "DesignOccupancy"));
}
