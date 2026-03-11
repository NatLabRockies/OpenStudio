/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterEquationFitCooling::iddObjectType(), hp.iddObject().type());

  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_TRUE(hp.isRatedCoolingCapacityAutosized());
  EXPECT_TRUE(hp.isRatedCoolingPowerConsumptionAutosized());

  EXPECT_FALSE(hp.referenceLoadSideFlowRate());
  EXPECT_FALSE(hp.referenceSourceSideFlowRate());
  EXPECT_FALSE(hp.ratedCoolingCapacity());
  EXPECT_FALSE(hp.ratedCoolingPowerConsumption());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());

  EXPECT_DOUBLE_EQ(8.0, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_TRUE(hp.setReferenceLoadSideFlowRate(0.101));
  ASSERT_TRUE(hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.101, hp.ratedLoadSideFlowRate());

  EXPECT_TRUE(hp.setRatedLoadSideFlowRate(0.111));
  ASSERT_TRUE(hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.111, *hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.111, hp.ratedLoadSideFlowRate());

  hp.autosizeReferenceLoadSideFlowRate();
  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());

  EXPECT_TRUE(hp.setReferenceSourceSideFlowRate(0.202));
  ASSERT_TRUE(hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.202, hp.ratedSourceSideFlowRate());

  EXPECT_TRUE(hp.setRatedSourceSideFlowRate(0.222));
  ASSERT_TRUE(hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.222, *hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.222, hp.ratedSourceSideFlowRate());

  hp.autosizeReferenceSourceSideFlowRate();
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());

  EXPECT_TRUE(hp.setRatedCoolingCapacity(12450.0));
  ASSERT_TRUE(hp.ratedCoolingCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.ratedCoolingCapacity());
  hp.autosizeRatedCoolingCapacity();
  EXPECT_TRUE(hp.isRatedCoolingCapacityAutosized());
  EXPECT_FALSE(hp.ratedCoolingCapacity());

  EXPECT_TRUE(hp.setRatedCoolingPowerConsumption(3450.0));
  ASSERT_TRUE(hp.ratedCoolingPowerConsumption());
  EXPECT_DOUBLE_EQ(3450.0, *hp.ratedCoolingPowerConsumption());
  hp.autosizeRatedCoolingPowerConsumption();
  EXPECT_TRUE(hp.isRatedCoolingPowerConsumptionAutosized());
  EXPECT_FALSE(hp.ratedCoolingPowerConsumption());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(7.25));
  EXPECT_DOUBLE_EQ(7.25, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());
}
