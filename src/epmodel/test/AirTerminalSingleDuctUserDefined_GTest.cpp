/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/AirTerminalSingleDuctUserDefined.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctUserDefined_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctUserDefined airTerminal(model);
  EXPECT_EQ(AirTerminalSingleDuctUserDefined::iddObjectType(), airTerminal.iddObject().type());
  EXPECT_FALSE(airTerminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctUserDefined airTerminal(model);

  EXPECT_TRUE(airTerminal.setNumberofPlantLoopConnections(2));
  EXPECT_EQ(2, airTerminal.numberofPlantLoopConnections());
}
