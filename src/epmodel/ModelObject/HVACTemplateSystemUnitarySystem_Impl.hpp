/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMUNITARYSYSTEM_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMUNITARYSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateSystemUnitarySystem_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateSystemUnitarySystem_Impl() override = default;

  std::string controlType() const;
  boost::optional<double> coolingSupplyAirFlowRate() const;
  boost::optional<double> heatingSupplyAirFlowRate() const;
  boost::optional<double> noLoadSupplyAirFlowRate() const;
  std::string supplyFanPlacement() const;
  double supplyFanTotalEfficiency() const;
  double supplyFanDeltaPressure() const;
  double supplyFanMotorEfficiency() const;
  double supplyFanMotorinAirStreamFraction() const;
  std::string coolingCoilType() const;
  int numberofSpeedsforCooling() const;
  double coolingDesignSupplyAirTemperature() const;
  boost::optional<double> dXCoolingCoilGrossRatedTotalCapacity() const;
  boost::optional<double> dXCoolingCoilGrossRatedSensibleHeatRatio() const;
  double dXCoolingCoilGrossRatedCOP() const;
  std::string heatingCoilType() const;
  int numberofSpeedsorStagesforHeating() const;
  double heatingDesignSupplyAirTemperature() const;
  boost::optional<double> heatingCoilGrossRatedCapacity() const;
  double gasHeatingCoilEfficiency() const;
  double gasHeatingCoilParasiticElectricLoad() const;
  double heatPumpHeatingCoilGrossRatedCOP() const;
  double heatPumpHeatingMinimumOutdoorDryBulbTemperature() const;
  double heatPumpDefrostMaximumOutdoorDryBulbTemperature() const;
  std::string heatPumpDefrostStrategy() const;
  std::string heatPumpDefrostControl() const;
  double heatPumpDefrostTimePeriodFraction() const;
  std::string supplementalHeatingorReheatCoilType() const;
  boost::optional<double> supplementalHeatingorReheatCoilCapacity() const;
  double supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature() const;
  double supplementalGasHeatingorReheatCoilEfficiency() const;
  double supplementalGasHeatingorReheatCoilParasiticElectricLoad() const;
  boost::optional<double> maximumOutdoorAirFlowRate() const;
  boost::optional<double> minimumOutdoorAirFlowRate() const;
  std::string economizerType() const;
  std::string economizerLockout() const;
  boost::optional<double> economizerMaximumLimitDryBulbTemperature() const;
  boost::optional<double> economizerMaximumLimitEnthalpy() const;
  boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
  boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
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
  std::string sizingOption() const;
  bool returnFan() const;
  double returnFanTotalEfficiency() const;
  double returnFanDeltaPressure() const;
  double returnFanMotorEfficiency() const;
  double returnFanMotorinAirStreamFraction() const;

  bool isControlTypeDefaulted() const;
  bool isCoolingSupplyAirFlowRateDefaulted() const;
  bool isHeatingSupplyAirFlowRateDefaulted() const;
  bool isNoLoadSupplyAirFlowRateDefaulted() const;
  bool isSupplyFanPlacementDefaulted() const;
  bool isSupplyFanTotalEfficiencyDefaulted() const;
  bool isSupplyFanDeltaPressureDefaulted() const;
  bool isSupplyFanMotorEfficiencyDefaulted() const;
  bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
  bool isCoolingCoilTypeDefaulted() const;
  bool isNumberofSpeedsforCoolingDefaulted() const;
  bool isCoolingDesignSupplyAirTemperatureDefaulted() const;
  bool isDXCoolingCoilGrossRatedTotalCapacityDefaulted() const;
  bool isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
  bool isDXCoolingCoilGrossRatedCOPDefaulted() const;
  bool isHeatingCoilTypeDefaulted() const;
  bool isNumberofSpeedsorStagesforHeatingDefaulted() const;
  bool isHeatingDesignSupplyAirTemperatureDefaulted() const;
  bool isHeatingCoilGrossRatedCapacityDefaulted() const;
  bool isGasHeatingCoilEfficiencyDefaulted() const;
  bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
  bool isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const;
  bool isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const;
  bool isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const;
  bool isHeatPumpDefrostStrategyDefaulted() const;
  bool isHeatPumpDefrostControlDefaulted() const;
  bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
  bool isSupplementalHeatingorReheatCoilTypeDefaulted() const;
  bool isSupplementalHeatingorReheatCoilCapacityDefaulted() const;
  bool isSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperatureDefaulted() const;
  bool isSupplementalGasHeatingorReheatCoilEfficiencyDefaulted() const;
  bool isSupplementalGasHeatingorReheatCoilParasiticElectricLoadDefaulted() const;
  bool isMaximumOutdoorAirFlowRateDefaulted() const;
  bool isMinimumOutdoorAirFlowRateDefaulted() const;
  bool isEconomizerTypeDefaulted() const;
  bool isEconomizerLockoutDefaulted() const;
  bool isEconomizerMaximumLimitDryBulbTemperatureDefaulted() const;
  bool isEconomizerMaximumLimitEnthalpyDefaulted() const;
  bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
  bool isEconomizerMinimumLimitDryBulbTemperatureDefaulted() const;
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
  bool isSizingOptionDefaulted() const;
  bool isReturnFanDefaulted() const;
  bool isReturnFanTotalEfficiencyDefaulted() const;
  bool isReturnFanDeltaPressureDefaulted() const;
  bool isReturnFanMotorEfficiencyDefaulted() const;
  bool isReturnFanMotorinAirStreamFractionDefaulted() const;

  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool isNoLoadSupplyAirFlowRateAutosized() const;
  bool isDXCoolingCoilGrossRatedTotalCapacityAutosized() const;
  bool isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
  bool isHeatingCoilGrossRatedCapacityAutosized() const;
  bool isSupplementalHeatingorReheatCoilCapacityAutosized() const;
  bool isMaximumOutdoorAirFlowRateAutosized() const;
  bool isMinimumOutdoorAirFlowRateAutosized() const;
  bool isHumidifierRatedElectricPowerAutosized() const;

  bool setControlType(const std::string& controlType);
  bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
  bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
  bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
  bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
  bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
  bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
  bool setCoolingCoilType(const std::string& coolingCoilType);
  bool setNumberofSpeedsforCooling(int numberofSpeedsforCooling);
  bool setCoolingDesignSupplyAirTemperature(double coolingDesignSupplyAirTemperature);
  bool setDXCoolingCoilGrossRatedTotalCapacity(double dXCoolingCoilGrossRatedTotalCapacity);
  bool setDXCoolingCoilGrossRatedSensibleHeatRatio(double dXCoolingCoilGrossRatedSensibleHeatRatio);
  bool setDXCoolingCoilGrossRatedCOP(double dXCoolingCoilGrossRatedCOP);
  bool setHeatingCoilType(const std::string& heatingCoilType);
  bool setNumberofSpeedsorStagesforHeating(int numberofSpeedsorStagesforHeating);
  bool setHeatingDesignSupplyAirTemperature(double heatingDesignSupplyAirTemperature);
  bool setHeatingCoilGrossRatedCapacity(double heatingCoilGrossRatedCapacity);
  bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
  bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
  bool setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP);
  bool setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature);
  bool setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature);
  bool setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy);
  bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
  bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
  bool setSupplementalHeatingorReheatCoilType(const std::string& supplementalHeatingorReheatCoilType);
  bool setSupplementalHeatingorReheatCoilCapacity(double supplementalHeatingorReheatCoilCapacity);
  bool setSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature(
    double supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature);
  bool setSupplementalGasHeatingorReheatCoilEfficiency(double supplementalGasHeatingorReheatCoilEfficiency);
  bool setSupplementalGasHeatingorReheatCoilParasiticElectricLoad(double supplementalGasHeatingorReheatCoilParasiticElectricLoad);
  bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
  bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
  bool setEconomizerType(const std::string& economizerType);
  bool setEconomizerLockout(const std::string& economizerLockout);
  bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
  bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
  bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
  bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
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
  bool setSizingOption(const std::string& sizingOption);
  bool setReturnFan(bool returnFan);
  bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
  bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
  bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
  bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);

  void resetControlType();
  void resetCoolingSupplyAirFlowRate();
  void resetHeatingSupplyAirFlowRate();
  void resetNoLoadSupplyAirFlowRate();
  void resetSupplyFanPlacement();
  void resetSupplyFanTotalEfficiency();
  void resetSupplyFanDeltaPressure();
  void resetSupplyFanMotorEfficiency();
  void resetSupplyFanMotorinAirStreamFraction();
  void resetCoolingCoilType();
  void resetNumberofSpeedsforCooling();
  void resetCoolingDesignSupplyAirTemperature();
  void resetDXCoolingCoilGrossRatedTotalCapacity();
  void resetDXCoolingCoilGrossRatedSensibleHeatRatio();
  void resetDXCoolingCoilGrossRatedCOP();
  void resetHeatingCoilType();
  void resetNumberofSpeedsorStagesforHeating();
  void resetHeatingDesignSupplyAirTemperature();
  void resetHeatingCoilGrossRatedCapacity();
  void resetGasHeatingCoilEfficiency();
  void resetGasHeatingCoilParasiticElectricLoad();
  void resetHeatPumpHeatingCoilGrossRatedCOP();
  void resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature();
  void resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature();
  void resetHeatPumpDefrostStrategy();
  void resetHeatPumpDefrostControl();
  void resetHeatPumpDefrostTimePeriodFraction();
  void resetSupplementalHeatingorReheatCoilType();
  void resetSupplementalHeatingorReheatCoilCapacity();
  void resetSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature();
  void resetSupplementalGasHeatingorReheatCoilEfficiency();
  void resetSupplementalGasHeatingorReheatCoilParasiticElectricLoad();
  void resetMaximumOutdoorAirFlowRate();
  void resetMinimumOutdoorAirFlowRate();
  void resetEconomizerType();
  void resetEconomizerLockout();
  void resetEconomizerMaximumLimitDryBulbTemperature();
  void resetEconomizerMaximumLimitEnthalpy();
  void resetEconomizerMaximumLimitDewpointTemperature();
  void resetEconomizerMinimumLimitDryBulbTemperature();
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
  void resetSizingOption();
  void resetReturnFan();
  void resetReturnFanTotalEfficiency();
  void resetReturnFanDeltaPressure();
  void resetReturnFanMotorEfficiency();
  void resetReturnFanMotorinAirStreamFraction();

  void autosizeCoolingSupplyAirFlowRate();
  void autosizeHeatingSupplyAirFlowRate();
  void autosizeNoLoadSupplyAirFlowRate();
  void autosizeDXCoolingCoilGrossRatedTotalCapacity();
  void autosizeDXCoolingCoilGrossRatedSensibleHeatRatio();
  void autosizeHeatingCoilGrossRatedCapacity();
  void autosizeSupplementalHeatingorReheatCoilCapacity();
  void autosizeMaximumOutdoorAirFlowRate();
  void autosizeMinimumOutdoorAirFlowRate();
  void autosizeHumidifierRatedElectricPower();

  std::vector<std::string> controlTypeValues() const;
  std::vector<std::string> supplyFanPlacementValues() const;
  std::vector<std::string> coolingCoilTypeValues() const;
  std::vector<std::string> heatingCoilTypeValues() const;
  std::vector<std::string> heatPumpDefrostStrategyValues() const;
  std::vector<std::string> heatPumpDefrostControlValues() const;
  std::vector<std::string> supplementalHeatingorReheatCoilTypeValues() const;
  std::vector<std::string> economizerTypeValues() const;
  std::vector<std::string> economizerLockoutValues() const;
  std::vector<std::string> heatRecoveryTypeValues() const;
  std::vector<std::string> heatRecoveryHeatExchangerTypeValues() const;
  std::vector<std::string> heatRecoveryFrostControlTypeValues() const;
  std::vector<std::string> dehumidificationControlTypeValues() const;
  std::vector<std::string> humidifierTypeValues() const;
  std::vector<std::string> sizingOptionValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
