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

  /** \brief Selects plant equipment for chiller heater changeover operation.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-control.html#plantequipmentoperationchillerheaterchangeover,PlantEquipmentOperation:ChillerHeaterChangeover}
   *
   * \par Important behavior
   * If the backup heating setpoint is left blank, EnergyPlus uses the primary
   * heating setpoint at outdoor low temperature. The backup outdoor temperature
   * is a separate optional input.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for
   * <code>PlantEquipmentOperation:ChillerHeaterChangeover</code>; this wrapper
   * is new to the EPModel API.
   *
   * \par Known limitations
   * The zone-list, load-operation-scheme, and dedicated heat-pump relationships
   * are not exposed through typed public methods.
   */
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
