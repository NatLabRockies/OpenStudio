/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "ModelObject/AirLoopHVACControllerList.hpp"
#include "ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ModelObject/ControllerMechanicalVentilation.hpp"
#include "ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "Model.hpp"
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

namespace openstudio {
namespace epmodel {

ControllerOutdoorAir::ControllerOutdoorAir(const Model& model) : ParentObject(ControllerOutdoorAir::iddObjectType(), model) {
  auto impl = getImpl<detail::ControllerOutdoorAir_Impl>();
  OS_ASSERT(impl);
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

boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> findOwningOutdoorAirSystemForCanonicalize(
  const openstudio::epmodel::ControllerOutdoorAir& controller) {
  for (const auto& oaSystem : controller.model().getModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
    // Canonicalization path may run before OA-system invariants are fully
    // established on every instance, so use a tolerant lookup here.
    auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
      openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
    if (!controllerList) {
      continue;
    }
    auto oaController = controllerList->optionalControllerOutdoorAir();
    if (oaController && (*oaController == controller)) {
      return oaSystem;
    }
  }
  return boost::none;
}

bool hasServedZoneWithDesignSpecificationOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controller, LoadContext& context) {
  auto oaSystem = findOwningOutdoorAirSystemForCanonicalize(controller);
  if (!oaSystem) {
    return false;
  }

  for (const auto& zone : controller.model().getModelObjects<openstudio::epmodel::ThermalZone>()) {
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
  if (!value) {
    return boost::none;
  }
  return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
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
  return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::ControllerMechanicalVentilation>(
    openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName);
}

openstudio::epmodel::ControllerMechanicalVentilation ControllerOutdoorAir_Impl::controllerMechanicalVentilation() const {
  if (auto result = optionalControllerMechanicalVentilation()) {
    return *result;
  }

  // Design pattern for epmodel parity:
  // - Canonicalize may synthesize Controller:MechanicalVentilation only when domain requirements warrant it
  //   (eg, zone OA specs that need mechanical ventilation behavior).
  // - This getter remains non-throwing for API parity and creates on demand when missing.
  auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
  auto newController = openstudio::epmodel::ControllerMechanicalVentilation(model());
  OS_ASSERT(thisController.setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName, newController.handle()));
  return newController;
}

bool ControllerOutdoorAir_Impl::setControllerMechanicalVentilation(
  const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation) {
  const bool result = setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName,
                                 controllerMechanicalVentilation.handle(), false);
  if (result) {
    if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
      if (auto airLoop = oaSystem->airLoopHVAC()) {
        airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      }
    }
  }
  return result;
}

boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> ControllerOutdoorAir_Impl::airLoopHVACOutdoorAirSystem() const {
  const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
  for (const auto& oaSystem : model().getModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
    // This accessor is used by canonicalization flows (eg CMV rebuild),
    // where other OA systems in the same model may not yet satisfy
    // getControllerOutdoorAir() invariants. Use tolerant relationship
    // lookup here to avoid cross-object canonicalization ordering asserts.
    auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
      openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
    if (!controllerList) {
      continue;
    }
    auto controller = controllerList->optionalControllerOutdoorAir();
    if (controller && (*controller == thisController)) {
      return oaSystem;
    }
  }
  return boost::none;
}

void ControllerOutdoorAir_Impl::doCanonicalize(LoadContext& context) {
  auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
  auto target = optionalControllerMechanicalVentilation();

  if (!target && hasServedZoneWithDesignSpecificationOutdoorAir(thisController, context)) {
    auto newController = openstudio::epmodel::ControllerMechanicalVentilation(model());
    OS_ASSERT(thisController.setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName, newController.handle()));
    target = newController;
    detail::addLoadInfo(context, "Created Controller:MechanicalVentilation '" + newController.nameString() + "' for Controller:OutdoorAir '"
                                   + thisController.nameString() + "' because DesignSpecification:OutdoorAir assignments exist in the model.");
  }

  // Canonical OA policy:
  // - If zone OA assignments exist in the model, CMV is synthesized/maintained at canonicalization.
  // - Otherwise CMV is optional and may still be created on-demand by getter API.
  if (target) {
    target->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->canonicalize(context);
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
