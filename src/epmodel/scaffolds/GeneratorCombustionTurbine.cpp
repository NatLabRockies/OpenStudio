/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorCombustionTurbine.hpp"
#include "GeneratorCombustionTurbine_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_CombustionTurbine_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorCombustionTurbine::GeneratorCombustionTurbine(const Model& model) : ModelObject(GeneratorCombustionTurbine::iddObjectType(), model) {}

  GeneratorCombustionTurbine::GeneratorCombustionTurbine(std::shared_ptr<detail::GeneratorCombustionTurbine_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorCombustionTurbine::iddObjectType() {
    return IddObjectType::Generator_CombustionTurbine;
  }

  std::vector<std::string> GeneratorCombustionTurbine::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Generator_CombustionTurbineFields::FuelType);
  }

  boost::optional<double> GeneratorCombustionTurbine::ratedPowerOutput() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->ratedPowerOutput();
  }

  bool GeneratorCombustionTurbine::setRatedPowerOutput(double ratedPowerOutput) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setRatedPowerOutput(ratedPowerOutput);
  }

  boost::optional<double> GeneratorCombustionTurbine::minimumPartLoadRatio() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->minimumPartLoadRatio();
  }

  bool GeneratorCombustionTurbine::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  boost::optional<double> GeneratorCombustionTurbine::maximumPartLoadRatio() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->maximumPartLoadRatio();
  }

  bool GeneratorCombustionTurbine::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  boost::optional<double> GeneratorCombustionTurbine::optimumPartLoadRatio() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->optimumPartLoadRatio();
  }

  bool GeneratorCombustionTurbine::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  boost::optional<double> GeneratorCombustionTurbine::coefficient1ofUFactorTimesAreaCurve() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->coefficient1ofUFactorTimesAreaCurve();
  }

  bool GeneratorCombustionTurbine::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setCoefficient1ofUFactorTimesAreaCurve(coefficient1ofUFactorTimesAreaCurve);
  }

  boost::optional<double> GeneratorCombustionTurbine::coefficient2ofUFactorTimesAreaCurve() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->coefficient2ofUFactorTimesAreaCurve();
  }

  bool GeneratorCombustionTurbine::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setCoefficient2ofUFactorTimesAreaCurve(coefficient2ofUFactorTimesAreaCurve);
  }

  boost::optional<double> GeneratorCombustionTurbine::maximumExhaustFlowperUnitofPowerOutput() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->maximumExhaustFlowperUnitofPowerOutput();
  }

  bool GeneratorCombustionTurbine::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setMaximumExhaustFlowperUnitofPowerOutput(maximumExhaustFlowperUnitofPowerOutput);
  }

  boost::optional<double> GeneratorCombustionTurbine::designMinimumExhaustTemperature() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->designMinimumExhaustTemperature();
  }

  bool GeneratorCombustionTurbine::setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setDesignMinimumExhaustTemperature(designMinimumExhaustTemperature);
  }

  boost::optional<double> GeneratorCombustionTurbine::designAirInletTemperature() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->designAirInletTemperature();
  }

  bool GeneratorCombustionTurbine::setDesignAirInletTemperature(double designAirInletTemperature) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setDesignAirInletTemperature(designAirInletTemperature);
  }

  boost::optional<double> GeneratorCombustionTurbine::fuelHigherHeatingValue() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->fuelHigherHeatingValue();
  }

  bool GeneratorCombustionTurbine::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setFuelHigherHeatingValue(fuelHigherHeatingValue);
  }

  double GeneratorCombustionTurbine::designHeatRecoveryWaterFlowRate() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->designHeatRecoveryWaterFlowRate();
  }

  bool GeneratorCombustionTurbine::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->isDesignHeatRecoveryWaterFlowRateDefaulted();
  }

  bool GeneratorCombustionTurbine::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
  }

  void GeneratorCombustionTurbine::resetDesignHeatRecoveryWaterFlowRate() {
    getImpl<detail::GeneratorCombustionTurbine_Impl>()->resetDesignHeatRecoveryWaterFlowRate();
  }

  std::string GeneratorCombustionTurbine::fuelType() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->fuelType();
  }

  bool GeneratorCombustionTurbine::isFuelTypeDefaulted() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->isFuelTypeDefaulted();
  }

  bool GeneratorCombustionTurbine::setFuelType(const std::string& fuelType) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setFuelType(fuelType);
  }

  void GeneratorCombustionTurbine::resetFuelType() {
    getImpl<detail::GeneratorCombustionTurbine_Impl>()->resetFuelType();
  }

  double GeneratorCombustionTurbine::heatRecoveryMaximumTemperature() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->heatRecoveryMaximumTemperature();
  }

  bool GeneratorCombustionTurbine::isHeatRecoveryMaximumTemperatureDefaulted() const {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->isHeatRecoveryMaximumTemperatureDefaulted();
  }

  bool GeneratorCombustionTurbine::setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature) {
    return getImpl<detail::GeneratorCombustionTurbine_Impl>()->setHeatRecoveryMaximumTemperature(heatRecoveryMaximumTemperature);
  }

  void GeneratorCombustionTurbine::resetHeatRecoveryMaximumTemperature() {
    getImpl<detail::GeneratorCombustionTurbine_Impl>()->resetHeatRecoveryMaximumTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> GeneratorCombustionTurbine_Impl::ratedPowerOutput() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::RatedPowerOutput, true);
    }

    bool GeneratorCombustionTurbine_Impl::setRatedPowerOutput(double ratedPowerOutput) {
      const bool result = setDouble(openstudio::Generator_CombustionTurbineFields::RatedPowerOutput, ratedPowerOutput);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::MinimumPartLoadRatio, true);
    }

    bool GeneratorCombustionTurbine_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::Generator_CombustionTurbineFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::MaximumPartLoadRatio, true);
    }

    bool GeneratorCombustionTurbine_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::Generator_CombustionTurbineFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::OptimumPartLoadRatio, true);
    }

    bool GeneratorCombustionTurbine_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      const bool result = setDouble(openstudio::Generator_CombustionTurbineFields::OptimumPartLoadRatio, optimumPartLoadRatio);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::coefficient1ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, true);
    }

    bool GeneratorCombustionTurbine_Impl::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
      const bool result =
        setDouble(openstudio::Generator_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, coefficient1ofUFactorTimesAreaCurve);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::coefficient2ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, true);
    }

    bool GeneratorCombustionTurbine_Impl::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
      return setDouble(openstudio::Generator_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, coefficient2ofUFactorTimesAreaCurve);
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::maximumExhaustFlowperUnitofPowerOutput() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, true);
    }

    bool GeneratorCombustionTurbine_Impl::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
      const bool result =
        setDouble(openstudio::Generator_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, maximumExhaustFlowperUnitofPowerOutput);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::designMinimumExhaustTemperature() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::DesignMinimumExhaustTemperature, true);
    }

    bool GeneratorCombustionTurbine_Impl::setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature) {
      const bool result = setDouble(openstudio::Generator_CombustionTurbineFields::DesignMinimumExhaustTemperature, designMinimumExhaustTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::designAirInletTemperature() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::DesignAirInletTemperature, true);
    }

    bool GeneratorCombustionTurbine_Impl::setDesignAirInletTemperature(double designAirInletTemperature) {
      const bool result = setDouble(openstudio::Generator_CombustionTurbineFields::DesignAirInletTemperature, designAirInletTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GeneratorCombustionTurbine_Impl::fuelHigherHeatingValue() const {
      return getDouble(openstudio::Generator_CombustionTurbineFields::FuelHigherHeatingValue, true);
    }

    bool GeneratorCombustionTurbine_Impl::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
      const bool result = setDouble(openstudio::Generator_CombustionTurbineFields::FuelHigherHeatingValue, fuelHigherHeatingValue);
      OS_ASSERT(result);
      return result;
    }

    double GeneratorCombustionTurbine_Impl::designHeatRecoveryWaterFlowRate() const {
      if (auto value = getDouble(openstudio::Generator_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, false)) {
        return *value;
      }
      return 0.0;
    }

    bool GeneratorCombustionTurbine_Impl::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::Generator_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate);
    }

    bool GeneratorCombustionTurbine_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
      return setDouble(openstudio::Generator_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
    }

    void GeneratorCombustionTurbine_Impl::resetDesignHeatRecoveryWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Generator_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, ""));
    }

    std::string GeneratorCombustionTurbine_Impl::fuelType() const {
      if (auto value = getString(openstudio::Generator_CombustionTurbineFields::FuelType, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "NaturalGas";
    }

    bool GeneratorCombustionTurbine_Impl::isFuelTypeDefaulted() const {
      return isEmpty(openstudio::Generator_CombustionTurbineFields::FuelType);
    }

    bool GeneratorCombustionTurbine_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Generator_CombustionTurbineFields::FuelType, fuelType);
    }

    void GeneratorCombustionTurbine_Impl::resetFuelType() {
      OS_ASSERT(setString(openstudio::Generator_CombustionTurbineFields::FuelType, ""));
    }

    double GeneratorCombustionTurbine_Impl::heatRecoveryMaximumTemperature() const {
      if (auto value = getDouble(openstudio::Generator_CombustionTurbineFields::HeatRecoveryMaximumTemperature, false)) {
        return *value;
      }
      return 80.0;
    }

    bool GeneratorCombustionTurbine_Impl::isHeatRecoveryMaximumTemperatureDefaulted() const {
      return isEmpty(openstudio::Generator_CombustionTurbineFields::HeatRecoveryMaximumTemperature);
    }

    bool GeneratorCombustionTurbine_Impl::setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature) {
      return setDouble(openstudio::Generator_CombustionTurbineFields::HeatRecoveryMaximumTemperature, heatRecoveryMaximumTemperature);
    }

    void GeneratorCombustionTurbine_Impl::resetHeatRecoveryMaximumTemperature() {
      OS_ASSERT(setString(openstudio::Generator_CombustionTurbineFields::HeatRecoveryMaximumTemperature, ""));
    }

    std::vector<std::string> GeneratorCombustionTurbine_Impl::fuelTypeValues() const {
      return openstudio::epmodel::GeneratorCombustionTurbine::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
