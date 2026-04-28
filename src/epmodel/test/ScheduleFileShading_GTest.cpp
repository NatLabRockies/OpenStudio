/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ScheduleFileShading.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleFileShading_DefaultConstructor) {
  Model model;
  ScheduleFileShading scheduleFileShading(model);
  EXPECT_EQ(ScheduleFileShading::iddObjectType(), scheduleFileShading.iddObject().type());
}

TEST_F(EPModelFixture, ScheduleFileShading_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleFileShading scheduleFileShading(model);

  EXPECT_TRUE(scheduleFileShading.setFileName("shading_schedule.csv"));
  EXPECT_EQ("shading_schedule.csv", scheduleFileShading.fileName());
}
