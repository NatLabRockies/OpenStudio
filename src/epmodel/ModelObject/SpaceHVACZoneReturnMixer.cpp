/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceHVACZoneReturnMixer.hpp"
#include "SpaceHVACZoneReturnMixer_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

SpaceHVACZoneReturnMixer::SpaceHVACZoneReturnMixer(const Model& model)
  : ModelObject(SpaceHVACZoneReturnMixer::iddObjectType(), model) {}

SpaceHVACZoneReturnMixer::SpaceHVACZoneReturnMixer(std::shared_ptr<detail::SpaceHVACZoneReturnMixer_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SpaceHVACZoneReturnMixer::iddObjectType() {
  return IddObjectType::SpaceHVAC_ZoneReturnMixer;
}

}  // namespace epmodel
}  // namespace openstudio
