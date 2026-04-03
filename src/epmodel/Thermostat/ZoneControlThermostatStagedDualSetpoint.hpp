/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_ZONECONTROLTHERMOSTATSTAGEDDUALSETPOINT_HPP
#define EPMODEL_THERMOSTAT_ZONECONTROLTHERMOSTATSTAGEDDUALSETPOINT_HPP

#include "Thermostat/Thermostat.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class ZoneControlThermostatStagedDualSetpoint_Impl;
  }

  class EPMODEL_API ZoneControlThermostatStagedDualSetpoint : public Thermostat
  {
   public:
    explicit ZoneControlThermostatStagedDualSetpoint(const Model& model);

    virtual ~ZoneControlThermostatStagedDualSetpoint() override = default;
    ZoneControlThermostatStagedDualSetpoint(const ZoneControlThermostatStagedDualSetpoint& other) = default;
    ZoneControlThermostatStagedDualSetpoint(ZoneControlThermostatStagedDualSetpoint&& other) = default;
    ZoneControlThermostatStagedDualSetpoint& operator=(const ZoneControlThermostatStagedDualSetpoint&) = default;
    ZoneControlThermostatStagedDualSetpoint& operator=(ZoneControlThermostatStagedDualSetpoint&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity. The canonical staged-dual-setpoint scalar and schedule surfaces are preserved, including constructor defaults.
    // - Canonical Counterpart: openstudio::model::ZoneControlThermostatStagedDualSetpoint.
    // - Implemented Parity: The staged temperature offsets, throttling ranges, stage counts, and the heating/cooling schedule relationship APIs match
    //   the canonical model surface.
    // - Field/Storage Mapping: Numeric staging methods map directly to the corresponding ZoneControl:Thermostat:StagedDualSetpoint numeric fields. The
    //   heating/cooling schedule accessors bind to the matching schedule object-list fields.
    // - Remaining Parity Work: Add canonical schedule-type validation in the heating/cooling schedule setters.

    int numberofHeatingStages() const;
    bool setNumberofHeatingStages(int numberofHeatingStages);

    boost::optional<Schedule> heatingTemperatureSetpointSchedule() const;
    bool setHeatingTemperatureSetpointSchedule(Schedule& schedule);
    void resetHeatingTemperatureSetpointSchedule();

    double heatingThrottlingTemperatureRange() const;
    bool setHeatingThrottlingTemperatureRange(double heatingThrottlingTemperatureRange);

    double stage1HeatingTemperatureOffset() const;
    bool setStage1HeatingTemperatureOffset(double stage1HeatingTemperatureOffset);

    double stage2HeatingTemperatureOffset() const;
    bool setStage2HeatingTemperatureOffset(double stage2HeatingTemperatureOffset);

    double stage3HeatingTemperatureOffset() const;
    bool setStage3HeatingTemperatureOffset(double stage3HeatingTemperatureOffset);

    double stage4HeatingTemperatureOffset() const;
    bool setStage4HeatingTemperatureOffset(double stage4HeatingTemperatureOffset);

    int numberofCoolingStages() const;
    bool setNumberofCoolingStages(int numberofCoolingStages);

    boost::optional<Schedule> coolingTemperatureSetpointBaseSchedule() const;
    bool setCoolingTemperatureSetpointBaseSchedule(Schedule& schedule);
    void resetCoolingTemperatureSetpointBaseSchedule();

    double coolingThrottlingTemperatureRange() const;
    bool setCoolingThrottlingTemperatureRange(double coolingThrottlingTemperatureRange);

    double stage1CoolingTemperatureOffset() const;
    bool setStage1CoolingTemperatureOffset(double stage1CoolingTemperatureOffset);

    double stage2CoolingTemperatureOffset() const;
    bool setStage2CoolingTemperatureOffset(double stage2CoolingTemperatureOffset);

    double stage3CoolingTemperatureOffset() const;
    bool setStage3CoolingTemperatureOffset(double stage3CoolingTemperatureOffset);

    double stage4CoolingTemperatureOffset() const;
    bool setStage4CoolingTemperatureOffset(double stage4CoolingTemperatureOffset);

   protected:
    using ImplType = detail::ZoneControlThermostatStagedDualSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlThermostatStagedDualSetpoint(std::shared_ptr<detail::ZoneControlThermostatStagedDualSetpoint_Impl> impl);
  };

  using OptionalZoneControlThermostatStagedDualSetpoint = boost::optional<ZoneControlThermostatStagedDualSetpoint>;
  using ZoneControlThermostatStagedDualSetpointVector = std::vector<ZoneControlThermostatStagedDualSetpoint>;

}  // namespace epmodel
}  // namespace openstudio

#endif
