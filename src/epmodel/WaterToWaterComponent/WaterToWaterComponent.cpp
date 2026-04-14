/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/WaterToWaterComponent.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include "ModelObject/Branch_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <algorithm>
#include <limits>

#include <utilities/core/StringHelpers.hpp>

namespace openstudio {
namespace epmodel {

WaterToWaterComponent::WaterToWaterComponent(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

WaterToWaterComponent::WaterToWaterComponent(std::shared_ptr<detail::WaterToWaterComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

unsigned WaterToWaterComponent::supplyInletPort() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->supplyInletPort();
}

unsigned WaterToWaterComponent::supplyOutletPort() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->supplyOutletPort();
}

boost::optional<ModelObject> WaterToWaterComponent::supplyInletModelObject() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->supplyInletModelObject();
}

boost::optional<ModelObject> WaterToWaterComponent::supplyOutletModelObject() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->supplyOutletModelObject();
}

unsigned WaterToWaterComponent::demandInletPort() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->demandInletPort();
}

unsigned WaterToWaterComponent::demandOutletPort() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->demandOutletPort();
}

boost::optional<ModelObject> WaterToWaterComponent::demandInletModelObject() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->demandInletModelObject();
}

boost::optional<ModelObject> WaterToWaterComponent::demandOutletModelObject() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->demandOutletModelObject();
}

boost::optional<PlantLoop> WaterToWaterComponent::plantLoop() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->plantLoop();
}

boost::optional<PlantLoop> WaterToWaterComponent::secondaryPlantLoop() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->secondaryPlantLoop();
}

bool WaterToWaterComponent::removeFromPlantLoop() {
  return getImpl<detail::WaterToWaterComponent_Impl>()->removeFromPlantLoop();
}

bool WaterToWaterComponent::removeFromSecondaryPlantLoop() {
  return getImpl<detail::WaterToWaterComponent_Impl>()->removeFromSecondaryPlantLoop();
}

unsigned WaterToWaterComponent::tertiaryInletPort() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->tertiaryInletPort();
}

unsigned WaterToWaterComponent::tertiaryOutletPort() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->tertiaryOutletPort();
}

boost::optional<ModelObject> WaterToWaterComponent::tertiaryInletModelObject() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->tertiaryInletModelObject();
}

boost::optional<ModelObject> WaterToWaterComponent::tertiaryOutletModelObject() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->tertiaryOutletModelObject();
}

boost::optional<PlantLoop> WaterToWaterComponent::tertiaryPlantLoop() const {
  return getImpl<detail::WaterToWaterComponent_Impl>()->tertiaryPlantLoop();
}

bool WaterToWaterComponent::removeFromTertiaryPlantLoop() {
  return getImpl<detail::WaterToWaterComponent_Impl>()->removeFromTertiaryPlantLoop();
}

bool WaterToWaterComponent::addToTertiaryNode(Node& node) {
  return getImpl<detail::WaterToWaterComponent_Impl>()->addToTertiaryNode(node);
}

namespace detail {

boost::optional<ModelObject> WaterToWaterComponent_Impl::supplyInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(supplyInletPort());
}

boost::optional<ModelObject> WaterToWaterComponent_Impl::supplyOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(supplyOutletPort());
}

boost::optional<ModelObject> WaterToWaterComponent_Impl::demandInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(demandInletPort());
}

boost::optional<ModelObject> WaterToWaterComponent_Impl::demandOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(demandOutletPort());
}

// Water-to-water equipment uses the same branch representation as straight
// components. The difference is only which pair of ports is active on the
// current loop interface, so the insertion logic lives here at the base class.
bool WaterToWaterComponent_Impl::insertOnBranch(Node& node, const Branch& branch, unsigned inletPort, unsigned outletPort) {
  const auto nodeName = node.name();
  if (!nodeName) {
    return false;
  }

  auto thisObject = getObject<ModelObject>();
  if (!thisObject.name()) {
    thisObject.createName();
    if (!thisObject.name()) {
      return false;
    }
  }

  const auto thisName = thisObject.nameString();
  auto components = branch.components();
  if (components.empty()) {
    const std::string newInletName = *nodeName;
    const std::string newOutletName = *nodeName + " - " + thisName + " Outlet";

    if (!branch.getImpl<detail::Branch_Impl>()->appendComponent(thisObject, newInletName, newOutletName)) {
      return false;
    }

    auto newInletNode = model().getOrCreateTransientByName<Node>(newInletName);
    auto newOutletNode = model().getOrCreateTransientByName<Node>(newOutletName);
    setPointer(inletPort, newInletNode.handle(), false);
    setPointer(outletPort, newOutletNode.handle(), false);
    return true;
  }

  for (std::size_t i = 0; i < components.size(); ++i) {
    auto inletNode = branch.componentInletNode(static_cast<unsigned>(i));
    auto outletNode = branch.componentOutletNode(static_cast<unsigned>(i));

    const bool matchesInlet = inletNode && openstudio::istringEqual(inletNode->nameString(), *nodeName);
    const bool matchesOutlet = outletNode && openstudio::istringEqual(outletNode->nameString(), *nodeName);
    if (!matchesInlet && !matchesOutlet) {
      continue;
    }

    const std::string newNodeName = *nodeName + " - " + thisName + " Outlet";
    const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1u);

    std::string newInletName;
    std::string newOutletName;
    if (matchesOutlet && (i + 1u == components.size())) {
      newInletName = newNodeName;
      newOutletName = *nodeName;
    } else {
      newInletName = *nodeName;
      newOutletName = newNodeName;
    }

    if (!branch.getImpl<detail::Branch_Impl>()->insertComponent(insertIndex, thisObject, newInletName, newOutletName)) {
      return false;
    }

    auto newInletNode = model().getOrCreateTransientByName<Node>(newInletName);
    auto newOutletNode = model().getOrCreateTransientByName<Node>(newOutletName);
    setPointer(inletPort, newInletNode.handle(), false);
    setPointer(outletPort, newOutletNode.handle(), false);

    auto newNode = model().getOrCreateTransientByName<Node>(newNodeName);
    if (matchesInlet) {
      return branch.getImpl<detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode);
    }
    return branch.getImpl<detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode);
  }

  return false;
}

bool WaterToWaterComponent_Impl::addToNode(Node& node) {
  auto plantLoop_ = node.plantLoop();
  if (!plantLoop_) {
    return false;
  }

  auto branch = plantLoop_->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
  if (!branch) {
    return false;
  }

  if (plantLoop_->supplyComponent(node.handle())) {
    removeFromPlantLoop();
    return insertOnBranch(node, *branch, supplyInletPort(), supplyOutletPort());
  }

  if (plantLoop_->demandComponent(node.handle())) {
    removeFromSecondaryPlantLoop();
    return insertOnBranch(node, *branch, demandInletPort(), demandOutletPort());
  }

  return false;
}

std::vector<IdfObject> WaterToWaterComponent_Impl::remove() {
  removeFromPlantLoop();
  removeFromSecondaryPlantLoop();
  removeFromTertiaryPlantLoop();
  return HVACComponent_Impl::remove();
}

void WaterToWaterComponent_Impl::disconnect() {
  setPointer(supplyInletPort(), Handle(), false);
  setPointer(supplyOutletPort(), Handle(), false);
  setPointer(demandInletPort(), Handle(), false);
  setPointer(demandOutletPort(), Handle(), false);

  const auto tertiaryInlet = tertiaryInletPort();
  const auto tertiaryOutlet = tertiaryOutletPort();
  if (tertiaryInlet != std::numeric_limits<unsigned>::max()) {
    setPointer(tertiaryInlet, Handle(), false);
  }
  if (tertiaryOutlet != std::numeric_limits<unsigned>::max()) {
    setPointer(tertiaryOutlet, Handle(), false);
  }
}

boost::optional<PlantLoop> WaterToWaterComponent_Impl::plantLoop() const {
  auto tertiaryLoop = tertiaryPlantLoop();
  const auto plantLoops = model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>();
  for (const auto& plantLoop_ : plantLoops) {
    if (tertiaryLoop && (tertiaryLoop->handle() == plantLoop_.handle())) {
      continue;
    }
    const auto supplyComponents = plantLoop_.supplyComponents(openstudio::IddObjectType::Catchall);
    if (std::ranges::find_if(supplyComponents, [&](const auto& component) { return component.handle() == handle(); }) != supplyComponents.end()) {
      return plantLoop_;
    }
  }
  return boost::none;
}

boost::optional<PlantLoop> WaterToWaterComponent_Impl::secondaryPlantLoop() const {
  auto tertiaryLoop = tertiaryPlantLoop();
  const auto plantLoops = model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>();
  for (const auto& plantLoop_ : plantLoops) {
    if (tertiaryLoop && (tertiaryLoop->handle() == plantLoop_.handle())) {
      continue;
    }
    const auto demandComponents = plantLoop_.demandComponents(openstudio::IddObjectType::Catchall);
    if (std::ranges::find_if(demandComponents, [&](const auto& component) { return component.handle() == handle(); }) != demandComponents.end()) {
      return plantLoop_;
    }
  }
  return boost::none;
}

bool WaterToWaterComponent_Impl::removeFromBranch(unsigned inletPort, unsigned outletPort, const boost::optional<PlantLoop>& plantLoop_) {
  if (!plantLoop_) {
    return false;
  }

  auto inletNode = getObject<ModelObject>().getModelObjectTarget<Node>(inletPort);
  auto outletNode = getObject<ModelObject>().getModelObjectTarget<Node>(outletPort);
  if (!inletNode || !outletNode) {
    return false;
  }

  auto branch = plantLoop_->getImpl<detail::PlantLoop_Impl>()->branchForNode(*inletNode);
  if (!branch) {
    branch = plantLoop_->getImpl<detail::PlantLoop_Impl>()->branchForNode(*outletNode);
  }
  if (!branch) {
    return false;
  }

  auto components = branch->components();
  auto thisObject = getObject<ModelObject>();
  for (unsigned i = 0; i < components.size(); ++i) {
    if (components[i] != thisObject) {
      continue;
    }
    if (i + 1u < components.size()) {
      if (!branch->getImpl<detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
        return false;
      }
    }
    if (!branch->getImpl<detail::Branch_Impl>()->removeComponent(i)) {
      return false;
    }
    setPointer(inletPort, Handle(), false);
    setPointer(outletPort, Handle(), false);
    return true;
  }

  return false;
}

bool WaterToWaterComponent_Impl::removeFromPlantLoop() {
  return removeFromBranch(supplyInletPort(), supplyOutletPort(), plantLoop());
}

bool WaterToWaterComponent_Impl::removeFromSecondaryPlantLoop() {
  return removeFromBranch(demandInletPort(), demandOutletPort(), secondaryPlantLoop());
}

unsigned WaterToWaterComponent_Impl::tertiaryInletPort() const {
  return std::numeric_limits<unsigned>::max();
}

unsigned WaterToWaterComponent_Impl::tertiaryOutletPort() const {
  return std::numeric_limits<unsigned>::max();
}

boost::optional<ModelObject> WaterToWaterComponent_Impl::tertiaryInletModelObject() const {
  const auto port = tertiaryInletPort();
  if (port == std::numeric_limits<unsigned>::max()) {
    return boost::none;
  }
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(port);
}

boost::optional<ModelObject> WaterToWaterComponent_Impl::tertiaryOutletModelObject() const {
  const auto port = tertiaryOutletPort();
  if (port == std::numeric_limits<unsigned>::max()) {
    return boost::none;
  }
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(port);
}

boost::optional<PlantLoop> WaterToWaterComponent_Impl::tertiaryPlantLoop() const {
  auto inletModelObject = tertiaryInletModelObject();
  auto outletModelObject = tertiaryOutletModelObject();
  if (!inletModelObject || !outletModelObject) {
    return boost::none;
  }

  auto inletNode = inletModelObject->optionalCast<Node>();
  auto outletNode = outletModelObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return boost::none;
  }

  auto inletLoop = inletNode->plantLoop();
  auto outletLoop = outletNode->plantLoop();
  if (inletLoop && outletLoop && (inletLoop->handle() == outletLoop->handle())) {
    return inletLoop;
  }
  return boost::none;
}

bool WaterToWaterComponent_Impl::shouldRouteDemandSideNodeToTertiary(const Node& node) const {
  const auto inletPort = tertiaryInletPort();
  const auto outletPort = tertiaryOutletPort();
  if ((inletPort == std::numeric_limits<unsigned>::max()) || (outletPort == std::numeric_limits<unsigned>::max())) {
    return false;
  }

  auto plantLoop_ = node.plantLoop();
  if (!plantLoop_ || !plantLoop_->demandComponent(node.handle())) {
    return false;
  }

  auto demandLoop = secondaryPlantLoop();
  if (!demandLoop || (plantLoop_->handle() == demandLoop->handle())) {
    return false;
  }

  return !tertiaryPlantLoop();
}

bool WaterToWaterComponent_Impl::removeFromTertiaryPlantLoop() {
  const auto inletPort = tertiaryInletPort();
  const auto outletPort = tertiaryOutletPort();
  if ((inletPort == std::numeric_limits<unsigned>::max()) || (outletPort == std::numeric_limits<unsigned>::max())) {
    return false;
  }
  return removeFromBranch(inletPort, outletPort, tertiaryPlantLoop());
}

bool WaterToWaterComponent_Impl::addToTertiaryNode(Node& node) {
  const auto inletPort = tertiaryInletPort();
  const auto outletPort = tertiaryOutletPort();
  if ((inletPort == std::numeric_limits<unsigned>::max()) || (outletPort == std::numeric_limits<unsigned>::max())) {
    return false;
  }

  const auto nodeObject = node.cast<ModelObject>();
  const auto tertiaryInletObject = tertiaryInletModelObject();
  const auto tertiaryOutletObject = tertiaryOutletModelObject();
  if ((tertiaryInletObject && (*tertiaryInletObject == nodeObject)) || (tertiaryOutletObject && (*tertiaryOutletObject == nodeObject))) {
    return false;
  }

  auto plantLoop_ = node.plantLoop();
  if (!plantLoop_) {
    return false;
  }

  auto branch = plantLoop_->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
  if (!branch) {
    return false;
  }

  removeFromTertiaryPlantLoop();
  return insertOnBranch(node, *branch, inletPort, outletPort);
}

bool WaterToWaterComponent_Impl::addToDemandSideTertiaryNode(Node& node) {
  auto plantLoop_ = node.plantLoop();
  if (!plantLoop_ || !plantLoop_->demandComponent(node.handle())) {
    return false;
  }
  return WaterToWaterComponent_Impl::addToTertiaryNode(node);
}

}  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
