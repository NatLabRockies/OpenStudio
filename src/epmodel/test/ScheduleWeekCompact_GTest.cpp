/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ScheduleWeekCompact.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleWeekCompact_DefaultConstructor) {
  Model model;
  ScheduleWeekCompact scheduleWeekCompact(model);
  EXPECT_EQ(ScheduleWeekCompact::iddObjectType(), scheduleWeekCompact.iddObject().type());
}

TEST_F(EPModelFixture, ScheduleWeekCompact_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleWeekCompact scheduleWeekCompact(model);

  EXPECT_TRUE(scheduleWeekCompact.setName("Week Compact Schedule"));
  EXPECT_EQ("Week Compact Schedule", scheduleWeekCompact.nameString());
}
