/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_HPP
#define EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_HPP

#include "Thermostat/Thermostat.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class ThermostatSetpointDualSetpoint_Impl;
  }

  class EPMODEL_API ThermostatSetpointDualSetpoint : public Thermostat
  {
   public:
    explicit ThermostatSetpointDualSetpoint(const Model& model);

    virtual ~ThermostatSetpointDualSetpoint() override = default;
    ThermostatSetpointDualSetpoint(const ThermostatSetpointDualSetpoint& other) = default;
    ThermostatSetpointDualSetpoint(ThermostatSetpointDualSetpoint&& other) = default;
    ThermostatSetpointDualSetpoint& operator=(const ThermostatSetpointDualSetpoint&) = default;
    ThermostatSetpointDualSetpoint& operator=(ThermostatSetpointDualSetpoint&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity. The canonical thermostat base and the dual-setpoint schedule/temperature-difference surface are preserved.
    // - Canonical Counterpart: openstudio::model::ThermostatSetpointDualSetpoint.
    // - Implemented Parity: Heating/cooling schedule relationships, deprecated schedule aliases, and the cutout/setpoint temperature-difference
    //   accessors mirror the canonical model surface.
    // - Field/Storage Mapping: Schedule relationships bind directly to the EnergyPlus Heating/Cooling Setpoint Temperature Schedule Name object-list
    //   fields. TemperatureDifferenceBetweenCutoutAndSetpoint synchronizes to the attached ZoneControl:Thermostat companion when a zone owns the
    //   thermostat, and epmodel keeps runtime thermostat-local state for the unattached canonical API behavior.
    // - Documented Delta: ThermostatSetpoint:SingleCooling and ThermostatSetpoint:SingleHeating continue to be imported into this wrapper shape, so
    //   schedule semantics still reflect the imported EnergyPlus object type when loaded from those source objects.
    // - Remaining Parity Work: Persist unattached temperature-difference state across save/load boundaries without depending on a zone attachment, and
    //   add canonical schedule-type validation in the heating/cooling schedule setters.
    boost::optional<Schedule> heatingSetpointTemperatureSchedule() const;
    boost::optional<Schedule> coolingSetpointTemperatureSchedule() const;

    bool setHeatingSetpointTemperatureSchedule(Schedule& schedule);
    void resetHeatingSetpointTemperatureSchedule();

    bool setCoolingSetpointTemperatureSchedule(Schedule& schedule);
    void resetCoolingSetpointTemperatureSchedule();

    double temperatureDifferenceBetweenCutoutAndSetpoint() const;
    bool setTemperatureDifferenceBetweenCutoutAndSetpoint(double deltaT);
    bool isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const;

    /** \deprecated */
    boost::optional<Schedule> getHeatingSchedule() const;
    /** \deprecated */
    bool setHeatingSchedule(Schedule& schedule);
    /** \deprecated */
    void resetHeatingSchedule();

    /** \deprecated */
    boost::optional<Schedule> getCoolingSchedule() const;
    /** \deprecated */
    bool setCoolingSchedule(Schedule& schedule);
    /** \deprecated */
    void resetCoolingSchedule();

   protected:
    using ImplType = detail::ThermostatSetpointDualSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermostatSetpointDualSetpoint(std::shared_ptr<detail::ThermostatSetpointDualSetpoint_Impl> impl);
  };

  using OptionalThermostatSetpointDualSetpoint = boost::optional<ThermostatSetpointDualSetpoint>;

}  // namespace epmodel
}  // namespace openstudio

#endif
