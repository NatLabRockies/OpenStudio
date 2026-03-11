/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ChillerElectric.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectric_DefaultConstructor) {
  Model model;
  ChillerElectric chiller(model);
  EXPECT_EQ(ChillerElectric::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectric chiller(model);

  EXPECT_TRUE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  chiller.resetCondenserType();
  EXPECT_TRUE(chiller.isCondenserTypeDefaulted());

  EXPECT_TRUE(chiller.setNominalCapacity(700000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(700000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, chiller.nominalCOP());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.12));
  ASSERT_TRUE(chiller.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.12, chiller.minimumPartLoadRatio().get());
  chiller.resetMinimumPartLoadRatio();
  EXPECT_FALSE(chiller.minimumPartLoadRatio());

  EXPECT_TRUE(chiller.setTemperatureRiseCoefficient(1.6));
  EXPECT_DOUBLE_EQ(1.6, chiller.temperatureRiseCoefficient());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.024));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.024, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());
  chiller.resetDesignChilledWaterFlowRate();
  EXPECT_FALSE(chiller.designChilledWaterFlowRate());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.007));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.007, chiller.designHeatRecoveryWaterFlowRate().get());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setBasinHeaterSetpointTemperature(6.2));
  EXPECT_DOUBLE_EQ(6.2, chiller.basinHeaterSetpointTemperature());
  chiller.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(chiller.isBasinHeaterSetpointTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(2.0, chiller.basinHeaterSetpointTemperature());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.4));
  ASSERT_TRUE(chiller.condenserHeatRecoveryRelativeCapacityFraction());
  EXPECT_DOUBLE_EQ(0.4, chiller.condenserHeatRecoveryRelativeCapacityFraction().get());
  chiller.resetCondenserHeatRecoveryRelativeCapacityFraction();
  EXPECT_FALSE(chiller.condenserHeatRecoveryRelativeCapacityFraction());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());
  chiller.resetEndUseSubcategory();
  EXPECT_TRUE(chiller.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(1.2));
  EXPECT_DOUBLE_EQ(1.2, chiller.thermosiphonMinimumTemperatureDifference());
  chiller.resetThermosiphonMinimumTemperatureDifference();
  EXPECT_TRUE(chiller.isThermosiphonMinimumTemperatureDifferenceDefaulted());
  EXPECT_DOUBLE_EQ(0.0, chiller.thermosiphonMinimumTemperatureDifference());
}
