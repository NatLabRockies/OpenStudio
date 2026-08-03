/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GasLayer/GasLayer.hpp"
#include "GasLayer/GasLayer_Impl.hpp"

namespace openstudio {
namespace epmodel {

  GasLayer::GasLayer(IddObjectType type, const Model& model) : FenestrationMaterial(type, model) {}

  GasLayer::GasLayer(std::shared_ptr<detail::GasLayer_Impl> impl) : FenestrationMaterial(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
