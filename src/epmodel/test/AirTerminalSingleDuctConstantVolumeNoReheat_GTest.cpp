/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirTerminalSingleDuctConstantVolumeNoReheat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirTerminalSingleDuctConstantVolumeNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}
