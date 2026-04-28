/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include <algorithm>

#include "EPModelFixture.hpp"
#include "../scaffolds/GeneratorInternalCombustionEngine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorInternalCombustionEngine_DefaultConstructor) {
  Model model;
  GeneratorInternalCombustionEngine generator(model);
  EXPECT_EQ(GeneratorInternalCombustionEngine::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorInternalCombustionEngine_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorInternalCombustionEngine generator(model);

  EXPECT_TRUE(generator.setRatedPowerOutput(98000.0));
  ASSERT_TRUE(generator.ratedPowerOutput());
  EXPECT_DOUBLE_EQ(98000.0, generator.ratedPowerOutput().get());

  EXPECT_TRUE(generator.setMinimumPartLoadRatio(0.25));
  ASSERT_TRUE(generator.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.25, generator.minimumPartLoadRatio().get());

  EXPECT_TRUE(generator.setMaximumPartLoadRatio(0.98));
  ASSERT_TRUE(generator.maximumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.98, generator.maximumPartLoadRatio().get());

  EXPECT_TRUE(generator.setOptimumPartLoadRatio(0.80));
  ASSERT_TRUE(generator.optimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.80, generator.optimumPartLoadRatio().get());

  EXPECT_TRUE(generator.setCoefficient1ofUFactorTimesAreaCurve(0.20));
  ASSERT_TRUE(generator.coefficient1ofUFactorTimesAreaCurve());
  EXPECT_DOUBLE_EQ(0.20, generator.coefficient1ofUFactorTimesAreaCurve().get());

  EXPECT_TRUE(generator.setCoefficient2ofUFactorTimesAreaCurve(1.2));
  ASSERT_TRUE(generator.coefficient2ofUFactorTimesAreaCurve());
  EXPECT_DOUBLE_EQ(1.2, generator.coefficient2ofUFactorTimesAreaCurve().get());

  EXPECT_TRUE(generator.setMaximumExhaustFlowperUnitofPowerOutput(2.9e-6));
  ASSERT_TRUE(generator.maximumExhaustFlowperUnitofPowerOutput());
  EXPECT_DOUBLE_EQ(2.9e-6, generator.maximumExhaustFlowperUnitofPowerOutput().get());

  EXPECT_TRUE(generator.setDesignMinimumExhaustTemperature(170.0));
  ASSERT_TRUE(generator.designMinimumExhaustTemperature());
  EXPECT_DOUBLE_EQ(170.0, generator.designMinimumExhaustTemperature().get());

  EXPECT_TRUE(generator.setFuelHigherHeatingValue(49800.0));
  ASSERT_TRUE(generator.fuelHigherHeatingValue());
  EXPECT_DOUBLE_EQ(49800.0, generator.fuelHigherHeatingValue().get());

  EXPECT_TRUE(generator.isDesignHeatRecoveryWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.designHeatRecoveryWaterFlowRate());
  EXPECT_TRUE(generator.setDesignHeatRecoveryWaterFlowRate(0.0015));
  EXPECT_DOUBLE_EQ(0.0015, generator.designHeatRecoveryWaterFlowRate());
  EXPECT_FALSE(generator.isDesignHeatRecoveryWaterFlowRateDefaulted());
  generator.resetDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(generator.isDesignHeatRecoveryWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.designHeatRecoveryWaterFlowRate());

  const auto fuelTypes = GeneratorInternalCombustionEngine::fuelTypeValues();
  EXPECT_FALSE(fuelTypes.empty());
  EXPECT_NE(std::find(fuelTypes.begin(), fuelTypes.end(), "Diesel"), fuelTypes.end());

  EXPECT_TRUE(generator.isFuelTypeDefaulted());
  EXPECT_EQ("Diesel", generator.fuelType());
  EXPECT_TRUE(generator.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", generator.fuelType());
  EXPECT_FALSE(generator.isFuelTypeDefaulted());
  generator.resetFuelType();
  EXPECT_TRUE(generator.isFuelTypeDefaulted());
  EXPECT_EQ("Diesel", generator.fuelType());

  EXPECT_TRUE(generator.isHeatRecoveryMaximumTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(80.0, generator.heatRecoveryMaximumTemperature());
  EXPECT_TRUE(generator.setHeatRecoveryMaximumTemperature(86.0));
  EXPECT_DOUBLE_EQ(86.0, generator.heatRecoveryMaximumTemperature());
  EXPECT_FALSE(generator.isHeatRecoveryMaximumTemperatureDefaulted());
  generator.resetHeatRecoveryMaximumTemperature();
  EXPECT_TRUE(generator.isHeatRecoveryMaximumTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(80.0, generator.heatRecoveryMaximumTemperature());
}
