/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHYBRIDVENTILATION_HPP
#define EPMODEL_AVAILABILITYMANAGERHYBRIDVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerHybridVentilation_Impl;
  }

  /** \brief Controls availability using outdoor conditions and hybrid-ventilation settings.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerhybridventilation,AvailabilityManager:HybridVentilation}
   *
   * \par Important behavior
   * A newly constructed manager sets rain indicators to enabled, maximum wind
   * speed to 40.0 m/s, outdoor temperature limits to 20.0 and 30.0 °C, outdoor
   * enthalpy limits to 20,000 and 30,000 J/kg, outdoor dewpoint limits to 15.0
   * and 30.0 °C, and both minimum operation times to 0.0 minutes. The current
   * wrapper exposes those scalar fields directly; its schedule, zone, curve,
   * and ventilation-object relationships are not part of the typed API.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerHybridVentilation</code>.
   *
   * - <b>Not yet available:</b> <code>loop()</code> and the constructor overload
   *   accepting the ventilation-control-mode and minimum-outdoor-ventilation
   *   schedules.
   * - <b>Not yet available:</b> The controlled-zone, required and optional
   *   schedule, opening-factor curve, and zone-ventilation-object relationship
   *   methods: <code>controlledZone()</code>,
   *   <code>setControlledZone(...)</code>, <code>resetControlledZone()</code>,
   *   <code>ventilationControlModeSchedule()</code>,
   *   <code>setVentilationControlModeSchedule(...)</code>,
   *   <code>minimumOutdoorVentilationAirSchedule()</code>,
   *   <code>setMinimumOutdoorVentilationAirSchedule(...)</code>,
   *   <code>openingFactorFunctionofWindSpeedCurve()</code> and its setter and
   *   reset method, the Airflow Network and simple-control schedule methods,
   *   and <code>zoneVentilationObject()</code> with its setter and reset method.
   *
   * \par Known limitations
   * The EPModel wrapper currently exposes scalar fields only. It cannot be
   * passed to typed loop-assignment APIs or fully configured through typed
   * relationship methods.
   */
  class EPMODEL_API AvailabilityManagerHybridVentilation : public ModelObject
  {
   public:
    explicit AvailabilityManagerHybridVentilation(const Model& model);

    virtual ~AvailabilityManagerHybridVentilation() override = default;
    AvailabilityManagerHybridVentilation(const AvailabilityManagerHybridVentilation& other) = default;
    AvailabilityManagerHybridVentilation(AvailabilityManagerHybridVentilation&& other) = default;
    AvailabilityManagerHybridVentilation& operator=(const AvailabilityManagerHybridVentilation&) = default;
    AvailabilityManagerHybridVentilation& operator=(AvailabilityManagerHybridVentilation&&) = default;

    static IddObjectType iddObjectType();

    bool useWeatherFileRainIndicators() const;
    bool setUseWeatherFileRainIndicators(bool useWeatherFileRainIndicators);

    double maximumWindSpeed() const;
    bool setMaximumWindSpeed(double maximumWindSpeed);

    double minimumOutdoorTemperature() const;
    bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

    double maximumOutdoorTemperature() const;
    bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

    double minimumOutdoorEnthalpy() const;
    bool setMinimumOutdoorEnthalpy(double minimumOutdoorEnthalpy);

    double maximumOutdoorEnthalpy() const;
    bool setMaximumOutdoorEnthalpy(double maximumOutdoorEnthalpy);

    double minimumOutdoorDewpoint() const;
    bool setMinimumOutdoorDewpoint(double minimumOutdoorDewpoint);

    double maximumOutdoorDewpoint() const;
    bool setMaximumOutdoorDewpoint(double maximumOutdoorDewpoint);

    double minimumHVACOperationTime() const;
    bool setMinimumHVACOperationTime(double minimumHVACOperationTime);

    double minimumVentilationTime() const;
    bool setMinimumVentilationTime(double minimumVentilationTime);

   protected:
    using ImplType = detail::AvailabilityManagerHybridVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerHybridVentilation(std::shared_ptr<detail::AvailabilityManagerHybridVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
