/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Compact_FieldEnums.hxx>
#include <utilities/idd/Schedule_Constant_FieldEnums.hxx>
#include <utilities/idd/Schedule_File_FieldEnums.hxx>
#include <utilities/idd/Schedule_Year_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Schedule::Schedule(IddObjectType type, const Model& model) : ScheduleBase(type, model) {
    OS_ASSERT(getImpl<detail::Schedule_Impl>());
  }

  Schedule::Schedule(std::shared_ptr<detail::Schedule_Impl> impl) : ScheduleBase(std::move(impl)) {
    OS_ASSERT(getImpl<detail::Schedule_Impl>());
  }

  namespace detail {

    boost::optional<unsigned> Schedule_Impl::scheduleTypeLimitsFieldIndex() const {
      switch (iddObject().type().value()) {
        case IddObjectType::Schedule_Constant:
          return openstudio::Schedule_ConstantFields::ScheduleTypeLimitsName;
        case IddObjectType::Schedule_Compact:
          return openstudio::Schedule_CompactFields::ScheduleTypeLimitsName;
        case IddObjectType::Schedule_Year:
          return openstudio::Schedule_YearFields::ScheduleTypeLimitsName;
        case IddObjectType::Schedule_File:
          return openstudio::Schedule_FileFields::ScheduleTypeLimitsName;
        default:
          return boost::none;
      }
    }

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
