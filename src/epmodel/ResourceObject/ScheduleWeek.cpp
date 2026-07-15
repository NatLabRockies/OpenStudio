/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ScheduleWeek.hpp"
#include "ResourceObject/ScheduleWeek_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleWeek::ScheduleWeek(const Model& model) : ModelObject(ScheduleWeek::iddObjectType(), model) {}

  ScheduleWeek::ScheduleWeek(std::shared_ptr<detail::ScheduleWeek_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ScheduleWeek::iddObjectType() {
    return IddObjectType::Schedule_Week_Daily;
  }

}  // namespace epmodel
}  // namespace openstudio
