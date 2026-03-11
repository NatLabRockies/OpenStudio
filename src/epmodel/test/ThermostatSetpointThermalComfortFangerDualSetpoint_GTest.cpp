/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ThermostatSetpointThermalComfortFangerDualSetpoint.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerDualSetpoint_DefaultConstructor) {
  Model model;
  ThermostatSetpointThermalComfortFangerDualSetpoint setpoint(model);
  EXPECT_EQ(ThermostatSetpointThermalComfortFangerDualSetpoint::iddObjectType(), setpoint.iddObject().type());
}

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerDualSetpoint_ScalarAccessors_RoundTrip) {
  Model model;
  ThermostatSetpointThermalComfortFangerDualSetpoint setpoint(model);

  EXPECT_TRUE(setpoint.setName("Living Space Setpoint"));
  EXPECT_EQ("Living Space Setpoint", setpoint.nameString());
}
