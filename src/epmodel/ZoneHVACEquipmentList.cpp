/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACEquipmentList.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ZoneHVACEquipmentList::ZoneHVACEquipmentList(const Model& model) : ModelObject(ZoneHVACEquipmentList::iddObjectType(), model) {
  auto impl = getImpl<detail::ZoneHVACEquipmentList_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

ZoneHVACEquipmentList::ZoneHVACEquipmentList(std::shared_ptr<detail::ZoneHVACEquipmentList_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ZoneHVACEquipmentList::iddObjectType() {
  return IddObjectType::ZoneHVAC_EquipmentList;
}

}  // namespace epmodel
}  // namespace openstudio
