/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowMaterialShadeEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialShadeEquivalentLayer_DefaultConstructor) {
  Model model;
  WindowMaterialShadeEquivalentLayer layer(model);

  EXPECT_EQ(WindowMaterialShadeEquivalentLayer::iddObjectType(), layer.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, layer.shadeBeamBeamSolarTransmittance());
  EXPECT_TRUE(layer.isShadeBeamBeamSolarTransmittanceDefaulted());
  EXPECT_FALSE(layer.shadeBeamBeamVisibleTransmittanceAtNormalIncidence());
  EXPECT_FALSE(layer.shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence());
  EXPECT_FALSE(layer.shadeBeamDiffuseVisibleReflectanceAtNormalIncidence());
  EXPECT_DOUBLE_EQ(0.05, layer.shadeMaterialInfraredTransmittance());
  EXPECT_TRUE(layer.isShadeMaterialInfraredTransmittanceDefaulted());
  EXPECT_DOUBLE_EQ(0.91, layer.frontSideShadeMaterialInfraredEmissivity());
  EXPECT_TRUE(layer.isFrontSideShadeMaterialInfraredEmissivityDefaulted());
  EXPECT_DOUBLE_EQ(0.91, layer.backSideShadeMaterialInfraredEmissivity());
  EXPECT_TRUE(layer.isBackSideShadeMaterialInfraredEmissivityDefaulted());
}

TEST_F(EPModelFixture, WindowMaterialShadeEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialShadeEquivalentLayer layer(model);

  EXPECT_TRUE(layer.setShadeBeamBeamSolarTransmittance(0.12));
  EXPECT_TRUE(layer.setFrontSideShadeBeamDiffuseSolarTransmittance(0.21));
  EXPECT_TRUE(layer.setBackSideShadeBeamDiffuseSolarTransmittance(0.32));
  EXPECT_TRUE(layer.setFrontSideShadeBeamDiffuseSolarReflectance(0.41));
  EXPECT_TRUE(layer.setBackSideShadeBeamDiffuseSolarReflectance(0.52));
  EXPECT_TRUE(layer.setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(0.18));
  EXPECT_TRUE(layer.setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(0.29));
  EXPECT_TRUE(layer.setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(0.19));
  EXPECT_TRUE(layer.setShadeMaterialInfraredTransmittance(0.23));
  EXPECT_TRUE(layer.setFrontSideShadeMaterialInfraredEmissivity(0.78));
  EXPECT_TRUE(layer.setBackSideShadeMaterialInfraredEmissivity(0.34));

  EXPECT_DOUBLE_EQ(0.12, layer.shadeBeamBeamSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.21, layer.frontSideShadeBeamDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.32, layer.backSideShadeBeamDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.41, layer.frontSideShadeBeamDiffuseSolarReflectance());
  EXPECT_DOUBLE_EQ(0.52, layer.backSideShadeBeamDiffuseSolarReflectance());
  ASSERT_TRUE(layer.shadeBeamBeamVisibleTransmittanceAtNormalIncidence());
  EXPECT_DOUBLE_EQ(0.18, *layer.shadeBeamBeamVisibleTransmittanceAtNormalIncidence());
  ASSERT_TRUE(layer.shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence());
  EXPECT_DOUBLE_EQ(0.29, *layer.shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence());
  ASSERT_TRUE(layer.shadeBeamDiffuseVisibleReflectanceAtNormalIncidence());
  EXPECT_DOUBLE_EQ(0.19, *layer.shadeBeamDiffuseVisibleReflectanceAtNormalIncidence());
  EXPECT_DOUBLE_EQ(0.23, layer.shadeMaterialInfraredTransmittance());
  EXPECT_DOUBLE_EQ(0.78, layer.frontSideShadeMaterialInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.34, layer.backSideShadeMaterialInfraredEmissivity());
  EXPECT_FALSE(layer.isShadeBeamBeamSolarTransmittanceDefaulted());

  layer.resetShadeBeamBeamSolarTransmittance();
  EXPECT_TRUE(layer.isShadeBeamBeamSolarTransmittanceDefaulted());
  EXPECT_DOUBLE_EQ(0.0, layer.shadeBeamBeamSolarTransmittance());

  EXPECT_FALSE(layer.isShadeMaterialInfraredTransmittanceDefaulted());
  layer.resetShadeMaterialInfraredTransmittance();
  EXPECT_TRUE(layer.isShadeMaterialInfraredTransmittanceDefaulted());
  EXPECT_DOUBLE_EQ(0.05, layer.shadeMaterialInfraredTransmittance());

  EXPECT_FALSE(layer.isFrontSideShadeMaterialInfraredEmissivityDefaulted());
  layer.resetFrontSideShadeMaterialInfraredEmissivity();
  EXPECT_TRUE(layer.isFrontSideShadeMaterialInfraredEmissivityDefaulted());
  EXPECT_DOUBLE_EQ(0.91, layer.frontSideShadeMaterialInfraredEmissivity());

  EXPECT_FALSE(layer.isBackSideShadeMaterialInfraredEmissivityDefaulted());
  layer.resetBackSideShadeMaterialInfraredEmissivity();
  EXPECT_TRUE(layer.isBackSideShadeMaterialInfraredEmissivityDefaulted());
  EXPECT_DOUBLE_EQ(0.91, layer.backSideShadeMaterialInfraredEmissivity());
}
