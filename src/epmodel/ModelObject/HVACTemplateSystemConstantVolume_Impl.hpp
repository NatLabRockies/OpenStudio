/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMCONSTANTVOLUME_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMCONSTANTVOLUME_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateSystemConstantVolume_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateSystemConstantVolume_Impl() override = default;

  boost::optional<double> supplyFanMaximumFlowRate() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string supplyFanPlacement() const;
  std::string coolingCoilType() const;
  std::string coolingCoilSetpointControlType() const;
  double coolingCoilDesignSetpointTemperature() const;
  double coolingCoilSetpointatOutdoorDryBulbLow() const;
  double coolingCoilResetOutdoorDryBulbLow() const;
  double coolingCoilSetpointatOutdoorDryBulbHigh() const;
  double coolingCoilResetOutdoorDryBulbHigh() const;
  std::string heatingCoilType() const;
  std::string heatingCoilSetpointControlType() const;
  double heatingCoilDesignSetpoint() const;
  double heatingCoilSetpointatOutdoorDryBulbLow() const;
  double heatingCoilResetOutdoorDryBulbLow() const;
  double heatingCoilSetpointatOutdoorDryBulbHigh() const;
  double heatingCoilResetOutdoorDryBulbHigh() const;
  boost::optional<double> heatingCoilCapacity() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  std::string preheatCoilType() const;
  double preheatCoilDesignSetpoint() const;
  double gasPreheatCoilEfficiency() const;
  double gasPreheatCoilParasiticElectricLoad() const;
  boost::optional<double> maximumOutdoorAirFlowRate() const;
  boost::optional<double> minimumOutdoorAirFlowRate() const;
  std::string economizerType() const;
  boost::optional<double> economizerUpperTemperatureLimit() const;
  boost::optional<double> economizerLowerTemperatureLimit() const;
  boost::optional<double> economizerUpperEnthalpyLimit() const;
  boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
  std::string nightCycleControl() const;
  std::string heatRecoveryType() const;
  double sensibleHeatRecoveryEffectiveness() const;
  double latentHeatRecoveryEffectiveness() const;
  std::string heatRecoveryHeatExchangerType() const;
  std::string heatRecoveryFrostControlType() const;
  std::string dehumidificationControlType() const;
  double dehumidificationRelativeHumiditySetpoint() const;
  std::string humidifierType() const;
  double humidifierRatedCapacity() const;
  boost::optional<double> humidifierRatedElectricPower() const;
  double humidifierRelativeHumiditySetpoint() const;
  bool returnFan() const;
  double returnFanTotalEfficiency() const;
  double returnFanDeltaPressure() const;
  double returnFanMotorEfficiency() const;
  double returnFanMotorinAirStreamFraction() const;

  bool isSupplyFanMaximumFlowRateDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingCoilSetpointControlTypeDefaulted() const;
  bool isCoolingCoilDesignSetpointTemperatureDefaulted() const;
  bool isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
  bool isCoolingCoilResetOutdoorDryBulbLowDefaulted() const;
  bool isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
  bool isCoolingCoilResetOutdoorDryBulbHighDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isHeatingCoilSetpointControlTypeDefaulted() const;
  bool isHeatingCoilDesignSetpointDefaulted() const;
  bool isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
  bool isHeatingCoilResetOutdoorDryBulbLowDefaulted() const;
  bool isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
  bool isHeatingCoilResetOutdoorDryBulbHighDefaulted() const;
  bool isHeatingCoilCapacityDefaulted() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isPreheatCoilTypeDefaulted() const;
  bool isPreheatCoilDesignSetpointDefaulted() const;
  bool isGasPreheatCoilEfficiencyDefaulted() const;
  bool isGasPreheatCoilParasiticElectricLoadDefaulted() const;
  bool isMaximumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirFlowRateDefaulted() const;
  bool isEconomizerTypeDefaulted() const;
  bool isNightCycleControlDefaulted() const;
  bool isHeatRecoveryTypeDefaulted() const;
  bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
  bool isLatentHeatRecoveryEffectivenessDefaulted() const;
  bool isHeatRecoveryHeatExchangerTypeDefaulted() const;
  bool isHeatRecoveryFrostControlTypeDefaulted() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool isDehumidificationRelativeHumiditySetpointDefaulted() const;
  bool isHumidifierTypeDefaulted() const;
  bool isHumidifierRatedCapacityDefaulted() const;
  bool isHumidifierRatedElectricPowerDefaulted() const;
  bool isHumidifierRelativeHumiditySetpointDefaulted() const;
  bool isReturnFanDefaulted() const;
  bool isReturnFanTotalEfficiencyDefaulted() const;
  bool isReturnFanDeltaPressureDefaulted() const;
  bool isReturnFanMotorEfficiencyDefaulted() const;
  bool isReturnFanMotorinAirStreamFractionDefaulted() const;
  bool isSupplyFanMaximumFlowRateAutosized() const;
  bool isHeatingCoilCapacityAutosized() const;
  bool isMaximumOutdoorAirFlowRateAutosized() const;
  bool isMinimumOutdoorAirFlowRateAutosized() const;
  bool isHumidifierRatedElectricPowerAutosized() const;

  bool setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingCoilSetpointControlType(const std::string& coolingCoilSetpointControlType);
  bool setCoolingCoilDesignSetpointTemperature(double coolingCoilDesignSetpointTemperature);
  bool setCoolingCoilSetpointatOutdoorDryBulbLow(double coolingCoilSetpointatOutdoorDryBulbLow);
  bool setCoolingCoilResetOutdoorDryBulbLow(double coolingCoilResetOutdoorDryBulbLow);
  bool setCoolingCoilSetpointatOutdoorDryBulbHigh(double coolingCoilSetpointatOutdoorDryBulbHigh);
  bool setCoolingCoilResetOutdoorDryBulbHigh(double coolingCoilResetOutdoorDryBulbHigh);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingCoilSetpointControlType(const std::string& heatingCoilSetpointControlType);
  bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
  bool setHeatingCoilSetpointatOutdoorDryBulbLow(double heatingCoilSetpointatOutdoorDryBulbLow);
  bool setHeatingCoilResetOutdoorDryBulbLow(double heatingCoilResetOutdoorDryBulbLow);
  bool setHeatingCoilSetpointatOutdoorDryBulbHigh(double heatingCoilSetpointatOutdoorDryBulbHigh);
  bool setHeatingCoilResetOutdoorDryBulbHigh(double heatingCoilResetOutdoorDryBulbHigh);
  bool setHeatingCoilCapacity(double heatingCoilCapacity);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setPreheatCoilType(const std::string& preheatCoilType);
  bool setPreheatCoilDesignSetpoint(double preheatCoilDesignSetpoint);
  bool setGasPreheatCoilEfficiency(double gasPreheatCoilEfficiency);
  bool setGasPreheatCoilParasiticElectricLoad(double gasPreheatCoilParasiticElectricLoad);
  bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
  bool setEconomizerType(const std::string& economizerType);
  bool setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit);
  bool setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit);
  bool setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit);
  bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
  bool setNightCycleControl(const std::string& nightCycleControl);
  bool setHeatRecoveryType(const std::string& heatRecoveryType);
  bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
  bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
  bool setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType);
  bool setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType);
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  bool setDehumidificationRelativeHumiditySetpoint(double dehumidificationRelativeHumiditySetpoint);
  bool setHumidifierType(const std::string& humidifierType);
  bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
  bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
  bool setHumidifierRelativeHumiditySetpoint(double humidifierRelativeHumiditySetpoint);
  bool setReturnFan(bool returnFan);
  bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
  bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
  bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
  bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);

  void resetSupplyFanMaximumFlowRate();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetSupplyFanMotorinAirStreamFraction();
  void resetSupplyFanPlacement();
  void resetCoolingCoilType();
  void resetCoolingCoilSetpointControlType();
  void resetCoolingCoilDesignSetpointTemperature();
  void resetCoolingCoilSetpointatOutdoorDryBulbLow();
  void resetCoolingCoilResetOutdoorDryBulbLow();
  void resetCoolingCoilSetpointatOutdoorDryBulbHigh();
  void resetCoolingCoilResetOutdoorDryBulbHigh();
  void resetHeatingCoilType();
  void resetHeatingCoilSetpointControlType();
  void resetHeatingCoilDesignSetpoint();
  void resetHeatingCoilSetpointatOutdoorDryBulbLow();
  void resetHeatingCoilResetOutdoorDryBulbLow();
  void resetHeatingCoilSetpointatOutdoorDryBulbHigh();
  void resetHeatingCoilResetOutdoorDryBulbHigh();
  void resetHeatingCoilCapacity();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetPreheatCoilType();
  void resetPreheatCoilDesignSetpoint();
  void resetGasPreheatCoilEfficiency();
  void resetGasPreheatCoilParasiticElectricLoad();
  void resetMaximumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirFlowRate();
  void resetEconomizerType();
  void resetEconomizerUpperTemperatureLimit();
  void resetEconomizerLowerTemperatureLimit();
  void resetEconomizerUpperEnthalpyLimit();
  void resetEconomizerMaximumLimitDewpointTemperature();
  void resetNightCycleControl();
  void resetHeatRecoveryType();
  void resetSensibleHeatRecoveryEffectiveness();
  void resetLatentHeatRecoveryEffectiveness();
  void resetHeatRecoveryHeatExchangerType();
  void resetHeatRecoveryFrostControlType();
  void resetDehumidificationControlType();
  void resetDehumidificationRelativeHumiditySetpoint();
  void resetHumidifierType();
  void resetHumidifierRatedCapacity();
  void resetHumidifierRatedElectricPower();
  void resetHumidifierRelativeHumiditySetpoint();
  void resetReturnFan();
  void resetReturnFanTotalEfficiency();
  void resetReturnFanDeltaPressure();
  void resetReturnFanMotorEfficiency();
  void resetReturnFanMotorinAirStreamFraction();
  void autosizeSupplyFanMaximumFlowRate();
  void autosizeHeatingCoilCapacity();
  void autosizeMaximumOutdoorAirFlowRate();
  void autosizeMinimumOutdoorAirFlowRate();
  void autosizeHumidifierRatedElectricPower();

  std::vector<std::string> supplyFanPlacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> coolingCoilSetpointControlTypeValues() const;
  std::vector<std::string> heatingCoilTypeValues() const;
  std::vector<std::string> heatingCoilSetpointControlTypeValues() const;
  std::vector<std::string> preheatCoilTypeValues() const;
  std::vector<std::string> economizerTypeValues() const;
  std::vector<std::string> nightCycleControlValues() const;
  std::vector<std::string> heatRecoveryTypeValues() const;
  std::vector<std::string> heatRecoveryHeatExchangerTypeValues() const;
  std::vector<std::string> heatRecoveryFrostControlTypeValues() const;
  std::vector<std::string> dehumidificationControlTypeValues() const;
  std::vector<std::string> humidifierTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
