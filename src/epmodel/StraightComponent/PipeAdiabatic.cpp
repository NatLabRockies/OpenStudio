/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PipeAdiabatic.hpp"
#include "StraightComponent/PipeAdiabatic_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Node.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Pipe_Adiabatic_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

PipeAdiabatic::PipeAdiabatic(const Model& model) : StraightComponent(PipeAdiabatic::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::PipeAdiabatic_Impl>());
}

PipeAdiabatic::PipeAdiabatic(std::shared_ptr<detail::PipeAdiabatic_Impl> impl) : StraightComponent(std::move(impl)) {}

unsigned PipeAdiabatic::inletPort() const {
  return getImpl<detail::PipeAdiabatic_Impl>()->inletPort();
}

unsigned PipeAdiabatic::outletPort() const {
  return getImpl<detail::PipeAdiabatic_Impl>()->outletPort();
}

IddObjectType PipeAdiabatic::iddObjectType() {
  return IddObjectType::Pipe_Adiabatic;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned PipeAdiabatic_Impl::inletPort() const {
  // Relationship mapping only: Pipe:Adiabatic Inlet Node Name
  return openstudio::Pipe_AdiabaticFields::InletNodeName;
}

unsigned PipeAdiabatic_Impl::outletPort() const {
  // Relationship mapping only: Pipe:Adiabatic Outlet Node Name
  return openstudio::Pipe_AdiabaticFields::OutletNodeName;
}

bool PipeAdiabatic_Impl::addToNode(Node& node) {
  for (const auto& plant : model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>()) {
    if (plant.component(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
  }

  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
