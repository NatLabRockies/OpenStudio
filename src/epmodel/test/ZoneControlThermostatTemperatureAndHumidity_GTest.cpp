/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneControlThermostatTemperatureAndHumidity.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlThermostatTemperatureAndHumidity_DefaultConstructor) {
  Model model;
  ZoneControlThermostatTemperatureAndHumidity thermostat(model);
  EXPECT_EQ(ZoneControlThermostatTemperatureAndHumidity::iddObjectType(), thermostat.iddObject().type());
  EXPECT_EQ("Overcool", thermostat.dehumidificationControlType());
  EXPECT_EQ("Constant", thermostat.overcoolRangeInputMethod());
  ASSERT_TRUE(thermostat.overcoolConstantRange());
  EXPECT_DOUBLE_EQ(1.7, *thermostat.overcoolConstantRange());
  ASSERT_TRUE(thermostat.overcoolControlRatio());
  EXPECT_DOUBLE_EQ(3.6, *thermostat.overcoolControlRatio());
  EXPECT_TRUE(thermostat.isOvercoolConstantRangeDefaulted());
  EXPECT_TRUE(thermostat.isOvercoolControlRatioDefaulted());
}

TEST_F(EPModelFixture, ZoneControlThermostatTemperatureAndHumidity_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlThermostatTemperatureAndHumidity thermostat(model);

  EXPECT_TRUE(thermostat.setDehumidificationControlType("None"));
  EXPECT_TRUE(thermostat.setOvercoolRangeInputMethod("Scheduled"));
  EXPECT_TRUE(thermostat.setOvercoolConstantRange(2.2));
  EXPECT_TRUE(thermostat.setOvercoolControlRatio(5.6));

  EXPECT_EQ("None", thermostat.dehumidificationControlType());
  EXPECT_EQ("Scheduled", thermostat.overcoolRangeInputMethod());
  ASSERT_TRUE(thermostat.overcoolConstantRange());
  EXPECT_DOUBLE_EQ(2.2, *thermostat.overcoolConstantRange());
  EXPECT_FALSE(thermostat.isOvercoolConstantRangeDefaulted());
  ASSERT_TRUE(thermostat.overcoolControlRatio());
  EXPECT_DOUBLE_EQ(5.6, *thermostat.overcoolControlRatio());
  EXPECT_FALSE(thermostat.isOvercoolControlRatioDefaulted());

  thermostat.resetDehumidificationControlType();
  thermostat.resetOvercoolRangeInputMethod();
  thermostat.resetOvercoolConstantRange();
  thermostat.resetOvercoolControlRatio();

  EXPECT_TRUE(thermostat.isDehumidificationControlTypeDefaulted());
  EXPECT_TRUE(thermostat.isOvercoolRangeInputMethodDefaulted());
  EXPECT_TRUE(thermostat.isOvercoolConstantRangeDefaulted());
  EXPECT_TRUE(thermostat.isOvercoolControlRatioDefaulted());
}
