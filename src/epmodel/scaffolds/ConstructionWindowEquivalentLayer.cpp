/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionWindowEquivalentLayer.hpp"
#include "ConstructionWindowEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ConstructionWindowEquivalentLayer::ConstructionWindowEquivalentLayer(const Model& model)
  : ModelObject(ConstructionWindowEquivalentLayer::iddObjectType(), model) {}

ConstructionWindowEquivalentLayer::ConstructionWindowEquivalentLayer(std::shared_ptr<detail::ConstructionWindowEquivalentLayer_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ConstructionWindowEquivalentLayer::iddObjectType() {
  return IddObjectType::Construction_WindowEquivalentLayer;
}

}  // namespace epmodel
}  // namespace openstudio
