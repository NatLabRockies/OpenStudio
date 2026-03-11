/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoilCoolingWaterToAirHeatPumpParameterEstimation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpParameterEstimation_DefaultConstructor) {
  Model model;
  CoilCoolingWaterToAirHeatPumpParameterEstimation coil(model);
  EXPECT_EQ(CoilCoolingWaterToAirHeatPumpParameterEstimation::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpParameterEstimation_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpParameterEstimation coil(model);

  EXPECT_TRUE(coil.setCompressorType("Scroll"));
  EXPECT_EQ("Scroll", coil.compressorType());

  EXPECT_TRUE(coil.setDesignSourceSideFlowRate(0.0036));
  EXPECT_DOUBLE_EQ(0.0036, coil.designSourceSideFlowRate());

  EXPECT_TRUE(coil.setNominalCoolingCoilCapacity(8400.0));
  EXPECT_DOUBLE_EQ(8400.0, coil.nominalCoolingCoilCapacity());

  EXPECT_TRUE(coil.setNominalTimeforCondensateRemovaltoBegin(300.0));
  EXPECT_DOUBLE_EQ(300.0, coil.nominalTimeforCondensateRemovaltoBegin());
  EXPECT_FALSE(coil.isNominalTimeforCondensateRemovaltoBeginDefaulted());
  coil.resetNominalTimeforCondensateRemovaltoBegin();
  EXPECT_TRUE(coil.isNominalTimeforCondensateRemovaltoBeginDefaulted());

  EXPECT_TRUE(coil.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(1.2));
  EXPECT_DOUBLE_EQ(1.2, coil.ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity());
  EXPECT_FALSE(coil.isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted());
  coil.resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  EXPECT_TRUE(coil.isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted());

  EXPECT_TRUE(coil.setHighPressureCutoff(3100000.0));
  EXPECT_DOUBLE_EQ(3100000.0, coil.highPressureCutoff());

  EXPECT_TRUE(coil.setLowPressureCutoff(320000.0));
  EXPECT_DOUBLE_EQ(320000.0, coil.lowPressureCutoff());

  EXPECT_TRUE(coil.setLoadSideTotalHeatTransferCoefficient(480.0));
  EXPECT_DOUBLE_EQ(480.0, coil.loadSideTotalHeatTransferCoefficient());

  EXPECT_TRUE(coil.setLoadSideOutsideSurfaceHeatTransferCoefficient(520.0));
  EXPECT_DOUBLE_EQ(520.0, coil.loadSideOutsideSurfaceHeatTransferCoefficient());

  EXPECT_TRUE(coil.setSuperheatTemperatureattheEvaporatorOutlet(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.superheatTemperatureattheEvaporatorOutlet());

  EXPECT_TRUE(coil.setCompressorPowerLosses(85.0));
  EXPECT_DOUBLE_EQ(85.0, coil.compressorPowerLosses());

  EXPECT_TRUE(coil.setCompressorEfficiency(0.83));
  EXPECT_DOUBLE_EQ(0.83, coil.compressorEfficiency());

  EXPECT_TRUE(coil.setCompressorPistonDisplacement(0.0009));
  ASSERT_TRUE(coil.compressorPistonDisplacement());
  EXPECT_DOUBLE_EQ(0.0009, coil.compressorPistonDisplacement().get());
  coil.resetCompressorPistonDisplacement();
  EXPECT_FALSE(coil.compressorPistonDisplacement());

  EXPECT_TRUE(coil.setCompressorSuctionDischargePressureDrop(20000.0));
  ASSERT_TRUE(coil.compressorSuctionDischargePressureDrop());
  EXPECT_DOUBLE_EQ(20000.0, coil.compressorSuctionDischargePressureDrop().get());
  coil.resetCompressorSuctionDischargePressureDrop();
  EXPECT_FALSE(coil.compressorSuctionDischargePressureDrop());

  EXPECT_TRUE(coil.setCompressorClearanceFactor(0.04));
  ASSERT_TRUE(coil.compressorClearanceFactor());
  EXPECT_DOUBLE_EQ(0.04, coil.compressorClearanceFactor().get());
  coil.resetCompressorClearanceFactor();
  EXPECT_FALSE(coil.compressorClearanceFactor());

  EXPECT_TRUE(coil.setRefrigerantVolumeFlowRate(0.0011));
  ASSERT_TRUE(coil.refrigerantVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.0011, coil.refrigerantVolumeFlowRate().get());
  coil.resetRefrigerantVolumeFlowRate();
  EXPECT_FALSE(coil.refrigerantVolumeFlowRate());

  EXPECT_TRUE(coil.setVolumeRatio(1.9));
  ASSERT_TRUE(coil.volumeRatio());
  EXPECT_DOUBLE_EQ(1.9, coil.volumeRatio().get());
  coil.resetVolumeRatio();
  EXPECT_FALSE(coil.volumeRatio());

  EXPECT_TRUE(coil.setLeakRateCoefficient(0.001));
  ASSERT_TRUE(coil.leakRateCoefficient());
  EXPECT_DOUBLE_EQ(0.001, coil.leakRateCoefficient().get());
  coil.resetLeakRateCoefficient();
  EXPECT_FALSE(coil.leakRateCoefficient());

  EXPECT_TRUE(coil.setSourceSideHeatTransferCoefficient(410.0));
  ASSERT_TRUE(coil.sourceSideHeatTransferCoefficient());
  EXPECT_DOUBLE_EQ(410.0, coil.sourceSideHeatTransferCoefficient().get());
  coil.resetSourceSideHeatTransferCoefficient();
  EXPECT_FALSE(coil.sourceSideHeatTransferCoefficient());

  EXPECT_TRUE(coil.setSourceSideHeatTransferResistance1(0.2));
  ASSERT_TRUE(coil.sourceSideHeatTransferResistance1());
  EXPECT_DOUBLE_EQ(0.2, coil.sourceSideHeatTransferResistance1().get());
  coil.resetSourceSideHeatTransferResistance1();
  EXPECT_FALSE(coil.sourceSideHeatTransferResistance1());

  EXPECT_TRUE(coil.setSourceSideHeatTransferResistance2(300.0));
  ASSERT_TRUE(coil.sourceSideHeatTransferResistance2());
  EXPECT_DOUBLE_EQ(300.0, coil.sourceSideHeatTransferResistance2().get());
  coil.resetSourceSideHeatTransferResistance2();
  EXPECT_FALSE(coil.sourceSideHeatTransferResistance2());

  EXPECT_TRUE(coil.setMaximumCyclingRate(3.0));
  EXPECT_DOUBLE_EQ(3.0, coil.maximumCyclingRate());
  EXPECT_FALSE(coil.isMaximumCyclingRateDefaulted());
  coil.resetMaximumCyclingRate();
  EXPECT_TRUE(coil.isMaximumCyclingRateDefaulted());

  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(45.0));
  EXPECT_DOUBLE_EQ(45.0, coil.latentCapacityTimeConstant());
  EXPECT_FALSE(coil.isLatentCapacityTimeConstantDefaulted());
  coil.resetLatentCapacityTimeConstant();
  EXPECT_TRUE(coil.isLatentCapacityTimeConstantDefaulted());

  EXPECT_TRUE(coil.setFanDelayTime(90.0));
  EXPECT_DOUBLE_EQ(90.0, coil.fanDelayTime());
  EXPECT_FALSE(coil.isFanDelayTimeDefaulted());
  coil.resetFanDelayTime();
  EXPECT_TRUE(coil.isFanDelayTimeDefaulted());
}
