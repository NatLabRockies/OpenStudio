/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Schedule/ScheduleRuleset.hpp"
#include "Schedule/ScheduleRuleset_Impl.hpp"
#include "Schedule/ScheduleRule.hpp"
#include "ResourceObject/ScheduleWeek.hpp"
#include "ResourceObject/ScheduleWeek_Impl.hpp"
#include "ScheduleBase/ScheduleDay.hpp"
#include "ScheduleBase/ScheduleDay_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Year_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/time/Date.hpp>
#include <utilities/time/Time.hpp>

#include <algorithm>
#include <array>
#include <sstream>

namespace {

// Creates a ScheduleRuleset_Impl directly — bypassing the IDD-type factory so that
// plain Schedule:Year objects loaded from IDF remain ScheduleYear_Impl instances.
std::shared_ptr<openstudio::epmodel::detail::ScheduleRuleset_Impl> makeRulesetImpl(const openstudio::epmodel::Model& model) {
  openstudio::IdfObject idfObject(openstudio::IddObjectType::Schedule_Year);
  auto modelImpl = model.getImpl<openstudio::epmodel::detail::Model_Impl>();
  auto impl = std::make_shared<openstudio::epmodel::detail::ScheduleRuleset_Impl>(idfObject, modelImpl.get(), false);
  std::vector<std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>> impls{impl};
  modelImpl->addObjects(impls, false);
  return impl;
}

}  // namespace

namespace openstudio {
namespace epmodel {

  ScheduleRuleset::ScheduleRuleset(const Model& model) : ScheduleYear(makeRulesetImpl(model)) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    OS_ASSERT(impl);

    ScheduleDay defaultDay(model);
    defaultDay.setName(nameString() + " Default Day Schedule");
    impl->m_defaultDaySchedule = defaultDay;

    impl->rebuildScheduleYear();
  }

  ScheduleRuleset::ScheduleRuleset(const Model& model, double value) : ScheduleYear(makeRulesetImpl(model)) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    OS_ASSERT(impl);

    ScheduleDay defaultDay(model);
    defaultDay.setName(nameString() + " Default Day Schedule");
    defaultDay.addValue(openstudio::Time(0, 24, 0, 0), value);
    impl->m_defaultDaySchedule = defaultDay;

    impl->rebuildScheduleYear();
  }

  ScheduleRuleset::ScheduleRuleset(std::shared_ptr<detail::ScheduleRuleset_Impl> impl) : ScheduleYear(std::move(impl)) {}

  IddObjectType ScheduleRuleset::iddObjectType() {
    return IddObjectType::Schedule_Year;
  }

  ScheduleDay ScheduleRuleset::defaultDaySchedule() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    OS_ASSERT(impl->m_defaultDaySchedule.has_value());
    return *impl->m_defaultDaySchedule;
  }

  ScheduleDay ScheduleRuleset::summerDesignDaySchedule() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    return impl->m_summerDesignDaySchedule.value_or(*impl->m_defaultDaySchedule);
  }

  bool ScheduleRuleset::isSummerDesignDayScheduleDefaulted() const {
    return !getImpl<detail::ScheduleRuleset_Impl>()->m_summerDesignDaySchedule.has_value();
  }

  bool ScheduleRuleset::setSummerDesignDaySchedule(const ScheduleDay& schedule) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_summerDesignDaySchedule = schedule;
    impl->rebuildScheduleYear();
    return true;
  }

  void ScheduleRuleset::resetSummerDesignDaySchedule() {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_summerDesignDaySchedule = boost::none;
    impl->rebuildScheduleYear();
  }

  ScheduleDay ScheduleRuleset::winterDesignDaySchedule() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    return impl->m_winterDesignDaySchedule.value_or(*impl->m_defaultDaySchedule);
  }

  bool ScheduleRuleset::isWinterDesignDayScheduleDefaulted() const {
    return !getImpl<detail::ScheduleRuleset_Impl>()->m_winterDesignDaySchedule.has_value();
  }

  bool ScheduleRuleset::setWinterDesignDaySchedule(const ScheduleDay& schedule) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_winterDesignDaySchedule = schedule;
    impl->rebuildScheduleYear();
    return true;
  }

  void ScheduleRuleset::resetWinterDesignDaySchedule() {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_winterDesignDaySchedule = boost::none;
    impl->rebuildScheduleYear();
  }

  ScheduleDay ScheduleRuleset::holidaySchedule() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    return impl->m_holidaySchedule.value_or(*impl->m_defaultDaySchedule);
  }

  bool ScheduleRuleset::isHolidayScheduleDefaulted() const {
    return !getImpl<detail::ScheduleRuleset_Impl>()->m_holidaySchedule.has_value();
  }

  bool ScheduleRuleset::setHolidaySchedule(const ScheduleDay& schedule) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_holidaySchedule = schedule;
    impl->rebuildScheduleYear();
    return true;
  }

  void ScheduleRuleset::resetHolidaySchedule() {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_holidaySchedule = boost::none;
    impl->rebuildScheduleYear();
  }

  ScheduleDay ScheduleRuleset::customDay1Schedule() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    return impl->m_customDay1Schedule.value_or(*impl->m_defaultDaySchedule);
  }

  bool ScheduleRuleset::isCustomDay1ScheduleDefaulted() const {
    return !getImpl<detail::ScheduleRuleset_Impl>()->m_customDay1Schedule.has_value();
  }

  bool ScheduleRuleset::setCustomDay1Schedule(const ScheduleDay& schedule) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_customDay1Schedule = schedule;
    impl->rebuildScheduleYear();
    return true;
  }

  void ScheduleRuleset::resetCustomDay1Schedule() {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_customDay1Schedule = boost::none;
    impl->rebuildScheduleYear();
  }

  ScheduleDay ScheduleRuleset::customDay2Schedule() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    return impl->m_customDay2Schedule.value_or(*impl->m_defaultDaySchedule);
  }

  bool ScheduleRuleset::isCustomDay2ScheduleDefaulted() const {
    return !getImpl<detail::ScheduleRuleset_Impl>()->m_customDay2Schedule.has_value();
  }

  bool ScheduleRuleset::setCustomDay2Schedule(const ScheduleDay& schedule) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_customDay2Schedule = schedule;
    impl->rebuildScheduleYear();
    return true;
  }

  void ScheduleRuleset::resetCustomDay2Schedule() {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    impl->m_customDay2Schedule = boost::none;
    impl->rebuildScheduleYear();
  }

  std::vector<ScheduleRule> ScheduleRuleset::scheduleRules() const {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    std::vector<ScheduleRule> result;
    result.reserve(impl->m_rules.size());
    for (int i = 0; i < static_cast<int>(impl->m_rules.size()); ++i) {
      result.emplace_back(ScheduleRule(*this, i));
    }
    return result;
  }

  bool ScheduleRuleset::setScheduleRuleIndex(ScheduleRule& rule, unsigned index) {
    auto impl = getImpl<detail::ScheduleRuleset_Impl>();
    const int currentIdx = rule.ruleIndex();
    if (currentIdx < 0 || currentIdx >= static_cast<int>(impl->m_rules.size())) {
      return false;
    }
    if (index >= impl->m_rules.size()) {
      return false;
    }
    auto ruleData = impl->m_rules[currentIdx];
    impl->m_rules.erase(impl->m_rules.begin() + currentIdx);
    impl->m_rules.insert(impl->m_rules.begin() + index, ruleData);
    rule.m_ruleIndex = static_cast<int>(index);
    impl->rebuildScheduleYear();
    return true;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    void ScheduleRuleset_Impl::rebuildScheduleYear() {
      if (!m_defaultDaySchedule) {
        return;
      }

      auto ruleset = getObject<openstudio::epmodel::ScheduleRuleset>();
      auto model = ruleset.model();
      const std::string rulesetName = ruleset.nameString();
      const std::string weekPrefix = rulesetName + " Week Rule - ";

      // Remove Schedule:Week:Daily objects created by previous rebuilds for this ruleset.
      for (auto& week : model.getConcreteModelObjects<ScheduleWeek>()) {
        if (week.nameString().rfind(weekPrefix, 0) == 0) {
          week.remove();
        }
      }

      // Clear existing extensible groups on the Schedule:Year.
      ruleset.clearExtensibleGroups();

      const ScheduleDay& defaultDay = *m_defaultDaySchedule;
      const ScheduleDay& summerDay = m_summerDesignDaySchedule.value_or(defaultDay);
      const ScheduleDay& winterDay = m_winterDesignDaySchedule.value_or(defaultDay);
      const ScheduleDay& holidayDay = m_holidaySchedule.value_or(defaultDay);
      const ScheduleDay& custom1Day = m_customDay1Schedule.value_or(defaultDay);
      const ScheduleDay& custom2Day = m_customDay2Schedule.value_or(defaultDay);

      const openstudio::Date jan1(openstudio::MonthOfYear::Jan, 1);
      const openstudio::Date dec31(openstudio::MonthOfYear::Dec, 31);

      // Collect breakpoints: start/end+1 of each rule, plus year boundaries.
      std::vector<openstudio::Date> breakpoints;
      breakpoints.push_back(jan1);
      for (const auto& rule : m_rules) {
        breakpoints.push_back(rule.startDate);
        breakpoints.push_back(rule.endDate + openstudio::Time(1, 0, 0, 0));
      }
      breakpoints.push_back(dec31 + openstudio::Time(1, 0, 0, 0));

      std::sort(breakpoints.begin(), breakpoints.end());
      breakpoints.erase(std::unique(breakpoints.begin(), breakpoints.end()), breakpoints.end());

      // A pattern is 12 handles: [0..6] = Sun–Sat, [7] = Holiday, [8] = Summer, [9] = Winter, [10] = Custom1, [11] = Custom2.
      using Pattern = std::array<openstudio::Handle, 12>;

      struct Interval
      {
        openstudio::Date start;
        openstudio::Date end;
        Pattern pattern;
      };

      // For each day-of-week index 0..6, find the highest-priority rule that covers the interval and applies to that day.
      auto effectiveDayHandle = [&](int dowIndex, const openstudio::Date& iStart, const openstudio::Date& iEnd) -> openstudio::Handle {
        for (const auto& rule : m_rules) {
          if (rule.startDate <= iStart && rule.endDate >= iEnd) {
            const bool applies = (dowIndex == 0 && rule.applySunday) || (dowIndex == 1 && rule.applyMonday) || (dowIndex == 2 && rule.applyTuesday)
                                 || (dowIndex == 3 && rule.applyWednesday) || (dowIndex == 4 && rule.applyThursday)
                                 || (dowIndex == 5 && rule.applyFriday) || (dowIndex == 6 && rule.applySaturday);
            if (applies && rule.daySchedule) {
              return rule.daySchedule->handle();
            }
          }
        }
        return defaultDay.handle();
      };

      std::vector<Interval> intervals;
      for (size_t i = 0; i + 1 < breakpoints.size(); ++i) {
        openstudio::Date s = breakpoints[i];
        openstudio::Date e = breakpoints[i + 1] - openstudio::Time(1, 0, 0, 0);

        if (s > dec31) {
          break;
        }
        if (e > dec31) {
          e = dec31;
        }
        if (s > e) {
          continue;
        }

        Pattern pat;
        for (int dow = 0; dow < 7; ++dow) {
          pat[dow] = effectiveDayHandle(dow, s, e);
        }
        pat[7] = holidayDay.handle();
        pat[8] = summerDay.handle();
        pat[9] = winterDay.handle();
        pat[10] = custom1Day.handle();
        pat[11] = custom2Day.handle();

        intervals.push_back({s, e, pat});
      }

      // Cover entire year with default if no breakpoints produced intervals.
      if (intervals.empty()) {
        Pattern pat;
        for (int i = 0; i < 7; ++i) {
          pat[i] = defaultDay.handle();
        }
        pat[7] = holidayDay.handle();
        pat[8] = summerDay.handle();
        pat[9] = winterDay.handle();
        pat[10] = custom1Day.handle();
        pat[11] = custom2Day.handle();
        intervals.push_back({jan1, dec31, pat});
      }

      // Merge consecutive intervals with the same pattern.
      std::vector<Interval> merged;
      for (auto& iv : intervals) {
        if (!merged.empty() && merged.back().pattern == iv.pattern) {
          merged.back().end = iv.end;
        } else {
          merged.push_back(iv);
        }
      }

      // Create a Schedule:Week:Daily for each merged interval and add a Schedule:Year extensible group.
      for (const auto& iv : merged) {
        std::ostringstream nameStream;
        nameStream << weekPrefix << iv.start.monthOfYear().valueName() << iv.start.dayOfMonth() << "-" << iv.end.monthOfYear().valueName()
                   << iv.end.dayOfMonth();
        const std::string weekName = nameStream.str();

        ScheduleWeek week(model);
        week.setName(weekName);

        auto getDay = [&](const openstudio::Handle& h) -> boost::optional<ScheduleDay> { return model.getModelObject<ScheduleDay>(h); };

        if (auto d = getDay(iv.pattern[0])) {
          week.setSundaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[1])) {
          week.setMondaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[2])) {
          week.setTuesdaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[3])) {
          week.setWednesdaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[4])) {
          week.setThursdaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[5])) {
          week.setFridaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[6])) {
          week.setSaturdaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[7])) {
          week.setHolidaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[8])) {
          week.setSummerDesignDaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[9])) {
          week.setWinterDesignDaySchedule(*d);
        }
        if (auto d = getDay(iv.pattern[10])) {
          week.setCustomDay1Schedule(*d);
        }
        if (auto d = getDay(iv.pattern[11])) {
          week.setCustomDay2Schedule(*d);
        }

        auto extGroup = ruleset.pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
        OS_ASSERT(!extGroup.empty());
        extGroup.setPointer(Schedule_YearExtensibleFields::Schedule_WeekName, week.handle());
        extGroup.setInt(Schedule_YearExtensibleFields::StartMonth, static_cast<int>(openstudio::month(iv.start.monthOfYear())));
        extGroup.setInt(Schedule_YearExtensibleFields::StartDay, static_cast<int>(iv.start.dayOfMonth()));
        extGroup.setInt(Schedule_YearExtensibleFields::EndMonth, static_cast<int>(openstudio::month(iv.end.monthOfYear())));
        extGroup.setInt(Schedule_YearExtensibleFields::EndDay, static_cast<int>(iv.end.dayOfMonth()));
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
