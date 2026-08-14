/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "ScopedTestFailure.hpp"
#include "../TestFailurePoint.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"
#include "../Model.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Mixer/Mixer.hpp"
#include "../Mixer/ConnectorMixer.hpp"
#include "../Mixer/ConnectorMixer_Impl.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "../Splitter/Splitter.hpp"
#include "../Splitter/ConnectorSplitter.hpp"
#include "../Splitter/ConnectorSplitter_Impl.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/Branch_Impl.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../ModelObject/AirLoopHVACControllerList.hpp"
#include "../ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../ModelObject/SizingPlant_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"
#include "../StraightComponent/BoilerHotWater_Impl.hpp"
#include "../StraightComponent/CoolingTowerSingleSpeed.hpp"
#include "../StraightComponent/CoolingTowerSingleSpeed_Impl.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../StraightComponent/PipeAdiabatic_Impl.hpp"
#include "../StraightComponent/PumpVariableSpeed.hpp"
#include "../StraightComponent/PumpVariableSpeed_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanConstantVolume_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "../WaterToAirComponent/WaterToAirComponent.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../WaterToWaterComponent/HeatExchangerFluidToFluid.hpp"
#include "../WaterToWaterComponent/HeatExchangerFluidToFluid_Impl.hpp"
#include "../scaffolds/ThermalStorageChilledWaterMixed.hpp"
#include "../WaterToWaterComponent/ThermalStorageChilledWaterStratified.hpp"
#include "../WaterToWaterComponent/ThermalStorageChilledWaterStratified_Impl.hpp"
#include "../WaterToWaterComponent/WaterToWaterComponent.hpp"
#include "../WaterToWaterComponent/WaterHeaterMixed.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../ModelObject/WaterHeaterSizing_Impl.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling_Impl.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitVentilator.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ConnectorList_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_FluidToFluid_FieldEnums.hxx>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Cooling_FieldEnums.hxx>
#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Heating_FieldEnums.hxx>
#include <utilities/idd/ThermalStorage_ChilledWater_Mixed_FieldEnums.hxx>
#include <utilities/idd/ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>
#include <utilities/idd/WaterHeater_Mixed_FieldEnums.hxx>
#include <utilities/idd/WaterHeater_Sizing_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_FourPipeFanCoil_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentList_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <array>
#include <set>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

struct PlantAttachmentTopologySnapshot
{
  std::vector<openstudio::Handle> branchHandles;
  std::vector<std::vector<openstudio::Handle>> branchComponentHandles;
  std::vector<std::vector<openstudio::Handle>> branchInletNodeHandles;
  std::vector<std::vector<openstudio::Handle>> branchOutletNodeHandles;
  std::vector<openstudio::Handle> branchListHandles;
  std::vector<std::vector<openstudio::Handle>> branchListBranchHandles;
  std::vector<openstudio::Handle> splitterHandles;
  std::vector<boost::optional<openstudio::Handle>> splitterInletHandles;
  std::vector<std::vector<openstudio::Handle>> splitterOutletHandles;
  std::vector<openstudio::Handle> mixerHandles;
  std::vector<std::vector<openstudio::Handle>> mixerInletHandles;
  std::vector<boost::optional<openstudio::Handle>> mixerOutletHandles;
  std::vector<openstudio::Handle> nodeHandles;
  std::vector<openstudio::Handle> sourceComponentHandles;
  std::vector<openstudio::Handle> targetComponentHandles;
  boost::optional<openstudio::Handle> sourceSetpointTargetHandle;
  boost::optional<openstudio::Handle> targetSetpointTargetHandle;
  boost::optional<openstudio::Handle> componentInletHandle;
  boost::optional<openstudio::Handle> componentOutletHandle;

  bool operator==(const PlantAttachmentTopologySnapshot&) const = default;
};

template <typename T>
std::vector<openstudio::Handle> objectHandles(const std::vector<T>& objects) {
  std::vector<openstudio::Handle> result;
  result.reserve(objects.size());
  for (const auto& object : objects) {
    result.push_back(object.handle());
  }
  return result;
}

PlantAttachmentTopologySnapshot capturePlantTopology(const Model& model, const PlantLoop& sourceLoop, const PlantLoop& targetLoop, bool supplySide) {
  PlantAttachmentTopologySnapshot result;
  auto branches = model.getConcreteModelObjects<Branch>();
  std::ranges::sort(branches, {}, [](const auto& branch) { return branch.handle(); });
  for (const auto& branch : branches) {
    result.branchHandles.push_back(branch.handle());
    result.branchComponentHandles.push_back(objectHandles(branch.components()));

    std::vector<openstudio::Handle> inletHandles;
    std::vector<openstudio::Handle> outletHandles;
    for (unsigned i = 0u; i < branch.extensibleGroups().size(); ++i) {
      if (auto inlet = branch.componentInletNode(i)) {
        inletHandles.push_back(inlet->handle());
      }
      if (auto outlet = branch.componentOutletNode(i)) {
        outletHandles.push_back(outlet->handle());
      }
    }
    result.branchInletNodeHandles.push_back(std::move(inletHandles));
    result.branchOutletNodeHandles.push_back(std::move(outletHandles));
  }
  auto nodes = model.getConcreteModelObjects<Node>();
  std::ranges::sort(nodes, {}, [](const auto& node) { return node.handle(); });
  for (const auto& node : nodes) {
    result.nodeHandles.push_back(node.handle());
  }
  auto branchLists = model.getConcreteModelObjects<BranchList>();
  std::ranges::sort(branchLists, {}, [](const auto& branchList) { return branchList.handle(); });
  for (const auto& branchList : branchLists) {
    result.branchListHandles.push_back(branchList.handle());
    result.branchListBranchHandles.push_back(objectHandles(branchList.branches()));
  }
  auto splitters = model.getConcreteModelObjects<ConnectorSplitter>();
  std::ranges::sort(splitters, {}, [](const auto& splitter) { return splitter.handle(); });
  for (const auto& splitter : splitters) {
    result.splitterHandles.push_back(splitter.handle());
    const auto inlet = splitter.inletModelObject();
    result.splitterInletHandles.push_back(inlet ? boost::optional<openstudio::Handle>(inlet->handle()) : boost::none);
    result.splitterOutletHandles.push_back(objectHandles(splitter.outletModelObjects()));
  }
  auto mixers = model.getConcreteModelObjects<ConnectorMixer>();
  std::ranges::sort(mixers, {}, [](const auto& mixer) { return mixer.handle(); });
  for (const auto& mixer : mixers) {
    result.mixerHandles.push_back(mixer.handle());
    result.mixerInletHandles.push_back(objectHandles(mixer.inletModelObjects()));
    const auto outlet = mixer.outletModelObject();
    result.mixerOutletHandles.push_back(outlet ? boost::optional<openstudio::Handle>(outlet->handle()) : boost::none);
  }

  result.sourceComponentHandles = objectHandles(supplySide ? sourceLoop.supplyComponents() : sourceLoop.demandComponents());
  result.targetComponentHandles = objectHandles(supplySide ? targetLoop.supplyComponents() : targetLoop.demandComponents());
  if (auto sourceSetpointTarget = sourceLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
    result.sourceSetpointTargetHandle = sourceSetpointTarget->handle();
  }
  if (auto targetSetpointTarget = targetLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
    result.targetSetpointTargetHandle = targetSetpointTarget->handle();
  }
  return result;
}

PlantAttachmentTopologySnapshot capturePlantAttachmentTopology(const Model& model, const PlantLoop& sourceLoop, const PlantLoop& targetLoop,
                                                               const StraightComponent& component, bool supplySide) {
  auto result = capturePlantTopology(model, sourceLoop, targetLoop, supplySide);
  if (auto inlet = component.inletModelObject()) {
    result.componentInletHandle = inlet->handle();
  }
  if (auto outlet = component.outletModelObject()) {
    result.componentOutletHandle = outlet->handle();
  }
  return result;
}

struct FluidToFluidHeatExchangerMoveSnapshot
{
  PlantAttachmentTopologySnapshot plantTopology;
  std::vector<openstudio::Handle> modelObjectHandles;
  std::vector<std::pair<openstudio::Handle, std::vector<boost::optional<std::string>>>> modelRawFields;
  std::vector<openstudio::Handle> primarySupplyComponentHandles;
  boost::optional<openstudio::Handle> primarySetpointTargetHandle;
  boost::optional<openstudio::Handle> primaryOwnerHandle;
  boost::optional<openstudio::Handle> secondaryOwnerHandle;
  boost::optional<openstudio::Handle> supplyInletHandle;
  boost::optional<openstudio::Handle> supplyOutletHandle;
  boost::optional<openstudio::Handle> demandInletHandle;
  boost::optional<openstudio::Handle> demandOutletHandle;
  boost::optional<openstudio::Handle> availabilityScheduleHandle;
  boost::optional<openstudio::Handle> supplyOverrideHandle;
  boost::optional<openstudio::Handle> demandOverrideHandle;
  std::vector<boost::optional<std::string>> heatExchangerRawFields;
  std::array<boost::optional<std::string>, 3> setpointRawFields;

  bool operator==(const FluidToFluidHeatExchangerMoveSnapshot&) const = default;
};

boost::optional<std::string> rawField(const openstudio::WorkspaceObject& object, unsigned field) {
  auto workspaceImpl = object.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  EXPECT_TRUE(workspaceImpl);
  return workspaceImpl ? workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true) : boost::none;
}

FluidToFluidHeatExchangerMoveSnapshot captureFluidToFluidHeatExchangerMove(const Model& model, const PlantLoop& primaryLoop,
                                                                           const PlantLoop& sourceLoop, const PlantLoop& targetLoop,
                                                                           const HeatExchangerFluidToFluid& heatExchanger,
                                                                           bool observeComponentOwners = true) {
  FluidToFluidHeatExchangerMoveSnapshot result;
  if (observeComponentOwners) {
    result.plantTopology = capturePlantTopology(model, sourceLoop, targetLoop, false);
  }
  auto objects = model.objects();
  std::ranges::sort(objects, {}, [](const auto& object) { return object.handle(); });
  for (const auto& object : objects) {
    result.modelObjectHandles.push_back(object.handle());
    std::vector<boost::optional<std::string>> fields;
    for (unsigned field = 0u; field < object.numFields(); ++field) {
      fields.push_back(rawField(object, field));
    }
    while (!fields.empty() && !fields.back()) {
      fields.pop_back();
    }
    result.modelRawFields.emplace_back(object.handle(), std::move(fields));
  }
  if (observeComponentOwners) {
    result.primarySupplyComponentHandles = objectHandles(primaryLoop.supplyComponents());
  }
  if (auto setpointTarget = primaryLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
    result.primarySetpointTargetHandle = setpointTarget->handle();
  }
  if (observeComponentOwners) {
    if (auto owner = heatExchanger.plantLoop()) {
      result.primaryOwnerHandle = owner->handle();
    }
    if (auto owner = heatExchanger.secondaryPlantLoop()) {
      result.secondaryOwnerHandle = owner->handle();
    }
  }
  if (auto node = heatExchanger.supplyInletModelObject()) {
    result.supplyInletHandle = node->handle();
  }
  if (auto node = heatExchanger.supplyOutletModelObject()) {
    result.supplyOutletHandle = node->handle();
  }
  if (auto node = heatExchanger.demandInletModelObject()) {
    result.demandInletHandle = node->handle();
  }
  if (auto node = heatExchanger.demandOutletModelObject()) {
    result.demandOutletHandle = node->handle();
  }
  if (auto schedule = heatExchanger.availabilitySchedule()) {
    result.availabilityScheduleHandle = schedule->handle();
  }
  if (auto node = heatExchanger.componentOverrideLoopSupplySideInletNode()) {
    result.supplyOverrideHandle = node->handle();
  }
  if (auto node = heatExchanger.componentOverrideLoopDemandSideInletNode()) {
    result.demandOverrideHandle = node->handle();
  }
  for (unsigned field = 0u; field < heatExchanger.numFields(); ++field) {
    result.heatExchangerRawFields.push_back(rawField(heatExchanger, field));
  }
  result.setpointRawFields = {rawField(primaryLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName),
                              rawField(sourceLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName),
                              rawField(targetLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)};
  return result;
}

struct EquationFitHeatPumpMoveSnapshot
{
  PlantAttachmentTopologySnapshot plantTopology;
  std::vector<openstudio::Handle> modelObjectHandles;
  std::vector<std::pair<openstudio::Handle, std::vector<boost::optional<std::string>>>> modelRawFields;
  std::vector<openstudio::Handle> primarySupplyComponentHandles;
  boost::optional<openstudio::Handle> primarySetpointTargetHandle;
  boost::optional<openstudio::Handle> primaryOwnerHandle;
  boost::optional<openstudio::Handle> secondaryOwnerHandle;
  boost::optional<openstudio::Handle> supplyInletHandle;
  boost::optional<openstudio::Handle> supplyOutletHandle;
  boost::optional<openstudio::Handle> demandInletHandle;
  boost::optional<openstudio::Handle> demandOutletHandle;
  std::array<boost::optional<std::string>, 3> setpointRawFields;

  bool operator==(const EquationFitHeatPumpMoveSnapshot&) const = default;
};

struct ThermalStorageMoveSnapshot
{
  PlantAttachmentTopologySnapshot plantTopology;
  std::vector<openstudio::Handle> modelObjectHandles;
  std::vector<std::pair<openstudio::Handle, std::vector<boost::optional<std::string>>>> modelRawFields;
  std::vector<openstudio::Handle> primarySupplyComponentHandles;
  boost::optional<openstudio::Handle> primarySetpointTargetHandle;
  boost::optional<openstudio::Handle> primaryOwnerHandle;
  boost::optional<openstudio::Handle> secondaryOwnerHandle;
  boost::optional<openstudio::Handle> supplyInletHandle;
  boost::optional<openstudio::Handle> supplyOutletHandle;
  boost::optional<openstudio::Handle> demandInletHandle;
  boost::optional<openstudio::Handle> demandOutletHandle;
  boost::optional<openstudio::Handle> sizingHandle;
  boost::optional<openstudio::Handle> setpointScheduleHandle;
  boost::optional<openstudio::Handle> ambientScheduleHandle;
  boost::optional<openstudio::Handle> useSideScheduleHandle;
  boost::optional<openstudio::Handle> sourceSideScheduleHandle;
  boost::optional<openstudio::Handle> ambientZoneHandle;
  boost::optional<std::string> ambientOutdoorAirNodeName;
  std::vector<boost::optional<std::string>> storageRawFields;
  std::vector<boost::optional<std::string>> sizingRawFields;
  std::array<boost::optional<std::string>, 3> setpointRawFields;

  bool operator==(const ThermalStorageMoveSnapshot&) const = default;
};

ThermalStorageMoveSnapshot captureThermalStorageMove(const Model& model, const PlantLoop& primaryLoop, const PlantLoop& sourceLoop,
                                                     const PlantLoop& targetLoop, const ThermalStorageChilledWaterStratified& storage,
                                                     bool observeOwners = true) {
  ThermalStorageMoveSnapshot result;
  if (observeOwners) {
    result.plantTopology = capturePlantTopology(model, sourceLoop, targetLoop, false);
    result.primarySupplyComponentHandles = objectHandles(primaryLoop.supplyComponents());
  }
  auto objects = model.objects();
  std::ranges::sort(objects, {}, [](const auto& object) { return object.handle(); });
  for (const auto& object : objects) {
    result.modelObjectHandles.push_back(object.handle());
    std::vector<boost::optional<std::string>> fields;
    for (unsigned field = 0u; field < object.numFields(); ++field) {
      fields.push_back(rawField(object, field));
    }
    while (!fields.empty() && !fields.back()) {
      fields.pop_back();
    }
    result.modelRawFields.emplace_back(object.handle(), std::move(fields));
  }
  if (auto setpointTarget = primaryLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
    result.primarySetpointTargetHandle = setpointTarget->handle();
  }
  if (observeOwners) {
    if (auto owner = storage.plantLoop()) {
      result.primaryOwnerHandle = owner->handle();
    }
    if (auto owner = storage.secondaryPlantLoop()) {
      result.secondaryOwnerHandle = owner->handle();
    }
  }
  if (auto node = storage.supplyInletModelObject()) {
    result.supplyInletHandle = node->handle();
  }
  if (auto node = storage.supplyOutletModelObject()) {
    result.supplyOutletHandle = node->handle();
  }
  if (auto node = storage.demandInletModelObject()) {
    result.demandInletHandle = node->handle();
  }
  if (auto node = storage.demandOutletModelObject()) {
    result.demandOutletHandle = node->handle();
  }
  try {
    const auto sizing = storage.waterHeaterSizing();
    result.sizingHandle = sizing.handle();
    for (unsigned field = 0u; field < sizing.numFields(); ++field) {
      result.sizingRawFields.push_back(rawField(sizing, field));
    }
  } catch (const std::exception&) {
  }
  if (auto schedule = storage.setpointTemperatureSchedule()) {
    result.setpointScheduleHandle = schedule->handle();
  }
  if (auto schedule = storage.ambientTemperatureSchedule()) {
    result.ambientScheduleHandle = schedule->handle();
  }
  if (auto schedule = storage.useSideAvailabilitySchedule()) {
    result.useSideScheduleHandle = schedule->handle();
  }
  if (auto schedule = storage.sourceSideAvailabilitySchedule()) {
    result.sourceSideScheduleHandle = schedule->handle();
  }
  if (auto zone = storage.ambientTemperatureThermalZone()) {
    result.ambientZoneHandle = zone->handle();
  }
  result.ambientOutdoorAirNodeName = storage.ambientTemperatureOutdoorAirNodeName();
  for (unsigned field = 0u; field < storage.numFields(); ++field) {
    result.storageRawFields.push_back(rawField(storage, field));
  }
  result.setpointRawFields = {rawField(primaryLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName),
                              rawField(sourceLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName),
                              rawField(targetLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)};
  return result;
}

EquationFitHeatPumpMoveSnapshot captureEquationFitHeatPumpMove(const Model& model, const PlantLoop& primaryLoop, const PlantLoop& sourceLoop,
                                                               const PlantLoop& targetLoop, const WaterToWaterComponent& heatPump,
                                                               bool observeTopology = true) {
  EquationFitHeatPumpMoveSnapshot result;
  if (observeTopology) {
    result.plantTopology = capturePlantTopology(model, sourceLoop, targetLoop, false);
    result.primarySupplyComponentHandles = objectHandles(primaryLoop.supplyComponents());
  }
  auto objects = model.objects();
  std::ranges::sort(objects, {}, [](const auto& object) { return object.handle(); });
  for (const auto& object : objects) {
    result.modelObjectHandles.push_back(object.handle());
    std::vector<boost::optional<std::string>> fields;
    for (unsigned field = 0u; field < object.numFields(); ++field) {
      fields.push_back(rawField(object, field));
    }
    while (!fields.empty() && !fields.back()) {
      fields.pop_back();
    }
    result.modelRawFields.emplace_back(object.handle(), std::move(fields));
  }
  if (auto setpointTarget = primaryLoop.getModelObjectTarget<Node>(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)) {
    result.primarySetpointTargetHandle = setpointTarget->handle();
  }
  if (observeTopology) {
    if (auto owner = heatPump.plantLoop()) {
      result.primaryOwnerHandle = owner->handle();
    }
    if (auto owner = heatPump.secondaryPlantLoop()) {
      result.secondaryOwnerHandle = owner->handle();
    }
  }
  if (auto node = heatPump.supplyInletModelObject()) {
    result.supplyInletHandle = node->handle();
  }
  if (auto node = heatPump.supplyOutletModelObject()) {
    result.supplyOutletHandle = node->handle();
  }
  if (auto node = heatPump.demandInletModelObject()) {
    result.demandInletHandle = node->handle();
  }
  if (auto node = heatPump.demandOutletModelObject()) {
    result.demandOutletHandle = node->handle();
  }
  result.setpointRawFields = {rawField(primaryLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName),
                              rawField(sourceLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName),
                              rawField(targetLoop, openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName)};
  return result;
}

std::vector<std::pair<openstudio::Handle, boost::optional<std::string>>> equationFitCompanionRawFields(const Model& model) {
  std::vector<std::pair<openstudio::Handle, boost::optional<std::string>>> result;
  for (const auto& heating : model.getConcreteModelObjects<HeatPumpWaterToWaterEquationFitHeating>()) {
    result.emplace_back(heating.handle(),
                        rawField(heating, openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName));
  }
  for (const auto& cooling : model.getConcreteModelObjects<HeatPumpWaterToWaterEquationFitCooling>()) {
    result.emplace_back(cooling.handle(),
                        rawField(cooling, openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::CompanionHeatingHeatPumpName));
  }
  std::ranges::sort(result, {}, [](const auto& field) { return field.first; });
  return result;
}

struct WaterCoilMoveTopologySnapshot
{
  PlantAttachmentTopologySnapshot plantTopology;
  openstudio::Handle coilHandle;
  std::vector<openstudio::Handle> airSupplyComponentHandles;
  boost::optional<openstudio::Handle> airLoopHandle;
  boost::optional<openstudio::Handle> plantLoopHandle;
  boost::optional<openstudio::Handle> airInletHandle;
  boost::optional<openstudio::Handle> airOutletHandle;
  boost::optional<openstudio::Handle> waterInletHandle;
  boost::optional<openstudio::Handle> waterOutletHandle;
  std::vector<openstudio::Handle> controllerHandles;
  std::vector<boost::optional<std::string>> controllerActions;
  std::vector<boost::optional<openstudio::Handle>> controllerActuatorHandles;
  std::vector<boost::optional<openstudio::Handle>> controllerSensorHandles;
  std::vector<openstudio::Handle> controllerListHandles;
  std::vector<std::vector<openstudio::Handle>> controllerListControllerHandles;

  bool operator==(const WaterCoilMoveTopologySnapshot&) const = default;
};

WaterCoilMoveTopologySnapshot captureWaterCoilMoveTopology(const Model& model, const PlantLoop& sourceLoop, const PlantLoop& targetLoop,
                                                           const AirLoopHVAC& airLoop, const WaterToAirComponent& coil) {
  WaterCoilMoveTopologySnapshot result;
  result.plantTopology = capturePlantTopology(model, sourceLoop, targetLoop, false);
  result.coilHandle = coil.handle();
  result.airSupplyComponentHandles = objectHandles(airLoop.supplyComponents());
  if (auto owner = coil.airLoopHVAC()) {
    result.airLoopHandle = owner->handle();
  }
  if (auto owner = coil.plantLoop()) {
    result.plantLoopHandle = owner->handle();
  }
  if (auto node = coil.airInletModelObject()) {
    result.airInletHandle = node->handle();
  }
  if (auto node = coil.airOutletModelObject()) {
    result.airOutletHandle = node->handle();
  }
  if (auto node = coil.waterInletModelObject()) {
    result.waterInletHandle = node->handle();
  }
  if (auto node = coil.waterOutletModelObject()) {
    result.waterOutletHandle = node->handle();
  }
  for (const auto& controller : model.getConcreteModelObjects<ControllerWaterCoil>()) {
    result.controllerHandles.push_back(controller.handle());
    result.controllerActions.push_back(controller.action());
    const auto actuatorNode = controller.actuatorNode();
    const auto sensorNode = controller.sensorNode();
    result.controllerActuatorHandles.push_back(actuatorNode ? boost::optional<openstudio::Handle>(actuatorNode->handle()) : boost::none);
    result.controllerSensorHandles.push_back(sensorNode ? boost::optional<openstudio::Handle>(sensorNode->handle()) : boost::none);
  }
  for (const auto& controllerList : model.getConcreteModelObjects<AirLoopHVACControllerList>()) {
    result.controllerListHandles.push_back(controllerList.handle());
    result.controllerListControllerHandles.push_back(objectHandles(controllerList.controllers()));
  }
  return result;
}

void expectWaterCoilMoveTopologyEqual(const WaterCoilMoveTopologySnapshot& expected, const WaterCoilMoveTopologySnapshot& actual) {
  EXPECT_EQ(expected.plantTopology.branchHandles, actual.plantTopology.branchHandles);
  EXPECT_EQ(expected.plantTopology.branchComponentHandles, actual.plantTopology.branchComponentHandles);
  EXPECT_EQ(expected.plantTopology.branchInletNodeHandles, actual.plantTopology.branchInletNodeHandles);
  EXPECT_EQ(expected.plantTopology.branchOutletNodeHandles, actual.plantTopology.branchOutletNodeHandles);
  EXPECT_EQ(expected.plantTopology.branchListHandles, actual.plantTopology.branchListHandles);
  EXPECT_EQ(expected.plantTopology.branchListBranchHandles, actual.plantTopology.branchListBranchHandles);
  EXPECT_EQ(expected.plantTopology.splitterHandles, actual.plantTopology.splitterHandles);
  EXPECT_TRUE(expected.plantTopology.splitterInletHandles == actual.plantTopology.splitterInletHandles);
  EXPECT_EQ(expected.plantTopology.splitterOutletHandles, actual.plantTopology.splitterOutletHandles);
  EXPECT_EQ(expected.plantTopology.mixerHandles, actual.plantTopology.mixerHandles);
  EXPECT_EQ(expected.plantTopology.mixerInletHandles, actual.plantTopology.mixerInletHandles);
  EXPECT_TRUE(expected.plantTopology.mixerOutletHandles == actual.plantTopology.mixerOutletHandles);
  EXPECT_EQ(expected.plantTopology.nodeHandles, actual.plantTopology.nodeHandles);
  EXPECT_EQ(expected.plantTopology.sourceComponentHandles, actual.plantTopology.sourceComponentHandles);
  EXPECT_EQ(expected.plantTopology.targetComponentHandles, actual.plantTopology.targetComponentHandles);
  EXPECT_TRUE(expected.plantTopology.sourceSetpointTargetHandle == actual.plantTopology.sourceSetpointTargetHandle);
  EXPECT_TRUE(expected.plantTopology.targetSetpointTargetHandle == actual.plantTopology.targetSetpointTargetHandle);
  EXPECT_EQ(expected.coilHandle, actual.coilHandle);
  EXPECT_EQ(expected.airSupplyComponentHandles, actual.airSupplyComponentHandles);
  EXPECT_TRUE(expected.airLoopHandle == actual.airLoopHandle);
  EXPECT_TRUE(expected.plantLoopHandle == actual.plantLoopHandle);
  EXPECT_TRUE(expected.airInletHandle == actual.airInletHandle);
  EXPECT_TRUE(expected.airOutletHandle == actual.airOutletHandle);
  EXPECT_TRUE(expected.waterInletHandle == actual.waterInletHandle);
  EXPECT_TRUE(expected.waterOutletHandle == actual.waterOutletHandle);
  EXPECT_EQ(expected.controllerHandles, actual.controllerHandles);
  EXPECT_TRUE(expected.controllerActions == actual.controllerActions);
  EXPECT_TRUE(expected.controllerActuatorHandles == actual.controllerActuatorHandles);
  EXPECT_TRUE(expected.controllerSensorHandles == actual.controllerSensorHandles);
  EXPECT_EQ(expected.controllerListHandles, actual.controllerListHandles);
  EXPECT_EQ(expected.controllerListControllerHandles, actual.controllerListControllerHandles);
}

struct ContainedReheatExternalTopologySnapshot
{
  openstudio::Handle coilHandle;
  openstudio::Handle terminalHandle;
  openstudio::Handle airLoopHandle;
  openstudio::Handle thermalZoneHandle;
  std::vector<openstudio::Handle> terminalChildHandles;
  boost::optional<openstudio::Handle> coilParentHandle;
  boost::optional<openstudio::Handle> coilAirLoopHandle;
  boost::optional<openstudio::Handle> terminalAirLoopHandle;
  boost::optional<openstudio::Handle> coilAirInletHandle;
  boost::optional<openstudio::Handle> coilAirOutletHandle;
  boost::optional<openstudio::Handle> terminalAirInletHandle;
  boost::optional<openstudio::Handle> terminalAirOutletHandle;
  std::vector<openstudio::Handle> airDemandComponentHandles;
  std::vector<openstudio::Handle> airThermalZoneHandles;
  std::vector<openstudio::Handle> zoneEquipmentHandles;
  std::vector<openstudio::Handle> zoneTerminalHandles;
  std::vector<openstudio::Handle> zoneSplitterOutletHandles;
  std::vector<openstudio::Handle> zoneMixerInletHandles;
  std::vector<openstudio::Handle> airDistributionUnitHandles;
  std::vector<boost::optional<openstudio::Handle>> airDistributionUnitTerminalHandles;
  std::vector<boost::optional<openstudio::Handle>> airDistributionUnitOutletHandles;
  std::vector<openstudio::Handle> controllerHandles;
  std::vector<openstudio::Handle> controllerListHandles;
  std::vector<std::vector<openstudio::Handle>> controllerListControllerHandles;
  openstudio::Handle availabilityScheduleHandle;
  boost::optional<double> maximumAirFlowRate;
  boost::optional<double> maximumHotWaterOrSteamFlowRate;
  double minimumHotWaterOrSteamFlowRate;
  double convergenceTolerance;
  double maximumReheatAirTemperature;
  double ratedInletWaterTemperature;

  bool operator==(const ContainedReheatExternalTopologySnapshot&) const = default;
};

ContainedReheatExternalTopologySnapshot captureContainedReheatExternalTopology(const Model& model, const AirLoopHVAC& airLoop,
                                                                               const ThermalZone& thermalZone,
                                                                               const AirTerminalSingleDuctConstantVolumeReheat& terminal,
                                                                               const CoilHeatingWater& coil) {
  ContainedReheatExternalTopologySnapshot result;
  result.coilHandle = coil.handle();
  result.terminalHandle = terminal.handle();
  result.airLoopHandle = airLoop.handle();
  result.thermalZoneHandle = thermalZone.handle();
  result.terminalChildHandles = objectHandles(terminal.children());
  result.airDemandComponentHandles = objectHandles(airLoop.demandComponents());
  result.airThermalZoneHandles = objectHandles(airLoop.thermalZones());
  result.zoneEquipmentHandles = objectHandles(thermalZone.equipment());
  result.zoneTerminalHandles = objectHandles(thermalZone.airLoopHVACTerminals());
  result.zoneSplitterOutletHandles = objectHandles(airLoop.zoneSplitter().outletModelObjects());
  result.zoneMixerInletHandles = objectHandles(airLoop.zoneMixer().inletModelObjects());
  result.availabilityScheduleHandle = terminal.availabilitySchedule().handle();
  result.maximumAirFlowRate = terminal.maximumAirFlowRate();
  result.maximumHotWaterOrSteamFlowRate = terminal.maximumHotWaterorSteamFlowRate();
  result.minimumHotWaterOrSteamFlowRate = terminal.minimumHotWaterorSteamFlowRate();
  result.convergenceTolerance = terminal.convergenceTolerance();
  result.maximumReheatAirTemperature = terminal.maximumReheatAirTemperature();
  result.ratedInletWaterTemperature = coil.ratedInletWaterTemperature();

  if (auto owner = coil.containingHVACComponent()) {
    result.coilParentHandle = owner->handle();
  }
  if (auto owner = coil.airLoopHVAC()) {
    result.coilAirLoopHandle = owner->handle();
  }
  if (auto owner = terminal.airLoopHVAC()) {
    result.terminalAirLoopHandle = owner->handle();
  }
  if (auto node = coil.airInletModelObject()) {
    result.coilAirInletHandle = node->handle();
  }
  if (auto node = coil.airOutletModelObject()) {
    result.coilAirOutletHandle = node->handle();
  }
  if (auto node = terminal.inletModelObject()) {
    result.terminalAirInletHandle = node->handle();
  }
  if (auto node = terminal.outletModelObject()) {
    result.terminalAirOutletHandle = node->handle();
  }

  auto airDistributionUnits = model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>();
  std::ranges::sort(airDistributionUnits, {}, [](const auto& object) { return object.handle(); });
  for (const auto& airDistributionUnit : airDistributionUnits) {
    result.airDistributionUnitHandles.push_back(airDistributionUnit.handle());
    const auto linkedTerminal = airDistributionUnit.airTerminal();
    const auto outletNode = airDistributionUnit.outletNode();
    result.airDistributionUnitTerminalHandles.push_back(linkedTerminal ? boost::optional<openstudio::Handle>(linkedTerminal->handle()) : boost::none);
    result.airDistributionUnitOutletHandles.push_back(outletNode ? boost::optional<openstudio::Handle>(outletNode->handle()) : boost::none);
  }

  auto controllers = model.getConcreteModelObjects<ControllerWaterCoil>();
  std::ranges::sort(controllers, {}, [](const auto& controller) { return controller.handle(); });
  result.controllerHandles = objectHandles(controllers);
  auto controllerLists = model.getConcreteModelObjects<AirLoopHVACControllerList>();
  std::ranges::sort(controllerLists, {}, [](const auto& controllerList) { return controllerList.handle(); });
  for (const auto& controllerList : controllerLists) {
    result.controllerListHandles.push_back(controllerList.handle());
    result.controllerListControllerHandles.push_back(objectHandles(controllerList.controllers()));
  }
  return result;
}

struct ContainedReheatMoveTopologySnapshot
{
  PlantAttachmentTopologySnapshot plantTopology;
  ContainedReheatExternalTopologySnapshot externalTopology;
  std::vector<openstudio::Handle> modelObjectHandles;
  boost::optional<openstudio::Handle> plantLoopHandle;
  boost::optional<openstudio::Handle> waterInletHandle;
  boost::optional<openstudio::Handle> waterOutletHandle;

  bool operator==(const ContainedReheatMoveTopologySnapshot&) const = default;
};

ContainedReheatMoveTopologySnapshot captureContainedReheatMoveTopology(const Model& model, const PlantLoop& sourceLoop, const PlantLoop& targetLoop,
                                                                       const AirLoopHVAC& airLoop, const ThermalZone& thermalZone,
                                                                       const AirTerminalSingleDuctConstantVolumeReheat& terminal,
                                                                       const CoilHeatingWater& coil) {
  ContainedReheatMoveTopologySnapshot result{capturePlantTopology(model, sourceLoop, targetLoop, false),
                                             captureContainedReheatExternalTopology(model, airLoop, thermalZone, terminal, coil),
                                             {},
                                             boost::none,
                                             boost::none,
                                             boost::none};
  const auto modelObjects = model.objects();
  result.modelObjectHandles.reserve(modelObjects.size());
  for (const auto& object : modelObjects) {
    result.modelObjectHandles.push_back(object.handle());
  }
  std::ranges::sort(result.modelObjectHandles);
  if (auto owner = coil.plantLoop()) {
    result.plantLoopHandle = owner->handle();
  }
  if (auto node = coil.waterInletModelObject()) {
    result.waterInletHandle = node->handle();
  }
  if (auto node = coil.waterOutletModelObject()) {
    result.waterOutletHandle = node->handle();
  }
  return result;
}

struct FourPipeFanCoilMoveTopologySnapshot
{
  PlantAttachmentTopologySnapshot plantTopology;
  std::vector<openstudio::Handle> modelObjectHandles;
  openstudio::Handle fanCoilHandle;
  openstudio::Handle zoneHandle;
  std::vector<openstudio::Handle> childHandles;
  std::vector<openstudio::Handle> zoneEquipmentHandles;
  std::vector<openstudio::Handle> zoneInletNodeHandles;
  std::vector<openstudio::Handle> zoneExhaustNodeHandles;
  boost::optional<openstudio::Handle> fanCoilZoneHandle;
  boost::optional<std::string> fanCoilZoneName;
  std::array<boost::optional<openstudio::Handle>, 4> airLoopOwnerHandles;
  std::array<boost::optional<openstudio::Handle>, 4> outdoorAirSystemOwnerHandles;
  std::array<boost::optional<std::string>, 4> airLoopOwnerNames;
  std::array<boost::optional<std::string>, 4> outdoorAirSystemOwnerNames;
  std::array<boost::optional<openstudio::Handle>, 3> roleTargetHandles;
  std::array<boost::optional<std::string>, 3> roleTargetNames;
  std::array<boost::optional<std::string>, 3> roleTargetTypes;
  std::array<boost::optional<std::string>, 3> rawRoleNames;
  std::array<boost::optional<std::string>, 3> rawRoleTypes;
  std::array<boost::optional<openstudio::Handle>, 8> airNodeHandles;
  boost::optional<openstudio::Handle> coolingPlantLoopHandle;
  boost::optional<openstudio::Handle> heatingPlantLoopHandle;
  boost::optional<std::string> coolingPlantLoopName;
  boost::optional<std::string> heatingPlantLoopName;
  std::array<boost::optional<openstudio::Handle>, 4> waterNodeHandles;
  std::vector<openstudio::Handle> controllerHandles;
  std::vector<boost::optional<openstudio::Handle>> controllerActuatorHandles;
  std::vector<boost::optional<std::string>> rawControllerActuatorNames;
  openstudio::Handle availabilityScheduleHandle;
  std::string availabilityScheduleName;
  std::string capacityControlMethod;
  boost::optional<double> maximumSupplyAirFlowRate;
  boost::optional<double> maximumColdWaterFlowRate;
  double minimumColdWaterFlowRate;
  double coolingConvergenceTolerance;
  boost::optional<double> maximumHotWaterFlowRate;
  double minimumHotWaterFlowRate;
  double heatingConvergenceTolerance;
  boost::optional<double> fanPressureRise;
  boost::optional<double> coolingDesignWaterFlowRate;
  boost::optional<double> coolingDesignInletWaterTemperature;
  boost::optional<double> coolingDesignOutletAirTemperature;
  boost::optional<double> heatingMaximumWaterFlowRate;
  double heatingRatedInletWaterTemperature;
  double heatingRatedOutletAirTemperature;

  bool operator==(const FourPipeFanCoilMoveTopologySnapshot&) const = default;
};

FourPipeFanCoilMoveTopologySnapshot captureFourPipeFanCoilMoveTopology(const Model& model, const PlantLoop& sourceLoop, const PlantLoop& targetLoop,
                                                                       const ThermalZone& zone, const ZoneHVACFourPipeFanCoil& fanCoil,
                                                                       const StraightComponent& fan, const CoilCoolingWater& cooling,
                                                                       const CoilHeatingWater& heating) {
  FourPipeFanCoilMoveTopologySnapshot result;
  result.plantTopology = capturePlantTopology(model, sourceLoop, targetLoop, false);
  const auto modelObjects = model.objects();
  result.modelObjectHandles.reserve(modelObjects.size());
  for (const auto& object : modelObjects) {
    result.modelObjectHandles.push_back(object.handle());
  }
  std::ranges::sort(result.modelObjectHandles);

  result.fanCoilHandle = fanCoil.handle();
  result.zoneHandle = zone.handle();
  result.childHandles = objectHandles(fanCoil.children());
  result.zoneEquipmentHandles = objectHandles(zone.equipment());
  const auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  if (connections) {
    result.zoneInletNodeHandles = objectHandles(connections->zoneAirInletNodes());
    result.zoneExhaustNodeHandles = objectHandles(connections->zoneAirExhaustNodes());
  }
  if (auto owner = fanCoil.thermalZone()) {
    result.fanCoilZoneHandle = owner->handle();
    result.fanCoilZoneName = owner->nameString();
  }
  const std::array<HVACComponent, 4> airComponents = {fanCoil.cast<HVACComponent>(), fan.cast<HVACComponent>(), cooling.cast<HVACComponent>(),
                                                      heating.cast<HVACComponent>()};
  for (unsigned i = 0u; i < airComponents.size(); ++i) {
    if (auto owner = airComponents[i].airLoopHVAC()) {
      result.airLoopOwnerHandles[i] = owner->handle();
      result.airLoopOwnerNames[i] = owner->nameString();
    }
    if (auto owner = airComponents[i].airLoopHVACOutdoorAirSystem()) {
      result.outdoorAirSystemOwnerHandles[i] = owner->handle();
      result.outdoorAirSystemOwnerNames[i] = owner->nameString();
    }
  }

  const std::array<std::pair<unsigned, unsigned>, 3> roleFields = {
    std::pair{openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType},
    std::pair{openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType},
    std::pair{openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType}};
  auto fanCoilWorkspaceImpl = fanCoil.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  OS_ASSERT(fanCoilWorkspaceImpl);
  for (unsigned i = 0u; i < roleFields.size(); ++i) {
    const auto& [nameField, typeField] = roleFields[i];
    if (auto target = fanCoil.getModelObjectTarget<ModelObject>(nameField)) {
      result.roleTargetHandles[i] = target->handle();
      result.roleTargetNames[i] = target->nameString();
      result.roleTargetTypes[i] = target->iddObject().name();
    }
    result.rawRoleNames[i] = fanCoilWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(nameField, false, true);
    result.rawRoleTypes[i] = fanCoilWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(typeField, false, true);
  }

  const std::array<boost::optional<ModelObject>, 8> airNodes = {
    fanCoil.inletNode() ? boost::optional<ModelObject>(fanCoil.inletNode()->cast<ModelObject>()) : boost::none,
    fan.inletModelObject(),
    fan.outletModelObject(),
    cooling.airInletModelObject(),
    cooling.airOutletModelObject(),
    heating.airInletModelObject(),
    heating.airOutletModelObject(),
    fanCoil.outletNode() ? boost::optional<ModelObject>(fanCoil.outletNode()->cast<ModelObject>()) : boost::none};
  for (unsigned i = 0u; i < airNodes.size(); ++i) {
    if (airNodes[i]) {
      result.airNodeHandles[i] = airNodes[i]->handle();
    }
  }

  if (auto owner = cooling.plantLoop()) {
    result.coolingPlantLoopHandle = owner->handle();
    result.coolingPlantLoopName = owner->nameString();
  }
  if (auto owner = heating.plantLoop()) {
    result.heatingPlantLoopHandle = owner->handle();
    result.heatingPlantLoopName = owner->nameString();
  }
  const std::array<boost::optional<ModelObject>, 4> waterNodes = {cooling.waterInletModelObject(), cooling.waterOutletModelObject(),
                                                                  heating.waterInletModelObject(), heating.waterOutletModelObject()};
  for (unsigned i = 0u; i < waterNodes.size(); ++i) {
    if (waterNodes[i]) {
      result.waterNodeHandles[i] = waterNodes[i]->handle();
    }
  }

  auto controllers = model.getConcreteModelObjects<ControllerWaterCoil>();
  std::ranges::sort(controllers, {}, [](const auto& controller) { return controller.handle(); });
  result.controllerHandles = objectHandles(controllers);
  for (const auto& controller : controllers) {
    const auto actuator = controller.actuatorNode();
    result.controllerActuatorHandles.push_back(actuator ? boost::optional<openstudio::Handle>(actuator->handle()) : boost::none);
    auto workspaceImpl = controller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    OS_ASSERT(workspaceImpl);
    result.rawControllerActuatorNames.push_back(
      workspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Controller_WaterCoilFields::ActuatorNodeName, false, true));
  }
  result.availabilityScheduleHandle = fanCoil.availabilitySchedule().handle();
  result.availabilityScheduleName = fanCoil.availabilitySchedule().nameString();
  result.capacityControlMethod = fanCoil.capacityControlMethod();
  result.maximumSupplyAirFlowRate = fanCoil.maximumSupplyAirFlowRate();
  result.maximumColdWaterFlowRate = fanCoil.maximumColdWaterFlowRate();
  result.minimumColdWaterFlowRate = fanCoil.minimumColdWaterFlowRate();
  result.coolingConvergenceTolerance = fanCoil.coolingConvergenceTolerance();
  result.maximumHotWaterFlowRate = fanCoil.maximumHotWaterFlowRate();
  result.minimumHotWaterFlowRate = fanCoil.minimumHotWaterFlowRate();
  result.heatingConvergenceTolerance = fanCoil.heatingConvergenceTolerance();
  if (auto constantFan = fan.optionalCast<FanConstantVolume>()) {
    result.fanPressureRise = constantFan->pressureRise();
  }
  result.coolingDesignWaterFlowRate = cooling.designWaterFlowRate();
  result.coolingDesignInletWaterTemperature = cooling.designInletWaterTemperature();
  result.coolingDesignOutletAirTemperature = cooling.designOutletAirTemperature();
  result.heatingMaximumWaterFlowRate = heating.maximumWaterFlowRate();
  result.heatingRatedInletWaterTemperature = heating.ratedInletWaterTemperature();
  result.heatingRatedOutletAirTemperature = heating.ratedOutletAirTemperature();
  return result;
}

void expectFourPipeFanCoilExternalTopologyPreserved(const FourPipeFanCoilMoveTopologySnapshot& expected,
                                                    const FourPipeFanCoilMoveTopologySnapshot& actual, bool selectedHeating) {
  EXPECT_EQ(expected.fanCoilHandle, actual.fanCoilHandle);
  EXPECT_EQ(expected.zoneHandle, actual.zoneHandle);
  EXPECT_EQ(expected.childHandles, actual.childHandles);
  EXPECT_EQ(expected.zoneEquipmentHandles, actual.zoneEquipmentHandles);
  EXPECT_EQ(expected.zoneInletNodeHandles, actual.zoneInletNodeHandles);
  EXPECT_EQ(expected.zoneExhaustNodeHandles, actual.zoneExhaustNodeHandles);
  EXPECT_TRUE(expected.fanCoilZoneHandle == actual.fanCoilZoneHandle);
  EXPECT_TRUE(expected.fanCoilZoneName == actual.fanCoilZoneName);
  EXPECT_TRUE(expected.airLoopOwnerHandles == actual.airLoopOwnerHandles);
  EXPECT_TRUE(expected.outdoorAirSystemOwnerHandles == actual.outdoorAirSystemOwnerHandles);
  EXPECT_TRUE(expected.airLoopOwnerNames == actual.airLoopOwnerNames);
  EXPECT_TRUE(expected.outdoorAirSystemOwnerNames == actual.outdoorAirSystemOwnerNames);
  EXPECT_TRUE(expected.roleTargetHandles == actual.roleTargetHandles);
  EXPECT_TRUE(expected.roleTargetNames == actual.roleTargetNames);
  EXPECT_TRUE(expected.roleTargetTypes == actual.roleTargetTypes);
  EXPECT_TRUE(expected.rawRoleNames == actual.rawRoleNames);
  EXPECT_TRUE(expected.rawRoleTypes == actual.rawRoleTypes);
  EXPECT_TRUE(expected.airNodeHandles == actual.airNodeHandles);
  EXPECT_EQ(expected.controllerHandles, actual.controllerHandles);
  EXPECT_TRUE(expected.controllerActuatorHandles == actual.controllerActuatorHandles);
  EXPECT_TRUE(expected.rawControllerActuatorNames == actual.rawControllerActuatorNames);
  EXPECT_EQ(expected.availabilityScheduleHandle, actual.availabilityScheduleHandle);
  EXPECT_EQ(expected.availabilityScheduleName, actual.availabilityScheduleName);
  EXPECT_EQ(expected.capacityControlMethod, actual.capacityControlMethod);
  EXPECT_TRUE(expected.maximumSupplyAirFlowRate == actual.maximumSupplyAirFlowRate);
  EXPECT_TRUE(expected.maximumColdWaterFlowRate == actual.maximumColdWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.minimumColdWaterFlowRate, actual.minimumColdWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.coolingConvergenceTolerance, actual.coolingConvergenceTolerance);
  EXPECT_TRUE(expected.maximumHotWaterFlowRate == actual.maximumHotWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.minimumHotWaterFlowRate, actual.minimumHotWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.heatingConvergenceTolerance, actual.heatingConvergenceTolerance);
  EXPECT_TRUE(expected.fanPressureRise == actual.fanPressureRise);
  EXPECT_TRUE(expected.coolingDesignWaterFlowRate == actual.coolingDesignWaterFlowRate);
  EXPECT_TRUE(expected.coolingDesignInletWaterTemperature == actual.coolingDesignInletWaterTemperature);
  EXPECT_TRUE(expected.coolingDesignOutletAirTemperature == actual.coolingDesignOutletAirTemperature);
  EXPECT_TRUE(expected.heatingMaximumWaterFlowRate == actual.heatingMaximumWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.heatingRatedInletWaterTemperature, actual.heatingRatedInletWaterTemperature);
  EXPECT_DOUBLE_EQ(expected.heatingRatedOutletAirTemperature, actual.heatingRatedOutletAirTemperature);
  if (selectedHeating) {
    EXPECT_TRUE(expected.coolingPlantLoopHandle == actual.coolingPlantLoopHandle);
    EXPECT_TRUE(expected.waterNodeHandles[0] == actual.waterNodeHandles[0]);
    EXPECT_TRUE(expected.waterNodeHandles[1] == actual.waterNodeHandles[1]);
  } else {
    EXPECT_TRUE(expected.heatingPlantLoopHandle == actual.heatingPlantLoopHandle);
    EXPECT_TRUE(expected.waterNodeHandles[2] == actual.waterNodeHandles[2]);
    EXPECT_TRUE(expected.waterNodeHandles[3] == actual.waterNodeHandles[3]);
  }
}

void expectFourPipeFanCoilExternalTopologySurvivesReload(const FourPipeFanCoilMoveTopologySnapshot& expected,
                                                         const FourPipeFanCoilMoveTopologySnapshot& actual) {
  EXPECT_EQ(expected.childHandles.size(), actual.childHandles.size());
  EXPECT_EQ(expected.zoneEquipmentHandles.size(), actual.zoneEquipmentHandles.size());
  EXPECT_EQ(expected.zoneInletNodeHandles.size(), actual.zoneInletNodeHandles.size());
  EXPECT_EQ(expected.zoneExhaustNodeHandles.size(), actual.zoneExhaustNodeHandles.size());
  EXPECT_TRUE(expected.fanCoilZoneName == actual.fanCoilZoneName);
  EXPECT_TRUE(expected.airLoopOwnerNames == actual.airLoopOwnerNames);
  EXPECT_TRUE(expected.outdoorAirSystemOwnerNames == actual.outdoorAirSystemOwnerNames);
  EXPECT_TRUE(expected.roleTargetNames == actual.roleTargetNames);
  EXPECT_TRUE(expected.roleTargetTypes == actual.roleTargetTypes);
  EXPECT_TRUE(expected.rawRoleNames == actual.rawRoleNames);
  EXPECT_TRUE(expected.rawRoleTypes == actual.rawRoleTypes);
  EXPECT_TRUE(expected.coolingPlantLoopName == actual.coolingPlantLoopName);
  EXPECT_TRUE(expected.heatingPlantLoopName == actual.heatingPlantLoopName);
  EXPECT_EQ(expected.controllerHandles.size(), actual.controllerHandles.size());
  EXPECT_TRUE(expected.rawControllerActuatorNames == actual.rawControllerActuatorNames);
  EXPECT_EQ(expected.availabilityScheduleName, actual.availabilityScheduleName);
  EXPECT_EQ(expected.capacityControlMethod, actual.capacityControlMethod);
  EXPECT_TRUE(expected.maximumSupplyAirFlowRate == actual.maximumSupplyAirFlowRate);
  EXPECT_TRUE(expected.maximumColdWaterFlowRate == actual.maximumColdWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.minimumColdWaterFlowRate, actual.minimumColdWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.coolingConvergenceTolerance, actual.coolingConvergenceTolerance);
  EXPECT_TRUE(expected.maximumHotWaterFlowRate == actual.maximumHotWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.minimumHotWaterFlowRate, actual.minimumHotWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.heatingConvergenceTolerance, actual.heatingConvergenceTolerance);
  EXPECT_TRUE(expected.fanPressureRise == actual.fanPressureRise);
  EXPECT_TRUE(expected.coolingDesignWaterFlowRate == actual.coolingDesignWaterFlowRate);
  EXPECT_TRUE(expected.coolingDesignInletWaterTemperature == actual.coolingDesignInletWaterTemperature);
  EXPECT_TRUE(expected.coolingDesignOutletAirTemperature == actual.coolingDesignOutletAirTemperature);
  EXPECT_TRUE(expected.heatingMaximumWaterFlowRate == actual.heatingMaximumWaterFlowRate);
  EXPECT_DOUBLE_EQ(expected.heatingRatedInletWaterTemperature, actual.heatingRatedInletWaterTemperature);
  EXPECT_DOUBLE_EQ(expected.heatingRatedOutletAirTemperature, actual.heatingRatedOutletAirTemperature);

  ASSERT_TRUE(std::ranges::all_of(actual.airNodeHandles, [](const auto& handle) { return static_cast<bool>(handle); }));
  EXPECT_TRUE(actual.airNodeHandles[0] == actual.airNodeHandles[1]);
  EXPECT_TRUE(actual.airNodeHandles[2] == actual.airNodeHandles[3]);
  EXPECT_TRUE(actual.airNodeHandles[4] == actual.airNodeHandles[5]);
  EXPECT_TRUE(actual.airNodeHandles[6] == actual.airNodeHandles[7]);
  EXPECT_EQ(1, std::ranges::count(actual.zoneInletNodeHandles, *actual.airNodeHandles[7]));
  EXPECT_EQ(1, std::ranges::count(actual.zoneExhaustNodeHandles, *actual.airNodeHandles[0]));
  const std::set<openstudio::Handle> boundaryHandles = {*actual.airNodeHandles[0], *actual.airNodeHandles[2], *actual.airNodeHandles[4],
                                                        *actual.airNodeHandles[6]};
  EXPECT_EQ(4u, boundaryHandles.size());
}

void expectDemandBranchAndConnectorOrder(PlantLoop plantLoop, const std::vector<openstudio::Handle>& expectedBranchHandles) {
  const auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto branches = branchList->branches();
  ASSERT_EQ(expectedBranchHandles, objectHandles(branches));
  ASSERT_GE(branches.size(), 3u);

  auto splitter = plantLoop.demandSplitter().cast<ConnectorSplitter>();
  auto mixer = plantLoop.demandMixer().cast<ConnectorMixer>();
  std::vector<openstudio::Handle> splitterBranchTargets;
  std::vector<openstudio::Handle> mixerBranchTargets;
  std::vector<openstudio::Handle> splitterTargets;
  std::vector<openstudio::Handle> mixerTargets;
  bool allEquipmentBranchesHaveRows = true;
  unsigned equipmentIndex = 0u;
  for (auto branch = branches.begin() + 1; branch != branches.end() - 1; ++branch, ++equipmentIndex) {
    const auto splitterBranch = splitter.getModelObjectTarget<Branch>(splitter.outletPort(equipmentIndex));
    const auto mixerBranch = mixer.getModelObjectTarget<Branch>(mixer.inletPort(equipmentIndex));
    ASSERT_TRUE(splitterBranch);
    ASSERT_TRUE(mixerBranch);
    splitterBranchTargets.push_back(splitterBranch->handle());
    mixerBranchTargets.push_back(mixerBranch->handle());
    const auto rowCount = static_cast<unsigned>(branch->extensibleGroups().size());
    if (rowCount == 0u) {
      allEquipmentBranchesHaveRows = false;
      continue;
    }
    const auto branchInlet = branch->componentInletNode(0u);
    const auto branchOutlet = branch->componentOutletNode(rowCount - 1u);
    ASSERT_TRUE(branchInlet);
    ASSERT_TRUE(branchOutlet);
    splitterTargets.push_back(branchInlet->handle());
    mixerTargets.push_back(branchOutlet->handle());
  }
  const std::vector<openstudio::Handle> equipmentBranchHandles(expectedBranchHandles.begin() + 1, expectedBranchHandles.end() - 1);
  EXPECT_EQ(equipmentBranchHandles, splitterBranchTargets);
  EXPECT_EQ(equipmentBranchHandles, mixerBranchTargets);
  if (allEquipmentBranchesHaveRows) {
    EXPECT_EQ(splitterTargets, objectHandles(splitter.outletModelObjects()));
    EXPECT_EQ(mixerTargets, objectHandles(mixer.inletModelObjects()));
  }
}

}  // namespace

TEST_F(EPModelFixture, PlantLoop_DefaultConstructor) {
  Model model;
  PlantLoop plantLoop(model);
  EXPECT_EQ(PlantLoop::iddObjectType(), plantLoop.iddObject().type());
}

TEST_F(EPModelFixture, PlantLoop_DefaultConstructor_CreatesCanonicalCompanions) {
  Model model;
  PlantLoop plantLoop(model);

  EXPECT_EQ(plantLoop.supplyOutletNode(), plantLoop.loopTemperatureSetpointNode());

  auto sizingPlant = plantLoop.sizingPlant();
  auto sizingPlantLoop = sizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
  ASSERT_TRUE(sizingPlantLoop);
  EXPECT_EQ(plantLoop, *sizingPlantLoop);

  auto assignmentList = plantLoop.getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
  ASSERT_TRUE(assignmentList);
  EXPECT_TRUE(plantLoop.availabilityManagers().empty());

  auto operationSchemes =
    plantLoop.getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(operationSchemes);
  EXPECT_FALSE(plantLoop.plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationScheme());

  auto supplyConnectorList = plantLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName);
  auto demandConnectorList = plantLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
  ASSERT_TRUE(supplyConnectorList);
  ASSERT_TRUE(demandConnectorList);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::ConnectorList), supplyConnectorList->iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::ConnectorList), demandConnectorList->iddObject().type());
  ASSERT_EQ(2u, supplyConnectorList->extensibleGroups().size());
  ASSERT_EQ(2u, demandConnectorList->extensibleGroups().size());
  EXPECT_EQ("Connector:Splitter",
            supplyConnectorList->extensibleGroups()[0].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
  EXPECT_EQ("Connector:Mixer",
            supplyConnectorList->extensibleGroups()[1].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
  EXPECT_EQ("Connector:Splitter",
            demandConnectorList->extensibleGroups()[0].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
  EXPECT_EQ("Connector:Mixer",
            demandConnectorList->extensibleGroups()[1].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
}

TEST_F(EPModelFixture, PlantLoop_CanonicalRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-canonical-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant availabilitySchedule(model);
  AvailabilityManagerScheduledOn availabilityManager(model);
  PlantEquipmentOperationHeatingLoad operationScheme(model);
  ScheduleConstant operationSchedule(model);

  ASSERT_TRUE(plantLoop.setName("Canonical Removal Plant Loop"));
  ASSERT_TRUE(availabilitySchedule.setName("Canonical Removal Availability Schedule"));
  ASSERT_TRUE(availabilityManager.setName("Canonical Removal Availability Manager"));
  ASSERT_TRUE(operationScheme.setName("Canonical Removal Heating Operation"));
  ASSERT_TRUE(operationSchedule.setName("Canonical Removal Operation Schedule"));
  ASSERT_TRUE(availabilityManager.setSchedule(availabilitySchedule));
  ASSERT_TRUE(plantLoop.addAvailabilityManager(availabilityManager));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(operationScheme));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(operationSchedule));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Canonical Removal Plant Loop");
  auto loadedAvailabilityManager =
    loadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Canonical Removal Availability Manager");
  auto loadedAvailabilitySchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Availability Schedule");
  auto loadedOperationScheme = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Canonical Removal Heating Operation");
  auto loadedOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Operation Schedule");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedAvailabilityManager);
  ASSERT_TRUE(loadedAvailabilitySchedule);
  ASSERT_TRUE(loadedOperationScheme);
  ASSERT_TRUE(loadedOperationSchedule);

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }

  std::vector<openstudio::Handle> canonicalOwnerHandles;
  const auto supplyBranchList = loadedPlantLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  const auto demandBranchList = loadedPlantLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  const auto supplyConnectorList = loadedPlantLoop->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName);
  const auto demandConnectorList = loadedPlantLoop->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
  const auto assignmentList =
    loadedPlantLoop->getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
  const auto operationSchemes =
    loadedPlantLoop->getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(supplyBranchList);
  ASSERT_TRUE(demandBranchList);
  ASSERT_TRUE(supplyConnectorList);
  ASSERT_TRUE(demandConnectorList);
  ASSERT_TRUE(assignmentList);
  ASSERT_TRUE(operationSchemes);
  canonicalOwnerHandles.push_back(supplyBranchList->handle());
  canonicalOwnerHandles.push_back(demandBranchList->handle());
  canonicalOwnerHandles.push_back(supplyConnectorList->handle());
  canonicalOwnerHandles.push_back(demandConnectorList->handle());
  canonicalOwnerHandles.push_back(assignmentList->handle());
  canonicalOwnerHandles.push_back(operationSchemes->handle());
  for (const auto& branch : supplyBranchList->branches()) {
    canonicalOwnerHandles.push_back(branch.handle());
  }
  for (const auto& branch : demandBranchList->branches()) {
    canonicalOwnerHandles.push_back(branch.handle());
  }

  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto plantLoopHandle = loadedPlantLoop->handle();

  ASSERT_TRUE(loadedAvailabilityManager->loop());
  EXPECT_EQ(plantLoopHandle, loadedAvailabilityManager->loop()->handle());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*loadedOperationScheme, *loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(loadedPlantLoop->remove().empty());

  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  for (const auto& handle : canonicalOwnerHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilityManager->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilitySchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationScheme->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationSchedule->handle()));
  EXPECT_FALSE(loadedAvailabilityManager->loop());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  auto reloadedAvailabilityManager =
    reloadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Canonical Removal Availability Manager");
  EXPECT_TRUE(reloadedAvailabilityManager);
  if (reloadedAvailabilityManager) {
    EXPECT_FALSE(reloadedAvailabilityManager->loop());
  }
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Availability Schedule"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Canonical Removal Heating Operation"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Operation Schedule"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_StraightComponentRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-straight-component-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.setName("Straight Component Removal Plant Loop"));
  ASSERT_TRUE(pipe.setName("Owned Supply Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop, *pipe.plantLoop());
  EXPECT_TRUE(plantLoop.supplyComponent(pipe.handle()));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Straight Component Removal Plant Loop");
  auto loadedPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedPipe);
  ASSERT_TRUE(loadedPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(loadedPipe->handle()));
  EXPECT_EQ(7u, loadedPlantLoop->supplyComponents().size());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto pipeHandle = loadedPipe->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());

  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(pipeHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Pipe"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SameSideMultipleStraightComponentRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-same-side-multiple-straight-component-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic firstPipe(model);
  PipeAdiabatic secondPipe(model);
  ASSERT_TRUE(plantLoop.setName("Same Side Multiple Straight Component Loop"));
  ASSERT_TRUE(firstPipe.setName("First Same Side Supply Pipe"));
  ASSERT_TRUE(secondPipe.setName("Second Same Side Supply Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(firstPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(secondPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Same Side Multiple Straight Component Loop");
  auto loadedFirstPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("First Same Side Supply Pipe");
  auto loadedSecondPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Second Same Side Supply Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedFirstPipe);
  ASSERT_TRUE(loadedSecondPipe);
  ASSERT_TRUE(loadedFirstPipe->plantLoop());
  ASSERT_TRUE(loadedSecondPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedFirstPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSecondPipe->plantLoop());
  EXPECT_EQ(2u, loadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto firstPipeHandle = loadedFirstPipe->handle();
  const auto secondPipeHandle = loadedSecondPipe->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());

  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(firstPipeHandle));
  EXPECT_FALSE(loadedModel->getObject(secondPipeHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("First Same Side Supply Pipe"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Second Same Side Supply Pipe"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SupplyBranchRemovalPreservesSpecifiedComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-supply-branch-removal-preserves-component.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic removedBranchPipe(model);
  PipeAdiabatic siblingPipe(model);
  ASSERT_TRUE(plantLoop.setName("Supply Branch Removal Plant Loop"));
  ASSERT_TRUE(removedBranchPipe.setName("Detached Supply Branch Pipe"));
  ASSERT_TRUE(siblingPipe.setName("Surviving Sibling Supply Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(removedBranchPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(siblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Supply Branch Removal Plant Loop");
  auto loadedRemovedBranchPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Supply Branch Pipe");
  auto loadedSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Supply Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedRemovedBranchPipe);
  ASSERT_TRUE(loadedSiblingPipe);
  ASSERT_TRUE(loadedRemovedBranchPipe->plantLoop());
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_EQ(2u, loadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  const auto removedBranchPipeHandle = loadedRemovedBranchPipe->handle();
  const auto siblingPipeHandle = loadedSiblingPipe->handle();
  ASSERT_TRUE(loadedPlantLoop->removeSupplyBranchWithComponent(*loadedRemovedBranchPipe));
  EXPECT_TRUE(loadedModel->getObject(removedBranchPipeHandle));
  EXPECT_TRUE(loadedModel->getObject(siblingPipeHandle));
  EXPECT_FALSE(loadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(loadedRemovedBranchPipe->loop());
  EXPECT_FALSE(loadedPlantLoop->supplyComponent(removedBranchPipeHandle));
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(siblingPipeHandle));
  EXPECT_EQ(1u, loadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPlantLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Supply Branch Removal Plant Loop");
  auto reloadedRemovedBranchPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Supply Branch Pipe");
  auto reloadedSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Supply Pipe");
  ASSERT_TRUE(reloadedPlantLoop);
  ASSERT_TRUE(reloadedRemovedBranchPipe);
  ASSERT_TRUE(reloadedSiblingPipe);
  EXPECT_FALSE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(reloadedRemovedBranchPipe->loop());
  EXPECT_FALSE(reloadedPlantLoop->supplyComponent(reloadedRemovedBranchPipe->handle()));
  ASSERT_TRUE(reloadedSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedPlantLoop->supplyComponent(reloadedSiblingPipe->handle()));
  EXPECT_EQ(1u, reloadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(reloadedPlantLoop->addSupplyBranchForComponent(*reloadedRemovedBranchPipe));
  ASSERT_TRUE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(2u, reloadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_DemandBranchRemovalPreservesSpecifiedComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-demand-branch-removal-preserves-component.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic removedBranchPipe(model);
  PipeAdiabatic siblingPipe(model);
  ASSERT_TRUE(plantLoop.setName("Demand Branch Removal Plant Loop"));
  ASSERT_TRUE(removedBranchPipe.setName("Detached Demand Branch Pipe"));
  ASSERT_TRUE(siblingPipe.setName("Surviving Sibling Demand Pipe"));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(removedBranchPipe));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(siblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Demand Branch Removal Plant Loop");
  auto loadedRemovedBranchPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Demand Branch Pipe");
  auto loadedSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Demand Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedRemovedBranchPipe);
  ASSERT_TRUE(loadedSiblingPipe);
  ASSERT_TRUE(loadedRemovedBranchPipe->plantLoop());
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_EQ(2u, loadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  const auto removedBranchPipeHandle = loadedRemovedBranchPipe->handle();
  const auto siblingPipeHandle = loadedSiblingPipe->handle();
  ASSERT_TRUE(loadedPlantLoop->removeDemandBranchWithComponent(*loadedRemovedBranchPipe));
  EXPECT_TRUE(loadedModel->getObject(removedBranchPipeHandle));
  EXPECT_TRUE(loadedModel->getObject(siblingPipeHandle));
  EXPECT_FALSE(loadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(loadedRemovedBranchPipe->loop());
  EXPECT_FALSE(loadedPlantLoop->demandComponent(removedBranchPipeHandle));
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->demandComponent(siblingPipeHandle));
  EXPECT_EQ(1u, loadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPlantLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Demand Branch Removal Plant Loop");
  auto reloadedRemovedBranchPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Demand Branch Pipe");
  auto reloadedSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Demand Pipe");
  ASSERT_TRUE(reloadedPlantLoop);
  ASSERT_TRUE(reloadedRemovedBranchPipe);
  ASSERT_TRUE(reloadedSiblingPipe);
  EXPECT_FALSE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(reloadedRemovedBranchPipe->loop());
  EXPECT_FALSE(reloadedPlantLoop->demandComponent(reloadedRemovedBranchPipe->handle()));
  ASSERT_TRUE(reloadedSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedPlantLoop->demandComponent(reloadedSiblingPipe->handle()));
  EXPECT_EQ(1u, reloadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(reloadedPlantLoop->addDemandBranchForComponent(*reloadedRemovedBranchPipe));
  ASSERT_TRUE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(2u, reloadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SupplyBranchAddMovesOwnedStraightComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-cross-loop-supply-branch-move.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  PipeAdiabatic targetSiblingPipe(model);
  ASSERT_TRUE(sourceLoop.setName("Source Supply Branch Move Loop"));
  ASSERT_TRUE(targetLoop.setName("Target Supply Branch Move Loop"));
  ASSERT_TRUE(movingPipe.setName("Moved Supply Branch Pipe"));
  ASSERT_TRUE(targetSiblingPipe.setName("Target Sibling Supply Pipe"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(movingPipe));
  ASSERT_TRUE(targetLoop.addSupplyBranchForComponent(targetSiblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Source Supply Branch Move Loop");
  auto loadedTargetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Target Supply Branch Move Loop");
  auto loadedMovingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Supply Branch Pipe");
  auto loadedTargetSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Supply Pipe");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedTargetLoop);
  ASSERT_TRUE(loadedMovingPipe);
  ASSERT_TRUE(loadedTargetSiblingPipe);
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());
  EXPECT_EQ(1u, loadedTargetLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedTargetLoop->addSupplyBranchForComponent(*loadedMovingPipe));
  EXPECT_FALSE(loadedSourceLoop->supplyComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->supplyComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->supplyComponent(loadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedSourceLoop->supplyComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, loadedTargetLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Source Supply Branch Move Loop");
  auto reloadedTargetLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Target Supply Branch Move Loop");
  auto reloadedMovingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Supply Branch Pipe");
  auto reloadedTargetSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Supply Pipe");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedTargetLoop);
  ASSERT_TRUE(reloadedMovingPipe);
  ASSERT_TRUE(reloadedTargetSiblingPipe);
  EXPECT_FALSE(reloadedSourceLoop->supplyComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->supplyComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->supplyComponent(reloadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(reloadedMovingPipe->plantLoop());
  ASSERT_TRUE(reloadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedMovingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedSourceLoop->supplyComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, reloadedTargetLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_DemandBranchAddMovesOwnedStraightComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-cross-loop-demand-branch-move.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  PipeAdiabatic targetSiblingPipe(model);
  ASSERT_TRUE(sourceLoop.setName("Source Demand Branch Move Loop"));
  ASSERT_TRUE(targetLoop.setName("Target Demand Branch Move Loop"));
  ASSERT_TRUE(movingPipe.setName("Moved Demand Branch Pipe"));
  ASSERT_TRUE(targetSiblingPipe.setName("Target Sibling Demand Pipe"));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(movingPipe));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetSiblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Source Demand Branch Move Loop");
  auto loadedTargetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Target Demand Branch Move Loop");
  auto loadedMovingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Demand Branch Pipe");
  auto loadedTargetSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Demand Pipe");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedTargetLoop);
  ASSERT_TRUE(loadedMovingPipe);
  ASSERT_TRUE(loadedTargetSiblingPipe);
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());
  EXPECT_EQ(1u, loadedTargetLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedTargetLoop->addDemandBranchForComponent(*loadedMovingPipe));
  EXPECT_FALSE(loadedSourceLoop->demandComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->demandComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->demandComponent(loadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedSourceLoop->demandComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, loadedTargetLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Source Demand Branch Move Loop");
  auto reloadedTargetLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Target Demand Branch Move Loop");
  auto reloadedMovingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Demand Branch Pipe");
  auto reloadedTargetSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Demand Pipe");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedTargetLoop);
  ASSERT_TRUE(reloadedMovingPipe);
  ASSERT_TRUE(reloadedTargetSiblingPipe);
  EXPECT_FALSE(reloadedSourceLoop->demandComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->demandComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->demandComponent(reloadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(reloadedMovingPipe->plantLoop());
  ASSERT_TRUE(reloadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedMovingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedSourceLoop->demandComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, reloadedTargetLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SupplyBranchAttachmentFailureRestoresDefaultBranchAndRetries) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.setName("Transactional Default Supply Loop"));
  ASSERT_TRUE(pipe.setName("Transactional Default Supply Pipe"));

  const auto before = capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, true);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchAttachmentPrepared);
    EXPECT_FALSE(plantLoop.addSupplyBranchForComponent(pipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, true));
  EXPECT_FALSE(pipe.plantLoop());

  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop, *pipe.plantLoop());
  EXPECT_TRUE(plantLoop.supplyComponent(pipe.handle()));
}

TEST_F(EPModelFixture, PlantLoop_SupplyBranchMoveFailureRestoresBothLoopsAndRetries) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  PipeAdiabatic targetPipe(model);
  ASSERT_TRUE(sourceLoop.setName("Transactional Source Supply Loop"));
  ASSERT_TRUE(targetLoop.setName("Transactional Target Supply Loop"));
  ASSERT_TRUE(movingPipe.setName("Transactional Moving Supply Pipe"));
  ASSERT_TRUE(targetPipe.setName("Transactional Target Supply Pipe"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(movingPipe));
  ASSERT_TRUE(targetLoop.addSupplyBranchForComponent(targetPipe));

  const auto before = capturePlantAttachmentTopology(model, sourceLoop, targetLoop, movingPipe, true);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addSupplyBranchForComponent(movingPipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, sourceLoop, targetLoop, movingPipe, true));
  ASSERT_TRUE(movingPipe.plantLoop());
  EXPECT_EQ(sourceLoop, *movingPipe.plantLoop());

  ASSERT_TRUE(targetLoop.addSupplyBranchForComponent(movingPipe));
  ASSERT_TRUE(movingPipe.plantLoop());
  EXPECT_EQ(targetLoop, *movingPipe.plantLoop());
  EXPECT_FALSE(sourceLoop.supplyComponent(movingPipe.handle()));
  EXPECT_TRUE(targetLoop.supplyComponent(movingPipe.handle()));
  EXPECT_TRUE(targetLoop.supplyComponent(targetPipe.handle()));
}

TEST_F(EPModelFixture, PlantLoop_DemandBranchAttachmentFailureRestoresDefaultBranchAndRetries) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.setName("Transactional Default Demand Loop"));
  ASSERT_TRUE(pipe.setName("Transactional Default Demand Pipe"));

  const auto before = capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, false);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchAttachmentPrepared);
    EXPECT_FALSE(plantLoop.addDemandBranchForComponent(pipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, false));
  EXPECT_FALSE(pipe.plantLoop());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop, *pipe.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponent(pipe.handle()));
}

TEST_F(EPModelFixture, PlantLoop_DemandBranchMoveFailureRestoresBothLoopsAndRetries) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  PipeAdiabatic targetPipe(model);
  ASSERT_TRUE(sourceLoop.setName("Transactional Source Demand Loop"));
  ASSERT_TRUE(targetLoop.setName("Transactional Target Demand Loop"));
  ASSERT_TRUE(movingPipe.setName("Transactional Moving Demand Pipe"));
  ASSERT_TRUE(targetPipe.setName("Transactional Target Demand Pipe"));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(movingPipe));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetPipe));

  const auto before = capturePlantAttachmentTopology(model, sourceLoop, targetLoop, movingPipe, false);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(movingPipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, sourceLoop, targetLoop, movingPipe, false));
  ASSERT_TRUE(movingPipe.plantLoop());
  EXPECT_EQ(sourceLoop, *movingPipe.plantLoop());

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(movingPipe));
  ASSERT_TRUE(movingPipe.plantLoop());
  EXPECT_EQ(targetLoop, *movingPipe.plantLoop());
  EXPECT_FALSE(sourceLoop.demandComponent(movingPipe.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(movingPipe.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(targetPipe.handle()));
}

TEST_F(EPModelFixture, PlantLoop_SupplyPipeMoveRemovesEmptiedParallelSourceBranch) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic retainedPipe(model);
  PipeAdiabatic movingPipe(model);
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(retainedPipe));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(movingPipe));

  auto sourceLoopImpl = sourceLoop.getImpl<detail::PlantLoop_Impl>();
  auto sourceEquipmentBranches = sourceLoopImpl->supplyEquipmentBranches();
  ASSERT_EQ(2u, sourceEquipmentBranches.size());
  const auto movingBranch = std::ranges::find_if(sourceEquipmentBranches, [&movingPipe](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, movingPipe.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceEquipmentBranches.end(), movingBranch);
  const auto movingBranchHandle = movingBranch->handle();

  ASSERT_TRUE(targetLoop.addSupplyBranchForComponent(movingPipe));
  sourceEquipmentBranches = sourceLoopImpl->supplyEquipmentBranches();
  ASSERT_EQ(1u, sourceEquipmentBranches.size());
  EXPECT_EQ(std::vector<ModelObject>{retainedPipe.cast<ModelObject>()}, sourceEquipmentBranches.front().components());
  EXPECT_FALSE(model.getObject(movingBranchHandle));
  EXPECT_EQ(1u, sourceLoopImpl->supplySplitter().cast<ConnectorSplitter>().nextBranchIndex());
  EXPECT_EQ(1u, sourceLoopImpl->supplyMixer().cast<ConnectorMixer>().nextBranchIndex());
}

TEST_F(EPModelFixture, PlantLoop_DemandPipeMoveRemovesEmptiedParallelSourceBranch) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic retainedPipe(model);
  PipeAdiabatic movingPipe(model);
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(retainedPipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(movingPipe));

  auto sourceLoopImpl = sourceLoop.getImpl<detail::PlantLoop_Impl>();
  auto sourceEquipmentBranches = sourceLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(2u, sourceEquipmentBranches.size());
  const auto movingBranch = std::ranges::find_if(sourceEquipmentBranches, [&movingPipe](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, movingPipe.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceEquipmentBranches.end(), movingBranch);
  const auto movingBranchHandle = movingBranch->handle();

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(movingPipe));
  sourceEquipmentBranches = sourceLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, sourceEquipmentBranches.size());
  EXPECT_EQ(std::vector<ModelObject>{retainedPipe.cast<ModelObject>()}, sourceEquipmentBranches.front().components());
  EXPECT_FALSE(model.getObject(movingBranchHandle));
  EXPECT_EQ(1u, sourceLoopImpl->demandSplitter().cast<ConnectorSplitter>().nextBranchIndex());
  EXPECT_EQ(1u, sourceLoopImpl->demandMixer().cast<ConnectorMixer>().nextBranchIndex());
}

TEST_F(EPModelFixture, PlantLoop_SupplyPipeMoveRepairsPreviousStraightComponentOutlet) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic retainedPipe(model);
  PipeAdiabatic movingPipe(model);
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(retainedPipe));
  auto insertionNode = retainedPipe.outletModelObject()->cast<Node>();
  ASSERT_TRUE(movingPipe.addToNode(insertionNode));

  const auto bypassNode = movingPipe.outletModelObject()->cast<Node>();
  ASSERT_NE(bypassNode, retainedPipe.outletModelObject()->cast<Node>());
  ASSERT_TRUE(targetLoop.addSupplyBranchForComponent(movingPipe));

  ASSERT_TRUE(retainedPipe.outletModelObject());
  EXPECT_EQ(bypassNode, retainedPipe.outletModelObject()->cast<Node>());
  const auto sourceBranches = sourceLoop.getImpl<detail::PlantLoop_Impl>()->supplyEquipmentBranches();
  ASSERT_EQ(1u, sourceBranches.size());
  EXPECT_EQ(std::vector<ModelObject>{retainedPipe.cast<ModelObject>()}, sourceBranches.front().components());
  ASSERT_TRUE(sourceBranches.front().componentOutletNode(0u));
  EXPECT_EQ(bypassNode, *sourceBranches.front().componentOutletNode(0u));
}

TEST_F(EPModelFixture, PlantLoop_DemandPipeMoveRepairsNextWaterCoilInlet) {
  Model model;
  ScheduleConstant availabilitySchedule(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  CoilHeatingWater retainedCoil(model, availabilitySchedule);
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(movingPipe));
  auto insertionNode = movingPipe.outletModelObject()->cast<Node>();
  ASSERT_TRUE(retainedCoil.addToNode(insertionNode));

  const auto bypassNode = movingPipe.inletModelObject()->cast<Node>();
  ASSERT_NE(bypassNode, retainedCoil.waterInletModelObject()->cast<Node>());
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(movingPipe));

  ASSERT_TRUE(retainedCoil.waterInletModelObject());
  EXPECT_EQ(bypassNode, retainedCoil.waterInletModelObject()->cast<Node>());
  const auto sourceBranches = sourceLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches();
  ASSERT_EQ(1u, sourceBranches.size());
  EXPECT_EQ(std::vector<ModelObject>{retainedCoil.cast<ModelObject>()}, sourceBranches.front().components());
  ASSERT_TRUE(sourceBranches.front().componentInletNode(0u));
  EXPECT_EQ(bypassNode, *sourceBranches.front().componentInletNode(0u));
}

TEST_F(EPModelFixture, PlantLoop_SupplyDefaultPipeBranchRemovalFailureRestoresAndRetries) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());
  const auto inletNodeHandle = pipe.inletModelObject()->handle();
  const auto outletNodeHandle = pipe.outletModelObject()->handle();
  auto setpointTarget = plantLoop.supplyInletNode();
  ASSERT_TRUE(plantLoop.setLoopTemperatureSetpointNode(setpointTarget));
  const auto setpointTargetHandle = setpointTarget.handle();
  auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto originalBranchHandles = objectHandles(branchList->branches());
  ASSERT_EQ(3u, originalBranchHandles.size());
  const auto originalDefaultBranchHandle = originalBranchHandles[1];

  const auto before = capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, true);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchRemovalPrepared);
    EXPECT_FALSE(plantLoop.removeSupplyBranchWithComponent(pipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, true));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());

  ASSERT_TRUE(plantLoop.removeSupplyBranchWithComponent(pipe));
  EXPECT_TRUE(model.getObject(pipe.handle()));
  EXPECT_FALSE(pipe.inletModelObject());
  EXPECT_FALSE(pipe.outletModelObject());
  EXPECT_FALSE(pipe.plantLoop());
  EXPECT_FALSE(plantLoop.supplyComponent(pipe.handle()));
  EXPECT_TRUE(model.getObject(inletNodeHandle));
  EXPECT_TRUE(model.getObject(outletNodeHandle));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(branchList);
  const std::vector<openstudio::Handle> expectedBranchHandles{originalBranchHandles.front(), originalDefaultBranchHandle,
                                                              originalBranchHandles.back()};
  EXPECT_EQ(expectedBranchHandles, objectHandles(branchList->branches()));
  ASSERT_TRUE(model.getObject(originalDefaultBranchHandle));
  ASSERT_EQ(3u, branchList->branches().size());
  EXPECT_EQ(originalDefaultBranchHandle, branchList->branches()[1].handle());
  EXPECT_TRUE(branchList->branches()[1].components().empty());
  EXPECT_EQ(1u, plantLoop.supplySplitter().cast<ConnectorSplitter>().nextBranchIndex());
  EXPECT_EQ(1u, plantLoop.supplyMixer().cast<ConnectorMixer>().nextBranchIndex());

  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());
  EXPECT_EQ(inletNodeHandle, pipe.inletModelObject()->handle());
  EXPECT_EQ(outletNodeHandle, pipe.outletModelObject()->handle());
  EXPECT_TRUE(plantLoop.supplyComponent(pipe.handle()));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(expectedBranchHandles, objectHandles(branchList->branches()));
}

TEST_F(EPModelFixture, PlantLoop_DemandDefaultPipeBranchRemovalFailureRestoresAndRetries) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(pipe));
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());
  const auto inletNodeHandle = pipe.inletModelObject()->handle();
  const auto outletNodeHandle = pipe.outletModelObject()->handle();
  auto setpointTarget = plantLoop.supplyInletNode();
  ASSERT_TRUE(plantLoop.setLoopTemperatureSetpointNode(setpointTarget));
  const auto setpointTargetHandle = setpointTarget.handle();
  auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto originalBranchHandles = objectHandles(branchList->branches());
  ASSERT_EQ(3u, originalBranchHandles.size());
  const auto originalDefaultBranchHandle = originalBranchHandles[1];

  const auto before = capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, false);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchRemovalPrepared);
    EXPECT_FALSE(plantLoop.removeDemandBranchWithComponent(pipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, plantLoop, plantLoop, pipe, false));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(pipe));
  EXPECT_TRUE(model.getObject(pipe.handle()));
  EXPECT_FALSE(pipe.inletModelObject());
  EXPECT_FALSE(pipe.outletModelObject());
  EXPECT_FALSE(pipe.plantLoop());
  EXPECT_FALSE(plantLoop.demandComponent(pipe.handle()));
  EXPECT_TRUE(model.getObject(inletNodeHandle));
  EXPECT_TRUE(model.getObject(outletNodeHandle));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  const std::vector<openstudio::Handle> expectedBranchHandles{originalBranchHandles.front(), originalDefaultBranchHandle,
                                                              originalBranchHandles.back()};
  EXPECT_EQ(expectedBranchHandles, objectHandles(branchList->branches()));
  ASSERT_TRUE(model.getObject(originalDefaultBranchHandle));
  ASSERT_EQ(3u, branchList->branches().size());
  EXPECT_EQ(originalDefaultBranchHandle, branchList->branches()[1].handle());
  EXPECT_TRUE(branchList->branches()[1].components().empty());
  EXPECT_EQ(1u, plantLoop.demandSplitter().cast<ConnectorSplitter>().nextBranchIndex());
  EXPECT_EQ(1u, plantLoop.demandMixer().cast<ConnectorMixer>().nextBranchIndex());

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(pipe));
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());
  EXPECT_EQ(inletNodeHandle, pipe.inletModelObject()->handle());
  EXPECT_EQ(outletNodeHandle, pipe.outletModelObject()->handle());
  EXPECT_TRUE(plantLoop.demandComponent(pipe.handle()));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(expectedBranchHandles, objectHandles(branchList->branches()));
}

TEST_F(EPModelFixture, PlantLoop_SupplyParallelPipeBranchRemovalFailureRestoresAndRetries) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic retainedPipe(model);
  PipeAdiabatic removedPipe(model);
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(retainedPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(removedPipe));
  ASSERT_TRUE(removedPipe.inletModelObject());
  ASSERT_TRUE(removedPipe.outletModelObject());
  const auto inletNodeHandle = removedPipe.inletModelObject()->handle();
  const auto outletNodeHandle = removedPipe.outletModelObject()->handle();
  auto setpointTarget = plantLoop.supplyInletNode();
  ASSERT_TRUE(plantLoop.setLoopTemperatureSetpointNode(setpointTarget));
  const auto setpointTargetHandle = setpointTarget.handle();

  auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto listedBranches = branchList->branches();
  const auto branchHandlesBefore = objectHandles(listedBranches);
  ASSERT_EQ(4u, branchHandlesBefore.size());
  const auto retainedBranch = std::ranges::find_if(listedBranches, [&retainedPipe](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, retainedPipe.cast<ModelObject>()) != components.end();
  });
  const auto removedBranch = std::ranges::find_if(listedBranches, [&removedPipe](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, removedPipe.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(listedBranches.end(), retainedBranch);
  ASSERT_NE(listedBranches.end(), removedBranch);
  const auto retainedBranchHandle = retainedBranch->handle();
  const auto removedBranchHandle = removedBranch->handle();
  auto expectedBranchHandlesAfterRemoval = branchHandlesBefore;
  const auto erasedBranch = std::ranges::find(expectedBranchHandlesAfterRemoval, removedBranchHandle);
  ASSERT_NE(expectedBranchHandlesAfterRemoval.end(), erasedBranch);
  expectedBranchHandlesAfterRemoval.erase(erasedBranch);
  ASSERT_EQ(3u, expectedBranchHandlesAfterRemoval.size());

  const auto before = capturePlantAttachmentTopology(model, plantLoop, plantLoop, removedPipe, true);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchRemovalPrepared);
    EXPECT_FALSE(plantLoop.removeSupplyBranchWithComponent(removedPipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, plantLoop, plantLoop, removedPipe, true));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());

  ASSERT_TRUE(plantLoop.removeSupplyBranchWithComponent(removedPipe));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(removedPipe.handle()));
  EXPECT_TRUE(model.getObject(inletNodeHandle));
  EXPECT_TRUE(model.getObject(outletNodeHandle));
  EXPECT_FALSE(plantLoop.supplyComponent(removedPipe.handle()));
  EXPECT_TRUE(plantLoop.supplyComponent(retainedPipe.handle()));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto branchesAfterRemoval = branchList->branches();
  EXPECT_EQ(expectedBranchHandlesAfterRemoval, objectHandles(branchesAfterRemoval));
  ASSERT_EQ(3u, branchesAfterRemoval.size());
  ASSERT_EQ(retainedBranchHandle, branchesAfterRemoval[1].handle());
  ASSERT_EQ(1u, branchesAfterRemoval[1].extensibleGroups().size());
  const auto retainedBranchInlet = branchesAfterRemoval[1].componentInletNode(0u);
  const auto retainedBranchOutlet = branchesAfterRemoval[1].componentOutletNode(0u);
  ASSERT_TRUE(retainedBranchInlet);
  ASSERT_TRUE(retainedBranchOutlet);
  EXPECT_EQ(std::vector<openstudio::Handle>{retainedBranchInlet->handle()},
            objectHandles(plantLoop.supplySplitter().cast<ConnectorSplitter>().outletModelObjects()));
  EXPECT_EQ(std::vector<openstudio::Handle>{retainedBranchOutlet->handle()},
            objectHandles(plantLoop.supplyMixer().cast<ConnectorMixer>().inletModelObjects()));

  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(removedPipe));
  ASSERT_TRUE(removedPipe.inletModelObject());
  ASSERT_TRUE(removedPipe.outletModelObject());
  EXPECT_EQ(inletNodeHandle, removedPipe.inletModelObject()->handle());
  EXPECT_EQ(outletNodeHandle, removedPipe.outletModelObject()->handle());
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto branchHandlesAfterReAdd = objectHandles(branchList->branches());
  ASSERT_EQ(4u, branchHandlesAfterReAdd.size());
  std::vector<openstudio::Handle> splitterTargetsAfterReAdd;
  std::vector<openstudio::Handle> mixerTargetsAfterReAdd;
  const auto branchesAfterReAdd = branchList->branches();
  for (auto branch = branchesAfterReAdd.begin() + 1; branch != branchesAfterReAdd.end() - 1; ++branch) {
    ASSERT_EQ(1u, branch->extensibleGroups().size());
    const auto branchInlet = branch->componentInletNode(0u);
    const auto branchOutlet = branch->componentOutletNode(0u);
    ASSERT_TRUE(branchInlet);
    ASSERT_TRUE(branchOutlet);
    splitterTargetsAfterReAdd.push_back(branchInlet->handle());
    mixerTargetsAfterReAdd.push_back(branchOutlet->handle());
  }
  EXPECT_EQ(splitterTargetsAfterReAdd, objectHandles(plantLoop.supplySplitter().cast<ConnectorSplitter>().outletModelObjects()));
  EXPECT_EQ(mixerTargetsAfterReAdd, objectHandles(plantLoop.supplyMixer().cast<ConnectorMixer>().inletModelObjects()));
}

TEST_F(EPModelFixture, PlantLoop_DemandParallelPipeBranchRemovalFailureRestoresAndRetries) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic retainedPipe(model);
  PipeAdiabatic removedPipe(model);
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(retainedPipe));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(removedPipe));
  ASSERT_TRUE(removedPipe.inletModelObject());
  ASSERT_TRUE(removedPipe.outletModelObject());
  const auto inletNodeHandle = removedPipe.inletModelObject()->handle();
  const auto outletNodeHandle = removedPipe.outletModelObject()->handle();
  auto setpointTarget = plantLoop.supplyInletNode();
  ASSERT_TRUE(plantLoop.setLoopTemperatureSetpointNode(setpointTarget));
  const auto setpointTargetHandle = setpointTarget.handle();

  auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto listedBranches = branchList->branches();
  const auto branchHandlesBefore = objectHandles(listedBranches);
  ASSERT_EQ(4u, branchHandlesBefore.size());
  const auto retainedBranch = std::ranges::find_if(listedBranches, [&retainedPipe](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, retainedPipe.cast<ModelObject>()) != components.end();
  });
  const auto removedBranch = std::ranges::find_if(listedBranches, [&removedPipe](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, removedPipe.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(listedBranches.end(), retainedBranch);
  ASSERT_NE(listedBranches.end(), removedBranch);
  const auto retainedBranchHandle = retainedBranch->handle();
  const auto removedBranchHandle = removedBranch->handle();
  auto expectedBranchHandlesAfterRemoval = branchHandlesBefore;
  const auto erasedBranch = std::ranges::find(expectedBranchHandlesAfterRemoval, removedBranchHandle);
  ASSERT_NE(expectedBranchHandlesAfterRemoval.end(), erasedBranch);
  expectedBranchHandlesAfterRemoval.erase(erasedBranch);
  ASSERT_EQ(3u, expectedBranchHandlesAfterRemoval.size());

  const auto before = capturePlantAttachmentTopology(model, plantLoop, plantLoop, removedPipe, false);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterPipeBranchRemovalPrepared);
    EXPECT_FALSE(plantLoop.removeDemandBranchWithComponent(removedPipe));
  }
  EXPECT_EQ(before, capturePlantAttachmentTopology(model, plantLoop, plantLoop, removedPipe, false));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(removedPipe));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(removedPipe.handle()));
  EXPECT_TRUE(model.getObject(inletNodeHandle));
  EXPECT_TRUE(model.getObject(outletNodeHandle));
  EXPECT_FALSE(plantLoop.demandComponent(removedPipe.handle()));
  EXPECT_TRUE(plantLoop.demandComponent(retainedPipe.handle()));
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto branchesAfterRemoval = branchList->branches();
  EXPECT_EQ(expectedBranchHandlesAfterRemoval, objectHandles(branchesAfterRemoval));
  ASSERT_EQ(3u, branchesAfterRemoval.size());
  ASSERT_EQ(retainedBranchHandle, branchesAfterRemoval[1].handle());
  ASSERT_EQ(1u, branchesAfterRemoval[1].extensibleGroups().size());
  const auto retainedBranchInlet = branchesAfterRemoval[1].componentInletNode(0u);
  const auto retainedBranchOutlet = branchesAfterRemoval[1].componentOutletNode(0u);
  ASSERT_TRUE(retainedBranchInlet);
  ASSERT_TRUE(retainedBranchOutlet);
  EXPECT_EQ(std::vector<openstudio::Handle>{retainedBranchInlet->handle()},
            objectHandles(plantLoop.demandSplitter().cast<ConnectorSplitter>().outletModelObjects()));
  EXPECT_EQ(std::vector<openstudio::Handle>{retainedBranchOutlet->handle()},
            objectHandles(plantLoop.demandMixer().cast<ConnectorMixer>().inletModelObjects()));

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(removedPipe));
  ASSERT_TRUE(removedPipe.inletModelObject());
  ASSERT_TRUE(removedPipe.outletModelObject());
  EXPECT_EQ(inletNodeHandle, removedPipe.inletModelObject()->handle());
  EXPECT_EQ(outletNodeHandle, removedPipe.outletModelObject()->handle());
  EXPECT_EQ(setpointTargetHandle, plantLoop.loopTemperatureSetpointNode().handle());
  branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  const auto branchHandlesAfterReAdd = objectHandles(branchList->branches());
  ASSERT_EQ(4u, branchHandlesAfterReAdd.size());
  std::vector<openstudio::Handle> splitterTargetsAfterReAdd;
  std::vector<openstudio::Handle> mixerTargetsAfterReAdd;
  const auto branchesAfterReAdd = branchList->branches();
  for (auto branch = branchesAfterReAdd.begin() + 1; branch != branchesAfterReAdd.end() - 1; ++branch) {
    ASSERT_EQ(1u, branch->extensibleGroups().size());
    const auto branchInlet = branch->componentInletNode(0u);
    const auto branchOutlet = branch->componentOutletNode(0u);
    ASSERT_TRUE(branchInlet);
    ASSERT_TRUE(branchOutlet);
    splitterTargetsAfterReAdd.push_back(branchInlet->handle());
    mixerTargetsAfterReAdd.push_back(branchOutlet->handle());
  }
  EXPECT_EQ(splitterTargetsAfterReAdd, objectHandles(plantLoop.demandSplitter().cast<ConnectorSplitter>().outletModelObjects()));
  EXPECT_EQ(mixerTargetsAfterReAdd, objectHandles(plantLoop.demandMixer().cast<ConnectorMixer>().inletModelObjects()));
}

TEST_F(EPModelFixture, PlantLoop_PipeBranchRemovalRejectsSerialRowsWithoutMutation) {
  Model model;
  PlantLoop supplyLoop(model);
  PipeAdiabatic supplyFirstPipe(model);
  PipeAdiabatic supplySecondPipe(model);
  ASSERT_TRUE(supplyLoop.addSupplyBranchForComponent(supplyFirstPipe));
  ASSERT_TRUE(supplyFirstPipe.outletModelObject());
  auto supplyInsertionNode = supplyFirstPipe.outletModelObject()->cast<Node>();
  ASSERT_TRUE(supplySecondPipe.addToNode(supplyInsertionNode));
  const auto supplyBefore = capturePlantAttachmentTopology(model, supplyLoop, supplyLoop, supplySecondPipe, true);
  EXPECT_FALSE(supplyLoop.removeSupplyBranchWithComponent(supplySecondPipe));
  EXPECT_EQ(supplyBefore, capturePlantAttachmentTopology(model, supplyLoop, supplyLoop, supplySecondPipe, true));

  PlantLoop demandLoop(model);
  PipeAdiabatic demandFirstPipe(model);
  PipeAdiabatic demandSecondPipe(model);
  ASSERT_TRUE(demandLoop.addDemandBranchForComponent(demandFirstPipe));
  ASSERT_TRUE(demandFirstPipe.outletModelObject());
  auto demandInsertionNode = demandFirstPipe.outletModelObject()->cast<Node>();
  ASSERT_TRUE(demandSecondPipe.addToNode(demandInsertionNode));
  const auto demandBefore = capturePlantAttachmentTopology(model, demandLoop, demandLoop, demandSecondPipe, false);
  EXPECT_FALSE(demandLoop.removeDemandBranchWithComponent(demandSecondPipe));
  EXPECT_EQ(demandBefore, capturePlantAttachmentTopology(model, demandLoop, demandLoop, demandSecondPipe, false));
}

TEST_F(EPModelFixture, PlantLoop_HeatingWaterCoilDemandMoveDefaultSourceToOccupiedTargetIsTransactional) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-heating-water-coil-demand-move.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  CoilHeatingWater coil(model);
  PipeAdiabatic targetPipe(model);
  ASSERT_TRUE(airLoop.setName("Moved Heating Coil Air Loop"));
  ASSERT_TRUE(sourceLoop.setName("Moved Heating Coil Source Plant Loop"));
  ASSERT_TRUE(targetLoop.setName("Moved Heating Coil Target Plant Loop"));
  ASSERT_TRUE(coil.setName("Moved Standalone Heating Water Coil"));
  ASSERT_TRUE(targetPipe.setName("Retained Target Demand Pipe"));
  ASSERT_TRUE(coil.setRatedInletWaterTemperature(61.25));

  auto airInsertionNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(airInsertionNode));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetPipe));
  auto sourceSetpointTarget = sourceLoop.supplyInletNode();
  auto targetSetpointTarget = targetLoop.supplyInletNode();
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpointTarget));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpointTarget));

  ASSERT_TRUE(coil.airInletModelObject());
  ASSERT_TRUE(coil.airOutletModelObject());
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());
  const auto airInletHandle = coil.airInletModelObject()->handle();
  const auto airOutletHandle = coil.airOutletModelObject()->handle();
  const auto sourceWaterInletHandle = coil.waterInletModelObject()->handle();
  const auto sourceWaterOutletHandle = coil.waterOutletModelObject()->handle();
  const auto airSupplyHandles = objectHandles(airLoop.supplyComponents());

  auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(controller->action());
  EXPECT_EQ("Normal", *controller->action());
  ASSERT_TRUE(controller->actuatorNode());
  ASSERT_TRUE(controller->sensorNode());
  const auto controllerHandle = controller->handle();
  const auto controllerSensorHandle = controller->sensorNode()->handle();
  auto controllerList = airLoop.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  const auto controllerListHandle = controllerList->handle();
  const auto controllerListMembers = objectHandles(controllerList->controllers());
  EXPECT_EQ(std::vector<openstudio::Handle>{controllerHandle}, controllerListMembers);

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchList->branches());
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(3u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto sourceDefaultBranchHandle = sourceBranchHandlesBefore[1];

  const auto before = captureWaterCoilMoveTopology(model, sourceLoop, targetLoop, airLoop, coil);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(coil));
  }
  expectWaterCoilMoveTopologyEqual(before, captureWaterCoilMoveTopology(model, sourceLoop, targetLoop, airLoop, coil));
  EXPECT_DOUBLE_EQ(61.25, coil.ratedInletWaterTemperature());

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(coil));
  EXPECT_FALSE(sourceLoop.demandComponent(coil.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(coil.handle()));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(targetLoop, *coil.plantLoop());
  ASSERT_TRUE(coil.airLoopHVAC());
  EXPECT_EQ(airLoop, *coil.airLoopHVAC());
  EXPECT_EQ(airSupplyHandles, objectHandles(airLoop.supplyComponents()));
  ASSERT_TRUE(coil.airInletModelObject());
  ASSERT_TRUE(coil.airOutletModelObject());
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());
  EXPECT_EQ(airInletHandle, coil.airInletModelObject()->handle());
  EXPECT_EQ(airOutletHandle, coil.airOutletModelObject()->handle());
  EXPECT_NE(sourceWaterInletHandle, coil.waterInletModelObject()->handle());
  EXPECT_NE(sourceWaterOutletHandle, coil.waterOutletModelObject()->handle());
  EXPECT_TRUE(model.getObject(sourceWaterInletHandle));
  EXPECT_TRUE(model.getObject(sourceWaterOutletHandle));
  EXPECT_DOUBLE_EQ(61.25, coil.ratedInletWaterTemperature());
  EXPECT_EQ(sourceSetpointTarget.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpointTarget.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(sourceBranchHandlesBefore, objectHandles(sourceBranchList->branches()));
  ASSERT_EQ(sourceDefaultBranchHandle, sourceBranchList->branches()[1].handle());
  EXPECT_TRUE(sourceBranchList->branches()[1].components().empty());
  expectDemandBranchAndConnectorOrder(sourceLoop, sourceBranchHandlesBefore);
  const auto targetBranchHandlesAfter = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, targetBranchHandlesAfter.size());
  EXPECT_EQ(targetBranchHandlesBefore[0], targetBranchHandlesAfter[0]);
  EXPECT_EQ(targetBranchHandlesBefore[1], targetBranchHandlesAfter[1]);
  EXPECT_EQ(targetBranchHandlesBefore[2], targetBranchHandlesAfter[3]);
  EXPECT_NE(targetBranchHandlesBefore[1], targetBranchHandlesAfter[2]);
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesAfter);

  controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  EXPECT_EQ(controllerHandle, controller->handle());
  ASSERT_TRUE(controller->action());
  EXPECT_EQ("Normal", *controller->action());
  ASSERT_TRUE(controller->actuatorNode());
  ASSERT_TRUE(controller->sensorNode());
  EXPECT_EQ(coil.waterInletModelObject()->handle(), controller->actuatorNode()->handle());
  EXPECT_EQ(controllerSensorHandle, controller->sensorNode()->handle());
  controllerList = airLoop.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  EXPECT_EQ(controllerListHandle, controllerList->handle());
  EXPECT_EQ(controllerListMembers, objectHandles(controllerList->controllers()));

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Moved Heating Coil Air Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Moved Heating Coil Source Plant Loop");
  auto loadedTargetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Moved Heating Coil Target Plant Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Moved Standalone Heating Water Coil");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedTargetLoop);
  ASSERT_TRUE(loadedCoil);
  EXPECT_FALSE(loadedSourceLoop->demandComponent(loadedCoil->handle()));
  EXPECT_TRUE(loadedTargetLoop->demandComponent(loadedCoil->handle()));
  ASSERT_TRUE(loadedCoil->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedCoil->plantLoop());
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_DOUBLE_EQ(61.25, loadedCoil->ratedInletWaterTemperature());
  const auto loadedController = loadedCoil->controllerWaterCoil();
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedController->action());
  EXPECT_EQ("Normal", *loadedController->action());
  ASSERT_TRUE(loadedController->actuatorNode());
  ASSERT_TRUE(loadedController->sensorNode());
  ASSERT_TRUE(loadedCoil->waterInletModelObject());
  ASSERT_TRUE(loadedCoil->airOutletModelObject());
  EXPECT_EQ(loadedCoil->waterInletModelObject()->handle(), loadedController->actuatorNode()->handle());
  EXPECT_EQ(loadedCoil->airOutletModelObject()->handle(), loadedController->sensorNode()->handle());
  const auto loadedControllerList = loadedAirLoop->getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
  ASSERT_TRUE(loadedControllerList);
  EXPECT_EQ(std::vector<openstudio::Handle>{loadedController->handle()}, objectHandles(loadedControllerList->controllers()));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_CoolingWaterCoilDemandMoveParallelSourceToDefaultTargetIsTransactional) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic retainedSourcePipe(model);
  CoilCoolingWater coil(model);
  ASSERT_TRUE(coil.setTypeOfAnalysis("DetailedAnalysis"));

  auto airInsertionNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(airInsertionNode));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(retainedSourcePipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coil));
  auto sourceSetpointTarget = sourceLoop.supplyInletNode();
  auto targetSetpointTarget = targetLoop.supplyInletNode();
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpointTarget));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpointTarget));

  ASSERT_TRUE(coil.airInletModelObject());
  ASSERT_TRUE(coil.airOutletModelObject());
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());
  const auto airInletHandle = coil.airInletModelObject()->handle();
  const auto airOutletHandle = coil.airOutletModelObject()->handle();
  const auto sourceWaterInletHandle = coil.waterInletModelObject()->handle();
  const auto sourceWaterOutletHandle = coil.waterOutletModelObject()->handle();
  const auto airSupplyHandles = objectHandles(airLoop.supplyComponents());

  auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(controller->action());
  EXPECT_EQ("Reverse", *controller->action());
  ASSERT_TRUE(controller->sensorNode());
  const auto controllerHandle = controller->handle();
  const auto controllerSensorHandle = controller->sensorNode()->handle();
  auto controllerList = airLoop.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  const auto controllerListHandle = controllerList->handle();
  const auto controllerListMembers = objectHandles(controllerList->controllers());

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchesBefore = sourceBranchList->branches();
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchesBefore);
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto removedBranch = std::ranges::find_if(sourceBranchesBefore, [&coil](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, coil.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceBranchesBefore.end(), removedBranch);
  const auto removedBranchHandle = removedBranch->handle();
  const auto targetDefaultBranchHandle = targetBranchHandlesBefore[1];
  auto expectedSourceBranchHandlesAfter = sourceBranchHandlesBefore;
  const auto removedHandle = std::ranges::find(expectedSourceBranchHandlesAfter, removedBranchHandle);
  ASSERT_NE(expectedSourceBranchHandlesAfter.end(), removedHandle);
  expectedSourceBranchHandlesAfter.erase(removedHandle);

  const auto before = captureWaterCoilMoveTopology(model, sourceLoop, targetLoop, airLoop, coil);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(coil));
  }
  expectWaterCoilMoveTopologyEqual(before, captureWaterCoilMoveTopology(model, sourceLoop, targetLoop, airLoop, coil));
  EXPECT_EQ("DetailedAnalysis", coil.typeOfAnalysis());

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(coil));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(sourceWaterInletHandle));
  EXPECT_TRUE(model.getObject(sourceWaterOutletHandle));
  EXPECT_FALSE(sourceLoop.demandComponent(coil.handle()));
  EXPECT_TRUE(sourceLoop.demandComponent(retainedSourcePipe.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(coil.handle()));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(targetLoop, *coil.plantLoop());
  ASSERT_TRUE(coil.airLoopHVAC());
  EXPECT_EQ(airLoop, *coil.airLoopHVAC());
  EXPECT_EQ(airSupplyHandles, objectHandles(airLoop.supplyComponents()));
  ASSERT_TRUE(coil.airInletModelObject());
  ASSERT_TRUE(coil.airOutletModelObject());
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());
  EXPECT_EQ(airInletHandle, coil.airInletModelObject()->handle());
  EXPECT_EQ(airOutletHandle, coil.airOutletModelObject()->handle());
  EXPECT_NE(sourceWaterInletHandle, coil.waterInletModelObject()->handle());
  EXPECT_NE(sourceWaterOutletHandle, coil.waterOutletModelObject()->handle());
  EXPECT_EQ("DetailedAnalysis", coil.typeOfAnalysis());
  EXPECT_EQ(sourceSetpointTarget.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpointTarget.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  expectDemandBranchAndConnectorOrder(sourceLoop, expectedSourceBranchHandlesAfter);
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  ASSERT_EQ(targetDefaultBranchHandle, targetBranchList->branches()[1].handle());
  EXPECT_EQ(std::vector<ModelObject>{coil.cast<ModelObject>()}, targetBranchList->branches()[1].components());
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);

  controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  EXPECT_EQ(controllerHandle, controller->handle());
  ASSERT_TRUE(controller->action());
  EXPECT_EQ("Reverse", *controller->action());
  ASSERT_TRUE(controller->actuatorNode());
  ASSERT_TRUE(controller->sensorNode());
  EXPECT_EQ(coil.waterInletModelObject()->handle(), controller->actuatorNode()->handle());
  EXPECT_EQ(controllerSensorHandle, controller->sensorNode()->handle());
  controllerList = airLoop.getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVACFields::ControllerListName);
  ASSERT_TRUE(controllerList);
  EXPECT_EQ(controllerListHandle, controllerList->handle());
  EXPECT_EQ(controllerListMembers, objectHandles(controllerList->controllers()));
}

TEST_F(EPModelFixture, PlantLoop_WaterCoilDemandMoveRejectsSameLoopAndNonSingleRowSourceWithoutMutation) {
  Model model;
  AirLoopHVAC sameLoopAir(model);
  PlantLoop sameLoopPlant(model);
  CoilHeatingWater sameLoopCoil(model);
  auto sameLoopAirNode = sameLoopAir.supplyOutletNode();
  ASSERT_TRUE(sameLoopCoil.addToNode(sameLoopAirNode));
  ASSERT_TRUE(sameLoopPlant.addDemandBranchForComponent(sameLoopCoil));
  const auto sameLoopBefore = captureWaterCoilMoveTopology(model, sameLoopPlant, sameLoopPlant, sameLoopAir, sameLoopCoil);
  EXPECT_FALSE(sameLoopPlant.addDemandBranchForComponent(sameLoopCoil));
  expectWaterCoilMoveTopologyEqual(sameLoopBefore, captureWaterCoilMoveTopology(model, sameLoopPlant, sameLoopPlant, sameLoopAir, sameLoopCoil));

  AirLoopHVAC serialAir(model);
  PlantLoop serialSource(model);
  PlantLoop serialTarget(model);
  CoilCoolingWater serialCoil(model);
  PipeAdiabatic serialPipe(model);
  auto serialAirNode = serialAir.supplyOutletNode();
  ASSERT_TRUE(serialCoil.addToNode(serialAirNode));
  ASSERT_TRUE(serialSource.addDemandBranchForComponent(serialCoil));
  ASSERT_TRUE(serialCoil.waterOutletModelObject());
  auto serialInsertionNode = serialCoil.waterOutletModelObject()->cast<Node>();
  ASSERT_TRUE(serialPipe.addToNode(serialInsertionNode));
  const auto serialBefore = captureWaterCoilMoveTopology(model, serialSource, serialTarget, serialAir, serialCoil);
  EXPECT_FALSE(serialTarget.addDemandBranchForComponent(serialCoil));
  expectWaterCoilMoveTopologyEqual(serialBefore, captureWaterCoilMoveTopology(model, serialSource, serialTarget, serialAir, serialCoil));
}

TEST_F(EPModelFixture, PlantLoop_ContainedReheatCoilDemandMoveDefaultSourceToOccupiedTargetIsTransactionalAcrossReload) {
  const auto idfPath =
    openstudio::tempDir()
    / openstudio::toPath("epmodel-contained-reheat-coil-default-move-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model seedModel;
  AirLoopHVAC seedAirLoop(seedModel);
  ThermalZone seedZone(seedModel);
  PlantLoop seedSourceLoop(seedModel);
  PlantLoop seedTargetLoop(seedModel);
  CoilHeatingWater seedCoil(seedModel);
  auto availabilitySchedule = seedModel.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeReheat seedTerminal(seedModel, availabilitySchedule, seedCoil);
  PipeAdiabatic seedTargetPipe(seedModel);
  ASSERT_TRUE(seedAirLoop.setName("Contained Reheat Default Move Air Loop"));
  ASSERT_TRUE(seedZone.setName("Contained Reheat Default Move Zone"));
  ASSERT_TRUE(seedSourceLoop.setName("Contained Reheat Default Move Source Loop"));
  ASSERT_TRUE(seedTargetLoop.setName("Contained Reheat Default Move Target Loop"));
  ASSERT_TRUE(seedCoil.setName("Contained Reheat Default Move Coil"));
  ASSERT_TRUE(seedTerminal.setName("Contained Reheat Default Move Terminal"));
  ASSERT_TRUE(seedTargetPipe.setName("Contained Reheat Default Move Target Pipe"));
  ASSERT_TRUE(seedTerminal.setMaximumAirFlowRate(1.75));
  ASSERT_TRUE(seedTerminal.setMaximumHotWaterorSteamFlowRate(0.014));
  ASSERT_TRUE(seedTerminal.setMinimumHotWaterorSteamFlowRate(0.002));
  ASSERT_TRUE(seedTerminal.setConvergenceTolerance(0.0007));
  ASSERT_TRUE(seedTerminal.setMaximumReheatAirTemperature(38.5));
  ASSERT_TRUE(seedCoil.setRatedInletWaterTemperature(63.25));
  ASSERT_TRUE(seedAirLoop.addBranchForZone(seedZone, seedTerminal));
  ASSERT_TRUE(seedSourceLoop.addDemandBranchForComponent(seedCoil));
  ASSERT_TRUE(seedTargetLoop.addDemandBranchForComponent(seedTargetPipe));
  auto seedSourceSetpoint = seedSourceLoop.supplyInletNode();
  auto seedTargetSetpoint = seedTargetLoop.supplyInletNode();
  ASSERT_TRUE(seedSourceLoop.setLoopTemperatureSetpointNode(seedSourceSetpoint));
  ASSERT_TRUE(seedTargetLoop.setLoopTemperatureSetpointNode(seedTargetSetpoint));
  EXPECT_FALSE(seedCoil.controllerWaterCoil());
  ASSERT_EQ(1u, seedTerminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit).size());
  ASSERT_TRUE(seedModel.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto airLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Contained Reheat Default Move Air Loop");
  auto zone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Contained Reheat Default Move Zone");
  auto sourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Contained Reheat Default Move Source Loop");
  auto targetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Contained Reheat Default Move Target Loop");
  auto coil = loadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Contained Reheat Default Move Coil");
  auto terminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeReheat>("Contained Reheat Default Move Terminal");
  ASSERT_TRUE(airLoop);
  ASSERT_TRUE(zone);
  ASSERT_TRUE(sourceLoop);
  ASSERT_TRUE(targetLoop);
  ASSERT_TRUE(coil);
  ASSERT_TRUE(terminal);

  auto sourceBranchList = sourceLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchList->branches());
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(3u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto sourceDefaultBranchHandle = sourceBranchHandlesBefore[1];
  ASSERT_TRUE(coil->waterInletModelObject());
  ASSERT_TRUE(coil->waterOutletModelObject());
  const auto sourceWaterInletHandle = coil->waterInletModelObject()->handle();
  const auto sourceWaterOutletHandle = coil->waterOutletModelObject()->handle();
  const auto sourceSetpointHandle = sourceLoop->loopTemperatureSetpointNode().handle();
  const auto targetSetpointHandle = targetLoop->loopTemperatureSetpointNode().handle();
  const auto externalBefore = captureContainedReheatExternalTopology(*loadedModel, *airLoop, *zone, *terminal, *coil);
  const auto before = captureContainedReheatMoveTopology(*loadedModel, *sourceLoop, *targetLoop, *airLoop, *zone, *terminal, *coil);

  {
    test::ScopedTestFailure failure(*loadedModel, detail::TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop->addDemandBranchForComponent(*coil));
  }
  EXPECT_EQ(before, captureContainedReheatMoveTopology(*loadedModel, *sourceLoop, *targetLoop, *airLoop, *zone, *terminal, *coil));

  ASSERT_TRUE(targetLoop->addDemandBranchForComponent(*coil));
  EXPECT_FALSE(sourceLoop->demandComponent(coil->handle()));
  EXPECT_TRUE(targetLoop->demandComponent(coil->handle()));
  ASSERT_TRUE(coil->plantLoop());
  EXPECT_EQ(*targetLoop, *coil->plantLoop());
  EXPECT_EQ(externalBefore, captureContainedReheatExternalTopology(*loadedModel, *airLoop, *zone, *terminal, *coil));
  EXPECT_FALSE(coil->controllerWaterCoil());
  ASSERT_TRUE(coil->waterInletModelObject());
  ASSERT_TRUE(coil->waterOutletModelObject());
  EXPECT_NE(sourceWaterInletHandle, coil->waterInletModelObject()->handle());
  EXPECT_NE(sourceWaterOutletHandle, coil->waterOutletModelObject()->handle());
  EXPECT_TRUE(loadedModel->getObject(sourceWaterInletHandle));
  EXPECT_TRUE(loadedModel->getObject(sourceWaterOutletHandle));
  EXPECT_EQ(sourceSetpointHandle, sourceLoop->loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpointHandle, targetLoop->loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(sourceBranchHandlesBefore, objectHandles(sourceBranchList->branches()));
  ASSERT_EQ(sourceDefaultBranchHandle, sourceBranchList->branches()[1].handle());
  EXPECT_TRUE(sourceBranchList->branches()[1].components().empty());
  expectDemandBranchAndConnectorOrder(*sourceLoop, sourceBranchHandlesBefore);
  const auto targetBranchHandlesAfter = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, targetBranchHandlesAfter.size());
  EXPECT_EQ(targetBranchHandlesBefore[0], targetBranchHandlesAfter[0]);
  EXPECT_EQ(targetBranchHandlesBefore[1], targetBranchHandlesAfter[1]);
  EXPECT_EQ(targetBranchHandlesBefore[2], targetBranchHandlesAfter[3]);
  EXPECT_NE(targetBranchHandlesBefore[1], targetBranchHandlesAfter[2]);
  expectDemandBranchAndConnectorOrder(*targetLoop, targetBranchHandlesAfter);

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedAirLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Contained Reheat Default Move Air Loop");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Contained Reheat Default Move Zone");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Contained Reheat Default Move Source Loop");
  auto reloadedTargetLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Contained Reheat Default Move Target Loop");
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Contained Reheat Default Move Coil");
  auto reloadedTerminal =
    reloadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeReheat>("Contained Reheat Default Move Terminal");
  ASSERT_TRUE(reloadedAirLoop);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedTargetLoop);
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedTerminal);
  EXPECT_FALSE(reloadedSourceLoop->demandComponent(reloadedCoil->handle()));
  EXPECT_TRUE(reloadedTargetLoop->demandComponent(reloadedCoil->handle()));
  ASSERT_TRUE(reloadedCoil->containingHVACComponent());
  EXPECT_EQ(reloadedTerminal->handle(), reloadedCoil->containingHVACComponent()->handle());
  EXPECT_EQ(reloadedCoil->handle(), reloadedTerminal->reheatCoil().handle());
  ASSERT_TRUE(reloadedCoil->airInletModelObject());
  ASSERT_TRUE(reloadedCoil->airOutletModelObject());
  ASSERT_TRUE(reloadedTerminal->inletModelObject());
  ASSERT_TRUE(reloadedTerminal->outletModelObject());
  EXPECT_EQ(reloadedCoil->airInletModelObject()->handle(), reloadedTerminal->inletModelObject()->handle());
  EXPECT_EQ(reloadedCoil->airOutletModelObject()->handle(), reloadedTerminal->outletModelObject()->handle());
  EXPECT_FALSE(reloadedCoil->controllerWaterCoil());
  EXPECT_EQ(1u, std::ranges::count_if(reloadedAirLoop->demandComponents(),
                                      [&reloadedTerminal](const auto& component) { return component.handle() == reloadedTerminal->handle(); }));
  EXPECT_EQ(1u, std::ranges::count_if(reloadedZone->equipment(),
                                      [&reloadedTerminal](const auto& component) { return component.handle() == reloadedTerminal->handle(); }));
  const auto reloadedAdus = reloadedTerminal->getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit);
  ASSERT_EQ(1u, reloadedAdus.size());
  auto reloadedAdu = reloadedAdus.front().optionalCast<ZoneHVACAirDistributionUnit>();
  ASSERT_TRUE(reloadedAdu);
  ASSERT_TRUE(reloadedAdu->airTerminal());
  ASSERT_TRUE(reloadedAdu->outletNode());
  EXPECT_EQ(reloadedTerminal->handle(), reloadedAdu->airTerminal()->handle());
  EXPECT_EQ(reloadedTerminal->outletModelObject()->handle(), reloadedAdu->outletNode()->handle());
  ASSERT_TRUE(reloadedTerminal->maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.75, *reloadedTerminal->maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(63.25, reloadedCoil->ratedInletWaterTemperature());
}

TEST_F(EPModelFixture, PlantLoop_ContainedReheatCoilDemandMoveParallelSourceToDefaultTargetIsTransactional) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic retainedSourcePipe(model);
  CoilHeatingWater coil(model);
  auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, availabilitySchedule, coil);
  ASSERT_TRUE(terminal.setMaximumReheatAirTemperature(39.25));
  ASSERT_TRUE(coil.setRatedInletWaterTemperature(62.75));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(retainedSourcePipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coil));
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));
  EXPECT_FALSE(coil.controllerWaterCoil());

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchesBefore = sourceBranchList->branches();
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchesBefore);
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto removedBranch = std::ranges::find_if(sourceBranchesBefore, [&coil](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, coil.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceBranchesBefore.end(), removedBranch);
  const auto removedBranchHandle = removedBranch->handle();
  auto expectedSourceBranchHandlesAfter = sourceBranchHandlesBefore;
  const auto removedHandle = std::ranges::find(expectedSourceBranchHandlesAfter, removedBranchHandle);
  ASSERT_NE(expectedSourceBranchHandlesAfter.end(), removedHandle);
  expectedSourceBranchHandlesAfter.erase(removedHandle);
  const auto targetDefaultBranchHandle = targetBranchHandlesBefore[1];
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());
  const auto sourceWaterInletHandle = coil.waterInletModelObject()->handle();
  const auto sourceWaterOutletHandle = coil.waterOutletModelObject()->handle();
  const auto externalBefore = captureContainedReheatExternalTopology(model, airLoop, zone, terminal, coil);
  const auto before = captureContainedReheatMoveTopology(model, sourceLoop, targetLoop, airLoop, zone, terminal, coil);

  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(coil));
  }
  EXPECT_EQ(before, captureContainedReheatMoveTopology(model, sourceLoop, targetLoop, airLoop, zone, terminal, coil));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(coil));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(sourceWaterInletHandle));
  EXPECT_TRUE(model.getObject(sourceWaterOutletHandle));
  EXPECT_FALSE(sourceLoop.demandComponent(coil.handle()));
  EXPECT_TRUE(sourceLoop.demandComponent(retainedSourcePipe.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(coil.handle()));
  EXPECT_EQ(externalBefore, captureContainedReheatExternalTopology(model, airLoop, zone, terminal, coil));
  EXPECT_FALSE(coil.controllerWaterCoil());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  expectDemandBranchAndConnectorOrder(sourceLoop, expectedSourceBranchHandlesAfter);
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  ASSERT_EQ(targetDefaultBranchHandle, targetBranchList->branches()[1].handle());
  EXPECT_EQ(std::vector<ModelObject>{coil.cast<ModelObject>()}, targetBranchList->branches()[1].components());
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);
}

TEST_F(EPModelFixture, PlantLoop_ContainedReheatCoilDemandMoveRejectsSameLoopAndSerialSourceWithoutMutation) {
  Model model;
  AirLoopHVAC sameLoopAir(model);
  ThermalZone sameLoopZone(model);
  PlantLoop sameLoopPlant(model);
  CoilHeatingWater sameLoopCoil(model);
  auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeReheat sameLoopTerminal(model, availabilitySchedule, sameLoopCoil);
  ASSERT_TRUE(sameLoopAir.addBranchForZone(sameLoopZone, sameLoopTerminal));
  ASSERT_TRUE(sameLoopPlant.addDemandBranchForComponent(sameLoopCoil));
  const auto sameLoopBefore =
    captureContainedReheatMoveTopology(model, sameLoopPlant, sameLoopPlant, sameLoopAir, sameLoopZone, sameLoopTerminal, sameLoopCoil);
  EXPECT_FALSE(sameLoopPlant.addDemandBranchForComponent(sameLoopCoil));
  EXPECT_EQ(sameLoopBefore,
            captureContainedReheatMoveTopology(model, sameLoopPlant, sameLoopPlant, sameLoopAir, sameLoopZone, sameLoopTerminal, sameLoopCoil));

  AirLoopHVAC serialAir(model);
  ThermalZone serialZone(model);
  PlantLoop serialSource(model);
  PlantLoop serialTarget(model);
  CoilHeatingWater serialCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat serialTerminal(model, availabilitySchedule, serialCoil);
  PipeAdiabatic serialPipe(model);
  ASSERT_TRUE(serialAir.addBranchForZone(serialZone, serialTerminal));
  ASSERT_TRUE(serialSource.addDemandBranchForComponent(serialCoil));
  ASSERT_TRUE(serialCoil.waterOutletModelObject());
  auto serialInsertionNode = serialCoil.waterOutletModelObject()->cast<Node>();
  ASSERT_TRUE(serialPipe.addToNode(serialInsertionNode));
  const auto serialBefore = captureContainedReheatMoveTopology(model, serialSource, serialTarget, serialAir, serialZone, serialTerminal, serialCoil);
  EXPECT_FALSE(serialTarget.addDemandBranchForComponent(serialCoil));
  EXPECT_EQ(serialBefore, captureContainedReheatMoveTopology(model, serialSource, serialTarget, serialAir, serialZone, serialTerminal, serialCoil));
}

TEST_F(EPModelFixture, PlantLoop_FourPipeFanCoilHeatingDemandMoveDefaultSourceToOccupiedTargetIsTransactionalAcrossReload) {
  const auto idfPath = openstudio::tempDir()
                       / openstudio::toPath("epmodel-four-pipe-fan-coil-heating-move-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model seedModel;
  PlantLoop seedSourceLoop(seedModel);
  PlantLoop seedTargetLoop(seedModel);
  PlantLoop seedCoolingLoop(seedModel);
  ThermalZone seedZone(seedModel);
  ZoneHVACFourPipeFanCoil seedFanCoil(seedModel);
  FanConstantVolume seedFan(seedModel);
  CoilCoolingWater seedCooling(seedModel);
  CoilHeatingWater seedHeating(seedModel);
  PipeAdiabatic seedTargetPipe(seedModel);
  ASSERT_TRUE(seedSourceLoop.setName("Four Pipe Heating Move Source"));
  ASSERT_TRUE(seedTargetLoop.setName("Four Pipe Heating Move Target"));
  ASSERT_TRUE(seedCoolingLoop.setName("Four Pipe Heating Move Cooling Loop"));
  ASSERT_TRUE(seedZone.setName("Four Pipe Heating Move Zone"));
  ASSERT_TRUE(seedFanCoil.setName("Four Pipe Heating Move Fan Coil"));
  ASSERT_TRUE(seedFan.setName("Four Pipe Heating Move Fan"));
  ASSERT_TRUE(seedCooling.setName("Four Pipe Heating Move Cooling Coil"));
  ASSERT_TRUE(seedHeating.setName("Four Pipe Heating Move Heating Coil"));
  ASSERT_TRUE(seedTargetPipe.setName("Four Pipe Heating Move Target Pipe"));
  ASSERT_TRUE(seedFanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(seedFanCoil.setSupplyAirFan(seedFan));
  ASSERT_TRUE(seedFanCoil.setCoolingCoil(seedCooling));
  ASSERT_TRUE(seedFanCoil.setHeatingCoil(seedHeating));
  ASSERT_TRUE(seedFanCoil.setMaximumSupplyAirFlowRate(1.35));
  ASSERT_TRUE(seedFanCoil.setMaximumColdWaterFlowRate(0.42));
  ASSERT_TRUE(seedFanCoil.setMinimumColdWaterFlowRate(0.04));
  ASSERT_TRUE(seedFanCoil.setCoolingConvergenceTolerance(0.0022));
  ASSERT_TRUE(seedFanCoil.setMaximumHotWaterFlowRate(0.31));
  ASSERT_TRUE(seedFanCoil.setMinimumHotWaterFlowRate(0.03));
  ASSERT_TRUE(seedFanCoil.setHeatingConvergenceTolerance(0.0018));
  ASSERT_TRUE(seedFan.setPressureRise(525.0));
  ASSERT_TRUE(seedCooling.setDesignWaterFlowRate(0.27));
  ASSERT_TRUE(seedCooling.setDesignInletWaterTemperature(6.75));
  ASSERT_TRUE(seedCooling.setDesignOutletAirTemperature(13.2));
  ASSERT_TRUE(seedHeating.setMaximumWaterFlowRate(0.19));
  ASSERT_TRUE(seedHeating.setRatedInletWaterTemperature(62.25));
  ASSERT_TRUE(seedHeating.setRatedOutletAirTemperature(37.4));
  ASSERT_TRUE(seedFanCoil.addToThermalZone(seedZone));
  ASSERT_TRUE(seedCoolingLoop.addDemandBranchForComponent(seedCooling));
  ASSERT_TRUE(seedSourceLoop.addDemandBranchForComponent(seedHeating));
  ASSERT_TRUE(seedTargetLoop.addDemandBranchForComponent(seedTargetPipe));
  auto seedSourceSetpoint = seedSourceLoop.supplyInletNode();
  auto seedTargetSetpoint = seedTargetLoop.supplyInletNode();
  ASSERT_TRUE(seedSourceLoop.setLoopTemperatureSetpointNode(seedSourceSetpoint));
  ASSERT_TRUE(seedTargetLoop.setLoopTemperatureSetpointNode(seedTargetSetpoint));
  EXPECT_FALSE(seedCooling.controllerWaterCoil());
  EXPECT_FALSE(seedHeating.controllerWaterCoil());
  ASSERT_TRUE(seedModel.save(idfPath, true));

  auto model = Model::load(idfPath);
  ASSERT_TRUE(model);
  auto sourceLoop = model->getConcreteModelObjectByName<PlantLoop>("Four Pipe Heating Move Source");
  auto targetLoop = model->getConcreteModelObjectByName<PlantLoop>("Four Pipe Heating Move Target");
  auto coolingLoop = model->getConcreteModelObjectByName<PlantLoop>("Four Pipe Heating Move Cooling Loop");
  auto zone = model->getConcreteModelObjectByName<ThermalZone>("Four Pipe Heating Move Zone");
  auto fanCoil = model->getConcreteModelObjectByName<ZoneHVACFourPipeFanCoil>("Four Pipe Heating Move Fan Coil");
  auto fan = model->getConcreteModelObjectByName<FanConstantVolume>("Four Pipe Heating Move Fan");
  auto cooling = model->getConcreteModelObjectByName<CoilCoolingWater>("Four Pipe Heating Move Cooling Coil");
  auto heating = model->getConcreteModelObjectByName<CoilHeatingWater>("Four Pipe Heating Move Heating Coil");
  auto targetPipe = model->getConcreteModelObjectByName<PipeAdiabatic>("Four Pipe Heating Move Target Pipe");
  ASSERT_TRUE(sourceLoop);
  ASSERT_TRUE(targetLoop);
  ASSERT_TRUE(coolingLoop);
  ASSERT_TRUE(zone);
  ASSERT_TRUE(fanCoil);
  ASSERT_TRUE(fan);
  ASSERT_TRUE(cooling);
  ASSERT_TRUE(heating);
  ASSERT_TRUE(targetPipe);

  auto sourceBranchList = sourceLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchList->branches());
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(3u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto sourceDefaultBranchHandle = sourceBranchHandlesBefore[1];
  ASSERT_TRUE(heating->waterInletModelObject());
  ASSERT_TRUE(heating->waterOutletModelObject());
  const auto oldHeatingInlet = heating->waterInletModelObject()->handle();
  const auto oldHeatingOutlet = heating->waterOutletModelObject()->handle();
  const auto before = captureFourPipeFanCoilMoveTopology(*model, *sourceLoop, *targetLoop, *zone, *fanCoil, *fan, *cooling, *heating);

  {
    test::ScopedTestFailure failure(*model, detail::TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop->addDemandBranchForComponent(*heating));
  }
  EXPECT_EQ(before, captureFourPipeFanCoilMoveTopology(*model, *sourceLoop, *targetLoop, *zone, *fanCoil, *fan, *cooling, *heating));

  ASSERT_TRUE(targetLoop->addDemandBranchForComponent(*heating));
  EXPECT_FALSE(sourceLoop->demandComponent(heating->handle()));
  EXPECT_TRUE(targetLoop->demandComponent(heating->handle()));
  EXPECT_TRUE(targetLoop->demandComponent(targetPipe->handle()));
  EXPECT_TRUE(coolingLoop->demandComponent(cooling->handle()));
  EXPECT_TRUE(model->getObject(oldHeatingInlet));
  EXPECT_TRUE(model->getObject(oldHeatingOutlet));
  const auto after = captureFourPipeFanCoilMoveTopology(*model, *sourceLoop, *targetLoop, *zone, *fanCoil, *fan, *cooling, *heating);
  expectFourPipeFanCoilExternalTopologyPreserved(before, after, true);
  EXPECT_TRUE(before.plantTopology.sourceSetpointTargetHandle == after.plantTopology.sourceSetpointTargetHandle);
  EXPECT_TRUE(before.plantTopology.targetSetpointTargetHandle == after.plantTopology.targetSetpointTargetHandle);

  sourceBranchList = sourceLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(sourceBranchHandlesBefore, objectHandles(sourceBranchList->branches()));
  EXPECT_EQ(sourceDefaultBranchHandle, sourceBranchList->branches()[1].handle());
  EXPECT_TRUE(sourceBranchList->branches()[1].components().empty());
  expectDemandBranchAndConnectorOrder(*sourceLoop, sourceBranchHandlesBefore);
  const auto targetBranchHandlesAfter = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, targetBranchHandlesAfter.size());
  EXPECT_EQ(targetBranchHandlesBefore[0], targetBranchHandlesAfter[0]);
  EXPECT_EQ(targetBranchHandlesBefore[1], targetBranchHandlesAfter[1]);
  EXPECT_EQ(targetBranchHandlesBefore[2], targetBranchHandlesAfter[3]);
  expectDemandBranchAndConnectorOrder(*targetLoop, targetBranchHandlesAfter);

  ASSERT_TRUE(model->save(idfPath, true));
  auto reloaded = Model::load(idfPath);
  ASSERT_TRUE(reloaded);
  auto reloadedSource = reloaded->getConcreteModelObjectByName<PlantLoop>("Four Pipe Heating Move Source");
  auto reloadedTarget = reloaded->getConcreteModelObjectByName<PlantLoop>("Four Pipe Heating Move Target");
  auto reloadedCoolingLoop = reloaded->getConcreteModelObjectByName<PlantLoop>("Four Pipe Heating Move Cooling Loop");
  auto reloadedZone = reloaded->getConcreteModelObjectByName<ThermalZone>("Four Pipe Heating Move Zone");
  auto reloadedFanCoil = reloaded->getConcreteModelObjectByName<ZoneHVACFourPipeFanCoil>("Four Pipe Heating Move Fan Coil");
  auto reloadedFan = reloaded->getConcreteModelObjectByName<FanConstantVolume>("Four Pipe Heating Move Fan");
  auto reloadedCooling = reloaded->getConcreteModelObjectByName<CoilCoolingWater>("Four Pipe Heating Move Cooling Coil");
  auto reloadedHeating = reloaded->getConcreteModelObjectByName<CoilHeatingWater>("Four Pipe Heating Move Heating Coil");
  ASSERT_TRUE(reloadedSource);
  ASSERT_TRUE(reloadedTarget);
  ASSERT_TRUE(reloadedCoolingLoop);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedFanCoil);
  ASSERT_TRUE(reloadedFan);
  ASSERT_TRUE(reloadedCooling);
  ASSERT_TRUE(reloadedHeating);
  EXPECT_FALSE(reloadedSource->demandComponent(reloadedHeating->handle()));
  EXPECT_TRUE(reloadedTarget->demandComponent(reloadedHeating->handle()));
  EXPECT_TRUE(reloadedCoolingLoop->demandComponent(reloadedCooling->handle()));
  EXPECT_EQ(1u, std::ranges::count_if(reloadedZone->equipment(),
                                      [&reloadedFanCoil](const auto& equipment) { return equipment.handle() == reloadedFanCoil->handle(); }));
  EXPECT_EQ((std::vector<ModelObject>{reloadedFan->cast<ModelObject>(), reloadedCooling->cast<ModelObject>(), reloadedHeating->cast<ModelObject>()}),
            reloadedFanCoil->children());
  EXPECT_FALSE(reloadedCooling->controllerWaterCoil());
  EXPECT_FALSE(reloadedHeating->controllerWaterCoil());
  const auto reloadedAfter = captureFourPipeFanCoilMoveTopology(*reloaded, *reloadedSource, *reloadedTarget, *reloadedZone, *reloadedFanCoil,
                                                                *reloadedFan, *reloadedCooling, *reloadedHeating);
  expectFourPipeFanCoilExternalTopologySurvivesReload(after, reloadedAfter);

  const auto fanCoilHandle = reloadedFanCoil->handle();
  const auto fanHandle = reloadedFan->handle();
  const auto coolingHandle = reloadedCooling->handle();
  const auto heatingHandle = reloadedHeating->handle();
  EXPECT_FALSE(reloadedFanCoil->remove().empty());
  EXPECT_FALSE(reloaded->getObject(fanCoilHandle));
  EXPECT_FALSE(reloaded->getObject(fanHandle));
  EXPECT_FALSE(reloaded->getObject(coolingHandle));
  EXPECT_FALSE(reloaded->getObject(heatingHandle));
  EXPECT_FALSE(reloadedCoolingLoop->demandComponent(coolingHandle));
  EXPECT_FALSE(reloadedTarget->demandComponent(heatingHandle));
  EXPECT_TRUE(reloaded->getObject(reloadedSource->handle()));
  EXPECT_TRUE(reloaded->getObject(reloadedTarget->handle()));
  EXPECT_TRUE(reloaded->getObject(reloadedCoolingLoop->handle()));
}

TEST_F(EPModelFixture, PlantLoop_FourPipeFanCoilCoolingDemandMoveParallelSourceToDefaultTargetIsTransactional) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PlantLoop heatingLoop(model);
  ThermalZone zone(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater cooling(model);
  CoilHeatingWater heating(model);
  PipeAdiabatic retainedSourcePipe(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(cooling));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heating));
  ASSERT_TRUE(fanCoil.setMaximumSupplyAirFlowRate(1.15));
  ASSERT_TRUE(fanCoil.setMaximumColdWaterFlowRate(0.39));
  ASSERT_TRUE(fanCoil.setMinimumColdWaterFlowRate(0.035));
  ASSERT_TRUE(fanCoil.setCoolingConvergenceTolerance(0.0024));
  ASSERT_TRUE(fanCoil.setMaximumHotWaterFlowRate(0.29));
  ASSERT_TRUE(fanCoil.setMinimumHotWaterFlowRate(0.025));
  ASSERT_TRUE(fanCoil.setHeatingConvergenceTolerance(0.0016));
  ASSERT_TRUE(fan.setPressureRise(485.0));
  ASSERT_TRUE(cooling.setDesignWaterFlowRate(0.24));
  ASSERT_TRUE(cooling.setDesignInletWaterTemperature(7.25));
  ASSERT_TRUE(cooling.setDesignOutletAirTemperature(13.8));
  ASSERT_TRUE(heating.setMaximumWaterFlowRate(0.17));
  ASSERT_TRUE(heating.setRatedInletWaterTemperature(61.75));
  ASSERT_TRUE(heating.setRatedOutletAirTemperature(36.9));
  ASSERT_TRUE(fanCoil.addToThermalZone(zone));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(retainedSourcePipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(cooling));
  ASSERT_TRUE(heatingLoop.addDemandBranchForComponent(heating));
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchesBefore = sourceBranchList->branches();
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchesBefore);
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto coolingBranch = std::ranges::find_if(sourceBranchesBefore, [&cooling](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, cooling.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceBranchesBefore.end(), coolingBranch);
  const auto removedBranchHandle = coolingBranch->handle();
  auto expectedSourceBranchHandlesAfter = sourceBranchHandlesBefore;
  expectedSourceBranchHandlesAfter.erase(std::ranges::find(expectedSourceBranchHandlesAfter, removedBranchHandle));
  const auto targetDefaultBranchHandle = targetBranchHandlesBefore[1];
  ASSERT_TRUE(cooling.waterInletModelObject());
  ASSERT_TRUE(cooling.waterOutletModelObject());
  const auto oldCoolingInlet = cooling.waterInletModelObject()->handle();
  const auto oldCoolingOutlet = cooling.waterOutletModelObject()->handle();
  const auto before = captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating);

  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterWaterCoilBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(cooling));
  }
  EXPECT_EQ(before, captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(cooling));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(oldCoolingInlet));
  EXPECT_TRUE(model.getObject(oldCoolingOutlet));
  EXPECT_FALSE(sourceLoop.demandComponent(cooling.handle()));
  EXPECT_TRUE(sourceLoop.demandComponent(retainedSourcePipe.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(cooling.handle()));
  EXPECT_TRUE(heatingLoop.demandComponent(heating.handle()));
  const auto after = captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating);
  expectFourPipeFanCoilExternalTopologyPreserved(before, after, false);
  EXPECT_TRUE(before.plantTopology.sourceSetpointTargetHandle == after.plantTopology.sourceSetpointTargetHandle);
  EXPECT_TRUE(before.plantTopology.targetSetpointTargetHandle == after.plantTopology.targetSetpointTargetHandle);

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(expectedSourceBranchHandlesAfter, objectHandles(sourceBranchList->branches()));
  expectDemandBranchAndConnectorOrder(sourceLoop, expectedSourceBranchHandlesAfter);
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  EXPECT_EQ(targetDefaultBranchHandle, targetBranchList->branches()[1].handle());
  EXPECT_EQ(std::vector<ModelObject>{cooling.cast<ModelObject>()}, targetBranchList->branches()[1].components());
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);
}

TEST_F(EPModelFixture, PlantLoop_FourPipeFanCoilDemandMoveRejectsSameLoopSerialDetachedAndWrongOwnerWithoutMutation) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PlantLoop coolingLoop(model);
  ThermalZone zone(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater cooling(model);
  CoilHeatingWater heating(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(cooling));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heating));
  ASSERT_TRUE(fanCoil.addToThermalZone(zone));
  ASSERT_TRUE(coolingLoop.addDemandBranchForComponent(cooling));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heating));

  const auto sameLoopBefore = captureFourPipeFanCoilMoveTopology(model, sourceLoop, sourceLoop, zone, fanCoil, fan, cooling, heating);
  EXPECT_FALSE(sourceLoop.addDemandBranchForComponent(heating));
  EXPECT_EQ(sameLoopBefore, captureFourPipeFanCoilMoveTopology(model, sourceLoop, sourceLoop, zone, fanCoil, fan, cooling, heating));

  ASSERT_TRUE(heating.waterOutletModelObject());
  PipeAdiabatic serialPipe(model);
  auto serialInsertionNode = heating.waterOutletModelObject()->cast<Node>();
  ASSERT_TRUE(serialPipe.addToNode(serialInsertionNode));
  const auto serialBefore = captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating);
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heating));
  EXPECT_EQ(serialBefore, captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating));

  PlantLoop detachedSource(model);
  PlantLoop detachedTarget(model);
  PlantLoop detachedCoolingLoop(model);
  ZoneHVACFourPipeFanCoil detachedFanCoil(model);
  FanConstantVolume detachedFan(model);
  CoilCoolingWater detachedCooling(model);
  CoilHeatingWater detachedHeating(model);
  ASSERT_TRUE(detachedFanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(detachedFanCoil.setSupplyAirFan(detachedFan));
  ASSERT_TRUE(detachedFanCoil.setCoolingCoil(detachedCooling));
  ASSERT_TRUE(detachedFanCoil.setHeatingCoil(detachedHeating));
  ASSERT_TRUE(detachedCoolingLoop.addDemandBranchForComponent(detachedCooling));
  ASSERT_TRUE(detachedSource.addDemandBranchForComponent(detachedHeating));
  const auto detachedBefore = capturePlantTopology(model, detachedSource, detachedTarget, false);
  const auto detachedObjectsBefore = objectHandles(model.objects());
  EXPECT_FALSE(detachedTarget.addDemandBranchForComponent(detachedHeating));
  EXPECT_EQ(detachedBefore, capturePlantTopology(model, detachedSource, detachedTarget, false));
  EXPECT_EQ(detachedObjectsBefore, objectHandles(model.objects()));

  PlantLoop wrongSource(model);
  PlantLoop wrongTarget(model);
  ThermalZone wrongZone(model);
  ZoneHVACUnitVentilator wrongOwner(model);
  FanConstantVolume wrongFan(model);
  CoilHeatingWater wrongHeating(model);
  ASSERT_TRUE(wrongOwner.setSupplyAirFan(wrongFan));
  ASSERT_TRUE(wrongOwner.setHeatingCoil(wrongHeating));
  ASSERT_TRUE(wrongOwner.addToThermalZone(wrongZone));
  ASSERT_TRUE(wrongSource.addDemandBranchForComponent(wrongHeating));
  const auto wrongBefore = capturePlantTopology(model, wrongSource, wrongTarget, false);
  const auto wrongObjectsBefore = objectHandles(model.objects());
  EXPECT_FALSE(wrongTarget.addDemandBranchForComponent(wrongHeating));
  EXPECT_EQ(wrongBefore, capturePlantTopology(model, wrongSource, wrongTarget, false));
  EXPECT_EQ(wrongObjectsBefore, objectHandles(model.objects()));
}

TEST_F(EPModelFixture, PlantLoop_FourPipeFanCoilDemandMoveRejectsInletSideMixerAirLoopOwnershipWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctInletSideMixer inletSideMixer(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater cooling(model);
  CoilHeatingWater heating(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PlantLoop coolingLoop(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(cooling));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heating));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, inletSideMixer));
  ASSERT_TRUE(inletSideMixer.outletModelObject());
  auto mixerOutlet = inletSideMixer.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(mixerOutlet);
  ASSERT_TRUE(fanCoil.addToNode(*mixerOutlet));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heating));
  ASSERT_TRUE(coolingLoop.addDemandBranchForComponent(cooling));

  const auto before = captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating);
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heating));
  EXPECT_EQ(before, captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating));
  EXPECT_TRUE(airLoop.demandComponent(inletSideMixer.handle()));
  ASSERT_TRUE(fanCoil.thermalZone());
  EXPECT_EQ(zone.handle(), fanCoil.thermalZone()->handle());
}

TEST_F(EPModelFixture, PlantLoop_FourPipeFanCoilDemandMoveRejectsTypedAndRawControllerActuatorCollisionsForSelectedAndSiblingChildren) {
  struct ControllerCollisionCase
  {
    bool selectedHeating;
    bool rawOnly;
    bool collideWithSibling;
  };
  const std::array cases = {ControllerCollisionCase{true, false, false},  ControllerCollisionCase{true, true, false},
                            ControllerCollisionCase{false, false, false}, ControllerCollisionCase{false, true, false},
                            ControllerCollisionCase{true, false, true},   ControllerCollisionCase{true, true, true},
                            ControllerCollisionCase{false, false, true},  ControllerCollisionCase{false, true, true}};
  for (const auto& testCase : cases) {
    const bool selectedHeating = testCase.selectedHeating;
    const bool rawOnly = testCase.rawOnly;
    Model model;
    ThermalZone zone(model);
    ZoneHVACFourPipeFanCoil fanCoil(model);
    FanConstantVolume fan(model);
    CoilCoolingWater cooling(model);
    CoilHeatingWater heating(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    PlantLoop siblingLoop(model);
    ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
    ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
    ASSERT_TRUE(fanCoil.setCoolingCoil(cooling));
    ASSERT_TRUE(fanCoil.setHeatingCoil(heating));
    ASSERT_TRUE(fanCoil.addToThermalZone(zone));
    auto selected = selectedHeating ? heating.cast<WaterToAirComponent>() : cooling.cast<WaterToAirComponent>();
    auto sibling = selectedHeating ? cooling.cast<WaterToAirComponent>() : heating.cast<WaterToAirComponent>();
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(selected));
    ASSERT_TRUE(siblingLoop.addDemandBranchForComponent(sibling));
    const auto controlled = testCase.collideWithSibling ? sibling : selected;
    ASSERT_TRUE(controlled.waterInletModelObject());
    ASSERT_TRUE(controlled.airOutletModelObject());
    auto waterInlet = controlled.waterInletModelObject()->optionalCast<Node>();
    auto airOutlet = controlled.airOutletModelObject()->optionalCast<Node>();
    ASSERT_TRUE(waterInlet);
    ASSERT_TRUE(airOutlet);

    ControllerWaterCoil controller(model);
    if (rawOnly) {
      auto workspaceImpl = controller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(workspaceImpl);
      ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Controller_WaterCoilFields::ActuatorNodeName,
                                                                               waterInlet->nameString(), false));
    } else {
      ASSERT_TRUE(controller.setActuatorNode(*waterInlet));
      ASSERT_TRUE(controller.setSensorNode(*airOutlet));
      const bool controllerOnHeating = selectedHeating != testCase.collideWithSibling;
      const auto inferredController = controllerOnHeating ? heating.controllerWaterCoil() : cooling.controllerWaterCoil();
      ASSERT_TRUE(inferredController);
      EXPECT_EQ(controller.handle(), inferredController->handle());
    }

    const auto before = captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(selected))
      << (selectedHeating ? "heating" : "cooling") << " move, " << (rawOnly ? "raw" : "typed") << " actuator on "
      << (testCase.collideWithSibling ? "sibling" : "selected") << " child";
    EXPECT_EQ(before, captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating));
  }
}

TEST_F(EPModelFixture, PlantLoop_FourPipeFanCoilDemandMoveRejectsMalformedFanRolesAirPathAndDuplicateZoneOrRoleWithoutMutation) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater cooling(model);
  CoilHeatingWater heating(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PlantLoop coolingLoop(model);
  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(cooling));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heating));
  ASSERT_TRUE(fanCoil.addToThermalZone(zone));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heating));
  ASSERT_TRUE(coolingLoop.addDemandBranchForComponent(cooling));

  const auto expectRejectedUnchanged = [&]() {
    const auto before = captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heating));
    EXPECT_EQ(before, captureFourPipeFanCoilMoveTopology(model, sourceLoop, targetLoop, zone, fanCoil, fan, cooling, heating));
  };

  // Seed an impossible unsupported fan role while retaining the otherwise
  // canonical fan-to-cooling adjacency.
  ASSERT_TRUE(fan.inletModelObject());
  ASSERT_TRUE(fan.outletModelObject());
  PipeAdiabatic unsupportedFan(model);
  ASSERT_TRUE(unsupportedFan.setPointer(unsupportedFan.inletPort(), fan.inletModelObject()->handle()));
  ASSERT_TRUE(unsupportedFan.setPointer(unsupportedFan.outletPort(), fan.outletModelObject()->handle()));
  auto fanCoilWorkspaceImpl = fanCoil.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(fanCoilWorkspaceImpl);
  ASSERT_TRUE(fanCoilWorkspaceImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, unsupportedFan.handle(), false));
  ASSERT_TRUE(fanCoilWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType,
                                                                                  unsupportedFan.iddObject().name(), false));
  expectRejectedUnchanged();
  ASSERT_TRUE(fanCoil.setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, fan.handle()));
  ASSERT_TRUE(fanCoil.setString(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, fan.iddObject().name()));

  ASSERT_TRUE(fanCoilWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType,
                                                                                  cooling.iddObject().name(), false));
  expectRejectedUnchanged();
  ASSERT_TRUE(fanCoilWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType,
                                                                                  heating.iddObject().name(), false));

  ASSERT_TRUE(cooling.airInletModelObject());
  const auto coolingAirInlet = cooling.airInletModelObject()->cast<Node>();
  Node brokenAirPathNode(model);
  ASSERT_TRUE(cooling.setPointer(cooling.airInletPort(), brokenAirPathNode.handle()));
  expectRejectedUnchanged();
  ASSERT_TRUE(cooling.setPointer(cooling.airInletPort(), coolingAirInlet.handle()));

  // Collapse one internal boundary while retaining exact component-to-
  // component adjacency.
  ASSERT_TRUE(fanCoil.inletNode());
  ASSERT_TRUE(fan.outletModelObject());
  const auto fanCoilInlet = *fanCoil.inletNode();
  const auto fanOutlet = fan.outletModelObject()->cast<Node>();
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), fanCoilInlet.handle()));
  ASSERT_TRUE(cooling.setPointer(cooling.airInletPort(), fanCoilInlet.handle()));
  expectRejectedUnchanged();
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), fanOutlet.handle()));
  ASSERT_TRUE(cooling.setPointer(cooling.airInletPort(), fanOutlet.handle()));

  // An inlet-side mixer source is rejected even without an AirLoop owner.
  AirTerminalSingleDuctInletSideMixer detachedMixer(model);
  auto detachedMixerWorkspaceImpl = detachedMixer.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(detachedMixerWorkspaceImpl);
  ASSERT_TRUE(detachedMixerWorkspaceImpl->setPointer(detachedMixer.outletPort(), fanCoilInlet.handle(), false));
  EXPECT_FALSE(fanCoil.airLoopHVAC());
  EXPECT_FALSE(detachedMixer.airLoopHVAC());
  expectRejectedUnchanged();
  ASSERT_TRUE(detachedMixerWorkspaceImpl->setPointer(detachedMixer.outletPort(), openstudio::Handle(), false));

  // Seed an impossible OA equipment-list owner without changing the fan's
  // canonical FourPipe nodes.
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto oaEquipmentList = oaSystem.getModelObjectTarget<AirLoopHVACOutdoorAirSystemEquipmentList>(
    openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
  ASSERT_TRUE(oaEquipmentList);
  auto oaEquipmentListImpl = oaEquipmentList->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
  ASSERT_TRUE(oaEquipmentListImpl);
  const auto oaMixers = subsetCastVector<OutdoorAirMixer>(oaEquipmentList->equipment());
  ASSERT_EQ(1u, oaMixers.size());
  auto oaMixer = oaMixers.front();
  const auto originalOAMixerOutdoorNode = oaMixer.getModelObjectTarget<Node>(openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName);
  ASSERT_TRUE(originalOAMixerOutdoorNode);
  ASSERT_TRUE(oaEquipmentListImpl->addEquipment(fan));
  ASSERT_TRUE(oaMixer.setPointer(openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName, fanOutlet.handle()));
  ASSERT_TRUE(fan.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(oaSystem.handle(), fan.airLoopHVACOutdoorAirSystem()->handle());
  expectRejectedUnchanged();
  ASSERT_TRUE(oaEquipmentListImpl->removeEquipment(fan));
  ASSERT_TRUE(oaMixer.setPointer(openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName, originalOAMixerOutdoorNode->handle()));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto equipmentList = connections->zoneHVACEquipmentList();
  const auto originalEquipmentRows = equipmentList.extensibleGroups().size();
  auto duplicateEquipmentRow = equipmentList.pushExtensibleGroup();
  ASSERT_FALSE(duplicateEquipmentRow.empty());
  ASSERT_TRUE(
    duplicateEquipmentRow.setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType, fanCoil.iddObject().name(), false));
  ASSERT_TRUE(duplicateEquipmentRow.setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, fanCoil.nameString(), false));
  ASSERT_TRUE(duplicateEquipmentRow.setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, 2u));
  ASSERT_TRUE(duplicateEquipmentRow.setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, 2u));
  expectRejectedUnchanged();
  EXPECT_EQ(originalEquipmentRows + 1u, equipmentList.extensibleGroups().size());
  EXPECT_FALSE(equipmentList.popExtensibleGroup().empty());

  // Other zones' raw direct-node and raw NodeList aliases are rejected even
  // though they belong to different equipment lists and are unresolved by the
  // canonical collection accessor.
  ThermalZone aliasZone(model);
  auto aliasConnections = aliasZone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  auto aliasConnectionsWorkspaceImpl = aliasConnections.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl);
  constexpr unsigned exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
  constexpr unsigned inletField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName;
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl->setPointer(exhaustField, openstudio::Handle(), false));
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(exhaustField, fanCoilInlet.nameString(), false));
  const auto rawDirectAliasBefore = aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(exhaustField, false, true);
  expectRejectedUnchanged();
  EXPECT_TRUE(rawDirectAliasBefore == aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(exhaustField, false, true));
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(exhaustField, "", false));

  ASSERT_TRUE(fanCoil.outletNode());
  NodeList rawAliasNodeList(model);
  auto rawAliasNodeRow = rawAliasNodeList.pushExtensibleGroup();
  ASSERT_FALSE(rawAliasNodeRow.empty());
  ASSERT_TRUE(rawAliasNodeRow.setString(openstudio::NodeListExtensibleFields::NodeName, fanCoil.outletNode()->nameString(), false));
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl->setPointer(inletField, openstudio::Handle(), false));
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(inletField, rawAliasNodeList.nameString(), false));
  const auto rawNodeListAliasBefore = aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  expectRejectedUnchanged();
  EXPECT_TRUE(rawNodeListAliasBefore == aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true));
  ASSERT_TRUE(aliasConnectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(inletField, "", false));

  ZoneHVACFourPipeFanCoil managedAliasParent(model);
  auto managedAliasWorkspaceImpl = managedAliasParent.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(managedAliasWorkspaceImpl);
  ASSERT_TRUE(managedAliasWorkspaceImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, heating.handle(), false));
  ASSERT_TRUE(managedAliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(
    openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, heating.iddObject().name(), false));
  expectRejectedUnchanged();
  ASSERT_TRUE(managedAliasWorkspaceImpl->setPointer(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, openstudio::Handle(), false));
  ASSERT_TRUE(managedAliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(
    openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, "", false));

  struct RawRoleAliasCase
  {
    ModelObject child;
    unsigned nameField;
    unsigned typeField;
  };
  const std::array rawRoleAliasCases = {RawRoleAliasCase{fan.cast<ModelObject>(), openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName,
                                                         openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType},
                                        RawRoleAliasCase{cooling.cast<ModelObject>(), openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName,
                                                         openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType},
                                        RawRoleAliasCase{heating.cast<ModelObject>(), openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName,
                                                         openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType}};
  for (const auto& aliasCase : rawRoleAliasCases) {
    ZoneHVACFourPipeFanCoil rawAliasParent(model);
    auto aliasWorkspaceImpl = rawAliasParent.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    ASSERT_TRUE(aliasWorkspaceImpl);
    ASSERT_TRUE(aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(aliasCase.typeField, aliasCase.child.iddObject().name(), false));
    ASSERT_TRUE(aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(aliasCase.nameField, aliasCase.child.nameString(), false));
    const auto rawAliasTypeBefore = aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(aliasCase.typeField, false, true);
    const auto rawAliasNameBefore = aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(aliasCase.nameField, false, true);
    expectRejectedUnchanged();
    EXPECT_TRUE(rawAliasTypeBefore == aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(aliasCase.typeField, false, true));
    EXPECT_TRUE(rawAliasNameBefore == aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(aliasCase.nameField, false, true));
    ASSERT_TRUE(aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(aliasCase.nameField, "", false));
    ASSERT_TRUE(aliasWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(aliasCase.typeField, "", false));
  }
}

TEST_F(EPModelFixture, PlantLoop_ThermalStorageSourceDemandMoveDefaultToOccupiedIsTransactionalAcrossReload) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-thermal-storage-source-move-" + openstudio::toString(openstudio::createUUID()) + ".idf");
  ScopedFileRemoval cleanup(idfPath);

  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  ThermalStorageChilledWaterStratified storage(model);
  PipeAdiabatic targetPipe(model);
  ScheduleConstant setpointSchedule(model);
  ScheduleConstant ambientSchedule(model);
  ScheduleConstant useSchedule(model);
  ScheduleConstant sourceSchedule(model);
  ThermalZone ambientZone(model);
  ASSERT_TRUE(primaryLoop.setName("Thermal Storage UseSide Loop"));
  ASSERT_TRUE(sourceLoop.setName("Thermal Storage Original SourceSide Loop"));
  ASSERT_TRUE(targetLoop.setName("Thermal Storage Moved SourceSide Loop"));
  ASSERT_TRUE(storage.setName("Moved Stratified Chilled Water Storage"));
  ASSERT_TRUE(targetPipe.setName("Retained Thermal Storage Target Pipe"));
  ASSERT_TRUE(setpointSchedule.setName("Thermal Storage Setpoint Schedule"));
  ASSERT_TRUE(ambientSchedule.setName("Thermal Storage Ambient Schedule"));
  ASSERT_TRUE(useSchedule.setName("Thermal Storage Use Schedule"));
  ASSERT_TRUE(sourceSchedule.setName("Thermal Storage Source Schedule"));
  ASSERT_TRUE(ambientZone.setName("Thermal Storage Ambient Zone"));
  ASSERT_TRUE(setpointSchedule.setValue(6.5));
  ASSERT_TRUE(ambientSchedule.setValue(22.0));
  ASSERT_TRUE(useSchedule.setValue(0.8));
  ASSERT_TRUE(sourceSchedule.setValue(0.6));
  ASSERT_TRUE(storage.setSetpointTemperatureSchedule(setpointSchedule));
  ASSERT_TRUE(storage.setAmbientTemperatureSchedule(ambientSchedule));
  ASSERT_TRUE(storage.setUseSideAvailabilitySchedule(useSchedule));
  ASSERT_TRUE(storage.setSourceSideAvailabilitySchedule(sourceSchedule));
  ASSERT_TRUE(storage.setAmbientTemperatureThermalZone(ambientZone));
  ASSERT_TRUE(storage.setAmbientTemperatureOutdoorAirNodeName("Preserved Storage Ambient OA Node"));
  ASSERT_TRUE(storage.setTankVolume(73.25));
  ASSERT_TRUE(storage.setSourceSideHeatTransferEffectiveness(0.87));
  auto sizing = storage.waterHeaterSizing();
  ASSERT_TRUE(sizing.setTimeStorageCanMeetPeakDraw(1.75));
  ASSERT_TRUE(sizing.setTimeforTankRecovery(3.25));
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(storage));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetPipe));
  auto primarySetpoint = primaryLoop.supplyInletNode();
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(primaryLoop.setLoopTemperatureSetpointNode(primarySetpoint));
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  ASSERT_TRUE(storage.supplyInletModelObject());
  ASSERT_TRUE(storage.supplyOutletModelObject());
  ASSERT_TRUE(storage.demandInletModelObject());
  ASSERT_TRUE(storage.demandOutletModelObject());
  const auto primaryInletHandle = storage.supplyInletModelObject()->handle();
  const auto primaryOutletHandle = storage.supplyOutletModelObject()->handle();
  const auto oldSourceInletHandle = storage.demandInletModelObject()->handle();
  const auto oldSourceOutletHandle = storage.demandOutletModelObject()->handle();
  const auto sizingHandle = sizing.handle();

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchList->branches());
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(3u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto sourceDefaultBranch = sourceBranchHandlesBefore[1];

  const auto before = captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterThermalStorageSourceBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(storage));
  }
  EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(storage.plantLoop());
  ASSERT_TRUE(storage.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *storage.plantLoop());
  EXPECT_EQ(targetLoop, *storage.secondaryPlantLoop());
  EXPECT_FALSE(sourceLoop.demandComponent(storage.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(storage.handle()));
  ASSERT_TRUE(storage.supplyInletModelObject());
  ASSERT_TRUE(storage.supplyOutletModelObject());
  ASSERT_TRUE(storage.demandInletModelObject());
  ASSERT_TRUE(storage.demandOutletModelObject());
  EXPECT_EQ(primaryInletHandle, storage.supplyInletModelObject()->handle());
  EXPECT_EQ(primaryOutletHandle, storage.supplyOutletModelObject()->handle());
  EXPECT_NE(oldSourceInletHandle, storage.demandInletModelObject()->handle());
  EXPECT_NE(oldSourceOutletHandle, storage.demandOutletModelObject()->handle());
  EXPECT_TRUE(model.getObject(oldSourceInletHandle));
  EXPECT_TRUE(model.getObject(oldSourceOutletHandle));
  EXPECT_EQ(sizingHandle, storage.waterHeaterSizing().handle());
  EXPECT_DOUBLE_EQ(1.75, *storage.waterHeaterSizing().timeStorageCanMeetPeakDraw());
  EXPECT_DOUBLE_EQ(3.25, *storage.waterHeaterSizing().timeforTankRecovery());
  ASSERT_TRUE(storage.setpointTemperatureSchedule());
  ASSERT_TRUE(storage.ambientTemperatureSchedule());
  ASSERT_TRUE(storage.useSideAvailabilitySchedule());
  ASSERT_TRUE(storage.sourceSideAvailabilitySchedule());
  ASSERT_TRUE(storage.ambientTemperatureThermalZone());
  ASSERT_TRUE(storage.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ(setpointSchedule, *storage.setpointTemperatureSchedule());
  EXPECT_EQ(ambientSchedule, *storage.ambientTemperatureSchedule());
  EXPECT_EQ(useSchedule, *storage.useSideAvailabilitySchedule());
  EXPECT_EQ(sourceSchedule, *storage.sourceSideAvailabilitySchedule());
  EXPECT_EQ(ambientZone, *storage.ambientTemperatureThermalZone());
  EXPECT_EQ("Preserved Storage Ambient OA Node", *storage.ambientTemperatureOutdoorAirNodeName());
  EXPECT_DOUBLE_EQ(73.25, storage.tankVolume());
  EXPECT_DOUBLE_EQ(0.87, storage.sourceSideHeatTransferEffectiveness());
  for (unsigned field = 0u; field < storage.numFields(); ++field) {
    if (field == storage.demandInletPort() || field == storage.demandOutletPort()) {
      continue;
    }
    ASSERT_LT(field, before.storageRawFields.size());
    EXPECT_TRUE(before.storageRawFields[field] == rawField(storage, field));
  }
  EXPECT_TRUE(before.sizingRawFields == captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage).sizingRawFields);
  EXPECT_EQ(primarySetpoint.handle(), primaryLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(sourceBranchHandlesBefore, objectHandles(sourceBranchList->branches()));
  EXPECT_EQ(sourceDefaultBranch, sourceBranchList->branches()[1].handle());
  EXPECT_TRUE(sourceBranchList->branches()[1].components().empty());
  expectDemandBranchAndConnectorOrder(sourceLoop, sourceBranchHandlesBefore);
  const auto targetBranchHandlesAfter = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, targetBranchHandlesAfter.size());
  EXPECT_EQ(targetBranchHandlesBefore[0], targetBranchHandlesAfter[0]);
  EXPECT_EQ(targetBranchHandlesBefore[1], targetBranchHandlesAfter[1]);
  EXPECT_EQ(targetBranchHandlesBefore[2], targetBranchHandlesAfter[3]);
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesAfter);

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  const auto report = loadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  auto loadedPrimary = loadedModel->getConcreteModelObjectByName<PlantLoop>("Thermal Storage UseSide Loop");
  auto loadedSource = loadedModel->getConcreteModelObjectByName<PlantLoop>("Thermal Storage Original SourceSide Loop");
  auto loadedTarget = loadedModel->getConcreteModelObjectByName<PlantLoop>("Thermal Storage Moved SourceSide Loop");
  auto loadedStorage = loadedModel->getConcreteModelObjectByName<ThermalStorageChilledWaterStratified>("Moved Stratified Chilled Water Storage");
  auto loadedTargetPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Retained Thermal Storage Target Pipe");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Thermal Storage Ambient Zone");
  ASSERT_TRUE(loadedPrimary);
  ASSERT_TRUE(loadedSource);
  ASSERT_TRUE(loadedTarget);
  ASSERT_TRUE(loadedStorage);
  ASSERT_TRUE(loadedTargetPipe);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedStorage->plantLoop());
  ASSERT_TRUE(loadedStorage->secondaryPlantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedStorage->plantLoop());
  EXPECT_EQ(*loadedTarget, *loadedStorage->secondaryPlantLoop());
  EXPECT_FALSE(loadedSource->demandComponent(loadedStorage->handle()));
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<WaterHeaterSizing>().size());
  EXPECT_EQ(loadedStorage->handle(), loadedStorage->waterHeaterSizing().waterHeater().handle());
  EXPECT_DOUBLE_EQ(1.75, *loadedStorage->waterHeaterSizing().timeStorageCanMeetPeakDraw());
  EXPECT_DOUBLE_EQ(3.25, *loadedStorage->waterHeaterSizing().timeforTankRecovery());
  ASSERT_TRUE(loadedStorage->ambientTemperatureThermalZone());
  ASSERT_TRUE(loadedStorage->ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ(*loadedZone, *loadedStorage->ambientTemperatureThermalZone());
  EXPECT_EQ("Preserved Storage Ambient OA Node", *loadedStorage->ambientTemperatureOutdoorAirNodeName());
  EXPECT_DOUBLE_EQ(73.25, loadedStorage->tankVolume());
  EXPECT_DOUBLE_EQ(0.87, loadedStorage->sourceSideHeatTransferEffectiveness());

  const auto loadedStorageHandle = loadedStorage->handle();
  const auto loadedSizingHandle = loadedStorage->waterHeaterSizing().handle();
  const auto loadedPrimaryComponents = objectHandles(loadedPrimary->supplyComponents());
  ASSERT_TRUE(loadedStorage->supplyInletModelObject());
  ASSERT_TRUE(loadedStorage->supplyOutletModelObject());
  const auto loadedPrimaryInletHandle = loadedStorage->supplyInletModelObject()->handle();
  const auto loadedPrimaryOutletHandle = loadedStorage->supplyOutletModelObject()->handle();
  std::set<openstudio::Handle> removedTargetHandles{loadedTarget->handle(), loadedTarget->sizingPlant().handle(), loadedTargetPipe->handle()};
  const auto addTargetOwner = [&removedTargetHandles, &loadedStorage](const ModelObject& object) {
    if (object.handle() != loadedStorage->handle()) {
      removedTargetHandles.insert(object.handle());
    }
  };
  const auto loadedSupplyBranchList = loadedTarget->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  const auto loadedDemandBranchList = loadedTarget->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  const auto loadedSupplyConnectorList = loadedTarget->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName);
  const auto loadedDemandConnectorList = loadedTarget->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
  const auto loadedAssignmentList =
    loadedTarget->getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
  const auto loadedOperationSchemes =
    loadedTarget->getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(loadedSupplyBranchList);
  ASSERT_TRUE(loadedDemandBranchList);
  ASSERT_TRUE(loadedSupplyConnectorList);
  ASSERT_TRUE(loadedDemandConnectorList);
  ASSERT_TRUE(loadedAssignmentList);
  ASSERT_TRUE(loadedOperationSchemes);
  addTargetOwner(*loadedSupplyBranchList);
  addTargetOwner(*loadedDemandBranchList);
  addTargetOwner(*loadedSupplyConnectorList);
  addTargetOwner(*loadedDemandConnectorList);
  addTargetOwner(*loadedAssignmentList);
  addTargetOwner(*loadedOperationSchemes);
  for (const auto& branches : {loadedSupplyBranchList->branches(), loadedDemandBranchList->branches()}) {
    for (const auto& branch : branches) {
      addTargetOwner(branch);
      for (unsigned row = 0u; row < branch.extensibleGroups().size(); ++row) {
        if (auto inlet = branch.componentInletNode(row)) {
          addTargetOwner(*inlet);
        }
        if (auto outlet = branch.componentOutletNode(row)) {
          addTargetOwner(*outlet);
        }
      }
    }
  }
  addTargetOwner(loadedTarget->supplySplitter());
  addTargetOwner(loadedTarget->supplyMixer());
  addTargetOwner(loadedTarget->demandSplitter());
  addTargetOwner(loadedTarget->demandMixer());
  addTargetOwner(loadedTarget->supplyInletNode());
  addTargetOwner(loadedTarget->supplyOutletNode());
  addTargetOwner(loadedTarget->demandInletNode());
  addTargetOwner(loadedTarget->demandOutletNode());

  EXPECT_FALSE(loadedTarget->remove().empty());
  for (const auto& handle : removedTargetHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(loadedPrimary->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedSource->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedStorageHandle));
  EXPECT_TRUE(loadedModel->getObject(loadedSizingHandle));
  EXPECT_EQ(loadedPrimaryComponents, objectHandles(loadedPrimary->supplyComponents()));
  ASSERT_TRUE(loadedStorage->plantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedStorage->plantLoop());
  EXPECT_FALSE(loadedStorage->secondaryPlantLoop());
  EXPECT_FALSE(loadedStorage->demandInletModelObject());
  EXPECT_FALSE(loadedStorage->demandOutletModelObject());
  ASSERT_TRUE(loadedStorage->supplyInletModelObject());
  ASSERT_TRUE(loadedStorage->supplyOutletModelObject());
  EXPECT_EQ(loadedPrimaryInletHandle, loadedStorage->supplyInletModelObject()->handle());
  EXPECT_EQ(loadedPrimaryOutletHandle, loadedStorage->supplyOutletModelObject()->handle());
  EXPECT_EQ(loadedSizingHandle, loadedStorage->waterHeaterSizing().handle());
}

TEST_F(EPModelFixture, PlantLoop_ThermalStorageSourceDemandMoveParallelToDefaultIsTransactionalAndDirectRemovalReattaches) {
  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  ThermalStorageChilledWaterStratified storage(model);
  PipeAdiabatic retainedSourcePipe(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(storage));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(retainedSourcePipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(storage.demandInletModelObject());
  ASSERT_TRUE(storage.demandOutletModelObject());
  auto primarySetpoint = primaryLoop.supplyInletNode();
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(primaryLoop.setLoopTemperatureSetpointNode(primarySetpoint));
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  const auto sizingHandle = storage.waterHeaterSizing().handle();
  const auto oldSourceInletHandle = storage.demandInletModelObject()->handle();
  const auto oldSourceOutletHandle = storage.demandOutletModelObject()->handle();
  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchesBefore = sourceBranchList->branches();
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchesBefore);
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto removedBranch = std::ranges::find_if(sourceBranchesBefore, [&storage](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, storage.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceBranchesBefore.end(), removedBranch);
  const auto removedBranchHandle = removedBranch->handle();
  auto expectedSourceBranches = sourceBranchHandlesBefore;
  expectedSourceBranches.erase(std::ranges::find(expectedSourceBranches, removedBranchHandle));
  const auto targetDefaultBranch = targetBranchHandlesBefore[1];

  const auto before = captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterThermalStorageSourceBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(storage));
  }
  EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(storage));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(oldSourceInletHandle));
  EXPECT_TRUE(model.getObject(oldSourceOutletHandle));
  EXPECT_EQ(sizingHandle, storage.waterHeaterSizing().handle());
  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(expectedSourceBranches, objectHandles(sourceBranchList->branches()));
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  EXPECT_EQ(targetDefaultBranch, targetBranchList->branches()[1].handle());
  expectDemandBranchAndConnectorOrder(sourceLoop, expectedSourceBranches);
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);
  EXPECT_EQ(primarySetpoint.handle(), primaryLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  ASSERT_TRUE(targetLoop.removeDemandBranchWithComponent(storage));
  EXPECT_TRUE(storage.plantLoop());
  EXPECT_FALSE(storage.secondaryPlantLoop());
  EXPECT_FALSE(storage.demandInletModelObject());
  EXPECT_FALSE(storage.demandOutletModelObject());
  EXPECT_EQ(sizingHandle, storage.waterHeaterSizing().handle());
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  EXPECT_TRUE(targetBranchList->branches()[1].components().empty());

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(storage.secondaryPlantLoop());
  EXPECT_EQ(targetLoop, *storage.secondaryPlantLoop());
  EXPECT_EQ(sizingHandle, storage.waterHeaterSizing().handle());
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  EXPECT_EQ(targetDefaultBranch, targetBranchList->branches()[1].handle());
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);
}

TEST_F(EPModelFixture, PlantLoop_ThermalStorageOwnerRemovalRetainsSizingUntilFinalOwnerInEitherOrder) {
  const auto runRemovalOrder = [](bool primaryFirst) {
    SCOPED_TRACE(primaryFirst ? "primary-first" : "source-first");
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    ThermalStorageChilledWaterStratified storage(model);
    ScheduleConstant preservedSchedule(model);
    ThermalZone preservedZone(model);
    ASSERT_TRUE(preservedSchedule.setValue(19.0));
    ASSERT_TRUE(storage.setAmbientTemperatureSchedule(preservedSchedule));
    ASSERT_TRUE(storage.setAmbientTemperatureThermalZone(preservedZone));
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(storage));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(storage));
    PipeAdiabatic finalOwnerPipe(model);
    ASSERT_TRUE(primaryFirst ? sourceLoop.addDemandBranchForComponent(finalOwnerPipe) : primaryLoop.addSupplyBranchForComponent(finalOwnerPipe));

    const auto storageHandle = storage.handle();
    const auto sizingHandle = storage.waterHeaterSizing().handle();
    const auto scheduleHandle = preservedSchedule.handle();
    const auto zoneHandle = preservedZone.handle();
    const auto primaryHandle = primaryLoop.handle();
    const auto sourceHandle = sourceLoop.handle();
    const auto finalOwnerPipeHandle = finalOwnerPipe.handle();
    auto& firstLoop = primaryFirst ? primaryLoop : sourceLoop;
    auto& secondLoop = primaryFirst ? sourceLoop : primaryLoop;
    EXPECT_FALSE(firstLoop.remove().empty());
    EXPECT_FALSE(model.getObject(primaryFirst ? primaryHandle : sourceHandle));
    EXPECT_TRUE(model.getObject(storageHandle));
    EXPECT_TRUE(model.getObject(sizingHandle));
    EXPECT_EQ(sizingHandle, storage.waterHeaterSizing().handle());
    EXPECT_EQ(storageHandle, storage.waterHeaterSizing().waterHeater().handle());
    EXPECT_EQ(primaryFirst, !storage.plantLoop());
    EXPECT_EQ(!primaryFirst, !storage.secondaryPlantLoop());
    EXPECT_TRUE(model.getObject(scheduleHandle));
    EXPECT_TRUE(model.getObject(zoneHandle));
    EXPECT_TRUE(model.getObject(finalOwnerPipeHandle));

    EXPECT_FALSE(secondLoop.remove().empty());
    EXPECT_FALSE(model.getObject(primaryFirst ? sourceHandle : primaryHandle));
    EXPECT_FALSE(model.getObject(storageHandle));
    EXPECT_FALSE(model.getObject(sizingHandle));
    EXPECT_FALSE(model.getObject(finalOwnerPipeHandle));
    EXPECT_TRUE(model.getObject(scheduleHandle));
    EXPECT_TRUE(model.getObject(zoneHandle));
  };

  runRemovalOrder(false);
  runRemovalOrder(true);
}

TEST_F(EPModelFixture, PlantLoop_ThermalStorageInitialDemandAttachmentAndOwnerRejectionsRemainExact) {
  Model model;
  PlantLoop unattachedTarget(model);
  ThermalStorageChilledWaterStratified unattachedStorage(model);
  EXPECT_TRUE(unattachedTarget.addDemandBranchForComponent(unattachedStorage));
  EXPECT_FALSE(unattachedStorage.plantLoop());
  ASSERT_TRUE(unattachedStorage.secondaryPlantLoop());
  EXPECT_EQ(unattachedTarget, *unattachedStorage.secondaryPlantLoop());

  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  ThermalStorageChilledWaterStratified storage(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(storage));
  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(storage.plantLoop());
  ASSERT_TRUE(storage.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *storage.plantLoop());
  EXPECT_EQ(sourceLoop, *storage.secondaryPlantLoop());

  const auto before = captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage);
  EXPECT_FALSE(primaryLoop.addDemandBranchForComponent(storage));
  EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage));
  EXPECT_FALSE(sourceLoop.addDemandBranchForComponent(storage));
  EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage));
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(storage, true));
  EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage));

  Model foreignModel;
  PlantLoop foreignTarget(foreignModel);
  EXPECT_FALSE(foreignTarget.addDemandBranchForComponent(storage));
  EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage));
}

TEST_F(EPModelFixture, PlantLoop_ThermalStorageMoveAndOwnerRemovalRejectMalformedSizingEvidenceWithoutMutation) {
  enum class SizingCase
  {
    Missing,
    Duplicate,
    RawOnlyAlias,
    WrongTarget,
    AmbiguousMixedStorageName,
    AmbiguousWaterHeaterName,
  };

  for (const auto sizingCase : {SizingCase::Missing, SizingCase::Duplicate, SizingCase::RawOnlyAlias, SizingCase::WrongTarget,
                                SizingCase::AmbiguousMixedStorageName, SizingCase::AmbiguousWaterHeaterName}) {
    SCOPED_TRACE(static_cast<int>(sizingCase));
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    ThermalStorageChilledWaterStratified storage(model);
    ASSERT_TRUE(storage.setName("Sizing Evidence Storage"));
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(storage));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(storage));

    if (sizingCase == SizingCase::Missing) {
      storage.waterHeaterSizing().remove();
    } else if (sizingCase == SizingCase::Duplicate) {
      WaterHeaterSizing duplicate(storage);
      ASSERT_EQ(storage.handle(), duplicate.waterHeater().handle());
    } else if (sizingCase == SizingCase::RawOnlyAlias) {
      WaterHeaterSizing rawAlias(model);
      auto rawAliasImpl = rawAlias.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(rawAliasImpl);
      ASSERT_TRUE(rawAliasImpl->setPointer(openstudio::WaterHeater_SizingFields::WaterHeaterName, openstudio::Handle(), false));
      ASSERT_TRUE(rawAliasImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::WaterHeater_SizingFields::WaterHeaterName,
                                                                              storage.nameString(), false));
    } else if (sizingCase == SizingCase::WrongTarget) {
      HeatExchangerFluidToFluid wrongTarget(model);
      ASSERT_TRUE(wrongTarget.setName("Wrong Sizing Target"));
      auto sizingImpl = storage.waterHeaterSizing().getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(sizingImpl);
      ASSERT_TRUE(sizingImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::WaterHeater_SizingFields::WaterHeaterName,
                                                                            wrongTarget.nameString(), false));
    } else if (sizingCase == SizingCase::AmbiguousMixedStorageName) {
      ThermalStorageChilledWaterMixed ambiguousStorageName(model);
      auto ambiguousImpl = ambiguousStorageName.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(ambiguousImpl);
      ASSERT_TRUE(ambiguousImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::ThermalStorage_ChilledWater_MixedFields::Name,
                                                                               storage.nameString(), false));
    } else {
      WaterHeaterMixed ambiguousWaterHeaterName(model);
      auto ambiguousImpl = ambiguousWaterHeaterName.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(ambiguousImpl);
      ASSERT_TRUE(
        ambiguousImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::WaterHeater_MixedFields::Name, storage.nameString(), false));
    }

    const auto before = captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage, false);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(storage));
    EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage, false));
    std::vector<openstudio::IdfObject> removed;
    EXPECT_NO_THROW(removed = primaryLoop.remove());
    EXPECT_TRUE(removed.empty());
    EXPECT_TRUE(model.getObject(primaryLoop.handle()));
    EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage, false));
  }
}

TEST_F(EPModelFixture, PlantLoop_ThermalStorageMoveRejectsMalformedPortsRowsScaffoldsAndNodeCollisionsWithoutMutation) {
  enum class MalformedCase
  {
    PartialPort,
    SerialPrimary,
    SerialSource,
    RawDuplicateRow,
    TargetScaffoldAlias,
    TargetNodeCollision,
  };

  for (const auto malformedCase : {MalformedCase::PartialPort, MalformedCase::SerialPrimary, MalformedCase::SerialSource,
                                   MalformedCase::RawDuplicateRow, MalformedCase::TargetScaffoldAlias, MalformedCase::TargetNodeCollision}) {
    SCOPED_TRACE(static_cast<int>(malformedCase));
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    ThermalStorageChilledWaterStratified storage(model);
    ASSERT_TRUE(targetLoop.setName("Storage Malformed Target"));
    ASSERT_TRUE(storage.setName("Storage Malformed Component"));
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(storage));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(storage));

    if (malformedCase == MalformedCase::PartialPort) {
      auto storageImpl = storage.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(storageImpl);
      ASSERT_TRUE(storageImpl->setPointer(storage.demandOutletPort(), openstudio::Handle(), false));
    } else if (malformedCase == MalformedCase::SerialPrimary) {
      PipeAdiabatic serialPipe(model);
      ASSERT_TRUE(storage.supplyOutletModelObject());
      auto insertionNode = storage.supplyOutletModelObject()->cast<Node>();
      ASSERT_TRUE(serialPipe.addToNode(insertionNode));
    } else if (malformedCase == MalformedCase::SerialSource) {
      PipeAdiabatic serialPipe(model);
      ASSERT_TRUE(storage.demandOutletModelObject());
      auto insertionNode = storage.demandOutletModelObject()->cast<Node>();
      ASSERT_TRUE(serialPipe.addToNode(insertionNode));
    } else if (malformedCase == MalformedCase::RawDuplicateRow) {
      Branch rawAliasBranch(model);
      auto rawAliasRow = rawAliasBranch.pushExtensibleGroup();
      ASSERT_FALSE(rawAliasRow.empty());
      ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentObjectType, storage.iddObject().name(), false));
      ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentName, storage.nameString(), false));
      ASSERT_TRUE(
        rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentInletNodeName, storage.demandInletModelObject()->nameString(), false));
      ASSERT_TRUE(
        rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentOutletNodeName, storage.demandOutletModelObject()->nameString(), false));
    } else if (malformedCase == MalformedCase::TargetScaffoldAlias) {
      PlantLoop aliasLoop(model);
      auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
      ASSERT_TRUE(targetBranchList);
      auto aliasLoopImpl = aliasLoop.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(aliasLoopImpl);
      ASSERT_TRUE(aliasLoopImpl->setPointer(openstudio::PlantLoopFields::PlantSideBranchListName, targetBranchList->handle(), false));
    } else {
      auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
      ASSERT_TRUE(targetBranchList);
      ASSERT_EQ(3u, targetBranchList->branches().size());
      Node collision(model);
      ASSERT_TRUE(collision.setName(targetBranchList->branches()[1].nameString() + " Node - " + storage.nameString() + " Outlet"));
    }

    const bool canObserveOwners = malformedCase != MalformedCase::PartialPort;
    const auto before = captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage, canObserveOwners);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(storage));
    EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage, canObserveOwners));
    if (malformedCase == MalformedCase::PartialPort || malformedCase == MalformedCase::SerialPrimary || malformedCase == MalformedCase::SerialSource
        || malformedCase == MalformedCase::RawDuplicateRow) {
      auto& malformedOwner = malformedCase == MalformedCase::SerialPrimary ? primaryLoop : sourceLoop;
      std::vector<openstudio::IdfObject> removed;
      EXPECT_NO_THROW(removed = malformedOwner.remove());
      EXPECT_TRUE(removed.empty());
      EXPECT_TRUE(model.getObject(malformedOwner.handle()));
      EXPECT_EQ(before, captureThermalStorageMove(model, primaryLoop, sourceLoop, targetLoop, storage, canObserveOwners));
    }
  }
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerDemandMoveDefaultSourceToOccupiedTargetIsTransactionalAcrossReload) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-fluid-to-fluid-demand-move-" + openstudio::toString(openstudio::createUUID()) + ".idf");
  ScopedFileRemoval cleanup(idfPath);

  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  PipeAdiabatic targetPipe(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(primaryLoop.setName("Fluid HX Primary Loop"));
  ASSERT_TRUE(sourceLoop.setName("Fluid HX Original Secondary Loop"));
  ASSERT_TRUE(targetLoop.setName("Fluid HX Moved Secondary Loop"));
  ASSERT_TRUE(heatExchanger.setName("Moved Fluid To Fluid Heat Exchanger"));
  ASSERT_TRUE(targetPipe.setName("Retained Fluid HX Target Pipe"));
  ASSERT_TRUE(availability.setName("Fluid HX Availability"));
  ASSERT_TRUE(availability.setValue(0.75));
  ASSERT_TRUE(heatExchanger.setAvailabilitySchedule(availability));
  ASSERT_TRUE(heatExchanger.setHeatExchangerUFactorTimesAreaValue(417.25));
  ASSERT_TRUE(heatExchanger.setSizingFactor(1.17));
  ASSERT_TRUE(heatExchanger.setControlType("CoolingSetpointModulated"));
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetPipe));
  auto primarySetpoint = primaryLoop.supplyInletNode();
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(primaryLoop.setLoopTemperatureSetpointNode(primarySetpoint));
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  ASSERT_TRUE(heatExchanger.supplyInletModelObject());
  ASSERT_TRUE(heatExchanger.supplyOutletModelObject());
  ASSERT_TRUE(heatExchanger.demandInletModelObject());
  ASSERT_TRUE(heatExchanger.demandOutletModelObject());
  const auto primaryInlet = heatExchanger.supplyInletModelObject()->cast<Node>();
  const auto primaryOutlet = heatExchanger.supplyOutletModelObject()->cast<Node>();
  const auto oldDemandInlet = heatExchanger.demandInletModelObject()->cast<Node>();
  const auto oldDemandOutlet = heatExchanger.demandOutletModelObject()->cast<Node>();
  ASSERT_TRUE(heatExchanger.setComponentOverrideLoopSupplySideInletNode(primaryInlet));
  ASSERT_TRUE(heatExchanger.setComponentOverrideLoopDemandSideInletNode(oldDemandInlet));

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchList->branches());
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(3u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto sourceDefaultBranch = sourceBranchHandlesBefore[1];

  const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterFluidToFluidHeatExchangerBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
  }
  EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(heatExchanger));
  ASSERT_TRUE(heatExchanger.plantLoop());
  ASSERT_TRUE(heatExchanger.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *heatExchanger.plantLoop());
  EXPECT_EQ(targetLoop, *heatExchanger.secondaryPlantLoop());
  EXPECT_FALSE(sourceLoop.demandComponent(heatExchanger.handle()));
  EXPECT_TRUE(targetLoop.demandComponent(heatExchanger.handle()));
  ASSERT_TRUE(heatExchanger.supplyInletModelObject());
  ASSERT_TRUE(heatExchanger.supplyOutletModelObject());
  ASSERT_TRUE(heatExchanger.demandInletModelObject());
  ASSERT_TRUE(heatExchanger.demandOutletModelObject());
  EXPECT_EQ(primaryInlet.handle(), heatExchanger.supplyInletModelObject()->handle());
  EXPECT_EQ(primaryOutlet.handle(), heatExchanger.supplyOutletModelObject()->handle());
  EXPECT_NE(oldDemandInlet.handle(), heatExchanger.demandInletModelObject()->handle());
  EXPECT_NE(oldDemandOutlet.handle(), heatExchanger.demandOutletModelObject()->handle());
  EXPECT_TRUE(model.getObject(oldDemandInlet.handle()));
  EXPECT_TRUE(model.getObject(oldDemandOutlet.handle()));
  ASSERT_TRUE(heatExchanger.availabilitySchedule());
  ASSERT_TRUE(heatExchanger.componentOverrideLoopSupplySideInletNode());
  ASSERT_TRUE(heatExchanger.componentOverrideLoopDemandSideInletNode());
  EXPECT_EQ(availability.handle(), heatExchanger.availabilitySchedule()->handle());
  EXPECT_EQ(primaryInlet.handle(), heatExchanger.componentOverrideLoopSupplySideInletNode()->handle());
  EXPECT_EQ(oldDemandInlet.handle(), heatExchanger.componentOverrideLoopDemandSideInletNode()->handle());
  EXPECT_DOUBLE_EQ(417.25, *heatExchanger.heatExchangerUFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1.17, heatExchanger.sizingFactor());
  EXPECT_EQ("CoolingSetpointModulated", heatExchanger.controlType());
  EXPECT_EQ(primarySetpoint.handle(), primaryLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(sourceBranchHandlesBefore, objectHandles(sourceBranchList->branches()));
  EXPECT_EQ(sourceDefaultBranch, sourceBranchList->branches()[1].handle());
  EXPECT_TRUE(sourceBranchList->branches()[1].components().empty());
  expectDemandBranchAndConnectorOrder(sourceLoop, sourceBranchHandlesBefore);
  const auto targetBranchHandlesAfter = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, targetBranchHandlesAfter.size());
  EXPECT_EQ(targetBranchHandlesBefore[0], targetBranchHandlesAfter[0]);
  EXPECT_EQ(targetBranchHandlesBefore[1], targetBranchHandlesAfter[1]);
  EXPECT_EQ(targetBranchHandlesBefore[2], targetBranchHandlesAfter[3]);
  EXPECT_NE(targetBranchHandlesBefore[1], targetBranchHandlesAfter[2]);
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesAfter);

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPrimary = loadedModel->getConcreteModelObjectByName<PlantLoop>("Fluid HX Primary Loop");
  auto loadedSource = loadedModel->getConcreteModelObjectByName<PlantLoop>("Fluid HX Original Secondary Loop");
  auto loadedTarget = loadedModel->getConcreteModelObjectByName<PlantLoop>("Fluid HX Moved Secondary Loop");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Moved Fluid To Fluid Heat Exchanger");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Fluid HX Availability");
  ASSERT_TRUE(loadedPrimary);
  ASSERT_TRUE(loadedSource);
  ASSERT_TRUE(loadedTarget);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedHeatExchanger->plantLoop());
  ASSERT_TRUE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedHeatExchanger->plantLoop());
  EXPECT_EQ(*loadedTarget, *loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_FALSE(loadedSource->demandComponent(loadedHeatExchanger->handle()));
  EXPECT_TRUE(loadedTarget->demandComponent(loadedHeatExchanger->handle()));
  ASSERT_TRUE(loadedHeatExchanger->availabilitySchedule());
  EXPECT_EQ(*loadedAvailability, *loadedHeatExchanger->availabilitySchedule());
  ASSERT_TRUE(loadedHeatExchanger->componentOverrideLoopSupplySideInletNode());
  ASSERT_TRUE(loadedHeatExchanger->componentOverrideLoopDemandSideInletNode());
  EXPECT_EQ(primaryInlet.nameString(), loadedHeatExchanger->componentOverrideLoopSupplySideInletNode()->nameString());
  EXPECT_EQ(oldDemandInlet.nameString(), loadedHeatExchanger->componentOverrideLoopDemandSideInletNode()->nameString());
  EXPECT_DOUBLE_EQ(417.25, *loadedHeatExchanger->heatExchangerUFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1.17, loadedHeatExchanger->sizingFactor());
  EXPECT_EQ("CoolingSetpointModulated", loadedHeatExchanger->controlType());
  EXPECT_EQ(primarySetpoint.nameString(), loadedPrimary->loopTemperatureSetpointNode().nameString());
  EXPECT_EQ(sourceSetpoint.nameString(), loadedSource->loopTemperatureSetpointNode().nameString());
  EXPECT_EQ(targetSetpoint.nameString(), loadedTarget->loopTemperatureSetpointNode().nameString());
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerDemandMoveParallelSourceToDefaultTargetIsTransactionalAndSecondaryRemovalRetainsPrimary) {
  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  PipeAdiabatic retainedSourcePipe(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(retainedSourcePipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));
  auto primarySetpoint = primaryLoop.supplyInletNode();
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(primaryLoop.setLoopTemperatureSetpointNode(primarySetpoint));
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  ASSERT_TRUE(heatExchanger.supplyInletModelObject());
  ASSERT_TRUE(heatExchanger.supplyOutletModelObject());
  ASSERT_TRUE(heatExchanger.demandInletModelObject());
  ASSERT_TRUE(heatExchanger.demandOutletModelObject());
  const auto primaryInletHandle = heatExchanger.supplyInletModelObject()->handle();
  const auto primaryOutletHandle = heatExchanger.supplyOutletModelObject()->handle();
  const auto oldDemandInletHandle = heatExchanger.demandInletModelObject()->handle();
  const auto oldDemandOutletHandle = heatExchanger.demandOutletModelObject()->handle();

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchesBefore = sourceBranchList->branches();
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchesBefore);
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto removedBranch = std::ranges::find_if(sourceBranchesBefore, [&heatExchanger](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, heatExchanger.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceBranchesBefore.end(), removedBranch);
  const auto removedBranchHandle = removedBranch->handle();
  auto expectedSourceBranchHandles = sourceBranchHandlesBefore;
  const auto removedHandle = std::ranges::find(expectedSourceBranchHandles, removedBranchHandle);
  ASSERT_NE(expectedSourceBranchHandles.end(), removedHandle);
  expectedSourceBranchHandles.erase(removedHandle);
  const auto targetDefaultBranch = targetBranchHandlesBefore[1];

  const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterFluidToFluidHeatExchangerBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
  }
  EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(heatExchanger));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(oldDemandInletHandle));
  EXPECT_TRUE(model.getObject(oldDemandOutletHandle));
  ASSERT_TRUE(heatExchanger.plantLoop());
  ASSERT_TRUE(heatExchanger.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *heatExchanger.plantLoop());
  EXPECT_EQ(targetLoop, *heatExchanger.secondaryPlantLoop());
  ASSERT_TRUE(heatExchanger.supplyInletModelObject());
  ASSERT_TRUE(heatExchanger.supplyOutletModelObject());
  EXPECT_EQ(primaryInletHandle, heatExchanger.supplyInletModelObject()->handle());
  EXPECT_EQ(primaryOutletHandle, heatExchanger.supplyOutletModelObject()->handle());
  EXPECT_EQ(primarySetpoint.handle(), primaryLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(expectedSourceBranchHandles, objectHandles(sourceBranchList->branches()));
  expectDemandBranchAndConnectorOrder(sourceLoop, expectedSourceBranchHandles);
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  EXPECT_EQ(targetDefaultBranch, targetBranchList->branches()[1].handle());
  EXPECT_EQ(std::vector<ModelObject>{heatExchanger.cast<ModelObject>()}, targetBranchList->branches()[1].components());
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);

  const auto targetHandle = targetLoop.handle();
  EXPECT_FALSE(targetLoop.remove().empty());
  EXPECT_FALSE(model.getObject(targetHandle));
  EXPECT_TRUE(model.getObject(heatExchanger.handle()));
  ASSERT_TRUE(heatExchanger.plantLoop());
  EXPECT_EQ(primaryLoop, *heatExchanger.plantLoop());
  EXPECT_FALSE(heatExchanger.secondaryPlantLoop());
  EXPECT_TRUE(heatExchanger.supplyInletModelObject());
  EXPECT_TRUE(heatExchanger.supplyOutletModelObject());
  EXPECT_FALSE(heatExchanger.demandInletModelObject());
  EXPECT_FALSE(heatExchanger.demandOutletModelObject());
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerMovedPrimaryRemovalRetainsSecondary) {
  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(heatExchanger));
  ASSERT_TRUE(heatExchanger.plantLoop());
  ASSERT_TRUE(heatExchanger.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *heatExchanger.plantLoop());
  EXPECT_EQ(targetLoop, *heatExchanger.secondaryPlantLoop());

  const auto targetDemandInletHandle = heatExchanger.demandInletModelObject()->handle();
  const auto targetDemandOutletHandle = heatExchanger.demandOutletModelObject()->handle();
  const auto primaryHandle = primaryLoop.handle();
  EXPECT_FALSE(primaryLoop.remove().empty());
  EXPECT_FALSE(model.getObject(primaryHandle));
  EXPECT_TRUE(model.getObject(heatExchanger.handle()));
  EXPECT_FALSE(heatExchanger.plantLoop());
  EXPECT_FALSE(heatExchanger.supplyInletModelObject());
  EXPECT_FALSE(heatExchanger.supplyOutletModelObject());
  ASSERT_TRUE(heatExchanger.secondaryPlantLoop());
  EXPECT_EQ(targetLoop, *heatExchanger.secondaryPlantLoop());
  ASSERT_TRUE(heatExchanger.demandInletModelObject());
  ASSERT_TRUE(heatExchanger.demandOutletModelObject());
  EXPECT_EQ(targetDemandInletHandle, heatExchanger.demandInletModelObject()->handle());
  EXPECT_EQ(targetDemandOutletHandle, heatExchanger.demandOutletModelObject()->handle());
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerInitialDemandAttachmentRemainsSupported) {
  Model model;
  PlantLoop unattachedTarget(model);
  HeatExchangerFluidToFluid unattachedHeatExchanger(model);
  EXPECT_TRUE(unattachedTarget.addDemandBranchForComponent(unattachedHeatExchanger));
  EXPECT_FALSE(unattachedHeatExchanger.plantLoop());
  ASSERT_TRUE(unattachedHeatExchanger.secondaryPlantLoop());
  EXPECT_EQ(unattachedTarget, *unattachedHeatExchanger.secondaryPlantLoop());

  PlantLoop primaryLoop(model);
  PlantLoop primaryOnlyTarget(model);
  HeatExchangerFluidToFluid primaryOnlyHeatExchanger(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(primaryOnlyHeatExchanger));
  EXPECT_TRUE(primaryOnlyTarget.addDemandBranchForComponent(primaryOnlyHeatExchanger));
  ASSERT_TRUE(primaryOnlyHeatExchanger.plantLoop());
  ASSERT_TRUE(primaryOnlyHeatExchanger.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *primaryOnlyHeatExchanger.plantLoop());
  EXPECT_EQ(primaryOnlyTarget, *primaryOnlyHeatExchanger.secondaryPlantLoop());
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerDemandMoveRejectsSamePrimaryTertiarySerialAndForeignTargetsWithoutMutation) {
  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));

  const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
  EXPECT_FALSE(sourceLoop.addDemandBranchForComponent(heatExchanger));
  EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));
  EXPECT_FALSE(primaryLoop.addDemandBranchForComponent(heatExchanger));
  EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger, true));
  EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));

  Model foreignModel;
  PlantLoop foreignTarget(foreignModel);
  EXPECT_FALSE(foreignTarget.addDemandBranchForComponent(heatExchanger));
  EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));

  ASSERT_TRUE(heatExchanger.demandOutletModelObject());
  PipeAdiabatic serialPipe(model);
  auto serialInsertionNode = heatExchanger.demandOutletModelObject()->cast<Node>();
  ASSERT_TRUE(serialPipe.addToNode(serialInsertionNode));
  const auto serialBefore = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
  EXPECT_EQ(serialBefore, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerDemandMoveRejectsPartialAndRawBranchEvidenceWithoutMutation) {
  {
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop unusedSourceLoop(model);
    PlantLoop targetLoop(model);
    HeatExchangerFluidToFluid heatExchanger(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
    Node malformedDemandInlet(model);
    auto heatExchangerWorkspaceImpl = heatExchanger.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    ASSERT_TRUE(heatExchangerWorkspaceImpl);
    ASSERT_TRUE(heatExchangerWorkspaceImpl->setPointer(heatExchanger.demandInletPort(), openstudio::Handle(), false));
    ASSERT_TRUE(heatExchangerWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(heatExchanger.demandInletPort(),
                                                                                          malformedDemandInlet.nameString(), false));
    const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, unusedSourceLoop, targetLoop, heatExchanger, false);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
    EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, unusedSourceLoop, targetLoop, heatExchanger, false));
  }

  {
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    HeatExchangerFluidToFluid heatExchanger(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));
    ASSERT_TRUE(heatExchanger.demandInletModelObject());
    ASSERT_TRUE(heatExchanger.demandOutletModelObject());

    Branch rawAliasBranch(model);
    auto rawAliasRow = rawAliasBranch.pushExtensibleGroup();
    ASSERT_FALSE(rawAliasRow.empty());
    ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentObjectType, heatExchanger.iddObject().name(), false));
    ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentName, heatExchanger.nameString(), false));
    ASSERT_TRUE(
      rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentInletNodeName, heatExchanger.demandInletModelObject()->nameString(), false));
    ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentOutletNodeName,
                                      heatExchanger.demandOutletModelObject()->nameString(), false));
    const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
    EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));
  }
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerInitialDispatchRejectsMalformedPrimaryEvidenceWithoutMutation) {
  enum class MalformedPrimaryCase
  {
    OrphanRow,
    WrongSideRow,
    DuplicateBranchListMembership,
  };

  for (const auto malformedCase :
       {MalformedPrimaryCase::OrphanRow, MalformedPrimaryCase::WrongSideRow, MalformedPrimaryCase::DuplicateBranchListMembership}) {
    SCOPED_TRACE(static_cast<int>(malformedCase));
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop unusedSourceLoop(model);
    PlantLoop targetLoop(model);
    HeatExchangerFluidToFluid heatExchanger(model);

    if (malformedCase == MalformedPrimaryCase::OrphanRow) {
      Branch orphanBranch(model);
      Node orphanInlet(model);
      Node orphanOutlet(model);
      auto orphanBranchImpl = orphanBranch.getImpl<detail::Branch_Impl>();
      ASSERT_TRUE(orphanBranchImpl);
      ASSERT_TRUE(orphanBranchImpl->appendComponent(heatExchanger.cast<ModelObject>(), orphanInlet.nameString(), orphanOutlet.nameString()));
    } else if (malformedCase == MalformedPrimaryCase::WrongSideRow) {
      ASSERT_TRUE(primaryLoop.addDemandBranchForComponent(heatExchanger));
      ASSERT_TRUE(heatExchanger.demandInletModelObject());
      ASSERT_TRUE(heatExchanger.demandOutletModelObject());
      auto heatExchangerWorkspaceImpl = heatExchanger.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(heatExchangerWorkspaceImpl);
      ASSERT_TRUE(heatExchangerWorkspaceImpl->setPointer(heatExchanger.supplyInletPort(), heatExchanger.demandInletModelObject()->handle(), false));
      ASSERT_TRUE(heatExchangerWorkspaceImpl->setPointer(heatExchanger.supplyOutletPort(), heatExchanger.demandOutletModelObject()->handle(), false));
      ASSERT_TRUE(heatExchangerWorkspaceImpl->setPointer(heatExchanger.demandInletPort(), openstudio::Handle(), false));
      ASSERT_TRUE(heatExchangerWorkspaceImpl->setPointer(heatExchanger.demandOutletPort(), openstudio::Handle(), false));
    } else {
      ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
      auto primaryBranchList = primaryLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
      ASSERT_TRUE(primaryBranchList);
      const auto primaryBranches = primaryBranchList->branches();
      const auto primaryBranch = std::ranges::find_if(primaryBranches, [&heatExchanger](const auto& branch) {
        const auto components = branch.components();
        return std::ranges::find(components, heatExchanger.cast<ModelObject>()) != components.end();
      });
      ASSERT_NE(primaryBranches.end(), primaryBranch);
      auto duplicateRow = primaryBranchList->pushExtensibleGroup();
      ASSERT_FALSE(duplicateRow.empty());
      ASSERT_TRUE(duplicateRow.setString(openstudio::BranchListExtensibleFields::BranchName, primaryBranch->nameString(), false));
    }

    const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, unusedSourceLoop, targetLoop, heatExchanger, false);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
    EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, unusedSourceLoop, targetLoop, heatExchanger, false));
  }
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerDemandMoveRejectsTargetScaffoldAliasesWithoutMutation) {
  enum class TargetAliasCase
  {
    ManagedBranchListOwner,
    RawConnectorListOwner,
    RawBranchListMembership,
  };

  for (const auto aliasCase :
       {TargetAliasCase::ManagedBranchListOwner, TargetAliasCase::RawConnectorListOwner, TargetAliasCase::RawBranchListMembership}) {
    SCOPED_TRACE(static_cast<int>(aliasCase));
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    PlantLoop aliasLoop(model);
    HeatExchangerFluidToFluid heatExchanger(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));

    auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
    auto targetConnectorList = targetLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
    ASSERT_TRUE(targetBranchList);
    ASSERT_TRUE(targetConnectorList);
    auto aliasLoopWorkspaceImpl = aliasLoop.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    ASSERT_TRUE(aliasLoopWorkspaceImpl);

    if (aliasCase == TargetAliasCase::ManagedBranchListOwner) {
      ASSERT_TRUE(aliasLoopWorkspaceImpl->setPointer(openstudio::PlantLoopFields::PlantSideBranchListName, targetBranchList->handle(), false));
    } else if (aliasCase == TargetAliasCase::RawConnectorListOwner) {
      ASSERT_TRUE(aliasLoopWorkspaceImpl->setPointer(openstudio::PlantLoopFields::PlantSideConnectorListName, openstudio::Handle(), false));
      ASSERT_TRUE(aliasLoopWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::PlantLoopFields::PlantSideConnectorListName,
                                                                                        targetConnectorList->nameString(), false));
    } else {
      BranchList rawAliasList(model);
      auto rawAliasRow = rawAliasList.pushExtensibleGroup();
      ASSERT_FALSE(rawAliasRow.empty());
      ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchListExtensibleFields::BranchName, targetBranchList->branches()[1].nameString(), false));
    }

    const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
    EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));
  }
}

TEST_F(EPModelFixture, PlantLoop_FluidToFluidHeatExchangerDemandMoveRejectsTargetNodeNameCollisionsWithoutMutation) {
  enum class NodeCollisionCase
  {
    DefaultAnchor,
    DefaultOutlet,
    DefaultOutletRawOwner,
    NewBranchInlet,
    NewBranchOutlet,
  };

  for (const auto collisionCase : {NodeCollisionCase::DefaultAnchor, NodeCollisionCase::DefaultOutlet, NodeCollisionCase::DefaultOutletRawOwner,
                                   NodeCollisionCase::NewBranchInlet, NodeCollisionCase::NewBranchOutlet}) {
    SCOPED_TRACE(static_cast<int>(collisionCase));
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    HeatExchangerFluidToFluid heatExchanger(model);
    ASSERT_TRUE(targetLoop.setName("HX Node Collision Target"));
    ASSERT_TRUE(heatExchanger.setName("HX Node Collision Component"));
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatExchanger));

    const bool occupiedTarget = collisionCase == NodeCollisionCase::NewBranchInlet || collisionCase == NodeCollisionCase::NewBranchOutlet;
    if (occupiedTarget) {
      PipeAdiabatic targetPipe(model);
      ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetPipe));
    }
    auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
    ASSERT_TRUE(targetBranchList);
    ASSERT_EQ(3u, targetBranchList->branches().size());
    const auto plannedBranchName = occupiedTarget ? targetLoop.nameString() + " Demand Branch 2" : targetBranchList->branches()[1].nameString();
    const auto plannedInletName = plannedBranchName + " Node";
    const auto plannedOutletName = plannedInletName + " - " + heatExchanger.nameString() + " Outlet";
    const auto collisionName = (collisionCase == NodeCollisionCase::DefaultAnchor || collisionCase == NodeCollisionCase::NewBranchInlet)
                                 ? plannedInletName
                                 : plannedOutletName;
    if (collisionCase == NodeCollisionCase::DefaultOutletRawOwner) {
      PipeAdiabatic rawOwner(model);
      auto rawOwnerWorkspaceImpl = rawOwner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      ASSERT_TRUE(rawOwnerWorkspaceImpl);
      ASSERT_TRUE(rawOwnerWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(rawOwner.inletPort(), collisionName, false));
    } else {
      Node collision(model);
      if (collisionCase == NodeCollisionCase::DefaultAnchor) {
        const auto nameField = collision.iddObject().nameFieldIndex();
        auto collisionWorkspaceImpl = collision.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        ASSERT_TRUE(nameField);
        ASSERT_TRUE(collisionWorkspaceImpl);
        ASSERT_TRUE(collisionWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(*nameField, collisionName, false));
      } else {
        ASSERT_TRUE(collision.setName(collisionName));
      }
    }

    const auto before = captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatExchanger));
    EXPECT_EQ(before, captureFluidToFluidHeatExchangerMove(model, primaryLoop, sourceLoop, targetLoop, heatExchanger));
  }
}

TEST_F(EPModelFixture, PlantLoop_EquationFitHeatingLoadSideDemandMoveDefaultToOccupiedIsTransactionalAcrossReload) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-heating-demand-move-" + openstudio::toString(openstudio::createUUID()) + ".idf");
  ScopedFileRemoval cleanup(idfPath);

  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatPump(model);
  HeatPumpWaterToWaterEquationFitCooling companion(model);
  PipeAdiabatic targetPipe(model);
  ASSERT_TRUE(primaryLoop.setName("EquationFit Heating Source Primary"));
  ASSERT_TRUE(sourceLoop.setName("EquationFit Heating Original Load Secondary"));
  ASSERT_TRUE(targetLoop.setName("EquationFit Heating Moved Load Secondary"));
  ASSERT_TRUE(heatPump.setName("Moved EquationFit Heating Heat Pump"));
  ASSERT_TRUE(companion.setName("Reciprocal EquationFit Cooling Companion"));
  ASSERT_TRUE(targetPipe.setName("EquationFit Heating Target Pipe"));
  ASSERT_TRUE(heatPump.setReferenceCoefficientofPerformance(6.75));
  ASSERT_TRUE(heatPump.setSizingFactor(1.13));
  ASSERT_TRUE(heatPump.setRatedHeatingCapacity(18350.0));
  ASSERT_TRUE(heatPump.setCompanionCoolingHeatPump(companion));
  ASSERT_TRUE(companion.setCompanionHeatingHeatPump(heatPump));
  auto primaryOutlet = primaryLoop.supplyOutletNode();
  ASSERT_TRUE(heatPump.addToNode(primaryOutlet));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetPipe));
  auto primarySetpoint = primaryLoop.supplyInletNode();
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(primaryLoop.setLoopTemperatureSetpointNode(primarySetpoint));
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  ASSERT_TRUE(heatPump.supplyInletModelObject());
  ASSERT_TRUE(heatPump.supplyOutletModelObject());
  ASSERT_TRUE(heatPump.demandInletModelObject());
  ASSERT_TRUE(heatPump.demandOutletModelObject());
  const auto primaryInletHandle = heatPump.supplyInletModelObject()->handle();
  const auto primaryOutletHandle = heatPump.supplyOutletModelObject()->handle();
  const auto oldLoadInletHandle = heatPump.demandInletModelObject()->handle();
  const auto oldLoadOutletHandle = heatPump.demandOutletModelObject()->handle();
  const auto sourceSideInletRaw = rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName);
  const auto sourceSideOutletRaw = rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName);
  const auto companionFieldsBefore = equationFitCompanionRawFields(model);
  const auto heatingCapacityCurveHandle = heatPump.heatingCapacityCurve().handle();
  const auto heatingPowerCurveHandle = heatPump.heatingCompressorPowerCurve().handle();

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchList->branches());
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(3u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto sourceDefaultBranchHandle = sourceBranchHandlesBefore[1];

  const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterEquationFitHeatPumpBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
  }
  EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatPump.plantLoop());
  ASSERT_TRUE(heatPump.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *heatPump.plantLoop());
  EXPECT_EQ(targetLoop, *heatPump.secondaryPlantLoop());
  ASSERT_TRUE(heatPump.supplyInletModelObject());
  ASSERT_TRUE(heatPump.supplyOutletModelObject());
  ASSERT_TRUE(heatPump.demandInletModelObject());
  ASSERT_TRUE(heatPump.demandOutletModelObject());
  EXPECT_EQ(primaryInletHandle, heatPump.supplyInletModelObject()->handle());
  EXPECT_EQ(primaryOutletHandle, heatPump.supplyOutletModelObject()->handle());
  EXPECT_NE(oldLoadInletHandle, heatPump.demandInletModelObject()->handle());
  EXPECT_NE(oldLoadOutletHandle, heatPump.demandOutletModelObject()->handle());
  EXPECT_TRUE(model.getObject(oldLoadInletHandle));
  EXPECT_TRUE(model.getObject(oldLoadOutletHandle));
  EXPECT_TRUE(sourceSideInletRaw == rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName));
  EXPECT_TRUE(sourceSideOutletRaw == rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName));
  const auto loadSideInlet = heatPump.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName);
  const auto loadSideOutlet =
    heatPump.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName);
  ASSERT_TRUE(loadSideInlet);
  ASSERT_TRUE(loadSideOutlet);
  EXPECT_EQ(heatPump.demandInletModelObject()->handle(), loadSideInlet->handle());
  EXPECT_EQ(heatPump.demandOutletModelObject()->handle(), loadSideOutlet->handle());
  EXPECT_TRUE(companionFieldsBefore == equationFitCompanionRawFields(model));
  ASSERT_TRUE(heatPump.companionCoolingHeatPump());
  ASSERT_TRUE(companion.companionHeatingHeatPump());
  EXPECT_EQ(companion, *heatPump.companionCoolingHeatPump());
  EXPECT_EQ(heatPump, *companion.companionHeatingHeatPump());
  EXPECT_DOUBLE_EQ(6.75, heatPump.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.13, heatPump.sizingFactor());
  ASSERT_TRUE(heatPump.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(18350.0, *heatPump.ratedHeatingCapacity());
  EXPECT_EQ(heatingCapacityCurveHandle, heatPump.heatingCapacityCurve().handle());
  EXPECT_EQ(heatingPowerCurveHandle, heatPump.heatingCompressorPowerCurve().handle());
  EXPECT_EQ(primarySetpoint.handle(), primaryLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(sourceBranchHandlesBefore, objectHandles(sourceBranchList->branches()));
  EXPECT_EQ(sourceDefaultBranchHandle, sourceBranchList->branches()[1].handle());
  EXPECT_TRUE(sourceBranchList->branches()[1].components().empty());
  expectDemandBranchAndConnectorOrder(sourceLoop, sourceBranchHandlesBefore);
  const auto targetBranchHandlesAfter = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, targetBranchHandlesAfter.size());
  EXPECT_EQ(targetBranchHandlesBefore[0], targetBranchHandlesAfter[0]);
  EXPECT_EQ(targetBranchHandlesBefore[1], targetBranchHandlesAfter[1]);
  EXPECT_EQ(targetBranchHandlesBefore[2], targetBranchHandlesAfter[3]);
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesAfter);

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPrimary = loadedModel->getConcreteModelObjectByName<PlantLoop>("EquationFit Heating Source Primary");
  auto loadedSource = loadedModel->getConcreteModelObjectByName<PlantLoop>("EquationFit Heating Original Load Secondary");
  auto loadedTarget = loadedModel->getConcreteModelObjectByName<PlantLoop>("EquationFit Heating Moved Load Secondary");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Moved EquationFit Heating Heat Pump");
  auto loadedCompanion =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Reciprocal EquationFit Cooling Companion");
  auto loadedTargetPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("EquationFit Heating Target Pipe");
  ASSERT_TRUE(loadedPrimary);
  ASSERT_TRUE(loadedSource);
  ASSERT_TRUE(loadedTarget);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedCompanion);
  ASSERT_TRUE(loadedTargetPipe);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedTarget, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedSource->demandComponent(loadedHeatPump->handle()));
  ASSERT_TRUE(loadedHeatPump->supplyInletModelObject());
  ASSERT_TRUE(loadedHeatPump->demandInletModelObject());
  const auto loadedSourceSideInlet =
    loadedHeatPump->getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName);
  const auto loadedLoadSideInlet =
    loadedHeatPump->getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName);
  ASSERT_TRUE(loadedSourceSideInlet);
  ASSERT_TRUE(loadedLoadSideInlet);
  EXPECT_EQ(loadedHeatPump->supplyInletModelObject()->handle(), loadedSourceSideInlet->handle());
  EXPECT_EQ(loadedHeatPump->demandInletModelObject()->handle(), loadedLoadSideInlet->handle());
  ASSERT_TRUE(loadedHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCompanion->companionHeatingHeatPump());
  EXPECT_EQ(*loadedCompanion, *loadedHeatPump->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatPump, *loadedCompanion->companionHeatingHeatPump());

  // Keep this lifecycle assertion inside the existing single-specialized-owner
  // removal contract by first removing the ordinary occupied-target branch.
  ASSERT_TRUE(loadedTarget->removeDemandBranchWithComponent(*loadedTargetPipe));
  EXPECT_TRUE(loadedModel->getObject(loadedTargetPipe->handle()));
  const auto loadedTargetHandle = loadedTarget->handle();
  EXPECT_FALSE(loadedTarget->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedTargetHandle));
  EXPECT_TRUE(loadedModel->getObject(loadedHeatPump->handle()));
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCompanion->companionHeatingHeatPump());
}

TEST_F(EPModelFixture, PlantLoop_EquationFitCoolingSourceSideDemandMoveParallelToDefaultIsTransactionalAcrossReload) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-cooling-demand-move-" + openstudio::toString(openstudio::createUUID()) + ".idf");
  ScopedFileRemoval cleanup(idfPath);

  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatPumpWaterToWaterEquationFitCooling heatPump(model);
  HeatPumpWaterToWaterEquationFitHeating companion(model);
  PipeAdiabatic sourcePipe(model);
  ASSERT_TRUE(primaryLoop.setName("EquationFit Cooling Load Primary"));
  ASSERT_TRUE(sourceLoop.setName("EquationFit Cooling Original Source Secondary"));
  ASSERT_TRUE(targetLoop.setName("EquationFit Cooling Moved Source Secondary"));
  ASSERT_TRUE(heatPump.setName("Moved EquationFit Cooling Heat Pump"));
  ASSERT_TRUE(companion.setName("One Way EquationFit Heating Companion"));
  ASSERT_TRUE(sourcePipe.setName("EquationFit Cooling Source Pipe"));
  ASSERT_TRUE(heatPump.setReferenceCoefficientofPerformance(5.85));
  ASSERT_TRUE(heatPump.setSizingFactor(1.07));
  ASSERT_TRUE(heatPump.setRatedCoolingCapacity(22600.0));
  ASSERT_TRUE(companion.setCompanionCoolingHeatPump(heatPump));
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(sourcePipe));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  auto primarySetpoint = primaryLoop.supplyInletNode();
  auto sourceSetpoint = sourceLoop.supplyInletNode();
  auto targetSetpoint = targetLoop.supplyInletNode();
  ASSERT_TRUE(primaryLoop.setLoopTemperatureSetpointNode(primarySetpoint));
  ASSERT_TRUE(sourceLoop.setLoopTemperatureSetpointNode(sourceSetpoint));
  ASSERT_TRUE(targetLoop.setLoopTemperatureSetpointNode(targetSetpoint));

  ASSERT_TRUE(heatPump.supplyInletModelObject());
  ASSERT_TRUE(heatPump.supplyOutletModelObject());
  ASSERT_TRUE(heatPump.demandInletModelObject());
  ASSERT_TRUE(heatPump.demandOutletModelObject());
  const auto primaryInletHandle = heatPump.supplyInletModelObject()->handle();
  const auto primaryOutletHandle = heatPump.supplyOutletModelObject()->handle();
  const auto oldSourceInletHandle = heatPump.demandInletModelObject()->handle();
  const auto oldSourceOutletHandle = heatPump.demandOutletModelObject()->handle();
  const auto loadSideInletRaw = rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName);
  const auto loadSideOutletRaw = rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName);
  const auto companionFieldsBefore = equationFitCompanionRawFields(model);
  const auto coolingCapacityCurveHandle = heatPump.coolingCapacityCurve().handle();
  const auto coolingPowerCurveHandle = heatPump.coolingCompressorPowerCurve().handle();

  auto sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  auto targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  const auto sourceBranchesBefore = sourceBranchList->branches();
  const auto sourceBranchHandlesBefore = objectHandles(sourceBranchesBefore);
  const auto targetBranchHandlesBefore = objectHandles(targetBranchList->branches());
  ASSERT_EQ(4u, sourceBranchHandlesBefore.size());
  ASSERT_EQ(3u, targetBranchHandlesBefore.size());
  const auto removedBranch = std::ranges::find_if(sourceBranchesBefore, [&heatPump](const auto& branch) {
    const auto components = branch.components();
    return std::ranges::find(components, heatPump.cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(sourceBranchesBefore.end(), removedBranch);
  const auto removedBranchHandle = removedBranch->handle();
  auto expectedSourceBranchHandles = sourceBranchHandlesBefore;
  const auto removedHandle = std::ranges::find(expectedSourceBranchHandles, removedBranchHandle);
  ASSERT_NE(expectedSourceBranchHandles.end(), removedHandle);
  expectedSourceBranchHandles.erase(removedHandle);
  const auto targetDefaultBranchHandle = targetBranchHandlesBefore[1];

  const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::PlantLoopAfterEquationFitHeatPumpBranchAttachmentPrepared);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
  }
  EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));

  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(heatPump));
  EXPECT_FALSE(model.getObject(removedBranchHandle));
  EXPECT_TRUE(model.getObject(oldSourceInletHandle));
  EXPECT_TRUE(model.getObject(oldSourceOutletHandle));
  ASSERT_TRUE(heatPump.plantLoop());
  ASSERT_TRUE(heatPump.secondaryPlantLoop());
  EXPECT_EQ(primaryLoop, *heatPump.plantLoop());
  EXPECT_EQ(targetLoop, *heatPump.secondaryPlantLoop());
  ASSERT_TRUE(heatPump.supplyInletModelObject());
  ASSERT_TRUE(heatPump.supplyOutletModelObject());
  ASSERT_TRUE(heatPump.demandInletModelObject());
  ASSERT_TRUE(heatPump.demandOutletModelObject());
  EXPECT_EQ(primaryInletHandle, heatPump.supplyInletModelObject()->handle());
  EXPECT_EQ(primaryOutletHandle, heatPump.supplyOutletModelObject()->handle());
  EXPECT_NE(oldSourceInletHandle, heatPump.demandInletModelObject()->handle());
  EXPECT_NE(oldSourceOutletHandle, heatPump.demandOutletModelObject()->handle());
  EXPECT_TRUE(loadSideInletRaw == rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName));
  EXPECT_TRUE(loadSideOutletRaw == rawField(heatPump, openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName));
  const auto sourceSideInlet =
    heatPump.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName);
  const auto sourceSideOutlet =
    heatPump.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName);
  ASSERT_TRUE(sourceSideInlet);
  ASSERT_TRUE(sourceSideOutlet);
  EXPECT_EQ(heatPump.demandInletModelObject()->handle(), sourceSideInlet->handle());
  EXPECT_EQ(heatPump.demandOutletModelObject()->handle(), sourceSideOutlet->handle());
  EXPECT_TRUE(companionFieldsBefore == equationFitCompanionRawFields(model));
  EXPECT_FALSE(heatPump.companionHeatingHeatPump());
  ASSERT_TRUE(companion.companionCoolingHeatPump());
  EXPECT_EQ(heatPump, *companion.companionCoolingHeatPump());
  EXPECT_DOUBLE_EQ(5.85, heatPump.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.07, heatPump.sizingFactor());
  ASSERT_TRUE(heatPump.ratedCoolingCapacity());
  EXPECT_DOUBLE_EQ(22600.0, *heatPump.ratedCoolingCapacity());
  EXPECT_EQ(coolingCapacityCurveHandle, heatPump.coolingCapacityCurve().handle());
  EXPECT_EQ(coolingPowerCurveHandle, heatPump.coolingCompressorPowerCurve().handle());
  EXPECT_EQ(primarySetpoint.handle(), primaryLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(sourceSetpoint.handle(), sourceLoop.loopTemperatureSetpointNode().handle());
  EXPECT_EQ(targetSetpoint.handle(), targetLoop.loopTemperatureSetpointNode().handle());

  sourceBranchList = sourceLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  targetBranchList = targetLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(sourceBranchList);
  ASSERT_TRUE(targetBranchList);
  EXPECT_EQ(expectedSourceBranchHandles, objectHandles(sourceBranchList->branches()));
  expectDemandBranchAndConnectorOrder(sourceLoop, expectedSourceBranchHandles);
  EXPECT_EQ(targetBranchHandlesBefore, objectHandles(targetBranchList->branches()));
  EXPECT_EQ(targetDefaultBranchHandle, targetBranchList->branches()[1].handle());
  EXPECT_EQ(std::vector<ModelObject>{heatPump.cast<ModelObject>()}, targetBranchList->branches()[1].components());
  expectDemandBranchAndConnectorOrder(targetLoop, targetBranchHandlesBefore);

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPrimary = loadedModel->getConcreteModelObjectByName<PlantLoop>("EquationFit Cooling Load Primary");
  auto loadedSource = loadedModel->getConcreteModelObjectByName<PlantLoop>("EquationFit Cooling Original Source Secondary");
  auto loadedTarget = loadedModel->getConcreteModelObjectByName<PlantLoop>("EquationFit Cooling Moved Source Secondary");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Moved EquationFit Cooling Heat Pump");
  auto loadedCompanion = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("One Way EquationFit Heating Companion");
  ASSERT_TRUE(loadedPrimary);
  ASSERT_TRUE(loadedSource);
  ASSERT_TRUE(loadedTarget);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedCompanion);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedTarget, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedSource->demandComponent(loadedHeatPump->handle()));
  ASSERT_TRUE(loadedHeatPump->supplyInletModelObject());
  ASSERT_TRUE(loadedHeatPump->demandInletModelObject());
  const auto loadedLoadSideInlet =
    loadedHeatPump->getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName);
  const auto loadedSourceSideInlet =
    loadedHeatPump->getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName);
  ASSERT_TRUE(loadedLoadSideInlet);
  ASSERT_TRUE(loadedSourceSideInlet);
  EXPECT_EQ(loadedHeatPump->supplyInletModelObject()->handle(), loadedLoadSideInlet->handle());
  EXPECT_EQ(loadedHeatPump->demandInletModelObject()->handle(), loadedSourceSideInlet->handle());
  EXPECT_FALSE(loadedHeatPump->companionHeatingHeatPump());
  ASSERT_TRUE(loadedCompanion->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatPump, *loadedCompanion->companionCoolingHeatPump());

  const auto loadedPrimaryHandle = loadedPrimary->handle();
  EXPECT_FALSE(loadedPrimary->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedPrimaryHandle));
  EXPECT_TRUE(loadedModel->getObject(loadedHeatPump->handle()));
  EXPECT_FALSE(loadedHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedTarget, *loadedHeatPump->secondaryPlantLoop());
  ASSERT_TRUE(loadedCompanion->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatPump, *loadedCompanion->companionCoolingHeatPump());
}

TEST_F(EPModelFixture, PlantLoop_EquationFitHeatPumpInitialDemandAttachmentAndConcretePortSemanticsRemainSupported) {
  Model model;

  PlantLoop unattachedHeatingTarget(model);
  HeatPumpWaterToWaterEquationFitHeating unattachedHeating(model);
  ASSERT_TRUE(unattachedHeatingTarget.addDemandBranchForComponent(unattachedHeating));
  EXPECT_FALSE(unattachedHeating.plantLoop());
  ASSERT_TRUE(unattachedHeating.secondaryPlantLoop());
  EXPECT_EQ(unattachedHeatingTarget, *unattachedHeating.secondaryPlantLoop());
  ASSERT_TRUE(unattachedHeating.demandInletModelObject());
  ASSERT_TRUE(unattachedHeating.demandOutletModelObject());
  const auto unattachedHeatingLoadInlet =
    unattachedHeating.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName);
  const auto unattachedHeatingLoadOutlet =
    unattachedHeating.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName);
  ASSERT_TRUE(unattachedHeatingLoadInlet);
  ASSERT_TRUE(unattachedHeatingLoadOutlet);
  EXPECT_EQ(unattachedHeating.demandInletModelObject()->handle(), unattachedHeatingLoadInlet->handle());
  EXPECT_EQ(unattachedHeating.demandOutletModelObject()->handle(), unattachedHeatingLoadOutlet->handle());

  PlantLoop unattachedCoolingTarget(model);
  HeatPumpWaterToWaterEquationFitCooling unattachedCooling(model);
  ASSERT_TRUE(unattachedCoolingTarget.addDemandBranchForComponent(unattachedCooling));
  EXPECT_FALSE(unattachedCooling.plantLoop());
  ASSERT_TRUE(unattachedCooling.secondaryPlantLoop());
  EXPECT_EQ(unattachedCoolingTarget, *unattachedCooling.secondaryPlantLoop());
  ASSERT_TRUE(unattachedCooling.demandInletModelObject());
  ASSERT_TRUE(unattachedCooling.demandOutletModelObject());
  const auto unattachedCoolingSourceInlet =
    unattachedCooling.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName);
  const auto unattachedCoolingSourceOutlet =
    unattachedCooling.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName);
  ASSERT_TRUE(unattachedCoolingSourceInlet);
  ASSERT_TRUE(unattachedCoolingSourceOutlet);
  EXPECT_EQ(unattachedCooling.demandInletModelObject()->handle(), unattachedCoolingSourceInlet->handle());
  EXPECT_EQ(unattachedCooling.demandOutletModelObject()->handle(), unattachedCoolingSourceOutlet->handle());

  PlantLoop heatingPrimary(model);
  PlantLoop heatingSecondary(model);
  HeatPumpWaterToWaterEquationFitHeating primaryOnlyHeating(model);
  ASSERT_TRUE(heatingPrimary.addSupplyBranchForComponent(primaryOnlyHeating));
  ASSERT_TRUE(heatingSecondary.addDemandBranchForComponent(primaryOnlyHeating));
  ASSERT_TRUE(primaryOnlyHeating.plantLoop());
  ASSERT_TRUE(primaryOnlyHeating.secondaryPlantLoop());
  EXPECT_EQ(heatingPrimary, *primaryOnlyHeating.plantLoop());
  EXPECT_EQ(heatingSecondary, *primaryOnlyHeating.secondaryPlantLoop());
  ASSERT_TRUE(primaryOnlyHeating.supplyInletModelObject());
  ASSERT_TRUE(primaryOnlyHeating.demandInletModelObject());
  const auto heatingSourceInlet =
    primaryOnlyHeating.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName);
  const auto heatingLoadInlet =
    primaryOnlyHeating.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName);
  ASSERT_TRUE(heatingSourceInlet);
  ASSERT_TRUE(heatingLoadInlet);
  EXPECT_EQ(primaryOnlyHeating.supplyInletModelObject()->handle(), heatingSourceInlet->handle());
  EXPECT_EQ(primaryOnlyHeating.demandInletModelObject()->handle(), heatingLoadInlet->handle());
  EXPECT_FALSE(primaryOnlyHeating.companionCoolingHeatPump());

  PlantLoop coolingPrimary(model);
  PlantLoop coolingSecondary(model);
  HeatPumpWaterToWaterEquationFitCooling primaryOnlyCooling(model);
  ASSERT_TRUE(coolingPrimary.addSupplyBranchForComponent(primaryOnlyCooling));
  ASSERT_TRUE(coolingSecondary.addDemandBranchForComponent(primaryOnlyCooling));
  ASSERT_TRUE(primaryOnlyCooling.plantLoop());
  ASSERT_TRUE(primaryOnlyCooling.secondaryPlantLoop());
  EXPECT_EQ(coolingPrimary, *primaryOnlyCooling.plantLoop());
  EXPECT_EQ(coolingSecondary, *primaryOnlyCooling.secondaryPlantLoop());
  ASSERT_TRUE(primaryOnlyCooling.supplyInletModelObject());
  ASSERT_TRUE(primaryOnlyCooling.demandInletModelObject());
  const auto coolingLoadInlet =
    primaryOnlyCooling.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName);
  const auto coolingSourceInlet =
    primaryOnlyCooling.getModelObjectTarget<Node>(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName);
  ASSERT_TRUE(coolingLoadInlet);
  ASSERT_TRUE(coolingSourceInlet);
  EXPECT_EQ(primaryOnlyCooling.supplyInletModelObject()->handle(), coolingLoadInlet->handle());
  EXPECT_EQ(primaryOnlyCooling.demandInletModelObject()->handle(), coolingSourceInlet->handle());
  EXPECT_FALSE(primaryOnlyCooling.companionHeatingHeatPump());
}

TEST_F(EPModelFixture, PlantLoop_EquationFitHeatPumpDemandMoveRejectsSamePrimaryTertiarySerialAndForeignTargetsWithoutMutation) {
  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatPump(model);
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));

  const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
  EXPECT_FALSE(sourceLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));
  EXPECT_FALSE(primaryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump, true));
  EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));

  Model foreignModel;
  PlantLoop foreignTarget(foreignModel);
  EXPECT_FALSE(foreignTarget.addDemandBranchForComponent(heatPump));
  EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));

  ASSERT_TRUE(heatPump.demandOutletModelObject());
  PipeAdiabatic serialPipe(model);
  auto serialInsertionNode = heatPump.demandOutletModelObject()->cast<Node>();
  ASSERT_TRUE(serialPipe.addToNode(serialInsertionNode));
  const auto serialBefore = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
  EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ(serialBefore, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));
}

TEST_F(EPModelFixture, PlantLoop_EquationFitHeatPumpDemandMoveRejectsMalformedPortBranchAndCompanionEvidenceWithoutMutation) {
  {
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop unusedSourceLoop(model);
    PlantLoop targetLoop(model);
    HeatPumpWaterToWaterEquationFitHeating heatPump(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatPump));
    Node malformedLoadInlet(model);
    auto heatPumpWorkspaceImpl = heatPump.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    ASSERT_TRUE(heatPumpWorkspaceImpl);
    ASSERT_TRUE(heatPumpWorkspaceImpl->setPointer(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName,
                                                  openstudio::Handle(), false));
    ASSERT_TRUE(heatPumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(
      openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName, malformedLoadInlet.nameString(), false));
    const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, unusedSourceLoop, targetLoop, heatPump, false);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
    EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, unusedSourceLoop, targetLoop, heatPump, false));
  }

  {
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    HeatPumpWaterToWaterEquationFitCooling heatPump(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatPump));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
    ASSERT_TRUE(heatPump.demandInletModelObject());
    ASSERT_TRUE(heatPump.demandOutletModelObject());
    Branch rawAliasBranch(model);
    auto rawAliasRow = rawAliasBranch.pushExtensibleGroup();
    ASSERT_FALSE(rawAliasRow.empty());
    ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentObjectType, heatPump.iddObject().name(), false));
    ASSERT_TRUE(rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentName, heatPump.nameString(), false));
    ASSERT_TRUE(
      rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentInletNodeName, heatPump.demandInletModelObject()->nameString(), false));
    ASSERT_TRUE(
      rawAliasRow.setString(openstudio::BranchExtensibleFields::ComponentOutletNodeName, heatPump.demandOutletModelObject()->nameString(), false));
    const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
    EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));
  }

  {
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    HeatPumpWaterToWaterEquationFitHeating heatPump(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatPump));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
    auto heatPumpWorkspaceImpl = heatPump.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    ASSERT_TRUE(heatPumpWorkspaceImpl);
    ASSERT_TRUE(heatPumpWorkspaceImpl->setPointer(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName,
                                                  openstudio::Handle(), false));
    ASSERT_TRUE(heatPumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(
      openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName, "Missing Cooling Companion", false));
    const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
    EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));
  }

  {
    Model model;
    PlantLoop primaryLoop(model);
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    HeatPumpWaterToWaterEquationFitCooling heatPump(model);
    HeatPumpWaterToWaterEquationFitHeating rawInboundCompanion(model);
    ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatPump));
    ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
    auto companionWorkspaceImpl = rawInboundCompanion.getImpl<openstudio::detail::WorkspaceObject_Impl>();
    ASSERT_TRUE(companionWorkspaceImpl);
    ASSERT_TRUE(companionWorkspaceImpl->setPointer(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName,
                                                   openstudio::Handle(), false));
    ASSERT_TRUE(companionWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(
      openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::CompanionCoolingHeatPumpName, heatPump.nameString(), false));
    const auto before = captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump);
    EXPECT_FALSE(targetLoop.addDemandBranchForComponent(heatPump));
    EXPECT_EQ(before, captureEquationFitHeatPumpMove(model, primaryLoop, sourceLoop, targetLoop, heatPump));
  }
}

TEST_F(EPModelFixture, PlantLoop_ConfiguredChillerCondenserLoopRemovalPreservesPrimaryOwnerAndControls) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-configured-chiller-condenser-loop-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  ChillerElectricEIR chiller(model);
  PumpVariableSpeed pump(model);
  CoolingTowerSingleSpeed tower(model);
  PlantEquipmentOperationCoolingLoad operationScheme(model);
  ScheduleConstant operationSchedule(model);
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Retained Chiller Primary Loop"));
  ASSERT_TRUE(condenserLoop.setName("Removed Configured Chiller Condenser Loop"));
  ASSERT_TRUE(chiller.setName("Retained Configured Condenser Chiller"));
  ASSERT_TRUE(pump.setName("Removed Condenser Pump"));
  ASSERT_TRUE(tower.setName("Removed Condenser Tower"));
  ASSERT_TRUE(operationScheme.setName("Retained Condenser Operation Scheme"));
  ASSERT_TRUE(operationSchedule.setName("Retained Condenser Operation Schedule"));
  ASSERT_TRUE(basinSchedule.setName("Retained Condenser Basin Schedule"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  auto condenserSupplyInletNode = condenserLoop.supplyInletNode();
  ASSERT_TRUE(pump.addToNode(condenserSupplyInletNode));
  ASSERT_TRUE(condenserLoop.addSupplyBranchForComponent(tower));
  ASSERT_TRUE(tower.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(operationScheme.addEquipment(tower));
  ASSERT_TRUE(condenserLoop.setPlantEquipmentOperationCoolingLoad(operationScheme));
  ASSERT_TRUE(condenserLoop.setPlantEquipmentOperationCoolingLoadSchedule(operationSchedule));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Retained Chiller Primary Loop");
  auto loadedCondenserLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Configured Chiller Condenser Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Retained Configured Condenser Chiller");
  auto loadedPump = loadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Removed Condenser Pump");
  auto loadedTower = loadedModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Removed Condenser Tower");
  auto loadedOperationScheme = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Retained Condenser Operation Scheme");
  auto loadedOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Retained Condenser Operation Schedule");
  auto loadedBasinSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Retained Condenser Basin Schedule");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedPump);
  ASSERT_TRUE(loadedTower);
  ASSERT_TRUE(loadedOperationScheme);
  ASSERT_TRUE(loadedOperationSchedule);
  ASSERT_TRUE(loadedBasinSchedule);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());
  ASSERT_EQ(1u, loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).size());
  EXPECT_EQ(*loadedTower, loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).front());

  std::set<openstudio::Handle> condenserOwnerHandles;
  const auto addOwner = [&condenserOwnerHandles, &loadedChiller](const ModelObject& object) {
    if (object.handle() != loadedChiller->handle()) {
      condenserOwnerHandles.insert(object.handle());
    }
  };
  for (const auto& component : loadedCondenserLoop->supplyComponents()) {
    addOwner(component);
  }
  for (const auto& component : loadedCondenserLoop->demandComponents()) {
    addOwner(component);
  }
  const auto supplyBranchList = loadedCondenserLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  const auto demandBranchList = loadedCondenserLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  const auto supplyConnectorList = loadedCondenserLoop->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName);
  const auto demandConnectorList = loadedCondenserLoop->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
  const auto assignmentList =
    loadedCondenserLoop->getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
  const auto operationSchemes =
    loadedCondenserLoop->getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(supplyBranchList);
  ASSERT_TRUE(demandBranchList);
  ASSERT_TRUE(supplyConnectorList);
  ASSERT_TRUE(demandConnectorList);
  ASSERT_TRUE(assignmentList);
  ASSERT_TRUE(operationSchemes);
  addOwner(*supplyBranchList);
  addOwner(*demandBranchList);
  addOwner(*supplyConnectorList);
  addOwner(*demandConnectorList);
  addOwner(*assignmentList);
  addOwner(*operationSchemes);
  for (const auto& branch : supplyBranchList->branches()) {
    addOwner(branch);
    for (unsigned i = 0u; i < branch.extensibleGroups().size(); ++i) {
      if (auto inletNode = branch.componentInletNode(i)) {
        addOwner(*inletNode);
      }
      if (auto outletNode = branch.componentOutletNode(i)) {
        addOwner(*outletNode);
      }
    }
  }
  for (const auto& branch : demandBranchList->branches()) {
    addOwner(branch);
    for (unsigned i = 0u; i < branch.extensibleGroups().size(); ++i) {
      if (auto inletNode = branch.componentInletNode(i)) {
        addOwner(*inletNode);
      }
      if (auto outletNode = branch.componentOutletNode(i)) {
        addOwner(*outletNode);
      }
    }
  }
  addOwner(loadedCondenserLoop->supplySplitter());
  addOwner(loadedCondenserLoop->supplyMixer());
  addOwner(loadedCondenserLoop->demandSplitter());
  addOwner(loadedCondenserLoop->demandMixer());
  addOwner(loadedCondenserLoop->supplyInletNode());
  addOwner(loadedCondenserLoop->supplyOutletNode());
  addOwner(loadedCondenserLoop->demandInletNode());
  addOwner(loadedCondenserLoop->demandOutletNode());
  addOwner(*loadedPump);
  addOwner(*loadedTower);

  const auto condenserLoopHandle = loadedCondenserLoop->handle();
  const auto condenserSizingHandle = loadedCondenserLoop->sizingPlant().handle();
  const auto chillerHandle = loadedChiller->handle();
  ASSERT_FALSE(loadedCondenserLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(condenserLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(condenserSizingHandle));
  for (const auto& handle : condenserOwnerHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_TRUE(loadedChilledWaterLoop->supplyComponent(chillerHandle));
  EXPECT_FALSE(loadedChiller->condenserWaterLoop());
  EXPECT_FALSE(loadedChiller->condenserInletNode());
  EXPECT_FALSE(loadedChiller->condenserOutletNode());
  EXPECT_EQ("AirCooled", loadedChiller->condenserType());
  EXPECT_TRUE(loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).empty());
  EXPECT_TRUE(loadedModel->getObject(loadedOperationScheme->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationSchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedBasinSchedule->handle()));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Configured Chiller Condenser Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Removed Condenser Pump"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Removed Condenser Tower"));
  auto reloadedChilledWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Retained Chiller Primary Loop");
  auto reloadedChiller = reloadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Retained Configured Condenser Chiller");
  auto reloadedOperationScheme =
    reloadedModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Retained Condenser Operation Scheme");
  ASSERT_TRUE(reloadedChilledWaterLoop);
  ASSERT_TRUE(reloadedChiller);
  ASSERT_TRUE(reloadedOperationScheme);
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_FALSE(reloadedChiller->condenserWaterLoop());
  EXPECT_FALSE(reloadedChiller->condenserInletNode());
  EXPECT_FALSE(reloadedChiller->condenserOutletNode());
  EXPECT_EQ("AirCooled", reloadedChiller->condenserType());
  EXPECT_TRUE(reloadedOperationScheme->equipment(reloadedOperationScheme->maximumUpperLimit()).empty());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Retained Condenser Operation Schedule"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Retained Condenser Basin Schedule"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_DirectChillerCondenserBranchRemovalPreservesLoopEquipmentAndPrimaryOwner) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-direct-chiller-condenser-branch-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  ChillerElectricEIR chiller(model);
  PumpVariableSpeed pump(model);
  CoolingTowerSingleSpeed tower(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Direct Removal Chiller Primary Loop"));
  ASSERT_TRUE(condenserLoop.setName("Retained Direct Removal Condenser Loop"));
  ASSERT_TRUE(chiller.setName("Direct Condenser Branch Removal Chiller"));
  ASSERT_TRUE(pump.setName("Retained Direct Removal Pump"));
  ASSERT_TRUE(tower.setName("Retained Direct Removal Tower"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  auto condenserSupplyInletNode = condenserLoop.supplyInletNode();
  ASSERT_TRUE(pump.addToNode(condenserSupplyInletNode));
  ASSERT_TRUE(condenserLoop.addSupplyBranchForComponent(tower));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Direct Removal Chiller Primary Loop");
  auto loadedCondenserLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Retained Direct Removal Condenser Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Direct Condenser Branch Removal Chiller");
  auto loadedPump = loadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Retained Direct Removal Pump");
  auto loadedTower = loadedModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Retained Direct Removal Tower");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedPump);
  ASSERT_TRUE(loadedTower);
  const auto condenserLoopHandle = loadedCondenserLoop->handle();
  const auto condenserSizingHandle = loadedCondenserLoop->sizingPlant().handle();
  const auto pumpHandle = loadedPump->handle();
  const auto towerHandle = loadedTower->handle();
  ASSERT_TRUE(loadedChiller->chilledWaterInletNode());
  ASSERT_TRUE(loadedChiller->chilledWaterOutletNode());
  const auto primaryInletHandle = loadedChiller->chilledWaterInletNode()->handle();
  const auto primaryOutletHandle = loadedChiller->chilledWaterOutletNode()->handle();

  ASSERT_TRUE(loadedCondenserLoop->removeDemandBranchWithComponent(*loadedChiller));
  EXPECT_TRUE(loadedModel->getObject(condenserLoopHandle));
  EXPECT_TRUE(loadedModel->getObject(condenserSizingHandle));
  EXPECT_TRUE(loadedModel->getObject(pumpHandle));
  EXPECT_TRUE(loadedModel->getObject(towerHandle));
  EXPECT_TRUE(loadedCondenserLoop->supplyComponent(pumpHandle));
  EXPECT_TRUE(loadedCondenserLoop->supplyComponent(towerHandle));
  EXPECT_FALSE(loadedCondenserLoop->demandComponent(loadedChiller->handle()));
  EXPECT_FALSE(loadedChiller->condenserWaterLoop());
  EXPECT_FALSE(loadedChiller->condenserInletNode());
  EXPECT_FALSE(loadedChiller->condenserOutletNode());
  EXPECT_EQ("AirCooled", loadedChiller->condenserType());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(primaryInletHandle, loadedChiller->chilledWaterInletNode()->handle());
  EXPECT_EQ(primaryOutletHandle, loadedChiller->chilledWaterOutletNode()->handle());
  EXPECT_TRUE(loadedChilledWaterLoop->supplyComponent(loadedChiller->handle()));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedChilledWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Direct Removal Chiller Primary Loop");
  auto reloadedCondenserLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Retained Direct Removal Condenser Loop");
  auto reloadedChiller = reloadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Direct Condenser Branch Removal Chiller");
  auto reloadedPump = reloadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Retained Direct Removal Pump");
  auto reloadedTower = reloadedModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Retained Direct Removal Tower");
  ASSERT_TRUE(reloadedChilledWaterLoop);
  ASSERT_TRUE(reloadedCondenserLoop);
  ASSERT_TRUE(reloadedChiller);
  ASSERT_TRUE(reloadedPump);
  ASSERT_TRUE(reloadedTower);
  EXPECT_TRUE(reloadedCondenserLoop->supplyComponent(reloadedPump->handle()));
  EXPECT_TRUE(reloadedCondenserLoop->supplyComponent(reloadedTower->handle()));
  EXPECT_FALSE(reloadedCondenserLoop->demandComponent(reloadedChiller->handle()));
  EXPECT_FALSE(reloadedChiller->condenserWaterLoop());
  EXPECT_FALSE(reloadedChiller->condenserInletNode());
  EXPECT_FALSE(reloadedChiller->condenserOutletNode());
  EXPECT_EQ("AirCooled", reloadedChiller->condenserType());
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_TRUE(reloadedChilledWaterLoop->supplyComponent(reloadedChiller->handle()));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_BoilerControlRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-boiler-control-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  BoilerHotWater boiler(model);
  PlantEquipmentOperationHeatingLoad operationScheme(model);
  ScheduleConstant operationSchedule(model);
  ScheduleConstant availabilitySchedule(model);
  AvailabilityManagerScheduledOn availabilityManager(model);
  ASSERT_TRUE(plantLoop.setName("Boiler Control Removal Plant Loop"));
  ASSERT_TRUE(boiler.setName("Removal Lifecycle Boiler"));
  ASSERT_TRUE(operationScheme.setName("Removal Lifecycle Heating Operation"));
  ASSERT_TRUE(operationSchedule.setName("Removal Lifecycle Operation Schedule"));
  ASSERT_TRUE(availabilitySchedule.setName("Removal Lifecycle Availability Schedule"));
  ASSERT_TRUE(availabilityManager.setName("Removal Lifecycle Availability Manager"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(boiler));
  ASSERT_TRUE(operationScheme.addEquipment(boiler));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(operationScheme));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(operationSchedule));
  ASSERT_TRUE(availabilityManager.setSchedule(availabilitySchedule));
  ASSERT_TRUE(plantLoop.addAvailabilityManager(availabilityManager));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Boiler Control Removal Plant Loop");
  auto loadedBoiler = loadedModel->getConcreteModelObjectByName<BoilerHotWater>("Removal Lifecycle Boiler");
  auto loadedOperationScheme = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Removal Lifecycle Heating Operation");
  auto loadedOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Operation Schedule");
  auto loadedAvailabilitySchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Availability Schedule");
  auto loadedAvailabilityManager =
    loadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Removal Lifecycle Availability Manager");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedBoiler);
  ASSERT_TRUE(loadedOperationScheme);
  ASSERT_TRUE(loadedOperationSchedule);
  ASSERT_TRUE(loadedAvailabilitySchedule);
  ASSERT_TRUE(loadedAvailabilityManager);
  ASSERT_TRUE(loadedBoiler->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedBoiler->plantLoop());
  ASSERT_EQ(1u, loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).size());
  EXPECT_EQ(*loadedBoiler, loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).front());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*loadedOperationScheme, *loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(*loadedOperationSchedule, *loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  ASSERT_TRUE(loadedAvailabilityManager->loop());
  EXPECT_EQ(*loadedPlantLoop, *loadedAvailabilityManager->loop());
  EXPECT_EQ(*loadedAvailabilitySchedule, loadedAvailabilityManager->schedule());

  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto boilerHandle = loadedBoiler->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(boilerHandle));
  EXPECT_TRUE(loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).empty());
  EXPECT_FALSE(loadedAvailabilityManager->loop());
  EXPECT_TRUE(loadedModel->getObject(loadedOperationScheme->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationSchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilityManager->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilitySchedule->handle()));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<BoilerHotWater>("Removal Lifecycle Boiler"));
  auto reloadedOperationScheme =
    reloadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Removal Lifecycle Heating Operation");
  auto reloadedAvailabilityManager =
    reloadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Removal Lifecycle Availability Manager");
  ASSERT_TRUE(reloadedOperationScheme);
  EXPECT_TRUE(reloadedOperationScheme->equipment(reloadedOperationScheme->maximumUpperLimit()).empty());
  ASSERT_TRUE(reloadedAvailabilityManager);
  EXPECT_FALSE(reloadedAvailabilityManager->loop());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Operation Schedule"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Availability Schedule"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_MultiSideStraightComponentRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-multi-side-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic supplyPipe(model);
  PipeAdiabatic demandPipe(model);
  ASSERT_TRUE(plantLoop.setName("Multi-side Removal Plant Loop"));
  ASSERT_TRUE(supplyPipe.setName("Owned Supply Removal Pipe"));
  ASSERT_TRUE(demandPipe.setName("Owned Demand Removal Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(supplyPipe));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(demandPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Multi-side Removal Plant Loop");
  auto loadedSupplyPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Removal Pipe");
  auto loadedDemandPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Demand Removal Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedSupplyPipe);
  ASSERT_TRUE(loadedDemandPipe);
  ASSERT_TRUE(loadedSupplyPipe->plantLoop());
  ASSERT_TRUE(loadedDemandPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSupplyPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedDemandPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(loadedSupplyPipe->handle()));
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedDemandPipe->handle()));
  EXPECT_EQ(7u, loadedPlantLoop->supplyComponents().size());
  EXPECT_EQ(7u, loadedPlantLoop->demandComponents().size());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto supplyPipeHandle = loadedSupplyPipe->handle();
  const auto demandPipeHandle = loadedDemandPipe->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(supplyPipeHandle));
  EXPECT_FALSE(loadedModel->getObject(demandPipeHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Removal Pipe"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Demand Removal Pipe"));

  openstudio::filesystem::remove(idfPath);
}

namespace {
template <typename CoilType>
void runSharedWaterCoilRemovalLifecycle(const openstudio::path& idfPath, const std::string& coilLabel, const std::string& expectedControllerAction) {
  const auto scheduleName = "Shared " + coilLabel + " Availability Schedule";
  const auto coilName = "Shared " + coilLabel;
  const auto airLoopName = "Surviving " + coilLabel + " Air Loop";
  const auto plantLoopName = "Removed " + coilLabel + " Plant Loop";
  Model model;
  ScheduleConstant availabilitySchedule(model);
  CoilType coil(model, availabilitySchedule);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(availabilitySchedule.setName(scheduleName));
  ASSERT_TRUE(coil.setName(coilName));
  ASSERT_TRUE(airLoop.setName(airLoopName));
  ASSERT_TRUE(plantLoop.setName(plantLoopName));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>(scheduleName);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilType>(coilName);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>(airLoopName);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>(plantLoopName);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  ASSERT_TRUE(loadedCoil->plantLoop());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedPlantLoop, *loadedCoil->plantLoop());
  EXPECT_TRUE(loadedAirLoop->supplyComponent(loadedCoil->handle()));
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedCoil->handle()));
  EXPECT_EQ(1u, loadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());
  EXPECT_EQ(1u, loadedPlantLoop->demandComponents(CoilType::iddObjectType()).size());
  EXPECT_TRUE(loadedCoil->airInletModelObject());
  EXPECT_TRUE(loadedCoil->airOutletModelObject());
  EXPECT_TRUE(loadedCoil->waterInletModelObject());
  EXPECT_TRUE(loadedCoil->waterOutletModelObject());
  auto loadedController = loadedCoil->controllerWaterCoil();
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedController->action());
  EXPECT_EQ(expectedControllerAction, *loadedController->action());

  std::vector<openstudio::Handle> plantTopologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    plantTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    if (component.handle() != loadedCoil->handle()) {
      plantTopologyHandles.push_back(component.handle());
    }
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto controllerHandle = loadedController->handle();
  const auto coilHandle = loadedCoil->handle();
  const auto airLoopHandle = loadedAirLoop->handle();
  const auto scheduleHandle = loadedSchedule->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(controllerHandle));
  for (const auto& handle : plantTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  EXPECT_TRUE(loadedModel->getObject(coilHandle));
  EXPECT_TRUE(loadedModel->getObject(airLoopHandle));
  EXPECT_TRUE(loadedModel->getObject(scheduleHandle));
  EXPECT_FALSE(loadedCoil->plantLoop());
  EXPECT_FALSE(loadedCoil->waterInletModelObject());
  EXPECT_FALSE(loadedCoil->waterOutletModelObject());
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_TRUE(loadedAirLoop->supplyComponent(coilHandle));
  EXPECT_TRUE(loadedCoil->airInletModelObject());
  EXPECT_TRUE(loadedCoil->airOutletModelObject());
  EXPECT_EQ(1u, loadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());

  EXPECT_TRUE(loadedCoil->removeFromAirLoopHVAC());
  EXPECT_FALSE(loadedCoil->airLoopHVAC());
  EXPECT_TRUE(loadedAirLoop->supplyComponents(CoilType::iddObjectType()).empty());
  auto loadedSupplyOutletNode = loadedAirLoop->supplyOutletNode();
  EXPECT_TRUE(loadedCoil->addToNode(loadedSupplyOutletNode));
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_EQ(1u, loadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilType>(coilName);
  auto reloadedAirLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>(airLoopName);
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedAirLoop);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<ControllerWaterCoil>().empty());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>(scheduleName));
  EXPECT_FALSE(reloadedCoil->plantLoop());
  EXPECT_FALSE(reloadedCoil->waterInletModelObject());
  EXPECT_FALSE(reloadedCoil->waterOutletModelObject());
  ASSERT_TRUE(reloadedCoil->airLoopHVAC());
  EXPECT_EQ(*reloadedAirLoop, *reloadedCoil->airLoopHVAC());
  EXPECT_TRUE(reloadedAirLoop->supplyComponent(reloadedCoil->handle()));
  EXPECT_EQ(1u, reloadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}
}  // namespace

TEST_F(EPModelFixture, PlantLoop_SharedWaterCoilRemovalLifecycle) {
  runSharedWaterCoilRemovalLifecycle<CoilHeatingWater>(
    openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-shared-heating-water-coil-removal.idf"), "Heating Water Coil", "Normal");
}

TEST_F(EPModelFixture, PlantLoop_SharedCoolingCoilRemovalLifecycle) {
  runSharedWaterCoilRemovalLifecycle<CoilCoolingWater>(
    openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-shared-cooling-water-coil-removal.idf"), "Cooling Water Coil", "Reverse");
}

TEST_F(EPModelFixture, PlantLoop_DualLoopHeatExchangerRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-dual-loop-heat-exchanger-removal.idf");

  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop secondaryLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  ASSERT_TRUE(primaryLoop.setName("Removed Primary Heat Exchanger Loop"));
  ASSERT_TRUE(secondaryLoop.setName("Removed Secondary Heat Exchanger Loop"));
  ASSERT_TRUE(heatExchanger.setName("Surviving Dual Loop Heat Exchanger"));
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(secondaryLoop.addDemandBranchForComponent(heatExchanger));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPrimary = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Primary Heat Exchanger Loop");
  auto loadedSecondary = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Secondary Heat Exchanger Loop");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Surviving Dual Loop Heat Exchanger");
  ASSERT_TRUE(loadedPrimary);
  ASSERT_TRUE(loadedSecondary);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedHeatExchanger->plantLoop());
  ASSERT_TRUE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedHeatExchanger->plantLoop());
  EXPECT_EQ(*loadedSecondary, *loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedPrimary->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSecondary->demandComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->demandInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->demandOutletModelObject());

  std::vector<openstudio::Handle> primaryTopologyHandles;
  for (const auto& component : loadedPrimary->supplyComponents()) {
    if (component.handle() != loadedHeatExchanger->handle()) {
      primaryTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedPrimary->demandComponents()) {
    primaryTopologyHandles.push_back(component.handle());
  }
  const auto primaryHandle = loadedPrimary->handle();
  const auto primarySizingHandle = loadedPrimary->sizingPlant().handle();
  EXPECT_FALSE(loadedPrimary->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(primaryHandle));
  EXPECT_FALSE(loadedModel->getObject(primarySizingHandle));
  for (const auto& handle : primaryTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedHeatExchanger->plantLoop());
  EXPECT_FALSE(loadedHeatExchanger->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatExchanger->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*loadedSecondary, *loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSecondary->demandComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatExchanger->demandInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->demandOutletModelObject());

  PlantLoop replacementPrimary(*loadedModel);
  ASSERT_TRUE(replacementPrimary.setName("Replacement Primary Heat Exchanger Loop"));
  ASSERT_TRUE(replacementPrimary.addSupplyBranchForComponent(*loadedHeatExchanger));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto primaryReattachedModel = Model::load(idfPath);
  ASSERT_TRUE(primaryReattachedModel);
  auto reattachedHeatExchanger =
    primaryReattachedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Surviving Dual Loop Heat Exchanger");
  auto reattachedPrimary = primaryReattachedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Primary Heat Exchanger Loop");
  auto originalSecondary = primaryReattachedModel->getConcreteModelObjectByName<PlantLoop>("Removed Secondary Heat Exchanger Loop");
  ASSERT_TRUE(reattachedHeatExchanger);
  ASSERT_TRUE(reattachedPrimary);
  ASSERT_TRUE(originalSecondary);
  ASSERT_TRUE(reattachedHeatExchanger->plantLoop());
  ASSERT_TRUE(reattachedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*reattachedPrimary, *reattachedHeatExchanger->plantLoop());
  EXPECT_EQ(*originalSecondary, *reattachedHeatExchanger->secondaryPlantLoop());

  std::vector<openstudio::Handle> secondaryTopologyHandles;
  for (const auto& component : originalSecondary->supplyComponents()) {
    secondaryTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : originalSecondary->demandComponents()) {
    if (component.handle() != reattachedHeatExchanger->handle()) {
      secondaryTopologyHandles.push_back(component.handle());
    }
  }
  const auto secondaryHandle = originalSecondary->handle();
  const auto secondarySizingHandle = originalSecondary->sizingPlant().handle();
  EXPECT_FALSE(originalSecondary->remove().empty());
  EXPECT_FALSE(primaryReattachedModel->getObject(secondaryHandle));
  EXPECT_FALSE(primaryReattachedModel->getObject(secondarySizingHandle));
  for (const auto& handle : secondaryTopologyHandles) {
    EXPECT_FALSE(primaryReattachedModel->getObject(handle));
  }
  EXPECT_FALSE(reattachedHeatExchanger->secondaryPlantLoop());
  EXPECT_FALSE(reattachedHeatExchanger->demandInletModelObject());
  EXPECT_FALSE(reattachedHeatExchanger->demandOutletModelObject());
  ASSERT_TRUE(reattachedHeatExchanger->plantLoop());
  EXPECT_EQ(*reattachedPrimary, *reattachedHeatExchanger->plantLoop());
  EXPECT_EQ(1u, reattachedPrimary->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(reattachedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(reattachedHeatExchanger->supplyOutletModelObject());

  PlantLoop replacementSecondary(*primaryReattachedModel);
  ASSERT_TRUE(replacementSecondary.setName("Replacement Secondary Heat Exchanger Loop"));
  ASSERT_TRUE(replacementSecondary.addDemandBranchForComponent(*reattachedHeatExchanger));
  ASSERT_TRUE(primaryReattachedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedHeatExchanger = reloadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Surviving Dual Loop Heat Exchanger");
  auto reloadedPrimary = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Primary Heat Exchanger Loop");
  auto reloadedSecondary = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Secondary Heat Exchanger Loop");
  ASSERT_TRUE(reloadedHeatExchanger);
  ASSERT_TRUE(reloadedPrimary);
  ASSERT_TRUE(reloadedSecondary);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Primary Heat Exchanger Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Secondary Heat Exchanger Loop"));
  ASSERT_TRUE(reloadedHeatExchanger->plantLoop());
  ASSERT_TRUE(reloadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*reloadedPrimary, *reloadedHeatExchanger->plantLoop());
  EXPECT_EQ(*reloadedSecondary, *reloadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(1u, reloadedPrimary->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSecondary->demandComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(reloadedHeatExchanger->supplyOutletModelObject());
  EXPECT_TRUE(reloadedHeatExchanger->demandInletModelObject());
  EXPECT_TRUE(reloadedHeatExchanger->demandOutletModelObject());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_LastOwnerHeatExchangerRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-last-owner-heat-exchanger-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  ASSERT_TRUE(plantLoop.setName("Last Owner Heat Exchanger Loop"));
  ASSERT_TRUE(heatExchanger.setName("Owned Last Owner Heat Exchanger"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Heat Exchanger Loop");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Owned Last Owner Heat Exchanger");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedHeatExchanger->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedHeatExchanger->plantLoop());
  EXPECT_FALSE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatExchanger->tertiaryPlantLoop());
  EXPECT_EQ(1u, loadedPlantLoop->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->supplyOutletModelObject());
  EXPECT_FALSE(loadedHeatExchanger->demandInletModelObject());
  EXPECT_FALSE(loadedHeatExchanger->demandOutletModelObject());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    if (component.handle() != loadedHeatExchanger->handle()) {
      topologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto loopHandle = loadedPlantLoop->handle();
  const auto sizingHandle = loadedPlantLoop->sizingPlant().handle();
  const auto heatExchangerHandle = loadedHeatExchanger->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingHandle));
  EXPECT_FALSE(loadedModel->getObject(heatExchangerHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Heat Exchanger Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Owned Last Owner Heat Exchanger"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_ScalarAccessors_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);

  EXPECT_TRUE(plantLoop.setName("Main Plant Loop"));
  EXPECT_EQ("Main Plant Loop", plantLoop.nameString());

  EXPECT_TRUE(plantLoop.setMaximumLoopTemperature(108.5));
  EXPECT_DOUBLE_EQ(108.5, plantLoop.maximumLoopTemperature());

  EXPECT_TRUE(plantLoop.setMinimumLoopTemperature(30.25));
  EXPECT_DOUBLE_EQ(30.25, plantLoop.minimumLoopTemperature());

  EXPECT_TRUE(plantLoop.setPlantLoopVolume(0.45));
  ASSERT_TRUE(plantLoop.plantLoopVolume());
  EXPECT_DOUBLE_EQ(0.45, plantLoop.plantLoopVolume().get());

  plantLoop.autocalculatePlantLoopVolume();
  EXPECT_TRUE(plantLoop.isPlantLoopVolumeAutocalculated());

  EXPECT_TRUE(plantLoop.setCommonPipeSimulation("CommonPipe"));
  EXPECT_EQ("CommonPipe", plantLoop.commonPipeSimulation());
  EXPECT_FALSE(plantLoop.isCommonPipeSimulationDefaulted());
  plantLoop.resetCommonPipeSimulation();
  EXPECT_TRUE(plantLoop.isCommonPipeSimulationDefaulted());
}

TEST_F(EPModelFixture, PlantLoop_CanonicalTopology) {
  Model model;
  PlantLoop plantLoop(model);

  const auto supply = plantLoop.supplyComponents();
  const auto demand = plantLoop.demandComponents();

  ASSERT_EQ(5u, supply.size());
  ASSERT_EQ(5u, demand.size());

  EXPECT_EQ(plantLoop.supplyInletNode(), supply.front().cast<Node>());
  EXPECT_EQ(plantLoop.supplyOutletNode(), supply.back().cast<Node>());
  EXPECT_EQ(plantLoop.demandInletNode(), demand.front().cast<Node>());
  EXPECT_EQ(plantLoop.demandOutletNode(), demand.back().cast<Node>());
}

TEST_F(EPModelFixture, PlantLoop_AvailabilityManagerMutators_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);
  AvailabilityManagerScheduledOn firstManager(model);
  AvailabilityManagerScheduledOn secondManager(model);
  AvailabilityManagerNightCycle nightCycleManager(model);

  EXPECT_TRUE(plantLoop.addAvailabilityManager(firstManager));
  EXPECT_TRUE(plantLoop.addAvailabilityManager(secondManager));
  EXPECT_FALSE(plantLoop.addAvailabilityManager(nightCycleManager));
  ASSERT_EQ(2u, plantLoop.availabilityManagers().size());
  EXPECT_EQ(1u, plantLoop.availabilityManagerPriority(firstManager));
  EXPECT_EQ(2u, plantLoop.availabilityManagerPriority(secondManager));

  EXPECT_TRUE(plantLoop.setAvailabilityManagerPriority(secondManager, 1u));
  EXPECT_EQ(1u, plantLoop.availabilityManagerPriority(secondManager));
  EXPECT_EQ(2u, plantLoop.availabilityManagerPriority(firstManager));

  EXPECT_TRUE(plantLoop.removeAvailabilityManager(firstManager));
  ASSERT_EQ(1u, plantLoop.availabilityManagers().size());
  EXPECT_EQ(secondManager.cast<ModelObject>(), plantLoop.availabilityManagers().front().cast<ModelObject>());

  plantLoop.resetAvailabilityManagers();
  EXPECT_TRUE(plantLoop.availabilityManagers().empty());
}

TEST_F(EPModelFixture, PlantLoop_OperationSchemes_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);
  PlantEquipmentOperationHeatingLoad heating(model);
  PlantEquipmentOperationCoolingLoad cooling(model);
  PlantEquipmentOperationOutdoorDryBulb primary(model);
  ScheduleConstant heatingSchedule(model);
  ScheduleConstant coolingSchedule(model);
  ScheduleConstant primarySchedule(model);
  ScheduleConstant componentSchedule(model);

  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(heating));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(heatingSchedule));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationCoolingLoad(cooling));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationCoolingLoadSchedule(coolingSchedule));
  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationScheme(primary));
  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  ASSERT_TRUE(plantLoop.setComponentSetpointOperationSchemeSchedule(componentSchedule));

  auto heatingResult = plantLoop.plantEquipmentOperationHeatingLoad();
  ASSERT_TRUE(heatingResult);
  EXPECT_EQ(heating.handle(), heatingResult->handle());

  auto coolingResult = plantLoop.plantEquipmentOperationCoolingLoad();
  ASSERT_TRUE(coolingResult);
  EXPECT_EQ(cooling.handle(), coolingResult->handle());

  auto primaryResult = plantLoop.primaryPlantEquipmentOperationScheme();
  ASSERT_TRUE(primaryResult);
  EXPECT_EQ(primary.handle(), primaryResult->handle());

  auto heatingScheduleResult = plantLoop.plantEquipmentOperationHeatingLoadSchedule();
  ASSERT_TRUE(heatingScheduleResult);
  EXPECT_EQ(heatingSchedule.handle(), heatingScheduleResult->handle());

  auto coolingScheduleResult = plantLoop.plantEquipmentOperationCoolingLoadSchedule();
  ASSERT_TRUE(coolingScheduleResult);
  EXPECT_EQ(coolingSchedule.handle(), coolingScheduleResult->handle());

  auto primaryScheduleResult = plantLoop.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());

  auto componentScheduleResult = plantLoop.componentSetpointOperationSchemeSchedule();
  ASSERT_TRUE(componentScheduleResult);
  EXPECT_EQ(componentSchedule.handle(), componentScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantLoop_PrimaryOperationScheduleResetIsIsolated) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant coolingSchedule(model);
  ScheduleConstant primarySchedule(model);

  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationCoolingLoadSchedule(coolingSchedule));
  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  ASSERT_TRUE(plantLoop.plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_TRUE(plantLoop.primaryPlantEquipmentOperationSchemeSchedule());

  plantLoop.resetPrimaryPlantEquipmentOperationSchemeSchedule();

  ASSERT_TRUE(plantLoop.plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(coolingSchedule, *plantLoop.plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationSchemeSchedule());
}

TEST_F(EPModelFixture, PlantLoop_HeatingScheduleCanExistWithoutHeatingScheme) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant heatingSchedule(model);

  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(heatingSchedule));
  EXPECT_FALSE(plantLoop.plantEquipmentOperationHeatingLoad());

  auto heatingScheduleResult = plantLoop.plantEquipmentOperationHeatingLoadSchedule();
  ASSERT_TRUE(heatingScheduleResult);
  EXPECT_EQ(heatingSchedule.handle(), heatingScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantLoop_PrimaryScheduleCanExistWithoutPrimaryScheme) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant primarySchedule(model);

  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationScheme());

  auto primaryScheduleResult = plantLoop.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantLoop_AddRemoveSupplyBranchForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop.handle(), pipe.plantLoop()->handle());
  ASSERT_TRUE(pipe.loop());
  EXPECT_EQ(plantLoop.handle(), pipe.loop()->handle());
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  EXPECT_TRUE(plantLoop.removeSupplyBranchWithComponent(pipe));
  EXPECT_FALSE(pipe.plantLoop());
  EXPECT_FALSE(pipe.loop());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
}

TEST_F(EPModelFixture, PlantLoop_AddRemoveDemandBranchForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop.handle(), pipe.plantLoop()->handle());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  EXPECT_TRUE(plantLoop.removeDemandBranchWithComponent(pipe));
  EXPECT_FALSE(pipe.plantLoop());
  EXPECT_FALSE(pipe.loop());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, PlantLoop_AddRemoveDemandBranchForWaterToAirComponent) {
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater coil(model);

  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil.plantLoop()->handle());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  EXPECT_TRUE(plantLoop.removeDemandBranchWithComponent(coil));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, PlantLoop_RemoveHeatingWaterCoilRemovesOnlyItsParallelDemandBranch) {
  Model model;
  PlantLoop plantLoop(model);
  AirLoopHVAC airLoop(model);
  PipeAdiabatic siblingPipe(model);
  CoilHeatingWater coil(model);

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(siblingPipe));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  const auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);

  auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();
  ASSERT_TRUE(plantLoopImpl);
  const auto equipmentBranchesBefore = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(2u, equipmentBranchesBefore.size());
  const auto targetBranchIt = std::ranges::find_if(equipmentBranchesBefore, [&](const auto& branch) {
    const auto components = branch.components();
    return components.size() == 1u && components.front() == coil.cast<ModelObject>();
  });
  ASSERT_NE(equipmentBranchesBefore.end(), targetBranchIt);
  const auto targetBranchHandle = targetBranchIt->handle();
  const auto siblingBranchIt = std::ranges::find_if(equipmentBranchesBefore, [&](const auto& branch) {
    const auto components = branch.components();
    return components.size() == 1u && components.front() == siblingPipe.cast<ModelObject>();
  });
  ASSERT_NE(equipmentBranchesBefore.end(), siblingBranchIt);
  const auto siblingBranchHandle = siblingBranchIt->handle();

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(coil));

  EXPECT_FALSE(coil.plantLoop());
  EXPECT_TRUE(coil.airLoopHVAC());
  EXPECT_FALSE(model.getObject(controller->handle()));
  EXPECT_FALSE(model.getObject(targetBranchHandle));
  EXPECT_TRUE(model.getObject(siblingBranchHandle));
  const auto equipmentBranchesAfter = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, equipmentBranchesAfter.size());
  EXPECT_EQ(siblingBranchHandle, equipmentBranchesAfter.front().handle());
  EXPECT_EQ(1u, plantLoop.demandSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, plantLoop.demandMixer().inletModelObjects().size());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
}

TEST_F(EPModelFixture, PlantLoop_RemoveHeatingWaterCoilClearsTheDefaultDemandBranch) {
  Model model;
  PlantLoop plantLoop(model);
  AirLoopHVAC airLoop(model);
  CoilHeatingWater coil(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  const auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());

  auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();
  ASSERT_TRUE(plantLoopImpl);
  const auto equipmentBranchesBefore = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, equipmentBranchesBefore.size());
  const auto defaultBranchHandle = equipmentBranchesBefore.front().handle();

  ASSERT_TRUE(plantLoop.removeDemandBranchWithComponent(coil));

  EXPECT_TRUE(model.getObject(coil.handle()));
  EXPECT_FALSE(coil.plantLoop());
  EXPECT_TRUE(coil.airLoopHVAC());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());
  EXPECT_FALSE(model.getObject(controller->handle()));
  EXPECT_FALSE(coil.controllerWaterCoil());
  const auto equipmentBranchesAfter = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, equipmentBranchesAfter.size());
  EXPECT_EQ(defaultBranchHandle, equipmentBranchesAfter.front().handle());
  EXPECT_TRUE(equipmentBranchesAfter.front().components().empty());
  EXPECT_EQ(1u, plantLoop.demandSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, plantLoop.demandMixer().inletModelObjects().size());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
}

TEST_F(EPModelFixture, PlantLoop_RemoveHeatingWaterCoilRejectsMultiComponentBranchBeforeMutation) {
  Model model;
  PlantLoop plantLoop(model);
  AirLoopHVAC airLoop(model);
  CoilHeatingWater coil(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  const auto controller = coil.controllerWaterCoil();
  ASSERT_TRUE(controller);
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());

  auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();
  ASSERT_TRUE(plantLoopImpl);
  auto equipmentBranches = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, equipmentBranches.size());
  auto targetBranch = equipmentBranches.front();
  PipeAdiabatic competingPipe(model);
  ASSERT_TRUE(
    targetBranch.getImpl<detail::Branch_Impl>()->appendComponent(competingPipe.cast<ModelObject>(), "Competing Pipe Inlet", "Competing Pipe Outlet"));
  ASSERT_EQ(2u, targetBranch.components().size());

  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }
  const auto branchComponentsBefore = targetBranch.components();
  const auto listedBranchesBefore = plantLoopImpl->demandBranchList().branches();
  const auto splitterOutletsBefore = plantLoop.demandSplitter().outletModelObjects();
  const auto mixerInletsBefore = plantLoop.demandMixer().inletModelObjects();
  const auto waterInletHandle = coil.waterInletModelObject()->handle();
  const auto waterOutletHandle = coil.waterOutletModelObject()->handle();

  EXPECT_FALSE(plantLoop.removeDemandBranchWithComponent(coil));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(branchComponentsBefore, targetBranch.components());
  EXPECT_EQ(listedBranchesBefore, plantLoopImpl->demandBranchList().branches());
  EXPECT_EQ(splitterOutletsBefore, plantLoop.demandSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, plantLoop.demandMixer().inletModelObjects());
  ASSERT_TRUE(coil.waterInletModelObject());
  ASSERT_TRUE(coil.waterOutletModelObject());
  EXPECT_EQ(waterInletHandle, coil.waterInletModelObject()->handle());
  EXPECT_EQ(waterOutletHandle, coil.waterOutletModelObject()->handle());
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil.plantLoop()->handle());
  ASSERT_TRUE(model.getObject(controller->handle()));
  ASSERT_TRUE(coil.controllerWaterCoil());
  EXPECT_EQ(controller->handle(), coil.controllerWaterCoil()->handle());
}

TEST_F(EPModelFixture, PlantLoop_SupplyComponents_IncludeMultipleEquipmentBranchesInOrder) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic firstPipe(model);
  PipeAdiabatic secondPipe(model);

  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(firstPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(secondPipe));

  const auto supply = plantLoop.supplyComponents();
  ASSERT_EQ(10u, supply.size());

  const auto firstPipeIt = std::find(supply.begin(), supply.end(), firstPipe.cast<ModelObject>());
  const auto secondPipeIt = std::find(supply.begin(), supply.end(), secondPipe.cast<ModelObject>());
  const auto mixerIt = std::find(supply.begin(), supply.end(), plantLoop.supplyMixer().cast<ModelObject>());

  ASSERT_NE(supply.end(), firstPipeIt);
  ASSERT_NE(supply.end(), secondPipeIt);
  ASSERT_NE(supply.end(), mixerIt);

  EXPECT_LT(firstPipeIt, secondPipeIt);
  EXPECT_LT(secondPipeIt, mixerIt);
}

TEST_F(EPModelFixture, PlantLoop_Canonicalize_TwoBranchListsBecomeParallelEquipmentBranches) {
  Model model;
  PlantLoop plantLoop(model);

  auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();

  auto supplyBranchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(supplyBranchList);
  auto supplyBranchListImpl = supplyBranchList->getImpl<detail::BranchList_Impl>();

  auto supplyBranches = supplyBranchList->branches();
  ASSERT_EQ(3u, supplyBranches.size());
  ASSERT_TRUE(supplyBranchListImpl->removeBranch(supplyBranches.front()));
  ASSERT_TRUE(supplyBranchListImpl->removeBranch(supplyBranches.back()));

  Branch secondSupplyEquipmentBranch(model);
  ASSERT_TRUE(secondSupplyEquipmentBranch.setName("Recovered Supply Branch 2"));
  ASSERT_TRUE(supplyBranchListImpl->addBranch(secondSupplyEquipmentBranch));

  auto demandBranchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(demandBranchList);
  auto demandBranchListImpl = demandBranchList->getImpl<detail::BranchList_Impl>();

  auto demandBranches = demandBranchList->branches();
  ASSERT_EQ(3u, demandBranches.size());
  ASSERT_TRUE(demandBranchListImpl->removeBranch(demandBranches.front()));
  ASSERT_TRUE(demandBranchListImpl->removeBranch(demandBranches.back()));

  Branch secondDemandEquipmentBranch(model);
  ASSERT_TRUE(secondDemandEquipmentBranch.setName("Recovered Demand Branch 2"));
  ASSERT_TRUE(demandBranchListImpl->addBranch(secondDemandEquipmentBranch));

  detail::LoadContext context{model, SanitizationPolicy::Repair, SanitizationReport{}, {}};
  plantLoopImpl->canonicalize(context);

  EXPECT_EQ(4u, plantLoopImpl->supplyBranchList().branches().size());
  EXPECT_EQ(2u, plantLoopImpl->supplyEquipmentBranches().size());
  EXPECT_EQ(6u, plantLoop.supplyComponents().size());

  EXPECT_EQ(4u, plantLoopImpl->demandBranchList().branches().size());
  EXPECT_EQ(2u, plantLoopImpl->demandEquipmentBranches().size());
  EXPECT_EQ(6u, plantLoop.demandComponents().size());

  EXPECT_EQ(2u, plantLoop.supplySplitter().outletModelObjects().size());
  EXPECT_EQ(2u, plantLoop.supplyMixer().inletModelObjects().size());
  EXPECT_EQ(2u, plantLoop.demandSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, plantLoop.demandMixer().inletModelObjects().size());
}

TEST_F(EPModelFixture, PlantLoop_Canonicalize_RepairsSetpointAndDeduplicatesSizingPlant) {
  Model model;
  PlantLoop plantLoop(model);

  ASSERT_TRUE(plantLoop.setString(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, "Missing Setpoint Node"));

  SizingPlant duplicateSizingPlant(model, plantLoop);

  unsigned attachedSizingPlantCount = 0u;
  for (const auto& sizingPlant : model.getConcreteModelObjects<SizingPlant>()) {
    auto sizingPlantLoop = sizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
    if (sizingPlantLoop && (*sizingPlantLoop == plantLoop)) {
      ++attachedSizingPlantCount;
    }
  }
  EXPECT_EQ(2u, attachedSizingPlantCount);

  auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(plantLoop.supplyOutletNode(), plantLoop.loopTemperatureSetpointNode());

  attachedSizingPlantCount = 0u;
  for (const auto& sizingPlant : model.getConcreteModelObjects<SizingPlant>()) {
    auto sizingPlantLoop = sizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
    if (sizingPlantLoop && (*sizingPlantLoop == plantLoop)) {
      ++attachedSizingPlantCount;
    }
  }
  EXPECT_EQ(1u, attachedSizingPlantCount);
}

TEST_F(EPModelFixture, PlantLoop_AddDemandBranchRejectsTertiaryForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_FALSE(plantLoop.addDemandBranchForComponent(pipe, true));
  EXPECT_FALSE(pipe.plantLoop());
}
