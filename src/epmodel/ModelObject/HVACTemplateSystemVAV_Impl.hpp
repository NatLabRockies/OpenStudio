/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMVAV_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMVAV_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateSystemVAV_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateSystemVAV_Impl() override = default;

  boost::optional<double> supplyFanMaximumFlowRate() const;
  boost::optional<double> supplyFanMinimumFlowRate() const;
  std::string supplyFanPlacement() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string coolingCoilType() const;
  double coolingCoilDesignSetpoint() const;
  std::string heatingCoilType() const;
  double heatingCoilDesignSetpoint() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  std::string preheatCoilType() const;
  double preheatCoilDesignSetpoint() const;
  double gasPreheatCoilEfficiency() const;
  double gasPreheatCoilParasiticElectricLoad() const;
  boost::optional<double> maximumOutdoorAirFlowRate() const;
  boost::optional<double> minimumOutdoorAirFlowRate() const;
  std::string minimumOutdoorAirControlType() const;
  std::string economizerType() const;
  std::string economizerLockout() const;
  boost::optional<double> economizerUpperTemperatureLimit() const;
  boost::optional<double> economizerLowerTemperatureLimit() const;
  boost::optional<double> economizerUpperEnthalpyLimit() const;
  boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
  std::string supplyFanPartLoadPowerCoefficients() const;
  std::string nightCycleControl() const;
  std::string heatRecoveryType() const;
  double sensibleHeatRecoveryEffectiveness() const;
  double latentHeatRecoveryEffectiveness() const;
  std::string coolingCoilSetpointResetType() const;
  std::string heatingCoilSetpointResetType() const;
  std::string dehumidificationControlType() const;
  double dehumidificationSetpoint() const;
  std::string humidifierType() const;
  double humidifierRatedCapacity() const;
  boost::optional<double> humidifierRatedElectricPower() const;
  double humidifierSetpoint() const;
  std::string sizingOption() const;
  bool returnFan() const;
  double returnFanTotalEfficiency() const;
  double returnFanDeltaPressure() const;
  double returnFanMotorEfficiency() const;
  double returnFanMotorinAirStreamFraction() const;
  std::string returnFanPartLoadPowerCoefficients() const;

  bool isSupplyFanMaximumFlowRateDefaulted() const;
  bool isSupplyFanMinimumFlowRateDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingCoilDesignSetpointDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isHeatingCoilDesignSetpointDefaulted() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isPreheatCoilTypeDefaulted() const;
  bool isPreheatCoilDesignSetpointDefaulted() const;
  bool isGasPreheatCoilEfficiencyDefaulted() const;
  bool isGasPreheatCoilParasiticElectricLoadDefaulted() const;
  bool isMaximumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirControlTypeDefaulted() const;
  bool isEconomizerTypeDefaulted() const;
  bool isEconomizerLockoutDefaulted() const;
  bool isEconomizerUpperTemperatureLimitDefaulted() const;
  bool isEconomizerLowerTemperatureLimitDefaulted() const;
  bool isEconomizerUpperEnthalpyLimitDefaulted() const;
  bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
  bool isSupplyFanPartLoadPowerCoefficientsDefaulted() const;
  bool isNightCycleControlDefaulted() const;
  bool isHeatRecoveryTypeDefaulted() const;
  bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
  bool isLatentHeatRecoveryEffectivenessDefaulted() const;
  bool isCoolingCoilSetpointResetTypeDefaulted() const;
  bool isHeatingCoilSetpointResetTypeDefaulted() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool isDehumidificationSetpointDefaulted() const;
  bool isHumidifierTypeDefaulted() const;
  bool isHumidifierRatedCapacityDefaulted() const;
  bool isHumidifierRatedElectricPowerDefaulted() const;
  bool isHumidifierSetpointDefaulted() const;
  bool isSizingOptionDefaulted() const;
  bool isReturnFanDefaulted() const;
  bool isReturnFanTotalEfficiencyDefaulted() const;
  bool isReturnFanDeltaPressureDefaulted() const;
  bool isReturnFanMotorEfficiencyDefaulted() const;
  bool isReturnFanMotorinAirStreamFractionDefaulted() const;
  bool isReturnFanPartLoadPowerCoefficientsDefaulted() const;

  bool isSupplyFanMaximumFlowRateAutosized() const;
  bool isSupplyFanMinimumFlowRateAutosized() const;
  bool isMaximumOutdoorAirFlowRateAutosized() const;
  bool isMinimumOutdoorAirFlowRateAutosized() const;
  bool isHumidifierRatedElectricPowerAutosized() const;

  bool setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate);
  bool setSupplyFanMinimumFlowRate(double supplyFanMinimumFlowRate);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setPreheatCoilType(const std::string& preheatCoilType);
  bool setPreheatCoilDesignSetpoint(double preheatCoilDesignSetpoint);
  bool setGasPreheatCoilEfficiency(double gasPreheatCoilEfficiency);
  bool setGasPreheatCoilParasiticElectricLoad(double gasPreheatCoilParasiticElectricLoad);
  bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirControlType(const std::string& minimumOutdoorAirControlType);
  bool setEconomizerType(const std::string& economizerType);
  bool setEconomizerLockout(const std::string& economizerLockout);
  bool setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit);
  bool setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit);
  bool setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit);
  bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
  bool setSupplyFanPartLoadPowerCoefficients(const std::string& supplyFanPartLoadPowerCoefficients);
  bool setNightCycleControl(const std::string& nightCycleControl);
  bool setHeatRecoveryType(const std::string& heatRecoveryType);
  bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
  bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
  bool setCoolingCoilSetpointResetType(const std::string& coolingCoilSetpointResetType);
  bool setHeatingCoilSetpointResetType(const std::string& heatingCoilSetpointResetType);
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  bool setDehumidificationSetpoint(double dehumidificationSetpoint);
  bool setHumidifierType(const std::string& humidifierType);
  bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
  bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
  bool setHumidifierSetpoint(double humidifierSetpoint);
  bool setSizingOption(const std::string& sizingOption);
  bool setReturnFan(bool returnFan);
  bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
  bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
  bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
  bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);
  bool setReturnFanPartLoadPowerCoefficients(const std::string& returnFanPartLoadPowerCoefficients);

  void resetSupplyFanMaximumFlowRate();
  void resetSupplyFanMinimumFlowRate();
  void resetSupplyFanPlacement();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetSupplyFanMotorinAirStreamFraction();
  void resetCoolingCoilType();
  void resetCoolingCoilDesignSetpoint();
  void resetHeatingCoilType();
  void resetHeatingCoilDesignSetpoint();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetPreheatCoilType();
  void resetPreheatCoilDesignSetpoint();
  void resetGasPreheatCoilEfficiency();
  void resetGasPreheatCoilParasiticElectricLoad();
  void resetMaximumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirControlType();
  void resetEconomizerType();
  void resetEconomizerLockout();
  void resetEconomizerUpperTemperatureLimit();
  void resetEconomizerLowerTemperatureLimit();
  void resetEconomizerUpperEnthalpyLimit();
  void resetEconomizerMaximumLimitDewpointTemperature();
  void resetSupplyFanPartLoadPowerCoefficients();
  void resetNightCycleControl();
  void resetHeatRecoveryType();
  void resetSensibleHeatRecoveryEffectiveness();
  void resetLatentHeatRecoveryEffectiveness();
  void resetCoolingCoilSetpointResetType();
  void resetHeatingCoilSetpointResetType();
  void resetDehumidificationControlType();
  void resetDehumidificationSetpoint();
  void resetHumidifierType();
  void resetHumidifierRatedCapacity();
  void resetHumidifierRatedElectricPower();
  void resetHumidifierSetpoint();
  void resetSizingOption();
  void resetReturnFan();
  void resetReturnFanTotalEfficiency();
  void resetReturnFanDeltaPressure();
  void resetReturnFanMotorEfficiency();
  void resetReturnFanMotorinAirStreamFraction();
  void resetReturnFanPartLoadPowerCoefficients();

  void autosizeSupplyFanMaximumFlowRate();
  void autosizeSupplyFanMinimumFlowRate();
  void autosizeMaximumOutdoorAirFlowRate();
  void autosizeMinimumOutdoorAirFlowRate();
  void autosizeHumidifierRatedElectricPower();

  std::vector<std::string> supplyFanPlacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> heatingCoilTypeValues() const;
  std::vector<std::string> preheatCoilTypeValues() const;
  std::vector<std::string> minimumOutdoorAirControlTypeValues() const;
  std::vector<std::string> economizerTypeValues() const;
  std::vector<std::string> economizerLockoutValues() const;
  std::vector<std::string> supplyFanPartLoadPowerCoefficientsValues() const;
  std::vector<std::string> nightCycleControlValues() const;
  std::vector<std::string> heatRecoveryTypeValues() const;
  std::vector<std::string> coolingCoilSetpointResetTypeValues() const;
  std::vector<std::string> heatingCoilSetpointResetTypeValues() const;
  std::vector<std::string> dehumidificationControlTypeValues() const;
  std::vector<std::string> humidifierTypeValues() const;
  std::vector<std::string> sizingOptionValues() const;
  std::vector<std::string> returnFanPartLoadPowerCoefficientsValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
