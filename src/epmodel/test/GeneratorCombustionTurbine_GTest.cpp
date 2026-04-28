/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GeneratorCombustionTurbine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorCombustionTurbine_DefaultConstructor) {
  Model model;
  GeneratorCombustionTurbine generator(model);
  EXPECT_EQ(GeneratorCombustionTurbine::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorCombustionTurbine_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorCombustionTurbine generator(model);

  EXPECT_TRUE(generator.setRatedPowerOutput(125000.0));
  ASSERT_TRUE(generator.ratedPowerOutput());
  EXPECT_DOUBLE_EQ(125000.0, generator.ratedPowerOutput().get());

  EXPECT_TRUE(generator.setMinimumPartLoadRatio(0.22));
  ASSERT_TRUE(generator.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.22, generator.minimumPartLoadRatio().get());

  EXPECT_TRUE(generator.setMaximumPartLoadRatio(0.95));
  ASSERT_TRUE(generator.maximumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.95, generator.maximumPartLoadRatio().get());

  EXPECT_TRUE(generator.setOptimumPartLoadRatio(0.78));
  ASSERT_TRUE(generator.optimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.78, generator.optimumPartLoadRatio().get());

  EXPECT_TRUE(generator.setCoefficient1ofUFactorTimesAreaCurve(0.21));
  ASSERT_TRUE(generator.coefficient1ofUFactorTimesAreaCurve());
  EXPECT_DOUBLE_EQ(0.21, generator.coefficient1ofUFactorTimesAreaCurve().get());

  EXPECT_TRUE(generator.setCoefficient2ofUFactorTimesAreaCurve(1.1));
  ASSERT_TRUE(generator.coefficient2ofUFactorTimesAreaCurve());
  EXPECT_DOUBLE_EQ(1.1, generator.coefficient2ofUFactorTimesAreaCurve().get());

  EXPECT_TRUE(generator.setMaximumExhaustFlowperUnitofPowerOutput(2.8e-6));
  ASSERT_TRUE(generator.maximumExhaustFlowperUnitofPowerOutput());
  EXPECT_DOUBLE_EQ(2.8e-6, generator.maximumExhaustFlowperUnitofPowerOutput().get());

  EXPECT_TRUE(generator.setDesignMinimumExhaustTemperature(180.0));
  ASSERT_TRUE(generator.designMinimumExhaustTemperature());
  EXPECT_DOUBLE_EQ(180.0, generator.designMinimumExhaustTemperature().get());

  EXPECT_TRUE(generator.setDesignAirInletTemperature(15.0));
  ASSERT_TRUE(generator.designAirInletTemperature());
  EXPECT_DOUBLE_EQ(15.0, generator.designAirInletTemperature().get());

  EXPECT_TRUE(generator.setFuelHigherHeatingValue(50500.0));
  ASSERT_TRUE(generator.fuelHigherHeatingValue());
  EXPECT_DOUBLE_EQ(50500.0, generator.fuelHigherHeatingValue().get());

  EXPECT_TRUE(generator.isDesignHeatRecoveryWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.designHeatRecoveryWaterFlowRate());
  EXPECT_TRUE(generator.setDesignHeatRecoveryWaterFlowRate(0.003));
  EXPECT_DOUBLE_EQ(0.003, generator.designHeatRecoveryWaterFlowRate());
  EXPECT_FALSE(generator.isDesignHeatRecoveryWaterFlowRateDefaulted());
  generator.resetDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(generator.isDesignHeatRecoveryWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, generator.designHeatRecoveryWaterFlowRate());

  EXPECT_TRUE(generator.isFuelTypeDefaulted());
  EXPECT_EQ("NaturalGas", generator.fuelType());
  EXPECT_TRUE(generator.setFuelType("Diesel"));
  EXPECT_EQ("Diesel", generator.fuelType());
  EXPECT_FALSE(generator.isFuelTypeDefaulted());
  generator.resetFuelType();
  EXPECT_TRUE(generator.isFuelTypeDefaulted());
  EXPECT_EQ("NaturalGas", generator.fuelType());

  EXPECT_TRUE(generator.isHeatRecoveryMaximumTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(80.0, generator.heatRecoveryMaximumTemperature());
  EXPECT_TRUE(generator.setHeatRecoveryMaximumTemperature(88.0));
  EXPECT_DOUBLE_EQ(88.0, generator.heatRecoveryMaximumTemperature());
  EXPECT_FALSE(generator.isHeatRecoveryMaximumTemperatureDefaulted());
  generator.resetHeatRecoveryMaximumTemperature();
  EXPECT_TRUE(generator.isHeatRecoveryMaximumTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(80.0, generator.heatRecoveryMaximumTemperature());
}
