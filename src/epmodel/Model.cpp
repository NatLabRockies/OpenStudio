/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Model.hpp"
#include "Model_Impl.hpp"

#include "AirLoopHVACReturnPath_Impl.hpp"
#include "AirLoopHVACSupplyPath_Impl.hpp"
#include "AirLoopHVACControllerList_Impl.hpp"
#include "AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "AirLoopHVACZoneMixer_Impl.hpp"
#include "AirLoopHVACZoneSplitter_Impl.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "AvailabilityManagerAssignmentList_Impl.hpp"
#include "AvailabilityManagerNightCycle_Impl.hpp"
#include "AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"
#include "Branch_Impl.hpp"
#include "BranchList_Impl.hpp"
#include "CoilCoolingDXSingleSpeed_Impl.hpp"
#include "CoilHeatingGas_Impl.hpp"
#include "CoilSystemCoolingDX_Impl.hpp"
#include "ControllerMechanicalVentilation_Impl.hpp"
#include "ControllerOutdoorAir_Impl.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "FanConstantVolume_Impl.hpp"
#include "ModelObject_Impl.hpp"
#include "Node_Impl.hpp"
#include "NodeList_Impl.hpp"
#include "OutdoorAirMixer_Impl.hpp"
#include "SizingZone_Impl.hpp"
#include "Space_Impl.hpp"
#include "SetpointManagerMixedAir_Impl.hpp"
#include "SetpointManagerScheduled_Impl.hpp"
#include "SetpointManagerSingleZoneReheat_Impl.hpp"
#include "ThermalZone_Impl.hpp"
#include "ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>

#include "../utilities/core/Filesystem.hpp"
#include "../utilities/idf/IdfFile.hpp"
#include "../utilities/idf/IdfObject.hpp"

#include <sstream>

namespace openstudio {
namespace epmodel {

  void SanitizationReport::log() const {
    static constexpr const char* prefix = "[canonicalize] ";
    for (const auto& message : messages) {
      if (message.rfind("ERROR: ", 0) == 0) {
        LOG_FREE(Error, "openstudio.epmodel.Model", prefix << message.substr(7));
      } else if (message.rfind("WARN: ", 0) == 0) {
        LOG_FREE(Warn, "openstudio.epmodel.Model", prefix << message.substr(6));
      } else if (message.rfind("INFO: ", 0) == 0) {
        LOG_FREE(Info, "openstudio.epmodel.Model", prefix << message.substr(6));
      } else {
        LOG_FREE(Info, "openstudio.epmodel.Model", prefix << message);
      }
    }
  }

  // Creates an empty epmodel Workspace with the EnergyPlus schema and a Version object.
  // Use this when building an epmodel programmatically from scratch.
  Model::Model() : Workspace(std::shared_ptr<detail::Model_Impl>(new detail::Model_Impl())) {
    this->addVersionObject();
  }

  // Preferred import path for EnergyPlus IDF content.
  // This path calls Model_Impl::createObject(const IdfObject&, ...), which selects concrete
  // epmodel impl types by IddObjectType (for example AirLoopHVAC -> AirLoopHVAC_Impl).
  // The stored pointer type is WorkspaceObject_Impl, but the runtime type remains concrete.
  // After object ingestion, canonicalization runs with Repair policy.
  Model::Model(const openstudio::IdfFile& idfFile) : Workspace(std::shared_ptr<detail::Model_Impl>(new detail::Model_Impl(idfFile))) {
    openstudio::detail::WorkspaceObject_ImplPtrVector objectImplPtrs;
    if (auto vo = idfFile.versionObject()) {
      objectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(*vo, true));
    }
    for (const IdfObject& idfObject : idfFile.objects()) {
      objectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(idfObject, true));
    }
    getImpl<detail::Model_Impl>()->addObjects(objectImplPtrs);
    canonicalize(SanitizationPolicy::Repair);
  }

  // Converts/clones an existing Workspace into an epmodel::Model.
  // This path calls Model_Impl::createObject(const shared_ptr<WorkspaceObject_Impl>&, ...),
  // which preserves concrete runtime type when the source Workspace already contains epmodel
  // impl objects. If the source is a generic Workspace, concrete casts fail and the fallback
  // is ModelObject_Impl, so concrete epmodel queries may return fewer objects.
  // After cloning, canonicalization runs with Repair policy.
  Model::Model(const openstudio::Workspace& workspace)
    : Workspace(std::shared_ptr<detail::Model_Impl>(new detail::Model_Impl(*(workspace.getImpl<openstudio::detail::Workspace_Impl>()), true))) {
    openstudio::detail::WorkspaceObject_ImplPtrVector newObjectImplPtrs;
    HandleMap oldNewHandleMap;
    if (auto vo = workspace.versionObject()) {
      newObjectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(vo->getImpl<openstudio::detail::WorkspaceObject_Impl>(), true));
    }
    for (const WorkspaceObject& object : workspace.getImpl<openstudio::detail::Workspace_Impl>()->objects()) {
      newObjectImplPtrs.push_back(getImpl<detail::Model_Impl>()->createObject(object.getImpl<openstudio::detail::WorkspaceObject_Impl>(), true));
    }
    getImpl<detail::Model_Impl>()->addClones(newObjectImplPtrs, oldNewHandleMap, true);
    canonicalize(SanitizationPolicy::Repair);
  }

  // Convenience loader for disk-based IDF files.
  // Internally this delegates to the IdfFile constructor above (typed object materialization
  // plus canonicalization with Repair policy).
  boost::optional<Model> Model::load(const openstudio::path& idfPath) {
    if (!openstudio::filesystem::is_regular_file(idfPath)) {
      LOG_FREE(Warn, "openstudio.epmodel.Model", "Path is not a valid file: " << idfPath);
      return boost::none;
    }

    auto idfFile = openstudio::IdfFile::load(idfPath, openstudio::IddFileType::EnergyPlus);
    if (!idfFile) {
      LOG_FREE(Warn, "openstudio.epmodel.Model", "Failed to load idf at " << idfPath);
      return boost::none;
    }

    return Model(*idfFile);
  }

  // Internal bridge used when wrapping an already-constructed Model_Impl.
  Model::Model(std::shared_ptr<openstudio::epmodel::detail::Model_Impl> impl) : Workspace(std::move(impl)) {}

  SanitizationReport Model::canonicalize(SanitizationPolicy policy) {
    detail::LoadContext context{*this, policy, SanitizationReport{}, {}};
    if (policy == SanitizationPolicy::None) {
      return context.report;
    }

    // Fixed-point pass over all objects:
    // 1. One-time execution per object handle is enforced via context.visited.
    // 2. Order is intentionally not relied upon.
    // 3. Newly created objects from canonicalizers are picked up in later passes.
    while (true) {
      const auto visitedBefore = context.visited.size();
      for (const auto& object : this->objects()) {
        if (auto impl = object.getImpl<detail::ModelObject_Impl>()) {
          impl->canonicalize(context);
        }
      }
      if (context.visited.size() == visitedBefore) {
        break;
      }
    }

    std::ostringstream summary;
    summary << "Sanitization complete: infos=" << context.report.infoCount << ", warnings=" << context.report.warningCount
            << ", errors=" << context.report.errorCount << ".";
    detail::addLoadInfo(context, summary.str());
    return context.report;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    void addLoadInfo(LoadContext& ctx, const std::string& message) {
      ++ctx.report.infoCount;
      ctx.report.messages.push_back("INFO: " + message);
      LOG_FREE(Info, "openstudio.epmodel.Model", message);
    }

    void addLoadWarning(LoadContext& ctx, const std::string& message) {
      ++ctx.report.warningCount;
      ctx.report.messages.push_back("WARN: " + message);
      LOG_FREE(Warn, "openstudio.epmodel.Model", message);
    }

    void addLoadError(LoadContext& ctx, const std::string& message) {
      ++ctx.report.errorCount;
      ctx.report.messages.push_back("ERROR: " + message);
      LOG_FREE(Error, "openstudio.epmodel.Model", message);
    }

    Model_Impl::Model_Impl() : Workspace_Impl(StrictnessLevel::Draft, IddFileType::EnergyPlus) {
      // careful not to call anything that calls shared_from_this here, this is not yet constructed
    }

    Model_Impl::Model_Impl(const IdfFile& idfFile) : Workspace_Impl(idfFile, StrictnessLevel(StrictnessLevel::Draft)) {
      // careful not to call anything that calls shared_from_this here, this is not yet constructed
      if (iddFileType() != IddFileType::EnergyPlus) {
        LOG_AND_THROW("epmodel::Model must be constructed with the EnergyPlus Idd as the underlying data schema. (Attempted construction "
                      << "from IdfFile with IddFileType " << idfFile.iddFileType().valueDescription() << ".)");
      }
    }

    Model_Impl::Model_Impl(const openstudio::detail::Workspace_Impl& workspace, bool keepHandles)
      : openstudio::detail::Workspace_Impl(workspace, keepHandles) {
      // careful not to call anything that calls shared_from_this here, this is not yet constructed
      if (iddFileType() != IddFileType::EnergyPlus) {
        LOG_AND_THROW("epmodel::Model must be constructed with the EnergyPlus Idd as the underlying data schema. (Attempted construction "
                      << "from Workspace with IddFileType " << workspace.iddFileType().valueDescription() << ".)");
      }
    }

    Model_Impl::Model_Impl(const Model_Impl& other, bool keepHandles) : Workspace_Impl(other, keepHandles) {}

    Model_Impl::Model_Impl(const Model_Impl& other, const std::vector<Handle>& hs, bool keepHandles, StrictnessLevel level)
      : Workspace_Impl(other, hs, keepHandles, level) {}

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> Model_Impl::createObject(const IdfObject& object, bool keepHandle) {
      const auto type = object.iddObject().type();
      if (type == IddObjectType::AirLoopHVAC) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVAC_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_SupplyPath) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPath_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ReturnPath) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPath_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_OutdoorAirSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACOutdoorAirSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ControllerList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACControllerList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ZoneSplitter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneSplitter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ZoneMixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManagerAssignmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerAssignmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_NightCycle) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AvailabilityManagerNightCycle_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Branch) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Branch_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::BranchList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BranchList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Fuel) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGas_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_MixedAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerMixedAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_Scheduled) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerScheduled_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::SetpointManager_SingleZone_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SetpointManagerSingleZoneReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeNoReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Node_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::NodeList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new NodeList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::OutdoorAir_Mixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutdoorAirMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_OutdoorAirSystem_EquipmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACOutdoorAirSystemEquipmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Controller_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Controller_MechanicalVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerMechanicalVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DesignSpecification_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::DesignSpecification_OutdoorAir_SpaceList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationOutdoorAirSpaceList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Space) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Space_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Sizing_Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_EquipmentConnections) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentConnections_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_EquipmentList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ZoneHVAC_AirDistributionUnit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACAirDistributionUnit_Impl(object, this, keepHandle));
      }
      return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(object, this, keepHandle));
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> Model_Impl::createObject(const IdfObject& object, bool keepHandle, bool isTransient) {
      auto result = createObject(object, keepHandle);
      result->setTransient(isTransient);
      return result;
    }

    std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>
      Model_Impl::createObject(const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& originalObjectImplPtr, bool keepHandle) {

      if (auto airLoop = std::dynamic_pointer_cast<AirLoopHVAC_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVAC_Impl(*airLoop, this, keepHandle));
      }
      if (auto supplyPath = std::dynamic_pointer_cast<AirLoopHVACSupplyPath_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPath_Impl(*supplyPath, this, keepHandle));
      }
      if (auto returnPath = std::dynamic_pointer_cast<AirLoopHVACReturnPath_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPath_Impl(*returnPath, this, keepHandle));
      }
      if (auto outdoorAirSystem = std::dynamic_pointer_cast<AirLoopHVACOutdoorAirSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACOutdoorAirSystem_Impl(*outdoorAirSystem, this, keepHandle));
      }
      if (auto controllerList = std::dynamic_pointer_cast<AirLoopHVACControllerList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACControllerList_Impl(*controllerList, this, keepHandle));
      }
      if (auto zoneSplitter = std::dynamic_pointer_cast<AirLoopHVACZoneSplitter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneSplitter_Impl(*zoneSplitter, this, keepHandle));
      }
      if (auto zoneMixer = std::dynamic_pointer_cast<AirLoopHVACZoneMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACZoneMixer_Impl(*zoneMixer, this, keepHandle));
      }
      if (auto availabilityManagerAssignmentList = std::dynamic_pointer_cast<AvailabilityManagerAssignmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerAssignmentList_Impl(*availabilityManagerAssignmentList, this, keepHandle));
      }
      if (auto availabilityManagerNightCycle = std::dynamic_pointer_cast<AvailabilityManagerNightCycle_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerNightCycle_Impl(*availabilityManagerNightCycle, this, keepHandle));
      }
      if (auto branch = std::dynamic_pointer_cast<Branch_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Branch_Impl(*branch, this, keepHandle));
      }
      if (auto branchList = std::dynamic_pointer_cast<BranchList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BranchList_Impl(*branchList, this, keepHandle));
      }
      if (auto fan = std::dynamic_pointer_cast<FanConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanConstantVolume_Impl(*fan, this, keepHandle));
      }
      if (auto coilCoolingDXSingleSpeed = std::dynamic_pointer_cast<CoilCoolingDXSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXSingleSpeed_Impl(*coilCoolingDXSingleSpeed, this, keepHandle));
      }
      if (auto coilHeatingFuel = std::dynamic_pointer_cast<CoilHeatingGas_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGas_Impl(*coilHeatingFuel, this, keepHandle));
      }
      if (auto coilSystemCoolingDX = std::dynamic_pointer_cast<CoilSystemCoolingDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDX_Impl(*coilSystemCoolingDX, this, keepHandle));
      }
      if (auto setpointManagerMixedAir = std::dynamic_pointer_cast<SetpointManagerMixedAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerMixedAir_Impl(*setpointManagerMixedAir, this, keepHandle));
      }
      if (auto setpointManagerScheduled = std::dynamic_pointer_cast<SetpointManagerScheduled_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerScheduled_Impl(*setpointManagerScheduled, this, keepHandle));
      }
      if (auto setpointManagerSingleZoneReheat = std::dynamic_pointer_cast<SetpointManagerSingleZoneReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new SetpointManagerSingleZoneReheat_Impl(*setpointManagerSingleZoneReheat, this, keepHandle));
      }
      if (auto airTerminal = std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeNoReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeNoReheat_Impl(*airTerminal, this, keepHandle));
      }
      if (auto node = std::dynamic_pointer_cast<Node_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Node_Impl(*node, this, keepHandle));
      }
      if (auto nodeList = std::dynamic_pointer_cast<NodeList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new NodeList_Impl(*nodeList, this, keepHandle));
      }
      if (auto outdoorAirMixer = std::dynamic_pointer_cast<OutdoorAirMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new OutdoorAirMixer_Impl(*outdoorAirMixer, this, keepHandle));
      }
      if (auto outdoorAirEquipmentList = std::dynamic_pointer_cast<AirLoopHVACOutdoorAirSystemEquipmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACOutdoorAirSystemEquipmentList_Impl(*outdoorAirEquipmentList, this, keepHandle));
      }
      if (auto outdoorAirController = std::dynamic_pointer_cast<ControllerOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ControllerOutdoorAir_Impl(*outdoorAirController, this, keepHandle));
      }
      if (auto mechanicalVentilationController = std::dynamic_pointer_cast<ControllerMechanicalVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ControllerMechanicalVentilation_Impl(*mechanicalVentilationController, this, keepHandle));
      }
      if (auto dsoa = std::dynamic_pointer_cast<DesignSpecificationOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new DesignSpecificationOutdoorAir_Impl(*dsoa, this, keepHandle));
      }
      if (auto dsoaSpaceList = std::dynamic_pointer_cast<DesignSpecificationOutdoorAirSpaceList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new DesignSpecificationOutdoorAirSpaceList_Impl(*dsoaSpaceList, this, keepHandle));
      }
      if (auto zone = std::dynamic_pointer_cast<ThermalZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ThermalZone_Impl(*zone, this, keepHandle));
      }
      if (auto space = std::dynamic_pointer_cast<Space_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Space_Impl(*space, this, keepHandle));
      }
      if (auto sizingZone = std::dynamic_pointer_cast<SizingZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new SizingZone_Impl(*sizingZone, this, keepHandle));
      }
      if (auto zoneConnections = std::dynamic_pointer_cast<ZoneHVACEquipmentConnections_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentConnections_Impl(*zoneConnections, this, keepHandle));
      }
      if (auto zoneEquipmentList = std::dynamic_pointer_cast<ZoneHVACEquipmentList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ZoneHVACEquipmentList_Impl(*zoneEquipmentList, this, keepHandle));
      }
      if (auto airDistributionUnit = std::dynamic_pointer_cast<ZoneHVACAirDistributionUnit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ZoneHVACAirDistributionUnit_Impl(*airDistributionUnit, this, keepHandle));
      }
      return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(*originalObjectImplPtr, this, keepHandle));
    }

    openstudio::epmodel::Model Model_Impl::model() const {
      return Model(std::dynamic_pointer_cast<Model_Impl>(std::const_pointer_cast<openstudio::detail::Workspace_Impl>(this->shared_from_this())));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
