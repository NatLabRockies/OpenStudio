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
      bool isControlTypeDefaulted() const;
      bool setControlType(const std::string& controlType);
      void resetControlType();

      boost::optional<double> coolingSupplyAirFlowRate() const;
      bool isCoolingSupplyAirFlowRateDefaulted() const;
      bool isCoolingSupplyAirFlowRateAutosized() const;
      bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
      void resetCoolingSupplyAirFlowRate();
      void autosizeCoolingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRate() const;
      bool isHeatingSupplyAirFlowRateDefaulted() const;
      bool isHeatingSupplyAirFlowRateAutosized() const;
      bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
      void resetHeatingSupplyAirFlowRate();
      void autosizeHeatingSupplyAirFlowRate();

      boost::optional<double> noLoadSupplyAirFlowRate() const;
      bool isNoLoadSupplyAirFlowRateDefaulted() const;
      bool isNoLoadSupplyAirFlowRateAutosized() const;
      bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
      void resetNoLoadSupplyAirFlowRate();
      void autosizeNoLoadSupplyAirFlowRate();

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

      int numberofSpeedsforCooling() const;
      bool isNumberofSpeedsforCoolingDefaulted() const;
      bool setNumberofSpeedsforCooling(int numberofSpeedsforCooling);
      void resetNumberofSpeedsforCooling();

      double coolingDesignSupplyAirTemperature() const;
      bool isCoolingDesignSupplyAirTemperatureDefaulted() const;
      bool setCoolingDesignSupplyAirTemperature(double coolingDesignSupplyAirTemperature);
      void resetCoolingDesignSupplyAirTemperature();

      boost::optional<double> dXCoolingCoilGrossRatedTotalCapacity() const;
      bool isDXCoolingCoilGrossRatedTotalCapacityDefaulted() const;
      bool isDXCoolingCoilGrossRatedTotalCapacityAutosized() const;
      bool setDXCoolingCoilGrossRatedTotalCapacity(double dXCoolingCoilGrossRatedTotalCapacity);
      void resetDXCoolingCoilGrossRatedTotalCapacity();
      void autosizeDXCoolingCoilGrossRatedTotalCapacity();

      boost::optional<double> dXCoolingCoilGrossRatedSensibleHeatRatio() const;
      bool isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
      bool isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
      bool setDXCoolingCoilGrossRatedSensibleHeatRatio(double dXCoolingCoilGrossRatedSensibleHeatRatio);
      void resetDXCoolingCoilGrossRatedSensibleHeatRatio();
      void autosizeDXCoolingCoilGrossRatedSensibleHeatRatio();

      double dXCoolingCoilGrossRatedCOP() const;
      bool isDXCoolingCoilGrossRatedCOPDefaulted() const;
      bool setDXCoolingCoilGrossRatedCOP(double dXCoolingCoilGrossRatedCOP);
      void resetDXCoolingCoilGrossRatedCOP();

      std::string heatingCoilType() const;
      bool isHeatingCoilTypeDefaulted() const;
      bool setHeatingCoilType(const std::string& heatingCoilType);
      void resetHeatingCoilType();

      int numberofSpeedsorStagesforHeating() const;
      bool isNumberofSpeedsorStagesforHeatingDefaulted() const;
      bool setNumberofSpeedsorStagesforHeating(int numberofSpeedsorStagesforHeating);
      void resetNumberofSpeedsorStagesforHeating();

      double heatingDesignSupplyAirTemperature() const;
      bool isHeatingDesignSupplyAirTemperatureDefaulted() const;
      bool setHeatingDesignSupplyAirTemperature(double heatingDesignSupplyAirTemperature);
      void resetHeatingDesignSupplyAirTemperature();

      boost::optional<double> heatingCoilGrossRatedCapacity() const;
      bool isHeatingCoilGrossRatedCapacityDefaulted() const;
      bool isHeatingCoilGrossRatedCapacityAutosized() const;
      bool setHeatingCoilGrossRatedCapacity(double heatingCoilGrossRatedCapacity);
      void resetHeatingCoilGrossRatedCapacity();
      void autosizeHeatingCoilGrossRatedCapacity();

      double gasHeatingCoilEfficiency() const;
      bool isGasHeatingCoilEfficiencyDefaulted() const;
      bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
      void resetGasHeatingCoilEfficiency();

      double gasHeatingCoilParasiticElectricLoad() const;
      bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
      bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
      void resetGasHeatingCoilParasiticElectricLoad();

      double heatPumpHeatingCoilGrossRatedCOP() const;
      bool isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const;
      bool setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP);
      void resetHeatPumpHeatingCoilGrossRatedCOP();

      double heatPumpHeatingMinimumOutdoorDryBulbTemperature() const;
      bool isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const;
      bool setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature);
      void resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature();

      double heatPumpDefrostMaximumOutdoorDryBulbTemperature() const;
      bool isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const;
      bool setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature);
      void resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature();

      std::string heatPumpDefrostStrategy() const;
      bool isHeatPumpDefrostStrategyDefaulted() const;
      bool setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy);
      void resetHeatPumpDefrostStrategy();

      std::string heatPumpDefrostControl() const;
      bool isHeatPumpDefrostControlDefaulted() const;
      bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
      void resetHeatPumpDefrostControl();

      double heatPumpDefrostTimePeriodFraction() const;
      bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
      bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
      void resetHeatPumpDefrostTimePeriodFraction();

      std::string supplementalHeatingorReheatCoilType() const;
      bool isSupplementalHeatingorReheatCoilTypeDefaulted() const;
      bool setSupplementalHeatingorReheatCoilType(const std::string& supplementalHeatingorReheatCoilType);
      void resetSupplementalHeatingorReheatCoilType();

      boost::optional<double> supplementalHeatingorReheatCoilCapacity() const;
      bool isSupplementalHeatingorReheatCoilCapacityDefaulted() const;
      bool isSupplementalHeatingorReheatCoilCapacityAutosized() const;
      bool setSupplementalHeatingorReheatCoilCapacity(double supplementalHeatingorReheatCoilCapacity);
      void resetSupplementalHeatingorReheatCoilCapacity();
      void autosizeSupplementalHeatingorReheatCoilCapacity();

      double supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature() const;
      bool isSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperatureDefaulted() const;
      bool setSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature(double supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature);
      void resetSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature();

      double supplementalGasHeatingorReheatCoilEfficiency() const;
      bool isSupplementalGasHeatingorReheatCoilEfficiencyDefaulted() const;
      bool setSupplementalGasHeatingorReheatCoilEfficiency(double supplementalGasHeatingorReheatCoilEfficiency);
      void resetSupplementalGasHeatingorReheatCoilEfficiency();

      double supplementalGasHeatingorReheatCoilParasiticElectricLoad() const;
      bool isSupplementalGasHeatingorReheatCoilParasiticElectricLoadDefaulted() const;
      bool setSupplementalGasHeatingorReheatCoilParasiticElectricLoad(double supplementalGasHeatingorReheatCoilParasiticElectricLoad);
      void resetSupplementalGasHeatingorReheatCoilParasiticElectricLoad();

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
