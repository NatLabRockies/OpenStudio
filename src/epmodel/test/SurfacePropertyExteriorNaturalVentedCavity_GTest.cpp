/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfacePropertyExteriorNaturalVentedCavity.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyExteriorNaturalVentedCavity_DefaultConstructor) {
  Model model;
  SurfacePropertyExteriorNaturalVentedCavity cavity(model);
  EXPECT_EQ(SurfacePropertyExteriorNaturalVentedCavity::iddObjectType(), cavity.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyExteriorNaturalVentedCavity_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyExteriorNaturalVentedCavity cavity(model);

  EXPECT_FALSE(cavity.areaFractionOfOpenings());
  EXPECT_TRUE(cavity.setAreaFractionOfOpenings(0.6));
  ASSERT_TRUE(cavity.areaFractionOfOpenings());
  EXPECT_DOUBLE_EQ(0.6, cavity.areaFractionOfOpenings().get());
  EXPECT_FALSE(cavity.setAreaFractionOfOpenings(1.1));
  EXPECT_FALSE(cavity.setAreaFractionOfOpenings(-0.1));
  cavity.resetAreaFractionOfOpenings();
  EXPECT_FALSE(cavity.areaFractionOfOpenings());

  EXPECT_FALSE(cavity.thermalEmissivityOfExteriorBaffleMaterial());
  EXPECT_TRUE(cavity.setThermalEmissivityOfExteriorBaffleMaterial(0.8));
  ASSERT_TRUE(cavity.thermalEmissivityOfExteriorBaffleMaterial());
  EXPECT_DOUBLE_EQ(0.8, cavity.thermalEmissivityOfExteriorBaffleMaterial().get());
  EXPECT_FALSE(cavity.setThermalEmissivityOfExteriorBaffleMaterial(-0.1));
  EXPECT_FALSE(cavity.setThermalEmissivityOfExteriorBaffleMaterial(1.5));
  cavity.resetThermalEmissivityOfExteriorBaffleMaterial();
  EXPECT_FALSE(cavity.thermalEmissivityOfExteriorBaffleMaterial());

  EXPECT_FALSE(cavity.solarAbsorbtivityOfExteriorBaffle());
  EXPECT_TRUE(cavity.setSolarAbsorbtivityOfExteriorBaffle(0.4));
  ASSERT_TRUE(cavity.solarAbsorbtivityOfExteriorBaffle());
  EXPECT_DOUBLE_EQ(0.4, cavity.solarAbsorbtivityOfExteriorBaffle().get());
  EXPECT_FALSE(cavity.setSolarAbsorbtivityOfExteriorBaffle(-0.1));
  EXPECT_FALSE(cavity.setSolarAbsorbtivityOfExteriorBaffle(1.4));
  cavity.resetSolarAbsorbtivityOfExteriorBaffle();
  EXPECT_FALSE(cavity.solarAbsorbtivityOfExteriorBaffle());

  EXPECT_FALSE(cavity.heightScaleForBuoyancyDrivenVentilation());
  EXPECT_TRUE(cavity.setHeightScaleForBuoyancyDrivenVentilation(2.0));
  ASSERT_TRUE(cavity.heightScaleForBuoyancyDrivenVentilation());
  EXPECT_DOUBLE_EQ(2.0, cavity.heightScaleForBuoyancyDrivenVentilation().get());
  EXPECT_FALSE(cavity.setHeightScaleForBuoyancyDrivenVentilation(0.0));
  EXPECT_FALSE(cavity.setHeightScaleForBuoyancyDrivenVentilation(-1.0));
  cavity.resetHeightScaleForBuoyancyDrivenVentilation();
  EXPECT_FALSE(cavity.heightScaleForBuoyancyDrivenVentilation());

  EXPECT_FALSE(cavity.effectiveThicknessOfCavityBehindExteriorBaffle());
  EXPECT_TRUE(cavity.setEffectiveThicknessOfCavityBehindExteriorBaffle(0.25));
  ASSERT_TRUE(cavity.effectiveThicknessOfCavityBehindExteriorBaffle());
  EXPECT_DOUBLE_EQ(0.25, cavity.effectiveThicknessOfCavityBehindExteriorBaffle().get());
  EXPECT_FALSE(cavity.setEffectiveThicknessOfCavityBehindExteriorBaffle(0.0));
  cavity.resetEffectiveThicknessOfCavityBehindExteriorBaffle();
  EXPECT_FALSE(cavity.effectiveThicknessOfCavityBehindExteriorBaffle());

  EXPECT_TRUE(cavity.isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted());
  EXPECT_DOUBLE_EQ(1.0, cavity.ratioOfActualSurfaceAreaToProjectedSurfaceArea());
  EXPECT_TRUE(cavity.setRatioOfActualSurfaceAreaToProjectedSurfaceArea(1.25));
  EXPECT_DOUBLE_EQ(1.25, cavity.ratioOfActualSurfaceAreaToProjectedSurfaceArea());
  EXPECT_FALSE(cavity.isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted());
  EXPECT_FALSE(cavity.setRatioOfActualSurfaceAreaToProjectedSurfaceArea(0.5));
  EXPECT_FALSE(cavity.setRatioOfActualSurfaceAreaToProjectedSurfaceArea(2.5));
  cavity.resetRatioOfActualSurfaceAreaToProjectedSurfaceArea();
  EXPECT_TRUE(cavity.isRatioOfActualSurfaceAreaToProjectedSurfaceAreaDefaulted());
  EXPECT_DOUBLE_EQ(1.0, cavity.ratioOfActualSurfaceAreaToProjectedSurfaceArea());

  auto roughnessValues = SurfacePropertyExteriorNaturalVentedCavity::roughnessOfExteriorSurfaceValues();
  ASSERT_FALSE(roughnessValues.empty());
  EXPECT_TRUE(cavity.setRoughnessOfExteriorSurface(roughnessValues.front()));
  EXPECT_EQ(roughnessValues.front(), cavity.roughnessOfExteriorSurface());
  EXPECT_FALSE(cavity.setRoughnessOfExteriorSurface("NotAChoice"));

  EXPECT_TRUE(cavity.isEffectivenessForPerforationsWithRespectToWindDefaulted());
  EXPECT_DOUBLE_EQ(0.25, cavity.effectivenessForPerforationsWithRespectToWind());
  EXPECT_TRUE(cavity.setEffectivenessForPerforationsWithRespectToWind(1.0));
  EXPECT_DOUBLE_EQ(1.0, cavity.effectivenessForPerforationsWithRespectToWind());
  EXPECT_FALSE(cavity.isEffectivenessForPerforationsWithRespectToWindDefaulted());
  EXPECT_FALSE(cavity.setEffectivenessForPerforationsWithRespectToWind(0.0));
  EXPECT_FALSE(cavity.setEffectivenessForPerforationsWithRespectToWind(2.0));
  cavity.resetEffectivenessForPerforationsWithRespectToWind();
  EXPECT_TRUE(cavity.isEffectivenessForPerforationsWithRespectToWindDefaulted());
  EXPECT_DOUBLE_EQ(0.25, cavity.effectivenessForPerforationsWithRespectToWind());

  EXPECT_TRUE(cavity.isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.65, cavity.dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow());
  EXPECT_TRUE(cavity.setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(1.2));
  EXPECT_DOUBLE_EQ(1.2, cavity.dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow());
  EXPECT_FALSE(cavity.isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted());
  EXPECT_FALSE(cavity.setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(0.0));
  EXPECT_FALSE(cavity.setDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow(2.0));
  cavity.resetDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow();
  EXPECT_TRUE(cavity.isDischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.65, cavity.dischargeCoefficientForOpeningsWithRespectToBuoyancyDrivenFlow());
}

TEST_F(EPModelFixture, SurfacePropertyExteriorNaturalVentedCavity_ChoiceValues) {
  auto values = SurfacePropertyExteriorNaturalVentedCavity::roughnessOfExteriorSurfaceValues();
  EXPECT_EQ(6u, values.size());
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "VerySmooth"));
}
