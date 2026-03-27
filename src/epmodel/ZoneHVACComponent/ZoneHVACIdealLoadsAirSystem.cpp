/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem.hpp"
#include "ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem_Impl.hpp"

#include "Model.hpp"

#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_IdealLoadsAirSystem_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACIdealLoadsAirSystem::ZoneHVACIdealLoadsAirSystem(const Model& model)
    : ZoneHVACComponent(ZoneHVACIdealLoadsAirSystem::iddObjectType(), model) {
    bool ok = true;
    ok = setHeatingFuelType("DistrictHeatingWater");
    OS_ASSERT(ok);
    ok = setCoolingFuelType("DistrictCooling");
    OS_ASSERT(ok);
  }

  ZoneHVACIdealLoadsAirSystem::ZoneHVACIdealLoadsAirSystem(std::shared_ptr<detail::ZoneHVACIdealLoadsAirSystem_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACIdealLoadsAirSystem::iddObjectType() {
    return IddObjectType::ZoneHVAC_IdealLoadsAirSystem;
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::heatingLimitValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::coolingLimitValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::humidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::demandControlledVentilationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::outdoorAirEconomizerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::heatRecoveryTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::heatingFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelType);
  }

  std::vector<std::string> ZoneHVACIdealLoadsAirSystem::coolingFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelType);
  }

  double ZoneHVACIdealLoadsAirSystem::maximumHeatingSupplyAirTemperature() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->maximumHeatingSupplyAirTemperature();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMaximumHeatingSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMaximumHeatingSupplyAirTemperatureDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMaximumHeatingSupplyAirTemperature(double maximumHeatingSupplyAirTemperature) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMaximumHeatingSupplyAirTemperature(maximumHeatingSupplyAirTemperature);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMaximumHeatingSupplyAirTemperature() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMaximumHeatingSupplyAirTemperature();
  }

  double ZoneHVACIdealLoadsAirSystem::minimumCoolingSupplyAirTemperature() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->minimumCoolingSupplyAirTemperature();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMinimumCoolingSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMinimumCoolingSupplyAirTemperatureDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMinimumCoolingSupplyAirTemperature(double minimumCoolingSupplyAirTemperature) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMinimumCoolingSupplyAirTemperature(minimumCoolingSupplyAirTemperature);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMinimumCoolingSupplyAirTemperature() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMinimumCoolingSupplyAirTemperature();
  }

  double ZoneHVACIdealLoadsAirSystem::maximumHeatingSupplyAirHumidityRatio() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->maximumHeatingSupplyAirHumidityRatio();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMaximumHeatingSupplyAirHumidityRatioDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMaximumHeatingSupplyAirHumidityRatioDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMaximumHeatingSupplyAirHumidityRatio(double maximumHeatingSupplyAirHumidityRatio) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMaximumHeatingSupplyAirHumidityRatio(maximumHeatingSupplyAirHumidityRatio);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMaximumHeatingSupplyAirHumidityRatio() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMaximumHeatingSupplyAirHumidityRatio();
  }

  double ZoneHVACIdealLoadsAirSystem::minimumCoolingSupplyAirHumidityRatio() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->minimumCoolingSupplyAirHumidityRatio();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMinimumCoolingSupplyAirHumidityRatioDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMinimumCoolingSupplyAirHumidityRatioDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMinimumCoolingSupplyAirHumidityRatio(double minimumCoolingSupplyAirHumidityRatio) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMinimumCoolingSupplyAirHumidityRatio(minimumCoolingSupplyAirHumidityRatio);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMinimumCoolingSupplyAirHumidityRatio() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMinimumCoolingSupplyAirHumidityRatio();
  }

  std::string ZoneHVACIdealLoadsAirSystem::heatingLimit() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->heatingLimit();
  }

  bool ZoneHVACIdealLoadsAirSystem::isHeatingLimitDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isHeatingLimitDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setHeatingLimit(const std::string& heatingLimit) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setHeatingLimit(heatingLimit);
  }

  void ZoneHVACIdealLoadsAirSystem::resetHeatingLimit() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetHeatingLimit();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::maximumHeatingAirFlowRate() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->maximumHeatingAirFlowRate();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMaximumHeatingAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMaximumHeatingAirFlowRateAutosized();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMaximumHeatingAirFlowRate(maximumHeatingAirFlowRate);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMaximumHeatingAirFlowRate() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMaximumHeatingAirFlowRate();
  }

  void ZoneHVACIdealLoadsAirSystem::autosizeMaximumHeatingAirFlowRate() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizeMaximumHeatingAirFlowRate();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::autosizedMaximumHeatingAirFlowRate() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizedMaximumHeatingAirFlowRate();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::maximumSensibleHeatingCapacity() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->maximumSensibleHeatingCapacity();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMaximumSensibleHeatingCapacityAutosized() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMaximumSensibleHeatingCapacityAutosized();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMaximumSensibleHeatingCapacity(double maximumSensibleHeatingCapacity) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMaximumSensibleHeatingCapacity(maximumSensibleHeatingCapacity);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMaximumSensibleHeatingCapacity() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMaximumSensibleHeatingCapacity();
  }

  void ZoneHVACIdealLoadsAirSystem::autosizeMaximumSensibleHeatingCapacity() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizeMaximumSensibleHeatingCapacity();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::autosizedMaximumSensibleHeatingCapacity() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizedMaximumSensibleHeatingCapacity();
  }

  std::string ZoneHVACIdealLoadsAirSystem::coolingLimit() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->coolingLimit();
  }

  bool ZoneHVACIdealLoadsAirSystem::isCoolingLimitDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isCoolingLimitDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setCoolingLimit(const std::string& coolingLimit) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setCoolingLimit(coolingLimit);
  }

  void ZoneHVACIdealLoadsAirSystem::resetCoolingLimit() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetCoolingLimit();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::maximumCoolingAirFlowRate() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->maximumCoolingAirFlowRate();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMaximumCoolingAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMaximumCoolingAirFlowRateAutosized();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMaximumCoolingAirFlowRate(maximumCoolingAirFlowRate);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMaximumCoolingAirFlowRate() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMaximumCoolingAirFlowRate();
  }

  void ZoneHVACIdealLoadsAirSystem::autosizeMaximumCoolingAirFlowRate() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizeMaximumCoolingAirFlowRate();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::autosizedMaximumCoolingAirFlowRate() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizedMaximumCoolingAirFlowRate();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::maximumTotalCoolingCapacity() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->maximumTotalCoolingCapacity();
  }

  bool ZoneHVACIdealLoadsAirSystem::isMaximumTotalCoolingCapacityAutosized() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isMaximumTotalCoolingCapacityAutosized();
  }

  bool ZoneHVACIdealLoadsAirSystem::setMaximumTotalCoolingCapacity(double maximumTotalCoolingCapacity) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setMaximumTotalCoolingCapacity(maximumTotalCoolingCapacity);
  }

  void ZoneHVACIdealLoadsAirSystem::resetMaximumTotalCoolingCapacity() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetMaximumTotalCoolingCapacity();
  }

  void ZoneHVACIdealLoadsAirSystem::autosizeMaximumTotalCoolingCapacity() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizeMaximumTotalCoolingCapacity();
  }

  boost::optional<double> ZoneHVACIdealLoadsAirSystem::autosizedMaximumTotalCoolingCapacity() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->autosizedMaximumTotalCoolingCapacity();
  }

  std::string ZoneHVACIdealLoadsAirSystem::dehumidificationControlType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->dehumidificationControlType();
  }

  bool ZoneHVACIdealLoadsAirSystem::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  void ZoneHVACIdealLoadsAirSystem::resetDehumidificationControlType() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetDehumidificationControlType();
  }

  double ZoneHVACIdealLoadsAirSystem::coolingSensibleHeatRatio() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->coolingSensibleHeatRatio();
  }

  bool ZoneHVACIdealLoadsAirSystem::isCoolingSensibleHeatRatioDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isCoolingSensibleHeatRatioDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setCoolingSensibleHeatRatio(double coolingSensibleHeatRatio) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setCoolingSensibleHeatRatio(coolingSensibleHeatRatio);
  }

  void ZoneHVACIdealLoadsAirSystem::resetCoolingSensibleHeatRatio() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetCoolingSensibleHeatRatio();
  }

  std::string ZoneHVACIdealLoadsAirSystem::humidificationControlType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->humidificationControlType();
  }

  bool ZoneHVACIdealLoadsAirSystem::isHumidificationControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isHumidificationControlTypeDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setHumidificationControlType(const std::string& humidificationControlType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setHumidificationControlType(humidificationControlType);
  }

  void ZoneHVACIdealLoadsAirSystem::resetHumidificationControlType() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetHumidificationControlType();
  }

  std::string ZoneHVACIdealLoadsAirSystem::demandControlledVentilationType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->demandControlledVentilationType();
  }

  bool ZoneHVACIdealLoadsAirSystem::isDemandControlledVentilationTypeDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isDemandControlledVentilationTypeDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setDemandControlledVentilationType(const std::string& demandControlledVentilationType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setDemandControlledVentilationType(demandControlledVentilationType);
  }

  void ZoneHVACIdealLoadsAirSystem::resetDemandControlledVentilationType() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetDemandControlledVentilationType();
  }

  std::string ZoneHVACIdealLoadsAirSystem::outdoorAirEconomizerType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->outdoorAirEconomizerType();
  }

  bool ZoneHVACIdealLoadsAirSystem::isOutdoorAirEconomizerTypeDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isOutdoorAirEconomizerTypeDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setOutdoorAirEconomizerType(const std::string& outdoorAirEconomizerType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setOutdoorAirEconomizerType(outdoorAirEconomizerType);
  }

  void ZoneHVACIdealLoadsAirSystem::resetOutdoorAirEconomizerType() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetOutdoorAirEconomizerType();
  }

  std::string ZoneHVACIdealLoadsAirSystem::heatRecoveryType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->heatRecoveryType();
  }

  bool ZoneHVACIdealLoadsAirSystem::isHeatRecoveryTypeDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isHeatRecoveryTypeDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setHeatRecoveryType(const std::string& heatRecoveryType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setHeatRecoveryType(heatRecoveryType);
  }

  void ZoneHVACIdealLoadsAirSystem::resetHeatRecoveryType() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetHeatRecoveryType();
  }

  double ZoneHVACIdealLoadsAirSystem::sensibleHeatRecoveryEffectiveness() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->sensibleHeatRecoveryEffectiveness();
  }

  bool ZoneHVACIdealLoadsAirSystem::isSensibleHeatRecoveryEffectivenessDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isSensibleHeatRecoveryEffectivenessDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setSensibleHeatRecoveryEffectiveness(sensibleHeatRecoveryEffectiveness);
  }

  void ZoneHVACIdealLoadsAirSystem::resetSensibleHeatRecoveryEffectiveness() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetSensibleHeatRecoveryEffectiveness();
  }

  double ZoneHVACIdealLoadsAirSystem::latentHeatRecoveryEffectiveness() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->latentHeatRecoveryEffectiveness();
  }

  bool ZoneHVACIdealLoadsAirSystem::isLatentHeatRecoveryEffectivenessDefaulted() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->isLatentHeatRecoveryEffectivenessDefaulted();
  }

  bool ZoneHVACIdealLoadsAirSystem::setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setLatentHeatRecoveryEffectiveness(latentHeatRecoveryEffectiveness);
  }

  void ZoneHVACIdealLoadsAirSystem::resetLatentHeatRecoveryEffectiveness() {
    getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->resetLatentHeatRecoveryEffectiveness();
  }

  std::string ZoneHVACIdealLoadsAirSystem::heatingFuelType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->heatingFuelType();
  }

  bool ZoneHVACIdealLoadsAirSystem::setHeatingFuelType(const std::string& heatingFuelType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setHeatingFuelType(heatingFuelType);
  }

  std::string ZoneHVACIdealLoadsAirSystem::coolingFuelType() const {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->coolingFuelType();
  }

  bool ZoneHVACIdealLoadsAirSystem::setCoolingFuelType(const std::string& coolingFuelType) {
    return getImpl<detail::ZoneHVACIdealLoadsAirSystem_Impl>()->setCoolingFuelType(coolingFuelType);
  }

  namespace detail {

    unsigned ZoneHVACIdealLoadsAirSystem_Impl::inletPort() const {
      return ZoneHVAC_IdealLoadsAirSystemFields::ZoneSupplyAirNodeName;
    }

    unsigned ZoneHVACIdealLoadsAirSystem_Impl::outletPort() const {
      return ZoneHVAC_IdealLoadsAirSystemFields::ZoneExhaustAirNodeName;
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::maximumHeatingSupplyAirTemperature() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMaximumHeatingSupplyAirTemperatureDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature);
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::minimumCoolingSupplyAirTemperature() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMinimumCoolingSupplyAirTemperatureDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature);
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::maximumHeatingSupplyAirHumidityRatio() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMaximumHeatingSupplyAirHumidityRatioDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio);
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::minimumCoolingSupplyAirHumidityRatio() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMinimumCoolingSupplyAirHumidityRatioDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio);
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::heatingLimit() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isHeatingLimitDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit);
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::maximumHeatingAirFlowRate() const {
      return getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, true);
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMaximumHeatingAirFlowRateAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::maximumSensibleHeatingCapacity() const {
      return getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, true);
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMaximumSensibleHeatingCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::coolingLimit() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isCoolingLimitDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit);
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::maximumCoolingAirFlowRate() const {
      return getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, true);
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMaximumCoolingAirFlowRateAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::maximumTotalCoolingCapacity() const {
      return getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, true);
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isMaximumTotalCoolingCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::dehumidificationControlType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType);
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::coolingSensibleHeatRatio() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isCoolingSensibleHeatRatioDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio);
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::humidificationControlType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isHumidificationControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType);
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::demandControlledVentilationType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isDemandControlledVentilationTypeDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType);
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::outdoorAirEconomizerType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isOutdoorAirEconomizerTypeDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType);
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::heatRecoveryType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isHeatRecoveryTypeDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType);
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::sensibleHeatRecoveryEffectiveness() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isSensibleHeatRecoveryEffectivenessDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness);
    }

    double ZoneHVACIdealLoadsAirSystem_Impl::latentHeatRecoveryEffectiveness() const {
      auto value = getDouble(ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::isLatentHeatRecoveryEffectivenessDefaulted() const {
      return isEmpty(ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness);
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::heatingFuelType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelType, true);
      OS_ASSERT(value);
      return value.get();
    }

    std::string ZoneHVACIdealLoadsAirSystem_Impl::coolingFuelType() const {
      auto value = getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelType, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::autosizedMaximumHeatingAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::autosizedMaximumSensibleHeatingCapacity() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::autosizedMaximumCoolingAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACIdealLoadsAirSystem_Impl::autosizedMaximumTotalCoolingCapacity() const {
      return boost::none;
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMaximumHeatingSupplyAirTemperature(double maximumHeatingSupplyAirTemperature) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature, maximumHeatingSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMaximumHeatingSupplyAirTemperature() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMinimumCoolingSupplyAirTemperature(double minimumCoolingSupplyAirTemperature) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature, minimumCoolingSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMinimumCoolingSupplyAirTemperature() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMaximumHeatingSupplyAirHumidityRatio(double maximumHeatingSupplyAirHumidityRatio) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio, maximumHeatingSupplyAirHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMaximumHeatingSupplyAirHumidityRatio() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMinimumCoolingSupplyAirHumidityRatio(double minimumCoolingSupplyAirHumidityRatio) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio, minimumCoolingSupplyAirHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMinimumCoolingSupplyAirHumidityRatio() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setHeatingLimit(const std::string& heatingLimit) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit, heatingLimit);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetHeatingLimit() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, maximumHeatingAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMaximumHeatingAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, ""));
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::autosizeMaximumHeatingAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, "autosize"));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMaximumSensibleHeatingCapacity(double maximumSensibleHeatingCapacity) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, maximumSensibleHeatingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMaximumSensibleHeatingCapacity() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, ""));
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::autosizeMaximumSensibleHeatingCapacity() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, "autosize"));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setCoolingLimit(const std::string& coolingLimit) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit, coolingLimit);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetCoolingLimit() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, maximumCoolingAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMaximumCoolingAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, ""));
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::autosizeMaximumCoolingAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, "autosize"));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setMaximumTotalCoolingCapacity(double maximumTotalCoolingCapacity) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, maximumTotalCoolingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetMaximumTotalCoolingCapacity() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, ""));
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::autosizeMaximumTotalCoolingCapacity() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, "autosize"));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType, dehumidificationControlType);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setCoolingSensibleHeatRatio(double coolingSensibleHeatRatio) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio, coolingSensibleHeatRatio);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetCoolingSensibleHeatRatio() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setHumidificationControlType(const std::string& humidificationControlType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType, humidificationControlType);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetHumidificationControlType() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setDemandControlledVentilationType(const std::string& demandControlledVentilationType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType, demandControlledVentilationType);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetDemandControlledVentilationType() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setOutdoorAirEconomizerType(const std::string& outdoorAirEconomizerType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType, outdoorAirEconomizerType);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetOutdoorAirEconomizerType() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setHeatRecoveryType(const std::string& heatRecoveryType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType, heatRecoveryType);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetHeatRecoveryType() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness, sensibleHeatRecoveryEffectiveness);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetSensibleHeatRecoveryEffectiveness() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness) {
      const bool result = setDouble(ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness, latentHeatRecoveryEffectiveness);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACIdealLoadsAirSystem_Impl::resetLatentHeatRecoveryEffectiveness() {
      OS_ASSERT(setString(ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness, ""));
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setHeatingFuelType(const std::string& heatingFuelType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelType, heatingFuelType);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACIdealLoadsAirSystem_Impl::setCoolingFuelType(const std::string& coolingFuelType) {
      const bool result = setString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelType, coolingFuelType);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
