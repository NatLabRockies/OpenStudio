/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

Schedule::Schedule(IddObjectType type, const Model& model) : ModelObject(type, model) {
  OS_ASSERT(getImpl<detail::Schedule_Impl>());
}

Schedule::Schedule(std::shared_ptr<detail::Schedule_Impl> impl) : ModelObject(std::move(impl)) {
  OS_ASSERT(getImpl<detail::Schedule_Impl>());
}

}  // namespace epmodel
}  // namespace openstudio
