/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleBase/ScheduleBase.hpp"
#include "ScheduleBase/ScheduleBase_Impl.hpp"

#include "Model.hpp"
#include "ResourceObject/ScheduleTypeLimits.hpp"
#include "ResourceObject/ScheduleTypeLimits_Impl.hpp"

#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

  ScheduleBase::ScheduleBase(IddObjectType type, const Model& model) : ResourceObject(type, model) {}

  ScheduleBase::ScheduleBase(std::shared_ptr<detail::ScheduleBase_Impl> impl)
    : ResourceObject(std::static_pointer_cast<detail::ResourceObject_Impl>(std::move(impl))) {}

  boost::optional<ScheduleTypeLimits> ScheduleBase::scheduleTypeLimits() const {
    return getImpl<detail::ScheduleBase_Impl>()->scheduleTypeLimits();
  }

  bool ScheduleBase::setScheduleTypeLimits(const ScheduleTypeLimits& scheduleTypeLimits) {
    return getImpl<detail::ScheduleBase_Impl>()->setScheduleTypeLimits(scheduleTypeLimits);
  }

  bool ScheduleBase::resetScheduleTypeLimits() {
    return getImpl<detail::ScheduleBase_Impl>()->resetScheduleTypeLimits();
  }

  void ScheduleBase::ensureNoLeapDays() {
    getImpl<detail::ScheduleBase_Impl>()->ensureNoLeapDays();
  }

  namespace detail {

    bool ScheduleBase_Impl::valuesAreWithinBounds() const {
      if (auto scheduleTypeLimits_ = this->scheduleTypeLimits()) {
        OptionalDouble minBound = scheduleTypeLimits_->lowerLimitValue();
        OptionalDouble maxBound = scheduleTypeLimits_->upperLimitValue();
        if (minBound || maxBound) {
          for (double value : values()) {
            if (minBound && (value < *minBound)) {
              return false;
            }
            if (maxBound && (value > *maxBound)) {
              return false;
            }
          }
        }
      }
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
