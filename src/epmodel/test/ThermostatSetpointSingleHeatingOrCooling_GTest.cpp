/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ThermostatSetpointSingleHeatingOrCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermostatSetpointSingleHeatingOrCooling_DefaultConstructor) {
  Model model;
  ThermostatSetpointSingleHeatingOrCooling setpoint(model);
  EXPECT_EQ(ThermostatSetpointSingleHeatingOrCooling::iddObjectType(), setpoint.iddObject().type());
}

TEST_F(EPModelFixture, ThermostatSetpointSingleHeatingOrCooling_ScalarAccessors_RoundTrip) {
  Model model;
  ThermostatSetpointSingleHeatingOrCooling setpoint(model);

  EXPECT_TRUE(setpoint.setName("Living Space Setpoint"));
  EXPECT_EQ("Living Space Setpoint", setpoint.nameString());
}
