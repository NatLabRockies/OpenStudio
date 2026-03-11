/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ThermostatSetpointThermalComfortFangerSingleCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerSingleCooling_DefaultConstructor) {
  Model model;
  ThermostatSetpointThermalComfortFangerSingleCooling setpoint(model);
  EXPECT_EQ(ThermostatSetpointThermalComfortFangerSingleCooling::iddObjectType(), setpoint.iddObject().type());
}

TEST_F(EPModelFixture, ThermostatSetpointThermalComfortFangerSingleCooling_ScalarAccessors_RoundTrip) {
  Model model;
  ThermostatSetpointThermalComfortFangerSingleCooling setpoint(model);

  EXPECT_TRUE(setpoint.setName("Living Space Cooling Comfort"));
  EXPECT_EQ("Living Space Cooling Comfort", setpoint.nameString());
}
