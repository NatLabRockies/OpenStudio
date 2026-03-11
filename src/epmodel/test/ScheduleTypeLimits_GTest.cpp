/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleTypeLimits_DefaultConstructor) {
  Model model;
  ScheduleTypeLimits scheduleTypeLimits(model);
  EXPECT_EQ(ScheduleTypeLimits::iddObjectType(), scheduleTypeLimits.iddObject().type());
}

TEST_F(EPModelFixture, ScheduleTypeLimits_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleTypeLimits scheduleTypeLimits(model);

  EXPECT_TRUE(scheduleTypeLimits.setLowerLimitValue(-10.0));
  ASSERT_TRUE(scheduleTypeLimits.lowerLimitValue());
  EXPECT_DOUBLE_EQ(-10.0, scheduleTypeLimits.lowerLimitValue().get());

  EXPECT_TRUE(scheduleTypeLimits.setUpperLimitValue(75.0));
  ASSERT_TRUE(scheduleTypeLimits.upperLimitValue());
  EXPECT_DOUBLE_EQ(75.0, scheduleTypeLimits.upperLimitValue().get());

  EXPECT_TRUE(scheduleTypeLimits.setNumericType("Continuous"));
  ASSERT_TRUE(scheduleTypeLimits.numericType());
  EXPECT_EQ("Continuous", scheduleTypeLimits.numericType().get());

  EXPECT_TRUE(scheduleTypeLimits.setUnitType("Temperature"));
  EXPECT_EQ("Temperature", scheduleTypeLimits.unitType());
  EXPECT_FALSE(scheduleTypeLimits.isUnitTypeDefaulted());

  scheduleTypeLimits.resetNumericType();
  EXPECT_FALSE(scheduleTypeLimits.numericType());

  scheduleTypeLimits.resetLowerLimitValue();
  EXPECT_FALSE(scheduleTypeLimits.lowerLimitValue());

  scheduleTypeLimits.resetUpperLimitValue();
  EXPECT_FALSE(scheduleTypeLimits.upperLimitValue());

  scheduleTypeLimits.resetUnitType();
  EXPECT_TRUE(scheduleTypeLimits.isUnitTypeDefaulted());
}
