/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Model.hpp"
#include "../ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACEnergyRecoveryVentilatorController_DefaultConstructor) {
  Model model;
  ZoneHVACEnergyRecoveryVentilatorController controller(model);
  SUCCEED();
}

TEST_F(EPModelFixture, API_ZoneHVACEnergyRecoveryVentilatorController_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEnergyRecoveryVentilatorController controller(model);

  ASSERT_TRUE(controller.setTemperatureHighLimit(35.75));
  ASSERT_TRUE(controller.temperatureHighLimit());
  EXPECT_NEAR(35.75, *controller.temperatureHighLimit(), 1e-9);
  controller.resetTemperatureHighLimit();
  EXPECT_FALSE(controller.temperatureHighLimit());

  ASSERT_TRUE(controller.setTemperatureLowLimit(5.0));
  ASSERT_TRUE(controller.temperatureLowLimit());
  EXPECT_NEAR(5.0, *controller.temperatureLowLimit(), 1e-9);
  controller.resetTemperatureLowLimit();
  EXPECT_FALSE(controller.temperatureLowLimit());

  ASSERT_TRUE(controller.setEnthalpyHighLimit(42000.0));
  ASSERT_TRUE(controller.enthalpyHighLimit());
  EXPECT_NEAR(42000.0, *controller.enthalpyHighLimit(), 1e-9);
  controller.resetEnthalpyHighLimit();
  EXPECT_FALSE(controller.enthalpyHighLimit());

  ASSERT_TRUE(controller.setDewpointTemperatureLimit(15.5));
  ASSERT_TRUE(controller.dewpointTemperatureLimit());
  EXPECT_NEAR(15.5, *controller.dewpointTemperatureLimit(), 1e-9);
  controller.resetDewpointTemperatureLimit();
  EXPECT_FALSE(controller.dewpointTemperatureLimit());

  const auto temperatureLimitValues = ZoneHVACEnergyRecoveryVentilatorController::exhaustAirTemperatureLimitValues();
  ASSERT_FALSE(temperatureLimitValues.empty());
  EXPECT_TRUE(controller.setExhaustAirTemperatureLimit(temperatureLimitValues.front()));
  EXPECT_EQ(temperatureLimitValues.front(), controller.exhaustAirTemperatureLimit());

  const auto enthalpyLimitValues = ZoneHVACEnergyRecoveryVentilatorController::exhaustAirEnthalpyLimitValues();
  ASSERT_FALSE(enthalpyLimitValues.empty());
  EXPECT_TRUE(controller.setExhaustAirEnthalpyLimit(enthalpyLimitValues.front()));
  EXPECT_EQ(enthalpyLimitValues.front(), controller.exhaustAirEnthalpyLimit());

  EXPECT_TRUE(controller.setHighHumidityControlFlag(true));
  EXPECT_TRUE(controller.highHumidityControlFlag());
  EXPECT_TRUE(controller.setHighHumidityControlFlag(false));
  EXPECT_FALSE(controller.highHumidityControlFlag());

  ASSERT_TRUE(controller.setHighHumidityOutdoorAirFlowRatio(1.41));
  EXPECT_NEAR(1.41, controller.highHumidityOutdoorAirFlowRatio(), 1e-9);

  EXPECT_TRUE(controller.setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(false));
  EXPECT_FALSE(controller.controlHighIndoorHumidityBasedOnOutdoorHumidityRatio());
}
