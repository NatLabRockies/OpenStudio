/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateSystemDedicatedOutdoorAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemDedicatedOutdoorAir_DefaultConstructor) {
  Model model;
  HVACTemplateSystemDedicatedOutdoorAir object(model);
  EXPECT_EQ(HVACTemplateSystemDedicatedOutdoorAir::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemDedicatedOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemDedicatedOutdoorAir object(model);

  EXPECT_TRUE(object.setAirOutletType("DirectIntoZone"));
  EXPECT_EQ("DirectIntoZone", object.airOutletType());

  EXPECT_TRUE(object.setSupplyFanFlowRate(1.1));
  ASSERT_TRUE(object.supplyFanFlowRate());
  EXPECT_DOUBLE_EQ(1.1, object.supplyFanFlowRate().get());
  EXPECT_FALSE(object.isSupplyFanFlowRateAutosized());
  object.autosizeSupplyFanFlowRate();
  EXPECT_TRUE(object.isSupplyFanFlowRateAutosized());
  object.resetSupplyFanFlowRate();
  EXPECT_TRUE(object.isSupplyFanFlowRateDefaulted());

  EXPECT_TRUE(object.setCoolingCoilType("TwoSpeedDX"));
  EXPECT_EQ("TwoSpeedDX", object.coolingCoilType());
  EXPECT_TRUE(object.setDXCoolingCoilGrossRatedTotalCapacity(5000.0));
  ASSERT_TRUE(object.dXCoolingCoilGrossRatedTotalCapacity());
  EXPECT_DOUBLE_EQ(5000.0, object.dXCoolingCoilGrossRatedTotalCapacity().get());
  object.autosizeDXCoolingCoilGrossRatedTotalCapacity();
  EXPECT_TRUE(object.isDXCoolingCoilGrossRatedTotalCapacityAutosized());

  EXPECT_TRUE(object.setHeatingCoilType("Gas"));
  EXPECT_EQ("Gas", object.heatingCoilType());
  EXPECT_TRUE(object.setGasHeatingCoilEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, object.gasHeatingCoilEfficiency());

  EXPECT_TRUE(object.setHumidifierRatedElectricPower(800.0));
  ASSERT_TRUE(object.humidifierRatedElectricPower());
  EXPECT_DOUBLE_EQ(800.0, object.humidifierRatedElectricPower().get());
  object.autosizeHumidifierRatedElectricPower();
  EXPECT_TRUE(object.isHumidifierRatedElectricPowerAutosized());

  EXPECT_FALSE(object.setAirOutletType("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemDedicatedOutdoorAir::airOutletTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemDedicatedOutdoorAir::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemDedicatedOutdoorAir::humidifierTypeValues().size(), 1u);
}
