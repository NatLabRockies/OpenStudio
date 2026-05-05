/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATESYSTEMUNITARYHEATPUMPAIRTOAIR_IMPL_HPP
#define EPMODEL_HVACTEMPLATESYSTEMUNITARYHEATPUMPAIRTOAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl() override = default;

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

      double coolingDesignSupplyAirTemperature() const;
      bool isCoolingDesignSupplyAirTemperatureDefaulted() const;
      bool setCoolingDesignSupplyAirTemperature(double coolingDesignSupplyAirTemperature);
      void resetCoolingDesignSupplyAirTemperature();

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

      std::string heatPumpHeatingCoilType() const;
      bool isHeatPumpHeatingCoilTypeDefaulted() const;
      bool setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType);
      void resetHeatPumpHeatingCoilType();

      double heatingDesignSupplyAirTemperature() const;
      bool isHeatingDesignSupplyAirTemperatureDefaulted() const;
      bool setHeatingDesignSupplyAirTemperature(double heatingDesignSupplyAirTemperature);
      void resetHeatingDesignSupplyAirTemperature();

      boost::optional<double> heatPumpHeatingCoilGrossRatedCapacity() const;
      bool isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const;
      bool isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const;
      bool setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity);
      void resetHeatPumpHeatingCoilGrossRatedCapacity();
      void autosizeHeatPumpHeatingCoilGrossRatedCapacity();

      double heatPumpHeatingCoilRatedCOP() const;
      bool isHeatPumpHeatingCoilRatedCOPDefaulted() const;
      bool setHeatPumpHeatingCoilRatedCOP(double heatPumpHeatingCoilRatedCOP);
      void resetHeatPumpHeatingCoilRatedCOP();

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

      std::string supplementalHeatingCoilType() const;
      bool isSupplementalHeatingCoilTypeDefaulted() const;
      bool setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType);
      void resetSupplementalHeatingCoilType();

      boost::optional<double> supplementalHeatingCoilCapacity() const;
      bool isSupplementalHeatingCoilCapacityDefaulted() const;
      bool isSupplementalHeatingCoilCapacityAutosized() const;
      bool setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity);
      void resetSupplementalHeatingCoilCapacity();
      void autosizeSupplementalHeatingCoilCapacity();

      double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature() const;
      bool isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted() const;
      bool setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature(double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature);
      void resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature();

      double supplementalGasHeatingCoilEfficiency() const;
      bool isSupplementalGasHeatingCoilEfficiencyDefaulted() const;
      bool setSupplementalGasHeatingCoilEfficiency(double supplementalGasHeatingCoilEfficiency);
      void resetSupplementalGasHeatingCoilEfficiency();

      double supplementalGasHeatingCoilParasiticElectricLoad() const;
      bool isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted() const;
      bool setSupplementalGasHeatingCoilParasiticElectricLoad(double supplementalGasHeatingCoilParasiticElectricLoad);
      void resetSupplementalGasHeatingCoilParasiticElectricLoad();

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
      bool setEconomizerMaximumLimitDryBulbTemperature(double economizerMaximumLimitDryBulbTemperature);
      void resetEconomizerMaximumLimitDryBulbTemperature();

      boost::optional<double> economizerMaximumLimitEnthalpy() const;
      bool setEconomizerMaximumLimitEnthalpy(double economizerMaximumLimitEnthalpy);
      void resetEconomizerMaximumLimitEnthalpy();

      boost::optional<double> economizerMaximumLimitDewpointTemperature() const;
      bool setEconomizerMaximumLimitDewpointTemperature(double economizerMaximumLimitDewpointTemperature);
      void resetEconomizerMaximumLimitDewpointTemperature();

      boost::optional<double> economizerMinimumLimitDryBulbTemperature() const;
      bool setEconomizerMinimumLimitDryBulbTemperature(double economizerMinimumLimitDryBulbTemperature);
      void resetEconomizerMinimumLimitDryBulbTemperature();

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

      std::vector<std::string> supplyFanPlacementValues() const;
      std::vector<std::string> coolingCoilTypeValues() const;
      std::vector<std::string> heatPumpHeatingCoilTypeValues() const;
      std::vector<std::string> heatPumpDefrostStrategyValues() const;
      std::vector<std::string> heatPumpDefrostControlValues() const;
      std::vector<std::string> supplementalHeatingCoilTypeValues() const;
      std::vector<std::string> economizerTypeValues() const;
      std::vector<std::string> economizerLockoutValues() const;
      std::vector<std::string> nightCycleControlValues() const;
      std::vector<std::string> heatRecoveryTypeValues() const;
      std::vector<std::string> humidifierTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
