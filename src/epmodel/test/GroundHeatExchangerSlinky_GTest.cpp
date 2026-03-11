/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatExchangerSlinky.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerSlinky_DefaultConstructor) {
  Model model;
  GroundHeatExchangerSlinky ghx(model);
  EXPECT_EQ(GroundHeatExchangerSlinky::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_DOUBLE_EQ(0.002, ghx.designFlowRate());
  EXPECT_DOUBLE_EQ(1.08, ghx.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(962.0, ghx.soilDensity());
  EXPECT_DOUBLE_EQ(2576.0, ghx.soilSpecificHeat());
  EXPECT_DOUBLE_EQ(0.4, ghx.pipeThermalConductivity());
  EXPECT_DOUBLE_EQ(641.0, ghx.pipeDensity());
  EXPECT_DOUBLE_EQ(2405.0, ghx.pipeSpecificHeat());
  EXPECT_DOUBLE_EQ(0.02667, ghx.pipeOuterDiameter());
  EXPECT_DOUBLE_EQ(0.002413, ghx.pipeThickness());
  EXPECT_DOUBLE_EQ(1.0, ghx.coilDiameter());
  EXPECT_DOUBLE_EQ(0.20, ghx.coilPitch());
  EXPECT_DOUBLE_EQ(1.8, ghx.trenchDepth());
  EXPECT_DOUBLE_EQ(10.0, ghx.trenchLength());
  EXPECT_EQ(1, ghx.numberofTrenches());
  EXPECT_DOUBLE_EQ(2.0, ghx.horizontalSpacingBetweenPipes());
  EXPECT_FALSE(ghx.heatExchangerConfiguration());
  EXPECT_FALSE(ghx.maximumLengthofSimulation());
}

TEST_F(EPModelFixture, GroundHeatExchangerSlinky_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerSlinky ghx(model);

  EXPECT_FALSE(GroundHeatExchangerSlinky::heatExchangerConfigurationValues().empty());
  EXPECT_FALSE(GroundHeatExchangerSlinky::undisturbedGroundTemperatureModelTypeValues().empty());

  EXPECT_TRUE(ghx.setDesignFlowRate(0.003));
  EXPECT_DOUBLE_EQ(0.003, ghx.designFlowRate());
  EXPECT_TRUE(ghx.isDesignFlowRateDefaulted() == false);
  ghx.resetDesignFlowRate();
  EXPECT_TRUE(ghx.isDesignFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.002, ghx.designFlowRate());

  EXPECT_TRUE(ghx.setSoilThermalConductivity(1.5));
  EXPECT_DOUBLE_EQ(1.5, ghx.soilThermalConductivity());
  EXPECT_TRUE(ghx.setSoilDensity(1020.0));
  EXPECT_DOUBLE_EQ(1020.0, ghx.soilDensity());
  EXPECT_TRUE(ghx.setSoilSpecificHeat(2700.0));
  EXPECT_DOUBLE_EQ(2700.0, ghx.soilSpecificHeat());
  EXPECT_TRUE(ghx.setPipeThermalConductivity(0.45));
  EXPECT_DOUBLE_EQ(0.45, ghx.pipeThermalConductivity());
  EXPECT_TRUE(ghx.setPipeDensity(700.0));
  EXPECT_DOUBLE_EQ(700.0, ghx.pipeDensity());
  EXPECT_TRUE(ghx.setPipeSpecificHeat(2450.0));
  EXPECT_DOUBLE_EQ(2450.0, ghx.pipeSpecificHeat());
  EXPECT_TRUE(ghx.setPipeOuterDiameter(0.03));
  EXPECT_DOUBLE_EQ(0.03, ghx.pipeOuterDiameter());
  EXPECT_TRUE(ghx.setPipeThickness(0.003));
  EXPECT_DOUBLE_EQ(0.003, ghx.pipeThickness());
  EXPECT_TRUE(ghx.setCoilDiameter(1.5));
  EXPECT_DOUBLE_EQ(1.5, ghx.coilDiameter());
  EXPECT_TRUE(ghx.setCoilPitch(0.25));
  EXPECT_DOUBLE_EQ(0.25, ghx.coilPitch());
  EXPECT_TRUE(ghx.setTrenchDepth(2.0));
  EXPECT_DOUBLE_EQ(2.0, ghx.trenchDepth());
  EXPECT_TRUE(ghx.setTrenchLength(12.0));
  EXPECT_DOUBLE_EQ(12.0, ghx.trenchLength());
  EXPECT_TRUE(ghx.setNumberofTrenches(3));
  EXPECT_EQ(3, ghx.numberofTrenches());
  EXPECT_TRUE(ghx.setHorizontalSpacingBetweenPipes(2.5));
  EXPECT_DOUBLE_EQ(2.5, ghx.horizontalSpacingBetweenPipes());

  EXPECT_TRUE(ghx.setHeatExchangerConfiguration("Vertical"));
  ASSERT_TRUE(ghx.heatExchangerConfiguration());
  EXPECT_EQ("Vertical", ghx.heatExchangerConfiguration().get());
  ghx.resetHeatExchangerConfiguration();
  EXPECT_FALSE(ghx.heatExchangerConfiguration());

  EXPECT_TRUE(ghx.setUndisturbedGroundTemperatureModelType("Site:GroundTemperature:Undisturbed:KusudaAchenbach"));
  EXPECT_EQ("Site:GroundTemperature:Undisturbed:KusudaAchenbach", ghx.undisturbedGroundTemperatureModelType());

  EXPECT_TRUE(ghx.setMaximumLengthofSimulation(5.0));
  ASSERT_TRUE(ghx.maximumLengthofSimulation());
  EXPECT_DOUBLE_EQ(5.0, ghx.maximumLengthofSimulation().get());
  ghx.resetMaximumLengthofSimulation();
  EXPECT_FALSE(ghx.maximumLengthofSimulation());
}
