/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/SizingZone.hpp"
#include "../HVACComponent/ThermalZone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_SizingZone_DefaultConstructor) {
  Model model;
  ThermalZone zone(model);
  SizingZone sizingZone(model, zone);
  EXPECT_EQ(SizingZone::iddObjectType(), sizingZone.iddObject().type());
  EXPECT_EQ(zone, sizingZone.thermalZone());
}

TEST_F(EPModelFixture, API_ThermalZone_SizingZoneNonOptionalGetter) {
  Model model;
  ThermalZone zone(model);

  auto sizingZone = zone.sizingZone();
  EXPECT_EQ(zone, sizingZone.thermalZone());

  auto secondRead = zone.sizingZone();
  EXPECT_EQ(sizingZone, secondRead);
}

TEST_F(EPModelFixture, API_SizingZone_DesignSpecificationZoneAirDistributionScalarAccessors_RoundTrip) {
  Model model;
  ThermalZone zone(model);
  auto sizingZone = zone.sizingZone();

  EXPECT_TRUE(sizingZone.isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted());
  EXPECT_TRUE(sizingZone.isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted());
  EXPECT_TRUE(sizingZone.isDesignZoneSecondaryRecirculationFractionDefaulted());
  EXPECT_TRUE(sizingZone.isDesignMinimumZoneVentilationEfficiencyDefaulted());

  EXPECT_DOUBLE_EQ(1.0, sizingZone.designZoneAirDistributionEffectivenessinCoolingMode());
  EXPECT_DOUBLE_EQ(1.0, sizingZone.designZoneAirDistributionEffectivenessinHeatingMode());
  EXPECT_DOUBLE_EQ(0.0, sizingZone.designZoneSecondaryRecirculationFraction());
  EXPECT_DOUBLE_EQ(0.0, sizingZone.designMinimumZoneVentilationEfficiency());

  EXPECT_TRUE(sizingZone.setDesignZoneAirDistributionEffectivenessinCoolingMode(0.8));
  EXPECT_TRUE(sizingZone.setDesignZoneAirDistributionEffectivenessinHeatingMode(0.7));
  EXPECT_TRUE(sizingZone.setDesignZoneSecondaryRecirculationFraction(0.6));
  EXPECT_TRUE(sizingZone.setDesignMinimumZoneVentilationEfficiency(0.5));

  EXPECT_FALSE(sizingZone.isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted());
  EXPECT_FALSE(sizingZone.isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted());
  EXPECT_FALSE(sizingZone.isDesignZoneSecondaryRecirculationFractionDefaulted());
  EXPECT_FALSE(sizingZone.isDesignMinimumZoneVentilationEfficiencyDefaulted());

  EXPECT_DOUBLE_EQ(0.8, sizingZone.designZoneAirDistributionEffectivenessinCoolingMode());
  EXPECT_DOUBLE_EQ(0.7, sizingZone.designZoneAirDistributionEffectivenessinHeatingMode());
  EXPECT_DOUBLE_EQ(0.6, sizingZone.designZoneSecondaryRecirculationFraction());
  EXPECT_DOUBLE_EQ(0.5, sizingZone.designMinimumZoneVentilationEfficiency());

  sizingZone.resetDesignZoneAirDistributionEffectivenessinCoolingMode();
  sizingZone.resetDesignZoneAirDistributionEffectivenessinHeatingMode();
  sizingZone.resetDesignZoneSecondaryRecirculationFraction();
  sizingZone.resetDesignMinimumZoneVentilationEfficiency();

  EXPECT_TRUE(sizingZone.isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted());
  EXPECT_TRUE(sizingZone.isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted());
  EXPECT_TRUE(sizingZone.isDesignZoneSecondaryRecirculationFractionDefaulted());
  EXPECT_TRUE(sizingZone.isDesignMinimumZoneVentilationEfficiencyDefaulted());

  EXPECT_DOUBLE_EQ(1.0, sizingZone.designZoneAirDistributionEffectivenessinCoolingMode());
  EXPECT_DOUBLE_EQ(1.0, sizingZone.designZoneAirDistributionEffectivenessinHeatingMode());
  EXPECT_DOUBLE_EQ(0.0, sizingZone.designZoneSecondaryRecirculationFraction());
  EXPECT_DOUBLE_EQ(0.0, sizingZone.designMinimumZoneVentilationEfficiency());
}

TEST_F(EPModelFixture, API_SizingZone_SizingZoneScalarAccessors_RoundTrip) {
  Model model;
  ThermalZone zone(model);
  auto sizingZone = zone.sizingZone();

  EXPECT_EQ("DesignDay", sizingZone.coolingDesignAirFlowMethod());
  EXPECT_EQ("DesignDay", sizingZone.heatingDesignAirFlowMethod());
  EXPECT_EQ("Coincident", sizingZone.sizingOption());
  EXPECT_EQ("None", sizingZone.heatingCoilSizingMethod());
  EXPECT_DOUBLE_EQ(1.0, sizingZone.maximumHeatingCapacityToCoolingLoadSizingRatio());

  std::string coolingDesignAirFlowMethod = sizingZone.coolingDesignAirFlowMethod();
  for (const auto& value : SizingZone::coolingDesignAirFlowMethodValues()) {
    if (value != sizingZone.coolingDesignAirFlowMethod()) {
      coolingDesignAirFlowMethod = value;
      break;
    }
  }
  EXPECT_TRUE(sizingZone.setCoolingDesignAirFlowMethod(coolingDesignAirFlowMethod));
  EXPECT_TRUE(sizingZone.setCoolingDesignAirFlowRate(0.75));
  std::string heatingDesignAirFlowMethod = sizingZone.heatingDesignAirFlowMethod();
  for (const auto& value : SizingZone::heatingDesignAirFlowMethodValues()) {
    if (value != sizingZone.heatingDesignAirFlowMethod()) {
      heatingDesignAirFlowMethod = value;
      break;
    }
  }
  EXPECT_TRUE(sizingZone.setHeatingDesignAirFlowMethod(heatingDesignAirFlowMethod));
  EXPECT_TRUE(sizingZone.setHeatingDesignAirFlowRate(0.65));
  EXPECT_TRUE(sizingZone.setZoneHeatingSizingFactor(1.12));
  EXPECT_TRUE(sizingZone.setZoneCoolingSizingFactor(1.08));
  EXPECT_TRUE(sizingZone.setZoneLoadSizingMethod("Sensible And Latent Load"));
  EXPECT_TRUE(sizingZone.setZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod("SupplyAirHumidityRatio"));
  EXPECT_TRUE(sizingZone.setZoneDehumidificationDesignSupplyAirHumidityRatio(0.0077));
  EXPECT_TRUE(sizingZone.setZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod("SupplyAirHumidityRatio"));
  EXPECT_TRUE(sizingZone.setZoneHumidificationDesignSupplyAirHumidityRatio(0.0081));
  EXPECT_TRUE(sizingZone.setSizingOption("NonCoincident"));
  std::string heatingCoilSizingMethod = sizingZone.heatingCoilSizingMethod();
  for (const auto& value : SizingZone::heatingCoilSizingMethodValues()) {
    if (value != sizingZone.heatingCoilSizingMethod()) {
      heatingCoilSizingMethod = value;
      break;
    }
  }
  EXPECT_TRUE(sizingZone.setHeatingCoilSizingMethod(heatingCoilSizingMethod));
  EXPECT_TRUE(sizingZone.setMaximumHeatingCapacityToCoolingLoadSizingRatio(1.35));

  EXPECT_EQ(coolingDesignAirFlowMethod, sizingZone.coolingDesignAirFlowMethod());
  EXPECT_DOUBLE_EQ(0.75, sizingZone.coolingDesignAirFlowRate());
  EXPECT_EQ(heatingDesignAirFlowMethod, sizingZone.heatingDesignAirFlowMethod());
  EXPECT_DOUBLE_EQ(0.65, sizingZone.heatingDesignAirFlowRate());
  ASSERT_TRUE(sizingZone.zoneHeatingSizingFactor());
  EXPECT_DOUBLE_EQ(1.12, sizingZone.zoneHeatingSizingFactor().get());
  ASSERT_TRUE(sizingZone.zoneCoolingSizingFactor());
  EXPECT_DOUBLE_EQ(1.08, sizingZone.zoneCoolingSizingFactor().get());
  EXPECT_EQ("Sensible And Latent Load", sizingZone.zoneLoadSizingMethod());
  EXPECT_EQ("SupplyAirHumidityRatio", sizingZone.zoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod());
  ASSERT_TRUE(sizingZone.zoneDehumidificationDesignSupplyAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0077, sizingZone.zoneDehumidificationDesignSupplyAirHumidityRatio().get());
  EXPECT_EQ("SupplyAirHumidityRatio", sizingZone.zoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod());
  ASSERT_TRUE(sizingZone.zoneHumidificationDesignSupplyAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0081, sizingZone.zoneHumidificationDesignSupplyAirHumidityRatio().get());
  EXPECT_EQ("NonCoincident", sizingZone.sizingOption());
  EXPECT_EQ(heatingCoilSizingMethod, sizingZone.heatingCoilSizingMethod());
  EXPECT_DOUBLE_EQ(1.35, sizingZone.maximumHeatingCapacityToCoolingLoadSizingRatio());

  sizingZone.resetCoolingDesignAirFlowMethod();
  sizingZone.resetCoolingDesignAirFlowRate();
  sizingZone.resetHeatingDesignAirFlowMethod();
  sizingZone.resetHeatingDesignAirFlowRate();
  sizingZone.resetZoneHeatingSizingFactor();
  sizingZone.resetZoneCoolingSizingFactor();
  sizingZone.resetZoneDehumidificationDesignSupplyAirHumidityRatio();
  sizingZone.resetZoneHumidificationDesignSupplyAirHumidityRatio();

  EXPECT_TRUE(sizingZone.isCoolingDesignAirFlowMethodDefaulted());
  EXPECT_TRUE(sizingZone.isCoolingDesignAirFlowRateDefaulted());
  EXPECT_TRUE(sizingZone.isHeatingDesignAirFlowMethodDefaulted());
  EXPECT_TRUE(sizingZone.isHeatingDesignAirFlowRateDefaulted());
  EXPECT_FALSE(sizingZone.zoneHeatingSizingFactor());
  EXPECT_FALSE(sizingZone.zoneCoolingSizingFactor());
  EXPECT_FALSE(sizingZone.zoneDehumidificationDesignSupplyAirHumidityRatio());
  EXPECT_FALSE(sizingZone.zoneHumidificationDesignSupplyAirHumidityRatio());
}
