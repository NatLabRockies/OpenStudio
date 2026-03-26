/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "HVACComponent/Splitter.hpp"

#include <utilities/core/StringHelpers.hpp>

namespace openstudio {
namespace epmodel {

WaterToAirComponent::WaterToAirComponent(std::shared_ptr<detail::WaterToAirComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

WaterToAirComponent::WaterToAirComponent(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

unsigned WaterToAirComponent::airInletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airInletPort();
}

unsigned WaterToAirComponent::airOutletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airOutletPort();
}

boost::optional<ModelObject> WaterToAirComponent::airInletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airInletModelObject();
}

boost::optional<ModelObject> WaterToAirComponent::airOutletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airOutletModelObject();
}

unsigned WaterToAirComponent::waterInletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterInletPort();
}

unsigned WaterToAirComponent::waterOutletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterOutletPort();
}

boost::optional<ModelObject> WaterToAirComponent::waterInletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterInletModelObject();
}

boost::optional<ModelObject> WaterToAirComponent::waterOutletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterOutletModelObject();
}

boost::optional<AirLoopHVAC> WaterToAirComponent::airLoopHVAC() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airLoopHVAC();
}

boost::optional<PlantLoop> WaterToAirComponent::plantLoop() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->plantLoop();
}

bool WaterToAirComponent::addToNode(Node& node) {
  return getImpl<detail::WaterToAirComponent_Impl>()->addToNode(node);
}

bool WaterToAirComponent::addToSplitter(Splitter& splitter) {
  return getImpl<detail::WaterToAirComponent_Impl>()->addToSplitter(splitter);
}

std::vector<IdfObject> WaterToAirComponent::remove() {
  return getImpl<detail::WaterToAirComponent_Impl>()->remove();
}

void WaterToAirComponent::disconnectWaterSide() {
  getImpl<detail::WaterToAirComponent_Impl>()->disconnectWaterSide();
}

void WaterToAirComponent::disconnectAirSide() {
  getImpl<detail::WaterToAirComponent_Impl>()->disconnectAirSide();
}

bool WaterToAirComponent::removeFromAirLoopHVAC() {
  return getImpl<detail::WaterToAirComponent_Impl>()->removeFromAirLoopHVAC();
}

bool WaterToAirComponent::removeFromPlantLoop() {
  return getImpl<detail::WaterToAirComponent_Impl>()->removeFromPlantLoop();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool WaterToAirComponent_Impl::insertOnBranch(Node& node, const Branch& branch, unsigned inletPort, unsigned outletPort) {
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

boost::optional<ModelObject> WaterToAirComponent_Impl::airInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(airInletPort());
}

boost::optional<ModelObject> WaterToAirComponent_Impl::airOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(airOutletPort());
}

boost::optional<ModelObject> WaterToAirComponent_Impl::waterInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(waterInletPort());
}

boost::optional<ModelObject> WaterToAirComponent_Impl::waterOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(waterOutletPort());
}

bool WaterToAirComponent_Impl::addToNode(Node& node) {
  const auto nodeObject = node.cast<ModelObject>();
  if (airInletModelObject() == nodeObject || airOutletModelObject() == nodeObject || waterInletModelObject() == nodeObject
      || waterOutletModelObject() == nodeObject) {
    return false;
  }
  if (node.airLoopHVACOutdoorAirSystem()) {
    return false;
  }

  if (auto airLoop = node.airLoopHVAC()) {
    if (airLoop->demandComponent(node.handle())) {
      return false;
    }

    auto branchList = airLoop->getImpl<detail::AirLoopHVAC_Impl>()->branchList();
    auto branches = branchList.branches();
    if (branches.empty()) {
      return false;
    }

    removeFromAirLoopHVAC();
    if (!insertOnBranch(node, branches.front(), airInletPort(), airOutletPort())) {
      return false;
    }

    airLoop->getImpl<detail::AirLoopHVAC_Impl>()->syncSetpointManagerMixedAirFanNodes();
    return true;
  }

  auto plantLoop = node.plantLoop();
  if (!plantLoop) {
    return false;
  }

  if (!plantLoop->demandComponent(node.handle())) {
    return false;
  }

  auto branch = plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
  if (!branch) {
    return false;
  }

  removeFromPlantLoop();
  return insertOnBranch(node, *branch, waterInletPort(), waterOutletPort());
}

bool WaterToAirComponent_Impl::addToSplitter(Splitter&) {
  return false;
}

std::vector<IdfObject> WaterToAirComponent_Impl::remove() {
  if (!isRemovable()) {
    return {};
  }
  removeFromAirLoopHVAC();
  removeFromPlantLoop();
  return HVACComponent_Impl::remove();
}

void WaterToAirComponent_Impl::disconnectWaterSide() {
  setPointer(waterInletPort(), Handle(), false);
  setPointer(waterOutletPort(), Handle(), false);
}

void WaterToAirComponent_Impl::disconnectAirSide() {
  setPointer(airInletPort(), Handle(), false);
  setPointer(airOutletPort(), Handle(), false);
}

void WaterToAirComponent_Impl::disconnect() {
  disconnectWaterSide();
  disconnectAirSide();
}

bool WaterToAirComponent_Impl::removeFromAirLoopHVAC() {
  auto thisObject = getObject<ModelObject>();
  auto airLoop = thisObject.cast<WaterToAirComponent>().airLoopHVAC();
  if (!airLoop || !airLoop->supplyComponent(handle())) {
    return false;
  }

  auto inletObject = airInletModelObject();
  auto outletObject = airOutletModelObject();
  if (!inletObject || !outletObject) {
    return false;
  }

  auto inletNode = inletObject->optionalCast<Node>();
  auto outletNode = outletObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return false;
  }

  auto branchList = airLoop->getImpl<detail::AirLoopHVAC_Impl>()->branchList();
  auto branches = branchList.branches();
  if (branches.empty()) {
    return false;
  }

  auto branch = branches.front();
  auto components = branch.components();
  for (unsigned i = 0; i < components.size(); ++i) {
    if (components[i] != thisObject) {
      continue;
    }
    if (i + 1u < components.size()) {
      if (!branch.getImpl<detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
        return false;
      }
    }
    if (!branch.getImpl<detail::Branch_Impl>()->removeComponent(i)) {
      return false;
    }
    airLoop->getImpl<detail::AirLoopHVAC_Impl>()->syncSetpointManagerMixedAirFanNodes();
    return true;
  }

  return false;
}

bool WaterToAirComponent_Impl::removeFromPlantLoop() {
  auto thisObject = getObject<ModelObject>();
  auto plantLoop = thisObject.cast<WaterToAirComponent>().plantLoop();
  if (!plantLoop) {
    return false;
  }

  auto inletObject = waterInletModelObject();
  auto outletObject = waterOutletModelObject();
  if (!inletObject || !outletObject) {
    return false;
  }

  auto inletNode = inletObject->optionalCast<Node>();
  auto outletNode = outletObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return false;
  }

  auto branch = plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(*inletNode);
  if (!branch) {
    branch = plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(*outletNode);
  }
  if (!branch) {
    return false;
  }

  auto components = branch->components();
  for (unsigned i = 0; i < components.size(); ++i) {
    if (components[i] != thisObject) {
      continue;
    }
    if (i + 1u < components.size()) {
      if (!branch->getImpl<detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
        return false;
      }
    }
    return branch->getImpl<detail::Branch_Impl>()->removeComponent(i);
  }

  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
