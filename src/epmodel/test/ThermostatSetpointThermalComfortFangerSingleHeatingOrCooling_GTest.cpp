/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_DefaultConstructor) {
  Model model;
  ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling setpoint(model);
  EXPECT_EQ(ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling::iddObjectType(), setpoint.iddObject().type());
}

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling_ScalarAccessors_RoundTrip) {
  Model model;
  ThermostatSetpointThermalComfortFangerSingleHeatingOrCooling setpoint(model);

  EXPECT_TRUE(setpoint.setName("Living Space Comfort"));
  EXPECT_EQ("Living Space Comfort", setpoint.nameString());
}
