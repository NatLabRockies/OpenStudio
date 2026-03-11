/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SetpointManagerReturnAirBypassFlow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerReturnAirBypassFlow_DefaultConstructor) {
  Model model;
  SetpointManagerReturnAirBypassFlow setpointManager(model);
  EXPECT_EQ(SetpointManagerReturnAirBypassFlow::iddObjectType(), setpointManager.iddObject().type());
}

TEST_F(EPModelFixture, SetpointManagerReturnAirBypassFlow_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerReturnAirBypassFlow setpointManager(model);

  EXPECT_TRUE(setpointManager.setName("Return Air Bypass SPM"));
  EXPECT_EQ("Return Air Bypass SPM", setpointManager.nameString());

  EXPECT_EQ("Flow", setpointManager.controlVariable());
  EXPECT_TRUE(setpointManager.isControlVariableDefaulted());

  EXPECT_TRUE(setpointManager.setControlVariable("Flow"));
  EXPECT_EQ("Flow", setpointManager.controlVariable());
  EXPECT_FALSE(setpointManager.isControlVariableDefaulted());

  setpointManager.resetControlVariable();
  EXPECT_TRUE(setpointManager.isControlVariableDefaulted());
  EXPECT_EQ("Flow", setpointManager.controlVariable());
}
