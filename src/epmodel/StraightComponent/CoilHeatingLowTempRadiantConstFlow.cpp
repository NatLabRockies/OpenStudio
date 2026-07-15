/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"

#include "Model.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Heating_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilHeatingLowTempRadiantConstFlow::CoilHeatingLowTempRadiantConstFlow(const Model& model)
    : StraightComponent(CoilHeatingLowTempRadiantConstFlow::iddObjectType(), model, false, true) {}

  CoilHeatingLowTempRadiantConstFlow::CoilHeatingLowTempRadiantConstFlow(std::shared_ptr<detail::CoilHeatingLowTempRadiantConstFlow_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingLowTempRadiantConstFlow::iddObjectType() {
    return IddObjectType::OS_Coil_Heating_LowTemperatureRadiant_ConstantFlow;
  }

  boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingHighWaterTemperatureSchedule() const {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingHighWaterTemperatureSchedule();
  }

  boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingLowWaterTemperatureSchedule() const {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingLowWaterTemperatureSchedule();
  }

  boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingHighControlTemperatureSchedule() const {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingHighControlTemperatureSchedule();
  }

  boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow::heatingLowControlTemperatureSchedule() const {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->heatingLowControlTemperatureSchedule();
  }

  bool CoilHeatingLowTempRadiantConstFlow::setHeatingHighWaterTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingHighWaterTemperatureSchedule(schedule);
  }

  void CoilHeatingLowTempRadiantConstFlow::resetHeatingHighWaterTemperatureSchedule() {
    getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingHighWaterTemperatureSchedule();
  }

  bool CoilHeatingLowTempRadiantConstFlow::setHeatingLowWaterTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingLowWaterTemperatureSchedule(schedule);
  }

  void CoilHeatingLowTempRadiantConstFlow::resetHeatingLowWaterTemperatureSchedule() {
    getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingLowWaterTemperatureSchedule();
  }

  bool CoilHeatingLowTempRadiantConstFlow::setHeatingHighControlTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingHighControlTemperatureSchedule(schedule);
  }

  void CoilHeatingLowTempRadiantConstFlow::resetHeatingHighControlTemperatureSchedule() {
    getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingHighControlTemperatureSchedule();
  }

  bool CoilHeatingLowTempRadiantConstFlow::setHeatingLowControlTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->setHeatingLowControlTemperatureSchedule(schedule);
  }

  void CoilHeatingLowTempRadiantConstFlow::resetHeatingLowControlTemperatureSchedule() {
    getImpl<detail::CoilHeatingLowTempRadiantConstFlow_Impl>()->resetHeatingLowControlTemperatureSchedule();
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

      bool removeTransientRadiantParentFromPlantLoop(const CoilHeatingLowTempRadiantConstFlow_Impl& coilImpl, ModelObject parentObject,
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

    unsigned CoilHeatingLowTempRadiantConstFlow_Impl::inletPort() const {
      return openstudio::OS_Coil_Heating_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName;
    }

    unsigned CoilHeatingLowTempRadiantConstFlow_Impl::outletPort() const {
      return openstudio::OS_Coil_Heating_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName;
    }

    boost::optional<ModelObject> CoilHeatingLowTempRadiantConstFlow_Impl::inletModelObject() const {
      if (auto p = parent()) {
        if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resolvedNodeTarget(
              openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName)) {
          return node->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    boost::optional<ModelObject> CoilHeatingLowTempRadiantConstFlow_Impl::outletModelObject() const {
      if (auto p = parent()) {
        if (auto node = p->getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resolvedNodeTarget(
              openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName)) {
          return node->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    bool CoilHeatingLowTempRadiantConstFlow_Impl::addToNode(Node& node) {
      auto p = parent();
      if (!p || plantLoop()) {
        return false;
      }

      // The canonical OpenStudio surface lets the transient heating coil behave
      // like a plant component. EnergyPlus persists the parent radiant unit on the
      // branch instead, so this method inserts the parent object into the branch
      // and then wires the parent's heating-side water nodes to match the branch
      // row that conceptually belongs to this transient child.
      return addTransientRadiantParentToPlantNode(
        node, p->cast<ModelObject>(), openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName,
        openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, "Heating Coil");
    }

    bool CoilHeatingLowTempRadiantConstFlow_Impl::removeFromLoop() {
      if (auto p = parent()) {
        return removeTransientRadiantParentFromPlantLoop(*this, p->cast<ModelObject>(),
                                                         openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName,
                                                         openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName);
      }
      return false;
    }

    void CoilHeatingLowTempRadiantConstFlow_Impl::disconnect() {
      if (auto p = parent()) {
        p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName, Handle());
        p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, Handle());
      }
    }

    boost::optional<ZoneHVACLowTempRadiantConstFlow> CoilHeatingLowTempRadiantConstFlow_Impl::parent() const {
      const auto thisName = getObject<openstudio::epmodel::CoilHeatingLowTempRadiantConstFlow>().name();
      if (!thisName) {
        return boost::none;
      }

      // This is intentionally a name-based reverse lookup for now. These transient
      // companion coils are not persisted EnergyPlus objects, and today they do not
      // carry an explicit parent handle. The stable transient name gives us a way
      // to recover the owning radiant parent without inventing fake persisted
      // relationship fields. It works, but it is also a sign that a future
      // transient-ownership mechanism could be cleaner than reverse name matching.
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow>()) {
        if (openstudio::istringEqual(*thisName, detail::transientHeatingCoilName(candidate))) {
          return candidate;
        }
      }
      return boost::none;
    }

    boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingHighWaterTemperatureSchedule() const {
      if (auto p = parent()) {
        return p->getModelObjectTarget<Schedule>(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName);
      }
      return boost::none;
    }

    boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingLowWaterTemperatureSchedule() const {
      if (auto p = parent()) {
        return p->getModelObjectTarget<Schedule>(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName);
      }
      return boost::none;
    }

    boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingHighControlTemperatureSchedule() const {
      if (auto p = parent()) {
        return p->getModelObjectTarget<Schedule>(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName);
      }
      return boost::none;
    }

    boost::optional<Schedule> CoilHeatingLowTempRadiantConstFlow_Impl::heatingLowControlTemperatureSchedule() const {
      if (auto p = parent()) {
        return p->getModelObjectTarget<Schedule>(
          openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName);
      }
      return boost::none;
    }

    bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingHighWaterTemperatureSchedule(Schedule& schedule) {
      if (auto p = parent()) {
        return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName,
                             schedule.handle());
      }
      return false;
    }

    void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingHighWaterTemperatureSchedule() {
      if (auto p = parent()) {
        OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName, ""));
      }
    }

    bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingLowWaterTemperatureSchedule(Schedule& schedule) {
      if (auto p = parent()) {
        return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName,
                             schedule.handle());
      }
      return false;
    }

    void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingLowWaterTemperatureSchedule() {
      if (auto p = parent()) {
        OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName, ""));
      }
    }

    bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingHighControlTemperatureSchedule(Schedule& schedule) {
      if (auto p = parent()) {
        return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName,
                             schedule.handle());
      }
      return false;
    }

    void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingHighControlTemperatureSchedule() {
      if (auto p = parent()) {
        OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName, ""));
      }
    }

    bool CoilHeatingLowTempRadiantConstFlow_Impl::setHeatingLowControlTemperatureSchedule(Schedule& schedule) {
      if (auto p = parent()) {
        return p->setPointer(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName,
                             schedule.handle());
      }
      return false;
    }

    void CoilHeatingLowTempRadiantConstFlow_Impl::resetHeatingLowControlTemperatureSchedule() {
      if (auto p = parent()) {
        OS_ASSERT(p->setString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName, ""));
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
