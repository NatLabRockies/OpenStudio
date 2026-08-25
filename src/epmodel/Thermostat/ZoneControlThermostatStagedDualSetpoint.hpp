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

  /** \brief Represents the EnergyPlus ZoneControl:Thermostat:StagedDualSetpoint object.
   *
   * \par EnergyPlus object
   * \epobject{group-zone-controls-thermostats.html#zonecontrolthermostatstageddualsetpoint,ZoneControl:Thermostat:StagedDualSetpoint}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneControlThermostatStagedDualSetpoint</code>. Staging scalars and heating/cooling schedule relationships are represented.
   *
   * \par Known limitations
   * Constructor defaults and staged numeric fields map directly to EnergyPlus; schedule-type validation remains limited.
   */
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
