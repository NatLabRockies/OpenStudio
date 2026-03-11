/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateSystemUnitary.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemUnitary_DefaultConstructor) {
  Model model;
  HVACTemplateSystemUnitary object(model);
  EXPECT_EQ(HVACTemplateSystemUnitary::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemUnitary_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemUnitary object(model);

  EXPECT_TRUE(object.setHeatingCoilType("Gas"));
  EXPECT_EQ("Gas", object.heatingCoilType());

  EXPECT_TRUE(object.setSupplyFanMaximumFlowRate(1.1));
  ASSERT_TRUE(object.supplyFanMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.1, object.supplyFanMaximumFlowRate().get());
  object.autosizeSupplyFanMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyFanMaximumFlowRateAutosized());

  EXPECT_TRUE(object.setEconomizerUpperTemperatureLimit(24.0));
  ASSERT_TRUE(object.economizerUpperTemperatureLimit());
  EXPECT_DOUBLE_EQ(24.0, object.economizerUpperTemperatureLimit().get());
  object.resetEconomizerUpperTemperatureLimit();
  EXPECT_FALSE(object.economizerUpperTemperatureLimit());

  EXPECT_TRUE(object.setHumidifierRatedElectricPower(500.0));
  ASSERT_TRUE(object.humidifierRatedElectricPower());
  EXPECT_DOUBLE_EQ(500.0, object.humidifierRatedElectricPower().get());
  object.autosizeHumidifierRatedElectricPower();
  EXPECT_TRUE(object.isHumidifierRatedElectricPowerAutosized());

  EXPECT_TRUE(object.setReturnFan(true));
  EXPECT_TRUE(object.returnFan());

  EXPECT_FALSE(object.setCoolingCoilType("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemUnitary::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemUnitary::economizerTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemUnitary::humidifierTypeValues().size(), 1u);
}
