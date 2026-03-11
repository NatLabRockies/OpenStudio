/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SizingPeriodWeatherFileConditionType.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SizingPeriodWeatherFileConditionType_DefaultConstructor) {
  Model model;
  SizingPeriodWeatherFileConditionType obj(model);
  EXPECT_EQ(SizingPeriodWeatherFileConditionType::iddObjectType(), obj.iddObject().type());
}

TEST_F(EPModelFixture, SizingPeriodWeatherFileConditionType_ScalarAccessors_RoundTrip) {
  Model model;
  SizingPeriodWeatherFileConditionType obj(model);

  EXPECT_FALSE(SizingPeriodWeatherFileConditionType::periodSelectionValues().empty());
  EXPECT_FALSE(SizingPeriodWeatherFileConditionType::dayofWeekforStartDayValues().empty());

  EXPECT_TRUE(obj.setPeriodSelection("SummerExtreme"));
  EXPECT_EQ("SummerExtreme", obj.periodSelection());

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
