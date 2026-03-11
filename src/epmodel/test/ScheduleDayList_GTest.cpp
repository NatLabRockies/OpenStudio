/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ScheduleDayList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleDayList_DefaultConstructor) {
  Model model;
  ScheduleDayList schedule(model);
  EXPECT_EQ(ScheduleDayList::iddObjectType(), schedule.iddObject().type());
  EXPECT_FALSE(schedule.nameString().empty());
}

TEST_F(EPModelFixture, ScheduleDayList_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleDayList schedule(model);

  const auto values = ScheduleDayList::interpolatetoTimestepValues();
  ASSERT_FALSE(values.empty());

  EXPECT_TRUE(schedule.isInterpolatetoTimestepDefaulted());
  EXPECT_TRUE(schedule.setInterpolatetoTimestep("Linear"));
  EXPECT_EQ("Linear", schedule.interpolatetoTimestep());
  EXPECT_FALSE(schedule.isInterpolatetoTimestepDefaulted());

  schedule.resetInterpolatetoTimestep();
  EXPECT_TRUE(schedule.isInterpolatetoTimestepDefaulted());
  EXPECT_EQ("No", schedule.interpolatetoTimestep());

  EXPECT_FALSE(schedule.minutesperItem());
  EXPECT_TRUE(schedule.setMinutesperItem(15));
  ASSERT_TRUE(schedule.minutesperItem());
  EXPECT_EQ(15, schedule.minutesperItem().get());

  EXPECT_FALSE(schedule.setMinutesperItem(61));
  schedule.resetMinutesperItem();
  EXPECT_FALSE(schedule.minutesperItem());
}
