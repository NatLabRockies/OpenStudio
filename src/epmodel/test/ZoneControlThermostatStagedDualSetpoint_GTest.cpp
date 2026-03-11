/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Thermostat/ZoneControlThermostatStagedDualSetpoint.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlThermostatStagedDualSetpoint_DefaultConstructor) {
  Model model;
  ZoneControlThermostatStagedDualSetpoint thermostat(model);
  EXPECT_EQ(ZoneControlThermostatStagedDualSetpoint::iddObjectType(), thermostat.iddObject().type());
}

TEST_F(EPModelFixture, ZoneControlThermostatStagedDualSetpoint_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlThermostatStagedDualSetpoint thermostat(model);

  EXPECT_TRUE(thermostat.setNumberofHeatingStages(4));
  EXPECT_EQ(4, thermostat.numberofHeatingStages());
  EXPECT_TRUE(thermostat.setHeatingThrottlingTemperatureRange(2.5));
  EXPECT_DOUBLE_EQ(2.5, thermostat.heatingThrottlingTemperatureRange());

  EXPECT_TRUE(thermostat.setStage1HeatingTemperatureOffset(0.0));
  EXPECT_DOUBLE_EQ(0.0, thermostat.stage1HeatingTemperatureOffset());
  EXPECT_TRUE(thermostat.setStage2HeatingTemperatureOffset(-1.0));
  EXPECT_DOUBLE_EQ(-1.0, thermostat.stage2HeatingTemperatureOffset());
  EXPECT_TRUE(thermostat.setStage3HeatingTemperatureOffset(-2.0));
  EXPECT_DOUBLE_EQ(-2.0, thermostat.stage3HeatingTemperatureOffset());
  EXPECT_TRUE(thermostat.setStage4HeatingTemperatureOffset(-3.0));
  EXPECT_DOUBLE_EQ(-3.0, thermostat.stage4HeatingTemperatureOffset());

  EXPECT_TRUE(thermostat.setNumberofCoolingStages(3));
  EXPECT_EQ(3, thermostat.numberofCoolingStages());
  EXPECT_TRUE(thermostat.setCoolingThrottlingTemperatureRange(1.75));
  EXPECT_DOUBLE_EQ(1.75, thermostat.coolingThrottlingTemperatureRange());

  EXPECT_TRUE(thermostat.setStage1CoolingTemperatureOffset(0.5));
  EXPECT_DOUBLE_EQ(0.5, thermostat.stage1CoolingTemperatureOffset());
  EXPECT_TRUE(thermostat.setStage2CoolingTemperatureOffset(1.0));
  EXPECT_DOUBLE_EQ(1.0, thermostat.stage2CoolingTemperatureOffset());
  EXPECT_TRUE(thermostat.setStage3CoolingTemperatureOffset(1.5));
  EXPECT_DOUBLE_EQ(1.5, thermostat.stage3CoolingTemperatureOffset());
  EXPECT_TRUE(thermostat.setStage4CoolingTemperatureOffset(2.0));
  EXPECT_DOUBLE_EQ(2.0, thermostat.stage4CoolingTemperatureOffset());
}
