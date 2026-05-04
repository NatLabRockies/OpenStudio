/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FoundationKiva.hpp"
#include "../ModelObject/FoundationKivaSettings.hpp"
#include "../ModelObject/FoundationKivaSettings_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FoundationKiva_DefaultConstructor) {
  Model model;
  FoundationKiva foundationKiva(model);
  EXPECT_EQ(FoundationKiva::iddObjectType(), foundationKiva.iddObject().type());
}

TEST_F(EPModelFixture, FoundationKiva_ScalarAccessors_RoundTrip) {
  Model model;
  FoundationKiva foundationKiva(model);

  EXPECT_TRUE(foundationKiva.setInitialIndoorAirTemperature(21.25));
  ASSERT_TRUE(foundationKiva.initialIndoorAirTemperature());
  EXPECT_DOUBLE_EQ(21.25, *foundationKiva.initialIndoorAirTemperature());

  EXPECT_TRUE(foundationKiva.setInteriorHorizontalInsulationDepth(0.31));
  EXPECT_DOUBLE_EQ(0.31, foundationKiva.interiorHorizontalInsulationDepth());
  EXPECT_FALSE(foundationKiva.isInteriorHorizontalInsulationDepthDefaulted());
  foundationKiva.resetInteriorHorizontalInsulationDepth();
  EXPECT_TRUE(foundationKiva.isInteriorHorizontalInsulationDepthDefaulted());

  EXPECT_TRUE(foundationKiva.setInteriorHorizontalInsulationWidth(1.23));
  ASSERT_TRUE(foundationKiva.interiorHorizontalInsulationWidth());
  EXPECT_DOUBLE_EQ(1.23, *foundationKiva.interiorHorizontalInsulationWidth());

  EXPECT_TRUE(foundationKiva.setInteriorVerticalInsulationDepth(0.12));
  ASSERT_TRUE(foundationKiva.interiorVerticalInsulationDepth());
  EXPECT_DOUBLE_EQ(0.12, *foundationKiva.interiorVerticalInsulationDepth());

  EXPECT_TRUE(foundationKiva.setExteriorHorizontalInsulationDepth(0.22));
  ASSERT_TRUE(foundationKiva.exteriorHorizontalInsulationDepth());
  EXPECT_DOUBLE_EQ(0.22, *foundationKiva.exteriorHorizontalInsulationDepth());

  EXPECT_TRUE(foundationKiva.setExteriorHorizontalInsulationWidth(1.5));
  EXPECT_DOUBLE_EQ(1.5, foundationKiva.exteriorHorizontalInsulationWidth());
  EXPECT_FALSE(foundationKiva.isExteriorHorizontalInsulationWidthDefaulted());
  foundationKiva.resetExteriorHorizontalInsulationWidth();
  EXPECT_TRUE(foundationKiva.isExteriorHorizontalInsulationWidthDefaulted());

  EXPECT_TRUE(foundationKiva.setExteriorVerticalInsulationDepth(0.19));
  ASSERT_TRUE(foundationKiva.exteriorVerticalInsulationDepth());
  EXPECT_DOUBLE_EQ(0.19, *foundationKiva.exteriorVerticalInsulationDepth());

  EXPECT_TRUE(foundationKiva.setWallHeightAboveGrade(0.45));
  EXPECT_DOUBLE_EQ(0.45, foundationKiva.wallHeightAboveGrade());
  EXPECT_FALSE(foundationKiva.isWallHeightAboveGradeDefaulted());
  foundationKiva.resetWallHeightAboveGrade();
  EXPECT_TRUE(foundationKiva.isWallHeightAboveGradeDefaulted());

  EXPECT_TRUE(foundationKiva.setWallDepthBelowSlab(0.52));
  EXPECT_DOUBLE_EQ(0.52, foundationKiva.wallDepthBelowSlab());
  EXPECT_FALSE(foundationKiva.isWallDepthBelowSlabDefaulted());
  foundationKiva.resetWallDepthBelowSlab();
  EXPECT_TRUE(foundationKiva.isWallDepthBelowSlabDefaulted());

  EXPECT_TRUE(foundationKiva.setFootingDepth(0.41));
  EXPECT_DOUBLE_EQ(0.41, foundationKiva.footingDepth());
  EXPECT_FALSE(foundationKiva.isFootingDepthDefaulted());
  foundationKiva.resetFootingDepth();
  EXPECT_TRUE(foundationKiva.isFootingDepthDefaulted());
}

TEST_F(EPModelFixture, FoundationKivaSettings_DefaultConstructor) {
  Model model;
  auto foundationKivaSettings = model.getUniqueModelObject<FoundationKivaSettings>();
  EXPECT_EQ(FoundationKivaSettings::iddObjectType(), foundationKivaSettings.iddObject().type());
}

TEST_F(EPModelFixture, FoundationKivaSettings_ScalarAccessors_RoundTrip) {
  Model model;
  auto foundationKivaSettings = model.getUniqueModelObject<FoundationKivaSettings>();

  EXPECT_TRUE(foundationKivaSettings.setSoilConductivity(1.75));
  EXPECT_DOUBLE_EQ(1.75, foundationKivaSettings.soilConductivity());
  EXPECT_FALSE(foundationKivaSettings.isSoilConductivityDefaulted());
  foundationKivaSettings.resetSoilConductivity();
  EXPECT_TRUE(foundationKivaSettings.isSoilConductivityDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setSoilDensity(1850.0));
  EXPECT_DOUBLE_EQ(1850.0, foundationKivaSettings.soilDensity());
  EXPECT_FALSE(foundationKivaSettings.isSoilDensityDefaulted());
  foundationKivaSettings.resetSoilDensity();
  EXPECT_TRUE(foundationKivaSettings.isSoilDensityDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setSoilSpecificHeat(400.0));
  EXPECT_DOUBLE_EQ(400.0, foundationKivaSettings.soilSpecificHeat());
  EXPECT_FALSE(foundationKivaSettings.isSoilSpecificHeatDefaulted());
  foundationKivaSettings.resetSoilSpecificHeat();
  EXPECT_TRUE(foundationKivaSettings.isSoilSpecificHeatDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setGroundSolarAbsorptivity(0.95));
  EXPECT_DOUBLE_EQ(0.95, foundationKivaSettings.groundSolarAbsorptivity());
  EXPECT_FALSE(foundationKivaSettings.isGroundSolarAbsorptivityDefaulted());
  foundationKivaSettings.resetGroundSolarAbsorptivity();
  EXPECT_TRUE(foundationKivaSettings.isGroundSolarAbsorptivityDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setGroundThermalAbsorptivity(0.85));
  EXPECT_DOUBLE_EQ(0.85, foundationKivaSettings.groundThermalAbsorptivity());
  EXPECT_FALSE(foundationKivaSettings.isGroundThermalAbsorptivityDefaulted());
  foundationKivaSettings.resetGroundThermalAbsorptivity();
  EXPECT_TRUE(foundationKivaSettings.isGroundThermalAbsorptivityDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setGroundSurfaceRoughness(0.06));
  EXPECT_DOUBLE_EQ(0.06, foundationKivaSettings.groundSurfaceRoughness());
  EXPECT_FALSE(foundationKivaSettings.isGroundSurfaceRoughnessDefaulted());
  foundationKivaSettings.resetGroundSurfaceRoughness();
  EXPECT_TRUE(foundationKivaSettings.isGroundSurfaceRoughnessDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setFarFieldWidth(50.0));
  EXPECT_DOUBLE_EQ(50.0, foundationKivaSettings.farFieldWidth());
  EXPECT_FALSE(foundationKivaSettings.isFarFieldWidthDefaulted());
  foundationKivaSettings.resetFarFieldWidth();
  EXPECT_TRUE(foundationKivaSettings.isFarFieldWidthDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setDeepGroundBoundaryCondition("GroundWater"));
  EXPECT_EQ("GroundWater", foundationKivaSettings.deepGroundBoundaryCondition());
  EXPECT_FALSE(foundationKivaSettings.isDeepGroundBoundaryConditionAutoselected());
  foundationKivaSettings.resetDeepGroundBoundaryCondition();
  EXPECT_TRUE(foundationKivaSettings.isDeepGroundBoundaryConditionAutoselected());

  EXPECT_TRUE(foundationKivaSettings.setDeepGroundDepth(45.0));
  ASSERT_TRUE(foundationKivaSettings.deepGroundDepth());
  EXPECT_DOUBLE_EQ(45.0, *foundationKivaSettings.deepGroundDepth());
  EXPECT_FALSE(foundationKivaSettings.isDeepGroundDepthAutocalculated());
  foundationKivaSettings.autocalculateDeepGroundDepth();
  EXPECT_TRUE(foundationKivaSettings.isDeepGroundDepthAutocalculated());

  EXPECT_TRUE(foundationKivaSettings.setMinimumCellDimension(0.03));
  EXPECT_DOUBLE_EQ(0.03, foundationKivaSettings.minimumCellDimension());
  EXPECT_FALSE(foundationKivaSettings.isMinimumCellDimensionDefaulted());
  foundationKivaSettings.resetMinimumCellDimension();
  EXPECT_TRUE(foundationKivaSettings.isMinimumCellDimensionDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setMaximumCellGrowthCoefficient(1.3));
  EXPECT_DOUBLE_EQ(1.3, foundationKivaSettings.maximumCellGrowthCoefficient());
  EXPECT_FALSE(foundationKivaSettings.isMaximumCellGrowthCoefficientDefaulted());
  foundationKivaSettings.resetMaximumCellGrowthCoefficient();
  EXPECT_TRUE(foundationKivaSettings.isMaximumCellGrowthCoefficientDefaulted());

  EXPECT_TRUE(foundationKivaSettings.setSimulationTimestep("Timestep"));
  EXPECT_EQ("Timestep", foundationKivaSettings.simulationTimestep());
  EXPECT_FALSE(foundationKivaSettings.isSimulationTimestepDefaulted());
  foundationKivaSettings.resetSimulationTimestep();
  EXPECT_TRUE(foundationKivaSettings.isSimulationTimestepDefaulted());
}
