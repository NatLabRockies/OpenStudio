/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleRuleset.hpp"
#include "ScheduleRuleset_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ScheduleRuleset::ScheduleRuleset(const Model& model) : ModelObject(ScheduleRuleset::iddObjectType(), model) {}

ScheduleRuleset::ScheduleRuleset(std::shared_ptr<detail::ScheduleRuleset_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ScheduleRuleset::iddObjectType() {
  return IddObjectType::Schedule_Year;
}

}  // namespace epmodel
}  // namespace openstudio
