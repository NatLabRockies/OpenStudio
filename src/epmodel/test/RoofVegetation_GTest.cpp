/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../OpaqueMaterial/RoofVegetation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoofVegetation_DefaultConstructor) {
  Model model;
  RoofVegetation roofVegetation(model);

  EXPECT_EQ(RoofVegetation::iddObjectType(), roofVegetation.iddObject().type());
  EXPECT_FALSE(roofVegetation.nameString().empty());
  EXPECT_FALSE(RoofVegetation::roughnessValues().empty());
  EXPECT_FALSE(RoofVegetation::moistureDiffusionCalculationMethodValues().empty());
  EXPECT_EQ("Smooth", roofVegetation.roughness());
}

TEST_F(EPModelFixture, RoofVegetation_ScalarAccessors_RoundTrip) {
  Model model;
  RoofVegetation roofVegetation(model);

  EXPECT_TRUE(roofVegetation.setHeightofPlants(0.2));
  EXPECT_DOUBLE_EQ(0.2, roofVegetation.heightofPlants());

  EXPECT_TRUE(roofVegetation.setLeafAreaIndex(1.5));
  EXPECT_DOUBLE_EQ(1.5, roofVegetation.leafAreaIndex());

  EXPECT_TRUE(roofVegetation.setConductivityofDrySoil(0.35));
  EXPECT_DOUBLE_EQ(0.35, roofVegetation.conductivityofDrySoil());
  EXPECT_DOUBLE_EQ(0.35, roofVegetation.thermalConductivity());

  EXPECT_TRUE(roofVegetation.setDensityofDrySoil(900.0));
  EXPECT_DOUBLE_EQ(900.0, roofVegetation.density());

  EXPECT_TRUE(roofVegetation.setSpecificHeatofDrySoil(1200.0));
  EXPECT_DOUBLE_EQ(1200.0, roofVegetation.specificHeat());

  EXPECT_TRUE(roofVegetation.setMoistureDiffusionCalculationMethod("Simple"));
  EXPECT_EQ("Simple", roofVegetation.moistureDiffusionCalculationMethod());

  EXPECT_TRUE(roofVegetation.isSolarAbsorptanceDefaulted());
  EXPECT_TRUE(roofVegetation.setSolarAbsorptance(0.65));
  EXPECT_DOUBLE_EQ(0.65, roofVegetation.solarAbsorptance());
  EXPECT_FALSE(roofVegetation.isSolarAbsorptanceDefaulted());
  roofVegetation.resetSolarAbsorptance();
  EXPECT_TRUE(roofVegetation.isSolarAbsorptanceDefaulted());

  EXPECT_TRUE(roofVegetation.setInitialVolumetricMoistureConent(0.18));
  EXPECT_DOUBLE_EQ(0.18, roofVegetation.initialVolumetricMoistureContent());

  ASSERT_TRUE(roofVegetation.heatCapacity());
  EXPECT_DOUBLE_EQ(roofVegetation.specificHeat() * roofVegetation.density() * roofVegetation.thickness(), roofVegetation.heatCapacity().get());
}
