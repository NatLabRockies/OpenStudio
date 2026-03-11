/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Mixer/AirTerminalDualDuctVAV.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctVAV terminal(model);
  EXPECT_EQ(AirTerminalDualDuctVAV::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctVAV terminal(model);

  EXPECT_TRUE(terminal.setMaximumDamperAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumDamperAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumDamperAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumDamperAirFlowRateAutosized());

  terminal.autosizeMaximumDamperAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumDamperAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());
}
