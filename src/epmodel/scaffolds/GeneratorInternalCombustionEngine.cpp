/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorInternalCombustionEngine.hpp"
#include "GeneratorInternalCombustionEngine_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_InternalCombustionEngine_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorInternalCombustionEngine::GeneratorInternalCombustionEngine(const Model& model)
    : ModelObject(GeneratorInternalCombustionEngine::iddObjectType(), model) {}

  GeneratorInternalCombustionEngine::GeneratorInternalCombustionEngine(std::shared_ptr<detail::GeneratorInternalCombustionEngine_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorInternalCombustionEngine::iddObjectType() {
    return IddObjectType::Generator_InternalCombustionEngine;
  }

  std::vector<std::string> GeneratorInternalCombustionEngine::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_InternalCombustionEngineFields::FuelType);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::ratedPowerOutput() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->ratedPowerOutput();
  }

  bool GeneratorInternalCombustionEngine::setRatedPowerOutput(double ratedPowerOutput) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setRatedPowerOutput(ratedPowerOutput);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::minimumPartLoadRatio() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->minimumPartLoadRatio();
  }

  bool GeneratorInternalCombustionEngine::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::maximumPartLoadRatio() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->maximumPartLoadRatio();
  }

  bool GeneratorInternalCombustionEngine::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::optimumPartLoadRatio() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->optimumPartLoadRatio();
  }

  bool GeneratorInternalCombustionEngine::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::coefficient1ofUFactorTimesAreaCurve() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->coefficient1ofUFactorTimesAreaCurve();
  }

  bool GeneratorInternalCombustionEngine::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setCoefficient1ofUFactorTimesAreaCurve(coefficient1ofUFactorTimesAreaCurve);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::coefficient2ofUFactorTimesAreaCurve() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->coefficient2ofUFactorTimesAreaCurve();
  }

  bool GeneratorInternalCombustionEngine::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setCoefficient2ofUFactorTimesAreaCurve(coefficient2ofUFactorTimesAreaCurve);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::maximumExhaustFlowperUnitofPowerOutput() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->maximumExhaustFlowperUnitofPowerOutput();
  }

  bool GeneratorInternalCombustionEngine::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setMaximumExhaustFlowperUnitofPowerOutput(
      maximumExhaustFlowperUnitofPowerOutput);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::designMinimumExhaustTemperature() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->designMinimumExhaustTemperature();
  }

  bool GeneratorInternalCombustionEngine::setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setDesignMinimumExhaustTemperature(designMinimumExhaustTemperature);
  }

  boost::optional<double> GeneratorInternalCombustionEngine::fuelHigherHeatingValue() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->fuelHigherHeatingValue();
  }

  bool GeneratorInternalCombustionEngine::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setFuelHigherHeatingValue(fuelHigherHeatingValue);
  }

  double GeneratorInternalCombustionEngine::designHeatRecoveryWaterFlowRate() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->designHeatRecoveryWaterFlowRate();
  }

  bool GeneratorInternalCombustionEngine::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->isDesignHeatRecoveryWaterFlowRateDefaulted();
  }

  bool GeneratorInternalCombustionEngine::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
  }

  void GeneratorInternalCombustionEngine::resetDesignHeatRecoveryWaterFlowRate() {
    getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->resetDesignHeatRecoveryWaterFlowRate();
  }

  std::string GeneratorInternalCombustionEngine::fuelType() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->fuelType();
  }

  bool GeneratorInternalCombustionEngine::isFuelTypeDefaulted() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->isFuelTypeDefaulted();
  }

  bool GeneratorInternalCombustionEngine::setFuelType(const std::string& fuelType) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setFuelType(fuelType);
  }

  void GeneratorInternalCombustionEngine::resetFuelType() {
    getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->resetFuelType();
  }

  double GeneratorInternalCombustionEngine::heatRecoveryMaximumTemperature() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->heatRecoveryMaximumTemperature();
  }

  bool GeneratorInternalCombustionEngine::isHeatRecoveryMaximumTemperatureDefaulted() const {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->isHeatRecoveryMaximumTemperatureDefaulted();
  }

  bool GeneratorInternalCombustionEngine::setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature) {
    return getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->setHeatRecoveryMaximumTemperature(heatRecoveryMaximumTemperature);
  }

  void GeneratorInternalCombustionEngine::resetHeatRecoveryMaximumTemperature() {
    getImpl<detail::GeneratorInternalCombustionEngine_Impl>()->resetHeatRecoveryMaximumTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::ratedPowerOutput() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::RatedPowerOutput, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setRatedPowerOutput(double ratedPowerOutput) {
      const bool result = setDouble(openstudio::Generator_InternalCombustionEngineFields::RatedPowerOutput, ratedPowerOutput);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::MinimumPartLoadRatio, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::Generator_InternalCombustionEngineFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::MaximumPartLoadRatio, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::Generator_InternalCombustionEngineFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::OptimumPartLoadRatio, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      const bool result = setDouble(openstudio::Generator_InternalCombustionEngineFields::OptimumPartLoadRatio, optimumPartLoadRatio);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::coefficient1ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::Coefficient1ofUFactorTimesAreaCurve, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
      const bool result =
        setDouble(openstudio::Generator_InternalCombustionEngineFields::Coefficient1ofUFactorTimesAreaCurve, coefficient1ofUFactorTimesAreaCurve);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::coefficient2ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::Coefficient2ofUFactorTimesAreaCurve, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
      return setDouble(openstudio::Generator_InternalCombustionEngineFields::Coefficient2ofUFactorTimesAreaCurve,
                       coefficient2ofUFactorTimesAreaCurve);
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::maximumExhaustFlowperUnitofPowerOutput() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::MaximumExhaustFlowperUnitofPowerOutput, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
      const bool result = setDouble(openstudio::Generator_InternalCombustionEngineFields::MaximumExhaustFlowperUnitofPowerOutput,
                                    maximumExhaustFlowperUnitofPowerOutput);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::designMinimumExhaustTemperature() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::DesignMinimumExhaustTemperature, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature) {
      const bool result =
        setDouble(openstudio::Generator_InternalCombustionEngineFields::DesignMinimumExhaustTemperature, designMinimumExhaustTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorInternalCombustionEngine_Impl::fuelHigherHeatingValue() const {
      return getDouble(openstudio::Generator_InternalCombustionEngineFields::FuelHigherHeatingValue, true);
    }

    bool GeneratorInternalCombustionEngine_Impl::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
      const bool result = setDouble(openstudio::Generator_InternalCombustionEngineFields::FuelHigherHeatingValue, fuelHigherHeatingValue);
      OS_ASSERT(result);
      return result;
    }

    double GeneratorInternalCombustionEngine_Impl::designHeatRecoveryWaterFlowRate() const {
      if (auto value = getDouble(openstudio::Generator_InternalCombustionEngineFields::DesignHeatRecoveryWaterFlowRate, false)) {
        return *value;
      }
      return 0.0;
    }

    bool GeneratorInternalCombustionEngine_Impl::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::Generator_InternalCombustionEngineFields::DesignHeatRecoveryWaterFlowRate);
    }

    bool GeneratorInternalCombustionEngine_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
      return setDouble(openstudio::Generator_InternalCombustionEngineFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
    }

    void GeneratorInternalCombustionEngine_Impl::resetDesignHeatRecoveryWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Generator_InternalCombustionEngineFields::DesignHeatRecoveryWaterFlowRate, ""));
    }

    std::string GeneratorInternalCombustionEngine_Impl::fuelType() const {
      if (auto value = getString(openstudio::Generator_InternalCombustionEngineFields::FuelType, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "Diesel";
    }

    bool GeneratorInternalCombustionEngine_Impl::isFuelTypeDefaulted() const {
      return isEmpty(openstudio::Generator_InternalCombustionEngineFields::FuelType);
    }

    bool GeneratorInternalCombustionEngine_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Generator_InternalCombustionEngineFields::FuelType, fuelType);
    }

    void GeneratorInternalCombustionEngine_Impl::resetFuelType() {
      OS_ASSERT(setString(openstudio::Generator_InternalCombustionEngineFields::FuelType, ""));
    }

    double GeneratorInternalCombustionEngine_Impl::heatRecoveryMaximumTemperature() const {
      if (auto value = getDouble(openstudio::Generator_InternalCombustionEngineFields::HeatRecoveryMaximumTemperature, false)) {
        return *value;
      }
      return 80.0;
    }

    bool GeneratorInternalCombustionEngine_Impl::isHeatRecoveryMaximumTemperatureDefaulted() const {
      return isEmpty(openstudio::Generator_InternalCombustionEngineFields::HeatRecoveryMaximumTemperature);
    }

    bool GeneratorInternalCombustionEngine_Impl::setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature) {
      return setDouble(openstudio::Generator_InternalCombustionEngineFields::HeatRecoveryMaximumTemperature, heatRecoveryMaximumTemperature);
    }

    void GeneratorInternalCombustionEngine_Impl::resetHeatRecoveryMaximumTemperature() {
      OS_ASSERT(setString(openstudio::Generator_InternalCombustionEngineFields::HeatRecoveryMaximumTemperature, ""));
    }

    std::vector<std::string> GeneratorInternalCombustionEngine_Impl::fuelTypeValues() const {
      return openstudio::epmodel::GeneratorInternalCombustionEngine::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
