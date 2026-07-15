/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"

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
#include <utilities/idd/OS_Coil_Cooling_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilCoolingLowTempRadiantVarFlow::CoilCoolingLowTempRadiantVarFlow(const Model& model)
    : StraightComponent(CoilCoolingLowTempRadiantVarFlow::iddObjectType(), model, false, true) {}

  CoilCoolingLowTempRadiantVarFlow::CoilCoolingLowTempRadiantVarFlow(std::shared_ptr<detail::CoilCoolingLowTempRadiantVarFlow_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingLowTempRadiantVarFlow::iddObjectType() {
    return IddObjectType::OS_Coil_Cooling_LowTemperatureRadiant_VariableFlow;
  }

  std::vector<std::string> CoilCoolingLowTempRadiantVarFlow::coolingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod);
  }

  std::vector<std::string> CoilCoolingLowTempRadiantVarFlow::condensationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType);
  }

  boost::optional<double> CoilCoolingLowTempRadiantVarFlow::maximumColdWaterFlow() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->maximumColdWaterFlow();
  }

  bool CoilCoolingLowTempRadiantVarFlow::isMaximumColdWaterFlowDefaulted() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->isMaximumColdWaterFlowDefaulted();
  }

  bool CoilCoolingLowTempRadiantVarFlow::isMaximumColdWaterFlowAutosized() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->isMaximumColdWaterFlowAutosized();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setMaximumColdWaterFlow(double maximumColdWaterFlow) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setMaximumColdWaterFlow(maximumColdWaterFlow);
  }

  void CoilCoolingLowTempRadiantVarFlow::resetMaximumColdWaterFlow() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->resetMaximumColdWaterFlow();
  }

  void CoilCoolingLowTempRadiantVarFlow::autosizeMaximumColdWaterFlow() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->autosizeMaximumColdWaterFlow();
  }

  boost::optional<double> CoilCoolingLowTempRadiantVarFlow::autosizedMaximumColdWaterFlow() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->autosizedMaximumColdWaterFlow();
  }

  double CoilCoolingLowTempRadiantVarFlow::coolingControlThrottlingRange() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->coolingControlThrottlingRange();
  }

  bool CoilCoolingLowTempRadiantVarFlow::isCoolingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->isCoolingControlThrottlingRangeDefaulted();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
  }

  void CoilCoolingLowTempRadiantVarFlow::resetCoolingControlThrottlingRange() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->resetCoolingControlThrottlingRange();
  }

  boost::optional<Schedule> CoilCoolingLowTempRadiantVarFlow::coolingControlTemperatureSchedule() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->coolingControlTemperatureSchedule();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCoolingControlTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCoolingControlTemperatureSchedule(schedule);
  }

  void CoilCoolingLowTempRadiantVarFlow::resetCoolingControlTemperatureSchedule() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->resetCoolingControlTemperatureSchedule();
  }

  std::string CoilCoolingLowTempRadiantVarFlow::condensationControlType() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->condensationControlType();
  }

  bool CoilCoolingLowTempRadiantVarFlow::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->isCondensationControlTypeDefaulted();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCondensationControlType(const std::string& condensationControlType) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCondensationControlType(condensationControlType);
  }

  void CoilCoolingLowTempRadiantVarFlow::resetCondensationControlType() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->resetCondensationControlType();
  }

  double CoilCoolingLowTempRadiantVarFlow::condensationControlDewpointOffset() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->condensationControlDewpointOffset();
  }

  bool CoilCoolingLowTempRadiantVarFlow::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCondensationControlDewpointOffset(condensationControlDewpointOffset);
  }

  void CoilCoolingLowTempRadiantVarFlow::resetCondensationControlDewpointOffset() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->resetCondensationControlDewpointOffset();
  }

  std::string CoilCoolingLowTempRadiantVarFlow::coolingDesignCapacityMethod() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->coolingDesignCapacityMethod();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
  }

  boost::optional<double> CoilCoolingLowTempRadiantVarFlow::coolingDesignCapacity() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->coolingDesignCapacity();
  }

  bool CoilCoolingLowTempRadiantVarFlow::isCoolingDesignCapacityAutosized() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->isCoolingDesignCapacityAutosized();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCoolingDesignCapacity(double coolingDesignCapacity) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
  }

  void CoilCoolingLowTempRadiantVarFlow::autosizeCoolingDesignCapacity() {
    getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->autosizeCoolingDesignCapacity();
  }

  boost::optional<double> CoilCoolingLowTempRadiantVarFlow::autosizedCoolingDesignCapacity() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->autosizedCoolingDesignCapacity();
  }

  double CoilCoolingLowTempRadiantVarFlow::coolingDesignCapacityPerFloorArea() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->coolingDesignCapacityPerFloorArea();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacityPerFloorArea(coolingDesignCapacityPerFloorArea);
  }

  double CoilCoolingLowTempRadiantVarFlow::fractionofAutosizedCoolingDesignCapacity() const {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->fractionofAutosizedCoolingDesignCapacity();
  }

  bool CoilCoolingLowTempRadiantVarFlow::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
    return getImpl<detail::CoilCoolingLowTempRadiantVarFlow_Impl>()->setFractionofAutosizedCoolingDesignCapacity(
      fractionofAutosizedCoolingDesignCapacity);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool addTransientRadiantParentToPlantNode(Node& node, ModelObject parentObject, unsigned inletField, unsigned outletField,
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

      bool removeTransientRadiantParentFromPlantLoop(const CoilCoolingLowTempRadiantVarFlow_Impl& coilImpl, ModelObject parentObject,
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

    unsigned CoilCoolingLowTempRadiantVarFlow_Impl::inletPort() const {
      return openstudio::OS_Coil_Cooling_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName;
    }

    unsigned CoilCoolingLowTempRadiantVarFlow_Impl::outletPort() const {
      return openstudio::OS_Coil_Cooling_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName;
    }

    boost::optional<ModelObject> CoilCoolingLowTempRadiantVarFlow_Impl::inletModelObject() const {
      if (auto p = parent()) {
        if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resolvedNodeTarget(
              openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName)) {
          return node->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    boost::optional<ModelObject> CoilCoolingLowTempRadiantVarFlow_Impl::outletModelObject() const {
      if (auto p = parent()) {
        if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resolvedNodeTarget(
              openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName)) {
          return node->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::addToNode(Node& node) {
      auto p = parent();
      if (!p || plantLoop()) {
        return false;
      }

      return addTransientRadiantParentToPlantNode(
        node, p->cast<ModelObject>(), openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName,
        openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, "Cooling Coil");
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::removeFromLoop() {
      if (auto p = parent()) {
        return removeTransientRadiantParentFromPlantLoop(*this, p->cast<ModelObject>(),
                                                         openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName,
                                                         openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::disconnect() {
      if (auto p = parent()) {
        p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterInletNodeName, Handle());
        p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingWaterOutletNodeName, Handle());
      }
    }

    boost::optional<ZoneHVACLowTempRadiantVarFlow> CoilCoolingLowTempRadiantVarFlow_Impl::parent() const {
      const auto thisName = getObject<openstudio::epmodel::CoilCoolingLowTempRadiantVarFlow>().name();
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
        if (openstudio::istringEqual(*thisName, detail::transientCoolingCoilName(candidate))) {
          return candidate;
        }
      }
      return boost::none;
    }

    boost::optional<double> CoilCoolingLowTempRadiantVarFlow_Impl::maximumColdWaterFlow() const {
      if (auto p = parent()) {
        return p->maximumColdWaterFlow();
      }
      return boost::none;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::isMaximumColdWaterFlowDefaulted() const {
      if (auto p = parent()) {
        return !p->maximumColdWaterFlow() && !p->isMaximumColdWaterFlowAutosized();
      }
      return true;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::isMaximumColdWaterFlowAutosized() const {
      if (auto p = parent()) {
        return p->isMaximumColdWaterFlowAutosized();
      }
      return false;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setMaximumColdWaterFlow(double maximumColdWaterFlow) {
      if (auto p = parent()) {
        return p->setMaximumColdWaterFlow(maximumColdWaterFlow);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::resetMaximumColdWaterFlow() {
      if (auto p = parent()) {
        OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, ""));
      }
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::autosizeMaximumColdWaterFlow() {
      if (auto p = parent()) {
        p->autosizeMaximumColdWaterFlow();
      }
    }

    boost::optional<double> CoilCoolingLowTempRadiantVarFlow_Impl::autosizedMaximumColdWaterFlow() const {
      // This transient child is a view over parent-owned radiant storage. The
      // parent can query autosized values for its own persisted fields, but we do
      // not yet have a clean public path to expose those SQL-backed results
      // through this transient child surface.
      return boost::none;
    }

    double CoilCoolingLowTempRadiantVarFlow_Impl::coolingControlThrottlingRange() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingControlThrottlingRange();
        }
      }
      return 0.5;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::isCoolingControlThrottlingRangeDefaulted() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCoolingControlThrottlingRangeDefaulted();
        }
      }
      return true;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::resetCoolingControlThrottlingRange() {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCoolingControlThrottlingRange();
      }
    }

    boost::optional<Schedule> CoilCoolingLowTempRadiantVarFlow_Impl::coolingControlTemperatureSchedule() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->coolingControlTemperatureSchedule();
        }
      }
      return boost::none;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCoolingControlTemperatureSchedule(Schedule& schedule) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingControlTemperatureSchedule(schedule);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::resetCoolingControlTemperatureSchedule() {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCoolingControlTemperatureSchedule();
      }
    }

    std::string CoilCoolingLowTempRadiantVarFlow_Impl::condensationControlType() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->condensationControlType();
        }
      }
      return "SimpleOff";
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::isCondensationControlTypeDefaulted() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCondensationControlTypeDefaulted();
        }
      }
      return true;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCondensationControlType(const std::string& condensationControlType) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCondensationControlType(condensationControlType);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::resetCondensationControlType() {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCondensationControlType();
      }
    }

    double CoilCoolingLowTempRadiantVarFlow_Impl::condensationControlDewpointOffset() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->condensationControlDewpointOffset();
        }
      }
      return 1.0;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->isCondensationControlDewpointOffsetDefaulted();
        }
      }
      return true;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCondensationControlDewpointOffset(
          condensationControlDewpointOffset);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::resetCondensationControlDewpointOffset() {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->resetCondensationControlDewpointOffset();
      }
    }

    std::string CoilCoolingLowTempRadiantVarFlow_Impl::coolingDesignCapacityMethod() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          return design->getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->coolingDesignCapacityMethod();
        }
      }
      return "CoolingDesignCapacity";
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
      }
      return false;
    }

    boost::optional<double> CoilCoolingLowTempRadiantVarFlow_Impl::coolingDesignCapacity() const {
      if (auto p = parent()) {
        return p->coolingDesignCapacity();
      }
      return boost::none;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::isCoolingDesignCapacityAutosized() const {
      if (auto p = parent()) {
        return p->isCoolingDesignCapacityAutosized();
      }
      return false;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
      if (auto p = parent()) {
        return p->setCoolingDesignCapacity(coolingDesignCapacity);
      }
      return false;
    }

    void CoilCoolingLowTempRadiantVarFlow_Impl::autosizeCoolingDesignCapacity() {
      if (auto p = parent()) {
        p->autosizeCoolingDesignCapacity();
      }
    }

    boost::optional<double> CoilCoolingLowTempRadiantVarFlow_Impl::autosizedCoolingDesignCapacity() const {
      // This transient child is a view over parent-owned radiant storage. The
      // parent can query autosized values for its own persisted fields, but we do
      // not yet have a clean public path to expose those SQL-backed results
      // through this transient child surface.
      return boost::none;
    }

    double CoilCoolingLowTempRadiantVarFlow_Impl::coolingDesignCapacityPerFloorArea() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          if (const auto value = design->coolingDesignCapacityPerFloorArea()) {
            return *value;
          }
        }
      }
      OS_ASSERT(false);
      return 0.0;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setCoolingDesignCapacityPerFloorArea(
          coolingDesignCapacityPerFloorArea);
      }
      return false;
    }

    double CoilCoolingLowTempRadiantVarFlow_Impl::fractionofAutosizedCoolingDesignCapacity() const {
      if (auto p = parent()) {
        if (const auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->designObject()) {
          if (const auto value = design->fractionofAutosizedCoolingDesignCapacity()) {
            return *value;
          }
        }
      }
      OS_ASSERT(false);
      return 0.0;
    }

    bool CoilCoolingLowTempRadiantVarFlow_Impl::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
      if (auto p = parent()) {
        auto design = p->getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->ensureDesignObject();
        return design.getImpl<detail::ZoneHVACLowTempRadiantVarFlowDesign_Impl>()->setFractionofAutosizedCoolingDesignCapacity(
          fractionofAutosizedCoolingDesignCapacity);
      }
      return false;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
