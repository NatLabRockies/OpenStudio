/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "ModelObject/AirLoopHVACControllerList.hpp"
#include "ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ModelObject/ControllerMechanicalVentilation.hpp"
#include "ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "ModelObject/OutdoorAirMixer.hpp"
#include "ModelObject/OutdoorAirMixer_Impl.hpp"
#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "SizingZone.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Deprecated.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <iterator>

namespace openstudio {
namespace epmodel {

  ControllerOutdoorAir::ControllerOutdoorAir(const Model& model) : ParentObject(ControllerOutdoorAir::iddObjectType(), model) {
    auto impl = getImpl<detail::ControllerOutdoorAir_Impl>();
    OS_ASSERT(impl);
    impl->resetMinimumOutdoorAirSchedule();
    impl->resetMinimumFractionofOutdoorAirSchedule();
    impl->resetMaximumFractionofOutdoorAirSchedule();
    impl->resetTimeofDayEconomizerControlSchedule();
    impl->resetElectronicEnthalpyLimitCurve();
    impl->resetHumidistatControlZone();
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ControllerOutdoorAir::ControllerOutdoorAir(std::shared_ptr<detail::ControllerOutdoorAir_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType ControllerOutdoorAir::iddObjectType() {
    return IddObjectType::Controller_OutdoorAir;
  }

  std::vector<std::string> ControllerOutdoorAir::economizerControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Controller_OutdoorAirFields::EconomizerControlType);
  }

  std::vector<std::string> ControllerOutdoorAir::economizerControlActionTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Controller_OutdoorAirFields::EconomizerControlActionType);
  }

  std::vector<std::string> ControllerOutdoorAir::lockoutTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Controller_OutdoorAirFields::LockoutType);
  }

  std::vector<std::string> ControllerOutdoorAir::minimumLimitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Controller_OutdoorAirFields::MinimumLimitType);
  }

  std::vector<std::string> ControllerOutdoorAir::heatRecoveryBypassControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Controller_OutdoorAirFields::HeatRecoveryBypassControlType);
  }

  std::vector<std::string> ControllerOutdoorAir::economizerOperationStagingValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Controller_OutdoorAirFields::EconomizerOperationStaging);
  }

  boost::optional<Schedule> ControllerOutdoorAir::minimumOutdoorAirSchedule() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->minimumOutdoorAirSchedule();
  }

  bool ControllerOutdoorAir::setMinimumOutdoorAirSchedule(Schedule& schedule) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setMinimumOutdoorAirSchedule(schedule);
  }

  void ControllerOutdoorAir::resetMinimumOutdoorAirSchedule() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->resetMinimumOutdoorAirSchedule();
  }

  boost::optional<Schedule> ControllerOutdoorAir::minimumFractionofOutdoorAirSchedule() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->minimumFractionofOutdoorAirSchedule();
  }

  bool ControllerOutdoorAir::setMinimumFractionofOutdoorAirSchedule(Schedule& schedule) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setMinimumFractionofOutdoorAirSchedule(schedule);
  }

  void ControllerOutdoorAir::resetMinimumFractionofOutdoorAirSchedule() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->resetMinimumFractionofOutdoorAirSchedule();
  }

  boost::optional<Schedule> ControllerOutdoorAir::maximumFractionofOutdoorAirSchedule() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->maximumFractionofOutdoorAirSchedule();
  }

  bool ControllerOutdoorAir::setMaximumFractionofOutdoorAirSchedule(Schedule& schedule) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setMaximumFractionofOutdoorAirSchedule(schedule);
  }

  void ControllerOutdoorAir::resetMaximumFractionofOutdoorAirSchedule() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->resetMaximumFractionofOutdoorAirSchedule();
  }

  boost::optional<Schedule> ControllerOutdoorAir::timeofDayEconomizerControlSchedule() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->timeofDayEconomizerControlSchedule();
  }

  bool ControllerOutdoorAir::setTimeofDayEconomizerControlSchedule(Schedule& schedule) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setTimeofDayEconomizerControlSchedule(schedule);
  }

  void ControllerOutdoorAir::resetTimeofDayEconomizerControlSchedule() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->resetTimeofDayEconomizerControlSchedule();
  }

  boost::optional<double> ControllerOutdoorAir::minimumOutdoorAirFlowRate() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->minimumOutdoorAirFlowRate();
  }

  bool ControllerOutdoorAir::isMinimumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->isMinimumOutdoorAirFlowRateAutosized();
  }

  bool ControllerOutdoorAir::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setMinimumOutdoorAirFlowRate(minimumOutdoorAirFlowRate);
  }

  void ControllerOutdoorAir::autosizeMinimumOutdoorAirFlowRate() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->autosizeMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ControllerOutdoorAir::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ControllerOutdoorAir::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool ControllerOutdoorAir::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  void ControllerOutdoorAir::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  std::string ControllerOutdoorAir::getEconomizerControlType() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getEconomizerControlType();
  }

  bool ControllerOutdoorAir::setEconomizerControlType(const std::string& value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerControlType(value);
  }

  std::string ControllerOutdoorAir::getEconomizerControlActionType() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getEconomizerControlActionType();
  }

  bool ControllerOutdoorAir::setEconomizerControlActionType(const std::string& value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerControlActionType(value);
  }

  boost::optional<double> ControllerOutdoorAir::getEconomizerMaximumLimitDryBulbTemperature() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getEconomizerMaximumLimitDryBulbTemperature();
  }

  bool ControllerOutdoorAir::setEconomizerMaximumLimitDryBulbTemperature(double value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMaximumLimitDryBulbTemperature(value);
  }

  void ControllerOutdoorAir::resetEconomizerMaximumLimitDryBulbTemperature() {
    const bool ok = getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMaximumLimitDryBulbTemperature(boost::none);
    OS_ASSERT(ok);
  }

  boost::optional<double> ControllerOutdoorAir::getEconomizerMaximumLimitEnthalpy() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getEconomizerMaximumLimitEnthalpy();
  }

  bool ControllerOutdoorAir::setEconomizerMaximumLimitEnthalpy(double value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMaximumLimitEnthalpy(value);
  }

  void ControllerOutdoorAir::resetEconomizerMaximumLimitEnthalpy() {
    const bool ok = getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMaximumLimitEnthalpy(boost::none);
    OS_ASSERT(ok);
  }

  boost::optional<double> ControllerOutdoorAir::getEconomizerMaximumLimitDewpointTemperature() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getEconomizerMaximumLimitDewpointTemperature();
  }

  bool ControllerOutdoorAir::setEconomizerMaximumLimitDewpointTemperature(double value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMaximumLimitDewpointTemperature(value);
  }

  void ControllerOutdoorAir::resetEconomizerMaximumLimitDewpointTemperature() {
    const bool ok = getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMaximumLimitDewpointTemperature(boost::none);
    OS_ASSERT(ok);
  }

  boost::optional<Curve> ControllerOutdoorAir::electronicEnthalpyLimitCurve() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->electronicEnthalpyLimitCurve();
  }

  bool ControllerOutdoorAir::setElectronicEnthalpyLimitCurve(const Curve& curve) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setElectronicEnthalpyLimitCurve(curve);
  }

  void ControllerOutdoorAir::resetElectronicEnthalpyLimitCurve() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->resetElectronicEnthalpyLimitCurve();
  }

  boost::optional<double> ControllerOutdoorAir::getEconomizerMinimumLimitDryBulbTemperature() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getEconomizerMinimumLimitDryBulbTemperature();
  }

  bool ControllerOutdoorAir::setEconomizerMinimumLimitDryBulbTemperature(double value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMinimumLimitDryBulbTemperature(value);
  }

  void ControllerOutdoorAir::resetEconomizerMinimumLimitDryBulbTemperature() {
    const bool ok = getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerMinimumLimitDryBulbTemperature(boost::none);
    OS_ASSERT(ok);
  }

  std::string ControllerOutdoorAir::getLockoutType() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getLockoutType();
  }

  bool ControllerOutdoorAir::setLockoutType(const std::string& value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setLockoutType(value);
  }

  std::string ControllerOutdoorAir::getMinimumLimitType() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getMinimumLimitType();
  }

  bool ControllerOutdoorAir::setMinimumLimitType(const std::string& value) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setMinimumLimitType(value);
  }

  boost::optional<bool> ControllerOutdoorAir::getHighHumidityControl() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getHighHumidityControl();
  }

  bool ControllerOutdoorAir::setHighHumidityControl(bool val) {
    (void)val;
    return false;
  }

  boost::optional<ThermalZone> ControllerOutdoorAir::humidistatControlZone() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->humidistatControlZone();
  }

  bool ControllerOutdoorAir::setHumidistatControlZone(const ThermalZone& thermalZone) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setHumidistatControlZone(thermalZone);
  }

  void ControllerOutdoorAir::resetHumidistatControlZone() {
    getImpl<detail::ControllerOutdoorAir_Impl>()->resetHumidistatControlZone();
  }

  double ControllerOutdoorAir::getHighHumidityOutdoorAirFlowRatio() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getHighHumidityOutdoorAirFlowRatio();
  }

  bool ControllerOutdoorAir::setHighHumidityOutdoorAirFlowRatio(double v) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setHighHumidityOutdoorAirFlowRatio(v);
  }

  bool ControllerOutdoorAir::getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio();
  }

  bool ControllerOutdoorAir::setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool v) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(v);
  }

  boost::optional<std::string> ControllerOutdoorAir::getHeatRecoveryBypassControlType() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->getHeatRecoveryBypassControlType();
  }

  bool ControllerOutdoorAir::setHeatRecoveryBypassControlType(const std::string& v) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setHeatRecoveryBypassControlType(v);
  }

  std::string ControllerOutdoorAir::economizerOperationStaging() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->economizerOperationStaging();
  }

  bool ControllerOutdoorAir::setEconomizerOperationStaging(const std::string& v) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setEconomizerOperationStaging(v);
  }

  ControllerMechanicalVentilation ControllerOutdoorAir::controllerMechanicalVentilation() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->controllerMechanicalVentilation();
  }

  bool ControllerOutdoorAir::setControllerMechanicalVentilation(const ControllerMechanicalVentilation& controllerMechanicalVentilation) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setControllerMechanicalVentilation(controllerMechanicalVentilation);
  }

  boost::optional<AirLoopHVACOutdoorAirSystem> ControllerOutdoorAir::airLoopHVACOutdoorAirSystem() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->airLoopHVACOutdoorAirSystem();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>
        findOwningOutdoorAirSystemForCanonicalize(const openstudio::epmodel::ControllerOutdoorAir& controller) {
        auto controllerImpl = controller.getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>();
        const auto hasUniqueTransientList = [](const openstudio::epmodel::ControllerOutdoorAir& candidate) {
          auto candidateImpl = candidate.getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>();
          if (!candidateImpl || !candidateImpl->isTransient()) {
            return false;
          }
          unsigned transientListCount = 0u;
          for (const auto& source : candidate.getModelObjectSources<openstudio::epmodel::AirLoopHVACControllerList>()) {
            auto listImpl = source.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>();
            auto listedController = source.optionalControllerOutdoorAir();
            if (listImpl && listImpl->isTransient() && listedController && (*listedController == candidate)) {
              ++transientListCount;
            }
          }
          return transientListCount == 1u;
        };

        boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> result;
        for (const auto& oaSystem : controller.model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
          // Canonicalization path may run before OA-system invariants are fully
          // established on every instance, so use a tolerant lookup here.
          auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
            openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
          bool matches = false;
          if (controllerList) {
            auto oaController = controllerList->optionalControllerOutdoorAir();
            matches = oaController && (*oaController == controller);
          }
          if (!matches && controllerImpl && controllerImpl->isTransient() && hasUniqueTransientList(controller)
              && oaSystem.airLoopHVACDedicatedOutdoorAirSystem()) {
            auto actuatorNode = controller.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
            if (actuatorNode) {
              auto outdoorModelObject = oaSystem.outdoorAirModelObject();
              if (outdoorModelObject && (outdoorModelObject->handle() == actuatorNode->handle())) {
                unsigned projectedControllerCount = 0u;
                for (const auto& candidate : controller.model().getConcreteModelObjects<openstudio::epmodel::ControllerOutdoorAir>()) {
                  if (!hasUniqueTransientList(candidate)) {
                    continue;
                  }
                  auto candidateActuator =
                    candidate.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
                  if (candidateActuator && (candidateActuator->handle() == outdoorModelObject->handle())) {
                    ++projectedControllerCount;
                  }
                }
                matches = projectedControllerCount == 1u;
              }
            }
          }
          if (matches) {
            if (result) {
              return boost::none;
            }
            result = oaSystem;
          }
        }
        return result;
      }

      bool hasServedZoneWithDesignSpecificationOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controller, LoadContext& context) {
        auto oaSystem = findOwningOutdoorAirSystemForCanonicalize(controller);
        if (!oaSystem) {
          return false;
        }

        for (const auto& zone : controller.model().getConcreteModelObjects<openstudio::epmodel::ThermalZone>()) {
          zone.getImpl<openstudio::epmodel::detail::ThermalZone_Impl>()->canonicalize(context);

          auto sizingZone = zone.sizingZone();
          if (sizingZone.getModelObjectTarget<openstudio::epmodel::ModelObject>(
                openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName)) {
            return true;
          }
        }

        return false;
      }

    }  // namespace

    boost::optional<openstudio::epmodel::Schedule> ControllerOutdoorAir_Impl::minimumOutdoorAirSchedule() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName);
    }

    bool ControllerOutdoorAir_Impl::setMinimumOutdoorAirSchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the minimum outdoor air schedule because it belongs to a different model.");
        return false;
      }
      if (!setSchedule(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName, "ControllerOutdoorAir", "Minimum Outdoor Air",
                       schedule)) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the minimum outdoor air schedule because its schedule type limits are incompatible.");
        return false;
      }
      return true;
    }

    void ControllerOutdoorAir_Impl::resetMinimumOutdoorAirSchedule() {
      OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ControllerOutdoorAir_Impl::minimumFractionofOutdoorAirSchedule() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName);
    }

    bool ControllerOutdoorAir_Impl::setMinimumFractionofOutdoorAirSchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the minimum fraction of outdoor air schedule because it belongs to a different model.");
        return false;
      }
      if (!setSchedule(openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, "ControllerOutdoorAir",
                       "Minimum Fraction of Outdoor Air", schedule)) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the minimum fraction of outdoor air schedule because its schedule type limits are incompatible.");
        return false;
      }
      return true;
    }

    void ControllerOutdoorAir_Impl::resetMinimumFractionofOutdoorAirSchedule() {
      OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, Handle(), false));
      OS_ASSERT(
        openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ControllerOutdoorAir_Impl::maximumFractionofOutdoorAirSchedule() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName);
    }

    bool ControllerOutdoorAir_Impl::setMaximumFractionofOutdoorAirSchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the maximum fraction of outdoor air schedule because it belongs to a different model.");
        return false;
      }
      if (!setSchedule(openstudio::Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName, "ControllerOutdoorAir",
                       "Maximum Fraction of Outdoor Air", schedule)) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the maximum fraction of outdoor air schedule because its schedule type limits are incompatible.");
        return false;
      }
      return true;
    }

    void ControllerOutdoorAir_Impl::resetMaximumFractionofOutdoorAirSchedule() {
      OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName, Handle(), false));
      OS_ASSERT(
        openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName, "", false));
    }

    boost::optional<openstudio::epmodel::Schedule> ControllerOutdoorAir_Impl::timeofDayEconomizerControlSchedule() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName);
    }

    bool ControllerOutdoorAir_Impl::setTimeofDayEconomizerControlSchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the time-of-day economizer control schedule because it belongs to a different model.");
        return false;
      }
      if (!setSchedule(openstudio::Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName, "ControllerOutdoorAir",
                       "Time of Day Economizer Control", schedule)) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the time-of-day economizer control schedule because its schedule type limits are incompatible.");
        return false;
      }
      return true;
    }

    void ControllerOutdoorAir_Impl::resetTimeofDayEconomizerControlSchedule() {
      OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName, Handle(), false));
      OS_ASSERT(
        openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName, "", false));
    }

    boost::optional<double> ControllerOutdoorAir_Impl::minimumOutdoorAirFlowRate() const {
      return getDouble(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirFlowRate, true);
    }

    bool ControllerOutdoorAir_Impl::isMinimumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ControllerOutdoorAir_Impl::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
      return setDouble(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirFlowRate, minimumOutdoorAirFlowRate);
    }

    void ControllerOutdoorAir_Impl::autosizeMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ControllerOutdoorAir_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(openstudio::Controller_OutdoorAirFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ControllerOutdoorAir_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::Controller_OutdoorAirFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ControllerOutdoorAir_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      return setDouble(openstudio::Controller_OutdoorAirFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
    }

    void ControllerOutdoorAir_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::Controller_OutdoorAirFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    std::string ControllerOutdoorAir_Impl::getEconomizerControlType() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::EconomizerControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerOutdoorAir_Impl::setEconomizerControlType(const std::string& value) {
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerControlType, value);
    }

    std::string ControllerOutdoorAir_Impl::getEconomizerControlActionType() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::EconomizerControlActionType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerOutdoorAir_Impl::setEconomizerControlActionType(const std::string& value) {
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerControlActionType, value);
    }

    boost::optional<double> ControllerOutdoorAir_Impl::getEconomizerMaximumLimitDryBulbTemperature() const {
      return getDouble(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitDryBulbTemperature);
    }

    bool ControllerOutdoorAir_Impl::setEconomizerMaximumLimitDryBulbTemperature(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitDryBulbTemperature, *value);
      }
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitDryBulbTemperature, "");
    }

    boost::optional<double> ControllerOutdoorAir_Impl::getEconomizerMaximumLimitEnthalpy() const {
      return getDouble(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitEnthalpy);
    }

    bool ControllerOutdoorAir_Impl::setEconomizerMaximumLimitEnthalpy(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitEnthalpy, *value);
      }
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitEnthalpy, "");
    }

    boost::optional<double> ControllerOutdoorAir_Impl::getEconomizerMaximumLimitDewpointTemperature() const {
      return getDouble(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitDewpointTemperature);
    }

    bool ControllerOutdoorAir_Impl::setEconomizerMaximumLimitDewpointTemperature(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitDewpointTemperature, *value);
      }
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerMaximumLimitDewpointTemperature, "");
    }

    boost::optional<openstudio::epmodel::Curve> ControllerOutdoorAir_Impl::electronicEnthalpyLimitCurve() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName);
    }

    bool ControllerOutdoorAir_Impl::setElectronicEnthalpyLimitCurve(const openstudio::epmodel::Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the electronic enthalpy limit curve because it belongs to a different model.");
        return false;
      }

      const auto field = openstudio::Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the electronic enthalpy limit curve because curve type '" << curve.iddObject().type().valueName()
                                                                                       << "' is not accepted by the controller field.");
        return false;
      }
      if (!setPointer(field, curve.handle(), false)) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir", "Failed to set the electronic enthalpy limit curve relationship.");
        return false;
      }
      return true;
    }

    void ControllerOutdoorAir_Impl::resetElectronicEnthalpyLimitCurve() {
      const auto field = openstudio::Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<double> ControllerOutdoorAir_Impl::getEconomizerMinimumLimitDryBulbTemperature() const {
      return getDouble(openstudio::Controller_OutdoorAirFields::EconomizerMinimumLimitDryBulbTemperature);
    }

    bool ControllerOutdoorAir_Impl::setEconomizerMinimumLimitDryBulbTemperature(boost::optional<double> value) {
      if (value) {
        return setDouble(openstudio::Controller_OutdoorAirFields::EconomizerMinimumLimitDryBulbTemperature, *value);
      }
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerMinimumLimitDryBulbTemperature, "");
    }

    std::string ControllerOutdoorAir_Impl::getLockoutType() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::LockoutType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerOutdoorAir_Impl::setLockoutType(const std::string& value) {
      return setString(openstudio::Controller_OutdoorAirFields::LockoutType, value);
    }

    std::string ControllerOutdoorAir_Impl::getMinimumLimitType() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::MinimumLimitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerOutdoorAir_Impl::setMinimumLimitType(const std::string& value) {
      return setString(openstudio::Controller_OutdoorAirFields::MinimumLimitType, value);
    }

    boost::optional<bool> ControllerOutdoorAir_Impl::getHighHumidityControl() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::HighHumidityControl, true);
      if (!value || value->empty()) {
        return boost::none;
      }
      return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
    }

    boost::optional<openstudio::epmodel::ThermalZone> ControllerOutdoorAir_Impl::humidistatControlZone() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(
        openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName);
    }

    bool ControllerOutdoorAir_Impl::setHumidistatControlZone(const openstudio::epmodel::ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir", "Cannot set the humidistat control zone because it belongs to a different model.");
        return false;
      }

      const auto zoneField = openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName;
      const auto highHumidityField = openstudio::Controller_OutdoorAirFields::HighHumidityControl;
      if (!model().canBeTarget(thermalZone.handle(), iddObject().objectLists(zoneField))) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the humidistat control zone because ThermalZone is not accepted by the controller field.");
        return false;
      }

      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      const auto originalZoneTarget = thisController.getTarget(zoneField);
      const auto originalZoneRaw = openstudio::detail::IdfObject_Impl::getString(zoneField, false, true);
      const auto originalHighHumidityRaw = openstudio::detail::IdfObject_Impl::getString(highHumidityField, false, true);

      const bool zoneSet = setPointer(zoneField, thermalZone.handle(), false);
      const bool highHumiditySet = zoneSet && setString(highHumidityField, "Yes");
      if (zoneSet && highHumiditySet) {
        return true;
      }

      bool restored = setPointer(zoneField, originalZoneTarget ? originalZoneTarget->handle() : Handle(), false);
      restored = openstudio::detail::IdfObject_Impl::setString(zoneField, originalZoneRaw.value_or(""), false) && restored;
      restored = openstudio::detail::IdfObject_Impl::setString(highHumidityField, originalHighHumidityRaw.value_or(""), false) && restored;
      OS_ASSERT(restored);
      LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir", "Failed to set the humidistat control zone relationship.");
      return false;
    }

    void ControllerOutdoorAir_Impl::resetHumidistatControlZone() {
      const auto zoneField = openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName;
      const auto highHumidityField = openstudio::Controller_OutdoorAirFields::HighHumidityControl;
      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      const auto originalZoneTarget = thisController.getTarget(zoneField);
      const auto originalZoneRaw = openstudio::detail::IdfObject_Impl::getString(zoneField, false, true);
      const auto originalHighHumidityRaw = openstudio::detail::IdfObject_Impl::getString(highHumidityField, false, true);

      const bool zoneCleared = setPointer(zoneField, Handle(), false);
      const bool rawCleared = zoneCleared && openstudio::detail::IdfObject_Impl::setString(zoneField, "", false);
      const bool highHumidityCleared = rawCleared && setString(highHumidityField, "No");
      if (zoneCleared && rawCleared && highHumidityCleared) {
        return;
      }

      bool restored = setPointer(zoneField, originalZoneTarget ? originalZoneTarget->handle() : Handle(), false);
      restored = openstudio::detail::IdfObject_Impl::setString(zoneField, originalZoneRaw.value_or(""), false) && restored;
      restored = openstudio::detail::IdfObject_Impl::setString(highHumidityField, originalHighHumidityRaw.value_or(""), false) && restored;
      OS_ASSERT(restored);
      OS_ASSERT(false);
    }

    double ControllerOutdoorAir_Impl::getHighHumidityOutdoorAirFlowRatio() const {
      const auto value = getDouble(openstudio::Controller_OutdoorAirFields::HighHumidityOutdoorAirFlowRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerOutdoorAir_Impl::setHighHumidityOutdoorAirFlowRatio(double v) {
      return setDouble(openstudio::Controller_OutdoorAirFields::HighHumidityOutdoorAirFlowRatio, v);
    }

    bool ControllerOutdoorAir_Impl::getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
    }

    bool ControllerOutdoorAir_Impl::setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool v) {
      const bool result = setString(openstudio::Controller_OutdoorAirFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, v ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    boost::optional<std::string> ControllerOutdoorAir_Impl::getHeatRecoveryBypassControlType() const {
      return getString(openstudio::Controller_OutdoorAirFields::HeatRecoveryBypassControlType);
    }

    bool ControllerOutdoorAir_Impl::setHeatRecoveryBypassControlType(const std::string& v) {
      return setString(openstudio::Controller_OutdoorAirFields::HeatRecoveryBypassControlType, v);
    }

    std::string ControllerOutdoorAir_Impl::economizerOperationStaging() const {
      const auto value = getString(openstudio::Controller_OutdoorAirFields::EconomizerOperationStaging, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerOutdoorAir_Impl::setEconomizerOperationStaging(const std::string& v) {
      return setString(openstudio::Controller_OutdoorAirFields::EconomizerOperationStaging, v);
    }

    std::vector<std::string> ControllerOutdoorAir_Impl::economizerControlTypeValues() const {
      return openstudio::epmodel::ControllerOutdoorAir::economizerControlTypeValues();
    }

    std::vector<std::string> ControllerOutdoorAir_Impl::economizerControlActionTypeValues() const {
      return openstudio::epmodel::ControllerOutdoorAir::economizerControlActionTypeValues();
    }

    std::vector<std::string> ControllerOutdoorAir_Impl::lockoutTypeValues() const {
      return openstudio::epmodel::ControllerOutdoorAir::lockoutTypeValues();
    }

    std::vector<std::string> ControllerOutdoorAir_Impl::minimumLimitTypeValues() const {
      return openstudio::epmodel::ControllerOutdoorAir::minimumLimitTypeValues();
    }

    std::vector<std::string> ControllerOutdoorAir_Impl::heatRecoveryBypassControlTypeValues() const {
      return openstudio::epmodel::ControllerOutdoorAir::heatRecoveryBypassControlTypeValues();
    }

    std::vector<std::string> ControllerOutdoorAir_Impl::economizerOperationStagingValues() const {
      return openstudio::epmodel::ControllerOutdoorAir::economizerOperationStagingValues();
    }

    boost::optional<openstudio::epmodel::ControllerMechanicalVentilation> ControllerOutdoorAir_Impl::optionalControllerMechanicalVentilation() const {
      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      const auto observation = openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(thisController);
      if (!observation.canonical || !observation.managedTargetHandle) {
        return boost::none;
      }
      return model().getModelObject<openstudio::epmodel::ControllerMechanicalVentilation>(*observation.managedTargetHandle);
    }

    openstudio::epmodel::ControllerMechanicalVentilation ControllerOutdoorAir_Impl::controllerMechanicalVentilation() const {
      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      const auto observation = openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(thisController);
      if (observation.hasEvidence) {
        if (observation.canonical && observation.managedTargetHandle) {
          auto target = model().getModelObject<openstudio::epmodel::ControllerMechanicalVentilation>(*observation.managedTargetHandle);
          if (target) {
            const auto targetImpl = target->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
            OS_ASSERT(targetImpl);
            if (targetImpl->outdoorAirClaimInspection().exactlyOwnedBy(thisController.handle())) {
              return *target;
            }
          }
        }
        LOG_FREE_AND_THROW("openstudio.epmodel.ControllerOutdoorAir",
                           "Controller:OutdoorAir '" << thisController.nameString()
                                                     << "' has an unresolved, ambiguous, or malformed mechanical ventilation relationship.");
      }

      // Design pattern for epmodel parity:
      // - Canonicalize may synthesize Controller:MechanicalVentilation only when domain requirements warrant it
      //   (eg, zone OA specs that need mechanical ventilation behavior).
      // - This getter creates only from a truly blank relationship and never overwrites persisted evidence.
      auto newController = openstudio::epmodel::ControllerMechanicalVentilation(model());
      if (!const_cast<ControllerOutdoorAir_Impl*>(this)->setControllerMechanicalVentilation(newController)) {
        newController.remove();
        LOG_FREE_AND_THROW("openstudio.epmodel.ControllerOutdoorAir",
                           "Failed to attach a provisional Controller:MechanicalVentilation to Controller:OutdoorAir '" << thisController.nameString()
                                                                                                                        << "'.");
      }
      return newController;
    }

    bool ControllerOutdoorAir_Impl::setControllerMechanicalVentilation(
      const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation) {
      return setControllerMechanicalVentilation(controllerMechanicalVentilation, true);
    }

    bool ControllerOutdoorAir_Impl::setControllerMechanicalVentilation(
      const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation, bool syncRows) {
      if (controllerMechanicalVentilation.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the mechanical ventilation controller because it belongs to a different model.");
        return false;
      }
      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      const auto currentObservation = openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(thisController);
      boost::optional<openstudio::epmodel::ControllerMechanicalVentilation> oldController;
      if (currentObservation.hasEvidence) {
        if (!currentObservation.canonical || !currentObservation.managedTargetHandle) {
          LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                   "Cannot replace the mechanical ventilation controller because the current relationship is malformed.");
          return false;
        }
        oldController = model().getModelObject<openstudio::epmodel::ControllerMechanicalVentilation>(*currentObservation.managedTargetHandle);
        if (!oldController) {
          return false;
        }
        const auto oldImpl = oldController->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
        OS_ASSERT(oldImpl);
        if (!oldImpl->outdoorAirClaimInspection().exactlyOwnedBy(thisController.handle())) {
          LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                   "Cannot replace the mechanical ventilation controller because its current ownership is ambiguous.");
          return false;
        }
        if (*oldController == controllerMechanicalVentilation) {
          return true;
        }
      }

      auto mechanicalVentilationImpl = controllerMechanicalVentilation.getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
      OS_ASSERT(mechanicalVentilationImpl);
      if (!mechanicalVentilationImpl->outdoorAirClaimInspection().unclaimed()) {
        LOG_FREE(Warn, "openstudio.epmodel.ControllerOutdoorAir",
                 "Cannot set the mechanical ventilation controller because it is already claimed or has malformed ownership evidence.");
        return false;
      }

      if (!setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName, controllerMechanicalVentilation.handle(),
                      false)) {
        return false;
      }
      mechanicalVentilationImpl->setTransient(isTransient());
      if (oldController) {
        const auto oldImpl = oldController->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
        OS_ASSERT(oldImpl);
        if (oldImpl->outdoorAirClaimInspection().unclaimed()) {
          // Canonical Model preserves the replaced CMV; clear only EPModel's transient projection state.
          oldImpl->setTransient(false);
        }
      }
      if (syncRows) {
        if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
          if (auto airLoop = oaSystem->airLoopHVAC()) {
            airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
          }
        }
      }
      return true;
    }

    boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> ControllerOutdoorAir_Impl::airLoopHVACOutdoorAirSystem() const {
      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      return findOwningOutdoorAirSystemForCanonicalize(thisController);
    }

    void ControllerOutdoorAir_Impl::doCanonicalize(LoadContext& context) {
      auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();

      {
        const auto field = openstudio::Controller_OutdoorAirFields::MinimumOutdoorAirScheduleName;
        const auto existingTarget = thisController.getTarget(field);
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        auto schedule = existingTarget ? existingTarget->optionalCast<openstudio::epmodel::Schedule>() : boost::none;
        if (schedule) {
          if (!setMinimumOutdoorAirSchedule(*schedule)) {
            resetMinimumOutdoorAirSchedule();
            detail::addLoadWarning(context, "Cleared the incompatible minimum outdoor air schedule from Controller:OutdoorAir '"
                                              + thisController.nameString() + "'.");
          }
        } else if (existingTarget || (raw && !raw->empty())) {
          resetMinimumOutdoorAirSchedule();
          detail::addLoadWarning(context, "Cleared the unresolved minimum outdoor air schedule from Controller:OutdoorAir '"
                                            + thisController.nameString() + "'.");
        }
      }

      {
        const auto field = openstudio::Controller_OutdoorAirFields::MinimumFractionofOutdoorAirScheduleName;
        const auto existingTarget = thisController.getTarget(field);
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        auto schedule = existingTarget ? existingTarget->optionalCast<openstudio::epmodel::Schedule>() : boost::none;
        if (schedule) {
          if (!setMinimumFractionofOutdoorAirSchedule(*schedule)) {
            resetMinimumFractionofOutdoorAirSchedule();
            detail::addLoadWarning(context, "Cleared the incompatible minimum fraction of outdoor air schedule from Controller:OutdoorAir '"
                                              + thisController.nameString() + "'.");
          }
        } else if (existingTarget || (raw && !raw->empty())) {
          resetMinimumFractionofOutdoorAirSchedule();
          detail::addLoadWarning(context, "Cleared the unresolved minimum fraction of outdoor air schedule from Controller:OutdoorAir '"
                                            + thisController.nameString() + "'.");
        }
      }

      {
        const auto field = openstudio::Controller_OutdoorAirFields::MaximumFractionofOutdoorAirScheduleName;
        const auto existingTarget = thisController.getTarget(field);
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        auto schedule = existingTarget ? existingTarget->optionalCast<openstudio::epmodel::Schedule>() : boost::none;
        if (schedule) {
          if (!setMaximumFractionofOutdoorAirSchedule(*schedule)) {
            resetMaximumFractionofOutdoorAirSchedule();
            detail::addLoadWarning(context, "Cleared the incompatible maximum fraction of outdoor air schedule from Controller:OutdoorAir '"
                                              + thisController.nameString() + "'.");
          }
        } else if (existingTarget || (raw && !raw->empty())) {
          resetMaximumFractionofOutdoorAirSchedule();
          detail::addLoadWarning(context, "Cleared the unresolved maximum fraction of outdoor air schedule from Controller:OutdoorAir '"
                                            + thisController.nameString() + "'.");
        }
      }

      {
        const auto field = openstudio::Controller_OutdoorAirFields::TimeofDayEconomizerControlScheduleName;
        const auto existingTarget = thisController.getTarget(field);
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        auto schedule = existingTarget ? existingTarget->optionalCast<openstudio::epmodel::Schedule>() : boost::none;
        if (schedule) {
          if (!setTimeofDayEconomizerControlSchedule(*schedule)) {
            resetTimeofDayEconomizerControlSchedule();
            detail::addLoadWarning(context, "Cleared the incompatible time-of-day economizer control schedule from Controller:OutdoorAir '"
                                              + thisController.nameString() + "'.");
          }
        } else if (existingTarget || (raw && !raw->empty())) {
          resetTimeofDayEconomizerControlSchedule();
          detail::addLoadWarning(context, "Cleared the unresolved time-of-day economizer control schedule from Controller:OutdoorAir '"
                                            + thisController.nameString() + "'.");
        }
      }

      {
        const auto field = openstudio::Controller_OutdoorAirFields::ElectronicEnthalpyLimitCurveName;
        const auto existingTarget = thisController.getTarget(field);
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        const auto curve = existingTarget ? existingTarget->optionalCast<openstudio::epmodel::Curve>() : boost::none;
        if (curve) {
          if (!setElectronicEnthalpyLimitCurve(*curve)) {
            resetElectronicEnthalpyLimitCurve();
            detail::addLoadWarning(context, "Cleared the incompatible electronic enthalpy limit curve from Controller:OutdoorAir '"
                                              + thisController.nameString() + "'.");
          }
        } else if (existingTarget || (raw && !raw->empty())) {
          resetElectronicEnthalpyLimitCurve();
          detail::addLoadWarning(context, "Cleared the unresolved electronic enthalpy limit curve from Controller:OutdoorAir '"
                                            + thisController.nameString() + "'.");
        }
      }

      {
        const auto field = openstudio::Controller_OutdoorAirFields::HumidistatControlZoneName;
        const auto existingTarget = thisController.getTarget(field);
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        const auto zone = existingTarget ? existingTarget->optionalCast<openstudio::epmodel::ThermalZone>() : boost::none;
        const bool highHumidityEnabled = getHighHumidityControl().value_or(false);
        if (zone && model().canBeTarget(zone->handle(), iddObject().objectLists(field))) {
          if (!highHumidityEnabled) {
            OS_ASSERT(setHumidistatControlZone(*zone));
            detail::addLoadInfo(context, "Enabled high humidity control for the existing humidistat zone on Controller:OutdoorAir '"
                                           + thisController.nameString() + "'.");
          }
        } else if (existingTarget || (raw && !raw->empty()) || highHumidityEnabled) {
          resetHumidistatControlZone();
          detail::addLoadWarning(context, "Cleared an incomplete humidistat control relationship from Controller:OutdoorAir '"
                                            + thisController.nameString() + "'.");
        }
      }

      if (!maximumOutdoorAirFlowRate() && !isMaximumOutdoorAirFlowRateAutosized()) {
        autosizeMaximumOutdoorAirFlowRate();
      }
      if (!minimumOutdoorAirFlowRate() && !isMinimumOutdoorAirFlowRateAutosized()) {
        OS_ASSERT(setMinimumOutdoorAirFlowRate(0.0));
      }
      if (getEconomizerControlType().empty()) {
        OS_ASSERT(setEconomizerControlType("NoEconomizer"));
      }
      if (getEconomizerControlActionType().empty()) {
        OS_ASSERT(setEconomizerControlActionType("ModulateFlow"));
      }
      if (getLockoutType().empty()) {
        OS_ASSERT(setLockoutType("NoLockout"));
      }
      if (getMinimumLimitType().empty()) {
        OS_ASSERT(setMinimumLimitType("FixedMinimum"));
      }
      if (!getHighHumidityControl()) {
        OS_ASSERT(setString(openstudio::Controller_OutdoorAirFields::HighHumidityControl, "No"));
      }
      if (!getDouble(openstudio::Controller_OutdoorAirFields::HighHumidityOutdoorAirFlowRatio, true)) {
        OS_ASSERT(setHighHumidityOutdoorAirFlowRatio(1.0));
      }
      if (auto value = getString(openstudio::Controller_OutdoorAirFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, true);
          !value || value->empty()) {
        OS_ASSERT(setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(true));
      }
      if (auto value = getHeatRecoveryBypassControlType(); !value || value->empty()) {
        OS_ASSERT(setHeatRecoveryBypassControlType("BypassWhenWithinEconomizerLimits"));
      }
      if (economizerOperationStaging().empty()) {
        OS_ASSERT(setEconomizerOperationStaging("InterlockedWithMechanicalCooling"));
      }

      if (auto oaSystem = findOwningOutdoorAirSystemForCanonicalize(thisController)) {
        auto equipmentList = oaSystem->getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>(
          openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
        if (equipmentList && !subsetCastVector<openstudio::epmodel::OutdoorAirMixer>(equipmentList->equipment()).empty()) {
          if (oaSystem->airLoopHVACDedicatedOutdoorAirSystem()) {
            if (auto node = oaSystem->outdoorAirModelObject()) {
              OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::ActuatorNodeName, node->handle(), false));
            }
          } else if (auto node = oaSystem->outboardOANode()) {
            OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::ActuatorNodeName, node->handle(), false));
          }
          if (auto node = oaSystem->mixedAirModelObject()) {
            OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::MixedAirNodeName, node->handle(), false));
          }
          if (auto node = oaSystem->reliefAirModelObject()) {
            OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::ReliefAirOutletNodeName, node->handle(), false));
          }
          if (auto node = oaSystem->returnAirModelObject()) {
            OS_ASSERT(setPointer(openstudio::Controller_OutdoorAirFields::ReturnAirNodeName, node->handle(), false));
          }
        }
      }

      constexpr unsigned mechanicalVentilationField = openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName;
      auto observation = openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(thisController);
      boost::optional<openstudio::epmodel::ControllerMechanicalVentilation> observedMechanicalVentilation;
      if (observation.managedTargetHandle) {
        observedMechanicalVentilation =
          model().getModelObject<openstudio::epmodel::ControllerMechanicalVentilation>(*observation.managedTargetHandle);
      } else if (observation.rawTarget && !observation.rawTarget->empty()) {
        for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::ControllerMechanicalVentilation>()) {
          const auto candidateName = candidate.name();
          if (openstudio::toUUID(*observation.rawTarget) == candidate.handle()
              || (candidateName && openstudio::istringEqual(*observation.rawTarget, *candidateName))) {
            if (observedMechanicalVentilation) {
              observedMechanicalVentilation = boost::none;
              break;
            }
            observedMechanicalVentilation = candidate;
          }
        }
      }

      if (observation.hasEvidence && !observation.canonical) {
        std::vector<Handle> malformedClaimants{thisController.handle()};
        if (observedMechanicalVentilation) {
          const auto observedImpl = observedMechanicalVentilation->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
          OS_ASSERT(observedImpl);
          const auto claims = observedImpl->outdoorAirClaimInspection();
          if (!claims.malformedClaimantHandles.empty()) {
            malformedClaimants = claims.malformedClaimantHandles;
          }
        }
        for (const auto& claimantHandle : malformedClaimants) {
          if (auto claimant = model().getModelObject<openstudio::epmodel::ControllerOutdoorAir>(claimantHandle)) {
            OS_ASSERT(openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl::clearOutdoorAirClaimField(*claimant));
            detail::addLoadWarning(context, "Cleared a malformed mechanical ventilation relationship from Controller:OutdoorAir '"
                                              + claimant->nameString() + "'.");
          }
        }
      }

      auto target = optionalControllerMechanicalVentilation();
      if (target) {
        auto targetImpl = target->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
        OS_ASSERT(targetImpl);
        auto claims = targetImpl->outdoorAirClaimInspection();
        if (!claims.hasMalformedClaim && claims.canonicalClaimantHandles.size() > 1u) {
          // Resolve a valid shared import deterministically: the lowest OA-controller
          // handle retains the imported CMV and every later owner receives a full clone.
          for (auto claimantIt = std::next(claims.canonicalClaimantHandles.begin()); claimantIt != claims.canonicalClaimantHandles.end();
               ++claimantIt) {
            auto claimant = model().getModelObject<openstudio::epmodel::ControllerOutdoorAir>(*claimantIt);
            if (!claimant) {
              continue;
            }
            const auto claimantObservation =
              openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(*claimant);
            if (!claimantObservation.canonical || !claimantObservation.managedTargetHandle
                || *claimantObservation.managedTargetHandle != target->handle()) {
              continue;
            }

            auto cloneIdfObject = target->idfObject().clone(false);
            OS_ASSERT(cloneIdfObject.setName(model().nextName(openstudio::IddObjectType::Controller_MechanicalVentilation, true)));
            auto cloneObject = model().addObject(cloneIdfObject);
            auto clone = cloneObject ? cloneObject->optionalCast<openstudio::epmodel::ControllerMechanicalVentilation>() : boost::none;
            auto claimantImpl = claimant->getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>();
            OS_ASSERT(claimantImpl);
            if (!clone || !claimantImpl->setPointer(mechanicalVentilationField, clone->handle(), false)) {
              if (clone) {
                clone->remove();
              }
              detail::addLoadError(context, "Could not split a shared Controller:MechanicalVentilation for Controller:OutdoorAir '"
                                              + claimant->nameString() + "'.");
              continue;
            }

            auto cloneImpl = clone->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
            OS_ASSERT(cloneImpl);
            cloneImpl->setTransient(claimantImpl->isTransient());
            cloneImpl->canonicalize(context);
            detail::addLoadWarning(context, "Cloned shared Controller:MechanicalVentilation '" + target->nameString()
                                              + "' for Controller:OutdoorAir '" + claimant->nameString() + "'.");
          }
          target = optionalControllerMechanicalVentilation();
          if (target) {
            targetImpl = target->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
            OS_ASSERT(targetImpl);
          }
        }
      }

      if (!target && hasServedZoneWithDesignSpecificationOutdoorAir(thisController, context)) {
        auto newController = openstudio::epmodel::ControllerMechanicalVentilation(model());
        if (!setControllerMechanicalVentilation(newController, false)) {
          newController.remove();
          detail::addLoadError(context, "Could not attach a required Controller:MechanicalVentilation to Controller:OutdoorAir '"
                                          + thisController.nameString() + "'.");
        } else {
          target = newController;
          detail::addLoadInfo(context, "Created Controller:MechanicalVentilation '" + newController.nameString() + "' for Controller:OutdoorAir '"
                                         + thisController.nameString() + "' because DesignSpecification:OutdoorAir assignments exist in the model.");
        }
      }

      // Canonical OA policy: an existing CMV is maintained only for its one exact OA-controller claimant.
      // A blank field may synthesize on demand, while malformed persisted evidence is cleared before that decision.
      if (target) {
        auto targetImpl = target->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
        OS_ASSERT(targetImpl);
        if (targetImpl->outdoorAirClaimInspection().exactlyOwnedBy(thisController.handle())) {
          targetImpl->setTransient(isTransient());
          targetImpl->canonicalize(context);
        }
      }
      // Load-time CMV row synchronization belongs to AirLoopHVAC canonicalization,
      // after its required NodeLists and demand topology have been repaired.
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
