/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/SkyTemperature.hpp"
#include "ModelObject/SkyTemperature_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WeatherProperty_SkyTemperature_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  SkyTemperature::SkyTemperature(const Model& model) : ModelObject(SkyTemperature::iddObjectType(), model) {}

  SkyTemperature::SkyTemperature(std::shared_ptr<detail::SkyTemperature_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SkyTemperature::iddObjectType() {
    return IddObjectType::WeatherProperty_SkyTemperature;
  }

  std::vector<std::string> SkyTemperature::calculationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WeatherProperty_SkyTemperatureFields::CalculationType);
  }

  std::string SkyTemperature::calculationType() const {
    return getImpl<detail::SkyTemperature_Impl>()->calculationType();
  }

  bool SkyTemperature::setCalculationType(const std::string& calculationType) {
    return getImpl<detail::SkyTemperature_Impl>()->setCalculationType(calculationType);
  }

  bool SkyTemperature::isCalculationTypeDefaulted() const {
    return getImpl<detail::SkyTemperature_Impl>()->isCalculationTypeDefaulted();
  }

  void SkyTemperature::resetCalculationType() {
    getImpl<detail::SkyTemperature_Impl>()->resetCalculationType();
  }

  bool SkyTemperature::useWeatherFileHorizontalIR() const {
    return getImpl<detail::SkyTemperature_Impl>()->useWeatherFileHorizontalIR();
  }

  bool SkyTemperature::setUseWeatherFileHorizontalIR(bool useWeatherFileHorizontalIR) {
    return getImpl<detail::SkyTemperature_Impl>()->setUseWeatherFileHorizontalIR(useWeatherFileHorizontalIR);
  }

  bool SkyTemperature::isUseWeatherFileHorizontalIRDefaulted() const {
    return getImpl<detail::SkyTemperature_Impl>()->isUseWeatherFileHorizontalIRDefaulted();
  }

  void SkyTemperature::resetUseWeatherFileHorizontalIR() {
    getImpl<detail::SkyTemperature_Impl>()->resetUseWeatherFileHorizontalIR();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SkyTemperature_Impl::calculationType() const {
      const auto value = getString(openstudio::WeatherProperty_SkyTemperatureFields::CalculationType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SkyTemperature_Impl::setCalculationType(const std::string& calculationType) {
      return setString(openstudio::WeatherProperty_SkyTemperatureFields::CalculationType, calculationType);
    }

    bool SkyTemperature_Impl::isCalculationTypeDefaulted() const {
      return isEmpty(openstudio::WeatherProperty_SkyTemperatureFields::CalculationType);
    }

    void SkyTemperature_Impl::resetCalculationType() {
      OS_ASSERT(setString(openstudio::WeatherProperty_SkyTemperatureFields::CalculationType, ""));
    }

    std::vector<std::string> SkyTemperature_Impl::calculationTypeValues() const {
      return openstudio::epmodel::SkyTemperature::calculationTypeValues();
    }

    bool SkyTemperature_Impl::useWeatherFileHorizontalIR() const {
      if (auto value = getString(openstudio::WeatherProperty_SkyTemperatureFields::UseWeatherFileHorizontalIR, true)) {
        return openstudio::istringEqual(*value, "Yes");
      }
      return true;
    }

    bool SkyTemperature_Impl::setUseWeatherFileHorizontalIR(bool useWeatherFileHorizontalIR) {
      const bool result =
        setString(openstudio::WeatherProperty_SkyTemperatureFields::UseWeatherFileHorizontalIR, useWeatherFileHorizontalIR ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    bool SkyTemperature_Impl::isUseWeatherFileHorizontalIRDefaulted() const {
      return isEmpty(openstudio::WeatherProperty_SkyTemperatureFields::UseWeatherFileHorizontalIR);
    }

    void SkyTemperature_Impl::resetUseWeatherFileHorizontalIR() {
      OS_ASSERT(setString(openstudio::WeatherProperty_SkyTemperatureFields::UseWeatherFileHorizontalIR, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
