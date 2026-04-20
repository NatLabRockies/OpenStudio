/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/CoilHeatingWaterToAirHeatPumpParameterEstimation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpParameterEstimation_DefaultConstructor) {
  Model model;
  CoilHeatingWaterToAirHeatPumpParameterEstimation coil(model);
  EXPECT_EQ(CoilHeatingWaterToAirHeatPumpParameterEstimation::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpParameterEstimation_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingWaterToAirHeatPumpParameterEstimation coil(model);

  EXPECT_TRUE(coil.setCompressorType("Scroll"));
  EXPECT_EQ("Scroll", coil.compressorType());

  EXPECT_TRUE(coil.setDesignSourceSideFlowRate(0.0038));
  EXPECT_DOUBLE_EQ(0.0038, coil.designSourceSideFlowRate());

  EXPECT_TRUE(coil.setGrossRatedHeatingCapacity(9500.0));
  EXPECT_DOUBLE_EQ(9500.0, coil.grossRatedHeatingCapacity());

  EXPECT_TRUE(coil.setHighPressureCutoff(3150000.0));
  EXPECT_DOUBLE_EQ(3150000.0, coil.highPressureCutoff());

  EXPECT_TRUE(coil.setLowPressureCutoff(325000.0));
  EXPECT_DOUBLE_EQ(325000.0, coil.lowPressureCutoff());

  EXPECT_TRUE(coil.setLoadSideTotalHeatTransferCoefficient(490.0));
  EXPECT_DOUBLE_EQ(490.0, coil.loadSideTotalHeatTransferCoefficient());

  EXPECT_TRUE(coil.setSuperheatTemperatureattheEvaporatorOutlet(6.5));
  EXPECT_DOUBLE_EQ(6.5, coil.superheatTemperatureattheEvaporatorOutlet());

  EXPECT_TRUE(coil.setCompressorPowerLosses(90.0));
  EXPECT_DOUBLE_EQ(90.0, coil.compressorPowerLosses());

  EXPECT_TRUE(coil.setCompressorEfficiency(0.84));
  EXPECT_DOUBLE_EQ(0.84, coil.compressorEfficiency());

  EXPECT_TRUE(coil.setCompressorPistonDisplacement(0.001));
  ASSERT_TRUE(coil.compressorPistonDisplacement());
  EXPECT_DOUBLE_EQ(0.001, coil.compressorPistonDisplacement().get());
  coil.resetCompressorPistonDisplacement();
  EXPECT_FALSE(coil.compressorPistonDisplacement());

  EXPECT_TRUE(coil.setCompressorSuctionDischargePressureDrop(18000.0));
  ASSERT_TRUE(coil.compressorSuctionDischargePressureDrop());
  EXPECT_DOUBLE_EQ(18000.0, coil.compressorSuctionDischargePressureDrop().get());
  coil.resetCompressorSuctionDischargePressureDrop();
  EXPECT_FALSE(coil.compressorSuctionDischargePressureDrop());

  EXPECT_TRUE(coil.setCompressorClearanceFactor(0.035));
  ASSERT_TRUE(coil.compressorClearanceFactor());
  EXPECT_DOUBLE_EQ(0.035, coil.compressorClearanceFactor().get());
  coil.resetCompressorClearanceFactor();
  EXPECT_FALSE(coil.compressorClearanceFactor());

  EXPECT_TRUE(coil.setRefrigerantVolumeFlowRate(0.0012));
  ASSERT_TRUE(coil.refrigerantVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.0012, coil.refrigerantVolumeFlowRate().get());
  coil.resetRefrigerantVolumeFlowRate();
  EXPECT_FALSE(coil.refrigerantVolumeFlowRate());

  EXPECT_TRUE(coil.setVolumeRatio(1.8));
  ASSERT_TRUE(coil.volumeRatio());
  EXPECT_DOUBLE_EQ(1.8, coil.volumeRatio().get());
  coil.resetVolumeRatio();
  EXPECT_FALSE(coil.volumeRatio());

  EXPECT_TRUE(coil.setLeakRateCoefficient(0.0009));
  ASSERT_TRUE(coil.leakRateCoefficient());
  EXPECT_DOUBLE_EQ(0.0009, coil.leakRateCoefficient().get());
  coil.resetLeakRateCoefficient();
  EXPECT_FALSE(coil.leakRateCoefficient());

  EXPECT_TRUE(coil.setSourceSideHeatTransferCoefficient(415.0));
  ASSERT_TRUE(coil.sourceSideHeatTransferCoefficient());
  EXPECT_DOUBLE_EQ(415.0, coil.sourceSideHeatTransferCoefficient().get());
  coil.resetSourceSideHeatTransferCoefficient();
  EXPECT_FALSE(coil.sourceSideHeatTransferCoefficient());

  EXPECT_TRUE(coil.setSourceSideHeatTransferResistance1(0.25));
  ASSERT_TRUE(coil.sourceSideHeatTransferResistance1());
  EXPECT_DOUBLE_EQ(0.25, coil.sourceSideHeatTransferResistance1().get());
  coil.resetSourceSideHeatTransferResistance1();
  EXPECT_FALSE(coil.sourceSideHeatTransferResistance1());

  EXPECT_TRUE(coil.setSourceSideHeatTransferResistance2(305.0));
  ASSERT_TRUE(coil.sourceSideHeatTransferResistance2());
  EXPECT_DOUBLE_EQ(305.0, coil.sourceSideHeatTransferResistance2().get());
  coil.resetSourceSideHeatTransferResistance2();
  EXPECT_FALSE(coil.sourceSideHeatTransferResistance2());
}
