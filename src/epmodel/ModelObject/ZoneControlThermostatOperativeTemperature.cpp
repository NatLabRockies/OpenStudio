/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlThermostatOperativeTemperature.hpp"
#include "ZoneControlThermostatOperativeTemperature_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneControl_Thermostat_OperativeTemperature_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneControlThermostatOperativeTemperature::ZoneControlThermostatOperativeTemperature(const Model& model)
    : ModelObject(ZoneControlThermostatOperativeTemperature::iddObjectType(), model) {
    OS_ASSERT(setRadiativeFractionInputMode("Constant"));
  }

  ZoneControlThermostatOperativeTemperature::ZoneControlThermostatOperativeTemperature(
    std::shared_ptr<detail::ZoneControlThermostatOperativeTemperature_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlThermostatOperativeTemperature::iddObjectType() {
    return IddObjectType::ZoneControl_Thermostat_OperativeTemperature;
  }

  std::vector<std::string> ZoneControlThermostatOperativeTemperature::radiativeFractionInputModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::RadiativeFractionInputMode);
  }

  std::vector<std::string> ZoneControlThermostatOperativeTemperature::adaptiveComfortModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::AdaptiveComfortModelType);
  }

  std::string ZoneControlThermostatOperativeTemperature::radiativeFractionInputMode() const {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->radiativeFractionInputMode();
  }

  bool ZoneControlThermostatOperativeTemperature::setRadiativeFractionInputMode(const std::string& radiativeFractionInputMode) {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->setRadiativeFractionInputMode(radiativeFractionInputMode);
  }

  boost::optional<double> ZoneControlThermostatOperativeTemperature::fixedRadiativeFraction() const {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->fixedRadiativeFraction();
  }

  bool ZoneControlThermostatOperativeTemperature::setFixedRadiativeFraction(double fixedRadiativeFraction) {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->setFixedRadiativeFraction(fixedRadiativeFraction);
  }

  std::string ZoneControlThermostatOperativeTemperature::adaptiveComfortModelType() const {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->adaptiveComfortModelType();
  }

  bool ZoneControlThermostatOperativeTemperature::setAdaptiveComfortModelType(const std::string& adaptiveComfortModelType) {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->setAdaptiveComfortModelType(adaptiveComfortModelType);
  }

  bool ZoneControlThermostatOperativeTemperature::isAdaptiveComfortModelTypeDefaulted() const {
    return getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->isAdaptiveComfortModelTypeDefaulted();
  }

  void ZoneControlThermostatOperativeTemperature::resetAdaptiveComfortModelType() {
    getImpl<detail::ZoneControlThermostatOperativeTemperature_Impl>()->resetAdaptiveComfortModelType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> ZoneControlThermostatOperativeTemperature_Impl::radiativeFractionInputModeValues() const {
      return openstudio::epmodel::ZoneControlThermostatOperativeTemperature::radiativeFractionInputModeValues();
    }

    std::vector<std::string> ZoneControlThermostatOperativeTemperature_Impl::adaptiveComfortModelTypeValues() const {
      return openstudio::epmodel::ZoneControlThermostatOperativeTemperature::adaptiveComfortModelTypeValues();
    }

    std::string ZoneControlThermostatOperativeTemperature_Impl::radiativeFractionInputMode() const {
      const auto value = getString(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::RadiativeFractionInputMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatOperativeTemperature_Impl::setRadiativeFractionInputMode(const std::string& radiativeFractionInputMode) {
      const bool result =
        setString(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::RadiativeFractionInputMode, radiativeFractionInputMode);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneControlThermostatOperativeTemperature_Impl::fixedRadiativeFraction() const {
      return getDouble(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::FixedRadiativeFraction, true);
    }

    bool ZoneControlThermostatOperativeTemperature_Impl::setFixedRadiativeFraction(double fixedRadiativeFraction) {
      return setDouble(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::FixedRadiativeFraction, fixedRadiativeFraction);
    }

    std::string ZoneControlThermostatOperativeTemperature_Impl::adaptiveComfortModelType() const {
      const auto value = getString(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::AdaptiveComfortModelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatOperativeTemperature_Impl::setAdaptiveComfortModelType(const std::string& adaptiveComfortModelType) {
      return setString(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::AdaptiveComfortModelType, adaptiveComfortModelType);
    }

    bool ZoneControlThermostatOperativeTemperature_Impl::isAdaptiveComfortModelTypeDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::AdaptiveComfortModelType);
    }

    void ZoneControlThermostatOperativeTemperature_Impl::resetAdaptiveComfortModelType() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_OperativeTemperatureFields::AdaptiveComfortModelType, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
