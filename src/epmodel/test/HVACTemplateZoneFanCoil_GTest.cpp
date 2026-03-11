/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateZoneFanCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneFanCoil_DefaultConstructor) {
  Model model;
  HVACTemplateZoneFanCoil object(model);
  EXPECT_EQ(HVACTemplateZoneFanCoil::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneFanCoil_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneFanCoil object(model);

  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateDefaulted());
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateAutosized());
  EXPECT_TRUE(object.setSupplyAirMaximumFlowRate(1.1));
  ASSERT_TRUE(object.supplyAirMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.1, object.supplyAirMaximumFlowRate().get());
  EXPECT_FALSE(object.isSupplyAirMaximumFlowRateAutosized());
  object.autosizeSupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateAutosized());
  object.resetSupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyAirMaximumFlowRateDefaulted());

  EXPECT_FALSE(object.zoneHeatingSizingFactor());
  EXPECT_TRUE(object.setZoneHeatingSizingFactor(1.1));
  ASSERT_TRUE(object.zoneHeatingSizingFactor());
  EXPECT_DOUBLE_EQ(1.1, object.zoneHeatingSizingFactor().get());
  EXPECT_FALSE(object.setZoneHeatingSizingFactor(-0.1));

  EXPECT_FALSE(object.zoneCoolingSizingFactor());
  EXPECT_TRUE(object.setZoneCoolingSizingFactor(1.2));
  ASSERT_TRUE(object.zoneCoolingSizingFactor());
  EXPECT_DOUBLE_EQ(1.2, object.zoneCoolingSizingFactor().get());
  EXPECT_FALSE(object.setZoneCoolingSizingFactor(-0.1));

  EXPECT_TRUE(object.isOutdoorAirMethodDefaulted());
  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_FALSE(object.setOutdoorAirMethod("InvalidChoice"));
  object.resetOutdoorAirMethod();
  EXPECT_TRUE(object.isOutdoorAirMethodDefaulted());

  EXPECT_TRUE(object.isOutdoorAirFlowRateperPersonDefaulted());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperPerson(0.012));
  EXPECT_DOUBLE_EQ(0.012, object.outdoorAirFlowRateperPerson());
  object.resetOutdoorAirFlowRateperPerson();
  EXPECT_TRUE(object.isOutdoorAirFlowRateperPersonDefaulted());

  EXPECT_TRUE(object.setSupplyFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.supplyFanTotalEfficiency());
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(1.2));

  EXPECT_TRUE(object.setSupplyFanDeltaPressure(180.0));
  EXPECT_DOUBLE_EQ(180.0, object.supplyFanDeltaPressure());
  EXPECT_FALSE(object.setSupplyFanDeltaPressure(-1.0));

  EXPECT_TRUE(object.setSupplyFanMotorEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.supplyFanMotorEfficiency());
  EXPECT_FALSE(object.setSupplyFanMotorEfficiency(1.2));

  EXPECT_TRUE(object.setSupplyFanMotorinAirStreamFraction(0.9));
  EXPECT_DOUBLE_EQ(0.9, object.supplyFanMotorinAirStreamFraction());
  EXPECT_FALSE(object.setSupplyFanMotorinAirStreamFraction(1.2));

  EXPECT_TRUE(object.setCoolingCoilType("ChilledWater"));
  EXPECT_EQ("ChilledWater", object.coolingCoilType());
  EXPECT_FALSE(object.setCoolingCoilType("InvalidChoice"));

  EXPECT_TRUE(object.setHeatingCoilType("HotWater"));
  EXPECT_EQ("HotWater", object.heatingCoilType());
  EXPECT_FALSE(object.setHeatingCoilType("InvalidChoice"));

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());
  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureDifference(10.5));
  EXPECT_DOUBLE_EQ(10.5, object.zoneCoolingDesignSupplyAirTemperatureDifference());

  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneHeatingDesignSupplyAirTemperatureInputMethod());
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureDifference(28.0));
  EXPECT_DOUBLE_EQ(28.0, object.zoneHeatingDesignSupplyAirTemperatureDifference());

  EXPECT_TRUE(object.setCapacityControlMethod("CyclingFan"));
  ASSERT_TRUE(object.capacityControlMethod());
  EXPECT_EQ("CyclingFan", object.capacityControlMethod().get());
  EXPECT_FALSE(object.setCapacityControlMethod("InvalidChoice"));
  object.resetCapacityControlMethod();

  EXPECT_TRUE(object.setLowSpeedSupplyAirFlowRatio(0.4));
  EXPECT_DOUBLE_EQ(0.4, object.lowSpeedSupplyAirFlowRatio());
  EXPECT_FALSE(object.setLowSpeedSupplyAirFlowRatio(0.0));

  EXPECT_TRUE(object.setMediumSpeedSupplyAirFlowRatio(0.7));
  EXPECT_DOUBLE_EQ(0.7, object.mediumSpeedSupplyAirFlowRatio());
  EXPECT_FALSE(object.setMediumSpeedSupplyAirFlowRatio(0.0));

  EXPECT_TRUE(object.isBaseboardHeatingTypeDefaulted());
  EXPECT_TRUE(object.setBaseboardHeatingType("Electric"));
  EXPECT_EQ("Electric", object.baseboardHeatingType());
  EXPECT_FALSE(object.setBaseboardHeatingType("InvalidChoice"));

  EXPECT_TRUE(object.isBaseboardHeatingCapacityDefaulted());
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(7000.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(7000.0, object.baseboardHeatingCapacity().get());
  EXPECT_FALSE(object.isBaseboardHeatingCapacityAutosized());
  object.autosizeBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());

  EXPECT_GE(HVACTemplateZoneFanCoil::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneFanCoil::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneFanCoil::heatingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneFanCoil::zoneCoolingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneFanCoil::zoneHeatingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneFanCoil::capacityControlMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneFanCoil::baseboardHeatingTypeValues().size(), 1u);
}
