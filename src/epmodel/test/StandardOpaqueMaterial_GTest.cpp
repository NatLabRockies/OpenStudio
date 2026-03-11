/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../OpaqueMaterial/StandardOpaqueMaterial.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, StandardOpaqueMaterial_DefaultConstructor) {
  Model model;
  StandardOpaqueMaterial standardOpaqueMaterial(model);

  EXPECT_EQ(StandardOpaqueMaterial::iddObjectType(), standardOpaqueMaterial.iddObject().type());
  EXPECT_FALSE(standardOpaqueMaterial.nameString().empty());
  EXPECT_FALSE(StandardOpaqueMaterial::roughnessValues().empty());
  EXPECT_EQ("Smooth", standardOpaqueMaterial.roughness());
  EXPECT_DOUBLE_EQ(0.1, standardOpaqueMaterial.thickness());
  EXPECT_DOUBLE_EQ(0.1, standardOpaqueMaterial.conductivity());
  EXPECT_DOUBLE_EQ(0.1, standardOpaqueMaterial.density());
  EXPECT_DOUBLE_EQ(1400.0, standardOpaqueMaterial.specificHeat());
}

TEST_F(EPModelFixture, StandardOpaqueMaterial_ScalarAccessors_RoundTrip) {
  Model model;
  StandardOpaqueMaterial standardOpaqueMaterial(model);

  EXPECT_TRUE(standardOpaqueMaterial.setThermalConductivity(0.5));
  EXPECT_DOUBLE_EQ(0.5, standardOpaqueMaterial.thermalConductivity());

  EXPECT_TRUE(standardOpaqueMaterial.setThickness(0.2));
  EXPECT_DOUBLE_EQ(0.2, standardOpaqueMaterial.thickness());
  EXPECT_DOUBLE_EQ(0.4, standardOpaqueMaterial.thermalResistance());

  EXPECT_TRUE(standardOpaqueMaterial.setThermalResistance(0.8));
  EXPECT_DOUBLE_EQ(0.8, standardOpaqueMaterial.thermalResistance());

  EXPECT_TRUE(standardOpaqueMaterial.setThermalResistivity(5.0));
  EXPECT_DOUBLE_EQ(5.0, standardOpaqueMaterial.thermalResistivity());

  EXPECT_TRUE(standardOpaqueMaterial.setThermalConductance(2.0));
  EXPECT_DOUBLE_EQ(2.0, standardOpaqueMaterial.thermalConductance());

  EXPECT_TRUE(standardOpaqueMaterial.setSolarAbsorptance(0.45));
  EXPECT_DOUBLE_EQ(0.45, standardOpaqueMaterial.solarAbsorptance());
  ASSERT_TRUE(standardOpaqueMaterial.solarReflectance());
  EXPECT_DOUBLE_EQ(0.55, standardOpaqueMaterial.solarReflectance().get());

  EXPECT_TRUE(standardOpaqueMaterial.setVisibleReflectance(0.25));
  EXPECT_DOUBLE_EQ(0.75, standardOpaqueMaterial.visibleAbsorptance());
  ASSERT_TRUE(standardOpaqueMaterial.visibleReflectance());
  EXPECT_DOUBLE_EQ(0.25, standardOpaqueMaterial.visibleReflectance().get());

  EXPECT_TRUE(standardOpaqueMaterial.isThermalAbsorptanceDefaulted());
  EXPECT_TRUE(standardOpaqueMaterial.setThermalAbsorptance(0.88));
  EXPECT_FALSE(standardOpaqueMaterial.isThermalAbsorptanceDefaulted());
  EXPECT_DOUBLE_EQ(0.88, standardOpaqueMaterial.thermalAbsorptance());

  EXPECT_TRUE(standardOpaqueMaterial.setThermalAbsorptance(boost::none));
  EXPECT_TRUE(standardOpaqueMaterial.isThermalAbsorptanceDefaulted());

  EXPECT_TRUE(standardOpaqueMaterial.setSolarAbsorptance(boost::none));
  EXPECT_TRUE(standardOpaqueMaterial.isSolarAbsorptanceDefaulted());

  EXPECT_TRUE(standardOpaqueMaterial.setVisibleAbsorptance(boost::none));
  EXPECT_TRUE(standardOpaqueMaterial.isVisibleAbsorptanceDefaulted());

  ASSERT_TRUE(standardOpaqueMaterial.heatCapacity());
  EXPECT_DOUBLE_EQ(standardOpaqueMaterial.specificHeat() * standardOpaqueMaterial.density() * standardOpaqueMaterial.thickness(),
                   standardOpaqueMaterial.heatCapacity().get());
}
