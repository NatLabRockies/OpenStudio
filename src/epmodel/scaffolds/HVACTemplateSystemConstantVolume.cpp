/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemConstantVolume.hpp"
#include "HVACTemplateSystemConstantVolume_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateSystemConstantVolume::HVACTemplateSystemConstantVolume(const Model& model)
    : ModelObject(HVACTemplateSystemConstantVolume::iddObjectType(), model) {}

  HVACTemplateSystemConstantVolume::HVACTemplateSystemConstantVolume(std::shared_ptr<detail::HVACTemplateSystemConstantVolume_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateSystemConstantVolume::iddObjectType() {
    return IddObjectType::HVACTemplate_System_ConstantVolume;
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::supplyFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanPlacement);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::coolingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::coolingCoilSetpointControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointControlType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::heatingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::heatingCoilSetpointControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointControlType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::preheatCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::economizerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::nightCycleControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::NightCycleControl);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::heatRecoveryTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::heatRecoveryHeatExchangerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryHeatExchangerType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::heatRecoveryFrostControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryFrostControlType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationControlType);
  }

  std::vector<std::string> HVACTemplateSystemConstantVolume::humidifierTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierType);
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::supplyFanMaximumFlowRate() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->supplyFanMaximumFlowRate();
  }

  double HVACTemplateSystemConstantVolume::supplyFanTotalEfficiency() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->supplyFanTotalEfficiency();
  }

  double HVACTemplateSystemConstantVolume::supplyFanDeltaPressure() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->supplyFanDeltaPressure();
  }

  double HVACTemplateSystemConstantVolume::supplyFanMotorEfficiency() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->supplyFanMotorEfficiency();
  }

  double HVACTemplateSystemConstantVolume::supplyFanMotorinAirStreamFraction() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->supplyFanMotorinAirStreamFraction();
  }

  std::string HVACTemplateSystemConstantVolume::supplyFanPlacement() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->supplyFanPlacement();
  }

  std::string HVACTemplateSystemConstantVolume::coolingCoilType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilType();
  }

  std::string HVACTemplateSystemConstantVolume::coolingCoilSetpointControlType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilSetpointControlType();
  }

  double HVACTemplateSystemConstantVolume::coolingCoilDesignSetpointTemperature() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilDesignSetpointTemperature();
  }

  double HVACTemplateSystemConstantVolume::coolingCoilSetpointatOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilSetpointatOutdoorDryBulbLow();
  }

  double HVACTemplateSystemConstantVolume::coolingCoilResetOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilResetOutdoorDryBulbLow();
  }

  double HVACTemplateSystemConstantVolume::coolingCoilSetpointatOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilSetpointatOutdoorDryBulbHigh();
  }

  double HVACTemplateSystemConstantVolume::coolingCoilResetOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->coolingCoilResetOutdoorDryBulbHigh();
  }

  std::string HVACTemplateSystemConstantVolume::heatingCoilType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilType();
  }

  std::string HVACTemplateSystemConstantVolume::heatingCoilSetpointControlType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilSetpointControlType();
  }

  double HVACTemplateSystemConstantVolume::heatingCoilDesignSetpoint() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilDesignSetpoint();
  }

  double HVACTemplateSystemConstantVolume::heatingCoilSetpointatOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilSetpointatOutdoorDryBulbLow();
  }

  double HVACTemplateSystemConstantVolume::heatingCoilResetOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilResetOutdoorDryBulbLow();
  }

  double HVACTemplateSystemConstantVolume::heatingCoilSetpointatOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilSetpointatOutdoorDryBulbHigh();
  }

  double HVACTemplateSystemConstantVolume::heatingCoilResetOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilResetOutdoorDryBulbHigh();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::heatingCoilCapacity() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatingCoilCapacity();
  }

  double HVACTemplateSystemConstantVolume::gasHeatingCoilEfficiency() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->gasHeatingCoilEfficiency();
  }

  double HVACTemplateSystemConstantVolume::gasHeatingCoilParasiticElectricLoad() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->gasHeatingCoilParasiticElectricLoad();
  }

  std::string HVACTemplateSystemConstantVolume::preheatCoilType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->preheatCoilType();
  }

  double HVACTemplateSystemConstantVolume::preheatCoilDesignSetpoint() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->preheatCoilDesignSetpoint();
  }

  double HVACTemplateSystemConstantVolume::gasPreheatCoilEfficiency() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->gasPreheatCoilEfficiency();
  }

  double HVACTemplateSystemConstantVolume::gasPreheatCoilParasiticElectricLoad() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->gasPreheatCoilParasiticElectricLoad();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->maximumOutdoorAirFlowRate();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::minimumOutdoorAirFlowRate() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->minimumOutdoorAirFlowRate();
  }

  std::string HVACTemplateSystemConstantVolume::economizerType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->economizerType();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::economizerUpperTemperatureLimit() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->economizerUpperTemperatureLimit();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::economizerLowerTemperatureLimit() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->economizerLowerTemperatureLimit();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::economizerUpperEnthalpyLimit() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->economizerUpperEnthalpyLimit();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::economizerMaximumLimitDewpointTemperature() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->economizerMaximumLimitDewpointTemperature();
  }

  std::string HVACTemplateSystemConstantVolume::nightCycleControl() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->nightCycleControl();
  }

  std::string HVACTemplateSystemConstantVolume::heatRecoveryType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatRecoveryType();
  }

  double HVACTemplateSystemConstantVolume::sensibleHeatRecoveryEffectiveness() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->sensibleHeatRecoveryEffectiveness();
  }

  double HVACTemplateSystemConstantVolume::latentHeatRecoveryEffectiveness() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->latentHeatRecoveryEffectiveness();
  }

  std::string HVACTemplateSystemConstantVolume::heatRecoveryHeatExchangerType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatRecoveryHeatExchangerType();
  }

  std::string HVACTemplateSystemConstantVolume::heatRecoveryFrostControlType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->heatRecoveryFrostControlType();
  }

  std::string HVACTemplateSystemConstantVolume::dehumidificationControlType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->dehumidificationControlType();
  }

  double HVACTemplateSystemConstantVolume::dehumidificationRelativeHumiditySetpoint() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->dehumidificationRelativeHumiditySetpoint();
  }

  std::string HVACTemplateSystemConstantVolume::humidifierType() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->humidifierType();
  }

  double HVACTemplateSystemConstantVolume::humidifierRatedCapacity() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->humidifierRatedCapacity();
  }

  boost::optional<double> HVACTemplateSystemConstantVolume::humidifierRatedElectricPower() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->humidifierRatedElectricPower();
  }

  double HVACTemplateSystemConstantVolume::humidifierRelativeHumiditySetpoint() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->humidifierRelativeHumiditySetpoint();
  }

  bool HVACTemplateSystemConstantVolume::returnFan() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->returnFan();
  }

  double HVACTemplateSystemConstantVolume::returnFanTotalEfficiency() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->returnFanTotalEfficiency();
  }

  double HVACTemplateSystemConstantVolume::returnFanDeltaPressure() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->returnFanDeltaPressure();
  }

  double HVACTemplateSystemConstantVolume::returnFanMotorEfficiency() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->returnFanMotorEfficiency();
  }

  double HVACTemplateSystemConstantVolume::returnFanMotorinAirStreamFraction() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->returnFanMotorinAirStreamFraction();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanMaximumFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanMaximumFlowRateDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanTotalEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanTotalEfficiencyDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanDeltaPressureDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanDeltaPressureDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanMotorEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanMotorEfficiencyDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanMotorinAirStreamFractionDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanMotorinAirStreamFractionDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanPlacementDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanPlacementDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilSetpointControlTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilSetpointControlTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilDesignSetpointTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilDesignSetpointTemperatureDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilResetOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilResetOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isCoolingCoilResetOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isCoolingCoilResetOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilSetpointControlTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilSetpointControlTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilDesignSetpointDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilDesignSetpointDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilResetOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilResetOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilResetOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilResetOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilCapacityDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isGasHeatingCoilEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isGasHeatingCoilEfficiencyDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isGasHeatingCoilParasiticElectricLoadDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isGasHeatingCoilParasiticElectricLoadDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isPreheatCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isPreheatCoilTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isPreheatCoilDesignSetpointDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isPreheatCoilDesignSetpointDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isGasPreheatCoilEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isGasPreheatCoilEfficiencyDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isGasPreheatCoilParasiticElectricLoadDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isGasPreheatCoilParasiticElectricLoadDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isMaximumOutdoorAirFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isMaximumOutdoorAirFlowRateDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isMinimumOutdoorAirFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isMinimumOutdoorAirFlowRateDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isEconomizerTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isEconomizerTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isNightCycleControlDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isNightCycleControlDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatRecoveryTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatRecoveryTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSensibleHeatRecoveryEffectivenessDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSensibleHeatRecoveryEffectivenessDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isLatentHeatRecoveryEffectivenessDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isLatentHeatRecoveryEffectivenessDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatRecoveryHeatExchangerTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatRecoveryHeatExchangerTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHeatRecoveryFrostControlTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatRecoveryFrostControlTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isDehumidificationRelativeHumiditySetpointDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isDehumidificationRelativeHumiditySetpointDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHumidifierTypeDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHumidifierTypeDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHumidifierRatedCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHumidifierRatedCapacityDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHumidifierRatedElectricPowerDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHumidifierRatedElectricPowerDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isHumidifierRelativeHumiditySetpointDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHumidifierRelativeHumiditySetpointDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isReturnFanDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isReturnFanDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isReturnFanTotalEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isReturnFanTotalEfficiencyDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isReturnFanDeltaPressureDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isReturnFanDeltaPressureDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isReturnFanMotorEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isReturnFanMotorEfficiencyDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isReturnFanMotorinAirStreamFractionDefaulted() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isReturnFanMotorinAirStreamFractionDefaulted();
  }

  bool HVACTemplateSystemConstantVolume::isSupplyFanMaximumFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isSupplyFanMaximumFlowRateAutosized();
  }

  bool HVACTemplateSystemConstantVolume::isHeatingCoilCapacityAutosized() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHeatingCoilCapacityAutosized();
  }

  bool HVACTemplateSystemConstantVolume::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool HVACTemplateSystemConstantVolume::isMinimumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isMinimumOutdoorAirFlowRateAutosized();
  }

  bool HVACTemplateSystemConstantVolume::isHumidifierRatedElectricPowerAutosized() const {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->isHumidifierRatedElectricPowerAutosized();
  }

  bool HVACTemplateSystemConstantVolume::setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSupplyFanMaximumFlowRate(supplyFanMaximumFlowRate);
  }

  bool HVACTemplateSystemConstantVolume::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSupplyFanTotalEfficiency(supplyFanTotalEfficiency);
  }

  bool HVACTemplateSystemConstantVolume::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSupplyFanDeltaPressure(supplyFanDeltaPressure);
  }

  bool HVACTemplateSystemConstantVolume::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSupplyFanMotorEfficiency(supplyFanMotorEfficiency);
  }

  bool HVACTemplateSystemConstantVolume::setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSupplyFanMotorinAirStreamFraction(supplyFanMotorinAirStreamFraction);
  }

  bool HVACTemplateSystemConstantVolume::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSupplyFanPlacement(supplyFanPlacement);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilType(const std::string& coolingCoilType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilType(coolingCoilType);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilSetpointControlType(const std::string& coolingCoilSetpointControlType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilSetpointControlType(coolingCoilSetpointControlType);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilDesignSetpointTemperature(double coolingCoilDesignSetpointTemperature) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilDesignSetpointTemperature(coolingCoilDesignSetpointTemperature);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilSetpointatOutdoorDryBulbLow(double coolingCoilSetpointatOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilSetpointatOutdoorDryBulbLow(
      coolingCoilSetpointatOutdoorDryBulbLow);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilResetOutdoorDryBulbLow(double coolingCoilResetOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilResetOutdoorDryBulbLow(coolingCoilResetOutdoorDryBulbLow);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilSetpointatOutdoorDryBulbHigh(double coolingCoilSetpointatOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilSetpointatOutdoorDryBulbHigh(
      coolingCoilSetpointatOutdoorDryBulbHigh);
  }

  bool HVACTemplateSystemConstantVolume::setCoolingCoilResetOutdoorDryBulbHigh(double coolingCoilResetOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setCoolingCoilResetOutdoorDryBulbHigh(coolingCoilResetOutdoorDryBulbHigh);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilType(const std::string& heatingCoilType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilType(heatingCoilType);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilSetpointControlType(const std::string& heatingCoilSetpointControlType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilSetpointControlType(heatingCoilSetpointControlType);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilDesignSetpoint(heatingCoilDesignSetpoint);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilSetpointatOutdoorDryBulbLow(double heatingCoilSetpointatOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilSetpointatOutdoorDryBulbLow(
      heatingCoilSetpointatOutdoorDryBulbLow);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilResetOutdoorDryBulbLow(double heatingCoilResetOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilResetOutdoorDryBulbLow(heatingCoilResetOutdoorDryBulbLow);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilSetpointatOutdoorDryBulbHigh(double heatingCoilSetpointatOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilSetpointatOutdoorDryBulbHigh(
      heatingCoilSetpointatOutdoorDryBulbHigh);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilResetOutdoorDryBulbHigh(double heatingCoilResetOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilResetOutdoorDryBulbHigh(heatingCoilResetOutdoorDryBulbHigh);
  }

  bool HVACTemplateSystemConstantVolume::setHeatingCoilCapacity(double heatingCoilCapacity) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatingCoilCapacity(heatingCoilCapacity);
  }

  bool HVACTemplateSystemConstantVolume::setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setGasHeatingCoilEfficiency(gasHeatingCoilEfficiency);
  }

  bool HVACTemplateSystemConstantVolume::setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setGasHeatingCoilParasiticElectricLoad(gasHeatingCoilParasiticElectricLoad);
  }

  bool HVACTemplateSystemConstantVolume::setPreheatCoilType(const std::string& preheatCoilType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setPreheatCoilType(preheatCoilType);
  }

  bool HVACTemplateSystemConstantVolume::setPreheatCoilDesignSetpoint(double preheatCoilDesignSetpoint) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setPreheatCoilDesignSetpoint(preheatCoilDesignSetpoint);
  }

  bool HVACTemplateSystemConstantVolume::setGasPreheatCoilEfficiency(double gasPreheatCoilEfficiency) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setGasPreheatCoilEfficiency(gasPreheatCoilEfficiency);
  }

  bool HVACTemplateSystemConstantVolume::setGasPreheatCoilParasiticElectricLoad(double gasPreheatCoilParasiticElectricLoad) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setGasPreheatCoilParasiticElectricLoad(gasPreheatCoilParasiticElectricLoad);
  }

  bool HVACTemplateSystemConstantVolume::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  bool HVACTemplateSystemConstantVolume::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setMinimumOutdoorAirFlowRate(minimumOutdoorAirFlowRate);
  }

  bool HVACTemplateSystemConstantVolume::setEconomizerType(const std::string& economizerType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setEconomizerType(economizerType);
  }

  bool HVACTemplateSystemConstantVolume::setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setEconomizerUpperTemperatureLimit(economizerUpperTemperatureLimit);
  }

  bool HVACTemplateSystemConstantVolume::setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setEconomizerLowerTemperatureLimit(economizerLowerTemperatureLimit);
  }

  bool HVACTemplateSystemConstantVolume::setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setEconomizerUpperEnthalpyLimit(economizerUpperEnthalpyLimit);
  }

  bool HVACTemplateSystemConstantVolume::setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setEconomizerMaximumLimitDewpointTemperature(
      economizerMaximumLimitDewpointTemperature);
  }

  bool HVACTemplateSystemConstantVolume::setNightCycleControl(const std::string& nightCycleControl) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setNightCycleControl(nightCycleControl);
  }

  bool HVACTemplateSystemConstantVolume::setHeatRecoveryType(const std::string& heatRecoveryType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatRecoveryType(heatRecoveryType);
  }

  bool HVACTemplateSystemConstantVolume::setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setSensibleHeatRecoveryEffectiveness(sensibleHeatRecoveryEffectiveness);
  }

  bool HVACTemplateSystemConstantVolume::setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setLatentHeatRecoveryEffectiveness(latentHeatRecoveryEffectiveness);
  }

  bool HVACTemplateSystemConstantVolume::setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatRecoveryHeatExchangerType(heatRecoveryHeatExchangerType);
  }

  bool HVACTemplateSystemConstantVolume::setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHeatRecoveryFrostControlType(heatRecoveryFrostControlType);
  }

  bool HVACTemplateSystemConstantVolume::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  bool HVACTemplateSystemConstantVolume::setDehumidificationRelativeHumiditySetpoint(double dehumidificationRelativeHumiditySetpoint) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setDehumidificationRelativeHumiditySetpoint(
      dehumidificationRelativeHumiditySetpoint);
  }

  bool HVACTemplateSystemConstantVolume::setHumidifierType(const std::string& humidifierType) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHumidifierType(humidifierType);
  }

  bool HVACTemplateSystemConstantVolume::setHumidifierRatedCapacity(double humidifierRatedCapacity) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHumidifierRatedCapacity(humidifierRatedCapacity);
  }

  bool HVACTemplateSystemConstantVolume::setHumidifierRatedElectricPower(double humidifierRatedElectricPower) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHumidifierRatedElectricPower(humidifierRatedElectricPower);
  }

  bool HVACTemplateSystemConstantVolume::setHumidifierRelativeHumiditySetpoint(double humidifierRelativeHumiditySetpoint) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setHumidifierRelativeHumiditySetpoint(humidifierRelativeHumiditySetpoint);
  }

  bool HVACTemplateSystemConstantVolume::setReturnFan(bool returnFan) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setReturnFan(returnFan);
  }

  bool HVACTemplateSystemConstantVolume::setReturnFanTotalEfficiency(double returnFanTotalEfficiency) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setReturnFanTotalEfficiency(returnFanTotalEfficiency);
  }

  bool HVACTemplateSystemConstantVolume::setReturnFanDeltaPressure(double returnFanDeltaPressure) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setReturnFanDeltaPressure(returnFanDeltaPressure);
  }

  bool HVACTemplateSystemConstantVolume::setReturnFanMotorEfficiency(double returnFanMotorEfficiency) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setReturnFanMotorEfficiency(returnFanMotorEfficiency);
  }

  bool HVACTemplateSystemConstantVolume::setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction) {
    return getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->setReturnFanMotorinAirStreamFraction(returnFanMotorinAirStreamFraction);
  }

  void HVACTemplateSystemConstantVolume::resetSupplyFanMaximumFlowRate() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSupplyFanMaximumFlowRate();
  }

  void HVACTemplateSystemConstantVolume::resetSupplyFanTotalEfficiency() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSupplyFanTotalEfficiency();
  }

  void HVACTemplateSystemConstantVolume::resetSupplyFanDeltaPressure() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSupplyFanDeltaPressure();
  }

  void HVACTemplateSystemConstantVolume::resetSupplyFanMotorEfficiency() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSupplyFanMotorEfficiency();
  }

  void HVACTemplateSystemConstantVolume::resetSupplyFanMotorinAirStreamFraction() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSupplyFanMotorinAirStreamFraction();
  }

  void HVACTemplateSystemConstantVolume::resetSupplyFanPlacement() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSupplyFanPlacement();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilType();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilSetpointControlType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilSetpointControlType();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilDesignSetpointTemperature() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilDesignSetpointTemperature();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilSetpointatOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilSetpointatOutdoorDryBulbLow();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilResetOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilResetOutdoorDryBulbLow();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilSetpointatOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilSetpointatOutdoorDryBulbHigh();
  }

  void HVACTemplateSystemConstantVolume::resetCoolingCoilResetOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetCoolingCoilResetOutdoorDryBulbHigh();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilType();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilSetpointControlType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilSetpointControlType();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilDesignSetpoint() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilDesignSetpoint();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilSetpointatOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilSetpointatOutdoorDryBulbLow();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilResetOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilResetOutdoorDryBulbLow();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilSetpointatOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilSetpointatOutdoorDryBulbHigh();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilResetOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilResetOutdoorDryBulbHigh();
  }

  void HVACTemplateSystemConstantVolume::resetHeatingCoilCapacity() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatingCoilCapacity();
  }

  void HVACTemplateSystemConstantVolume::resetGasHeatingCoilEfficiency() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetGasHeatingCoilEfficiency();
  }

  void HVACTemplateSystemConstantVolume::resetGasHeatingCoilParasiticElectricLoad() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetGasHeatingCoilParasiticElectricLoad();
  }

  void HVACTemplateSystemConstantVolume::resetPreheatCoilType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetPreheatCoilType();
  }

  void HVACTemplateSystemConstantVolume::resetPreheatCoilDesignSetpoint() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetPreheatCoilDesignSetpoint();
  }

  void HVACTemplateSystemConstantVolume::resetGasPreheatCoilEfficiency() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetGasPreheatCoilEfficiency();
  }

  void HVACTemplateSystemConstantVolume::resetGasPreheatCoilParasiticElectricLoad() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetGasPreheatCoilParasiticElectricLoad();
  }

  void HVACTemplateSystemConstantVolume::resetMaximumOutdoorAirFlowRate() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetMaximumOutdoorAirFlowRate();
  }

  void HVACTemplateSystemConstantVolume::resetMinimumOutdoorAirFlowRate() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetMinimumOutdoorAirFlowRate();
  }

  void HVACTemplateSystemConstantVolume::resetEconomizerType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetEconomizerType();
  }

  void HVACTemplateSystemConstantVolume::resetEconomizerUpperTemperatureLimit() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetEconomizerUpperTemperatureLimit();
  }

  void HVACTemplateSystemConstantVolume::resetEconomizerLowerTemperatureLimit() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetEconomizerLowerTemperatureLimit();
  }

  void HVACTemplateSystemConstantVolume::resetEconomizerUpperEnthalpyLimit() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetEconomizerUpperEnthalpyLimit();
  }

  void HVACTemplateSystemConstantVolume::resetEconomizerMaximumLimitDewpointTemperature() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetEconomizerMaximumLimitDewpointTemperature();
  }

  void HVACTemplateSystemConstantVolume::resetNightCycleControl() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetNightCycleControl();
  }

  void HVACTemplateSystemConstantVolume::resetHeatRecoveryType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatRecoveryType();
  }

  void HVACTemplateSystemConstantVolume::resetSensibleHeatRecoveryEffectiveness() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetSensibleHeatRecoveryEffectiveness();
  }

  void HVACTemplateSystemConstantVolume::resetLatentHeatRecoveryEffectiveness() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetLatentHeatRecoveryEffectiveness();
  }

  void HVACTemplateSystemConstantVolume::resetHeatRecoveryHeatExchangerType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatRecoveryHeatExchangerType();
  }

  void HVACTemplateSystemConstantVolume::resetHeatRecoveryFrostControlType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHeatRecoveryFrostControlType();
  }

  void HVACTemplateSystemConstantVolume::resetDehumidificationControlType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetDehumidificationControlType();
  }

  void HVACTemplateSystemConstantVolume::resetDehumidificationRelativeHumiditySetpoint() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetDehumidificationRelativeHumiditySetpoint();
  }

  void HVACTemplateSystemConstantVolume::resetHumidifierType() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHumidifierType();
  }

  void HVACTemplateSystemConstantVolume::resetHumidifierRatedCapacity() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHumidifierRatedCapacity();
  }

  void HVACTemplateSystemConstantVolume::resetHumidifierRatedElectricPower() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHumidifierRatedElectricPower();
  }

  void HVACTemplateSystemConstantVolume::resetHumidifierRelativeHumiditySetpoint() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetHumidifierRelativeHumiditySetpoint();
  }

  void HVACTemplateSystemConstantVolume::resetReturnFan() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetReturnFan();
  }

  void HVACTemplateSystemConstantVolume::resetReturnFanTotalEfficiency() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetReturnFanTotalEfficiency();
  }

  void HVACTemplateSystemConstantVolume::resetReturnFanDeltaPressure() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetReturnFanDeltaPressure();
  }

  void HVACTemplateSystemConstantVolume::resetReturnFanMotorEfficiency() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetReturnFanMotorEfficiency();
  }

  void HVACTemplateSystemConstantVolume::resetReturnFanMotorinAirStreamFraction() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->resetReturnFanMotorinAirStreamFraction();
  }

  void HVACTemplateSystemConstantVolume::autosizeSupplyFanMaximumFlowRate() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->autosizeSupplyFanMaximumFlowRate();
  }

  void HVACTemplateSystemConstantVolume::autosizeHeatingCoilCapacity() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->autosizeHeatingCoilCapacity();
  }

  void HVACTemplateSystemConstantVolume::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  void HVACTemplateSystemConstantVolume::autosizeMinimumOutdoorAirFlowRate() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->autosizeMinimumOutdoorAirFlowRate();
  }

  void HVACTemplateSystemConstantVolume::autosizeHumidifierRatedElectricPower() {
    getImpl<detail::HVACTemplateSystemConstantVolume_Impl>()->autosizeHumidifierRatedElectricPower();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::supplyFanMaximumFlowRate() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMaximumFlowRate, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanMaximumFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMaximumFlowRate);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanMaximumFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMaximumFlowRate, supplyFanMaximumFlowRate);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSupplyFanMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMaximumFlowRate, ""));
    }

    void HVACTemplateSystemConstantVolume_Impl::autosizeSupplyFanMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMaximumFlowRate, "autosize"));
    }

    double HVACTemplateSystemConstantVolume_Impl::supplyFanTotalEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanTotalEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanTotalEfficiency);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanTotalEfficiency, supplyFanTotalEfficiency);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSupplyFanTotalEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanTotalEfficiency, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::supplyFanDeltaPressure() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanDeltaPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanDeltaPressureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanDeltaPressure);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanDeltaPressure, supplyFanDeltaPressure);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSupplyFanDeltaPressure() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanDeltaPressure, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::supplyFanMotorEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorEfficiency);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorEfficiency, supplyFanMotorEfficiency);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSupplyFanMotorEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorEfficiency, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::supplyFanMotorinAirStreamFraction() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorinAirStreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanMotorinAirStreamFractionDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorinAirStreamFraction);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorinAirStreamFraction, supplyFanMotorinAirStreamFraction);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSupplyFanMotorinAirStreamFraction() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanMotorinAirStreamFraction, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::supplyFanPlacement() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSupplyFanPlacementDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanPlacement);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanPlacement, supplyFanPlacement);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSupplyFanPlacement() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanPlacement, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::coolingCoilType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilType(const std::string& coolingCoilType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilType, coolingCoilType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilType, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::coolingCoilSetpointControlType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilSetpointControlTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointControlType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilSetpointControlType(const std::string& coolingCoilSetpointControlType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointControlType, coolingCoilSetpointControlType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilSetpointControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointControlType, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::coolingCoilDesignSetpointTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilDesignSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilDesignSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilDesignSetpointTemperature);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilDesignSetpointTemperature(double coolingCoilDesignSetpointTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilDesignSetpointTemperature, coolingCoilDesignSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilDesignSetpointTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilDesignSetpointTemperature, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::coolingCoilSetpointatOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbLow);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilSetpointatOutdoorDryBulbLow(double coolingCoilSetpointatOutdoorDryBulbLow) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbLow,
                                    coolingCoilSetpointatOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilSetpointatOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbLow, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::coolingCoilResetOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilResetOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbLow);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilResetOutdoorDryBulbLow(double coolingCoilResetOutdoorDryBulbLow) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbLow, coolingCoilResetOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilResetOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbLow, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::coolingCoilSetpointatOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbHigh);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilSetpointatOutdoorDryBulbHigh(double coolingCoilSetpointatOutdoorDryBulbHigh) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbHigh,
                                    coolingCoilSetpointatOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilSetpointatOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointatOutdoorDryBulbHigh, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::coolingCoilResetOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isCoolingCoilResetOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbHigh);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setCoolingCoilResetOutdoorDryBulbHigh(double coolingCoilResetOutdoorDryBulbHigh) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbHigh, coolingCoilResetOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetCoolingCoilResetOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilResetOutdoorDryBulbHigh, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::heatingCoilType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilType(const std::string& heatingCoilType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilType, heatingCoilType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilType, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::heatingCoilSetpointControlType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilSetpointControlTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointControlType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilSetpointControlType(const std::string& heatingCoilSetpointControlType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointControlType, heatingCoilSetpointControlType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilSetpointControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointControlType, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::heatingCoilDesignSetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilDesignSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilDesignSetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilDesignSetpoint);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilDesignSetpoint, heatingCoilDesignSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilDesignSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilDesignSetpoint, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::heatingCoilSetpointatOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbLow);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilSetpointatOutdoorDryBulbLow(double heatingCoilSetpointatOutdoorDryBulbLow) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbLow,
                                    heatingCoilSetpointatOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilSetpointatOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbLow, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::heatingCoilResetOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilResetOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbLow);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilResetOutdoorDryBulbLow(double heatingCoilResetOutdoorDryBulbLow) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbLow, heatingCoilResetOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilResetOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbLow, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::heatingCoilSetpointatOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbHigh);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilSetpointatOutdoorDryBulbHigh(double heatingCoilSetpointatOutdoorDryBulbHigh) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbHigh,
                                    heatingCoilSetpointatOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilSetpointatOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointatOutdoorDryBulbHigh, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::heatingCoilResetOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilResetOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbHigh);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilResetOutdoorDryBulbHigh(double heatingCoilResetOutdoorDryBulbHigh) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbHigh, heatingCoilResetOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilResetOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilResetOutdoorDryBulbHigh, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::heatingCoilCapacity() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilCapacity, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilCapacity);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatingCoilCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatingCoilCapacity(double heatingCoilCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilCapacity, heatingCoilCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatingCoilCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilCapacity, ""));
    }

    void HVACTemplateSystemConstantVolume_Impl::autosizeHeatingCoilCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilCapacity, "autosize"));
    }

    double HVACTemplateSystemConstantVolume_Impl::gasHeatingCoilEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isGasHeatingCoilEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilEfficiency);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilEfficiency, gasHeatingCoilEfficiency);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetGasHeatingCoilEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilEfficiency, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::gasHeatingCoilParasiticElectricLoad() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isGasHeatingCoilParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilParasiticElectricLoad);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilParasiticElectricLoad,
                       gasHeatingCoilParasiticElectricLoad);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetGasHeatingCoilParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::GasHeatingCoilParasiticElectricLoad, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::preheatCoilType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isPreheatCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setPreheatCoilType(const std::string& preheatCoilType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilType, preheatCoilType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetPreheatCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilType, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::preheatCoilDesignSetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilDesignSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isPreheatCoilDesignSetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilDesignSetpoint);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setPreheatCoilDesignSetpoint(double preheatCoilDesignSetpoint) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilDesignSetpoint, preheatCoilDesignSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetPreheatCoilDesignSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilDesignSetpoint, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::gasPreheatCoilEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isGasPreheatCoilEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilEfficiency);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setGasPreheatCoilEfficiency(double gasPreheatCoilEfficiency) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilEfficiency, gasPreheatCoilEfficiency);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetGasPreheatCoilEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilEfficiency, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::gasPreheatCoilParasiticElectricLoad() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isGasPreheatCoilParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilParasiticElectricLoad);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setGasPreheatCoilParasiticElectricLoad(double gasPreheatCoilParasiticElectricLoad) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilParasiticElectricLoad,
                       gasPreheatCoilParasiticElectricLoad);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetGasPreheatCoilParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::GasPreheatCoilParasiticElectricLoad, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::MaximumOutdoorAirFlowRate, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isMaximumOutdoorAirFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::MaximumOutdoorAirFlowRate);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateSystemConstantVolume_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::MaximumOutdoorAirFlowRate, ""));
    }

    void HVACTemplateSystemConstantVolume_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::minimumOutdoorAirFlowRate() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::MinimumOutdoorAirFlowRate, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isMinimumOutdoorAirFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::MinimumOutdoorAirFlowRate);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isMinimumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::MinimumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateSystemConstantVolume_Impl::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::MinimumOutdoorAirFlowRate, minimumOutdoorAirFlowRate);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::MinimumOutdoorAirFlowRate, ""));
    }

    void HVACTemplateSystemConstantVolume_Impl::autosizeMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::MinimumOutdoorAirFlowRate, "autosize"));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::economizerType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isEconomizerTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setEconomizerType(const std::string& economizerType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerType, economizerType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetEconomizerType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerType, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::economizerUpperTemperatureLimit() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerUpperTemperatureLimit, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerUpperTemperatureLimit, economizerUpperTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetEconomizerUpperTemperatureLimit() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerUpperTemperatureLimit, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::economizerLowerTemperatureLimit() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerLowerTemperatureLimit, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit) {
      const bool result =
        setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerLowerTemperatureLimit, economizerLowerTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetEconomizerLowerTemperatureLimit() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerLowerTemperatureLimit, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::economizerUpperEnthalpyLimit() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerUpperEnthalpyLimit, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerUpperEnthalpyLimit, economizerUpperEnthalpyLimit);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetEconomizerUpperEnthalpyLimit() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerUpperEnthalpyLimit, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::economizerMaximumLimitDewpointTemperature() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerMaximumLimitDewpointTemperature, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature) {
      const bool result = setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerMaximumLimitDewpointTemperature,
                                    economizerMaximumLimitDewpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetEconomizerMaximumLimitDewpointTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerMaximumLimitDewpointTemperature, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::nightCycleControl() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::NightCycleControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isNightCycleControlDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::NightCycleControl);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setNightCycleControl(const std::string& nightCycleControl) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::NightCycleControl, nightCycleControl);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetNightCycleControl() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::NightCycleControl, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::heatRecoveryType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatRecoveryTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatRecoveryType(const std::string& heatRecoveryType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryType, heatRecoveryType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatRecoveryType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryType, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::sensibleHeatRecoveryEffectiveness() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SensibleHeatRecoveryEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isSensibleHeatRecoveryEffectivenessDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::SensibleHeatRecoveryEffectiveness);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::SensibleHeatRecoveryEffectiveness, sensibleHeatRecoveryEffectiveness);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetSensibleHeatRecoveryEffectiveness() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::SensibleHeatRecoveryEffectiveness, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::latentHeatRecoveryEffectiveness() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::LatentHeatRecoveryEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isLatentHeatRecoveryEffectivenessDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::LatentHeatRecoveryEffectiveness);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::LatentHeatRecoveryEffectiveness, latentHeatRecoveryEffectiveness);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetLatentHeatRecoveryEffectiveness() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::LatentHeatRecoveryEffectiveness, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::heatRecoveryHeatExchangerType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryHeatExchangerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatRecoveryHeatExchangerTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryHeatExchangerType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryHeatExchangerType, heatRecoveryHeatExchangerType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatRecoveryHeatExchangerType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryHeatExchangerType, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::heatRecoveryFrostControlType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryFrostControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHeatRecoveryFrostControlTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryFrostControlType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryFrostControlType, heatRecoveryFrostControlType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHeatRecoveryFrostControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryFrostControlType, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::dehumidificationControlType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationControlType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationControlType, dehumidificationControlType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationControlType, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::dehumidificationRelativeHumiditySetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationRelativeHumiditySetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isDehumidificationRelativeHumiditySetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationRelativeHumiditySetpoint);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setDehumidificationRelativeHumiditySetpoint(double dehumidificationRelativeHumiditySetpoint) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationRelativeHumiditySetpoint,
                       dehumidificationRelativeHumiditySetpoint);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetDehumidificationRelativeHumiditySetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationRelativeHumiditySetpoint, ""));
    }

    std::string HVACTemplateSystemConstantVolume_Impl::humidifierType() const {
      auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHumidifierTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierType);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHumidifierType(const std::string& humidifierType) {
      return setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierType, humidifierType);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHumidifierType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierType, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::humidifierRatedCapacity() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHumidifierRatedCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedCapacity);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHumidifierRatedCapacity(double humidifierRatedCapacity) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedCapacity, humidifierRatedCapacity);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHumidifierRatedCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedCapacity, ""));
    }

    boost::optional<double> HVACTemplateSystemConstantVolume_Impl::humidifierRatedElectricPower() const {
      return getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedElectricPower, true);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHumidifierRatedElectricPowerDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedElectricPower);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHumidifierRatedElectricPowerAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedElectricPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHumidifierRatedElectricPower(double humidifierRatedElectricPower) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedElectricPower, humidifierRatedElectricPower);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHumidifierRatedElectricPower() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedElectricPower, ""));
    }

    void HVACTemplateSystemConstantVolume_Impl::autosizeHumidifierRatedElectricPower() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRatedElectricPower, "autosize"));
    }

    double HVACTemplateSystemConstantVolume_Impl::humidifierRelativeHumiditySetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRelativeHumiditySetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isHumidifierRelativeHumiditySetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRelativeHumiditySetpoint);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setHumidifierRelativeHumiditySetpoint(double humidifierRelativeHumiditySetpoint) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRelativeHumiditySetpoint, humidifierRelativeHumiditySetpoint);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetHumidifierRelativeHumiditySetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierRelativeHumiditySetpoint, ""));
    }

    bool HVACTemplateSystemConstantVolume_Impl::returnFan() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFan);
    }

    bool HVACTemplateSystemConstantVolume_Impl::isReturnFanDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFan);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setReturnFan(bool returnFan) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFan, returnFan);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateSystemConstantVolume_Impl::resetReturnFan() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFan, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::returnFanTotalEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isReturnFanTotalEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanTotalEfficiency);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setReturnFanTotalEfficiency(double returnFanTotalEfficiency) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanTotalEfficiency, returnFanTotalEfficiency);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetReturnFanTotalEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanTotalEfficiency, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::returnFanDeltaPressure() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanDeltaPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isReturnFanDeltaPressureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanDeltaPressure);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setReturnFanDeltaPressure(double returnFanDeltaPressure) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanDeltaPressure, returnFanDeltaPressure);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetReturnFanDeltaPressure() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanDeltaPressure, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::returnFanMotorEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isReturnFanMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorEfficiency);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setReturnFanMotorEfficiency(double returnFanMotorEfficiency) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorEfficiency, returnFanMotorEfficiency);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetReturnFanMotorEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorEfficiency, ""));
    }

    double HVACTemplateSystemConstantVolume_Impl::returnFanMotorinAirStreamFraction() const {
      auto value = getDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorinAirStreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateSystemConstantVolume_Impl::isReturnFanMotorinAirStreamFractionDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorinAirStreamFraction);
    }

    bool HVACTemplateSystemConstantVolume_Impl::setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction) {
      return setDouble(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorinAirStreamFraction, returnFanMotorinAirStreamFraction);
    }

    void HVACTemplateSystemConstantVolume_Impl::resetReturnFanMotorinAirStreamFraction() {
      OS_ASSERT(setString(openstudio::HVACTemplate_System_ConstantVolumeFields::ReturnFanMotorinAirStreamFraction, ""));
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::supplyFanPlacementValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::SupplyFanPlacement);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::coolingCoilTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::coolingCoilSetpointControlTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::CoolingCoilSetpointControlType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::heatingCoilTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::heatingCoilSetpointControlTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::HeatingCoilSetpointControlType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::preheatCoilTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::PreheatCoilType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::economizerTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::EconomizerType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::nightCycleControlValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::NightCycleControl);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::heatRecoveryTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::heatRecoveryHeatExchangerTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryHeatExchangerType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::heatRecoveryFrostControlTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::HeatRecoveryFrostControlType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::dehumidificationControlTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::DehumidificationControlType);
    }

    std::vector<std::string> HVACTemplateSystemConstantVolume_Impl::humidifierTypeValues() const {
      return getIddKeyNames(iddObject(), openstudio::HVACTemplate_System_ConstantVolumeFields::HumidifierType);
    }
  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
