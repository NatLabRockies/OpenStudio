/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleWeekCompact.hpp"
#include "ScheduleWeekCompact_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleWeekCompact::ScheduleWeekCompact(const Model& model) : ModelObject(ScheduleWeekCompact::iddObjectType(), model) {}

  ScheduleWeekCompact::ScheduleWeekCompact(std::shared_ptr<detail::ScheduleWeekCompact_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ScheduleWeekCompact::iddObjectType() {
    return IddObjectType::Schedule_Week_Compact;
  }

}  // namespace epmodel
}  // namespace openstudio
