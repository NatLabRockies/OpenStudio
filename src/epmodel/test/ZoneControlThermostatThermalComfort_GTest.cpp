/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneControlThermostatThermalComfort.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlThermostatThermalComfort_DefaultConstructor) {
  Model model;
  ZoneControlThermostatThermalComfort thermostat(model);

  EXPECT_EQ(ZoneControlThermostatThermalComfort::iddObjectType(), thermostat.iddObject().type());
  EXPECT_EQ("PeopleAverage", thermostat.averagingMethod());
  ASSERT_TRUE(thermostat.minimumDryBulbTemperatureSetpoint());
  EXPECT_DOUBLE_EQ(0.0, *thermostat.minimumDryBulbTemperatureSetpoint());
  ASSERT_TRUE(thermostat.maximumDryBulbTemperatureSetpoint());
  EXPECT_DOUBLE_EQ(50.0, *thermostat.maximumDryBulbTemperatureSetpoint());
  EXPECT_TRUE(thermostat.isMinimumDryBulbTemperatureSetpointDefaulted());
  EXPECT_TRUE(thermostat.isMaximumDryBulbTemperatureSetpointDefaulted());
}

TEST_F(EPModelFixture, ZoneControlThermostatThermalComfort_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlThermostatThermalComfort thermostat(model);

  EXPECT_TRUE(thermostat.setAveragingMethod("SpecificObject"));
  EXPECT_TRUE(thermostat.setMinimumDryBulbTemperatureSetpoint(21.7));
  EXPECT_TRUE(thermostat.setMaximumDryBulbTemperatureSetpoint(27.6));

  EXPECT_EQ("SpecificObject", thermostat.averagingMethod());
  ASSERT_TRUE(thermostat.minimumDryBulbTemperatureSetpoint());
  EXPECT_DOUBLE_EQ(21.7, *thermostat.minimumDryBulbTemperatureSetpoint());
  EXPECT_FALSE(thermostat.isMinimumDryBulbTemperatureSetpointDefaulted());
  ASSERT_TRUE(thermostat.maximumDryBulbTemperatureSetpoint());
  EXPECT_DOUBLE_EQ(27.6, *thermostat.maximumDryBulbTemperatureSetpoint());
  EXPECT_FALSE(thermostat.isMaximumDryBulbTemperatureSetpointDefaulted());

  thermostat.resetAveragingMethod();
  thermostat.resetMinimumDryBulbTemperatureSetpoint();
  thermostat.resetMaximumDryBulbTemperatureSetpoint();

  EXPECT_TRUE(thermostat.isAveragingMethodDefaulted());
  EXPECT_TRUE(thermostat.isMinimumDryBulbTemperatureSetpointDefaulted());
  EXPECT_TRUE(thermostat.isMaximumDryBulbTemperatureSetpointDefaulted());
}
