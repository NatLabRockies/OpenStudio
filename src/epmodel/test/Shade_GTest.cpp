/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ShadingMaterial/Shade.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Shade_DefaultConstructor) {
  Model model;
  Shade shade(model);
  EXPECT_TRUE(shade.setSolarTransmittance(0.25));
}

TEST_F(EPModelFixture, Shade_ScalarAccessors_RoundTrip) {
  Model model;
  Shade shade(model);

  EXPECT_TRUE(shade.setSolarTransmittance(0.25));
  EXPECT_TRUE(shade.setSolarReflectance(0.3));
  EXPECT_DOUBLE_EQ(0.25, shade.solarTransmittance());
  EXPECT_DOUBLE_EQ(0.3, shade.solarReflectance());
  EXPECT_DOUBLE_EQ(1.0 - 0.25 - 0.3, shade.solarAbsorptance());

  EXPECT_TRUE(shade.setVisibleTransmittance(0.28));
  EXPECT_TRUE(shade.setVisibleReflectance(0.32));
  EXPECT_DOUBLE_EQ(0.28, shade.visibleTransmittance());
  EXPECT_DOUBLE_EQ(0.32, shade.visibleReflectance());
  EXPECT_DOUBLE_EQ(1.0 - 0.28 - 0.32, shade.visibleAbsorptance());

  EXPECT_TRUE(shade.setThermalHemisphericalEmissivity(0.85));
  EXPECT_DOUBLE_EQ(0.85, shade.thermalHemisphericalEmissivity());

  EXPECT_TRUE(shade.setThermalTransmittance(0.12));
  EXPECT_DOUBLE_EQ(0.12, shade.thermalTransmittance());

  EXPECT_TRUE(shade.setThermalConductivity(120.0));
  EXPECT_TRUE(shade.setThickness(0.005));
  EXPECT_DOUBLE_EQ(120.0, shade.thermalConductivity());
  EXPECT_DOUBLE_EQ(120.0 / 0.005, shade.thermalConductance());

  EXPECT_TRUE(shade.setThermalConductance(50.0));
  EXPECT_DOUBLE_EQ(50.0, shade.thermalConductance());

  EXPECT_TRUE(shade.setThermalResistivity(1.0 / 80.0));
  EXPECT_DOUBLE_EQ(80.0, shade.thermalConductivity());

  EXPECT_TRUE(shade.setThermalResistance(0.02));
  EXPECT_DOUBLE_EQ(0.02, shade.thermalResistance());

  EXPECT_TRUE(shade.setThickness(0.01));
  EXPECT_DOUBLE_EQ(0.01, shade.thickness());

  EXPECT_TRUE(shade.setConductivity(200.0));
  EXPECT_DOUBLE_EQ(200.0, shade.conductivity());

  EXPECT_TRUE(shade.setShadetoGlassDistance(0.04));
  EXPECT_DOUBLE_EQ(0.04, shade.shadetoGlassDistance());
  shade.resetShadetoGlassDistance();
  EXPECT_TRUE(shade.isShadetoGlassDistanceDefaulted());

  EXPECT_TRUE(shade.setTopOpeningMultiplier(0.1));
  EXPECT_DOUBLE_EQ(0.1, shade.topOpeningMultiplier());
  shade.resetTopOpeningMultiplier();
  EXPECT_TRUE(shade.isTopOpeningMultiplierDefaulted());

  EXPECT_TRUE(shade.setBottomOpeningMultiplier(0.11));
  EXPECT_DOUBLE_EQ(0.11, shade.bottomOpeningMultiplier());
  shade.resetBottomOpeningMultiplier();
  EXPECT_TRUE(shade.isBottomOpeningMultiplierDefaulted());

  EXPECT_TRUE(shade.setLeftSideOpeningMultiplier(0.12));
  EXPECT_DOUBLE_EQ(0.12, shade.leftSideOpeningMultiplier());
  shade.resetLeftSideOpeningMultiplier();
  EXPECT_TRUE(shade.isLeftSideOpeningMultiplierDefaulted());

  EXPECT_TRUE(shade.setRightSideOpeningMultiplier(0.13));
  EXPECT_DOUBLE_EQ(0.13, shade.rightSideOpeningMultiplier());
  shade.resetRightSideOpeningMultiplier();
  EXPECT_TRUE(shade.isRightSideOpeningMultiplierDefaulted());

  EXPECT_TRUE(shade.setAirflowPermeability(0.35));
  EXPECT_DOUBLE_EQ(0.35, shade.airflowPermeability());
  shade.resetAirflowPermeability();
  EXPECT_TRUE(shade.isAirflowPermeabilityDefaulted());
}
