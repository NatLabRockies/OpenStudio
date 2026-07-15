/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILUSERDEFINED_IMPL_HPP
#define EPMODEL_COILUSERDEFINED_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class ThermalZone;
  class EnergyManagementSystemActuator;
  class EnergyManagementSystemProgram;
  class EnergyManagementSystemProgramCallingManager;

  namespace detail {

    class EPMODEL_API CoilUserDefined_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilUserDefined_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;

      int numberofAirConnections() const;
      std::vector<IdfObject> remove() override;
      ComponentType componentType() const override;
      std::vector<FuelType> coolingFuelTypes() const override;
      std::vector<FuelType> heatingFuelTypes() const override;
      std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

      EnergyManagementSystemProgramCallingManager overallModelSimulationProgramCallingManager() const;
      bool setOverallModelSimulationProgramCallingManager(const EnergyManagementSystemProgramCallingManager& emsProgramCallingManager);

      EnergyManagementSystemProgramCallingManager modelSetupandSizingProgramCallingManager() const;
      bool setModelSetupandSizingProgramCallingManager(const EnergyManagementSystemProgramCallingManager& emsProgramCallingManager);

      boost::optional<ThermalZone> ambientZone() const;
      bool setAmbientZone(const ThermalZone& thermalZone);
      void resetAmbientZone();

      EnergyManagementSystemProgram overallSimulationProgram() const;
      bool setOverallSimulationProgram(const EnergyManagementSystemProgram& emsProgram);

      EnergyManagementSystemProgram initializationSimulationProgram() const;
      bool setInitializationSimulationProgram(const EnergyManagementSystemProgram& emsProgram);

      EnergyManagementSystemActuator airOutletTemperatureActuator() const;
      bool setAirOutletTemperatureActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator airOutletHumidityRatioActuator() const;
      bool setAirOutletHumidityRatioActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator airMassFlowRateActuator() const;
      bool setAirMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator plantMinimumMassFlowRateActuator() const;
      bool setPlantMinimumMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator plantMaximumMassFlowRateActuator() const;
      bool setPlantMaximumMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator plantDesignVolumeFlowRateActuator() const;
      bool setPlantDesignVolumeFlowRateActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator plantOutletTemperatureActuator() const;
      bool setPlantOutletTemperatureActuator(const EnergyManagementSystemActuator& emsActuator);

      EnergyManagementSystemActuator plantMassFlowRateActuator() const;
      bool setPlantMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator);

      std::vector<ModelObject> children() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
