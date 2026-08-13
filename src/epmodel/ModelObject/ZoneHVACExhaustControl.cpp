/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/ZoneHVACExhaustControl.hpp"
#include "ModelObject/ZoneHVACExhaustControl_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"
#include "ModelObject/AirLoopHVACExhaustSystem.hpp"
#include "ModelObject/AirLoopHVACExhaustSystem_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_ExhaustControl_FieldEnums.hxx>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  ZoneHVACExhaustControl::ZoneHVACExhaustControl(const Model& model) : ModelObject(ZoneHVACExhaustControl::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACExhaustControl_Impl>());

    autosizeDesignExhaustFlowRate();
    OS_ASSERT(setFlowControlType("Scheduled"));
  }

  ZoneHVACExhaustControl::ZoneHVACExhaustControl(std::shared_ptr<detail::ZoneHVACExhaustControl_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACExhaustControl::iddObjectType() {
    return IddObjectType::ZoneHVAC_ExhaustControl;
  }

  std::vector<std::string> ZoneHVACExhaustControl::flowControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType);
  }

  boost::optional<Schedule> ZoneHVACExhaustControl::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->availabilitySchedule();
  }

  boost::optional<ThermalZone> ZoneHVACExhaustControl::thermalZone() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->thermalZone();
  }

  boost::optional<Node> ZoneHVACExhaustControl::inletNode() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->inletNode();
  }

  boost::optional<Node> ZoneHVACExhaustControl::outletNode() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->outletNode();
  }

  std::string ZoneHVACExhaustControl::flowControlType() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->flowControlType();
  }

  bool ZoneHVACExhaustControl::setFlowControlType(const std::string& flowControlType) {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->setFlowControlType(flowControlType);
  }

  bool ZoneHVACExhaustControl::isFlowControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->isFlowControlTypeDefaulted();
  }

  void ZoneHVACExhaustControl::resetFlowControlType() {
    getImpl<detail::ZoneHVACExhaustControl_Impl>()->resetFlowControlType();
  }

  boost::optional<double> ZoneHVACExhaustControl::designExhaustFlowRate() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->designExhaustFlowRate();
  }

  bool ZoneHVACExhaustControl::isDesignExhaustFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->isDesignExhaustFlowRateAutosized();
  }

  bool ZoneHVACExhaustControl::setDesignExhaustFlowRate(double designExhaustFlowRate) {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->setDesignExhaustFlowRate(designExhaustFlowRate);
  }

  void ZoneHVACExhaustControl::autosizeDesignExhaustFlowRate() {
    getImpl<detail::ZoneHVACExhaustControl_Impl>()->autosizeDesignExhaustFlowRate();
  }

  void ZoneHVACExhaustControl::resetDesignExhaustFlowRate() {
    getImpl<detail::ZoneHVACExhaustControl_Impl>()->resetDesignExhaustFlowRate();
  }

  boost::optional<Schedule> ZoneHVACExhaustControl::exhaustFlowFractionSchedule() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->exhaustFlowFractionSchedule();
  }

  boost::optional<ModelObject> ZoneHVACExhaustControl::supplyNodeorNodeList() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->supplyNodeorNodeList();
  }

  boost::optional<Schedule> ZoneHVACExhaustControl::minimumZoneTemperatureLimitSchedule() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->minimumZoneTemperatureLimitSchedule();
  }

  boost::optional<Schedule> ZoneHVACExhaustControl::minimumExhaustFlowFractionSchedule() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->minimumExhaustFlowFractionSchedule();
  }

  boost::optional<Schedule> ZoneHVACExhaustControl::balancedExhaustFractionSchedule() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->balancedExhaustFractionSchedule();
  }

  boost::optional<AirLoopHVACExhaustSystem> ZoneHVACExhaustControl::airLoopHVACExhaustSystem() const {
    return getImpl<detail::ZoneHVACExhaustControl_Impl>()->airLoopHVACExhaustSystem();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> ZoneHVACExhaustControl_Impl::flowControlTypeValues() const {
      return openstudio::epmodel::ZoneHVACExhaustControl::flowControlTypeValues();
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneHVACExhaustControl_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneHVAC_ExhaustControlFields::AvailabilityScheduleName);
    }

    boost::optional<openstudio::epmodel::ThermalZone> ZoneHVACExhaustControl_Impl::thermalZone() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(openstudio::ZoneHVAC_ExhaustControlFields::ZoneName);
    }

    boost::optional<openstudio::epmodel::Node> ZoneHVACExhaustControl_Impl::inletNode() const {
      return resolvedNodeTarget(openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName);
    }

    boost::optional<openstudio::epmodel::Node> ZoneHVACExhaustControl_Impl::outletNode() const {
      return resolvedNodeTarget(openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName);
    }

    std::string ZoneHVACExhaustControl_Impl::flowControlType() const {
      const auto value = getString(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACExhaustControl_Impl::isFlowControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType);
    }

    bool ZoneHVACExhaustControl_Impl::setFlowControlType(const std::string& flowControlType) {
      return setString(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType, flowControlType);
    }

    void ZoneHVACExhaustControl_Impl::resetFlowControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_ExhaustControlFields::FlowControlType, ""));
    }

    boost::optional<double> ZoneHVACExhaustControl_Impl::designExhaustFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, true);
    }

    bool ZoneHVACExhaustControl_Impl::isDesignExhaustFlowRateAutosized() const {
      return !designExhaustFlowRate();
    }

    bool ZoneHVACExhaustControl_Impl::setDesignExhaustFlowRate(double designExhaustFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, designExhaustFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACExhaustControl_Impl::autosizeDesignExhaustFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, "autosize"));
    }

    void ZoneHVACExhaustControl_Impl::resetDesignExhaustFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_ExhaustControlFields::DesignExhaustFlowRate, ""));
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneHVACExhaustControl_Impl::exhaustFlowFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneHVAC_ExhaustControlFields::ExhaustFlowFractionScheduleName);
    }

    boost::optional<openstudio::epmodel::ModelObject> ZoneHVACExhaustControl_Impl::supplyNodeorNodeList() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
        openstudio::ZoneHVAC_ExhaustControlFields::SupplyNodeorNodeListName);
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneHVACExhaustControl_Impl::minimumZoneTemperatureLimitSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneHVAC_ExhaustControlFields::MinimumZoneTemperatureLimitScheduleName);
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneHVACExhaustControl_Impl::minimumExhaustFlowFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneHVAC_ExhaustControlFields::MinimumExhaustFlowFractionScheduleName);
    }

    boost::optional<openstudio::epmodel::Schedule> ZoneHVACExhaustControl_Impl::balancedExhaustFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ZoneHVAC_ExhaustControlFields::BalancedExhaustFractionScheduleName);
    }

    boost::optional<openstudio::epmodel::AirLoopHVACExhaustSystem> ZoneHVACExhaustControl_Impl::airLoopHVACExhaustSystem() const {
      const auto outlet = outletNode();
      if (!outlet) {
        return boost::none;
      }

      boost::optional<openstudio::epmodel::AirLoopHVACExhaustSystem> result;
      for (const auto& system : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACExhaustSystem>()) {
        const auto mixer = system.zoneMixer();
        if (!mixer) {
          continue;
        }
        const auto inlets = mixer->inletModelObjects();
        if (std::ranges::find(inlets, outlet->cast<ModelObject>()) != inlets.end()) {
          if (result) {
            return boost::none;
          }
          result = system;
        }
      }
      return result;
    }

    std::vector<openstudio::IdfObject> ZoneHVACExhaustControl_Impl::remove() {
      auto control = getObject<openstudio::epmodel::ZoneHVACExhaustControl>();
      auto owningModel = model();
      if (auto owner = airLoopHVACExhaustSystem()) {
        return owner->getImpl<openstudio::epmodel::detail::AirLoopHVACExhaustSystem_Impl>()->removeZoneHVACExhaustControlObjects(control);
      }

      const auto outlet = outletNode();
      if (outlet) {
        const auto outletObject = outlet->cast<openstudio::epmodel::ModelObject>();
        for (const auto& mixer : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACZoneMixer>()) {
          const auto inlets = mixer.inletModelObjects();
          if (std::ranges::find(inlets, outletObject) != inlets.end()) {
            return {};
          }
        }
      }

      const auto zone = thermalZone();
      const auto inlet = inletNode();
      boost::optional<openstudio::epmodel::ZoneHVACEquipmentConnections> connections;
      boost::optional<Handle> registrationSourceHandle;
      std::size_t inletCount = 0u;
      if (zone && inlet) {
        auto zoneImpl = zone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        connections = zoneImpl->zoneHVACEquipmentConnections();
        if (connections) {
          auto connectionsImpl = connections->getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentConnections_Impl>();
          OS_ASSERT(connectionsImpl);
          inletCount = std::ranges::count(connections->zoneAirExhaustNodes(), *inlet);
          if ((inletCount > 1) || ((inletCount == 1) && !connectionsImpl->hasExclusiveZoneAirExhaustNodeStorage())) {
            return {};
          }
          if (inletCount == 1) {
            constexpr unsigned exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
            const auto registrationTarget = connections->getTarget(exhaustField);
            if (!registrationTarget) {
              return {};
            }
            registrationSourceHandle = registrationTarget->handle() == inlet->handle() ? connections->handle() : registrationTarget->handle();
          }
        }
      }

      if (inlet) {
        const auto inletSources = inlet->sources();
        if (inletSources.size() != (registrationSourceHandle ? 2u : 1u)) {
          return {};
        }
        bool foundControlInlet = false;
        bool foundRegistration = !registrationSourceHandle;
        for (const auto& source : inletSources) {
          const auto sourceFields = source.getSourceIndices(inlet->handle());
          if (source.handle() == control.handle()) {
            foundControlInlet = (sourceFields.size() == 1u) && (sourceFields.front() == openstudio::ZoneHVAC_ExhaustControlFields::InletNodeName);
          } else if (registrationSourceHandle && (source.handle() == *registrationSourceHandle)) {
            foundRegistration = sourceFields.size() == 1u;
          } else {
            return {};
          }
        }
        if (!foundControlInlet || !foundRegistration) {
          return {};
        }
      }

      if (outlet) {
        const auto outletSources = outlet->sources();
        if (outletSources.size() != 1u || outletSources.front().handle() != control.handle()) {
          return {};
        }
        const auto sourceFields = outletSources.front().getSourceIndices(outlet->handle());
        if ((sourceFields.size() != 1u) || (sourceFields.front() != openstudio::ZoneHVAC_ExhaustControlFields::OutletNodeName)) {
          return {};
        }
      }

      if (connections && inletCount == 1u) {
        auto connectionsImpl = connections->getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentConnections_Impl>();
        OS_ASSERT(connectionsImpl);
        if (!connectionsImpl->removeZoneAirExhaustNode(*inlet)) {
          return {};
        }
      }

      auto result = ModelObject_Impl::remove();
      OS_ASSERT(!result.empty());
      for (auto node : {inlet, outlet}) {
        if (node && owningModel.getObject(node->handle()) && node->sources().empty()) {
          auto removed = node->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
