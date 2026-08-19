/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILUSERDEFINED_HPP
#define EPMODEL_COILUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class ThermalZone;
  class EnergyManagementSystemActuator;
  class EnergyManagementSystemProgram;
  class EnergyManagementSystemProgramCallingManager;

  namespace detail {
    class CoilUserDefined_Impl;
  }

  /** \brief Represents an EMS-controlled user-defined coil.
   *
   * \par EnergyPlus object
   * \epobject{group-user-defined-hvac-and-plant-component.html#coiluserdefined,Coil:UserDefined}, together with its referenced
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemprogramcallingmanager,EnergyManagementSystem:ProgramCallingManager},
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemprogram,EnergyManagementSystem:Program}, and
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemactuator,EnergyManagementSystem:Actuator} objects.
   *
   * \par Important behavior
   * The overall and initialization program accessors are derived from the
   * first program row on their calling managers because EnergyPlus stores those
   * links on the manager. Actuator accessors manage real EnergyPlus actuator
   * objects targeting this coil. Removing the coil also removes the associated
   * EMS child objects returned by <code>children()</code>.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::CoilUserDefined</code>. EPModel additionally
   * exposes the inherited water-to-air topology operations
   * (<code>addToNode()</code>, <code>disconnectAirSide()</code>, and
   * <code>removeFromAirLoopHVAC()</code>) and a <code>children()</code> query
   * for its persisted EMS companion objects.
   *
   * \par Known limitations
   * EMS program and actuator behavior remains subject to EnergyPlus EMS
   * calling-manager and actuator validation. Removing the coil also removes
   * the associated EMS child objects returned by <code>children()</code>.
   */
  class EPMODEL_API CoilUserDefined : public WaterToAirComponent
  {
   public:
    explicit CoilUserDefined(const Model& model);

    virtual ~CoilUserDefined() override = default;
    CoilUserDefined(const CoilUserDefined& other) = default;
    CoilUserDefined(CoilUserDefined&& other) = default;
    CoilUserDefined& operator=(const CoilUserDefined&) = default;
    CoilUserDefined& operator=(CoilUserDefined&&) = default;

    static IddObjectType iddObjectType();

    int numberofAirConnections() const;
    bool addToNode(Node& node);
    void disconnectAirSide();
    bool removeFromAirLoopHVAC();

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

    std::vector<ModelObject> children() const;

    void renameEMSSubComponents();

   protected:
    using ImplType = detail::CoilUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilUserDefined(std::shared_ptr<detail::CoilUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
