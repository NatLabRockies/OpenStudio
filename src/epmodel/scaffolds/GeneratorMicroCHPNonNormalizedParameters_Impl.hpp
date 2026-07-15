/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORMICROCHPNONNORMALIZEDPARAMETERS_IMPL_HPP
#define EPMODEL_GENERATORMICROCHPNONNORMALIZEDPARAMETERS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorMicroCHPNonNormalizedParameters_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorMicroCHPNonNormalizedParameters_Impl() override = default;

      boost::optional<double> maximumElectricPower() const;
      bool setMaximumElectricPower(double maximumElectricPower);
      void resetMaximumElectricPower();

      boost::optional<double> minimumElectricPower() const;
      bool setMinimumElectricPower(double minimumElectricPower);
      void resetMinimumElectricPower();

      boost::optional<double> minimumCoolingWaterFlowRate() const;
      bool setMinimumCoolingWaterFlowRate(double minimumCoolingWaterFlowRate);
      void resetMinimumCoolingWaterFlowRate();

      boost::optional<double> maximumCoolingWaterTemperature() const;
      bool setMaximumCoolingWaterTemperature(double maximumCoolingWaterTemperature);
      void resetMaximumCoolingWaterTemperature();

      boost::optional<std::string> coolingWaterFlowRateMode() const;
      bool setCoolingWaterFlowRateMode(const std::string& coolingWaterFlowRateMode);
      void resetCoolingWaterFlowRateMode();

      boost::optional<double> maximumNetElectricalPowerRateofChange() const;
      bool setMaximumNetElectricalPowerRateofChange(double maximumNetElectricalPowerRateofChange);
      void resetMaximumNetElectricalPowerRateofChange();

      boost::optional<double> maximumFuelFlowRateofChange() const;
      bool setMaximumFuelFlowRateofChange(double maximumFuelFlowRateofChange);
      void resetMaximumFuelFlowRateofChange();

      boost::optional<double> heatExchangerUFactorTimesAreaValue() const;
      bool setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue);
      void resetHeatExchangerUFactorTimesAreaValue();

      boost::optional<double> skinLossUFactorTimesAreaValue() const;
      bool setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue);
      void resetSkinLossUFactorTimesAreaValue();

      boost::optional<double> skinLossRadiativeFraction() const;
      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
      void resetSkinLossRadiativeFraction();

      boost::optional<double> aggregatedThermalMassofEnergyConversionPortionofGenerator() const;
      bool setAggregatedThermalMassofEnergyConversionPortionofGenerator(double aggregatedThermalMassofEnergyConversionPortionofGenerator);
      void resetAggregatedThermalMassofEnergyConversionPortionofGenerator();

      boost::optional<double> aggregatedThermalMassofHeatRecoveryPortionofGenerator() const;
      bool setAggregatedThermalMassofHeatRecoveryPortionofGenerator(double aggregatedThermalMassofHeatRecoveryPortionofGenerator);
      void resetAggregatedThermalMassofHeatRecoveryPortionofGenerator();

      boost::optional<double> standbyPower() const;
      bool setStandbyPower(double standbyPower);
      void resetStandbyPower();

      boost::optional<std::string> warmUpMode() const;
      bool setWarmUpMode(const std::string& warmUpMode);
      void resetWarmUpMode();

      boost::optional<double> warmUpFuelFlowRateCoefficient() const;
      bool setWarmUpFuelFlowRateCoefficient(double warmUpFuelFlowRateCoefficient);
      void resetWarmUpFuelFlowRateCoefficient();

      boost::optional<double> nominalEngineOperatingTemperature() const;
      bool setNominalEngineOperatingTemperature(double nominalEngineOperatingTemperature);
      void resetNominalEngineOperatingTemperature();

      boost::optional<double> warmUpPowerCoefficient() const;
      bool setWarmUpPowerCoefficient(double warmUpPowerCoefficient);
      void resetWarmUpPowerCoefficient();

      boost::optional<double> warmUpFuelFlowRateLimitRatio() const;
      bool setWarmUpFuelFlowRateLimitRatio(double warmUpFuelFlowRateLimitRatio);
      void resetWarmUpFuelFlowRateLimitRatio();

      boost::optional<double> warmUpDelayTime() const;
      bool setWarmUpDelayTime(double warmUpDelayTime);
      void resetWarmUpDelayTime();

      boost::optional<double> coolDownPower() const;
      bool setCoolDownPower(double coolDownPower);
      void resetCoolDownPower();

      boost::optional<double> coolDownDelayTime() const;
      bool setCoolDownDelayTime(double coolDownDelayTime);
      void resetCoolDownDelayTime();

      boost::optional<std::string> restartMode() const;
      bool setRestartMode(const std::string& restartMode);
      void resetRestartMode();

      std::vector<std::string> coolingWaterFlowRateModeValues() const;
      std::vector<std::string> warmUpModeValues() const;
      std::vector<std::string> restartModeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
