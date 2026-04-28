/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CondenserEquipmentList.hpp"
#include "CondenserEquipmentList_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CondenserEquipmentList::CondenserEquipmentList(const Model& model) : ModelObject(CondenserEquipmentList::iddObjectType(), model) {}

CondenserEquipmentList::CondenserEquipmentList(std::shared_ptr<detail::CondenserEquipmentList_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CondenserEquipmentList::iddObjectType() {
  return IddObjectType::CondenserEquipmentList;
}

}  // namespace epmodel
}  // namespace openstudio
