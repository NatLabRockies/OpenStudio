/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_ZONECONTROLTHERMOSTATSTAGEDDUALSETPOINT_HPP
#define EPMODEL_THERMOSTAT_ZONECONTROLTHERMOSTATSTAGEDDUALSETPOINT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneControlThermostatStagedDualSetpoint_Impl;
  }

  class EPMODEL_API ZoneControlThermostatStagedDualSetpoint : public ModelObject
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
    // - API: Mirrors the openstudio::model ZoneControlThermostatStagedDualSetpoint interface so scalar names/signatures are preserved for compatibility.
    // - Field Mapping: ForwardTranslator translateZoneControlThermostatStagedDualSetpoint wires the staging numeric fields (numberofHeatingStages, heatingThrottlingTemperatureRange, stage heating/cooling offsets, numberofCoolingStages, coolingThrottlingTemperatureRange) directly to the EnergyPlus ZoneControl:Thermostat:StagedDualSetpoint fields listed in the IDD.
    // - Field Mapping: Heating Temperature Setpoint Schedule and Cooling Temperature Setpoint Base Schedule remain relationship-like schedule references and are intentionally excluded from this scalar-only API.
    // - TODO(parity): Add explicit schedule helpers after relationship coverage reaches parity with the Ruby generator.

    int numberofHeatingStages() const;
    double heatingThrottlingTemperatureRange() const;
    double stage1HeatingTemperatureOffset() const;
    double stage2HeatingTemperatureOffset() const;
    double stage3HeatingTemperatureOffset() const;
    double stage4HeatingTemperatureOffset() const;

    int numberofCoolingStages() const;
    double coolingThrottlingTemperatureRange() const;
    double stage1CoolingTemperatureOffset() const;
    double stage2CoolingTemperatureOffset() const;
    double stage3CoolingTemperatureOffset() const;
    double stage4CoolingTemperatureOffset() const;

    bool setNumberofHeatingStages(int numberofHeatingStages);
    bool setHeatingThrottlingTemperatureRange(double heatingThrottlingTemperatureRange);
    bool setStage1HeatingTemperatureOffset(double stage1HeatingTemperatureOffset);
    bool setStage2HeatingTemperatureOffset(double stage2HeatingTemperatureOffset);
    bool setStage3HeatingTemperatureOffset(double stage3HeatingTemperatureOffset);
    bool setStage4HeatingTemperatureOffset(double stage4HeatingTemperatureOffset);

    bool setNumberofCoolingStages(int numberofCoolingStages);
    bool setCoolingThrottlingTemperatureRange(double coolingThrottlingTemperatureRange);
    bool setStage1CoolingTemperatureOffset(double stage1CoolingTemperatureOffset);
    bool setStage2CoolingTemperatureOffset(double stage2CoolingTemperatureOffset);
    bool setStage3CoolingTemperatureOffset(double stage3CoolingTemperatureOffset);
    bool setStage4CoolingTemperatureOffset(double stage4CoolingTemperatureOffset);

   protected:
    using ImplType = detail::ZoneControlThermostatStagedDualSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlThermostatStagedDualSetpoint(std::shared_ptr<detail::ZoneControlThermostatStagedDualSetpoint_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
