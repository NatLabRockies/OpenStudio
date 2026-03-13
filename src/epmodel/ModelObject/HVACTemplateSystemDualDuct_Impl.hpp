/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMDUALDUCT_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMDUALDUCT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateSystemDualDuct_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateSystemDualDuct_Impl() override = default;

      std::string systemConfigurationType() const;
      bool isSystemConfigurationTypeDefaulted() const;
      bool setSystemConfigurationType(const std::string& systemConfigurationType);
      void resetSystemConfigurationType();

      boost::optional<double> mainSupplyFanMaximumFlowRate() const;
      bool isMainSupplyFanMaximumFlowRateDefaulted() const;
      bool isMainSupplyFanMaximumFlowRateAutosized() const;
      bool setMainSupplyFanMaximumFlowRate(double mainSupplyFanMaximumFlowRate);
      void resetMainSupplyFanMaximumFlowRate();
      void autosizeMainSupplyFanMaximumFlowRate();

      double mainSupplyFanMinimumFlowFraction() const;
      bool isMainSupplyFanMinimumFlowFractionDefaulted() const;
      bool setMainSupplyFanMinimumFlowFraction(double mainSupplyFanMinimumFlowFraction);
      void resetMainSupplyFanMinimumFlowFraction();

      double mainSupplyFanTotalEfficiency() const;
      bool isMainSupplyFanTotalEfficiencyDefaulted() const;
      bool setMainSupplyFanTotalEfficiency(double mainSupplyFanTotalEfficiency);
      void resetMainSupplyFanTotalEfficiency();

      double mainSupplyFanDeltaPressure() const;
      bool isMainSupplyFanDeltaPressureDefaulted() const;
      bool setMainSupplyFanDeltaPressure(double mainSupplyFanDeltaPressure);
      void resetMainSupplyFanDeltaPressure();

      double mainSupplyFanMotorEfficiency() const;
      bool isMainSupplyFanMotorEfficiencyDefaulted() const;
      bool setMainSupplyFanMotorEfficiency(double mainSupplyFanMotorEfficiency);
      void resetMainSupplyFanMotorEfficiency();

      double mainSupplyFanMotorinAirStreamFraction() const;
      bool isMainSupplyFanMotorinAirStreamFractionDefaulted() const;
      bool setMainSupplyFanMotorinAirStreamFraction(double mainSupplyFanMotorinAirStreamFraction);
      void resetMainSupplyFanMotorinAirStreamFraction();

      std::string mainSupplyFanPartLoadPowerCoefficients() const;
      bool isMainSupplyFanPartLoadPowerCoefficientsDefaulted() const;
      bool setMainSupplyFanPartLoadPowerCoefficients(const std::string& mainSupplyFanPartLoadPowerCoefficients);
      void resetMainSupplyFanPartLoadPowerCoefficients();

      boost::optional<double> coldDuctSupplyFanMaximumFlowRate() const;
      bool isColdDuctSupplyFanMaximumFlowRateDefaulted() const;
      bool isColdDuctSupplyFanMaximumFlowRateAutosized() const;
      bool setColdDuctSupplyFanMaximumFlowRate(double coldDuctSupplyFanMaximumFlowRate);
      void resetColdDuctSupplyFanMaximumFlowRate();
      void autosizeColdDuctSupplyFanMaximumFlowRate();

      double coldDuctSupplyFanMinimumFlowFraction() const;
      bool isColdDuctSupplyFanMinimumFlowFractionDefaulted() const;
      bool setColdDuctSupplyFanMinimumFlowFraction(double coldDuctSupplyFanMinimumFlowFraction);
      void resetColdDuctSupplyFanMinimumFlowFraction();

      double coldDuctSupplyFanTotalEfficiency() const;
      bool isColdDuctSupplyFanTotalEfficiencyDefaulted() const;
      bool setColdDuctSupplyFanTotalEfficiency(double coldDuctSupplyFanTotalEfficiency);
      void resetColdDuctSupplyFanTotalEfficiency();

      double coldDuctSupplyFanDeltaPressure() const;
      bool isColdDuctSupplyFanDeltaPressureDefaulted() const;
      bool setColdDuctSupplyFanDeltaPressure(double coldDuctSupplyFanDeltaPressure);
      void resetColdDuctSupplyFanDeltaPressure();

      double coldDuctSupplyFanMotorEfficiency() const;
      bool isColdDuctSupplyFanMotorEfficiencyDefaulted() const;
      bool setColdDuctSupplyFanMotorEfficiency(double coldDuctSupplyFanMotorEfficiency);
      void resetColdDuctSupplyFanMotorEfficiency();

      double coldDuctSupplyFanMotorinAirStreamFraction() const;
      bool isColdDuctSupplyFanMotorinAirStreamFractionDefaulted() const;
      bool setColdDuctSupplyFanMotorinAirStreamFraction(double coldDuctSupplyFanMotorinAirStreamFraction);
      void resetColdDuctSupplyFanMotorinAirStreamFraction();

      std::string coldDuctSupplyFanPartLoadPowerCoefficients() const;
      bool isColdDuctSupplyFanPartLoadPowerCoefficientsDefaulted() const;
      bool setColdDuctSupplyFanPartLoadPowerCoefficients(const std::string& coldDuctSupplyFanPartLoadPowerCoefficients);
      void resetColdDuctSupplyFanPartLoadPowerCoefficients();

      std::string coldDuctSupplyFanPlacement() const;
      bool isColdDuctSupplyFanPlacementDefaulted() const;
      bool setColdDuctSupplyFanPlacement(const std::string& coldDuctSupplyFanPlacement);
      void resetColdDuctSupplyFanPlacement();

      boost::optional<double> hotDuctSupplyFanMaximumFlowRate() const;
      bool isHotDuctSupplyFanMaximumFlowRateDefaulted() const;
      bool isHotDuctSupplyFanMaximumFlowRateAutosized() const;
      bool setHotDuctSupplyFanMaximumFlowRate(double hotDuctSupplyFanMaximumFlowRate);
      void resetHotDuctSupplyFanMaximumFlowRate();
      void autosizeHotDuctSupplyFanMaximumFlowRate();

      double hotDuctSupplyFanMinimumFlowFraction() const;
      bool isHotDuctSupplyFanMinimumFlowFractionDefaulted() const;
      bool setHotDuctSupplyFanMinimumFlowFraction(double hotDuctSupplyFanMinimumFlowFraction);
      void resetHotDuctSupplyFanMinimumFlowFraction();

      double hotDuctSupplyFanTotalEfficiency() const;
      bool isHotDuctSupplyFanTotalEfficiencyDefaulted() const;
      bool setHotDuctSupplyFanTotalEfficiency(double hotDuctSupplyFanTotalEfficiency);
      void resetHotDuctSupplyFanTotalEfficiency();

      double hotDuctSupplyFanDeltaPressure() const;
      bool isHotDuctSupplyFanDeltaPressureDefaulted() const;
      bool setHotDuctSupplyFanDeltaPressure(double hotDuctSupplyFanDeltaPressure);
      void resetHotDuctSupplyFanDeltaPressure();

      double hotDuctSupplyFanMotorEfficiency() const;
      bool isHotDuctSupplyFanMotorEfficiencyDefaulted() const;
      bool setHotDuctSupplyFanMotorEfficiency(double hotDuctSupplyFanMotorEfficiency);
      void resetHotDuctSupplyFanMotorEfficiency();

      double hotDuctSupplyFanMotorinAirStreamFraction() const;
      bool isHotDuctSupplyFanMotorinAirStreamFractionDefaulted() const;
      bool setHotDuctSupplyFanMotorinAirStreamFraction(double hotDuctSupplyFanMotorinAirStreamFraction);
      void resetHotDuctSupplyFanMotorinAirStreamFraction();

      std::string hotDuctSupplyFanPartLoadPowerCoefficients() const;
      bool isHotDuctSupplyFanPartLoadPowerCoefficientsDefaulted() const;
      bool setHotDuctSupplyFanPartLoadPowerCoefficients(const std::string& hotDuctSupplyFanPartLoadPowerCoefficients);
      void resetHotDuctSupplyFanPartLoadPowerCoefficients();

      std::string hotDuctSupplyFanPlacement() const;
      bool isHotDuctSupplyFanPlacementDefaulted() const;
      bool setHotDuctSupplyFanPlacement(const std::string& hotDuctSupplyFanPlacement);
      void resetHotDuctSupplyFanPlacement();

      std::string coolingCoilType() const;
      bool isCoolingCoilTypeDefaulted() const;
      bool setCoolingCoilType(const std::string& coolingCoilType);
      void resetCoolingCoilType();

      std::string coolingCoilSetpointControlType() const;
      bool isCoolingCoilSetpointControlTypeDefaulted() const;
      bool setCoolingCoilSetpointControlType(const std::string& coolingCoilSetpointControlType);
      void resetCoolingCoilSetpointControlType();

      double coolingCoilDesignSetpointTemperature() const;
      bool isCoolingCoilDesignSetpointTemperatureDefaulted() const;
      bool setCoolingCoilDesignSetpointTemperature(double coolingCoilDesignSetpointTemperature);
      void resetCoolingCoilDesignSetpointTemperature();

      double coolingCoilSetpointatOutdoorDryBulbLow() const;
      bool isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
      bool setCoolingCoilSetpointatOutdoorDryBulbLow(double coolingCoilSetpointatOutdoorDryBulbLow);
      void resetCoolingCoilSetpointatOutdoorDryBulbLow();

      double coolingCoilResetOutdoorDryBulbLow() const;
      bool isCoolingCoilResetOutdoorDryBulbLowDefaulted() const;
      bool setCoolingCoilResetOutdoorDryBulbLow(double coolingCoilResetOutdoorDryBulbLow);
      void resetCoolingCoilResetOutdoorDryBulbLow();

      double coolingCoilSetpointatOutdoorDryBulbHigh() const;
      bool isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
      bool setCoolingCoilSetpointatOutdoorDryBulbHigh(double coolingCoilSetpointatOutdoorDryBulbHigh);
      void resetCoolingCoilSetpointatOutdoorDryBulbHigh();

      double coolingCoilResetOutdoorDryBulbHigh() const;
      bool isCoolingCoilResetOutdoorDryBulbHighDefaulted() const;
      bool setCoolingCoilResetOutdoorDryBulbHigh(double coolingCoilResetOutdoorDryBulbHigh);
      void resetCoolingCoilResetOutdoorDryBulbHigh();

      std::string heatingCoilType() const;
      bool isHeatingCoilTypeDefaulted() const;
      bool setHeatingCoilType(const std::string& heatingCoilType);
      void resetHeatingCoilType();

      std::string heatingCoilSetpointControlType() const;
      bool isHeatingCoilSetpointControlTypeDefaulted() const;
      bool setHeatingCoilSetpointControlType(const std::string& heatingCoilSetpointControlType);
      void resetHeatingCoilSetpointControlType();

      double heatingCoilDesignSetpoint() const;
      bool isHeatingCoilDesignSetpointDefaulted() const;
      bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
      void resetHeatingCoilDesignSetpoint();

      double heatingCoilSetpointatOutdoorDryBulbLow() const;
      bool isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted() const;
      bool setHeatingCoilSetpointatOutdoorDryBulbLow(double heatingCoilSetpointatOutdoorDryBulbLow);
      void resetHeatingCoilSetpointatOutdoorDryBulbLow();

      double heatingCoilResetOutdoorDryBulbLow() const;
      bool isHeatingCoilResetOutdoorDryBulbLowDefaulted() const;
      bool setHeatingCoilResetOutdoorDryBulbLow(double heatingCoilResetOutdoorDryBulbLow);
      void resetHeatingCoilResetOutdoorDryBulbLow();

      double heatingCoilSetpointatOutdoorDryBulbHigh() const;
      bool isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted() const;
      bool setHeatingCoilSetpointatOutdoorDryBulbHigh(double heatingCoilSetpointatOutdoorDryBulbHigh);
      void resetHeatingCoilSetpointatOutdoorDryBulbHigh();

      double heatingCoilResetOutdoorDryBulbHigh() const;
      bool isHeatingCoilResetOutdoorDryBulbHighDefaulted() const;
      bool setHeatingCoilResetOutdoorDryBulbHigh(double heatingCoilResetOutdoorDryBulbHigh);
      void resetHeatingCoilResetOutdoorDryBulbHigh();

      boost::optional<double> heatingCoilCapacity() const;
      bool isHeatingCoilCapacityDefaulted() const;
      bool isHeatingCoilCapacityAutosized() const;
      bool setHeatingCoilCapacity(double heatingCoilCapacity);
      void resetHeatingCoilCapacity();
      void autosizeHeatingCoilCapacity();

      double gasHeatingCoilEfficiency() const;
      bool isGasHeatingCoilEfficiencyDefaulted() const;
      bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
      void resetGasHeatingCoilEfficiency();

      double gasHeatingCoilParasiticElectricLoad() const;
      bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
      bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
      void resetGasHeatingCoilParasiticElectricLoad();

      std::string preheatCoilType() const;
      bool isPreheatCoilTypeDefaulted() const;
      bool setPreheatCoilType(const std::string& preheatCoilType);
      void resetPreheatCoilType();

      double preheatCoilDesignSetpoint() const;
      bool isPreheatCoilDesignSetpointDefaulted() const;
      bool setPreheatCoilDesignSetpoint(double preheatCoilDesignSetpoint);
      void resetPreheatCoilDesignSetpoint();

      double gasPreheatCoilEfficiency() const;
      bool isGasPreheatCoilEfficiencyDefaulted() const;
      bool setGasPreheatCoilEfficiency(double gasPreheatCoilEfficiency);
      void resetGasPreheatCoilEfficiency();

      double gasPreheatCoilParasiticElectricLoad() const;
      bool isGasPreheatCoilParasiticElectricLoadDefaulted() const;
      bool setGasPreheatCoilParasiticElectricLoad(double gasPreheatCoilParasiticElectricLoad);
      void resetGasPreheatCoilParasiticElectricLoad();

      boost::optional<double> maximumOutdoorAirFlowRate() const;
      bool isMaximumOutdoorAirFlowRateDefaulted() const;
      bool isMaximumOutdoorAirFlowRateAutosized() const;
      bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
      void resetMaximumOutdoorAirFlowRate();
      void autosizeMaximumOutdoorAirFlowRate();

      boost::optional<double> minimumOutdoorAirFlowRate() const;
      bool isMinimumOutdoorAirFlowRateDefaulted() const;
      bool isMinimumOutdoorAirFlowRateAutosized() const;
      bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
      void resetMinimumOutdoorAirFlowRate();
      void autosizeMinimumOutdoorAirFlowRate();

      std::string minimumOutdoorAirControlType() const;
      bool isMinimumOutdoorAirControlTypeDefaulted() const;
      bool setMinimumOutdoorAirControlType(const std::string& minimumOutdoorAirControlType);
      void resetMinimumOutdoorAirControlType();

      std::string economizerType() const;
      bool isEconomizerTypeDefaulted() const;
      bool setEconomizerType(const std::string& economizerType);
      void resetEconomizerType();

      std::string economizerLockout() const;
      bool isEconomizerLockoutDefaulted() const;
      bool setEconomizerLockout(const std::string& economizerLockout);
      void resetEconomizerLockout();

      boost::optional<double> economizerUpperTemperatureLimit() const;
      bool isEconomizerUpperTemperatureLimitDefaulted() const;
      bool setEconomizerUpperTemperatureLimit(double economizerUpperTemperatureLimit);
      void resetEconomizerUpperTemperatureLimit();

      boost::optional<double> economizerLowerTemperatureLimit() const;
      bool isEconomizerLowerTemperatureLimitDefaulted() const;
      bool setEconomizerLowerTemperatureLimit(double economizerLowerTemperatureLimit);
      void resetEconomizerLowerTemperatureLimit();

      boost::optional<double> economizerUpperEnthalpyLimit() const;
      bool isEconomizerUpperEnthalpyLimitDefaulted() const;
      bool setEconomizerUpperEnthalpyLimit(double economizerUpperEnthalpyLimit);
      void resetEconomizerUpperEnthalpyLimit();

      boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
      bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
      bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
      void resetEconomizerMaximumLimitDewpointTemperature();

      std::string nightCycleControl() const;
      bool isNightCycleControlDefaulted() const;
      bool setNightCycleControl(const std::string& nightCycleControl);
      void resetNightCycleControl();

      std::string heatRecoveryType() const;
      bool isHeatRecoveryTypeDefaulted() const;
      bool setHeatRecoveryType(const std::string& heatRecoveryType);
      void resetHeatRecoveryType();

      double sensibleHeatRecoveryEffectiveness() const;
      bool isSensibleHeatRecoveryEffectivenessDefaulted() const;
      bool setSensibleHeatRecoveryEffectiveness(double sensibleHeatRecoveryEffectiveness);
      void resetSensibleHeatRecoveryEffectiveness();

      double latentHeatRecoveryEffectiveness() const;
      bool isLatentHeatRecoveryEffectivenessDefaulted() const;
      bool setLatentHeatRecoveryEffectiveness(double latentHeatRecoveryEffectiveness);
      void resetLatentHeatRecoveryEffectiveness();

      std::string heatRecoveryHeatExchangerType() const;
      bool isHeatRecoveryHeatExchangerTypeDefaulted() const;
      bool setHeatRecoveryHeatExchangerType(const std::string& heatRecoveryHeatExchangerType);
      void resetHeatRecoveryHeatExchangerType();

      std::string heatRecoveryFrostControlType() const;
      bool isHeatRecoveryFrostControlTypeDefaulted() const;
      bool setHeatRecoveryFrostControlType(const std::string& heatRecoveryFrostControlType);
      void resetHeatRecoveryFrostControlType();

      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      double dehumidificationRelativeHumiditySetpoint() const;
      bool isDehumidificationRelativeHumiditySetpointDefaulted() const;
      bool setDehumidificationRelativeHumiditySetpoint(double dehumidificationRelativeHumiditySetpoint);
      void resetDehumidificationRelativeHumiditySetpoint();

      std::string humidifierType() const;
      bool isHumidifierTypeDefaulted() const;
      bool setHumidifierType(const std::string& humidifierType);
      void resetHumidifierType();

      double humidifierRatedCapacity() const;
      bool isHumidifierRatedCapacityDefaulted() const;
      bool setHumidifierRatedCapacity(double humidifierRatedCapacity);
      void resetHumidifierRatedCapacity();

      boost::optional<double> humidifierRatedElectricPower() const;
      bool isHumidifierRatedElectricPowerDefaulted() const;
      bool isHumidifierRatedElectricPowerAutosized() const;
      bool setHumidifierRatedElectricPower(double humidifierRatedElectricPower);
      void resetHumidifierRatedElectricPower();
      void autosizeHumidifierRatedElectricPower();

      double humidifierRelativeHumiditySetpoint() const;
      bool isHumidifierRelativeHumiditySetpointDefaulted() const;
      bool setHumidifierRelativeHumiditySetpoint(double humidifierRelativeHumiditySetpoint);
      void resetHumidifierRelativeHumiditySetpoint();

      std::string sizingOption() const;
      bool isSizingOptionDefaulted() const;
      bool setSizingOption(const std::string& sizingOption);
      void resetSizingOption();

      bool returnFan() const;
      bool isReturnFanDefaulted() const;
      bool setReturnFan(bool returnFan);
      void resetReturnFan();

      double returnFanTotalEfficiency() const;
      bool isReturnFanTotalEfficiencyDefaulted() const;
      bool setReturnFanTotalEfficiency(double returnFanTotalEfficiency);
      void resetReturnFanTotalEfficiency();

      double returnFanDeltaPressure() const;
      bool isReturnFanDeltaPressureDefaulted() const;
      bool setReturnFanDeltaPressure(double returnFanDeltaPressure);
      void resetReturnFanDeltaPressure();

      double returnFanMotorEfficiency() const;
      bool isReturnFanMotorEfficiencyDefaulted() const;
      bool setReturnFanMotorEfficiency(double returnFanMotorEfficiency);
      void resetReturnFanMotorEfficiency();

      double returnFanMotorinAirStreamFraction() const;
      bool isReturnFanMotorinAirStreamFractionDefaulted() const;
      bool setReturnFanMotorinAirStreamFraction(double returnFanMotorinAirStreamFraction);
      void resetReturnFanMotorinAirStreamFraction();

      std::string returnFanPartLoadPowerCoefficients() const;
      bool isReturnFanPartLoadPowerCoefficientsDefaulted() const;
      bool setReturnFanPartLoadPowerCoefficients(const std::string& returnFanPartLoadPowerCoefficients);
      void resetReturnFanPartLoadPowerCoefficients();

      std::vector<std::string> systemConfigurationTypeValues() const;
      std::vector<std::string> mainSupplyFanPartLoadPowerCoefficientsValues() const;
      std::vector<std::string> coldDuctSupplyFanPartLoadPowerCoefficientsValues() const;
      std::vector<std::string> coldDuctSupplyFanPlacementValues() const;
      std::vector<std::string> hotDuctSupplyFanPartLoadPowerCoefficientsValues() const;
      std::vector<std::string> hotDuctSupplyFanPlacementValues() const;
      std::vector<std::string> coolingCoilTypeValues() const;
      std::vector<std::string> coolingCoilSetpointControlTypeValues() const;
      std::vector<std::string> heatingCoilTypeValues() const;
      std::vector<std::string> heatingCoilSetpointControlTypeValues() const;
      std::vector<std::string> preheatCoilTypeValues() const;
      std::vector<std::string> minimumOutdoorAirControlTypeValues() const;
      std::vector<std::string> economizerTypeValues() const;
      std::vector<std::string> economizerLockoutValues() const;
      std::vector<std::string> nightCycleControlValues() const;
      std::vector<std::string> heatRecoveryTypeValues() const;
      std::vector<std::string> heatRecoveryHeatExchangerTypeValues() const;
      std::vector<std::string> heatRecoveryFrostControlTypeValues() const;
      std::vector<std::string> dehumidificationControlTypeValues() const;
      std::vector<std::string> humidifierTypeValues() const;
      std::vector<std::string> sizingOptionValues() const;
      std::vector<std::string> returnFanPartLoadPowerCoefficientsValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
