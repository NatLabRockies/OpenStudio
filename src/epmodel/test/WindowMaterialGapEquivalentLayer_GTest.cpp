/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowMaterialGapEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialGapEquivalentLayer_DefaultConstructor) {
  Model model;
  WindowMaterialGapEquivalentLayer layer(model);
  EXPECT_EQ(WindowMaterialGapEquivalentLayer::iddObjectType(), layer.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0127, layer.thickness());
  EXPECT_EQ("AIR", layer.gasType());
  EXPECT_EQ("Sealed", layer.gapVentType());
  EXPECT_FALSE(layer.conductivityCoefficientA());
  EXPECT_FALSE(layer.molecularWeight());
}

TEST_F(EPModelFixture, WindowMaterialGapEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialGapEquivalentLayer layer(model);

  EXPECT_TRUE(layer.setThickness(0.02));
  EXPECT_TRUE(layer.setGasType("CUSTOM"));
  EXPECT_TRUE(layer.setGapVentType("VentedIndoor"));
  EXPECT_TRUE(layer.setConductivityCoefficientA(0.05));
  EXPECT_TRUE(layer.setViscosityCoefficientA(1.0e-5));
  EXPECT_TRUE(layer.setSpecificHeatCoefficientA(1000.0));
  EXPECT_TRUE(layer.setMolecularWeight(39.948));
  EXPECT_TRUE(layer.setSpecificHeatRatio(1.66));

  EXPECT_DOUBLE_EQ(0.02, layer.thickness());
  EXPECT_EQ("CUSTOM", layer.gasType());
  EXPECT_EQ("VentedIndoor", layer.gapVentType());
  EXPECT_TRUE(layer.conductivityCoefficientA());
  EXPECT_DOUBLE_EQ(0.05, *layer.conductivityCoefficientA());
  EXPECT_TRUE(layer.viscosityCoefficientA());
  EXPECT_DOUBLE_EQ(1.0e-5, *layer.viscosityCoefficientA());
  EXPECT_TRUE(layer.specificHeatCoefficientA());
  EXPECT_DOUBLE_EQ(1000.0, *layer.specificHeatCoefficientA());
  EXPECT_TRUE(layer.molecularWeight());
  EXPECT_DOUBLE_EQ(39.948, *layer.molecularWeight());
  EXPECT_TRUE(layer.specificHeatRatio());
  EXPECT_DOUBLE_EQ(1.66, *layer.specificHeatRatio());
}
