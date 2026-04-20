/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilUserDefined.hpp"
#include "WaterToAirComponent/CoilUserDefined_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/EnergyManagementSystemActuator.hpp"
#include "ModelObject/EnergyManagementSystemActuator_Impl.hpp"
#include "ModelObject/EnergyManagementSystemProgram.hpp"
#include "ModelObject/EnergyManagementSystemProgram_Impl.hpp"
#include "ModelObject/EnergyManagementSystemProgramCallingManager.hpp"
#include "ModelObject/EnergyManagementSystemProgramCallingManager_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/Coil_UserDefined_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <set>

namespace openstudio {
namespace epmodel {

namespace {

// Coil:UserDefined does not store direct pointers to its EMS programs or
// actuators in the EnergyPlus schema. The program calling managers are stored
// directly on the coil, the programs hang off those managers, and the actuators
// point back to the coil. These helpers keep that storage model localized here
// so the public wrapper can still present the canonical OpenStudio surface.

constexpr std::string_view kUserDefinedComponentModelCallingPoint = "UserDefinedComponentModel";

constexpr std::string_view kAirConnectionType = "Air Connection 1";
constexpr std::string_view kPlantConnectionType = "Plant Connection";

constexpr std::string_view kAirOutletTemperatureControlType = "Outlet Temperature";
constexpr std::string_view kAirOutletHumidityRatioControlType = "Outlet Humidity Ratio";
constexpr std::string_view kAirMassFlowRateControlType = "Mass Flow Rate";
constexpr std::string_view kPlantMinimumMassFlowRateControlType = "Minimum Mass Flow Rate";
constexpr std::string_view kPlantMaximumMassFlowRateControlType = "Maximum Mass Flow Rate";
constexpr std::string_view kPlantDesignVolumeFlowRateControlType = "Design Volume Flow Rate";
constexpr std::string_view kPlantOutletTemperatureControlType = "Outlet Temperature";
constexpr std::string_view kPlantMassFlowRateControlType = "Mass Flow Rate";

constexpr std::string_view kOverallPCMChildSuffix = "overallModelSimulationProgramCallingManager";
constexpr std::string_view kSizingPCMChildSuffix = "modelSetupandSizingProgramCallingManager";
constexpr std::string_view kOverallProgramChildSuffix = "overallSimulationProgram";
constexpr std::string_view kInitializationProgramChildSuffix = "initializationSimulationProgram";
constexpr std::string_view kAirOutletTemperatureDefaultName = "airOutletTemperature";
constexpr std::string_view kAirOutletHumidityRatioDefaultName = "airOutletHumidityRatio";
constexpr std::string_view kAirMassFlowRateDefaultName = "airMassFlowRate";
constexpr std::string_view kPlantMinimumMassFlowRateDefaultName = "plantMinimumMassFlowRate";
constexpr std::string_view kPlantMaximumMassFlowRateDefaultName = "plantMaximumMassFlowRate";
constexpr std::string_view kPlantDesignVolumeFlowRateDefaultName = "plantDesignVolumeFlowRate";
constexpr std::string_view kPlantMassFlowRateDefaultName = "plantMassFlowRate";
constexpr std::string_view kPlantOutletTemperatureDefaultName = "plantOutletTemperature";
constexpr std::string_view kAirOutletTemperatureActuatorChildSuffix = "airOutletTemperatureActuator";
constexpr std::string_view kAirOutletHumidityRatioActuatorChildSuffix = "airOutletHumidityRatioActuator";
constexpr std::string_view kAirMassFlowRateActuatorChildSuffix = "airMassFlowRateActuator";
constexpr std::string_view kPlantMinimumMassFlowRateActuatorChildSuffix = "plantMinimumMassFlowRateActuator";
constexpr std::string_view kPlantMaximumMassFlowRateActuatorChildSuffix = "plantMaximumMassFlowRateActuator";
constexpr std::string_view kPlantDesignVolumeFlowRateActuatorChildSuffix = "plantDesignVolumeFlowRateActuator";
constexpr std::string_view kPlantMassFlowRateActuatorChildSuffix = "plantMassFlowRateActuator";
constexpr std::string_view kPlantOutletTemperatureActuatorChildSuffix = "plantOutletTemperatureActuator";

std::string prefixedChildName(const CoilUserDefined& coil, const std::string_view suffix) {
  std::string prefix = coil.nameString();
  std::replace(prefix.begin(), prefix.end(), ' ', '_');
  return prefix + "_" + std::string(suffix);
}

boost::optional<EnergyManagementSystemActuator> resolveActuatorForRole(
  const CoilUserDefined& coil, const std::string_view componentType, const std::string_view controlType, const std::string_view defaultName,
  const std::string_view renamedSuffix) {
  std::vector<EnergyManagementSystemActuator> matches;
  for (const auto& actuator : coil.model().getConcreteModelObjects<EnergyManagementSystemActuator>()) {
    const auto actuatedComponent = actuator.actuatedComponent();
    if (!actuatedComponent || actuatedComponent->handle() != coil.handle()) {
      continue;
    }
    if (openstudio::istringEqual(actuator.actuatedComponentType(), std::string(componentType))
        && openstudio::istringEqual(actuator.actuatedComponentControlType(), std::string(controlType))) {
      matches.push_back(actuator);
    }
  }

  if (matches.empty()) {
    if (auto namedActuator = coil.model().getConcreteModelObjectByName<EnergyManagementSystemActuator>(std::string(defaultName))) {
      return namedActuator;
    }
    if (auto renamedActuator =
          coil.model().getConcreteModelObjectByName<EnergyManagementSystemActuator>(prefixedChildName(coil, renamedSuffix))) {
      return renamedActuator;
    }
    return boost::none;
  }

  std::ranges::sort(matches, [](const auto& lhs, const auto& rhs) { return lhs.nameString() < rhs.nameString(); });
  return matches.front();
}

bool bindActuatorRole(const CoilUserDefined& coil, const EnergyManagementSystemActuator& actuator, const std::string_view componentType,
                      const std::string_view controlType) {
  auto boundActuator = actuator;
  return boundActuator.setActuatedComponent(coil) && boundActuator.setActuatedComponentType(std::string(componentType))
         && boundActuator.setActuatedComponentControlType(std::string(controlType));
}

boost::optional<EnergyManagementSystemProgram> firstProgram(const EnergyManagementSystemProgramCallingManager& programCallingManager) {
  return programCallingManager.getProgram(0);
}

bool setPrimaryProgram(EnergyManagementSystemProgramCallingManager programCallingManager, const EnergyManagementSystemProgram& program) {
  if (programCallingManager.getProgram(0)) {
    return programCallingManager.setProgram(program, 0);
  }
  return programCallingManager.addProgram(program);
}

template <typename ChildType>
void appendUniqueChild(std::vector<ModelObject>& children, std::set<Handle>& seenHandles, const ChildType& child) {
  if (!seenHandles.insert(child.handle()).second) {
    return;
  }
  children.push_back(child);
}

}  // namespace

CoilUserDefined::CoilUserDefined(const Model& model) : WaterToAirComponent(CoilUserDefined::iddObjectType(), model) {
  bool ok = setString(openstudio::Coil_UserDefinedFields::NumberofAirConnections, "");
  OS_ASSERT(ok);

  EnergyManagementSystemActuator airOutletTemperature(*this, std::string(kAirConnectionType), std::string(kAirOutletTemperatureControlType));
  airOutletTemperature.setName("airOutletTemperature");
  ok = setAirOutletTemperatureActuator(airOutletTemperature) && ok;

  EnergyManagementSystemActuator airOutletHumidityRatio(*this, std::string(kAirConnectionType),
                                                        std::string(kAirOutletHumidityRatioControlType));
  airOutletHumidityRatio.setName("airOutletHumidityRatio");
  ok = setAirOutletHumidityRatioActuator(airOutletHumidityRatio) && ok;

  EnergyManagementSystemActuator airMassFlowRate(*this, std::string(kAirConnectionType), std::string(kAirMassFlowRateControlType));
  airMassFlowRate.setName("airMassFlowRate");
  ok = setAirMassFlowRateActuator(airMassFlowRate) && ok;

  EnergyManagementSystemActuator plantMinimumMassFlowRate(*this, std::string(kPlantConnectionType),
                                                          std::string(kPlantMinimumMassFlowRateControlType));
  plantMinimumMassFlowRate.setName("plantMinimumMassFlowRate");
  ok = setPlantMinimumMassFlowRateActuator(plantMinimumMassFlowRate) && ok;

  EnergyManagementSystemActuator plantMaximumMassFlowRate(*this, std::string(kPlantConnectionType),
                                                          std::string(kPlantMaximumMassFlowRateControlType));
  plantMaximumMassFlowRate.setName("plantMaximumMassFlowRate");
  ok = setPlantMaximumMassFlowRateActuator(plantMaximumMassFlowRate) && ok;

  EnergyManagementSystemActuator plantDesignVolumeFlowRate(*this, std::string(kPlantConnectionType),
                                                           std::string(kPlantDesignVolumeFlowRateControlType));
  plantDesignVolumeFlowRate.setName("plantDesignVolumeFlowRate");
  ok = setPlantDesignVolumeFlowRateActuator(plantDesignVolumeFlowRate) && ok;

  EnergyManagementSystemActuator plantMassFlowRate(*this, std::string(kPlantConnectionType), std::string(kPlantMassFlowRateControlType));
  plantMassFlowRate.setName("plantMassFlowRate");
  ok = setPlantMassFlowRateActuator(plantMassFlowRate) && ok;

  EnergyManagementSystemActuator plantOutletTemperature(*this, std::string(kPlantConnectionType),
                                                        std::string(kPlantOutletTemperatureControlType));
  plantOutletTemperature.setName("plantOutletTemperature");
  ok = setPlantOutletTemperatureActuator(plantOutletTemperature) && ok;

  EnergyManagementSystemProgram overallProgram(model);
  overallProgram.setName("overallSimulationProgram");

  EnergyManagementSystemProgramCallingManager overallPCM(model);
  overallPCM.setName("overallModelSimulationProgramCallingManager");
  ok = overallPCM.setCallingPoint(std::string(kUserDefinedComponentModelCallingPoint)) && ok;
  ok = overallPCM.addProgram(overallProgram) && ok;
  ok = setOverallModelSimulationProgramCallingManager(overallPCM) && ok;

  EnergyManagementSystemProgram initializationProgram(model);
  initializationProgram.setName("initializationSimulationProgram");

  EnergyManagementSystemProgramCallingManager sizingPCM(model);
  sizingPCM.setName("modelSetupandSizingProgramCallingManager");
  ok = sizingPCM.setCallingPoint(std::string(kUserDefinedComponentModelCallingPoint)) && ok;
  ok = sizingPCM.addProgram(initializationProgram) && ok;
  ok = setModelSetupandSizingProgramCallingManager(sizingPCM) && ok;

  OS_ASSERT(ok);
}

CoilUserDefined::CoilUserDefined(std::shared_ptr<detail::CoilUserDefined_Impl> impl) : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilUserDefined::iddObjectType() {
  return IddObjectType::Coil_UserDefined;
}

int CoilUserDefined::numberofAirConnections() const {
  return getImpl<detail::CoilUserDefined_Impl>()->numberofAirConnections();
}

bool CoilUserDefined::addToNode(Node& node) {
  const bool result = WaterToAirComponent::addToNode(node);
  if (result && airInletModelObject() && airOutletModelObject()) {
    OS_ASSERT(setInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, 1));
  }
  return result;
}

void CoilUserDefined::disconnectAirSide() {
  WaterToAirComponent::disconnectAirSide();
  OS_ASSERT(setString(openstudio::Coil_UserDefinedFields::NumberofAirConnections, ""));
}

bool CoilUserDefined::removeFromAirLoopHVAC() {
  const bool result = WaterToAirComponent::removeFromAirLoopHVAC();
  if (result) {
    OS_ASSERT(setString(openstudio::Coil_UserDefinedFields::NumberofAirConnections, ""));
  }
  return result;
}

EnergyManagementSystemProgramCallingManager CoilUserDefined::overallModelSimulationProgramCallingManager() const {
  return getImpl<detail::CoilUserDefined_Impl>()->overallModelSimulationProgramCallingManager();
}

bool CoilUserDefined::setOverallModelSimulationProgramCallingManager(const EnergyManagementSystemProgramCallingManager& emsProgramCallingManager) {
  return getImpl<detail::CoilUserDefined_Impl>()->setOverallModelSimulationProgramCallingManager(emsProgramCallingManager);
}

EnergyManagementSystemProgramCallingManager CoilUserDefined::modelSetupandSizingProgramCallingManager() const {
  return getImpl<detail::CoilUserDefined_Impl>()->modelSetupandSizingProgramCallingManager();
}

bool CoilUserDefined::setModelSetupandSizingProgramCallingManager(const EnergyManagementSystemProgramCallingManager& emsProgramCallingManager) {
  return getImpl<detail::CoilUserDefined_Impl>()->setModelSetupandSizingProgramCallingManager(emsProgramCallingManager);
}

boost::optional<ThermalZone> CoilUserDefined::ambientZone() const {
  return getImpl<detail::CoilUserDefined_Impl>()->ambientZone();
}

bool CoilUserDefined::setAmbientZone(const ThermalZone& thermalZone) {
  return getImpl<detail::CoilUserDefined_Impl>()->setAmbientZone(thermalZone);
}

void CoilUserDefined::resetAmbientZone() {
  getImpl<detail::CoilUserDefined_Impl>()->resetAmbientZone();
}

EnergyManagementSystemProgram CoilUserDefined::overallSimulationProgram() const {
  return getImpl<detail::CoilUserDefined_Impl>()->overallSimulationProgram();
}

bool CoilUserDefined::setOverallSimulationProgram(const EnergyManagementSystemProgram& emsProgram) {
  return getImpl<detail::CoilUserDefined_Impl>()->setOverallSimulationProgram(emsProgram);
}

EnergyManagementSystemProgram CoilUserDefined::initializationSimulationProgram() const {
  return getImpl<detail::CoilUserDefined_Impl>()->initializationSimulationProgram();
}

bool CoilUserDefined::setInitializationSimulationProgram(const EnergyManagementSystemProgram& emsProgram) {
  return getImpl<detail::CoilUserDefined_Impl>()->setInitializationSimulationProgram(emsProgram);
}

EnergyManagementSystemActuator CoilUserDefined::airOutletTemperatureActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->airOutletTemperatureActuator();
}

bool CoilUserDefined::setAirOutletTemperatureActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setAirOutletTemperatureActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::airOutletHumidityRatioActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->airOutletHumidityRatioActuator();
}

bool CoilUserDefined::setAirOutletHumidityRatioActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setAirOutletHumidityRatioActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::airMassFlowRateActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->airMassFlowRateActuator();
}

bool CoilUserDefined::setAirMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setAirMassFlowRateActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::plantMinimumMassFlowRateActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->plantMinimumMassFlowRateActuator();
}

bool CoilUserDefined::setPlantMinimumMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setPlantMinimumMassFlowRateActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::plantMaximumMassFlowRateActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->plantMaximumMassFlowRateActuator();
}

bool CoilUserDefined::setPlantMaximumMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setPlantMaximumMassFlowRateActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::plantDesignVolumeFlowRateActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->plantDesignVolumeFlowRateActuator();
}

bool CoilUserDefined::setPlantDesignVolumeFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setPlantDesignVolumeFlowRateActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::plantOutletTemperatureActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->plantOutletTemperatureActuator();
}

bool CoilUserDefined::setPlantOutletTemperatureActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setPlantOutletTemperatureActuator(emsActuator);
}

EnergyManagementSystemActuator CoilUserDefined::plantMassFlowRateActuator() const {
  return getImpl<detail::CoilUserDefined_Impl>()->plantMassFlowRateActuator();
}

bool CoilUserDefined::setPlantMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return getImpl<detail::CoilUserDefined_Impl>()->setPlantMassFlowRateActuator(emsActuator);
}

std::vector<ModelObject> CoilUserDefined::children() const {
  return getImpl<detail::CoilUserDefined_Impl>()->children();
}

void CoilUserDefined::renameEMSSubComponents() {
  auto thisObject = *this;
  if (!thisObject.name()) {
    thisObject.createName();
  }

  overallModelSimulationProgramCallingManager().setName(prefixedChildName(*this, kOverallPCMChildSuffix));
  modelSetupandSizingProgramCallingManager().setName(prefixedChildName(*this, kSizingPCMChildSuffix));
  overallSimulationProgram().setName(prefixedChildName(*this, kOverallProgramChildSuffix));
  initializationSimulationProgram().setName(prefixedChildName(*this, kInitializationProgramChildSuffix));
  airOutletTemperatureActuator().setName(prefixedChildName(*this, kAirOutletTemperatureActuatorChildSuffix));
  airOutletHumidityRatioActuator().setName(prefixedChildName(*this, kAirOutletHumidityRatioActuatorChildSuffix));
  airMassFlowRateActuator().setName(prefixedChildName(*this, kAirMassFlowRateActuatorChildSuffix));
  plantMinimumMassFlowRateActuator().setName(prefixedChildName(*this, kPlantMinimumMassFlowRateActuatorChildSuffix));
  plantMaximumMassFlowRateActuator().setName(prefixedChildName(*this, kPlantMaximumMassFlowRateActuatorChildSuffix));
  plantDesignVolumeFlowRateActuator().setName(prefixedChildName(*this, kPlantDesignVolumeFlowRateActuatorChildSuffix));
  plantMassFlowRateActuator().setName(prefixedChildName(*this, kPlantMassFlowRateActuatorChildSuffix));
  plantOutletTemperatureActuator().setName(prefixedChildName(*this, kPlantOutletTemperatureActuatorChildSuffix));
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

[[noreturn]] void throwMissingRequiredChild(const ModelObject& object, const std::string& childDescription) {
  LOG_FREE_AND_THROW("openstudio.epmodel.CoilUserDefined", object.briefDescription() << " does not have " << childDescription << " attached.");
}

}  // namespace

unsigned CoilUserDefined_Impl::airInletPort() const {
  return openstudio::Coil_UserDefinedFields::AirConnection1InletNodeName;
}

unsigned CoilUserDefined_Impl::airOutletPort() const {
  return openstudio::Coil_UserDefinedFields::AirConnection1OutletNodeName;
}

unsigned CoilUserDefined_Impl::waterInletPort() const {
  return openstudio::Coil_UserDefinedFields::PlantConnectionInletNodeName;
}

unsigned CoilUserDefined_Impl::waterOutletPort() const {
  return openstudio::Coil_UserDefinedFields::PlantConnectionOutletNodeName;
}

int CoilUserDefined_Impl::numberofAirConnections() const {
  if (airInletModelObject() && airOutletModelObject()) {
    return 1;
  }
  return 0;
}

EnergyManagementSystemProgramCallingManager CoilUserDefined_Impl::overallModelSimulationProgramCallingManager() const {
  if (auto value = getObject<ModelObject>().getModelObjectTarget<EnergyManagementSystemProgramCallingManager>(
        openstudio::Coil_UserDefinedFields::OverallModelSimulationProgramCallingManagerName)) {
    return *value;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "an Overall Model Simulation Program Calling Manager");
}

bool CoilUserDefined_Impl::setOverallModelSimulationProgramCallingManager(
  const EnergyManagementSystemProgramCallingManager& emsProgramCallingManager) {
  return setPointer(openstudio::Coil_UserDefinedFields::OverallModelSimulationProgramCallingManagerName, emsProgramCallingManager.handle());
}

EnergyManagementSystemProgramCallingManager CoilUserDefined_Impl::modelSetupandSizingProgramCallingManager() const {
  if (auto value = getObject<ModelObject>().getModelObjectTarget<EnergyManagementSystemProgramCallingManager>(
        openstudio::Coil_UserDefinedFields::ModelSetupandSizingProgramCallingManagerName)) {
    return *value;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "a Model Setup and Sizing Program Calling Manager");
}

bool CoilUserDefined_Impl::setModelSetupandSizingProgramCallingManager(
  const EnergyManagementSystemProgramCallingManager& emsProgramCallingManager) {
  return setPointer(openstudio::Coil_UserDefinedFields::ModelSetupandSizingProgramCallingManagerName, emsProgramCallingManager.handle());
}

boost::optional<ThermalZone> CoilUserDefined_Impl::ambientZone() const {
  return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Coil_UserDefinedFields::AmbientZoneName);
}

bool CoilUserDefined_Impl::setAmbientZone(const ThermalZone& thermalZone) {
  return setPointer(openstudio::Coil_UserDefinedFields::AmbientZoneName, thermalZone.handle());
}

void CoilUserDefined_Impl::resetAmbientZone() {
  OS_ASSERT(setString(openstudio::Coil_UserDefinedFields::AmbientZoneName, ""));
}

EnergyManagementSystemProgram CoilUserDefined_Impl::overallSimulationProgram() const {
  if (auto program = firstProgram(overallModelSimulationProgramCallingManager())) {
    return *program;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "an Overall Simulation Program");
}

bool CoilUserDefined_Impl::setOverallSimulationProgram(const EnergyManagementSystemProgram& emsProgram) {
  return setPrimaryProgram(overallModelSimulationProgramCallingManager(), emsProgram);
}

EnergyManagementSystemProgram CoilUserDefined_Impl::initializationSimulationProgram() const {
  if (auto program = firstProgram(modelSetupandSizingProgramCallingManager())) {
    return *program;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "an Initialization Simulation Program");
}

bool CoilUserDefined_Impl::setInitializationSimulationProgram(const EnergyManagementSystemProgram& emsProgram) {
  return setPrimaryProgram(modelSetupandSizingProgramCallingManager(), emsProgram);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::airOutletTemperatureActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kAirConnectionType,
                                             kAirOutletTemperatureControlType, kAirOutletTemperatureDefaultName,
                                             kAirOutletTemperatureActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "an Air Outlet Temperature Actuator");
}

bool CoilUserDefined_Impl::setAirOutletTemperatureActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kAirConnectionType,
                          kAirOutletTemperatureControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::airOutletHumidityRatioActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kAirConnectionType,
                                             kAirOutletHumidityRatioControlType, kAirOutletHumidityRatioDefaultName,
                                             kAirOutletHumidityRatioActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "an Air Outlet Humidity Ratio Actuator");
}

bool CoilUserDefined_Impl::setAirOutletHumidityRatioActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kAirConnectionType,
                          kAirOutletHumidityRatioControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::airMassFlowRateActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kAirConnectionType,
                                             kAirMassFlowRateControlType, kAirMassFlowRateDefaultName,
                                             kAirMassFlowRateActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "an Air Mass Flow Rate Actuator");
}

bool CoilUserDefined_Impl::setAirMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kAirConnectionType,
                          kAirMassFlowRateControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::plantMinimumMassFlowRateActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kPlantConnectionType,
                                             kPlantMinimumMassFlowRateControlType, kPlantMinimumMassFlowRateDefaultName,
                                             kPlantMinimumMassFlowRateActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "a Plant Minimum Mass Flow Rate Actuator");
}

bool CoilUserDefined_Impl::setPlantMinimumMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kPlantConnectionType,
                          kPlantMinimumMassFlowRateControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::plantMaximumMassFlowRateActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kPlantConnectionType,
                                             kPlantMaximumMassFlowRateControlType, kPlantMaximumMassFlowRateDefaultName,
                                             kPlantMaximumMassFlowRateActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "a Plant Maximum Mass Flow Rate Actuator");
}

bool CoilUserDefined_Impl::setPlantMaximumMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kPlantConnectionType,
                          kPlantMaximumMassFlowRateControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::plantDesignVolumeFlowRateActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kPlantConnectionType,
                                             kPlantDesignVolumeFlowRateControlType, kPlantDesignVolumeFlowRateDefaultName,
                                             kPlantDesignVolumeFlowRateActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "a Plant Design Volume Flow Rate Actuator");
}

bool CoilUserDefined_Impl::setPlantDesignVolumeFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kPlantConnectionType,
                          kPlantDesignVolumeFlowRateControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::plantOutletTemperatureActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kPlantConnectionType,
                                             kPlantOutletTemperatureControlType, kPlantOutletTemperatureDefaultName,
                                             kPlantOutletTemperatureActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "a Plant Outlet Temperature Actuator");
}

bool CoilUserDefined_Impl::setPlantOutletTemperatureActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kPlantConnectionType,
                          kPlantOutletTemperatureControlType);
}

EnergyManagementSystemActuator CoilUserDefined_Impl::plantMassFlowRateActuator() const {
  if (auto actuator = resolveActuatorForRole(getObject<openstudio::epmodel::CoilUserDefined>(), kPlantConnectionType,
                                             kPlantMassFlowRateControlType, kPlantMassFlowRateDefaultName, kPlantMassFlowRateActuatorChildSuffix)) {
    return *actuator;
  }
  throwMissingRequiredChild(getObject<ModelObject>(), "a Plant Mass Flow Rate Actuator");
}

bool CoilUserDefined_Impl::setPlantMassFlowRateActuator(const EnergyManagementSystemActuator& emsActuator) {
  return bindActuatorRole(getObject<openstudio::epmodel::CoilUserDefined>(), emsActuator, kPlantConnectionType,
                          kPlantMassFlowRateControlType);
}

openstudio::ComponentType CoilUserDefined_Impl::componentType() const {
  return openstudio::ComponentType::Both;
}

std::vector<openstudio::FuelType> CoilUserDefined_Impl::coolingFuelTypes() const {
  return {};
}

std::vector<openstudio::FuelType> CoilUserDefined_Impl::heatingFuelTypes() const {
  return {};
}

std::vector<openstudio::AppGFuelType> CoilUserDefined_Impl::appGHeatingFuelTypes() const {
  return {};
}

std::vector<ModelObject> CoilUserDefined_Impl::children() const {
  std::vector<ModelObject> result;
  std::set<Handle> seenHandles;

  appendUniqueChild(result, seenHandles, overallModelSimulationProgramCallingManager());
  appendUniqueChild(result, seenHandles, modelSetupandSizingProgramCallingManager());
  appendUniqueChild(result, seenHandles, overallSimulationProgram());
  appendUniqueChild(result, seenHandles, initializationSimulationProgram());
  appendUniqueChild(result, seenHandles, airOutletTemperatureActuator());
  appendUniqueChild(result, seenHandles, airOutletHumidityRatioActuator());
  appendUniqueChild(result, seenHandles, airMassFlowRateActuator());
  appendUniqueChild(result, seenHandles, plantMinimumMassFlowRateActuator());
  appendUniqueChild(result, seenHandles, plantMaximumMassFlowRateActuator());
  appendUniqueChild(result, seenHandles, plantDesignVolumeFlowRateActuator());
  appendUniqueChild(result, seenHandles, plantMassFlowRateActuator());
  appendUniqueChild(result, seenHandles, plantOutletTemperatureActuator());

  return result;
}

std::vector<IdfObject> CoilUserDefined_Impl::remove() {
  if (!isRemovable()) {
    return {};
  }

  for (auto& child : children()) {
    child.remove();
  }

  return WaterToAirComponent_Impl::remove();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
