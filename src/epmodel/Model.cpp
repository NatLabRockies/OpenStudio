/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Model.hpp"
#include "Model_Impl.hpp"

#include "ModelObject/AirLoopHVACReturnPath_Impl.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "Mixer/AirTerminalDualDuctConstantVolume_Impl.hpp"
#include "Mixer/AirTerminalDualDuctVAV_Impl.hpp"
#include "Mixer/AirTerminalDualDuctVAVOutdoorAir_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"
#include "ModelObject/AirTerminalSingleDuctUserDefined_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVNoReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"
#include "ModelObject/AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "AvailabilityManagerAssignmentList_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerNightCycle_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerDifferentialThermostat_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOn_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerHighTemperatureTurnOff_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerLowTemperatureTurnOff_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerHybridVentilation_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerNightVentilation_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerOptimumStart_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOff_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"
#include "StraightComponent/BoilerHotWater_Impl.hpp"
#include "StraightComponent/BoilerSteam_Impl.hpp"
#include "WaterToWaterComponent/ChillerAbsorption_Impl.hpp"
#include "WaterToWaterComponent/ChillerAbsorptionIndirect_Impl.hpp"
#include "ModelObject/ChillerCombustionTurbine_Impl.hpp"
#include "ModelObject/ChillerHeaterAbsorptionDirectFired_Impl.hpp"
#include "ParentObject/ChillerHeaterPerformanceElectricEIR_Impl.hpp"
#include "ParentObject/CoilPerformanceDXCooling_Impl.hpp"
#include "ModelObject/ChillerConstantCOP_Impl.hpp"
#include "ModelObject/ChillerEngineDriven_Impl.hpp"
#include "ModelObject/ChillerElectric_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricReformulatedEIR_Impl.hpp"
#include "WaterToWaterComponent/ChillerElectricASHRAE205_Impl.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ParentObject/Building_Impl.hpp"
#include "BranchList_Impl.hpp"
#include "StraightComponent/CoilCoolingDXMultiSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXSingleSpeedThermalStorage_Impl.hpp"
#include "StraightComponent/CoilCoolingDXVariableSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXTwoSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitSpeed_Impl.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"
#include "StraightComponent/CoilHeatingDXMultiSpeed_Impl.hpp"
#include "StraightComponent/CoilHeatingDXSingleSpeed_Impl.hpp"
#include "StraightComponent/CoilHeatingDXVariableSpeed_Impl.hpp"
#include "StraightComponent/CoilHeatingDesuperheater_Impl.hpp"
#include "StraightComponent/CoilWaterHeatingDesuperheater_Impl.hpp"
#include "StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "StraightComponent/CoilHeatingElectricMultiStage_Impl.hpp"
#include "StraightComponent/CoilHeatingGasMultiStage_Impl.hpp"
#include "ModelObject/CoilHeatingSteam_Impl.hpp"
#include "ModelObject/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"
#include "CoilHeatingGas_Impl.hpp"
#include "ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted_Impl.hpp"
#include "ControllerMechanicalVentilation_Impl.hpp"
#include "ControllerOutdoorAir_Impl.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "FanConstantVolume_Impl.hpp"
#include "ModelObject_Impl.hpp"
#include "StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl.hpp"
#include "HVACComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"
#include "HVACComponent/CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "HVACComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"
#include "HVACComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "HVACComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"
#include "WaterToAirComponent/CoilUserDefined_Impl.hpp"
#include "ModelObject/CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl.hpp"
#include "ModelObject/CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl.hpp"
#include "ModelObject/CoilCoolingWaterDetailedGeometry_Impl.hpp"
#include "ModelObject/CoilDXASHRAE205Performance_Impl.hpp"
#include "WaterToWaterComponent/CentralHeatPumpSystem_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentConstantPressureDrop_Impl.hpp"
#include "ModelObject/CeilingAdiabatic_Impl.hpp"
#include "ModelObject/CeilingInterzone_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentDuct_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionDuctSizing_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionDuctViewFactors_Impl.hpp"
#include "AirflowNetworkLinkage/AirflowNetworkDistributionLinkage_Impl.hpp"
#include "AirflowNetworkNode/AirflowNetworkDistributionNode_Impl.hpp"
#include "ModelObject/AirflowNetworkIntraZoneNode_Impl.hpp"
#include "ModelObject/AirflowNetworkIntraZoneLinkage_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneExternalNode_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneZone_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSpecifiedFlowRate_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneReferenceCrackConditions_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSurface_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSurfaceCrack_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentDetailedOpening_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentHorizontalOpening_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentSimpleOpening_Impl.hpp"
#include "ModelObject/AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl.hpp"
#include "ModelObject/AirflowNetworkOccupantVentilationControl_Impl.hpp"
#include "ParentObject/AirflowNetworkSimulationControl_Impl.hpp"
#include "ModelObject/AirflowNetworkZoneControlPressureController_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentFan_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentHeatExchanger_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentLeak_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentLeakageRatio_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentOutdoorAirFlow_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentReliefAirFlow_Impl.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentTerminalUnit_Impl.hpp"
#include "ModelObject/AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACExhaustSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACMixer_Impl.hpp"
#include "ModelObject/AirLoopHVACSplitter_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryFurnaceHeatCool_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryFurnaceHeatOnly_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryHeatOnly_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryHeatCool_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir_Impl.hpp"
#include "ModelObject/AirLoopHVACUnitaryHeatPumpWaterToAir_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl.hpp"
#include "ZoneHVACComponent/AirLoopHVACUnitarySystem_Impl.hpp"
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
      if (type == IddObjectType::AirLoopHVAC_ReturnPlenum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPlenum_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_SupplyPlenum) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPlenum_Impl(object, this, keepHandle));
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
      if (type == IddObjectType::AvailabilityManager_DifferentialThermostat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerDifferentialThermostat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_HighTemperatureTurnOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_HighTemperatureTurnOn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_LowTemperatureTurnOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerLowTemperatureTurnOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_LowTemperatureTurnOn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerLowTemperatureTurnOn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_HybridVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHybridVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_NightVentilation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerNightVentilation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_OptimumStart) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerOptimumStart_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_ScheduledOff) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerScheduledOff_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AvailabilityManager_ScheduledOn) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerScheduledOn_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Branch) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Branch_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::BranchList) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BranchList_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Building) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Building_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Boiler_HotWater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerHotWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Boiler_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Absorption) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerAbsorption_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Absorption_Indirect) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerAbsorptionIndirect_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_CombustionTurbine) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerCombustionTurbine_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ChillerHeater_Absorption_DirectFired) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterAbsorptionDirectFired_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::ChillerHeaterPerformance_Electric_EIR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterPerformanceElectricEIR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_ConstantCOP) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerConstantCOP_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_EngineDriven) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerEngineDriven_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric_EIR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricEIR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric_ReformulatedEIR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricReformulatedEIR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Chiller_Electric_ASHRAE205) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricASHRAE205_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Fan_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_SingleSpeed_ThermalStorage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXSingleSpeedThermalStorage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_MultiSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXMultiSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_TwoSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXTwoSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_TwoStageWithHumidityControlMode) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXTwoStageWithHumidityControlMode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilPerformance_DX_Cooling) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilPerformanceDXCooling_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_CurveFit_OperatingMode) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitOperatingMode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_CurveFit_Performance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitPerformance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_CurveFit_Speed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXCurveFitSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Water) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingWater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_WaterToAirHeatPump_ParameterEstimation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_WaterToAirHeatPump_ParameterEstimation) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Cooling_Water_DetailedGeometry) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterDetailedGeometry_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_DX_ASHRAE205_Performance) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilDXASHRAE205Performance_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_MultiSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXMultiSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_SingleSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXSingleSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_DX_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDXVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Desuperheater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingDesuperheater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_Desuperheater) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilWaterHeatingDesuperheater_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Electric) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingElectric_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Electric_MultiStage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingElectricMultiStage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Gas_MultiStage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGasMultiStage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_Heating_Steam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingSteam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_DX) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDX_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilSystemCoolingDXHeatExchangerAssisted_Impl(object, this, keepHandle));
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
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctParallelPIUReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctSeriesPIUReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_DualDuct_ConstantVolume) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalDualDuctConstantVolume_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_DualDuct_VAV) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalDualDuctVAV_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalDualDuctVAVOutdoorAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_CooledBeam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeCooledBeam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_UserDefined) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctUserDefined_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctVAVNoReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_Reheat) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalSingleDuctVAVReheat_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl(object, this, keepHandle));
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
      if (type == IddObjectType::AirConditioner_VariableRefrigerantFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::CentralHeatPumpSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CentralHeatPumpSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Coil) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentCoil_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_ConstantPressureDrop) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentConstantPressureDrop_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Ceiling_Adiabatic) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingAdiabatic_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::Ceiling_Interzone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingInterzone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Duct) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentDuct_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_DuctSizing) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctSizing_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_DuctViewFactors) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctViewFactors_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Linkage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionLinkage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_IntraZone_Node) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkIntraZoneNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_IntraZone_Linkage) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkIntraZoneLinkage_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_ExternalNode) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneExternalNode_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Zone) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneZone_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_SpecifiedFlowRate) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSpecifiedFlowRate_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_ReferenceCrackConditions) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneReferenceCrackConditions_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientArray) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientValues) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Surface) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurface_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Surface_Crack) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurfaceCrack_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Surface_EffectiveLeakageArea) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_DetailedOpening) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentDetailedOpening_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_HorizontalOpening) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentHorizontalOpening_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_SimpleOpening) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentSimpleOpening_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_MultiZone_Component_ZoneExhaustFan) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_OccupantVentilationControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkOccupantVentilationControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_SimulationControl) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkSimulationControl_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_ZoneControl_PressureController) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkZoneControlPressureController_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Fan) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentFan_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_HeatExchanger) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentHeatExchanger_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_Leak) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeak_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_LeakageRatio) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeakageRatio_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_OutdoorAirFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentOutdoorAirFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_ReliefAirFlow) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentReliefAirFlow_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirflowNetwork_Distribution_Component_TerminalUnit) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentTerminalUnit_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_DedicatedOutdoorAirSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACDedicatedOutdoorAirSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_ExhaustSystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACExhaustSystem_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Mixer) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACMixer_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Splitter) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSplitter_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatCool) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryFurnaceHeatCool_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_Unitary_Furnace_HeatOnly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryFurnaceHeatOnly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatCool) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatCool_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatOnly) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatOnly_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitaryHeatPumpAirToAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatPump_WaterToAir) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpWaterToAir_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl(object, this, keepHandle));
      }
      if (type == IddObjectType::AirLoopHVAC_UnitarySystem) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACUnitarySystem_Impl(object, this, keepHandle));
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
      if (auto returnPlenum = std::dynamic_pointer_cast<AirLoopHVACReturnPlenum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACReturnPlenum_Impl(*returnPlenum, this, keepHandle));
      }
      if (auto supplyPlenum = std::dynamic_pointer_cast<AirLoopHVACSupplyPlenum_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSupplyPlenum_Impl(*supplyPlenum, this, keepHandle));
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
      if (auto availabilityManagerDifferentialThermostat =
            std::dynamic_pointer_cast<AvailabilityManagerDifferentialThermostat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerDifferentialThermostat_Impl(*availabilityManagerDifferentialThermostat, this, keepHandle));
      }
      if (auto availabilityManagerHighTemperatureTurnOff =
            std::dynamic_pointer_cast<AvailabilityManagerHighTemperatureTurnOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOff_Impl(*availabilityManagerHighTemperatureTurnOff, this, keepHandle));
      }
      if (auto availabilityManagerHighTemperatureTurnOn =
            std::dynamic_pointer_cast<AvailabilityManagerHighTemperatureTurnOn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHighTemperatureTurnOn_Impl(*availabilityManagerHighTemperatureTurnOn, this, keepHandle));
      }
      if (auto availabilityManagerLowTemperatureTurnOff =
            std::dynamic_pointer_cast<AvailabilityManagerLowTemperatureTurnOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerLowTemperatureTurnOff_Impl(*availabilityManagerLowTemperatureTurnOff, this, keepHandle));
      }
      if (auto availabilityManagerLowTemperatureTurnOn =
            std::dynamic_pointer_cast<AvailabilityManagerLowTemperatureTurnOn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerLowTemperatureTurnOn_Impl(*availabilityManagerLowTemperatureTurnOn, this, keepHandle));
      }
      if (auto availabilityManagerHybridVentilation =
            std::dynamic_pointer_cast<AvailabilityManagerHybridVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerHybridVentilation_Impl(*availabilityManagerHybridVentilation, this, keepHandle));
      }
      if (auto availabilityManagerNightVentilation =
            std::dynamic_pointer_cast<AvailabilityManagerNightVentilation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerNightVentilation_Impl(*availabilityManagerNightVentilation, this, keepHandle));
      }
      if (auto availabilityManagerOptimumStart = std::dynamic_pointer_cast<AvailabilityManagerOptimumStart_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerOptimumStart_Impl(*availabilityManagerOptimumStart, this, keepHandle));
      }
      if (auto availabilityManagerScheduledOff = std::dynamic_pointer_cast<AvailabilityManagerScheduledOff_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerScheduledOff_Impl(*availabilityManagerScheduledOff, this, keepHandle));
      }
      if (auto availabilityManagerScheduledOn = std::dynamic_pointer_cast<AvailabilityManagerScheduledOn_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AvailabilityManagerScheduledOn_Impl(*availabilityManagerScheduledOn, this, keepHandle));
      }
      if (auto branch = std::dynamic_pointer_cast<Branch_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Branch_Impl(*branch, this, keepHandle));
      }
      if (auto branchList = std::dynamic_pointer_cast<BranchList_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BranchList_Impl(*branchList, this, keepHandle));
      }
      if (auto building = std::dynamic_pointer_cast<Building_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new Building_Impl(*building, this, keepHandle));
      }
      if (auto boilerHotWater = std::dynamic_pointer_cast<BoilerHotWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerHotWater_Impl(*boilerHotWater, this, keepHandle));
      }
      if (auto boilerSteam = std::dynamic_pointer_cast<BoilerSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new BoilerSteam_Impl(*boilerSteam, this, keepHandle));
      }
      if (auto chillerAbsorption = std::dynamic_pointer_cast<ChillerAbsorption_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerAbsorption_Impl(*chillerAbsorption, this, keepHandle));
      }
      if (auto chillerAbsorptionIndirect = std::dynamic_pointer_cast<ChillerAbsorptionIndirect_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerAbsorptionIndirect_Impl(*chillerAbsorptionIndirect, this, keepHandle));
      }
      if (auto chillerCombustionTurbine = std::dynamic_pointer_cast<ChillerCombustionTurbine_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerCombustionTurbine_Impl(*chillerCombustionTurbine, this, keepHandle));
      }
      if (auto chillerHeaterAbsorptionDirectFired = std::dynamic_pointer_cast<ChillerHeaterAbsorptionDirectFired_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterAbsorptionDirectFired_Impl(*chillerHeaterAbsorptionDirectFired, this, keepHandle));
      }
      if (auto chillerHeaterPerformanceElectricEIR =
            std::dynamic_pointer_cast<ChillerHeaterPerformanceElectricEIR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerHeaterPerformanceElectricEIR_Impl(*chillerHeaterPerformanceElectricEIR, this, keepHandle));
      }
      if (auto chillerConstantCOP = std::dynamic_pointer_cast<ChillerConstantCOP_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerConstantCOP_Impl(*chillerConstantCOP, this, keepHandle));
      }
      if (auto chillerEngineDriven = std::dynamic_pointer_cast<ChillerEngineDriven_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerEngineDriven_Impl(*chillerEngineDriven, this, keepHandle));
      }
      if (auto chillerElectric = std::dynamic_pointer_cast<ChillerElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectric_Impl(*chillerElectric, this, keepHandle));
      }
      if (auto chillerElectricEIR = std::dynamic_pointer_cast<ChillerElectricEIR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ChillerElectricEIR_Impl(*chillerElectricEIR, this, keepHandle));
      }
      if (auto chillerElectricReformulatedEIR = std::dynamic_pointer_cast<ChillerElectricReformulatedEIR_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerElectricReformulatedEIR_Impl(*chillerElectricReformulatedEIR, this, keepHandle));
      }
      if (auto chillerElectricASHRAE205 = std::dynamic_pointer_cast<ChillerElectricASHRAE205_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new ChillerElectricASHRAE205_Impl(*chillerElectricASHRAE205, this, keepHandle));
      }
      if (auto fan = std::dynamic_pointer_cast<FanConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new FanConstantVolume_Impl(*fan, this, keepHandle));
      }
      if (auto coilCoolingDXSingleSpeed = std::dynamic_pointer_cast<CoilCoolingDXSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXSingleSpeed_Impl(*coilCoolingDXSingleSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXSingleSpeedThermalStorage =
            std::dynamic_pointer_cast<CoilCoolingDXSingleSpeedThermalStorage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXSingleSpeedThermalStorage_Impl(*coilCoolingDXSingleSpeedThermalStorage, this, keepHandle));
      }
      if (auto coilCoolingDXVariableSpeed = std::dynamic_pointer_cast<CoilCoolingDXVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableSpeed_Impl(*coilCoolingDXVariableSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXMultiSpeed = std::dynamic_pointer_cast<CoilCoolingDXMultiSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXMultiSpeed_Impl(*coilCoolingDXMultiSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXTwoSpeed = std::dynamic_pointer_cast<CoilCoolingDXTwoSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXTwoSpeed_Impl(*coilCoolingDXTwoSpeed, this, keepHandle));
      }
      if (auto coilCoolingDXTwoStageWithHumidityControlMode =
            std::dynamic_pointer_cast<CoilCoolingDXTwoStageWithHumidityControlMode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXTwoStageWithHumidityControlMode_Impl(*coilCoolingDXTwoStageWithHumidityControlMode, this, keepHandle));
      }
      if (auto coilPerformanceDXCooling = std::dynamic_pointer_cast<CoilPerformanceDXCooling_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilPerformanceDXCooling_Impl(*coilPerformanceDXCooling, this, keepHandle));
      }
      if (auto coilCoolingDXCurveFitOperatingMode =
            std::dynamic_pointer_cast<CoilCoolingDXCurveFitOperatingMode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitOperatingMode_Impl(*coilCoolingDXCurveFitOperatingMode, this, keepHandle));
      }
      if (auto coilCoolingDXCurveFitPerformance =
            std::dynamic_pointer_cast<CoilCoolingDXCurveFitPerformance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitPerformance_Impl(*coilCoolingDXCurveFitPerformance, this, keepHandle));
      }
      if (auto coilCoolingDXCurveFitSpeed = std::dynamic_pointer_cast<CoilCoolingDXCurveFitSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXCurveFitSpeed_Impl(*coilCoolingDXCurveFitSpeed, this, keepHandle));
      }
      if (auto coilCoolingDX = std::dynamic_pointer_cast<CoilCoolingDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDX_Impl(*coilCoolingDX, this, keepHandle));
      }
      if (auto coilCoolingDXVariableRefrigerantFlow =
            std::dynamic_pointer_cast<CoilCoolingDXVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingDXVariableRefrigerantFlow_Impl(*coilCoolingDXVariableRefrigerantFlow, this, keepHandle));
      }
      if (auto coilCoolingDXVariableRefrigerantFlowFluidTemperatureControl =
            std::dynamic_pointer_cast<CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(
          *coilCoolingDXVariableRefrigerantFlowFluidTemperatureControl, this, keepHandle));
      }
      if (auto coilHeatingDXVariableRefrigerantFlow =
            std::dynamic_pointer_cast<CoilHeatingDXVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableRefrigerantFlow_Impl(*coilHeatingDXVariableRefrigerantFlow, this, keepHandle));
      }
      if (auto coilHeatingDXVariableRefrigerantFlowFluidTemperatureControl =
            std::dynamic_pointer_cast<CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl(
            *coilHeatingDXVariableRefrigerantFlowFluidTemperatureControl, this, keepHandle));
      }
      if (auto coilCoolingWater = std::dynamic_pointer_cast<CoilCoolingWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWater_Impl(*coilCoolingWater, this, keepHandle));
      }
      if (auto coilHeatingWater = std::dynamic_pointer_cast<CoilHeatingWater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingWater_Impl(*coilHeatingWater, this, keepHandle));
      }
      if (auto coilCoolingWaterToAirHeatPumpEquationFit =
            std::dynamic_pointer_cast<CoilCoolingWaterToAirHeatPumpEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpEquationFit_Impl(*coilCoolingWaterToAirHeatPumpEquationFit, this, keepHandle));
      }
      if (auto coilHeatingWaterToAirHeatPumpEquationFit =
            std::dynamic_pointer_cast<CoilHeatingWaterToAirHeatPumpEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpEquationFit_Impl(*coilHeatingWaterToAirHeatPumpEquationFit, this, keepHandle));
      }
      if (auto coilCoolingWaterToAirHeatPumpVariableSpeedEquationFit =
            std::dynamic_pointer_cast<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(
          *coilCoolingWaterToAirHeatPumpVariableSpeedEquationFit, this, keepHandle));
      }
      if (auto coilHeatingWaterToAirHeatPumpVariableSpeedEquationFit =
            std::dynamic_pointer_cast<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl(
          *coilHeatingWaterToAirHeatPumpVariableSpeedEquationFit, this, keepHandle));
      }
      if (auto coilUserDefined = std::dynamic_pointer_cast<CoilUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilUserDefined_Impl(*coilUserDefined, this, keepHandle));
      }
      if (auto coilCoolingWaterToAirHeatPumpParameterEstimation =
            std::dynamic_pointer_cast<CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl(*coilCoolingWaterToAirHeatPumpParameterEstimation, this, keepHandle));
      }
      if (auto coilHeatingWaterToAirHeatPumpParameterEstimation =
            std::dynamic_pointer_cast<CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl(*coilHeatingWaterToAirHeatPumpParameterEstimation, this, keepHandle));
      }
      if (auto coilCoolingWaterDetailedGeometry = std::dynamic_pointer_cast<CoilCoolingWaterDetailedGeometry_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilCoolingWaterDetailedGeometry_Impl(*coilCoolingWaterDetailedGeometry, this, keepHandle));
      }
      if (auto coilDXASHRAE205Performance = std::dynamic_pointer_cast<CoilDXASHRAE205Performance_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilDXASHRAE205Performance_Impl(*coilDXASHRAE205Performance, this, keepHandle));
      }
      if (auto coilHeatingDXMultiSpeed = std::dynamic_pointer_cast<CoilHeatingDXMultiSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXMultiSpeed_Impl(*coilHeatingDXMultiSpeed, this, keepHandle));
      }
      if (auto coilHeatingDXSingleSpeed = std::dynamic_pointer_cast<CoilHeatingDXSingleSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXSingleSpeed_Impl(*coilHeatingDXSingleSpeed, this, keepHandle));
      }
      if (auto coilHeatingDXVariableSpeed = std::dynamic_pointer_cast<CoilHeatingDXVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDXVariableSpeed_Impl(*coilHeatingDXVariableSpeed, this, keepHandle));
      }
      if (auto coilHeatingDesuperheater = std::dynamic_pointer_cast<CoilHeatingDesuperheater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingDesuperheater_Impl(*coilHeatingDesuperheater, this, keepHandle));
      }
      if (auto coilWaterHeatingDesuperheater = std::dynamic_pointer_cast<CoilWaterHeatingDesuperheater_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingDesuperheater_Impl(*coilWaterHeatingDesuperheater, this, keepHandle));
      }
      if (auto coilHeatingElectric = std::dynamic_pointer_cast<CoilHeatingElectric_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingElectric_Impl(*coilHeatingElectric, this, keepHandle));
      }
      if (auto coilHeatingElectricMultiStage = std::dynamic_pointer_cast<CoilHeatingElectricMultiStage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingElectricMultiStage_Impl(*coilHeatingElectricMultiStage, this, keepHandle));
      }
      if (auto coilHeatingGasMultiStage = std::dynamic_pointer_cast<CoilHeatingGasMultiStage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilHeatingGasMultiStage_Impl(*coilHeatingGasMultiStage, this, keepHandle));
      }
      if (auto coilHeatingSteam = std::dynamic_pointer_cast<CoilHeatingSteam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingSteam_Impl(*coilHeatingSteam, this, keepHandle));
      }
      if (auto coilWaterHeatingAirToWaterHeatPumpWrapped =
            std::dynamic_pointer_cast<CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl(*coilWaterHeatingAirToWaterHeatPumpWrapped, this, keepHandle));
      }
      if (auto coilWaterHeatingAirToWaterHeatPumpVariableSpeed =
            std::dynamic_pointer_cast<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl(*coilWaterHeatingAirToWaterHeatPumpVariableSpeed, this, keepHandle));
      }
      if (auto coilHeatingFuel = std::dynamic_pointer_cast<CoilHeatingGas_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilHeatingGas_Impl(*coilHeatingFuel, this, keepHandle));
      }
      if (auto coilSystemCoolingDX = std::dynamic_pointer_cast<CoilSystemCoolingDX_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CoilSystemCoolingDX_Impl(*coilSystemCoolingDX, this, keepHandle));
      }
      if (auto coilSystemCoolingDXHeatExchangerAssisted =
            std::dynamic_pointer_cast<CoilSystemCoolingDXHeatExchangerAssisted_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CoilSystemCoolingDXHeatExchangerAssisted_Impl(*coilSystemCoolingDXHeatExchangerAssisted, this, keepHandle));
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
      if (auto airTerminalReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeReheat_Impl(*airTerminalReheat, this, keepHandle));
      }
      if (auto airTerminalParallelPIUReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctParallelPIUReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctParallelPIUReheat_Impl(*airTerminalParallelPIUReheat, this, keepHandle));
      }
      if (auto airTerminalSeriesPIUReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctSeriesPIUReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctSeriesPIUReheat_Impl(*airTerminalSeriesPIUReheat, this, keepHandle));
      }
      if (auto airTerminalDualDuctConstantVolume =
            std::dynamic_pointer_cast<AirTerminalDualDuctConstantVolume_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalDualDuctConstantVolume_Impl(*airTerminalDualDuctConstantVolume, this, keepHandle));
      }
      if (auto airTerminalDualDuctVAV = std::dynamic_pointer_cast<AirTerminalDualDuctVAV_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirTerminalDualDuctVAV_Impl(*airTerminalDualDuctVAV, this, keepHandle));
      }
      if (auto airTerminalDualDuctVAVOutdoorAir = std::dynamic_pointer_cast<AirTerminalDualDuctVAVOutdoorAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalDualDuctVAVOutdoorAir_Impl(*airTerminalDualDuctVAVOutdoorAir, this, keepHandle));
      }
      if (auto airTerminalSingleDuctConstantVolumeCooledBeam =
            std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeCooledBeam_Impl(*airTerminalSingleDuctConstantVolumeCooledBeam, this, keepHandle));
      }
      if (auto airTerminalSingleDuctConstantVolumeFourPipeBeam =
            std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl(*airTerminalSingleDuctConstantVolumeFourPipeBeam, this, keepHandle));
      }
      if (auto airTerminalSingleDuctConstantVolumeFourPipeInduction =
            std::dynamic_pointer_cast<AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl(*airTerminalSingleDuctConstantVolumeFourPipeInduction, this, keepHandle));
      }
      if (auto airTerminalSingleDuctUserDefined = std::dynamic_pointer_cast<AirTerminalSingleDuctUserDefined_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctUserDefined_Impl(*airTerminalSingleDuctUserDefined, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVHeatAndCoolNoReheat =
            std::dynamic_pointer_cast<AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl(*airTerminalSingleDuctVAVHeatAndCoolNoReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVHeatAndCoolReheat =
            std::dynamic_pointer_cast<AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl(*airTerminalSingleDuctVAVHeatAndCoolReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVNoReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctVAVNoReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVNoReheat_Impl(*airTerminalSingleDuctVAVNoReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVReheat = std::dynamic_pointer_cast<AirTerminalSingleDuctVAVReheat_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVReheat_Impl(*airTerminalSingleDuctVAVReheat, this, keepHandle));
      }
      if (auto airTerminalSingleDuctVAVReheatVariableSpeedFan =
            std::dynamic_pointer_cast<AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl(*airTerminalSingleDuctVAVReheatVariableSpeedFan, this, keepHandle));
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
      if (auto vrf = std::dynamic_pointer_cast<AirConditionerVariableRefrigerantFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirConditionerVariableRefrigerantFlow_Impl(*vrf, this, keepHandle));
      }
      if (auto vrfFluid = std::dynamic_pointer_cast<AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>(
            originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl(*vrfFluid, this, keepHandle));
      }
      if (auto vrfFluidHR = std::dynamic_pointer_cast<AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>(
            originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl(*vrfFluidHR, this, keepHandle));
      }
      if (auto centralHeatPumpSystem = std::dynamic_pointer_cast<CentralHeatPumpSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new CentralHeatPumpSystem_Impl(*centralHeatPumpSystem, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentCoil =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentCoil_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentCoil_Impl(*airflowNetworkDistributionComponentCoil, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentConstantPressureDrop =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentConstantPressureDrop_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkDistributionComponentConstantPressureDrop_Impl(
          *airflowNetworkDistributionComponentConstantPressureDrop, this, keepHandle));
      }
      if (auto ceilingAdiabatic = std::dynamic_pointer_cast<CeilingAdiabatic_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingAdiabatic_Impl(*ceilingAdiabatic, this, keepHandle));
      }
      if (auto ceilingInterzone = std::dynamic_pointer_cast<CeilingInterzone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new CeilingInterzone_Impl(*ceilingInterzone, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentDuct =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentDuct_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentDuct_Impl(*airflowNetworkDistributionComponentDuct, this, keepHandle));
      }
      if (auto airflowNetworkDistributionDuctSizing =
            std::dynamic_pointer_cast<AirflowNetworkDistributionDuctSizing_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctSizing_Impl(*airflowNetworkDistributionDuctSizing, this, keepHandle));
      }
      if (auto airflowNetworkDistributionDuctViewFactors =
            std::dynamic_pointer_cast<AirflowNetworkDistributionDuctViewFactors_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionDuctViewFactors_Impl(*airflowNetworkDistributionDuctViewFactors, this, keepHandle));
      }
      if (auto airflowNetworkDistributionLinkage =
            std::dynamic_pointer_cast<AirflowNetworkDistributionLinkage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionLinkage_Impl(*airflowNetworkDistributionLinkage, this, keepHandle));
      }
      if (auto airflowNetworkDistributionNode = std::dynamic_pointer_cast<AirflowNetworkDistributionNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionNode_Impl(*airflowNetworkDistributionNode, this, keepHandle));
      }
      if (auto airflowNetworkIntraZoneNode = std::dynamic_pointer_cast<AirflowNetworkIntraZoneNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkIntraZoneNode_Impl(*airflowNetworkIntraZoneNode, this, keepHandle));
      }
      if (auto airflowNetworkIntraZoneLinkage = std::dynamic_pointer_cast<AirflowNetworkIntraZoneLinkage_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkIntraZoneLinkage_Impl(*airflowNetworkIntraZoneLinkage, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneExternalNode =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneExternalNode_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneExternalNode_Impl(*airflowNetworkMultiZoneExternalNode, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneZone = std::dynamic_pointer_cast<AirflowNetworkMultiZoneZone_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneZone_Impl(*airflowNetworkMultiZoneZone, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSpecifiedFlowRate =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneSpecifiedFlowRate_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSpecifiedFlowRate_Impl(*airflowNetworkMultiZoneSpecifiedFlowRate, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneReferenceCrackConditions =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneReferenceCrackConditions_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneReferenceCrackConditions_Impl(
          *airflowNetworkMultiZoneReferenceCrackConditions, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneWindPressureCoefficientArray =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl(*airflowNetworkMultiZoneWindPressureCoefficientArray, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneWindPressureCoefficientValues =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl(
          *airflowNetworkMultiZoneWindPressureCoefficientValues, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSurface = std::dynamic_pointer_cast<AirflowNetworkMultiZoneSurface_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurface_Impl(*airflowNetworkMultiZoneSurface, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSurfaceCrack =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneSurfaceCrack_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneSurfaceCrack_Impl(*airflowNetworkMultiZoneSurfaceCrack, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneSurfaceEffectiveLeakageArea =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl(
          *airflowNetworkMultiZoneSurfaceEffectiveLeakageArea, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentDetailedOpening =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentDetailedOpening_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentDetailedOpening_Impl(*airflowNetworkMultiZoneComponentDetailedOpening, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentHorizontalOpening =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentHorizontalOpening_Impl(*airflowNetworkMultiZoneComponentHorizontalOpening, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentSimpleOpening =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentSimpleOpening_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentSimpleOpening_Impl(*airflowNetworkMultiZoneComponentSimpleOpening, this, keepHandle));
      }
      if (auto airflowNetworkMultiZoneComponentZoneExhaustFan =
            std::dynamic_pointer_cast<AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl(*airflowNetworkMultiZoneComponentZoneExhaustFan, this, keepHandle));
      }
      if (auto airflowNetworkOccupantVentilationControl =
            std::dynamic_pointer_cast<AirflowNetworkOccupantVentilationControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkOccupantVentilationControl_Impl(*airflowNetworkOccupantVentilationControl, this, keepHandle));
      }
      if (auto airflowNetworkSimulationControl =
            std::dynamic_pointer_cast<AirflowNetworkSimulationControl_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkSimulationControl_Impl(*airflowNetworkSimulationControl, this, keepHandle));
      }
      if (auto airflowNetworkZoneControlPressureController =
            std::dynamic_pointer_cast<AirflowNetworkZoneControlPressureController_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkZoneControlPressureController_Impl(*airflowNetworkZoneControlPressureController, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentFan =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentFan_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentFan_Impl(*airflowNetworkDistributionComponentFan, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentHeatExchanger =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentHeatExchanger_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentHeatExchanger_Impl(*airflowNetworkDistributionComponentHeatExchanger, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentLeak =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentLeak_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeak_Impl(*airflowNetworkDistributionComponentLeak, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentLeakageRatio =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentLeakageRatio_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentLeakageRatio_Impl(*airflowNetworkDistributionComponentLeakageRatio, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentOutdoorAirFlow =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentOutdoorAirFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentOutdoorAirFlow_Impl(*airflowNetworkDistributionComponentOutdoorAirFlow, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentReliefAirFlow =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentReliefAirFlow_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentReliefAirFlow_Impl(*airflowNetworkDistributionComponentReliefAirFlow, this, keepHandle));
      }
      if (auto airflowNetworkDistributionComponentTerminalUnit =
            std::dynamic_pointer_cast<AirflowNetworkDistributionComponentTerminalUnit_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirflowNetworkDistributionComponentTerminalUnit_Impl(*airflowNetworkDistributionComponentTerminalUnit, this, keepHandle));
      }
      if (auto doas = std::dynamic_pointer_cast<AirLoopHVACDedicatedOutdoorAirSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACDedicatedOutdoorAirSystem_Impl(*doas, this, keepHandle));
      }
      if (auto exhaustSystem = std::dynamic_pointer_cast<AirLoopHVACExhaustSystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACExhaustSystem_Impl(*exhaustSystem, this, keepHandle));
      }
      if (auto airLoopHVACMixer = std::dynamic_pointer_cast<AirLoopHVACMixer_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACMixer_Impl(*airLoopHVACMixer, this, keepHandle));
      }
      if (auto airLoopHVACSplitter = std::dynamic_pointer_cast<AirLoopHVACSplitter_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new AirLoopHVACSplitter_Impl(*airLoopHVACSplitter, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryFurnaceHeatCool = std::dynamic_pointer_cast<AirLoopHVACUnitaryFurnaceHeatCool_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryFurnaceHeatCool_Impl(*airLoopHVACUnitaryFurnaceHeatCool, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryFurnaceHeatOnly = std::dynamic_pointer_cast<AirLoopHVACUnitaryFurnaceHeatOnly_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryFurnaceHeatOnly_Impl(*airLoopHVACUnitaryFurnaceHeatOnly, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatCool = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatCool_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatCool_Impl(*airLoopHVACUnitaryHeatCool, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatOnly = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatOnly_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatOnly_Impl(*airLoopHVACUnitaryHeatOnly, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatPumpAirToAir = std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatPumpAirToAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpAirToAir_Impl(*airLoopHVACUnitaryHeatPumpAirToAir, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatPumpWaterToAir =
            std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatPumpWaterToAir_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpWaterToAir_Impl(*airLoopHVACUnitaryHeatPumpWaterToAir, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatPumpAirToAirMultiSpeed =
            std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl(*airLoopHVACUnitaryHeatPumpAirToAirMultiSpeed, this, keepHandle));
      }
      if (auto airLoopHVACUnitaryHeatCoolVAVChangeoverBypass =
            std::dynamic_pointer_cast<AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl(*airLoopHVACUnitaryHeatCoolVAVChangeoverBypass, this, keepHandle));
      }
      if (auto airLoopHVACUnitarySystem = std::dynamic_pointer_cast<AirLoopHVACUnitarySystem_Impl>(originalObjectImplPtr)) {
        return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(
          new AirLoopHVACUnitarySystem_Impl(*airLoopHVACUnitarySystem, this, keepHandle));
      }
      return std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>(new ModelObject_Impl(*originalObjectImplPtr, this, keepHandle));
    }

    openstudio::epmodel::Model Model_Impl::model() const {
      return Model(std::dynamic_pointer_cast<Model_Impl>(std::const_pointer_cast<openstudio::detail::Workspace_Impl>(this->shared_from_this())));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
