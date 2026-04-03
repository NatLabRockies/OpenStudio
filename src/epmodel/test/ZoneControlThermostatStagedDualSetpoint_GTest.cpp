/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Thermostat/ZoneControlThermostatStagedDualSetpoint.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlThermostatStagedDualSetpoint_DefaultConstructor) {
  Model model;
  ZoneControlThermostatStagedDualSetpoint thermostat(model);
  EXPECT_EQ(ZoneControlThermostatStagedDualSetpoint::iddObjectType(), thermostat.iddObject().type());
  EXPECT_EQ(2, thermostat.numberofHeatingStages());
  EXPECT_DOUBLE_EQ(1.1, thermostat.heatingThrottlingTemperatureRange());
  EXPECT_DOUBLE_EQ(0.0, thermostat.stage1HeatingTemperatureOffset());
  EXPECT_DOUBLE_EQ(-0.5, thermostat.stage2HeatingTemperatureOffset());
  EXPECT_DOUBLE_EQ(-1.0, thermostat.stage3HeatingTemperatureOffset());
  EXPECT_DOUBLE_EQ(-1.5, thermostat.stage4HeatingTemperatureOffset());
  EXPECT_EQ(4, thermostat.numberofCoolingStages());
  EXPECT_DOUBLE_EQ(1.1, thermostat.coolingThrottlingTemperatureRange());
  EXPECT_DOUBLE_EQ(0.0, thermostat.stage1CoolingTemperatureOffset());
  EXPECT_DOUBLE_EQ(1.0, thermostat.stage2CoolingTemperatureOffset());
  EXPECT_DOUBLE_EQ(2.0, thermostat.stage3CoolingTemperatureOffset());
  EXPECT_DOUBLE_EQ(3.0, thermostat.stage4CoolingTemperatureOffset());
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

TEST_F(EPModelFixture, ZoneControlThermostatStagedDualSetpoint_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneControlThermostatStagedDualSetpoint thermostat(model);
  ScheduleConstant heatingSchedule(model);
  ScheduleConstant coolingSchedule(model);

  EXPECT_FALSE(thermostat.heatingTemperatureSetpointSchedule());
  EXPECT_FALSE(thermostat.coolingTemperatureSetpointBaseSchedule());

  EXPECT_TRUE(thermostat.setHeatingTemperatureSetpointSchedule(heatingSchedule));
  EXPECT_TRUE(thermostat.heatingTemperatureSetpointSchedule());
  EXPECT_EQ(heatingSchedule, thermostat.heatingTemperatureSetpointSchedule().get());
  ASSERT_TRUE(heatingSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", heatingSchedule.scheduleTypeLimits()->unitType());

  EXPECT_TRUE(thermostat.setCoolingTemperatureSetpointBaseSchedule(coolingSchedule));
  EXPECT_TRUE(thermostat.coolingTemperatureSetpointBaseSchedule());
  EXPECT_EQ(coolingSchedule, thermostat.coolingTemperatureSetpointBaseSchedule().get());
  ASSERT_TRUE(coolingSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", coolingSchedule.scheduleTypeLimits()->unitType());

  thermostat.resetHeatingTemperatureSetpointSchedule();
  EXPECT_FALSE(thermostat.heatingTemperatureSetpointSchedule());

  thermostat.resetCoolingTemperatureSetpointBaseSchedule();
  EXPECT_FALSE(thermostat.coolingTemperatureSetpointBaseSchedule());
}

TEST_F(EPModelFixture, ZoneControlThermostatStagedDualSetpoint_ScheduleRelationships_RejectIncompatibleScheduleTypeLimits) {
  Model model;
  ZoneControlThermostatStagedDualSetpoint thermostat(model);
  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(availabilityLimits));

  EXPECT_FALSE(thermostat.setHeatingTemperatureSetpointSchedule(wrongSchedule));
  EXPECT_FALSE(thermostat.setCoolingTemperatureSetpointBaseSchedule(wrongSchedule));
}
