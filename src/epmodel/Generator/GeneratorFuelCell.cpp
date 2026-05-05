/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCell.hpp"
#include "GeneratorFuelCell_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCell::GeneratorFuelCell(const Model& model) : ModelObject(GeneratorFuelCell::iddObjectType(), model) {}

  GeneratorFuelCell::GeneratorFuelCell(std::shared_ptr<detail::GeneratorFuelCell_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCell::iddObjectType() {
    return IddObjectType::Generator_FuelCell;
  }

}  // namespace epmodel
}  // namespace openstudio
