/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant_Impl.hpp"

#include "Model.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Heating_Water_Baseboard_Radiant_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Water_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingWaterBaseboardRadiant::CoilHeatingWaterBaseboardRadiant(const Model& model)
  : StraightComponent(CoilHeatingWaterBaseboardRadiant::iddObjectType(), model, false, true) {}

CoilHeatingWaterBaseboardRadiant::CoilHeatingWaterBaseboardRadiant(std::shared_ptr<detail::CoilHeatingWaterBaseboardRadiant_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingWaterBaseboardRadiant::iddObjectType() {
  return IddObjectType::OS_Coil_Heating_Water_Baseboard_Radiant;
}

std::vector<std::string> CoilHeatingWaterBaseboardRadiant::heatingDesignCapacityMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_Coil_Heating_Water_Baseboard_RadiantFields::HeatingDesignCapacityMethod);
}

double CoilHeatingWaterBaseboardRadiant::ratedAverageWaterTemperature() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->ratedAverageWaterTemperature();
}

bool CoilHeatingWaterBaseboardRadiant::setRatedAverageWaterTemperature(double ratedAverageWaterTemperature) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setRatedAverageWaterTemperature(ratedAverageWaterTemperature);
}

double CoilHeatingWaterBaseboardRadiant::ratedWaterMassFlowRate() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->ratedWaterMassFlowRate();
}

bool CoilHeatingWaterBaseboardRadiant::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
}

std::string CoilHeatingWaterBaseboardRadiant::heatingDesignCapacityMethod() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->heatingDesignCapacityMethod();
}

bool CoilHeatingWaterBaseboardRadiant::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant::heatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->heatingDesignCapacity();
}

bool CoilHeatingWaterBaseboardRadiant::isHeatingDesignCapacityAutosized() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->isHeatingDesignCapacityAutosized();
}

bool CoilHeatingWaterBaseboardRadiant::setHeatingDesignCapacity(double heatingDesignCapacity) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
}

void CoilHeatingWaterBaseboardRadiant::autosizeHeatingDesignCapacity() {
  getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->autosizeHeatingDesignCapacity();
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant::autosizedHeatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->autosizedHeatingDesignCapacity();
}

double CoilHeatingWaterBaseboardRadiant::heatingDesignCapacityPerFloorArea() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->heatingDesignCapacityPerFloorArea();
}

bool CoilHeatingWaterBaseboardRadiant::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
}

double CoilHeatingWaterBaseboardRadiant::fractionofAutosizedHeatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->fractionofAutosizedHeatingDesignCapacity();
}

bool CoilHeatingWaterBaseboardRadiant::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
    fractionofAutosizedHeatingDesignCapacity);
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant::maximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->maximumWaterFlowRate();
}

bool CoilHeatingWaterBaseboardRadiant::isMaximumWaterFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->isMaximumWaterFlowRateAutosized();
}

bool CoilHeatingWaterBaseboardRadiant::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
}

void CoilHeatingWaterBaseboardRadiant::autosizeMaximumWaterFlowRate() {
  getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->autosizeMaximumWaterFlowRate();
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant::autosizedMaximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->autosizedMaximumWaterFlowRate();
}

double CoilHeatingWaterBaseboardRadiant::convergenceTolerance() const {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->convergenceTolerance();
}

bool CoilHeatingWaterBaseboardRadiant::setConvergenceTolerance(double convergenceTolerance) {
  return getImpl<detail::CoilHeatingWaterBaseboardRadiant_Impl>()->setConvergenceTolerance(convergenceTolerance);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

// These helpers stay file-local because they only implement the plant-branch
// projection contract for the transient radiant baseboard coil. They are not a
// general loop utility; they translate one canonical child-facing operation
// into the persisted parent row mutation that EnergyPlus actually stores.

constexpr double kDefaultRatedAverageWaterTemperature = 87.78;
constexpr double kDefaultRatedWaterMassFlowRate = 0.063;
constexpr double kDefaultHeatingDesignCapacityPerFloorArea = 0.0;
constexpr double kDefaultFractionOfAutosizedHeatingDesignCapacity = 1.0;
constexpr double kDefaultConvergenceTolerance = 0.001;

// Insert the persisted parent baseboard object on the branch row that the
// canonical transient coil conceptually owns, then align the parent's water
// node fields with the inserted branch row so later traversal can project back
// to the child.
bool addTransientBaseboardParentToPlantNode(Node& node, ModelObject parentObject, unsigned inletField, unsigned outletField,
                                            const std::string& roleLabel) {
  auto plantLoop = node.plantLoop();
  if (!plantLoop) {
    return false;
  }

  auto plantLoopImpl = plantLoop->getImpl<detail::PlantLoop_Impl>();
  auto branch = plantLoopImpl->branchForNode(node);
  if (!branch) {
    return false;
  }

  const auto nodeName = node.name();
  if (!nodeName) {
    return false;
  }

  if (!parentObject.name()) {
    parentObject.createName();
    if (!parentObject.name()) {
      return false;
    }
  }

  const auto parentName = parentObject.nameString();
  const auto roleObjectName = parentName + " " + roleLabel;

  auto components = branch->components();
  if (components.empty()) {
    std::string newInletName;
    std::string newOutletName;
    const bool isOutletAnchor = ((*branch == plantLoopImpl->supplyOutletBranch()) && (node == plantLoop->supplyOutletNode()))
                                || ((*branch == plantLoopImpl->demandOutletBranch()) && (node == plantLoop->demandOutletNode()));
    if (isOutletAnchor) {
      newInletName = *nodeName + " - " + roleObjectName + " Inlet";
      newOutletName = *nodeName;
    } else {
      newInletName = *nodeName;
      newOutletName = *nodeName + " - " + roleObjectName + " Outlet";
    }

    if (!branch->getImpl<detail::Branch_Impl>()->appendComponent(parentObject, newInletName, newOutletName)) {
      return false;
    }

    auto inletNode = node.model().getOrCreateTransientByName<Node>(newInletName);
    auto outletNode = node.model().getOrCreateTransientByName<Node>(newOutletName);
    return parentObject.setPointer(inletField, inletNode.handle()) && parentObject.setPointer(outletField, outletNode.handle());
  }

  for (unsigned i = 0; i < components.size(); ++i) {
    const auto inletNode = branch->componentInletNode(i);
    const auto outletNode = branch->componentOutletNode(i);
    const bool matchesInlet = inletNode && (*inletNode == node);
    const bool matchesOutlet = outletNode && (*outletNode == node);
    if (!matchesInlet && !matchesOutlet) {
      continue;
    }

    const std::string newNodeName = *nodeName + " - " + roleObjectName + " Outlet";
    const unsigned insertIndex = matchesInlet ? i : static_cast<unsigned>(i + 1u);

    std::string newInletName;
    std::string newOutletName;
    if (matchesOutlet && (i + 1u == components.size())) {
      newInletName = newNodeName;
      newOutletName = *nodeName;
    } else {
      newInletName = *nodeName;
      newOutletName = newNodeName;
    }

    if (!branch->getImpl<detail::Branch_Impl>()->insertComponent(insertIndex, parentObject, newInletName, newOutletName)) {
      return false;
    }

    auto newInletNode = node.model().getOrCreateTransientByName<Node>(newInletName);
    auto newOutletNode = node.model().getOrCreateTransientByName<Node>(newOutletName);
    if (!(parentObject.setPointer(inletField, newInletNode.handle()) && parentObject.setPointer(outletField, newOutletNode.handle()))) {
      return false;
    }

    auto newNode = node.model().getOrCreateTransientByName<Node>(newNodeName);
    if (matchesInlet) {
      return branch->getImpl<detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode);
    }
    return branch->getImpl<detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode);
  }

  return false;
}

// Remove the persisted parent row that currently represents the transient coil
// on a plant branch, then clear the parent's corresponding water node fields so
// the child no longer resolves as loop-connected.
bool removeTransientBaseboardParentFromPlantLoop(const CoilHeatingWaterBaseboardRadiant_Impl& coilImpl, ModelObject parentObject,
                                                 unsigned inletField, unsigned outletField) {
  auto inletNode = coilImpl.inletModelObject() ? coilImpl.inletModelObject()->optionalCast<Node>() : boost::none;
  auto outletNode = coilImpl.outletModelObject() ? coilImpl.outletModelObject()->optionalCast<Node>() : boost::none;
  if (!inletNode || !outletNode) {
    return false;
  }

  auto plantLoop = coilImpl.getObject<openstudio::epmodel::HVACComponent>().plantLoop();
  if (!plantLoop) {
    return false;
  }

  auto plantLoopImpl = plantLoop->getImpl<detail::PlantLoop_Impl>();
  auto branch = plantLoopImpl->branchForNode(*inletNode);
  if (!branch) {
    branch = plantLoopImpl->branchForNode(*outletNode);
  }
  if (!branch) {
    return false;
  }

  auto components = branch->components();
  for (unsigned i = 0; i < components.size(); ++i) {
    if (components[i] != parentObject) {
      continue;
    }

    const auto branchInletNode = branch->componentInletNode(i);
    const auto branchOutletNode = branch->componentOutletNode(i);
    if (!(branchInletNode && branchOutletNode && (*branchInletNode == *inletNode) && (*branchOutletNode == *outletNode))) {
      continue;
    }

    if ((i + 1u < components.size()) && !branch->getImpl<detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
      return false;
    }
    if (!branch->getImpl<detail::Branch_Impl>()->removeComponent(i)) {
      return false;
    }

    return parentObject.setPointer(inletField, Handle()) && parentObject.setPointer(outletField, Handle());
  }

  return false;
}

}  // namespace

unsigned CoilHeatingWaterBaseboardRadiant_Impl::inletPort() const {
  return openstudio::OS_Coil_Heating_Water_Baseboard_RadiantFields::InletNodeName;
}

unsigned CoilHeatingWaterBaseboardRadiant_Impl::outletPort() const {
  return openstudio::OS_Coil_Heating_Water_Baseboard_RadiantFields::OutletNodeName;
}

boost::optional<ModelObject> CoilHeatingWaterBaseboardRadiant_Impl::inletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

boost::optional<ModelObject> CoilHeatingWaterBaseboardRadiant_Impl::outletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::addToNode(Node& node) {
  auto p = parent();
  if (!p || plantLoop()) {
    return false;
  }

  // The canonical OpenStudio surface lets the transient heating coil behave
  // like plant equipment. EnergyPlus persists the parent baseboard object on
  // the branch instead, so this inserts the parent row and then wires the
  // parent's water-side nodes to match the branch row that conceptually
  // belongs to this transient child.
  return addTransientBaseboardParentToPlantNode(node, p->cast<ModelObject>(),
                                                openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName,
                                                openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName,
                                                "Heating Coil");
}

bool CoilHeatingWaterBaseboardRadiant_Impl::removeFromLoop() {
  if (auto p = parent()) {
    return removeTransientBaseboardParentFromPlantLoop(*this, p->cast<ModelObject>(),
                                                       openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName,
                                                       openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName);
  }
  return false;
}

void CoilHeatingWaterBaseboardRadiant_Impl::disconnect() {
  if (auto p = parent()) {
    p->setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName, Handle());
    p->setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName, Handle());
  }
}

double CoilHeatingWaterBaseboardRadiant_Impl::ratedAverageWaterTemperature() const {
  if (auto p = parent()) {
    if (auto value = p->ratedAverageWaterTemperature()) {
      return *value;
    }
  }
  return kDefaultRatedAverageWaterTemperature;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setRatedAverageWaterTemperature(double ratedAverageWaterTemperature) {
  if (auto p = parent()) {
    return p->setRatedAverageWaterTemperature(ratedAverageWaterTemperature);
  }
  return false;
}

double CoilHeatingWaterBaseboardRadiant_Impl::ratedWaterMassFlowRate() const {
  if (auto p = parent()) {
    if (auto value = p->ratedWaterMassFlowRate()) {
      return *value;
    }
  }
  return kDefaultRatedWaterMassFlowRate;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
  if (auto p = parent()) {
    return p->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
  }
  return false;
}

std::string CoilHeatingWaterBaseboardRadiant_Impl::heatingDesignCapacityMethod() const {
  if (auto p = parent()) {
    if (auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->designObject()) {
      return design->heatingDesignCapacityMethod();
    }
  }
  return "HeatingDesignCapacity";
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ensureDesignObject();
    return design.setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }
  return false;
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant_Impl::heatingDesignCapacity() const {
  if (auto p = parent()) {
    return p->heatingDesignCapacity();
  }
  return boost::none;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::isHeatingDesignCapacityAutosized() const {
  if (auto p = parent()) {
    return p->isHeatingDesignCapacityAutosized();
  }
  return false;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
  if (auto p = parent()) {
    return p->setHeatingDesignCapacity(heatingDesignCapacity);
  }
  return false;
}

void CoilHeatingWaterBaseboardRadiant_Impl::autosizeHeatingDesignCapacity() {
  if (auto p = parent()) {
    p->autosizeHeatingDesignCapacity();
  }
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant_Impl::autosizedHeatingDesignCapacity() const {
  return boost::none;
}

double CoilHeatingWaterBaseboardRadiant_Impl::heatingDesignCapacityPerFloorArea() const {
  if (auto p = parent()) {
    if (auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->designObject()) {
      if (auto value = design->heatingDesignCapacityPerFloorArea()) {
        return *value;
      }
    }
  }
  return kDefaultHeatingDesignCapacityPerFloorArea;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ensureDesignObject();
    return design.setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
  }
  return false;
}

double CoilHeatingWaterBaseboardRadiant_Impl::fractionofAutosizedHeatingDesignCapacity() const {
  if (auto p = parent()) {
    if (auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->designObject()) {
      return design->fractionofAutosizedHeatingDesignCapacity();
    }
  }
  return kDefaultFractionOfAutosizedHeatingDesignCapacity;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ensureDesignObject();
    return design.setFractionofAutosizedHeatingDesignCapacity(fractionofAutosizedHeatingDesignCapacity);
  }
  return false;
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant_Impl::maximumWaterFlowRate() const {
  if (auto p = parent()) {
    return p->maximumWaterFlowRate();
  }
  return boost::none;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::isMaximumWaterFlowRateAutosized() const {
  if (auto p = parent()) {
    return p->isMaximumWaterFlowRateAutosized();
  }
  return false;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
  if (auto p = parent()) {
    return p->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }
  return false;
}

void CoilHeatingWaterBaseboardRadiant_Impl::autosizeMaximumWaterFlowRate() {
  if (auto p = parent()) {
    p->autosizeMaximumWaterFlowRate();
  }
}

boost::optional<double> CoilHeatingWaterBaseboardRadiant_Impl::autosizedMaximumWaterFlowRate() const {
  return boost::none;
}

double CoilHeatingWaterBaseboardRadiant_Impl::convergenceTolerance() const {
  if (auto p = parent()) {
    if (auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->designObject()) {
      return design->convergenceTolerance();
    }
  }
  return kDefaultConvergenceTolerance;
}

bool CoilHeatingWaterBaseboardRadiant_Impl::setConvergenceTolerance(double convergenceTolerance) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ensureDesignObject();
    return design.setConvergenceTolerance(convergenceTolerance);
  }
  return false;
}

boost::optional<ZoneHVACBaseboardRadiantConvectiveWater> CoilHeatingWaterBaseboardRadiant_Impl::parent() const {
  const auto thisName = getObject<openstudio::epmodel::CoilHeatingWaterBaseboardRadiant>().name();
  if (!thisName) {
    return boost::none;
  }

  // This is intentionally a name-based reverse lookup for now. These transient
  // companion coils are not persisted EnergyPlus objects, and today they do not
  // carry an explicit parent handle. The stable transient name gives us a way
  // to recover the owning baseboard parent without inventing fake persisted
  // relationship fields. It works, but it is also a sign that a future
  // transient-ownership mechanism could be cleaner than reverse name matching.
  for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACBaseboardRadiantConvectiveWater>()) {
    if (openstudio::istringEqual(*thisName, detail::transientHeatingCoilName(candidate))) {
      return candidate;
    }
  }
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
