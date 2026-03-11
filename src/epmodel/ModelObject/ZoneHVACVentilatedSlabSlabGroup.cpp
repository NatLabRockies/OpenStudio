/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACVentilatedSlabSlabGroup.hpp"
#include "ZoneHVACVentilatedSlabSlabGroup_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACVentilatedSlabSlabGroup::ZoneHVACVentilatedSlabSlabGroup(const Model& model)
    : ModelObject(ZoneHVACVentilatedSlabSlabGroup::iddObjectType(), model) {}

  ZoneHVACVentilatedSlabSlabGroup::ZoneHVACVentilatedSlabSlabGroup(std::shared_ptr<detail::ZoneHVACVentilatedSlabSlabGroup_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACVentilatedSlabSlabGroup::iddObjectType() {
    return IddObjectType::ZoneHVAC_VentilatedSlab_SlabGroup;
  }

}  // namespace epmodel
}  // namespace openstudio
