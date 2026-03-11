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
