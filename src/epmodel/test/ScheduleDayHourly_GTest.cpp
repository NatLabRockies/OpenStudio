/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ScheduleDayHourly.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleDayHourly_DefaultConstructor) {
  Model model;
  ScheduleDayHourly schedule(model);
  EXPECT_EQ(ScheduleDayHourly::iddObjectType(), schedule.iddObject().type());
  EXPECT_FALSE(schedule.nameString().empty());
}

TEST_F(EPModelFixture, ScheduleDayHourly_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleDayHourly schedule(model);

  EXPECT_TRUE(schedule.isHour1Defaulted());
  EXPECT_TRUE(schedule.setHour1(0.25));
  EXPECT_DOUBLE_EQ(0.25, schedule.hour1());
  EXPECT_FALSE(schedule.isHour1Defaulted());
  schedule.resetHour1();
  EXPECT_TRUE(schedule.isHour1Defaulted());
  EXPECT_DOUBLE_EQ(0.0, schedule.hour1());

  EXPECT_TRUE(schedule.isHour12Defaulted());
  EXPECT_TRUE(schedule.setHour12(0.6));
  EXPECT_DOUBLE_EQ(0.6, schedule.hour12());

  EXPECT_TRUE(schedule.isHour24Defaulted());
  EXPECT_TRUE(schedule.setHour24(1.0));
  EXPECT_DOUBLE_EQ(1.0, schedule.hour24());
  EXPECT_FALSE(schedule.isHour24Defaulted());
  schedule.resetHour24();
  EXPECT_TRUE(schedule.isHour24Defaulted());
  EXPECT_DOUBLE_EQ(0.0, schedule.hour24());
}
