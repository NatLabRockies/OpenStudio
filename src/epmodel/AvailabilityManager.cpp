/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager.hpp"
#include "AvailabilityManager_Impl.hpp"

#include "AvailabilityManagerAssignmentList.hpp"
#include "AvailabilityManagerAssignmentList_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

AvailabilityManager::AvailabilityManager(IddObjectType type, const Model& model) : ModelObject(type, model) {
  OS_ASSERT(getImpl<detail::AvailabilityManager_Impl>());
}

AvailabilityManager::AvailabilityManager(std::shared_ptr<detail::AvailabilityManager_Impl> impl) : ModelObject(std::move(impl)) {}

boost::optional<Loop> AvailabilityManager::loop() const {
  return getImpl<detail::AvailabilityManager_Impl>()->loop();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<openstudio::epmodel::Loop> AvailabilityManager_Impl::loop() const {
  const auto thisAvm = getObject<openstudio::epmodel::AvailabilityManager>();
  for (const auto& assignmentList : model().getConcreteModelObjects<openstudio::epmodel::AvailabilityManagerAssignmentList>()) {
    for (const auto& avm : assignmentList.availabilityManagers()) {
      if (avm == thisAvm) {
        return assignmentList.loop();
      }
    }
  }
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
