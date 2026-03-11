/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACOutdoorAirUnitEquipmentList.hpp"
#include "ZoneHVACOutdoorAirUnitEquipmentList_Impl.hpp"

#include "Model.hpp"

namespace openstudio {
namespace epmodel {

  ZoneHVACOutdoorAirUnitEquipmentList::ZoneHVACOutdoorAirUnitEquipmentList(const Model& model)
    : ModelObject(ZoneHVACOutdoorAirUnitEquipmentList::iddObjectType(), model) {}

  ZoneHVACOutdoorAirUnitEquipmentList::ZoneHVACOutdoorAirUnitEquipmentList(std::shared_ptr<detail::ZoneHVACOutdoorAirUnitEquipmentList_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACOutdoorAirUnitEquipmentList::iddObjectType() {
    return IddObjectType::ZoneHVAC_OutdoorAirUnit_EquipmentList;
  }

}  // namespace epmodel
}  // namespace openstudio
