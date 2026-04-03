/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCHILLERHEATERCHANGEOVER_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCHILLERHEATERCHANGEOVER_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantEquipmentOperationChillerHeaterChangeover_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationChillerHeaterChangeover : public PlantEquipmentOperationScheme
  {
   public:
    explicit PlantEquipmentOperationChillerHeaterChangeover(const Model& model);

    virtual ~PlantEquipmentOperationChillerHeaterChangeover() override = default;
    PlantEquipmentOperationChillerHeaterChangeover(const PlantEquipmentOperationChillerHeaterChangeover& other) = default;
    PlantEquipmentOperationChillerHeaterChangeover(PlantEquipmentOperationChillerHeaterChangeover&& other) = default;
    PlantEquipmentOperationChillerHeaterChangeover& operator=(const PlantEquipmentOperationChillerHeaterChangeover&) = default;
    PlantEquipmentOperationChillerHeaterChangeover& operator=(PlantEquipmentOperationChillerHeaterChangeover&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived PlantEquipmentOperation:ChillerHeaterChangeover naming is preserved for this no-counterpart type.
    // - Field Mapping: Required cooling/heating setpoint fields, optional secondary setpoints, and the Boiler Setpoint Temperature Offset map directly to the same-named EnergyPlus fields; the backup setpoint follows the IDD note that it falls back to the outdoor low setpoint when blank.
    // - Field Mapping: Relationship-like object-list fields (Name/ControlSchemeList, Zone Load Polling ZoneList Name, the four load scheme references, and the dedicated PLHP object names) are intentionally excluded from this scalar-only pass.
    // - TODO(parity): Add relationship APIs/ForwardTranslator wiring for the excluded fields once scalar saturation completes.
    double primaryCoolingPlantSetpointTemperature() const;
    bool setPrimaryCoolingPlantSetpointTemperature(double primaryCoolingPlantSetpointTemperature);

    boost::optional<double> secondaryDistributionCoolingPlantSetpointTemperature() const;
    bool setSecondaryDistributionCoolingPlantSetpointTemperature(double secondaryDistributionCoolingPlantSetpointTemperature);
    void resetSecondaryDistributionCoolingPlantSetpointTemperature();

    double primaryHeatingPlantSetpointatOutdoorHighTemperature() const;
    bool setPrimaryHeatingPlantSetpointatOutdoorHighTemperature(double primaryHeatingPlantSetpointatOutdoorHighTemperature);

    double outdoorHighTemperature() const;
    bool setOutdoorHighTemperature(double outdoorHighTemperature);

    double primaryHeatingPlantSetpointatOutdoorLowTemperature() const;
    bool setPrimaryHeatingPlantSetpointatOutdoorLowTemperature(double primaryHeatingPlantSetpointatOutdoorLowTemperature);

    double outdoorLowTemperature() const;
    bool setOutdoorLowTemperature(double outdoorLowTemperature);

    boost::optional<double> secondaryDistributionHeatingPlantSetpointTemperature() const;
    bool setSecondaryDistributionHeatingPlantSetpointTemperature(double secondaryDistributionHeatingPlantSetpointTemperature);
    void resetSecondaryDistributionHeatingPlantSetpointTemperature();

    double boilerSetpointTemperatureOffset() const;
    bool setBoilerSetpointTemperatureOffset(double boilerSetpointTemperatureOffset);
    void resetBoilerSetpointTemperatureOffset();
    bool isBoilerSetpointTemperatureOffsetDefaulted() const;

    boost::optional<double> primaryHeatingPlantSetpointatBackupOutdoorLowTemperature() const;
    bool setPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature(double primaryHeatingPlantSetpointatBackupOutdoorLowTemperature);
    void resetPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature();

    boost::optional<double> backupOutdoorLowTemperature() const;
    bool setBackupOutdoorLowTemperature(double backupOutdoorLowTemperature);
    void resetBackupOutdoorLowTemperature();

   protected:
    using ImplType = detail::PlantEquipmentOperationChillerHeaterChangeover_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantEquipmentOperationChillerHeaterChangeover(std::shared_ptr<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
