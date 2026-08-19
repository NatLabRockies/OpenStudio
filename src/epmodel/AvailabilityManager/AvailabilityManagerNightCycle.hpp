/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_HPP

#include "EPModelAPI.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class Model;

  namespace detail {
    class AvailabilityManagerNightCycle_Impl;
  }

  /** \brief Cycles an air loop during unoccupied periods to meet night-cycle conditions.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagernightcycle,AvailabilityManager:NightCycle}
   *
   * \par Important behavior
   * A newly constructed manager initializes thermostat tolerance to 1.0 and
   * cycling runtime to 3600.0 seconds. <code>airLoopHVAC()</code> is derived
   * from the assigned loop and returns an air loop only when the owning loop is
   * an <code>AirLoopHVAC</code>.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerNightCycle</code>.
   *
   * - <b>Not yet available:</b> <code>applicabilitySchedule()</code> and
   *   <code>setApplicabilitySchedule(...)</code>,
   *   <code>fanSchedule()</code>, and the control, cooling-control,
   *   heating-control, and heating-fans-only thermal-zone relationship methods
   *   (<code>controlThermalZones()</code>,
   *   <code>setControlThermalZones(...)</code>,
   *   <code>resetControlThermalZones()</code>, and the corresponding methods
   *   for the other three zone groups).
   *
   * \par Known limitations
   * The manager's scalar controls and loop discovery are available, but its
   * applicability schedule, fan schedule, and thermal-zone lists cannot yet be
   * configured through typed EPModel methods.
   */
  class EPMODEL_API AvailabilityManagerNightCycle : public AvailabilityManager
  {
   public:
    explicit AvailabilityManagerNightCycle(const Model& model);

    virtual ~AvailabilityManagerNightCycle() override = default;
    AvailabilityManagerNightCycle(const AvailabilityManagerNightCycle& other) = default;
    AvailabilityManagerNightCycle(AvailabilityManagerNightCycle&& other) = default;
    AvailabilityManagerNightCycle& operator=(const AvailabilityManagerNightCycle&) = default;
    AvailabilityManagerNightCycle& operator=(AvailabilityManagerNightCycle&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> cyclingRunTimeControlTypeValues();

    boost::optional<AirLoopHVAC> airLoopHVAC() const;

    std::string controlType() const;
    bool setControlType(const std::string& controlType);
    bool isControlTypeDefaulted() const;
    void resetControlType();

    double thermostatTolerance() const;
    bool setThermostatTolerance(double thermostatTolerance);
    bool isThermostatToleranceDefaulted() const;
    void resetThermostatTolerance();

    double cyclingRunTime() const;
    bool setCyclingRunTime(double cyclingRunTime);
    bool isCyclingRunTimeDefaulted() const;
    void resetCyclingRunTime();

    std::string cyclingRunTimeControlType() const;
    bool setCyclingRunTimeControlType(const std::string& cyclingRunTimeControlType);
    bool isCyclingRunTimeControlTypeDefaulted() const;
    void resetCyclingRunTimeControlType();

   protected:
    using ImplType = detail::AvailabilityManagerNightCycle_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerNightCycle(std::shared_ptr<detail::AvailabilityManagerNightCycle_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
