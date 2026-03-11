/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ShadingMaterial/Screen.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Screen_DefaultConstructor) {
  Model model;
  Screen screen(model);
  EXPECT_TRUE(screen.setDiffuseSolarReflectance(0.05));
}

TEST_F(EPModelFixture, Screen_ScalarAccessors_RoundTrip) {
  Model model;
  Screen screen(model);

  EXPECT_TRUE(screen.setReflectedBeamTransmittanceAccountingMethod("ModelAsDirectBeam"));
  EXPECT_EQ("ModelAsDirectBeam", screen.reflectedBeamTransmittanceAccountingMethod());
  screen.resetReflectedBeamTransmittanceAccountingMethod();
  EXPECT_TRUE(screen.isReflectedBeamTransmittanceAccountingMethodDefaulted());

  EXPECT_TRUE(screen.setDiffuseSolarReflectance(0.2));
  EXPECT_DOUBLE_EQ(0.2, screen.diffuseSolarReflectance());
  EXPECT_TRUE(screen.setDiffuseVisibleReflectance(0.25));
  EXPECT_DOUBLE_EQ(0.25, screen.diffuseVisibleReflectance());

  EXPECT_TRUE(screen.setThermalHemisphericalEmissivity(0.88));
  EXPECT_DOUBLE_EQ(0.88, screen.thermalHemisphericalEmissivity());
  screen.resetThermalHemisphericalEmissivity();
  EXPECT_TRUE(screen.isThermalHemisphericalEmissivityDefaulted());

  EXPECT_TRUE(screen.setScreenMaterialDiameter(0.002));
  EXPECT_TRUE(screen.setThermalConductivity(130.0));
  EXPECT_DOUBLE_EQ(130.0, screen.thermalConductivity());
  EXPECT_DOUBLE_EQ(130.0 / 0.002, screen.thermalConductance());

  EXPECT_TRUE(screen.setThermalResistivity(1.0 / 110.0));
  EXPECT_DOUBLE_EQ(110.0, screen.thermalConductivity());

  EXPECT_TRUE(screen.setScreenMaterialSpacing(0.0011));
  EXPECT_DOUBLE_EQ(0.0011, screen.screenMaterialSpacing());

  EXPECT_TRUE(screen.setScreentoGlassDistance(0.03));
  EXPECT_DOUBLE_EQ(0.03, screen.screentoGlassDistance());
  screen.resetScreentoGlassDistance();
  EXPECT_TRUE(screen.isScreentoGlassDistanceDefaulted());

  EXPECT_TRUE(screen.setTopOpeningMultiplier(0.12));
  EXPECT_DOUBLE_EQ(0.12, screen.topOpeningMultiplier());
  screen.resetTopOpeningMultiplier();
  EXPECT_TRUE(screen.isTopOpeningMultiplierDefaulted());

  EXPECT_TRUE(screen.setBottomOpeningMultiplier(0.13));
  EXPECT_DOUBLE_EQ(0.13, screen.bottomOpeningMultiplier());
  screen.resetBottomOpeningMultiplier();
  EXPECT_TRUE(screen.isBottomOpeningMultiplierDefaulted());

  EXPECT_TRUE(screen.setLeftSideOpeningMultiplier(0.14));
  EXPECT_DOUBLE_EQ(0.14, screen.leftSideOpeningMultiplier());
  screen.resetLeftSideOpeningMultiplier();
  EXPECT_TRUE(screen.isLeftSideOpeningMultiplierDefaulted());

  EXPECT_TRUE(screen.setRightSideOpeningMultiplier(0.15));
  EXPECT_DOUBLE_EQ(0.15, screen.rightSideOpeningMultiplier());
  screen.resetRightSideOpeningMultiplier();
  EXPECT_TRUE(screen.isRightSideOpeningMultiplierDefaulted());

  EXPECT_TRUE(screen.setAngleofResolutionforScreenTransmittanceOutputMap("2"));
  EXPECT_EQ("2", screen.angleofResolutionforScreenTransmittanceOutputMap());
  screen.resetAngleofResolutionforScreenTransmittanceOutputMap();
  EXPECT_TRUE(screen.isAngleofResolutionforScreenTransmittanceOutputMapDefaulted());
}
