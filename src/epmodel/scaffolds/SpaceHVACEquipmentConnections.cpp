/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceHVACEquipmentConnections.hpp"
#include "SpaceHVACEquipmentConnections_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SpaceHVACEquipmentConnections::SpaceHVACEquipmentConnections(const Model& model)
    : ModelObject(SpaceHVACEquipmentConnections::iddObjectType(), model) {}

  SpaceHVACEquipmentConnections::SpaceHVACEquipmentConnections(std::shared_ptr<detail::SpaceHVACEquipmentConnections_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SpaceHVACEquipmentConnections::iddObjectType() {
    return IddObjectType::SpaceHVAC_EquipmentConnections;
  }

}  // namespace epmodel
}  // namespace openstudio
