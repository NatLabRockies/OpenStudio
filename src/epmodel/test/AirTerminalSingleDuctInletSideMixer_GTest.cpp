/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctInletSideMixer terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctInletSideMixer::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());

  EXPECT_EQ("CurrentOccupancy", terminal.perPersonVentilationRateMode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctInletSideMixer_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctInletSideMixer terminal(model);

  EXPECT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());

  EXPECT_FALSE(terminal.setPerPersonVentilationRateMode("InvalidChoice"));

  const auto values = AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "CurrentOccupancy"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "DesignOccupancy"));
}
