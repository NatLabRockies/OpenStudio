/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelPartitionMaterial/InfraredTransparentMaterial.hpp"
#include "ModelPartitionMaterial/InfraredTransparentMaterial_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  InfraredTransparentMaterial::InfraredTransparentMaterial(const Model& model) : ModelObject(InfraredTransparentMaterial::iddObjectType(), model) {}

  InfraredTransparentMaterial::InfraredTransparentMaterial(std::shared_ptr<detail::InfraredTransparentMaterial_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType InfraredTransparentMaterial::iddObjectType() {
    return IddObjectType::Material_InfraredTransparent;
  }

}  // namespace epmodel
}  // namespace openstudio
