/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateZonePTHP.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZonePTHP_DefaultConstructor) {
  Model model;
  HVACTemplateZonePTHP object(model);
  EXPECT_EQ(HVACTemplateZonePTHP::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZonePTHP_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZonePTHP object(model);

  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRate(1.2));
  ASSERT_TRUE(object.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.coolingSupplyAirFlowRate().get());
  object.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setHeatingSupplyAirFlowRate(1.1));
  ASSERT_TRUE(object.heatingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.1, object.heatingSupplyAirFlowRate().get());
  object.autosizeHeatingSupplyAirFlowRate();
  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.setNoLoadSupplyAirFlowRate(0.5));
  ASSERT_TRUE(object.noLoadSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, object.noLoadSupplyAirFlowRate().get());
  EXPECT_FALSE(object.setNoLoadSupplyAirFlowRate(-0.1));

  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperPerson(0.011));
  EXPECT_DOUBLE_EQ(0.011, object.outdoorAirFlowRateperPerson());

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());
  EXPECT_TRUE(object.setSupplyFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.supplyFanTotalEfficiency());

  EXPECT_TRUE(object.setCoolingCoilType("SingleSpeedDX"));
  EXPECT_EQ("SingleSpeedDX", object.coolingCoilType());
  EXPECT_TRUE(object.isCoolingCoilGrossRatedTotalCapacityAutosized());
  EXPECT_TRUE(object.setCoolingCoilGrossRatedTotalCapacity(2500.0));
  ASSERT_TRUE(object.coolingCoilGrossRatedTotalCapacity());
  EXPECT_DOUBLE_EQ(2500.0, object.coolingCoilGrossRatedTotalCapacity().get());
  EXPECT_TRUE(object.setCoolingCoilGrossRatedCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, object.coolingCoilGrossRatedCOP());

  EXPECT_TRUE(object.setHeatPumpHeatingCoilType("SingleSpeedDXHeatPump"));
  EXPECT_EQ("SingleSpeedDXHeatPump", object.heatPumpHeatingCoilType());
  EXPECT_TRUE(object.isHeatPumpHeatingCoilGrossRatedCapacityAutosized());
  EXPECT_TRUE(object.setHeatPumpHeatingCoilGrossRatedCapacity(3500.0));
  ASSERT_TRUE(object.heatPumpHeatingCoilGrossRatedCapacity());
  EXPECT_DOUBLE_EQ(3500.0, object.heatPumpHeatingCoilGrossRatedCapacity().get());
  EXPECT_TRUE(object.setHeatPumpHeatingCoilGrossRatedCOP(3.0));
  EXPECT_DOUBLE_EQ(3.0, object.heatPumpHeatingCoilGrossRatedCOP());

  EXPECT_TRUE(object.setHeatPumpDefrostStrategy("Resistive"));
  EXPECT_EQ("Resistive", object.heatPumpDefrostStrategy());
  EXPECT_TRUE(object.setHeatPumpDefrostControl("OnDemand"));
  EXPECT_EQ("OnDemand", object.heatPumpDefrostControl());
  EXPECT_TRUE(object.setHeatPumpDefrostTimePeriodFraction(0.08));
  EXPECT_DOUBLE_EQ(0.08, object.heatPumpDefrostTimePeriodFraction());

  EXPECT_TRUE(object.setSupplementalHeatingCoilType("Gas"));
  EXPECT_EQ("Gas", object.supplementalHeatingCoilType());
  EXPECT_TRUE(object.isSupplementalHeatingCoilCapacityAutosized());
  EXPECT_TRUE(object.setSupplementalHeatingCoilCapacity(1200.0));
  ASSERT_TRUE(object.supplementalHeatingCoilCapacity());
  EXPECT_DOUBLE_EQ(1200.0, object.supplementalHeatingCoilCapacity().get());
  EXPECT_TRUE(object.setSupplementalGasHeatingCoilEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.supplementalGasHeatingCoilEfficiency());

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
  EXPECT_EQ("SupplyAirTemperature", object.zoneHeatingDesignSupplyAirTemperatureInputMethod());

  EXPECT_TRUE(object.setBaseboardHeatingType("Electric"));
  EXPECT_EQ("Electric", object.baseboardHeatingType());
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(1200.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(1200.0, object.baseboardHeatingCapacity().get());

  EXPECT_TRUE(object.setCapacityControlMethod("SingleZoneVAV"));
  EXPECT_EQ("SingleZoneVAV", object.capacityControlMethod());

  EXPECT_GE(HVACTemplateZonePTHP::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTHP::supplyFanPlacementValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTHP::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTHP::heatPumpHeatingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTHP::heatPumpDefrostStrategyValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTHP::heatPumpDefrostControlValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTHP::supplementalHeatingCoilTypeValues().size(), 1u);
}
