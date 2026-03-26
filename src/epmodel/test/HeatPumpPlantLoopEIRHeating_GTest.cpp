/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_DefaultConstructor) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  EXPECT_EQ(HeatPumpPlantLoopEIRHeating::iddObjectType(), hp.iddObject().type());
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
  EXPECT_DOUBLE_EQ(1.0, hp.heatingToCoolingCapacitySizingRatio());
  EXPECT_EQ("CoolingCapacity", hp.heatPumpSizingMethod());
  EXPECT_EQ("Load", hp.controlType());
  EXPECT_EQ("ConstantFlow", hp.flowMode());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(-100.0, hp.minimumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(100.0, hp.maximumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(10.0, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());
  EXPECT_EQ("None", hp.heatPumpDefrostControl());
  EXPECT_DOUBLE_EQ(0.058333, hp.heatPumpDefrostTimePeriodFraction());
  EXPECT_DOUBLE_EQ(4.5, hp.minimumHeatRecoveryOutletTemperature());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  const auto condenserTypes = HeatPumpPlantLoopEIRHeating::condenserTypeValues();
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

  EXPECT_TRUE(hp.setHeatingToCoolingCapacitySizingRatio(1.08));
  EXPECT_DOUBLE_EQ(1.08, hp.heatingToCoolingCapacitySizingRatio());

  EXPECT_TRUE(hp.setHeatPumpSizingMethod("CoolingCapacity"));
  EXPECT_EQ("CoolingCapacity", hp.heatPumpSizingMethod());

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

  EXPECT_TRUE(hp.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(5.0));
  EXPECT_DOUBLE_EQ(5.0, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());

  EXPECT_TRUE(hp.setHeatPumpDefrostControl("None"));
  EXPECT_EQ("None", hp.heatPumpDefrostControl());

  EXPECT_TRUE(hp.setHeatPumpDefrostTimePeriodFraction(0.08));
  EXPECT_DOUBLE_EQ(0.08, hp.heatPumpDefrostTimePeriodFraction());

  EXPECT_TRUE(hp.setMinimumHeatRecoveryOutletTemperature(6.0));
  EXPECT_DOUBLE_EQ(6.0, hp.minimumHeatRecoveryOutletTemperature());
}
