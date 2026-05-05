/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ChillerHeaterAbsorptionDoubleEffect.hpp"
#include "ChillerHeaterAbsorptionDoubleEffect_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ChillerHeater_Absorption_DoubleEffect_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ChillerHeaterAbsorptionDoubleEffect::ChillerHeaterAbsorptionDoubleEffect(const Model& model)
    : ModelObject(ChillerHeaterAbsorptionDoubleEffect::iddObjectType(), model) {}

  ChillerHeaterAbsorptionDoubleEffect::ChillerHeaterAbsorptionDoubleEffect(std::shared_ptr<detail::ChillerHeaterAbsorptionDoubleEffect_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ChillerHeaterAbsorptionDoubleEffect::iddObjectType() {
    return IddObjectType::ChillerHeater_Absorption_DoubleEffect;
  }

  std::vector<std::string> ChillerHeaterAbsorptionDoubleEffect::temperatureCurveInputVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ChillerHeater_Absorption_DoubleEffectFields::TemperatureCurveInputVariable);
  }

  std::vector<std::string> ChillerHeaterAbsorptionDoubleEffect::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ChillerHeater_Absorption_DoubleEffectFields::CondenserType);
  }

  boost::optional<double> ChillerHeaterAbsorptionDoubleEffect::nominalCoolingCapacity() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->nominalCoolingCapacity();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isNominalCoolingCapacityDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isNominalCoolingCapacityDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isNominalCoolingCapacityAutosized() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isNominalCoolingCapacityAutosized();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setNominalCoolingCapacity(double nominalCoolingCapacity) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setNominalCoolingCapacity(nominalCoolingCapacity);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetNominalCoolingCapacity() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetNominalCoolingCapacity();
  }

  void ChillerHeaterAbsorptionDoubleEffect::autosizeNominalCoolingCapacity() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->autosizeNominalCoolingCapacity();
  }

  double ChillerHeaterAbsorptionDoubleEffect::heatingtoCoolingCapacityRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->heatingtoCoolingCapacityRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isHeatingtoCoolingCapacityRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isHeatingtoCoolingCapacityRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setHeatingtoCoolingCapacityRatio(double heatingtoCoolingCapacityRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setHeatingtoCoolingCapacityRatio(heatingtoCoolingCapacityRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetHeatingtoCoolingCapacityRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetHeatingtoCoolingCapacityRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::thermalEnergyInputtoCoolingOutputRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->thermalEnergyInputtoCoolingOutputRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isThermalEnergyInputtoCoolingOutputRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isThermalEnergyInputtoCoolingOutputRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setThermalEnergyInputtoCoolingOutputRatio(double thermalEnergyInputtoCoolingOutputRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setThermalEnergyInputtoCoolingOutputRatio(
      thermalEnergyInputtoCoolingOutputRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetThermalEnergyInputtoCoolingOutputRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetThermalEnergyInputtoCoolingOutputRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::thermalEnergyInputtoHeatingOutputRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->thermalEnergyInputtoHeatingOutputRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isThermalEnergyInputtoHeatingOutputRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isThermalEnergyInputtoHeatingOutputRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setThermalEnergyInputtoHeatingOutputRatio(double thermalEnergyInputtoHeatingOutputRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setThermalEnergyInputtoHeatingOutputRatio(
      thermalEnergyInputtoHeatingOutputRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetThermalEnergyInputtoHeatingOutputRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetThermalEnergyInputtoHeatingOutputRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::electricInputtoCoolingOutputRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->electricInputtoCoolingOutputRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isElectricInputtoCoolingOutputRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isElectricInputtoCoolingOutputRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setElectricInputtoCoolingOutputRatio(double electricInputtoCoolingOutputRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setElectricInputtoCoolingOutputRatio(electricInputtoCoolingOutputRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetElectricInputtoCoolingOutputRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetElectricInputtoCoolingOutputRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::electricInputtoHeatingOutputRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->electricInputtoHeatingOutputRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isElectricInputtoHeatingOutputRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isElectricInputtoHeatingOutputRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setElectricInputtoHeatingOutputRatio(double electricInputtoHeatingOutputRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setElectricInputtoHeatingOutputRatio(electricInputtoHeatingOutputRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetElectricInputtoHeatingOutputRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetElectricInputtoHeatingOutputRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::minimumPartLoadRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->minimumPartLoadRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isMinimumPartLoadRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isMinimumPartLoadRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetMinimumPartLoadRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetMinimumPartLoadRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::maximumPartLoadRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->maximumPartLoadRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isMaximumPartLoadRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isMaximumPartLoadRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetMaximumPartLoadRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetMaximumPartLoadRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::optimumPartLoadRatio() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->optimumPartLoadRatio();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isOptimumPartLoadRatioDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isOptimumPartLoadRatioDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetOptimumPartLoadRatio() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetOptimumPartLoadRatio();
  }

  double ChillerHeaterAbsorptionDoubleEffect::designEnteringCondenserWaterTemperature() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->designEnteringCondenserWaterTemperature();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignEnteringCondenserWaterTemperatureDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignEnteringCondenserWaterTemperatureDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setDesignEnteringCondenserWaterTemperature(double designEnteringCondenserWaterTemperature) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setDesignEnteringCondenserWaterTemperature(
      designEnteringCondenserWaterTemperature);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetDesignEnteringCondenserWaterTemperature() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetDesignEnteringCondenserWaterTemperature();
  }

  double ChillerHeaterAbsorptionDoubleEffect::designLeavingChilledWaterTemperature() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->designLeavingChilledWaterTemperature();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignLeavingChilledWaterTemperatureDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignLeavingChilledWaterTemperatureDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setDesignLeavingChilledWaterTemperature(double designLeavingChilledWaterTemperature) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setDesignLeavingChilledWaterTemperature(designLeavingChilledWaterTemperature);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetDesignLeavingChilledWaterTemperature() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetDesignLeavingChilledWaterTemperature();
  }

  boost::optional<double> ChillerHeaterAbsorptionDoubleEffect::designChilledWaterFlowRate() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->designChilledWaterFlowRate();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignChilledWaterFlowRateDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignChilledWaterFlowRateDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignChilledWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignChilledWaterFlowRateAutosized();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetDesignChilledWaterFlowRate();
  }

  void ChillerHeaterAbsorptionDoubleEffect::autosizeDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->autosizeDesignChilledWaterFlowRate();
  }

  boost::optional<double> ChillerHeaterAbsorptionDoubleEffect::designCondenserWaterFlowRate() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->designCondenserWaterFlowRate();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignCondenserWaterFlowRateDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignCondenserWaterFlowRateDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignCondenserWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignCondenserWaterFlowRateAutosized();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetDesignCondenserWaterFlowRate();
  }

  void ChillerHeaterAbsorptionDoubleEffect::autosizeDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->autosizeDesignCondenserWaterFlowRate();
  }

  boost::optional<double> ChillerHeaterAbsorptionDoubleEffect::designHotWaterFlowRate() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->designHotWaterFlowRate();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignHotWaterFlowRateDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignHotWaterFlowRateDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isDesignHotWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isDesignHotWaterFlowRateAutosized();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setDesignHotWaterFlowRate(double designHotWaterFlowRate) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setDesignHotWaterFlowRate(designHotWaterFlowRate);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetDesignHotWaterFlowRate() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetDesignHotWaterFlowRate();
  }

  void ChillerHeaterAbsorptionDoubleEffect::autosizeDesignHotWaterFlowRate() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->autosizeDesignHotWaterFlowRate();
  }

  std::string ChillerHeaterAbsorptionDoubleEffect::temperatureCurveInputVariable() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->temperatureCurveInputVariable();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isTemperatureCurveInputVariableDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isTemperatureCurveInputVariableDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setTemperatureCurveInputVariable(const std::string& temperatureCurveInputVariable) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setTemperatureCurveInputVariable(temperatureCurveInputVariable);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetTemperatureCurveInputVariable() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetTemperatureCurveInputVariable();
  }

  std::string ChillerHeaterAbsorptionDoubleEffect::condenserType() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->condenserType();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isCondenserTypeDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isCondenserTypeDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setCondenserType(condenserType);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetCondenserType() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetCondenserType();
  }

  double ChillerHeaterAbsorptionDoubleEffect::chilledWaterTemperatureLowerLimit() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->chilledWaterTemperatureLowerLimit();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isChilledWaterTemperatureLowerLimitDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isChilledWaterTemperatureLowerLimitDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setChilledWaterTemperatureLowerLimit(double chilledWaterTemperatureLowerLimit) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setChilledWaterTemperatureLowerLimit(chilledWaterTemperatureLowerLimit);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetChilledWaterTemperatureLowerLimit() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetChilledWaterTemperatureLowerLimit();
  }

  double ChillerHeaterAbsorptionDoubleEffect::sizingFactor() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->sizingFactor();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::isSizingFactorDefaulted() const {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->isSizingFactorDefaulted();
  }

  bool ChillerHeaterAbsorptionDoubleEffect::setSizingFactor(double sizingFactor) {
    return getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->setSizingFactor(sizingFactor);
  }

  void ChillerHeaterAbsorptionDoubleEffect::resetSizingFactor() {
    getImpl<detail::ChillerHeaterAbsorptionDoubleEffect_Impl>()->resetSizingFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ChillerHeaterAbsorptionDoubleEffect_Impl::nominalCoolingCapacity() const {
      return getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity, true);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isNominalCoolingCapacityDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isNominalCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setNominalCoolingCapacity(double nominalCoolingCapacity) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity, nominalCoolingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetNominalCoolingCapacity() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity, "");
      OS_ASSERT(result);
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::autosizeNominalCoolingCapacity() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::heatingtoCoolingCapacityRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::HeatingtoCoolingCapacityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isHeatingtoCoolingCapacityRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::HeatingtoCoolingCapacityRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setHeatingtoCoolingCapacityRatio(double heatingtoCoolingCapacityRatio) {
      const bool result =
        setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::HeatingtoCoolingCapacityRatio, heatingtoCoolingCapacityRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetHeatingtoCoolingCapacityRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::HeatingtoCoolingCapacityRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::thermalEnergyInputtoCoolingOutputRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoCoolingOutputRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isThermalEnergyInputtoCoolingOutputRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoCoolingOutputRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setThermalEnergyInputtoCoolingOutputRatio(double thermalEnergyInputtoCoolingOutputRatio) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoCoolingOutputRatio,
                                    thermalEnergyInputtoCoolingOutputRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetThermalEnergyInputtoCoolingOutputRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoCoolingOutputRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::thermalEnergyInputtoHeatingOutputRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoHeatingOutputRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isThermalEnergyInputtoHeatingOutputRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoHeatingOutputRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setThermalEnergyInputtoHeatingOutputRatio(double thermalEnergyInputtoHeatingOutputRatio) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoHeatingOutputRatio,
                                    thermalEnergyInputtoHeatingOutputRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetThermalEnergyInputtoHeatingOutputRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoHeatingOutputRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::electricInputtoCoolingOutputRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isElectricInputtoCoolingOutputRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setElectricInputtoCoolingOutputRatio(double electricInputtoCoolingOutputRatio) {
      const bool result =
        setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatio, electricInputtoCoolingOutputRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetElectricInputtoCoolingOutputRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::electricInputtoHeatingOutputRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoHeatingOutputRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isElectricInputtoHeatingOutputRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoHeatingOutputRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setElectricInputtoHeatingOutputRatio(double electricInputtoHeatingOutputRatio) {
      const bool result =
        setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoHeatingOutputRatio, electricInputtoHeatingOutputRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetElectricInputtoHeatingOutputRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoHeatingOutputRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::minimumPartLoadRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MinimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isMinimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MinimumPartLoadRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MinimumPartLoadRatio, minimumPartLoadRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetMinimumPartLoadRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MinimumPartLoadRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::maximumPartLoadRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MaximumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isMaximumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MaximumPartLoadRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MaximumPartLoadRatio, maximumPartLoadRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetMaximumPartLoadRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::MaximumPartLoadRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::optimumPartLoadRatio() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::OptimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isOptimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::OptimumPartLoadRatio);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::OptimumPartLoadRatio, optimumPartLoadRatio);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetOptimumPartLoadRatio() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::OptimumPartLoadRatio, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::designEnteringCondenserWaterTemperature() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignEnteringCondenserWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignEnteringCondenserWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignEnteringCondenserWaterTemperature);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setDesignEnteringCondenserWaterTemperature(double designEnteringCondenserWaterTemperature) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignEnteringCondenserWaterTemperature,
                                    designEnteringCondenserWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetDesignEnteringCondenserWaterTemperature() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignEnteringCondenserWaterTemperature, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::designLeavingChilledWaterTemperature() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignLeavingChilledWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignLeavingChilledWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignLeavingChilledWaterTemperature);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setDesignLeavingChilledWaterTemperature(double designLeavingChilledWaterTemperature) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignLeavingChilledWaterTemperature,
                                    designLeavingChilledWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetDesignLeavingChilledWaterTemperature() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignLeavingChilledWaterTemperature, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ChillerHeaterAbsorptionDoubleEffect_Impl::designChilledWaterFlowRate() const {
      return getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate, true);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignChilledWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignChilledWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetDesignChilledWaterFlowRate() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate, "");
      OS_ASSERT(result);
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::autosizeDesignChilledWaterFlowRate() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ChillerHeaterAbsorptionDoubleEffect_Impl::designCondenserWaterFlowRate() const {
      return getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate, true);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignCondenserWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignCondenserWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
      const bool result =
        setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetDesignCondenserWaterFlowRate() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate, "");
      OS_ASSERT(result);
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::autosizeDesignCondenserWaterFlowRate() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ChillerHeaterAbsorptionDoubleEffect_Impl::designHotWaterFlowRate() const {
      return getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate, true);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignHotWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isDesignHotWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setDesignHotWaterFlowRate(double designHotWaterFlowRate) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate, designHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetDesignHotWaterFlowRate() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate, "");
      OS_ASSERT(result);
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::autosizeDesignHotWaterFlowRate() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    std::string ChillerHeaterAbsorptionDoubleEffect_Impl::temperatureCurveInputVariable() const {
      if (auto value = getString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::TemperatureCurveInputVariable, false)) {
        return *value;
      }
      return "EnteringCondenser";
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isTemperatureCurveInputVariableDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::TemperatureCurveInputVariable);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setTemperatureCurveInputVariable(const std::string& temperatureCurveInputVariable) {
      const bool result =
        setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::TemperatureCurveInputVariable, temperatureCurveInputVariable);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetTemperatureCurveInputVariable() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::TemperatureCurveInputVariable, "");
      OS_ASSERT(result);
    }

    std::string ChillerHeaterAbsorptionDoubleEffect_Impl::condenserType() const {
      if (auto value = getString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::CondenserType, false)) {
        return *value;
      }
      return "WaterCooled";
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::CondenserType);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setCondenserType(const std::string& condenserType) {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::CondenserType, condenserType);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetCondenserType() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::CondenserType, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::chilledWaterTemperatureLowerLimit() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterTemperatureLowerLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isChilledWaterTemperatureLowerLimitDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterTemperatureLowerLimit);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setChilledWaterTemperatureLowerLimit(double chilledWaterTemperatureLowerLimit) {
      const bool result =
        setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterTemperatureLowerLimit, chilledWaterTemperatureLowerLimit);
      OS_ASSERT(result);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetChilledWaterTemperatureLowerLimit() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterTemperatureLowerLimit, "");
      OS_ASSERT(result);
    }

    double ChillerHeaterAbsorptionDoubleEffect_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::ChillerHeater_Absorption_DoubleEffectFields::SizingFactor);
    }

    bool ChillerHeaterAbsorptionDoubleEffect_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(openstudio::ChillerHeater_Absorption_DoubleEffectFields::SizingFactor, sizingFactor);
      return result;
    }

    void ChillerHeaterAbsorptionDoubleEffect_Impl::resetSizingFactor() {
      const bool result = setString(openstudio::ChillerHeater_Absorption_DoubleEffectFields::SizingFactor, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> ChillerHeaterAbsorptionDoubleEffect_Impl::temperatureCurveInputVariableValues() const {
      return openstudio::epmodel::ChillerHeaterAbsorptionDoubleEffect::temperatureCurveInputVariableValues();
    }

    std::vector<std::string> ChillerHeaterAbsorptionDoubleEffect_Impl::condenserTypeValues() const {
      return openstudio::epmodel::ChillerHeaterAbsorptionDoubleEffect::condenserTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
