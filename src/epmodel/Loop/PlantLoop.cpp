/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "TestFailurePoint.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject_Impl.inl"
#include "AvailabilityManager/AvailabilityManager.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "ModelObject/AirLoopHVACControllerList.hpp"
#include "ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "ModelObject/SizingPlant.hpp"
#include "ModelObject/SizingPlant_Impl.hpp"
#include "ModelObject/WaterHeaterSizing.hpp"
#include "ModelObject/WaterHeaterSizing_Impl.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "Schedule/Schedule.hpp"
#include "StraightComponent/Node.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ModelObject/BranchList.hpp"
#include "ModelObject/BranchList_Impl.hpp"
#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"
#include "HVACComponent/ControllerWaterCoil.hpp"
#include "HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "ModelObject.hpp"
#include "Splitter/Splitter.hpp"
#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "StraightComponent/StraightComponent_Impl.hpp"
#include "StraightComponent/PipeAdiabatic.hpp"
#include "StraightComponent/PipeAdiabatic_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"
#include "StraightComponent/CompoundTerminalTopologyInspection.hpp"
#include "StraightComponent/SingleDuctTerminalRemovalPlan.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant.hpp"
#include "StraightComponent/CoilCoolingCooledBeam.hpp"
#include "StraightComponent/CoilCoolingCooledBeam_Impl.hpp"
#include "StraightComponent/CoilCoolingFourPipeBeam.hpp"
#include "StraightComponent/CoilCoolingFourPipeBeam_Impl.hpp"
#include "StraightComponent/CoilHeatingFourPipeBeam.hpp"
#include "StraightComponent/CoilHeatingFourPipeBeam_Impl.hpp"
#include "StraightComponent/CoilCoolingWaterPanelRadiant_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboard_Impl.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant_Impl.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
#include "StraightComponent/GroundHeatExchangerVertical.hpp"
#include "StraightComponent/GroundHeatExchangerVertical_Impl.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricEIR.hpp"
#include "WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp"
#include "WaterToWaterComponent/ChillerElectricReformulatedEIR_Impl.hpp"
#include "WaterToWaterComponent/CentralHeatPumpSystem.hpp"
#include "WaterToWaterComponent/CentralHeatPumpSystem_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling_Impl.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"
#include "WaterToWaterComponent/HeatExchangerFluidToFluid.hpp"
#include "WaterToWaterComponent/HeatExchangerFluidToFluid_Impl.hpp"
#include "WaterToWaterComponent/ThermalStorageChilledWaterStratified.hpp"
#include "WaterToWaterComponent/ThermalStorageChilledWaterStratified_Impl.hpp"
#include "WaterToWaterComponent/WaterHeaterMixed.hpp"
#include "WaterToWaterComponent/WaterHeaterMixed_Impl.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"
#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <set>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Chiller_Electric_EIR_FieldEnums.hxx>
#include <utilities/idd/ConnectorList_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/GroundHeatExchanger_System_FieldEnums.hxx>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Cooling_FieldEnums.hxx>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Heating_FieldEnums.hxx>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Cooling_FieldEnums.hxx>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_PlantLoop_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>
#include <utilities/idd/ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>
#include <utilities/idd/WaterHeater_Sizing_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_FourPipeFanCoil_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  PlantLoop::PlantLoop(const Model& model) : Loop(PlantLoop::iddObjectType(), model) {
    const auto loopHandle = handle();
    const auto canonicalNameIsTaken = [&model, &loopHandle](const std::string& candidate) {
      const auto prefix = candidate + " ";
      return std::ranges::any_of(model.objects(), [&loopHandle, &candidate, &prefix](const auto& object) {
        if (object.handle() == loopHandle) {
          return false;
        }
        const auto objectName = object.name();
        return objectName && ((*objectName == candidate) || objectName->starts_with(prefix));
      });
    };

    const auto initialName = nameString();
    auto canonicalName = initialName;
    unsigned suffix = 2u;
    while (canonicalNameIsTaken(canonicalName)) {
      canonicalName = initialName + " " + std::to_string(suffix++);
    }
    if (canonicalName != initialName) {
      OS_ASSERT(setName(canonicalName));
    }

    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    getImpl<detail::PlantLoop_Impl>()->canonicalize(context);
  }

  PlantLoop::PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl) : Loop(std::move(impl)) {}

  IddObjectType PlantLoop::iddObjectType() {
    return IddObjectType::PlantLoop;
  }

  std::string PlantLoop::loadDistributionScheme() const {
    return getImpl<detail::PlantLoop_Impl>()->loadDistributionScheme();
  }

  bool PlantLoop::setLoadDistributionScheme(const std::string& scheme) {
    return getImpl<detail::PlantLoop_Impl>()->setLoadDistributionScheme(scheme);
  }

  std::string PlantLoop::fluidType() const {
    return getImpl<detail::PlantLoop_Impl>()->fluidType();
  }

  bool PlantLoop::setFluidType(const std::string& value) {
    return getImpl<detail::PlantLoop_Impl>()->setFluidType(value);
  }

  int PlantLoop::glycolConcentration() const {
    return getImpl<detail::PlantLoop_Impl>()->glycolConcentration();
  }

  bool PlantLoop::setGlycolConcentration(int glycolConcentration) {
    return getImpl<detail::PlantLoop_Impl>()->setGlycolConcentration(glycolConcentration);
  }

  double PlantLoop::maximumLoopTemperature() const {
    return getImpl<detail::PlantLoop_Impl>()->maximumLoopTemperature();
  }

  bool PlantLoop::setMaximumLoopTemperature(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMaximumLoopTemperature(value);
  }

  double PlantLoop::minimumLoopTemperature() const {
    return getImpl<detail::PlantLoop_Impl>()->minimumLoopTemperature();
  }

  bool PlantLoop::setMinimumLoopTemperature(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMinimumLoopTemperature(value);
  }

  boost::optional<double> PlantLoop::maximumLoopFlowRate() const {
    return getImpl<detail::PlantLoop_Impl>()->maximumLoopFlowRate();
  }

  bool PlantLoop::setMaximumLoopFlowRate(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMaximumLoopFlowRate(value);
  }

  bool PlantLoop::isMaximumLoopFlowRateAutosized() const {
    return getImpl<detail::PlantLoop_Impl>()->isMaximumLoopFlowRateAutosized();
  }

  void PlantLoop::autosizeMaximumLoopFlowRate() {
    getImpl<detail::PlantLoop_Impl>()->autosizeMaximumLoopFlowRate();
  }

  boost::optional<double> PlantLoop::minimumLoopFlowRate() const {
    return getImpl<detail::PlantLoop_Impl>()->minimumLoopFlowRate();
  }

  bool PlantLoop::setMinimumLoopFlowRate(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setMinimumLoopFlowRate(value);
  }

  bool PlantLoop::isMinimumLoopFlowRateAutosized() const {
    return getImpl<detail::PlantLoop_Impl>()->isMinimumLoopFlowRateAutosized();
  }

  void PlantLoop::autosizeMinimumLoopFlowRate() {
    getImpl<detail::PlantLoop_Impl>()->autosizeMinimumLoopFlowRate();
  }

  boost::optional<double> PlantLoop::plantLoopVolume() const {
    return getImpl<detail::PlantLoop_Impl>()->plantLoopVolume();
  }

  bool PlantLoop::setPlantLoopVolume(double value) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantLoopVolume(value);
  }

  bool PlantLoop::isPlantLoopVolumeAutocalculated() const {
    return getImpl<detail::PlantLoop_Impl>()->isPlantLoopVolumeAutocalculated();
  }

  void PlantLoop::autocalculatePlantLoopVolume() {
    getImpl<detail::PlantLoop_Impl>()->autocalculatePlantLoopVolume();
  }

  std::string PlantLoop::commonPipeSimulation() const {
    return getImpl<detail::PlantLoop_Impl>()->commonPipeSimulation();
  }

  bool PlantLoop::isCommonPipeSimulationDefaulted() const {
    return getImpl<detail::PlantLoop_Impl>()->isCommonPipeSimulationDefaulted();
  }

  bool PlantLoop::setCommonPipeSimulation(const std::string& value) {
    return getImpl<detail::PlantLoop_Impl>()->setCommonPipeSimulation(value);
  }

  void PlantLoop::resetCommonPipeSimulation() {
    getImpl<detail::PlantLoop_Impl>()->resetCommonPipeSimulation();
  }

  Node PlantLoop::loopTemperatureSetpointNode() {
    return getImpl<detail::PlantLoop_Impl>()->loopTemperatureSetpointNode();
  }

  bool PlantLoop::setLoopTemperatureSetpointNode(Node& node) {
    return getImpl<detail::PlantLoop_Impl>()->setLoopTemperatureSetpointNode(node);
  }

  boost::optional<PlantEquipmentOperationHeatingLoad> PlantLoop::plantEquipmentOperationHeatingLoad() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationHeatingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationHeatingLoad(const PlantEquipmentOperationHeatingLoad& plantOperation) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationHeatingLoad(plantOperation);
  }

  void PlantLoop::resetPlantEquipmentOperationHeatingLoad() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationHeatingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationHeatingLoadSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationHeatingLoadSchedule(schedule);
  }

  void PlantLoop::resetPlantEquipmentOperationHeatingLoadSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationHeatingLoadSchedule();
  }

  boost::optional<Schedule> PlantLoop::plantEquipmentOperationHeatingLoadSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationHeatingLoadSchedule();
  }

  boost::optional<PlantEquipmentOperationCoolingLoad> PlantLoop::plantEquipmentOperationCoolingLoad() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationCoolingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationCoolingLoad(const PlantEquipmentOperationCoolingLoad& plantOperation) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationCoolingLoad(plantOperation);
  }

  void PlantLoop::resetPlantEquipmentOperationCoolingLoad() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationCoolingLoad();
  }

  bool PlantLoop::setPlantEquipmentOperationCoolingLoadSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setPlantEquipmentOperationCoolingLoadSchedule(schedule);
  }

  boost::optional<Schedule> PlantLoop::plantEquipmentOperationCoolingLoadSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->plantEquipmentOperationCoolingLoadSchedule();
  }

  void PlantLoop::resetPlantEquipmentOperationCoolingLoadSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetPlantEquipmentOperationCoolingLoadSchedule();
  }

  boost::optional<PlantEquipmentOperationScheme> PlantLoop::primaryPlantEquipmentOperationScheme() const {
    return getImpl<detail::PlantLoop_Impl>()->primaryPlantEquipmentOperationScheme();
  }

  bool PlantLoop::setPrimaryPlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& plantOperation) {
    return getImpl<detail::PlantLoop_Impl>()->setPrimaryPlantEquipmentOperationScheme(plantOperation);
  }

  void PlantLoop::resetPrimaryPlantEquipmentOperationScheme() {
    getImpl<detail::PlantLoop_Impl>()->resetPrimaryPlantEquipmentOperationScheme();
  }

  bool PlantLoop::setPrimaryPlantEquipmentOperationSchemeSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setPrimaryPlantEquipmentOperationSchemeSchedule(schedule);
  }

  void PlantLoop::resetPrimaryPlantEquipmentOperationSchemeSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetPrimaryPlantEquipmentOperationSchemeSchedule();
  }

  boost::optional<Schedule> PlantLoop::primaryPlantEquipmentOperationSchemeSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->primaryPlantEquipmentOperationSchemeSchedule();
  }

  bool PlantLoop::setComponentSetpointOperationSchemeSchedule(Schedule& schedule) {
    return getImpl<detail::PlantLoop_Impl>()->setComponentSetpointOperationSchemeSchedule(schedule);
  }

  void PlantLoop::resetComponentSetpointOperationSchemeSchedule() {
    getImpl<detail::PlantLoop_Impl>()->resetComponentSetpointOperationSchemeSchedule();
  }

  boost::optional<Schedule> PlantLoop::componentSetpointOperationSchemeSchedule() const {
    return getImpl<detail::PlantLoop_Impl>()->componentSetpointOperationSchemeSchedule();
  }

  Node PlantLoop::supplyInletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyInletNode();
  }

  Node PlantLoop::supplyOutletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyOutletNode();
  }

  std::vector<Node> PlantLoop::supplyOutletNodes() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyOutletNodes();
  }

  Node PlantLoop::demandInletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->demandInletNode();
  }

  std::vector<Node> PlantLoop::demandInletNodes() const {
    return getImpl<detail::PlantLoop_Impl>()->demandInletNodes();
  }

  Node PlantLoop::demandOutletNode() const {
    return getImpl<detail::PlantLoop_Impl>()->demandOutletNode();
  }

  Mixer PlantLoop::supplyMixer() const {
    return getImpl<detail::PlantLoop_Impl>()->supplyMixer();
  }

  Splitter PlantLoop::supplySplitter() const {
    return getImpl<detail::PlantLoop_Impl>()->supplySplitter();
  }

  Mixer PlantLoop::demandMixer() {
    return getImpl<detail::PlantLoop_Impl>()->demandMixer();
  }

  Splitter PlantLoop::demandSplitter() {
    return getImpl<detail::PlantLoop_Impl>()->demandSplitter();
  }

  std::vector<ModelObject> PlantLoop::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                       openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->supplyComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> PlantLoop::supplyComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->supplyComponents(type);
  }

  std::vector<ModelObject> PlantLoop::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                       openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->demandComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> PlantLoop::demandComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::PlantLoop_Impl>()->demandComponents(type);
  }

  bool PlantLoop::addSupplyBranchForComponent(HVACComponent hvacComponent) {
    return getImpl<detail::PlantLoop_Impl>()->addSupplyBranchForComponent(hvacComponent);
  }

  bool PlantLoop::removeSupplyBranchWithComponent(HVACComponent hvacComponent) {
    return getImpl<detail::PlantLoop_Impl>()->removeSupplyBranchWithComponent(hvacComponent);
  }

  bool PlantLoop::addDemandBranchForComponent(HVACComponent hvacComponent, bool tertiary) {
    return getImpl<detail::PlantLoop_Impl>()->addDemandBranchForComponent(hvacComponent, tertiary);
  }

  bool PlantLoop::removeDemandBranchWithComponent(HVACComponent hvacComponent) {
    return getImpl<detail::PlantLoop_Impl>()->removeDemandBranchWithComponent(hvacComponent);
  }

  SizingPlant PlantLoop::sizingPlant() const {
    return getImpl<detail::PlantLoop_Impl>()->sizingPlant();
  }

  std::vector<AvailabilityManager> PlantLoop::availabilityManagers() const {
    return getImpl<detail::PlantLoop_Impl>()->availabilityManagers();
  }

  bool PlantLoop::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::PlantLoop_Impl>()->addAvailabilityManager(availabilityManager);
  }

  bool PlantLoop::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::PlantLoop_Impl>()->addAvailabilityManager(availabilityManager, priority);
  }

  bool PlantLoop::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
    return getImpl<detail::PlantLoop_Impl>()->setAvailabilityManagers(availabilityManagers);
  }

  void PlantLoop::resetAvailabilityManagers() {
    getImpl<detail::PlantLoop_Impl>()->resetAvailabilityManagers();
  }

  bool PlantLoop::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::PlantLoop_Impl>()->removeAvailabilityManager(availabilityManager);
  }

  bool PlantLoop::removeAvailabilityManager(unsigned priority) {
    return getImpl<detail::PlantLoop_Impl>()->removeAvailabilityManager(priority);
  }

  bool PlantLoop::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::PlantLoop_Impl>()->setAvailabilityManagerPriority(availabilityManager, priority);
  }

  unsigned PlantLoop::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
    return getImpl<detail::PlantLoop_Impl>()->availabilityManagerPriority(availabilityManager);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      // PlantLoop still stores branch topology in the raw EnergyPlus branch
      // objects, so a number of small local helpers are needed to answer
      // higher-level OpenStudio questions without promoting them into broader
      // reusable APIs prematurely. Keep these helpers file-local unless and
      // until the same behavior is needed in more than one loop
      // implementation.
      bool isBeamDemandBranchComponent(const HVACComponent& hvacComponent) {
        return hvacComponent.optionalCast<CoilCoolingCooledBeam>() || hvacComponent.optionalCast<CoilCoolingFourPipeBeam>()
               || hvacComponent.optionalCast<CoilHeatingFourPipeBeam>();
      }

      template <typename CoilType>
      bool hasOtherBeamDemandComponentOnLoopOfType(const Model& model, const PlantLoop& thisLoop, const HVACComponent& hvacComponent) {
        for (const auto& coil : model.getConcreteModelObjects<CoilType>()) {
          if (coil.handle() == hvacComponent.handle()) {
            continue;
          }
          if (auto loop = coil.plantLoop()) {
            if (*loop == thisLoop) {
              return true;
            }
          }
        }
        return false;
      }

      bool hasOtherBeamDemandComponentOnLoop(const Model& model, const PlantLoop& thisLoop, const HVACComponent& hvacComponent) {
        return hasOtherBeamDemandComponentOnLoopOfType<CoilCoolingCooledBeam>(model, thisLoop, hvacComponent)
               || hasOtherBeamDemandComponentOnLoopOfType<CoilCoolingFourPipeBeam>(model, thisLoop, hvacComponent)
               || hasOtherBeamDemandComponentOnLoopOfType<CoilHeatingFourPipeBeam>(model, thisLoop, hvacComponent);
      }

      bool branchContainsNode(Model model, const Branch& branch, const Node& node, const Node& inletNode, const Node& outletNode, bool isInletBranch,
                              bool isOutletBranch, bool isEquipmentBranch) {
        // Empty equipment branches are represented by a transient branch node
        // rather than a persisted component row. The inlet and outlet anchor
        // branches use the loop's canonical inlet/outlet nodes instead.
        const auto components = branch.components();
        if (components.empty()) {
          if (isEquipmentBranch) {
            return model.getOrCreateTransientByName<Node>(branch.nameString() + " Node") == node;
          }
          if (isInletBranch) {
            return inletNode == node;
          }
          if (isOutletBranch) {
            return outletNode == node;
          }
          return false;
        }

        if (auto firstInletNode = branch.componentInletNode(0u)) {
          if (*firstInletNode == node) {
            return true;
          }
        }

        for (unsigned i = 0; i < components.size(); ++i) {
          if (auto branchOutletNode = branch.componentOutletNode(i)) {
            if (*branchOutletNode == node) {
              return true;
            }
          }
        }

        return false;
      }

      // Plant-loop projection is driven by exact node-role matches, not by
      // child names or parent type alone. That keeps traversal aligned with
      // the actual branch row that was inserted into the loop.
      bool sameNodeTargets(const boost::optional<Node>& lhs, const boost::optional<Node>& rhs) {
        return lhs && rhs && (*lhs == *rhs);
      }

      // Some radiant families persist the parent ZoneHVAC object on the branch
      // even though the canonical OpenStudio API exposes a child coil on the
      // loop. This helper projects the stored parent row back to the transient
      // child coil when the branch inlet/outlet nodes line up with that
      // specific heating or cooling role.
      boost::optional<ModelObject> projectPlantTraversalComponent(const ModelObject& component, const boost::optional<Node>& branchInletNode,
                                                                  const boost::optional<Node>& branchOutletNode) {
        if (auto radiant = component.optionalCast<ZoneHVACLowTempRadiantConstFlow>()) {
          const auto heatingCoil = radiant->heatingCoil();
          const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
            return heatingCoil.cast<ModelObject>();
          }

          const auto coolingCoil = radiant->coolingCoil();
          const auto coolingInlet = coolingCoil.inletModelObject() ? coolingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto coolingOutlet = coolingCoil.outletModelObject() ? coolingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, coolingInlet) && sameNodeTargets(branchOutletNode, coolingOutlet)) {
            return coolingCoil.cast<ModelObject>();
          }
        }

        if (auto radiant = component.optionalCast<ZoneHVACLowTempRadiantVarFlow>()) {
          if (auto heating = radiant->heatingCoil()) {
            auto heatingCoil = heating->cast<CoilHeatingLowTempRadiantVarFlow>();
            const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
            const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
            if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
              return heatingCoil.cast<ModelObject>();
            }
          }

          if (auto cooling = radiant->coolingCoil()) {
            auto coolingCoil = cooling->cast<CoilCoolingLowTempRadiantVarFlow>();
            const auto coolingInlet = coolingCoil.inletModelObject() ? coolingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
            const auto coolingOutlet = coolingCoil.outletModelObject() ? coolingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
            if (sameNodeTargets(branchInletNode, coolingInlet) && sameNodeTargets(branchOutletNode, coolingOutlet)) {
              return coolingCoil.cast<ModelObject>();
            }
          }
        }

        if (auto baseboard = component.optionalCast<ZoneHVACBaseboardRadiantConvectiveWater>()) {
          const auto heatingCoil = baseboard->heatingCoil().cast<CoilHeatingWaterBaseboardRadiant>();
          const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
            return heatingCoil.cast<ModelObject>();
          }
        }

        if (auto baseboard = component.optionalCast<ZoneHVACBaseboardConvectiveWater>()) {
          const auto heatingCoil = baseboard->heatingCoil().cast<CoilHeatingWaterBaseboard>();
          const auto heatingInlet = heatingCoil.inletModelObject() ? heatingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto heatingOutlet = heatingCoil.outletModelObject() ? heatingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, heatingInlet) && sameNodeTargets(branchOutletNode, heatingOutlet)) {
            return heatingCoil.cast<ModelObject>();
          }
        }

        if (auto panel = component.optionalCast<ZoneHVACCoolingPanelRadiantConvectiveWater>()) {
          const auto coolingCoil = panel->coolingCoil().cast<CoilCoolingWaterPanelRadiant>();
          const auto coolingInlet = coolingCoil.inletModelObject() ? coolingCoil.inletModelObject()->optionalCast<Node>() : boost::none;
          const auto coolingOutlet = coolingCoil.outletModelObject() ? coolingCoil.outletModelObject()->optionalCast<Node>() : boost::none;
          if (sameNodeTargets(branchInletNode, coolingInlet) && sameNodeTargets(branchOutletNode, coolingOutlet)) {
            return coolingCoil.cast<ModelObject>();
          }
        }

        if (component.iddObject().type() == IddObjectType::GroundHeatExchanger_System) {
          if (auto target = component.getTarget(openstudio::GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName)) {
            if (auto vertical = target->optionalCast<GroundHeatExchangerVertical>()) {
              const auto verticalInlet = vertical->inletModelObject() ? vertical->inletModelObject()->optionalCast<Node>() : boost::none;
              const auto verticalOutlet = vertical->outletModelObject() ? vertical->outletModelObject()->optionalCast<Node>() : boost::none;
              if (sameNodeTargets(branchInletNode, verticalInlet) && sameNodeTargets(branchOutletNode, verticalOutlet)) {
                return vertical->cast<ModelObject>();
              }
            }
          }
        }

        return component;
      }

      // Branch rows remain the persisted source of truth. This helper only
      // rewrites the traversal view that higher-level OpenStudio-style APIs
      // return to callers.
      std::vector<ModelObject> projectedBranchComponents(const Branch& branch) {
        const auto rawComponents = branch.components();
        std::vector<ModelObject> result;
        result.reserve(rawComponents.size());
        for (unsigned i = 0; i < rawComponents.size(); ++i) {
          result.push_back(*projectPlantTraversalComponent(rawComponents[i], branch.componentInletNode(i), branch.componentOutletNode(i)));
        }
        return result;
      }

    }  // namespace

    // PipeAdiabatic attachment is prepared while its existing
    // plant branch and node fields remain untouched. The target row is
    // provisional: abandoning the plan removes that row, any branch created
    // for it, and only the transient nodes created by preparation.
    class PlantLoop_Impl::PipeBranchAttachmentPlan
    {
     public:
      static std::unique_ptr<PipeBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl, StraightComponent component, bool supplySide) {
        if (component.model() != targetLoopImpl.model() || component.containingHVACComponent() || !component.name()) {
          return nullptr;
        }

        const auto inletPort = component.inletPort();
        const auto outletPort = component.outletPort();
        if (inletPort == 0u || outletPort == 0u || inletPort == outletPort) {
          return nullptr;
        }

        boost::optional<Branch> sourceBranch;
        boost::optional<PlantLoop> sourcePlantLoop;
        boost::optional<Node> sourceInletNode;
        boost::optional<Node> sourceOutletNode;
        boost::optional<ModelObject> sourceAdjacentComponent;
        bool sourceAdjacentInlet = false;
        bool removeEmptySourceBranch = false;
        boost::optional<BranchList> sourceBranchList;
        boost::optional<ConnectorSplitter> sourceSplitter;
        boost::optional<ConnectorMixer> sourceMixer;
        bool sourceSupplySide = false;
        unsigned sourceComponentIndex = 0u;
        if (auto sourceLoop = component.plantLoop()) {
          if (*sourceLoop == targetLoopImpl.getObject<PlantLoop>()) {
            return nullptr;
          }
          sourcePlantLoop = *sourceLoop;

          sourceInletNode = component.inletModelObject() ? component.inletModelObject()->optionalCast<Node>() : boost::none;
          sourceOutletNode = component.outletModelObject() ? component.outletModelObject()->optionalCast<Node>() : boost::none;
          if (!sourceInletNode || !sourceOutletNode) {
            return nullptr;
          }

          auto sourceLoopImpl = sourceLoop->getImpl<PlantLoop_Impl>();
          std::vector<Branch> sourceBranches{sourceLoopImpl->supplyInletBranch()};
          const auto sourceSupplyEquipmentBranches = sourceLoopImpl->supplyEquipmentBranches();
          sourceBranches.insert(sourceBranches.end(), sourceSupplyEquipmentBranches.begin(), sourceSupplyEquipmentBranches.end());
          sourceBranches.push_back(sourceLoopImpl->supplyOutletBranch());
          sourceBranches.push_back(sourceLoopImpl->demandInletBranch());
          const auto sourceDemandEquipmentBranches = sourceLoopImpl->demandEquipmentBranches();
          sourceBranches.insert(sourceBranches.end(), sourceDemandEquipmentBranches.begin(), sourceDemandEquipmentBranches.end());
          sourceBranches.push_back(sourceLoopImpl->demandOutletBranch());

          unsigned sourceOccurrences = 0u;
          for (const auto& candidateBranch : sourceBranches) {
            const auto sourceComponents = candidateBranch.components();
            for (unsigned i = 0u; i < sourceComponents.size(); ++i) {
              if (sourceComponents[i] != component.cast<ModelObject>()) {
                continue;
              }
              const auto branchInletNode = candidateBranch.componentInletNode(i);
              const auto branchOutletNode = candidateBranch.componentOutletNode(i);
              if (!branchInletNode || !branchOutletNode || *branchInletNode != *sourceInletNode || *branchOutletNode != *sourceOutletNode) {
                return nullptr;
              }
              ++sourceOccurrences;
              sourceBranch = candidateBranch;
              sourceComponentIndex = i;
            }
          }
          if (sourceOccurrences != 1u || !sourceBranch) {
            return nullptr;
          }

          const auto sourceComponents = sourceBranch->components();
          if (sourceComponentIndex + 1u < sourceComponents.size()) {
            const auto adjacentBranchNode = sourceBranch->componentInletNode(sourceComponentIndex + 1u);
            boost::optional<ModelObject> adjacentComponentNode;
            if (auto adjacent = sourceComponents[sourceComponentIndex + 1u].optionalCast<WaterToAirComponent>()) {
              adjacentComponentNode = adjacent->waterInletModelObject();
            } else if (auto adjacent = sourceComponents[sourceComponentIndex + 1u].optionalCast<StraightComponent>()) {
              adjacentComponentNode = adjacent->inletModelObject();
            } else {
              return nullptr;
            }
            if (!adjacentBranchNode || !adjacentComponentNode || adjacentBranchNode->handle() != sourceOutletNode->handle()
                || adjacentComponentNode->handle() != sourceOutletNode->handle()) {
              return nullptr;
            }
            sourceAdjacentComponent = sourceComponents[sourceComponentIndex + 1u];
            sourceAdjacentInlet = true;
          } else if (sourceComponentIndex > 0u) {
            const auto adjacentBranchNode = sourceBranch->componentOutletNode(sourceComponentIndex - 1u);
            boost::optional<ModelObject> adjacentComponentNode;
            if (auto adjacent = sourceComponents[sourceComponentIndex - 1u].optionalCast<WaterToAirComponent>()) {
              adjacentComponentNode = adjacent->waterOutletModelObject();
            } else if (auto adjacent = sourceComponents[sourceComponentIndex - 1u].optionalCast<StraightComponent>()) {
              adjacentComponentNode = adjacent->outletModelObject();
            } else {
              return nullptr;
            }
            if (!adjacentBranchNode || !adjacentComponentNode || adjacentBranchNode->handle() != sourceInletNode->handle()
                || adjacentComponentNode->handle() != sourceInletNode->handle()) {
              return nullptr;
            }
            sourceAdjacentComponent = sourceComponents[sourceComponentIndex - 1u];
          }

          const bool sourceIsSupplyEquipmentBranch =
            std::ranges::find(sourceSupplyEquipmentBranches, *sourceBranch) != sourceSupplyEquipmentBranches.end();
          const bool sourceIsDemandEquipmentBranch =
            std::ranges::find(sourceDemandEquipmentBranches, *sourceBranch) != sourceDemandEquipmentBranches.end();
          if (sourceComponents.size() == 1u
              && ((sourceIsSupplyEquipmentBranch && sourceSupplyEquipmentBranches.size() > 1u)
                  || (sourceIsDemandEquipmentBranch && sourceDemandEquipmentBranches.size() > 1u))) {
            sourceSupplySide = sourceIsSupplyEquipmentBranch;
            sourceBranchList = sourceSupplySide ? sourceLoopImpl->supplyBranchList() : sourceLoopImpl->demandBranchList();
            sourceSplitter = (sourceSupplySide ? sourceLoopImpl->supplySplitter() : sourceLoopImpl->demandSplitter()).cast<ConnectorSplitter>();
            sourceMixer = (sourceSupplySide ? sourceLoopImpl->supplyMixer() : sourceLoopImpl->demandMixer()).cast<ConnectorMixer>();
            removeEmptySourceBranch = true;
          }
        }

        auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        auto targetBranchList = supplySide ? targetLoopImpl.supplyBranchList() : targetLoopImpl.demandBranchList();
        auto targetEquipmentBranches = supplySide ? targetLoopImpl.supplyEquipmentBranches() : targetLoopImpl.demandEquipmentBranches();
        if (targetEquipmentBranches.empty()) {
          return nullptr;
        }
        auto targetSplitter = (supplySide ? targetLoopImpl.supplySplitter() : targetLoopImpl.demandSplitter()).cast<ConnectorSplitter>();
        auto targetMixer = (supplySide ? targetLoopImpl.supplyMixer() : targetLoopImpl.demandMixer()).cast<ConnectorMixer>();
        const auto originalTargetBranchCount = static_cast<unsigned>(targetBranchList.extensibleGroups().size());
        const auto targetBranchInsertIndex = static_cast<unsigned>(targetBranchList.branches().size() - 1u);

        bool createdTargetBranch = false;
        boost::optional<Branch> targetBranch;
        if (targetEquipmentBranches.size() == 1u && targetEquipmentBranches.front().extensibleGroups().empty()) {
          targetBranch = targetEquipmentBranches.front();
        } else {
          Branch branch(targetLoopImpl.model());
          const auto branchName = targetLoop.nameString() + (supplySide ? " Supply Branch " : " Demand Branch ")
                                  + std::to_string(static_cast<unsigned>(targetEquipmentBranches.size() + 1u));
          if (!branch.setName(branchName) && !branch.setName(targetLoopImpl.model().nextName(openstudio::IddObjectType::Branch, true))) {
            branch.remove();
            return nullptr;
          }

          targetBranch = branch;
          createdTargetBranch = true;
        }

        OS_ASSERT(targetBranch);
        auto plan = std::unique_ptr<PipeBranchAttachmentPlan>(
          new PipeBranchAttachmentPlan(targetLoop, component, supplySide, targetBranchList, targetSplitter, targetMixer, *targetBranch,
                                       createdTargetBranch, sourceBranch, sourcePlantLoop, sourceComponentIndex, sourceInletNode, sourceOutletNode,
                                       sourceAdjacentComponent, sourceAdjacentInlet, removeEmptySourceBranch, sourceBranchList, sourceSplitter,
                                       sourceMixer, sourceSupplySide, originalTargetBranchCount, targetBranchInsertIndex));
        if (createdTargetBranch) {
          plan->m_targetBranchInsertionAttempted = true;
          if (!targetBranchList.getImpl<BranchList_Impl>()->insertBranch(targetBranchInsertIndex, *targetBranch)) {
            return nullptr;
          }
          targetEquipmentBranches = supplySide ? targetLoopImpl.supplyEquipmentBranches() : targetLoopImpl.demandEquipmentBranches();
          const bool synchronized = supplySide ? targetLoopImpl.syncConnectorPorts(targetSplitter, targetMixer, targetLoopImpl.supplyInletBranch(),
                                                                                   targetLoopImpl.supplyOutletBranch(), targetEquipmentBranches)
                                               : targetLoopImpl.syncConnectorPorts(targetSplitter, targetMixer, targetLoopImpl.demandInletBranch(),
                                                                                   targetLoopImpl.demandOutletBranch(), targetEquipmentBranches);
          if (!synchronized) {
            return nullptr;
          }
        }

        const auto targetNodeName = targetBranch->nameString() + " Node";
        const auto targetOutletNodeName = targetNodeName + " - " + component.nameString() + " Outlet";
        const bool targetNodeExisted = static_cast<bool>(targetLoopImpl.model().getConcreteModelObjectByName<Node>(targetNodeName));
        const bool targetOutletNodeExisted = static_cast<bool>(targetLoopImpl.model().getConcreteModelObjectByName<Node>(targetOutletNodeName));

        if (!targetNodeExisted) {
          plan->m_createdNodeNames.push_back(targetNodeName);
        }
        if (!targetOutletNodeExisted && targetOutletNodeName != targetNodeName) {
          plan->m_createdNodeNames.push_back(targetOutletNodeName);
        }
        auto targetBranchImpl = targetBranch->getImpl<Branch_Impl>();
        OS_ASSERT(targetBranchImpl);
        plan->m_targetRowAttempted = true;
        if (!targetBranchImpl->appendComponent(component.cast<ModelObject>(), targetNodeName, targetOutletNodeName)) {
          return nullptr;
        }

        plan->m_targetInletNode = targetBranch->componentInletNode(0u);
        plan->m_targetOutletNode = targetBranch->componentOutletNode(0u);
        if (!plan->m_targetInletNode || !plan->m_targetOutletNode) {
          return nullptr;
        }

        plan->m_prepared = true;
        return plan;
      }

      PipeBranchAttachmentPlan(const PipeBranchAttachmentPlan&) = delete;
      PipeBranchAttachmentPlan& operator=(const PipeBranchAttachmentPlan&) = delete;
      PipeBranchAttachmentPlan(PipeBranchAttachmentPlan&&) = delete;
      PipeBranchAttachmentPlan& operator=(PipeBranchAttachmentPlan&&) = delete;

      ~PipeBranchAttachmentPlan() {
        if (m_committed) {
          return;
        }

        if (m_targetRowAttempted) {
          m_targetBranch.getImpl<Branch_Impl>()->clearComponents();
        }
        if (m_createdTargetBranch) {
          if (m_targetBranchInsertionAttempted && m_targetBranchList.extensibleGroups().size() > m_originalTargetBranchCount) {
            const auto removedFields = m_targetBranchList.eraseExtensibleGroup(m_targetBranchInsertIndex);
            OS_ASSERT(!removedFields.empty());
          }
          auto targetLoopImpl = m_targetLoop.getImpl<PlantLoop_Impl>();
          const auto equipmentBranches = m_supplySide ? targetLoopImpl->supplyEquipmentBranches() : targetLoopImpl->demandEquipmentBranches();
          // Canonical connector shape was proven before preparation; only this plan's same-model exact Branch was added, so rollback resync is no-fail.
          const bool synchronized = m_supplySide
                                      ? targetLoopImpl->syncConnectorPorts(m_targetSplitter, m_targetMixer, targetLoopImpl->supplyInletBranch(),
                                                                           targetLoopImpl->supplyOutletBranch(), equipmentBranches)
                                      : targetLoopImpl->syncConnectorPorts(m_targetSplitter, m_targetMixer, targetLoopImpl->demandInletBranch(),
                                                                           targetLoopImpl->demandOutletBranch(), equipmentBranches);
          OS_ASSERT(synchronized);
          m_targetBranch.remove();
          OS_ASSERT(!m_targetLoop.model().getObject(m_targetBranch.handle()));
        }
        for (auto it = m_createdNodeNames.rbegin(); it != m_createdNodeNames.rend(); ++it) {
          if (auto node = m_targetLoop.model().getConcreteModelObjectByName<Node>(*it)) {
            const auto nodeHandle = node->handle();
            node->remove();
            OS_ASSERT(!m_targetLoop.model().getObject(nodeHandle));
          }
        }
      }

      void commit() {
        OS_ASSERT(m_prepared && !m_committed && m_targetInletNode && m_targetOutletNode);

        if (m_sourceBranch) {
          auto sourceBranchImpl = m_sourceBranch->getImpl<Branch_Impl>();
          OS_ASSERT(sourceBranchImpl && m_sourceInletNode && m_sourceOutletNode);
          const auto sourceComponents = m_sourceBranch->components();
          OS_ASSERT(m_sourceComponentIndex < sourceComponents.size() && sourceComponents[m_sourceComponentIndex] == m_component.cast<ModelObject>());
          if (m_sourceComponentIndex + 1u < sourceComponents.size()) {
            const bool bypassed = sourceBranchImpl->setComponentInletNode(m_sourceComponentIndex + 1u, *m_sourceInletNode);
            OS_ASSERT(bypassed);
          } else if (m_sourceComponentIndex > 0u) {
            const bool bypassed = sourceBranchImpl->setComponentOutletNode(m_sourceComponentIndex - 1u, *m_sourceOutletNode);
            OS_ASSERT(bypassed);
          }
          if (m_sourceAdjacentComponent) {
            const bool repaired = StraightComponent_Impl::updateAdjacentBranchComponentNode(
              *m_sourceAdjacentComponent, m_sourceAdjacentInlet ? *m_sourceInletNode : *m_sourceOutletNode, m_sourceAdjacentInlet, false);
            OS_ASSERT(repaired);
          }
          const bool removed = sourceBranchImpl->removeComponent(m_sourceComponentIndex);
          OS_ASSERT(removed);

          if (m_removeEmptySourceBranch) {
            OS_ASSERT(m_sourceBranchList && m_sourceSplitter && m_sourceMixer);
            auto sourceBranchListImpl = m_sourceBranchList->getImpl<BranchList_Impl>();
            OS_ASSERT(sourceBranchListImpl);
            const bool removedBranchFromList = sourceBranchListImpl->removeBranch(*m_sourceBranch);
            OS_ASSERT(removedBranchFromList);
            m_sourceBranch->remove();
            OS_ASSERT(!m_targetLoop.model().getObject(m_sourceBranch->handle()));

            OS_ASSERT(m_sourcePlantLoop);
            auto sourceLoopImpl = m_sourcePlantLoop->getImpl<PlantLoop_Impl>();
            const auto sourceEquipmentBranches =
              m_sourceSupplySide ? sourceLoopImpl->supplyEquipmentBranches() : sourceLoopImpl->demandEquipmentBranches();
            const bool synchronized = m_sourceSupplySide
                                        ? sourceLoopImpl->syncConnectorPorts(*m_sourceSplitter, *m_sourceMixer, sourceLoopImpl->supplyInletBranch(),
                                                                             sourceLoopImpl->supplyOutletBranch(), sourceEquipmentBranches)
                                        : sourceLoopImpl->syncConnectorPorts(*m_sourceSplitter, *m_sourceMixer, sourceLoopImpl->demandInletBranch(),
                                                                             sourceLoopImpl->demandOutletBranch(), sourceEquipmentBranches);
            OS_ASSERT(synchronized);
          }
        }

        const bool inletSet = m_component.setPointer(m_component.inletPort(), m_targetInletNode->handle());
        const bool outletSet = m_component.setPointer(m_component.outletPort(), m_targetOutletNode->handle());
        OS_ASSERT(inletSet && outletSet);
        m_committed = true;
      }

     private:
      PipeBranchAttachmentPlan(PlantLoop targetLoop, StraightComponent component, bool supplySide, BranchList targetBranchList,
                               ConnectorSplitter targetSplitter, ConnectorMixer targetMixer, Branch targetBranch, bool createdTargetBranch,
                               boost::optional<Branch> sourceBranch, boost::optional<PlantLoop> sourcePlantLoop, unsigned sourceComponentIndex,
                               boost::optional<Node> sourceInletNode, boost::optional<Node> sourceOutletNode,
                               boost::optional<ModelObject> sourceAdjacentComponent, bool sourceAdjacentInlet, bool removeEmptySourceBranch,
                               boost::optional<BranchList> sourceBranchList, boost::optional<ConnectorSplitter> sourceSplitter,
                               boost::optional<ConnectorMixer> sourceMixer, bool sourceSupplySide, unsigned originalTargetBranchCount,
                               unsigned targetBranchInsertIndex)
        : m_targetLoop(std::move(targetLoop)),
          m_component(std::move(component)),
          m_supplySide(supplySide),
          m_targetBranchList(std::move(targetBranchList)),
          m_targetSplitter(std::move(targetSplitter)),
          m_targetMixer(std::move(targetMixer)),
          m_targetBranch(std::move(targetBranch)),
          m_createdTargetBranch(createdTargetBranch),
          m_sourceBranch(std::move(sourceBranch)),
          m_sourcePlantLoop(std::move(sourcePlantLoop)),
          m_sourceComponentIndex(sourceComponentIndex),
          m_sourceInletNode(std::move(sourceInletNode)),
          m_sourceOutletNode(std::move(sourceOutletNode)),
          m_sourceAdjacentComponent(std::move(sourceAdjacentComponent)),
          m_sourceAdjacentInlet(sourceAdjacentInlet),
          m_removeEmptySourceBranch(removeEmptySourceBranch),
          m_sourceBranchList(std::move(sourceBranchList)),
          m_sourceSplitter(std::move(sourceSplitter)),
          m_sourceMixer(std::move(sourceMixer)),
          m_sourceSupplySide(sourceSupplySide),
          m_originalTargetBranchCount(originalTargetBranchCount),
          m_targetBranchInsertIndex(targetBranchInsertIndex) {}

      PlantLoop m_targetLoop;
      StraightComponent m_component;
      bool m_supplySide;
      BranchList m_targetBranchList;
      ConnectorSplitter m_targetSplitter;
      ConnectorMixer m_targetMixer;
      Branch m_targetBranch;
      bool m_createdTargetBranch;
      boost::optional<Branch> m_sourceBranch;
      boost::optional<PlantLoop> m_sourcePlantLoop;
      unsigned m_sourceComponentIndex;
      boost::optional<Node> m_sourceInletNode;
      boost::optional<Node> m_sourceOutletNode;
      boost::optional<ModelObject> m_sourceAdjacentComponent;
      bool m_sourceAdjacentInlet;
      bool m_removeEmptySourceBranch;
      boost::optional<BranchList> m_sourceBranchList;
      boost::optional<ConnectorSplitter> m_sourceSplitter;
      boost::optional<ConnectorMixer> m_sourceMixer;
      bool m_sourceSupplySide;
      boost::optional<Node> m_targetInletNode;
      boost::optional<Node> m_targetOutletNode;
      std::vector<std::string> m_createdNodeNames;
      unsigned m_originalTargetBranchCount;
      unsigned m_targetBranchInsertIndex;
      bool m_targetBranchInsertionAttempted = false;
      bool m_targetRowAttempted = false;
      bool m_prepared = false;
      bool m_committed = false;
    };

    // Private one-shot demand-branch relocation shared only by the exact
    // owner-proven water-coil plans, the exact fluid-to-fluid heat exchanger,
    // the exact stratified chilled-water storage, the exact Electric EIR chiller
    // heat-recovery plan, the two exact PlantLoop EIR heat-pump source plans,
    // and the two exact EquationFit heat-pump plans below.
    // Callers retain all component-specific ownership
    // validation; this plan owns only the proven plant representation and two
    // explicit component-port writes.
    class PlantLoop_Impl::DemandBranchRelocationPlan
    {
     public:
      using ExternalRow = std::pair<Handle, unsigned>;

      static std::unique_ptr<DemandBranchRelocationPlan> prepareWaterCoil(PlantLoop_Impl& targetLoopImpl, WaterToAirComponent coil,
                                                                          const std::vector<ExternalRow>& validatedExternalRows) {
        const auto sourceLoop = coil.plantLoop();
        if (!sourceLoop) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, coil.cast<HVACComponent>(), *sourceLoop, coil.waterInletPort(), coil.waterOutletPort(),
                             validatedExternalRows);
      }

      static std::unique_ptr<DemandBranchRelocationPlan> prepareFluidToFluidHeatExchanger(PlantLoop_Impl& targetLoopImpl,
                                                                                          HeatExchangerFluidToFluid heatExchanger,
                                                                                          PlantLoop sourceLoop,
                                                                                          const ExternalRow& validatedPrimaryRow) {
        if (heatExchanger.iddObject().type() != HeatExchangerFluidToFluid::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, heatExchanger.cast<HVACComponent>(), std::move(sourceLoop), heatExchanger.demandInletPort(),
                             heatExchanger.demandOutletPort(), {validatedPrimaryRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan> prepareChillerElectricEIRHeatRecovery(PlantLoop_Impl& targetLoopImpl,
                                                                                               ChillerElectricEIR chiller, PlantLoop sourceLoop,
                                                                                               const ExternalRow& validatedPrimaryRow,
                                                                                               const ExternalRow& validatedCondenserRow) {
        if (chiller.iddObject().type() != ChillerElectricEIR::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, chiller.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::Chiller_Electric_EIRFields::HeatRecoveryInletNodeName,
                             openstudio::Chiller_Electric_EIRFields::HeatRecoveryOutletNodeName, {validatedPrimaryRow, validatedCondenserRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan> preparePlantLoopEIRHeatingSource(PlantLoop_Impl& targetLoopImpl,
                                                                                          HeatPumpPlantLoopEIRHeating heatPump, PlantLoop sourceLoop,
                                                                                          const ExternalRow& validatedPrimaryRow,
                                                                                          const ExternalRow& validatedHeatRecoveryRow) {
        if (heatPump.iddObject().type() != HeatPumpPlantLoopEIRHeating::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideInletNodeName,
                             openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideOutletNodeName,
                             {validatedPrimaryRow, validatedHeatRecoveryRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan> preparePlantLoopEIRCoolingSource(PlantLoop_Impl& targetLoopImpl,
                                                                                          HeatPumpPlantLoopEIRCooling heatPump, PlantLoop sourceLoop,
                                                                                          const ExternalRow& validatedPrimaryRow,
                                                                                          const ExternalRow& validatedHeatRecoveryRow) {
        if (heatPump.iddObject().type() != HeatPumpPlantLoopEIRCooling::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName,
                             openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName,
                             {validatedPrimaryRow, validatedHeatRecoveryRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan>
        preparePlantLoopEIRHeatingHeatRecovery(PlantLoop_Impl& targetLoopImpl, HeatPumpPlantLoopEIRHeating heatPump, PlantLoop sourceLoop,
                                               const ExternalRow& validatedPrimaryRow, const ExternalRow& validatedSourceRow) {
        if (heatPump.iddObject().type() != HeatPumpPlantLoopEIRHeating::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryInletNodeName,
                             openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryOutletNodeName, {validatedPrimaryRow, validatedSourceRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan>
        preparePlantLoopEIRCoolingHeatRecovery(PlantLoop_Impl& targetLoopImpl, HeatPumpPlantLoopEIRCooling heatPump, PlantLoop sourceLoop,
                                               const ExternalRow& validatedPrimaryRow, const ExternalRow& validatedSourceRow) {
        if (heatPump.iddObject().type() != HeatPumpPlantLoopEIRCooling::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName,
                             openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName, {validatedPrimaryRow, validatedSourceRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan> prepareThermalStorageChilledWaterStratified(PlantLoop_Impl& targetLoopImpl,
                                                                                                     ThermalStorageChilledWaterStratified storage,
                                                                                                     PlantLoop sourceLoop,
                                                                                                     const ExternalRow& validatedPrimaryRow) {
        if (storage.iddObject().type() != ThermalStorageChilledWaterStratified::iddObjectType()) {
          return nullptr;
        }
        return prepareProven(targetLoopImpl, storage.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletNodeName,
                             openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletNodeName, {validatedPrimaryRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan> prepareEquationFitHeatingHeatPump(PlantLoop_Impl& targetLoopImpl,
                                                                                           HeatPumpWaterToWaterEquationFitHeating heatPump,
                                                                                           PlantLoop sourceLoop,
                                                                                           const ExternalRow& validatedPrimaryRow) {
        if (heatPump.iddObject().type() != HeatPumpWaterToWaterEquationFitHeating::iddObjectType()) {
          return nullptr;
        }
        // For this exact EPModel type, demand attachment owns the persisted
        // load-side fields; the source-side fields remain with the primary loop.
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName,
                             openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName, {validatedPrimaryRow});
      }

      static std::unique_ptr<DemandBranchRelocationPlan> prepareEquationFitCoolingHeatPump(PlantLoop_Impl& targetLoopImpl,
                                                                                           HeatPumpWaterToWaterEquationFitCooling heatPump,
                                                                                           PlantLoop sourceLoop,
                                                                                           const ExternalRow& validatedPrimaryRow) {
        if (heatPump.iddObject().type() != HeatPumpWaterToWaterEquationFitCooling::iddObjectType()) {
          return nullptr;
        }
        // For this exact EPModel type, demand attachment owns the persisted
        // source-side fields; the load-side fields remain with the primary loop.
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), std::move(sourceLoop),
                             openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName,
                             openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName, {validatedPrimaryRow});
      }

     private:
      static bool rawNodeIdentityIsReferenced(const Model& model, const std::string& nodeName,
                                              const boost::optional<Handle>& nodeHandle = boost::none,
                                              const boost::optional<Handle>& ignoredObject = boost::none) {
        for (const auto& object : model.objects()) {
          if (ignoredObject && object.handle() == *ignoredObject) {
            continue;
          }
          auto workspaceImpl = object.getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(workspaceImpl);
          for (unsigned field = 0u; field < object.numFields(); ++field) {
            const auto raw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
            if (raw && !raw->empty() && (openstudio::istringEqual(*raw, nodeName) || (nodeHandle && openstudio::toUUID(*raw) == *nodeHandle))) {
              return true;
            }
          }
        }
        return false;
      }

      static bool generatedNodeNameIsAbsentAndUnowned(const Model& model, const std::string& nodeName) {
        return !model.getConcreteModelObjectByName<Node>(nodeName) && !rawNodeIdentityIsReferenced(model, nodeName);
      }

      static bool isCanonicalEmptyBranchAnchor(const Model& model, const Branch& branch, const std::string& nodeName) {
        const auto nodes = model.getConcreteModelObjects<Node>();
        boost::optional<Node> anchor;
        for (const auto& node : nodes) {
          if (!openstudio::istringEqual(node.nameString(), nodeName)) {
            continue;
          }
          if (anchor) {
            return false;
          }
          anchor = node;
        }
        return branch.extensibleGroups().empty() && anchor && anchor->sources().empty()
               && !rawNodeIdentityIsReferenced(model, nodeName, anchor->handle(), anchor->handle());
      }

      static std::unique_ptr<DemandBranchRelocationPlan> prepareProven(PlantLoop_Impl& targetLoopImpl, HVACComponent component, PlantLoop sourceLoop,
                                                                       unsigned inletPort, unsigned outletPort,
                                                                       const std::vector<ExternalRow>& validatedExternalRows) {
        if ((component.model() != targetLoopImpl.model()) || (sourceLoop.model() != targetLoopImpl.model()) || !component.name()) {
          return nullptr;
        }
        for (auto row = validatedExternalRows.begin(); row != validatedExternalRows.end(); ++row) {
          if (std::ranges::find(row + 1, validatedExternalRows.end(), *row) != validatedExternalRows.end()) {
            return nullptr;
          }
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if ((sourceLoop == targetLoop) || !sourceLoop.demandComponent(component.handle()) || targetLoopImpl.demandComponent(component.handle())) {
          return nullptr;
        }

        auto sourceLoopImpl = sourceLoop.getImpl<PlantLoop_Impl>();
        OS_ASSERT(sourceLoopImpl);
        auto sourceTopology = validatedDemandSideTopology(*sourceLoopImpl);
        auto targetTopology = validatedDemandSideTopology(targetLoopImpl);
        if (!sourceTopology || !targetTopology) {
          return nullptr;
        }

        const auto inletField = existingNodeField(component, inletPort);
        const auto outletField = existingNodeField(component, outletPort);
        if (!inletField.set || !inletField.node || !outletField.set || !outletField.node) {
          return nullptr;
        }

        boost::optional<Branch> sourceBranch;
        unsigned sourceOccurrences = 0u;
        std::vector<unsigned> externalOccurrences(validatedExternalRows.size(), 0u);
        for (const auto& branch : targetLoopImpl.model().getConcreteModelObjects<Branch>()) {
          const auto groups = branch.extensibleGroups();
          for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
            const auto componentNameIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentName));
            const auto relationship = existingObjectField(branch, componentNameIndex);
            auto branchWorkspaceImpl = branch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(branchWorkspaceImpl);
            const auto rawComponentName = branchWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(componentNameIndex, false, true);
            const auto rawComponentHandle = rawComponentName ? openstudio::toUUID(*rawComponentName) : Handle();
            const auto componentType = groups[groupIndex].getString(openstudio::BranchExtensibleFields::ComponentObjectType, false);
            const bool referencesComponent = (relationship.object && relationship.object->handle() == component.handle())
                                             || (!rawComponentHandle.isNull() && rawComponentHandle == component.handle())
                                             || (componentType && openstudio::istringEqual(*componentType, component.iddObject().name())
                                                 && rawComponentName && openstudio::istringEqual(*rawComponentName, component.nameString()));
            if (!referencesComponent) {
              continue;
            }
            if (!relationship.set || !relationship.object || relationship.object->handle() != component.handle() || !componentType
                || !openstudio::istringEqual(*componentType, component.iddObject().name())) {
              return nullptr;
            }

            const ExternalRow rowIdentity{branch.handle(), groupIndex};
            const auto externalRow = std::ranges::find(validatedExternalRows, rowIdentity);
            if (externalRow != validatedExternalRows.end()) {
              const auto externalIndex = static_cast<unsigned>(std::distance(validatedExternalRows.begin(), externalRow));
              ++externalOccurrences[externalIndex];
              if (std::ranges::find(sourceTopology->equipmentBranches, branch) != sourceTopology->equipmentBranches.end()) {
                return nullptr;
              }
              continue;
            }

            if (std::ranges::find(sourceTopology->equipmentBranches, branch) == sourceTopology->equipmentBranches.end()) {
              return nullptr;
            }
            const auto branchInletNodeIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentInletNodeName));
            const auto branchOutletNodeIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentOutletNodeName));
            const auto branchInletField = existingNodeField(branch, branchInletNodeIndex);
            const auto branchOutletField = existingNodeField(branch, branchOutletNodeIndex);
            ++sourceOccurrences;
            if (groups.size() != 1u || !branchInletField.set || !branchInletField.node || !branchOutletField.set || !branchOutletField.node
                || *branchInletField.node != *inletField.node || *branchOutletField.node != *outletField.node) {
              return nullptr;
            }
            sourceBranch = branch;
          }
        }
        if (sourceOccurrences != 1u || !sourceBranch
            || std::ranges::any_of(externalOccurrences, [](unsigned occurrences) { return occurrences != 1u; })) {
          return nullptr;
        }

        bool createdTargetBranch = false;
        boost::optional<Branch> targetBranch;
        if (targetTopology->equipmentBranches.size() == 1u && targetTopology->equipmentBranches.front().extensibleGroups().empty()) {
          targetBranch = targetTopology->equipmentBranches.front();
        } else {
          Branch branch(targetLoopImpl.model());
          const auto branchName =
            targetLoop.nameString() + " Demand Branch " + std::to_string(static_cast<unsigned>(targetTopology->equipmentBranches.size() + 1u));
          if (!branch.setName(branchName) && !branch.setName(targetLoopImpl.model().nextName(openstudio::IddObjectType::Branch, true))) {
            branch.remove();
            return nullptr;
          }
          targetBranch = branch;
          createdTargetBranch = true;
        }

        OS_ASSERT(targetBranch);
        const auto targetNodeName = targetBranch->nameString() + " Node";
        const auto targetOutletNodeName = targetNodeName + " - " + component.nameString() + " Outlet";
        const bool targetNodeNamesAreAvailable = createdTargetBranch
                                                   ? generatedNodeNameIsAbsentAndUnowned(targetLoopImpl.model(), targetNodeName)
                                                       && generatedNodeNameIsAbsentAndUnowned(targetLoopImpl.model(), targetOutletNodeName)
                                                   : isCanonicalEmptyBranchAnchor(targetLoopImpl.model(), *targetBranch, targetNodeName)
                                                       && generatedNodeNameIsAbsentAndUnowned(targetLoopImpl.model(), targetOutletNodeName);
        if (!targetNodeNamesAreAvailable) {
          if (createdTargetBranch) {
            targetBranch->remove();
          }
          return nullptr;
        }

        const auto targetBranchInsertIndex = static_cast<unsigned>(targetTopology->branchList.branches().size() - 1u);
        const auto originalTargetBranchCount = static_cast<unsigned>(targetTopology->branchList.extensibleGroups().size());
        auto plan = std::unique_ptr<DemandBranchRelocationPlan>(new DemandBranchRelocationPlan(
          targetLoop, sourceLoop, component, inletPort, outletPort, *sourceBranch, sourceTopology->branchList, sourceTopology->splitter,
          sourceTopology->mixer, sourceTopology->equipmentBranches.size() == 1u, sourceTopology->setpointTarget, targetTopology->branchList,
          targetTopology->splitter, targetTopology->mixer, *targetBranch, createdTargetBranch, targetTopology->setpointTarget,
          originalTargetBranchCount, targetBranchInsertIndex));

        if (createdTargetBranch) {
          plan->m_targetBranchInsertionAttempted = true;
          if (!targetTopology->branchList.getImpl<BranchList_Impl>()->insertBranch(targetBranchInsertIndex, *targetBranch)) {
            return nullptr;
          }
          const auto targetEquipmentBranches = targetLoopImpl.demandEquipmentBranches();
          if (!targetLoopImpl.syncConnectorPorts(targetTopology->splitter, targetTopology->mixer, targetLoopImpl.demandInletBranch(),
                                                 targetLoopImpl.demandOutletBranch(), targetEquipmentBranches)) {
            return nullptr;
          }
        }

        if (createdTargetBranch) {
          plan->m_createdNodeNames.push_back(targetNodeName);
        }
        plan->m_createdNodeNames.push_back(targetOutletNodeName);

        auto targetBranchImpl = targetBranch->getImpl<Branch_Impl>();
        OS_ASSERT(targetBranchImpl);
        plan->m_targetRowAttempted = true;
        if (!targetBranchImpl->appendComponent(component.cast<ModelObject>(), targetNodeName, targetOutletNodeName)) {
          return nullptr;
        }
        plan->m_targetInletNode = targetBranch->componentInletNode(0u);
        plan->m_targetOutletNode = targetBranch->componentOutletNode(0u);
        if (!plan->m_targetInletNode || !plan->m_targetOutletNode) {
          return nullptr;
        }

        plan->m_prepared = true;
        return plan;
      }

     public:
      DemandBranchRelocationPlan(const DemandBranchRelocationPlan&) = delete;
      DemandBranchRelocationPlan& operator=(const DemandBranchRelocationPlan&) = delete;
      DemandBranchRelocationPlan(DemandBranchRelocationPlan&&) = delete;
      DemandBranchRelocationPlan& operator=(DemandBranchRelocationPlan&&) = delete;

      ~DemandBranchRelocationPlan() {
        if (m_committed) {
          return;
        }

        if (m_targetRowAttempted) {
          m_targetBranch.getImpl<Branch_Impl>()->clearComponents();
        }
        if (m_createdTargetBranch) {
          if (m_targetBranchInsertionAttempted && m_targetBranchList.extensibleGroups().size() > m_originalTargetBranchCount) {
            const auto removedFields = m_targetBranchList.eraseExtensibleGroup(m_targetBranchInsertIndex);
            OS_ASSERT(!removedFields.empty());
          }
          auto targetLoopImpl = m_targetLoop.getImpl<PlantLoop_Impl>();
          // Canonical connector shape was proven before preparation; only this
          // plan's same-model exact Branch was added, so rollback resync is no-fail.
          const bool synchronized =
            targetLoopImpl->syncConnectorPorts(m_targetSplitter, m_targetMixer, targetLoopImpl->demandInletBranch(),
                                               targetLoopImpl->demandOutletBranch(), targetLoopImpl->demandEquipmentBranches());
          OS_ASSERT(synchronized);
          m_targetBranch.remove();
          OS_ASSERT(!m_targetLoop.model().getObject(m_targetBranch.handle()));
        }
        for (auto nodeName = m_createdNodeNames.rbegin(); nodeName != m_createdNodeNames.rend(); ++nodeName) {
          if (auto node = m_targetLoop.model().getConcreteModelObjectByName<Node>(*nodeName)) {
            const auto nodeHandle = node->handle();
            node->remove();
            OS_ASSERT(!m_targetLoop.model().getObject(nodeHandle));
          }
        }
      }

      Node targetInletNode() const {
        OS_ASSERT(m_prepared && m_targetInletNode);
        return *m_targetInletNode;
      }

      Node targetOutletNode() const {
        OS_ASSERT(m_prepared && m_targetOutletNode);
        return *m_targetOutletNode;
      }

      void commit() {
        OS_ASSERT(m_prepared && !m_committed && m_targetInletNode && m_targetOutletNode);
        const auto currentSourceSetpoint = m_sourceLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto currentTargetSetpoint = m_targetLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        OS_ASSERT(currentSourceSetpoint && *currentSourceSetpoint == m_sourceSetpointTarget);
        OS_ASSERT(currentTargetSetpoint && *currentTargetSetpoint == m_targetSetpointTarget);

        if (!m_keepSourceAsDefaultBranch) {
          auto sourceBranchListImpl = m_sourceBranchList.getImpl<BranchList_Impl>();
          OS_ASSERT(sourceBranchListImpl);
          const bool removedSourceBranch = sourceBranchListImpl->removeBranch(m_sourceBranch);
          OS_ASSERT(removedSourceBranch);
        }
        auto sourceBranchImpl = m_sourceBranch.getImpl<Branch_Impl>();
        OS_ASSERT(sourceBranchImpl);
        sourceBranchImpl->clearComponents();
        if (!m_keepSourceAsDefaultBranch) {
          m_sourceBranch.remove();
          OS_ASSERT(!m_sourceLoop.model().getObject(m_sourceBranch.handle()));
        }

        auto sourceLoopImpl = m_sourceLoop.getImpl<PlantLoop_Impl>();
        const bool synchronized = sourceLoopImpl->syncConnectorPorts(m_sourceSplitter, m_sourceMixer, sourceLoopImpl->demandInletBranch(),
                                                                     sourceLoopImpl->demandOutletBranch(), sourceLoopImpl->demandEquipmentBranches());
        OS_ASSERT(synchronized);

        // Prepare proved the exact live same-model NodeType fields and target
        // Nodes, so these two pointer writes are no-fail after source teardown.
        const bool inletSet = m_component.setPointer(m_inletPort, m_targetInletNode->handle());
        const bool outletSet = m_component.setPointer(m_outletPort, m_targetOutletNode->handle());
        OS_ASSERT(inletSet && outletSet);
        m_committed = true;
      }

     private:
      struct DemandSideTopology
      {
        BranchList branchList;
        ConnectorSplitter splitter;
        ConnectorMixer mixer;
        std::vector<Branch> equipmentBranches;
        Node setpointTarget;
      };

      static boost::optional<DemandSideTopology> validatedDemandSideTopology(PlantLoop_Impl& plantLoopImpl) {
        const auto plantLoop = plantLoopImpl.getObject<PlantLoop>();
        const auto setpointTarget = plantLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        auto branchList = plantLoopImpl.demandBranchList();
        const auto equipmentBranches = plantLoopImpl.demandEquipmentBranches();
        if (!setpointTarget || equipmentBranches.empty()) {
          return boost::none;
        }

        const auto listedBranches = branchList.branches();
        const auto inletBranch = plantLoopImpl.demandInletBranch();
        const auto outletBranch = plantLoopImpl.demandOutletBranch();
        if (listedBranches.size() != equipmentBranches.size() + 2u || listedBranches.front() != inletBranch
            || listedBranches.back() != outletBranch) {
          return boost::none;
        }
        for (unsigned i = 0u; i < equipmentBranches.size(); ++i) {
          if (listedBranches[i + 1u] != equipmentBranches[i]) {
            return boost::none;
          }
        }

        auto splitter = plantLoopImpl.demandSplitter().cast<ConnectorSplitter>();
        auto mixer = plantLoopImpl.demandMixer().cast<ConnectorMixer>();
        const auto splitterInletBranch = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
        const auto mixerOutletBranch = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
        if (!splitterInletBranch || *splitterInletBranch != inletBranch || !mixerOutletBranch || *mixerOutletBranch != outletBranch
            || splitter.nextBranchIndex() != equipmentBranches.size() || mixer.nextBranchIndex() != equipmentBranches.size()) {
          return boost::none;
        }
        for (unsigned i = 0u; i < equipmentBranches.size(); ++i) {
          const auto splitterBranch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
          const auto mixerBranch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
          if (!splitterBranch || *splitterBranch != equipmentBranches[i] || !mixerBranch || *mixerBranch != equipmentBranches[i]) {
            return boost::none;
          }
        }

        return DemandSideTopology{branchList, splitter, mixer, equipmentBranches, *setpointTarget};
      }

      DemandBranchRelocationPlan(PlantLoop targetLoop, PlantLoop sourceLoop, HVACComponent component, unsigned inletPort, unsigned outletPort,
                                 Branch sourceBranch, BranchList sourceBranchList, ConnectorSplitter sourceSplitter, ConnectorMixer sourceMixer,
                                 bool keepSourceAsDefaultBranch, Node sourceSetpointTarget, BranchList targetBranchList,
                                 ConnectorSplitter targetSplitter, ConnectorMixer targetMixer, Branch targetBranch, bool createdTargetBranch,
                                 Node targetSetpointTarget, unsigned originalTargetBranchCount, unsigned targetBranchInsertIndex)
        : m_targetLoop(std::move(targetLoop)),
          m_sourceLoop(std::move(sourceLoop)),
          m_component(std::move(component)),
          m_inletPort(inletPort),
          m_outletPort(outletPort),
          m_sourceBranch(std::move(sourceBranch)),
          m_sourceBranchList(std::move(sourceBranchList)),
          m_sourceSplitter(std::move(sourceSplitter)),
          m_sourceMixer(std::move(sourceMixer)),
          m_keepSourceAsDefaultBranch(keepSourceAsDefaultBranch),
          m_sourceSetpointTarget(std::move(sourceSetpointTarget)),
          m_targetBranchList(std::move(targetBranchList)),
          m_targetSplitter(std::move(targetSplitter)),
          m_targetMixer(std::move(targetMixer)),
          m_targetBranch(std::move(targetBranch)),
          m_createdTargetBranch(createdTargetBranch),
          m_targetSetpointTarget(std::move(targetSetpointTarget)),
          m_originalTargetBranchCount(originalTargetBranchCount),
          m_targetBranchInsertIndex(targetBranchInsertIndex) {}

      PlantLoop m_targetLoop;
      PlantLoop m_sourceLoop;
      HVACComponent m_component;
      unsigned m_inletPort;
      unsigned m_outletPort;
      Branch m_sourceBranch;
      BranchList m_sourceBranchList;
      ConnectorSplitter m_sourceSplitter;
      ConnectorMixer m_sourceMixer;
      bool m_keepSourceAsDefaultBranch;
      Node m_sourceSetpointTarget;
      BranchList m_targetBranchList;
      ConnectorSplitter m_targetSplitter;
      ConnectorMixer m_targetMixer;
      Branch m_targetBranch;
      bool m_createdTargetBranch;
      Node m_targetSetpointTarget;
      boost::optional<Node> m_targetInletNode;
      boost::optional<Node> m_targetOutletNode;
      std::vector<std::string> m_createdNodeNames;
      unsigned m_originalTargetBranchCount;
      unsigned m_targetBranchInsertIndex;
      bool m_targetBranchInsertionAttempted = false;
      bool m_targetRowAttempted = false;
      bool m_prepared = false;
      bool m_committed = false;
    };

    // Storage-only observation shared by exact component-specific relocation
    // plans. It proves persisted plant ownership without assigning physical
    // load/source semantics or mutating any object.
    class PlantLoop_Impl::ExactPlantBranchTopologyInspection
    {
     public:
      struct BranchOccurrence
      {
        Branch branch;
        unsigned row;
        Node inlet;
        Node outlet;
      };

      struct ObservedPlantSideTopology
      {
        BranchList branchList;
        ConnectorSplitter splitter;
        ConnectorMixer mixer;
        std::vector<Branch> equipmentBranches;
        Branch outletBranch;
        Node setpointTarget;
      };

      static bool rawFieldAgrees(const ModelObject& owner, unsigned field, const ModelObject& expected) {
        auto workspaceImpl = owner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto raw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (!raw || raw->empty()) {
          return true;
        }
        const auto expectedName = expected.name();
        return (expectedName && openstudio::istringEqual(*raw, *expectedName)) || openstudio::toUUID(*raw) == expected.handle();
      }

      static bool hasUniqueName(const ModelObject& object) {
        const auto name = object.name();
        return name && !name->empty() && std::ranges::count_if(object.model().objects(), [&object, &name](const auto& candidate) {
                                           const auto candidateName = candidate.name();
                                           return candidate.handle() != object.handle() && candidate.iddObject().type() == object.iddObject().type()
                                                  && candidateName && openstudio::istringEqual(*candidateName, *name);
                                         }) == 0;
      }

      static bool fieldHasEvidence(const ModelObject& owner, unsigned field) {
        const auto relationship = existingObjectField(owner, field);
        auto workspaceImpl = owner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto raw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
        return relationship.set || relationship.object || (raw && !raw->empty());
      }

      static boost::optional<ModelObject> exactObjectField(const ModelObject& owner, unsigned field) {
        const auto relationship = existingObjectField(owner, field);
        if (!relationship.set || !relationship.object || !rawFieldAgrees(owner, field, *relationship.object)) {
          return boost::none;
        }
        return relationship.object;
      }

      static boost::optional<Node> exactNodeField(const ModelObject& owner, unsigned field) {
        const auto object = exactObjectField(owner, field);
        return object ? object->optionalCast<Node>() : boost::none;
      }

      static bool referencesObject(const ModelObject& owner, unsigned field, const ModelObject& expected) {
        const auto relationship = existingObjectField(owner, field);
        if (relationship.object && relationship.object->handle() == expected.handle()) {
          return true;
        }
        auto workspaceImpl = owner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto raw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
        const auto expectedName = expected.name();
        return raw && !raw->empty()
               && ((expectedName && openstudio::istringEqual(*raw, *expectedName)) || openstudio::toUUID(*raw) == expected.handle());
      }

      static bool collectOccurrences(const HVACComponent& component, std::vector<BranchOccurrence>& result) {
        result.clear();
        for (const auto& branch : component.model().getConcreteModelObjects<Branch>()) {
          const auto groups = branch.extensibleGroups();
          for (unsigned row = 0u; row < groups.size(); ++row) {
            const auto componentNameField =
              branch.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchExtensibleFields::ComponentName));
            const auto relationship = existingObjectField(branch, componentNameField);
            auto branchWorkspaceImpl = branch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(branchWorkspaceImpl);
            const auto rawName = branchWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(componentNameField, false, true);
            const bool referencesComponent =
              (relationship.object && relationship.object->handle() == component.handle())
              || (rawName && !rawName->empty()
                  && (openstudio::istringEqual(*rawName, component.nameString()) || openstudio::toUUID(*rawName) == component.handle()));
            if (!referencesComponent) {
              continue;
            }
            const auto componentType = groups[row].getString(openstudio::BranchExtensibleFields::ComponentObjectType, false);
            const auto exactComponent = exactObjectField(branch, componentNameField);
            const auto inletField =
              branch.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchExtensibleFields::ComponentInletNodeName));
            const auto outletField =
              branch.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchExtensibleFields::ComponentOutletNodeName));
            const auto inlet = exactNodeField(branch, inletField);
            const auto outlet = exactNodeField(branch, outletField);
            if (!componentType || !openstudio::istringEqual(*componentType, component.iddObject().name()) || !exactComponent
                || exactComponent->handle() != component.handle() || !inlet || !outlet) {
              return false;
            }
            result.push_back({branch, row, *inlet, *outlet});
          }
        }
        return true;
      }

      static boost::optional<BranchList> uniqueBranchListForBranch(const Model& model, const Branch& branch) {
        boost::optional<BranchList> result;
        unsigned occurrences = 0u;
        for (const auto& branchList : model.getConcreteModelObjects<BranchList>()) {
          for (unsigned row = 0u; row < branchList.extensibleGroups().size(); ++row) {
            const auto branchField =
              branchList.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchListExtensibleFields::BranchName));
            if (!referencesObject(branchList, branchField, branch)) {
              continue;
            }
            const auto exactBranch = exactObjectField(branchList, branchField);
            if (!exactBranch || exactBranch->handle() != branch.handle()) {
              return boost::none;
            }
            ++occurrences;
            result = branchList;
          }
        }
        return occurrences == 1u ? result : boost::none;
      }

      static boost::optional<PlantLoop> uniquePlantLoopForBranchList(const Model& model, const BranchList& branchList, bool supplySide) {
        boost::optional<PlantLoop> result;
        unsigned occurrences = 0u;
        const unsigned expectedField =
          supplySide ? openstudio::PlantLoopFields::PlantSideBranchListName : openstudio::PlantLoopFields::DemandSideBranchListName;
        for (const auto& plantLoop : model.getConcreteModelObjects<PlantLoop>()) {
          for (const unsigned field : {openstudio::PlantLoopFields::PlantSideBranchListName, openstudio::PlantLoopFields::DemandSideBranchListName}) {
            if (!referencesObject(plantLoop, field, branchList)) {
              continue;
            }
            const auto exactBranchList = exactObjectField(plantLoop, field);
            if (field != expectedField || !exactBranchList || exactBranchList->handle() != branchList.handle()) {
              return boost::none;
            }
            ++occurrences;
            result = plantLoop;
          }
        }
        return occurrences == 1u ? result : boost::none;
      }

      static boost::optional<PlantLoop> uniquePlantLoopForConnectorList(const Model& model, const ModelObject& connectorList, bool supplySide) {
        boost::optional<PlantLoop> result;
        unsigned occurrences = 0u;
        const unsigned expectedField =
          supplySide ? openstudio::PlantLoopFields::PlantSideConnectorListName : openstudio::PlantLoopFields::DemandSideConnectorListName;
        for (const auto& plantLoop : model.getConcreteModelObjects<PlantLoop>()) {
          for (const unsigned field :
               {openstudio::PlantLoopFields::PlantSideConnectorListName, openstudio::PlantLoopFields::DemandSideConnectorListName}) {
            if (!referencesObject(plantLoop, field, connectorList)) {
              continue;
            }
            const auto exactConnectorList = exactObjectField(plantLoop, field);
            if (field != expectedField || !exactConnectorList || exactConnectorList->handle() != connectorList.handle()) {
              return boost::none;
            }
            ++occurrences;
            result = plantLoop;
          }
        }
        return occurrences == 1u ? result : boost::none;
      }

      static boost::optional<ObservedPlantSideTopology> observedPlantSideTopology(const PlantLoop& plantLoop, bool supplySide) {
        const unsigned branchListField =
          supplySide ? openstudio::PlantLoopFields::PlantSideBranchListName : openstudio::PlantLoopFields::DemandSideBranchListName;
        const unsigned connectorListField =
          supplySide ? openstudio::PlantLoopFields::PlantSideConnectorListName : openstudio::PlantLoopFields::DemandSideConnectorListName;
        const auto branchListObject = exactObjectField(plantLoop, branchListField);
        const auto connectorList = exactObjectField(plantLoop, connectorListField);
        const auto setpointTarget = exactNodeField(plantLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto branchList = branchListObject ? branchListObject->optionalCast<BranchList>() : boost::none;
        if (!branchList || !connectorList || connectorList->iddObject().type() != openstudio::IddObjectType::ConnectorList || !setpointTarget
            || !hasUniqueName(*branchList) || !hasUniqueName(*connectorList)) {
          return boost::none;
        }
        const auto branchListOwner = uniquePlantLoopForBranchList(plantLoop.model(), *branchList, supplySide);
        const auto connectorListOwner = uniquePlantLoopForConnectorList(plantLoop.model(), *connectorList, supplySide);
        if (!branchListOwner || *branchListOwner != plantLoop || !connectorListOwner || *connectorListOwner != plantLoop
            || !hasUniqueName(*setpointTarget)) {
          return boost::none;
        }

        std::vector<Branch> branches;
        std::set<Handle> branchHandles;
        for (unsigned row = 0u; row < branchList->extensibleGroups().size(); ++row) {
          const auto branchField =
            branchList->iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchListExtensibleFields::BranchName));
          const auto branchObject = exactObjectField(*branchList, branchField);
          const auto branch = branchObject ? branchObject->optionalCast<Branch>() : boost::none;
          const auto owningBranchList = branch ? uniqueBranchListForBranch(plantLoop.model(), *branch) : boost::none;
          if (!branch || !hasUniqueName(*branch) || !owningBranchList || *owningBranchList != *branchList
              || !branchHandles.insert(branch->handle()).second) {
            return boost::none;
          }
          branches.push_back(*branch);
        }
        if (branches.size() < 3u) {
          return boost::none;
        }
        const std::vector<Branch> equipmentBranches(std::next(branches.begin()), std::prev(branches.end()));

        boost::optional<ConnectorSplitter> splitter;
        boost::optional<ConnectorMixer> mixer;
        const auto connectorGroups = connectorList->extensibleGroups();
        if (connectorGroups.size() != 2u) {
          return boost::none;
        }
        for (unsigned row = 0u; row < connectorGroups.size(); ++row) {
          const auto connectorNameField =
            connectorList->iddObject().index(openstudio::ExtensibleIndex(row, openstudio::ConnectorListExtensibleFields::ConnectorName));
          const auto connectorObject = exactObjectField(*connectorList, connectorNameField);
          const auto connectorType = connectorGroups[row].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType, false);
          if (!connectorObject || !connectorType) {
            return boost::none;
          }
          if (auto candidate = connectorObject->optionalCast<ConnectorSplitter>()) {
            if (splitter || !openstudio::istringEqual(*connectorType, candidate->iddObject().name())) {
              return boost::none;
            }
            splitter = *candidate;
          } else if (auto candidate = connectorObject->optionalCast<ConnectorMixer>()) {
            if (mixer || !openstudio::istringEqual(*connectorType, candidate->iddObject().name())) {
              return boost::none;
            }
            mixer = *candidate;
          } else {
            return boost::none;
          }
        }
        if (!splitter || !mixer || !hasUniqueName(*splitter) || !hasUniqueName(*mixer)
            || splitter->extensibleGroups().size() != equipmentBranches.size() || mixer->extensibleGroups().size() != equipmentBranches.size()) {
          return boost::none;
        }
        const auto splitterInlet = exactObjectField(*splitter, splitter->inletPort());
        const auto mixerOutlet = exactObjectField(*mixer, mixer->outletPort());
        if (!splitterInlet || splitterInlet->handle() != branches.front().handle() || !mixerOutlet
            || mixerOutlet->handle() != branches.back().handle()) {
          return boost::none;
        }
        for (unsigned row = 0u; row < equipmentBranches.size(); ++row) {
          const auto splitterOutlet = exactObjectField(*splitter, splitter->outletPort(row));
          const auto mixerInlet = exactObjectField(*mixer, mixer->inletPort(row));
          if (!splitterOutlet || splitterOutlet->handle() != equipmentBranches[row].handle() || !mixerInlet
              || mixerInlet->handle() != equipmentBranches[row].handle()) {
            return boost::none;
          }
        }
        return ObservedPlantSideTopology{*branchList, *splitter, *mixer, equipmentBranches, branches.back(), *setpointTarget};
      }
    };

    // Exact Chiller:Electric:EIR heat-recovery moves retain their proven
    // chilled-water and WaterCooled condenser owners. This plan observes all
    // three plant representations before the generic tertiary path can remove
    // the current heat-recovery row.
    class PlantLoop_Impl::ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan : private PlantLoop_Impl::ExactPlantBranchTopologyInspection
    {
     public:
      static bool requiresExactAttachmentDispatch(const ChillerElectricEIR& chiller) {
        if (chiller.iddObject().type() != ChillerElectricEIR::iddObjectType() || !hasUniqueName(chiller)) {
          return true;
        }

        const bool heatRecoveryInletEvidence = fieldHasEvidence(chiller, openstudio::Chiller_Electric_EIRFields::HeatRecoveryInletNodeName);
        const bool heatRecoveryOutletEvidence = fieldHasEvidence(chiller, openstudio::Chiller_Electric_EIRFields::HeatRecoveryOutletNodeName);
        if (heatRecoveryInletEvidence || heatRecoveryOutletEvidence) {
          return true;
        }

        // Preserve the existing initial tertiary attachment only when every
        // existing non-HR row is an exact canonical chilled/condenser row.
        return !hasCanonicalNoHeatRecoveryAttachment(chiller);
      }

      static std::unique_ptr<ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                               ChillerElectricEIR chiller) {
        if (chiller.iddObject().type() != ChillerElectricEIR::iddObjectType() || chiller.model() != targetLoopImpl.model() || !hasUniqueName(chiller)
            || !persistedCondenserIsWaterCooled(chiller)) {
          return nullptr;
        }

        const auto chilledInlet = exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::ChilledWaterInletNodeName);
        const auto chilledOutlet = exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::ChilledWaterOutletNodeName);
        const auto condenserInlet = exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::CondenserInletNodeName);
        const auto condenserOutlet = exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::CondenserOutletNodeName);
        const auto heatRecoveryInlet = exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::HeatRecoveryInletNodeName);
        const auto heatRecoveryOutlet = exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::HeatRecoveryOutletNodeName);
        if (!chilledInlet || !chilledOutlet || !condenserInlet || !condenserOutlet || !heatRecoveryInlet || !heatRecoveryOutlet) {
          return nullptr;
        }

        const std::array<Node, 6> ports{*chilledInlet, *chilledOutlet, *condenserInlet, *condenserOutlet, *heatRecoveryInlet, *heatRecoveryOutlet};
        std::set<Handle> portHandles;
        for (const auto& port : ports) {
          if (!hasUniqueName(port) || !portHandles.insert(port.handle()).second) {
            return nullptr;
          }
        }

        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(chiller, occurrences) || occurrences.size() != 3u) {
          return nullptr;
        }
        boost::optional<BranchOccurrence> primaryOccurrence;
        boost::optional<BranchOccurrence> condenserOccurrence;
        boost::optional<BranchOccurrence> sourceOccurrence;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return nullptr;
          }
          if (occurrence.inlet == *chilledInlet && occurrence.outlet == *chilledOutlet) {
            if (primaryOccurrence) {
              return nullptr;
            }
            primaryOccurrence = occurrence;
          } else if (occurrence.inlet == *condenserInlet && occurrence.outlet == *condenserOutlet) {
            if (condenserOccurrence) {
              return nullptr;
            }
            condenserOccurrence = occurrence;
          } else if (occurrence.inlet == *heatRecoveryInlet && occurrence.outlet == *heatRecoveryOutlet) {
            if (sourceOccurrence) {
              return nullptr;
            }
            sourceOccurrence = occurrence;
          } else {
            return nullptr;
          }
        }
        if (!primaryOccurrence || !condenserOccurrence || !sourceOccurrence) {
          return nullptr;
        }

        const auto primaryBranchList = uniqueBranchListForBranch(chiller.model(), primaryOccurrence->branch);
        const auto condenserBranchList = uniqueBranchListForBranch(chiller.model(), condenserOccurrence->branch);
        const auto sourceBranchList = uniqueBranchListForBranch(chiller.model(), sourceOccurrence->branch);
        if (!primaryBranchList || !condenserBranchList || !sourceBranchList || *primaryBranchList == *condenserBranchList
            || *primaryBranchList == *sourceBranchList || *condenserBranchList == *sourceBranchList) {
          return nullptr;
        }

        const auto primaryOwner = uniquePlantLoopForBranchList(chiller.model(), *primaryBranchList, true);
        const auto condenserOwner = uniquePlantLoopForBranchList(chiller.model(), *condenserBranchList, false);
        const auto sourceOwner = uniquePlantLoopForBranchList(chiller.model(), *sourceBranchList, false);
        if (!primaryOwner || !condenserOwner || !sourceOwner || *primaryOwner == *condenserOwner || *primaryOwner == *sourceOwner
            || *condenserOwner == *sourceOwner) {
          return nullptr;
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if (targetLoop == *primaryOwner || targetLoop == *condenserOwner || targetLoop == *sourceOwner) {
          return nullptr;
        }
        const auto primaryTopology = observedPlantSideTopology(*primaryOwner, true);
        const auto condenserTopology = observedPlantSideTopology(*condenserOwner, false);
        const auto sourceTopology = observedPlantSideTopology(*sourceOwner, false);
        const auto targetTopology = observedPlantSideTopology(targetLoop, false);
        if (!primaryTopology || !condenserTopology || !sourceTopology || !targetTopology || primaryTopology->branchList != *primaryBranchList
            || condenserTopology->branchList != *condenserBranchList || sourceTopology->branchList != *sourceBranchList
            || std::ranges::count(primaryTopology->equipmentBranches, primaryOccurrence->branch) != 1
            || std::ranges::count(condenserTopology->equipmentBranches, condenserOccurrence->branch) != 1
            || std::ranges::count(sourceTopology->equipmentBranches, sourceOccurrence->branch) != 1) {
          return nullptr;
        }

        auto plantRelocation = DemandBranchRelocationPlan::prepareChillerElectricEIRHeatRecovery(
          targetLoopImpl, chiller, *sourceOwner, {primaryOccurrence->branch.handle(), primaryOccurrence->row},
          {condenserOccurrence->branch.handle(), condenserOccurrence->row});
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan>(new ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan(
          std::move(plantRelocation), *primaryOwner, *condenserOwner, primaryTopology->setpointTarget, condenserTopology->setpointTarget));
      }

      ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan(const ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan&) = delete;
      ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan& operator=(const ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan&) = delete;
      ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan(ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan&&) = delete;
      ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan& operator=(ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan&&) = delete;
      ~ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(m_plantRelocation && !m_committed);
        const auto primarySetpoint = m_primaryOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto condenserSetpoint = m_condenserOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        OS_ASSERT(primarySetpoint && *primarySetpoint == m_primarySetpointTarget);
        OS_ASSERT(condenserSetpoint && *condenserSetpoint == m_condenserSetpointTarget);
        m_plantRelocation->commit();
        m_committed = true;
      }

     private:
      static bool persistedCondenserIsWaterCooled(const ChillerElectricEIR& chiller) {
        auto workspaceImpl = chiller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto raw =
          workspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Chiller_Electric_EIRFields::CondenserType, false, true);
        return raw && openstudio::istringEqual(*raw, "WaterCooled");
      }

      static bool hasCanonicalNoHeatRecoveryAttachment(const ChillerElectricEIR& chiller) {
        const bool chilledInletEvidence = fieldHasEvidence(chiller, openstudio::Chiller_Electric_EIRFields::ChilledWaterInletNodeName);
        const bool chilledOutletEvidence = fieldHasEvidence(chiller, openstudio::Chiller_Electric_EIRFields::ChilledWaterOutletNodeName);
        const bool condenserInletEvidence = fieldHasEvidence(chiller, openstudio::Chiller_Electric_EIRFields::CondenserInletNodeName);
        const bool condenserOutletEvidence = fieldHasEvidence(chiller, openstudio::Chiller_Electric_EIRFields::CondenserOutletNodeName);
        if (chilledInletEvidence != chilledOutletEvidence || condenserInletEvidence != condenserOutletEvidence) {
          return false;
        }

        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(chiller, occurrences)) {
          return false;
        }
        if (!chilledInletEvidence && !condenserInletEvidence) {
          return occurrences.empty();
        }

        const auto chilledInlet =
          chilledInletEvidence ? exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::ChilledWaterInletNodeName) : boost::none;
        const auto chilledOutlet =
          chilledOutletEvidence ? exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::ChilledWaterOutletNodeName) : boost::none;
        const auto condenserInlet =
          condenserInletEvidence ? exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::CondenserInletNodeName) : boost::none;
        const auto condenserOutlet =
          condenserOutletEvidence ? exactNodeField(chiller, openstudio::Chiller_Electric_EIRFields::CondenserOutletNodeName) : boost::none;
        if ((chilledInletEvidence && (!chilledInlet || !chilledOutlet)) || (condenserInletEvidence && (!condenserInlet || !condenserOutlet))
            || (condenserInletEvidence && !persistedCondenserIsWaterCooled(chiller))) {
          return false;
        }

        std::set<Handle> portHandles;
        for (const auto& port : {chilledInlet, chilledOutlet, condenserInlet, condenserOutlet}) {
          if (port && (!hasUniqueName(*port) || !portHandles.insert(port->handle()).second)) {
            return false;
          }
        }
        const unsigned expectedOccurrences = static_cast<unsigned>(chilledInletEvidence) + static_cast<unsigned>(condenserInletEvidence);
        if (occurrences.size() != expectedOccurrences) {
          return false;
        }

        boost::optional<PlantLoop> primaryOwner;
        boost::optional<PlantLoop> condenserOwner;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return false;
          }
          const bool isPrimary = chilledInlet && chilledOutlet && occurrence.inlet == *chilledInlet && occurrence.outlet == *chilledOutlet;
          const bool isCondenser = condenserInlet && condenserOutlet && occurrence.inlet == *condenserInlet && occurrence.outlet == *condenserOutlet;
          if (isPrimary == isCondenser) {
            return false;
          }
          const auto branchList = uniqueBranchListForBranch(chiller.model(), occurrence.branch);
          const auto owner = branchList ? uniquePlantLoopForBranchList(chiller.model(), *branchList, isPrimary) : boost::none;
          const auto topology = owner ? observedPlantSideTopology(*owner, isPrimary) : boost::none;
          if (!branchList || !owner || !topology || topology->branchList != *branchList
              || std::ranges::count(topology->equipmentBranches, occurrence.branch) != 1) {
            return false;
          }
          if (isPrimary) {
            if (primaryOwner) {
              return false;
            }
            primaryOwner = *owner;
          } else {
            if (condenserOwner) {
              return false;
            }
            condenserOwner = *owner;
          }
        }
        return !primaryOwner || !condenserOwner || *primaryOwner != *condenserOwner;
      }

      ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan(std::unique_ptr<DemandBranchRelocationPlan> plantRelocation, PlantLoop primaryOwner,
                                                               PlantLoop condenserOwner, Node primarySetpointTarget, Node condenserSetpointTarget)
        : m_plantRelocation(std::move(plantRelocation)),
          m_primaryOwner(std::move(primaryOwner)),
          m_condenserOwner(std::move(condenserOwner)),
          m_primarySetpointTarget(std::move(primarySetpointTarget)),
          m_condenserSetpointTarget(std::move(condenserSetpointTarget)) {}

      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      PlantLoop m_primaryOwner;
      PlantLoop m_condenserOwner;
      Node m_primarySetpointTarget;
      Node m_condenserSetpointTarget;
      bool m_committed = false;
    };

    // Role-neutral observational proof shared by the exact PlantLoop EIR
    // SourceSide relocation/removal and HeatRecovery relocation plans.
    class PlantLoop_Impl::PlantLoopEIRHeatPumpTopologyInspection : private PlantLoop_Impl::ExactPlantBranchTopologyInspection
    {
     public:
      struct Descriptor
      {
        IddObjectType componentType;
        unsigned loadInletPort;
        unsigned loadOutletPort;
        unsigned sourceInletPort;
        unsigned sourceOutletPort;
        unsigned heatRecoveryInletPort;
        unsigned heatRecoveryOutletPort;
        unsigned condenserTypeField;
        unsigned outboundCompanionField;
        IddObjectType companionType;
        unsigned inboundCompanionField;
      };

      struct ProvenOccurrenceOwner
      {
        BranchList branchList;
        PlantLoop plantLoop;
        ObservedPlantSideTopology topology;
      };

      struct ProvenFullyOwnedTopology
      {
        ProvenOccurrenceOwner primary;
        ProvenOccurrenceOwner source;
        ProvenOccurrenceOwner heatRecovery;
        BranchOccurrence primaryOccurrence;
        BranchOccurrence sourceOccurrence;
        BranchOccurrence heatRecoveryOccurrence;
      };

      static Descriptor heatingDescriptor() {
        return {HeatPumpPlantLoopEIRHeating::iddObjectType(),
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideInletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideOutletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideInletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideOutletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryInletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryOutletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType,
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName,
                HeatPumpPlantLoopEIRCooling::iddObjectType(),
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CompanionHeatPumpName};
      }

      static Descriptor coolingDescriptor() {
        return {HeatPumpPlantLoopEIRCooling::iddObjectType(),
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideInletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideOutletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType,
                openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CompanionHeatPumpName,
                HeatPumpPlantLoopEIRHeating::iddObjectType(),
                openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName};
      }

      static bool persistedCondenserTypeIs(const HVACComponent& heatPump, const Descriptor& descriptor, const std::string& expected) {
        auto workspaceImpl = heatPump.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto raw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(descriptor.condenserTypeField, false, true);
        return raw && openstudio::istringEqual(*raw, expected);
      }

      static bool companionEvidenceIsExact(const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (fieldHasEvidence(heatPump, descriptor.outboundCompanionField)) {
          const auto companion = exactObjectField(heatPump, descriptor.outboundCompanionField);
          if (!companion || companion->iddObject().type() != descriptor.companionType || !hasUniqueName(*companion)) {
            return false;
          }
        }

        if (descriptor.companionType == HeatPumpPlantLoopEIRCooling::iddObjectType()) {
          for (const auto& candidate : heatPump.model().getConcreteModelObjects<HeatPumpPlantLoopEIRCooling>()) {
            if (!inboundCompanionEvidenceIsExact(heatPump, candidate, descriptor.inboundCompanionField)) {
              return false;
            }
          }
        } else {
          for (const auto& candidate : heatPump.model().getConcreteModelObjects<HeatPumpPlantLoopEIRHeating>()) {
            if (!inboundCompanionEvidenceIsExact(heatPump, candidate, descriptor.inboundCompanionField)) {
              return false;
            }
          }
        }
        return true;
      }

      static boost::optional<ProvenOccurrenceOwner> provenOwnerForOccurrence(const BranchOccurrence& occurrence, bool supplySide,
                                                                             bool allowSupplyOutlet) {
        const auto branchList = uniqueBranchListForBranch(occurrence.branch.model(), occurrence.branch);
        const auto owner = branchList ? uniquePlantLoopForBranchList(occurrence.branch.model(), *branchList, supplySide) : boost::none;
        const auto topology = owner ? observedPlantSideTopology(*owner, supplySide) : boost::none;
        if (!branchList || !owner || !topology || topology->branchList != *branchList) {
          return boost::none;
        }
        const bool isEquipmentBranch = std::ranges::count(topology->equipmentBranches, occurrence.branch) == 1;
        const bool isAllowedSupplyOutlet = supplySide && allowSupplyOutlet && topology->outletBranch == occurrence.branch;
        if (!isEquipmentBranch && !isAllowedSupplyOutlet) {
          return boost::none;
        }
        return ProvenOccurrenceOwner{*branchList, *owner, *topology};
      }

      static bool isCanonicalFallthroughAttachment(const HVACComponent& heatPump, const Descriptor& descriptor) {
        const bool loadInletEvidence = fieldHasEvidence(heatPump, descriptor.loadInletPort);
        const bool loadOutletEvidence = fieldHasEvidence(heatPump, descriptor.loadOutletPort);
        const bool sourceInletEvidence = fieldHasEvidence(heatPump, descriptor.sourceInletPort);
        const bool sourceOutletEvidence = fieldHasEvidence(heatPump, descriptor.sourceOutletPort);
        const bool heatRecoveryInletEvidence = fieldHasEvidence(heatPump, descriptor.heatRecoveryInletPort);
        const bool heatRecoveryOutletEvidence = fieldHasEvidence(heatPump, descriptor.heatRecoveryOutletPort);
        if (loadInletEvidence != loadOutletEvidence || sourceInletEvidence != sourceOutletEvidence
            || heatRecoveryInletEvidence != heatRecoveryOutletEvidence) {
          return false;
        }

        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatPump, occurrences)) {
          return false;
        }
        if (!loadInletEvidence && !sourceInletEvidence && !heatRecoveryInletEvidence) {
          return occurrences.empty() && persistedCondenserTypeIs(heatPump, descriptor, "AirSource");
        }

        const bool primaryOnly = loadInletEvidence && !sourceInletEvidence && !heatRecoveryInletEvidence;
        const bool primaryAndSource = loadInletEvidence && sourceInletEvidence && !heatRecoveryInletEvidence;
        const bool primaryAndHeatRecovery = loadInletEvidence && !sourceInletEvidence && heatRecoveryInletEvidence;
        if (!primaryOnly && !primaryAndSource && !primaryAndHeatRecovery) {
          return false;
        }
        if (!persistedCondenserTypeIs(heatPump, descriptor, sourceInletEvidence ? "WaterSource" : "AirSource")) {
          return false;
        }

        const auto loadInlet = exactNodeField(heatPump, descriptor.loadInletPort);
        const auto loadOutlet = exactNodeField(heatPump, descriptor.loadOutletPort);
        const auto sourceInlet = sourceInletEvidence ? exactNodeField(heatPump, descriptor.sourceInletPort) : boost::none;
        const auto sourceOutlet = sourceOutletEvidence ? exactNodeField(heatPump, descriptor.sourceOutletPort) : boost::none;
        const auto heatRecoveryInlet = heatRecoveryInletEvidence ? exactNodeField(heatPump, descriptor.heatRecoveryInletPort) : boost::none;
        const auto heatRecoveryOutlet = heatRecoveryOutletEvidence ? exactNodeField(heatPump, descriptor.heatRecoveryOutletPort) : boost::none;
        if (!loadInlet || !loadOutlet || (sourceInletEvidence && (!sourceInlet || !sourceOutlet))
            || (heatRecoveryInletEvidence && (!heatRecoveryInlet || !heatRecoveryOutlet))) {
          return false;
        }

        std::set<Handle> portHandles;
        for (const auto& port : {loadInlet, loadOutlet, sourceInlet, sourceOutlet, heatRecoveryInlet, heatRecoveryOutlet}) {
          if (port && (!hasUniqueName(*port) || !portHandles.insert(port->handle()).second)) {
            return false;
          }
        }
        const unsigned expectedOccurrences = 1u + static_cast<unsigned>(sourceInletEvidence) + static_cast<unsigned>(heatRecoveryInletEvidence);
        if (occurrences.size() != expectedOccurrences) {
          return false;
        }

        std::vector<PlantLoop> owners;
        std::vector<BranchList> branchLists;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return false;
          }
          const bool isLoad = occurrence.inlet == *loadInlet && occurrence.outlet == *loadOutlet;
          const bool isSource = sourceInlet && sourceOutlet && occurrence.inlet == *sourceInlet && occurrence.outlet == *sourceOutlet;
          const bool isHeatRecovery =
            heatRecoveryInlet && heatRecoveryOutlet && occurrence.inlet == *heatRecoveryInlet && occurrence.outlet == *heatRecoveryOutlet;
          if (static_cast<unsigned>(isLoad) + static_cast<unsigned>(isSource) + static_cast<unsigned>(isHeatRecovery) != 1u) {
            return false;
          }
          const auto provenOwner = provenOwnerForOccurrence(occurrence, isLoad, isLoad);
          if (!provenOwner || std::ranges::any_of(owners, [&provenOwner](const auto& owner) { return owner == provenOwner->plantLoop; })
              || std::ranges::any_of(branchLists, [&provenOwner](const auto& branchList) { return branchList == provenOwner->branchList; })) {
            return false;
          }
          owners.push_back(provenOwner->plantLoop);
          branchLists.push_back(provenOwner->branchList);
        }
        return true;
      }

      static bool requiresExactAttachmentDispatch(const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (heatPump.iddObject().type() != descriptor.componentType || !hasUniqueName(heatPump) || !companionEvidenceIsExact(heatPump, descriptor)) {
          return true;
        }
        return !isCanonicalFallthroughAttachment(heatPump, descriptor);
      }

      static boost::optional<ProvenFullyOwnedTopology> inspectFullyOwned(const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (heatPump.iddObject().type() != descriptor.componentType || !hasUniqueName(heatPump) || !companionEvidenceIsExact(heatPump, descriptor)
            || !persistedCondenserTypeIs(heatPump, descriptor, "WaterSource") || !hasAllOwnershipFieldEvidence(heatPump, descriptor)) {
          return boost::none;
        }

        const auto loadInlet = exactNodeField(heatPump, descriptor.loadInletPort);
        const auto loadOutlet = exactNodeField(heatPump, descriptor.loadOutletPort);
        const auto sourceInlet = exactNodeField(heatPump, descriptor.sourceInletPort);
        const auto sourceOutlet = exactNodeField(heatPump, descriptor.sourceOutletPort);
        const auto heatRecoveryInlet = exactNodeField(heatPump, descriptor.heatRecoveryInletPort);
        const auto heatRecoveryOutlet = exactNodeField(heatPump, descriptor.heatRecoveryOutletPort);
        if (!loadInlet || !loadOutlet || !sourceInlet || !sourceOutlet || !heatRecoveryInlet || !heatRecoveryOutlet) {
          return boost::none;
        }

        const std::array<Node, 6> ports{*loadInlet, *loadOutlet, *sourceInlet, *sourceOutlet, *heatRecoveryInlet, *heatRecoveryOutlet};
        std::set<Handle> portHandles;
        for (const auto& port : ports) {
          if (!hasUniqueName(port) || !portHandles.insert(port.handle()).second) {
            return boost::none;
          }
        }

        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatPump, occurrences) || occurrences.size() != 3u) {
          return boost::none;
        }
        boost::optional<BranchOccurrence> primaryOccurrence;
        boost::optional<BranchOccurrence> sourceOccurrence;
        boost::optional<BranchOccurrence> heatRecoveryOccurrence;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return boost::none;
          }
          if (occurrence.inlet == *loadInlet && occurrence.outlet == *loadOutlet) {
            if (primaryOccurrence) {
              return boost::none;
            }
            primaryOccurrence = occurrence;
          } else if (occurrence.inlet == *sourceInlet && occurrence.outlet == *sourceOutlet) {
            if (sourceOccurrence) {
              return boost::none;
            }
            sourceOccurrence = occurrence;
          } else if (occurrence.inlet == *heatRecoveryInlet && occurrence.outlet == *heatRecoveryOutlet) {
            if (heatRecoveryOccurrence) {
              return boost::none;
            }
            heatRecoveryOccurrence = occurrence;
          } else {
            return boost::none;
          }
        }
        if (!primaryOccurrence || !sourceOccurrence || !heatRecoveryOccurrence) {
          return boost::none;
        }

        const auto primary = provenOwnerForOccurrence(*primaryOccurrence, true, true);
        const auto source = provenOwnerForOccurrence(*sourceOccurrence, false, false);
        const auto heatRecovery = provenOwnerForOccurrence(*heatRecoveryOccurrence, false, false);
        if (!primary || !source || !heatRecovery || primary->branchList == source->branchList || primary->branchList == heatRecovery->branchList
            || source->branchList == heatRecovery->branchList || primary->plantLoop == source->plantLoop
            || primary->plantLoop == heatRecovery->plantLoop || source->plantLoop == heatRecovery->plantLoop) {
          return boost::none;
        }
        return ProvenFullyOwnedTopology{*primary, *source, *heatRecovery, *primaryOccurrence, *sourceOccurrence, *heatRecoveryOccurrence};
      }

      static bool receiverDemandSideReferencesComponent(PlantLoop_Impl& receiver, const HVACComponent& component) {
        const auto receiverLoop = receiver.getObject<PlantLoop>();
        const auto branches = receiver.model().getConcreteModelObjects<Branch>();
        const auto demandBranchListField = openstudio::PlantLoopFields::DemandSideBranchListName;
        for (const auto& branch : branches) {
          if (referencesObject(receiverLoop, demandBranchListField, branch) && branchReferencesComponent(branch, component)) {
            return true;
          }
        }
        for (const auto& branchList : receiver.model().getConcreteModelObjects<BranchList>()) {
          if (!referencesObject(receiverLoop, demandBranchListField, branchList)) {
            continue;
          }
          for (unsigned row = 0u; row < branchList.extensibleGroups().size(); ++row) {
            const auto branchField =
              branchList.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchListExtensibleFields::BranchName));
            for (const auto& branch : branches) {
              if (referencesObject(branchList, branchField, branch) && branchReferencesComponent(branch, component)) {
                return true;
              }
            }
          }
        }
        return false;
      }

      static bool hasHeatRecoveryPortOrRowEvidence(const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (fieldHasEvidence(heatPump, descriptor.heatRecoveryInletPort) || fieldHasEvidence(heatPump, descriptor.heatRecoveryOutletPort)) {
          return true;
        }
        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatPump, occurrences)) {
          return true;
        }
        const auto loadInlet = exactNodeField(heatPump, descriptor.loadInletPort);
        const auto loadOutlet = exactNodeField(heatPump, descriptor.loadOutletPort);
        const auto sourceInlet = exactNodeField(heatPump, descriptor.sourceInletPort);
        const auto sourceOutlet = exactNodeField(heatPump, descriptor.sourceOutletPort);
        return std::ranges::any_of(occurrences, [&](const auto& occurrence) {
          const bool loadRow = loadInlet && loadOutlet && occurrence.inlet == *loadInlet && occurrence.outlet == *loadOutlet;
          const bool sourceRow = sourceInlet && sourceOutlet && occurrence.inlet == *sourceInlet && occurrence.outlet == *sourceOutlet;
          return !loadRow && !sourceRow;
        });
      }

      static bool targetIsObservedOwner(PlantLoop_Impl& targetLoopImpl, const HVACComponent& heatPump) {
        if (heatPump.model() != targetLoopImpl.model()) {
          return false;
        }
        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatPump, occurrences)) {
          return false;
        }
        for (const auto& occurrence : occurrences) {
          const auto branchList = uniqueBranchListForBranch(heatPump.model(), occurrence.branch);
          if (!branchList) {
            continue;
          }
          for (const bool supplySide : {true, false}) {
            const auto owner = uniquePlantLoopForBranchList(heatPump.model(), *branchList, supplySide);
            if (owner && *owner == targetLoop) {
              return true;
            }
          }
        }
        return false;
      }

      static bool targetDemandTopologyIsCanonical(const PlantLoop& targetLoop) {
        return static_cast<bool>(observedPlantSideTopology(targetLoop, false));
      }

     private:
      static bool inboundCompanionEvidenceIsExact(const HVACComponent& heatPump, const ModelObject& candidate, unsigned companionField) {
        if (!referencesObject(candidate, companionField, heatPump)) {
          return true;
        }
        const auto inboundTarget = exactObjectField(candidate, companionField);
        return inboundTarget && inboundTarget->handle() == heatPump.handle() && hasUniqueName(candidate);
      }

      static bool hasAllOwnershipFieldEvidence(const HVACComponent& heatPump, const Descriptor& descriptor) {
        return fieldHasEvidence(heatPump, descriptor.loadInletPort) && fieldHasEvidence(heatPump, descriptor.loadOutletPort)
               && fieldHasEvidence(heatPump, descriptor.sourceInletPort) && fieldHasEvidence(heatPump, descriptor.sourceOutletPort)
               && fieldHasEvidence(heatPump, descriptor.heatRecoveryInletPort) && fieldHasEvidence(heatPump, descriptor.heatRecoveryOutletPort);
      }

      static bool branchReferencesComponent(const Branch& branch, const HVACComponent& component) {
        for (unsigned row = 0u; row < branch.extensibleGroups().size(); ++row) {
          const auto componentNameField =
            branch.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchExtensibleFields::ComponentName));
          if (referencesObject(branch, componentNameField, component)) {
            return true;
          }
        }
        return false;
      }
    };

    // Exact PlantLoop EIR heating/cooling source-side moves retain their
    // proven load and heat-recovery owners. The classifier preserves the
    // existing staged attachment sequence and claims every malformed or fully
    // three-owned representation before generic WaterToWater mutation.
    class PlantLoop_Impl::PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan
    {
     public:
      static bool requiresExactAttachmentDispatch(const HeatPumpPlantLoopEIRHeating& heatPump) {
        return requiresExactAttachmentDispatch(heatPump.cast<HVACComponent>(), heatingDescriptor());
      }

      static bool requiresExactAttachmentDispatch(const HeatPumpPlantLoopEIRCooling& heatPump) {
        return requiresExactAttachmentDispatch(heatPump.cast<HVACComponent>(), coolingDescriptor());
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                           HeatPumpPlantLoopEIRHeating heatPump) {
        return prepareShared(targetLoopImpl, heatPump.cast<HVACComponent>(), heatingDescriptor());
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                           HeatPumpPlantLoopEIRCooling heatPump) {
        return prepareShared(targetLoopImpl, heatPump.cast<HVACComponent>(), coolingDescriptor());
      }

      PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan(const PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan&) = delete;
      PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan& operator=(const PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan&) = delete;
      PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan(PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan&&) = delete;
      PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan& operator=(PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan&&) = delete;
      ~PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(m_plantRelocation && !m_committed);
        const auto primarySetpoint = m_primaryOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto heatRecoverySetpoint =
          m_heatRecoveryOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        OS_ASSERT(primarySetpoint && *primarySetpoint == m_primarySetpointTarget);
        OS_ASSERT(heatRecoverySetpoint && *heatRecoverySetpoint == m_heatRecoverySetpointTarget);
        m_plantRelocation->commit();
        m_committed = true;
      }

     private:
      using SharedInspection = PlantLoopEIRHeatPumpTopologyInspection;
      using Descriptor = SharedInspection::Descriptor;

      static Descriptor heatingDescriptor() {
        return SharedInspection::heatingDescriptor();
      }

      static Descriptor coolingDescriptor() {
        return SharedInspection::coolingDescriptor();
      }

      static bool requiresExactAttachmentDispatch(const HVACComponent& heatPump, const Descriptor& descriptor) {
        return SharedInspection::requiresExactAttachmentDispatch(heatPump, descriptor);
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan>
        prepareShared(PlantLoop_Impl& targetLoopImpl, HVACComponent heatPump, const Descriptor& descriptor) {
        if (heatPump.model() != targetLoopImpl.model()) {
          return nullptr;
        }
        const auto proven = SharedInspection::inspectFullyOwned(heatPump, descriptor);
        if (!proven) {
          return nullptr;
        }
        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if (targetLoop == proven->primary.plantLoop || targetLoop == proven->source.plantLoop || targetLoop == proven->heatRecovery.plantLoop
            || !SharedInspection::targetDemandTopologyIsCanonical(targetLoop)) {
          return nullptr;
        }

        const DemandBranchRelocationPlan::ExternalRow primaryRow{proven->primaryOccurrence.branch.handle(), proven->primaryOccurrence.row};
        const DemandBranchRelocationPlan::ExternalRow heatRecoveryRow{proven->heatRecoveryOccurrence.branch.handle(),
                                                                      proven->heatRecoveryOccurrence.row};
        std::unique_ptr<DemandBranchRelocationPlan> plantRelocation;
        if (descriptor.componentType == HeatPumpPlantLoopEIRHeating::iddObjectType()) {
          plantRelocation = DemandBranchRelocationPlan::preparePlantLoopEIRHeatingSource(targetLoopImpl, heatPump.cast<HeatPumpPlantLoopEIRHeating>(),
                                                                                         proven->source.plantLoop, primaryRow, heatRecoveryRow);
        } else if (descriptor.componentType == HeatPumpPlantLoopEIRCooling::iddObjectType()) {
          plantRelocation = DemandBranchRelocationPlan::preparePlantLoopEIRCoolingSource(targetLoopImpl, heatPump.cast<HeatPumpPlantLoopEIRCooling>(),
                                                                                         proven->source.plantLoop, primaryRow, heatRecoveryRow);
        }
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan>(new PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan(
          std::move(plantRelocation), proven->primary.plantLoop, proven->heatRecovery.plantLoop, proven->primary.topology.setpointTarget,
          proven->heatRecovery.topology.setpointTarget));
      }

      PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan(std::unique_ptr<DemandBranchRelocationPlan> plantRelocation, PlantLoop primaryOwner,
                                                           PlantLoop heatRecoveryOwner, Node primarySetpointTarget, Node heatRecoverySetpointTarget)
        : m_plantRelocation(std::move(plantRelocation)),
          m_primaryOwner(std::move(primaryOwner)),
          m_heatRecoveryOwner(std::move(heatRecoveryOwner)),
          m_primarySetpointTarget(std::move(primarySetpointTarget)),
          m_heatRecoverySetpointTarget(std::move(heatRecoverySetpointTarget)) {}

      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      PlantLoop m_primaryOwner;
      PlantLoop m_heatRecoveryOwner;
      Node m_primarySetpointTarget;
      Node m_heatRecoverySetpointTarget;
      bool m_committed = false;
    };

    // Exact explicit-tertiary relocation of the HeatRecovery role retains the
    // proven LoadSide and SourceSide owners and delegates only the selected
    // plant row/port mutation to the shared relocation core.
    class PlantLoop_Impl::PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan
    {
     public:
      static bool requiresExactAttachmentDispatch(PlantLoop_Impl& targetLoopImpl, const HeatPumpPlantLoopEIRHeating& heatPump) {
        return requiresExactAttachmentDispatch(targetLoopImpl, heatPump.cast<HVACComponent>(), SharedInspection::heatingDescriptor());
      }

      static bool requiresExactAttachmentDispatch(PlantLoop_Impl& targetLoopImpl, const HeatPumpPlantLoopEIRCooling& heatPump) {
        return requiresExactAttachmentDispatch(targetLoopImpl, heatPump.cast<HVACComponent>(), SharedInspection::coolingDescriptor());
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                                 HeatPumpPlantLoopEIRHeating heatPump) {
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), SharedInspection::heatingDescriptor());
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                                 HeatPumpPlantLoopEIRCooling heatPump) {
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), SharedInspection::coolingDescriptor());
      }

      PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan(const PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan&) = delete;
      PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan&
        operator=(const PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan&) = delete;
      PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan(PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan&&) = delete;
      PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan& operator=(PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan&&) = delete;
      ~PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(m_plantRelocation && !m_committed);
        assertRetainedSetpointIdentity();
        m_plantRelocation->commit();
        assertRetainedSetpointIdentity();
        m_committed = true;
      }

     private:
      using SharedInspection = PlantLoopEIRHeatPumpTopologyInspection;
      using Descriptor = SharedInspection::Descriptor;

      static bool requiresExactAttachmentDispatch(PlantLoop_Impl& targetLoopImpl, const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (heatPump.model() != targetLoopImpl.model() || heatPump.iddObject().type() != descriptor.componentType) {
          return true;
        }
        if (!SharedInspection::hasHeatRecoveryPortOrRowEvidence(heatPump, descriptor)) {
          // Only observationally exact staged states may reach the legacy
          // explicit-tertiary attachment path.
          return SharedInspection::requiresExactAttachmentDispatch(heatPump, descriptor)
                 || SharedInspection::targetIsObservedOwner(targetLoopImpl, heatPump);
        }
        return true;
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan>
        prepareProven(PlantLoop_Impl& targetLoopImpl, HVACComponent heatPump, const Descriptor& descriptor) {
        const auto proven = SharedInspection::inspectFullyOwned(heatPump, descriptor);
        if (!proven) {
          return nullptr;
        }
        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if (targetLoop == proven->primary.plantLoop || targetLoop == proven->source.plantLoop || targetLoop == proven->heatRecovery.plantLoop
            || !SharedInspection::targetDemandTopologyIsCanonical(targetLoop)) {
          return nullptr;
        }

        const DemandBranchRelocationPlan::ExternalRow primaryRow{proven->primaryOccurrence.branch.handle(), proven->primaryOccurrence.row};
        const DemandBranchRelocationPlan::ExternalRow sourceRow{proven->sourceOccurrence.branch.handle(), proven->sourceOccurrence.row};
        std::unique_ptr<DemandBranchRelocationPlan> plantRelocation;
        if (descriptor.componentType == HeatPumpPlantLoopEIRHeating::iddObjectType()) {
          plantRelocation = DemandBranchRelocationPlan::preparePlantLoopEIRHeatingHeatRecovery(
            targetLoopImpl, heatPump.cast<HeatPumpPlantLoopEIRHeating>(), proven->heatRecovery.plantLoop, primaryRow, sourceRow);
        } else if (descriptor.componentType == HeatPumpPlantLoopEIRCooling::iddObjectType()) {
          plantRelocation = DemandBranchRelocationPlan::preparePlantLoopEIRCoolingHeatRecovery(
            targetLoopImpl, heatPump.cast<HeatPumpPlantLoopEIRCooling>(), proven->heatRecovery.plantLoop, primaryRow, sourceRow);
        }
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan>(
          new PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan(std::move(plantRelocation), proven->primary.plantLoop,
                                                                         proven->source.plantLoop, proven->primary.topology.setpointTarget,
                                                                         proven->source.topology.setpointTarget));
      }

      PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan(std::unique_ptr<DemandBranchRelocationPlan> plantRelocation, PlantLoop primaryOwner,
                                                                 PlantLoop sourceOwner, Node primarySetpointTarget, Node sourceSetpointTarget)
        : m_plantRelocation(std::move(plantRelocation)),
          m_primaryOwner(std::move(primaryOwner)),
          m_sourceOwner(std::move(sourceOwner)),
          m_primarySetpointTarget(std::move(primarySetpointTarget)),
          m_sourceSetpointTarget(std::move(sourceSetpointTarget)) {}

      void assertRetainedSetpointIdentity() const {
        const auto primarySetpoint = m_primaryOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto sourceSetpoint = m_sourceOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        OS_ASSERT(primarySetpoint && *primarySetpoint == m_primarySetpointTarget);
        OS_ASSERT(sourceSetpoint && *sourceSetpoint == m_sourceSetpointTarget);
      }

      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      PlantLoop m_primaryOwner;
      PlantLoop m_sourceOwner;
      Node m_primarySetpointTarget;
      Node m_sourceSetpointTarget;
      bool m_committed = false;
    };

    // Direct removal of a fully three-owned PlantLoop EIR heat pump must
    // distinguish its SourceSide demand row from its HeatRecovery demand row.
    // The existing single-branch teardown owns the plant mutation; this
    // wrapper proves the two retained owners and the selected SourceSide role.
    class PlantLoop_Impl::PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan
    {
     public:
      static bool requiresExactRemovalDispatch(PlantLoop_Impl& receiver, const HeatPumpPlantLoopEIRHeating& heatPump) {
        return requiresExactRemovalDispatch(receiver, heatPump.cast<HVACComponent>(), PlantLoopEIRHeatPumpTopologyInspection::heatingDescriptor());
      }

      static bool requiresExactRemovalDispatch(PlantLoop_Impl& receiver, const HeatPumpPlantLoopEIRCooling& heatPump) {
        return requiresExactRemovalDispatch(receiver, heatPump.cast<HVACComponent>(), PlantLoopEIRHeatPumpTopologyInspection::coolingDescriptor());
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan> prepare(PlantLoop_Impl& receiver,
                                                                                        HeatPumpPlantLoopEIRHeating heatPump) {
        return prepareProven(receiver, heatPump.cast<HVACComponent>(), PlantLoopEIRHeatPumpTopologyInspection::heatingDescriptor());
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan> prepare(PlantLoop_Impl& receiver,
                                                                                        HeatPumpPlantLoopEIRCooling heatPump) {
        return prepareProven(receiver, heatPump.cast<HVACComponent>(), PlantLoopEIRHeatPumpTopologyInspection::coolingDescriptor());
      }

      PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan(const PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan&) = delete;
      PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan& operator=(const PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan&) = delete;
      PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan(PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan&&) = delete;
      PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan& operator=(PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan&&) = delete;
      ~PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan() = default;

      void commit() {
        OS_ASSERT(m_branchRemoval && !m_committed);
        assertSetpointIdentity();
        m_branchRemoval->commit();
        assertSetpointIdentity();
        m_committed = true;
      }

     private:
      using SharedInspection = PlantLoopEIRHeatPumpTopologyInspection;
      using Descriptor = SharedInspection::Descriptor;

      static bool requiresExactRemovalDispatch(PlantLoop_Impl& receiver, const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (heatPump.model() != receiver.model() || heatPump.iddObject().type() != descriptor.componentType) {
          return false;
        }
        if (const auto proven = SharedInspection::inspectFullyOwned(heatPump, descriptor)) {
          // A proven HeatRecovery receiver intentionally falls through to the
          // existing tertiary removal behavior.
          const auto receiverLoop = receiver.getObject<PlantLoop>();
          if (proven->heatRecovery.plantLoop == receiverLoop) {
            return false;
          }
          if (proven->source.plantLoop == receiverLoop) {
            return true;
          }
        }
        // Preserve the established generic lifecycle for observationally exact
        // unattached and staged (primary-only or exact two-owner) shapes.
        if (!SharedInspection::requiresExactAttachmentDispatch(heatPump, descriptor)) {
          return false;
        }
        // Classification is observational: any managed or raw HP row reached
        // through this receiver's persisted demand BranchList is claimed, so
        // malformed Source/HeatRecovery evidence cannot reach generic removal.
        return SharedInspection::receiverDemandSideReferencesComponent(receiver, heatPump);
      }

      static std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan> prepareProven(PlantLoop_Impl& receiver, HVACComponent heatPump,
                                                                                              const Descriptor& descriptor) {
        const auto proven = SharedInspection::inspectFullyOwned(heatPump, descriptor);
        const auto receiverLoop = receiver.getObject<PlantLoop>();
        if (!proven || proven->source.plantLoop != receiverLoop) {
          return nullptr;
        }

        auto branchRemoval = receiver.prepareDemandBranchRemoval(heatPump, descriptor.sourceInletPort, descriptor.sourceOutletPort, false,
                                                                 DemandBranchPostDisconnectUpdate::PlantLoopEIRHeatPumpAirSource);
        if (!branchRemoval) {
          return nullptr;
        }
        return std::unique_ptr<PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan>(new PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan(
          std::move(branchRemoval), proven->primary.plantLoop, proven->source.plantLoop, proven->heatRecovery.plantLoop,
          proven->primary.topology.setpointTarget, proven->source.topology.setpointTarget, proven->heatRecovery.topology.setpointTarget));
      }

      PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan(std::unique_ptr<DemandBranchRemovalPlan> branchRemoval, PlantLoop primaryOwner,
                                                        PlantLoop sourceOwner, PlantLoop heatRecoveryOwner, Node primarySetpointTarget,
                                                        Node sourceSetpointTarget, Node heatRecoverySetpointTarget)
        : m_branchRemoval(std::move(branchRemoval)),
          m_primaryOwner(std::move(primaryOwner)),
          m_sourceOwner(std::move(sourceOwner)),
          m_heatRecoveryOwner(std::move(heatRecoveryOwner)),
          m_primarySetpointTarget(std::move(primarySetpointTarget)),
          m_sourceSetpointTarget(std::move(sourceSetpointTarget)),
          m_heatRecoverySetpointTarget(std::move(heatRecoverySetpointTarget)) {}

      void assertSetpointIdentity() const {
        const auto primarySetpoint = m_primaryOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto sourceSetpoint = m_sourceOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        const auto heatRecoverySetpoint =
          m_heatRecoveryOwner.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        OS_ASSERT(primarySetpoint && *primarySetpoint == m_primarySetpointTarget);
        OS_ASSERT(sourceSetpoint && *sourceSetpoint == m_sourceSetpointTarget);
        OS_ASSERT(heatRecoverySetpoint && *heatRecoverySetpoint == m_heatRecoverySetpointTarget);
      }

      std::unique_ptr<DemandBranchRemovalPlan> m_branchRemoval;
      PlantLoop m_primaryOwner;
      PlantLoop m_sourceOwner;
      PlantLoop m_heatRecoveryOwner;
      Node m_primarySetpointTarget;
      Node m_sourceSetpointTarget;
      Node m_heatRecoverySetpointTarget;
      bool m_committed = false;
    };

    // Exact HeatExchanger:FluidToFluid demand-side moves retain their proven
    // primary supply owner. An observational classifier keeps every partial or
    // malformed attachment out of the generic water-to-water path.
    class PlantLoop_Impl::FluidToFluidHeatExchangerDemandBranchAttachmentPlan : private PlantLoop_Impl::ExactPlantBranchTopologyInspection
    {
     public:
      static bool requiresExactAttachmentDispatch(const HeatExchangerFluidToFluid& heatExchanger) {
        if (heatExchanger.iddObject().type() != HeatExchangerFluidToFluid::iddObjectType() || !hasUniqueName(heatExchanger)) {
          return true;
        }

        const bool supplyInletEvidence = fieldHasEvidence(heatExchanger, heatExchanger.supplyInletPort());
        const bool supplyOutletEvidence = fieldHasEvidence(heatExchanger, heatExchanger.supplyOutletPort());
        const bool demandInletEvidence = fieldHasEvidence(heatExchanger, heatExchanger.demandInletPort());
        const bool demandOutletEvidence = fieldHasEvidence(heatExchanger, heatExchanger.demandOutletPort());
        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatExchanger, occurrences)) {
          return true;
        }

        const bool anyFieldEvidence = supplyInletEvidence || supplyOutletEvidence || demandInletEvidence || demandOutletEvidence;
        if (!anyFieldEvidence && occurrences.empty()) {
          return false;
        }
        if (!supplyInletEvidence || !supplyOutletEvidence || demandInletEvidence || demandOutletEvidence || occurrences.size() != 1u) {
          return true;
        }

        const auto supplyInlet = exactNodeField(heatExchanger, heatExchanger.supplyInletPort());
        const auto supplyOutlet = exactNodeField(heatExchanger, heatExchanger.supplyOutletPort());
        if (!supplyInlet || !supplyOutlet || *supplyInlet == *supplyOutlet || !hasUniqueName(*supplyInlet) || !hasUniqueName(*supplyOutlet)) {
          return true;
        }

        const auto& primaryOccurrence = occurrences.front();
        if (primaryOccurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(primaryOccurrence.branch)
            || primaryOccurrence.inlet != *supplyInlet || primaryOccurrence.outlet != *supplyOutlet) {
          return true;
        }

        const auto branchList = uniqueBranchListForBranch(heatExchanger.model(), primaryOccurrence.branch);
        const auto primaryOwner = branchList ? uniquePlantLoopForBranchList(heatExchanger.model(), *branchList, true) : boost::none;
        const auto primaryTopology = primaryOwner ? observedPlantSideTopology(*primaryOwner, true) : boost::none;
        const bool primaryPlacementSupported = primaryTopology
                                               && (std::ranges::count(primaryTopology->equipmentBranches, primaryOccurrence.branch) == 1
                                                   || primaryTopology->outletBranch == primaryOccurrence.branch);
        return !branchList || !primaryOwner || !primaryTopology || primaryTopology->branchList != *branchList || !primaryPlacementSupported;
      }

      static bool targetIsPrimaryOwner(const PlantLoop_Impl& targetLoopImpl, const HeatExchangerFluidToFluid& heatExchanger) {
        const auto supplyInlet = exactNodeField(heatExchanger, heatExchanger.supplyInletPort());
        const auto supplyOutlet = exactNodeField(heatExchanger, heatExchanger.supplyOutletPort());
        std::vector<BranchOccurrence> occurrences;
        if (!supplyInlet || !supplyOutlet || !collectOccurrences(heatExchanger, occurrences)) {
          return false;
        }
        const auto occurrence = std::ranges::find_if(
          occurrences, [&](const auto& candidate) { return candidate.inlet == *supplyInlet && candidate.outlet == *supplyOutlet; });
        if (occurrence == occurrences.end()) {
          return false;
        }
        const auto branchList = uniqueBranchListForBranch(targetLoopImpl.model(), occurrence->branch);
        const auto primaryOwner = branchList ? uniquePlantLoopForBranchList(targetLoopImpl.model(), *branchList, true) : boost::none;
        return primaryOwner && *primaryOwner == targetLoopImpl.getObject<PlantLoop>();
      }

      static std::unique_ptr<FluidToFluidHeatExchangerDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                          HeatExchangerFluidToFluid heatExchanger) {
        if (heatExchanger.iddObject().type() != HeatExchangerFluidToFluid::iddObjectType() || heatExchanger.model() != targetLoopImpl.model()
            || !hasUniqueName(heatExchanger)) {
          return nullptr;
        }

        const auto supplyInlet = exactNodeField(heatExchanger, heatExchanger.supplyInletPort());
        const auto supplyOutlet = exactNodeField(heatExchanger, heatExchanger.supplyOutletPort());
        const auto demandInlet = exactNodeField(heatExchanger, heatExchanger.demandInletPort());
        const auto demandOutlet = exactNodeField(heatExchanger, heatExchanger.demandOutletPort());
        if (!supplyInlet || !supplyOutlet || !demandInlet || !demandOutlet) {
          return nullptr;
        }
        const std::array<Node, 4> ports{*supplyInlet, *supplyOutlet, *demandInlet, *demandOutlet};
        std::set<Handle> portHandles;
        for (const auto& port : ports) {
          if (!hasUniqueName(port) || !portHandles.insert(port.handle()).second) {
            return nullptr;
          }
        }

        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatExchanger, occurrences) || occurrences.size() != 2u) {
          return nullptr;
        }
        boost::optional<BranchOccurrence> primaryOccurrence;
        boost::optional<BranchOccurrence> sourceOccurrence;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return nullptr;
          }
          if (occurrence.inlet == *supplyInlet && occurrence.outlet == *supplyOutlet) {
            if (primaryOccurrence) {
              return nullptr;
            }
            primaryOccurrence = occurrence;
          } else if (occurrence.inlet == *demandInlet && occurrence.outlet == *demandOutlet) {
            if (sourceOccurrence) {
              return nullptr;
            }
            sourceOccurrence = occurrence;
          } else {
            return nullptr;
          }
        }
        if (!primaryOccurrence || !sourceOccurrence) {
          return nullptr;
        }

        const auto primaryBranchList = uniqueBranchListForBranch(targetLoopImpl.model(), primaryOccurrence->branch);
        const auto sourceBranchList = uniqueBranchListForBranch(targetLoopImpl.model(), sourceOccurrence->branch);
        if (!primaryBranchList || !sourceBranchList || *primaryBranchList == *sourceBranchList) {
          return nullptr;
        }
        const auto primaryOwner = uniquePlantLoopForBranchList(targetLoopImpl.model(), *primaryBranchList, true);
        const auto sourceOwner = uniquePlantLoopForBranchList(targetLoopImpl.model(), *sourceBranchList, false);
        if (!primaryOwner || !sourceOwner || *primaryOwner == *sourceOwner) {
          return nullptr;
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if (targetLoop == *primaryOwner || targetLoop == *sourceOwner) {
          return nullptr;
        }
        const auto primaryTopology = observedPlantSideTopology(*primaryOwner, true);
        const auto sourceTopology = observedPlantSideTopology(*sourceOwner, false);
        const auto targetTopology = observedPlantSideTopology(targetLoop, false);
        const bool primaryPlacementSupported = primaryTopology
                                               && (std::ranges::count(primaryTopology->equipmentBranches, primaryOccurrence->branch) == 1
                                                   || primaryTopology->outletBranch == primaryOccurrence->branch);
        if (!primaryTopology || !sourceTopology || !targetTopology || primaryTopology->branchList != *primaryBranchList
            || sourceTopology->branchList != *sourceBranchList || !primaryPlacementSupported
            || std::ranges::count(sourceTopology->equipmentBranches, sourceOccurrence->branch) != 1) {
          return nullptr;
        }

        auto plantRelocation = DemandBranchRelocationPlan::prepareFluidToFluidHeatExchanger(
          targetLoopImpl, heatExchanger, *sourceOwner, {primaryOccurrence->branch.handle(), primaryOccurrence->row});
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<FluidToFluidHeatExchangerDemandBranchAttachmentPlan>(
          new FluidToFluidHeatExchangerDemandBranchAttachmentPlan(std::move(plantRelocation)));
      }

      FluidToFluidHeatExchangerDemandBranchAttachmentPlan(const FluidToFluidHeatExchangerDemandBranchAttachmentPlan&) = delete;
      FluidToFluidHeatExchangerDemandBranchAttachmentPlan& operator=(const FluidToFluidHeatExchangerDemandBranchAttachmentPlan&) = delete;
      FluidToFluidHeatExchangerDemandBranchAttachmentPlan(FluidToFluidHeatExchangerDemandBranchAttachmentPlan&&) = delete;
      FluidToFluidHeatExchangerDemandBranchAttachmentPlan& operator=(FluidToFluidHeatExchangerDemandBranchAttachmentPlan&&) = delete;
      ~FluidToFluidHeatExchangerDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(m_plantRelocation && !m_committed);
        m_plantRelocation->commit();
        m_committed = true;
      }

     private:
      explicit FluidToFluidHeatExchangerDemandBranchAttachmentPlan(std::unique_ptr<DemandBranchRelocationPlan> plantRelocation)
        : m_plantRelocation(std::move(plantRelocation)) {}

      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      bool m_committed = false;
    };

    // Exact ThermalStorage:ChilledWater:Stratified source-side moves retain
    // their proven UseSide owner and canonical WaterHeater:Sizing child. The
    // plan never reads or writes schedules, ambient relationships, or storage
    // fields outside the two explicit SourceSide ports.
    class PlantLoop_Impl::ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan : private PlantLoop_Impl::ExactPlantBranchTopologyInspection
    {
     public:
      struct ProvenOwnership
      {
        boost::optional<PlantLoop> primaryOwner;
        boost::optional<PlantLoop> sourceOwner;
        boost::optional<BranchOccurrence> primaryOccurrence;
        boost::optional<BranchOccurrence> sourceOccurrence;
        WaterHeaterSizing sizing;
      };

      static bool requiresExactAttachmentDispatch(const ThermalStorageChilledWaterStratified& storage) {
        if (storage.iddObject().type() != ThermalStorageChilledWaterStratified::iddObjectType() || !hasUniqueEligibleStorageName(storage)
            || !exactSizingChild(storage)) {
          return true;
        }

        const bool supplyInletEvidence = fieldHasEvidence(storage, storage.supplyInletPort());
        const bool supplyOutletEvidence = fieldHasEvidence(storage, storage.supplyOutletPort());
        const bool demandInletEvidence = fieldHasEvidence(storage, storage.demandInletPort());
        const bool demandOutletEvidence = fieldHasEvidence(storage, storage.demandOutletPort());
        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(storage, occurrences)) {
          return true;
        }

        const bool anyFieldEvidence = supplyInletEvidence || supplyOutletEvidence || demandInletEvidence || demandOutletEvidence;
        if (!anyFieldEvidence && occurrences.empty()) {
          return false;
        }

        const auto ownership = provenOwnership(storage, false, false);
        return !ownership || !ownership->primaryOwner || ownership->sourceOwner;
      }

      static bool targetIsPrimaryOwner(const PlantLoop_Impl& targetLoopImpl, const ThermalStorageChilledWaterStratified& storage) {
        const auto ownership = provenOwnership(storage, false, false);
        return ownership && ownership->primaryOwner && *ownership->primaryOwner == targetLoopImpl.getObject<PlantLoop>();
      }

      static boost::optional<ProvenOwnership> provenOwnershipForRemoval(const ThermalStorageChilledWaterStratified& storage) {
        return provenOwnership(storage, false, false);
      }

      static bool hasBranchEvidence(const ThermalStorageChilledWaterStratified& storage, const std::vector<Branch>& branches) {
        for (const auto& branch : branches) {
          for (unsigned row = 0u; row < branch.extensibleGroups().size(); ++row) {
            const auto componentNameField =
              branch.iddObject().index(openstudio::ExtensibleIndex(row, openstudio::BranchExtensibleFields::ComponentName));
            if (referencesObject(branch, componentNameField, storage)) {
              return true;
            }
          }
        }
        return false;
      }

      static std::unique_ptr<ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                                     ThermalStorageChilledWaterStratified storage) {
        if (storage.model() != targetLoopImpl.model()) {
          return nullptr;
        }
        const auto ownership = provenOwnership(storage, true, true);
        if (!ownership || !ownership->primaryOwner || !ownership->sourceOwner || !ownership->primaryOccurrence) {
          return nullptr;
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if (targetLoop == *ownership->primaryOwner || targetLoop == *ownership->sourceOwner || !observedPlantSideTopology(targetLoop, false)) {
          return nullptr;
        }

        auto plantRelocation = DemandBranchRelocationPlan::prepareThermalStorageChilledWaterStratified(
          targetLoopImpl, storage, *ownership->sourceOwner, {ownership->primaryOccurrence->branch.handle(), ownership->primaryOccurrence->row});
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan>(
          new ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan(std::move(plantRelocation)));
      }

      ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan(const ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan&) = delete;
      ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan&
        operator=(const ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan&) = delete;
      ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan(ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan&&) = delete;
      ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan&
        operator=(ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan&&) = delete;
      ~ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(m_plantRelocation && !m_committed);
        m_plantRelocation->commit();
        m_committed = true;
      }

     private:
      static bool hasUniqueEligibleStorageName(const ThermalStorageChilledWaterStratified& storage) {
        const auto name = storage.name();
        if (!name || name->empty()) {
          return false;
        }
        return std::ranges::count_if(storage.model().objects(),
                                     [&name](const auto& candidate) {
                                       const auto references = candidate.iddObject().references();
                                       const bool isEligible = std::ranges::any_of(references, [](const auto& reference) {
                                         return openstudio::istringEqual(reference, "ThermalStorageWaterNames")
                                                || openstudio::istringEqual(reference, "WaterHeaterNames");
                                       });
                                       const auto candidateName = candidate.name();
                                       return isEligible && candidateName && openstudio::istringEqual(*candidateName, *name);
                                     })
               == 1;
      }

      static boost::optional<WaterHeaterSizing> exactSizingChild(const ThermalStorageChilledWaterStratified& storage) {
        if (!hasUniqueEligibleStorageName(storage)) {
          return boost::none;
        }

        boost::optional<WaterHeaterSizing> result;
        unsigned occurrences = 0u;
        for (const auto& sizing : storage.model().getConcreteModelObjects<WaterHeaterSizing>()) {
          if (!referencesObject(sizing, openstudio::WaterHeater_SizingFields::WaterHeaterName, storage)) {
            continue;
          }
          const auto target = exactObjectField(sizing, openstudio::WaterHeater_SizingFields::WaterHeaterName);
          if (!target || target->handle() != storage.handle() || target->iddObject().type() != storage.iddObject().type()) {
            return boost::none;
          }
          ++occurrences;
          result = sizing;
        }
        return occurrences == 1u ? result : boost::none;
      }

      static boost::optional<ProvenOwnership> provenOwnership(const ThermalStorageChilledWaterStratified& storage, bool requirePrimary,
                                                              bool requireSource) {
        if (storage.iddObject().type() != ThermalStorageChilledWaterStratified::iddObjectType() || !hasUniqueEligibleStorageName(storage)) {
          return boost::none;
        }
        const auto sizing = exactSizingChild(storage);
        if (!sizing) {
          return boost::none;
        }

        const bool supplyInletEvidence = fieldHasEvidence(storage, storage.supplyInletPort());
        const bool supplyOutletEvidence = fieldHasEvidence(storage, storage.supplyOutletPort());
        const bool demandInletEvidence = fieldHasEvidence(storage, storage.demandInletPort());
        const bool demandOutletEvidence = fieldHasEvidence(storage, storage.demandOutletPort());
        if (supplyInletEvidence != supplyOutletEvidence || demandInletEvidence != demandOutletEvidence || (requirePrimary && !supplyInletEvidence)
            || (requireSource && !demandInletEvidence) || (!supplyInletEvidence && !demandInletEvidence)) {
          return boost::none;
        }

        const auto supplyInlet = supplyInletEvidence ? exactNodeField(storage, storage.supplyInletPort()) : boost::none;
        const auto supplyOutlet = supplyOutletEvidence ? exactNodeField(storage, storage.supplyOutletPort()) : boost::none;
        const auto demandInlet = demandInletEvidence ? exactNodeField(storage, storage.demandInletPort()) : boost::none;
        const auto demandOutlet = demandOutletEvidence ? exactNodeField(storage, storage.demandOutletPort()) : boost::none;
        if ((supplyInletEvidence && (!supplyInlet || !supplyOutlet)) || (demandInletEvidence && (!demandInlet || !demandOutlet))) {
          return boost::none;
        }

        std::set<Handle> portHandles;
        for (const auto& port : {supplyInlet, supplyOutlet, demandInlet, demandOutlet}) {
          if (port && (!hasUniqueName(*port) || !portHandles.insert(port->handle()).second)) {
            return boost::none;
          }
        }

        std::vector<BranchOccurrence> occurrences;
        const unsigned expectedOccurrences = static_cast<unsigned>(supplyInletEvidence) + static_cast<unsigned>(demandInletEvidence);
        if (!collectOccurrences(storage, occurrences) || occurrences.size() != expectedOccurrences) {
          return boost::none;
        }

        boost::optional<BranchOccurrence> primaryOccurrence;
        boost::optional<BranchOccurrence> sourceOccurrence;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return boost::none;
          }
          if (supplyInlet && supplyOutlet && occurrence.inlet == *supplyInlet && occurrence.outlet == *supplyOutlet) {
            if (primaryOccurrence) {
              return boost::none;
            }
            primaryOccurrence = occurrence;
          } else if (demandInlet && demandOutlet && occurrence.inlet == *demandInlet && occurrence.outlet == *demandOutlet) {
            if (sourceOccurrence) {
              return boost::none;
            }
            sourceOccurrence = occurrence;
          } else {
            return boost::none;
          }
        }
        if (static_cast<bool>(primaryOccurrence) != supplyInletEvidence || static_cast<bool>(sourceOccurrence) != demandInletEvidence) {
          return boost::none;
        }

        boost::optional<PlantLoop> primaryOwner;
        boost::optional<PlantLoop> sourceOwner;
        boost::optional<BranchList> primaryBranchList;
        boost::optional<BranchList> sourceBranchList;
        if (primaryOccurrence) {
          primaryBranchList = uniqueBranchListForBranch(storage.model(), primaryOccurrence->branch);
          primaryOwner = primaryBranchList ? uniquePlantLoopForBranchList(storage.model(), *primaryBranchList, true) : boost::none;
          const auto topology = primaryOwner ? observedPlantSideTopology(*primaryOwner, true) : boost::none;
          if (!primaryBranchList || !primaryOwner || !topology || topology->branchList != *primaryBranchList
              || std::ranges::count(topology->equipmentBranches, primaryOccurrence->branch) != 1) {
            return boost::none;
          }
        }
        if (sourceOccurrence) {
          sourceBranchList = uniqueBranchListForBranch(storage.model(), sourceOccurrence->branch);
          sourceOwner = sourceBranchList ? uniquePlantLoopForBranchList(storage.model(), *sourceBranchList, false) : boost::none;
          const auto topology = sourceOwner ? observedPlantSideTopology(*sourceOwner, false) : boost::none;
          if (!sourceBranchList || !sourceOwner || !topology || topology->branchList != *sourceBranchList
              || std::ranges::count(topology->equipmentBranches, sourceOccurrence->branch) != 1) {
            return boost::none;
          }
        }
        if (primaryOwner && sourceOwner && (*primaryOwner == *sourceOwner || *primaryBranchList == *sourceBranchList)) {
          return boost::none;
        }

        return ProvenOwnership{primaryOwner, sourceOwner, primaryOccurrence, sourceOccurrence, *sizing};
      }

      explicit ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan(std::unique_ptr<DemandBranchRelocationPlan> plantRelocation)
        : m_plantRelocation(std::move(plantRelocation)) {}

      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      bool m_committed = false;
    };

    // Exact EquationFit heat-pump demand moves preserve the selected object's
    // primary owner and companion graph. The descriptors deliberately encode
    // EPModel persisted fields rather than generic physical-side semantics.
    class PlantLoop_Impl::EquationFitHeatPumpDemandBranchAttachmentPlan : private PlantLoop_Impl::ExactPlantBranchTopologyInspection
    {
     public:
      static bool requiresExactAttachmentDispatch(const HeatPumpWaterToWaterEquationFitHeating& heatPump) {
        return requiresExactAttachmentDispatch(heatPump.cast<HVACComponent>(), heatingDescriptor());
      }

      static bool requiresExactAttachmentDispatch(const HeatPumpWaterToWaterEquationFitCooling& heatPump) {
        return requiresExactAttachmentDispatch(heatPump.cast<HVACComponent>(), coolingDescriptor());
      }

      static bool targetIsPrimaryOwner(const PlantLoop_Impl& targetLoopImpl, const HeatPumpWaterToWaterEquationFitHeating& heatPump) {
        return targetIsPrimaryOwner(targetLoopImpl, heatPump.cast<HVACComponent>(), heatingDescriptor());
      }

      static bool targetIsPrimaryOwner(const PlantLoop_Impl& targetLoopImpl, const HeatPumpWaterToWaterEquationFitCooling& heatPump) {
        return targetIsPrimaryOwner(targetLoopImpl, heatPump.cast<HVACComponent>(), coolingDescriptor());
      }

      static std::unique_ptr<EquationFitHeatPumpDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                    HeatPumpWaterToWaterEquationFitHeating heatPump) {
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), heatingDescriptor());
      }

      static std::unique_ptr<EquationFitHeatPumpDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl,
                                                                                    HeatPumpWaterToWaterEquationFitCooling heatPump) {
        return prepareProven(targetLoopImpl, heatPump.cast<HVACComponent>(), coolingDescriptor());
      }

      EquationFitHeatPumpDemandBranchAttachmentPlan(const EquationFitHeatPumpDemandBranchAttachmentPlan&) = delete;
      EquationFitHeatPumpDemandBranchAttachmentPlan& operator=(const EquationFitHeatPumpDemandBranchAttachmentPlan&) = delete;
      EquationFitHeatPumpDemandBranchAttachmentPlan(EquationFitHeatPumpDemandBranchAttachmentPlan&&) = delete;
      EquationFitHeatPumpDemandBranchAttachmentPlan& operator=(EquationFitHeatPumpDemandBranchAttachmentPlan&&) = delete;
      ~EquationFitHeatPumpDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(m_plantRelocation && !m_committed);
        m_plantRelocation->commit();
        m_committed = true;
      }

     private:
      struct Descriptor
      {
        IddObjectType componentType;
        unsigned supplyInletPort;
        unsigned supplyOutletPort;
        unsigned demandInletPort;
        unsigned demandOutletPort;
        unsigned outboundCompanionField;
        IddObjectType companionType;
        unsigned inboundCompanionField;
      };

      static Descriptor heatingDescriptor() {
        return {HeatPumpWaterToWaterEquationFitHeating::iddObjectType(),
                openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName,
                HeatPumpWaterToWaterEquationFitCooling::iddObjectType(),
                openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::CompanionHeatingHeatPumpName};
      }

      static Descriptor coolingDescriptor() {
        return {HeatPumpWaterToWaterEquationFitCooling::iddObjectType(),
                openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName,
                openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::CompanionHeatingHeatPumpName,
                HeatPumpWaterToWaterEquationFitHeating::iddObjectType(),
                openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName};
      }

      static bool inboundCompanionEvidenceIsExact(const HVACComponent& heatPump, const ModelObject& candidate, unsigned companionField) {
        if (!referencesObject(candidate, companionField, heatPump)) {
          return true;
        }
        const auto inboundTarget = exactObjectField(candidate, companionField);
        return inboundTarget && inboundTarget->handle() == heatPump.handle() && hasUniqueName(candidate);
      }

      static bool companionEvidenceIsExact(const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (fieldHasEvidence(heatPump, descriptor.outboundCompanionField)) {
          const auto companion = exactObjectField(heatPump, descriptor.outboundCompanionField);
          if (!companion || companion->iddObject().type() != descriptor.companionType || !hasUniqueName(*companion)) {
            return false;
          }
        }

        if (descriptor.companionType == HeatPumpWaterToWaterEquationFitCooling::iddObjectType()) {
          for (const auto& candidate : heatPump.model().getConcreteModelObjects<HeatPumpWaterToWaterEquationFitCooling>()) {
            if (!inboundCompanionEvidenceIsExact(heatPump, candidate, descriptor.inboundCompanionField)) {
              return false;
            }
          }
        } else {
          for (const auto& candidate : heatPump.model().getConcreteModelObjects<HeatPumpWaterToWaterEquationFitHeating>()) {
            if (!inboundCompanionEvidenceIsExact(heatPump, candidate, descriptor.inboundCompanionField)) {
              return false;
            }
          }
        }
        return true;
      }

      static bool requiresExactAttachmentDispatch(const HVACComponent& heatPump, const Descriptor& descriptor) {
        if (heatPump.iddObject().type() != descriptor.componentType || !hasUniqueName(heatPump) || !companionEvidenceIsExact(heatPump, descriptor)) {
          return true;
        }

        const bool supplyInletEvidence = fieldHasEvidence(heatPump, descriptor.supplyInletPort);
        const bool supplyOutletEvidence = fieldHasEvidence(heatPump, descriptor.supplyOutletPort);
        const bool demandInletEvidence = fieldHasEvidence(heatPump, descriptor.demandInletPort);
        const bool demandOutletEvidence = fieldHasEvidence(heatPump, descriptor.demandOutletPort);
        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatPump, occurrences)) {
          return true;
        }

        const bool anyFieldEvidence = supplyInletEvidence || supplyOutletEvidence || demandInletEvidence || demandOutletEvidence;
        if (!anyFieldEvidence && occurrences.empty()) {
          return false;
        }
        if (!supplyInletEvidence || !supplyOutletEvidence || demandInletEvidence || demandOutletEvidence || occurrences.size() != 1u) {
          return true;
        }

        const auto supplyInlet = exactNodeField(heatPump, descriptor.supplyInletPort);
        const auto supplyOutlet = exactNodeField(heatPump, descriptor.supplyOutletPort);
        if (!supplyInlet || !supplyOutlet || *supplyInlet == *supplyOutlet || !hasUniqueName(*supplyInlet) || !hasUniqueName(*supplyOutlet)) {
          return true;
        }

        const auto& primaryOccurrence = occurrences.front();
        if (primaryOccurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(primaryOccurrence.branch)
            || primaryOccurrence.inlet != *supplyInlet || primaryOccurrence.outlet != *supplyOutlet) {
          return true;
        }

        const auto branchList = uniqueBranchListForBranch(heatPump.model(), primaryOccurrence.branch);
        const auto primaryOwner = branchList ? uniquePlantLoopForBranchList(heatPump.model(), *branchList, true) : boost::none;
        const auto primaryTopology = primaryOwner ? observedPlantSideTopology(*primaryOwner, true) : boost::none;
        const bool primaryPlacementSupported = primaryTopology
                                               && (std::ranges::count(primaryTopology->equipmentBranches, primaryOccurrence.branch) == 1
                                                   || primaryTopology->outletBranch == primaryOccurrence.branch);
        return !branchList || !primaryOwner || !primaryTopology || primaryTopology->branchList != *branchList || !primaryPlacementSupported;
      }

      static bool targetIsPrimaryOwner(const PlantLoop_Impl& targetLoopImpl, const HVACComponent& heatPump, const Descriptor& descriptor) {
        const auto supplyInlet = exactNodeField(heatPump, descriptor.supplyInletPort);
        const auto supplyOutlet = exactNodeField(heatPump, descriptor.supplyOutletPort);
        std::vector<BranchOccurrence> occurrences;
        if (!supplyInlet || !supplyOutlet || !collectOccurrences(heatPump, occurrences)) {
          return false;
        }
        const auto occurrence = std::ranges::find_if(
          occurrences, [&](const auto& candidate) { return candidate.inlet == *supplyInlet && candidate.outlet == *supplyOutlet; });
        if (occurrence == occurrences.end()) {
          return false;
        }
        const auto branchList = uniqueBranchListForBranch(targetLoopImpl.model(), occurrence->branch);
        const auto primaryOwner = branchList ? uniquePlantLoopForBranchList(targetLoopImpl.model(), *branchList, true) : boost::none;
        return primaryOwner && *primaryOwner == targetLoopImpl.getObject<PlantLoop>();
      }

      static std::unique_ptr<EquationFitHeatPumpDemandBranchAttachmentPlan> prepareProven(PlantLoop_Impl& targetLoopImpl, HVACComponent heatPump,
                                                                                          const Descriptor& descriptor) {
        if (heatPump.iddObject().type() != descriptor.componentType || heatPump.model() != targetLoopImpl.model() || !hasUniqueName(heatPump)
            || !companionEvidenceIsExact(heatPump, descriptor)) {
          return nullptr;
        }

        const auto supplyInlet = exactNodeField(heatPump, descriptor.supplyInletPort);
        const auto supplyOutlet = exactNodeField(heatPump, descriptor.supplyOutletPort);
        const auto demandInlet = exactNodeField(heatPump, descriptor.demandInletPort);
        const auto demandOutlet = exactNodeField(heatPump, descriptor.demandOutletPort);
        if (!supplyInlet || !supplyOutlet || !demandInlet || !demandOutlet) {
          return nullptr;
        }
        const std::array<Node, 4> ports{*supplyInlet, *supplyOutlet, *demandInlet, *demandOutlet};
        std::set<Handle> portHandles;
        for (const auto& port : ports) {
          if (!hasUniqueName(port) || !portHandles.insert(port.handle()).second) {
            return nullptr;
          }
        }

        std::vector<BranchOccurrence> occurrences;
        if (!collectOccurrences(heatPump, occurrences) || occurrences.size() != 2u) {
          return nullptr;
        }
        boost::optional<BranchOccurrence> primaryOccurrence;
        boost::optional<BranchOccurrence> sourceOccurrence;
        for (const auto& occurrence : occurrences) {
          if (occurrence.branch.extensibleGroups().size() != 1u || !hasUniqueName(occurrence.branch)) {
            return nullptr;
          }
          if (occurrence.inlet == *supplyInlet && occurrence.outlet == *supplyOutlet) {
            if (primaryOccurrence) {
              return nullptr;
            }
            primaryOccurrence = occurrence;
          } else if (occurrence.inlet == *demandInlet && occurrence.outlet == *demandOutlet) {
            if (sourceOccurrence) {
              return nullptr;
            }
            sourceOccurrence = occurrence;
          } else {
            return nullptr;
          }
        }
        if (!primaryOccurrence || !sourceOccurrence) {
          return nullptr;
        }

        const auto primaryBranchList = uniqueBranchListForBranch(targetLoopImpl.model(), primaryOccurrence->branch);
        const auto sourceBranchList = uniqueBranchListForBranch(targetLoopImpl.model(), sourceOccurrence->branch);
        if (!primaryBranchList || !sourceBranchList || *primaryBranchList == *sourceBranchList) {
          return nullptr;
        }
        const auto primaryOwner = uniquePlantLoopForBranchList(targetLoopImpl.model(), *primaryBranchList, true);
        const auto sourceOwner = uniquePlantLoopForBranchList(targetLoopImpl.model(), *sourceBranchList, false);
        if (!primaryOwner || !sourceOwner || *primaryOwner == *sourceOwner) {
          return nullptr;
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        if (targetLoop == *primaryOwner || targetLoop == *sourceOwner) {
          return nullptr;
        }
        const auto primaryTopology = observedPlantSideTopology(*primaryOwner, true);
        const auto sourceTopology = observedPlantSideTopology(*sourceOwner, false);
        const auto targetTopology = observedPlantSideTopology(targetLoop, false);
        const bool primaryPlacementSupported = primaryTopology
                                               && (std::ranges::count(primaryTopology->equipmentBranches, primaryOccurrence->branch) == 1
                                                   || primaryTopology->outletBranch == primaryOccurrence->branch);
        if (!primaryTopology || !sourceTopology || !targetTopology || primaryTopology->branchList != *primaryBranchList
            || sourceTopology->branchList != *sourceBranchList || !primaryPlacementSupported
            || std::ranges::count(sourceTopology->equipmentBranches, sourceOccurrence->branch) != 1) {
          return nullptr;
        }

        std::unique_ptr<DemandBranchRelocationPlan> plantRelocation;
        const DemandBranchRelocationPlan::ExternalRow primaryRow{primaryOccurrence->branch.handle(), primaryOccurrence->row};
        if (descriptor.componentType == HeatPumpWaterToWaterEquationFitHeating::iddObjectType()) {
          plantRelocation = DemandBranchRelocationPlan::prepareEquationFitHeatingHeatPump(
            targetLoopImpl, heatPump.cast<HeatPumpWaterToWaterEquationFitHeating>(), *sourceOwner, primaryRow);
        } else if (descriptor.componentType == HeatPumpWaterToWaterEquationFitCooling::iddObjectType()) {
          plantRelocation = DemandBranchRelocationPlan::prepareEquationFitCoolingHeatPump(
            targetLoopImpl, heatPump.cast<HeatPumpWaterToWaterEquationFitCooling>(), *sourceOwner, primaryRow);
        }
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<EquationFitHeatPumpDemandBranchAttachmentPlan>(
          new EquationFitHeatPumpDemandBranchAttachmentPlan(std::move(plantRelocation)));
      }

      explicit EquationFitHeatPumpDemandBranchAttachmentPlan(std::unique_ptr<DemandBranchRelocationPlan> plantRelocation)
        : m_plantRelocation(std::move(plantRelocation)) {}

      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      bool m_committed = false;
    };

    // Exact standalone heating- and cooling-water coils can retain their
    // air-side owner and controller while their single-component demand branch
    // moves between PlantLoops. Target representation is provisional until
    // commit; source plant, air, and controller state remain untouched during
    // preparation.
    class PlantLoop_Impl::WaterCoilDemandBranchAttachmentPlan
    {
     public:
      static std::unique_ptr<WaterCoilDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl, WaterToAirComponent coil) {
        const auto coilType = coil.iddObject().type();
        if ((coilType != CoilHeatingWater::iddObjectType() && coilType != CoilCoolingWater::iddObjectType())
            || (coil.model() != targetLoopImpl.model()) || !coil.name() || coil.containingHVACComponent()) {
          return nullptr;
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        const auto sourceLoop = coil.plantLoop();
        const auto airLoop = coil.airLoopHVAC();
        if (!sourceLoop || (*sourceLoop == targetLoop) || !airLoop || !sourceLoop->demandComponent(coil.handle())
            || targetLoopImpl.demandComponent(coil.handle())) {
          return nullptr;
        }

        const auto waterInletField = existingNodeField(coil, coil.waterInletPort());
        const auto waterOutletField = existingNodeField(coil, coil.waterOutletPort());
        const auto airInletField = existingNodeField(coil, coil.airInletPort());
        const auto airOutletField = existingNodeField(coil, coil.airOutletPort());
        if (!waterInletField.set || !waterInletField.node || !waterOutletField.set || !waterOutletField.node || !airInletField.set
            || !airInletField.node || !airOutletField.set || !airOutletField.node) {
          return nullptr;
        }

        const auto airSupplyComponents = airLoop->supplyComponents();
        if (std::ranges::count_if(airSupplyComponents, [&coil](const auto& component) { return component.handle() == coil.handle(); }) != 1) {
          return nullptr;
        }

        auto airLoopImpl = airLoop->getImpl<AirLoopHVAC_Impl>();
        OS_ASSERT(airLoopImpl);
        const auto airBranches = airLoopImpl->branchList().branches();
        std::vector<DemandBranchRelocationPlan::ExternalRow> validatedExternalRows;
        unsigned airOccurrences = 0u;
        for (const auto& branch : targetLoopImpl.model().getConcreteModelObjects<Branch>()) {
          const auto groups = branch.extensibleGroups();
          for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
            const auto componentNameIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentName));
            const auto relationship = existingObjectField(branch, componentNameIndex);
            auto branchWorkspaceImpl = branch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(branchWorkspaceImpl);
            const auto rawComponentName = branchWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(componentNameIndex, false, true);
            const auto rawComponentHandle = rawComponentName ? openstudio::toUUID(*rawComponentName) : Handle();
            const auto componentType = groups[groupIndex].getString(openstudio::BranchExtensibleFields::ComponentObjectType, false);
            const bool referencesCoil = (relationship.object && relationship.object->handle() == coil.handle())
                                        || (!rawComponentHandle.isNull() && rawComponentHandle == coil.handle())
                                        || (componentType && openstudio::istringEqual(*componentType, coil.iddObject().name()) && rawComponentName
                                            && openstudio::istringEqual(*rawComponentName, coil.nameString()));
            if (!referencesCoil) {
              continue;
            }
            if (std::ranges::find(airBranches, branch) == airBranches.end()) {
              continue;
            }
            if (!relationship.set || !relationship.object || relationship.object->handle() != coil.handle() || !componentType
                || !openstudio::istringEqual(*componentType, coil.iddObject().name())) {
              return nullptr;
            }

            const auto branchInletNodeIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentInletNodeName));
            const auto branchOutletNodeIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentOutletNodeName));
            const auto branchInletField = existingNodeField(branch, branchInletNodeIndex);
            const auto branchOutletField = existingNodeField(branch, branchOutletNodeIndex);
            if (!branchInletField.set || !branchInletField.node || !branchOutletField.set || !branchOutletField.node) {
              return nullptr;
            }

            ++airOccurrences;
            if (*branchInletField.node != *airInletField.node || *branchOutletField.node != *airOutletField.node) {
              return nullptr;
            }
            validatedExternalRows.emplace_back(branch.handle(), groupIndex);
          }
        }
        if (airOccurrences != 1u) {
          return nullptr;
        }

        boost::optional<ControllerWaterCoil> controller;
        unsigned actuatorMatches = 0u;
        unsigned controllerMatches = 0u;
        for (const auto& candidate : targetLoopImpl.model().getConcreteModelObjects<ControllerWaterCoil>()) {
          const auto actuatorNode = candidate.actuatorNode();
          const auto sensorNode = candidate.sensorNode();
          if (actuatorNode && *actuatorNode == *waterInletField.node) {
            ++actuatorMatches;
            if (sensorNode && *sensorNode == *airOutletField.node) {
              ++controllerMatches;
              controller = candidate;
            }
          }
        }
        if (actuatorMatches != 1u || controllerMatches != 1u || !controller) {
          return nullptr;
        }
        const auto controlledCoil = controller->waterCoil();
        if (!controlledCoil || controlledCoil->handle() != coil.handle()) {
          return nullptr;
        }

        const auto controllerList = airLoop->getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
        if (!controllerList || std::ranges::count_if(controllerList->controllers(), [&controller](const auto& candidate) {
                                 return candidate.handle() == controller->handle();
                               }) != 1) {
          return nullptr;
        }
        unsigned controllerListOccurrences = 0u;
        for (const auto& candidateList : targetLoopImpl.model().getConcreteModelObjects<AirLoopHVACControllerList>()) {
          controllerListOccurrences += static_cast<unsigned>(std::ranges::count_if(
            candidateList.controllers(), [&controller](const auto& candidate) { return candidate.handle() == controller->handle(); }));
        }
        if (controllerListOccurrences != 1u) {
          return nullptr;
        }

        auto plantRelocation = DemandBranchRelocationPlan::prepareWaterCoil(targetLoopImpl, coil, validatedExternalRows);
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<WaterCoilDemandBranchAttachmentPlan>(
          new WaterCoilDemandBranchAttachmentPlan(coil, *airLoop, *controller, std::move(plantRelocation)));
      }

      WaterCoilDemandBranchAttachmentPlan(const WaterCoilDemandBranchAttachmentPlan&) = delete;
      WaterCoilDemandBranchAttachmentPlan& operator=(const WaterCoilDemandBranchAttachmentPlan&) = delete;
      WaterCoilDemandBranchAttachmentPlan(WaterCoilDemandBranchAttachmentPlan&&) = delete;
      WaterCoilDemandBranchAttachmentPlan& operator=(WaterCoilDemandBranchAttachmentPlan&&) = delete;

      ~WaterCoilDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(!m_committed && m_plantRelocation);
        const auto targetInletNode = m_plantRelocation->targetInletNode();
        m_plantRelocation->commit();
        // Owner-local prepare proved this controller and its exact live
        // same-model actuator field; plant relocation has just set the coil's
        // water inlet to this Node, so the post-water write is no-fail.
        const bool actuatorSet = m_controller.setActuatorNode(targetInletNode);
        OS_ASSERT(actuatorSet);

        OS_ASSERT(m_coil.airLoopHVAC() && *m_coil.airLoopHVAC() == m_airLoop);
        OS_ASSERT(m_controller.sensorNode());
        m_committed = true;
      }

     private:
      WaterCoilDemandBranchAttachmentPlan(WaterToAirComponent coil, AirLoopHVAC airLoop, ControllerWaterCoil controller,
                                          std::unique_ptr<DemandBranchRelocationPlan> plantRelocation)
        : m_coil(std::move(coil)),
          m_airLoop(std::move(airLoop)),
          m_controller(std::move(controller)),
          m_plantRelocation(std::move(plantRelocation)) {}

      WaterToAirComponent m_coil;
      AirLoopHVAC m_airLoop;
      ControllerWaterCoil m_controller;
      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      bool m_committed = false;
    };

    // Exact heating-water coils contained by constant-volume reheat terminals
    // can move their single-component demand branch without disturbing the
    // terminal's canonical air/zone ownership. The terminal-removal plan is
    // retained only as a read-only topology proof and is never committed.
    class PlantLoop_Impl::ContainedReheatCoilDemandBranchAttachmentPlan
    {
     public:
      static std::unique_ptr<ContainedReheatCoilDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl, const CoilHeatingWater& coil) {
        if ((coil.model() != targetLoopImpl.model()) || !coil.name()) {
          return nullptr;
        }

        const auto containingComponent = coil.containingHVACComponent();
        const auto terminal = containingComponent ? containingComponent->optionalCast<AirTerminalSingleDuctConstantVolumeReheat>()
                                                  : boost::optional<AirTerminalSingleDuctConstantVolumeReheat>();
        if (!terminal || !terminal->name() || !isSoleOwnedChild(terminal->cast<ModelObject>(), coil)) {
          return nullptr;
        }

        const auto terminalCoilField = existingObjectField(*terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
        const auto terminalCoilType =
          terminal->getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, false, true);
        if (!terminalCoilField.set || !terminalCoilField.object || terminalCoilField.object->handle() != coil.handle() || !terminalCoilType
            || !openstudio::istringEqual(*terminalCoilType, coil.iddObject().name())) {
          return nullptr;
        }

        const auto targetLoop = targetLoopImpl.getObject<PlantLoop>();
        const auto sourceLoop = coil.plantLoop();
        if (!sourceLoop || (*sourceLoop == targetLoop) || !sourceLoop->demandComponent(coil.handle())
            || targetLoopImpl.demandComponent(coil.handle())) {
          return nullptr;
        }

        const auto waterInletField = existingNodeField(coil, coil.waterInletPort());
        const auto waterOutletField = existingNodeField(coil, coil.waterOutletPort());
        const auto coilAirInletField = existingNodeField(coil, coil.airInletPort());
        const auto coilAirOutletField = existingNodeField(coil, coil.airOutletPort());
        const auto terminalAirInletField = existingNodeField(*terminal, terminal->inletPort());
        const auto terminalAirOutletField = existingNodeField(*terminal, terminal->outletPort());
        if (!waterInletField.set || !waterInletField.node || !waterOutletField.set || !waterOutletField.node || !coilAirInletField.set
            || !coilAirInletField.node || !coilAirOutletField.set || !coilAirOutletField.node || !terminalAirInletField.set
            || !terminalAirInletField.node || !terminalAirOutletField.set || !terminalAirOutletField.node
            || *coilAirInletField.node != *terminalAirInletField.node || *coilAirOutletField.node != *terminalAirOutletField.node) {
          return nullptr;
        }

        boost::optional<AirLoopHVAC> airLoop;
        unsigned airLoopOccurrences = 0u;
        for (const auto& candidate : targetLoopImpl.model().getConcreteModelObjects<AirLoopHVAC>()) {
          const auto demandComponents = candidate.demandComponents();
          const auto count = static_cast<unsigned>(
            std::ranges::count_if(demandComponents, [&terminal](const auto& component) { return component.handle() == terminal->handle(); }));
          airLoopOccurrences += count;
          if (count == 1u) {
            airLoop = candidate;
          } else if (count > 1u) {
            return nullptr;
          }
        }
        if (airLoopOccurrences != 1u || !airLoop || !terminal->airLoopHVAC() || *terminal->airLoopHVAC() != *airLoop) {
          return nullptr;
        }

        boost::optional<ThermalZone> thermalZone;
        unsigned zoneEquipmentOccurrences = 0u;
        for (const auto& candidate : targetLoopImpl.model().getConcreteModelObjects<ThermalZone>()) {
          const auto equipment = candidate.equipment();
          const auto count = static_cast<unsigned>(
            std::ranges::count_if(equipment, [&terminal](const auto& object) { return object.handle() == terminal->handle(); }));
          zoneEquipmentOccurrences += count;
          if (count == 1u) {
            thermalZone = candidate;
          } else if (count > 1u) {
            return nullptr;
          }
        }
        if (zoneEquipmentOccurrences != 1u || !thermalZone || !thermalZone->airLoopHVAC() || *thermalZone->airLoopHVAC() != *airLoop) {
          return nullptr;
        }
        const auto zoneTerminals = thermalZone->airLoopHVACTerminals();
        if (std::ranges::count_if(zoneTerminals, [&terminal](const auto& candidate) { return candidate.handle() == terminal->handle(); }) != 1) {
          return nullptr;
        }

        const auto aduSources = terminal->getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit);
        if (aduSources.size() != 1u) {
          return nullptr;
        }
        const auto airDistributionUnit = aduSources.front().optionalCast<ZoneHVACAirDistributionUnit>();
        if (!airDistributionUnit || !airDistributionUnit->airTerminal() || airDistributionUnit->airTerminal()->handle() != terminal->handle()
            || !airDistributionUnit->outletNode() || *airDistributionUnit->outletNode() != *terminalAirOutletField.node) {
          return nullptr;
        }

        auto terminalAsStraight = terminal->cast<StraightComponent>();
        auto terminalTopologyProof = SingleDuctTerminalRemovalPlan::prepare(terminalAsStraight, std::vector<ModelObject>{coil.cast<ModelObject>()});
        if (!terminalTopologyProof) {
          return nullptr;
        }

        if (coil.controllerWaterCoil()) {
          return nullptr;
        }
        for (const auto& controller : targetLoopImpl.model().getConcreteModelObjects<ControllerWaterCoil>()) {
          const auto actuatorNode = controller.actuatorNode();
          if (actuatorNode && *actuatorNode == *waterInletField.node) {
            return nullptr;
          }
        }

        auto plantRelocation = DemandBranchRelocationPlan::prepareWaterCoil(targetLoopImpl, coil, {});
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<ContainedReheatCoilDemandBranchAttachmentPlan>(new ContainedReheatCoilDemandBranchAttachmentPlan(
          coil, *terminal, *airLoop, *thermalZone, *airDistributionUnit, *terminalAirInletField.node, *terminalAirOutletField.node,
          std::move(terminalTopologyProof), std::move(plantRelocation)));
      }

      ContainedReheatCoilDemandBranchAttachmentPlan(const ContainedReheatCoilDemandBranchAttachmentPlan&) = delete;
      ContainedReheatCoilDemandBranchAttachmentPlan& operator=(const ContainedReheatCoilDemandBranchAttachmentPlan&) = delete;
      ContainedReheatCoilDemandBranchAttachmentPlan(ContainedReheatCoilDemandBranchAttachmentPlan&&) = delete;
      ContainedReheatCoilDemandBranchAttachmentPlan& operator=(ContainedReheatCoilDemandBranchAttachmentPlan&&) = delete;

      ~ContainedReheatCoilDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(!m_committed && m_plantRelocation && m_terminalTopologyProof);
        m_plantRelocation->commit();

        const auto currentOwner = m_coil.containingHVACComponent();
        OS_ASSERT(currentOwner && currentOwner->handle() == m_terminal.handle());
        OS_ASSERT(m_terminal.reheatCoil().handle() == m_coil.handle());
        OS_ASSERT(m_coil.airInletModelObject() && m_coil.airInletModelObject()->handle() == m_airInletNode.handle());
        OS_ASSERT(m_coil.airOutletModelObject() && m_coil.airOutletModelObject()->handle() == m_airOutletNode.handle());
        OS_ASSERT(m_terminal.airLoopHVAC() && *m_terminal.airLoopHVAC() == m_airLoop);
        OS_ASSERT(m_thermalZone.airLoopHVAC() && *m_thermalZone.airLoopHVAC() == m_airLoop);
        OS_ASSERT(m_airDistributionUnit.airTerminal() && m_airDistributionUnit.airTerminal()->handle() == m_terminal.handle());
        OS_ASSERT(m_airDistributionUnit.outletNode() && m_airDistributionUnit.outletNode()->handle() == m_airOutletNode.handle());
        OS_ASSERT(!m_coil.controllerWaterCoil());
        m_committed = true;
      }

     private:
      ContainedReheatCoilDemandBranchAttachmentPlan(CoilHeatingWater coil, AirTerminalSingleDuctConstantVolumeReheat terminal, AirLoopHVAC airLoop,
                                                    ThermalZone thermalZone, ZoneHVACAirDistributionUnit airDistributionUnit, Node airInletNode,
                                                    Node airOutletNode, std::unique_ptr<SingleDuctTerminalRemovalPlan> terminalTopologyProof,
                                                    std::unique_ptr<DemandBranchRelocationPlan> plantRelocation)
        : m_coil(std::move(coil)),
          m_terminal(std::move(terminal)),
          m_airLoop(std::move(airLoop)),
          m_thermalZone(std::move(thermalZone)),
          m_airDistributionUnit(std::move(airDistributionUnit)),
          m_airInletNode(std::move(airInletNode)),
          m_airOutletNode(std::move(airOutletNode)),
          m_terminalTopologyProof(std::move(terminalTopologyProof)),
          m_plantRelocation(std::move(plantRelocation)) {}

      CoilHeatingWater m_coil;
      AirTerminalSingleDuctConstantVolumeReheat m_terminal;
      AirLoopHVAC m_airLoop;
      ThermalZone m_thermalZone;
      ZoneHVACAirDistributionUnit m_airDistributionUnit;
      Node m_airInletNode;
      Node m_airOutletNode;
      // Declared before relocation so rollback completes while the uncommitted
      // read-only terminal topology proof is still alive.
      std::unique_ptr<SingleDuctTerminalRemovalPlan> m_terminalTopologyProof;
      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      bool m_committed = false;
    };

    struct FourPipeZoneOwnershipSnapshot
    {
      ThermalZone zone;
      ZoneHVACEquipmentConnections connections;
      ZoneHVACEquipmentList equipmentList;
    };

    // Observe the one canonical zone registration without invoking accessors
    // that may repair missing EquipmentConnections or materialize node fields.
    boost::optional<FourPipeZoneOwnershipSnapshot> fourPipeZoneOwnershipSnapshot(const Model& model, const ZoneHVACFourPipeFanCoil& fanCoil,
                                                                                 const Node& fanCoilInlet, const Node& fanCoilOutlet) {
      const auto rawField = [](const ModelObject& owner, unsigned field) {
        auto workspaceImpl = owner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        return workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
      };
      const auto rawReferences = [](const boost::optional<std::string>& rawValue, const ModelObject& object) {
        if (!rawValue || rawValue->empty()) {
          return false;
        }
        const auto rawHandle = openstudio::toUUID(*rawValue);
        return (!rawHandle.isNull() && rawHandle == object.handle()) || openstudio::istringEqual(*rawValue, object.nameString());
      };
      const auto rawAgrees = [&rawReferences](const boost::optional<std::string>& rawValue, const ModelObject& object) {
        return !rawValue || rawValue->empty() || rawReferences(rawValue, object);
      };
      const auto nodeAliasOccurrences = [&](const ZoneHVACEquipmentConnections& connections, unsigned field, const Node& node) {
        const auto relationship = existingObjectField(connections, field);
        const auto rawTarget = rawField(connections, field);
        unsigned occurrences = 0u;
        if ((relationship.object && relationship.object->handle() == node.handle()) || rawReferences(rawTarget, node)) {
          ++occurrences;
        }

        std::set<Handle> referencedNodeLists;
        if (relationship.object) {
          if (auto nodeList = relationship.object->optionalCast<NodeList>()) {
            referencedNodeLists.insert(nodeList->handle());
          }
        }
        for (const auto& nodeList : model.getConcreteModelObjects<NodeList>()) {
          if (rawReferences(rawTarget, nodeList)) {
            referencedNodeLists.insert(nodeList.handle());
          }
        }
        for (const auto& nodeListHandle : referencedNodeLists) {
          const auto nodeListObject = model.getObject(nodeListHandle);
          const auto nodeList = nodeListObject ? nodeListObject->optionalCast<NodeList>() : boost::optional<NodeList>();
          if (!nodeList) {
            continue;
          }
          const auto groups = nodeList->extensibleGroups();
          for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
            const auto nodeField =
              nodeList->iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::NodeListExtensibleFields::NodeName));
            const auto nodeRelationship = existingObjectField(*nodeList, nodeField);
            const auto rawNode = rawField(*nodeList, nodeField);
            if ((nodeRelationship.object && nodeRelationship.object->handle() == node.handle()) || rawReferences(rawNode, node)) {
              ++occurrences;
            }
          }
        }
        return occurrences;
      };

      struct EquipmentOccurrence
      {
        ZoneHVACEquipmentList list;
      };
      std::vector<EquipmentOccurrence> equipmentOccurrences;
      for (const auto& list : model.getConcreteModelObjects<ZoneHVACEquipmentList>()) {
        const auto groups = list.extensibleGroups();
        for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
          const auto nameField =
            list.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName));
          const auto relationship = existingObjectField(list, nameField);
          const auto rawName = rawField(list, nameField);
          const auto rawType = groups[groupIndex].getString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType, false);
          if ((!relationship.object || relationship.object->handle() != fanCoil.handle()) && !rawReferences(rawName, fanCoil)) {
            continue;
          }
          if (!relationship.set || !relationship.object || relationship.object->handle() != fanCoil.handle() || !rawAgrees(rawName, fanCoil)
              || !rawType || !openstudio::istringEqual(*rawType, fanCoil.iddObject().name())) {
            return boost::none;
          }
          equipmentOccurrences.push_back(EquipmentOccurrence{list});
        }
      }
      if (equipmentOccurrences.size() != 1u) {
        return boost::none;
      }

      const auto equipmentList = equipmentOccurrences.front().list;
      std::vector<FourPipeZoneOwnershipSnapshot> ownershipMatches;
      unsigned inletOccurrences = 0u;
      unsigned exhaustOccurrences = 0u;
      for (const auto& connections : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        const auto zoneRelationship = existingObjectField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
        const auto listRelationship =
          existingObjectField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);
        const auto rawZone = rawField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
        const auto rawList = rawField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);
        const auto inletNodes =
          existingNodeCollectionField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
        const auto exhaustNodes =
          existingNodeCollectionField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);

        inletOccurrences +=
          nodeAliasOccurrences(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, fanCoilOutlet);
        exhaustOccurrences +=
          nodeAliasOccurrences(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, fanCoilInlet);

        if ((!listRelationship.object || listRelationship.object->handle() != equipmentList.handle()) && !rawReferences(rawList, equipmentList)) {
          continue;
        }
        const auto zone = zoneRelationship.object ? zoneRelationship.object->optionalCast<ThermalZone>() : boost::optional<ThermalZone>();
        if (!listRelationship.set || !listRelationship.object || listRelationship.object->handle() != equipmentList.handle()
            || !rawAgrees(rawList, equipmentList) || !zoneRelationship.set || !zone || !rawAgrees(rawZone, *zone) || !inletNodes.valid
            || !inletNodes.target || !exhaustNodes.valid || !exhaustNodes.target || std::ranges::count(inletNodes.nodes, fanCoilOutlet) != 1
            || std::ranges::count(exhaustNodes.nodes, fanCoilInlet) != 1) {
          return boost::none;
        }
        ownershipMatches.push_back(FourPipeZoneOwnershipSnapshot{*zone, connections, equipmentList});
      }
      if (ownershipMatches.size() != 1u || inletOccurrences != 1u || exhaustOccurrences != 1u) {
        return boost::none;
      }

      unsigned zoneConnectionOccurrences = 0u;
      for (const auto& connections : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        const auto zoneRelationship = existingObjectField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
        const auto rawZone = rawField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
        if ((zoneRelationship.object && zoneRelationship.object->handle() == ownershipMatches.front().zone.handle())
            || rawReferences(rawZone, ownershipMatches.front().zone)) {
          ++zoneConnectionOccurrences;
        }
      }
      if (zoneConnectionOccurrences != 1u) {
        return boost::none;
      }
      return ownershipMatches.front();
    }

    // Exact heating- and cooling-water children of an ordinary zone-owned
    // four-pipe fan coil can relocate independently. FourPipe role aliases
    // and zone registration are inspected read-only; the shared plan owns
    // only plant topology and the selected child's two water ports.
    class PlantLoop_Impl::FourPipeFanCoilDemandBranchAttachmentPlan
    {
     public:
      static std::unique_ptr<FourPipeFanCoilDemandBranchAttachmentPlan> prepare(PlantLoop_Impl& targetLoopImpl, const WaterToAirComponent& coil) {
        const auto coilType = coil.iddObject().type();
        const bool selectedHeating = coilType == CoilHeatingWater::iddObjectType();
        if ((!selectedHeating && coilType != CoilCoolingWater::iddObjectType()) || (coil.model() != targetLoopImpl.model()) || !coil.name()) {
          return nullptr;
        }

        const auto containingComponent = coil.containingHVACComponent();
        const auto fanCoil =
          containingComponent ? containingComponent->optionalCast<ZoneHVACFourPipeFanCoil>() : boost::optional<ZoneHVACFourPipeFanCoil>();
        if (!fanCoil || !fanCoil->name()) {
          return nullptr;
        }

        const auto fanField = existingObjectField(*fanCoil, openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName);
        const auto coolingField = existingObjectField(*fanCoil, openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName);
        const auto heatingField = existingObjectField(*fanCoil, openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName);
        const auto fanType = fanCoil->getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, false, true);
        const auto coolingType = fanCoil->getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, false, true);
        const auto heatingType = fanCoil->getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, false, true);
        const auto fan = fanField.object ? fanField.object->optionalCast<StraightComponent>() : boost::optional<StraightComponent>();
        const auto cooling = coolingField.object ? coolingField.object->optionalCast<CoilCoolingWater>() : boost::optional<CoilCoolingWater>();
        const auto heating = heatingField.object ? heatingField.object->optionalCast<CoilHeatingWater>() : boost::optional<CoilHeatingWater>();
        if (!fanField.set || !fan || !fanType || !openstudio::istringEqual(*fanType, fan->iddObject().name()) || !coolingField.set || !cooling
            || !coolingType || !openstudio::istringEqual(*coolingType, cooling->iddObject().name()) || !heatingField.set || !heating || !heatingType
            || !openstudio::istringEqual(*heatingType, heating->iddObject().name())
            || (selectedHeating ? heating->handle() != coil.handle() : cooling->handle() != coil.handle())) {
          return nullptr;
        }

        const auto expectedChildren = std::vector<ModelObject>{fan->cast<ModelObject>(), cooling->cast<ModelObject>(), heating->cast<ModelObject>()};
        if (fanCoil->children() != expectedChildren || !isSoleOwnedChild(fanCoil->cast<ModelObject>(), *fan)
            || !isSoleOwnedChild(fanCoil->cast<ModelObject>(), *cooling) || !isSoleOwnedChild(fanCoil->cast<ModelObject>(), *heating)) {
          return nullptr;
        }

        const std::array<std::pair<unsigned, unsigned>, 3> roleFields = {
          std::pair{openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType},
          std::pair{openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType},
          std::pair{openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType}};
        const std::array<std::pair<ModelObject, unsigned>, 3> expectedRoles = {
          std::pair{fan->cast<ModelObject>(), openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName},
          std::pair{cooling->cast<ModelObject>(), openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName},
          std::pair{heating->cast<ModelObject>(), openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName}};
        for (const auto& [expectedChild, expectedField] : expectedRoles) {
          unsigned roleOccurrences = 0u;
          for (const auto& candidate : targetLoopImpl.model().getConcreteModelObjects<ZoneHVACFourPipeFanCoil>()) {
            auto workspaceImpl = candidate.getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(workspaceImpl);
            for (const auto& [nameField, typeField] : roleFields) {
              const auto relationship = existingObjectField(candidate, nameField);
              const auto rawName = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(nameField, false, true);
              const auto rawHandle = rawName ? openstudio::toUUID(*rawName) : Handle();
              const auto rawType = candidate.getString(typeField, false, true);
              const bool rawNameSet = rawName && !rawName->empty();
              const bool rawNameMatches =
                rawName
                && ((!rawHandle.isNull() && rawHandle == expectedChild.handle()) || openstudio::istringEqual(*rawName, expectedChild.nameString()));
              if ((!relationship.object || relationship.object->handle() != expectedChild.handle()) && !rawNameMatches) {
                continue;
              }
              ++roleOccurrences;
              if (candidate.handle() != fanCoil->handle() || nameField != expectedField || !relationship.set || !relationship.object
                  || relationship.object->handle() != expectedChild.handle() || (rawNameSet && !rawNameMatches) || !rawType
                  || !openstudio::istringEqual(*rawType, expectedChild.iddObject().name())) {
                return nullptr;
              }
            }
          }
          if (roleOccurrences != 1u) {
            return nullptr;
          }
        }

        // Keep this allowlist in lockstep with
        // ZoneHVACFourPipeFanCoil_Impl::setSupplyAirFan.
        const auto fanObjectType = fan->iddObject().type();
        bool fanTypeAllowed = fanObjectType == IddObjectType::OS_Fan_SystemModel || fanObjectType == IddObjectType::Fan_SystemModel;
        if (openstudio::istringEqual(fanCoil->capacityControlMethod(), "ConstantFanVariableFlow")) {
          fanTypeAllowed = fanTypeAllowed || fanObjectType == IddObjectType::OS_Fan_ConstantVolume || fanObjectType == IddObjectType::OS_Fan_OnOff
                           || fanObjectType == IddObjectType::Fan_ConstantVolume || fanObjectType == IddObjectType::Fan_OnOff;
        } else if (openstudio::istringEqual(fanCoil->capacityControlMethod(), "CyclingFan")) {
          fanTypeAllowed = fanTypeAllowed || fanObjectType == IddObjectType::OS_Fan_OnOff || fanObjectType == IddObjectType::Fan_OnOff;
        } else if (openstudio::istringEqual(fanCoil->capacityControlMethod(), "VariableFanVariableFlow")
                   || openstudio::istringEqual(fanCoil->capacityControlMethod(), "VariableFanConstantFlow")) {
          fanTypeAllowed =
            fanTypeAllowed || fanObjectType == IddObjectType::OS_Fan_VariableVolume || fanObjectType == IddObjectType::Fan_VariableVolume;
        }
        if (!fanTypeAllowed) {
          return nullptr;
        }

        const auto fanCoilInlet = existingNodeField(*fanCoil, fanCoil->inletPort());
        const auto fanCoilOutlet = existingNodeField(*fanCoil, fanCoil->outletPort());
        const auto fanInlet = existingNodeField(*fan, fan->inletPort());
        const auto fanOutlet = existingNodeField(*fan, fan->outletPort());
        const auto coolingAirInlet = existingNodeField(*cooling, cooling->airInletPort());
        const auto coolingAirOutlet = existingNodeField(*cooling, cooling->airOutletPort());
        const auto heatingAirInlet = existingNodeField(*heating, heating->airInletPort());
        const auto heatingAirOutlet = existingNodeField(*heating, heating->airOutletPort());
        if (!fanCoilInlet.set || !fanCoilInlet.node || !fanCoilOutlet.set || !fanCoilOutlet.node || !fanInlet.set || !fanInlet.node || !fanOutlet.set
            || !fanOutlet.node || !coolingAirInlet.set || !coolingAirInlet.node || !coolingAirOutlet.set || !coolingAirOutlet.node
            || !heatingAirInlet.set || !heatingAirInlet.node || !heatingAirOutlet.set || !heatingAirOutlet.node
            || *fanCoilInlet.node != *fanInlet.node || *fanOutlet.node != *coolingAirInlet.node || *coolingAirOutlet.node != *heatingAirInlet.node
            || *heatingAirOutlet.node != *fanCoilOutlet.node
            || std::set<Handle>{fanCoilInlet.node->handle(), fanOutlet.node->handle(), coolingAirOutlet.node->handle(), fanCoilOutlet.node->handle()}
                   .size()
                 != 4u) {
          return nullptr;
        }

        if (fanCoil->airLoopHVAC() || fanCoil->airLoopHVACOutdoorAirSystem() || fan->airLoopHVAC() || fan->airLoopHVACOutdoorAirSystem()
            || cooling->airLoopHVAC() || cooling->airLoopHVACOutdoorAirSystem() || heating->airLoopHVAC() || heating->airLoopHVACOutdoorAirSystem()
            || std::ranges::any_of(fanCoilInlet.node->sources(), [](const openstudio::WorkspaceObject& source) {
                 return static_cast<bool>(source.optionalCast<AirTerminalSingleDuctInletSideMixer>());
               })) {
          return nullptr;
        }

        const auto zoneOwnership = fourPipeZoneOwnershipSnapshot(targetLoopImpl.model(), *fanCoil, *fanCoilInlet.node, *fanCoilOutlet.node);
        if (!zoneOwnership) {
          return nullptr;
        }

        const auto coolingWaterInlet = existingNodeField(*cooling, cooling->waterInletPort());
        const auto heatingWaterInlet = existingNodeField(*heating, heating->waterInletPort());
        if (!coolingWaterInlet.set || !coolingWaterInlet.node || !heatingWaterInlet.set || !heatingWaterInlet.node || cooling->controllerWaterCoil()
            || heating->controllerWaterCoil()) {
          return nullptr;
        }
        for (const auto& controller : targetLoopImpl.model().getConcreteModelObjects<ControllerWaterCoil>()) {
          const auto actuatorField = existingObjectField(controller, openstudio::Controller_WaterCoilFields::ActuatorNodeName);
          auto workspaceImpl = controller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(workspaceImpl);
          const auto rawActuator =
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Controller_WaterCoilFields::ActuatorNodeName, false, true);
          const auto rawActuatorHandle = rawActuator ? openstudio::toUUID(*rawActuator) : Handle();
          const auto referencesWaterInlet = [&](const Node& waterInlet) {
            return (actuatorField.object && actuatorField.object->handle() == waterInlet.handle())
                   || (!rawActuatorHandle.isNull() && rawActuatorHandle == waterInlet.handle())
                   || (rawActuator && openstudio::istringEqual(*rawActuator, waterInlet.nameString()));
          };
          if (referencesWaterInlet(*coolingWaterInlet.node) || referencesWaterInlet(*heatingWaterInlet.node)) {
            return nullptr;
          }
        }

        auto plantRelocation = DemandBranchRelocationPlan::prepareWaterCoil(targetLoopImpl, coil, {});
        if (!plantRelocation) {
          return nullptr;
        }
        return std::unique_ptr<FourPipeFanCoilDemandBranchAttachmentPlan>(new FourPipeFanCoilDemandBranchAttachmentPlan(
          coil, *fanCoil, zoneOwnership->zone, zoneOwnership->connections, zoneOwnership->equipmentList, *fan, *cooling, *heating, *fanCoilInlet.node,
          *fanOutlet.node, *coolingAirOutlet.node, *fanCoilOutlet.node, std::move(plantRelocation)));
      }

      FourPipeFanCoilDemandBranchAttachmentPlan(const FourPipeFanCoilDemandBranchAttachmentPlan&) = delete;
      FourPipeFanCoilDemandBranchAttachmentPlan& operator=(const FourPipeFanCoilDemandBranchAttachmentPlan&) = delete;
      FourPipeFanCoilDemandBranchAttachmentPlan(FourPipeFanCoilDemandBranchAttachmentPlan&&) = delete;
      FourPipeFanCoilDemandBranchAttachmentPlan& operator=(FourPipeFanCoilDemandBranchAttachmentPlan&&) = delete;

      ~FourPipeFanCoilDemandBranchAttachmentPlan() = default;

      void commit() {
        OS_ASSERT(!m_committed && m_plantRelocation);
        m_plantRelocation->commit();

        OS_ASSERT(m_fanCoil.model().getObject(m_thermalZone.handle()) && m_fanCoil.model().getObject(m_zoneConnections.handle())
                  && m_fanCoil.model().getObject(m_zoneEquipmentList.handle()));
        OS_ASSERT(m_coil.containingHVACComponent() && m_coil.containingHVACComponent()->handle() == m_fanCoil.handle());
        OS_ASSERT((m_coil.iddObject().type() == CoilHeatingWater::iddObjectType() && m_heating.handle() == m_coil.handle())
                  || (m_coil.iddObject().type() == CoilCoolingWater::iddObjectType() && m_cooling.handle() == m_coil.handle()));
        OS_ASSERT((m_fanCoil.children()
                   == std::vector<ModelObject>{m_fan.cast<ModelObject>(), m_cooling.cast<ModelObject>(), m_heating.cast<ModelObject>()}));
        OS_ASSERT(m_fan.inletModelObject() && m_fan.inletModelObject()->handle() == m_fanCoilInlet.handle());
        OS_ASSERT(m_fan.outletModelObject() && m_fan.outletModelObject()->handle() == m_fanOutlet.handle());
        OS_ASSERT(m_cooling.airInletModelObject() && m_cooling.airInletModelObject()->handle() == m_fanOutlet.handle());
        OS_ASSERT(m_cooling.airOutletModelObject() && m_cooling.airOutletModelObject()->handle() == m_coolingOutlet.handle());
        OS_ASSERT(m_heating.airInletModelObject() && m_heating.airInletModelObject()->handle() == m_coolingOutlet.handle());
        OS_ASSERT(m_heating.airOutletModelObject() && m_heating.airOutletModelObject()->handle() == m_fanCoilOutlet.handle());
        OS_ASSERT(!m_cooling.controllerWaterCoil() && !m_heating.controllerWaterCoil());
        m_committed = true;
      }

     private:
      FourPipeFanCoilDemandBranchAttachmentPlan(WaterToAirComponent coil, ZoneHVACFourPipeFanCoil fanCoil, ThermalZone thermalZone,
                                                ZoneHVACEquipmentConnections zoneConnections, ZoneHVACEquipmentList zoneEquipmentList,
                                                StraightComponent fan, CoilCoolingWater cooling, CoilHeatingWater heating, Node fanCoilInlet,
                                                Node fanOutlet, Node coolingOutlet, Node fanCoilOutlet,
                                                std::unique_ptr<DemandBranchRelocationPlan> plantRelocation)
        : m_coil(std::move(coil)),
          m_fanCoil(std::move(fanCoil)),
          m_thermalZone(std::move(thermalZone)),
          m_zoneConnections(std::move(zoneConnections)),
          m_zoneEquipmentList(std::move(zoneEquipmentList)),
          m_fan(std::move(fan)),
          m_cooling(std::move(cooling)),
          m_heating(std::move(heating)),
          m_fanCoilInlet(std::move(fanCoilInlet)),
          m_fanOutlet(std::move(fanOutlet)),
          m_coolingOutlet(std::move(coolingOutlet)),
          m_fanCoilOutlet(std::move(fanCoilOutlet)),
          m_plantRelocation(std::move(plantRelocation)) {}

      WaterToAirComponent m_coil;
      ZoneHVACFourPipeFanCoil m_fanCoil;
      ThermalZone m_thermalZone;
      ZoneHVACEquipmentConnections m_zoneConnections;
      ZoneHVACEquipmentList m_zoneEquipmentList;
      StraightComponent m_fan;
      CoilCoolingWater m_cooling;
      CoilHeatingWater m_heating;
      Node m_fanCoilInlet;
      Node m_fanOutlet;
      Node m_coolingOutlet;
      Node m_fanCoilOutlet;
      std::unique_ptr<DemandBranchRelocationPlan> m_plantRelocation;
      bool m_committed = false;
    };

    // Exact PipeAdiabatic equipment-branch removal is entirely read-only
    // until commit. The pipe and its existing transient nodes are retained;
    // only its proven branch row and, for a parallel path, owner-local branch
    // representation are removed.
    class PlantLoop_Impl::PipeBranchRemovalPlan
    {
     public:
      static std::unique_ptr<PipeBranchRemovalPlan> prepare(PlantLoop_Impl& plantLoopImpl, const PipeAdiabatic& pipe, bool supplySide) {
        const auto plantLoop = plantLoopImpl.getObject<PlantLoop>();
        if ((pipe.model() != plantLoopImpl.model()) || !pipe.name() || pipe.containingHVACComponent() || pipe.airLoopHVAC()) {
          return nullptr;
        }

        const auto owningPlantLoop = pipe.plantLoop();
        const auto owningLoop = pipe.loop();
        if (!owningPlantLoop || (*owningPlantLoop != plantLoop) || !owningLoop || (*owningLoop != plantLoop)
            || (supplySide ? !plantLoopImpl.supplyComponent(pipe.handle()) : !plantLoopImpl.demandComponent(pipe.handle()))) {
          return nullptr;
        }

        const auto inletField = existingNodeField(pipe, pipe.inletPort());
        const auto outletField = existingNodeField(pipe, pipe.outletPort());
        if (!inletField.set || !inletField.node || !outletField.set || !outletField.node) {
          return nullptr;
        }

        auto branchList = supplySide ? plantLoopImpl.supplyBranchList() : plantLoopImpl.demandBranchList();
        const auto equipmentBranches = supplySide ? plantLoopImpl.supplyEquipmentBranches() : plantLoopImpl.demandEquipmentBranches();
        if (equipmentBranches.empty()) {
          return nullptr;
        }

        boost::optional<Branch> targetBranch;
        unsigned targetOccurrences = 0u;
        for (const auto& branch : plantLoopImpl.model().getConcreteModelObjects<Branch>()) {
          const auto groups = branch.extensibleGroups();
          for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
            const auto componentNameIndex =
              branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentName));
            const auto relationship = existingObjectField(branch, componentNameIndex);
            auto branchWorkspaceImpl = branch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(branchWorkspaceImpl);
            const auto rawComponentName = branchWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(componentNameIndex, false, true);
            const auto rawComponentHandle = rawComponentName ? openstudio::toUUID(*rawComponentName) : Handle();
            const auto componentType = groups[groupIndex].getString(openstudio::BranchExtensibleFields::ComponentObjectType, false);
            const bool referencesPipe = (relationship.object && (relationship.object->handle() == pipe.handle()))
                                        || (!rawComponentHandle.isNull() && (rawComponentHandle == pipe.handle()))
                                        || (componentType && openstudio::istringEqual(*componentType, pipe.iddObject().name()) && rawComponentName
                                            && openstudio::istringEqual(*rawComponentName, pipe.nameString()));
            if (!referencesPipe) {
              continue;
            }

            ++targetOccurrences;
            if (!relationship.set || !relationship.object || (relationship.object->handle() != pipe.handle()) || !componentType
                || !openstudio::istringEqual(*componentType, pipe.iddObject().name())) {
              return nullptr;
            }
            if (std::ranges::find(equipmentBranches, branch) == equipmentBranches.end()) {
              return nullptr;
            }
            targetBranch = branch;
          }
        }
        if ((targetOccurrences != 1u) || !targetBranch || (targetBranch->extensibleGroups().size() != 1u)) {
          return nullptr;
        }

        const auto branchInletNodeIndex =
          targetBranch->iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentInletNodeName));
        const auto branchOutletNodeIndex =
          targetBranch->iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentOutletNodeName));
        const auto branchInletField = existingNodeField(*targetBranch, branchInletNodeIndex);
        const auto branchOutletField = existingNodeField(*targetBranch, branchOutletNodeIndex);
        if (!branchInletField.set || !branchInletField.node || !branchOutletField.set || !branchOutletField.node
            || (*branchInletField.node != *inletField.node) || (*branchOutletField.node != *outletField.node)) {
          return nullptr;
        }

        const auto listedBranches = branchList.branches();
        const auto inletBranch = supplySide ? plantLoopImpl.supplyInletBranch() : plantLoopImpl.demandInletBranch();
        const auto outletBranch = supplySide ? plantLoopImpl.supplyOutletBranch() : plantLoopImpl.demandOutletBranch();
        if ((listedBranches.size() != equipmentBranches.size() + 2u) || (listedBranches.front() != inletBranch)
            || (listedBranches.back() != outletBranch) || (std::ranges::count(listedBranches, *targetBranch) != 1)) {
          return nullptr;
        }
        for (unsigned i = 0u; i < equipmentBranches.size(); ++i) {
          if (listedBranches[i + 1u] != equipmentBranches[i]) {
            return nullptr;
          }
        }

        auto splitter = (supplySide ? plantLoopImpl.supplySplitter() : plantLoopImpl.demandSplitter()).cast<ConnectorSplitter>();
        auto mixer = (supplySide ? plantLoopImpl.supplyMixer() : plantLoopImpl.demandMixer()).cast<ConnectorMixer>();
        const auto splitterInletBranch = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
        const auto mixerOutletBranch = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
        if (!splitterInletBranch || (*splitterInletBranch != inletBranch) || !mixerOutletBranch || (*mixerOutletBranch != outletBranch)
            || (splitter.nextBranchIndex() != equipmentBranches.size()) || (mixer.nextBranchIndex() != equipmentBranches.size())) {
          return nullptr;
        }
        for (unsigned i = 0u; i < equipmentBranches.size(); ++i) {
          const auto splitterBranch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
          const auto mixerBranch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
          if (!splitterBranch || (*splitterBranch != equipmentBranches[i]) || !mixerBranch || (*mixerBranch != equipmentBranches[i])) {
            return nullptr;
          }
        }

        return std::unique_ptr<PipeBranchRemovalPlan>(
          new PipeBranchRemovalPlan(plantLoop, pipe, supplySide, branchList, splitter, mixer, *targetBranch, equipmentBranches.size() == 1u,
                                    !plantLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)));
      }

      PipeBranchRemovalPlan(const PipeBranchRemovalPlan&) = delete;
      PipeBranchRemovalPlan& operator=(const PipeBranchRemovalPlan&) = delete;
      PipeBranchRemovalPlan(PipeBranchRemovalPlan&&) = delete;
      PipeBranchRemovalPlan& operator=(PipeBranchRemovalPlan&&) = delete;

      void commit() {
        OS_ASSERT(m_prepared && !m_committed);

        const bool inletCleared = m_pipe.setPointer(m_pipe.inletPort(), Handle());
        const bool outletCleared = m_pipe.setPointer(m_pipe.outletPort(), Handle());
        OS_ASSERT(inletCleared && outletCleared);

        if (!m_keepAsDefaultBranch) {
          auto branchListImpl = m_branchList.getImpl<BranchList_Impl>();
          OS_ASSERT(branchListImpl);
          const bool removedBranchFromList = branchListImpl->removeBranch(m_branch);
          OS_ASSERT(removedBranchFromList);
        }

        auto branchImpl = m_branch.getImpl<Branch_Impl>();
        OS_ASSERT(branchImpl);
        branchImpl->clearComponents();

        if (!m_keepAsDefaultBranch) {
          m_branch.remove();
          OS_ASSERT(!m_plantLoop.model().getObject(m_branch.handle()));
        }

        auto plantLoopImpl = m_plantLoop.getImpl<PlantLoop_Impl>();
        const auto equipmentBranches = m_supplySide ? plantLoopImpl->supplyEquipmentBranches() : plantLoopImpl->demandEquipmentBranches();
        const bool synchronized = m_supplySide ? plantLoopImpl->syncConnectorPorts(m_splitter, m_mixer, plantLoopImpl->supplyInletBranch(),
                                                                                   plantLoopImpl->supplyOutletBranch(), equipmentBranches)
                                               : plantLoopImpl->syncConnectorPorts(m_splitter, m_mixer, plantLoopImpl->demandInletBranch(),
                                                                                   plantLoopImpl->demandOutletBranch(), equipmentBranches);
        OS_ASSERT(synchronized);

        if (m_repairSetpointTarget) {
          const bool repairedSetpointTarget = plantLoopImpl->setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName,
                                                                        plantLoopImpl->supplyOutletNode().handle(), false);
          OS_ASSERT(repairedSetpointTarget);
        }

        m_committed = true;
      }

     private:
      PipeBranchRemovalPlan(PlantLoop plantLoop, PipeAdiabatic pipe, bool supplySide, BranchList branchList, ConnectorSplitter splitter,
                            ConnectorMixer mixer, Branch branch, bool keepAsDefaultBranch, bool repairSetpointTarget)
        : m_plantLoop(std::move(plantLoop)),
          m_pipe(std::move(pipe)),
          m_supplySide(supplySide),
          m_branchList(std::move(branchList)),
          m_splitter(std::move(splitter)),
          m_mixer(std::move(mixer)),
          m_branch(std::move(branch)),
          m_keepAsDefaultBranch(keepAsDefaultBranch),
          m_repairSetpointTarget(repairSetpointTarget) {}

      PlantLoop m_plantLoop;
      PipeAdiabatic m_pipe;
      bool m_supplySide;
      BranchList m_branchList;
      ConnectorSplitter m_splitter;
      ConnectorMixer m_mixer;
      Branch m_branch;
      bool m_keepAsDefaultBranch;
      bool m_repairSetpointTarget;
      bool m_prepared = true;
      bool m_committed = false;
    };

    struct PlantLoop_Impl::DemandBranchRemovalPlan::State
    {
      PlantLoop plantLoop;
      HVACComponent component;
      unsigned inletPort;
      unsigned outletPort;
      bool waterToAirComponent;
      DemandBranchPostDisconnectUpdate postDisconnectUpdate;
      Branch branch;
      BranchList branchList;
      ConnectorSplitter splitter;
      ConnectorMixer mixer;
      bool keepAsDefaultBranch;
    };

    PlantLoop_Impl::DemandBranchRemovalPlan::DemandBranchRemovalPlan(std::unique_ptr<State> state) : m_state(std::move(state)) {
      OS_ASSERT(m_state);
    }

    PlantLoop_Impl::DemandBranchRemovalPlan::~DemandBranchRemovalPlan() = default;

    void PlantLoop_Impl::DemandBranchRemovalPlan::commit() {
      OS_ASSERT(m_state);
      OS_ASSERT(!m_committed);

      auto plantLoopImpl = m_state->plantLoop.getImpl<PlantLoop_Impl>();
      OS_ASSERT(plantLoopImpl);

      if (m_state->waterToAirComponent) {
        auto coil = m_state->component.cast<WaterToAirComponent>();
        const bool removedCoilFromBranch = coil.removeFromPlantLoop();
        OS_ASSERT(removedCoilFromBranch);
        coil.disconnectWaterSide();
        if (!coil.airLoopHVAC() && !coil.containingHVACComponent()) {
          coil.remove();
        }
      } else {
        const bool inletCleared = m_state->component.setPointer(m_state->inletPort, Handle());
        const bool outletCleared = m_state->component.setPointer(m_state->outletPort, Handle());
        OS_ASSERT(inletCleared && outletCleared);
        if (m_state->postDisconnectUpdate == DemandBranchPostDisconnectUpdate::ChillerCondenserAirCooled) {
          auto chiller = m_state->component.cast<ChillerElectricEIR>();
          const bool resetCondenserType = chiller.setCondenserType("AirCooled");
          OS_ASSERT(resetCondenserType);
        } else if (m_state->postDisconnectUpdate == DemandBranchPostDisconnectUpdate::PlantLoopEIRHeatPumpAirSource) {
          bool resetCondenserType = false;
          if (m_state->component.iddObject().type() == HeatPumpPlantLoopEIRHeating::iddObjectType()) {
            resetCondenserType = m_state->component.cast<HeatPumpPlantLoopEIRHeating>().setCondenserType("AirSource");
          } else {
            OS_ASSERT(m_state->component.iddObject().type() == HeatPumpPlantLoopEIRCooling::iddObjectType());
            resetCondenserType = m_state->component.cast<HeatPumpPlantLoopEIRCooling>().setCondenserType("AirSource");
          }
          // Exact preparation proved the same-model concrete heat-pump type
          // and SourceSide fields. Once those fields are cleared, AirSource is
          // the concrete setter's canonical no-fail state transition.
          OS_ASSERT(resetCondenserType);
        }
      }

      if (!m_state->keepAsDefaultBranch) {
        auto branchListImpl = m_state->branchList.getImpl<BranchList_Impl>();
        OS_ASSERT(branchListImpl);
        const bool removedBranchFromList = branchListImpl->removeBranch(m_state->branch);
        OS_ASSERT(removedBranchFromList);
      }

      auto branchImpl = m_state->branch.getImpl<Branch_Impl>();
      OS_ASSERT(branchImpl);
      branchImpl->clearComponents();

      if (!m_state->keepAsDefaultBranch) {
        m_state->branch.remove();
        OS_ASSERT(!m_state->plantLoop.model().getObject(m_state->branch.handle()));
      }

      const bool synchronizedConnectors =
        plantLoopImpl->syncConnectorPorts(m_state->splitter, m_state->mixer, plantLoopImpl->demandInletBranch(), plantLoopImpl->demandOutletBranch(),
                                          plantLoopImpl->demandEquipmentBranches());
      OS_ASSERT(synchronizedConnectors);

      if (!m_state->plantLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        const bool repairedSetpointNode =
          plantLoopImpl->setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, plantLoopImpl->supplyOutletNode().handle(), false);
        OS_ASSERT(repairedSetpointNode);
      }

      m_committed = true;
    }

    // PlantLoop stores its topology in EnergyPlus branch/connective-tissue objects,
    // but the API we are trying to preserve is the higher-level OpenStudio loop API.
    // This helper keeps the two representations aligned after canonicalization and
    // after branch edits. The BranchList is the source of truth: one inlet branch,
    // one or more equipment branches in the middle, and one outlet branch. The
    // splitter and mixer are rebuilt to match that ordering exactly.
    bool PlantLoop_Impl::syncConnectorPorts(ConnectorSplitter& splitter, ConnectorMixer& mixer, const Branch& inletBranch, const Branch& outletBranch,
                                            const std::vector<Branch>& equipmentBranches) const {
      if (!splitter.getImpl<openstudio::epmodel::detail::ConnectorSplitter_Impl>()->setInletBranch(inletBranch)) {
        return false;
      }
      if (!mixer.getImpl<openstudio::epmodel::detail::ConnectorMixer_Impl>()->setOutletBranch(outletBranch)) {
        return false;
      }

      while (splitter.nextBranchIndex() > equipmentBranches.size()) {
        splitter.removePortForBranch(splitter.nextBranchIndex() - 1u);
      }
      while (mixer.nextBranchIndex() > equipmentBranches.size()) {
        mixer.removePortForBranch(mixer.nextBranchIndex() - 1u);
      }

      for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
        if (!splitter.setOutletModelObject(i, equipmentBranches[i].cast<ModelObject>())) {
          return false;
        }
        if (!mixer.setInletModelObject(i, equipmentBranches[i].cast<ModelObject>())) {
          return false;
        }
      }

      return true;
    }

    // Nodes on a PlantLoop are resolved back to a Branch so higher-level APIs can
    // answer questions like "which branch am I on?" and remove a branch by giving
    // one of its nodes. Empty equipment branches are represented by a transient
    // branch node, while inlet and outlet branches fall back to the loop endpoint
    // nodes when they do not yet contain real components.
    boost::optional<Branch> PlantLoop_Impl::supplyBranchForNode(const Node& node) const {
      const auto inletBranch = supplyInletBranch();
      const auto outletBranch = supplyOutletBranch();
      const auto equipmentBranches = supplyEquipmentBranches();
      const auto inletNode = supplyInletNode();
      const auto outletNode = supplyOutletNode();

      if (branchContainsNode(model(), inletBranch, node, inletNode, outletNode, true, false, false)) {
        return inletBranch;
      }

      for (const auto& branch : equipmentBranches) {
        if (branchContainsNode(model(), branch, node, inletNode, outletNode, false, false, true)) {
          return branch;
        }
      }

      if (branchContainsNode(model(), outletBranch, node, inletNode, outletNode, false, true, false)) {
        return outletBranch;
      }

      return boost::none;
    }

    // Demand-side branch lookup follows the same rules as plant side. Keeping the
    // logic parallel makes it easier to reason about supply and demand behavior
    // together when topology repair or traversal changes.
    boost::optional<Branch> PlantLoop_Impl::demandBranchForNode(const Node& node) const {
      const auto inletBranch = demandInletBranch();
      const auto outletBranch = demandOutletBranch();
      const auto equipmentBranches = demandEquipmentBranches();
      const auto inletNode = demandInletNode();
      const auto outletNode = demandOutletNode();

      if (branchContainsNode(model(), inletBranch, node, inletNode, outletNode, true, false, false)) {
        return inletBranch;
      }

      for (const auto& branch : equipmentBranches) {
        if (branchContainsNode(model(), branch, node, inletNode, outletNode, false, false, true)) {
          return branch;
        }
      }

      if (branchContainsNode(model(), outletBranch, node, inletNode, outletNode, false, true, false)) {
        return outletBranch;
      }

      return boost::none;
    }

    Node PlantLoop_Impl::supplyInletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::PlantSideInletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    Node PlantLoop_Impl::supplyOutletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::PlantSideOutletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<Node> PlantLoop_Impl::supplyOutletNodes() const {
      return {supplyOutletNode()};
    }

    Node PlantLoop_Impl::demandInletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::DemandSideInletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<Node> PlantLoop_Impl::demandInletNodes() const {
      return {demandInletNode()};
    }

    Node PlantLoop_Impl::demandOutletNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::DemandSideOutletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    BranchList PlantLoop_Impl::supplyBranchList() const {
      auto branchList = getObject<PlantLoop>().getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
      OS_ASSERT(branchList);
      return *branchList;
    }

    BranchList PlantLoop_Impl::demandBranchList() const {
      auto branchList = getObject<PlantLoop>().getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
      OS_ASSERT(branchList);
      return *branchList;
    }

    Branch PlantLoop_Impl::supplyInletBranch() const {
      const auto branches = supplyBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.front();
    }

    Branch PlantLoop_Impl::supplyOutletBranch() const {
      const auto branches = supplyBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.back();
    }

    Branch PlantLoop_Impl::demandInletBranch() const {
      const auto branches = demandBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.front();
    }

    Branch PlantLoop_Impl::demandOutletBranch() const {
      const auto branches = demandBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return branches.back();
    }

    std::vector<Branch> PlantLoop_Impl::supplyEquipmentBranches() const {
      auto branches = supplyBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return std::vector<Branch>(std::next(branches.begin()), std::prev(branches.end()));
    }

    std::vector<Branch> PlantLoop_Impl::demandEquipmentBranches() const {
      auto branches = demandBranchList().branches();
      OS_ASSERT(branches.size() >= 3u);
      return std::vector<Branch>(std::next(branches.begin()), std::prev(branches.end()));
    }

    Splitter PlantLoop_Impl::supplySplitter() const {
      const auto inletBranch = supplyInletBranch();
      const auto equipmentBranches = supplyEquipmentBranches();
      boost::optional<ConnectorSplitter> result;
      for (const auto& splitter : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
        if (!inlet || !(*inlet == inletBranch)) {
          continue;
        }

        if (splitter.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          result = splitter;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Mixer PlantLoop_Impl::supplyMixer() const {
      const auto outletBranch = supplyOutletBranch();
      const auto equipmentBranches = supplyEquipmentBranches();
      boost::optional<ConnectorMixer> result;
      for (const auto& mixer : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
        if (!outlet || !(*outlet == outletBranch)) {
          continue;
        }

        if (mixer.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          result = mixer;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Splitter PlantLoop_Impl::demandSplitter() const {
      const auto inletBranch = demandInletBranch();
      const auto equipmentBranches = demandEquipmentBranches();
      boost::optional<ConnectorSplitter> result;
      for (const auto& splitter : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
        if (!inlet || !(*inlet == inletBranch)) {
          continue;
        }

        if (splitter.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          result = splitter;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Mixer PlantLoop_Impl::demandMixer() const {
      const auto outletBranch = demandOutletBranch();
      const auto equipmentBranches = demandEquipmentBranches();
      boost::optional<ConnectorMixer> result;
      for (const auto& mixer : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
        if (!outlet || !(*outlet == outletBranch)) {
          continue;
        }

        if (mixer.nextBranchIndex() != equipmentBranches.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
          auto branch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
          if (!branch || !(*branch == equipmentBranches[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          result = mixer;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    std::vector<ModelObject> PlantLoop_Impl::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                              openstudio::IddObjectType type) const {
      AdjacencyBuilder builder;
      const auto supplyInlet = supplyInletNode().cast<ModelObject>();
      const auto splitter = supplySplitter().cast<ModelObject>();
      const auto mixer = supplyMixer().cast<ModelObject>();
      const auto supplyOutlet = supplyOutletNode().cast<ModelObject>();

      ModelObject previousObject = supplyInlet;
      {
        const auto branch = supplyInletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != splitter) {
        builder.addLink(previousObject, splitter);
      }

      for (const auto& branch : supplyEquipmentBranches()) {
        previousObject = splitter;
        const auto components = projectedBranchComponents(branch);
        if (components.empty()) {
          const auto branchNode = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node").cast<ModelObject>();
          if (previousObject != branchNode) {
            builder.addLink(previousObject, branchNode);
          }
          previousObject = branchNode;
        } else {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }

        if (previousObject != mixer) {
          builder.addLink(previousObject, mixer);
        }
      }

      previousObject = mixer;
      {
        const auto branch = supplyOutletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != supplyOutlet) {
        builder.addLink(previousObject, supplyOutlet);
      }

      auto pathObjects = builder.walkPath(model(), inletComp, outletComp);
      if (type == openstudio::IddObjectType::Catchall) {
        return pathObjects;
      }

      std::vector<ModelObject> filtered;
      filtered.reserve(pathObjects.size());
      for (const auto& object : pathObjects) {
        if (object.iddObject().type() == type) {
          filtered.push_back(object);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> PlantLoop_Impl::supplyComponents(openstudio::IddObjectType type) const {
      return supplyComponents(supplyInletNode(), supplyOutletNode(), type);
    }

    std::vector<ModelObject> PlantLoop_Impl::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                              openstudio::IddObjectType type) const {
      AdjacencyBuilder builder;
      const auto demandInlet = demandInletNode().cast<ModelObject>();
      const auto splitter = demandSplitter().cast<ModelObject>();
      const auto mixer = demandMixer().cast<ModelObject>();
      const auto demandOutlet = demandOutletNode().cast<ModelObject>();

      ModelObject previousObject = demandInlet;
      {
        const auto branch = demandInletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != splitter) {
        builder.addLink(previousObject, splitter);
      }

      for (const auto& branch : demandEquipmentBranches()) {
        previousObject = splitter;
        const auto components = projectedBranchComponents(branch);
        if (components.empty()) {
          const auto branchNode = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node").cast<ModelObject>();
          if (previousObject != branchNode) {
            builder.addLink(previousObject, branchNode);
          }
          previousObject = branchNode;
        } else {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }

        if (previousObject != mixer) {
          builder.addLink(previousObject, mixer);
        }
      }

      previousObject = mixer;
      {
        const auto branch = demandOutletBranch();
        const auto components = projectedBranchComponents(branch);
        if (!components.empty()) {
          if (auto inletNode = branch.componentInletNode(0u)) {
            if (previousObject != inletNode->cast<ModelObject>()) {
              builder.addLink(previousObject, inletNode->cast<ModelObject>());
            }
            previousObject = inletNode->cast<ModelObject>();
          }

          for (unsigned i = 0; i < components.size(); ++i) {
            if (previousObject != components[i]) {
              builder.addLink(previousObject, components[i]);
            }
            previousObject = components[i];

            if (auto outletNode = branch.componentOutletNode(i)) {
              if (previousObject != outletNode->cast<ModelObject>()) {
                builder.addLink(previousObject, outletNode->cast<ModelObject>());
              }
              previousObject = outletNode->cast<ModelObject>();
            }
          }
        }
      }

      if (previousObject != demandOutlet) {
        builder.addLink(previousObject, demandOutlet);
      }

      auto pathObjects = builder.walkPath(model(), inletComp, outletComp);
      if (type == openstudio::IddObjectType::Catchall) {
        return pathObjects;
      }

      std::vector<ModelObject> filtered;
      filtered.reserve(pathObjects.size());
      for (const auto& object : pathObjects) {
        if (object.iddObject().type() == type) {
          filtered.push_back(object);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> PlantLoop_Impl::demandComponents(openstudio::IddObjectType type) const {
      return demandComponents(demandInletNode(), demandOutletNode(), type);
    }

    std::vector<IdfObject> PlantLoop_Impl::remove() {
      std::vector<IdfObject> result;
      auto plantLoop = getObject<PlantLoop>();
      const auto owningModel = model();

      const auto appendRemoved = [&result](std::vector<IdfObject>&& removed) { result.insert(result.end(), removed.begin(), removed.end()); };

      const auto supplyBranches = supplyBranchList().branches();
      const auto demandBranches = demandBranchList().branches();
      for (const auto& storage : model().getConcreteModelObjects<ThermalStorageChilledWaterStratified>()) {
        const bool selectedStorageEvidence =
          ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::hasBranchEvidence(storage, supplyBranches)
          || ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::hasBranchEvidence(storage, demandBranches);
        if (selectedStorageEvidence && !ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::provenOwnershipForRemoval(storage)) {
          return {};
        }
      }
      enum class SelectedWaterToWaterOwner
      {
        Supply,
        SecondarySupply,
        SecondaryDemand,
        TertiarySupply,
        TertiaryDemand,
      };
      struct SelectedWaterToWaterComponent
      {
        WaterToWaterComponent component;
        SelectedWaterToWaterOwner owner;
        bool retained;
        boost::optional<WaterHeaterSizing> ownedSizing;
      };
      std::vector<WaterToAirComponent> retainedWaterCoils;
      std::vector<SelectedWaterToWaterComponent> selectedWaterToWaterComponents;
      size_t ownedSupplyStraightComponentCount = 0u;
      size_t ownedDemandStraightComponentCount = 0u;
      size_t selectedSpecializedComponentCount = 0u;
      bool rejectedExactThermalStorage = false;
      const auto hasOnlySelectedComponents = [&](const auto& branches, bool supplySide) {
        for (const auto& branch : branches) {
          for (const auto& component : branch.components()) {
            auto straightComponent = component.template optionalCast<StraightComponent>();
            if (straightComponent) {
              if (straightComponent->containingHVACComponent() || !straightComponent->children().empty()) {
                return false;
              }
              auto componentPlantLoop = straightComponent->plantLoop();
              if (!componentPlantLoop || *componentPlantLoop != plantLoop) {
                return false;
              }
              if (supplySide) {
                ++ownedSupplyStraightComponentCount;
              } else {
                ++ownedDemandStraightComponentCount;
              }
              continue;
            }

            auto waterCoil = component.template optionalCast<WaterToAirComponent>();
            const bool isSelectedWaterCoil =
              component.template optionalCast<CoilHeatingWater>() || component.template optionalCast<CoilCoolingWater>();
            if (waterCoil && isSelectedWaterCoil) {
              if (supplySide || waterCoil->containingHVACComponent() || !waterCoil->children().empty()) {
                return false;
              }
              auto componentPlantLoop = waterCoil->plantLoop();
              auto componentAirLoop = waterCoil->airLoopHVAC();
              if (!componentPlantLoop || *componentPlantLoop != plantLoop || !componentAirLoop) {
                return false;
              }
              ++selectedSpecializedComponentCount;
              if (std::ranges::none_of(retainedWaterCoils, [&waterCoil](const auto& existing) { return existing.handle() == waterCoil->handle(); })) {
                retainedWaterCoils.push_back(*waterCoil);
              }
              continue;
            }

            auto waterToWaterComponent = component.template optionalCast<WaterToWaterComponent>();
            const auto waterHeaterMixed = component.template optionalCast<WaterHeaterMixed>();
            const auto waterHeaterStratified = component.template optionalCast<WaterHeaterStratified>();
            const bool isSelectedWaterHeater = waterHeaterMixed || waterHeaterStratified;
            const auto thermalStorage = component.template optionalCast<ThermalStorageChilledWaterStratified>();
            const auto thermalStorageOwnership =
              thermalStorage ? ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::provenOwnershipForRemoval(*thermalStorage)
                             : boost::none;
            if (thermalStorage && !thermalStorageOwnership) {
              rejectedExactThermalStorage = true;
              return false;
            }
            const auto children = thermalStorage ? std::vector<ModelObject>{thermalStorageOwnership->sizing.template cast<ModelObject>()}
                                                 : (waterToWaterComponent ? waterToWaterComponent->children() : std::vector<ModelObject>{});
            const bool hasSelectedWaterHeaterChild =
              isSelectedWaterHeater && (children.size() == 1u) && (children.front().iddObject().type() == WaterHeaterSizing::iddObjectType());
            const bool hasSelectedThermalStorageChild =
              thermalStorage && (children.size() == 1u) && (children.front().iddObject().type() == WaterHeaterSizing::iddObjectType());
            if (!waterToWaterComponent || (!thermalStorage && waterToWaterComponent->containingHVACComponent())
                || (!children.empty() && !hasSelectedWaterHeaterChild && !hasSelectedThermalStorageChild)) {
              return false;
            }

            auto primaryLoop = thermalStorage ? thermalStorageOwnership->primaryOwner : waterToWaterComponent->plantLoop();
            auto secondaryLoop = thermalStorage ? thermalStorageOwnership->sourceOwner : waterToWaterComponent->secondaryPlantLoop();
            auto tertiaryLoop = thermalStorage ? boost::optional<PlantLoop>{} : waterToWaterComponent->tertiaryPlantLoop();
            bool retained = false;
            auto selectedOwner = supplySide ? SelectedWaterToWaterOwner::Supply : SelectedWaterToWaterOwner::SecondaryDemand;
            if (thermalStorage) {
              if (supplySide && primaryLoop && (*primaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = static_cast<bool>(secondaryLoop);
              } else if (!supplySide && secondaryLoop && (*secondaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = static_cast<bool>(primaryLoop);
              } else {
                rejectedExactThermalStorage = true;
                return false;
              }
            } else if (component.template optionalCast<HeatExchangerFluidToFluid>()) {
              if (tertiaryLoop) {
                return false;
              }
              retained = supplySide ? static_cast<bool>(secondaryLoop) : static_cast<bool>(primaryLoop);
              if ((supplySide && (!primaryLoop || (*primaryLoop != plantLoop))) || (!supplySide && (!secondaryLoop || (*secondaryLoop != plantLoop)))
                  || (primaryLoop && secondaryLoop && (*primaryLoop == *secondaryLoop)) || (!supplySide && !retained)) {
                return false;
              }
            } else if (component.template optionalCast<HeatPumpWaterToWaterEquationFitHeating>()) {
              if (tertiaryLoop) {
                return false;
              }
              if (supplySide) {
                if (!primaryLoop || (*primaryLoop != plantLoop) || (secondaryLoop && (*primaryLoop == *secondaryLoop))) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = static_cast<bool>(secondaryLoop);
              } else if (secondaryLoop && (*secondaryLoop == plantLoop) && (!primaryLoop || (*primaryLoop != *secondaryLoop))) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = static_cast<bool>(primaryLoop);
              } else {
                return false;
              }
            } else if (component.template optionalCast<HeatPumpWaterToWaterEquationFitCooling>()) {
              if (tertiaryLoop) {
                return false;
              }
              if (supplySide) {
                if (!primaryLoop || (*primaryLoop != plantLoop) || (secondaryLoop && (*primaryLoop == *secondaryLoop))) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = static_cast<bool>(secondaryLoop);
              } else if (secondaryLoop && (*secondaryLoop == plantLoop) && (!primaryLoop || (*primaryLoop != *secondaryLoop))) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = static_cast<bool>(primaryLoop);
              } else {
                return false;
              }
            } else if (component.template optionalCast<ChillerElectricEIR>()) {
              if ((primaryLoop && secondaryLoop && (*primaryLoop == *secondaryLoop))
                  || (primaryLoop && tertiaryLoop && (*primaryLoop == *tertiaryLoop))
                  || (secondaryLoop && tertiaryLoop && (*secondaryLoop == *tertiaryLoop))) {
                return false;
              }
              if (supplySide && primaryLoop && (*primaryLoop == plantLoop)) {
                const bool hasBothDemandOwners = secondaryLoop && tertiaryLoop;
                const bool hasNoDemandOwners = !secondaryLoop && !tertiaryLoop;
                if (!hasBothDemandOwners && !hasNoDemandOwners) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = hasBothDemandOwners;
              } else if (!supplySide && primaryLoop && secondaryLoop && (*secondaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = true;
              } else if (!supplySide && primaryLoop && secondaryLoop && tertiaryLoop && (*tertiaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::TertiaryDemand;
                retained = true;
              } else {
                return false;
              }
            } else if (component.template optionalCast<ChillerElectricReformulatedEIR>()) {
              if ((primaryLoop && secondaryLoop && (*primaryLoop == *secondaryLoop))
                  || (primaryLoop && tertiaryLoop && (*primaryLoop == *tertiaryLoop))
                  || (secondaryLoop && tertiaryLoop && (*secondaryLoop == *tertiaryLoop))) {
                return false;
              }
              if (supplySide && primaryLoop && (*primaryLoop == plantLoop)) {
                const bool hasBothDemandOwners = secondaryLoop && tertiaryLoop;
                const bool hasNoDemandOwners = !secondaryLoop && !tertiaryLoop;
                if (!hasBothDemandOwners && !hasNoDemandOwners) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = hasBothDemandOwners;
              } else if (!supplySide && secondaryLoop && (*secondaryLoop == plantLoop)) {
                const bool hasPrimaryOwner = static_cast<bool>(primaryLoop);
                const bool isOnlySecondaryOwner = !primaryLoop && !tertiaryLoop;
                if (!hasPrimaryOwner && !isOnlySecondaryOwner) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = !isOnlySecondaryOwner;
              } else if (!supplySide && secondaryLoop && tertiaryLoop && (*tertiaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::TertiaryDemand;
                retained = true;
              } else {
                return false;
              }
            } else if (component.template optionalCast<CentralHeatPumpSystem>()) {
              if ((primaryLoop && secondaryLoop && (*primaryLoop == *secondaryLoop))
                  || (primaryLoop && tertiaryLoop && (*primaryLoop == *tertiaryLoop))
                  || (secondaryLoop && tertiaryLoop && (*secondaryLoop == *tertiaryLoop))) {
                return false;
              }
              if (!supplySide && primaryLoop && secondaryLoop && (*secondaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = true;
              } else if (supplySide && primaryLoop && (*primaryLoop == plantLoop)) {
                const bool hasBothOtherOwners = secondaryLoop && tertiaryLoop;
                const bool hasNoOtherOwners = !secondaryLoop && !tertiaryLoop;
                if (!hasBothOtherOwners && !hasNoOtherOwners) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = hasBothOtherOwners;
              } else if (supplySide && primaryLoop && secondaryLoop && tertiaryLoop && (*tertiaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::TertiarySupply;
                retained = true;
              } else {
                return false;
              }
            } else if (component.template optionalCast<HeatPumpPlantLoopEIRHeating>()
                       || component.template optionalCast<HeatPumpPlantLoopEIRCooling>()) {
              if ((primaryLoop && secondaryLoop && (*primaryLoop == *secondaryLoop))
                  || (primaryLoop && tertiaryLoop && (*primaryLoop == *tertiaryLoop))
                  || (secondaryLoop && tertiaryLoop && (*secondaryLoop == *tertiaryLoop))) {
                return false;
              }
              if (supplySide && primaryLoop && (*primaryLoop == plantLoop)) {
                const bool hasBothDemandOwners = secondaryLoop && tertiaryLoop;
                const bool hasNoDemandOwners = !secondaryLoop && !tertiaryLoop;
                if (!hasBothDemandOwners && !hasNoDemandOwners) {
                  return false;
                }
                selectedOwner = SelectedWaterToWaterOwner::Supply;
                retained = hasBothDemandOwners;
              } else if (!supplySide && primaryLoop && secondaryLoop && (*secondaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = true;
              } else if (!supplySide && primaryLoop && secondaryLoop && tertiaryLoop && (*tertiaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::TertiaryDemand;
                retained = true;
              } else {
                return false;
              }
            } else if (isSelectedWaterHeater) {
              if (!primaryLoop || tertiaryLoop || (secondaryLoop && (*primaryLoop == *secondaryLoop))) {
                return false;
              }
              if (supplySide) {
                if (*primaryLoop == plantLoop) {
                  selectedOwner = SelectedWaterToWaterOwner::Supply;
                  retained = static_cast<bool>(secondaryLoop);
                } else if (secondaryLoop && (*secondaryLoop == plantLoop)) {
                  selectedOwner = SelectedWaterToWaterOwner::SecondarySupply;
                  retained = true;
                } else {
                  return false;
                }
              } else if (secondaryLoop && (*secondaryLoop == plantLoop)) {
                selectedOwner = SelectedWaterToWaterOwner::SecondaryDemand;
                retained = true;
              } else {
                return false;
              }
            } else {
              return false;
            }

            ++selectedSpecializedComponentCount;
            if (std::ranges::none_of(selectedWaterToWaterComponents, [&waterToWaterComponent](const auto& existing) {
                  return existing.component.handle() == waterToWaterComponent->handle();
                })) {
              selectedWaterToWaterComponents.push_back(
                {*waterToWaterComponent, selectedOwner, retained,
                 thermalStorage ? boost::optional<WaterHeaterSizing>(thermalStorageOwnership->sizing) : boost::none});
            }
          }
        }
        return true;
      };
      const bool hasOnlySelectedSupplyComponents = hasOnlySelectedComponents(supplyBranches, true);
      const bool hasOnlySelectedDemandComponents = hasOnlySelectedComponents(demandBranches, false);
      if (rejectedExactThermalStorage) {
        return {};
      }
      bool isSelectedEquationFitCompanionPair = false;
      if (hasOnlySelectedSupplyComponents && hasOnlySelectedDemandComponents && retainedWaterCoils.empty()
          && (selectedSpecializedComponentCount == 2u) && (selectedWaterToWaterComponents.size() == 2u)
          && ((ownedSupplyStraightComponentCount + ownedDemandStraightComponentCount) == 0u)) {
        const auto heating = std::ranges::find_if(selectedWaterToWaterComponents, [](const auto& selected) {
          return selected.component.template optionalCast<HeatPumpWaterToWaterEquationFitHeating>().has_value();
        });
        const auto cooling = std::ranges::find_if(selectedWaterToWaterComponents, [](const auto& selected) {
          return selected.component.template optionalCast<HeatPumpWaterToWaterEquationFitCooling>().has_value();
        });
        if ((heating != selectedWaterToWaterComponents.end()) && (cooling != selectedWaterToWaterComponents.end())
            && (heating->owner == SelectedWaterToWaterOwner::Supply) && (cooling->owner == SelectedWaterToWaterOwner::SecondaryDemand)) {
          const auto heatingHeatPump = heating->component.cast<HeatPumpWaterToWaterEquationFitHeating>();
          const auto coolingHeatPump = cooling->component.cast<HeatPumpWaterToWaterEquationFitCooling>();
          const auto companionCoolingHeatPump = heatingHeatPump.companionCoolingHeatPump();
          const auto companionHeatingHeatPump = coolingHeatPump.companionHeatingHeatPump();
          isSelectedEquationFitCompanionPair = companionCoolingHeatPump && companionHeatingHeatPump
                                               && (companionCoolingHeatPump->handle() == coolingHeatPump.handle())
                                               && (companionHeatingHeatPump->handle() == heatingHeatPump.handle());
        }
      }
      bool isSelectedChillerCondenserWithOwnedSupplyEquipment = false;
      // A configured condenser loop owns its ordinary supply equipment, but
      // only the chiller's secondary ports. Keep this exception distinct from
      // primary and heat-recovery ownership.
      if ((selectedSpecializedComponentCount == 1u) && retainedWaterCoils.empty() && (selectedWaterToWaterComponents.size() == 1u)
          && (ownedSupplyStraightComponentCount > 0u) && (ownedDemandStraightComponentCount == 0u)) {
        const auto& selected = selectedWaterToWaterComponents.front();
        const auto chiller = selected.component.optionalCast<ChillerElectricEIR>();
        const auto primaryLoop = chiller ? chiller->plantLoop() : boost::none;
        const auto condenserLoop = chiller ? chiller->secondaryPlantLoop() : boost::none;
        isSelectedChillerCondenserWithOwnedSupplyEquipment =
          chiller && selected.retained && (selected.owner == SelectedWaterToWaterOwner::SecondaryDemand) && primaryLoop && (*primaryLoop != plantLoop)
          && condenserLoop && (*condenserLoop == plantLoop) && !chiller->tertiaryPlantLoop();
      }
      bool isSelectedThermalStorageWithOwnedStraightEquipment = false;
      // One exact storage owner can share its loop with ordinary equipment.
      // Its validated sizing child remains selected even when this is the last
      // owner; no other specialized family enters this exception.
      if ((selectedSpecializedComponentCount == 1u) && retainedWaterCoils.empty() && (selectedWaterToWaterComponents.size() == 1u)
          && ((ownedSupplyStraightComponentCount + ownedDemandStraightComponentCount) > 0u)) {
        const auto& selected = selectedWaterToWaterComponents.front();
        const auto storage = selected.component.optionalCast<ThermalStorageChilledWaterStratified>();
        isSelectedThermalStorageWithOwnedStraightEquipment =
          storage && selected.ownedSizing
          && ((selected.owner == SelectedWaterToWaterOwner::Supply) || (selected.owner == SelectedWaterToWaterOwner::SecondaryDemand));
      }
      const bool hasSelectedSpecializedCardinality =
        (selectedSpecializedComponentCount == 0u)
        || ((selectedSpecializedComponentCount == 1u) && ((ownedSupplyStraightComponentCount + ownedDemandStraightComponentCount) == 0u))
        || isSelectedEquationFitCompanionPair || isSelectedChillerCondenserWithOwnedSupplyEquipment
        || isSelectedThermalStorageWithOwnedStraightEquipment;
      if (!hasOnlySelectedSupplyComponents || !hasOnlySelectedDemandComponents || !hasSelectedSpecializedCardinality) {
        // Specialized branch members are separate ownership lifecycles.
        // Preserve the pre-existing generic behavior until each has a paired
        // contract.
        return Loop_Impl::remove();
      }

      std::vector<ModelObject> removalObjects;
      const auto addRemovalObject = [&removalObjects](const ModelObject& object) {
        if (std::ranges::none_of(removalObjects, [&object](const auto& existing) { return existing.handle() == object.handle(); })) {
          removalObjects.push_back(object);
        }
      };
      const auto isRetainedSharedComponent = [&retainedWaterCoils, &selectedWaterToWaterComponents](const ModelObject& component) {
        return std::ranges::any_of(retainedWaterCoils, [&component](const auto& waterCoil) { return waterCoil.handle() == component.handle(); })
               || std::ranges::any_of(selectedWaterToWaterComponents, [&component](const auto& selectedComponent) {
                    return selectedComponent.retained && (selectedComponent.component.handle() == component.handle());
                  });
      };

      // Capture the public topology before removing its PlantLoop source. This
      // includes the transient Nodes used to project empty equipment branches.
      for (const auto& component : supplyComponents(openstudio::IddObjectType::Catchall)) {
        if (!isRetainedSharedComponent(component)) {
          addRemovalObject(component);
        }
      }
      for (const auto& component : demandComponents(openstudio::IddObjectType::Catchall)) {
        if (!isRetainedSharedComponent(component)) {
          addRemovalObject(component);
        }
      }

      // Branches and connector rows are canonical PlantLoop scaffolding in an
      // EnergyPlus-native graph. They are owned by the loop even though their
      // storage differs from Model's OS objects.
      for (const auto& branch : supplyBranches) {
        addRemovalObject(branch.cast<ModelObject>());
      }
      for (const auto& branch : demandBranches) {
        addRemovalObject(branch.cast<ModelObject>());
      }
      addRemovalObject(supplyBranchList().cast<ModelObject>());
      addRemovalObject(demandBranchList().cast<ModelObject>());

      if (auto connectorList = plantLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName)) {
        addRemovalObject(*connectorList);
      }
      if (auto connectorList = plantLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName)) {
        addRemovalObject(*connectorList);
      }

      addRemovalObject(sizingPlant().cast<ModelObject>());
      addRemovalObject(availabilityManagerAssignmentList().cast<ModelObject>());
      addRemovalObject(plantEquipmentOperationSchemes().cast<ModelObject>());

      // A selected shared water coil is owned by its surviving air path, not
      // by this PlantLoop. Remove only the PlantLoop branch and inferred water
      // controller before deleting the owner-local canonical graph.
      for (auto waterCoil : retainedWaterCoils) {
        if (!plantLoop.removeDemandBranchWithComponent(waterCoil)) {
          return {};
        }
      }

      // A selected shared water-to-water component retains the port pairs
      // owned by its opposite PlantLoops. A selected last-owner component is
      // removed after its final branch and ports are cleared; the selected
      // water-heater paths also own their WaterHeaterSizing companions.
      for (auto selectedComponent : selectedWaterToWaterComponents) {
        const bool exactPlantLoopEIRSourceRemovalOwnsState = (selectedComponent.owner == SelectedWaterToWaterOwner::SecondaryDemand)
                                                             && selectedComponent.component.tertiaryPlantLoop()
                                                             && (selectedComponent.component.optionalCast<HeatPumpPlantLoopEIRHeating>()
                                                                 || selectedComponent.component.optionalCast<HeatPumpPlantLoopEIRCooling>());
        const bool supplyOwner =
          (selectedComponent.owner == SelectedWaterToWaterOwner::Supply) || (selectedComponent.owner == SelectedWaterToWaterOwner::SecondarySupply);
        const bool removed = (selectedComponent.owner == SelectedWaterToWaterOwner::TertiarySupply)
                               ? selectedComponent.component.removeFromTertiaryPlantLoop()
                               : (supplyOwner ? plantLoop.removeSupplyBranchWithComponent(selectedComponent.component)
                                              : plantLoop.removeDemandBranchWithComponent(selectedComponent.component));
        if (!removed) {
          return {};
        }
        if ((selectedComponent.owner == SelectedWaterToWaterOwner::SecondaryDemand) && !exactPlantLoopEIRSourceRemovalOwnsState) {
          if (auto heatPump = selectedComponent.component.optionalCast<HeatPumpPlantLoopEIRHeating>();
              heatPump && !heatPump->setCondenserType("AirSource")) {
            return {};
          }
          if (auto heatPump = selectedComponent.component.optionalCast<HeatPumpPlantLoopEIRCooling>();
              heatPump && !heatPump->setCondenserType("AirSource")) {
            return {};
          }
        }
        if (!selectedComponent.retained) {
          if (selectedComponent.ownedSizing) {
            appendRemoved(selectedComponent.ownedSizing->remove());
          } else if (auto waterHeater = selectedComponent.component.optionalCast<WaterHeaterMixed>()) {
            appendRemoved(waterHeater->waterHeaterSizing().remove());
          } else if (auto waterHeater = selectedComponent.component.optionalCast<WaterHeaterStratified>()) {
            appendRemoved(waterHeater->waterHeaterSizing().remove());
          }
          appendRemoved(selectedComponent.component.remove());
        }
      }

      appendRemoved(Loop_Impl::remove());

      std::set<Handle> removedHandles;
      for (auto object : removalObjects) {
        const auto handle = object.handle();
        if (handle.isNull() || removedHandles.contains(handle) || !owningModel.getObject(handle)) {
          continue;
        }
        removedHandles.insert(handle);
        appendRemoved(object.remove());
      }

      return result;
    }

    boost::optional<Branch> PlantLoop_Impl::branchForNode(const Node& node) const {
      if (auto branch = supplyBranchForNode(node)) {
        return branch;
      }
      return demandBranchForNode(node);
    }

    std::string PlantLoop_Impl::loadDistributionScheme() const {
      const auto value = getString(openstudio::PlantLoopFields::LoadDistributionScheme, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setLoadDistributionScheme(const std::string& scheme) {
      auto normalized = scheme;
      if (openstudio::istringEqual(normalized, "Sequential")) {
        normalized = "SequentialLoad";
      } else if (openstudio::istringEqual(normalized, "Uniform")) {
        normalized = "UniformLoad";
      }
      return setString(openstudio::PlantLoopFields::LoadDistributionScheme, normalized);
    }

    std::string PlantLoop_Impl::fluidType() const {
      const auto value = getString(openstudio::PlantLoopFields::FluidType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setFluidType(const std::string& value) {
      return setString(openstudio::PlantLoopFields::FluidType, value);
    }

    int PlantLoop_Impl::glycolConcentration() const {
      return getInt(openstudio::OS_PlantLoopFields::GlycolConcentration, true).get();
    }

    bool PlantLoop_Impl::setGlycolConcentration(int glycolConcentration) {
      return setInt(openstudio::OS_PlantLoopFields::GlycolConcentration, glycolConcentration);
    }

    double PlantLoop_Impl::maximumLoopTemperature() const {
      const auto value = getDouble(openstudio::PlantLoopFields::MaximumLoopTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setMaximumLoopTemperature(double value) {
      return setDouble(openstudio::PlantLoopFields::MaximumLoopTemperature, value);
    }

    double PlantLoop_Impl::minimumLoopTemperature() const {
      const auto value = getDouble(openstudio::PlantLoopFields::MinimumLoopTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::setMinimumLoopTemperature(double value) {
      return setDouble(openstudio::PlantLoopFields::MinimumLoopTemperature, value);
    }

    boost::optional<double> PlantLoop_Impl::maximumLoopFlowRate() const {
      return getDouble(openstudio::PlantLoopFields::MaximumLoopFlowRate, true);
    }

    bool PlantLoop_Impl::setMaximumLoopFlowRate(double value) {
      return setDouble(openstudio::PlantLoopFields::MaximumLoopFlowRate, value);
    }

    bool PlantLoop_Impl::isMaximumLoopFlowRateAutosized() const {
      if (const auto value = getString(openstudio::PlantLoopFields::MaximumLoopFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autosize");
      }
      return false;
    }

    void PlantLoop_Impl::autosizeMaximumLoopFlowRate() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::MaximumLoopFlowRate, "Autosize"));
    }

    boost::optional<double> PlantLoop_Impl::minimumLoopFlowRate() const {
      return getDouble(openstudio::PlantLoopFields::MinimumLoopFlowRate, true);
    }

    bool PlantLoop_Impl::setMinimumLoopFlowRate(double value) {
      return setDouble(openstudio::PlantLoopFields::MinimumLoopFlowRate, value);
    }

    bool PlantLoop_Impl::isMinimumLoopFlowRateAutosized() const {
      if (const auto value = getString(openstudio::PlantLoopFields::MinimumLoopFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "Autosize");
      }
      return false;
    }

    void PlantLoop_Impl::autosizeMinimumLoopFlowRate() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::MinimumLoopFlowRate, "Autosize"));
    }

    boost::optional<double> PlantLoop_Impl::plantLoopVolume() const {
      return getDouble(openstudio::PlantLoopFields::PlantLoopVolume, true);
    }

    bool PlantLoop_Impl::setPlantLoopVolume(double value) {
      return setDouble(openstudio::PlantLoopFields::PlantLoopVolume, value);
    }

    bool PlantLoop_Impl::isPlantLoopVolumeAutocalculated() const {
      if (const auto value = getString(openstudio::PlantLoopFields::PlantLoopVolume, true)) {
        return openstudio::istringEqual(value.get(), "Autocalculate");
      }
      return false;
    }

    void PlantLoop_Impl::autocalculatePlantLoopVolume() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::PlantLoopVolume, "Autocalculate"));
    }

    std::string PlantLoop_Impl::commonPipeSimulation() const {
      const auto value = getString(openstudio::PlantLoopFields::CommonPipeSimulation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool PlantLoop_Impl::isCommonPipeSimulationDefaulted() const {
      return isEmpty(openstudio::PlantLoopFields::CommonPipeSimulation);
    }

    bool PlantLoop_Impl::setCommonPipeSimulation(const std::string& value) {
      return setString(openstudio::PlantLoopFields::CommonPipeSimulation, value);
    }

    void PlantLoop_Impl::resetCommonPipeSimulation() {
      OS_ASSERT(setString(openstudio::PlantLoopFields::CommonPipeSimulation, ""));
    }

    Node PlantLoop_Impl::loopTemperatureSetpointNode() const {
      auto node = getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
      OS_ASSERT(node);
      return *node;
    }

    bool PlantLoop_Impl::setLoopTemperatureSetpointNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }
      return setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, node.handle(), false);
    }

    PlantEquipmentOperationSchemes PlantLoop_Impl::plantEquipmentOperationSchemes() const {
      auto operationSchemes =
        getObject<PlantLoop>().getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
      OS_ASSERT(operationSchemes);
      return *operationSchemes;
    }

    boost::optional<PlantEquipmentOperationHeatingLoad> PlantLoop_Impl::plantEquipmentOperationHeatingLoad() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationHeatingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationHeatingLoad(const PlantEquipmentOperationHeatingLoad& plantOperation) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationHeatingLoad(
        plantOperation);
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationHeatingLoad() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationHeatingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationHeatingLoadSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationHeatingLoadSchedule(
        schedule);
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationHeatingLoadSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationHeatingLoadSchedule();
    }

    boost::optional<Schedule> PlantLoop_Impl::plantEquipmentOperationHeatingLoadSchedule() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationHeatingLoadSchedule();
    }

    boost::optional<PlantEquipmentOperationCoolingLoad> PlantLoop_Impl::plantEquipmentOperationCoolingLoad() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationCoolingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationCoolingLoad(const PlantEquipmentOperationCoolingLoad& plantOperation) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationCoolingLoad(
        plantOperation);
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationCoolingLoad() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationCoolingLoad();
    }

    bool PlantLoop_Impl::setPlantEquipmentOperationCoolingLoadSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPlantEquipmentOperationCoolingLoadSchedule(
        schedule);
    }

    boost::optional<Schedule> PlantLoop_Impl::plantEquipmentOperationCoolingLoadSchedule() const {
      return plantEquipmentOperationSchemes().plantEquipmentOperationCoolingLoadSchedule();
    }

    void PlantLoop_Impl::resetPlantEquipmentOperationCoolingLoadSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPlantEquipmentOperationCoolingLoadSchedule();
    }

    boost::optional<PlantEquipmentOperationScheme> PlantLoop_Impl::primaryPlantEquipmentOperationScheme() const {
      return plantEquipmentOperationSchemes().primaryPlantEquipmentOperationScheme();
    }

    bool PlantLoop_Impl::setPrimaryPlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& plantOperation) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPrimaryPlantEquipmentOperationScheme(
        plantOperation);
    }

    void PlantLoop_Impl::resetPrimaryPlantEquipmentOperationScheme() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPrimaryPlantEquipmentOperationScheme();
    }

    bool PlantLoop_Impl::setPrimaryPlantEquipmentOperationSchemeSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setPrimaryPlantEquipmentOperationSchemeSchedule(
        schedule);
    }

    void PlantLoop_Impl::resetPrimaryPlantEquipmentOperationSchemeSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetPrimaryPlantEquipmentOperationSchemeSchedule();
    }

    boost::optional<Schedule> PlantLoop_Impl::primaryPlantEquipmentOperationSchemeSchedule() const {
      return plantEquipmentOperationSchemes().primaryPlantEquipmentOperationSchemeSchedule();
    }

    bool PlantLoop_Impl::setComponentSetpointOperationSchemeSchedule(Schedule& schedule) {
      return plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->setComponentSetpointOperationSchemeSchedule(
        schedule);
    }

    void PlantLoop_Impl::resetComponentSetpointOperationSchemeSchedule() {
      plantEquipmentOperationSchemes().getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->resetComponentSetpointOperationSchemeSchedule();
    }

    boost::optional<Schedule> PlantLoop_Impl::componentSetpointOperationSchemeSchedule() const {
      return plantEquipmentOperationSchemes().componentSetpointOperationSchemeSchedule();
    }

    SizingPlant PlantLoop_Impl::sizingPlant() const {
      boost::optional<SizingPlant> result;
      for (const auto& candidate : model().getConcreteModelObjects<SizingPlant>()) {
        auto plantLoop = candidate.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
        if (!plantLoop || !(*plantLoop == getObject<PlantLoop>())) {
          continue;
        }

        if (!result) {
          result = candidate;
        }
      }

      OS_ASSERT(result);
      return *result;
    }

    AvailabilityManagerAssignmentList PlantLoop_Impl::availabilityManagerAssignmentList() const {
      auto assignmentList =
        getObject<PlantLoop>().getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
      OS_ASSERT(assignmentList);
      return *assignmentList;
    }

    std::vector<AvailabilityManager> PlantLoop_Impl::availabilityManagers() const {
      return availabilityManagerAssignmentList().availabilityManagers();
    }

    bool PlantLoop_Impl::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
      const auto type = availabilityManager.iddObject().type();
      if ((type == IddObjectType::AvailabilityManager_NightCycle) || (type == IddObjectType::AvailabilityManager_HybridVentilation)
          || (type == IddObjectType::AvailabilityManager_NightVentilation)) {
        return false;
      }
      return availabilityManagerAssignmentList().addAvailabilityManager(availabilityManager);
    }

    bool PlantLoop_Impl::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
      if (!addAvailabilityManager(availabilityManager)) {
        return false;
      }
      return availabilityManagerAssignmentList().setAvailabilityManagerPriority(availabilityManager, priority);
    }

    bool PlantLoop_Impl::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
      for (const auto& availabilityManager : availabilityManagers) {
        const auto type = availabilityManager.iddObject().type();
        if ((type == IddObjectType::AvailabilityManager_NightCycle) || (type == IddObjectType::AvailabilityManager_HybridVentilation)
            || (type == IddObjectType::AvailabilityManager_NightVentilation)) {
          return false;
        }
      }
      return availabilityManagerAssignmentList().setAvailabilityManagers(availabilityManagers);
    }

    void PlantLoop_Impl::resetAvailabilityManagers() {
      availabilityManagerAssignmentList().resetAvailabilityManagers();
    }

    bool PlantLoop_Impl::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
      return availabilityManagerAssignmentList().removeAvailabilityManager(availabilityManager);
    }

    bool PlantLoop_Impl::removeAvailabilityManager(unsigned priority) {
      return availabilityManagerAssignmentList().removeAvailabilityManager(priority);
    }

    bool PlantLoop_Impl::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
      return availabilityManagerAssignmentList().setAvailabilityManagerPriority(availabilityManager, priority);
    }

    unsigned PlantLoop_Impl::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
      return availabilityManagerAssignmentList().availabilityManagerPriority(availabilityManager);
    }

    bool PlantLoop_Impl::addSupplyBranchForComponent(HVACComponent hvacComponent) {
      if (hvacComponent.model() != model()) {
        return false;
      }
      if (!hvacComponent.optionalCast<StraightComponent>() && !hvacComponent.optionalCast<WaterToWaterComponent>()) {
        return false;
      }
      if (hvacComponent.optionalCast<StraightComponent>()) {
        if (auto currentLoop = hvacComponent.loop(); currentLoop && (currentLoop->handle() == getObject<PlantLoop>().handle())) {
          return false;
        }
      }
      if (auto waterToWater = hvacComponent.optionalCast<WaterToWaterComponent>()) {
        if (waterToWater->plantLoop()) {
          const bool canRouteSupplySideToSource =
            (hvacComponent.optionalCast<WaterHeaterMixed>() || hvacComponent.optionalCast<WaterHeaterStratified>())
            && !waterToWater->secondaryPlantLoop();
          const bool canRouteSupplySideToTertiary =
            hvacComponent.optionalCast<CentralHeatPumpSystem>() && waterToWater->secondaryPlantLoop() && !waterToWater->tertiaryPlantLoop();
          if (!canRouteSupplySideToSource && !canRouteSupplySideToTertiary) {
            return false;
          }
        }
      }

      if (hvacComponent.iddObject().type() == PipeAdiabatic::iddObjectType() && !hvacComponent.airLoopHVAC()) {
        auto plan = PipeBranchAttachmentPlan::prepare(*this, hvacComponent.cast<StraightComponent>(), true);
        if (!plan) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to attach " << hvacComponent.briefDescription() << " to the supply side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its source row or the target equipment branch could not be validated.");
          return false;
        }
        if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPipeBranchAttachmentPrepared)) {
          return false;
        }
        plan->commit();
        return true;
      }

      auto branchList = supplyBranchList();
      auto equipmentBranches = supplyEquipmentBranches();
      OS_ASSERT(!equipmentBranches.empty());
      auto splitter = supplySplitter().cast<ConnectorSplitter>();
      auto mixer = supplyMixer().cast<ConnectorMixer>();

      // A newly canonicalized loop starts with one empty equipment branch. Reuse
      // that branch instead of manufacturing a second branch the first time
      // equipment is added.
      if (!isBeamDemandBranchComponent(hvacComponent) && (equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
        auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
        if (!hvacComponent.addToNode(node)) {
          return false;
        }
        return true;
      }

      const auto insertIndex = static_cast<unsigned>(branchList.branches().size() - 1u);
      Branch branch(model());
      if (!branch.setName(getObject<PlantLoop>().nameString() + " Supply Branch "
                          + std::to_string(static_cast<unsigned>(equipmentBranches.size() + 1u)))) {
        branch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
      }
      if (!branchList.getImpl<detail::BranchList_Impl>()->insertBranch(insertIndex, branch)) {
        return false;
      }

      equipmentBranches = supplyEquipmentBranches();
      if (!syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), equipmentBranches)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        branch.remove();
        return false;
      }

      auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
      if (!hvacComponent.addToNode(node)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), supplyEquipmentBranches());
        branch.remove();
        return false;
      }

      return true;
    }

    bool PlantLoop_Impl::removeSupplyBranchWithComponent(HVACComponent hvacComponent) {
      if (hvacComponent.iddObject().type() == PipeAdiabatic::iddObjectType()) {
        auto plan = PipeBranchRemovalPlan::prepare(*this, hvacComponent.cast<PipeAdiabatic>(), true);
        if (!plan) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to remove " << hvacComponent.briefDescription() << " from the supply side of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact single-component equipment branch could not be validated.");
          return false;
        }
        if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPipeBranchRemovalPrepared)) {
          return false;
        }
        plan->commit();
        return true;
      }

      if (!supplyComponent(hvacComponent.handle())) {
        return false;
      }

      auto equipmentBranches = supplyEquipmentBranches();
      const auto targetComponent = hvacComponent.cast<ModelObject>();
      boost::optional<Branch> targetBranch;
      for (const auto& branch : equipmentBranches) {
        const auto components = projectedBranchComponents(branch);
        if (std::ranges::find(components, targetComponent) != components.end()) {
          targetBranch = branch;
          break;
        }
      }

      if (!targetBranch) {
        if (auto node = hvacComponent.optionalCast<Node>()) {
          auto branch = branchForNode(*node);
          if (branch && (std::ranges::find(equipmentBranches, *branch) != equipmentBranches.end())) {
            targetBranch = *branch;
          }
        }
      }

      if (!targetBranch) {
        if (auto straightComponent = hvacComponent.optionalCast<StraightComponent>()) {
          if (auto inletObject = straightComponent->inletModelObject()) {
            if (auto inletNode = inletObject->optionalCast<Node>()) {
              targetBranch = branchForNode(*inletNode);
            }
          }
          if (!targetBranch) {
            if (auto outletObject = straightComponent->outletModelObject()) {
              if (auto outletNode = outletObject->optionalCast<Node>()) {
                targetBranch = branchForNode(*outletNode);
              }
            }
          }
        }
      }

      if (!targetBranch) {
        return false;
      }

      const auto components = projectedBranchComponents(*targetBranch);
      std::set<Handle> sourceSideWaterHeaterHandles;
      for (const auto& component : components) {
        const bool isSelectedWaterHeater = component.optionalCast<WaterHeaterMixed>() || component.optionalCast<WaterHeaterStratified>();
        if (auto waterHeater = component.optionalCast<WaterToWaterComponent>(); waterHeater && isSelectedWaterHeater) {
          const auto sourceLoop = waterHeater->secondaryPlantLoop();
          if (sourceLoop && (*sourceLoop == getObject<PlantLoop>())) {
            sourceSideWaterHeaterHandles.insert(waterHeater->handle());
          }
        }
      }

      auto branchList = supplyBranchList();
      const bool keepAsDefaultBranch = (equipmentBranches.size() == 1u);
      auto splitter = supplySplitter().cast<ConnectorSplitter>();
      auto mixer = supplyMixer().cast<ConnectorMixer>();
      if (!keepAsDefaultBranch) {
        if (!branchList.getImpl<detail::BranchList_Impl>()->removeBranch(*targetBranch)) {
          return false;
        }
      }

      targetBranch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->clearComponents();

      if (components.empty()) {
        if (auto straightComponent = hvacComponent.optionalCast<StraightComponent>()) {
          hvacComponent.setPointer(straightComponent->inletPort(), Handle());
          hvacComponent.setPointer(straightComponent->outletPort(), Handle());
        }
      }

      for (auto component : components) {
        if (auto straightComponent = component.optionalCast<StraightComponent>()) {
          if (component.optionalCast<GroundHeatExchangerVertical>()) {
            // The public vertical-ground-heat-exchanger identity projects a
            // GroundHeatExchanger:System row and owns its node cleanup.
            straightComponent->disconnect();
          } else {
            // Supply-branch removal already owns the branch edit. Clear
            // ordinary component ports directly instead of asking disconnect()
            // to traverse a BranchList that is temporarily being mutated.
            component.setPointer(straightComponent->inletPort(), Handle());
            component.setPointer(straightComponent->outletPort(), Handle());
          }
        } else if (auto waterToWater = component.optionalCast<WaterToWaterComponent>()) {
          if (sourceSideWaterHeaterHandles.contains(component.handle())) {
            component.setPointer(waterToWater->demandInletPort(), Handle());
            component.setPointer(waterToWater->demandOutletPort(), Handle());
          } else {
            component.setPointer(waterToWater->supplyInletPort(), Handle());
            component.setPointer(waterToWater->supplyOutletPort(), Handle());
          }
        } else {
          return false;
        }
      }

      if (!keepAsDefaultBranch) {
        targetBranch->remove();
      }

      if (!syncConnectorPorts(splitter, mixer, supplyInletBranch(), supplyOutletBranch(), supplyEquipmentBranches())) {
        return false;
      }

      if (!getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, supplyOutletNode().handle(), false));
      }

      return true;
    }

    bool PlantLoop_Impl::addDemandBranchForComponent(HVACComponent hvacComponent, bool tertiary) {
      if (hvacComponent.model() != model()) {
        return false;
      }
      const auto waterToAir = hvacComponent.optionalCast<WaterToAirComponent>();
      const bool exactMovableWaterCoilType = hvacComponent.iddObject().type() == CoilHeatingWater::iddObjectType()
                                             || hvacComponent.iddObject().type() == CoilCoolingWater::iddObjectType();
      if (!hvacComponent.optionalCast<StraightComponent>() && !waterToAir && !hvacComponent.optionalCast<WaterToWaterComponent>()) {
        return false;
      }
      if (waterToAir) {
        if (tertiary) {
          return false;
        }
        if (waterToAir->plantLoop()) {
          if (!exactMovableWaterCoilType) {
            return false;
          }
          if (const auto containingComponent = waterToAir->containingHVACComponent()) {
            if (waterToAir->iddObject().type() == CoilHeatingWater::iddObjectType()
                && containingComponent->iddObject().type() == AirTerminalSingleDuctConstantVolumeReheat::iddObjectType()) {
              auto plan = ContainedReheatCoilDemandBranchAttachmentPlan::prepare(*this, waterToAir->cast<CoilHeatingWater>());
              if (!plan) {
                LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                         "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of "
                                             << getObject<PlantLoop>().briefDescription()
                                             << " because its exact constant-volume reheat owner, canonical air/zone topology, single-row source "
                                                "demand branch, or target topology could not be validated.");
                return false;
              }
              if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared)) {
                return false;
              }
              plan->commit();
              return true;
            }
            if (containingComponent->iddObject().type() == ZoneHVACFourPipeFanCoil::iddObjectType()) {
              auto plan = FourPipeFanCoilDemandBranchAttachmentPlan::prepare(*this, *waterToAir);
              if (!plan) {
                LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                         "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of "
                                             << getObject<PlantLoop>().briefDescription()
                                             << " because its exact four-pipe fan-coil role ownership, ordinary zone topology, controller-free water "
                                                "children, single-row source demand branch, or target topology could not be validated.");
                return false;
              }
              if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared)) {
                return false;
              }
              plan->commit();
              return true;
            }
            return false;
          }
          auto plan = WaterCoilDemandBranchAttachmentPlan::prepare(*this, *waterToAir);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its direct air owner, unique controller, exact single-row source demand branch, or target "
                                            "topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (tertiary && hvacComponent.iddObject().type() == ChillerElectricEIR::iddObjectType()) {
        const auto chiller = hvacComponent.cast<ChillerElectricEIR>();
        if (ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(chiller)) {
          auto plan = ChillerElectricEIRHeatRecoveryDemandBranchAttachmentPlan::prepare(*this, chiller);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the heat-recovery demand side of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact chilled-water, WaterCooled condenser, and heat-recovery owners, six live ports, "
                                            "single-row branches, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterChillerElectricEIRHeatRecoveryBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (tertiary && hvacComponent.iddObject().type() == HeatPumpPlantLoopEIRHeating::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpPlantLoopEIRHeating>();
        if (PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(*this, heatPump)) {
          auto plan = PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the heat-recovery demand side of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact LoadSide, SourceSide, and HeatRecovery owners, WaterSource state, companion "
                                            "evidence, six live ports, single-row branches, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPlantLoopEIRHeatPumpHeatRecoveryBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (tertiary && hvacComponent.iddObject().type() == HeatPumpPlantLoopEIRCooling::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpPlantLoopEIRCooling>();
        if (PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(*this, heatPump)) {
          auto plan = PlantLoopEIRHeatPumpHeatRecoveryDemandBranchAttachmentPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the heat-recovery demand side of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact LoadSide, SourceSide, and HeatRecovery owners, WaterSource state, companion "
                                            "evidence, six live ports, single-row branches, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPlantLoopEIRHeatPumpHeatRecoveryBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (!tertiary && hvacComponent.iddObject().type() == HeatPumpPlantLoopEIRHeating::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpPlantLoopEIRHeating>();
        if (PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(heatPump)) {
          auto plan = PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the source-side demand of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact LoadSide, SourceSide, and HeatRecovery owners, WaterSource state, companion "
                                            "evidence, six live ports, single-row branches, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPlantLoopEIRHeatPumpSourceBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (!tertiary && hvacComponent.iddObject().type() == HeatPumpPlantLoopEIRCooling::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpPlantLoopEIRCooling>();
        if (PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(heatPump)) {
          auto plan = PlantLoopEIRHeatPumpSourceDemandBranchAttachmentPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the source-side demand of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact LoadSide, SourceSide, and HeatRecovery owners, WaterSource state, companion "
                                            "evidence, six live ports, single-row branches, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPlantLoopEIRHeatPumpSourceBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (hvacComponent.iddObject().type() == HeatPumpWaterToWaterEquationFitHeating::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpWaterToWaterEquationFitHeating>();
        if (tertiary) {
          return false;
        }
        if (EquationFitHeatPumpDemandBranchAttachmentPlan::targetIsPrimaryOwner(*this, heatPump)) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to attach " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because that PlantLoop is its proven source-side primary owner.");
          return false;
        }
        if (EquationFitHeatPumpDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(heatPump)) {
          auto plan = EquationFitHeatPumpDemandBranchAttachmentPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its exact source-side primary owner, load-side secondary owner, companion evidence, "
                                            "single-row branches, live ports, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterEquationFitHeatPumpBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (hvacComponent.iddObject().type() == HeatPumpWaterToWaterEquationFitCooling::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpWaterToWaterEquationFitCooling>();
        if (tertiary) {
          return false;
        }
        if (EquationFitHeatPumpDemandBranchAttachmentPlan::targetIsPrimaryOwner(*this, heatPump)) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to attach " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because that PlantLoop is its proven load-side primary owner.");
          return false;
        }
        if (EquationFitHeatPumpDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(heatPump)) {
          auto plan = EquationFitHeatPumpDemandBranchAttachmentPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its exact load-side primary owner, source-side secondary owner, companion evidence, "
                                            "single-row branches, live ports, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterEquationFitHeatPumpBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (hvacComponent.iddObject().type() == ThermalStorageChilledWaterStratified::iddObjectType()) {
        const auto storage = hvacComponent.cast<ThermalStorageChilledWaterStratified>();
        if (tertiary) {
          return false;
        }
        if (ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::targetIsPrimaryOwner(*this, storage)) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to attach " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because that PlantLoop is its proven UseSide primary owner.");
          return false;
        }
        if (ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(storage)) {
          auto plan = ThermalStorageChilledWaterStratifiedDemandBranchAttachmentPlan::prepare(*this, storage);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its exact UseSide primary owner, SourceSide secondary owner, WaterHeater:Sizing child, "
                                            "single-row branches, live ports, or target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterThermalStorageSourceBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (hvacComponent.iddObject().type() == HeatExchangerFluidToFluid::iddObjectType()) {
        const auto heatExchanger = hvacComponent.cast<HeatExchangerFluidToFluid>();
        if (tertiary) {
          return false;
        }
        if (FluidToFluidHeatExchangerDemandBranchAttachmentPlan::targetIsPrimaryOwner(*this, heatExchanger)) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to attach " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because that PlantLoop is its proven primary owner.");
          return false;
        }
        if (FluidToFluidHeatExchangerDemandBranchAttachmentPlan::requiresExactAttachmentDispatch(heatExchanger)) {
          auto plan = FluidToFluidHeatExchangerDemandBranchAttachmentPlan::prepare(*this, heatExchanger);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to move " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its exact primary and secondary owners, single-row equipment branches, live ports, or "
                                            "target topology could not be validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterFluidToFluidHeatExchangerBranchAttachmentPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }
      if (hvacComponent.optionalCast<StraightComponent>() && !isBeamDemandBranchComponent(hvacComponent)) {
        if (auto currentLoop = hvacComponent.loop(); currentLoop && (currentLoop->handle() == getObject<PlantLoop>().handle())) {
          return false;
        }
      }
      if (auto waterToWater = hvacComponent.optionalCast<WaterToWaterComponent>()) {
        if (tertiary) {
          if (waterToWater->tertiaryPlantLoop()) {
            return false;
          }
        }
      } else if (tertiary) {
        return false;
      }

      if (hvacComponent.iddObject().type() == PipeAdiabatic::iddObjectType() && !hvacComponent.airLoopHVAC()) {
        auto plan = PipeBranchAttachmentPlan::prepare(*this, hvacComponent.cast<StraightComponent>(), false);
        if (!plan) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to attach " << hvacComponent.briefDescription() << " to the demand side of " << getObject<PlantLoop>().briefDescription()
                                         << " because its source row or the target equipment branch could not be validated.");
          return false;
        }
        if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPipeBranchAttachmentPrepared)) {
          return false;
        }
        plan->commit();
        return true;
      }

      auto branchList = demandBranchList();
      auto equipmentBranches = demandEquipmentBranches();
      OS_ASSERT(!equipmentBranches.empty());
      auto splitter = demandSplitter().cast<ConnectorSplitter>();
      auto mixer = demandMixer().cast<ConnectorMixer>();

      const auto thisLoop = getObject<PlantLoop>();
      const bool hasBeamDemandComponent =
        isBeamDemandBranchComponent(hvacComponent) && hasOtherBeamDemandComponentOnLoop(model(), thisLoop, hvacComponent);

      if (isBeamDemandBranchComponent(hvacComponent) && !hasBeamDemandComponent && (equipmentBranches.size() == 1u)
          && equipmentBranches.front().extensibleGroups().empty()) {
        auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
        return hvacComponent.addToNode(node);
      }

      // Mirror the supply-side behavior: the first real component should claim the
      // default empty equipment branch instead of forcing an unnecessary parallel
      // branch into existence.
      if (!isBeamDemandBranchComponent(hvacComponent) && (equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
        auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
        if (tertiary) {
          return hvacComponent.cast<WaterToWaterComponent>().addToTertiaryNode(node);
        }
        return hvacComponent.addToNode(node);
      }

      const auto insertIndex = static_cast<unsigned>(branchList.branches().size() - 1u);
      Branch branch(model());
      if (!branch.setName(getObject<PlantLoop>().nameString() + " Demand Branch "
                          + std::to_string(static_cast<unsigned>(equipmentBranches.size() + 1u)))) {
        branch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
      }
      if (!branchList.getImpl<detail::BranchList_Impl>()->insertBranch(insertIndex, branch)) {
        return false;
      }

      equipmentBranches = demandEquipmentBranches();
      if (!syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), equipmentBranches)) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        branch.remove();
        return false;
      }

      auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
      bool connected = false;
      if (tertiary) {
        connected = hvacComponent.cast<WaterToWaterComponent>().addToTertiaryNode(node);
      } else {
        connected = hvacComponent.addToNode(node);
      }
      if (!connected) {
        branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
        syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), demandEquipmentBranches());
        branch.remove();
        return false;
      }

      return true;
    }

    std::unique_ptr<PlantLoop_Impl::DemandBranchRemovalPlan>
      PlantLoop_Impl::prepareDemandBranchRemoval(const HVACComponent& component, unsigned inletPort, unsigned outletPort, bool waterToAirComponent,
                                                 DemandBranchPostDisconnectUpdate postDisconnectUpdate) {
      if (component.model() != model()) {
        return nullptr;
      }

      const auto thisLoop = getObject<PlantLoop>();
      const auto inletNode = existingNodeField(component, inletPort).node;
      const auto outletNode = existingNodeField(component, outletPort).node;
      if (!inletNode || !outletNode) {
        return nullptr;
      }

      const auto targetObject = component.cast<ModelObject>();
      const auto equipmentBranches = demandEquipmentBranches();
      boost::optional<Branch> targetBranch;
      unsigned targetOccurrences = 0u;
      bool targetUsesProjectedRow = false;
      for (const auto& branch : equipmentBranches) {
        const auto groups = branch.extensibleGroups();
        for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
          const auto componentNameIndex =
            branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentName));
          const auto relationship = existingObjectField(branch, componentNameIndex);
          auto branchWorkspaceImpl = branch.getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(branchWorkspaceImpl);
          const auto rawComponentName = branchWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(componentNameIndex, false, true);
          const auto rawComponentHandle = rawComponentName ? openstudio::toUUID(*rawComponentName) : Handle();
          const auto componentType = groups[groupIndex].getString(openstudio::BranchExtensibleFields::ComponentObjectType, false);
          const auto branchInletNodeIndex =
            branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentInletNodeName));
          const auto branchOutletNodeIndex =
            branch.iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::BranchExtensibleFields::ComponentOutletNodeName));
          const auto branchInletNode = existingNodeField(branch, branchInletNodeIndex).node;
          const auto branchOutletNode = existingNodeField(branch, branchOutletNodeIndex).node;
          const bool projectedNameMatches =
            !relationship.object
            && (!rawComponentName || rawComponentName->empty() || openstudio::istringEqual(*rawComponentName, component.nameString())
                || (!rawComponentHandle.isNull() && rawComponentHandle == component.handle()));
          const bool projectedBeamRow = !waterToAirComponent && projectedNameMatches && componentType
                                        && openstudio::istringEqual(*componentType, component.iddObject().name()) && branchInletNode
                                        && branchOutletNode && *branchInletNode == *inletNode && *branchOutletNode == *outletNode;
          if ((relationship.object && relationship.object->handle() == targetObject.handle()) || projectedBeamRow) {
            ++targetOccurrences;
            targetBranch = branch;
            targetUsesProjectedRow = projectedBeamRow;
          }
        }
      }
      if (targetOccurrences != 1u || !targetBranch) {
        return nullptr;
      }

      if (targetUsesProjectedRow) {
        unsigned matchingComponentCount = 0u;
        for (const auto& candidate : model().getModelObjects<HVACComponent>()) {
          if (candidate.iddObject().type() != component.iddObject().type()) {
            continue;
          }
          const auto candidateInlet = existingNodeField(candidate, inletPort).node;
          const auto candidateOutlet = existingNodeField(candidate, outletPort).node;
          if (candidateInlet && candidateOutlet && *candidateInlet == *inletNode && *candidateOutlet == *outletNode) {
            ++matchingComponentCount;
          }
        }
        if (matchingComponentCount != 1u) {
          return nullptr;
        }
      }

      const auto targetGroups = targetBranch->extensibleGroups();
      const auto componentType =
        targetGroups.size() == 1u ? targetGroups.front().getString(openstudio::BranchExtensibleFields::ComponentObjectType, false) : boost::none;
      const auto componentNameIndex =
        targetGroups.size() == 1u
          ? targetBranch->iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentName))
          : 0u;
      const auto relationship = targetGroups.size() == 1u ? existingObjectField(*targetBranch, componentNameIndex) : detail::ExistingObjectField{};
      if (targetGroups.size() != 1u || !componentType || !openstudio::istringEqual(*componentType, component.iddObject().name())
          || ((!relationship.object || relationship.object->handle() != component.handle()) && !targetUsesProjectedRow)) {
        return nullptr;
      }

      const auto branchInletNodeIndex =
        targetBranch->iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentInletNodeName));
      const auto branchOutletNodeIndex =
        targetBranch->iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::BranchExtensibleFields::ComponentOutletNodeName));
      const auto branchInletNode = existingNodeField(*targetBranch, branchInletNodeIndex).node;
      const auto branchOutletNode = existingNodeField(*targetBranch, branchOutletNodeIndex).node;
      if (!branchInletNode || !branchOutletNode || *branchInletNode != *inletNode || *branchOutletNode != *outletNode) {
        return nullptr;
      }

      auto branchList = demandBranchList();
      const auto listedBranches = branchList.branches();
      if (listedBranches.size() != equipmentBranches.size() + 2u || listedBranches.front() != demandInletBranch()
          || listedBranches.back() != demandOutletBranch()) {
        return nullptr;
      }
      for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
        if (listedBranches[i + 1u] != equipmentBranches[i]) {
          return nullptr;
        }
      }
      if (std::ranges::count(listedBranches, *targetBranch) != 1) {
        return nullptr;
      }

      auto splitter = demandSplitter().cast<ConnectorSplitter>();
      auto mixer = demandMixer().cast<ConnectorMixer>();
      const auto splitterInletBranch = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
      const auto mixerOutletBranch = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
      if (!splitterInletBranch || *splitterInletBranch != listedBranches.front() || !mixerOutletBranch || *mixerOutletBranch != listedBranches.back()
          || splitter.nextBranchIndex() != equipmentBranches.size() || mixer.nextBranchIndex() != equipmentBranches.size()) {
        return nullptr;
      }
      for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
        const auto splitterBranch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
        const auto mixerBranch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
        if (!splitterBranch || *splitterBranch != equipmentBranches[i] || !mixerBranch || *mixerBranch != equipmentBranches[i]) {
          return nullptr;
        }
      }

      unsigned matchingControllerCount = 0u;
      const auto waterCoil = waterToAirComponent ? component.optionalCast<WaterToAirComponent>() : boost::none;
      const auto airOutletObject = waterCoil ? waterCoil->airOutletModelObject() : boost::none;
      if (waterCoil && airOutletObject) {
        for (const auto& controller : model().getConcreteModelObjects<ControllerWaterCoil>()) {
          const auto actuatorNode = controller.actuatorNode();
          const auto sensorNode = controller.sensorNode();
          if (actuatorNode && sensorNode && actuatorNode->handle() == inletNode->handle() && sensorNode->handle() == airOutletObject->handle()) {
            ++matchingControllerCount;
          }
        }
      }
      if (matchingControllerCount > 1u) {
        return nullptr;
      }

      auto state = std::make_unique<DemandBranchRemovalPlan::State>(
        DemandBranchRemovalPlan::State{thisLoop, component, inletPort, outletPort, waterToAirComponent, postDisconnectUpdate, *targetBranch,
                                       branchList, splitter, mixer, equipmentBranches.size() == 1u});
      return std::unique_ptr<DemandBranchRemovalPlan>(new DemandBranchRemovalPlan(std::move(state)));
    }

    std::unique_ptr<PlantLoop_Impl::WaterCoilDemandBranchRemovalPlan>
      PlantLoop_Impl::prepareWaterCoilDemandBranchRemoval(const WaterToAirComponent& coil) {
      return prepareDemandBranchRemoval(coil, coil.waterInletPort(), coil.waterOutletPort(), true);
    }

    std::unique_ptr<PlantLoop_Impl::WaterCoilDemandBranchRemovalPlan>
      PlantLoop_Impl::prepareCoilHeatingWaterDemandBranchRemoval(const CoilHeatingWater& coil) {
      return prepareWaterCoilDemandBranchRemoval(coil);
    }

    std::unique_ptr<PlantLoop_Impl::BeamCoilDemandBranchRemovalPlan>
      PlantLoop_Impl::prepareBeamCoilDemandBranchRemoval(const StraightComponent& coil) {
      const auto coilType = coil.iddObject().type();
      if (coilType != CoilCoolingCooledBeam::iddObjectType() && coilType != CoilCoolingFourPipeBeam::iddObjectType()
          && coilType != CoilHeatingFourPipeBeam::iddObjectType()) {
        return nullptr;
      }
      return prepareDemandBranchRemoval(coil, coil.inletPort(), coil.outletPort(), false);
    }

    std::unique_ptr<PlantLoop_Impl::ChillerCondenserDemandBranchRemovalPlan>
      PlantLoop_Impl::prepareChillerCondenserDemandBranchRemoval(const ChillerElectricEIR& chiller) {
      const auto thisLoop = getObject<PlantLoop>();
      const auto primaryLoop = chiller.plantLoop();
      const auto condenserLoop = chiller.secondaryPlantLoop();
      if (!primaryLoop || (*primaryLoop == thisLoop) || !condenserLoop || (*condenserLoop != thisLoop)
          || !openstudio::istringEqual(chiller.condenserType(), "WaterCooled")) {
        return nullptr;
      }
      return prepareDemandBranchRemoval(chiller, chiller.demandInletPort(), chiller.demandOutletPort(), false,
                                        DemandBranchPostDisconnectUpdate::ChillerCondenserAirCooled);
    }

    bool PlantLoop_Impl::removeDemandBranchWithComponent(HVACComponent hvacComponent) {
      if (hvacComponent.iddObject().type() == HeatPumpPlantLoopEIRHeating::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpPlantLoopEIRHeating>();
        if (PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan::requiresExactRemovalDispatch(*this, heatPump)) {
          auto plan = PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to remove " << hvacComponent.briefDescription() << " from the source-side demand of "
                                           << getObject<PlantLoop>().briefDescription()
                                           << " because its exact fully three-owned LoadSide, SourceSide, and HeatRecovery topology could not be "
                                              "validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPlantLoopEIRHeatPumpSourceBranchRemovalPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }

      if (hvacComponent.iddObject().type() == HeatPumpPlantLoopEIRCooling::iddObjectType()) {
        const auto heatPump = hvacComponent.cast<HeatPumpPlantLoopEIRCooling>();
        if (PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan::requiresExactRemovalDispatch(*this, heatPump)) {
          auto plan = PlantLoopEIRHeatPumpSourceDemandBranchRemovalPlan::prepare(*this, heatPump);
          if (!plan) {
            LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                     "Refusing to remove " << hvacComponent.briefDescription() << " from the source-side demand of "
                                           << getObject<PlantLoop>().briefDescription()
                                           << " because its exact fully three-owned LoadSide, SourceSide, and HeatRecovery topology could not be "
                                              "validated.");
            return false;
          }
          if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPlantLoopEIRHeatPumpSourceBranchRemovalPrepared)) {
            return false;
          }
          plan->commit();
          return true;
        }
      }

      if (auto waterToAir = hvacComponent.optionalCast<WaterToAirComponent>()) {
        auto plan = prepareWaterCoilDemandBranchRemoval(*waterToAir);
        if (!plan) {
          return false;
        }
        plan->commit();
        return true;
      }

      if (auto chiller = hvacComponent.optionalCast<ChillerElectricEIR>()) {
        if (auto condenserLoop = chiller->secondaryPlantLoop(); condenserLoop && (*condenserLoop == getObject<PlantLoop>())) {
          auto plan = prepareChillerCondenserDemandBranchRemoval(*chiller);
          if (!plan) {
            return false;
          }
          plan->commit();
          return true;
        }
      }

      if (hvacComponent.iddObject().type() == PipeAdiabatic::iddObjectType()) {
        auto plan = PipeBranchRemovalPlan::prepare(*this, hvacComponent.cast<PipeAdiabatic>(), false);
        if (!plan) {
          LOG_FREE(Warn, "openstudio.epmodel.PlantLoop",
                   "Refusing to remove " << hvacComponent.briefDescription() << " from the demand side of "
                                         << getObject<PlantLoop>().briefDescription()
                                         << " because its exact single-component equipment branch could not be validated.");
          return false;
        }
        if (testFailurePointReached(model(), TestFailurePoint::PlantLoopAfterPipeBranchRemovalPrepared)) {
          return false;
        }
        plan->commit();
        return true;
      }

      if (!demandComponent(hvacComponent.handle()) && !isBeamDemandBranchComponent(hvacComponent)) {
        return false;
      }

      auto equipmentBranches = demandEquipmentBranches();
      const auto targetComponent = hvacComponent.cast<ModelObject>();
      boost::optional<Branch> targetBranch;
      for (const auto& branch : equipmentBranches) {
        const auto components = projectedBranchComponents(branch);
        if (std::ranges::find(components, targetComponent) != components.end()) {
          targetBranch = branch;
          break;
        }
      }

      if (!targetBranch) {
        if (auto node = hvacComponent.optionalCast<Node>()) {
          auto branch = branchForNode(*node);
          if (branch && (std::ranges::find(equipmentBranches, *branch) != equipmentBranches.end())) {
            targetBranch = *branch;
          }
        }
      }

      if (!targetBranch) {
        if (auto straightComponent = hvacComponent.optionalCast<StraightComponent>()) {
          if (auto inletObject = straightComponent->inletModelObject()) {
            if (auto inletNode = inletObject->optionalCast<Node>()) {
              targetBranch = branchForNode(*inletNode);
            }
          }
          if (!targetBranch) {
            if (auto outletObject = straightComponent->outletModelObject()) {
              if (auto outletNode = outletObject->optionalCast<Node>()) {
                targetBranch = branchForNode(*outletNode);
              }
            }
          }
        }
      }

      if (!targetBranch) {
        return false;
      }

      const auto components = projectedBranchComponents(*targetBranch);

      auto branchList = demandBranchList();
      const bool keepAsDefaultBranch = (equipmentBranches.size() == 1u);
      auto splitter = demandSplitter().cast<ConnectorSplitter>();
      auto mixer = demandMixer().cast<ConnectorMixer>();

      if (components.empty()) {
        if (auto straightComponent = hvacComponent.optionalCast<StraightComponent>()) {
          hvacComponent.setPointer(straightComponent->inletPort(), Handle());
          hvacComponent.setPointer(straightComponent->outletPort(), Handle());
        }
      }

      for (auto component : components) {
        if (auto straightComponent = component.optionalCast<StraightComponent>()) {
          // Demand-branch removal already owns the branch edit, so clear the
          // straight-component node pointers directly instead of recursively
          // calling removeFromLoop() through disconnect().
          component.setPointer(straightComponent->inletPort(), Handle());
          component.setPointer(straightComponent->outletPort(), Handle());
        } else if (auto waterToAir = component.optionalCast<WaterToAirComponent>()) {
          if (!waterToAir->removeFromPlantLoop()) {
            return false;
          }
          waterToAir->disconnectWaterSide();
          if (!waterToAir->airLoopHVAC() && !waterToAir->containingHVACComponent()) {
            waterToAir->remove();
          }
        } else if (auto waterToWater = component.optionalCast<WaterToWaterComponent>()) {
          if (auto tertiaryLoop = waterToWater->tertiaryPlantLoop(); tertiaryLoop && tertiaryLoop->handle() == getObject<PlantLoop>().handle()) {
            component.setPointer(waterToWater->tertiaryInletPort(), Handle());
            component.setPointer(waterToWater->tertiaryOutletPort(), Handle());
          } else {
            component.setPointer(waterToWater->demandInletPort(), Handle());
            component.setPointer(waterToWater->demandOutletPort(), Handle());
          }
        } else {
          return false;
        }
      }

      if (!keepAsDefaultBranch) {
        if (!branchList.getImpl<detail::BranchList_Impl>()->removeBranch(*targetBranch)) {
          return false;
        }
      }

      targetBranch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->clearComponents();

      if (!keepAsDefaultBranch) {
        targetBranch->remove();
      }

      if (!syncConnectorPorts(splitter, mixer, demandInletBranch(), demandOutletBranch(), demandEquipmentBranches())) {
        return false;
      }

      if (!getObject<PlantLoop>().getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, supplyOutletNode().handle(), false));
      }

      return true;
    }

    void PlantLoop_Impl::doCanonicalize(LoadContext& context) {
      auto plantLoop = getObject<PlantLoop>();
      OS_ASSERT(!plantLoop.nameString().empty());
      const auto loopName = plantLoop.nameString();

      if (auto value = getString(openstudio::PlantLoopFields::MaximumLoopTemperature, true); !value || value->empty()) {
        OS_ASSERT(setMaximumLoopTemperature(100.0));
      }
      if (auto value = getString(openstudio::PlantLoopFields::MinimumLoopTemperature, true); !value || value->empty()) {
        OS_ASSERT(setMinimumLoopTemperature(0.0));
      }
      if (auto value = getString(openstudio::PlantLoopFields::MaximumLoopFlowRate, true); !value || value->empty()) {
        autosizeMaximumLoopFlowRate();
      }
      if (auto value = getString(openstudio::PlantLoopFields::MinimumLoopFlowRate, true); !value || value->empty()) {
        OS_ASSERT(setMinimumLoopFlowRate(0.0));
      }
      if (auto value = getString(openstudio::PlantLoopFields::PlantLoopVolume, true); !value || value->empty()) {
        autocalculatePlantLoopVolume();
      }

      // Canonical PlantLoop shape:
      // - each side has an inlet node and an outlet node on the PlantLoop object
      // - each side has a BranchList ordered as inlet branch, equipment branches,
      //   outlet branch
      // - each side has a splitter/mixer pair whose ports point at those branches
      //   in BranchList order
      //
      // This mirrors the baseline topology created by openstudio::model::PlantLoop:
      // inlet node -> splitter -> equipment branch region -> mixer -> outlet node.
      // Imported IDF can arrive in looser shapes, so canonicalization repairs it
      // into this form before normal API methods run.
      //
      // In particular:
      // - zero branches becomes one inlet branch, one equipment branch, one outlet branch
      // - one branch is treated as the equipment branch, with inlet/outlet added around it
      // - two branches are treated as parallel equipment branches, with inlet/outlet
      //   added around them
      // - three or more branches are interpreted as inlet / equipment... / outlet
      //
      // After this method returns, accessors and topology operations are allowed to
      // assume the repaired shape and assert on violations instead of carrying
      // defensive fallback logic.

      // Canonical topology anchor points.
      // These node references are the loop entry/exit contracts for plant
      // supply and demand traversal. Materialize them first so branch and
      // connector repair has stable anchors to attach to.
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::PlantSideInletNodeName, loopName + " Supply Inlet Node");
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::PlantSideOutletNodeName, loopName + " Supply Outlet Node");
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::DemandSideInletNodeName, loopName + " Demand Inlet Node");
      getOrCreateTarget<Node>(openstudio::PlantLoopFields::DemandSideOutletNodeName, loopName + " Demand Outlet Node");

      // Plant-side BranchList is the E+ source-of-truth for branch order.
      // Keep the canonical inlet/equipment/outlet branch contract intact so
      // traversal and branch mutation can reason from stored branch order.
      const auto supplyBranchListName = loopName + " Supply Branch List";
      auto supplyBranchListTarget = getOrCreateTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName, supplyBranchListName);
      if (supplyBranchListTarget.nameString().empty()) {
        supplyBranchListTarget.setName(supplyBranchListName);
      }

      auto supplyBranchListImpl = supplyBranchListTarget.getImpl<detail::BranchList_Impl>();

      auto supplyBranches = supplyBranchListTarget.branches();
      if (supplyBranches.empty()) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Supply Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(inletBranch);

        Branch equipmentBranch(model());
        if (!equipmentBranch.setName(loopName + " Supply Branch 1")) {
          equipmentBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(equipmentBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Supply Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(outletBranch);
        detail::addLoadInfo(context, "Created canonical plant-side branches for PlantLoop '" + loopName + "'.");
        supplyBranches = supplyBranchListTarget.branches();
      } else if (supplyBranches.size() == 1u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Supply Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Supply Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context, "Plant-side BranchList for PlantLoop '" + loopName
                                          + "' only had one branch. Treated it as the equipment branch and added inlet and outlet branches.");
        supplyBranches = supplyBranchListTarget.branches();
      } else if (supplyBranches.size() == 2u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Supply Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Supply Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        supplyBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context,
                               "Plant-side BranchList for PlantLoop '" + loopName
                                 + "' only had two branches. Preserved both as parallel equipment branches and added inlet and outlet branches.");
        supplyBranches = supplyBranchListTarget.branches();
      }

      if (supplyBranches.front().nameString().empty()) {
        supplyBranches.front().setName(loopName + " Supply Inlet Branch");
      }
      if (supplyBranches.back().nameString().empty()) {
        supplyBranches.back().setName(loopName + " Supply Outlet Branch");
      }
      for (unsigned i = 1u; i + 1u < supplyBranches.size(); ++i) {
        if (supplyBranches[i].nameString().empty()) {
          supplyBranches[i].setName(loopName + " Supply Branch " + std::to_string(i));
        }
      }

      // Demand-side BranchList mirrors the same inlet/equipment/outlet contract.
      // Demand topology uses separate branch storage but the same traversal
      // assumptions as plant side.
      const auto demandBranchListName = loopName + " Demand Branch List";
      auto demandBranchListTarget = getOrCreateTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName, demandBranchListName);
      if (demandBranchListTarget.nameString().empty()) {
        demandBranchListTarget.setName(demandBranchListName);
      }

      auto demandBranchListImpl = demandBranchListTarget.getImpl<detail::BranchList_Impl>();

      auto demandBranches = demandBranchListTarget.branches();
      if (demandBranches.empty()) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Demand Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(inletBranch);

        Branch equipmentBranch(model());
        if (!equipmentBranch.setName(loopName + " Demand Branch 1")) {
          equipmentBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(equipmentBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Demand Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(outletBranch);
        detail::addLoadInfo(context, "Created canonical demand-side branches for PlantLoop '" + loopName + "'.");
        demandBranches = demandBranchListTarget.branches();
      } else if (demandBranches.size() == 1u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Demand Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Demand Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context, "Demand-side BranchList for PlantLoop '" + loopName
                                          + "' only had one branch. Treated it as the equipment branch and added inlet and outlet branches.");
        demandBranches = demandBranchListTarget.branches();
      } else if (demandBranches.size() == 2u) {
        Branch inletBranch(model());
        if (!inletBranch.setName(loopName + " Demand Inlet Branch")) {
          inletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->insertBranch(0u, inletBranch);

        Branch outletBranch(model());
        if (!outletBranch.setName(loopName + " Demand Outlet Branch")) {
          outletBranch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
        }
        demandBranchListImpl->addBranch(outletBranch);
        detail::addLoadWarning(context,
                               "Demand-side BranchList for PlantLoop '" + loopName
                                 + "' only had two branches. Preserved both as parallel equipment branches and added inlet and outlet branches.");
        demandBranches = demandBranchListTarget.branches();
      }

      if (demandBranches.front().nameString().empty()) {
        demandBranches.front().setName(loopName + " Demand Inlet Branch");
      }
      if (demandBranches.back().nameString().empty()) {
        demandBranches.back().setName(loopName + " Demand Outlet Branch");
      }
      for (unsigned i = 1u; i + 1u < demandBranches.size(); ++i) {
        if (demandBranches[i].nameString().empty()) {
          demandBranches[i].setName(loopName + " Demand Branch " + std::to_string(i));
        }
      }

      // Canonicalize the branch rows first so the branch names are stable
      // before we materialize the empty equipment-branch nodes that the
      // connector paths expect to exist.
      auto supplyBranchListObject = supplyBranchList();
      for (const auto& branch : supplyBranchListObject.branches()) {
        if (auto branchImpl = branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()) {
          branchImpl->canonicalize(context);
        }
      }

      for (const auto& branch : supplyEquipmentBranches()) {
        if (branch.components().empty()) {
          model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
        }
      }

      auto demandBranchListObject = demandBranchList();
      for (const auto& branch : demandBranchListObject.branches()) {
        if (auto branchImpl = branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()) {
          branchImpl->canonicalize(context);
        }
      }

      for (const auto& branch : demandEquipmentBranches()) {
        if (branch.components().empty()) {
          model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
        }
      }

      // Plant-side splitter/mixer pair are keyed by inlet/outlet branches.
      // These connector objects are the fan-out/fan-in connective tissue for
      // the canonical plant-side equipment branches.
      const auto supplyInletBranchRef = supplyInletBranch();
      const auto supplyOutletBranchRef = supplyOutletBranch();
      const auto supplyEquipmentBranchRefs = supplyEquipmentBranches();

      boost::optional<ConnectorSplitter> supplySplitterObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = candidate.getModelObjectTarget<Branch>(candidate.inletPort());
        if (!inlet || !(*inlet == supplyInletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != supplyEquipmentBranchRefs.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < supplyEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.outletPort(i));
          if (!branch || !(*branch == supplyEquipmentBranchRefs[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          supplySplitterObject = candidate;
          break;
        }
      }
      if (!supplySplitterObject) {
        supplySplitterObject = ConnectorSplitter(model());
        supplySplitterObject->setName(loopName + " Supply Splitter");
        detail::addLoadInfo(context, "Created missing plant-side Connector:Splitter '" + supplySplitterObject->nameString() + "' for PlantLoop '"
                                       + loopName + "'.");
      }

      boost::optional<ConnectorMixer> supplyMixerObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = candidate.getModelObjectTarget<Branch>(candidate.outletPort());
        if (!outlet || !(*outlet == supplyOutletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != supplyEquipmentBranchRefs.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < supplyEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.inletPort(i));
          if (!branch || !(*branch == supplyEquipmentBranchRefs[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          supplyMixerObject = candidate;
          break;
        }
      }
      if (!supplyMixerObject) {
        supplyMixerObject = ConnectorMixer(model());
        supplyMixerObject->setName(loopName + " Supply Mixer");
        detail::addLoadInfo(context,
                            "Created missing plant-side Connector:Mixer '" + supplyMixerObject->nameString() + "' for PlantLoop '" + loopName + "'.");
      }

      if ((supplySplitterObject->nextBranchIndex() != supplyEquipmentBranchRefs.size())
          || (supplyMixerObject->nextBranchIndex() != supplyEquipmentBranchRefs.size())) {
        detail::addLoadWarning(context,
                               "Plant-side connector port count mismatch for PlantLoop '" + loopName + "'. Rebuilding ports from BranchList order.");
      }

      OS_ASSERT(
        syncConnectorPorts(*supplySplitterObject, *supplyMixerObject, supplyInletBranchRef, supplyOutletBranchRef, supplyEquipmentBranchRefs));

      auto ensureConnectorList = [&](int field, const std::string& listName, const ModelObject& splitter, const ModelObject& mixer) {
        auto connectorList = plantLoop.getModelObjectTarget<ModelObject>(field);
        if (!connectorList || connectorList->iddObject().type() != openstudio::IddObjectType::ConnectorList) {
          connectorList = ModelObject::create(openstudio::IddObjectType::ConnectorList, model());
          connectorList->setName(listName);
          OS_ASSERT(setPointer(field, connectorList->handle(), false));
        }

        connectorList->clearExtensibleGroups();
        for (const auto& connector : {splitter, mixer}) {
          auto group = connectorList->pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
          OS_ASSERT(group);
          OS_ASSERT(group->setString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType, connector.iddObject().name()));
          OS_ASSERT(group->setPointer(openstudio::ConnectorListExtensibleFields::ConnectorName, connector.handle(), false));
        }
      };

      ensureConnectorList(openstudio::PlantLoopFields::PlantSideConnectorListName, loopName + " Supply Connector List",
                          supplySplitterObject->cast<ModelObject>(), supplyMixerObject->cast<ModelObject>());

      // Demand-side splitter/mixer pair mirror the same branch contract.
      // Keep the branch ports synchronized to the BranchList instead of
      // letting connector extensibles become an independent source of truth.
      const auto demandInletBranchRef = demandInletBranch();
      const auto demandOutletBranchRef = demandOutletBranch();
      const auto demandEquipmentBranchRefs = demandEquipmentBranches();

      boost::optional<ConnectorSplitter> demandSplitterObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inlet = candidate.getModelObjectTarget<Branch>(candidate.inletPort());
        if (!inlet || !(*inlet == demandInletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != demandEquipmentBranchRefs.size()) {
          continue;
        }

        bool allOutletsMatch = true;
        for (unsigned i = 0; i < demandEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.outletPort(i));
          if (!branch || !(*branch == demandEquipmentBranchRefs[i])) {
            allOutletsMatch = false;
            break;
          }
        }

        if (allOutletsMatch) {
          demandSplitterObject = candidate;
          break;
        }
      }
      if (!demandSplitterObject) {
        demandSplitterObject = ConnectorSplitter(model());
        demandSplitterObject->setName(loopName + " Demand Splitter");
        detail::addLoadInfo(context, "Created missing demand-side Connector:Splitter '" + demandSplitterObject->nameString() + "' for PlantLoop '"
                                       + loopName + "'.");
      }

      boost::optional<ConnectorMixer> demandMixerObject;
      for (const auto& candidate : model().getConcreteModelObjects<ConnectorMixer>()) {
        auto outlet = candidate.getModelObjectTarget<Branch>(candidate.outletPort());
        if (!outlet || !(*outlet == demandOutletBranchRef)) {
          continue;
        }

        if (candidate.nextBranchIndex() != demandEquipmentBranchRefs.size()) {
          continue;
        }

        bool allInletsMatch = true;
        for (unsigned i = 0; i < demandEquipmentBranchRefs.size(); ++i) {
          auto branch = candidate.getModelObjectTarget<Branch>(candidate.inletPort(i));
          if (!branch || !(*branch == demandEquipmentBranchRefs[i])) {
            allInletsMatch = false;
            break;
          }
        }

        if (allInletsMatch) {
          demandMixerObject = candidate;
          break;
        }
      }
      if (!demandMixerObject) {
        demandMixerObject = ConnectorMixer(model());
        demandMixerObject->setName(loopName + " Demand Mixer");
        detail::addLoadInfo(context, "Created missing demand-side Connector:Mixer '" + demandMixerObject->nameString() + "' for PlantLoop '"
                                       + loopName + "'.");
      }

      if ((demandSplitterObject->nextBranchIndex() != demandEquipmentBranchRefs.size())
          || (demandMixerObject->nextBranchIndex() != demandEquipmentBranchRefs.size())) {
        detail::addLoadWarning(context,
                               "Demand-side connector port count mismatch for PlantLoop '" + loopName + "'. Rebuilding ports from BranchList order.");
      }

      OS_ASSERT(
        syncConnectorPorts(*demandSplitterObject, *demandMixerObject, demandInletBranchRef, demandOutletBranchRef, demandEquipmentBranchRefs));
      ensureConnectorList(openstudio::PlantLoopFields::DemandSideConnectorListName, loopName + " Demand Connector List",
                          demandSplitterObject->cast<ModelObject>(), demandMixerObject->cast<ModelObject>());

      // PlantLoop owns one canonical setpoint anchor, one sizing object, and
      // one availability-manager assignment list. Create or repair them here so
      // the public loop-facing APIs can trust that these relationships exist.
      if (auto setpointNode = plantLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
        (void)setpointNode;
      } else {
        const auto originalSetpointNodeName = plantLoop.getString(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName);
        bool repairedByName = false;
        if (originalSetpointNodeName && !originalSetpointNodeName->empty()) {
          for (const auto& candidate : model().getObjectsByName(*originalSetpointNodeName, true)) {
            if (auto node = candidate.optionalCast<Node>()) {
              OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, node->handle(), false));
              detail::addLoadWarning(context, "Recovered Loop Temperature Setpoint Node for PlantLoop '" + loopName + "' by matching Node '"
                                                + node->nameString() + "' by name.");
              repairedByName = true;
              break;
            }
          }
        }

        if (!repairedByName) {
          OS_ASSERT(setPointer(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, supplyOutletNode().handle(), false));
          if (originalSetpointNodeName && !originalSetpointNodeName->empty()) {
            detail::addLoadWarning(context, "PlantLoop '" + loopName
                                              + "' had an invalid Loop Temperature Setpoint Node reference. Reset it to the supply outlet node.");
          } else {
            detail::addLoadInfo(context, "Created default Loop Temperature Setpoint Node reference for PlantLoop '" + loopName
                                           + "' on the supply outlet node.");
          }
        }
      }

      std::vector<SizingPlant> sizingPlantsForLoop;
      for (const auto& candidate : model().getConcreteModelObjects<SizingPlant>()) {
        auto ownedLoop = candidate.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
        if (ownedLoop && (*ownedLoop == plantLoop)) {
          sizingPlantsForLoop.push_back(candidate);
        }
      }

      if (sizingPlantsForLoop.empty()) {
        SizingPlant sizingPlant(model(), plantLoop);
        if (!sizingPlant.setName(loopName + " Sizing Plant")) {
          sizingPlant.setName(model().nextName(openstudio::IddObjectType::Sizing_Plant, true));
        }
        detail::addLoadInfo(context, "Created missing Sizing:Plant '" + sizingPlant.nameString() + "' for PlantLoop '" + loopName + "'.");
      } else if (sizingPlantsForLoop.size() > 1u) {
        for (unsigned i = 1u; i < sizingPlantsForLoop.size(); ++i) {
          OS_ASSERT(sizingPlantsForLoop[i].setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));
        }
        detail::addLoadWarning(context, "PlantLoop '" + loopName + "' had multiple Sizing:Plant objects attached. Kept '"
                                          + sizingPlantsForLoop.front().nameString() + "' and detached the extras.");
      }

      auto assignmentList = getOrCreateTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName,
                                                                                 loopName + " Availability Manager List");
      if (assignmentList.nameString().empty()) {
        assignmentList.setName(loopName + " Availability Manager List");
      }
      assignmentList.getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->canonicalize(context);

      auto operationSchemes = getOrCreateTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName,
                                                                                loopName + " Operation Schemes");
      if (operationSchemes.nameString().empty()) {
        operationSchemes.setName(loopName + " Operation Schemes");
      }
      operationSchemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>()->canonicalize(context);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
