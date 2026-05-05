/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorMicroCHPNonNormalizedParameters.hpp"
#include "GeneratorMicroCHPNonNormalizedParameters_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_MicroCHP_NonNormalizedParameters_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorMicroCHPNonNormalizedParameters::GeneratorMicroCHPNonNormalizedParameters(const Model& model)
    : ModelObject(GeneratorMicroCHPNonNormalizedParameters::iddObjectType(), model) {}

  GeneratorMicroCHPNonNormalizedParameters::GeneratorMicroCHPNonNormalizedParameters(
    std::shared_ptr<detail::GeneratorMicroCHPNonNormalizedParameters_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorMicroCHPNonNormalizedParameters::iddObjectType() {
    return IddObjectType::Generator_MicroCHP_NonNormalizedParameters;
  }

  std::vector<std::string> GeneratorMicroCHPNonNormalizedParameters::coolingWaterFlowRateModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolingWaterFlowRateMode);
  }

  std::vector<std::string> GeneratorMicroCHPNonNormalizedParameters::warmUpModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpMode);
  }

  std::vector<std::string> GeneratorMicroCHPNonNormalizedParameters::restartModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_MicroCHP_NonNormalizedParametersFields::RestartMode);
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::maximumElectricPower() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->maximumElectricPower();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setMaximumElectricPower(double maximumElectricPower) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setMaximumElectricPower(maximumElectricPower);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetMaximumElectricPower() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetMaximumElectricPower();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::minimumElectricPower() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->minimumElectricPower();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setMinimumElectricPower(double minimumElectricPower) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setMinimumElectricPower(minimumElectricPower);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetMinimumElectricPower() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetMinimumElectricPower();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::minimumCoolingWaterFlowRate() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->minimumCoolingWaterFlowRate();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setMinimumCoolingWaterFlowRate(double minimumCoolingWaterFlowRate) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setMinimumCoolingWaterFlowRate(minimumCoolingWaterFlowRate);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetMinimumCoolingWaterFlowRate() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetMinimumCoolingWaterFlowRate();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::maximumCoolingWaterTemperature() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->maximumCoolingWaterTemperature();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setMaximumCoolingWaterTemperature(double maximumCoolingWaterTemperature) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setMaximumCoolingWaterTemperature(maximumCoolingWaterTemperature);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetMaximumCoolingWaterTemperature() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetMaximumCoolingWaterTemperature();
  }

  boost::optional<std::string> GeneratorMicroCHPNonNormalizedParameters::coolingWaterFlowRateMode() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->coolingWaterFlowRateMode();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setCoolingWaterFlowRateMode(const std::string& coolingWaterFlowRateMode) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setCoolingWaterFlowRateMode(coolingWaterFlowRateMode);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetCoolingWaterFlowRateMode() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetCoolingWaterFlowRateMode();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::maximumNetElectricalPowerRateofChange() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->maximumNetElectricalPowerRateofChange();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setMaximumNetElectricalPowerRateofChange(double maximumNetElectricalPowerRateofChange) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setMaximumNetElectricalPowerRateofChange(
      maximumNetElectricalPowerRateofChange);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetMaximumNetElectricalPowerRateofChange() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetMaximumNetElectricalPowerRateofChange();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::maximumFuelFlowRateofChange() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->maximumFuelFlowRateofChange();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setMaximumFuelFlowRateofChange(double maximumFuelFlowRateofChange) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setMaximumFuelFlowRateofChange(maximumFuelFlowRateofChange);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetMaximumFuelFlowRateofChange() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetMaximumFuelFlowRateofChange();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::heatExchangerUFactorTimesAreaValue() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->heatExchangerUFactorTimesAreaValue();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setHeatExchangerUFactorTimesAreaValue(
      heatExchangerUFactorTimesAreaValue);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetHeatExchangerUFactorTimesAreaValue() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetHeatExchangerUFactorTimesAreaValue();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::skinLossUFactorTimesAreaValue() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->skinLossUFactorTimesAreaValue();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setSkinLossUFactorTimesAreaValue(skinLossUFactorTimesAreaValue);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetSkinLossUFactorTimesAreaValue() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetSkinLossUFactorTimesAreaValue();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::skinLossRadiativeFraction() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->skinLossRadiativeFraction();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetSkinLossRadiativeFraction() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetSkinLossRadiativeFraction();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::aggregatedThermalMassofEnergyConversionPortionofGenerator() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->aggregatedThermalMassofEnergyConversionPortionofGenerator();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setAggregatedThermalMassofEnergyConversionPortionofGenerator(
    double aggregatedThermalMassofEnergyConversionPortionofGenerator) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setAggregatedThermalMassofEnergyConversionPortionofGenerator(
      aggregatedThermalMassofEnergyConversionPortionofGenerator);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetAggregatedThermalMassofEnergyConversionPortionofGenerator() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetAggregatedThermalMassofEnergyConversionPortionofGenerator();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::aggregatedThermalMassofHeatRecoveryPortionofGenerator() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->aggregatedThermalMassofHeatRecoveryPortionofGenerator();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setAggregatedThermalMassofHeatRecoveryPortionofGenerator(
    double aggregatedThermalMassofHeatRecoveryPortionofGenerator) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setAggregatedThermalMassofHeatRecoveryPortionofGenerator(
      aggregatedThermalMassofHeatRecoveryPortionofGenerator);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetAggregatedThermalMassofHeatRecoveryPortionofGenerator() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetAggregatedThermalMassofHeatRecoveryPortionofGenerator();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::standbyPower() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->standbyPower();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setStandbyPower(double standbyPower) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setStandbyPower(standbyPower);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetStandbyPower() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetStandbyPower();
  }

  boost::optional<std::string> GeneratorMicroCHPNonNormalizedParameters::warmUpMode() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->warmUpMode();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setWarmUpMode(const std::string& warmUpMode) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setWarmUpMode(warmUpMode);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetWarmUpMode() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetWarmUpMode();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::warmUpFuelFlowRateCoefficient() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->warmUpFuelFlowRateCoefficient();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setWarmUpFuelFlowRateCoefficient(double warmUpFuelFlowRateCoefficient) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setWarmUpFuelFlowRateCoefficient(warmUpFuelFlowRateCoefficient);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetWarmUpFuelFlowRateCoefficient() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetWarmUpFuelFlowRateCoefficient();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::nominalEngineOperatingTemperature() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->nominalEngineOperatingTemperature();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setNominalEngineOperatingTemperature(double nominalEngineOperatingTemperature) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setNominalEngineOperatingTemperature(nominalEngineOperatingTemperature);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetNominalEngineOperatingTemperature() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetNominalEngineOperatingTemperature();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::warmUpPowerCoefficient() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->warmUpPowerCoefficient();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setWarmUpPowerCoefficient(double warmUpPowerCoefficient) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setWarmUpPowerCoefficient(warmUpPowerCoefficient);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetWarmUpPowerCoefficient() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetWarmUpPowerCoefficient();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::warmUpFuelFlowRateLimitRatio() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->warmUpFuelFlowRateLimitRatio();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setWarmUpFuelFlowRateLimitRatio(double warmUpFuelFlowRateLimitRatio) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setWarmUpFuelFlowRateLimitRatio(warmUpFuelFlowRateLimitRatio);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetWarmUpFuelFlowRateLimitRatio() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetWarmUpFuelFlowRateLimitRatio();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::warmUpDelayTime() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->warmUpDelayTime();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setWarmUpDelayTime(double warmUpDelayTime) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setWarmUpDelayTime(warmUpDelayTime);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetWarmUpDelayTime() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetWarmUpDelayTime();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::coolDownPower() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->coolDownPower();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setCoolDownPower(double coolDownPower) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setCoolDownPower(coolDownPower);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetCoolDownPower() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetCoolDownPower();
  }

  boost::optional<double> GeneratorMicroCHPNonNormalizedParameters::coolDownDelayTime() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->coolDownDelayTime();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setCoolDownDelayTime(double coolDownDelayTime) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setCoolDownDelayTime(coolDownDelayTime);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetCoolDownDelayTime() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetCoolDownDelayTime();
  }

  boost::optional<std::string> GeneratorMicroCHPNonNormalizedParameters::restartMode() const {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->restartMode();
  }

  bool GeneratorMicroCHPNonNormalizedParameters::setRestartMode(const std::string& restartMode) {
    return getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->setRestartMode(restartMode);
  }

  void GeneratorMicroCHPNonNormalizedParameters::resetRestartMode() {
    getImpl<detail::GeneratorMicroCHPNonNormalizedParameters_Impl>()->resetRestartMode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::maximumElectricPower() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumElectricPower, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setMaximumElectricPower(double maximumElectricPower) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumElectricPower, maximumElectricPower);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetMaximumElectricPower() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumElectricPower, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::minimumElectricPower() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MinimumElectricPower, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setMinimumElectricPower(double minimumElectricPower) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MinimumElectricPower, minimumElectricPower);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetMinimumElectricPower() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MinimumElectricPower, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::minimumCoolingWaterFlowRate() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MinimumCoolingWaterFlowRate, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setMinimumCoolingWaterFlowRate(double minimumCoolingWaterFlowRate) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MinimumCoolingWaterFlowRate, minimumCoolingWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetMinimumCoolingWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MinimumCoolingWaterFlowRate, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::maximumCoolingWaterTemperature() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumCoolingWaterTemperature, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setMaximumCoolingWaterTemperature(double maximumCoolingWaterTemperature) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumCoolingWaterTemperature, maximumCoolingWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetMaximumCoolingWaterTemperature() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumCoolingWaterTemperature, ""));
    }

    boost::optional<std::string> GeneratorMicroCHPNonNormalizedParameters_Impl::coolingWaterFlowRateMode() const {
      return getString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolingWaterFlowRateMode, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setCoolingWaterFlowRateMode(const std::string& coolingWaterFlowRateMode) {
      return setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolingWaterFlowRateMode, coolingWaterFlowRateMode);
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetCoolingWaterFlowRateMode() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolingWaterFlowRateMode, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::maximumNetElectricalPowerRateofChange() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumNetElectricalPowerRateofChange, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setMaximumNetElectricalPowerRateofChange(double maximumNetElectricalPowerRateofChange) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumNetElectricalPowerRateofChange,
                                    maximumNetElectricalPowerRateofChange);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetMaximumNetElectricalPowerRateofChange() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumNetElectricalPowerRateofChange, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::maximumFuelFlowRateofChange() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumFuelFlowRateofChange, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setMaximumFuelFlowRateofChange(double maximumFuelFlowRateofChange) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumFuelFlowRateofChange, maximumFuelFlowRateofChange);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetMaximumFuelFlowRateofChange() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::MaximumFuelFlowRateofChange, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::heatExchangerUFactorTimesAreaValue() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::HeatExchangerUFactorTimesAreaValue, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::HeatExchangerUFactorTimesAreaValue,
                                    heatExchangerUFactorTimesAreaValue);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetHeatExchangerUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::HeatExchangerUFactorTimesAreaValue, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::skinLossUFactorTimesAreaValue() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::SkinLossUFactorTimesAreaValue, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setSkinLossUFactorTimesAreaValue(double skinLossUFactorTimesAreaValue) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::SkinLossUFactorTimesAreaValue, skinLossUFactorTimesAreaValue);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetSkinLossUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::SkinLossUFactorTimesAreaValue, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::skinLossRadiativeFraction() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::SkinLossRadiativeFraction, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetSkinLossRadiativeFraction() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::SkinLossRadiativeFraction, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::aggregatedThermalMassofEnergyConversionPortionofGenerator() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofEnergyConversionPortionofGenerator, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setAggregatedThermalMassofEnergyConversionPortionofGenerator(
      double aggregatedThermalMassofEnergyConversionPortionofGenerator) {
      return setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofEnergyConversionPortionofGenerator,
                       aggregatedThermalMassofEnergyConversionPortionofGenerator);
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetAggregatedThermalMassofEnergyConversionPortionofGenerator() {
      OS_ASSERT(
        setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofEnergyConversionPortionofGenerator, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::aggregatedThermalMassofHeatRecoveryPortionofGenerator() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofHeatRecoveryPortionofGenerator, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setAggregatedThermalMassofHeatRecoveryPortionofGenerator(
      double aggregatedThermalMassofHeatRecoveryPortionofGenerator) {
      return setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofHeatRecoveryPortionofGenerator,
                       aggregatedThermalMassofHeatRecoveryPortionofGenerator);
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetAggregatedThermalMassofHeatRecoveryPortionofGenerator() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofHeatRecoveryPortionofGenerator, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::standbyPower() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::StandbyPower, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setStandbyPower(double standbyPower) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::StandbyPower, standbyPower);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetStandbyPower() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::StandbyPower, ""));
    }

    boost::optional<std::string> GeneratorMicroCHPNonNormalizedParameters_Impl::warmUpMode() const {
      return getString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpMode, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setWarmUpMode(const std::string& warmUpMode) {
      return setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpMode, warmUpMode);
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetWarmUpMode() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpMode, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::warmUpFuelFlowRateCoefficient() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateCoefficient, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setWarmUpFuelFlowRateCoefficient(double warmUpFuelFlowRateCoefficient) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateCoefficient, warmUpFuelFlowRateCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetWarmUpFuelFlowRateCoefficient() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateCoefficient, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::nominalEngineOperatingTemperature() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::NominalEngineOperatingTemperature, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setNominalEngineOperatingTemperature(double nominalEngineOperatingTemperature) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::NominalEngineOperatingTemperature, nominalEngineOperatingTemperature);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetNominalEngineOperatingTemperature() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::NominalEngineOperatingTemperature, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::warmUpPowerCoefficient() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpPowerCoefficient, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setWarmUpPowerCoefficient(double warmUpPowerCoefficient) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpPowerCoefficient, warmUpPowerCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetWarmUpPowerCoefficient() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpPowerCoefficient, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::warmUpFuelFlowRateLimitRatio() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateLimitRatio, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setWarmUpFuelFlowRateLimitRatio(double warmUpFuelFlowRateLimitRatio) {
      const bool result =
        setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateLimitRatio, warmUpFuelFlowRateLimitRatio);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetWarmUpFuelFlowRateLimitRatio() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateLimitRatio, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::warmUpDelayTime() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpDelayTime, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setWarmUpDelayTime(double warmUpDelayTime) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpDelayTime, warmUpDelayTime);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetWarmUpDelayTime() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::WarmUpDelayTime, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::coolDownPower() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolDownPower, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setCoolDownPower(double coolDownPower) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolDownPower, coolDownPower);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetCoolDownPower() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolDownPower, ""));
    }

    boost::optional<double> GeneratorMicroCHPNonNormalizedParameters_Impl::coolDownDelayTime() const {
      return getDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolDownDelayTime, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setCoolDownDelayTime(double coolDownDelayTime) {
      const bool result = setDouble(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolDownDelayTime, coolDownDelayTime);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetCoolDownDelayTime() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::CoolDownDelayTime, ""));
    }

    boost::optional<std::string> GeneratorMicroCHPNonNormalizedParameters_Impl::restartMode() const {
      return getString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::RestartMode, true);
    }

    bool GeneratorMicroCHPNonNormalizedParameters_Impl::setRestartMode(const std::string& restartMode) {
      return setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::RestartMode, restartMode);
    }

    void GeneratorMicroCHPNonNormalizedParameters_Impl::resetRestartMode() {
      OS_ASSERT(setString(openstudio::Generator_MicroCHP_NonNormalizedParametersFields::RestartMode, ""));
    }

    std::vector<std::string> GeneratorMicroCHPNonNormalizedParameters_Impl::coolingWaterFlowRateModeValues() const {
      return openstudio::epmodel::GeneratorMicroCHPNonNormalizedParameters::coolingWaterFlowRateModeValues();
    }

    std::vector<std::string> GeneratorMicroCHPNonNormalizedParameters_Impl::warmUpModeValues() const {
      return openstudio::epmodel::GeneratorMicroCHPNonNormalizedParameters::warmUpModeValues();
    }

    std::vector<std::string> GeneratorMicroCHPNonNormalizedParameters_Impl::restartModeValues() const {
      return openstudio::epmodel::GeneratorMicroCHPNonNormalizedParameters::restartModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
