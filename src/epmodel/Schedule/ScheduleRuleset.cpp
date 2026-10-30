/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleRuleset.hpp"
#include "ScheduleRuleset_Impl.hpp"
#include "ScheduleRule.hpp"
#include "ScheduleRule_Impl.hpp"

#include "Model.hpp"
#include "ScheduleBase/ScheduleDay.hpp"
#include "ScheduleBase/ScheduleDay_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Year_Rules_FieldEnums.hxx>
#include <utilities/time/Time.hpp>

namespace openstudio {
namespace epmodel {

  ScheduleRuleset::ScheduleRuleset(const Model& model) : Schedule(ScheduleRuleset::iddObjectType(), model) {
    ScheduleDay defaultDaySchedule(model);
    OS_ASSERT(defaultDaySchedule.addValue(openstudio::Time(1, 0), 0.0));
    OS_ASSERT(getImpl<detail::ScheduleRuleset_Impl>()->setDefaultDaySchedule(defaultDaySchedule));
  }

  ScheduleRuleset::ScheduleRuleset(const Model& model, double value) : ScheduleRuleset(model) {
    OS_ASSERT(defaultDaySchedule().addValue(openstudio::Time(1, 0), value));
  }

  ScheduleRuleset::ScheduleRuleset(std::shared_ptr<detail::ScheduleRuleset_Impl> impl) : Schedule(std::move(impl)) {}

  IddObjectType ScheduleRuleset::iddObjectType() {
    return IddObjectType::Schedule_Year_Rules;
  }

  std::vector<ScheduleRule> ScheduleRuleset::scheduleRules() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->scheduleRules();
  }

  bool ScheduleRuleset::setScheduleRulePriorityOrder(ScheduleRule& scheduleRule, unsigned priorityOrder) {
    return getImpl<detail::ScheduleRuleset_Impl>()->setScheduleRulePriorityOrder(scheduleRule, priorityOrder);
  }

  bool ScheduleRuleset::setScheduleRuleIndex(ScheduleRule& scheduleRule, unsigned index) {
    return setScheduleRulePriorityOrder(scheduleRule, index);
  }

  std::vector<int> ScheduleRuleset::getActiveRuleIndices(const openstudio::Date& startDate, const openstudio::Date& endDate) const {
    return getImpl<detail::ScheduleRuleset_Impl>()->getActiveRuleIndices(startDate, endDate);
  }

  std::vector<ScheduleDay> ScheduleRuleset::getDaySchedules(const openstudio::Date& startDate, const openstudio::Date& endDate) const {
    return getImpl<detail::ScheduleRuleset_Impl>()->getDaySchedules(startDate, endDate);
  }

  ScheduleDay ScheduleRuleset::defaultDaySchedule() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->defaultDaySchedule();
  }

  ScheduleDay ScheduleRuleset::summerDesignDaySchedule() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->summerDesignDaySchedule();
  }

  bool ScheduleRuleset::isSummerDesignDayScheduleDefaulted() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->isSummerDesignDayScheduleDefaulted();
  }

  bool ScheduleRuleset::setSummerDesignDaySchedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleRuleset_Impl>()->setSummerDesignDaySchedule(schedule);
  }

  void ScheduleRuleset::resetSummerDesignDaySchedule() {
    getImpl<detail::ScheduleRuleset_Impl>()->resetSummerDesignDaySchedule();
  }

  ScheduleDay ScheduleRuleset::winterDesignDaySchedule() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->winterDesignDaySchedule();
  }

  bool ScheduleRuleset::isWinterDesignDayScheduleDefaulted() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->isWinterDesignDayScheduleDefaulted();
  }

  bool ScheduleRuleset::setWinterDesignDaySchedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleRuleset_Impl>()->setWinterDesignDaySchedule(schedule);
  }

  void ScheduleRuleset::resetWinterDesignDaySchedule() {
    getImpl<detail::ScheduleRuleset_Impl>()->resetWinterDesignDaySchedule();
  }

  ScheduleDay ScheduleRuleset::holidaySchedule() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->holidaySchedule();
  }

  bool ScheduleRuleset::isHolidayScheduleDefaulted() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->isHolidayScheduleDefaulted();
  }

  bool ScheduleRuleset::setHolidaySchedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleRuleset_Impl>()->setHolidaySchedule(schedule);
  }

  void ScheduleRuleset::resetHolidaySchedule() {
    getImpl<detail::ScheduleRuleset_Impl>()->resetHolidaySchedule();
  }

  ScheduleDay ScheduleRuleset::customDay1Schedule() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->customDay1Schedule();
  }

  bool ScheduleRuleset::isCustomDay1ScheduleDefaulted() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->isCustomDay1ScheduleDefaulted();
  }

  bool ScheduleRuleset::setCustomDay1Schedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleRuleset_Impl>()->setCustomDay1Schedule(schedule);
  }

  void ScheduleRuleset::resetCustomDay1Schedule() {
    getImpl<detail::ScheduleRuleset_Impl>()->resetCustomDay1Schedule();
  }

  ScheduleDay ScheduleRuleset::customDay2Schedule() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->customDay2Schedule();
  }

  bool ScheduleRuleset::isCustomDay2ScheduleDefaulted() const {
    return getImpl<detail::ScheduleRuleset_Impl>()->isCustomDay2ScheduleDefaulted();
  }

  bool ScheduleRuleset::setCustomDay2Schedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleRuleset_Impl>()->setCustomDay2Schedule(schedule);
  }

  void ScheduleRuleset::resetCustomDay2Schedule() {
    getImpl<detail::ScheduleRuleset_Impl>()->resetCustomDay2Schedule();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<ScheduleRule> ScheduleRuleset_Impl::scheduleRules() const {
      auto result = getObject<ModelObject>().getModelObjectSources<ScheduleRule>(ScheduleRule::iddObjectType());
      std::sort(result.begin(), result.end(), [](const ScheduleRule& left, const ScheduleRule& right) {
        return left.rulePriorityOrder() < right.rulePriorityOrder();
      });
      return result;
    }

    bool ScheduleRuleset_Impl::setScheduleRulePriorityOrder(ScheduleRule& scheduleRule, unsigned priorityOrder) {
      auto rules = this->scheduleRules();
      if (priorityOrder >= rules.size()) {
        return false;
      }

      auto target = std::find_if(rules.begin(), rules.end(), [&scheduleRule](const ScheduleRule& rule) {
        return rule.handle() == scheduleRule.handle();
      });
      if (target == rules.end()) {
        return false;
      }

      const auto oldPriorityOrder = static_cast<unsigned>(target->rulePriorityOrder());
      if (oldPriorityOrder == priorityOrder) {
        return true;
      }

      if (!scheduleRule.setRulePriorityOrderDirect(priorityOrder)) {
        return false;
      }

      for (auto& rule : rules) {
        if (rule.handle() == scheduleRule.handle()) {
          continue;
        }

        const auto currentPriorityOrder = static_cast<unsigned>(rule.rulePriorityOrder());
        if (oldPriorityOrder > priorityOrder && currentPriorityOrder >= priorityOrder && currentPriorityOrder < oldPriorityOrder) {
          OS_ASSERT(rule.setRulePriorityOrderDirect(currentPriorityOrder + 1));
        } else if (oldPriorityOrder < priorityOrder && currentPriorityOrder > oldPriorityOrder && currentPriorityOrder <= priorityOrder) {
          OS_ASSERT(rule.setRulePriorityOrderDirect(currentPriorityOrder - 1));
        }
      }
      return true;
    }

    std::vector<int> ScheduleRuleset_Impl::getActiveRuleIndices(const openstudio::Date& startDate, const openstudio::Date& endDate) const {
      std::vector<openstudio::Date> dates;
      if (startDate <= endDate) {
        for (auto date = startDate; date <= endDate; date += openstudio::Time(1)) {
          dates.push_back(date);
        }
      } else {
        for (auto date = startDate, lastDay = openstudio::Date(MonthOfYear::Dec, 31); date <= lastDay; date += openstudio::Time(1)) {
          dates.push_back(date);
        }
        for (auto date = openstudio::Date(MonthOfYear::Jan, 1); date <= endDate; date += openstudio::Time(1)) {
          dates.push_back(date);
        }
      }

      const auto rules = scheduleRules();
      std::vector<int> result(dates.size(), -1);
      for (unsigned dateIndex = 0; dateIndex < dates.size(); ++dateIndex) {
        for (unsigned ruleIndex = 0; ruleIndex < rules.size(); ++ruleIndex) {
          if (rules[ruleIndex].containsDate(dates[dateIndex])) {
            result[dateIndex] = static_cast<int>(ruleIndex);
            break;
          }
        }
      }
      return result;
    }

    std::vector<ScheduleDay> ScheduleRuleset_Impl::getDaySchedules(const openstudio::Date& startDate, const openstudio::Date& endDate) const {
      const auto rules = scheduleRules();
      const auto activeRuleIndices = getActiveRuleIndices(startDate, endDate);
      std::vector<ScheduleDay> result;
      result.reserve(activeRuleIndices.size());
      for (const int activeRuleIndex : activeRuleIndices) {
        if (activeRuleIndex < 0) {
          result.push_back(defaultDaySchedule());
        } else {
          result.push_back(rules[activeRuleIndex].daySchedule());
        }
      }
      return result;
    }

    ScheduleDay ScheduleRuleset_Impl::defaultDaySchedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Year_RulesFields::DefaultDayScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool ScheduleRuleset_Impl::setDefaultDaySchedule(const ScheduleDay& schedule) {
      return setPointer(Schedule_Year_RulesFields::DefaultDayScheduleName, schedule.handle());
    }

    ScheduleDay ScheduleRuleset_Impl::summerDesignDaySchedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Year_RulesFields::SummerDesignDayScheduleName);
      return schedule ? *schedule : defaultDaySchedule();
    }

    bool ScheduleRuleset_Impl::isSummerDesignDayScheduleDefaulted() const {
      return isEmpty(Schedule_Year_RulesFields::SummerDesignDayScheduleName);
    }

    bool ScheduleRuleset_Impl::setSummerDesignDaySchedule(const ScheduleDay& schedule) {
      return setPointer(Schedule_Year_RulesFields::SummerDesignDayScheduleName, schedule.handle());
    }

    void ScheduleRuleset_Impl::resetSummerDesignDaySchedule() {
      OS_ASSERT(setString(Schedule_Year_RulesFields::SummerDesignDayScheduleName, ""));
    }

    ScheduleDay ScheduleRuleset_Impl::winterDesignDaySchedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Year_RulesFields::WinterDesignDayScheduleName);
      return schedule ? *schedule : defaultDaySchedule();
    }

    bool ScheduleRuleset_Impl::isWinterDesignDayScheduleDefaulted() const {
      return isEmpty(Schedule_Year_RulesFields::WinterDesignDayScheduleName);
    }

    bool ScheduleRuleset_Impl::setWinterDesignDaySchedule(const ScheduleDay& schedule) {
      return setPointer(Schedule_Year_RulesFields::WinterDesignDayScheduleName, schedule.handle());
    }

    void ScheduleRuleset_Impl::resetWinterDesignDaySchedule() {
      OS_ASSERT(setString(Schedule_Year_RulesFields::WinterDesignDayScheduleName, ""));
    }

    ScheduleDay ScheduleRuleset_Impl::holidaySchedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Year_RulesFields::HolidayScheduleName);
      return schedule ? *schedule : defaultDaySchedule();
    }

    bool ScheduleRuleset_Impl::isHolidayScheduleDefaulted() const {
      return isEmpty(Schedule_Year_RulesFields::HolidayScheduleName);
    }

    bool ScheduleRuleset_Impl::setHolidaySchedule(const ScheduleDay& schedule) {
      return setPointer(Schedule_Year_RulesFields::HolidayScheduleName, schedule.handle());
    }

    void ScheduleRuleset_Impl::resetHolidaySchedule() {
      OS_ASSERT(setString(Schedule_Year_RulesFields::HolidayScheduleName, ""));
    }

    ScheduleDay ScheduleRuleset_Impl::customDay1Schedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Year_RulesFields::CustomDay1ScheduleName);
      return schedule ? *schedule : defaultDaySchedule();
    }

    bool ScheduleRuleset_Impl::isCustomDay1ScheduleDefaulted() const {
      return isEmpty(Schedule_Year_RulesFields::CustomDay1ScheduleName);
    }

    bool ScheduleRuleset_Impl::setCustomDay1Schedule(const ScheduleDay& schedule) {
      return setPointer(Schedule_Year_RulesFields::CustomDay1ScheduleName, schedule.handle());
    }

    void ScheduleRuleset_Impl::resetCustomDay1Schedule() {
      OS_ASSERT(setString(Schedule_Year_RulesFields::CustomDay1ScheduleName, ""));
    }

    ScheduleDay ScheduleRuleset_Impl::customDay2Schedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Year_RulesFields::CustomDay2ScheduleName);
      return schedule ? *schedule : defaultDaySchedule();
    }

    bool ScheduleRuleset_Impl::isCustomDay2ScheduleDefaulted() const {
      return isEmpty(Schedule_Year_RulesFields::CustomDay2ScheduleName);
    }

    bool ScheduleRuleset_Impl::setCustomDay2Schedule(const ScheduleDay& schedule) {
      return setPointer(Schedule_Year_RulesFields::CustomDay2ScheduleName, schedule.handle());
    }

    void ScheduleRuleset_Impl::resetCustomDay2Schedule() {
      OS_ASSERT(setString(Schedule_Year_RulesFields::CustomDay2ScheduleName, ""));
    }

    unsigned ScheduleRuleset_Impl::scheduleTypeLimitsFieldIndex() const {
      return Schedule_Year_RulesFields::ScheduleTypeLimitsName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio