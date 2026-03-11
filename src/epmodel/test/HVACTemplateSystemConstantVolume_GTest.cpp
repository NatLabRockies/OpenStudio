/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateSystemConstantVolume.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemConstantVolume_DefaultConstructor) {
  Model model;
  HVACTemplateSystemConstantVolume object(model);
  EXPECT_EQ(HVACTemplateSystemConstantVolume::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemConstantVolume_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemConstantVolume object(model);

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());

  EXPECT_TRUE(object.setSupplyFanMaximumFlowRate(1.75));
  ASSERT_TRUE(object.supplyFanMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.75, object.supplyFanMaximumFlowRate().get());
  EXPECT_FALSE(object.isSupplyFanMaximumFlowRateAutosized());
  object.autosizeSupplyFanMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyFanMaximumFlowRateAutosized());
  object.resetSupplyFanMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyFanMaximumFlowRateDefaulted());

  EXPECT_TRUE(object.setCoolingCoilType("ChilledWater"));
  EXPECT_EQ("ChilledWater", object.coolingCoilType());
  EXPECT_TRUE(object.setCoolingCoilDesignSetpointTemperature(13.2));
  EXPECT_DOUBLE_EQ(13.2, object.coolingCoilDesignSetpointTemperature());

  EXPECT_TRUE(object.setHeatingCoilCapacity(45000.0));
  ASSERT_TRUE(object.heatingCoilCapacity());
  EXPECT_DOUBLE_EQ(45000.0, object.heatingCoilCapacity().get());
  object.autosizeHeatingCoilCapacity();
  EXPECT_TRUE(object.isHeatingCoilCapacityAutosized());

  EXPECT_TRUE(object.setMaximumOutdoorAirFlowRate(0.7));
  ASSERT_TRUE(object.maximumOutdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.7, object.maximumOutdoorAirFlowRate().get());
  object.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(object.isMaximumOutdoorAirFlowRateAutosized());

  EXPECT_TRUE(object.setEconomizerUpperTemperatureLimit(26.0));
  ASSERT_TRUE(object.economizerUpperTemperatureLimit());
  EXPECT_DOUBLE_EQ(26.0, object.economizerUpperTemperatureLimit().get());
  object.resetEconomizerUpperTemperatureLimit();
  EXPECT_FALSE(object.economizerUpperTemperatureLimit());

  EXPECT_TRUE(object.setHumidifierRatedElectricPower(800.0));
  ASSERT_TRUE(object.humidifierRatedElectricPower());
  EXPECT_DOUBLE_EQ(800.0, object.humidifierRatedElectricPower().get());
  object.autosizeHumidifierRatedElectricPower();
  EXPECT_TRUE(object.isHumidifierRatedElectricPowerAutosized());

  EXPECT_TRUE(object.setReturnFan(true));
  EXPECT_TRUE(object.returnFan());
  EXPECT_TRUE(object.setReturnFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.returnFanTotalEfficiency());
  object.resetReturnFan();
  EXPECT_TRUE(object.isReturnFanDefaulted());

  EXPECT_FALSE(object.setSupplyFanPlacement("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanMaximumFlowRate(0.0));
  EXPECT_FALSE(object.setReturnFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemConstantVolume::supplyFanPlacementValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemConstantVolume::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemConstantVolume::nightCycleControlValues().size(), 1u);
}
