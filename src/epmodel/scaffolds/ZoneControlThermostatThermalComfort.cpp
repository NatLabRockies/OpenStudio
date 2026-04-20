/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlThermostatThermalComfort.hpp"
#include "ZoneControlThermostatThermalComfort_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneControl_Thermostat_ThermalComfort_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneControlThermostatThermalComfort::ZoneControlThermostatThermalComfort(const Model& model)
    : ModelObject(ZoneControlThermostatThermalComfort::iddObjectType(), model) {
    OS_ASSERT(setAveragingMethod("PeopleAverage"));
  }

  ZoneControlThermostatThermalComfort::ZoneControlThermostatThermalComfort(std::shared_ptr<detail::ZoneControlThermostatThermalComfort_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlThermostatThermalComfort::iddObjectType() {
    return IddObjectType::ZoneControl_Thermostat_ThermalComfort;
  }

  std::vector<std::string> ZoneControlThermostatThermalComfort::averagingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneControl_Thermostat_ThermalComfortFields::AveragingMethod);
  }

  std::string ZoneControlThermostatThermalComfort::averagingMethod() const {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->averagingMethod();
  }

  bool ZoneControlThermostatThermalComfort::setAveragingMethod(const std::string& averagingMethod) {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->setAveragingMethod(averagingMethod);
  }

  bool ZoneControlThermostatThermalComfort::isAveragingMethodDefaulted() const {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->isAveragingMethodDefaulted();
  }

  void ZoneControlThermostatThermalComfort::resetAveragingMethod() {
    getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->resetAveragingMethod();
  }

  boost::optional<double> ZoneControlThermostatThermalComfort::minimumDryBulbTemperatureSetpoint() const {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->minimumDryBulbTemperatureSetpoint();
  }

  bool ZoneControlThermostatThermalComfort::setMinimumDryBulbTemperatureSetpoint(double minimumDryBulbTemperatureSetpoint) {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->setMinimumDryBulbTemperatureSetpoint(minimumDryBulbTemperatureSetpoint);
  }

  bool ZoneControlThermostatThermalComfort::isMinimumDryBulbTemperatureSetpointDefaulted() const {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->isMinimumDryBulbTemperatureSetpointDefaulted();
  }

  void ZoneControlThermostatThermalComfort::resetMinimumDryBulbTemperatureSetpoint() {
    getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->resetMinimumDryBulbTemperatureSetpoint();
  }

  boost::optional<double> ZoneControlThermostatThermalComfort::maximumDryBulbTemperatureSetpoint() const {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->maximumDryBulbTemperatureSetpoint();
  }

  bool ZoneControlThermostatThermalComfort::setMaximumDryBulbTemperatureSetpoint(double maximumDryBulbTemperatureSetpoint) {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->setMaximumDryBulbTemperatureSetpoint(maximumDryBulbTemperatureSetpoint);
  }

  bool ZoneControlThermostatThermalComfort::isMaximumDryBulbTemperatureSetpointDefaulted() const {
    return getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->isMaximumDryBulbTemperatureSetpointDefaulted();
  }

  void ZoneControlThermostatThermalComfort::resetMaximumDryBulbTemperatureSetpoint() {
    getImpl<detail::ZoneControlThermostatThermalComfort_Impl>()->resetMaximumDryBulbTemperatureSetpoint();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneControlThermostatThermalComfort_Impl::averagingMethod() const {
      const auto value = getString(openstudio::ZoneControl_Thermostat_ThermalComfortFields::AveragingMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatThermalComfort_Impl::setAveragingMethod(const std::string& averagingMethod) {
      const bool result = setString(openstudio::ZoneControl_Thermostat_ThermalComfortFields::AveragingMethod, averagingMethod);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatThermalComfort_Impl::isAveragingMethodDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_ThermalComfortFields::AveragingMethod);
    }

    void ZoneControlThermostatThermalComfort_Impl::resetAveragingMethod() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_ThermalComfortFields::AveragingMethod, ""));
    }

    boost::optional<double> ZoneControlThermostatThermalComfort_Impl::minimumDryBulbTemperatureSetpoint() const {
      return getDouble(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MinimumDryBulbTemperatureSetpoint, true);
    }

    bool ZoneControlThermostatThermalComfort_Impl::setMinimumDryBulbTemperatureSetpoint(double minimumDryBulbTemperatureSetpoint) {
      const bool result =
        setDouble(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MinimumDryBulbTemperatureSetpoint, minimumDryBulbTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatThermalComfort_Impl::isMinimumDryBulbTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MinimumDryBulbTemperatureSetpoint);
    }

    void ZoneControlThermostatThermalComfort_Impl::resetMinimumDryBulbTemperatureSetpoint() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MinimumDryBulbTemperatureSetpoint, ""));
    }

    boost::optional<double> ZoneControlThermostatThermalComfort_Impl::maximumDryBulbTemperatureSetpoint() const {
      return getDouble(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MaximumDryBulbTemperatureSetpoint, true);
    }

    bool ZoneControlThermostatThermalComfort_Impl::setMaximumDryBulbTemperatureSetpoint(double maximumDryBulbTemperatureSetpoint) {
      const bool result =
        setDouble(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MaximumDryBulbTemperatureSetpoint, maximumDryBulbTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatThermalComfort_Impl::isMaximumDryBulbTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MaximumDryBulbTemperatureSetpoint);
    }

    void ZoneControlThermostatThermalComfort_Impl::resetMaximumDryBulbTemperatureSetpoint() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_ThermalComfortFields::MaximumDryBulbTemperatureSetpoint, ""));
    }

    std::vector<std::string> ZoneControlThermostatThermalComfort_Impl::averagingMethodValues() const {
      return openstudio::epmodel::ZoneControlThermostatThermalComfort::averagingMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
