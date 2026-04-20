/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateZoneUnitary.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneUnitary_DefaultConstructor) {
  Model model;
  HVACTemplateZoneUnitary object(model);
  EXPECT_EQ(HVACTemplateZoneUnitary::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneUnitary_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneUnitary object(model);

  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateDefaulted());
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateAutosized());
  EXPECT_TRUE(object.setSupplyAirMaximumFlowRate(1.2));
  ASSERT_TRUE(object.supplyAirMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.supplyAirMaximumFlowRate().get());
  EXPECT_FALSE(object.isSupplyAirMaximumFlowRateAutosized());
  object.autosizeSupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateAutosized());
  object.resetSupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateDefaulted());

  EXPECT_FALSE(object.zoneHeatingSizingFactor());
  EXPECT_TRUE(object.setZoneHeatingSizingFactor(1.1));
  ASSERT_TRUE(object.zoneHeatingSizingFactor());
  EXPECT_DOUBLE_EQ(1.1, object.zoneHeatingSizingFactor().get());
  object.resetZoneHeatingSizingFactor();
  EXPECT_FALSE(object.zoneHeatingSizingFactor());
  EXPECT_FALSE(object.setZoneHeatingSizingFactor(-0.1));

  EXPECT_FALSE(object.zoneCoolingSizingFactor());
  EXPECT_TRUE(object.setZoneCoolingSizingFactor(1.2));
  ASSERT_TRUE(object.zoneCoolingSizingFactor());
  EXPECT_DOUBLE_EQ(1.2, object.zoneCoolingSizingFactor().get());
  object.resetZoneCoolingSizingFactor();
  EXPECT_FALSE(object.zoneCoolingSizingFactor());
  EXPECT_FALSE(object.setZoneCoolingSizingFactor(-0.1));

  EXPECT_TRUE(object.isOutdoorAirMethodDefaulted());
  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_FALSE(object.isOutdoorAirMethodDefaulted());
  EXPECT_FALSE(object.setOutdoorAirMethod("InvalidChoice"));
  object.resetOutdoorAirMethod();
  EXPECT_TRUE(object.isOutdoorAirMethodDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperPersonDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperPerson(0.011));
  EXPECT_DOUBLE_EQ(0.011, object.outdoorAirFlowRateperPerson());
  object.resetOutdoorAirFlowRateperPerson();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperPersonDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneFloorAreaDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZoneFloorArea(0.001));
  EXPECT_DOUBLE_EQ(0.001, object.outdoorAirFlowRateperZoneFloorArea());
  object.resetOutdoorAirFlowRateperZoneFloorArea();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneFloorAreaDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZone(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.outdoorAirFlowRateperZone());
  object.resetOutdoorAirFlowRateperZone();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperZoneDefaulted());

  EXPECT_TRUE(object.isBaseboardHeatingTypeDefaulted());
  EXPECT_TRUE(object.setBaseboardHeatingType("Electric"));
  EXPECT_EQ("Electric", object.baseboardHeatingType());
  EXPECT_FALSE(object.setBaseboardHeatingType("InvalidChoice"));
  object.resetBaseboardHeatingType();
  EXPECT_TRUE(object.isBaseboardHeatingTypeDefaulted());

  EXPECT_TRUE(object.isBaseboardHeatingCapacityDefaulted());
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(7500.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(7500.0, object.baseboardHeatingCapacity().get());
  EXPECT_FALSE(object.isBaseboardHeatingCapacityAutosized());
  object.autosizeBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  object.resetBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityDefaulted());

  EXPECT_TRUE(object.isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted());
  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
  EXPECT_EQ("SupplyAirTemperature", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());
  EXPECT_FALSE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("InvalidChoice"));
  object.resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  EXPECT_TRUE(object.isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted());

  EXPECT_TRUE(object.isZoneCoolingDesignSupplyAirTemperatureDefaulted());
  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperature(13.0));
  EXPECT_DOUBLE_EQ(13.0, object.zoneCoolingDesignSupplyAirTemperature());
  object.resetZoneCoolingDesignSupplyAirTemperature();
  EXPECT_TRUE(object.isZoneCoolingDesignSupplyAirTemperatureDefaulted());

  EXPECT_TRUE(object.isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted());
  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureDifference(10.5));
  EXPECT_DOUBLE_EQ(10.5, object.zoneCoolingDesignSupplyAirTemperatureDifference());
  object.resetZoneCoolingDesignSupplyAirTemperatureDifference();
  EXPECT_TRUE(object.isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted());

  EXPECT_TRUE(object.isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted());
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneHeatingDesignSupplyAirTemperatureInputMethod());
  EXPECT_FALSE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("InvalidChoice"));
  object.resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  EXPECT_TRUE(object.isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted());

  EXPECT_TRUE(object.isZoneHeatingDesignSupplyAirTemperatureDefaulted());
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperature(52.0));
  EXPECT_DOUBLE_EQ(52.0, object.zoneHeatingDesignSupplyAirTemperature());
  object.resetZoneHeatingDesignSupplyAirTemperature();
  EXPECT_TRUE(object.isZoneHeatingDesignSupplyAirTemperatureDefaulted());

  EXPECT_TRUE(object.isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted());
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureDifference(28.0));
  EXPECT_DOUBLE_EQ(28.0, object.zoneHeatingDesignSupplyAirTemperatureDifference());
  object.resetZoneHeatingDesignSupplyAirTemperatureDifference();
  EXPECT_TRUE(object.isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted());

  EXPECT_GE(HVACTemplateZoneUnitary::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneUnitary::baseboardHeatingTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
}
