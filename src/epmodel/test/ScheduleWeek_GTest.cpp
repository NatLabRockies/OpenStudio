/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/ScheduleWeek.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleWeek_DefaultConstructor) {
  Model model;
  ScheduleWeek scheduleWeek(model);
  EXPECT_EQ(ScheduleWeek::iddObjectType(), scheduleWeek.iddObject().type());
}

TEST_F(EPModelFixture, ScheduleWeek_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleWeek scheduleWeek(model);

  EXPECT_TRUE(scheduleWeek.setName("Week Daily Schedule"));
  EXPECT_EQ("Week Daily Schedule", scheduleWeek.nameString());
}
