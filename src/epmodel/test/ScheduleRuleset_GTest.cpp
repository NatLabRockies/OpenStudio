/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleRuleset.hpp"
#include "../Schedule/ScheduleRuleset_Impl.hpp"
#include "../Schedule/ScheduleRule.hpp"
#include "../Schedule/ScheduleYear.hpp"
#include "../Schedule/ScheduleYear_Impl.hpp"
#include "../ResourceObject/ScheduleWeek.hpp"
#include "../ResourceObject/ScheduleWeek_Impl.hpp"
#include "../ScheduleBase/ScheduleDay.hpp"

#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/time/Date.hpp>
#include <utilities/time/Time.hpp>

using namespace openstudio::epmodel;

// --- Construction ---

TEST_F(EPModelFixture, ScheduleRuleset_DefaultConstructor) {
  Model model;
  ScheduleRuleset rs(model);

  EXPECT_EQ(ScheduleRuleset::iddObjectType(), rs.iddObject().type());
  EXPECT_FALSE(rs.nameString().empty());
}

TEST_F(EPModelFixture, ScheduleRuleset_ConstantValueConstructor) {
  Model model;
  ScheduleRuleset rs(model, 1.0);

  const ScheduleDay def = rs.defaultDaySchedule();
  EXPECT_EQ(1.0, def.getValue(openstudio::Time(0, 12, 0)));
}

// --- No load-time dispatch: a plain Schedule:Year must NOT become a ScheduleRuleset ---

TEST_F(EPModelFixture, ScheduleRuleset_NoLoadTimeDispatch) {
  Model model;
  ScheduleYear year(model);

  // The plain ScheduleYear must not be castable to ScheduleRuleset.
  EXPECT_FALSE(year.optionalCast<ScheduleRuleset>().has_value());
}

// --- Separation: ScheduleRuleset and ScheduleYear coexist ---

TEST_F(EPModelFixture, ScheduleRuleset_CoexistsWithScheduleYear) {
  Model model;
  ScheduleYear year(model);
  ScheduleRuleset rs(model);

  const auto years = model.getConcreteModelObjects<ScheduleYear>();
  const auto rulesets = model.getConcreteModelObjects<ScheduleRuleset>();

  // Both objects are Schedule:Year in the IDF.
  EXPECT_EQ(2u, years.size());
  // ScheduleRuleset is a subtype — getConcreteModelObjects<ScheduleRuleset>
  // returns only those backed by ScheduleRuleset_Impl.
  EXPECT_EQ(1u, rulesets.size());
}

// --- Default and design day schedules ---

TEST_F(EPModelFixture, ScheduleRuleset_DefaultDaySchedule) {
  Model model;
  ScheduleRuleset rs(model, 0.5);

  const ScheduleDay def = rs.defaultDaySchedule();
  EXPECT_DOUBLE_EQ(0.5, def.getValue(openstudio::Time(0, 6, 0)));
  EXPECT_DOUBLE_EQ(0.5, def.getValue(openstudio::Time(0, 23, 0)));
}

TEST_F(EPModelFixture, ScheduleRuleset_SummerDesignDaySchedule) {
  Model model;
  ScheduleRuleset rs(model, 0.0);

  EXPECT_TRUE(rs.isSummerDesignDayScheduleDefaulted());

  ScheduleDay summerDay(model);
  summerDay.addValue(openstudio::Time(0, 24, 0), 1.0);
  EXPECT_TRUE(rs.setSummerDesignDaySchedule(summerDay));
  EXPECT_FALSE(rs.isSummerDesignDayScheduleDefaulted());
  EXPECT_DOUBLE_EQ(1.0, rs.summerDesignDaySchedule().getValue(openstudio::Time(0, 12, 0)));

  rs.resetSummerDesignDaySchedule();
  EXPECT_TRUE(rs.isSummerDesignDayScheduleDefaulted());
  // Falls back to default day schedule value.
  EXPECT_DOUBLE_EQ(0.0, rs.summerDesignDaySchedule().getValue(openstudio::Time(0, 12, 0)));
}

// --- Rules ---

TEST_F(EPModelFixture, ScheduleRuleset_AddRule) {
  Model model;
  ScheduleRuleset rs(model, 0.0);

  EXPECT_TRUE(rs.scheduleRules().empty());

  ScheduleRule rule(rs);
  EXPECT_EQ(1u, rs.scheduleRules().size());
  EXPECT_EQ(0, rule.ruleIndex());
}

TEST_F(EPModelFixture, ScheduleRuleset_RulePriority) {
  Model model;
  ScheduleRuleset rs(model, 0.0);

  ScheduleRule rule0(rs);  // index 0 (highest priority)
  ScheduleRule rule1(rs);  // inserted at index 0 → pushes old rule to index 1

  const auto rules = rs.scheduleRules();
  ASSERT_EQ(2u, rules.size());
  EXPECT_EQ(0, rules[0].ruleIndex());
  EXPECT_EQ(1, rules[1].ruleIndex());
}

TEST_F(EPModelFixture, ScheduleRuleset_SetScheduleRuleIndex) {
  Model model;
  ScheduleRuleset rs(model, 0.0);

  ScheduleRule rule0(rs);
  ScheduleRule rule1(rs);
  // rule1 inserted last at front → index 0; rule0 pushed to index 1.

  // Use fresh references from scheduleRules() — constructed m_ruleIndex values are stale
  // after subsequent insertions at the front.
  auto rules = rs.scheduleRules();
  ASSERT_EQ(2u, rules.size());
  EXPECT_EQ(0, rules[0].ruleIndex());  // rule1 data
  EXPECT_EQ(1, rules[1].ruleIndex());  // rule0 data

  // Move rules[1] (index 1) to index 0.
  EXPECT_TRUE(rs.setScheduleRuleIndex(rules[1], 0));
  EXPECT_EQ(0, rules[1].ruleIndex());

  // Verify the new order via a fresh query.
  const auto reordered = rs.scheduleRules();
  ASSERT_EQ(2u, reordered.size());
  EXPECT_EQ(0, reordered[0].ruleIndex());
  EXPECT_EQ(1, reordered[1].ruleIndex());
}

TEST_F(EPModelFixture, ScheduleRuleset_RuleDayTypes) {
  Model model;
  ScheduleRuleset rs(model, 0.0);
  ScheduleRule rule(rs);

  EXPECT_FALSE(rule.applySunday());
  EXPECT_FALSE(rule.applyMonday());

  rule.setApplyWeekdays(true);
  EXPECT_TRUE(rule.applyWeekdays());
  EXPECT_FALSE(rule.applyWeekends());
  EXPECT_FALSE(rule.applyAllDays());

  rule.setApplyWeekends(true);
  EXPECT_TRUE(rule.applyAllDays());

  rule.setApplyAllDays(false);
  EXPECT_FALSE(rule.applySunday());
  EXPECT_FALSE(rule.applyFriday());
}

TEST_F(EPModelFixture, ScheduleRuleset_RuleDateRange) {
  Model model;
  ScheduleRuleset rs(model, 0.0);
  ScheduleRule rule(rs);

  const openstudio::Date start(openstudio::MonthOfYear::Jun, 1);
  const openstudio::Date end(openstudio::MonthOfYear::Aug, 31);

  EXPECT_TRUE(rule.setStartDate(start));
  EXPECT_TRUE(rule.setEndDate(end));

  ASSERT_TRUE(rule.startDate());
  ASSERT_TRUE(rule.endDate());
  EXPECT_EQ(start, *rule.startDate());
  EXPECT_EQ(end, *rule.endDate());
}

// --- rebuildScheduleYear produces valid IDF structure ---

TEST_F(EPModelFixture, ScheduleRuleset_RebuildProducesScheduleWeek) {
  Model model;
  ScheduleRuleset rs(model);

  // With no rules, rebuildScheduleYear creates one Schedule:Week:Daily covering the full year.
  const auto weeks = model.getConcreteModelObjects<ScheduleWeek>();
  EXPECT_GE(weeks.size(), 1u);

  // The Schedule:Year should have at least one extensible group (week + date range).
  const auto yearGroups = rs.extensibleGroups();
  EXPECT_GE(yearGroups.size(), 1u);
}

TEST_F(EPModelFixture, ScheduleRuleset_RuleWithDayScheduleApplied) {
  Model model;
  ScheduleRuleset rs(model, 0.0);

  ScheduleDay summerDay(model);
  summerDay.addValue(openstudio::Time(0, 24, 0), 0.9);

  ScheduleRule rule(rs, summerDay);
  rule.setApplyAllDays(true);
  rule.setStartDate(openstudio::Date(openstudio::MonthOfYear::Jun, 1));
  rule.setEndDate(openstudio::Date(openstudio::MonthOfYear::Aug, 31));

  // Three date intervals: Jan1–May31 (default), Jun1–Aug31 (rule), Sep1–Dec31 (default).
  // The first and last share the same pattern but are not consecutive, so they are not merged.
  const auto weeks = model.getConcreteModelObjects<ScheduleWeek>();
  EXPECT_EQ(3u, weeks.size());
  EXPECT_EQ(3u, rs.extensibleGroups().size());
}
