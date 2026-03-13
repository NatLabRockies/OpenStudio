/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/BoilerSteam.hpp"
#include "StraightComponent/BoilerSteam_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Boiler_Steam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  BoilerSteam::BoilerSteam(const Model& model) : ModelObject(BoilerSteam::iddObjectType(), model) {}

  BoilerSteam::BoilerSteam(std::shared_ptr<detail::BoilerSteam_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType BoilerSteam::iddObjectType() {
    return IddObjectType::Boiler_Steam;
  }

  std::vector<std::string> BoilerSteam::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Boiler_SteamFields::FuelType);
  }

  std::string BoilerSteam::fuelType() const {
    return getImpl<detail::BoilerSteam_Impl>()->fuelType();
  }

  bool BoilerSteam::setFuelType(const std::string& fuelType) {
    return getImpl<detail::BoilerSteam_Impl>()->setFuelType(fuelType);
  }

  boost::optional<double> BoilerSteam::maximumOperatingPressure() const {
    return getImpl<detail::BoilerSteam_Impl>()->maximumOperatingPressure();
  }

  bool BoilerSteam::setMaximumOperatingPressure(double maximumOperatingPressure) {
    return getImpl<detail::BoilerSteam_Impl>()->setMaximumOperatingPressure(maximumOperatingPressure);
  }

  void BoilerSteam::resetMaximumOperatingPressure() {
    getImpl<detail::BoilerSteam_Impl>()->resetMaximumOperatingPressure();
  }

  boost::optional<double> BoilerSteam::theoreticalEfficiency() const {
    return getImpl<detail::BoilerSteam_Impl>()->theoreticalEfficiency();
  }

  bool BoilerSteam::setTheoreticalEfficiency(double theoreticalEfficiency) {
    return getImpl<detail::BoilerSteam_Impl>()->setTheoreticalEfficiency(theoreticalEfficiency);
  }

  void BoilerSteam::resetTheoreticalEfficiency() {
    getImpl<detail::BoilerSteam_Impl>()->resetTheoreticalEfficiency();
  }

  boost::optional<double> BoilerSteam::designOutletSteamTemperature() const {
    return getImpl<detail::BoilerSteam_Impl>()->designOutletSteamTemperature();
  }

  bool BoilerSteam::setDesignOutletSteamTemperature(double designOutletSteamTemperature) {
    return getImpl<detail::BoilerSteam_Impl>()->setDesignOutletSteamTemperature(designOutletSteamTemperature);
  }

  void BoilerSteam::resetDesignOutletSteamTemperature() {
    getImpl<detail::BoilerSteam_Impl>()->resetDesignOutletSteamTemperature();
  }

  boost::optional<double> BoilerSteam::nominalCapacity() const {
    return getImpl<detail::BoilerSteam_Impl>()->nominalCapacity();
  }

  bool BoilerSteam::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::BoilerSteam_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void BoilerSteam::resetNominalCapacity() {
    getImpl<detail::BoilerSteam_Impl>()->resetNominalCapacity();
  }

  void BoilerSteam::autosizeNominalCapacity() {
    getImpl<detail::BoilerSteam_Impl>()->autosizeNominalCapacity();
  }

  bool BoilerSteam::isNominalCapacityAutosized() const {
    return getImpl<detail::BoilerSteam_Impl>()->isNominalCapacityAutosized();
  }

  boost::optional<double> BoilerSteam::minimumPartLoadRatio() const {
    return getImpl<detail::BoilerSteam_Impl>()->minimumPartLoadRatio();
  }

  bool BoilerSteam::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::BoilerSteam_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  void BoilerSteam::resetMinimumPartLoadRatio() {
    getImpl<detail::BoilerSteam_Impl>()->resetMinimumPartLoadRatio();
  }

  boost::optional<double> BoilerSteam::maximumPartLoadRatio() const {
    return getImpl<detail::BoilerSteam_Impl>()->maximumPartLoadRatio();
  }

  bool BoilerSteam::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::BoilerSteam_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  void BoilerSteam::resetMaximumPartLoadRatio() {
    getImpl<detail::BoilerSteam_Impl>()->resetMaximumPartLoadRatio();
  }

  boost::optional<double> BoilerSteam::optimumPartLoadRatio() const {
    return getImpl<detail::BoilerSteam_Impl>()->optimumPartLoadRatio();
  }

  bool BoilerSteam::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::BoilerSteam_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  void BoilerSteam::resetOptimumPartLoadRatio() {
    getImpl<detail::BoilerSteam_Impl>()->resetOptimumPartLoadRatio();
  }

  boost::optional<double> BoilerSteam::coefficient1ofFuelUseFunctionofPartLoadRatioCurve() const {
    return getImpl<detail::BoilerSteam_Impl>()->coefficient1ofFuelUseFunctionofPartLoadRatioCurve();
  }

  bool BoilerSteam::setCoefficient1ofFuelUseFunctionofPartLoadRatioCurve(double coefficient1ofFuelUseFunctionofPartLoadRatioCurve) {
    return getImpl<detail::BoilerSteam_Impl>()->setCoefficient1ofFuelUseFunctionofPartLoadRatioCurve(
      coefficient1ofFuelUseFunctionofPartLoadRatioCurve);
  }

  void BoilerSteam::resetCoefficient1ofFuelUseFunctionofPartLoadRatioCurve() {
    getImpl<detail::BoilerSteam_Impl>()->resetCoefficient1ofFuelUseFunctionofPartLoadRatioCurve();
  }

  boost::optional<double> BoilerSteam::coefficient2ofFuelUseFunctionofPartLoadRatioCurve() const {
    return getImpl<detail::BoilerSteam_Impl>()->coefficient2ofFuelUseFunctionofPartLoadRatioCurve();
  }

  bool BoilerSteam::setCoefficient2ofFuelUseFunctionofPartLoadRatioCurve(double coefficient2ofFuelUseFunctionofPartLoadRatioCurve) {
    return getImpl<detail::BoilerSteam_Impl>()->setCoefficient2ofFuelUseFunctionofPartLoadRatioCurve(
      coefficient2ofFuelUseFunctionofPartLoadRatioCurve);
  }

  void BoilerSteam::resetCoefficient2ofFuelUseFunctionofPartLoadRatioCurve() {
    getImpl<detail::BoilerSteam_Impl>()->resetCoefficient2ofFuelUseFunctionofPartLoadRatioCurve();
  }

  boost::optional<double> BoilerSteam::coefficient3ofFuelUseFunctionofPartLoadRatioCurve() const {
    return getImpl<detail::BoilerSteam_Impl>()->coefficient3ofFuelUseFunctionofPartLoadRatioCurve();
  }

  bool BoilerSteam::setCoefficient3ofFuelUseFunctionofPartLoadRatioCurve(double coefficient3ofFuelUseFunctionofPartLoadRatioCurve) {
    return getImpl<detail::BoilerSteam_Impl>()->setCoefficient3ofFuelUseFunctionofPartLoadRatioCurve(
      coefficient3ofFuelUseFunctionofPartLoadRatioCurve);
  }

  void BoilerSteam::resetCoefficient3ofFuelUseFunctionofPartLoadRatioCurve() {
    getImpl<detail::BoilerSteam_Impl>()->resetCoefficient3ofFuelUseFunctionofPartLoadRatioCurve();
  }

  double BoilerSteam::sizingFactor() const {
    return getImpl<detail::BoilerSteam_Impl>()->sizingFactor();
  }

  bool BoilerSteam::setSizingFactor(double sizingFactor) {
    return getImpl<detail::BoilerSteam_Impl>()->setSizingFactor(sizingFactor);
  }

  void BoilerSteam::resetSizingFactor() {
    getImpl<detail::BoilerSteam_Impl>()->resetSizingFactor();
  }

  bool BoilerSteam::isSizingFactorDefaulted() const {
    return getImpl<detail::BoilerSteam_Impl>()->isSizingFactorDefaulted();
  }

  std::string BoilerSteam::endUseSubcategory() const {
    return getImpl<detail::BoilerSteam_Impl>()->endUseSubcategory();
  }

  bool BoilerSteam::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::BoilerSteam_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string BoilerSteam_Impl::fuelType() const {
      const auto value = getString(openstudio::Boiler_SteamFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerSteam_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Boiler_SteamFields::FuelType, fuelType);
    }

    boost::optional<double> BoilerSteam_Impl::maximumOperatingPressure() const {
      return getDouble(openstudio::Boiler_SteamFields::MaximumOperatingPressure, true);
    }

    bool BoilerSteam_Impl::setMaximumOperatingPressure(double maximumOperatingPressure) {
      const bool result = setDouble(openstudio::Boiler_SteamFields::MaximumOperatingPressure, maximumOperatingPressure);
      OS_ASSERT(result);
      return result;
    }

    void BoilerSteam_Impl::resetMaximumOperatingPressure() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::MaximumOperatingPressure, ""));
    }

    boost::optional<double> BoilerSteam_Impl::theoreticalEfficiency() const {
      return getDouble(openstudio::Boiler_SteamFields::TheoreticalEfficiency, true);
    }

    bool BoilerSteam_Impl::setTheoreticalEfficiency(double theoreticalEfficiency) {
      return setDouble(openstudio::Boiler_SteamFields::TheoreticalEfficiency, theoreticalEfficiency);
    }

    void BoilerSteam_Impl::resetTheoreticalEfficiency() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::TheoreticalEfficiency, ""));
    }

    boost::optional<double> BoilerSteam_Impl::designOutletSteamTemperature() const {
      return getDouble(openstudio::Boiler_SteamFields::DesignOutletSteamTemperature, true);
    }

    bool BoilerSteam_Impl::setDesignOutletSteamTemperature(double designOutletSteamTemperature) {
      const bool result = setDouble(openstudio::Boiler_SteamFields::DesignOutletSteamTemperature, designOutletSteamTemperature);
      OS_ASSERT(result);
      return result;
    }

    void BoilerSteam_Impl::resetDesignOutletSteamTemperature() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::DesignOutletSteamTemperature, ""));
    }

    boost::optional<double> BoilerSteam_Impl::nominalCapacity() const {
      return getDouble(openstudio::Boiler_SteamFields::NominalCapacity, true);
    }

    bool BoilerSteam_Impl::setNominalCapacity(double nominalCapacity) {
      const bool result = setDouble(openstudio::Boiler_SteamFields::NominalCapacity, nominalCapacity);
      OS_ASSERT(result);
      return result;
    }

    void BoilerSteam_Impl::resetNominalCapacity() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::NominalCapacity, ""));
    }

    void BoilerSteam_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::NominalCapacity, "autosize"));
    }

    bool BoilerSteam_Impl::isNominalCapacityAutosized() const {
      if (const auto value = getString(openstudio::Boiler_SteamFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> BoilerSteam_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::Boiler_SteamFields::MinimumPartLoadRatio, true);
    }

    bool BoilerSteam_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::Boiler_SteamFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    void BoilerSteam_Impl::resetMinimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::MinimumPartLoadRatio, ""));
    }

    boost::optional<double> BoilerSteam_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::Boiler_SteamFields::MaximumPartLoadRatio, true);
    }

    bool BoilerSteam_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::Boiler_SteamFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    void BoilerSteam_Impl::resetMaximumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::MaximumPartLoadRatio, ""));
    }

    boost::optional<double> BoilerSteam_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::Boiler_SteamFields::OptimumPartLoadRatio, true);
    }

    bool BoilerSteam_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::Boiler_SteamFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    void BoilerSteam_Impl::resetOptimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::OptimumPartLoadRatio, ""));
    }

    boost::optional<double> BoilerSteam_Impl::coefficient1ofFuelUseFunctionofPartLoadRatioCurve() const {
      return getDouble(openstudio::Boiler_SteamFields::Coefficient1ofFuelUseFunctionofPartLoadRatioCurve, true);
    }

    bool BoilerSteam_Impl::setCoefficient1ofFuelUseFunctionofPartLoadRatioCurve(double coefficient1ofFuelUseFunctionofPartLoadRatioCurve) {
      const bool result = setDouble(openstudio::Boiler_SteamFields::Coefficient1ofFuelUseFunctionofPartLoadRatioCurve,
                                    coefficient1ofFuelUseFunctionofPartLoadRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void BoilerSteam_Impl::resetCoefficient1ofFuelUseFunctionofPartLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::Coefficient1ofFuelUseFunctionofPartLoadRatioCurve, ""));
    }

    boost::optional<double> BoilerSteam_Impl::coefficient2ofFuelUseFunctionofPartLoadRatioCurve() const {
      return getDouble(openstudio::Boiler_SteamFields::Coefficient2ofFuelUseFunctionofPartLoadRatioCurve, true);
    }

    bool BoilerSteam_Impl::setCoefficient2ofFuelUseFunctionofPartLoadRatioCurve(double coefficient2ofFuelUseFunctionofPartLoadRatioCurve) {
      const bool result = setDouble(openstudio::Boiler_SteamFields::Coefficient2ofFuelUseFunctionofPartLoadRatioCurve,
                                    coefficient2ofFuelUseFunctionofPartLoadRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void BoilerSteam_Impl::resetCoefficient2ofFuelUseFunctionofPartLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::Coefficient2ofFuelUseFunctionofPartLoadRatioCurve, ""));
    }

    boost::optional<double> BoilerSteam_Impl::coefficient3ofFuelUseFunctionofPartLoadRatioCurve() const {
      return getDouble(openstudio::Boiler_SteamFields::Coefficient3ofFuelUseFunctionofPartLoadRatioCurve, true);
    }

    bool BoilerSteam_Impl::setCoefficient3ofFuelUseFunctionofPartLoadRatioCurve(double coefficient3ofFuelUseFunctionofPartLoadRatioCurve) {
      const bool result = setDouble(openstudio::Boiler_SteamFields::Coefficient3ofFuelUseFunctionofPartLoadRatioCurve,
                                    coefficient3ofFuelUseFunctionofPartLoadRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void BoilerSteam_Impl::resetCoefficient3ofFuelUseFunctionofPartLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::Coefficient3ofFuelUseFunctionofPartLoadRatioCurve, ""));
    }

    double BoilerSteam_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::Boiler_SteamFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerSteam_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::Boiler_SteamFields::SizingFactor, sizingFactor);
    }

    void BoilerSteam_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::Boiler_SteamFields::SizingFactor, ""));
    }

    bool BoilerSteam_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::Boiler_SteamFields::SizingFactor);
    }

    std::string BoilerSteam_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Boiler_SteamFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool BoilerSteam_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::Boiler_SteamFields::EndUseSubcategory, endUseSubcategory);
    }

    std::vector<std::string> BoilerSteam_Impl::fuelTypeValues() const {
      return BoilerSteam::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
