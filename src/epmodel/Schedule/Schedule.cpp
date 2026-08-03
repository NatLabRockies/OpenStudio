/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  Schedule::Schedule(IddObjectType type, const Model& model) : ScheduleBase(type, model) {
    OS_ASSERT(getImpl<detail::Schedule_Impl>());
  }

  Schedule::Schedule(std::shared_ptr<detail::Schedule_Impl> impl) : ScheduleBase(std::move(impl)) {
    OS_ASSERT(getImpl<detail::Schedule_Impl>());
  }

  namespace detail {

    std::vector<double> Schedule_Impl::values() const {
      // TODO: implement
      return {};
    }

    void Schedule_Impl::ensureNoLeapDays() {
      // TODO: implement if needed
    }

    bool Schedule_Impl::candidateIsCompatibleWithCurrentUse(const ScheduleTypeLimits& /*candidate*/) const {
      // TODO: implement compatibility check
      return true;
    }

    bool Schedule_Impl::okToResetScheduleTypeLimits() const {
      // TODO: implement check
      return true;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
