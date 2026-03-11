/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateZoneVRF.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneVRF_DefaultConstructor) {
  Model model;
  HVACTemplateZoneVRF object(model);
  EXPECT_EQ(HVACTemplateZoneVRF::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneVRF_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneVRF object(model);

  EXPECT_TRUE(object.setZoneHeatingSizingFactor(1.2));
  ASSERT_TRUE(object.zoneHeatingSizingFactor());
  EXPECT_DOUBLE_EQ(1.2, object.zoneHeatingSizingFactor().get());

  EXPECT_TRUE(object.setRatedTotalHeatingCapacitySizingRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, object.ratedTotalHeatingCapacitySizingRatio());
  EXPECT_FALSE(object.setRatedTotalHeatingCapacitySizingRatio(0.5));

  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRate(0.45));
  ASSERT_TRUE(object.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.45, object.coolingSupplyAirFlowRate().get());
  object.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_FALSE(object.setOutdoorAirMethod("InvalidChoice"));

  EXPECT_TRUE(object.setSupplyAirFanplacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyAirFanplacement());
  EXPECT_TRUE(object.setSupplyFanTotalEfficiency(0.8));
  EXPECT_DOUBLE_EQ(0.8, object.supplyFanTotalEfficiency());
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(1.2));

  EXPECT_TRUE(object.setCoolingCoilGrossRatedSensibleHeatRatio(0.75));
  ASSERT_TRUE(object.coolingCoilGrossRatedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.75, object.coolingCoilGrossRatedSensibleHeatRatio().get());
  EXPECT_FALSE(object.setCoolingCoilGrossRatedSensibleHeatRatio(0.4));

  EXPECT_TRUE(object.setZoneTerminalUnitOnParasiticElectricEnergyUse(5.0));
  EXPECT_DOUBLE_EQ(5.0, object.zoneTerminalUnitOnParasiticElectricEnergyUse());

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());

  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(2500.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(2500.0, object.baseboardHeatingCapacity().get());

  EXPECT_GE(HVACTemplateZoneVRF::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVRF::supplyAirFanplacementValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVRF::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVRF::heatPumpHeatingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVRF::zoneCoolingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVRF::zoneHeatingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVRF::baseboardHeatingTypeValues().size(), 1u);
}
