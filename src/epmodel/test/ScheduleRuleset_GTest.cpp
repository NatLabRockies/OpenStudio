/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleRuleset.hpp"
#include "../ScheduleBase/ScheduleDay.hpp"

#include <utilities/time/Time.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleRuleset_DefaultConstructor) {
  Model model;
  ScheduleRuleset schedule(model);

  EXPECT_EQ(ScheduleRuleset::iddObjectType(), schedule.iddObject().type());
  EXPECT_EQ(std::vector<openstudio::Time>{openstudio::Time(1, 0)}, schedule.defaultDaySchedule().times());
  EXPECT_EQ(std::vector<double>{0.0}, schedule.defaultDaySchedule().values());
  EXPECT_TRUE(schedule.isSummerDesignDayScheduleDefaulted());
  EXPECT_TRUE(schedule.isWinterDesignDayScheduleDefaulted());
  EXPECT_TRUE(schedule.isHolidayScheduleDefaulted());
  EXPECT_TRUE(schedule.isCustomDay1ScheduleDefaulted());
  EXPECT_TRUE(schedule.isCustomDay2ScheduleDefaulted());
  EXPECT_EQ(schedule.defaultDaySchedule(), schedule.summerDesignDaySchedule());
  EXPECT_EQ(schedule.defaultDaySchedule(), schedule.winterDesignDaySchedule());
  EXPECT_EQ(schedule.defaultDaySchedule(), schedule.holidaySchedule());
  EXPECT_EQ(schedule.defaultDaySchedule(), schedule.customDay1Schedule());
  EXPECT_EQ(schedule.defaultDaySchedule(), schedule.customDay2Schedule());
}

TEST_F(EPModelFixture, ScheduleRuleset_InitialValue) {
  Model model;
  ScheduleRuleset schedule(model, 0.75);

  EXPECT_EQ(std::vector<double>{0.75}, schedule.defaultDaySchedule().values());
}

TEST_F(EPModelFixture, ScheduleRuleset_SpecialDaySchedules) {
  Model model;
  ScheduleRuleset schedule(model);
  ScheduleDay summerSchedule(model);
  ASSERT_TRUE(summerSchedule.addValue(openstudio::Time(1, 0), 0.5));

  ASSERT_TRUE(schedule.setSummerDesignDaySchedule(summerSchedule));
  EXPECT_FALSE(schedule.isSummerDesignDayScheduleDefaulted());
  EXPECT_EQ(summerSchedule, schedule.summerDesignDaySchedule());

  schedule.resetSummerDesignDaySchedule();
  EXPECT_TRUE(schedule.isSummerDesignDayScheduleDefaulted());
  EXPECT_EQ(schedule.defaultDaySchedule(), schedule.summerDesignDaySchedule());
}