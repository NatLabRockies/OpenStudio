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
#include "../ResourceObject/ScheduleTypeLimits.hpp"

#include <utilities/time/Date.hpp>
#include <utilities/time/Time.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleRule_DefaultDayIsIndependent) {
  Model model;
  ScheduleRuleset ruleset(model);
  auto defaultDay = ruleset.defaultDaySchedule();
  ASSERT_TRUE(defaultDay.setName("Default Day"));
  ASSERT_TRUE(defaultDay.addValue(openstudio::Time(1, 0), 0.8));
  ScheduleTypeLimits limits(model);
  ASSERT_TRUE(ruleset.setScheduleTypeLimits(limits));

  ScheduleRule first(ruleset);
  ScheduleRule second(ruleset);
  auto firstDay = first.daySchedule();
  auto secondDay = second.daySchedule();
  EXPECT_NE(defaultDay, firstDay);
  EXPECT_NE(defaultDay, secondDay);
  EXPECT_NE(firstDay, secondDay);
  EXPECT_EQ(std::vector<openstudio::Time>{openstudio::Time(1, 0)}, firstDay.times());
  EXPECT_EQ(std::vector<double>{0.0}, firstDay.values());
  ASSERT_TRUE(firstDay.scheduleTypeLimits());
  EXPECT_EQ(limits, *firstDay.scheduleTypeLimits());

  ASSERT_TRUE(firstDay.setName("First Rule Day"));
  ASSERT_TRUE(firstDay.addValue(openstudio::Time(1, 0), 0.3));
  EXPECT_EQ("Default Day", defaultDay.nameString());
  EXPECT_EQ(std::vector<double>{0.8}, defaultDay.values());
  EXPECT_EQ(std::vector<double>{0.0}, secondDay.values());
  EXPECT_EQ(0, second.rulePriorityOrder());
  EXPECT_EQ(1, first.rulePriorityOrder());
}

TEST_F(EPModelFixture, ScheduleRule_CopiesSuppliedDay) {
  Model model;
  ScheduleRuleset ruleset(model);
  ScheduleDay source(model);
  ASSERT_TRUE(source.setName("Source Day"));
  ASSERT_TRUE(source.setInterpolatetoTimestep("Average"));
  ASSERT_TRUE(source.addValue(openstudio::Time(0, 12), 0.2));
  ASSERT_TRUE(source.addValue(openstudio::Time(1, 0), 0.7));
  ScheduleTypeLimits sourceLimits(model);
  ASSERT_TRUE(source.setScheduleTypeLimits(sourceLimits));

  ScheduleRule first(ruleset, source);
  ScheduleRule second(ruleset, source);
  auto firstDay = first.daySchedule();
  EXPECT_NE(source, firstDay);
  EXPECT_NE(firstDay, second.daySchedule());
  EXPECT_EQ(source.times(), firstDay.times());
  EXPECT_EQ(source.values(), firstDay.values());
  EXPECT_EQ(source.interpolatetoTimestep(), firstDay.interpolatetoTimestep());
  ASSERT_TRUE(firstDay.scheduleTypeLimits());
  EXPECT_EQ(sourceLimits, *firstDay.scheduleTypeLimits());

  ASSERT_TRUE(firstDay.setName("First Rule Day"));
  ASSERT_TRUE(firstDay.addValue(openstudio::Time(1, 0), 0.4));
  EXPECT_EQ("Source Day", source.nameString());
  EXPECT_EQ((std::vector<double>{0.2, 0.7}), source.values());
  EXPECT_EQ(source.values(), second.daySchedule().values());

  ScheduleTypeLimits parentLimits(model);
  ASSERT_TRUE(ruleset.setScheduleTypeLimits(parentLimits));
  ScheduleRule third(ruleset, source);
  ASSERT_TRUE(third.daySchedule().scheduleTypeLimits());
  EXPECT_EQ(parentLimits, *third.daySchedule().scheduleTypeLimits());
  EXPECT_EQ(sourceLimits, *source.scheduleTypeLimits());
}

TEST_F(EPModelFixture, ScheduleRule_CopiesDayFromAnotherModel) {
  Model sourceModel;
  ScheduleDay source(sourceModel);
  ASSERT_TRUE(source.setName("Source Day"));
  ASSERT_TRUE(source.addValue(openstudio::Time(1, 0), 0.7));
  ScheduleTypeLimits sourceLimits(sourceModel);
  ASSERT_TRUE(sourceLimits.setName("Source Limits"));
  ASSERT_TRUE(sourceLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(source.setScheduleTypeLimits(sourceLimits));

  Model targetModel;
  ScheduleRuleset ruleset(targetModel);
  ScheduleTypeLimits conflictingLimits(targetModel);
  ASSERT_TRUE(conflictingLimits.setName("Source Limits"));
  ASSERT_TRUE(conflictingLimits.setUpperLimitValue(10.0));
  ScheduleRule rule(ruleset, source);
  auto copiedDay = rule.daySchedule();
  EXPECT_EQ(targetModel, copiedDay.model());
  EXPECT_NE(source, copiedDay);
  EXPECT_EQ(source.times(), copiedDay.times());
  EXPECT_EQ(source.values(), copiedDay.values());
  ASSERT_TRUE(copiedDay.scheduleTypeLimits());
  EXPECT_EQ(targetModel, copiedDay.scheduleTypeLimits()->model());
  EXPECT_NE(conflictingLimits, *copiedDay.scheduleTypeLimits());
  const auto copiedUpperLimit = copiedDay.scheduleTypeLimits()->upperLimitValue();
  ASSERT_TRUE(copiedUpperLimit);
  EXPECT_DOUBLE_EQ(1.0, *copiedUpperLimit);
  ASSERT_TRUE(copiedDay.addValue(openstudio::Time(1, 0), 0.4));
  EXPECT_EQ(std::vector<double>{0.7}, source.values());

  ASSERT_TRUE(ruleset.setScheduleTypeLimits(conflictingLimits));
  ScheduleRule ruleWithParentLimits(ruleset, source);
  ASSERT_TRUE(ruleWithParentLimits.daySchedule().scheduleTypeLimits());
  EXPECT_EQ(conflictingLimits, *ruleWithParentLimits.daySchedule().scheduleTypeLimits());
  EXPECT_EQ(sourceLimits, *source.scheduleTypeLimits());
}

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
  EXPECT_EQ(0.1, scheduleRuleset.getDaySchedule(startDate).values().front());
  EXPECT_EQ(0.9, scheduleRuleset.getDaySchedule(openstudio::Date(openstudio::MonthOfYear::Mar, 1)).values().front());
}

TEST_F(EPModelFixture, ScheduleRule_LoadFromIdf) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-schedule-rule.idf");

  Model model;
  ScheduleRuleset scheduleRuleset(model);
  ASSERT_TRUE(scheduleRuleset.setName("Schedule Rule Ruleset"));
  ASSERT_TRUE(scheduleRuleset.defaultDaySchedule().setName("Default Day"));
  ASSERT_TRUE(scheduleRuleset.defaultDaySchedule().addValue(openstudio::Time(1, 0), 0.8));
  ScheduleRule rule(scheduleRuleset);
  ASSERT_TRUE(rule.setName("Schedule Rule"));
  ASSERT_TRUE(rule.daySchedule().setName("Rule Day"));
  ASSERT_TRUE(rule.daySchedule().addValue(openstudio::Time(1, 0), 0.3));
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
  EXPECT_EQ("Default Day", loadedRuleset->defaultDaySchedule().nameString());
  EXPECT_EQ("Rule Day", loadedRule.daySchedule().nameString());
  EXPECT_NE(loadedRuleset->defaultDaySchedule(), loadedRule.daySchedule());
  EXPECT_EQ(std::vector<double>{0.8}, loadedRuleset->defaultDaySchedule().values());
  EXPECT_EQ(std::vector<double>{0.3}, loadedRule.daySchedule().values());
  EXPECT_TRUE(loadedRule.applyWednesday());
  ASSERT_EQ(1u, loadedRule.dateRanges().size());
  EXPECT_EQ(openstudio::Date(openstudio::MonthOfYear::Mar, 1), loadedRule.dateRanges().front().first);

  openstudio::filesystem::remove(idfPath);
}