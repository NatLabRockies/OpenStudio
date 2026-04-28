/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowGapDeflectionState.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowGapDeflectionState_DefaultConstructor) {
  Model model;
  WindowGapDeflectionState deflectionState(model);
  EXPECT_EQ(WindowGapDeflectionState::iddObjectType(), deflectionState.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, deflectionState.deflectedThickness());
  EXPECT_DOUBLE_EQ(25.0, deflectionState.initialTemperature());
  EXPECT_DOUBLE_EQ(101325.0, deflectionState.initialPressure());
}

TEST_F(EPModelFixture, WindowGapDeflectionState_ScalarAccessors_RoundTrip) {
  Model model;
  WindowGapDeflectionState deflectionState(model);

  EXPECT_TRUE(deflectionState.setDeflectedThickness(0.0045));
  EXPECT_TRUE(deflectionState.setInitialTemperature(26.1));
  EXPECT_TRUE(deflectionState.setInitialPressure(102500.0));

  EXPECT_DOUBLE_EQ(0.0045, deflectionState.deflectedThickness());
  EXPECT_DOUBLE_EQ(26.1, deflectionState.initialTemperature());
  EXPECT_DOUBLE_EQ(102500.0, deflectionState.initialPressure());
}
