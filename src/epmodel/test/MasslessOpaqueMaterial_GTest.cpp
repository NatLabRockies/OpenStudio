/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../OpaqueMaterial/MasslessOpaqueMaterial.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MasslessOpaqueMaterial_DefaultConstructor) {
  Model model;
  MasslessOpaqueMaterial masslessOpaqueMaterial(model);

  EXPECT_EQ(MasslessOpaqueMaterial::iddObjectType(), masslessOpaqueMaterial.iddObject().type());
  EXPECT_FALSE(masslessOpaqueMaterial.nameString().empty());
  EXPECT_FALSE(MasslessOpaqueMaterial::roughnessValues().empty());
  EXPECT_EQ("Smooth", masslessOpaqueMaterial.roughness());
  EXPECT_DOUBLE_EQ(0.1, masslessOpaqueMaterial.thermalResistance());
  EXPECT_TRUE(masslessOpaqueMaterial.isThermalAbsorptanceDefaulted());
  EXPECT_TRUE(masslessOpaqueMaterial.isSolarAbsorptanceDefaulted());
  EXPECT_TRUE(masslessOpaqueMaterial.isVisibleAbsorptanceDefaulted());
}

TEST_F(EPModelFixture, MasslessOpaqueMaterial_ScalarAccessors_RoundTrip) {
  Model model;
  MasslessOpaqueMaterial masslessOpaqueMaterial(model);

  EXPECT_TRUE(masslessOpaqueMaterial.setRoughness("VeryRough"));
  EXPECT_EQ("VeryRough", masslessOpaqueMaterial.roughness());

  EXPECT_TRUE(masslessOpaqueMaterial.setThermalResistance(0.25));
  EXPECT_DOUBLE_EQ(0.25, masslessOpaqueMaterial.thermalResistance());

  EXPECT_TRUE(masslessOpaqueMaterial.setThermalAbsorptance(0.88));
  EXPECT_DOUBLE_EQ(0.88, masslessOpaqueMaterial.thermalAbsorptance());
  EXPECT_FALSE(masslessOpaqueMaterial.isThermalAbsorptanceDefaulted());
  masslessOpaqueMaterial.resetThermalAbsorptance();
  EXPECT_TRUE(masslessOpaqueMaterial.isThermalAbsorptanceDefaulted());

  EXPECT_TRUE(masslessOpaqueMaterial.setSolarAbsorptance(0.65));
  EXPECT_DOUBLE_EQ(0.65, masslessOpaqueMaterial.solarAbsorptance());
  EXPECT_FALSE(masslessOpaqueMaterial.isSolarAbsorptanceDefaulted());
  masslessOpaqueMaterial.resetSolarAbsorptance();
  EXPECT_TRUE(masslessOpaqueMaterial.isSolarAbsorptanceDefaulted());

  EXPECT_TRUE(masslessOpaqueMaterial.setVisibleAbsorptance(0.61));
  EXPECT_DOUBLE_EQ(0.61, masslessOpaqueMaterial.visibleAbsorptance());
  EXPECT_FALSE(masslessOpaqueMaterial.isVisibleAbsorptanceDefaulted());
  masslessOpaqueMaterial.resetVisibleAbsorptance();
  EXPECT_TRUE(masslessOpaqueMaterial.isVisibleAbsorptanceDefaulted());
}
