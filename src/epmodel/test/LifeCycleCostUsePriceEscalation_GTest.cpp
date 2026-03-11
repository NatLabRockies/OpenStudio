/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/LifeCycleCostUsePriceEscalation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, LifeCycleCostUsePriceEscalation_DefaultConstructor) {
  Model model;
  LifeCycleCostUsePriceEscalation lifeCycleCostUsePriceEscalation(model);

  EXPECT_EQ(LifeCycleCostUsePriceEscalation::iddObjectType(), lifeCycleCostUsePriceEscalation.iddObject().type());
}

TEST_F(EPModelFixture, LifeCycleCostUsePriceEscalation_ScalarAccessors_RoundTrip) {
  Model model;
  LifeCycleCostUsePriceEscalation lifeCycleCostUsePriceEscalation(model);

  const auto resources = LifeCycleCostUsePriceEscalation::resourceValues();
  EXPECT_FALSE(resources.empty());

  const auto months = LifeCycleCostUsePriceEscalation::escalationStartMonthValues();
  EXPECT_FALSE(months.empty());

  EXPECT_TRUE(lifeCycleCostUsePriceEscalation.setResource("Electricity"));
  EXPECT_EQ("Electricity", lifeCycleCostUsePriceEscalation.resource());

  EXPECT_FALSE(lifeCycleCostUsePriceEscalation.setResource("BadResource"));
  EXPECT_EQ("Electricity", lifeCycleCostUsePriceEscalation.resource());

  EXPECT_TRUE(lifeCycleCostUsePriceEscalation.setEscalationStartYear(2026));
  ASSERT_TRUE(lifeCycleCostUsePriceEscalation.escalationStartYear());
  EXPECT_EQ(2026, lifeCycleCostUsePriceEscalation.escalationStartYear().get());

  EXPECT_FALSE(lifeCycleCostUsePriceEscalation.setEscalationStartYear(1800));
  ASSERT_TRUE(lifeCycleCostUsePriceEscalation.escalationStartYear());
  EXPECT_EQ(2026, lifeCycleCostUsePriceEscalation.escalationStartYear().get());

  lifeCycleCostUsePriceEscalation.resetEscalationStartYear();
  EXPECT_FALSE(lifeCycleCostUsePriceEscalation.escalationStartYear());

  EXPECT_TRUE(lifeCycleCostUsePriceEscalation.isEscalationStartMonthDefaulted());
  EXPECT_EQ("January", lifeCycleCostUsePriceEscalation.escalationStartMonth());

  EXPECT_TRUE(lifeCycleCostUsePriceEscalation.setEscalationStartMonth("February"));
  EXPECT_FALSE(lifeCycleCostUsePriceEscalation.isEscalationStartMonthDefaulted());
  EXPECT_EQ("February", lifeCycleCostUsePriceEscalation.escalationStartMonth());

  EXPECT_FALSE(lifeCycleCostUsePriceEscalation.setEscalationStartMonth("NotAMonth"));
  EXPECT_EQ("February", lifeCycleCostUsePriceEscalation.escalationStartMonth());

  lifeCycleCostUsePriceEscalation.resetEscalationStartMonth();
  EXPECT_TRUE(lifeCycleCostUsePriceEscalation.isEscalationStartMonthDefaulted());
  EXPECT_EQ("January", lifeCycleCostUsePriceEscalation.escalationStartMonth());
}
