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

      boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
      bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
      bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
      bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
      void resetCoolingCoilGrossRatedTotalCapacity();
      void autosizeCoolingCoilGrossRatedTotalCapacity();

      boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
      bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
      bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
      bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
      void resetCoolingCoilGrossRatedSensibleHeatRatio();
      void autosizeCoolingCoilGrossRatedSensibleHeatRatio();

      double coolingCoilGrossRatedCOP() const;
      bool isCoolingCoilGrossRatedCOPDefaulted() const;
      bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
      void resetCoolingCoilGrossRatedCOP();

      std::string heatingCoilType() const;
      bool isHeatingCoilTypeDefaulted() const;
      bool setHeatingCoilType(const std::string& heatingCoilType);
      void resetHeatingCoilType();

      double heatingCoilDesignSetpoint() const;
      bool isHeatingCoilDesignSetpointDefaulted() const;
      bool setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint);
      void resetHeatingCoilDesignSetpoint();

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

      boost::optional<double> economizerMaximumLimitDryBulbTemperature() const;
      bool isEconomizerMaximumLimitDryBulbTemperatureDefaulted() const;
      bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
      void resetEconomizerMaximumLimitDryBulbTemperature();

      boost::optional<double> economizerMaximumLimitEnthalpy() const;
      bool isEconomizerMaximumLimitEnthalpyDefaulted() const;
      bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
      void resetEconomizerMaximumLimitEnthalpy();

      boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
      bool isEconomizerMaximumLimitDewpointTemperatureDefaulted() const;
      bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
      void resetEconomizerMaximumLimitDewpointTemperature();

      boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
      bool isEconomizerMinimumLimitDryBulbTemperatureDefaulted() const;
      bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
      void resetEconomizerMinimumLimitDryBulbTemperature();

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
