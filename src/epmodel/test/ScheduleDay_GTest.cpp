/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ScheduleBase/ScheduleDay.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleDay_DefaultConstructor) {
  Model model;
  ScheduleDay schedule(model);
  EXPECT_EQ(ScheduleDay::iddObjectType(), schedule.iddObject().type());
  EXPECT_FALSE(schedule.nameString().empty());
}

TEST_F(EPModelFixture, ScheduleDay_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleDay schedule(model);

  const auto values = ScheduleDay::interpolatetoTimestepValues();
  ASSERT_FALSE(values.empty());

  EXPECT_TRUE(schedule.isInterpolatetoTimestepDefaulted());
  EXPECT_TRUE(schedule.setInterpolatetoTimestep("Linear"));
  EXPECT_EQ("Linear", schedule.interpolatetoTimestep());
  EXPECT_FALSE(schedule.isInterpolatetoTimestepDefaulted());

  schedule.resetInterpolatetoTimestep();
  EXPECT_TRUE(schedule.isInterpolatetoTimestepDefaulted());
}
