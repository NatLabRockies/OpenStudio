/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent.hpp"
#include "HVACComponent_Impl.hpp"
#include "Model.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Splitter.hpp"
#include "StraightComponent/StraightComponent.hpp"

namespace openstudio {
namespace epmodel {

HVACComponent::HVACComponent(IddObjectType type, const Model& model, bool fastName, bool isTransient)
  : ParentObject(type, model, fastName, isTransient) {}

HVACComponent::HVACComponent(std::shared_ptr<detail::HVACComponent_Impl> impl) : ParentObject(std::move(impl)) {}

boost::optional<Loop> HVACComponent::loop() const {
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    return impl->loop();
  }
  return boost::none;
}

boost::optional<AirLoopHVAC> HVACComponent::airLoopHVAC() const {
  if (auto nodeImpl = getImpl<detail::Node_Impl>()) {
    return nodeImpl->airLoopHVAC();
  }
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    return impl->airLoopHVAC();
  }
  return boost::none;
}

boost::optional<HVACComponent> HVACComponent::containingHVACComponent() const {
  return boost::none;
}

// TODO: Implement containingStraightComponent once containment tracking is ready.
// boost::optional<StraightComponent> HVACComponent::containingStraightComponent() const {
//   return boost::none;
// }

bool HVACComponent::addToNode(Node& node) {
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    return impl->addToNode(node);
  }
  return false;
}

bool HVACComponent::addToSplitter(Splitter& splitter) {
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    return impl->addToSplitter(splitter);
  }
  return false;
}

void HVACComponent::disconnect() {
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    impl->disconnect();
  }
}

bool HVACComponent::isRemovable() const {
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    return impl->isRemovable();
  }
  return false;
}

std::vector<IdfObject> HVACComponent::remove() {
  if (auto impl = getImpl<detail::HVACComponent_Impl>()) {
    return impl->remove();
  }
  return {};
}

namespace detail {

boost::optional<Loop> HVACComponent_Impl::loop() const {
  // Mirror model behavior: check AirLoopHVAC first, then other loop types (PlantLoop not yet implemented).
  if (auto airLoop = airLoopHVAC()) {
    return airLoop->optionalCast<openstudio::epmodel::Loop>();
  }
  return boost::none;
}

boost::optional<AirLoopHVAC> HVACComponent_Impl::airLoopHVAC() const {
  // Resolve ownership through AirLoopHVAC traversal APIs so topology logic
  // remains centralized in supply/demand components implementations.
  const auto airLoops = model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>();
  for (const auto& airLoop : airLoops) {
    const auto components = airLoop.components(openstudio::IddObjectType::Catchall);
    for (const auto& component : components) {
      if (component.handle() == handle()) {
        return airLoop;
      }
    }
  }
  return boost::none;
}

bool HVACComponent_Impl::addToNode(Node& /*node*/) {
  return false;
}

bool HVACComponent_Impl::addToSplitter(Splitter& /*splitter*/) {
  return false;
}

void HVACComponent_Impl::disconnect() {}

bool HVACComponent_Impl::isRemovable() const {
  return true;
}

std::vector<IdfObject> HVACComponent_Impl::remove() {
  if (!isRemovable()) {
    return {};
  }
  disconnect();
  return ParentObject_Impl::remove();
}

}  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
