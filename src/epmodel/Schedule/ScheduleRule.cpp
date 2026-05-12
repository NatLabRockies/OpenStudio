/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Schedule/ScheduleRule.hpp"
#include "Schedule/ScheduleRuleset.hpp"
#include "Schedule/ScheduleRuleset_Impl.hpp"
#include "ScheduleBase/ScheduleDay_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>

#include <string>

namespace openstudio {
namespace epmodel {

  ScheduleRule::ScheduleRule(const ScheduleRuleset& ruleset, int ruleIndex)
    : m_ruleset(ruleset), m_ruleIndex(ruleIndex) {}

  ScheduleRule::ScheduleRule(ScheduleRuleset& scheduleRuleset)
    : m_ruleset(scheduleRuleset), m_ruleIndex(0) {
    auto impl = scheduleRuleset.getImpl<detail::ScheduleRuleset_Impl>();
    OS_ASSERT(impl);

    ScheduleDay daySchedule(scheduleRuleset.model());
    daySchedule.setName(scheduleRuleset.nameString() + " Rule " + std::to_string(impl->m_rules.size()) + " Day Schedule");

    detail::ScheduleRuleset_Impl::RuleData ruleData;
    ruleData.daySchedule = daySchedule;
    impl->m_rules.insert(impl->m_rules.begin(), ruleData);
    impl->rebuildScheduleYear();
  }

  ScheduleRule::ScheduleRule(ScheduleRuleset& scheduleRuleset, const ScheduleDay& daySchedule)
    : m_ruleset(scheduleRuleset), m_ruleIndex(0) {
    auto impl = scheduleRuleset.getImpl<detail::ScheduleRuleset_Impl>();
    OS_ASSERT(impl);

    detail::ScheduleRuleset_Impl::RuleData ruleData;
    ruleData.daySchedule = daySchedule;
    impl->m_rules.insert(impl->m_rules.begin(), ruleData);
    impl->rebuildScheduleYear();
  }

  ScheduleRuleset ScheduleRule::scheduleRuleset() const {
    return m_ruleset;
  }

  int ScheduleRule::ruleIndex() const {
    return m_ruleIndex;
  }

  ScheduleDay ScheduleRule::daySchedule() const {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(m_ruleIndex >= 0 && m_ruleIndex < static_cast<int>(impl->m_rules.size()));
    OS_ASSERT(impl->m_rules[m_ruleIndex].daySchedule.has_value());
    return *impl->m_rules[m_ruleIndex].daySchedule;
  }

  bool ScheduleRule::applySunday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applySunday;
  }
  bool ScheduleRule::applyMonday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applyMonday;
  }
  bool ScheduleRule::applyTuesday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applyTuesday;
  }
  bool ScheduleRule::applyWednesday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applyWednesday;
  }
  bool ScheduleRule::applyThursday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applyThursday;
  }
  bool ScheduleRule::applyFriday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applyFriday;
  }
  bool ScheduleRule::applySaturday() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].applySaturday;
  }

  bool ScheduleRule::applyWeekdays() const {
    const auto& r = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex];
    return r.applyMonday && r.applyTuesday && r.applyWednesday && r.applyThursday && r.applyFriday;
  }

  bool ScheduleRule::applyWeekends() const {
    const auto& r = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex];
    return r.applySunday && r.applySaturday;
  }

  bool ScheduleRule::applyAllDays() const {
    return applyWeekdays() && applyWeekends();
  }

  boost::optional<openstudio::Date> ScheduleRule::startDate() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].startDate;
  }

  boost::optional<openstudio::Date> ScheduleRule::endDate() const {
    return m_ruleset.getImpl<detail::ScheduleRuleset_Impl>()->m_rules[m_ruleIndex].endDate;
  }

  bool ScheduleRule::setApplySunday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applySunday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyMonday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applyMonday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyTuesday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applyTuesday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyWednesday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applyWednesday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyThursday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applyThursday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyFriday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applyFriday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplySaturday(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].applySaturday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyWeekdays(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    auto& r = impl->m_rules[m_ruleIndex];
    r.applyMonday = r.applyTuesday = r.applyWednesday = r.applyThursday = r.applyFriday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyWeekends(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    auto& r = impl->m_rules[m_ruleIndex];
    r.applySunday = r.applySaturday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setApplyAllDays(bool v) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    auto& r = impl->m_rules[m_ruleIndex];
    r.applySunday = r.applyMonday = r.applyTuesday = r.applyWednesday = r.applyThursday = r.applyFriday = r.applySaturday = v;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setStartDate(const openstudio::Date& date) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].startDate = date;
    impl->rebuildScheduleYear();
    return true;
  }

  bool ScheduleRule::setEndDate(const openstudio::Date& date) {
    auto impl = m_ruleset.getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_rules[m_ruleIndex].endDate = date;
    impl->rebuildScheduleYear();
    return true;
  }

}  // namespace epmodel
}  // namespace openstudio
