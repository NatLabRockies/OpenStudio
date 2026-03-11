/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowMaterialDrapeEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialDrapeEquivalentLayer_DefaultConstructor) {
  Model model;
  WindowMaterialDrapeEquivalentLayer drape(model);
  EXPECT_EQ(WindowMaterialDrapeEquivalentLayer::iddObjectType(), drape.iddObject().type());
}

TEST_F(EPModelFixture, WindowMaterialDrapeEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialDrapeEquivalentLayer drape(model);

  EXPECT_TRUE(drape.setFrontSideDrapeBeamDiffuseSolarTransmittance(0.2));
  EXPECT_TRUE(drape.setBackSideDrapeBeamDiffuseSolarTransmittance(0.25));
  EXPECT_TRUE(drape.setFrontSideDrapeBeamDiffuseSolarReflectance(0.3));
  EXPECT_TRUE(drape.setBackSideDrapeBeamDiffuseSolarReflectance(0.35));
  EXPECT_TRUE(drape.setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(0.05));
  EXPECT_TRUE(drape.setDrapeMaterialInfraredTransmittance(0.07));
  EXPECT_TRUE(drape.setFrontSideDrapeMaterialInfraredEmissivity(0.88));
  EXPECT_TRUE(drape.setBackSideDrapeMaterialInfraredEmissivity(0.85));
  EXPECT_TRUE(drape.setDrapeBeamBeamVisibleTransmittance(0.12));
  EXPECT_TRUE(drape.setDrapeBeamDiffuseVisibleTransmittance(0.15));
  EXPECT_TRUE(drape.setDrapeBeamDiffuseVisibleReflectance(0.18));
  EXPECT_TRUE(drape.setWidthOfPleatedFabric(0.01));
  EXPECT_TRUE(drape.setLengthOfPleatedFabric(0.015));

  EXPECT_DOUBLE_EQ(0.2, drape.frontSideDrapeBeamDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.25, drape.backSideDrapeBeamDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.3, drape.frontSideDrapeBeamDiffuseSolarReflectance());
  EXPECT_DOUBLE_EQ(0.35, drape.backSideDrapeBeamDiffuseSolarReflectance());
  EXPECT_DOUBLE_EQ(0.05, drape.drapeBeamBeamSolarTransmittanceAtNormalIncidence());
  EXPECT_DOUBLE_EQ(0.07, drape.drapeMaterialInfraredTransmittance());
  EXPECT_DOUBLE_EQ(0.88, drape.frontSideDrapeMaterialInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.85, drape.backSideDrapeMaterialInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.01, drape.widthOfPleatedFabric());
  EXPECT_DOUBLE_EQ(0.015, drape.lengthOfPleatedFabric());

  ASSERT_TRUE(drape.drapeBeamBeamVisibleTransmittance());
  EXPECT_DOUBLE_EQ(0.12, drape.drapeBeamBeamVisibleTransmittance().get());
  ASSERT_TRUE(drape.drapeBeamDiffuseVisibleTransmittance());
  EXPECT_DOUBLE_EQ(0.15, drape.drapeBeamDiffuseVisibleTransmittance().get());
  ASSERT_TRUE(drape.drapeBeamDiffuseVisibleReflectance());
  EXPECT_DOUBLE_EQ(0.18, drape.drapeBeamDiffuseVisibleReflectance().get());

  drape.resetDrapeBeamBeamVisibleTransmittance();
  drape.resetDrapeBeamDiffuseVisibleReflectance();

  EXPECT_FALSE(drape.drapeBeamBeamVisibleTransmittance());
  EXPECT_TRUE(drape.drapeBeamDiffuseVisibleTransmittance());
  EXPECT_FALSE(drape.drapeBeamDiffuseVisibleReflectance());
}
