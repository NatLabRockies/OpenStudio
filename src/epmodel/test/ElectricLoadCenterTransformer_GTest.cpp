/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ElectricLoadCenterTransformer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterTransformer_DefaultConstructor) {
  Model model;
  ElectricLoadCenterTransformer transformer(model);
  EXPECT_EQ(ElectricLoadCenterTransformer::iddObjectType(), transformer.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterTransformer_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterTransformer transformer(model);

  const auto transformerUsageValues = ElectricLoadCenterTransformer::transformerUsageValues();
  ASSERT_FALSE(transformerUsageValues.empty());
  EXPECT_TRUE(transformer.setTransformerUsage(transformerUsageValues.front()));
  EXPECT_EQ(transformerUsageValues.front(), transformer.transformerUsage());
  transformer.resetTransformerUsage();
  EXPECT_TRUE(transformer.isTransformerUsageDefaulted());

  EXPECT_TRUE(transformer.setRadiativeFraction(0.35));
  EXPECT_DOUBLE_EQ(0.35, transformer.radiativeFraction());
  transformer.resetRadiativeFraction();
  EXPECT_TRUE(transformer.isRadiativeFractionDefaulted());

  EXPECT_TRUE(transformer.setRatedCapacity(25000.0));
  ASSERT_TRUE(transformer.ratedCapacity());
  EXPECT_DOUBLE_EQ(25000.0, *transformer.ratedCapacity());
  transformer.resetRatedCapacity();
  EXPECT_FALSE(transformer.ratedCapacity());

  const auto phaseValues = ElectricLoadCenterTransformer::phaseValues();
  ASSERT_FALSE(phaseValues.empty());
  EXPECT_TRUE(transformer.setPhase(phaseValues.front()));
  EXPECT_EQ(phaseValues.front(), transformer.phase());
  transformer.resetPhase();
  EXPECT_TRUE(transformer.isPhaseDefaulted());

  const auto conductorMaterialValues = ElectricLoadCenterTransformer::conductorMaterialValues();
  ASSERT_FALSE(conductorMaterialValues.empty());
  EXPECT_TRUE(transformer.setConductorMaterial(conductorMaterialValues.front()));
  EXPECT_EQ(conductorMaterialValues.front(), transformer.conductorMaterial());
  transformer.resetConductorMaterial();
  EXPECT_TRUE(transformer.isConductorMaterialDefaulted());

  EXPECT_TRUE(transformer.setFullLoadTemperatureRise(140.0));
  EXPECT_DOUBLE_EQ(140.0, transformer.fullLoadTemperatureRise());
  transformer.resetFullLoadTemperatureRise();
  EXPECT_TRUE(transformer.isFullLoadTemperatureRiseDefaulted());

  EXPECT_TRUE(transformer.setFractionofEddyCurrentLosses(0.08));
  EXPECT_DOUBLE_EQ(0.08, transformer.fractionofEddyCurrentLosses());
  transformer.resetFractionofEddyCurrentLosses();
  EXPECT_TRUE(transformer.isFractionofEddyCurrentLossesDefaulted());

  const auto performanceInputMethodValues = ElectricLoadCenterTransformer::performanceInputMethodValues();
  ASSERT_FALSE(performanceInputMethodValues.empty());
  EXPECT_TRUE(transformer.setPerformanceInputMethod(performanceInputMethodValues.front()));
  EXPECT_EQ(performanceInputMethodValues.front(), transformer.performanceInputMethod());
  transformer.resetPerformanceInputMethod();
  EXPECT_TRUE(transformer.isPerformanceInputMethodDefaulted());

  EXPECT_TRUE(transformer.setRatedNoLoadLoss(400.0));
  ASSERT_TRUE(transformer.ratedNoLoadLoss());
  EXPECT_DOUBLE_EQ(400.0, *transformer.ratedNoLoadLoss());
  transformer.resetRatedNoLoadLoss();
  EXPECT_FALSE(transformer.ratedNoLoadLoss());

  EXPECT_TRUE(transformer.setRatedLoadLoss(850.0));
  ASSERT_TRUE(transformer.ratedLoadLoss());
  EXPECT_DOUBLE_EQ(850.0, *transformer.ratedLoadLoss());
  transformer.resetRatedLoadLoss();
  EXPECT_FALSE(transformer.ratedLoadLoss());

  EXPECT_TRUE(transformer.setNameplateEfficiency(0.985));
  EXPECT_DOUBLE_EQ(0.985, transformer.nameplateEfficiency());
  transformer.resetNameplateEfficiency();
  EXPECT_TRUE(transformer.isNameplateEfficiencyDefaulted());

  EXPECT_TRUE(transformer.setPerUnitLoadforNameplateEfficiency(0.50));
  EXPECT_DOUBLE_EQ(0.50, transformer.perUnitLoadforNameplateEfficiency());
  transformer.resetPerUnitLoadforNameplateEfficiency();
  EXPECT_TRUE(transformer.isPerUnitLoadforNameplateEfficiencyDefaulted());

  EXPECT_TRUE(transformer.setReferenceTemperatureforNameplateEfficiency(75.0));
  EXPECT_DOUBLE_EQ(75.0, transformer.referenceTemperatureforNameplateEfficiency());
  transformer.resetReferenceTemperatureforNameplateEfficiency();
  EXPECT_TRUE(transformer.isReferenceTemperatureforNameplateEfficiencyDefaulted());

  EXPECT_TRUE(transformer.setPerUnitLoadforMaximumEfficiency(0.60));
  ASSERT_TRUE(transformer.perUnitLoadforMaximumEfficiency());
  EXPECT_DOUBLE_EQ(0.60, *transformer.perUnitLoadforMaximumEfficiency());
  transformer.resetPerUnitLoadforMaximumEfficiency();
  EXPECT_FALSE(transformer.perUnitLoadforMaximumEfficiency());

  EXPECT_TRUE(transformer.setConsiderTransformerLossforUtilityCost(true));
  EXPECT_TRUE(transformer.considerTransformerLossforUtilityCost());
  EXPECT_TRUE(transformer.setConsiderTransformerLossforUtilityCost(false));
  EXPECT_FALSE(transformer.considerTransformerLossforUtilityCost());
  transformer.resetConsiderTransformerLossforUtilityCost();
  EXPECT_TRUE(transformer.isConsiderTransformerLossforUtilityCostDefaulted());
}
