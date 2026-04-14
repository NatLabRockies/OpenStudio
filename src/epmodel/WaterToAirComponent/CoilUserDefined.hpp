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

  // Schema Alignment Notes:
  // - Status: Near Parity. The canonical EMS-heavy companion-object surface is preserved in epmodel, but it is expressed over the real EnergyPlus
  //   storage layout instead of the OpenStudio-only direct pointer fields.
  // - Canonical Counterpart: openstudio::model::CoilUserDefined.
  // - Implemented Parity: the required program calling managers, derived overall/initialization programs, actuator helpers, ambient-zone relationship,
  //   `children`, and `renameEMSSubComponents` now match the canonical public contract.
  // - Field/Storage Mapping: the two program-calling-manager relationships map directly to the EnergyPlus `Coil:UserDefined` fields, while
  //   `overallSimulationProgram` and `initializationSimulationProgram` are derived from the first program row on those managers because EnergyPlus
  //   stores the program relationship there instead of on the coil object itself.
  // - Field/Storage Mapping: actuator helpers resolve and manage the real EnergyPlus `EnergyManagementSystem:Actuator` objects that target this coil.
  // - Evidence: `src/model/CoilUserDefined.hpp`, `src/model/CoilUserDefined.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilUserDefined.cpp`,
  //   and `src/model/test/CoilUserDefined_GTest.cpp`.
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
