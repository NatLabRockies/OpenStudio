/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingWaterPanelRadiant.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Cooling_Water_Panel_Radiant_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilCoolingWaterPanelRadiant::CoilCoolingWaterPanelRadiant(const Model& model)
    : StraightComponent(CoilCoolingWaterPanelRadiant::iddObjectType(), model, false, true) {}

  CoilCoolingWaterPanelRadiant::CoilCoolingWaterPanelRadiant(std::shared_ptr<detail::CoilCoolingWaterPanelRadiant_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingWaterPanelRadiant::iddObjectType() {
    return IddObjectType::OS_Coil_Cooling_Water_Panel_Radiant;
  }

  std::vector<std::string> CoilCoolingWaterPanelRadiant::coolingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water).get(),
                          openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod);
  }

  std::vector<std::string> CoilCoolingWaterPanelRadiant::controlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water).get(),
                          openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType);
  }

  std::vector<std::string> CoilCoolingWaterPanelRadiant::condensationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water).get(),
                          openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType);
  }

  double CoilCoolingWaterPanelRadiant::ratedInletWaterTemperature() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->ratedInletWaterTemperature();
  }

  bool CoilCoolingWaterPanelRadiant::isRatedInletWaterTemperatureDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isRatedInletWaterTemperatureDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setRatedInletWaterTemperature(ratedInletWaterTemperature);
  }

  void CoilCoolingWaterPanelRadiant::resetRatedInletWaterTemperature() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetRatedInletWaterTemperature();
  }

  double CoilCoolingWaterPanelRadiant::ratedInletSpaceTemperature() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->ratedInletSpaceTemperature();
  }

  bool CoilCoolingWaterPanelRadiant::isRatedInletSpaceTemperatureDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isRatedInletSpaceTemperatureDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setRatedInletSpaceTemperature(double ratedInletSpaceTemperature) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setRatedInletSpaceTemperature(ratedInletSpaceTemperature);
  }

  void CoilCoolingWaterPanelRadiant::resetRatedInletSpaceTemperature() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetRatedInletSpaceTemperature();
  }

  double CoilCoolingWaterPanelRadiant::ratedWaterMassFlowRate() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->ratedWaterMassFlowRate();
  }

  bool CoilCoolingWaterPanelRadiant::isRatedWaterMassFlowRateDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isRatedWaterMassFlowRateDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
  }

  void CoilCoolingWaterPanelRadiant::resetRatedWaterMassFlowRate() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetRatedWaterMassFlowRate();
  }

  std::string CoilCoolingWaterPanelRadiant::coolingDesignCapacityMethod() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->coolingDesignCapacityMethod();
  }

  bool CoilCoolingWaterPanelRadiant::isCoolingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isCoolingDesignCapacityMethodDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
  }

  void CoilCoolingWaterPanelRadiant::resetCoolingDesignCapacityMethod() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetCoolingDesignCapacityMethod();
  }

  boost::optional<double> CoilCoolingWaterPanelRadiant::coolingDesignCapacity() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->coolingDesignCapacity();
  }

  bool CoilCoolingWaterPanelRadiant::isCoolingDesignCapacityAutosized() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isCoolingDesignCapacityAutosized();
  }

  bool CoilCoolingWaterPanelRadiant::setCoolingDesignCapacity(double coolingDesignCapacity) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
  }

  void CoilCoolingWaterPanelRadiant::autosizeCoolingDesignCapacity() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->autosizeCoolingDesignCapacity();
  }

  boost::optional<double> CoilCoolingWaterPanelRadiant::autosizedCoolingDesignCapacity() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->autosizedCoolingDesignCapacity();
  }

  double CoilCoolingWaterPanelRadiant::coolingDesignCapacityPerFloorArea() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->coolingDesignCapacityPerFloorArea();
  }

  bool CoilCoolingWaterPanelRadiant::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCoolingDesignCapacityPerFloorArea(coolingDesignCapacityPerFloorArea);
  }

  double CoilCoolingWaterPanelRadiant::fractionofAutosizedCoolingDesignCapacity() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->fractionofAutosizedCoolingDesignCapacity();
  }

  bool CoilCoolingWaterPanelRadiant::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setFractionofAutosizedCoolingDesignCapacity(
      fractionofAutosizedCoolingDesignCapacity);
  }

  boost::optional<double> CoilCoolingWaterPanelRadiant::maximumChilledWaterFlowRate() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->maximumChilledWaterFlowRate();
  }

  bool CoilCoolingWaterPanelRadiant::isMaximumChilledWaterFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isMaximumChilledWaterFlowRateAutosized();
  }

  bool CoilCoolingWaterPanelRadiant::setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setMaximumChilledWaterFlowRate(maximumChilledWaterFlowRate);
  }

  void CoilCoolingWaterPanelRadiant::autosizeMaximumChilledWaterFlowRate() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->autosizeMaximumChilledWaterFlowRate();
  }

  boost::optional<double> CoilCoolingWaterPanelRadiant::autosizedMaximumChilledWaterFlowRate() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->autosizedMaximumChilledWaterFlowRate();
  }

  std::string CoilCoolingWaterPanelRadiant::controlType() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->controlType();
  }

  bool CoilCoolingWaterPanelRadiant::isControlTypeDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isControlTypeDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setControlType(const std::string& controlType) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setControlType(controlType);
  }

  void CoilCoolingWaterPanelRadiant::resetControlType() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetControlType();
  }

  double CoilCoolingWaterPanelRadiant::coolingControlThrottlingRange() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->coolingControlThrottlingRange();
  }

  bool CoilCoolingWaterPanelRadiant::isCoolingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isCoolingControlThrottlingRangeDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
  }

  void CoilCoolingWaterPanelRadiant::resetCoolingControlThrottlingRange() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetCoolingControlThrottlingRange();
  }

  boost::optional<Schedule> CoilCoolingWaterPanelRadiant::coolingControlTemperatureSchedule() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->coolingControlTemperatureSchedule();
  }

  bool CoilCoolingWaterPanelRadiant::setCoolingControlTemperatureSchedule(Schedule& coolingControlTemperatureSchedule) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCoolingControlTemperatureSchedule(coolingControlTemperatureSchedule);
  }

  void CoilCoolingWaterPanelRadiant::resetCoolingControlTemperatureSchedule() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetCoolingControlTemperatureSchedule();
  }

  std::string CoilCoolingWaterPanelRadiant::condensationControlType() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->condensationControlType();
  }

  bool CoilCoolingWaterPanelRadiant::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isCondensationControlTypeDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setCondensationControlType(const std::string& condensationControlType) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCondensationControlType(condensationControlType);
  }

  void CoilCoolingWaterPanelRadiant::resetCondensationControlType() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetCondensationControlType();
  }

  double CoilCoolingWaterPanelRadiant::condensationControlDewpointOffset() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->condensationControlDewpointOffset();
  }

  bool CoilCoolingWaterPanelRadiant::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  bool CoilCoolingWaterPanelRadiant::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
    return getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->setCondensationControlDewpointOffset(condensationControlDewpointOffset);
  }

  void CoilCoolingWaterPanelRadiant::resetCondensationControlDewpointOffset() {
    getImpl<detail::CoilCoolingWaterPanelRadiant_Impl>()->resetCondensationControlDewpointOffset();
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

      bool removeTransientRadiantParentFromPlantLoop(const CoilCoolingWaterPanelRadiant_Impl& coilImpl, ModelObject parentObject, unsigned inletField,
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

    unsigned CoilCoolingWaterPanelRadiant_Impl::inletPort() const {
      return openstudio::OS_Coil_Cooling_Water_Panel_RadiantFields::WaterInletNodeName;
    }

    unsigned CoilCoolingWaterPanelRadiant_Impl::outletPort() const {
      return openstudio::OS_Coil_Cooling_Water_Panel_RadiantFields::WaterOutletNodeName;
    }

    boost::optional<ModelObject> CoilCoolingWaterPanelRadiant_Impl::inletModelObject() const {
      if (auto p = parent()) {
        if (auto node = p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resolvedNodeTarget(
              openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName)) {
          return node->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    boost::optional<ModelObject> CoilCoolingWaterPanelRadiant_Impl::outletModelObject() const {
      if (auto p = parent()) {
        if (auto node = p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resolvedNodeTarget(
              openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName)) {
          return node->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::addToNode(Node& node) {
      auto p = parent();
      if (!p || plantLoop()) {
        return false;
      }

      return addTransientRadiantParentToPlantNode(
        node, p->cast<ModelObject>(), openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName,
        openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName, "Cooling Coil");
    }

    bool CoilCoolingWaterPanelRadiant_Impl::removeFromLoop() {
      if (auto p = parent()) {
        return removeTransientRadiantParentFromPlantLoop(*this, p->cast<ModelObject>(),
                                                         openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName,
                                                         openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::disconnect() {
      if (auto p = parent()) {
        p->setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName, Handle());
        p->setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName, Handle());
      }
    }

    boost::optional<ZoneHVACCoolingPanelRadiantConvectiveWater> CoilCoolingWaterPanelRadiant_Impl::parent() const {
      const auto thisName = getObject<openstudio::epmodel::CoilCoolingWaterPanelRadiant>().name();
      if (!thisName) {
        return boost::none;
      }

      // This transient companion still recovers its owner by stable generated
      // name. The child has no persisted EnergyPlus object or explicit parent
      // handle today, so the deterministic name is the mechanism that lets the
      // view find its owning cooling panel without inventing fake relationship
      // fields.
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACCoolingPanelRadiantConvectiveWater>()) {
        if (openstudio::istringEqual(*thisName, detail::transientCoolingCoilName(candidate))) {
          return candidate;
        }
      }

      return boost::none;
    }

    double CoilCoolingWaterPanelRadiant_Impl::ratedInletWaterTemperature() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->ratedInletWaterTemperature();
      }
      return 5.0;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isRatedInletWaterTemperatureDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isRatedInletWaterTemperatureDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setRatedInletWaterTemperature(double ratedInletWaterTemperature) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setRatedInletWaterTemperature(ratedInletWaterTemperature);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetRatedInletWaterTemperature() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetRatedInletWaterTemperature();
      }
    }

    double CoilCoolingWaterPanelRadiant_Impl::ratedInletSpaceTemperature() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->ratedInletSpaceTemperature();
      }
      return 24.0;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isRatedInletSpaceTemperatureDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isRatedInletSpaceTemperatureDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setRatedInletSpaceTemperature(double ratedInletSpaceTemperature) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setRatedInletSpaceTemperature(ratedInletSpaceTemperature);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetRatedInletSpaceTemperature() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetRatedInletSpaceTemperature();
      }
    }

    double CoilCoolingWaterPanelRadiant_Impl::ratedWaterMassFlowRate() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->ratedWaterMassFlowRate();
      }
      return 0.063;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isRatedWaterMassFlowRateDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isRatedWaterMassFlowRateDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetRatedWaterMassFlowRate() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetRatedWaterMassFlowRate();
      }
    }

    std::string CoilCoolingWaterPanelRadiant_Impl::coolingDesignCapacityMethod() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingDesignCapacityMethod();
      }
      return "CoolingDesignCapacity";
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isCoolingDesignCapacityMethodDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCoolingDesignCapacityMethodDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetCoolingDesignCapacityMethod() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCoolingDesignCapacityMethod();
      }
    }

    boost::optional<double> CoilCoolingWaterPanelRadiant_Impl::coolingDesignCapacity() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingDesignCapacity();
      }
      return boost::none;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isCoolingDesignCapacityAutosized() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCoolingDesignCapacityAutosized();
      }
      return false;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::autosizeCoolingDesignCapacity() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->autosizeCoolingDesignCapacity();
      }
    }

    boost::optional<double> CoilCoolingWaterPanelRadiant_Impl::autosizedCoolingDesignCapacity() const {
      // This transient child is a view over parent-owned radiant storage. The
      // parent can eventually surface autosized SQL-backed results for these
      // fields, but epmodel does not yet expose a clean public path for that on
      // this family.
      return boost::none;
    }

    double CoilCoolingWaterPanelRadiant_Impl::coolingDesignCapacityPerFloorArea() const {
      if (auto p = parent()) {
        if (auto value = p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingDesignCapacityPerFloorArea()) {
          return *value;
        }
      }
      return 0.0;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingDesignCapacityPerFloorArea(
          coolingDesignCapacityPerFloorArea);
      }
      return false;
    }

    double CoilCoolingWaterPanelRadiant_Impl::fractionofAutosizedCoolingDesignCapacity() const {
      if (auto p = parent()) {
        if (auto value = p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->fractionofAutosizedCoolingDesignCapacity()) {
          return *value;
        }
      }
      return 1.0;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setFractionOfAutosizedCoolingDesignCapacity(
          fractionofAutosizedCoolingDesignCapacity);
      }
      return false;
    }

    boost::optional<double> CoilCoolingWaterPanelRadiant_Impl::maximumChilledWaterFlowRate() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->maximumChilledWaterFlowRate();
      }
      return boost::none;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isMaximumChilledWaterFlowRateAutosized() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isMaximumChilledWaterFlowRateAutosized();
      }
      return false;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setMaximumChilledWaterFlowRate(maximumChilledWaterFlowRate);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::autosizeMaximumChilledWaterFlowRate() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->autosizeMaximumChilledWaterFlowRate();
      }
    }

    boost::optional<double> CoilCoolingWaterPanelRadiant_Impl::autosizedMaximumChilledWaterFlowRate() const {
      // This transient child is a view over parent-owned radiant storage. The
      // parent can eventually surface autosized SQL-backed results for these
      // fields, but epmodel does not yet expose a clean public path for that on
      // this family.
      return boost::none;
    }

    std::string CoilCoolingWaterPanelRadiant_Impl::controlType() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->controlType();
      }
      return "MeanAirTemperature";
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isControlTypeDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isControlTypeDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setControlType(const std::string& controlType) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setControlType(controlType);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetControlType() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetControlType();
      }
    }

    double CoilCoolingWaterPanelRadiant_Impl::coolingControlThrottlingRange() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->coolingControlThrottlingRange();
      }
      return 0.5;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isCoolingControlThrottlingRangeDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCoolingControlThrottlingRangeDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetCoolingControlThrottlingRange() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCoolingControlThrottlingRange();
      }
    }

    boost::optional<Schedule> CoilCoolingWaterPanelRadiant_Impl::coolingControlTemperatureSchedule() const {
      if (auto p = parent()) {
        return p->getModelObjectTarget<Schedule>(
          openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName);
      }
      return boost::none;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCoolingControlTemperatureSchedule(Schedule& coolingControlTemperatureSchedule) {
      if (auto p = parent()) {
        return p->setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName,
                             coolingControlTemperatureSchedule.handle());
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetCoolingControlTemperatureSchedule() {
      if (auto p = parent()) {
        OS_ASSERT(p->setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName, Handle()));
      }
    }

    std::string CoilCoolingWaterPanelRadiant_Impl::condensationControlType() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->condensationControlType();
      }
      return "SimpleOff";
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isCondensationControlTypeDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCondensationControlTypeDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCondensationControlType(const std::string& condensationControlType) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCondensationControlType(condensationControlType);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetCondensationControlType() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCondensationControlType();
      }
    }

    double CoilCoolingWaterPanelRadiant_Impl::condensationControlDewpointOffset() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->condensationControlDewpointOffset();
      }
      return 1.0;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->isCondensationControlDewpointOffsetDefaulted();
      }
      return true;
    }

    bool CoilCoolingWaterPanelRadiant_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
      if (auto p = parent()) {
        return p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->setCondensationControlDewpointOffset(
          condensationControlDewpointOffset);
      }
      return false;
    }

    void CoilCoolingWaterPanelRadiant_Impl::resetCondensationControlDewpointOffset() {
      if (auto p = parent()) {
        p->getImpl<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl>()->resetCondensationControlDewpointOffset();
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
