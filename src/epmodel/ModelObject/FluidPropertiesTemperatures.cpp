/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FluidPropertiesTemperatures.hpp"
#include "FluidPropertiesTemperatures_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FluidPropertiesTemperatures::FluidPropertiesTemperatures(const Model& model)
  : ModelObject(FluidPropertiesTemperatures::iddObjectType(), model) {}

FluidPropertiesTemperatures::FluidPropertiesTemperatures(std::shared_ptr<detail::FluidPropertiesTemperatures_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FluidPropertiesTemperatures::iddObjectType() {
  return IddObjectType::FluidProperties_Temperatures;
}

}  // namespace epmodel
}  // namespace openstudio
