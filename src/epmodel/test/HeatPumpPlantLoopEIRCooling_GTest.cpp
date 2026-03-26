/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_DefaultConstructor) {
  Model model;
  HeatPumpPlantLoopEIRCooling hp(model);

  EXPECT_EQ(HeatPumpPlantLoopEIRCooling::iddObjectType(), hp.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.tertiaryInletPort());
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());

  EXPECT_DOUBLE_EQ(7.5, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_EQ("Load", hp.controlType());
  EXPECT_EQ("ConstantFlow", hp.flowMode());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(-100.0, hp.minimumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(100.0, hp.maximumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(60.0, hp.maximumHeatRecoveryOutletTemperature());
  EXPECT_DOUBLE_EQ(0.0, hp.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRCooling hp(model);

  const auto condenserTypes = HeatPumpPlantLoopEIRCooling::condenserTypeValues();
  ASSERT_FALSE(condenserTypes.empty());
  EXPECT_TRUE(hp.setCondenserType(condenserTypes.front()));
  EXPECT_EQ(condenserTypes.front(), hp.condenserType());

  EXPECT_TRUE(hp.setLoadSideReferenceFlowRate(0.101));
  ASSERT_TRUE(hp.loadSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.loadSideReferenceFlowRate());
  hp.autosizeLoadSideReferenceFlowRate();
  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setSourceSideReferenceFlowRate(0.202));
  ASSERT_TRUE(hp.sourceSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.sourceSideReferenceFlowRate());
  hp.autosizeSourceSideReferenceFlowRate();
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setHeatRecoveryReferenceFlowRate(0.303));
  ASSERT_TRUE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.303, *hp.heatRecoveryReferenceFlowRate());
  hp.autosizeHeatRecoveryReferenceFlowRate();
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setReferenceCapacity(12450.0));
  ASSERT_TRUE(hp.referenceCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.referenceCapacity());
  hp.autosizeReferenceCapacity();
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.9));
  EXPECT_DOUBLE_EQ(6.9, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());

  EXPECT_TRUE(hp.setControlType("Setpoint"));
  EXPECT_EQ("Setpoint", hp.controlType());

  EXPECT_TRUE(hp.setFlowMode("VariableSpeedPumping"));
  EXPECT_EQ("VariableSpeedPumping", hp.flowMode());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.25));
  EXPECT_DOUBLE_EQ(0.25, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMinimumSourceInletTemperature(-9.0));
  EXPECT_DOUBLE_EQ(-9.0, hp.minimumSourceInletTemperature());

  EXPECT_TRUE(hp.setMaximumSourceInletTemperature(77.0));
  EXPECT_DOUBLE_EQ(77.0, hp.maximumSourceInletTemperature());

  EXPECT_TRUE(hp.setMaximumHeatRecoveryOutletTemperature(51.0));
  EXPECT_DOUBLE_EQ(51.0, hp.maximumHeatRecoveryOutletTemperature());

  EXPECT_TRUE(hp.setThermosiphonMinimumTemperatureDifference(0.9));
  EXPECT_DOUBLE_EQ(0.9, hp.thermosiphonMinimumTemperatureDifference());
}
