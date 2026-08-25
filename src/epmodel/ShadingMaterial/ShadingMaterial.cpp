/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingMaterial/ShadingMaterial.hpp"
#include "ShadingMaterial/ShadingMaterial_Impl.hpp"

namespace openstudio {
namespace epmodel {

  ShadingMaterial::ShadingMaterial(IddObjectType type, const Model& model) : FenestrationMaterial(type, model) {}

  ShadingMaterial::ShadingMaterial(std::shared_ptr<detail::ShadingMaterial_Impl> impl) : FenestrationMaterial(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
