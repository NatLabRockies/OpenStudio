/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerScheduledOn::AvailabilityManagerScheduledOn(const Model& model)
  : ModelObject(AvailabilityManagerScheduledOn::iddObjectType(), model) {}

AvailabilityManagerScheduledOn::AvailabilityManagerScheduledOn(std::shared_ptr<detail::AvailabilityManagerScheduledOn_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AvailabilityManagerScheduledOn::iddObjectType() {
  return IddObjectType::AvailabilityManager_ScheduledOn;
}

}  // namespace epmodel
}  // namespace openstudio
