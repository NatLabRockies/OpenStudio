/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleYear.hpp"
#include "ScheduleYear_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Year_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleYear::ScheduleYear(const Model& model) : Schedule(ScheduleYear::iddObjectType(), model) {}

  ScheduleYear::ScheduleYear(IddObjectType type, const Model& model) : Schedule(type, model) {}

  ScheduleYear::ScheduleYear(std::shared_ptr<detail::ScheduleYear_Impl> impl) : Schedule(std::move(impl)) {}

  IddObjectType ScheduleYear::iddObjectType() {
    return IddObjectType::Schedule_Year;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned ScheduleYear_Impl::scheduleTypeLimitsFieldIndex() const {
      return openstudio::Schedule_YearFields::ScheduleTypeLimitsName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
