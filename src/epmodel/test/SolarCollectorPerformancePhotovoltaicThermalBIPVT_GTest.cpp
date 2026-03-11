/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SolarCollectorPerformancePhotovoltaicThermalBIPVT.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorPerformancePhotovoltaicThermalBIPVT_DefaultConstructor) {
  Model model;
  SolarCollectorPerformancePhotovoltaicThermalBIPVT object(model);
  EXPECT_EQ(SolarCollectorPerformancePhotovoltaicThermalBIPVT::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorPerformancePhotovoltaicThermalBIPVT_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorPerformancePhotovoltaicThermalBIPVT object(model);

  EXPECT_TRUE(object.setEffectivePlenumGapThicknessBehindPVModules(0.05));
  EXPECT_DOUBLE_EQ(0.05, object.effectivePlenumGapThicknessBehindPVModules());

  EXPECT_TRUE(object.setPVCellNormalTransmittanceAbsorptanceProduct(0.91));
  EXPECT_DOUBLE_EQ(0.91, object.pVCellNormalTransmittanceAbsorptanceProduct());

  EXPECT_TRUE(object.setBackingMaterialNormalTransmittanceAbsorptanceProduct(0.82));
  EXPECT_DOUBLE_EQ(0.82, object.backingMaterialNormalTransmittanceAbsorptanceProduct());

  EXPECT_TRUE(object.setCladdingNormalTransmittanceAbsorptanceProduct(0.80));
  EXPECT_DOUBLE_EQ(0.80, object.claddingNormalTransmittanceAbsorptanceProduct());

  EXPECT_TRUE(object.setFractionofCollectorGrossAreaCoveredbyPVModule(0.88));
  EXPECT_DOUBLE_EQ(0.88, object.fractionofCollectorGrossAreaCoveredbyPVModule());

  EXPECT_TRUE(object.setFractionofPVCellAreatoPVModuleArea(0.95));
  EXPECT_DOUBLE_EQ(0.95, object.fractionofPVCellAreatoPVModuleArea());

  EXPECT_TRUE(object.setPVModuleTopThermalResistance(0.0035));
  EXPECT_DOUBLE_EQ(0.0035, object.pVModuleTopThermalResistance());

  EXPECT_TRUE(object.setPVModuleBottomThermalResistance(0.0028));
  EXPECT_DOUBLE_EQ(0.0028, object.pVModuleBottomThermalResistance());

  EXPECT_TRUE(object.setPVModuleFrontLongwaveEmissivity(0.86));
  EXPECT_DOUBLE_EQ(0.86, object.pVModuleFrontLongwaveEmissivity());

  EXPECT_TRUE(object.setPVModuleBackLongwaveEmissivity(0.93));
  EXPECT_DOUBLE_EQ(0.93, object.pVModuleBackLongwaveEmissivity());

  EXPECT_TRUE(object.setGlassThickness(0.003));
  EXPECT_DOUBLE_EQ(0.003, object.glassThickness());

  EXPECT_TRUE(object.setGlassRefractionIndex(1.48));
  EXPECT_DOUBLE_EQ(1.48, object.glassRefractionIndex());

  EXPECT_TRUE(object.setGlassExtinctionCoefficient(4.7));
  EXPECT_DOUBLE_EQ(4.7, object.glassExtinctionCoefficient());
}
