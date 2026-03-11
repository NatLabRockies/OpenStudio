/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerScheduledOff.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOff_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerScheduledOff::AvailabilityManagerScheduledOff(const Model& model)
  : ModelObject(AvailabilityManagerScheduledOff::iddObjectType(), model) {}

AvailabilityManagerScheduledOff::AvailabilityManagerScheduledOff(std::shared_ptr<detail::AvailabilityManagerScheduledOff_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AvailabilityManagerScheduledOff::iddObjectType() {
  return IddObjectType::AvailabilityManager_ScheduledOff;
}

}  // namespace epmodel
}  // namespace openstudio
