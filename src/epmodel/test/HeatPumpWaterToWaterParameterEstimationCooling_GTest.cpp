/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HeatPumpWaterToWaterParameterEstimationCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpWaterToWaterParameterEstimationCooling_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterParameterEstimationCooling hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterParameterEstimationCooling::iddObjectType(), hp.iddObject().type());

  EXPECT_FALSE(hp.nominalCOP());
  EXPECT_FALSE(hp.nominalCapacity());
  EXPECT_FALSE(hp.minimumPartLoadRatio());
  EXPECT_FALSE(hp.maximumPartLoadRatio());
  EXPECT_FALSE(hp.optimumPartLoadRatio());
  EXPECT_FALSE(hp.loadSideFlowRate());
  EXPECT_FALSE(hp.sourceSideFlowRate());
  EXPECT_FALSE(hp.loadSideHeatTransferCoefficient());
  EXPECT_FALSE(hp.sourceSideHeatTransferCoefficient());
  EXPECT_FALSE(hp.pistonDisplacement());
  EXPECT_FALSE(hp.compressorClearanceFactor());
  EXPECT_FALSE(hp.compressorSuctionandDischargePressureDrop());
  EXPECT_FALSE(hp.superheating());
  EXPECT_FALSE(hp.constantPartofElectromechanicalPowerLosses());
  EXPECT_FALSE(hp.lossFactor());

  EXPECT_TRUE(hp.isHighPressureCutOffDefaulted());
  EXPECT_TRUE(hp.isLowPressureCutOffDefaulted());
  EXPECT_DOUBLE_EQ(500000000.0, hp.highPressureCutOff());
  EXPECT_DOUBLE_EQ(0.0, hp.lowPressureCutOff());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterParameterEstimationCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterParameterEstimationCooling hp(model);

  EXPECT_TRUE(hp.setNominalCOP(4.25));
  ASSERT_TRUE(hp.nominalCOP());
  EXPECT_DOUBLE_EQ(4.25, hp.nominalCOP().get());

  EXPECT_TRUE(hp.setNominalCapacity(12500.0));
  ASSERT_TRUE(hp.nominalCapacity());
  EXPECT_DOUBLE_EQ(12500.0, hp.nominalCapacity().get());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.15));
  ASSERT_TRUE(hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.15, hp.minimumPartLoadRatio().get());

  EXPECT_TRUE(hp.setMaximumPartLoadRatio(1.0));
  ASSERT_TRUE(hp.maximumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, hp.maximumPartLoadRatio().get());

  EXPECT_TRUE(hp.setOptimumPartLoadRatio(0.75));
  ASSERT_TRUE(hp.optimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.75, hp.optimumPartLoadRatio().get());

  EXPECT_TRUE(hp.setLoadSideFlowRate(0.002));
  ASSERT_TRUE(hp.loadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.002, hp.loadSideFlowRate().get());

  EXPECT_TRUE(hp.setSourceSideFlowRate(0.0025));
  ASSERT_TRUE(hp.sourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.0025, hp.sourceSideFlowRate().get());

  EXPECT_TRUE(hp.setLoadSideHeatTransferCoefficient(500.0));
  ASSERT_TRUE(hp.loadSideHeatTransferCoefficient());
  EXPECT_DOUBLE_EQ(500.0, hp.loadSideHeatTransferCoefficient().get());

  EXPECT_TRUE(hp.setSourceSideHeatTransferCoefficient(525.0));
  ASSERT_TRUE(hp.sourceSideHeatTransferCoefficient());
  EXPECT_DOUBLE_EQ(525.0, hp.sourceSideHeatTransferCoefficient().get());

  EXPECT_TRUE(hp.setPistonDisplacement(0.0001));
  ASSERT_TRUE(hp.pistonDisplacement());
  EXPECT_DOUBLE_EQ(0.0001, hp.pistonDisplacement().get());

  EXPECT_TRUE(hp.setCompressorClearanceFactor(0.04));
  ASSERT_TRUE(hp.compressorClearanceFactor());
  EXPECT_DOUBLE_EQ(0.04, hp.compressorClearanceFactor().get());

  EXPECT_TRUE(hp.setCompressorSuctionandDischargePressureDrop(45000.0));
  ASSERT_TRUE(hp.compressorSuctionandDischargePressureDrop());
  EXPECT_DOUBLE_EQ(45000.0, hp.compressorSuctionandDischargePressureDrop().get());

  EXPECT_TRUE(hp.setSuperheating(5.0));
  ASSERT_TRUE(hp.superheating());
  EXPECT_DOUBLE_EQ(5.0, hp.superheating().get());

  EXPECT_TRUE(hp.setConstantPartofElectromechanicalPowerLosses(120.0));
  ASSERT_TRUE(hp.constantPartofElectromechanicalPowerLosses());
  EXPECT_DOUBLE_EQ(120.0, hp.constantPartofElectromechanicalPowerLosses().get());

  EXPECT_TRUE(hp.setLossFactor(0.08));
  ASSERT_TRUE(hp.lossFactor());
  EXPECT_DOUBLE_EQ(0.08, hp.lossFactor().get());

  EXPECT_TRUE(hp.setHighPressureCutOff(410000000.0));
  EXPECT_FALSE(hp.isHighPressureCutOffDefaulted());
  EXPECT_DOUBLE_EQ(410000000.0, hp.highPressureCutOff());
  hp.resetHighPressureCutOff();
  EXPECT_TRUE(hp.isHighPressureCutOffDefaulted());
  EXPECT_DOUBLE_EQ(500000000.0, hp.highPressureCutOff());

  EXPECT_TRUE(hp.setLowPressureCutOff(1234.0));
  EXPECT_FALSE(hp.isLowPressureCutOffDefaulted());
  EXPECT_DOUBLE_EQ(1234.0, hp.lowPressureCutOff());
  hp.resetLowPressureCutOff();
  EXPECT_TRUE(hp.isLowPressureCutOffDefaulted());
  EXPECT_DOUBLE_EQ(0.0, hp.lowPressureCutOff());
}
