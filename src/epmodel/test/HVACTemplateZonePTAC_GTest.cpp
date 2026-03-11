/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateZonePTAC.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateZonePTAC_DefaultConstructor) {
  Model model;
  HVACTemplateZonePTAC object(model);
  EXPECT_EQ(HVACTemplateZonePTAC::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateZonePTAC_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateZonePTAC object(model);

  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateDefaulted());
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRate(1.2));
  ASSERT_TRUE(object.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.coolingSupplyAirFlowRate().get());
  EXPECT_FALSE(object.isCoolingSupplyAirFlowRateAutosized());
  object.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateDefaulted());
  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setHeatingSupplyAirFlowRate(1.1));
  ASSERT_TRUE(object.heatingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.1, object.heatingSupplyAirFlowRate().get());
  object.autosizeHeatingSupplyAirFlowRate();
  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.isNoLoadSupplyAirFlowRateDefaulted());
  EXPECT_TRUE(object.setNoLoadSupplyAirFlowRate(0.5));
  ASSERT_TRUE(object.noLoadSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, object.noLoadSupplyAirFlowRate().get());
  EXPECT_FALSE(object.setNoLoadSupplyAirFlowRate(-0.1));
  object.resetNoLoadSupplyAirFlowRate();
  EXPECT_TRUE(object.isNoLoadSupplyAirFlowRateDefaulted());

  EXPECT_FALSE(object.zoneHeatingSizingFactor());
  EXPECT_TRUE(object.setZoneHeatingSizingFactor(1.2));
  ASSERT_TRUE(object.zoneHeatingSizingFactor());
  EXPECT_DOUBLE_EQ(1.2, object.zoneHeatingSizingFactor().get());
  EXPECT_FALSE(object.setZoneHeatingSizingFactor(-0.1));

  EXPECT_FALSE(object.zoneCoolingSizingFactor());
  EXPECT_TRUE(object.setZoneCoolingSizingFactor(1.1));
  ASSERT_TRUE(object.zoneCoolingSizingFactor());
  EXPECT_DOUBLE_EQ(1.1, object.zoneCoolingSizingFactor().get());
  EXPECT_FALSE(object.setZoneCoolingSizingFactor(-0.1));

  EXPECT_TRUE(object.setOutdoorAirMethod("Flow/Zone"));
  EXPECT_EQ("Flow/Zone", object.outdoorAirMethod());
  EXPECT_FALSE(object.setOutdoorAirMethod("InvalidChoice"));

  EXPECT_TRUE(object.setOutdoorAirFlowRateperPerson(0.011));
  EXPECT_DOUBLE_EQ(0.011, object.outdoorAirFlowRateperPerson());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZoneFloorArea(0.001));
  EXPECT_DOUBLE_EQ(0.001, object.outdoorAirFlowRateperZoneFloorArea());
  EXPECT_TRUE(object.setOutdoorAirFlowRateperZone(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.outdoorAirFlowRateperZone());

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());
  EXPECT_FALSE(object.setSupplyFanPlacement("InvalidChoice"));

  EXPECT_TRUE(object.setSupplyFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.supplyFanTotalEfficiency());
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(1.2));

  EXPECT_TRUE(object.setSupplyFanDeltaPressure(180.0));
  EXPECT_DOUBLE_EQ(180.0, object.supplyFanDeltaPressure());
  EXPECT_FALSE(object.setSupplyFanDeltaPressure(-1.0));

  EXPECT_TRUE(object.setSupplyFanMotorEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.supplyFanMotorEfficiency());
  EXPECT_FALSE(object.setSupplyFanMotorEfficiency(1.2));

  EXPECT_TRUE(object.setCoolingCoilType("SingleSpeedDX"));
  EXPECT_EQ("SingleSpeedDX", object.coolingCoilType());
  EXPECT_FALSE(object.setCoolingCoilType("InvalidChoice"));

  EXPECT_TRUE(object.isCoolingCoilGrossRatedTotalCapacityDefaulted());
  EXPECT_TRUE(object.isCoolingCoilGrossRatedTotalCapacityAutosized());
  EXPECT_TRUE(object.setCoolingCoilGrossRatedTotalCapacity(2500.0));
  ASSERT_TRUE(object.coolingCoilGrossRatedTotalCapacity());
  EXPECT_DOUBLE_EQ(2500.0, object.coolingCoilGrossRatedTotalCapacity().get());
  object.autosizeCoolingCoilGrossRatedTotalCapacity();
  EXPECT_TRUE(object.isCoolingCoilGrossRatedTotalCapacityAutosized());

  EXPECT_TRUE(object.isCoolingCoilGrossRatedSensibleHeatRatioDefaulted());
  EXPECT_TRUE(object.isCoolingCoilGrossRatedSensibleHeatRatioAutosized());
  EXPECT_TRUE(object.setCoolingCoilGrossRatedSensibleHeatRatio(0.75));
  ASSERT_TRUE(object.coolingCoilGrossRatedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.75, object.coolingCoilGrossRatedSensibleHeatRatio().get());
  EXPECT_FALSE(object.setCoolingCoilGrossRatedSensibleHeatRatio(0.2));
  object.autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  EXPECT_TRUE(object.isCoolingCoilGrossRatedSensibleHeatRatioAutosized());

  EXPECT_TRUE(object.setCoolingCoilGrossRatedCoolingCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, object.coolingCoilGrossRatedCoolingCOP());
  EXPECT_FALSE(object.setCoolingCoilGrossRatedCoolingCOP(0.0));

  EXPECT_TRUE(object.setHeatingCoilType("Gas"));
  EXPECT_EQ("Gas", object.heatingCoilType());
  EXPECT_FALSE(object.setHeatingCoilType("InvalidChoice"));

  EXPECT_TRUE(object.isHeatingCoilCapacityDefaulted());
  EXPECT_TRUE(object.isHeatingCoilCapacityAutosized());
  EXPECT_TRUE(object.setHeatingCoilCapacity(3500.0));
  ASSERT_TRUE(object.heatingCoilCapacity());
  EXPECT_DOUBLE_EQ(3500.0, object.heatingCoilCapacity().get());
  object.autosizeHeatingCoilCapacity();
  EXPECT_TRUE(object.isHeatingCoilCapacityAutosized());

  EXPECT_TRUE(object.setGasHeatingCoilEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.gasHeatingCoilEfficiency());
  EXPECT_FALSE(object.setGasHeatingCoilEfficiency(1.2));

  EXPECT_TRUE(object.setGasHeatingCoilParasiticElectricLoad(20.0));
  EXPECT_DOUBLE_EQ(20.0, object.gasHeatingCoilParasiticElectricLoad());
  EXPECT_FALSE(object.setGasHeatingCoilParasiticElectricLoad(-1.0));

  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("TemperatureDifference"));
  EXPECT_EQ("TemperatureDifference", object.zoneCoolingDesignSupplyAirTemperatureInputMethod());
  EXPECT_FALSE(object.setZoneCoolingDesignSupplyAirTemperatureInputMethod("InvalidChoice"));
  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperature(13.0));
  EXPECT_DOUBLE_EQ(13.0, object.zoneCoolingDesignSupplyAirTemperature());
  EXPECT_TRUE(object.setZoneCoolingDesignSupplyAirTemperatureDifference(10.5));
  EXPECT_DOUBLE_EQ(10.5, object.zoneCoolingDesignSupplyAirTemperatureDifference());

  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("SupplyAirTemperature"));
  EXPECT_EQ("SupplyAirTemperature", object.zoneHeatingDesignSupplyAirTemperatureInputMethod());
  EXPECT_FALSE(object.setZoneHeatingDesignSupplyAirTemperatureInputMethod("InvalidChoice"));
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperature(50.0));
  EXPECT_DOUBLE_EQ(50.0, object.zoneHeatingDesignSupplyAirTemperature());
  EXPECT_TRUE(object.setZoneHeatingDesignSupplyAirTemperatureDifference(30.0));
  EXPECT_DOUBLE_EQ(30.0, object.zoneHeatingDesignSupplyAirTemperatureDifference());

  EXPECT_TRUE(object.setBaseboardHeatingType("Electric"));
  EXPECT_EQ("Electric", object.baseboardHeatingType());
  EXPECT_FALSE(object.setBaseboardHeatingType("InvalidChoice"));

  EXPECT_TRUE(object.isBaseboardHeatingCapacityDefaulted());
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());
  EXPECT_TRUE(object.setBaseboardHeatingCapacity(1200.0));
  ASSERT_TRUE(object.baseboardHeatingCapacity());
  EXPECT_DOUBLE_EQ(1200.0, object.baseboardHeatingCapacity().get());
  object.autosizeBaseboardHeatingCapacity();
  EXPECT_TRUE(object.isBaseboardHeatingCapacityAutosized());

  EXPECT_TRUE(object.setCapacityControlMethod("SingleZoneVAV"));
  EXPECT_EQ("SingleZoneVAV", object.capacityControlMethod());
  EXPECT_FALSE(object.setCapacityControlMethod("InvalidChoice"));

  EXPECT_GE(HVACTemplateZonePTAC::outdoorAirMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::supplyFanPlacementValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::coolingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::heatingCoilTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::zoneCoolingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::zoneHeatingDesignSupplyAirTemperatureInputMethodValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::baseboardHeatingTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateZonePTAC::capacityControlMethodValues().size(), 1u);
}
