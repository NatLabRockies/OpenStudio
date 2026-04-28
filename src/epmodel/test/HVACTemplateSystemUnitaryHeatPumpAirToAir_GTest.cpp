/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateSystemUnitaryHeatPumpAirToAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemUnitaryHeatPumpAirToAir_DefaultConstructor) {
  Model model;
  HVACTemplateSystemUnitaryHeatPumpAirToAir object(model);
  EXPECT_EQ(HVACTemplateSystemUnitaryHeatPumpAirToAir::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemUnitaryHeatPumpAirToAir_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemUnitaryHeatPumpAirToAir object(model);

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());

  EXPECT_TRUE(object.setCoolingSupplyAirFlowRate(1.2));
  ASSERT_TRUE(object.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.coolingSupplyAirFlowRate().get());
  object.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.setEconomizerMaximumLimitDryBulbTemperature(24.0));
  ASSERT_TRUE(object.economizerMaximumLimitDryBulbTemperature());
  EXPECT_DOUBLE_EQ(24.0, object.economizerMaximumLimitDryBulbTemperature().get());
  object.resetEconomizerMaximumLimitDryBulbTemperature();
  EXPECT_FALSE(object.economizerMaximumLimitDryBulbTemperature());

  EXPECT_TRUE(object.setHumidifierRatedElectricPower(650.0));
  ASSERT_TRUE(object.humidifierRatedElectricPower());
  EXPECT_DOUBLE_EQ(650.0, object.humidifierRatedElectricPower().get());
  object.autosizeHumidifierRatedElectricPower();
  EXPECT_TRUE(object.isHumidifierRatedElectricPowerAutosized());

  EXPECT_TRUE(object.setReturnFan(true));
  EXPECT_TRUE(object.returnFan());

  EXPECT_FALSE(object.setSupplyFanPlacement("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemUnitaryHeatPumpAirToAir::economizerTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemUnitaryHeatPumpAirToAir::heatPumpDefrostControlValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemUnitaryHeatPumpAirToAir::humidifierTypeValues().size(), 1u);
}
