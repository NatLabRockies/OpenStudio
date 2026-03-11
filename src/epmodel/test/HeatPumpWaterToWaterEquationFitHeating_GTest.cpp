/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterEquationFitHeating::iddObjectType(), hp.iddObject().type());

  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_TRUE(hp.isRatedHeatingCapacityAutosized());
  EXPECT_TRUE(hp.isRatedHeatingPowerConsumptionAutosized());

  EXPECT_FALSE(hp.referenceLoadSideFlowRate());
  EXPECT_FALSE(hp.referenceSourceSideFlowRate());
  EXPECT_FALSE(hp.ratedHeatingCapacity());
  EXPECT_FALSE(hp.ratedHeatingPowerConsumption());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());

  EXPECT_DOUBLE_EQ(7.5, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

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

  EXPECT_TRUE(hp.setRatedHeatingCapacity(12450.0));
  ASSERT_TRUE(hp.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.ratedHeatingCapacity());
  hp.autosizeRatedHeatingCapacity();
  EXPECT_TRUE(hp.isRatedHeatingCapacityAutosized());
  EXPECT_FALSE(hp.ratedHeatingCapacity());

  EXPECT_TRUE(hp.setRatedHeatingPowerConsumption(3450.0));
  ASSERT_TRUE(hp.ratedHeatingPowerConsumption());
  EXPECT_DOUBLE_EQ(3450.0, *hp.ratedHeatingPowerConsumption());
  hp.autosizeRatedHeatingPowerConsumption();
  EXPECT_TRUE(hp.isRatedHeatingPowerConsumptionAutosized());
  EXPECT_FALSE(hp.ratedHeatingPowerConsumption());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.5));
  EXPECT_DOUBLE_EQ(6.5, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());
}
