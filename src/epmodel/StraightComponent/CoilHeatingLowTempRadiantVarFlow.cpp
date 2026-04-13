/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow_Impl.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantVarFlowDesign.hpp"
#include "ModelObject/ZoneHVACLowTempRadiantVarFlowDesign_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Heating_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingLowTempRadiantVarFlow::CoilHeatingLowTempRadiantVarFlow(const Model& model)
  : StraightComponent(CoilHeatingLowTempRadiantVarFlow::iddObjectType(), model, false, true) {}

CoilHeatingLowTempRadiantVarFlow::CoilHeatingLowTempRadiantVarFlow(std::shared_ptr<detail::CoilHeatingLowTempRadiantVarFlow_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingLowTempRadiantVarFlow::iddObjectType() {
  return IddObjectType::OS_Coil_Heating_LowTemperatureRadiant_VariableFlow;
}

std::vector<std::string> CoilHeatingLowTempRadiantVarFlow::heatingDesignCapacityMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                        ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod);
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow::maximumHotWaterFlow() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->maximumHotWaterFlow();
}

bool CoilHeatingLowTempRadiantVarFlow::isMaximumHotWaterFlowDefaulted() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->isMaximumHotWaterFlowDefaulted();
}

bool CoilHeatingLowTempRadiantVarFlow::isMaximumHotWaterFlowAutosized() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->isMaximumHotWaterFlowAutosized();
}

bool CoilHeatingLowTempRadiantVarFlow::setMaximumHotWaterFlow(double maximumHotWaterFlow) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setMaximumHotWaterFlow(maximumHotWaterFlow);
}

void CoilHeatingLowTempRadiantVarFlow::resetMaximumHotWaterFlow() {
  getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->resetMaximumHotWaterFlow();
}

void CoilHeatingLowTempRadiantVarFlow::autosizeMaximumHotWaterFlow() {
  getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->autosizeMaximumHotWaterFlow();
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow::autosizedMaximumHotWaterFlow() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->autosizedMaximumHotWaterFlow();
}

double CoilHeatingLowTempRadiantVarFlow::heatingControlThrottlingRange() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->heatingControlThrottlingRange();
}

bool CoilHeatingLowTempRadiantVarFlow::isHeatingControlThrottlingRangeDefaulted() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->isHeatingControlThrottlingRangeDefaulted();
}

bool CoilHeatingLowTempRadiantVarFlow::setHeatingControlThrottlingRange(double heatingControlThrottlingRange) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setHeatingControlThrottlingRange(heatingControlThrottlingRange);
}

void CoilHeatingLowTempRadiantVarFlow::resetHeatingControlThrottlingRange() {
  getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->resetHeatingControlThrottlingRange();
}

boost::optional<Schedule> CoilHeatingLowTempRadiantVarFlow::heatingControlTemperatureSchedule() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->heatingControlTemperatureSchedule();
}

bool CoilHeatingLowTempRadiantVarFlow::setHeatingControlTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setHeatingControlTemperatureSchedule(schedule);
}

void CoilHeatingLowTempRadiantVarFlow::resetHeatingControlTemperatureSchedule() {
  getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->resetHeatingControlTemperatureSchedule();
}

std::string CoilHeatingLowTempRadiantVarFlow::heatingDesignCapacityMethod() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->heatingDesignCapacityMethod();
}

bool CoilHeatingLowTempRadiantVarFlow::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow::heatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->heatingDesignCapacity();
}

bool CoilHeatingLowTempRadiantVarFlow::isHeatingDesignCapacityAutosized() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->isHeatingDesignCapacityAutosized();
}

bool CoilHeatingLowTempRadiantVarFlow::setHeatingDesignCapacity(double heatingDesignCapacity) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
}

void CoilHeatingLowTempRadiantVarFlow::autosizeHeatingDesignCapacity() {
  getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->autosizeHeatingDesignCapacity();
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow::autosizedHeatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->autosizedHeatingDesignCapacity();
}

double CoilHeatingLowTempRadiantVarFlow::heatingDesignCapacityPerFloorArea() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->heatingDesignCapacityPerFloorArea();
}

bool CoilHeatingLowTempRadiantVarFlow::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
}

double CoilHeatingLowTempRadiantVarFlow::fractionofAutosizedHeatingDesignCapacity() const {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->fractionofAutosizedHeatingDesignCapacity();
}

bool CoilHeatingLowTempRadiantVarFlow::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return getImpl<detail::CoilHeatingLowTempRadiantVarFlow_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
    fractionofAutosizedHeatingDesignCapacity);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool addTransientRadiantParentToPlantNode(Node& node, ModelObject parentObject, unsigned inletField, unsigned outletField, const std::string& roleLabel) {
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
  const auto setParentNodes = [&](const Node& inletNode, const Node& outletNode) {
    return parentObject.setPointer(inletField, inletNode.handle()) && parentObject.setPointer(outletField, outletNode.handle());
  };

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
    return setParentNodes(inletNode, outletNode);
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
    if (!setParentNodes(newInletNode, newOutletNode)) {
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

bool removeTransientRadiantParentFromPlantLoop(const CoilHeatingLowTempRadiantVarFlow_Impl& coilImpl, ModelObject parentObject, unsigned inletField,
                                               unsigned outletField) {
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

unsigned CoilHeatingLowTempRadiantVarFlow_Impl::inletPort() const {
  return openstudio::OS_Coil_Heating_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName;
}

unsigned CoilHeatingLowTempRadiantVarFlow_Impl::outletPort() const {
  return openstudio::OS_Coil_Heating_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName;
}

boost::optional<ModelObject> CoilHeatingLowTempRadiantVarFlow_Impl::inletModelObject() const {
  if (auto p = parent()) {
    if (auto node =
          p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resolvedNodeTarget(
            openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

boost::optional<ModelObject> CoilHeatingLowTempRadiantVarFlow_Impl::outletModelObject() const {
  if (auto p = parent()) {
    if (auto node =
          p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resolvedNodeTarget(
            openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName)) {
      return node->cast<ModelObject>();
    }
  }
  return boost::none;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::addToNode(Node& node) {
  auto p = parent();
  if (!p || plantLoop()) {
    return false;
  }

  return addTransientRadiantParentToPlantNode(node, p->cast<ModelObject>(),
                                              openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName,
                                              openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName,
                                              "Heating Coil");
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::removeFromLoop() {
  if (auto p = parent()) {
    return removeTransientRadiantParentFromPlantLoop(*this, p->cast<ModelObject>(),
                                                     openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName,
                                                     openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName);
  }
  return false;
}

void CoilHeatingLowTempRadiantVarFlow_Impl::disconnect() {
  if (auto p = parent()) {
    p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterInletNodeName, Handle());
    p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingWaterOutletNodeName, Handle());
  }
}

boost::optional<ZoneHVACLowTempRadiantVarFlow> CoilHeatingLowTempRadiantVarFlow_Impl::parent() const {
  const auto thisName = getObject<openstudio::epmodel::CoilHeatingLowTempRadiantVarFlow>().name();
  if (!thisName) {
    return boost::none;
  }

  // This is intentionally a name-based reverse lookup for now. These transient
  // companion coils are not persisted EnergyPlus objects, and today they do not
  // carry an explicit parent handle. The stable transient name gives us a way
  // to recover the owning radiant parent without inventing fake persisted
  // relationship fields. It works, but it is also a sign that a future
  // transient-ownership mechanism could be cleaner than reverse name matching.
  for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow>()) {
    if (openstudio::istringEqual(*thisName, detail::transientHeatingCoilName(candidate))) {
      return candidate;
    }
  }
  return boost::none;
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow_Impl::maximumHotWaterFlow() const {
  if (auto p = parent()) {
    return p->maximumHotWaterFlow();
  }
  return boost::none;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::isMaximumHotWaterFlowDefaulted() const {
  if (auto p = parent()) {
    return !p->maximumHotWaterFlow() && !p->isMaximumHotWaterFlowAutosized();
  }
  return true;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::isMaximumHotWaterFlowAutosized() const {
  if (auto p = parent()) {
    return p->isMaximumHotWaterFlowAutosized();
  }
  return false;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setMaximumHotWaterFlow(double maximumHotWaterFlow) {
  if (auto p = parent()) {
    return p->setMaximumHotWaterFlow(maximumHotWaterFlow);
  }
  return false;
}

void CoilHeatingLowTempRadiantVarFlow_Impl::resetMaximumHotWaterFlow() {
  if (auto p = parent()) {
    OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, ""));
  }
}

void CoilHeatingLowTempRadiantVarFlow_Impl::autosizeMaximumHotWaterFlow() {
  if (auto p = parent()) {
    p->autosizeMaximumHotWaterFlow();
  }
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow_Impl::autosizedMaximumHotWaterFlow() const {
  // This transient child is a view over parent-owned radiant storage. The
  // parent can query autosized values for its own persisted fields, but we do
  // not yet have a clean public path to expose those SQL-backed results
  // through this transient child surface.
  return boost::none;
}

double CoilHeatingLowTempRadiantVarFlow_Impl::heatingControlThrottlingRange() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingControlThrottlingRange();
    }
  }
  return 0.5;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::isHeatingControlThrottlingRangeDefaulted() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isHeatingControlThrottlingRangeDefaulted();
    }
  }
  return true;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setHeatingControlThrottlingRange(double heatingControlThrottlingRange) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingControlThrottlingRange(heatingControlThrottlingRange);
  }
  return false;
}

void CoilHeatingLowTempRadiantVarFlow_Impl::resetHeatingControlThrottlingRange() {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHeatingControlThrottlingRange();
  }
}

boost::optional<Schedule> CoilHeatingLowTempRadiantVarFlow_Impl::heatingControlTemperatureSchedule() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
      return design->heatingControlTemperatureSchedule();
    }
  }
  return boost::none;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setHeatingControlTemperatureSchedule(Schedule& schedule) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingControlTemperatureSchedule(schedule);
  }
  return false;
}

void CoilHeatingLowTempRadiantVarFlow_Impl::resetHeatingControlTemperatureSchedule() {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetHeatingControlTemperatureSchedule();
  }
}

std::string CoilHeatingLowTempRadiantVarFlow_Impl::heatingDesignCapacityMethod() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->heatingDesignCapacityMethod();
    }
  }
  return "HeatingDesignCapacity";
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }
  return false;
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow_Impl::heatingDesignCapacity() const {
  if (auto p = parent()) {
    return p->heatingDesignCapacity();
  }
  return boost::none;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::isHeatingDesignCapacityAutosized() const {
  if (auto p = parent()) {
    return p->isHeatingDesignCapacityAutosized();
  }
  return false;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
  if (auto p = parent()) {
    return p->setHeatingDesignCapacity(heatingDesignCapacity);
  }
  return false;
}

void CoilHeatingLowTempRadiantVarFlow_Impl::autosizeHeatingDesignCapacity() {
  if (auto p = parent()) {
    p->autosizeHeatingDesignCapacity();
  }
}

boost::optional<double> CoilHeatingLowTempRadiantVarFlow_Impl::autosizedHeatingDesignCapacity() const {
  // This transient child is a view over parent-owned radiant storage. The
  // parent can query autosized values for its own persisted fields, but we do
  // not yet have a clean public path to expose those SQL-backed results
  // through this transient child surface.
  return boost::none;
}

double CoilHeatingLowTempRadiantVarFlow_Impl::heatingDesignCapacityPerFloorArea() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
      if (const auto value = design->heatingDesignCapacityPerFloorArea()) {
        return *value;
      }
    }
  }
  OS_ASSERT(false);
  return 0.0;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setHeatingDesignCapacityPerFloorArea(
      heatingDesignCapacityPerFloorArea);
  }
  return false;
}

double CoilHeatingLowTempRadiantVarFlow_Impl::fractionofAutosizedHeatingDesignCapacity() const {
  if (auto p = parent()) {
    if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
      return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->fractionofAutosizedHeatingDesignCapacity();
    }
  }
  return 1.0;
}

bool CoilHeatingLowTempRadiantVarFlow_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  if (auto p = parent()) {
    auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
    return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }
  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
