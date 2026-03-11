/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCHILLERHEATERCHANGEOVER_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCHILLERHEATERCHANGEOVER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PlantEquipmentOperationChillerHeaterChangeover_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PlantEquipmentOperationChillerHeaterChangeover_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
