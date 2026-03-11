/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMCONSTANTVOLUME_HPP
#define EPMODEL_HVACTEMPLATESYSTEMCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateSystemConstantVolume_Impl;
}

class EPMODEL_API HVACTemplateSystemConstantVolume : public ModelObject
{
 public:
  explicit HVACTemplateSystemConstantVolume(const Model& model);

  virtual ~HVACTemplateSystemConstantVolume() override = default;
  HVACTemplateSystemConstantVolume(const HVACTemplateSystemConstantVolume& other) = default;
  HVACTemplateSystemConstantVolume(HVACTemplateSystemConstantVolume&& other) = default;
  HVACTemplateSystemConstantVolume& operator=(const HVACTemplateSystemConstantVolume&) = default;
  HVACTemplateSystemConstantVolume& operator=(HVACTemplateSystemConstantVolume&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyFanPlacementValues();
  static std::vector<std::string> coolingCoilTypeValues();
  static std::vector<std::string> coolingCoilSetpointControlTypeValues();
  static std::vector<std::string> heatingCoilTypeValues();
  static std::vector<std::string> heatingCoilSetpointControlTypeValues();
  static std::vector<std::string> preheatCoilTypeValues();
  static std::vector<std::string> economizerTypeValues();
  static std::vector<std::string> nightCycleControlValues();
  static std::vector<std::string> heatRecoveryTypeValues();
  static std::vector<std::string> heatRecoveryHeatExchangerTypeValues();
  static std::vector<std::string> heatRecoveryFrostControlTypeValues();
  static std::vector<std::string> dehumidificationControlTypeValues();
  static std::vector<std::string> humidifierTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:ConstantVolume non-name, non-link scalar fields.
  // - Field Mapping: Schedule/zone/plenum object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
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

 protected:
  using ImplType = detail::HVACTemplateSystemConstantVolume_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateSystemConstantVolume(std::shared_ptr<detail::HVACTemplateSystemConstantVolume_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
