/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboard_Impl.hpp"

#include "Model.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Heating_Water_Baseboard_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_Convective_Water_FieldEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

CoilHeatingWaterBaseboard::CoilHeatingWaterBaseboard(const Model& model)
  : StraightComponent(CoilHeatingWaterBaseboard::iddObjectType(), model, false, true) {}

CoilHeatingWaterBaseboard::CoilHeatingWaterBaseboard(std::shared_ptr<detail::CoilHeatingWaterBaseboard_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingWaterBaseboard::iddObjectType() {
  return IddObjectType::OS_Coil_Heating_Water_Baseboard;
}

std::vector<std::string> CoilHeatingWaterBaseboard::heatingDesignCapacityMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacityMethod);
}

std::string CoilHeatingWaterBaseboard::heatingDesignCapacityMethod() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->heatingDesignCapacityMethod();
}

bool CoilHeatingWaterBaseboard::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
}

boost::optional<double> CoilHeatingWaterBaseboard::heatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->heatingDesignCapacity();
}

bool CoilHeatingWaterBaseboard::isHeatingDesignCapacityAutosized() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->isHeatingDesignCapacityAutosized();
}

bool CoilHeatingWaterBaseboard::setHeatingDesignCapacity(double heatingDesignCapacity) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
}

void CoilHeatingWaterBaseboard::autosizeHeatingDesignCapacity() {
  getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->autosizeHeatingDesignCapacity();
}

boost::optional<double> CoilHeatingWaterBaseboard::autosizedHeatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->autosizedHeatingDesignCapacity();
}

double CoilHeatingWaterBaseboard::heatingDesignCapacityPerFloorArea() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->heatingDesignCapacityPerFloorArea();
}

bool CoilHeatingWaterBaseboard::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
}

double CoilHeatingWaterBaseboard::fractionofAutosizedHeatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->fractionofAutosizedHeatingDesignCapacity();
}

bool CoilHeatingWaterBaseboard::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
    fractionofAutosizedHeatingDesignCapacity);
}

boost::optional<double> CoilHeatingWaterBaseboard::uFactorTimesAreaValue() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->uFactorTimesAreaValue();
}

bool CoilHeatingWaterBaseboard::isUFactorTimesAreaValueDefaulted() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->isUFactorTimesAreaValueDefaulted();
}

bool CoilHeatingWaterBaseboard::isUFactorTimesAreaValueAutosized() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->isUFactorTimesAreaValueAutosized();
}

bool CoilHeatingWaterBaseboard::setUFactorTimesAreaValue(double uFactorTimesAreaValue) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setUFactorTimesAreaValue(uFactorTimesAreaValue);
}

void CoilHeatingWaterBaseboard::resetUFactorTimesAreaValue() {
  getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->resetUFactorTimesAreaValue();
}

void CoilHeatingWaterBaseboard::autosizeUFactorTimesAreaValue() {
  getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->autosizeUFactorTimesAreaValue();
}

boost::optional<double> CoilHeatingWaterBaseboard::autosizedUFactorTimesAreaValue() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->autosizedUFactorTimesAreaValue();
}

boost::optional<double> CoilHeatingWaterBaseboard::maximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->maximumWaterFlowRate();
}

bool CoilHeatingWaterBaseboard::isMaximumWaterFlowRateDefaulted() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->isMaximumWaterFlowRateDefaulted();
}

bool CoilHeatingWaterBaseboard::isMaximumWaterFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->isMaximumWaterFlowRateAutosized();
}

bool CoilHeatingWaterBaseboard::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
}

void CoilHeatingWaterBaseboard::resetMaximumWaterFlowRate() {
  getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->resetMaximumWaterFlowRate();
}

void CoilHeatingWaterBaseboard::autosizeMaximumWaterFlowRate() {
  getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->autosizeMaximumWaterFlowRate();
}

boost::optional<double> CoilHeatingWaterBaseboard::autosizedMaximumWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->autosizedMaximumWaterFlowRate();
}

double CoilHeatingWaterBaseboard::convergenceTolerance() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->convergenceTolerance();
}

bool CoilHeatingWaterBaseboard::isConvergenceToleranceDefaulted() const {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->isConvergenceToleranceDefaulted();
}

bool CoilHeatingWaterBaseboard::setConvergenceTolerance(double convergenceTolerance) {
  return getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->setConvergenceTolerance(convergenceTolerance);
}

void CoilHeatingWaterBaseboard::resetConvergenceTolerance() {
  getImpl<detail::CoilHeatingWaterBaseboard_Impl>()->resetConvergenceTolerance();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

// These helpers stay file-local because they only implement the plant-branch
// projection contract for the transient convective baseboard coil. They are
// not general loop utilities; they translate one canonical child-facing
// operation into the persisted parent row mutation that EnergyPlus actually
// stores.
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
// on a plant branch, then clear the parent's corresponding water node fields
// so the child no longer resolves as loop-connected.
bool removeTransientBaseboardParentFromPlantLoop(const CoilHeatingWaterBaseboard_Impl& coilImpl, ModelObject parentObject,
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

unsigned CoilHeatingWaterBaseboard_Impl::inletPort() const {
  return openstudio::OS_Coil_Heating_Water_BaseboardFields::WaterInletNodeName;
}

unsigned CoilHeatingWaterBaseboard_Impl::outletPort() const {
  return openstudio::OS_Coil_Heating_Water_BaseboardFields::WaterOutletNodeName;
}

boost::optional<ModelObject> CoilHeatingWaterBaseboard_Impl::inletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  if (auto node = resolvedNodeTarget(openstudio::OS_Coil_Heating_Water_BaseboardFields::WaterInletNodeName)) {
    return node->cast<ModelObject>();
  }
  return boost::none;
}

boost::optional<ModelObject> CoilHeatingWaterBaseboard_Impl::outletModelObject() const {
  if (auto p = parent()) {
    if (auto node = p->getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resolvedNodeTarget(
          openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  if (auto node = resolvedNodeTarget(openstudio::OS_Coil_Heating_Water_BaseboardFields::WaterOutletNodeName)) {
    return node->cast<ModelObject>();
  }
  return boost::none;
}

bool CoilHeatingWaterBaseboard_Impl::addToNode(Node& node) {
  auto p = parent();
  if (!p || plantLoop()) {
    return false;
  }

  return addTransientBaseboardParentToPlantNode(node, p->cast<ModelObject>(),
                                                openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName,
                                                openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName,
                                                "Heating Coil");
}

bool CoilHeatingWaterBaseboard_Impl::removeFromLoop() {
  if (auto p = parent()) {
    return removeTransientBaseboardParentFromPlantLoop(*this, p->cast<ModelObject>(),
                                                       openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName,
                                                       openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName);
  }
  return false;
}

void CoilHeatingWaterBaseboard_Impl::disconnect() {
  if (auto p = parent()) {
    p->setPointer(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName, Handle());
    p->setPointer(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName, Handle());
  }
}

std::string CoilHeatingWaterBaseboard_Impl::heatingDesignCapacityMethod() const {
  if (auto p = parent()) {
    return p->heatingDesignCapacityMethod();
  }
  auto value = getString(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacityMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterBaseboard_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  if (auto p = parent()) {
    return p->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }
  return setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
}

boost::optional<double> CoilHeatingWaterBaseboard_Impl::heatingDesignCapacity() const {
  if (auto p = parent()) {
    return p->heatingDesignCapacity();
  }
  return getDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacity, true);
}

bool CoilHeatingWaterBaseboard_Impl::isHeatingDesignCapacityAutosized() const {
  if (auto p = parent()) {
    return p->isHeatingDesignCapacityAutosized();
  }
  const auto value = getString(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacity, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool CoilHeatingWaterBaseboard_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
  if (auto p = parent()) {
    return p->setHeatingDesignCapacity(heatingDesignCapacity);
  }
  return setDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacity, heatingDesignCapacity);
}

void CoilHeatingWaterBaseboard_Impl::autosizeHeatingDesignCapacity() {
  if (auto p = parent()) {
    p->autosizeHeatingDesignCapacity();
    return;
  }
  OS_ASSERT(setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacity, "autosize"));
}

boost::optional<double> CoilHeatingWaterBaseboard_Impl::autosizedHeatingDesignCapacity() const {
  return boost::none;
}

double CoilHeatingWaterBaseboard_Impl::heatingDesignCapacityPerFloorArea() const {
  if (auto p = parent()) {
    return p->heatingDesignCapacityPerFloorArea();
  }
  auto value = getDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacityPerFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterBaseboard_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  if (auto p = parent()) {
    return p->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
  }
  return setDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::HeatingDesignCapacityPerFloorArea,
                   heatingDesignCapacityPerFloorArea);
}

double CoilHeatingWaterBaseboard_Impl::fractionofAutosizedHeatingDesignCapacity() const {
  if (auto p = parent()) {
    return p->fractionofAutosizedHeatingDesignCapacity();
  }
  auto value = getDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::FractionofAutosizedHeatingDesignCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterBaseboard_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  if (auto p = parent()) {
    return p->setFractionofAutosizedHeatingDesignCapacity(fractionofAutosizedHeatingDesignCapacity);
  }
  return setDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::FractionofAutosizedHeatingDesignCapacity,
                   fractionofAutosizedHeatingDesignCapacity);
}

boost::optional<double> CoilHeatingWaterBaseboard_Impl::uFactorTimesAreaValue() const {
  if (auto p = parent()) {
    return p->uFactorTimesAreaValue();
  }
  return getDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::UFactorTimesAreaValue, true);
}

bool CoilHeatingWaterBaseboard_Impl::isUFactorTimesAreaValueDefaulted() const {
  if (auto p = parent()) {
    return p->isUFactorTimesAreaValueDefaulted();
  }
  return isEmpty(openstudio::OS_Coil_Heating_Water_BaseboardFields::UFactorTimesAreaValue);
}

bool CoilHeatingWaterBaseboard_Impl::isUFactorTimesAreaValueAutosized() const {
  if (auto p = parent()) {
    return p->isUFactorTimesAreaValueAutosized();
  }
  const auto value = getString(openstudio::OS_Coil_Heating_Water_BaseboardFields::UFactorTimesAreaValue, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool CoilHeatingWaterBaseboard_Impl::setUFactorTimesAreaValue(double uFactorTimesAreaValue) {
  if (auto p = parent()) {
    return p->setUFactorTimesAreaValue(uFactorTimesAreaValue);
  }
  return setDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::UFactorTimesAreaValue, uFactorTimesAreaValue);
}

void CoilHeatingWaterBaseboard_Impl::resetUFactorTimesAreaValue() {
  if (auto p = parent()) {
    p->resetUFactorTimesAreaValue();
    return;
  }
  OS_ASSERT(setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::UFactorTimesAreaValue, ""));
}

void CoilHeatingWaterBaseboard_Impl::autosizeUFactorTimesAreaValue() {
  if (auto p = parent()) {
    p->autosizeUFactorTimesAreaValue();
    return;
  }
  OS_ASSERT(setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::UFactorTimesAreaValue, "autosize"));
}

boost::optional<double> CoilHeatingWaterBaseboard_Impl::autosizedUFactorTimesAreaValue() const {
  return boost::none;
}

boost::optional<double> CoilHeatingWaterBaseboard_Impl::maximumWaterFlowRate() const {
  if (auto p = parent()) {
    return p->maximumWaterFlowRate();
  }
  return getDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::MaximumWaterFlowRate, true);
}

bool CoilHeatingWaterBaseboard_Impl::isMaximumWaterFlowRateDefaulted() const {
  if (auto p = parent()) {
    return p->isMaximumWaterFlowRateDefaulted();
  }
  return isEmpty(openstudio::OS_Coil_Heating_Water_BaseboardFields::MaximumWaterFlowRate);
}

bool CoilHeatingWaterBaseboard_Impl::isMaximumWaterFlowRateAutosized() const {
  if (auto p = parent()) {
    return p->isMaximumWaterFlowRateAutosized();
  }
  const auto value = getString(openstudio::OS_Coil_Heating_Water_BaseboardFields::MaximumWaterFlowRate, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool CoilHeatingWaterBaseboard_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
  if (auto p = parent()) {
    return p->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }
  return setDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::MaximumWaterFlowRate, maximumWaterFlowRate);
}

void CoilHeatingWaterBaseboard_Impl::resetMaximumWaterFlowRate() {
  if (auto p = parent()) {
    p->resetMaximumWaterFlowRate();
    return;
  }
  OS_ASSERT(setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::MaximumWaterFlowRate, ""));
}

void CoilHeatingWaterBaseboard_Impl::autosizeMaximumWaterFlowRate() {
  if (auto p = parent()) {
    p->autosizeMaximumWaterFlowRate();
    return;
  }
  OS_ASSERT(setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::MaximumWaterFlowRate, "autosize"));
}

boost::optional<double> CoilHeatingWaterBaseboard_Impl::autosizedMaximumWaterFlowRate() const {
  return boost::none;
}

double CoilHeatingWaterBaseboard_Impl::convergenceTolerance() const {
  if (auto p = parent()) {
    return p->convergenceTolerance();
  }
  auto value = getDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::ConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterBaseboard_Impl::isConvergenceToleranceDefaulted() const {
  if (auto p = parent()) {
    return p->isConvergenceToleranceDefaulted();
  }
  return isEmpty(openstudio::OS_Coil_Heating_Water_BaseboardFields::ConvergenceTolerance);
}

bool CoilHeatingWaterBaseboard_Impl::setConvergenceTolerance(double convergenceTolerance) {
  if (auto p = parent()) {
    return p->setConvergenceTolerance(convergenceTolerance);
  }
  return setDouble(openstudio::OS_Coil_Heating_Water_BaseboardFields::ConvergenceTolerance, convergenceTolerance);
}

void CoilHeatingWaterBaseboard_Impl::resetConvergenceTolerance() {
  if (auto p = parent()) {
    p->resetConvergenceTolerance();
    return;
  }
  OS_ASSERT(setString(openstudio::OS_Coil_Heating_Water_BaseboardFields::ConvergenceTolerance, ""));
}

boost::optional<ZoneHVACBaseboardConvectiveWater> CoilHeatingWaterBaseboard_Impl::parent() const {
  // This is intentionally a reverse lookup by stable transient name. The
  // transient companion does not yet carry an explicit parent handle, so the
  // deterministic transient name is how we recover the owner without inventing
  // fake persisted relationship fields.
  const auto expectedName = getObject<CoilHeatingWaterBaseboard>().nameString();
  for (const auto& candidate : model().getConcreteModelObjects<ZoneHVACBaseboardConvectiveWater>()) {
    if (detail::transientHeatingCoilName(candidate) == expectedName) {
      return candidate;
    }
  }
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
