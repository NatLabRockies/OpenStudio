/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowMaterialGlazingEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialGlazingEquivalentLayer_DefaultConstructor) {
  Model model;
  WindowMaterialGlazingEquivalentLayer layer(model);
  EXPECT_EQ(WindowMaterialGlazingEquivalentLayer::iddObjectType(), layer.iddObject().type());
  EXPECT_EQ("SpectralAverage", layer.opticalDataType());
  EXPECT_DOUBLE_EQ(0.0, layer.frontSideBeamBeamSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.0, layer.backSideBeamBeamSolarReflectance());
  EXPECT_FALSE(layer.diffuseDiffuseSolarTransmittance());
  EXPECT_TRUE(layer.isDiffuseDiffuseSolarTransmittanceAutocalculated());
}

TEST_F(EPModelFixture, WindowMaterialGlazingEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialGlazingEquivalentLayer layer(model);

  EXPECT_TRUE(layer.setOpticalDataType("Spectral"));
  EXPECT_TRUE(layer.setFrontSideBeamBeamSolarTransmittance(0.35));
  EXPECT_TRUE(layer.setBackSideBeamBeamSolarReflectance(0.15));
  EXPECT_TRUE(layer.setFrontSideBeamDiffuseSolarTransmittance(0.05));
  EXPECT_TRUE(layer.setBackSideBeamDiffuseVisibleSolarTransmittance(0.04));
  EXPECT_TRUE(layer.setDiffuseDiffuseSolarTransmittance(0.45));
  EXPECT_TRUE(layer.setFrontSideDiffuseDiffuseSolarReflectance(0.22));
  EXPECT_TRUE(layer.setInfraredTransmittance(0.3));
  EXPECT_TRUE(layer.setFrontSideInfraredEmissivity(0.8));
  EXPECT_TRUE(layer.setBackSideInfraredEmissivity(0.7));
  EXPECT_TRUE(layer.setThermalResistance(0.2));
  EXPECT_TRUE(layer.setBackSideBeamDiffuseVisibleSolarReflectance(0.1));

  EXPECT_DOUBLE_EQ(0.35, layer.frontSideBeamBeamSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.15, layer.backSideBeamBeamSolarReflectance());
  EXPECT_DOUBLE_EQ(0.05, layer.frontSideBeamDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.04, layer.backSideBeamDiffuseVisibleSolarTransmittance());
  ASSERT_TRUE(layer.diffuseDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.45, *layer.diffuseDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.22, *layer.frontSideDiffuseDiffuseSolarReflectance());
  EXPECT_DOUBLE_EQ(0.3, layer.infraredTransmittance());
  EXPECT_DOUBLE_EQ(0.8, layer.frontSideInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.7, layer.backSideInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.2, layer.thermalResistance());
  EXPECT_EQ("Spectral", layer.opticalDataType());
  EXPECT_DOUBLE_EQ(0.1, layer.backSideBeamDiffuseVisibleSolarReflectance());

  layer.autocalculateDiffuseDiffuseSolarTransmittance();
  EXPECT_TRUE(layer.isDiffuseDiffuseSolarTransmittanceAutocalculated());
  EXPECT_FALSE(layer.diffuseDiffuseSolarTransmittance());

  layer.resetOpticalDataType();
  EXPECT_TRUE(layer.isOpticalDataTypeDefaulted());
}
