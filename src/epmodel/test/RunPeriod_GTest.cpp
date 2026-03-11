/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RunPeriodControlDaylightSavingTime.hpp"
#include "../ModelObject/RunPeriodControlSpecialDays.hpp"
#include "../ParentObject/RunPeriod.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RunPeriod_DefaultConstructor) {
  Model model;
  RunPeriod runPeriod(model);
  EXPECT_EQ(RunPeriod::iddObjectType(), runPeriod.iddObject().type());
}

TEST_F(EPModelFixture, RunPeriod_ScalarAccessors_RoundTrip) {
  Model model;
  RunPeriod runPeriod(model);

  EXPECT_EQ(1, runPeriod.getBeginMonth());
  EXPECT_EQ(1, runPeriod.getBeginDayOfMonth());
  EXPECT_EQ(12, runPeriod.getEndMonth());
  EXPECT_EQ(31, runPeriod.getEndDayOfMonth());
  EXPECT_TRUE(runPeriod.isAnnual());
  EXPECT_FALSE(runPeriod.isPartialYear());

  EXPECT_TRUE(runPeriod.setBeginMonth(2));
  EXPECT_TRUE(runPeriod.setBeginDayOfMonth(29));
  EXPECT_TRUE(runPeriod.setEndMonth(2));
  EXPECT_TRUE(runPeriod.setEndDayOfMonth(29));
  runPeriod.ensureNoLeapDays();
  EXPECT_EQ(28, runPeriod.getBeginDayOfMonth());
  EXPECT_EQ(28, runPeriod.getEndDayOfMonth());

  EXPECT_TRUE(runPeriod.setUseWeatherFileHolidays(false));
  EXPECT_FALSE(runPeriod.getUseWeatherFileHolidays());

  EXPECT_TRUE(runPeriod.setUseWeatherFileDaylightSavings(true));
  EXPECT_TRUE(runPeriod.getUseWeatherFileDaylightSavings());

  EXPECT_TRUE(runPeriod.setApplyWeekendHolidayRule(false));
  EXPECT_FALSE(runPeriod.getApplyWeekendHolidayRule());

  EXPECT_TRUE(runPeriod.setUseWeatherFileRainInd(false));
  EXPECT_FALSE(runPeriod.getUseWeatherFileRainInd());

  EXPECT_TRUE(runPeriod.setUseWeatherFileSnowInd(true));
  EXPECT_TRUE(runPeriod.getUseWeatherFileSnowInd());

  EXPECT_TRUE(runPeriod.setNumTimePeriodRepeats(3));
  EXPECT_EQ(3, runPeriod.getNumTimePeriodRepeats());
  EXPECT_TRUE(runPeriod.isRepeated());

  EXPECT_FALSE(runPeriod.isAnnual());
  EXPECT_TRUE(runPeriod.isPartialYear());
}

TEST_F(EPModelFixture, RunPeriodControlDaylightSavingTime_DefaultConstructor) {
  Model model;
  RunPeriodControlDaylightSavingTime runPeriodControlDaylightSavingTime(model);
  EXPECT_EQ(RunPeriodControlDaylightSavingTime::iddObjectType(), runPeriodControlDaylightSavingTime.iddObject().type());
}

TEST_F(EPModelFixture, RunPeriodControlDaylightSavingTime_ScalarAccessors_RoundTrip) {
  Model model;
  RunPeriodControlDaylightSavingTime runPeriodControlDaylightSavingTime(model);

  EXPECT_EQ("2nd Sunday in March", runPeriodControlDaylightSavingTime.startDate());
  EXPECT_EQ("1st Sunday in November", runPeriodControlDaylightSavingTime.endDate());

  EXPECT_TRUE(runPeriodControlDaylightSavingTime.setStartDate("Last Sunday in March"));
  EXPECT_TRUE(runPeriodControlDaylightSavingTime.setEndDate("Last Sunday in October"));
  EXPECT_EQ("Last Sunday in March", runPeriodControlDaylightSavingTime.startDate());
  EXPECT_EQ("Last Sunday in October", runPeriodControlDaylightSavingTime.endDate());

  EXPECT_TRUE(runPeriodControlDaylightSavingTime.setStartDate("3/1"));
  EXPECT_TRUE(runPeriodControlDaylightSavingTime.setEndDate("10/1"));
  EXPECT_EQ("3/1", runPeriodControlDaylightSavingTime.startDate());
  EXPECT_EQ("10/1", runPeriodControlDaylightSavingTime.endDate());
}

TEST_F(EPModelFixture, RunPeriodControlSpecialDays_DefaultConstructor) {
  Model model;
  RunPeriodControlSpecialDays runPeriodControlSpecialDays(model);
  EXPECT_EQ(RunPeriodControlSpecialDays::iddObjectType(), runPeriodControlSpecialDays.iddObject().type());
}

TEST_F(EPModelFixture, RunPeriodControlSpecialDays_ScalarAccessors_RoundTrip) {
  Model model;
  RunPeriodControlSpecialDays runPeriodControlSpecialDays(model);

  EXPECT_TRUE(runPeriodControlSpecialDays.setStartDate("4th Monday in February"));
  EXPECT_TRUE(runPeriodControlSpecialDays.setDuration(3));
  EXPECT_EQ("4th Monday in February", runPeriodControlSpecialDays.startDate());
  EXPECT_EQ(3u, runPeriodControlSpecialDays.duration());

  const auto values = RunPeriodControlSpecialDays::specialDayTypeValues();
  ASSERT_FALSE(values.empty());
  EXPECT_TRUE(runPeriodControlSpecialDays.setSpecialDayType(values.front()));
  EXPECT_EQ(values.front(), runPeriodControlSpecialDays.specialDayType());
}
