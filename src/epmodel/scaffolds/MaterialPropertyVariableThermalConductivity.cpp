/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/MaterialPropertyVariableThermalConductivity.hpp"
#include "scaffolds/MaterialPropertyVariableThermalConductivity_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyVariableThermalConductivity::MaterialPropertyVariableThermalConductivity(const Model& model)
    : ModelObject(MaterialPropertyVariableThermalConductivity::iddObjectType(), model) {}

  MaterialPropertyVariableThermalConductivity::MaterialPropertyVariableThermalConductivity(
    std::shared_ptr<detail::MaterialPropertyVariableThermalConductivity_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyVariableThermalConductivity::iddObjectType() {
    return IddObjectType::MaterialProperty_VariableThermalConductivity;
  }

}  // namespace epmodel
}  // namespace openstudio
