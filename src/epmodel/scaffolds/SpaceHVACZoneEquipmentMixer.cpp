/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceHVACZoneEquipmentMixer.hpp"
#include "SpaceHVACZoneEquipmentMixer_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SpaceHVACZoneEquipmentMixer::SpaceHVACZoneEquipmentMixer(const Model& model) : ModelObject(SpaceHVACZoneEquipmentMixer::iddObjectType(), model) {}

  SpaceHVACZoneEquipmentMixer::SpaceHVACZoneEquipmentMixer(std::shared_ptr<detail::SpaceHVACZoneEquipmentMixer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SpaceHVACZoneEquipmentMixer::iddObjectType() {
    return IddObjectType::SpaceHVAC_ZoneEquipmentMixer;
  }

}  // namespace epmodel
}  // namespace openstudio
