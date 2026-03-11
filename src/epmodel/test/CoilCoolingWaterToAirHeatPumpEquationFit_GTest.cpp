/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_DefaultConstructor) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);
  EXPECT_EQ(CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_TRUE(coil.setRatedAirFlowRate(0.74));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.74, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  coil.resetRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateDefaulted());

  EXPECT_TRUE(coil.setRatedWaterFlowRate(0.0036));
  ASSERT_TRUE(coil.ratedWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0036, coil.ratedWaterFlowRate().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAutosized());
  coil.autosizeRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAutosized());
  coil.resetRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(7200.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(7200.0, coil.ratedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.resetRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityDefaulted());

  EXPECT_TRUE(coil.setRatedSensibleCoolingCapacity(6100.0));
  ASSERT_TRUE(coil.ratedSensibleCoolingCapacity());
  EXPECT_DOUBLE_EQ(6100.0, coil.ratedSensibleCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedSensibleCoolingCapacityAutosized());
  coil.autosizeRatedSensibleCoolingCapacity();
  EXPECT_TRUE(coil.isRatedSensibleCoolingCapacityAutosized());
  coil.resetRatedSensibleCoolingCapacity();
  EXPECT_TRUE(coil.isRatedSensibleCoolingCapacityDefaulted());

  EXPECT_TRUE(coil.isRatedCoolingCoefficientofPerformanceDefaulted());
  EXPECT_TRUE(coil.setRatedCoolingCoefficientofPerformance(4.3));
  EXPECT_DOUBLE_EQ(4.3, coil.ratedCoolingCoefficientofPerformance());
  EXPECT_FALSE(coil.isRatedCoolingCoefficientofPerformanceDefaulted());

  EXPECT_TRUE(coil.setRatedEnteringWaterTemperature(29.4));
  EXPECT_DOUBLE_EQ(29.4, coil.ratedEnteringWaterTemperature());

  EXPECT_TRUE(coil.setRatedEnteringAirDryBulbTemperature(24.1));
  EXPECT_DOUBLE_EQ(24.1, coil.ratedEnteringAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatedEnteringAirWetBulbTemperature(16.2));
  EXPECT_DOUBLE_EQ(16.2, coil.ratedEnteringAirWetBulbTemperature());

  EXPECT_TRUE(coil.setNominalTimeforCondensateRemovaltoBegin(0.4));
  EXPECT_DOUBLE_EQ(0.4, coil.nominalTimeforCondensateRemovaltoBegin());
  EXPECT_FALSE(coil.isNominalTimeforCondensateRemovaltoBeginDefaulted());
  coil.resetNominalTimeforCondensateRemovaltoBegin();
  EXPECT_TRUE(coil.isNominalTimeforCondensateRemovaltoBeginDefaulted());

  EXPECT_TRUE(coil.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(1.8));
  EXPECT_DOUBLE_EQ(1.8, coil.ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity());
  EXPECT_FALSE(coil.isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted());
  coil.resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  EXPECT_TRUE(coil.isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted());

  EXPECT_TRUE(coil.setMaximumCyclingRate(2.7));
  EXPECT_DOUBLE_EQ(2.7, coil.maximumCyclingRate());

  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(60.0));
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());

  EXPECT_TRUE(coil.setFanDelayTime(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.fanDelayTime());
}
