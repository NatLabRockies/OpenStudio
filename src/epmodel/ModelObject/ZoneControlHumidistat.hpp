/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLHUMIDISTAT_HPP
#define EPMODEL_ZONECONTROLHUMIDISTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneControlHumidistat_Impl;
  }

  class EPMODEL_API ZoneControlHumidistat : public ModelObject
  {
   public:
    explicit ZoneControlHumidistat(const Model& model);

    virtual ~ZoneControlHumidistat() override = default;
    ZoneControlHumidistat(const ZoneControlHumidistat& other) = default;
    ZoneControlHumidistat(ZoneControlHumidistat&& other) = default;
    ZoneControlHumidistat& operator=(const ZoneControlHumidistat&) = default;
    ZoneControlHumidistat& operator=(ZoneControlHumidistat&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity for the schedule and ThermalZone ownership relationships represented by this EnergyPlus object.
    // - Canonical Counterpart: openstudio::model::ZoneControlHumidistat.
    // - Implemented Parity: Controlled-zone inverse and optional humidifying/dehumidifying relative-humidity schedule relationships.
    // - Field Mapping: Zone Name and the two setpoint schedule fields are EnergyPlus object-list pointers; schedule setters enforce continuous Percent [0, 100] limits.
    // - Ownership: ThermalZone owns its attached humidistat and removes it on replacement, reset, or zone removal; schedules remain caller-owned.
    // - Remaining Parity Work: None for these relationship and ownership APIs.
    boost::optional<ThermalZone> controlledZone() const;

    boost::optional<Schedule> humidifyingRelativeHumiditySetpointSchedule() const;
    boost::optional<Schedule> dehumidifyingRelativeHumiditySetpointSchedule() const;

    bool setHumidifyingRelativeHumiditySetpointSchedule(Schedule& schedule);
    bool setDehumidifyingRelativeHumiditySetpointSchedule(Schedule& schedule);

    void resetHumidifyingRelativeHumiditySetpointSchedule();
    void resetDehumidifyingRelativeHumiditySetpointSchedule();

   protected:
    using ImplType = detail::ZoneControlHumidistat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlHumidistat(std::shared_ptr<detail::ZoneControlHumidistat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONECONTROLHUMIDISTAT_HPP
