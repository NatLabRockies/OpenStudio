/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateZoneWaterToAirHeatPump.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneWaterToAirHeatPump_DefaultConstructor) {
  Model model;
  HVACTemplateZoneWaterToAirHeatPump object(model);
  EXPECT_EQ(HVACTemplateZoneWaterToAirHeatPump::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneWaterToAirHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneWaterToAirHeatPump object(model);

  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRate(0.6));
  ASSERT_TRUE(object.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.6, object.coolingSupplyAirFlowRate().get());
  object.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.setNoLoadSupplyAirFlowRate(0.0));
  ASSERT_TRUE(object.noLoadSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.0, object.noLoadSupplyAirFlowRate().get());
  EXPECT_FALSE(object.setNoLoadSupplyAirFlowRate(-0.1));

  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());

  EXPECT_TRUE(object.setCoolingCoilType("Coil:Cooling:WaterToAirHeatPump:EquationFit"));
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:EquationFit", object.coolingCoilType());

  EXPECT_TRUE(object.isSupplementalHeatingCoilCapacityAutosized());
  EXPECT_TRUE(object.setSupplementalHeatingCoilCapacity(1000.0));
  ASSERT_TRUE(object.supplementalHeatingCoilCapacity());
  EXPECT_DOUBLE_EQ(1000.0, object.supplementalHeatingCoilCapacity().get());

  EXPECT_TRUE(object.setMaximumCyclingRate(3.0));
  EXPECT_DOUBLE_EQ(3.0, object.maximumCyclingRate());
  EXPECT_FALSE(object.setMaximumCyclingRate(6.0));

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());

  EXPECT_TRUE(object.setHeatPumpCoilWaterFlowMode("Cycling"));
  EXPECT_EQ("Cycling", object.heatPumpCoilWaterFlowMode());

  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(750.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(750.0, object.baseboardHeatingCapacity().get());

  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::supplyFanPlacementValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::heatPumpHeatingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::zoneCoolingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::zoneHeatingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::heatPumpCoilWaterFlowModeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneWaterToAirHeatPump::baseboardHeatingTypeValues().size(), 1u);
}
