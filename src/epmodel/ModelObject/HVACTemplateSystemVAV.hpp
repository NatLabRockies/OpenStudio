/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMVAV_HPP
#define EPMODEL_HVACTEMPLATESYSTEMVAV_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateSystemVAV_Impl;
}

class EPMODEL_API HVACTemplateSystemVAV : public ModelObject
{
 public:
  explicit HVACTemplateSystemVAV(const Model& model);

  virtual ~HVACTemplateSystemVAV() override = default;
  HVACTemplateSystemVAV(const HVACTemplateSystemVAV& other) = default;
  HVACTemplateSystemVAV(HVACTemplateSystemVAV&& other) = default;
  HVACTemplateSystemVAV& operator=(const HVACTemplateSystemVAV&) = default;
  HVACTemplateSystemVAV& operator=(HVACTemplateSystemVAV&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyFanPlacementValues();
  static std::vector<std::string> coolingCoilTypeValues();
  static std::vector<std::string> heatingCoilTypeValues();
  static std::vector<std::string> preheatCoilTypeValues();
  static std::vector<std::string> minimumOutdoorAirControlTypeValues();
  static std::vector<std::string> economizerTypeValues();
  static std::vector<std::string> economizerLockoutValues();
  static std::vector<std::string> supplyFanPartLoadPowerCoefficientsValues();
  static std::vector<std::string> nightCycleControlValues();
  static std::vector<std::string> heatRecoveryTypeValues();
  static std::vector<std::string> coolingCoilSetpointResetTypeValues();
  static std::vector<std::string> heatingCoilSetpointResetTypeValues();
  static std::vector<std::string> dehumidificationControlTypeValues();
  static std::vector<std::string> humidifierTypeValues();
  static std::vector<std::string> sizingOptionValues();
  static std::vector<std::string> returnFanPartLoadPowerCoefficientsValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:System:VAV non-name, non-link scalar fields.
  // - Field Mapping: Schedule/plenum/control-zone object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
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

 protected:
  using ImplType = detail::HVACTemplateSystemVAV_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateSystemVAV(std::shared_ptr<detail::HVACTemplateSystemVAV_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
