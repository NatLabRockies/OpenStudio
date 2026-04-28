/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateSystemVAV.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemVAV_DefaultConstructor) {
  Model model;
  HVACTemplateSystemVAV object(model);
  EXPECT_EQ(HVACTemplateSystemVAV::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemVAV_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemVAV object(model);

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());

  EXPECT_TRUE(object.setSupplyFanMinimumFlowRate(0.0));
  ASSERT_TRUE(object.supplyFanMinimumFlowRate());
  EXPECT_DOUBLE_EQ(0.0, object.supplyFanMinimumFlowRate().get());
  object.autosizeSupplyFanMinimumFlowRate();
  EXPECT_TRUE(object.isSupplyFanMinimumFlowRateAutosized());

  EXPECT_TRUE(object.setCoolingCoilDesignSetpoint(12.5));
  EXPECT_DOUBLE_EQ(12.5, object.coolingCoilDesignSetpoint());

  EXPECT_TRUE(object.setPreheatCoilType("Gas"));
  EXPECT_EQ("Gas", object.preheatCoilType());
  EXPECT_TRUE(object.setPreheatCoilDesignSetpoint(7.0));
  EXPECT_DOUBLE_EQ(7.0, object.preheatCoilDesignSetpoint());

  EXPECT_TRUE(object.setEconomizerUpperTemperatureLimit(26.0));
  ASSERT_TRUE(object.economizerUpperTemperatureLimit());
  EXPECT_DOUBLE_EQ(26.0, object.economizerUpperTemperatureLimit().get());
  object.resetEconomizerUpperTemperatureLimit();
  EXPECT_FALSE(object.economizerUpperTemperatureLimit());

  EXPECT_TRUE(object.setHumidifierRatedElectricPower(950.0));
  ASSERT_TRUE(object.humidifierRatedElectricPower());
  EXPECT_DOUBLE_EQ(950.0, object.humidifierRatedElectricPower().get());
  object.autosizeHumidifierRatedElectricPower();
  EXPECT_TRUE(object.isHumidifierRatedElectricPowerAutosized());

  EXPECT_TRUE(object.setReturnFan(true));
  EXPECT_TRUE(object.returnFan());
  EXPECT_TRUE(object.setReturnFanPartLoadPowerCoefficients("VariableSpeedMotor"));
  EXPECT_EQ("VariableSpeedMotor", object.returnFanPartLoadPowerCoefficients());

  EXPECT_FALSE(object.setSupplyFanPlacement("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemVAV::preheatCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemVAV::supplyFanPartLoadPowerCoefficientsValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemVAV::coolingCoilSetpointResetTypeValues().size(), 1u);
}
