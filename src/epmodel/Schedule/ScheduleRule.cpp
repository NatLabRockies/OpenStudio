/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleRule.hpp"
#include "ScheduleRule_Impl.hpp"
#include "ScheduleRuleset.hpp"
#include "ScheduleRuleset_Impl.hpp"

#include "Model.hpp"
#include "ScheduleBase/ScheduleDay.hpp"
#include "ScheduleBase/ScheduleDay_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Week_Rule_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    openstudio::Date scheduleRuleDate(unsigned month, unsigned day) {
      const int year = month == 2 && day == 29 ? 2008 : 2009;
      return openstudio::Date(openstudio::MonthOfYear(month), day, year);
    }

  }  // namespace

  ScheduleRule::ScheduleRule(ScheduleRuleset& scheduleRuleset) : ScheduleRule(scheduleRuleset, scheduleRuleset.defaultDaySchedule()) {}

  ScheduleRule::ScheduleRule(ScheduleRuleset& scheduleRuleset, const ScheduleDay& daySchedule)
    : ParentObject(ScheduleRule::iddObjectType(), scheduleRuleset.model()) {
    auto impl = getImpl<detail::ScheduleRule_Impl>();
    const auto initialPriorityOrder = static_cast<unsigned>(scheduleRuleset.scheduleRules().size());
    OS_ASSERT(impl->setDaySchedule(daySchedule));
    OS_ASSERT(impl->setRulePriorityOrderDirect(initialPriorityOrder));
    OS_ASSERT(setPointer(Schedule_Week_RuleFields::ScheduleYearRulesName, scheduleRuleset.handle()));
    OS_ASSERT(scheduleRuleset.setScheduleRulePriorityOrder(*this, 0));
  }

  ScheduleRule::ScheduleRule(std::shared_ptr<detail::ScheduleRule_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType ScheduleRule::iddObjectType() {
    return IddObjectType::Schedule_Week_Rule;
  }

  std::vector<std::string> ScheduleRule::validDateSpecificationTypeValues() {
    return {"DateRange", "SpecificDates"};
  }

  ScheduleRuleset ScheduleRule::scheduleRuleset() const {
    return getImpl<detail::ScheduleRule_Impl>()->scheduleRuleset();
  }

  int ScheduleRule::rulePriorityOrder() const {
    return getImpl<detail::ScheduleRule_Impl>()->rulePriorityOrder();
  }

  bool ScheduleRule::setRulePriorityOrder(unsigned priorityOrder) {
    return getImpl<detail::ScheduleRule_Impl>()->setRulePriorityOrder(priorityOrder);
  }

  int ScheduleRule::ruleIndex() const {
    return rulePriorityOrder();
  }

  bool ScheduleRule::setRuleIndex(unsigned index) {
    return setRulePriorityOrder(index);
  }

  bool ScheduleRule::setRulePriorityOrderDirect(unsigned priorityOrder) {
    return getImpl<detail::ScheduleRule_Impl>()->setRulePriorityOrderDirect(priorityOrder);
  }

  ScheduleDay ScheduleRule::daySchedule() const {
    return getImpl<detail::ScheduleRule_Impl>()->daySchedule();
  }

  bool ScheduleRule::setDaySchedule(const ScheduleDay& daySchedule) {
    return getImpl<detail::ScheduleRule_Impl>()->setDaySchedule(daySchedule);
  }

  boost::optional<openstudio::Date> ScheduleRule::startDate() const {
    return getImpl<detail::ScheduleRule_Impl>()->startDate();
  }

  boost::optional<openstudio::Date> ScheduleRule::endDate() const {
    return getImpl<detail::ScheduleRule_Impl>()->endDate();
  }

  std::vector<openstudio::Date> ScheduleRule::specificDates() const {
    return getImpl<detail::ScheduleRule_Impl>()->specificDates();
  }

  std::string ScheduleRule::dateSpecificationType() const {
    return getImpl<detail::ScheduleRule_Impl>()->dateSpecificationType();
  }

  bool ScheduleRule::applySunday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applySunday();
  }

  bool ScheduleRule::setApplySunday(bool applySunday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplySunday(applySunday);
  }

  void ScheduleRule::setApplySundayNoFail(bool applySunday) {
    static_cast<void>(setApplySunday(applySunday));
  }

  bool ScheduleRule::applyMonday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyMonday();
  }

  bool ScheduleRule::setApplyMonday(bool applyMonday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyMonday(applyMonday);
  }

  void ScheduleRule::setApplyMondayNoFail(bool applyMonday) {
    static_cast<void>(setApplyMonday(applyMonday));
  }

  bool ScheduleRule::applyTuesday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyTuesday();
  }

  bool ScheduleRule::setApplyTuesday(bool applyTuesday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyTuesday(applyTuesday);
  }

  void ScheduleRule::setApplyTuesdayNoFail(bool applyTuesday) {
    static_cast<void>(setApplyTuesday(applyTuesday));
  }

  bool ScheduleRule::applyWednesday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyWednesday();
  }

  bool ScheduleRule::setApplyWednesday(bool applyWednesday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyWednesday(applyWednesday);
  }

  void ScheduleRule::setApplyWednesdayNoFail(bool applyWednesday) {
    static_cast<void>(setApplyWednesday(applyWednesday));
  }

  bool ScheduleRule::applyThursday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyThursday();
  }

  bool ScheduleRule::setApplyThursday(bool applyThursday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyThursday(applyThursday);
  }

  void ScheduleRule::setApplyThursdayNoFail(bool applyThursday) {
    static_cast<void>(setApplyThursday(applyThursday));
  }

  bool ScheduleRule::applyFriday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyFriday();
  }

  bool ScheduleRule::setApplyFriday(bool applyFriday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyFriday(applyFriday);
  }

  void ScheduleRule::setApplyFridayNoFail(bool applyFriday) {
    static_cast<void>(setApplyFriday(applyFriday));
  }

  bool ScheduleRule::applySaturday() const {
    return getImpl<detail::ScheduleRule_Impl>()->applySaturday();
  }

  bool ScheduleRule::setApplySaturday(bool applySaturday) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplySaturday(applySaturday);
  }

  void ScheduleRule::setApplySaturdayNoFail(bool applySaturday) {
    static_cast<void>(setApplySaturday(applySaturday));
  }

  bool ScheduleRule::applyAllDays() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyAllDays();
  }

  bool ScheduleRule::applyWeekdays() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyWeekdays();
  }

  bool ScheduleRule::applyWeekends() const {
    return getImpl<detail::ScheduleRule_Impl>()->applyWeekends();
  }

  bool ScheduleRule::setApplyAllDays(bool applyAllDays) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyAllDays(applyAllDays);
  }

  bool ScheduleRule::setApplyWeekdays(bool applyWeekdays) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyWeekdays(applyWeekdays);
  }

  bool ScheduleRule::setApplyWeekends(bool applyWeekends) {
    return getImpl<detail::ScheduleRule_Impl>()->setApplyWeekends(applyWeekends);
  }

  std::vector<ScheduleRuleDateRange> ScheduleRule::dateRanges() const {
    return getImpl<detail::ScheduleRule_Impl>()->dateRanges();
  }

  bool ScheduleRule::addDateRange(const openstudio::Date& startDate, const openstudio::Date& endDate) {
    return getImpl<detail::ScheduleRule_Impl>()->addDateRange(startDate, endDate);
  }

  bool ScheduleRule::setStartDate(const openstudio::Date& startDate) {
    return getImpl<detail::ScheduleRule_Impl>()->setStartDate(startDate);
  }

  bool ScheduleRule::setEndDate(const openstudio::Date& endDate) {
    return getImpl<detail::ScheduleRule_Impl>()->setEndDate(endDate);
  }

  bool ScheduleRule::addSpecificDate(const openstudio::Date& date) {
    return getImpl<detail::ScheduleRule_Impl>()->addSpecificDate(date);
  }

  void ScheduleRule::resetDateRanges() {
    getImpl<detail::ScheduleRule_Impl>()->resetDateRanges();
  }

  void ScheduleRule::ensureNoLeapDays() {
    getImpl<detail::ScheduleRule_Impl>()->ensureNoLeapDays();
  }

  bool ScheduleRule::containsDate(const openstudio::Date& date) const {
    return getImpl<detail::ScheduleRule_Impl>()->containsDate(date);
  }

  std::vector<bool> ScheduleRule::containsDates(const std::vector<openstudio::Date>& dates) const {
    return getImpl<detail::ScheduleRule_Impl>()->containsDates(dates);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    ScheduleRuleset ScheduleRule_Impl::scheduleRuleset() const {
      const auto result = getObject<ScheduleRule>().getModelObjectTarget<ScheduleRuleset>(Schedule_Week_RuleFields::ScheduleYearRulesName);
      OS_ASSERT(result);
      return *result;
    }

    int ScheduleRule_Impl::rulePriorityOrder() const {
      const auto value = getInt(Schedule_Week_RuleFields::RulePriorityOrder, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleRule_Impl::setRulePriorityOrder(unsigned priorityOrder) {
      auto ruleset = scheduleRuleset();
      auto rule = getObject<ScheduleRule>();
      return ruleset.setScheduleRulePriorityOrder(rule, priorityOrder);
    }

    bool ScheduleRule_Impl::setRulePriorityOrderDirect(unsigned priorityOrder) {
      return setInt(Schedule_Week_RuleFields::RulePriorityOrder, static_cast<int>(priorityOrder));
    }

    std::string ScheduleRule_Impl::dateSpecificationType() const {
      const auto ranges = dateRanges();
      const bool allSpecificDates = !ranges.empty() && std::all_of(ranges.begin(), ranges.end(), [](const ScheduleRuleDateRange& range) {
        return range.first.monthOfYear() == range.second.monthOfYear() && range.first.dayOfMonth() == range.second.dayOfMonth();
      });
      return allSpecificDates ? "SpecificDates" : "DateRange";
    }

    boost::optional<openstudio::Date> ScheduleRule_Impl::startDate() const {
      const auto ranges = dateRanges();
      if (ranges.size() == 1) {
        return ranges.front().first;
      }
      return boost::none;
    }

    boost::optional<openstudio::Date> ScheduleRule_Impl::endDate() const {
      const auto ranges = dateRanges();
      if (ranges.size() == 1) {
        return ranges.front().second;
      }
      return boost::none;
    }

    std::vector<openstudio::Date> ScheduleRule_Impl::specificDates() const {
      std::vector<openstudio::Date> result;
      for (const auto& range : dateRanges()) {
        if (range.first.monthOfYear() == range.second.monthOfYear() && range.first.dayOfMonth() == range.second.dayOfMonth()) {
          result.push_back(range.first);
        }
      }
      return result;
    }

    ScheduleDay ScheduleRule_Impl::daySchedule() const {
      const auto result = getObject<ScheduleRule>().getModelObjectTarget<ScheduleDay>(Schedule_Week_RuleFields::DayScheduleName);
      OS_ASSERT(result);
      return *result;
    }

    bool ScheduleRule_Impl::setDaySchedule(const ScheduleDay& daySchedule) {
      return setPointer(Schedule_Week_RuleFields::DayScheduleName, daySchedule.handle());
    }

    bool ScheduleRule_Impl::applyDay(unsigned fieldIndex) const {
      const auto value = getString(fieldIndex, true);
      OS_ASSERT(value);
      return istringEqual(*value, "Yes");
    }

    bool ScheduleRule_Impl::setApplyDay(unsigned fieldIndex, bool apply) {
      return setString(fieldIndex, apply ? "Yes" : "No");
    }

    bool ScheduleRule_Impl::applySunday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplySunday));
    }

    bool ScheduleRule_Impl::setApplySunday(bool applySunday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplySunday), applySunday);
    }

    bool ScheduleRule_Impl::applyMonday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyMonday));
    }

    bool ScheduleRule_Impl::setApplyMonday(bool applyMonday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyMonday), applyMonday);
    }

    bool ScheduleRule_Impl::applyTuesday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyTuesday));
    }

    bool ScheduleRule_Impl::setApplyTuesday(bool applyTuesday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyTuesday), applyTuesday);
    }

    bool ScheduleRule_Impl::applyWednesday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyWednesday));
    }

    bool ScheduleRule_Impl::setApplyWednesday(bool applyWednesday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyWednesday), applyWednesday);
    }

    bool ScheduleRule_Impl::applyThursday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyThursday));
    }

    bool ScheduleRule_Impl::setApplyThursday(bool applyThursday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyThursday), applyThursday);
    }

    bool ScheduleRule_Impl::applyFriday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyFriday));
    }

    bool ScheduleRule_Impl::setApplyFriday(bool applyFriday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplyFriday), applyFriday);
    }

    bool ScheduleRule_Impl::applySaturday() const {
      return applyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplySaturday));
    }

    bool ScheduleRule_Impl::setApplySaturday(bool applySaturday) {
      return setApplyDay(static_cast<unsigned>(Schedule_Week_RuleFields::ApplySaturday), applySaturday);
    }

    bool ScheduleRule_Impl::applyWeekdays() const {
      return applyMonday() && applyTuesday() && applyWednesday() && applyThursday() && applyFriday();
    }

    bool ScheduleRule_Impl::applyWeekends() const {
      return applySaturday() && applySunday();
    }

    bool ScheduleRule_Impl::applyAllDays() const {
      return applyWeekdays() && applyWeekends();
    }

    bool ScheduleRule_Impl::setApplyWeekdays(bool applyWeekdays) {
      return setApplyMonday(applyWeekdays) && setApplyTuesday(applyWeekdays) && setApplyWednesday(applyWeekdays) && setApplyThursday(applyWeekdays)
             && setApplyFriday(applyWeekdays);
    }

    bool ScheduleRule_Impl::setApplyWeekends(bool applyWeekends) {
      return setApplySaturday(applyWeekends) && setApplySunday(applyWeekends);
    }

    bool ScheduleRule_Impl::setApplyAllDays(bool applyAllDays) {
      return setApplyWeekdays(applyAllDays) && setApplyWeekends(applyAllDays);
    }

    std::vector<ScheduleRuleDateRange> ScheduleRule_Impl::dateRanges() const {
      std::vector<ScheduleRuleDateRange> result;
      for (const auto& group : getObject<ModelObject>().extensibleGroups()) {
        const auto startMonth = group.getInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::StartMonth));
        const auto startDay = group.getInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::StartDay));
        const auto endMonth = group.getInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::EndMonth));
        const auto endDay = group.getInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::EndDay));
        if (startMonth && startDay && endMonth && endDay) {
          result.emplace_back(scheduleRuleDate(*startMonth, *startDay), scheduleRuleDate(*endMonth, *endDay));
        }
      }
      return result;
    }

    bool ScheduleRule_Impl::addDateRange(const openstudio::Date& startDate, const openstudio::Date& endDate) {
      auto group = getObject<ModelObject>().pushExtensibleGroup();
            return group.setInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::StartMonth), startDate.monthOfYear().value())
              && group.setInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::StartDay), startDate.dayOfMonth())
              && group.setInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::EndMonth), endDate.monthOfYear().value())
              && group.setInt(static_cast<unsigned>(Schedule_Week_RuleExtensibleFields::EndDay), endDate.dayOfMonth());
    }

    bool ScheduleRule_Impl::setStartDate(const openstudio::Date& startDate) {
      const auto ranges = dateRanges();
      if (ranges.size() > 1) {
        return false;
      }
      const auto endDate = ranges.empty() ? openstudio::Date(MonthOfYear::Dec, 31) : ranges.front().second;
      resetDateRanges();
      return addDateRange(startDate, endDate);
    }

    bool ScheduleRule_Impl::setEndDate(const openstudio::Date& endDate) {
      const auto ranges = dateRanges();
      if (ranges.size() > 1) {
        return false;
      }
      const auto startDate = ranges.empty() ? openstudio::Date(MonthOfYear::Jan, 1) : ranges.front().first;
      resetDateRanges();
      return addDateRange(startDate, endDate);
    }

    bool ScheduleRule_Impl::addSpecificDate(const openstudio::Date& date) {
      return addDateRange(date, date);
    }

    void ScheduleRule_Impl::resetDateRanges() {
      getObject<ModelObject>().clearExtensibleGroups();
    }

    void ScheduleRule_Impl::ensureNoLeapDays() {
      auto ranges = dateRanges();
      for (auto& range : ranges) {
        if (range.first.monthOfYear().value() == 2 && range.first.dayOfMonth() == 29) {
          range.first = openstudio::Date(MonthOfYear::Feb, 28);
        }
        if (range.second.monthOfYear().value() == 2 && range.second.dayOfMonth() == 29) {
          range.second = openstudio::Date(MonthOfYear::Feb, 28);
        }
      }
      resetDateRanges();
      for (const auto& range : ranges) {
        OS_ASSERT(addDateRange(range.first, range.second));
      }
    }

    bool ScheduleRule_Impl::containsDate(const openstudio::Date& date) const {
      const auto current = std::make_pair(date.monthOfYear().value(), date.dayOfMonth());
      for (const auto& range : dateRanges()) {
        const auto start = std::make_pair(range.first.monthOfYear().value(), range.first.dayOfMonth());
        const auto end = std::make_pair(range.second.monthOfYear().value(), range.second.dayOfMonth());
        const bool inRange = start <= end ? current >= start && current <= end : current >= start || current <= end;
        if (!inRange) {
          continue;
        }

        switch (date.dayOfWeek().value()) {
          case DayOfWeek::Sunday:
            return applySunday();
          case DayOfWeek::Monday:
            return applyMonday();
          case DayOfWeek::Tuesday:
            return applyTuesday();
          case DayOfWeek::Wednesday:
            return applyWednesday();
          case DayOfWeek::Thursday:
            return applyThursday();
          case DayOfWeek::Friday:
            return applyFriday();
          case DayOfWeek::Saturday:
            return applySaturday();
          default:
            OS_ASSERT(false);
        }
      }
      return false;
    }

    std::vector<bool> ScheduleRule_Impl::containsDates(const std::vector<openstudio::Date>& dates) const {
      std::vector<bool> result;
      result.reserve(dates.size());
      for (const auto& date : dates) {
        result.push_back(containsDate(date));
      }
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio