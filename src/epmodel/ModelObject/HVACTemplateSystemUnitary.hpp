/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMUNITARY_HPP
#define EPMODEL_HVACTEMPLATESYSTEMUNITARY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateSystemUnitary_Impl;
}

class EPMODEL_API HVACTemplateSystemUnitary : public ModelObject
{
 public:
  explicit HVACTemplateSystemUnitary(const Model& model);

  virtual ~HVACTemplateSystemUnitary() override = default;
  HVACTemplateSystemUnitary(const HVACTemplateSystemUnitary& other) = default;
  HVACTemplateSystemUnitary(HVACTemplateSystemUnitary&& other) = default;
  HVACTemplateSystemUnitary& operator=(const HVACTemplateSystemUnitary&) = default;
  HVACTemplateSystemUnitary& operator=(HVACTemplateSystemUnitary&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> coolingCoilTypeValues();
  static std::vector<std::string> heatingCoilTypeValues();
  static std::vector<std::string> economizerTypeValues();
  static std::vector<std::string> economizerLockoutValues();
  static std::vector<std::string> supplyFanPlacementValues();
  static std::vector<std::string> nightCycleControlValues();
  static std::vector<std::string> heatRecoveryTypeValues();
  static std::vector<std::string> dehumidificationControlTypeValues();
  static std::vector<std::string> humidifierTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:Unitary non-name, non-link scalar fields.
  // - Field Mapping: Schedule/zone/plenum object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
  boost::optional<double> supplyFanMaximumFlowRate() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string coolingCoilType() const;
  double coolingDesignSupplyAirTemperature() const;
  boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
  double coolingCoilGrossRatedCOP() const;
  std::string heatingCoilType() const;
  double heatingDesignSupplyAirTemperature() const;
  boost::optional<double> heatingCoilCapacity() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  boost::optional<double> maximumOutdoorAirFlowRate() const;
  boost::optional<double> minimumOutdoorAirFlowRate() const;
  std::string economizerType() const;
  std::string economizerLockout() const;
  boost::optional<double> economizerUpperTemperatureLimit() const;
  boost::optional<double> economizerLowerTemperatureLimit() const;
  boost::optional<double> economizerUpperEnthalpyLimit() const;
  boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
  std::string supplyFanPlacement() const;
  std::string nightCycleControl() const;
  std::string heatRecoveryType() const;
  double sensibleHeatRecoveryEffectiveness() const;
  double latentHeatRecoveryEffectiveness() const;
  std::string dehumidificationControlType() const;
  double dehumidificationSetpoint() const;
  std::string humidifierType() const;
  double humidifierRatedCapacity() const;
  boost::optional<double> humidifierRatedElectricPower() const;
  double humidifierSetpoint() const;
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
  bool isCoolingCoilTypeDefaulted() const;
  bool isCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isCoolingCoilGrossRatedCOPDefaulted() const;
  bool isHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isHeatingCoilCapacityDefaulted() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isMaximumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirFlowRateDefaulted() const;
  bool isEconomizerTypeDefaulted() const;
  bool isEconomizerLockoutDefaulted() const;
  bool isEconomizerUpperTemperatureLimitDefaulted() const;
  bool isEconomizerLowerTemperatureLimitDefaulted() const;
  bool isEconomizerUpperEnthalpyLimitDefaulted() const;
  bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isNightCycleControlDefaulted() const;
  bool isHeatRecoveryTypeDefaulted() const;
  bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
  bool isLatentHeatRecoveryEffectivenessDefaulted() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool isDehumidificationSetpointDefaulted() const;
  bool isHumidifierTypeDefaulted() const;
  bool isHumidifierRatedCapacityDefaulted() const;
  bool isHumidifierRatedElectricPowerDefaulted() const;
  bool isHumidifierSetpointDefaulted() const;
  bool isReturnFanDefaulted() const;
  bool isReturnFanTotalEfficiencyDefaulted() const;
  bool isReturnFanDeltaPressureDefaulted() const;
  bool isReturnFanMotorEfficiencyDefaulted() const;
  bool isReturnFanMotorinAirStreamFractionDefaulted() const;

  bool isSupplyFanMaximumFlowRateAutosized() const;
  bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHeatingCoilCapacityAutosized() const;
  bool isMaximumOutdoorAirFlowRateAutosized() const;
  bool isMinimumOutdoorAirFlowRateAutosized() const;
  bool isHumidifierRatedElectricPowerAutosized() const;

  bool setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setCoolingDesignSupplyAirTemperature(double coolingDesignSupplyAirTemperature);
  bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
  bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
  bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingDesignSupplyAirTemperature(double heatingDesignSupplyAirTemperature);
  bool setHeatingCoilCapacity(double heatingCoilCapacity);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
  bool setEconomizerType(const std::string& economizerType);
  bool setEconomizerLockout(const std::string& economizerLockout);
  bool setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit);
  bool setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit);
  bool setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit);
  bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setNightCycleControl(const std::string& nightCycleControl);
  bool setHeatRecoveryType(const std::string& heatRecoveryType);
  bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
  bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  bool setDehumidificationSetpoint(double dehumidificationSetpoint);
  bool setHumidifierType(const std::string& humidifierType);
  bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
  bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
  bool setHumidifierSetpoint(double humidifierSetpoint);
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
  void resetCoolingCoilType();
  void resetCoolingDesignSupplyAirTemperature();
  void resetCoolingCoilGrossRatedTotalCapacity();
  void resetCoolingCoilGrossRatedSensibleHeatRatio();
  void resetCoolingCoilGrossRatedCOP();
  void resetHeatingDesignSupplyAirTemperature();
  void resetHeatingCoilCapacity();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetMaximumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirFlowRate();
  void resetEconomizerType();
  void resetEconomizerLockout();
  void resetEconomizerUpperTemperatureLimit();
  void resetEconomizerLowerTemperatureLimit();
  void resetEconomizerUpperEnthalpyLimit();
  void resetEconomizerMaximumLimitDewpointTemperature();
  void resetSupplyFanPlacement();
  void resetNightCycleControl();
  void resetHeatRecoveryType();
  void resetSensibleHeatRecoveryEffectiveness();
  void resetLatentHeatRecoveryEffectiveness();
  void resetDehumidificationControlType();
  void resetDehumidificationSetpoint();
  void resetHumidifierType();
  void resetHumidifierRatedCapacity();
  void resetHumidifierRatedElectricPower();
  void resetHumidifierSetpoint();
  void resetReturnFan();
  void resetReturnFanTotalEfficiency();
  void resetReturnFanDeltaPressure();
  void resetReturnFanMotorEfficiency();
  void resetReturnFanMotorinAirStreamFraction();

  void autosizeSupplyFanMaximumFlowRate();
  void autosizeCoolingCoilGrossRatedTotalCapacity();
  void autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeHeatingCoilCapacity();
  void autosizeMaximumOutdoorAirFlowRate();
  void autosizeMinimumOutdoorAirFlowRate();
  void autosizeHumidifierRatedElectricPower();

 protected:
  using ImplType = detail::HVACTemplateSystemUnitary_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateSystemUnitary(std::shared_ptr<detail::HVACTemplateSystemUnitary_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
