/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleRule.hpp"
#include "../Schedule/ScheduleRuleset.hpp"
#include "../Schedule/ScheduleRuleset_Impl.hpp"
#include "../ScheduleBase/ScheduleDay.hpp"

#include <utilities/time/Date.hpp>
#include <utilities/time/Time.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleRule_PriorityOrderAndWeekdays) {
  Model model;
  ScheduleRuleset scheduleRuleset(model);
  ScheduleDay daySchedule(model);
  ASSERT_TRUE(daySchedule.addValue(openstudio::Time(1, 0), 0.5));

  ScheduleRule firstRule(scheduleRuleset, daySchedule);
  ScheduleRule secondRule(scheduleRuleset, daySchedule);

  ASSERT_EQ(2u, scheduleRuleset.scheduleRules().size());
  EXPECT_EQ(secondRule, scheduleRuleset.scheduleRules().front());
  EXPECT_EQ(0, secondRule.rulePriorityOrder());
  EXPECT_EQ(1, firstRule.rulePriorityOrder());

  ASSERT_TRUE(firstRule.setRulePriorityOrder(0));
  EXPECT_EQ(firstRule, scheduleRuleset.scheduleRules().front());
  EXPECT_EQ(0, firstRule.rulePriorityOrder());
  EXPECT_EQ(1, secondRule.rulePriorityOrder());

  EXPECT_FALSE(firstRule.applyMonday());
  ASSERT_TRUE(firstRule.setApplyMonday(true));
  ASSERT_TRUE(firstRule.setApplyFriday(true));
  EXPECT_TRUE(firstRule.applyMonday());
  EXPECT_TRUE(firstRule.applyFriday());
  EXPECT_FALSE(firstRule.applyTuesday());
}

TEST_F(EPModelFixture, ScheduleRule_DateRanges) {
  Model model;
  ScheduleRuleset scheduleRuleset(model);
  ScheduleRule rule(scheduleRuleset);

  const openstudio::Date rangeStart(openstudio::MonthOfYear::Jan, 1);
  const openstudio::Date rangeEnd(openstudio::MonthOfYear::Feb, 28);
  const openstudio::Date leapDay(openstudio::MonthOfYear::Feb, 29, 2008);
  ASSERT_TRUE(rule.addDateRange(rangeStart, rangeEnd));
  ASSERT_TRUE(rule.addDateRange(leapDay, leapDay));

  const auto ranges = rule.dateRanges();
  ASSERT_EQ(2u, ranges.size());
  EXPECT_EQ(rangeStart, ranges[0].first);
  EXPECT_EQ(rangeEnd, ranges[0].second);
  EXPECT_EQ(leapDay, ranges[1].first);
  EXPECT_EQ(leapDay, ranges[1].second);

  rule.resetDateRanges();
  EXPECT_TRUE(rule.dateRanges().empty());
}

TEST_F(EPModelFixture, ScheduleRule_SpecificDatesAndConvenienceMethods) {
  Model model;
  ScheduleRuleset scheduleRuleset(model);
  ScheduleRule rule(scheduleRuleset);

  const openstudio::Date leapDay(openstudio::MonthOfYear::Feb, 29, 2008);
  ASSERT_TRUE(rule.addSpecificDate(leapDay));
  EXPECT_EQ(std::vector<openstudio::Date>{leapDay}, rule.specificDates());
  EXPECT_EQ((std::vector<std::string>{"DateRange", "SpecificDates"}), ScheduleRule::validDateSpecificationTypeValues());
  EXPECT_EQ("SpecificDates", rule.dateSpecificationType());
  ASSERT_TRUE(rule.startDate());
  ASSERT_TRUE(rule.endDate());
  EXPECT_EQ(leapDay, *rule.startDate());
  EXPECT_EQ(leapDay, *rule.endDate());

  ASSERT_TRUE(rule.setApplyAllDays(true));
  EXPECT_TRUE(rule.applyAllDays());
  EXPECT_TRUE(rule.applyWeekdays());
  EXPECT_TRUE(rule.applyWeekends());
  EXPECT_TRUE(rule.containsDate(leapDay));
  EXPECT_FALSE(rule.containsDate(openstudio::Date(openstudio::MonthOfYear::Feb, 28)));

  rule.setApplyMondayNoFail(false);
  EXPECT_FALSE(rule.applyMonday());
}

TEST_F(EPModelFixture, ScheduleRuleset_ActiveRuleIndicesAndDaySchedules) {
  Model model;
  ScheduleRuleset scheduleRuleset(model);
  ASSERT_TRUE(scheduleRuleset.defaultDaySchedule().addValue(openstudio::Time(1, 0), 0.1));

  ScheduleDay overrideDay(model);
  ASSERT_TRUE(overrideDay.addValue(openstudio::Time(1, 0), 0.9));
  ScheduleRule rule(scheduleRuleset, overrideDay);
  ASSERT_TRUE(rule.setApplyAllDays(true));
  ASSERT_TRUE(rule.addDateRange(openstudio::Date(openstudio::MonthOfYear::Mar, 1), openstudio::Date(openstudio::MonthOfYear::Mar, 2)));

  const auto startDate = openstudio::Date(openstudio::MonthOfYear::Feb, 28);
  const auto endDate = openstudio::Date(openstudio::MonthOfYear::Mar, 3);
  EXPECT_EQ((std::vector<int>{-1, 0, 0, -1}), scheduleRuleset.getActiveRuleIndices(startDate, endDate));

  const auto daySchedules = scheduleRuleset.getDaySchedules(startDate, endDate);
  ASSERT_EQ(4u, daySchedules.size());
  EXPECT_EQ(0.1, daySchedules[0].values().front());
  EXPECT_EQ(0.9, daySchedules[1].values().front());
  EXPECT_EQ(0.9, daySchedules[2].values().front());
  EXPECT_EQ(0.1, daySchedules[3].values().front());
}

TEST_F(EPModelFixture, ScheduleRule_LoadFromIdf) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-schedule-rule.idf");

  Model model;
  ScheduleRuleset scheduleRuleset(model);
  ASSERT_TRUE(scheduleRuleset.setName("Schedule Rule Ruleset"));
  ScheduleRule rule(scheduleRuleset);
  ASSERT_TRUE(rule.setName("Schedule Rule"));
  ASSERT_TRUE(rule.setApplyWednesday(true));
  ASSERT_TRUE(rule.addDateRange(openstudio::Date(openstudio::MonthOfYear::Mar, 1), openstudio::Date(openstudio::MonthOfYear::Mar, 31)));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedRuleset = loadedModel->getConcreteModelObjectByName<ScheduleRuleset>("Schedule Rule Ruleset");
  ASSERT_TRUE(loadedRuleset);
  ASSERT_EQ(1u, loadedRuleset->scheduleRules().size());

  const auto loadedRule = loadedRuleset->scheduleRules().front();
  EXPECT_EQ("Schedule Rule", loadedRule.nameString());
  EXPECT_TRUE(loadedRule.applyWednesday());
  ASSERT_EQ(1u, loadedRule.dateRanges().size());
  EXPECT_EQ(openstudio::Date(openstudio::MonthOfYear::Mar, 1), loadedRule.dateRanges().front().first);

  openstudio::filesystem::remove(idfPath);
}