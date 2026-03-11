/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ThermostatSetpointThermalComfortFangerSingleHeating.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerSingleHeating_DefaultConstructor) {
  Model model;
  ThermostatSetpointThermalComfortFangerSingleHeating setpoint(model);
  EXPECT_EQ(ThermostatSetpointThermalComfortFangerSingleHeating::iddObjectType(), setpoint.iddObject().type());
}

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerSingleHeating_ScalarAccessors_RoundTrip) {
  Model model;
  ThermostatSetpointThermalComfortFangerSingleHeating setpoint(model);

  EXPECT_TRUE(setpoint.setName("Living Space Heating Comfort"));
  EXPECT_EQ("Living Space Heating Comfort", setpoint.nameString());
}
