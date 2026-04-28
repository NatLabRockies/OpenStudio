/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateZoneVAVFanPowered.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZoneVAVFanPowered_DefaultConstructor) {
  Model model;
  HVACTemplateZoneVAVFanPowered object(model);
  EXPECT_EQ(HVACTemplateZoneVAVFanPowered::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZoneVAVFanPowered_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZoneVAVFanPowered object(model);

  EXPECT_TRUE(object.isPrimarySupplyAirMaximumFlowRateAutosized());
  EXPECT_TRUE(object.setPrimarySupplyAirMaximumFlowRate(1.2));
  ASSERT_TRUE(object.primarySupplyAirMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.primarySupplyAirMaximumFlowRate().get());
  EXPECT_FALSE(object.isPrimarySupplyAirMaximumFlowRateAutosized());
  object.autosizePrimarySupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isPrimarySupplyAirMaximumFlowRateAutosized());

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

  EXPECT_TRUE(object.isPrimarySupplyAirMinimumFlowFractionAutosized());
  EXPECT_TRUE(object.setPrimarySupplyAirMinimumFlowFraction(0.4));
  ASSERT_TRUE(object.primarySupplyAirMinimumFlowFraction());
  EXPECT_DOUBLE_EQ(0.4, object.primarySupplyAirMinimumFlowFraction().get());
  EXPECT_FALSE(object.setPrimarySupplyAirMinimumFlowFraction(1.2));
  object.autosizePrimarySupplyAirMinimumFlowFraction();
  EXPECT_TRUE(object.isPrimarySupplyAirMinimumFlowFractionAutosized());

  EXPECT_TRUE(object.isSecondarySupplyAirMaximumFlowRateAutosized());
  EXPECT_TRUE(object.setSecondarySupplyAirMaximumFlowRate(0.8));
  ASSERT_TRUE(object.secondarySupplyAirMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.8, object.secondarySupplyAirMaximumFlowRate().get());
  object.autosizeSecondarySupplyAirMaximumFlowRate();
  EXPECT_TRUE(object.isSecondarySupplyAirMaximumFlowRateAutosized());

  EXPECT_TRUE(object.setFlowType("Parallel"));
  EXPECT_EQ("Parallel", object.flowType());
  EXPECT_FALSE(object.setFlowType("InvalidChoice"));

  EXPECT_TRUE(object.isParallelFanOnFlowFractionAutosized());
  EXPECT_TRUE(object.setParallelFanOnFlowFraction(0.35));
  ASSERT_TRUE(object.parallelFanOnFlowFraction());
  EXPECT_DOUBLE_EQ(0.35, object.parallelFanOnFlowFraction().get());
  object.autosizeParallelFanOnFlowFraction();
  EXPECT_TRUE(object.isParallelFanOnFlowFractionAutosized());

  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_FALSE(object.setOutdoorAirMethod("InvalidChoice"));

  EXPECT_TRUE(object.setOutdoorAirFlowRateperPerson(0.011));
  EXPECT_DOUBLE_EQ(0.011, object.outdoorAirFlowRateperPerson());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZoneFloorArea(0.001));
  EXPECT_DOUBLE_EQ(0.001, object.outdoorAirFlowRateperZoneFloorArea());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZone(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.outdoorAirFlowRateperZone());

  EXPECT_TRUE(object.setReheatCoilType("Electric"));
  EXPECT_EQ("Electric", object.reheatCoilType());
  EXPECT_FALSE(object.setReheatCoilType("InvalidChoice"));

  EXPECT_TRUE(object.setFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.fanTotalEfficiency());
  EXPECT_FALSE(object.setFanTotalEfficiency(1.2));

  EXPECT_TRUE(object.setFanDeltaPressure(800.0));
  EXPECT_DOUBLE_EQ(800.0, object.fanDeltaPressure());
  EXPECT_FALSE(object.setFanDeltaPressure(-1.0));

  EXPECT_TRUE(object.setFanMotorEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.fanMotorEfficiency());
  EXPECT_FALSE(object.setFanMotorEfficiency(1.2));

  EXPECT_TRUE(object.setBaseboardHeatingType("Electric"));
  EXPECT_EQ("Electric", object.baseboardHeatingType());
  EXPECT_FALSE(object.setBaseboardHeatingType("InvalidChoice"));

  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(1500.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(1500.0, object.baseboardHeatingCapacity().get());
  object.autosizeBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
  EXPECT_EQ("SupplyAirTemperature", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());
  EXPECT_FALSE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("InvalidChoice"));

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperature(12.8));
  EXPECT_DOUBLE_EQ(12.8, object.zoneCoolingDesignSupplyAirTemperature());

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureDifference(11.11));
  EXPECT_DOUBLE_EQ(11.11, object.zoneCoolingDesignSupplyAirTemperatureDifference());

  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneHeatingDesignSupplyAirTemperatureInputMethod());
  EXPECT_FALSE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("InvalidChoice"));

  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperature(50.0));
  EXPECT_DOUBLE_EQ(50.0, object.zoneHeatingDesignSupplyAirTemperature());

  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureDifference(30.0));
  EXPECT_DOUBLE_EQ(30.0, object.zoneHeatingDesignSupplyAirTemperatureDifference());

  EXPECT_GE(HVACTemplateZoneVAVFanPowered::flowTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAVFanPowered::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAVFanPowered::reheatCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAVFanPowered::baseboardHeatingTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAVFanPowered::zoneCoolingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZoneVAVFanPowered::zoneHeatingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
}
