/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/DemandManagerAssignmentList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DemandManagerAssignmentList_DefaultConstructor) {
  Model model;
  DemandManagerAssignmentList object(model);
  EXPECT_EQ(DemandManagerAssignmentList::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, DemandManagerAssignmentList_ScalarAccessors_RoundTrip) {
  Model model;
  DemandManagerAssignmentList object(model);

  EXPECT_FALSE(DemandManagerAssignmentList::demandManagerPriorityValues().empty());

  EXPECT_TRUE(object.setMeterName("Electricity:Facility"));
  EXPECT_EQ("Electricity:Facility", object.meterName());

  EXPECT_TRUE(object.setDemandLimitSafetyFraction(0.9));
  EXPECT_DOUBLE_EQ(0.9, object.demandLimitSafetyFraction());
  EXPECT_FALSE(object.setDemandLimitSafetyFraction(-0.1));
  EXPECT_DOUBLE_EQ(0.9, object.demandLimitSafetyFraction());

  EXPECT_TRUE(object.setDemandWindowLength(15));
  EXPECT_EQ(15, object.demandWindowLength());
  EXPECT_FALSE(object.setDemandWindowLength(0));
  EXPECT_EQ(15, object.demandWindowLength());

  EXPECT_TRUE(object.setDemandManagerPriority("Sequential"));
  EXPECT_EQ("Sequential", object.demandManagerPriority());
  EXPECT_FALSE(object.setDemandManagerPriority("InvalidPriority"));
  EXPECT_EQ("Sequential", object.demandManagerPriority());
}
