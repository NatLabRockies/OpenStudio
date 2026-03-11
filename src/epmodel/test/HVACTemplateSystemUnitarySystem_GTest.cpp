/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateSystemUnitarySystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemUnitarySystem_DefaultConstructor) {
  Model model;
  HVACTemplateSystemUnitarySystem object(model);
  EXPECT_EQ(HVACTemplateSystemUnitarySystem::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemUnitarySystem_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemUnitarySystem object(model);

  EXPECT_TRUE(object.setControlType("SetPoint"));
  EXPECT_EQ("SetPoint", object.controlType());

  EXPECT_TRUE(object.setNumberofSpeedsforCooling(2));
  EXPECT_EQ(2, object.numberofSpeedsforCooling());

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

  EXPECT_FALSE(object.setControlType("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemUnitarySystem::controlTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemUnitarySystem::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemUnitarySystem::sizingOptionValues().size(), 1u);
}
