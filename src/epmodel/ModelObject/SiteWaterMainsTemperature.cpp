/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteWaterMainsTemperature.hpp"
#include "SiteWaterMainsTemperature_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Site_WaterMainsTemperature_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteWaterMainsTemperature::SiteWaterMainsTemperature(const Model& model) : ModelObject(SiteWaterMainsTemperature::iddObjectType(), model) {
    OS_ASSERT(setCalculationMethod("CorrelationFromWeatherFile"));
    OS_ASSERT(setTemperatureMultiplier(1.0));
    OS_ASSERT(setTemperatureOffset(0.0));
  }

  SiteWaterMainsTemperature::SiteWaterMainsTemperature(std::shared_ptr<detail::SiteWaterMainsTemperature_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteWaterMainsTemperature::iddObjectType() {
    return IddObjectType::Site_WaterMainsTemperature;
  }

  std::vector<std::string> SiteWaterMainsTemperature::calculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Site_WaterMainsTemperatureFields::CalculationMethod);
  }

  std::vector<std::string> SiteWaterMainsTemperature::validCalculationMethodValues() {
    return SiteWaterMainsTemperature::calculationMethodValues();
  }

  std::string SiteWaterMainsTemperature::calculationMethod() const {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->calculationMethod();
  }

  bool SiteWaterMainsTemperature::setCalculationMethod(const std::string& calculationMethod) {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->setCalculationMethod(calculationMethod);
  }

  boost::optional<double> SiteWaterMainsTemperature::annualAverageOutdoorAirTemperature() const {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->annualAverageOutdoorAirTemperature();
  }

  bool SiteWaterMainsTemperature::setAnnualAverageOutdoorAirTemperature(double annualAverageOutdoorAirTemperature) {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->setAnnualAverageOutdoorAirTemperature(annualAverageOutdoorAirTemperature);
  }

  void SiteWaterMainsTemperature::resetAnnualAverageOutdoorAirTemperature() {
    getImpl<detail::SiteWaterMainsTemperature_Impl>()->resetAnnualAverageOutdoorAirTemperature();
  }

  boost::optional<double> SiteWaterMainsTemperature::maximumDifferenceInMonthlyAverageOutdoorAirTemperatures() const {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->maximumDifferenceInMonthlyAverageOutdoorAirTemperatures();
  }

  bool SiteWaterMainsTemperature::setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(
    double maximumDifferenceInMonthlyAverageOutdoorAirTemperatures) {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(
      maximumDifferenceInMonthlyAverageOutdoorAirTemperatures);
  }

  void SiteWaterMainsTemperature::resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures() {
    getImpl<detail::SiteWaterMainsTemperature_Impl>()->resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures();
  }

  double SiteWaterMainsTemperature::temperatureMultiplier() const {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->temperatureMultiplier();
  }

  bool SiteWaterMainsTemperature::setTemperatureMultiplier(double temperatureMultiplier) {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->setTemperatureMultiplier(temperatureMultiplier);
  }

  double SiteWaterMainsTemperature::temperatureOffset() const {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->temperatureOffset();
  }

  bool SiteWaterMainsTemperature::setTemperatureOffset(double temperatureOffset) {
    return getImpl<detail::SiteWaterMainsTemperature_Impl>()->setTemperatureOffset(temperatureOffset);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SiteWaterMainsTemperature_Impl::calculationMethod() const {
      const auto value = getString(openstudio::Site_WaterMainsTemperatureFields::CalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteWaterMainsTemperature_Impl::setCalculationMethod(const std::string& calculationMethod) {
      return setString(openstudio::Site_WaterMainsTemperatureFields::CalculationMethod, calculationMethod);
    }

    boost::optional<double> SiteWaterMainsTemperature_Impl::annualAverageOutdoorAirTemperature() const {
      return getDouble(openstudio::Site_WaterMainsTemperatureFields::AnnualAverageOutdoorAirTemperature, true);
    }

    bool SiteWaterMainsTemperature_Impl::setAnnualAverageOutdoorAirTemperature(double annualAverageOutdoorAirTemperature) {
      bool result = setDouble(openstudio::Site_WaterMainsTemperatureFields::AnnualAverageOutdoorAirTemperature, annualAverageOutdoorAirTemperature);
      if (result) {
        result = setCalculationMethod("Correlation");
        OS_ASSERT(result);
      }
      OS_ASSERT(result);
      return result;
    }

    void SiteWaterMainsTemperature_Impl::resetAnnualAverageOutdoorAirTemperature() {
      OS_ASSERT(setString(openstudio::Site_WaterMainsTemperatureFields::AnnualAverageOutdoorAirTemperature, ""));
    }

    boost::optional<double> SiteWaterMainsTemperature_Impl::maximumDifferenceInMonthlyAverageOutdoorAirTemperatures() const {
      return getDouble(openstudio::Site_WaterMainsTemperatureFields::MaximumDifferenceInMonthlyAverageOutdoorAirTemperatures, true);
    }

    bool SiteWaterMainsTemperature_Impl::setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(
      double maximumDifferenceInMonthlyAverageOutdoorAirTemperatures) {
      bool result = setDouble(openstudio::Site_WaterMainsTemperatureFields::MaximumDifferenceInMonthlyAverageOutdoorAirTemperatures,
                              maximumDifferenceInMonthlyAverageOutdoorAirTemperatures);
      if (result) {
        result = setCalculationMethod("Correlation");
        OS_ASSERT(result);
      }
      return result;
    }

    void SiteWaterMainsTemperature_Impl::resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures() {
      OS_ASSERT(setString(openstudio::Site_WaterMainsTemperatureFields::MaximumDifferenceInMonthlyAverageOutdoorAirTemperatures, ""));
    }

    double SiteWaterMainsTemperature_Impl::temperatureMultiplier() const {
      const auto value = getDouble(openstudio::Site_WaterMainsTemperatureFields::TemperatureMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteWaterMainsTemperature_Impl::setTemperatureMultiplier(double temperatureMultiplier) {
      return setDouble(openstudio::Site_WaterMainsTemperatureFields::TemperatureMultiplier, temperatureMultiplier);
    }

    double SiteWaterMainsTemperature_Impl::temperatureOffset() const {
      const auto value = getDouble(openstudio::Site_WaterMainsTemperatureFields::TemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteWaterMainsTemperature_Impl::setTemperatureOffset(double temperatureOffset) {
      const bool result = setDouble(openstudio::Site_WaterMainsTemperatureFields::TemperatureOffset, temperatureOffset);
      OS_ASSERT(result);
      return result;
    }

    std::vector<std::string> SiteWaterMainsTemperature_Impl::calculationMethodValues() const {
      return openstudio::epmodel::SiteWaterMainsTemperature::calculationMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
