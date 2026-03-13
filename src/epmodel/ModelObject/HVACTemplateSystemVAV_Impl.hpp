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
      bool isSupplyFanMaximumFlowRateDefaulted() const;
      bool isSupplyFanMaximumFlowRateAutosized() const;
      bool setSupplyFanMaximumFlowRate(double supplyFanMaximumFlowRate);
      void resetSupplyFanMaximumFlowRate();
      void autosizeSupplyFanMaximumFlowRate();

      boost::optional<double> supplyFanMinimumFlowRate() const;
      bool isSupplyFanMinimumFlowRateDefaulted() const;
      bool isSupplyFanMinimumFlowRateAutosized() const;
      bool setSupplyFanMinimumFlowRate(double supplyFanMinimumFlowRate);
      void resetSupplyFanMinimumFlowRate();
      void autosizeSupplyFanMinimumFlowRate();

      std::string supplyFanPlacement() const;
      bool isSupplyFanPlacementDefaulted() const;
      bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
      void resetSupplyFanPlacement();

      double supplyFanTotalEfficiency() const;
      bool isSupplyFanTotalEfficiencyDefaulted() const;
      bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
      void resetSupplyFanTotalEfficiency();

      double supplyFanDeltaPressure() const;
      bool isSupplyFanDeltaPressureDefaulted() const;
      bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
      void resetSupplyFanDeltaPressure();

      double supplyFanMotorEfficiency() const;
      bool isSupplyFanMotorEfficiencyDefaulted() const;
      bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
      void resetSupplyFanMotorEfficiency();

      double supplyFanMotorinAirStreamFraction() const;
      bool isSupplyFanMotorinAirStreamFractionDefaulted() const;
      bool setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction);
      void resetSupplyFanMotorinAirStreamFraction();

      std::string coolingCoilType() const;
      bool isCoolingCoilTypeDefaulted() const;
      bool setCoolingCoilType(const std::string& coolingCoilType);
      void resetCoolingCoilType();

      double coolingCoilDesignSetpoint() const;
      bool isCoolingCoilDesignSetpointDefaulted() const;
      bool setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint);
      void resetCoolingCoilDesignSetpoint();

      std::string heatingCoilType() const;
      bool isHeatingCoilTypeDefaulted() const;
      bool setHeatingCoilType(const std::string& heatingCoilType);
      void resetHeatingCoilType();

      double heatingCoilDesignSetpoint() const;
      bool isHeatingCoilDesignSetpointDefaulted() const;
      bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
      void resetHeatingCoilDesignSetpoint();

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

      std::string supplyFanPartLoadPowerCoefficients() const;
      bool isSupplyFanPartLoadPowerCoefficientsDefaulted() const;
      bool setSupplyFanPartLoadPowerCoefficients(const std::string& supplyFanPartLoadPowerCoefficients);
      void resetSupplyFanPartLoadPowerCoefficients();

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

      std::string coolingCoilSetpointResetType() const;
      bool isCoolingCoilSetpointResetTypeDefaulted() const;
      bool setCoolingCoilSetpointResetType(const std::string& coolingCoilSetpointResetType);
      void resetCoolingCoilSetpointResetType();

      std::string heatingCoilSetpointResetType() const;
      bool isHeatingCoilSetpointResetTypeDefaulted() const;
      bool setHeatingCoilSetpointResetType(const std::string& heatingCoilSetpointResetType);
      void resetHeatingCoilSetpointResetType();

      std::string dehumidificationControlType() const;
      bool isDehumidificationControlTypeDefaulted() const;
      bool setDehumidificationControlType(const std::string& dehumidificationControlType);
      void resetDehumidificationControlType();

      double dehumidificationSetpoint() const;
      bool isDehumidificationSetpointDefaulted() const;
      bool setDehumidificationSetpoint(double dehumidificationSetpoint);
      void resetDehumidificationSetpoint();

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

      double humidifierSetpoint() const;
      bool isHumidifierSetpointDefaulted() const;
      bool setHumidifierSetpoint(double humidifierSetpoint);
      void resetHumidifierSetpoint();

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
