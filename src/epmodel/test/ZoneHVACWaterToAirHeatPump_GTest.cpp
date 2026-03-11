/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACWaterToAirHeatPump.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_DefaultConstructor) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_FALSE(wahp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(wahp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(wahp.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(wahp.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(wahp.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(wahp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(wahp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_TRUE(wahp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  EXPECT_TRUE(wahp.isFanPlacementDefaulted());
  EXPECT_TRUE(wahp.isHeatPumpCoilWaterFlowModeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_TRUE(wahp.setSupplyAirFlowRateDuringCoolingOperation(0.52));
  ASSERT_TRUE(wahp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.52, wahp.supplyAirFlowRateDuringCoolingOperation().get());
  wahp.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(wahp.setSupplyAirFlowRateDuringHeatingOperation(0.48));
  ASSERT_TRUE(wahp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.48, wahp.supplyAirFlowRateDuringHeatingOperation().get());
  wahp.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(wahp.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.16));
  ASSERT_TRUE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.16, wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  wahp.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  wahp.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(wahp.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(wahp.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.25));
  wahp.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.22));
  wahp.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.08));
  wahp.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(wahp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  wahp.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(wahp.setMaximumSupplyAirTemperaturefromSupplementalHeater(55.0));
  ASSERT_TRUE(wahp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(55.0, wahp.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  wahp.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(wahp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(wahp.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, wahp.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  wahp.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(wahp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(wahp.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", wahp.fanPlacement());
  wahp.resetFanPlacement();
  EXPECT_TRUE(wahp.isFanPlacementDefaulted());

  EXPECT_TRUE(wahp.setHeatPumpCoilWaterFlowMode("Cycling"));
  EXPECT_EQ("Cycling", wahp.heatPumpCoilWaterFlowMode());
  wahp.resetHeatPumpCoilWaterFlowMode();
  EXPECT_TRUE(wahp.isHeatPumpCoilWaterFlowModeDefaulted());

  EXPECT_TRUE(wahp.setDXHeatingCoilSizingRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, wahp.dXHeatingCoilSizingRatio());
}
