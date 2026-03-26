/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectricEIR_DefaultConstructor) {
  Model model;
  ChillerElectricEIR chiller(model);
  EXPECT_EQ(ChillerElectricEIR::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());
}

TEST_F(EPModelFixture, ChillerElectricEIR_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectricEIR chiller(model);

  EXPECT_TRUE(chiller.setReferenceCapacity(700000.0));
  ASSERT_TRUE(chiller.referenceCapacity());
  EXPECT_DOUBLE_EQ(700000.0, *chiller.referenceCapacity());
  EXPECT_FALSE(chiller.isReferenceCapacityAutosized());
  chiller.autosizeReferenceCapacity();
  EXPECT_TRUE(chiller.isReferenceCapacityAutosized());

  EXPECT_TRUE(chiller.setReferenceCOP(4.0));
  EXPECT_DOUBLE_EQ(4.0, chiller.referenceCOP());

  EXPECT_TRUE(chiller.setReferenceLeavingChilledWaterTemperature(6.5));
  EXPECT_DOUBLE_EQ(6.5, chiller.referenceLeavingChilledWaterTemperature());
  chiller.resetReferenceLeavingChilledWaterTemperature();
  EXPECT_TRUE(chiller.isReferenceLeavingChilledWaterTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceChilledWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.referenceChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, *chiller.referenceChilledWaterFlowRate());
  chiller.autosizeReferenceChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  chiller.resetCondenserType();
  EXPECT_TRUE(chiller.isCondenserTypeDefaulted());

  EXPECT_TRUE(chiller.setChillerFlowMode("LeavingSetpointModulated"));
  EXPECT_EQ("LeavingSetpointModulated", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.01));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.01, *chiller.designHeatRecoveryWaterFlowRate());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());

  EXPECT_TRUE(chiller.setBasinHeaterSetpointTemperature(5.0));
  EXPECT_DOUBLE_EQ(5.0, chiller.basinHeaterSetpointTemperature());
  chiller.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(chiller.isBasinHeaterSetpointTemperatureDefaulted());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserHeatRecoveryRelativeCapacityFraction());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());

  EXPECT_TRUE(chiller.setCondenserFlowControl("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());

  EXPECT_TRUE(chiller.setCondenserMinimumFlowFraction(0.25));
  EXPECT_DOUBLE_EQ(0.25, chiller.condenserMinimumFlowFraction());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(0.3));
  EXPECT_DOUBLE_EQ(0.3, chiller.thermosiphonMinimumTemperatureDifference());
}
