/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SizingPeriodWeatherFileDays.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SizingPeriodWeatherFileDays_DefaultConstructor) {
  Model model;
  SizingPeriodWeatherFileDays obj(model);
  EXPECT_EQ(SizingPeriodWeatherFileDays::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SizingPeriodWeatherFileDays_ScalarAccessors_RoundTrip) {
  Model model;
  SizingPeriodWeatherFileDays obj(model);

  EXPECT_FALSE(SizingPeriodWeatherFileDays::dayofWeekforStartDayValues().empty());

  EXPECT_TRUE(obj.setBeginMonth(1));
  EXPECT_EQ(1, obj.beginMonth());

  EXPECT_TRUE(obj.setBeginDayofMonth(2));
  EXPECT_EQ(2, obj.beginDayofMonth());

  EXPECT_TRUE(obj.setEndMonth(12));
  EXPECT_EQ(12, obj.endMonth());

  EXPECT_TRUE(obj.setEndDayofMonth(31));
  EXPECT_EQ(31, obj.endDayofMonth());

  EXPECT_TRUE(obj.setDayofWeekforStartDay("Sunday"));
  EXPECT_EQ("Sunday", obj.dayofWeekforStartDay());
  EXPECT_FALSE(obj.isDayofWeekforStartDayDefaulted());
  obj.resetDayofWeekforStartDay();
  EXPECT_TRUE(obj.isDayofWeekforStartDayDefaulted());

  EXPECT_TRUE(obj.setUseWeatherFileDaylightSavingPeriod(false));
  EXPECT_FALSE(obj.useWeatherFileDaylightSavingPeriod());
  EXPECT_FALSE(obj.isUseWeatherFileDaylightSavingPeriodDefaulted());
  obj.resetUseWeatherFileDaylightSavingPeriod();
  EXPECT_TRUE(obj.isUseWeatherFileDaylightSavingPeriodDefaulted());

  EXPECT_TRUE(obj.setUseWeatherFileRainandSnowIndicators(false));
  EXPECT_FALSE(obj.useWeatherFileRainandSnowIndicators());
  EXPECT_FALSE(obj.isUseWeatherFileRainandSnowIndicatorsDefaulted());
  obj.resetUseWeatherFileRainandSnowIndicators();
  EXPECT_TRUE(obj.isUseWeatherFileRainandSnowIndicatorsDefaulted());
}
