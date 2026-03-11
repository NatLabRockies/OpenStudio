/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMPACKAGEDVAV_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMPACKAGEDVAV_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateSystemPackagedVAV_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateSystemPackagedVAV_Impl() override = default;

  boost::optional<double> supplyFanMaximumFlowRate() const;
  boost::optional<double> supplyFanMinimumFlowRate() const;
  std::string supplyFanPlacement() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string coolingCoilType() const;
  double coolingCoilDesignSetpoint() const;
  boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
  double coolingCoilGrossRatedCOP() const;
  std::string heatingCoilType() const;
  double heatingCoilDesignSetpoint() const;
  boost::optional<double> heatingCoilCapacity() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  boost::optional<double> maximumOutdoorAirFlowRate() const;
  boost::optional<double> minimumOutdoorAirFlowRate() const;
  std::string minimumOutdoorAirControlType() const;
  std::string economizerType() const;
  std::string economizerLockout() const;
  boost::optional<double> economizerMaximumLimitDryBulbTemperature() const;
  boost::optional<double> economizerMaximumLimitEnthalpy() const;
  boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
  boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
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
  bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isCoolingCoilGrossRatedCOPDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isHeatingCoilDesignSetpointDefaulted() const;
  bool isHeatingCoilCapacityDefaulted() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isMaximumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirControlTypeDefaulted() const;
  bool isEconomizerTypeDefaulted() const;
  bool isEconomizerLockoutDefaulted() const;
  bool isEconomizerMaximumLimitDryBulbTemperatureDefaulted() const;
  bool isEconomizerMaximumLimitEnthalpyDefaulted() const;
  bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
  bool isEconomizerMinimumLimitDryBulbTemperatureDefaulted() const;
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
  bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHeatingCoilCapacityAutosized() const;
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
  bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
  bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
  bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
  bool setHeatingCoilCapacity(double heatingCoilCapacity);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirControlType(const std::string& minimumOutdoorAirControlType);
  bool setEconomizerType(const std::string& economizerType);
  bool setEconomizerLockout(const std::string& economizerLockout);
  bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
  bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
  bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
  bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
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
  void resetCoolingCoilGrossRatedTotalCapacity();
  void resetCoolingCoilGrossRatedSensibleHeatRatio();
  void resetCoolingCoilGrossRatedCOP();
  void resetHeatingCoilType();
  void resetHeatingCoilDesignSetpoint();
  void resetHeatingCoilCapacity();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetMaximumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirControlType();
  void resetEconomizerType();
  void resetEconomizerLockout();
  void resetEconomizerMaximumLimitDryBulbTemperature();
  void resetEconomizerMaximumLimitEnthalpy();
  void resetEconomizerMaximumLimitDewpointTemperature();
  void resetEconomizerMinimumLimitDryBulbTemperature();
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
  void autosizeCoolingCoilGrossRatedTotalCapacity();
  void autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeHeatingCoilCapacity();
  void autosizeMaximumOutdoorAirFlowRate();
  void autosizeMinimumOutdoorAirFlowRate();
  void autosizeHumidifierRatedElectricPower();

  std::vector<std::string> supplyFanPlacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> heatingCoilTypeValues() const;
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
