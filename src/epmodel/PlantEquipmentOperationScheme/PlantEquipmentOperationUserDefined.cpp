/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationUserDefined.hpp"
#include "PlantEquipmentOperationUserDefined_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  PlantEquipmentOperationUserDefined::PlantEquipmentOperationUserDefined(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationUserDefined::iddObjectType(), model) {}

  PlantEquipmentOperationUserDefined::PlantEquipmentOperationUserDefined(std::shared_ptr<detail::PlantEquipmentOperationUserDefined_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationUserDefined::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_UserDefined;
  }

}  // namespace epmodel
}  // namespace openstudio
