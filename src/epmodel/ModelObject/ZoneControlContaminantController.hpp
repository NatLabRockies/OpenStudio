/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLCONTAMINANTCONTROLLER_HPP
#define EPMODEL_ZONECONTROLCONTAMINANTCONTROLLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneControlContaminantController_Impl;
  }

  class EPMODEL_API ZoneControlContaminantController : public ModelObject
  {
   public:
    explicit ZoneControlContaminantController(const Model& model);

    virtual ~ZoneControlContaminantController() override = default;
    ZoneControlContaminantController(const ZoneControlContaminantController& other) = default;
    ZoneControlContaminantController(ZoneControlContaminantController&& other) = default;
    ZoneControlContaminantController& operator=(const ZoneControlContaminantController&) = default;
    ZoneControlContaminantController& operator=(ZoneControlContaminantController&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity for the canonical public relationship surface.
    // - Canonical Counterpart: openstudio::model::ZoneControlContaminantController.
    // - Implemented Parity: Controlled-zone observation and the five canonical optional schedule getter/setter/reset relationships.
    // - Field/Storage Mapping: controlledZone maps to E+ Zone Name; schedule setters use the five matching ScheduleNames fields with
    //   canonical availability or non-negative concentration limits. The E+-only Maximum Carbon Dioxide Concentration field is not exposed.
    // - Documented Delta: Existing ThermalZone assignment, replacement, reset, clone, and removal behavior is unchanged by this API-only phase.
    // - Remaining Parity Work: Broader ThermalZone ownership and direct clone/removal lifecycle parity remains demand-driven.

    boost::optional<ThermalZone> controlledZone() const;

    boost::optional<Schedule> carbonDioxideControlAvailabilitySchedule() const;
    bool setCarbonDioxideControlAvailabilitySchedule(Schedule& schedule);
    void resetCarbonDioxideControlAvailabilitySchedule();

    boost::optional<Schedule> carbonDioxideSetpointSchedule() const;
    bool setCarbonDioxideSetpointSchedule(Schedule& schedule);
    void resetCarbonDioxideSetpointSchedule();

    boost::optional<Schedule> minimumCarbonDioxideConcentrationSchedule() const;
    bool setMinimumCarbonDioxideConcentrationSchedule(Schedule& schedule);
    void resetMinimumCarbonDioxideConcentrationSchedule();

    boost::optional<Schedule> genericContaminantControlAvailabilitySchedule() const;
    bool setGenericContaminantControlAvailabilitySchedule(Schedule& schedule);
    void resetGenericContaminantControlAvailabilitySchedule();

    boost::optional<Schedule> genericContaminantSetpointSchedule() const;
    bool setGenericContaminantSetpointSchedule(Schedule& schedule);
    void resetGenericContaminantSetpointSchedule();

   protected:
    using ImplType = detail::ZoneControlContaminantController_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlContaminantController(std::shared_ptr<detail::ZoneControlContaminantController_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
