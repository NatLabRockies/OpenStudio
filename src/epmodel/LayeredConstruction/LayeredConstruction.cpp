/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LayeredConstruction/LayeredConstruction.hpp"
#include "LayeredConstruction/LayeredConstruction_Impl.hpp"

namespace openstudio {
namespace epmodel {

  LayeredConstruction::LayeredConstruction(IddObjectType type, const Model& model) : ConstructionBase(type, model) {}

  LayeredConstruction::LayeredConstruction(std::shared_ptr<detail::LayeredConstruction_Impl> impl) : ConstructionBase(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
