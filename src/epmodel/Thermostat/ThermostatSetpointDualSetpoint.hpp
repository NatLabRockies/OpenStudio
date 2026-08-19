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

  /** \brief Represents the EnergyPlus ThermostatSetpoint:DualSetpoint object.
   *
   * \par EnergyPlus object
   * \epobject{group-zone-controls-thermostats.html#thermostatsetpointdualsetpoint,ThermostatSetpoint:DualSetpoint}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ThermostatSetpointDualSetpoint</code>. Heating/cooling schedules and cutout/setpoint differences are represented, including deprecated schedule aliases.
   *
   * \par Known limitations
   * The temperature difference is synchronized to an attached ZoneControl:Thermostat; unattached runtime state does not yet persist across save/load, and imported single-heating/single-cooling objects are projected into this wrapper.
   */
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
