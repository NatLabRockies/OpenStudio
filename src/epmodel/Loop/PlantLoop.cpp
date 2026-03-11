/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"

#include "Model.hpp"

namespace openstudio {
namespace epmodel {

PlantLoop::PlantLoop(const Model& model) : Loop(PlantLoop::iddObjectType(), model) {}

PlantLoop::PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl) : Loop(std::move(impl)) {}

IddObjectType PlantLoop::iddObjectType() {
  return IddObjectType::PlantLoop;
}

}  // namespace epmodel
}  // namespace openstudio
