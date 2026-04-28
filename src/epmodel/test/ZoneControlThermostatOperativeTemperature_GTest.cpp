/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneControlThermostatOperativeTemperature.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlThermostatOperativeTemperature_DefaultConstructor) {
  Model model;
  ZoneControlThermostatOperativeTemperature thermostat(model);
  EXPECT_EQ(ZoneControlThermostatOperativeTemperature::iddObjectType(), thermostat.iddObject().type());
  EXPECT_EQ("Constant", thermostat.radiativeFractionInputMode());
  EXPECT_FALSE(thermostat.fixedRadiativeFraction());
  EXPECT_TRUE(thermostat.isAdaptiveComfortModelTypeDefaulted());
}

TEST_F(EPModelFixture, ZoneControlThermostatOperativeTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlThermostatOperativeTemperature thermostat(model);

  EXPECT_TRUE(thermostat.setRadiativeFractionInputMode("Scheduled"));
  EXPECT_TRUE(thermostat.setFixedRadiativeFraction(0.25));
  EXPECT_TRUE(thermostat.setAdaptiveComfortModelType("AdaptiveASH55CentralLine"));

  EXPECT_EQ("Scheduled", thermostat.radiativeFractionInputMode());
  ASSERT_TRUE(thermostat.fixedRadiativeFraction());
  EXPECT_DOUBLE_EQ(0.25, *thermostat.fixedRadiativeFraction());
  EXPECT_EQ("AdaptiveASH55CentralLine", thermostat.adaptiveComfortModelType());
  EXPECT_FALSE(thermostat.isAdaptiveComfortModelTypeDefaulted());

  thermostat.resetAdaptiveComfortModelType();
  EXPECT_TRUE(thermostat.isAdaptiveComfortModelTypeDefaulted());
}
