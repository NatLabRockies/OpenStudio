/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermostatSetpointDualSetpoint.hpp"
#include "ThermostatSetpointDualSetpoint_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ThermostatSetpoint_DualSetpoint_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  namespace detail {

    ThermostatSetpointDualSetpoint_Impl::ThermostatSetpointDualSetpoint_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : Thermostat_Impl(idfObject, model, keepHandle) {
      const auto type = idfObject.iddObject().type().value();
      OS_ASSERT((type == ThermostatSetpointDualSetpoint::iddObjectType().value())
                || (type == IddObjectType::ThermostatSetpoint_SingleCooling)
                || (type == IddObjectType::ThermostatSetpoint_SingleHeating));
    }

    ThermostatSetpointDualSetpoint_Impl::ThermostatSetpointDualSetpoint_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                                             bool keepHandle)
      : Thermostat_Impl(other, model, keepHandle) {
      const auto type = other.iddObject().type().value();
      OS_ASSERT((type == ThermostatSetpointDualSetpoint::iddObjectType().value())
                || (type == IddObjectType::ThermostatSetpoint_SingleCooling)
                || (type == IddObjectType::ThermostatSetpoint_SingleHeating));
    }

    ThermostatSetpointDualSetpoint_Impl::ThermostatSetpointDualSetpoint_Impl(const ThermostatSetpointDualSetpoint_Impl& other, Model_Impl* model,
                                                                             bool keepHandle)
      : Thermostat_Impl(other, model, keepHandle),
        m_temperatureDifferenceBetweenCutoutAndSetpoint(other.m_temperatureDifferenceBetweenCutoutAndSetpoint) {}

  }  // namespace detail

  ThermostatSetpointDualSetpoint::ThermostatSetpointDualSetpoint(const Model& model)
    : Thermostat(ThermostatSetpointDualSetpoint::iddObjectType(), model) {}

  ThermostatSetpointDualSetpoint::ThermostatSetpointDualSetpoint(std::shared_ptr<detail::ThermostatSetpointDualSetpoint_Impl> impl)
    : Thermostat(std::move(impl)) {}

  IddObjectType ThermostatSetpointDualSetpoint::iddObjectType() {
    return IddObjectType::ThermostatSetpoint_DualSetpoint;
  }

  boost::optional<Schedule> ThermostatSetpointDualSetpoint::heatingSetpointTemperatureSchedule() const {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->heatingSetpointTemperatureSchedule();
  }

  boost::optional<Schedule> ThermostatSetpointDualSetpoint::coolingSetpointTemperatureSchedule() const {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->coolingSetpointTemperatureSchedule();
  }

  bool ThermostatSetpointDualSetpoint::setHeatingSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->setHeatingSetpointTemperatureSchedule(schedule);
  }

  void ThermostatSetpointDualSetpoint::resetHeatingSetpointTemperatureSchedule() {
    getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->resetHeatingSetpointTemperatureSchedule();
  }

  bool ThermostatSetpointDualSetpoint::setCoolingSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->setCoolingSetpointTemperatureSchedule(schedule);
  }

  void ThermostatSetpointDualSetpoint::resetCoolingSetpointTemperatureSchedule() {
    getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->resetCoolingSetpointTemperatureSchedule();
  }

  double ThermostatSetpointDualSetpoint::temperatureDifferenceBetweenCutoutAndSetpoint() const {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->temperatureDifferenceBetweenCutoutAndSetpoint();
  }

  bool ThermostatSetpointDualSetpoint::setTemperatureDifferenceBetweenCutoutAndSetpoint(double deltaT) {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->setTemperatureDifferenceBetweenCutoutAndSetpoint(deltaT);
  }

  bool ThermostatSetpointDualSetpoint::isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const {
    return getImpl<detail::ThermostatSetpointDualSetpoint_Impl>()->isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted();
  }

  boost::optional<Schedule> ThermostatSetpointDualSetpoint::getHeatingSchedule() const {
    return heatingSetpointTemperatureSchedule();
  }

  bool ThermostatSetpointDualSetpoint::setHeatingSchedule(Schedule& schedule) {
    return setHeatingSetpointTemperatureSchedule(schedule);
  }

  void ThermostatSetpointDualSetpoint::resetHeatingSchedule() {
    resetHeatingSetpointTemperatureSchedule();
  }

  boost::optional<Schedule> ThermostatSetpointDualSetpoint::getCoolingSchedule() const {
    return coolingSetpointTemperatureSchedule();
  }

  bool ThermostatSetpointDualSetpoint::setCoolingSchedule(Schedule& schedule) {
    return setCoolingSetpointTemperatureSchedule(schedule);
  }

  void ThermostatSetpointDualSetpoint::resetCoolingSchedule() {
    resetCoolingSetpointTemperatureSchedule();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::Schedule> ThermostatSetpointDualSetpoint_Impl::heatingSetpointTemperatureSchedule() const {
      return getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ThermostatSetpoint_DualSetpointFields::HeatingSetpointTemperatureScheduleName);
    }

    boost::optional<openstudio::epmodel::Schedule> ThermostatSetpointDualSetpoint_Impl::coolingSetpointTemperatureSchedule() const {
      return getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::ThermostatSetpoint_DualSetpointFields::CoolingSetpointTemperatureScheduleName);
    }

    bool ThermostatSetpointDualSetpoint_Impl::setHeatingSetpointTemperatureSchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(openstudio::ThermostatSetpoint_DualSetpointFields::HeatingSetpointTemperatureScheduleName, schedule.handle(), false);
    }

    void ThermostatSetpointDualSetpoint_Impl::resetHeatingSetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::ThermostatSetpoint_DualSetpointFields::HeatingSetpointTemperatureScheduleName, "", false));
    }

    bool ThermostatSetpointDualSetpoint_Impl::setCoolingSetpointTemperatureSchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(openstudio::ThermostatSetpoint_DualSetpointFields::CoolingSetpointTemperatureScheduleName, schedule.handle(), false);
    }

    void ThermostatSetpointDualSetpoint_Impl::resetCoolingSetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::ThermostatSetpoint_DualSetpointFields::CoolingSetpointTemperatureScheduleName, "", false));
    }

    double ThermostatSetpointDualSetpoint_Impl::temperatureDifferenceBetweenCutoutAndSetpoint() const {
      if (auto zone = getObject<openstudio::epmodel::ThermostatSetpointDualSetpoint>().thermalZone()) {
        return zone->temperatureDifferenceBetweenCutoutAndSetpoint();
      }
      return storedTemperatureDifferenceBetweenCutoutAndSetpoint();
    }

    bool ThermostatSetpointDualSetpoint_Impl::setTemperatureDifferenceBetweenCutoutAndSetpoint(double deltaT) {
      setStoredTemperatureDifferenceBetweenCutoutAndSetpoint(deltaT);
      if (auto zone = getObject<openstudio::epmodel::ThermostatSetpointDualSetpoint>().thermalZone()) {
        return zone->setTemperatureDifferenceBetweenCutoutAndSetpoint(deltaT);
      }
      return true;
    }

    bool ThermostatSetpointDualSetpoint_Impl::isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const {
      if (auto zone = getObject<openstudio::epmodel::ThermostatSetpointDualSetpoint>().thermalZone()) {
        return zone->isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted();
      }
      return !hasStoredTemperatureDifferenceBetweenCutoutAndSetpoint();
    }

    void ThermostatSetpointDualSetpoint_Impl::applyTemperatureDifferenceBetweenCutoutAndSetpointToThermalZone(
      openstudio::epmodel::ThermalZone& thermalZone) const {
      if (hasStoredTemperatureDifferenceBetweenCutoutAndSetpoint()) {
        OS_ASSERT(thermalZone.setTemperatureDifferenceBetweenCutoutAndSetpoint(storedTemperatureDifferenceBetweenCutoutAndSetpoint()));
      } else {
        thermalZone.resetTemperatureDifferenceBetweenCutoutAndSetpoint();
      }
    }

    void ThermostatSetpointDualSetpoint_Impl::syncTemperatureDifferenceBetweenCutoutAndSetpointFromThermalZone(
      const openstudio::epmodel::ThermalZone& thermalZone) {
      if (thermalZone.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted()) {
        resetStoredTemperatureDifferenceBetweenCutoutAndSetpoint();
      } else {
        setStoredTemperatureDifferenceBetweenCutoutAndSetpoint(thermalZone.temperatureDifferenceBetweenCutoutAndSetpoint());
      }
    }

    double ThermostatSetpointDualSetpoint_Impl::storedTemperatureDifferenceBetweenCutoutAndSetpoint() const {
      return m_temperatureDifferenceBetweenCutoutAndSetpoint.value_or(0.0);
    }

    bool ThermostatSetpointDualSetpoint_Impl::hasStoredTemperatureDifferenceBetweenCutoutAndSetpoint() const {
      return static_cast<bool>(m_temperatureDifferenceBetweenCutoutAndSetpoint);
    }

    void ThermostatSetpointDualSetpoint_Impl::setStoredTemperatureDifferenceBetweenCutoutAndSetpoint(double deltaT) {
      m_temperatureDifferenceBetweenCutoutAndSetpoint = deltaT;
    }

    void ThermostatSetpointDualSetpoint_Impl::resetStoredTemperatureDifferenceBetweenCutoutAndSetpoint() {
      m_temperatureDifferenceBetweenCutoutAndSetpoint.reset();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
