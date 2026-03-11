/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/LifeCycleCost.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, LifeCycleCost_DefaultConstructor) {
  Model model;
  LifeCycleCost lifeCycleCost(model);
  EXPECT_EQ(LifeCycleCost::iddObjectType(), lifeCycleCost.iddObject().type());
}

TEST_F(EPModelFixture, LifeCycleCost_ScalarAccessors_RoundTrip) {
  Model model;
  LifeCycleCost lifeCycleCost(model);

  EXPECT_EQ("Maintenance", lifeCycleCost.category());
  EXPECT_TRUE(lifeCycleCost.isStartOfCostsDefaulted());
  EXPECT_EQ("ServicePeriod", lifeCycleCost.startOfCosts());
  EXPECT_TRUE(lifeCycleCost.isYearsFromStartDefaulted());
  EXPECT_EQ(0, lifeCycleCost.yearsFromStart());
  EXPECT_TRUE(lifeCycleCost.isMonthsFromStartDefaulted());
  EXPECT_EQ(0, lifeCycleCost.monthsFromStart());
  EXPECT_TRUE(lifeCycleCost.isRepeatPeriodYearsDefaulted());
  EXPECT_EQ(1, lifeCycleCost.repeatPeriodYears());
  EXPECT_TRUE(lifeCycleCost.isRepeatPeriodMonthsDefaulted());
  EXPECT_EQ(0, lifeCycleCost.repeatPeriodMonths());

  EXPECT_TRUE(lifeCycleCost.setCategory("Repair"));
  EXPECT_EQ("Repair", lifeCycleCost.category());

  EXPECT_TRUE(lifeCycleCost.setCost(12345.67));
  EXPECT_DOUBLE_EQ(12345.67, lifeCycleCost.cost());

  EXPECT_TRUE(lifeCycleCost.setStartOfCosts("BasePeriod"));
  EXPECT_EQ("BasePeriod", lifeCycleCost.startOfCosts());
  EXPECT_FALSE(lifeCycleCost.isStartOfCostsDefaulted());
  lifeCycleCost.resetStartOfCosts();
  EXPECT_EQ("ServicePeriod", lifeCycleCost.startOfCosts());
  EXPECT_TRUE(lifeCycleCost.isStartOfCostsDefaulted());

  EXPECT_TRUE(lifeCycleCost.setYearsFromStart(4));
  EXPECT_EQ(4, lifeCycleCost.yearsFromStart());
  EXPECT_FALSE(lifeCycleCost.isYearsFromStartDefaulted());
  lifeCycleCost.resetYearsFromStart();
  EXPECT_EQ(0, lifeCycleCost.yearsFromStart());
  EXPECT_TRUE(lifeCycleCost.isYearsFromStartDefaulted());

  EXPECT_TRUE(lifeCycleCost.setMonthsFromStart(7));
  EXPECT_EQ(7, lifeCycleCost.monthsFromStart());
  EXPECT_FALSE(lifeCycleCost.isMonthsFromStartDefaulted());
  lifeCycleCost.resetMonthsFromStart();
  EXPECT_EQ(0, lifeCycleCost.monthsFromStart());
  EXPECT_TRUE(lifeCycleCost.isMonthsFromStartDefaulted());

  EXPECT_TRUE(lifeCycleCost.setRepeatPeriodYears(3));
  EXPECT_EQ(3, lifeCycleCost.repeatPeriodYears());
  EXPECT_FALSE(lifeCycleCost.isRepeatPeriodYearsDefaulted());
  lifeCycleCost.resetRepeatPeriodYears();
  EXPECT_EQ(1, lifeCycleCost.repeatPeriodYears());
  EXPECT_TRUE(lifeCycleCost.isRepeatPeriodYearsDefaulted());

  EXPECT_TRUE(lifeCycleCost.setRepeatPeriodMonths(6));
  EXPECT_EQ(6, lifeCycleCost.repeatPeriodMonths());
  EXPECT_FALSE(lifeCycleCost.isRepeatPeriodMonthsDefaulted());
  lifeCycleCost.resetRepeatPeriodMonths();
  EXPECT_EQ(0, lifeCycleCost.repeatPeriodMonths());
  EXPECT_TRUE(lifeCycleCost.isRepeatPeriodMonthsDefaulted());

  const auto categories = LifeCycleCost::validCategoryValues();
  EXPECT_FALSE(categories.empty());
  const auto startOfCostsValues = LifeCycleCost::validStartOfCostsValues();
  EXPECT_FALSE(startOfCostsValues.empty());
}
