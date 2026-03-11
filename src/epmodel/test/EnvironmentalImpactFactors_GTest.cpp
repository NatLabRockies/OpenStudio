/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnvironmentalImpactFactors.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnvironmentalImpactFactors_DefaultConstructor) {
  Model model;
  EnvironmentalImpactFactors environmentalImpactFactors(model);

  EXPECT_EQ(EnvironmentalImpactFactors::iddObjectType(), environmentalImpactFactors.iddObject().type());
  EXPECT_DOUBLE_EQ(0.3, environmentalImpactFactors.districtHeatingWaterEfficiency());
  EXPECT_DOUBLE_EQ(3.0, environmentalImpactFactors.districtCoolingCOP());
  EXPECT_DOUBLE_EQ(0.25, environmentalImpactFactors.districtHeatingSteamConversionEfficiency());
  EXPECT_DOUBLE_EQ(80.7272, environmentalImpactFactors.totalCarbonEquivalentEmissionFactorFromN2O());
  EXPECT_DOUBLE_EQ(6.2727, environmentalImpactFactors.totalCarbonEquivalentEmissionFactorFromCH4());
  EXPECT_DOUBLE_EQ(0.2727, environmentalImpactFactors.totalCarbonEquivalentEmissionFactorFromCO2());

  // Preserved deprecated compatibility aliases.
  EXPECT_DOUBLE_EQ(0.3, environmentalImpactFactors.districtHeatingEfficiency());
  EXPECT_DOUBLE_EQ(0.25, environmentalImpactFactors.steamConversionEfficiency());
}

TEST_F(EPModelFixture, EnvironmentalImpactFactors_ScalarAccessors_RoundTrip) {
  Model model;
  EnvironmentalImpactFactors environmentalImpactFactors(model);

  EXPECT_TRUE(environmentalImpactFactors.setDistrictHeatingWaterEfficiency(0.35));
  EXPECT_TRUE(environmentalImpactFactors.setDistrictCoolingCOP(3.3));
  EXPECT_TRUE(environmentalImpactFactors.setDistrictHeatingSteamConversionEfficiency(0.27));
  EXPECT_TRUE(environmentalImpactFactors.setTotalCarbonEquivalentEmissionFactorFromN2O(79.2));
  EXPECT_TRUE(environmentalImpactFactors.setTotalCarbonEquivalentEmissionFactorFromCH4(6.1));
  EXPECT_TRUE(environmentalImpactFactors.setTotalCarbonEquivalentEmissionFactorFromCO2(0.31));

  EXPECT_DOUBLE_EQ(0.35, environmentalImpactFactors.districtHeatingWaterEfficiency());
  EXPECT_DOUBLE_EQ(3.3, environmentalImpactFactors.districtCoolingCOP());
  EXPECT_DOUBLE_EQ(0.27, environmentalImpactFactors.districtHeatingSteamConversionEfficiency());
  EXPECT_DOUBLE_EQ(79.2, environmentalImpactFactors.totalCarbonEquivalentEmissionFactorFromN2O());
  EXPECT_DOUBLE_EQ(6.1, environmentalImpactFactors.totalCarbonEquivalentEmissionFactorFromCH4());
  EXPECT_DOUBLE_EQ(0.31, environmentalImpactFactors.totalCarbonEquivalentEmissionFactorFromCO2());

  // Preserved deprecated compatibility aliases.
  EXPECT_TRUE(environmentalImpactFactors.setDistrictHeatingEfficiency(0.36));
  EXPECT_TRUE(environmentalImpactFactors.setSteamConversionEfficiency(0.28));
  EXPECT_DOUBLE_EQ(0.36, environmentalImpactFactors.districtHeatingEfficiency());
  EXPECT_DOUBLE_EQ(0.28, environmentalImpactFactors.steamConversionEfficiency());
}
