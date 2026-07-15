/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CondenserEquipmentOperationSchemes.hpp"
#include "CondenserEquipmentOperationSchemes_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CondenserEquipmentOperationSchemes::CondenserEquipmentOperationSchemes(const Model& model)
    : ModelObject(CondenserEquipmentOperationSchemes::iddObjectType(), model) {}

  CondenserEquipmentOperationSchemes::CondenserEquipmentOperationSchemes(std::shared_ptr<detail::CondenserEquipmentOperationSchemes_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CondenserEquipmentOperationSchemes::iddObjectType() {
    return IddObjectType::CondenserEquipmentOperationSchemes;
  }

}  // namespace epmodel
}  // namespace openstudio
