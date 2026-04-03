/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationUncontrolled.hpp"
#include "PlantEquipmentOperationUncontrolled_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantEquipmentOperationUncontrolled::PlantEquipmentOperationUncontrolled(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationUncontrolled::iddObjectType(), model) {}

  PlantEquipmentOperationUncontrolled::PlantEquipmentOperationUncontrolled(std::shared_ptr<detail::PlantEquipmentOperationUncontrolled_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationUncontrolled::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_Uncontrolled;
  }

}  // namespace epmodel
}  // namespace openstudio
