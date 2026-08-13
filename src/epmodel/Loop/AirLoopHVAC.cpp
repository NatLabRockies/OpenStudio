/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"

#include "BranchList.hpp"
#include "BranchList_Impl.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"
#include "AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "AvailabilityManager/AvailabilityManagerNightCycle_Impl.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "AirLoopHVACReturnPath.hpp"
#include "AirLoopHVACReturnPath_Impl.hpp"
#include "ModelObject/AirLoopHVACSupplyPath.hpp"
#include "ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "ModelObject/AirLoopHVACControllerList.hpp"
#include "ModelObject/AirLoopHVACControllerList_Impl.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "ModelObject/CoilSystemCoolingDX.hpp"
#include "ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Mixer/AirLoopHVACReturnPlenum.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "Mixer/AirTerminalDualDuctConstantVolume.hpp"
#include "Mixer/AirTerminalDualDuctVAV.hpp"
#include "Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp"
#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"
#include "Mixer/Mixer.hpp"
#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "HVACComponent/ControllerWaterCoil.hpp"
#include "HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "ModelObject/ControllerMechanicalVentilation.hpp"
#include "ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject_Impl.inl"
#include "Node.hpp"
#include "ModelObject/NodeList.hpp"
#include "ModelObject/NodeList_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl.hpp"
#include "StraightComponent/CoilCoolingCooledBeam.hpp"
#include "StraightComponent/CoilCoolingFourPipeBeam.hpp"
#include "StraightComponent/CoilHeatingFourPipeBeam.hpp"
#include "scaffolds/AirTerminalSingleDuctVAVReheatVariableSpeedFan.hpp"
#include "scaffolds/AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "ModelObject/SizingSystem.hpp"
#include "ModelObject/SizingSystem_Impl.hpp"
#include "SetpointManager/SetpointManagerMixedAir.hpp"
#include "SetpointManager/SetpointManagerMixedAir_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <algorithm>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ReturnPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_SupplyPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_SeriesPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan_FieldEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeam_FieldEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/ConnectorList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>
#include <utilities/idd/Sizing_System_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/core/Logger.hpp>
#include <utilities/core/Assert.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>
#include <set>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace openstudio {
namespace epmodel {

  AirLoopHVAC::AirLoopHVAC(const Model& model, bool dualDuct) : Loop(openstudio::IddObjectType::AirLoopHVAC, model) {
    auto impl = getImpl<detail::AirLoopHVAC_Impl>();
    OS_ASSERT(impl);

    // A renamed loop can leave its relationship-owned nodes under the
    // constructor's original default name. Do not let a later loop reclaim
    // those nodes merely because that default AirLoopHVAC name is available
    // again: doing so aliases the loops' supply and return topology.
    auto companionNameIsTaken = [&model](const std::string& loopName) {
      return static_cast<bool>(model.getConcreteModelObjectByName<Node>(loopName + " Supply Inlet Node"))
             || static_cast<bool>(model.getConcreteModelObjectByName<Node>(loopName + " Demand Outlet Node"))
             || static_cast<bool>(model.getConcreteModelObjectByName<AvailabilityManagerAssignmentList>(loopName + " Availability Manager List"));
    };
    while (companionNameIsTaken(nameString())) {
      OS_ASSERT(setName(model.nextName(iddObjectType(), false)));
    }

    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    autosizeDesignSupplyAirFlowRate();
    OS_ASSERT(setDesignReturnAirFlowFractionofSupplyAirFlow(1.0));
    if (dualDuct) {
      OS_ASSERT(impl->makeDualDuct());
    }
  }

  AirLoopHVAC::AirLoopHVAC(std::shared_ptr<detail::AirLoopHVAC_Impl> impl) : Loop(std::move(impl)) {}

  IddObjectType AirLoopHVAC::iddObjectType() {
    return IddObjectType::AirLoopHVAC;
  }

  boost::optional<double> AirLoopHVAC::designSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->designSupplyAirFlowRate();
  }

  bool AirLoopHVAC::isDesignSupplyAirFlowRateAutosized() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->isDesignSupplyAirFlowRateAutosized();
  }

  bool AirLoopHVAC::setDesignSupplyAirFlowRate(double designSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVAC_Impl>()->setDesignSupplyAirFlowRate(designSupplyAirFlowRate);
  }

  void AirLoopHVAC::resetDesignSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVAC_Impl>()->resetDesignSupplyAirFlowRate();
  }

  void AirLoopHVAC::autosizeDesignSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVAC_Impl>()->autosizeDesignSupplyAirFlowRate();
  }

  double AirLoopHVAC::designReturnAirFlowFractionofSupplyAirFlow() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->designReturnAirFlowFractionofSupplyAirFlow();
  }

  bool AirLoopHVAC::setDesignReturnAirFlowFractionofSupplyAirFlow(double designReturnAirFlowFractionofSupplyAirFlow) {
    return getImpl<detail::AirLoopHVAC_Impl>()->setDesignReturnAirFlowFractionofSupplyAirFlow(designReturnAirFlowFractionofSupplyAirFlow);
  }

  Node AirLoopHVAC::supplyInletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyInletNode();
  }

  Node AirLoopHVAC::supplyOutletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyOutletNode();
  }

  std::vector<Node> AirLoopHVAC::supplyOutletNodes() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyOutletNodes();
  }

  Node AirLoopHVAC::demandInletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandInletNode();
  }

  Node AirLoopHVAC::demandOutletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandOutletNode();
  }

  std::vector<Node> AirLoopHVAC::demandInletNodes() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandInletNodes();
  }

  bool AirLoopHVAC::isDualDuct() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->isDualDuct();
  }

  boost::optional<Splitter> AirLoopHVAC::supplySplitter() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplySplitter();
  }

  boost::optional<Node> AirLoopHVAC::supplySplitterInletNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplySplitterInletNode();
  }

  std::vector<Node> AirLoopHVAC::supplySplitterOutletNodes() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplySplitterOutletNodes();
  }

  AirLoopHVACZoneSplitter AirLoopHVAC::zoneSplitter() const {
    // Schema Alignment Notes:
    // - API: Preserve model-style zoneSplitter/zoneMixer relationship accessors.
    // - Field Mapping: AirLoopHVAC::ConnectorListName and Connector:Splitter linkage are surfaced via topology
    //   relationships (not scalar fields).
    return getImpl<detail::AirLoopHVAC_Impl>()->zoneSplitter();
  }

  AirLoopHVACZoneMixer AirLoopHVAC::zoneMixer() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->zoneMixer();
  }

  std::vector<ModelObject> AirLoopHVAC::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                         openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> AirLoopHVAC::supplyComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyComponents(type);
  }

  std::vector<ModelObject> AirLoopHVAC::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                         openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandComponents(inletComp, outletComp, type);
  }

  std::vector<ModelObject> AirLoopHVAC::demandComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->demandComponents(type);
  }

  std::vector<ModelObject> AirLoopHVAC::oaComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->oaComponents(type);
  }

  boost::optional<Node> AirLoopHVAC::outdoorAirNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> AirLoopHVAC::reliefAirNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->reliefAirNode();
  }

  boost::optional<Node> AirLoopHVAC::mixedAirNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->mixedAirNode();
  }

  boost::optional<Node> AirLoopHVAC::returnAirNode() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->returnAirNode();
  }

  boost::optional<AirLoopHVACOutdoorAirSystem> AirLoopHVAC::airLoopHVACOutdoorAirSystem() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->airLoopHVACOutdoorAirSystem();
  }

  boost::optional<HVACComponent> AirLoopHVAC::supplyFan() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->supplyFan();
  }

  boost::optional<HVACComponent> AirLoopHVAC::returnFan() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->returnFan();
  }

  boost::optional<HVACComponent> AirLoopHVAC::reliefFan() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->reliefFan();
  }

  SizingSystem AirLoopHVAC::sizingSystem() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->sizingSystem();
  }

  Schedule AirLoopHVAC::availabilitySchedule() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->availabilitySchedule();
  }

  bool AirLoopHVAC::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVAC_Impl>()->setAvailabilitySchedule(schedule);
  }

  std::vector<ThermalZone> AirLoopHVAC::thermalZones() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->thermalZones();
  }

  std::vector<AvailabilityManager> AirLoopHVAC::availabilityManagers() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->availabilityManagers();
  }

  bool AirLoopHVAC::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::AirLoopHVAC_Impl>()->addAvailabilityManager(availabilityManager);
  }

  bool AirLoopHVAC::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::AirLoopHVAC_Impl>()->addAvailabilityManager(availabilityManager, priority);
  }

  bool AirLoopHVAC::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
    return getImpl<detail::AirLoopHVAC_Impl>()->setAvailabilityManagers(availabilityManagers);
  }

  void AirLoopHVAC::resetAvailabilityManagers() {
    getImpl<detail::AirLoopHVAC_Impl>()->resetAvailabilityManagers();
  }

  bool AirLoopHVAC::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::AirLoopHVAC_Impl>()->removeAvailabilityManager(availabilityManager);
  }

  bool AirLoopHVAC::removeAvailabilityManager(unsigned priority) {
    return getImpl<detail::AirLoopHVAC_Impl>()->removeAvailabilityManager(priority);
  }

  bool AirLoopHVAC::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::AirLoopHVAC_Impl>()->setAvailabilityManagerPriority(availabilityManager, priority);
  }

  unsigned AirLoopHVAC::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
    return getImpl<detail::AirLoopHVAC_Impl>()->availabilityManagerPriority(availabilityManager);
  }

  bool AirLoopHVAC::setNightCycleControlType(const std::string& controlType) {
    return getImpl<detail::AirLoopHVAC_Impl>()->setNightCycleControlType(controlType);
  }

  std::string AirLoopHVAC::nightCycleControlType() const {
    return getImpl<detail::AirLoopHVAC_Impl>()->nightCycleControlType();
  }

  bool AirLoopHVAC::addBranchForZone(ThermalZone& thermalZone) {
    return getImpl<detail::AirLoopHVAC_Impl>()->addBranchForZone(thermalZone);
  }

  bool AirLoopHVAC::addBranchForZone(ThermalZone& thermalZone, HVACComponent& airTerminal) {
    return getImpl<detail::AirLoopHVAC_Impl>()->addBranchForZone(thermalZone, airTerminal);
  }

  bool AirLoopHVAC::addBranchForHVACComponent(HVACComponent& hvacComponent) {
    return getImpl<detail::AirLoopHVAC_Impl>()->addBranchForHVACComponent(hvacComponent);
  }

  bool AirLoopHVAC::removeBranchForZone(ThermalZone& thermalZone) {
    return getImpl<detail::AirLoopHVAC_Impl>()->removeBranchForZone(thermalZone);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {
    namespace {
      boost::optional<ZoneHVACAirDistributionUnit> airDistributionUnitForZoneEquipment(const ModelObject& equipment) {
        if (auto airDistributionUnit = equipment.optionalCast<ZoneHVACAirDistributionUnit>()) {
          return *airDistributionUnit;
        }

        for (const auto& source : equipment.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
          if (auto airDistributionUnit = source.optionalCast<ZoneHVACAirDistributionUnit>()) {
            return *airDistributionUnit;
          }
        }

        return boost::none;
      }

      boost::optional<ZoneHVACAirDistributionUnit> airDistributionUnitForTerminal(const ModelObject& terminal) {
        for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
          if (auto airDistributionUnit = source.optionalCast<ZoneHVACAirDistributionUnit>()) {
            return *airDistributionUnit;
          }
        }
        return boost::none;
      }
    }  // namespace

    // Owns the translator-facing projection that is required when a terminal
    // is placed on a demand branch before its zone is known. The terminal and
    // primary branch remain authoritative; this transaction owns only the
    // late-created secondary/induced-air, exhaust, equipment-list, and ADU
    // state. An abandoned projection restores the exact preexisting ADU outlet
    // and zone exhaust representation.
    class AirLoopHVAC_Impl::TerminalZoneProjectionPlan
    {
     public:
      static std::unique_ptr<TerminalZoneProjectionPlan> prepare(ModelObject terminal, ZoneHVACEquipmentConnections connections,
                                                                 Node terminalOutlet) {
        auto plan = std::unique_ptr<TerminalZoneProjectionPlan>(
          new TerminalZoneProjectionPlan(std::move(terminal), std::move(connections), std::move(terminalOutlet)));
        if (!plan->prepareProjection()) {
          return nullptr;
        }
        return plan;
      }

      TerminalZoneProjectionPlan(const TerminalZoneProjectionPlan&) = delete;
      TerminalZoneProjectionPlan& operator=(const TerminalZoneProjectionPlan&) = delete;
      TerminalZoneProjectionPlan(TerminalZoneProjectionPlan&&) = delete;
      TerminalZoneProjectionPlan& operator=(TerminalZoneProjectionPlan&&) = delete;

      ~TerminalZoneProjectionPlan() {
        if (m_state == State::Prepared) {
          cleanupPreparedState();
        }
      }

      void commit() {
        OS_ASSERT(m_state == State::Prepared);
        m_state = State::Committed;
      }

     private:
      enum class State
      {
        Prepared,
        Committed,
      };

      TerminalZoneProjectionPlan(ModelObject terminal, ZoneHVACEquipmentConnections connections, Node terminalOutlet)
        : m_terminal(std::move(terminal)), m_connections(std::move(connections)), m_terminalOutlet(std::move(terminalOutlet)) {}

      boost::optional<unsigned> secondaryOrInducedAirField() const {
        switch (m_terminal.iddObject().type().value()) {
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat:
            return openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName;
          case openstudio::IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat:
            return openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName;
          case openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction:
            return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName;
          default:
            return boost::none;
        }
      }

      std::string secondaryOrInducedAirNodeName() const {
        const bool induction = m_terminal.iddObject().type() == openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction;
        return m_terminalOutlet.nameString() + " - " + m_terminal.nameString()
               + (induction ? " Induced Air Inlet Node" : " Secondary Air Inlet Node");
      }

      void captureCreatedNodeLists() {
        for (const auto& nodeList : m_terminal.model().getConcreteModelObjects<NodeList>()) {
          if (m_originalNodeListHandles.contains(nodeList.handle())) {
            continue;
          }
          const auto found =
            std::ranges::find_if(m_createdNodeLists, [&nodeList](const auto& candidate) { return candidate.handle() == nodeList.handle(); });
          if (found == m_createdNodeLists.end()) {
            m_createdNodeLists.push_back(nodeList);
          }
        }
      }

      bool prepareSecondaryOrInducedAirProjection() {
        m_secondaryOrInducedAirField = secondaryOrInducedAirField();
        if (!m_secondaryOrInducedAirField) {
          return true;
        }

        for (const auto& nodeList : m_terminal.model().getConcreteModelObjects<NodeList>()) {
          m_originalNodeListHandles.insert(nodeList.handle());
        }
        m_originalExhaustNodes = m_connections.zoneAirExhaustNodes();
        if (auto target = m_connections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName)) {
          m_originalExhaustTarget = target->optionalCast<ModelObject>();
        }

        const auto originalTarget = m_terminal.getTarget(*m_secondaryOrInducedAirField);
        if (originalTarget) {
          m_originalSecondaryOrInducedAirTarget = originalTarget->optionalCast<ModelObject>();
          m_secondaryOrInducedAirNode = originalTarget->optionalCast<Node>();
          if (!m_secondaryOrInducedAirNode) {
            return false;
          }
        } else {
          const auto rawTarget = m_terminal.getString(*m_secondaryOrInducedAirField, false, true);
          if (rawTarget && !rawTarget->empty()) {
            return false;
          }
          const auto nodeName = secondaryOrInducedAirNodeName();
          const bool nodeExisted = static_cast<bool>(m_terminal.model().getConcreteModelObjectByName<Node>(nodeName));
          m_secondaryOrInducedAirNode = m_terminal.model().getOrCreateTransientByName<Node>(nodeName);
          m_createdSecondaryOrInducedAirNode = !nodeExisted;
          auto terminalImpl = m_terminal.getImpl<detail::ModelObject_Impl>();
          OS_ASSERT(terminalImpl);
          if (!terminalImpl->setPointer(*m_secondaryOrInducedAirField, m_secondaryOrInducedAirNode->handle(), false)) {
            return false;
          }
          m_secondaryOrInducedAirPointerChanged = true;
        }

        auto connectionsImpl = m_connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
        OS_ASSERT(connectionsImpl);
        if (!connectionsImpl->addZoneAirExhaustNode(*m_secondaryOrInducedAirNode)) {
          captureCreatedNodeLists();
          return false;
        }
        captureCreatedNodeLists();
        m_exhaustProjectionChanged = true;
        return true;
      }

      bool prepareEquipmentRegistration() {
        m_equipmentList = m_connections.zoneHVACEquipmentList();
        const auto originalEquipment = m_equipmentList->equipment();
        m_terminalWasRegistered = std::ranges::find(originalEquipment, m_terminal) != originalEquipment.end();
        m_originalAirDistributionUnit = airDistributionUnitForTerminal(m_terminal);
        if (m_originalAirDistributionUnit) {
          const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
          if (auto managedField = m_originalAirDistributionUnit->getField(outletField, false)) {
            const auto targetHandle = toUUID(*managedField);
            if (!targetHandle.isNull()) {
              if (auto target = m_terminal.model().getObject(targetHandle)) {
                m_originalADUOutletTarget = target->optionalCast<ModelObject>();
              }
            }
          }
          if (!m_originalADUOutletTarget) {
            auto workspaceImpl = m_originalAirDistributionUnit->getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(workspaceImpl);
            m_originalADUOutletNodeName = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
          }
        }

        if (!m_equipmentList->addEquipment(m_terminal)) {
          return false;
        }
        m_terminalRegistered = !m_terminalWasRegistered;

        m_projectedAirDistributionUnit = airDistributionUnitForTerminal(m_terminal);
        if (!m_projectedAirDistributionUnit) {
          return false;
        }
        m_createdAirDistributionUnit = !m_originalAirDistributionUnit;
        return true;
      }

      bool prepareProjection() {
        return prepareSecondaryOrInducedAirProjection() && prepareEquipmentRegistration();
      }

      void restoreExhaustProjection() {
        if (!m_secondaryOrInducedAirField) {
          return;
        }

        if (auto originalNodeList = m_originalExhaustTarget ? m_originalExhaustTarget->optionalCast<NodeList>() : boost::optional<NodeList>()) {
          auto nodeListImpl = originalNodeList->getImpl<detail::NodeList_Impl>();
          OS_ASSERT(nodeListImpl);
          for (const auto& node : originalNodeList->nodes()) {
            const bool removed = nodeListImpl->removeNode(node);
            OS_ASSERT(removed);
            (void)removed;
          }
          for (const auto& node : m_originalExhaustNodes) {
            const bool added = nodeListImpl->addNode(node);
            OS_ASSERT(added);
            (void)added;
          }
        }

        auto connectionsImpl = m_connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
        OS_ASSERT(connectionsImpl);
        const bool restored = connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName,
                                                          m_originalExhaustTarget ? m_originalExhaustTarget->handle() : Handle(), false);
        OS_ASSERT(restored);
        (void)restored;

        for (auto& nodeList : m_createdNodeLists) {
          if (!m_terminal.model().getObject(nodeList.handle())) {
            continue;
          }
          auto nodeListImpl = nodeList.getImpl<detail::NodeList_Impl>();
          OS_ASSERT(nodeListImpl);
          for (const auto& node : nodeList.nodes()) {
            const bool removed = nodeListImpl->removeNode(node);
            OS_ASSERT(removed);
            (void)removed;
          }
          nodeList.remove();
        }
      }

      void cleanupPreparedState() {
        if (m_equipmentList && m_terminalRegistered) {
          const bool removed = m_equipmentList->removeEquipment(m_terminal);
          OS_ASSERT(removed);
          (void)removed;
        }
        if (m_projectedAirDistributionUnit) {
          if (m_createdAirDistributionUnit) {
            if (m_terminal.model().getObject(m_projectedAirDistributionUnit->handle())) {
              m_projectedAirDistributionUnit->remove();
            }
          } else if (m_originalAirDistributionUnit) {
            auto aduImpl = m_originalAirDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
            OS_ASSERT(aduImpl);
            const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
            bool restored = false;
            if (m_originalADUOutletTarget) {
              restored = aduImpl->setPointer(outletField, m_originalADUOutletTarget->handle(), false);
            } else {
              const bool pointerCleared = aduImpl->setPointer(outletField, Handle(), false);
              const bool rawRestored =
                aduImpl->openstudio::detail::IdfObject_Impl::setString(outletField, m_originalADUOutletNodeName.get_value_or(""), false);
              restored = pointerCleared && rawRestored;
            }
            OS_ASSERT(restored);
            (void)restored;
          }
        }

        if (m_exhaustProjectionChanged || !m_createdNodeLists.empty()) {
          restoreExhaustProjection();
        }
        if (m_secondaryOrInducedAirPointerChanged && m_secondaryOrInducedAirField) {
          auto terminalImpl = m_terminal.getImpl<detail::ModelObject_Impl>();
          OS_ASSERT(terminalImpl);
          const bool restored = terminalImpl->setPointer(
            *m_secondaryOrInducedAirField, m_originalSecondaryOrInducedAirTarget ? m_originalSecondaryOrInducedAirTarget->handle() : Handle(), false);
          OS_ASSERT(restored);
          (void)restored;
        }
        if (m_createdSecondaryOrInducedAirNode && m_secondaryOrInducedAirNode
            && m_terminal.model().getObject(m_secondaryOrInducedAirNode->handle())) {
          m_secondaryOrInducedAirNode->remove();
        }
      }

      State m_state = State::Prepared;
      ModelObject m_terminal;
      ZoneHVACEquipmentConnections m_connections;
      Node m_terminalOutlet;
      boost::optional<unsigned> m_secondaryOrInducedAirField;
      boost::optional<ModelObject> m_originalSecondaryOrInducedAirTarget;
      boost::optional<Node> m_secondaryOrInducedAirNode;
      boost::optional<ModelObject> m_originalExhaustTarget;
      std::vector<Node> m_originalExhaustNodes;
      std::set<Handle> m_originalNodeListHandles;
      std::vector<NodeList> m_createdNodeLists;
      boost::optional<ZoneHVACEquipmentList> m_equipmentList;
      boost::optional<ZoneHVACAirDistributionUnit> m_originalAirDistributionUnit;
      boost::optional<ZoneHVACAirDistributionUnit> m_projectedAirDistributionUnit;
      boost::optional<ModelObject> m_originalADUOutletTarget;
      boost::optional<std::string> m_originalADUOutletNodeName;
      bool m_createdSecondaryOrInducedAirNode = false;
      bool m_secondaryOrInducedAirPointerChanged = false;
      bool m_exhaustProjectionChanged = false;
      bool m_terminalWasRegistered = false;
      bool m_terminalRegistered = false;
      bool m_createdAirDistributionUnit = false;
    };

    // Prepares the canonical clone-last object graph before the new air-side
    // branch is touched. The plan owns every cloned terminal/child and every
    // provisional plant branch until commit. Abandoning it removes only those
    // objects and branches, leaving the source terminal graph untouched.
    class AirLoopHVAC_Impl::SingleDuctTerminalClonePlan
    {
      struct ZoneProjectionSnapshot;

     public:
      static std::unique_ptr<SingleDuctTerminalClonePlan> prepare(StraightComponent source, DemandBranchAttachmentFailureStage failureStage) {
        auto plan = std::unique_ptr<SingleDuctTerminalClonePlan>(new SingleDuctTerminalClonePlan(std::move(source), failureStage));
        if (!plan->describeOwnedTopology()) {
          return nullptr;
        }
        if (!plan->preflightPlantTopology()) {
          return nullptr;
        }
        if (!plan->cloneOwnedTopology()) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Failed to prepare the owned clone graph for trailing terminal '" << plan->m_source.nameString() << "'.");
          return nullptr;
        }
        if (failureStage == DemandBranchAttachmentFailureStage::AfterTerminalClonePrepared) {
          return nullptr;
        }
        if (!plan->reconnectPlantTopology()) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Failed to reconnect an owned clone to the source plant topology for trailing terminal '" << plan->m_source.nameString() << "'.");
          return nullptr;
        }
        if (failureStage == DemandBranchAttachmentFailureStage::AfterPlantReconnectionPrepared) {
          return nullptr;
        }
        plan->m_state = State::Prepared;
        return plan;
      }

      SingleDuctTerminalClonePlan(const SingleDuctTerminalClonePlan&) = delete;
      SingleDuctTerminalClonePlan& operator=(const SingleDuctTerminalClonePlan&) = delete;
      SingleDuctTerminalClonePlan(SingleDuctTerminalClonePlan&& other) noexcept
        : m_state(other.m_state),
          m_source(std::move(other.m_source)),
          m_terminal(std::move(other.m_terminal)),
          m_children(std::move(other.m_children)),
          m_zoneProjection(std::move(other.m_zoneProjection)),
          m_failureStage(other.m_failureStage) {
        other.m_state = State::MovedFrom;
      }
      SingleDuctTerminalClonePlan& operator=(SingleDuctTerminalClonePlan&&) = delete;

      ~SingleDuctTerminalClonePlan() {
        if (m_state != State::Committed && m_state != State::MovedFrom) {
          cleanupPreparedState();
        }
      }

      HVACComponent terminal() const {
        OS_ASSERT(m_terminal);
        return *m_terminal;
      }

      bool prepareZoneProjectionSnapshot(ThermalZone& thermalZone) {
        if (m_zoneProjection || thermalZone.model() != m_source.model()) {
          return false;
        }
        auto connections = thermalZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
        if (!connections) {
          return false;
        }
        auto equipmentList = connections->zoneHVACEquipmentList();
        m_zoneProjection = std::make_unique<ZoneProjectionSnapshot>(*connections, equipmentList);

        for (const auto& group : equipmentList.extensibleGroups()) {
          m_zoneProjection->equipmentRows.push_back(group.fieldsWithHandles(false));
        }
        for (const auto& node : m_source.model().getConcreteModelObjects<Node>()) {
          m_zoneProjection->originalNodeHandles.insert(node.handle());
        }
        for (const auto& nodeList : m_source.model().getConcreteModelObjects<NodeList>()) {
          m_zoneProjection->originalNodeListHandles.insert(nodeList.handle());
        }

        const auto exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
        if (auto managedField = connections->getField(exhaustField, false)) {
          const auto targetHandle = toUUID(*managedField);
          if (!targetHandle.isNull()) {
            if (auto target = m_source.model().getObject(targetHandle)) {
              m_zoneProjection->originalExhaustTarget = target->optionalCast<ModelObject>();
            }
          }
        }
        if (!m_zoneProjection->originalExhaustTarget) {
          auto workspaceImpl = connections->getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(workspaceImpl);
          m_zoneProjection->originalExhaustRaw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(exhaustField, false, true);
        }
        if (auto nodeList = m_zoneProjection->originalExhaustTarget ? m_zoneProjection->originalExhaustTarget->optionalCast<NodeList>()
                                                                    : boost::optional<NodeList>()) {
          m_zoneProjection->originalExhaustNodes = nodeList->nodes();
        }
        return true;
      }

      void commit() {
        OS_ASSERT(m_state == State::Prepared);
        m_state = State::Committed;
      }

     private:
      enum class State
      {
        Preparing,
        Prepared,
        Committed,
        MovedFrom,
      };

      enum class ChildRole
      {
        ReheatCoil,
        Fan,
        HeatingCoil,
        CoolingCoil,
      };

      struct PlantConnection
      {
        PlantConnection(PlantLoop plantLoop_, Branch branch_) : plantLoop(std::move(plantLoop_)), branch(std::move(branch_)) {}

        PlantLoop plantLoop;
        Branch branch;
        std::vector<Node> createdNodes;
        bool cloneReconnected = false;
      };

      struct OwnedChild
      {
        OwnedChild(ChildRole role_, unsigned terminalField_, HVACComponent source_)
          : role(role_), terminalField(terminalField_), source(std::move(source_)) {}

        ChildRole role;
        unsigned terminalField;
        HVACComponent source;
        boost::optional<HVACComponent> clone;
        boost::optional<PlantConnection> plantConnection;
      };

      struct ZoneProjectionSnapshot
      {
        ZoneProjectionSnapshot(ZoneHVACEquipmentConnections connections_, ZoneHVACEquipmentList equipmentList_)
          : connections(std::move(connections_)), equipmentList(std::move(equipmentList_)) {}

        ZoneHVACEquipmentConnections connections;
        ZoneHVACEquipmentList equipmentList;
        std::vector<std::vector<std::string>> equipmentRows;
        boost::optional<ModelObject> originalExhaustTarget;
        boost::optional<std::string> originalExhaustRaw;
        std::vector<Node> originalExhaustNodes;
        std::set<Handle> originalNodeHandles;
        std::set<Handle> originalNodeListHandles;
      };

      SingleDuctTerminalClonePlan(StraightComponent source, DemandBranchAttachmentFailureStage failureStage)
        : m_source(std::move(source)), m_failureStage(failureStage) {}

      bool addOwnedChild(ChildRole role, unsigned terminalField, bool required) {
        auto child = m_source.getModelObjectTarget<HVACComponent>(terminalField);
        if (!child) {
          return !required;
        }
        if (child->model() != m_source.model()) {
          return false;
        }
        m_children.emplace_back(role, terminalField, *child);
        return true;
      }

      bool describeOwnedTopology() {
        const auto type = m_source.iddObject().type();
        bool supported = true;
        if ((type == openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat)
            || (type == openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat)
            || (type == openstudio::IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_NoReheat)) {
          // The existing childless clone-last families have no owned graph.
        } else if (type == AirTerminalSingleDuctConstantVolumeReheat::iddObjectType()) {
          supported = addOwnedChild(ChildRole::ReheatCoil, openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, true);
        } else if (type == AirTerminalSingleDuctVAVReheat::iddObjectType()) {
          supported = addOwnedChild(ChildRole::ReheatCoil, openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName, true);
        } else if (type == AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType()) {
          supported = addOwnedChild(ChildRole::ReheatCoil, openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName, true);
        } else if (type == AirTerminalSingleDuctParallelPIUReheat::iddObjectType()) {
          supported = addOwnedChild(ChildRole::ReheatCoil, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, true)
                      && addOwnedChild(ChildRole::Fan, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, true);
        } else if (type == AirTerminalSingleDuctSeriesPIUReheat::iddObjectType()) {
          supported = addOwnedChild(ChildRole::ReheatCoil, openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, true)
                      && addOwnedChild(ChildRole::Fan, openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, true);
        } else if (type == AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType()) {
          // EnergyPlus has no canonical model wrapper for this family. Mirror
          // the established PIU owner contract for its required fan and coil.
          supported =
            addOwnedChild(ChildRole::Fan, openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName, true)
            && addOwnedChild(ChildRole::HeatingCoil, openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName, true);
        } else if (type == AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType()) {
          supported =
            addOwnedChild(ChildRole::CoolingCoil, openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName, true);
        } else if (type == AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType()) {
          // Match canonical reconnection order: heating, then cooling.
          supported =
            addOwnedChild(ChildRole::HeatingCoil, openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName, false)
            && addOwnedChild(ChildRole::CoolingCoil, openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName, false);
        } else if (type == AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType()) {
          // Match canonical reconnection order: required heating, then optional cooling.
          supported =
            addOwnedChild(ChildRole::HeatingCoil, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, true)
            && addOwnedChild(ChildRole::CoolingCoil, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName,
                             false);
        } else {
          supported = false;
        }

        if (!supported) {
          const auto iddName = m_source.iddObject().name();
          if (iddName == "AirTerminal:SingleDuct:Mixer") {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "Cannot clone trailing inlet-side mixer terminal '"
                       << m_source.nameString()
                       << "': its secondary-air inlet can be owned by downstream ZoneHVAC equipment, and epmodel cannot re-home that "
                          "external topology transactionally.");
          } else if (iddName == "AirTerminal:SingleDuct:UserDefined") {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "Cannot clone trailing user-defined terminal '"
                       << m_source.nameString()
                       << "': no canonical model wrapper defines ownership for its optional plant, program, tank, and secondary-air relationships.");
          } else {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "The trailing single-duct terminal '" << m_source.nameString()
                                                           << "' does not have a safe owner-aware clone-last contract in epmodel.");
          }
          return false;
        }

        const auto declaredChildren = m_source.children();
        if (declaredChildren.size() != m_children.size()) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Refusing to clone trailing terminal '" << m_source.nameString() << "' because its owned-child graph is incomplete or ambiguous.");
          return false;
        }
        std::set<Handle> expectedHandles;
        for (const auto& child : m_children) {
          expectedHandles.insert(child.source.handle());
        }
        for (const auto& child : declaredChildren) {
          if (!expectedHandles.contains(child.handle())) {
            return false;
          }
        }
        return true;
      }

      boost::optional<std::pair<unsigned, unsigned>> plantPorts(const HVACComponent& child) const {
        if (auto waterToAir = child.optionalCast<WaterToAirComponent>()) {
          return std::make_pair(waterToAir->waterInletPort(), waterToAir->waterOutletPort());
        }
        const auto type = child.iddObject().type();
        if ((type == openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam) || (type == openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam)
            || (type == openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam)) {
          auto straight = child.optionalCast<StraightComponent>();
          if (!straight) {
            return boost::none;
          }
          return std::make_pair(straight->inletPort(), straight->outletPort());
        }
        return boost::none;
      }

      boost::optional<Node> managedNodeTarget(const HVACComponent& component, unsigned field) const {
        const auto value = component.getField(field, false);
        if (value) {
          const auto targetHandle = toUUID(*value);
          if (!targetHandle.isNull()) {
            const auto target = component.model().getObject(targetHandle);
            return target ? target->optionalCast<Node>() : boost::none;
          }
        }

        auto workspaceImpl = component.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        const auto rawName = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (!rawName || rawName->empty()) {
          return boost::none;
        }
        return component.model().getConcreteModelObjectByName<Node>(*rawName);
      }

      bool validatePlantConnectors(const PlantLoop& plantLoop, const std::vector<Branch>& branches) const {
        if (branches.size() < 3u) {
          return false;
        }
        unsigned matchingSplitters = 0u;
        for (const auto& splitter : plantLoop.model().getConcreteModelObjects<ConnectorSplitter>()) {
          auto inlet = splitter.getModelObjectTarget<Branch>(splitter.inletPort());
          if (!inlet || *inlet != branches.front() || splitter.nextBranchIndex() != (branches.size() - 2u)) {
            continue;
          }
          bool allOutletsMatch = true;
          for (unsigned i = 0u; i + 2u < branches.size(); ++i) {
            auto outlet = splitter.getModelObjectTarget<Branch>(splitter.outletPort(i));
            if (!outlet || *outlet != branches[i + 1u]) {
              allOutletsMatch = false;
              break;
            }
          }
          if (allOutletsMatch) {
            ++matchingSplitters;
          }
        }
        unsigned matchingMixers = 0u;
        for (const auto& mixer : plantLoop.model().getConcreteModelObjects<ConnectorMixer>()) {
          auto outlet = mixer.getModelObjectTarget<Branch>(mixer.outletPort());
          if (!outlet || *outlet != branches.back() || mixer.nextBranchIndex() != (branches.size() - 2u)) {
            continue;
          }
          bool allInletsMatch = true;
          for (unsigned i = 0u; i + 2u < branches.size(); ++i) {
            auto inlet = mixer.getModelObjectTarget<Branch>(mixer.inletPort(i));
            if (!inlet || *inlet != branches[i + 1u]) {
              allInletsMatch = false;
              break;
            }
          }
          if (allInletsMatch) {
            ++matchingMixers;
          }
        }
        return matchingSplitters == 1u && matchingMixers == 1u;
      }

      bool capturePlantConnection(OwnedChild& child) {
        const auto ports = plantPorts(child.source);
        if (!ports) {
          return true;
        }

        const auto inletNode = managedNodeTarget(child.source, ports->first);
        const auto outletNode = managedNodeTarget(child.source, ports->second);
        const bool hasInlet = static_cast<bool>(inletNode);
        const bool hasOutlet = static_cast<bool>(outletNode);
        if (hasInlet != hasOutlet) {
          return false;
        }

        unsigned occurrences = 0u;
        for (const auto& plantLoop : m_source.model().getConcreteModelObjects<PlantLoop>()) {
          auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
          if (!branchList) {
            continue;
          }
          const auto branches = branchList->branches();
          for (unsigned branchIndex = 0u; branchIndex < branches.size(); ++branchIndex) {
            const auto componentRows = branches[branchIndex].extensibleGroups();
            for (unsigned componentIndex = 0u; componentIndex < componentRows.size(); ++componentIndex) {
              const auto componentField = componentRows[componentIndex].getField(openstudio::BranchExtensibleFields::ComponentName, false);
              if (!componentField || toUUID(*componentField) != child.source.handle()) {
                continue;
              }
              ++occurrences;
              if ((branches.size() < 3u) || (branchIndex == 0u) || (branchIndex + 1u == branches.size())
                  || !validatePlantConnectors(plantLoop, branches)) {
                LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                         "Plant preflight rejected owned child '" << child.source.nameString()
                                                                  << "' because its demand branch connector projection is malformed.");
                return false;
              }
              const auto branchInletNode = branches[branchIndex].componentInletNode(componentIndex);
              const auto branchOutletNode = branches[branchIndex].componentOutletNode(componentIndex);
              const auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();
              OS_ASSERT(plantLoopImpl);
              const auto inletBranch = inletNode ? plantLoopImpl->branchForNode(*inletNode) : boost::none;
              const auto outletBranch = outletNode ? plantLoopImpl->branchForNode(*outletNode) : boost::none;
              if (!branchInletNode || !branchOutletNode || !inletNode || !outletNode || !inletBranch || !outletBranch
                  || (*branchInletNode != *inletNode) || (*branchOutletNode != *outletNode) || (*inletBranch != branches[branchIndex])
                  || (*outletBranch != branches[branchIndex])) {
                LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                         "Plant preflight rejected owned child '"
                           << child.source.nameString() << "' because its water ports do not resolve to its authoritative demand branch row.");
                return false;
              }
              child.plantConnection = PlantConnection(plantLoop, branches[branchIndex]);
            }
          }
        }

        const auto childType = child.source.iddObject().type();
        const bool isUnnamedBeamCoil = (childType == openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam)
                                       || (childType == openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam)
                                       || (childType == openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam);
        if (isUnnamedBeamCoil && hasInlet && occurrences == 0u) {
          for (const auto& plantLoop : m_source.model().getConcreteModelObjects<PlantLoop>()) {
            const auto branchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
            if (!branchList) {
              continue;
            }
            const auto branches = branchList->branches();
            if (!validatePlantConnectors(plantLoop, branches)) {
              return false;
            }
            for (unsigned branchIndex = 1u; branchIndex + 1u < branches.size(); ++branchIndex) {
              const auto rowCount = branches[branchIndex].extensibleGroups().size();
              for (unsigned rowIndex = 0u; rowIndex < rowCount; ++rowIndex) {
                const auto rowInlet = branches[branchIndex].componentInletNode(rowIndex);
                const auto rowOutlet = branches[branchIndex].componentOutletNode(rowIndex);
                if (!rowInlet || !rowOutlet || *rowInlet != *inletNode || *rowOutlet != *outletNode) {
                  continue;
                }
                ++occurrences;
                child.plantConnection = PlantConnection(plantLoop, branches[branchIndex]);
              }
            }
          }
        }

        if (occurrences > 1u || hasInlet != (occurrences == 1u)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Plant preflight rejected owned child '" << child.source.nameString() << "' because resolved ports=" << hasInlet
                                                            << " and authoritative branch occurrences=" << occurrences << ".");
          return false;
        }
        return true;
      }

      bool preflightPlantTopology() {
        std::set<std::pair<Handle, Handle>> occupiedBranches;
        for (auto& child : m_children) {
          if (!capturePlantConnection(child)) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "Refusing to clone trailing terminal '" << m_source.nameString() << "' because an owned child has malformed plant topology.");
            return false;
          }
          if (child.plantConnection
              && !occupiedBranches.emplace(child.plantConnection->plantLoop.handle(), child.plantConnection->branch.handle()).second) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "Refusing to clone trailing terminal '" << m_source.nameString()
                                                             << "' because multiple owned children share one plant demand branch.");
            return false;
          }
        }
        return true;
      }

      bool clearNodeFields(IdfObject& idfObject) const {
        auto idfImpl = idfObject.getImpl<openstudio::detail::IdfObject_Impl>();
        OS_ASSERT(idfImpl);
        for (unsigned fieldIndex = 0u; fieldIndex < idfObject.numFields(); ++fieldIndex) {
          const auto iddField = idfObject.iddObject().getField(fieldIndex);
          if (iddField && iddField->properties().type == openstudio::IddFieldType::NodeType && !idfImpl->setString(fieldIndex, "", false)) {
            return false;
          }
        }
        return true;
      }

      bool copyConfigurationFields(const ModelObject& source, ModelObject& target, const std::set<unsigned>& excludedFields) const {
        auto targetImpl = target.getImpl<detail::ModelObject_Impl>();
        OS_ASSERT(targetImpl);
        const auto nameField = source.iddObject().nameFieldIndex();
        for (unsigned fieldIndex = 0u; fieldIndex < source.numFields(); ++fieldIndex) {
          const auto iddField = source.iddObject().getField(fieldIndex);
          if (!iddField || excludedFields.contains(fieldIndex) || (nameField && fieldIndex == *nameField)
              || iddField->properties().type == openstudio::IddFieldType::HandleType
              || iddField->properties().type == openstudio::IddFieldType::NodeType) {
            continue;
          }
          const auto value = source.getField(fieldIndex, false);
          if (!value) {
            continue;
          }
          const auto targetHandle = toUUID(*value);
          const bool copied = !targetHandle.isNull() && source.model().getObject(targetHandle)
                                ? targetImpl->setPointer(fieldIndex, targetHandle, false)
                                : targetImpl->openstudio::detail::IdfObject_Impl::setString(fieldIndex, *value, false);
          if (!copied) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "Failed to copy configuration field " << fieldIndex << " for owner-aware clone type '" << source.iddObject().name() << "'.");
            return false;
          }
        }
        return true;
      }

      boost::optional<HVACComponent> cloneComponentWithoutTopology(const HVACComponent& source) const {
        const auto sourceType = source.iddObject().type();
        boost::optional<HVACComponent> constructedClone;
        if (sourceType == openstudio::IddObjectType::OS_Coil_Cooling_CooledBeam) {
          constructedClone = CoilCoolingCooledBeam(source.model()).cast<HVACComponent>();
        } else if (sourceType == openstudio::IddObjectType::OS_Coil_Cooling_FourPipeBeam) {
          constructedClone = CoilCoolingFourPipeBeam(source.model()).cast<HVACComponent>();
        } else if (sourceType == openstudio::IddObjectType::OS_Coil_Heating_FourPipeBeam) {
          constructedClone = CoilHeatingFourPipeBeam(source.model()).cast<HVACComponent>();
        }
        if (constructedClone) {
          const auto ports = plantPorts(source);
          std::set<unsigned> excludedFields;
          if (ports) {
            excludedFields.insert(ports->first);
            excludedFields.insert(ports->second);
          }
          auto constructedObject = constructedClone->cast<ModelObject>();
          if (!copyConfigurationFields(source.cast<ModelObject>(), constructedObject, excludedFields)) {
            constructedClone->remove();
            return boost::none;
          }
          return constructedClone;
        }

        auto cloneIdfObject = source.idfObject().clone(false);
        if (!cloneIdfObject.setName(source.model().nextName(source.iddObject().type(), true))) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Failed to assign a distinct name to owned child clone type '" << source.iddObject().name() << "'.");
          return boost::none;
        }
        if (!clearNodeFields(cloneIdfObject)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Failed to clear node fields on owned child clone type '" << source.iddObject().name() << "'.");
          return boost::none;
        }
        auto cloneObject = source.model().addObject(cloneIdfObject);
        if (!cloneObject) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "Failed to add owned child clone type '" << source.iddObject().name() << "'.");
          return boost::none;
        }
        auto clone = cloneObject->optionalCast<HVACComponent>();
        if (!clone) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                   "Owned child clone type '" << source.iddObject().name() << "' did not resolve as an HVACComponent.");
          cloneObject->remove();
          return boost::none;
        }
        return *clone;
      }

      bool assignOwnedChild(OwnedChild& child) {
        OS_ASSERT(m_terminal);
        OS_ASSERT(child.clone);
        auto clone = *child.clone;
        const auto type = m_source.iddObject().type();
        if (type == AirTerminalSingleDuctConstantVolumeReheat::iddObjectType()) {
          return m_terminal->cast<AirTerminalSingleDuctConstantVolumeReheat>().setReheatCoil(clone);
        }
        if (type == AirTerminalSingleDuctVAVReheat::iddObjectType()) {
          return m_terminal->cast<AirTerminalSingleDuctVAVReheat>().setReheatCoil(clone);
        }
        if (type == AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType()) {
          return m_terminal->cast<AirTerminalSingleDuctVAVHeatAndCoolReheat>().setReheatCoil(clone);
        }
        if (type == AirTerminalSingleDuctParallelPIUReheat::iddObjectType()) {
          auto terminal = m_terminal->cast<AirTerminalSingleDuctParallelPIUReheat>();
          return child.role == ChildRole::Fan ? terminal.setFan(clone) : terminal.setReheatCoil(clone);
        }
        if (type == AirTerminalSingleDuctSeriesPIUReheat::iddObjectType()) {
          auto terminal = m_terminal->cast<AirTerminalSingleDuctSeriesPIUReheat>();
          return child.role == ChildRole::Fan ? terminal.setFan(clone) : terminal.setReheatCoil(clone);
        }
        if (type == AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType()) {
          auto terminal = m_terminal->cast<AirTerminalSingleDuctVAVReheatVariableSpeedFan>();
          return child.role == ChildRole::Fan ? terminal.setFan(clone) : terminal.setHeatingCoil(clone);
        }
        if (type == AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType()) {
          return m_terminal->cast<AirTerminalSingleDuctConstantVolumeCooledBeam>().setCoolingCoil(clone);
        }
        if (type == AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType()) {
          auto terminal = m_terminal->cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam>();
          return child.role == ChildRole::HeatingCoil ? terminal.setHeatingCoil(clone) : terminal.setCoolingCoil(clone);
        }
        if (type == AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType()) {
          auto terminal = m_terminal->cast<AirTerminalSingleDuctConstantVolumeFourPipeInduction>();
          return child.role == ChildRole::HeatingCoil ? terminal.setHeatingCoil(clone) : terminal.setCoolingCoil(clone);
        }
        return false;
      }

      bool cloneOwnedTopology() {
        if (m_source.iddObject().type() == AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType()) {
          auto constructedTerminal = AirTerminalSingleDuctConstantVolumeCooledBeam(m_source.model());
          std::set<unsigned> excludedFields{m_source.inletPort(), m_source.outletPort()};
          for (const auto& child : m_children) {
            excludedFields.insert(child.terminalField);
          }
          auto sourceObject = m_source.cast<ModelObject>();
          auto constructedObject = constructedTerminal.cast<ModelObject>();
          if (!copyConfigurationFields(sourceObject, constructedObject, excludedFields)) {
            return false;
          }
          m_terminal = constructedTerminal.cast<HVACComponent>();
        } else {
          auto terminalIdfObject = m_source.idfObject().clone(false);
          if (!terminalIdfObject.setName(m_source.model().nextName(m_source.iddObject().type(), true)) || !clearNodeFields(terminalIdfObject)) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "Failed to clear the cloned terminal's name or node fields.");
            return false;
          }
          for (const auto& child : m_children) {
            if (!terminalIdfObject.setString(child.terminalField, "")) {
              LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "Failed to clear a cloned terminal owned-child field.");
              return false;
            }
          }

          boost::optional<unsigned> containedMixerField;
          const auto terminalType = m_source.iddObject().type();
          if (terminalType == AirTerminalSingleDuctParallelPIUReheat::iddObjectType()) {
            containedMixerField = openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName;
          } else if (terminalType == AirTerminalSingleDuctSeriesPIUReheat::iddObjectType()) {
            containedMixerField = openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName;
          } else if (terminalType == AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType()) {
            containedMixerField = openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName;
          }
          if (containedMixerField && !terminalIdfObject.setString(*containedMixerField, "")) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "Failed to clear a cloned terminal's contained zone mixer field.");
            return false;
          }

          auto terminalObject = m_source.model().addObject(terminalIdfObject);
          if (!terminalObject) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "Failed to add the cloned terminal object.");
            return false;
          }
          m_terminal = terminalObject->optionalCast<HVACComponent>();
          if (!m_terminal || !m_terminal->optionalCast<StraightComponent>()) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "The cloned terminal object did not resolve as a straight HVAC component.");
            terminalObject->remove();
            m_terminal = boost::none;
            return false;
          }
        }

        for (auto& child : m_children) {
          child.clone = cloneComponentWithoutTopology(child.source);
          if (!child.clone) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "Failed to clone owned child type '" << child.source.iddObject().name() << "'.");
            return false;
          }
          if (!assignOwnedChild(child)) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                     "Failed to assign cloned owned child type '" << child.source.iddObject().name() << "' to its terminal.");
            return false;
          }
        }

        const auto clonedChildren = m_terminal->children();
        if (clonedChildren.size() != m_children.size()) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "The cloned terminal's owned-child count did not match its source.");
          return false;
        }
        std::set<Handle> expectedHandles;
        for (const auto& child : m_children) {
          OS_ASSERT(child.clone);
          expectedHandles.insert(child.clone->handle());
        }
        for (const auto& child : clonedChildren) {
          if (!expectedHandles.contains(child.handle())) {
            LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC", "The cloned terminal resolved an unexpected owned-child handle.");
            return false;
          }
        }
        return true;
      }

      bool reconnectPlantTopology() {
        unsigned connectedChildren = 0u;
        for (auto& child : m_children) {
          if (!child.plantConnection) {
            continue;
          }
          OS_ASSERT(child.clone);
          std::set<Handle> originalNodeHandles;
          for (const auto& node : m_source.model().getConcreteModelObjects<Node>()) {
            originalNodeHandles.insert(node.handle());
          }
          const bool connected = child.plantConnection->plantLoop.addDemandBranchForComponent(*child.clone);
          for (const auto& node : m_source.model().getConcreteModelObjects<Node>()) {
            if (!originalNodeHandles.contains(node.handle())) {
              child.plantConnection->createdNodes.push_back(node);
            }
          }
          if (!connected) {
            return false;
          }
          child.plantConnection->cloneReconnected = true;
          ++connectedChildren;
          if ((m_failureStage == DemandBranchAttachmentFailureStage::AfterFirstPlantReconnectionPrepared) && (connectedChildren == 1u)) {
            return false;
          }
        }
        return true;
      }

      void restoreEquipmentRows() {
        if (!m_zoneProjection || !m_source.model().getObject(m_zoneProjection->equipmentList.handle())) {
          return;
        }
        auto groups = m_zoneProjection->equipmentList.extensibleGroups();
        while (groups.size() > m_zoneProjection->equipmentRows.size()) {
          m_zoneProjection->equipmentList.eraseExtensibleGroup(static_cast<unsigned>(groups.size() - 1u));
          groups = m_zoneProjection->equipmentList.extensibleGroups();
        }
        OS_ASSERT(groups.size() == m_zoneProjection->equipmentRows.size());
        if (groups.size() != m_zoneProjection->equipmentRows.size()) {
          return;
        }
        for (unsigned i = 0u; i < groups.size(); ++i) {
          const bool restored = groups[i].setFields(m_zoneProjection->equipmentRows[i]);
          OS_ASSERT(restored);
          (void)restored;
        }
      }

      void restoreExhaustProjection() {
        if (!m_zoneProjection || !m_source.model().getObject(m_zoneProjection->connections.handle())) {
          return;
        }
        const auto exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
        auto connectionsImpl = m_zoneProjection->connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
        OS_ASSERT(connectionsImpl);
        const bool cleared = connectionsImpl->setPointer(exhaustField, Handle(), false);
        OS_ASSERT(cleared);
        (void)cleared;

        for (auto& nodeList : m_source.model().getConcreteModelObjects<NodeList>()) {
          if (m_zoneProjection->originalNodeListHandles.contains(nodeList.handle())) {
            continue;
          }
          auto nodeListImpl = nodeList.getImpl<detail::NodeList_Impl>();
          OS_ASSERT(nodeListImpl);
          for (const auto& node : nodeList.nodes()) {
            const bool removed = nodeListImpl->removeNode(node);
            OS_ASSERT(removed);
            (void)removed;
          }
          nodeList.remove();
        }

        if (auto originalNodeList = m_zoneProjection->originalExhaustTarget ? m_zoneProjection->originalExhaustTarget->optionalCast<NodeList>()
                                                                            : boost::optional<NodeList>()) {
          auto nodeListImpl = originalNodeList->getImpl<detail::NodeList_Impl>();
          OS_ASSERT(nodeListImpl);
          for (const auto& node : originalNodeList->nodes()) {
            const bool removed = nodeListImpl->removeNode(node);
            OS_ASSERT(removed);
            (void)removed;
          }
          for (const auto& node : m_zoneProjection->originalExhaustNodes) {
            const bool added = nodeListImpl->addNode(node);
            OS_ASSERT(added);
            (void)added;
          }
        }

        bool restored = false;
        if (m_zoneProjection->originalExhaustTarget) {
          restored = connectionsImpl->setPointer(exhaustField, m_zoneProjection->originalExhaustTarget->handle(), false);
        } else {
          const bool pointerCleared = connectionsImpl->setPointer(exhaustField, Handle(), false);
          const bool rawRestored = connectionsImpl->openstudio::detail::IdfObject_Impl::setString(
            exhaustField, m_zoneProjection->originalExhaustRaw.get_value_or(""), false);
          restored = pointerCleared && rawRestored;
        }
        OS_ASSERT(restored);
        (void)restored;
      }

      void cleanupPreparedState() {
        for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
          if (!(it->clone && it->plantConnection)) {
            continue;
          }
          if (it->plantConnection->cloneReconnected) {
            const bool removed = it->plantConnection->plantLoop.removeDemandBranchWithComponent(*it->clone);
            OS_ASSERT(removed);
            (void)removed;
            it->plantConnection->cloneReconnected = false;
          }
          for (auto& node : it->plantConnection->createdNodes) {
            if (!m_source.model().getObject(node.handle())) {
              continue;
            }
            const auto removedNode = m_source.model().removeObject(node.handle());
            OS_ASSERT(removedNode);
            (void)removedNode;
          }
          it->plantConnection->createdNodes.clear();
        }

        std::vector<ZoneHVACAirDistributionUnit> clonedAirDistributionUnits;
        if (m_terminal) {
          for (const auto& source : m_terminal->getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
            if (auto airDistributionUnit = source.optionalCast<ZoneHVACAirDistributionUnit>()) {
              clonedAirDistributionUnits.push_back(*airDistributionUnit);
            }
          }
        }

        if (m_terminal && m_source.model().getObject(m_terminal->handle())) {
          const auto terminalHandle = m_terminal->handle();
          m_terminal->remove();
          OS_ASSERT(!m_source.model().getObject(terminalHandle));
        }
        for (auto& airDistributionUnit : clonedAirDistributionUnits) {
          if (m_source.model().getObject(airDistributionUnit.handle())) {
            airDistributionUnit.remove();
          }
        }
        restoreEquipmentRows();
        restoreExhaustProjection();
        for (auto& child : m_children) {
          if (child.clone && m_source.model().getObject(child.clone->handle())) {
            const auto childHandle = child.clone->handle();
            child.clone->remove();
            OS_ASSERT(!m_source.model().getObject(childHandle));
          }
        }
        if (m_zoneProjection) {
          for (auto& node : m_source.model().getConcreteModelObjects<Node>()) {
            if (m_zoneProjection->originalNodeHandles.contains(node.handle())) {
              continue;
            }
            const bool removed = m_source.model().removeObject(node.handle());
            OS_ASSERT(removed);
            (void)removed;
          }
        }
      }

      State m_state = State::Preparing;
      StraightComponent m_source;
      boost::optional<HVACComponent> m_terminal;
      std::vector<OwnedChild> m_children;
      std::unique_ptr<ZoneProjectionSnapshot> m_zoneProjection;
      DemandBranchAttachmentFailureStage m_failureStage = DemandBranchAttachmentFailureStage::None;
    };

    // Owns the whole provisional demand-branch attachment, not merely the
    // splitter/mixer row pair. A prepared transaction may also own a new
    // branch node and reversible zone-boundary wiring. Until commit, its
    // destructor restores the exact preexisting branch and zone state.
    class AirLoopHVAC_Impl::DemandBranchAttachmentPlan
    {
     public:
      static std::unique_ptr<DemandBranchAttachmentPlan> prepare(AirLoopHVAC& airLoop);
      static std::unique_ptr<DemandBranchAttachmentPlan> prepareForZone(AirLoopHVAC& airLoop);

      DemandBranchAttachmentPlan(const DemandBranchAttachmentPlan&) = delete;
      DemandBranchAttachmentPlan& operator=(const DemandBranchAttachmentPlan&) = delete;
      DemandBranchAttachmentPlan(DemandBranchAttachmentPlan&& other) noexcept;
      DemandBranchAttachmentPlan& operator=(DemandBranchAttachmentPlan&&) = delete;
      ~DemandBranchAttachmentPlan();

      Node node() const;
      unsigned branchIndex() const;
      bool prepareZoneAttachment(ThermalZone& thermalZone);
      bool prepareTerminalAttachment(HVACComponent& terminal, Node& node);
      bool commit(DemandBranchAttachmentFailureStage failureStage = DemandBranchAttachmentFailureStage::None);

     private:
      enum class State
      {
        Prepared,
        Committed,
        MovedFrom,
      };

      struct ProvisionalZoneAttachment
      {
        explicit ProvisionalZoneAttachment(ThermalZone thermalZone_) : thermalZone(std::move(thermalZone_)) {}

        ThermalZone thermalZone;
        std::vector<ModelObject> idealAirLoadsToRemove;
        bool createdConnections = false;
        boost::optional<ZoneHVACEquipmentConnections> connections;
        boost::optional<ZoneHVACEquipmentList> createdEquipmentList;
        boost::optional<ModelObject> originalInletFieldTarget;
        boost::optional<ModelObject> originalReturnFieldTarget;
        std::vector<Node> originalInletNodes;
        std::vector<Node> originalReturnNodes;
        std::set<Handle> originalNodeListHandles;
        std::vector<NodeList> createdNodeLists;
        boost::optional<Node> createdZoneInletNode;
        boost::optional<Node> createdZoneReturnNode;
      };

      DemandBranchAttachmentPlan(AirLoopHVAC airLoop, AirLoopHVACZoneSplitter splitter, AirLoopHVACZoneMixer mixer, unsigned branchIndex,
                                 Node branchNode, bool reusedBranch, bool createdBranchNode,
                                 boost::optional<ModelObject> originalSplitterOutlet = boost::none,
                                 boost::optional<ModelObject> originalMixerInlet = boost::none, bool preserveSplitterOutletForZone = false,
                                 boost::optional<ModelObject> existingTerminalForZone = boost::none);

      void cleanupPreparedState();
      void captureCreatedZoneNodeLists();
      void restoreZoneNodeField(unsigned field, const boost::optional<ModelObject>& originalTarget, const std::vector<Node>& originalNodes);
      void removeCreatedNode(const boost::optional<Node>& node);

      State m_state = State::Prepared;
      AirLoopHVAC m_airLoop;
      AirLoopHVACZoneSplitter m_splitter;
      AirLoopHVACZoneMixer m_mixer;
      unsigned m_branchIndex;
      Node m_branchNode;
      bool m_reusedBranch = false;
      bool m_createdBranchNode = false;
      bool m_splitterRowAdded = false;
      bool m_mixerRowAdded = false;
      boost::optional<ModelObject> m_originalSplitterOutlet;
      boost::optional<ModelObject> m_originalMixerInlet;
      bool m_preserveSplitterOutletForZone = false;
      boost::optional<ModelObject> m_existingTerminalForZone;
      bool m_terminalAttachmentAttempted = false;
      std::unique_ptr<ProvisionalZoneAttachment> m_zoneAttachment;
      std::unique_ptr<DualDuctTerminalInsertionPlan> m_dualDuctTerminalInsertionPlan;
    };

    class AirLoopHVAC_Impl::DualDuctZoneAttachment
    {
     public:
      static std::unique_ptr<DualDuctZoneAttachment> prepare(AirLoopHVAC& airLoop, ThermalZone& thermalZone, Mixer& terminal,
                                                             DualDuctZoneAttachmentFailureStage failureStage);

      DualDuctZoneAttachment(const DualDuctZoneAttachment&) = delete;
      DualDuctZoneAttachment& operator=(const DualDuctZoneAttachment&) = delete;
      DualDuctZoneAttachment(DualDuctZoneAttachment&&) = default;
      DualDuctZoneAttachment& operator=(DualDuctZoneAttachment&&) = delete;
      ~DualDuctZoneAttachment();

      void commit();

     private:
      enum class State
      {
        Prepared,
        Committed,
      };

      struct ProvisionalState
      {
        boost::optional<ZoneHVACAirDistributionUnit> airDistributionUnit;
        boost::optional<Node> returnNode;
        boost::optional<ZoneHVACEquipmentConnections> zoneConnections;
        boost::optional<ZoneHVACEquipmentList> equipmentList;
        boost::optional<Node> zoneAirNode;
      };

      DualDuctZoneAttachment(AirLoopHVAC airLoop, ThermalZone thermalZone, Mixer terminal, Node zoneInletNode, AirLoopHVACZoneMixer zoneMixer,
                             unsigned branchIndex, ZoneHVACEquipmentConnections zoneConnections, ZoneHVACEquipmentList equipmentList);

      void prepareReturnNode();
      bool prepareZoneEquipment();
      void cleanupProvisionalState();

      State m_state = State::Prepared;
      AirLoopHVAC m_airLoop;
      ThermalZone m_thermalZone;
      Mixer m_terminal;
      Node m_zoneInletNode;
      AirLoopHVACZoneMixer m_zoneMixer;
      unsigned m_branchIndex;
      ZoneHVACEquipmentConnections m_zoneConnections;
      ZoneHVACEquipmentList m_equipmentList;
      boost::optional<Node> m_zoneReturnNode;
      bool m_disableIdealAirLoads = false;
      bool m_registerEquipment = false;
      boost::optional<ZoneHVACAirDistributionUnit> m_airDistributionUnitToSynchronize;
      std::unique_ptr<ProvisionalState> m_provisionalState;
    };

    class AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan
    {
     public:
      static std::unique_ptr<DualDuctTerminalInsertionPlan> prepare(Mixer& terminal, Node& node);

      DualDuctTerminalInsertionPlan(const DualDuctTerminalInsertionPlan&) = delete;
      DualDuctTerminalInsertionPlan& operator=(const DualDuctTerminalInsertionPlan&) = delete;
      DualDuctTerminalInsertionPlan(DualDuctTerminalInsertionPlan&&) = default;
      DualDuctTerminalInsertionPlan& operator=(DualDuctTerminalInsertionPlan&&) = delete;
      ~DualDuctTerminalInsertionPlan();

      void commit();

     private:
      enum class State
      {
        Prepared,
        Committed,
      };

      struct ProvisionalObjects
      {
        boost::optional<ZoneHVACAirDistributionUnit> airDistributionUnit;
        boost::optional<AirLoopHVACSupplyPath> supplyPath;
        boost::optional<AirLoopHVACZoneSplitter> splitter;
        std::vector<Node> nodes;
      };

      DualDuctTerminalInsertionPlan(Mixer terminal, Node outletNode, AirLoopHVAC airLoop, AirLoopHVACZoneSplitter primarySplitter,
                                    unsigned primaryBranchIndex);

      bool prepareSecondaryDemandPath();
      void prepareTerminalInletNodes();
      bool prepareZoneEquipment(const boost::optional<ThermalZone>& servedZone);
      Node resolveOrCreateProvisionalNode(const std::string& name);
      void cleanupProvisionalObjects();

      State m_state = State::Prepared;
      Mixer m_terminal;
      Node m_outletNode;
      AirLoopHVAC m_airLoop;
      AirLoopHVACZoneSplitter m_primarySplitter;
      unsigned m_primaryBranchIndex;
      boost::optional<Node> m_primaryInletNode;
      boost::optional<Node> m_secondaryInletNode;
      boost::optional<Node> m_secondaryDemandInletNode;
      boost::optional<NodeList> m_demandInletNodeListToAppend;
      boost::optional<AirLoopHVACSupplyPath> m_secondarySupplyPath;
      boost::optional<AirLoopHVACZoneSplitter> m_secondarySplitter;
      unsigned m_secondaryBranchIndex = 0u;
      boost::optional<AirLoopHVACSupplyPath> m_supplyPathToAppendSplitter;
      boost::optional<ZoneHVACEquipmentList> m_equipmentListToRegister;
      boost::optional<ZoneHVACAirDistributionUnit> m_airDistributionUnitToSynchronize;
      std::unique_ptr<ProvisionalObjects> m_provisionalObjects;
    };

    boost::optional<double> AirLoopHVAC_Impl::designSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVACFields::DesignSupplyAirFlowRate, true);
    }

    bool AirLoopHVAC_Impl::isDesignSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVACFields::DesignSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVAC_Impl::setDesignSupplyAirFlowRate(double designSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVACFields::DesignSupplyAirFlowRate, designSupplyAirFlowRate);
    }

    void AirLoopHVAC_Impl::resetDesignSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVACFields::DesignSupplyAirFlowRate, ""));
    }

    void AirLoopHVAC_Impl::autosizeDesignSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVACFields::DesignSupplyAirFlowRate, "autosize"));
    }

    double AirLoopHVAC_Impl::designReturnAirFlowFractionofSupplyAirFlow() const {
      const auto value = getDouble(openstudio::AirLoopHVACFields::DesignReturnAirFlowFractionofSupplyAirFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVAC_Impl::setDesignReturnAirFlowFractionofSupplyAirFlow(double designReturnAirFlowFractionofSupplyAirFlow) {
      return setDouble(openstudio::AirLoopHVACFields::DesignReturnAirFlowFractionofSupplyAirFlow, designReturnAirFlowFractionofSupplyAirFlow);
    }

    AirLoopHVAC_Impl::DemandBranchAttachmentPlan::DemandBranchAttachmentPlan(
      AirLoopHVAC airLoop, AirLoopHVACZoneSplitter splitter, AirLoopHVACZoneMixer mixer, unsigned branchIndex, Node branchNode, bool reusedBranch,
      bool createdBranchNode, boost::optional<ModelObject> originalSplitterOutlet, boost::optional<ModelObject> originalMixerInlet,
      bool preserveSplitterOutletForZone, boost::optional<ModelObject> existingTerminalForZone)
      : m_airLoop(std::move(airLoop)),
        m_splitter(std::move(splitter)),
        m_mixer(std::move(mixer)),
        m_branchIndex(branchIndex),
        m_branchNode(std::move(branchNode)),
        m_reusedBranch(reusedBranch),
        m_createdBranchNode(createdBranchNode),
        m_originalSplitterOutlet(std::move(originalSplitterOutlet)),
        m_originalMixerInlet(std::move(originalMixerInlet)),
        m_preserveSplitterOutletForZone(preserveSplitterOutletForZone),
        m_existingTerminalForZone(std::move(existingTerminalForZone)) {}

    AirLoopHVAC_Impl::DemandBranchAttachmentPlan::DemandBranchAttachmentPlan(DemandBranchAttachmentPlan&& other) noexcept
      : m_state(other.m_state),
        m_airLoop(std::move(other.m_airLoop)),
        m_splitter(std::move(other.m_splitter)),
        m_mixer(std::move(other.m_mixer)),
        m_branchIndex(other.m_branchIndex),
        m_branchNode(std::move(other.m_branchNode)),
        m_reusedBranch(other.m_reusedBranch),
        m_createdBranchNode(other.m_createdBranchNode),
        m_splitterRowAdded(other.m_splitterRowAdded),
        m_mixerRowAdded(other.m_mixerRowAdded),
        m_originalSplitterOutlet(std::move(other.m_originalSplitterOutlet)),
        m_originalMixerInlet(std::move(other.m_originalMixerInlet)),
        m_preserveSplitterOutletForZone(other.m_preserveSplitterOutletForZone),
        m_existingTerminalForZone(std::move(other.m_existingTerminalForZone)),
        m_terminalAttachmentAttempted(other.m_terminalAttachmentAttempted),
        m_zoneAttachment(std::move(other.m_zoneAttachment)),
        m_dualDuctTerminalInsertionPlan(std::move(other.m_dualDuctTerminalInsertionPlan)) {
      other.m_state = State::MovedFrom;
      other.m_reusedBranch = false;
      other.m_createdBranchNode = false;
      other.m_splitterRowAdded = false;
      other.m_mixerRowAdded = false;
      other.m_preserveSplitterOutletForZone = false;
      other.m_terminalAttachmentAttempted = false;
    }

    AirLoopHVAC_Impl::DemandBranchAttachmentPlan::~DemandBranchAttachmentPlan() {
      if (m_state == State::Prepared) {
        cleanupPreparedState();
      }
    }

    std::unique_ptr<AirLoopHVAC_Impl::DemandBranchAttachmentPlan> AirLoopHVAC_Impl::DemandBranchAttachmentPlan::prepare(AirLoopHVAC& airLoop) {
      auto splitter = airLoop.zoneSplitter();
      auto mixer = airLoop.zoneMixer();
      const auto splitterOutlets = splitter.outletModelObjects();
      const auto mixerInlets = mixer.inletModelObjects();

      // The canonical empty loop has one shared splitter/mixer node. It is
      // model-owned and is never enrolled for deletion by the reservation.
      if (splitterOutlets.size() == 1u && mixerInlets.size() == 1u && splitterOutlets.front() == mixerInlets.front()) {
        auto branchNode = splitterOutlets.front().optionalCast<Node>();
        if (!branchNode) {
          return nullptr;
        }
        return std::unique_ptr<DemandBranchAttachmentPlan>(
          new DemandBranchAttachmentPlan(airLoop, splitter, mixer, 0u, *branchNode, true, false, splitterOutlets.front(), mixerInlets.front()));
      }

      const auto branchIndex = splitter.nextBranchIndex();
      // Canonicalization guarantees paired demand rows. Refuse to overwrite a
      // mismatched mixer row if malformed runtime state violates that contract.
      if (mixer.nextBranchIndex() != branchIndex) {
        return nullptr;
      }

      const auto branchNodeName = airLoop.nameString() + " Demand Branch Node " + std::to_string(branchIndex + 1u);
      const bool branchNodeExisted = static_cast<bool>(airLoop.model().getConcreteModelObjectByName<Node>(branchNodeName));
      auto branchNode = airLoop.model().getOrCreateTransientByName<Node>(branchNodeName);
      auto reservation = std::unique_ptr<DemandBranchAttachmentPlan>(
        new DemandBranchAttachmentPlan(airLoop, splitter, mixer, branchIndex, branchNode, false, !branchNodeExisted));

      // The setters push their extensible row before writing its final pointer.
      // Enroll each row first so a failed final write still removes the blank
      // row created by that setter.
      reservation->m_splitterRowAdded = true;
      if (!reservation->m_splitter.setOutletModelObject(branchIndex, branchNode.cast<ModelObject>())) {
        return nullptr;
      }
      reservation->m_mixerRowAdded = true;
      if (!reservation->m_mixer.setInletModelObject(branchIndex, branchNode.cast<ModelObject>())) {
        return nullptr;
      }
      return reservation;
    }

    std::unique_ptr<AirLoopHVAC_Impl::DemandBranchAttachmentPlan> AirLoopHVAC_Impl::DemandBranchAttachmentPlan::prepareForZone(AirLoopHVAC& airLoop) {
      auto airLoopImpl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      if (auto terminal = airLoopImpl->reusableSingleDuctTerminalForZone()) {
        auto splitter = airLoop.zoneSplitter();
        auto mixer = airLoop.zoneMixer();
        const auto splitterOutlets = splitter.outletModelObjects();
        const auto mixerInlets = mixer.inletModelObjects();
        if (splitterOutlets.empty() || splitterOutlets.size() != mixerInlets.size()) {
          return nullptr;
        }

        const auto branchIndex = static_cast<unsigned>(splitterOutlets.size() - 1u);
        auto terminalOutletNode = mixerInlets[branchIndex].optionalCast<Node>();
        if (!terminalOutletNode) {
          return nullptr;
        }

        // The trailing terminal already owns the splitter-side inlet. Enroll
        // its outlet node as the future zone inlet and leave that upstream
        // endpoint untouched throughout preparation.
        return std::unique_ptr<DemandBranchAttachmentPlan>(
          new DemandBranchAttachmentPlan(airLoop, splitter, mixer, branchIndex, *terminalOutletNode, true, false, splitterOutlets[branchIndex],
                                         mixerInlets[branchIndex], true, terminal->cast<ModelObject>()));
      }

      return prepare(airLoop);
    }

    Node AirLoopHVAC_Impl::DemandBranchAttachmentPlan::node() const {
      return m_branchNode;
    }

    unsigned AirLoopHVAC_Impl::DemandBranchAttachmentPlan::branchIndex() const {
      return m_branchIndex;
    }

    bool AirLoopHVAC_Impl::DemandBranchAttachmentPlan::prepareZoneAttachment(ThermalZone& thermalZone) {
      if (m_state != State::Prepared || m_zoneAttachment || m_terminalAttachmentAttempted || thermalZone.model() != m_airLoop.model()) {
        return false;
      }

      m_zoneAttachment = std::make_unique<ProvisionalZoneAttachment>(thermalZone);
      auto& zoneState = *m_zoneAttachment;
      for (const auto& equipment : thermalZone.equipment()) {
        if (equipment.iddObject().type() != openstudio::IddObjectType::ZoneHVAC_IdealLoadsAirSystem) {
          continue;
        }
        auto idealAirLoads = equipment.optionalCast<HVACComponent>();
        if (!idealAirLoads || !idealAirLoads->isRemovable()) {
          return false;
        }
        zoneState.idealAirLoadsToRemove.push_back(equipment);
      }
      for (const auto& nodeList : m_airLoop.model().getConcreteModelObjects<NodeList>()) {
        zoneState.originalNodeListHandles.insert(nodeList.handle());
      }

      auto thermalZoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(thermalZoneImpl);
      auto connections = thermalZoneImpl->zoneHVACEquipmentConnections();
      zoneState.createdConnections = !connections;

      const auto zoneInletNodeName = thermalZone.nameString() + " Demand Branch Node";
      const bool zoneInletNodeExisted =
        m_preserveSplitterOutletForZone || static_cast<bool>(m_airLoop.model().getConcreteModelObjectByName<Node>(zoneInletNodeName));
      const auto zoneReturnNodeName = thermalZone.nameString() + " Demand Return Node";
      const bool zoneReturnNodeExisted = static_cast<bool>(m_airLoop.model().getConcreteModelObjectByName<Node>(zoneReturnNodeName));

      if (!connections) {
        connections = thermalZoneImpl->getZoneHVACEquipmentConnections();
        zoneState.createdEquipmentList = connections->zoneHVACEquipmentList();
      }
      captureCreatedZoneNodeLists();
      zoneState.connections = *connections;
      zoneState.originalInletNodes = connections->zoneAirInletNodes();
      zoneState.originalReturnNodes = connections->zoneReturnAirNodes();
      if (auto target = connections->getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName)) {
        zoneState.originalInletFieldTarget = target->optionalCast<ModelObject>();
      }
      if (auto target = connections->getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName)) {
        zoneState.originalReturnFieldTarget = target->optionalCast<ModelObject>();
      }

      auto zoneInletNode = m_preserveSplitterOutletForZone ? m_branchNode : m_airLoop.model().getOrCreateTransientByName<Node>(zoneInletNodeName);
      auto zoneReturnNode = m_airLoop.model().getOrCreateTransientByName<Node>(zoneReturnNodeName);
      if (!zoneInletNodeExisted) {
        zoneState.createdZoneInletNode = zoneInletNode;
      }
      if (!zoneReturnNodeExisted) {
        zoneState.createdZoneReturnNode = zoneReturnNode;
      }

      if ((!m_preserveSplitterOutletForZone && !m_splitter.setOutletModelObject(m_branchIndex, zoneInletNode.cast<ModelObject>()))
          || !m_mixer.setInletModelObject(m_branchIndex, zoneReturnNode.cast<ModelObject>())) {
        return false;
      }

      auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(connectionsImpl);
      const bool inletAdded = connectionsImpl->addZoneAirInletNode(zoneInletNode);
      captureCreatedZoneNodeLists();
      if (!inletAdded) {
        return false;
      }

      const bool returnAdded = connectionsImpl->addZoneReturnAirNode(zoneReturnNode);
      captureCreatedZoneNodeLists();
      if (!returnAdded) {
        return false;
      }

      return true;
    }

    void AirLoopHVAC_Impl::DemandBranchAttachmentPlan::captureCreatedZoneNodeLists() {
      OS_ASSERT(m_zoneAttachment);
      for (const auto& nodeList : m_airLoop.model().getConcreteModelObjects<NodeList>()) {
        if (m_zoneAttachment->originalNodeListHandles.contains(nodeList.handle())) {
          continue;
        }
        const auto alreadyEnrolled = std::ranges::find_if(
          m_zoneAttachment->createdNodeLists, [&nodeList](const auto& enrolledNodeList) { return enrolledNodeList.handle() == nodeList.handle(); });
        if (alreadyEnrolled == m_zoneAttachment->createdNodeLists.end()) {
          m_zoneAttachment->createdNodeLists.push_back(nodeList);
        }
      }
    }

    bool AirLoopHVAC_Impl::DemandBranchAttachmentPlan::prepareTerminalAttachment(HVACComponent& terminal, Node& node) {
      if (m_state != State::Prepared || m_terminalAttachmentAttempted || terminal.model() != m_airLoop.model() || node.model() != m_airLoop.model()) {
        return false;
      }
      m_terminalAttachmentAttempted = true;

      if (auto dualDuctTerminal = terminal.optionalCast<Mixer>()) {
        // The nested plan remains Prepared until this outer plan commits, so
        // abandoning the branch also rolls back the secondary demand path.
        m_dualDuctTerminalInsertionPlan = DualDuctTerminalInsertionPlan::prepare(*dualDuctTerminal, node);
        return static_cast<bool>(m_dualDuctTerminalInsertionPlan);
      }

      if (!terminal.optionalCast<StraightComponent>()) {
        return false;
      }

      // Straight-terminal addToNode implementations own their family-specific
      // atomicity (extra ports, contained components, ADUs, and zone exhaust
      // projections). This plan owns only the branch and optional zone
      // attachment around that call; it intentionally does not invent a
      // second, incomplete inverse for terminal-family topology.
      return terminal.addToNode(node);
    }

    void AirLoopHVAC_Impl::DemandBranchAttachmentPlan::restoreZoneNodeField(unsigned field, const boost::optional<ModelObject>& originalTarget,
                                                                            const std::vector<Node>& originalNodes) {
      OS_ASSERT(m_zoneAttachment && m_zoneAttachment->connections);
      auto& connections = *m_zoneAttachment->connections;
      if (!m_airLoop.model().getObject(connections.handle())) {
        return;
      }

      if (originalTarget) {
        if (auto originalNodeList = originalTarget->optionalCast<NodeList>()) {
          auto nodeListImpl = originalNodeList->getImpl<detail::NodeList_Impl>();
          OS_ASSERT(nodeListImpl);
          for (const auto& currentNode : originalNodeList->nodes()) {
            const bool removed = nodeListImpl->removeNode(currentNode);
            OS_ASSERT(removed);
            (void)removed;
          }
          for (const auto& originalNode : originalNodes) {
            const bool added = nodeListImpl->addNode(originalNode);
            OS_ASSERT(added);
            (void)added;
          }
        }
      }

      const bool pointerRestored = connections.setPointer(field, originalTarget ? originalTarget->handle() : Handle());
      OS_ASSERT(pointerRestored);
      (void)pointerRestored;
    }

    void AirLoopHVAC_Impl::DemandBranchAttachmentPlan::removeCreatedNode(const boost::optional<Node>& node) {
      if (!node || !m_airLoop.model().getObject(node->handle())) {
        return;
      }
      const bool removed = m_airLoop.model().removeObject(node->handle());
      OS_ASSERT(removed);
      (void)removed;
    }

    void AirLoopHVAC_Impl::DemandBranchAttachmentPlan::cleanupPreparedState() {
      // The nested plan must release the secondary demand path and terminal
      // wiring while the outer branch and zone boundary still exist.
      m_dualDuctTerminalInsertionPlan.reset();

      // Restore or erase the branch rows first so no provisional zone node is
      // still referenced when its transaction-owned objects are removed.
      if (m_splitterRowAdded) {
        m_splitter.removePortForBranch(m_branchIndex);
      } else if (m_reusedBranch && m_originalSplitterOutlet) {
        const bool splitterRestored = m_splitter.setOutletModelObject(m_branchIndex, *m_originalSplitterOutlet);
        OS_ASSERT(splitterRestored);
        (void)splitterRestored;
      }
      if (m_mixerRowAdded) {
        m_mixer.removePortForBranch(m_branchIndex);
      } else if (m_reusedBranch && m_originalMixerInlet) {
        const bool mixerRestored = m_mixer.setInletModelObject(m_branchIndex, *m_originalMixerInlet);
        OS_ASSERT(mixerRestored);
        (void)mixerRestored;
      }

      if (m_zoneAttachment && m_zoneAttachment->connections) {
        auto& zoneState = *m_zoneAttachment;
        auto& connections = *zoneState.connections;
        if (zoneState.createdConnections) {
          if (m_airLoop.model().getObject(connections.handle())) {
            // This provisional owner is being deleted while its terminal
            // outlet node survives. Clear every reverse relationship first so
            // the retained node and zone cannot keep a stale source handle.
            auto connectionsImpl = connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
            OS_ASSERT(connectionsImpl);
            connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName, Handle(), false);
            connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName, Handle(), false);
            connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, Handle(), false);
            connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, Handle(), false);
            connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName, Handle(), false);
            connectionsImpl->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, Handle(), false);
            connections.remove();
          }
        } else {
          restoreZoneNodeField(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, zoneState.originalInletFieldTarget,
                               zoneState.originalInletNodes);
          restoreZoneNodeField(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, zoneState.originalReturnFieldTarget,
                               zoneState.originalReturnNodes);
        }

        for (auto& nodeList : zoneState.createdNodeLists) {
          if (m_airLoop.model().getObject(nodeList.handle())) {
            // A terminal-first rollback retains the terminal outlet node that
            // this provisional NodeList referenced. Erase the list rows first
            // so the retained node does not keep reverse pointers to a deleted
            // NodeList source.
            auto nodeListImpl = nodeList.getImpl<detail::NodeList_Impl>();
            OS_ASSERT(nodeListImpl);
            for (const auto& node : nodeList.nodes()) {
              const bool removed = nodeListImpl->removeNode(node);
              OS_ASSERT(removed);
              (void)removed;
            }
            nodeList.remove();
          }
        }
        if (zoneState.createdEquipmentList && m_airLoop.model().getObject(zoneState.createdEquipmentList->handle())) {
          zoneState.createdEquipmentList->remove();
        }
        removeCreatedNode(zoneState.createdZoneReturnNode);
        removeCreatedNode(zoneState.createdZoneInletNode);
      }

      if (m_createdBranchNode) {
        removeCreatedNode(m_branchNode);
      }
    }

    bool AirLoopHVAC_Impl::DemandBranchAttachmentPlan::commit(DemandBranchAttachmentFailureStage failureStage) {
      if (m_state != State::Prepared) {
        OS_ASSERT(false);
        return false;
      }

      std::vector<ModelObject> idealAirLoadsToRemove;
      const bool removeUnusedBranchNode = m_zoneAttachment && m_createdBranchNode;
      if (m_zoneAttachment) {
        idealAirLoadsToRemove = m_zoneAttachment->idealAirLoadsToRemove;
      }

      if (m_dualDuctTerminalInsertionPlan) {
        m_dualDuctTerminalInsertionPlan->commit();
      }

      std::unique_ptr<TerminalZoneProjectionPlan> terminalZoneProjection;
      if (m_existingTerminalForZone) {
        OS_ASSERT(m_zoneAttachment && m_zoneAttachment->connections);
        terminalZoneProjection = TerminalZoneProjectionPlan::prepare(*m_existingTerminalForZone, *m_zoneAttachment->connections, m_branchNode);
        if (!terminalZoneProjection) {
          return false;
        }
        if (failureStage == DemandBranchAttachmentFailureStage::AfterTerminalZoneProjectionPrepared) {
          return false;
        }
      }

      // Every removable ideal-load object was preflighted during preparation.
      // Cross the commit boundary before performing those destructive removals:
      // after this point the branch is authoritative and must not be rolled
      // back even if an internal removal contract is violated in release code.
      m_state = State::Committed;
      if (terminalZoneProjection) {
        terminalZoneProjection->commit();
      }
      m_zoneAttachment.reset();
      m_dualDuctTerminalInsertionPlan.reset();

      // A non-default reservation node is only the common row endpoint used
      // during preparation. Zone attachment replaces both row endpoints, so
      // retaining a transaction-created node here would leave an orphan.
      if (removeUnusedBranchNode) {
        removeCreatedNode(m_branchNode);
        m_createdBranchNode = false;
      }

      for (auto& idealAirLoads : idealAirLoadsToRemove) {
        const auto removedObjects = idealAirLoads.remove();
        const bool removed = !removedObjects.empty();
        OS_ASSERT(removed);
        (void)removed;
      }
      return true;
    }

    boost::optional<unsigned> AirLoopHVAC_Impl::demandBranchIndexForZoneInletNode(const openstudio::epmodel::Node& zoneInletNode) const {
      if (zoneInletNode.model() != model()) {
        return boost::none;
      }

      const auto splitterOutlets = zoneSplitter().outletModelObjects();
      const auto mixerInlets = zoneMixer().inletModelObjects();
      const auto servedZone = resolveZoneServedByInletNode(zoneInletNode);
      for (unsigned i = 0; i < splitterOutlets.size(); ++i) {
        if (splitterOutlets[i] == zoneInletNode.cast<ModelObject>()) {
          return i;
        }

        if (i >= mixerInlets.size()) {
          continue;
        }
        auto splitterOutletNode = splitterOutlets[i].optionalCast<Node>();
        auto mixerInletNode = mixerInlets[i].optionalCast<Node>();
        if (!splitterOutletNode || !mixerInletNode) {
          continue;
        }

        if (auto terminal = resolveTerminalOnDemandBranchNodes(*splitterOutletNode, *mixerInletNode)) {
          if (auto terminalOutlet = resolveTerminalOutletObject(*terminal)) {
            if (*terminalOutlet == zoneInletNode.cast<ModelObject>()) {
              return i;
            }
          }
        }

        if (servedZone) {
          if (auto returnZone = resolveZoneServedByReturnNode(*mixerInletNode)) {
            if (*servedZone == *returnZone) {
              return i;
            }
          }
        }
      }

      return boost::none;
    }

    bool AirLoopHVAC_Impl::ensureDefaultDemandBranch() {
      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      if (!splitter.outletModelObjects().empty()) {
        return true;
      }

      auto defaultNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(getObject<AirLoopHVAC>().nameString() + " Demand Branch Node");
      return splitter.setOutletModelObject(0u, defaultNode.cast<ModelObject>()) && mixer.setInletModelObject(0u, defaultNode.cast<ModelObject>());
    }

    boost::optional<Mixer> AirLoopHVAC_Impl::reusableDualDuctTerminalForZone() const {
      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      const auto splitterOutlets = splitter.outletModelObjects();
      const auto mixerInlets = mixer.inletModelObjects();
      const auto branchCount = std::min(splitterOutlets.size(), mixerInlets.size());

      for (auto branchIndex = branchCount; branchIndex > 0u; --branchIndex) {
        auto splitterOutletNode = splitterOutlets[branchIndex - 1u].optionalCast<Node>();
        auto mixerInletNode = mixerInlets[branchIndex - 1u].optionalCast<Node>();
        if (!splitterOutletNode || !mixerInletNode) {
          continue;
        }

        if (resolveZoneServedByInletNode(*mixerInletNode) || resolveZoneServedByReturnNode(*mixerInletNode)) {
          continue;
        }

        auto terminalObject = resolveTerminalOnDemandBranchNodes(*splitterOutletNode, *mixerInletNode);
        auto terminal = terminalObject ? terminalObject->optionalCast<Mixer>() : boost::none;
        if (!terminal) {
          continue;
        }

        auto terminalOutletObject = resolveTerminalOutletObject(*terminalObject);
        auto terminalOutletNode = terminalOutletObject ? terminalOutletObject->optionalCast<Node>() : boost::none;
        if (!terminalOutletNode || !(*terminalOutletNode == *mixerInletNode)) {
          continue;
        }

        return *terminal;
      }

      return boost::none;
    }

    bool AirLoopHVAC_Impl::removeDemandBranchAtIndex(unsigned branchIndex) {
      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      const auto splitterOutlets = splitter.outletModelObjects();
      const auto mixerInlets = mixer.inletModelObjects();
      if (branchIndex >= splitterOutlets.size() || branchIndex >= mixerInlets.size()) {
        return false;
      }

      splitter.removePortForBranch(branchIndex);
      mixer.removePortForBranch(branchIndex);

      const auto demandInlets = demandInletNodes();
      if (demandInlets.size() > 1u) {
        if (auto secondarySplitter = zoneSplitterForDemandInletNode(demandInlets[1])) {
          // Secondary demand branches belong to dual-duct terminals, not to
          // primary zone-branch indices. The terminal teardown removes its
          // own secondary branch by node identity before the primary zone
          // branch reaches this helper. Removing the same numeric index here
          // can delete a different terminal after secondary-row compaction.
          if (!collapseSecondaryDemandPathIfEmpty(demandInlets[1], *secondarySplitter)) {
            return false;
          }
        }
      }

      return ensureDefaultDemandBranch();
    }

    bool AirLoopHVAC_Impl::collapseSecondaryDemandPathIfEmpty(openstudio::epmodel::Node secondaryDemandInletNode,
                                                              openstudio::epmodel::AirLoopHVACZoneSplitter secondarySplitter) {
      if (secondaryDemandInletNode.model() != model() || secondarySplitter.model() != model()) {
        return false;
      }
      if (!secondarySplitter.outletModelObjects().empty()) {
        return true;
      }

      boost::optional<AirLoopHVACSupplyPath> secondarySupplyPath;
      for (const auto& supplyPath : model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
        if (auto inletNode = supplyPath.getImpl<detail::AirLoopHVACSupplyPath_Impl>()->supplyAirPathInletNode()) {
          if (*inletNode == secondaryDemandInletNode) {
            secondarySupplyPath = supplyPath;
            break;
          }
        }
      }

      auto airLoop = getObject<AirLoopHVAC>();
      auto demandInletNodeList = airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::DemandSideInletNodeNames);
      if (!demandInletNodeList || !demandInletNodeList->getImpl<detail::NodeList_Impl>()->removeNode(secondaryDemandInletNode)) {
        return false;
      }

      if (secondarySupplyPath) {
        secondarySupplyPath->remove();
      }
      secondarySplitter.remove();
      // The inlet node is no longer a loop component after its NodeList entry,
      // SupplyPath, and splitter have been removed.  Bypass Node::remove here:
      // its StraightComponent teardown rediscovers the loop while the dual
      // demand path is intentionally half-collapsed.
      const auto secondaryDemandInletHandle = secondaryDemandInletNode.handle();
      if (model().getObject(secondaryDemandInletHandle) && !model().removeObject(secondaryDemandInletHandle)) {
        return false;
      }

      return true;
    }

    bool AirLoopHVAC_Impl::detachZoneFromDemandNodes(openstudio::epmodel::ZoneHVACEquipmentConnections& connections) {
      auto impl = connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(impl);

      const auto inletNodes = connections.zoneAirInletNodes();
      for (const auto& node : inletNodes) {
        if (!impl->removeZoneAirInletNode(node)) {
          return false;
        }
      }

      const auto returnNodes = connections.zoneReturnAirNodes();
      for (const auto& node : returnNodes) {
        if (!impl->removeZoneReturnAirNode(node)) {
          return false;
        }
      }

      return true;
    }

    // Resolve the ThermalZone whose ZoneHVACEquipmentConnections lists this
    // node as a zone air inlet. This is how loop traversal moves from an air
    // terminal outlet/zone inlet node back to the served zone without requiring
    // OpenStudio model-style Connection objects.
    //
    // Multiple zones sharing the same inlet node is invalid for normal models,
    // but imported or hand-authored IDF can be ambiguous. Use deterministic
    // name ordering and warn rather than making traversal non-repeatable.
    boost::optional<ThermalZone> AirLoopHVAC_Impl::resolveZoneServedByInletNode(const Node& zoneInletNode) {
      const auto& m = zoneInletNode.model();
      std::vector<ThermalZone> zones;

      const auto inletNameMatches = [&](const ZoneHVACEquipmentConnections& conn) -> bool {
        const auto inletNodes = conn.zoneAirInletNodes();
        return std::ranges::find(inletNodes, zoneInletNode) != inletNodes.end();
      };

      for (const auto& conn : m.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        if (!inletNameMatches(conn)) {
          continue;
        }
        zones.push_back(conn.thermalZone());
      }

      if (zones.empty()) {
        return boost::none;
      }

      std::ranges::sort(zones, [](const ThermalZone& lhs, const ThermalZone& rhs) { return lhs.nameString() < rhs.nameString(); });
      if (zones.size() > 1u) {
        LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                 "Multiple ThermalZones reference zone inlet node '" << zoneInletNode.nameString() << "'. Using first zone by name ordering.");
      }
      return zones.front();
    }

    // Resolve the ThermalZone whose ZoneHVACEquipmentConnections lists this
    // node as a zone return node. This is the fallback for incomplete terminal
    // linkage: even if we cannot identify the terminal cleanly, the mixer-side
    // branch node can still identify the served zone.
    boost::optional<ThermalZone> AirLoopHVAC_Impl::resolveZoneServedByReturnNode(const Node& zoneReturnNode) {
      const auto& m = zoneReturnNode.model();
      std::vector<ThermalZone> zones;

      const auto outletNameMatches = [&](const ZoneHVACEquipmentConnections& conn) -> bool {
        const auto returnNodes = conn.zoneReturnAirNodes();
        return std::ranges::find(returnNodes, zoneReturnNode) != returnNodes.end();
      };

      for (const auto& conn : m.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        if (!outletNameMatches(conn)) {
          continue;
        }
        zones.push_back(conn.thermalZone());
      }

      if (zones.empty()) {
        return boost::none;
      }

      std::sort(zones.begin(), zones.end(), [](const ThermalZone& lhs, const ThermalZone& rhs) { return lhs.nameString() < rhs.nameString(); });
      if (zones.size() > 1u) {
        LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                 "Multiple ThermalZones reference zone return node '" << zoneReturnNode.nameString() << "'. Using first zone by name ordering.");
      }
      return zones.front();
    }

    bool AirLoopHVAC_Impl::isTerminalTypeValid(const openstudio::epmodel::HVACComponent& airTerminal) const {
      const bool loopIsDualDuct = isDualDuct();
      const bool terminalIsDualDuct = airTerminal.optionalCast<Mixer>().has_value();
      if (loopIsDualDuct == terminalIsDualDuct) {
        return true;
      }

      LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
               "Cannot assign terminal '" << airTerminal.nameString() << "' to '" << getObject<AirLoopHVAC>().nameString()
                                          << "' because the terminal type does not match the loop duct topology.");
      return false;
    }

    boost::optional<HVACComponent> AirLoopHVAC_Impl::reusableSingleDuctTerminalForZone() const {
      if (isDualDuct()) {
        return boost::none;
      }

      const auto splitterOutlets = zoneSplitter().outletModelObjects();
      const auto mixerInlets = zoneMixer().inletModelObjects();
      if (splitterOutlets.empty() || splitterOutlets.size() != mixerInlets.size()) {
        return boost::none;
      }

      auto splitterOutletNode = splitterOutlets.back().optionalCast<Node>();
      auto mixerInletNode = mixerInlets.back().optionalCast<Node>();
      if (!splitterOutletNode || !mixerInletNode) {
        return boost::none;
      }

      auto terminalObject = resolveTerminalOnDemandBranchNodes(*splitterOutletNode, *mixerInletNode);
      auto terminal = terminalObject ? terminalObject->optionalCast<HVACComponent>() : boost::optional<HVACComponent>();
      if (!terminal || !terminal->optionalCast<StraightComponent>()) {
        return boost::none;
      }

      auto terminalOutlet = resolveTerminalOutletObject(*terminalObject);
      auto terminalOutletNode = terminalOutlet ? terminalOutlet->optionalCast<Node>() : boost::optional<Node>();
      if (!terminalOutletNode || *terminalOutletNode != *mixerInletNode) {
        return boost::none;
      }

      // A zone-attached branch separates the terminal outlet/zone inlet from
      // the mixer-side return node. Equality here therefore proves this is the
      // canonical trailing terminal-only branch, not an occupied zone branch.
      if (resolveZoneServedByInletNode(*terminalOutletNode) || resolveZoneServedByReturnNode(*mixerInletNode)) {
        return boost::none;
      }
      return *terminal;
    }

    boost::optional<StraightComponent> AirLoopHVAC_Impl::lastSingleDuctTerminalForClone() const {
      if (isDualDuct()) {
        return boost::none;
      }

      const auto splitterOutlets = zoneSplitter().outletModelObjects();
      const auto mixerInlets = zoneMixer().inletModelObjects();
      if (splitterOutlets.empty() || splitterOutlets.size() != mixerInlets.size()) {
        return boost::none;
      }

      auto splitterOutletNode = splitterOutlets.back().optionalCast<Node>();
      auto mixerInletNode = mixerInlets.back().optionalCast<Node>();
      if (!splitterOutletNode || !mixerInletNode) {
        return boost::none;
      }

      auto terminalObject = resolveTerminalOnDemandBranchNodes(*splitterOutletNode, *mixerInletNode);
      auto sourceTerminal = terminalObject ? terminalObject->optionalCast<StraightComponent>() : boost::optional<StraightComponent>();
      if (!sourceTerminal) {
        return boost::none;
      }

      auto terminalOutletObject = sourceTerminal->outletModelObject();
      auto terminalOutletNode = terminalOutletObject ? terminalOutletObject->optionalCast<Node>() : boost::optional<Node>();
      auto inletZone = terminalOutletNode ? resolveZoneServedByInletNode(*terminalOutletNode) : boost::optional<ThermalZone>();
      auto returnZone = resolveZoneServedByReturnNode(*mixerInletNode);
      if (!inletZone || !returnZone || *inletZone != *returnZone) {
        return boost::none;
      }

      return *sourceTerminal;
    }

    boost::optional<HVACComponent> AirLoopHVAC_Impl::cloneLastDualDuctTerminalForBranch() const {
      const auto terminals = demandComponents(openstudio::IddObjectType::Catchall);
      for (auto it = terminals.rbegin(); it != terminals.rend(); ++it) {
        const auto objectType = it->iddObject().type();
        if (objectType != openstudio::IddObjectType::AirTerminal_DualDuct_ConstantVolume
            && objectType != openstudio::IddObjectType::AirTerminal_DualDuct_VAV
            && objectType != openstudio::IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir) {
          continue;
        }

        auto sourceTerminal = it->optionalCast<Mixer>();
        if (!sourceTerminal) {
          continue;
        }

        // Clone the persisted terminal object so schedules and all scalar
        // properties follow the canonical clone-last-terminal behavior. Clear
        // topology fields before adding it back to the model: a clone must not
        // briefly point at the source terminal's branch nodes.
        auto cloneIdfObject = it->idfObject();
        if (!cloneIdfObject.setName(model().nextName(objectType, true))) {
          return boost::none;
        }
        if (!cloneIdfObject.setString(sourceTerminal->inletPort(0u), "") || !cloneIdfObject.setString(sourceTerminal->inletPort(1u), "")
            || !cloneIdfObject.setString(sourceTerminal->outletPort(), "")) {
          return boost::none;
        }

        auto cloneObject = model().addObject(cloneIdfObject);
        if (!cloneObject) {
          return boost::none;
        }
        auto clone = cloneObject->optionalCast<HVACComponent>();
        if (!clone) {
          cloneObject->remove();
          return boost::none;
        }
        return *clone;
      }

      return boost::none;
    }

    // Return the downstream object for an air terminal regardless of whether
    // the terminal is modeled as a StraightComponent or as a Mixer. Single-duct
    // terminals are straight-through components; dual-duct terminals are mixers
    // because they have two upstream duct inlets and one outlet.
    boost::optional<ModelObject> AirLoopHVAC_Impl::resolveTerminalOutletObject(const ModelObject& terminalObject) {
      if (auto component = terminalObject.optionalCast<StraightComponent>()) {
        return component->outletModelObject();
      }
      if (auto mixer = terminalObject.optionalCast<Mixer>()) {
        return mixer->outletModelObject();
      }
      return boost::none;
    }

    // Walk a simple single-duct demand branch backwards from mixer inlet to
    // splitter outlet through StraightComponent node links. This intentionally
    // handles only straight-through branch equipment; mixer-style dual-duct
    // terminals are detected separately in resolveTerminalOnDemandBranchNodes.
    //
    // Ambiguous or cyclic branches return none. That keeps demandComponents()
    // conservative: if topology cannot be proven as a single ordered chain, the
    // caller can still use zone-node fallbacks instead of inventing an order.
    boost::optional<std::vector<StraightComponent>> AirLoopHVAC_Impl::resolveDemandBranchChain(const Node& branchStartNode,
                                                                                               const Node& branchEndNode) {
      std::vector<StraightComponent> components;
      auto currentNode = branchEndNode;
      std::set<openstudio::Handle> visitedNodeHandles{currentNode.handle()};

      for (unsigned depth = 0; depth < 64u && !(currentNode == branchStartNode); ++depth) {
        std::vector<std::pair<StraightComponent, Node>> candidates;
        for (const auto& sourceObject : currentNode.sources()) {
          auto candidate = sourceObject.optionalCast<StraightComponent>();
          if (!candidate || candidate->iddObject().type() == openstudio::IddObjectType::Node) {
            continue;
          }

          auto outletObject = candidate->outletModelObject();
          auto outletNode = outletObject ? outletObject->optionalCast<Node>() : boost::none;
          if (!outletNode || !(*outletNode == currentNode)) {
            continue;
          }

          auto inletObject = candidate->inletModelObject();
          auto inletNode = inletObject ? inletObject->optionalCast<Node>() : boost::none;
          if (!inletNode) {
            continue;
          }

          candidates.emplace_back(*candidate, *inletNode);
        }

        if (candidates.empty()) {
          return boost::none;
        }

        std::vector<std::pair<StraightComponent, Node>> nonVisitedCandidates;
        for (const auto& candidate : candidates) {
          if (visitedNodeHandles.find(candidate.second.handle()) == visitedNodeHandles.end()) {
            nonVisitedCandidates.push_back(candidate);
          }
        }

        const auto& selectedCandidates = nonVisitedCandidates.empty() ? candidates : nonVisitedCandidates;
        if (selectedCandidates.size() != 1u) {
          return boost::none;
        }

        const auto& [upstreamComponent, upstreamNode] = selectedCandidates.front();
        components.push_back(upstreamComponent);
        currentNode = upstreamNode;
        if (!visitedNodeHandles.insert(currentNode.handle()).second) {
          return boost::none;
        }
      }

      if (!(currentNode == branchStartNode)) {
        return boost::none;
      }
      return components;
    }

    // Identify the terminal occupying the zone branch between splitter outlet
    // and mixer inlet. For single-duct branches this is the last straight
    // component in the branch chain. For dual-duct branches the terminal is a
    // Mixer sourced by the splitter outlet and discharging to the zone/mixer
    // branch node.
    //
    // Returning none is acceptable for partially imported topology. The caller
    // still includes branch nodes and can resolve the zone from inlet/return
    // node relationships.
    boost::optional<ModelObject> AirLoopHVAC_Impl::resolveTerminalOnDemandBranchNodes(const Node& splitterOutletNode, const Node& mixerInletNode) {
      if (auto branchComponents = resolveDemandBranchChain(splitterOutletNode, mixerInletNode)) {
        for (const auto& component : *branchComponents) {
          auto candidate = component.cast<ModelObject>();
          const auto iddName = candidate.iddObject().name();
          if (iddName.starts_with("AirTerminal:") || iddName.starts_with("OS:AirTerminal:")) {
            return candidate;
          }
        }
      }

      for (const auto& sourceObject : splitterOutletNode.sources()) {
        const auto iddName = sourceObject.iddObject().name();
        if (!iddName.starts_with("AirTerminal:") && !iddName.starts_with("OS:AirTerminal:")) {
          continue;
        }
        if (auto straight = sourceObject.optionalCast<StraightComponent>()) {
          auto outletObject = straight->outletModelObject();
          auto outletNode = outletObject ? outletObject->optionalCast<Node>() : boost::none;
          if (!outletNode) {
            continue;
          }
          if (*outletNode == mixerInletNode) {
            return sourceObject.cast<ModelObject>();
          }

          auto inletZone = resolveZoneServedByInletNode(*outletNode);
          auto returnZone = resolveZoneServedByReturnNode(mixerInletNode);
          if (inletZone && returnZone && *inletZone == *returnZone) {
            return sourceObject.cast<ModelObject>();
          }
          continue;
        }
        if (auto mixer = sourceObject.optionalCast<Mixer>()) {
          if (auto outletObject = mixer->outletModelObject()) {
            if (auto outletNode = outletObject->optionalCast<Node>()) {
              if (*outletNode == mixerInletNode) {
                return sourceObject.cast<ModelObject>();
              }

              // An attached zone separates its inlet and return nodes. The
              // dual-duct terminal discharges to the former while the branch
              // ends at the latter, so recognize the terminal when both nodes
              // belong to the same served zone.
              auto inletZone = resolveZoneServedByInletNode(*outletNode);
              auto returnZone = resolveZoneServedByReturnNode(mixerInletNode);
              if (inletZone && returnZone && *inletZone == *returnZone) {
                return sourceObject.cast<ModelObject>();
              }
            }
          }
          continue;
        }
      }

      return boost::none;
    }

    void AirLoopHVAC_Impl::doCanonicalize(LoadContext& context) {
      auto airLoop = getObject<AirLoopHVAC>();
      OS_ASSERT(!airLoop.nameString().empty());
      const auto loopName = airLoop.nameString();

      // Demand topology has distinct authoritative layers:
      //
      // - ZoneSplitter and ZoneMixer ports define air-loop branch count and order.
      // - Terminal ports define equipment connectivity within each branch.
      // - ZoneHVACEquipmentConnections defines which inlet and return nodes belong
      //   to a ThermalZone.
      //
      // A connected zone intentionally separates the terminal outlet/zone inlet
      // from the mixer-side zone return. Canonicalization must preserve that
      // separation; traversal associates the two branch endpoints through their
      // common ThermalZone.

      // These keyed companions are the loop-level connective tissue later
      // queried through demand inlet/outlet association. Canonicalization keeps
      // a single canonical object for each key so const APIs never have to
      // guess which duplicate "really" belongs to the loop.
      auto removeDuplicateModelObject = [&](ModelObject duplicate, const std::string& roleDescription) {
        if (duplicate.remove().empty()) {
          detail::addLoadWarning(context, "Failed to remove duplicate " + roleDescription + " '" + duplicate.nameString() + "' for AirLoopHVAC '"
                                            + loopName + "'.");
        } else {
          detail::addLoadWarning(context,
                                 "Removed duplicate " + roleDescription + " '" + duplicate.nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
      };

      {  // Canonical topology anchor points.
         // These node references are the entry/exit contracts used by supply
         // and demand path traversal; if they drift, most loop APIs become
         // ambiguous. We always materialize them first.
        getOrCreateTarget<Node>(AirLoopHVACFields::SupplySideInletNodeName, loopName + " Supply Inlet Node");
        detail::NodeList_Impl::ensureAttachedNodeList(context, airLoop, AirLoopHVACFields::SupplySideOutletNodeNames, " Supply Outlet Nodes",
                                                      " Supply Outlet Node");
        detail::NodeList_Impl::ensureAttachedNodeList(context, airLoop, AirLoopHVACFields::DemandSideInletNodeNames, " Demand Inlet Nodes",
                                                      " Demand Inlet Node");
        getOrCreateTarget<Node>(AirLoopHVACFields::DemandSideOutletNodeName, loopName + " Demand Outlet Node");
        getOrCreateTarget<AvailabilityManagerAssignmentList>(AirLoopHVACFields::AvailabilityManagerListName, loopName + " Availability Manager List");

        {  // Supply branch storage contract.
           // BranchList is the E+ source-of-truth for supply component order.
           // Ensure at least one branch exists so path extraction can build a
           // deterministic adjacency graph.
          auto branchList = getOrCreateTarget<BranchList>(AirLoopHVACFields::BranchListName);
          if (branchList.branches().empty()) {
            const auto branch = Branch(model());
            branchList.getImpl<detail::BranchList_Impl>()->addBranch(branch);
            detail::addLoadInfo(context, "Added default Branch '" + branch.nameString() + "' to BranchList '" + branchList.nameString()
                                           + "' for AirLoopHVAC '" + airLoop.nameString() + "'.");
          }
        }
      }

      const auto demandInlet = demandInletNode();
      const auto demandOutlet = demandOutletNode();

      {  // Demand-side splitter anchor keyed by demand inlet node.
         // This reproduces openstudio::model topology assumptions while storing
         // the association using E+ node-linkage semantics.
        std::vector<AirLoopHVACZoneSplitter> matches;
        for (auto& zp : model().getConcreteModelObjects<AirLoopHVACZoneSplitter>()) {
          if (zp.getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->inletNode() == demandInlet) {
            matches.push_back(zp);
          }
        }

        boost::optional<AirLoopHVACZoneSplitter> zoneSplitter;
        if (!matches.empty()) {
          // Use name ordering only as a deterministic tiebreaker, then remove
          // every other object with the same demand-inlet key.
          std::sort(matches.begin(), matches.end(), [](const auto& lhs, const auto& rhs) { return lhs.nameString() < rhs.nameString(); });
          zoneSplitter = matches.front();
          for (auto it = std::next(matches.begin()); it != matches.end(); ++it) {
            removeDuplicateModelObject(it->cast<ModelObject>(), "AirLoopHVAC:ZoneSplitter");
          }
        }

        if (!zoneSplitter) {
          zoneSplitter = AirLoopHVACZoneSplitter(model());
          zoneSplitter->setName(loopName + " Zone Splitter");
          zoneSplitter->getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->setInletNode(demandInlet);
          detail::addLoadInfo(context,
                              "Created missing AirLoopHVAC:ZoneSplitter '" + zoneSplitter->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        zoneSplitter->getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->canonicalize(context);
      }

      {  // Demand-side mixer anchor keyed by demand outlet node.
         // Splitter + mixer pair define branch fan-out/fan-in boundaries.
        std::vector<AirLoopHVACZoneMixer> matches;
        for (auto& zm : model().getConcreteModelObjects<AirLoopHVACZoneMixer>()) {
          if (zm.getImpl<detail::AirLoopHVACZoneMixer_Impl>()->outletNode() == demandOutlet) {
            matches.push_back(zm);
          }
        }

        boost::optional<AirLoopHVACZoneMixer> zoneMixer;
        if (!matches.empty()) {
          std::sort(matches.begin(), matches.end(), [](const auto& lhs, const auto& rhs) { return lhs.nameString() < rhs.nameString(); });
          zoneMixer = matches.front();
          for (auto it = std::next(matches.begin()); it != matches.end(); ++it) {
            removeDuplicateModelObject(it->cast<ModelObject>(), "AirLoopHVAC:ZoneMixer");
          }
        }

        if (!zoneMixer) {
          zoneMixer = AirLoopHVACZoneMixer(model());
          zoneMixer->setName(loopName + " Zone Mixer");
          zoneMixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>()->setOutletNode(demandOutlet);
          detail::addLoadInfo(context, "Created missing AirLoopHVAC:ZoneMixer '" + zoneMixer->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        zoneMixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>()->canonicalize(context);
      }

      {  // SupplyPath object keyed by demand inlet node.
         // Path objects are connective tissue in E+ schema; we keep them
         // explicit so traversal and mutation do not infer hidden links.
        std::vector<AirLoopHVACSupplyPath> matches;
        for (auto& sp : model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
          if (sp.getImpl<detail::AirLoopHVACSupplyPath_Impl>()->supplyAirPathInletNode() == demandInlet) {
            matches.push_back(sp);
          }
        }

        boost::optional<AirLoopHVACSupplyPath> supplyPath;
        if (!matches.empty()) {
          std::sort(matches.begin(), matches.end(), [](const auto& lhs, const auto& rhs) { return lhs.nameString() < rhs.nameString(); });
          supplyPath = matches.front();
          for (auto it = std::next(matches.begin()); it != matches.end(); ++it) {
            removeDuplicateModelObject(it->cast<ModelObject>(), "AirLoopHVAC:SupplyPath");
          }
        }

        if (!supplyPath) {
          supplyPath = AirLoopHVACSupplyPath(model());
          supplyPath->setName(loopName + " Supply Path");
          supplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>()->setSupplyAirPathInletNode(airLoop.demandInletNode());
          detail::addLoadInfo(context,
                              "Created missing AirLoopHVAC:SupplyPath '" + supplyPath->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        supplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>()->canonicalize(context);
      }

      {  // ReturnPath object keyed by demand outlet node.
         // Together with SupplyPath this keeps demand topology round-trippable
         // through IDF connective-tissue objects.
        std::vector<AirLoopHVACReturnPath> matches;
        for (auto& rp : model().getConcreteModelObjects<AirLoopHVACReturnPath>()) {
          if (rp.getImpl<detail::AirLoopHVACReturnPath_Impl>()->returnAirPathOutletNode() == demandOutlet) {
            matches.push_back(rp);
          }
        }

        boost::optional<AirLoopHVACReturnPath> returnPath;
        if (!matches.empty()) {
          std::sort(matches.begin(), matches.end(), [](const auto& lhs, const auto& rhs) { return lhs.nameString() < rhs.nameString(); });
          returnPath = matches.front();
          for (auto it = std::next(matches.begin()); it != matches.end(); ++it) {
            removeDuplicateModelObject(it->cast<ModelObject>(), "AirLoopHVAC:ReturnPath");
          }
        }

        if (!returnPath) {
          returnPath = AirLoopHVACReturnPath(model());
          returnPath->setName(loopName + " Return Path");
          returnPath->getImpl<detail::AirLoopHVACReturnPath_Impl>()->setReturnAirPathOutletNode(airLoop.demandOutletNode());
          detail::addLoadInfo(context,
                              "Created missing AirLoopHVAC:ReturnPath '" + returnPath->nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        }
        returnPath->getImpl<detail::AirLoopHVACReturnPath_Impl>()->canonicalize(context);
      }

      {  // Ensure there is at least one Node between the zone splitter and mixer.
         // A changeover-bypass unitary may add a mixer-only inlet for bypass
         // return air. That inlet is not a demand branch and must not make the
         // paired splitter/mixer branch counts appear inconsistent.
        auto zs = zoneSplitter();
        auto zm = zoneMixer();
        const auto splitterOutlets = zs.outletModelObjects();
        const auto mixerInlets = zm.inletModelObjects();
        std::set<Handle> bypassReturnHandles;
        for (const auto& unitary : model().getConcreteModelObjects<AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass>()) {
          const auto bypassReturnNode = unitary.getModelObjectTarget<Node>(unitary.plenumorMixerAirPort());
          if (bypassReturnNode) {
            bypassReturnHandles.insert(bypassReturnNode->handle());
          }
        }

        std::vector<Node> bypassReturnNodes;
        for (const auto& inlet : mixerInlets) {
          if (bypassReturnHandles.contains(inlet.handle())) {
            bypassReturnNodes.push_back(inlet.cast<Node>());
          }
        }

        std::set<Handle> returnPlenumOutletHandles;
        std::size_t returnPlenumBranchCount = 0u;
        for (const auto& plenum : model().getConcreteModelObjects<AirLoopHVACReturnPlenum>()) {
          const auto outlet = plenum.outletModelObject();
          if (!outlet || (std::ranges::find(mixerInlets, *outlet) == mixerInlets.end())) {
            continue;
          }

          std::size_t servedInletCount = 0u;
          for (const auto& inlet : plenum.inletModelObjects()) {
            if (bypassReturnHandles.contains(inlet.handle())) {
              continue;
            }
            if (auto inletNode = inlet.optionalCast<Node>()) {
              if (resolveZoneServedByReturnNode(*inletNode)) {
                ++servedInletCount;
              }
            }
          }
          if (servedInletCount > 0u) {
            returnPlenumOutletHandles.insert(outlet->handle());
            returnPlenumBranchCount += servedInletCount;
          }
        }

        std::size_t directDemandBranchCount = 0u;
        for (const auto& inlet : mixerInlets) {
          if (!bypassReturnHandles.contains(inlet.handle()) && !returnPlenumOutletHandles.contains(inlet.handle())) {
            ++directDemandBranchCount;
          }
        }
        const auto demandMixerBranchCount = directDemandBranchCount + returnPlenumBranchCount;

        std::set<Handle> supplyPlenumInletHandles;
        std::size_t supplyPlenumBranchCount = 0u;
        for (const auto& plenum : model().getConcreteModelObjects<AirLoopHVACSupplyPlenum>()) {
          const auto inlet = plenum.inletModelObject();
          if (!inlet || (std::ranges::find(splitterOutlets, *inlet) == splitterOutlets.end()) || plenum.outletModelObjects().empty()) {
            continue;
          }
          supplyPlenumInletHandles.insert(inlet->handle());
          supplyPlenumBranchCount += plenum.outletModelObjects().size();
        }
        const auto directSupplyBranchCount = static_cast<std::size_t>(
          std::ranges::count_if(splitterOutlets, [&](const auto& outlet) { return !supplyPlenumInletHandles.contains(outlet.handle()); }));
        const auto demandSplitterBranchCount = directSupplyBranchCount + supplyPlenumBranchCount;
        bool rebuiltDemandBranches = false;

        if (demandSplitterBranchCount != demandMixerBranchCount) {
          if (returnPlenumOutletHandles.empty() && supplyPlenumInletHandles.empty()) {
            while (!zs.outletModelObjects().empty()) {
              zs.removePortForBranch(static_cast<unsigned>(zs.outletModelObjects().size() - 1u));
            }
            while (!zm.inletModelObjects().empty()) {
              zm.removePortForBranch(static_cast<unsigned>(zm.inletModelObjects().size() - 1u));
            }
            rebuiltDemandBranches = true;
            detail::addLoadWarning(context, "ZoneSplitter/ZoneMixer branch count mismatch for AirLoopHVAC '" + loopName
                                              + "' (effective supply branches=" + std::to_string(demandSplitterBranchCount)
                                              + ", effective return branches=" + std::to_string(demandMixerBranchCount) + ", bypass return="
                                              + std::to_string(bypassReturnNodes.size()) + "). Cleared branch node ports to rebuild.");
          } else {
            detail::addLoadWarning(context, "Effective supply/return branch count mismatch for AirLoopHVAC '" + loopName
                                              + "' (effective supply branches=" + std::to_string(demandSplitterBranchCount)
                                              + ", effective return branches=" + std::to_string(demandMixerBranchCount)
                                              + "). Preserved the plenum topology for explicit repair.");
          }
        }

        if (zs.outletModelObjects().empty()) {
          if (!rebuiltDemandBranches) {
            while (!zm.inletModelObjects().empty()) {
              zm.removePortForBranch(static_cast<unsigned>(zm.inletModelObjects().size() - 1u));
            }
          }
          Node branchNode(model());
          branchNode.setName(loopName + " Demand Branch Node");
          zs.setOutletModelObject(0u, branchNode);
          zm.setInletModelObject(0u, branchNode);
          detail::addLoadInfo(context, "Created demand branch node '" + branchNode.nameString()
                                         + "' between ZoneSplitter and ZoneMixer for AirLoopHVAC '" + loopName + "'.");
        }

        if (rebuiltDemandBranches || (mixerInlets.size() == bypassReturnNodes.size())) {
          for (const auto& bypassReturnNode : bypassReturnNodes) {
            zm.setInletModelObject(zm.nextBranchIndex(), bypassReturnNode);
          }
        }
      }

      {  // OA/CMV linkage is loop-scoped.
         // At most one OA system is supported on an AirLoopHVAC. Canonicalize
         // that OA system first, then rebuild CMV zone OA entries from loop thermal zones.
        if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
          auto oaSystemImpl = oaSystem->getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>();
          OS_ASSERT(oaSystemImpl);
          oaSystemImpl->canonicalize(context);
        }

        syncControllerMechanicalVentilationZoneOutdoorAirEntries();
        syncSetpointManagerMixedAirFanNodes();
      }

      syncSupplyWaterCoilControllers();

      {  // Sizing:System is a loop-owned companion object.
         // Loop-level sizing APIs assume one companion object per AirLoopHVAC,
         // so canonicalization creates it when missing.
        std::vector<SizingSystem> matches;
        for (const auto& sizingSystem : model().getConcreteModelObjects<SizingSystem>()) {
          auto linkedAirLoop = sizingSystem.getModelObjectTarget<AirLoopHVAC>(openstudio::Sizing_SystemFields::AirLoopName);
          if (linkedAirLoop && *linkedAirLoop == airLoop) {
            matches.push_back(sizingSystem);
          }
        }

        if (matches.empty()) {
          auto sizingSystem = SizingSystem(model(), airLoop);
          detail::addLoadInfo(context, "Created missing Sizing:System '" + sizingSystem.nameString() + "' for AirLoopHVAC '" + loopName + "'.");
        } else {
          // Loop-facing sizing APIs assume a total 1:1 relationship, so
          // duplicate loop-owned sizing objects are dropped here instead of
          // leaking ambiguity into sizingSystem().
          std::sort(matches.begin(), matches.end(), [](const auto& lhs, const auto& rhs) { return lhs.nameString() < rhs.nameString(); });
          for (auto it = std::next(matches.begin()); it != matches.end(); ++it) {
            removeDuplicateModelObject(it->cast<ModelObject>(), "Sizing:System");
          }
        }
      }

      auto assignmentList = availabilityManagerAssignmentList();
      assignmentList.getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->canonicalize(context);

      // AirLoopHVAC availability-schedule APIs are backed by one canonical
      // scheduled-on manager in the assignment list. Canonicalization ensures
      // it exists before any loop-facing availabilitySchedule() call relies on
      // it, then canonicalizes all current availability managers.
      auto availabilityScheduleManager = ensureAvailabilityScheduleManager();
      availabilityScheduleManager.getImpl<detail::AvailabilityManagerScheduledOn_Impl>()->canonicalize(context);
      for (auto& availabilityManager : availabilityManagers()) {
        availabilityManager.getImpl<detail::AvailabilityManager_Impl>()->canonicalize(context);
      }
    }

    void AirLoopHVAC_Impl::syncSupplyWaterCoilControllers() {
      auto airLoop = getObject<AirLoopHVAC>();
      std::vector<ControllerWaterCoil> requiredControllers;

      const auto addController = [&requiredControllers](const boost::optional<ControllerWaterCoil>& controller) {
        if (!controller) {
          return;
        }
        if (std::ranges::none_of(requiredControllers, [&controller](const auto& existing) { return existing.handle() == controller->handle(); })) {
          requiredControllers.push_back(*controller);
        }
      };

      for (const auto& supplyComponent : supplyComponents(openstudio::IddObjectType::Catchall)) {
        if (const auto coolingCoil = supplyComponent.optionalCast<CoilCoolingWater>()) {
          addController(coolingCoil->controllerWaterCoil());
        } else if (const auto heatingCoil = supplyComponent.optionalCast<CoilHeatingWater>()) {
          addController(heatingCoil->controllerWaterCoil());
        }
      }

      auto controllerList = airLoop.getModelObjectTarget<AirLoopHVACControllerList>(AirLoopHVACFields::ControllerListName);
      if (requiredControllers.empty()) {
        if (controllerList) {
          auto controllerListImpl = controllerList->getImpl<detail::AirLoopHVACControllerList_Impl>();
          for (const auto& controller : controllerList->controllers()) {
            if (auto waterController = controller.optionalCast<ControllerWaterCoil>()) {
              OS_ASSERT(controllerListImpl->removeController(waterController->cast<ModelObject>()));
            }
          }
        }
        return;
      }

      if (!controllerList) {
        AirLoopHVACControllerList createdControllerList(model());
        createdControllerList.setName(airLoop.nameString() + " Controllers");
        OS_ASSERT(setPointer(openstudio::AirLoopHVACFields::ControllerListName, createdControllerList.handle()));
        controllerList = createdControllerList;
      }

      auto controllerListImpl = controllerList->getImpl<detail::AirLoopHVACControllerList_Impl>();
      for (const auto& controller : controllerList->controllers()) {
        if (auto waterController = controller.optionalCast<ControllerWaterCoil>()) {
          const bool isRequired = std::ranges::any_of(requiredControllers, [&waterController](const auto& requiredController) {
            return requiredController.handle() == waterController->handle();
          });
          if (!isRequired) {
            OS_ASSERT(controllerListImpl->removeController(waterController->cast<ModelObject>()));
          }
        }
      }

      for (const auto& controller : requiredControllers) {
        OS_ASSERT(controllerListImpl->addController(controller.cast<ModelObject>()));
      }
    }

    // Schema Alignment Notes:
    // - API: availability manager list behavior is routed through AvailabilityManagerAssignmentList methods.
    // - Field Mapping: this resolves AirLoopHVACFields::AvailabilityManagerListName as a typed relationship target.
    AvailabilityManagerAssignmentList AirLoopHVAC_Impl::availabilityManagerAssignmentList() const {
      auto assignmentList =
        getObject<AirLoopHVAC>().getModelObjectTarget<AvailabilityManagerAssignmentList>(AirLoopHVACFields::AvailabilityManagerListName);
      OS_ASSERT(assignmentList);
      return *assignmentList;
    }

    std::vector<AvailabilityManager> AirLoopHVAC_Impl::availabilityManagers() const {
      return availabilityManagerAssignmentList().availabilityManagers();
    }

    boost::optional<openstudio::epmodel::AvailabilityManagerScheduledOn> AirLoopHVAC_Impl::availabilityScheduleManager() const {
      for (const auto& availabilityManager : availabilityManagers()) {
        if (auto scheduledOn = availabilityManager.optionalCast<openstudio::epmodel::AvailabilityManagerScheduledOn>()) {
          return scheduledOn;
        }
      }
      return boost::none;
    }

    openstudio::epmodel::AvailabilityManagerScheduledOn AirLoopHVAC_Impl::ensureAvailabilityScheduleManager() {
      if (auto scheduledOn = availabilityScheduleManager()) {
        return *scheduledOn;
      }

      auto scheduledOn = openstudio::epmodel::AvailabilityManagerScheduledOn(model());
      auto airLoop = getObject<AirLoopHVAC>();
      if (!airLoop.nameString().empty()) {
        scheduledOn.setName(airLoop.nameString() + " Availability Manager Scheduled On");
      }
      OS_ASSERT(availabilityManagerAssignmentList().addAvailabilityManager(scheduledOn));
      return scheduledOn;
    }

    bool AirLoopHVAC_Impl::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
      return availabilityManagerAssignmentList().addAvailabilityManager(availabilityManager);
    }

    bool AirLoopHVAC_Impl::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
      return availabilityManagerAssignmentList().addAvailabilityManager(availabilityManager, priority);
    }

    bool AirLoopHVAC_Impl::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
      if (!availabilityManagerAssignmentList().setAvailabilityManagers(availabilityManagers)) {
        return false;
      }
      ensureAvailabilityScheduleManager();
      return true;
    }

    void AirLoopHVAC_Impl::resetAvailabilityManagers() {
      availabilityManagerAssignmentList().resetAvailabilityManagers();
      ensureAvailabilityScheduleManager();
    }

    bool AirLoopHVAC_Impl::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
      if (!availabilityManagerAssignmentList().removeAvailabilityManager(availabilityManager)) {
        return false;
      }
      ensureAvailabilityScheduleManager();
      return true;
    }

    bool AirLoopHVAC_Impl::removeAvailabilityManager(unsigned priority) {
      if (!availabilityManagerAssignmentList().removeAvailabilityManager(priority)) {
        return false;
      }
      ensureAvailabilityScheduleManager();
      return true;
    }

    bool AirLoopHVAC_Impl::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
      return availabilityManagerAssignmentList().setAvailabilityManagerPriority(availabilityManager, priority);
    }

    unsigned AirLoopHVAC_Impl::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
      return availabilityManagerAssignmentList().availabilityManagerPriority(availabilityManager);
    }

    bool AirLoopHVAC_Impl::addBranchForHVACComponent(openstudio::epmodel::HVACComponent& hvacComponent) {
      return addBranchForHVACComponent(hvacComponent, DemandBranchAttachmentFailureStage::None);
    }

    bool AirLoopHVAC_Impl::addBranchForHVACComponent(openstudio::epmodel::HVACComponent& hvacComponent,
                                                     DemandBranchAttachmentFailureStage failureStage) {
      if (hvacComponent.model() != model()) {
        return false;
      }

      if (hvacComponent.airLoopHVAC()) {
        return false;
      }

      if (!isTerminalTypeValid(hvacComponent)) {
        return false;
      }

      auto airLoop = getObject<AirLoopHVAC>();
      auto reservation = DemandBranchAttachmentPlan::prepare(airLoop);
      if (!reservation) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterReservationPrepared) {
        return false;
      }

      auto branchNode = reservation->node();
      if (failureStage == DemandBranchAttachmentFailureStage::BeforeTerminalAttachment) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterDualDuctTerminalPrepared && !hvacComponent.optionalCast<Mixer>()) {
        return false;
      }
      if (!reservation->prepareTerminalAttachment(hvacComponent, branchNode)) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterDualDuctTerminalPrepared) {
        return false;
      }
      if (!reservation->commit(failureStage)) {
        return false;
      }

      syncSetpointManagerMixedAirFanNodes();
      return true;
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone) {
      return addBranchForZone(thermalZone, DualDuctZoneAttachmentFailureStage::None);
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, DualDuctZoneAttachmentFailureStage failureStage) {
      if (thermalZone.model() != model()) {
        return false;
      }

      const auto zones = thermalZones();
      if (std::find(zones.begin(), zones.end(), thermalZone) != zones.end()) {
        return false;
      }

      if (isDualDuct()) {
        // Match canonical AirLoopHVAC behavior: if the current trailing
        // dual-duct branch already has a terminal, attach the zone behind it
        // instead of cloning a new terminal branch.
        if (auto terminal = reusableDualDuctTerminalForZone()) {
          auto airLoop = getObject<AirLoopHVAC>();
          auto attachment = DualDuctZoneAttachment::prepare(airLoop, thermalZone, *terminal, failureStage);
          if (!attachment) {
            return false;
          }

          attachment->commit();
          return true;
        }

        if (failureStage != DualDuctZoneAttachmentFailureStage::None) {
          return false;
        }

        if (auto terminal = cloneLastDualDuctTerminalForBranch()) {
          if (addBranchForZone(thermalZone, *terminal)) {
            return true;
          }
          terminal->remove();
          return false;
        }
        return addBranchForZone(thermalZone, DemandBranchAttachmentFailureStage::None);
      }

      return addBranchForZone(thermalZone, DemandBranchAttachmentFailureStage::None);
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, DemandBranchAttachmentFailureStage failureStage) {
      if (thermalZone.model() != model()) {
        return false;
      }

      const auto zones = thermalZones();
      if (std::find(zones.begin(), zones.end(), thermalZone) != zones.end()) {
        return false;
      }

      auto airLoop = getObject<AirLoopHVAC>();
      if (!reusableSingleDuctTerminalForZone()) {
        if (auto sourceTerminal = lastSingleDuctTerminalForClone()) {
          // Declare the branch plan first so rollback removes the cloned
          // terminal (while its provisional branch and zone projection still
          // exist) before restoring the surrounding branch transaction.
          std::unique_ptr<DemandBranchAttachmentPlan> reservation;
          auto clonePlan = SingleDuctTerminalClonePlan::prepare(*sourceTerminal, failureStage);
          if (!clonePlan) {
            return false;
          }

          reservation = DemandBranchAttachmentPlan::prepare(airLoop);
          if (!reservation) {
            return false;
          }
          if (failureStage == DemandBranchAttachmentFailureStage::AfterReservationPrepared) {
            return false;
          }
          if (!reservation->prepareZoneAttachment(thermalZone)) {
            return false;
          }
          if (failureStage == DemandBranchAttachmentFailureStage::AfterZonePrepared) {
            return false;
          }
          if (!clonePlan->prepareZoneProjectionSnapshot(thermalZone)) {
            return false;
          }

          auto terminalNodeObject = zoneSplitter().outletModelObject(reservation->branchIndex());
          auto terminalNode = terminalNodeObject ? terminalNodeObject->optionalCast<Node>() : boost::optional<Node>();
          if (!terminalNode || failureStage == DemandBranchAttachmentFailureStage::BeforeTerminalAttachment
              || failureStage == DemandBranchAttachmentFailureStage::AfterDualDuctTerminalPrepared) {
            return false;
          }
          auto terminal = clonePlan->terminal();
          if (!reservation->prepareTerminalAttachment(terminal, *terminalNode)) {
            return false;
          }
          if (failureStage == DemandBranchAttachmentFailureStage::AfterTerminalZoneProjectionPrepared) {
            return false;
          }
          if (!reservation->commit(DemandBranchAttachmentFailureStage::None)) {
            return false;
          }
          clonePlan->commit();
          syncControllerMechanicalVentilationZoneOutdoorAirEntries();
          syncSetpointManagerMixedAirFanNodes();
          return true;
        }

        if (failureStage == DemandBranchAttachmentFailureStage::AfterTerminalClonePrepared
            || failureStage == DemandBranchAttachmentFailureStage::AfterFirstPlantReconnectionPrepared
            || failureStage == DemandBranchAttachmentFailureStage::AfterPlantReconnectionPrepared) {
          return false;
        }
      }

      auto reservation = DemandBranchAttachmentPlan::prepareForZone(airLoop);
      if (!reservation) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterReservationPrepared) {
        return false;
      }
      if (!reservation->prepareZoneAttachment(thermalZone)) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterZonePrepared) {
        return false;
      }
      if (!reservation->commit(failureStage)) {
        return false;
      }
      syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      return true;
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, openstudio::epmodel::HVACComponent& airTerminal) {
      return addBranchForZone(thermalZone, airTerminal, DemandBranchAttachmentFailureStage::None);
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, openstudio::epmodel::HVACComponent& airTerminal,
                                            DemandBranchAttachmentFailureStage failureStage) {
      if (thermalZone.model() != model() || airTerminal.model() != model()) {
        return false;
      }

      if (airTerminal.airLoopHVAC()) {
        return false;
      }

      if (!isTerminalTypeValid(airTerminal)) {
        return false;
      }

      const auto zones = thermalZones();
      if (std::find(zones.begin(), zones.end(), thermalZone) != zones.end()) {
        if (failureStage != DemandBranchAttachmentFailureStage::None) {
          return false;
        }
        // Removing an air terminal leaves the zone branch itself in place. If
        // that surviving branch now runs directly from the splitter to one of
        // this zone's inlet nodes, reuse it for the replacement terminal.
        // A populated terminal branch has a transient terminal inlet at the
        // splitter instead, so it will not match this condition.
        auto zoneConnections = thermalZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
        if (!zoneConnections) {
          return false;
        }
        const auto zoneInletNodes = zoneConnections->zoneAirInletNodes();
        const auto splitterOutlets = zoneSplitter().outletModelObjects();
        for (const auto& splitterOutlet : splitterOutlets) {
          auto splitterOutletNode = splitterOutlet.optionalCast<Node>();
          if (splitterOutletNode && std::ranges::find(zoneInletNodes, *splitterOutletNode) != zoneInletNodes.end()) {
            if (!airTerminal.addToNode(*splitterOutletNode)) {
              return false;
            }
            syncControllerMechanicalVentilationZoneOutdoorAirEntries();
            syncSetpointManagerMixedAirFanNodes();
            return true;
          }
        }
        return false;
      }

      auto airLoop = getObject<AirLoopHVAC>();
      auto reservation = DemandBranchAttachmentPlan::prepare(airLoop);
      if (!reservation) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterReservationPrepared) {
        return false;
      }
      if (!reservation->prepareZoneAttachment(thermalZone)) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterZonePrepared) {
        return false;
      }

      auto terminalNodeObject = zoneSplitter().outletModelObject(reservation->branchIndex());
      auto terminalNode = terminalNodeObject ? terminalNodeObject->optionalCast<Node>() : boost::optional<Node>();
      if (!terminalNode) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::BeforeTerminalAttachment) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterDualDuctTerminalPrepared && !airTerminal.optionalCast<Mixer>()) {
        return false;
      }
      if (!reservation->prepareTerminalAttachment(airTerminal, *terminalNode)) {
        return false;
      }
      if (failureStage == DemandBranchAttachmentFailureStage::AfterDualDuctTerminalPrepared) {
        return false;
      }
      if (!reservation->commit(failureStage)) {
        return false;
      }

      syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      syncSetpointManagerMixedAirFanNodes();
      return true;
    }

    AirLoopHVAC_Impl::DualDuctZoneAttachment::DualDuctZoneAttachment(AirLoopHVAC airLoop, ThermalZone thermalZone, Mixer terminal, Node zoneInletNode,
                                                                     AirLoopHVACZoneMixer zoneMixer, unsigned branchIndex,
                                                                     ZoneHVACEquipmentConnections zoneConnections,
                                                                     ZoneHVACEquipmentList equipmentList)
      : m_airLoop(std::move(airLoop)),
        m_thermalZone(std::move(thermalZone)),
        m_terminal(std::move(terminal)),
        m_zoneInletNode(std::move(zoneInletNode)),
        m_zoneMixer(std::move(zoneMixer)),
        m_branchIndex(branchIndex),
        m_zoneConnections(std::move(zoneConnections)),
        m_equipmentList(std::move(equipmentList)),
        m_provisionalState(std::make_unique<ProvisionalState>()) {}

    AirLoopHVAC_Impl::DualDuctZoneAttachment::~DualDuctZoneAttachment() {
      if (m_state == State::Prepared) {
        cleanupProvisionalState();
      }
    }

    void AirLoopHVAC_Impl::DualDuctZoneAttachment::cleanupProvisionalState() {
      if (!m_provisionalState) {
        return;
      }

      // Preparation enrolls only objects that it created. Existing return
      // nodes and ADUs remain model-owned even when preparation is abandoned.
      if (m_provisionalState->airDistributionUnit && m_airLoop.model().getObject(m_provisionalState->airDistributionUnit->handle())) {
        m_provisionalState->airDistributionUnit->remove();
      }
      if (m_provisionalState->returnNode && m_airLoop.model().getObject(m_provisionalState->returnNode->handle())) {
        const bool returnNodeRemoved = m_airLoop.model().removeObject(m_provisionalState->returnNode->handle());
        OS_ASSERT(returnNodeRemoved);
        (void)returnNodeRemoved;
      }
      if (m_provisionalState->zoneConnections && m_airLoop.model().getObject(m_provisionalState->zoneConnections->handle())) {
        m_provisionalState->zoneConnections->remove();
      }
      if (m_provisionalState->equipmentList && m_airLoop.model().getObject(m_provisionalState->equipmentList->handle())) {
        m_provisionalState->equipmentList->remove();
      }
      if (m_provisionalState->zoneAirNode && m_airLoop.model().getObject(m_provisionalState->zoneAirNode->handle())) {
        const bool zoneAirNodeRemoved = m_airLoop.model().removeObject(m_provisionalState->zoneAirNode->handle());
        OS_ASSERT(zoneAirNodeRemoved);
        (void)zoneAirNodeRemoved;
      }
    }

    void AirLoopHVAC_Impl::DualDuctZoneAttachment::prepareReturnNode() {
      const auto returnNodeName = m_thermalZone.nameString() + " Demand Return Node";
      if (auto existingNode = m_airLoop.model().getConcreteModelObjectByName<Node>(returnNodeName)) {
        m_zoneReturnNode = *existingNode;
        return;
      }

      auto returnNode = m_airLoop.model().getOrCreateTransientByName<Node>(returnNodeName);
      m_zoneReturnNode = returnNode;
      m_provisionalState->returnNode = returnNode;
    }

    bool AirLoopHVAC_Impl::DualDuctZoneAttachment::prepareZoneEquipment() {
      const auto terminalObject = m_terminal.cast<ModelObject>();
      const auto equipment = m_equipmentList.equipment();
      m_registerEquipment = std::ranges::find(equipment, terminalObject) == equipment.end();
      m_airDistributionUnitToSynchronize = airDistributionUnitForZoneEquipment(terminalObject);
      if (!m_registerEquipment || m_airDistributionUnitToSynchronize) {
        return true;
      }

      m_provisionalState->airDistributionUnit = ZoneHVACAirDistributionUnit(m_airLoop.model());
      if (!m_terminal.nameString().empty()) {
        m_provisionalState->airDistributionUnit->setName(m_terminal.nameString() + " Air Distribution Unit");
      }

      auto airDistributionUnitImpl = m_provisionalState->airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
      OS_ASSERT(airDistributionUnitImpl);
      if (!airDistributionUnitImpl->setAirTerminal(terminalObject) || !airDistributionUnitImpl->setOutletNode(m_zoneInletNode)) {
        return false;
      }

      m_airDistributionUnitToSynchronize = *m_provisionalState->airDistributionUnit;
      return true;
    }

    std::unique_ptr<AirLoopHVAC_Impl::DualDuctZoneAttachment>
      AirLoopHVAC_Impl::DualDuctZoneAttachment::prepare(AirLoopHVAC& airLoop, ThermalZone& thermalZone, Mixer& terminal,
                                                        DualDuctZoneAttachmentFailureStage failureStage) {
      if (airLoop.model() != thermalZone.model() || airLoop.model() != terminal.model() || !airLoop.isDualDuct()) {
        return nullptr;
      }

      const auto attachedZones = airLoop.thermalZones();
      if (std::ranges::find(attachedZones, thermalZone) != attachedZones.end()) {
        return nullptr;
      }

      auto terminalAirLoop = terminal.airLoopHVAC();
      if (!terminalAirLoop || *terminalAirLoop != airLoop) {
        return nullptr;
      }

      auto outletObject = terminal.outletModelObject();
      auto zoneInletNode = outletObject ? outletObject->optionalCast<Node>() : boost::none;
      if (!zoneInletNode) {
        return nullptr;
      }

      auto zoneMixer = airLoop.zoneMixer();
      const auto mixerInlets = zoneMixer.inletModelObjects();
      const auto mixerInletIt = std::ranges::find(mixerInlets, zoneInletNode->cast<ModelObject>());
      if (mixerInletIt == mixerInlets.end()) {
        return nullptr;
      }
      const auto branchIndex = static_cast<unsigned>(std::distance(mixerInlets.begin(), mixerInletIt));

      auto thermalZoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(thermalZoneImpl);
      auto zoneConnections = thermalZoneImpl->zoneHVACEquipmentConnections();
      const bool createdZoneConnections = !zoneConnections;
      const auto zoneAirNodeName = thermalZone.nameString() + " Demand Branch Node";
      const bool zoneAirNodeExisted = static_cast<bool>(airLoop.model().getConcreteModelObjectByName<Node>(zoneAirNodeName));
      if (!zoneConnections) {
        zoneConnections = thermalZoneImpl->getZoneHVACEquipmentConnections();
      }
      auto equipmentList = zoneConnections->zoneHVACEquipmentList();
      auto zoneAirNode = zoneConnections->zoneAirNode();

      auto attachment = std::unique_ptr<DualDuctZoneAttachment>(
        new DualDuctZoneAttachment(airLoop, thermalZone, terminal, *zoneInletNode, zoneMixer, branchIndex, *zoneConnections, equipmentList));
      if (createdZoneConnections) {
        attachment->m_provisionalState->zoneConnections = *zoneConnections;
        attachment->m_provisionalState->equipmentList = equipmentList;
        if (!zoneAirNodeExisted) {
          attachment->m_provisionalState->zoneAirNode = zoneAirNode;
        }
      }
      attachment->prepareReturnNode();
      if (!attachment->prepareZoneEquipment()) {
        return nullptr;
      }

      attachment->m_disableIdealAirLoads = thermalZone.useIdealAirLoads();

      if (failureStage == DualDuctZoneAttachmentFailureStage::AfterProvisionalObjectsPrepared) {
        return nullptr;
      }

      return attachment;
    }

    void AirLoopHVAC_Impl::DualDuctZoneAttachment::commit() {
      if (m_state != State::Prepared) {
        OS_ASSERT(false);
        return;
      }

      OS_ASSERT(m_zoneReturnNode);
      auto zoneConnectionsImpl = m_zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(zoneConnectionsImpl);

      // Preparation has resolved every owner and validated every relationship.
      // Keep each mutation outside its assertion so release builds execute the
      // full commit; a false result is an internal-contract violation here.
      if (m_disableIdealAirLoads) {
        const bool idealAirLoadsDisabled = m_thermalZone.setUseIdealAirLoads(false);
        OS_ASSERT(idealAirLoadsDisabled);
        (void)idealAirLoadsDisabled;
      }
      const bool mixerRewired = m_zoneMixer.setInletModelObject(m_branchIndex, m_zoneReturnNode->cast<ModelObject>());
      OS_ASSERT(mixerRewired);
      (void)mixerRewired;
      const bool inletRegistered = zoneConnectionsImpl->addZoneAirInletNode(m_zoneInletNode);
      OS_ASSERT(inletRegistered);
      (void)inletRegistered;
      const bool returnRegistered = zoneConnectionsImpl->addZoneReturnAirNode(*m_zoneReturnNode);
      OS_ASSERT(returnRegistered);
      (void)returnRegistered;

      if (m_registerEquipment) {
        const bool equipmentRegistered = m_equipmentList.addEquipment(m_terminal);
        OS_ASSERT(equipmentRegistered);
        (void)equipmentRegistered;
      }

      // A terminal-first branch can already have its translator-facing ADU.
      // Keep that wrapper's outlet synchronized while retaining the terminal
      // as the zone-facing equipment returned by epmodel.
      if (m_airDistributionUnitToSynchronize) {
        auto airDistributionUnitImpl = m_airDistributionUnitToSynchronize->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
        OS_ASSERT(airDistributionUnitImpl);
        const bool outletSynchronized = airDistributionUnitImpl->setOutletNode(m_zoneInletNode);
        OS_ASSERT(outletSynchronized);
        (void)outletSynchronized;
      }

      m_state = State::Committed;
      m_provisionalState.reset();

      auto airLoopImpl = m_airLoop.getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      airLoopImpl->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();
    }

    AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::DualDuctTerminalInsertionPlan(Mixer terminal, Node outletNode, AirLoopHVAC airLoop,
                                                                                   AirLoopHVACZoneSplitter primarySplitter,
                                                                                   unsigned primaryBranchIndex)
      : m_terminal(std::move(terminal)),
        m_outletNode(std::move(outletNode)),
        m_airLoop(std::move(airLoop)),
        m_primarySplitter(std::move(primarySplitter)),
        m_primaryBranchIndex(primaryBranchIndex),
        m_provisionalObjects(std::make_unique<ProvisionalObjects>()) {}

    AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::~DualDuctTerminalInsertionPlan() {
      if (m_state == State::Prepared) {
        cleanupProvisionalObjects();
      }
    }

    void AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::cleanupProvisionalObjects() {
      if (!m_provisionalObjects) {
        return;
      }

      // Preparation owns only objects that were newly created for this
      // insertion. Existing imported infrastructure is never enrolled.
      if (m_provisionalObjects->airDistributionUnit && m_terminal.model().getObject(m_provisionalObjects->airDistributionUnit->handle())) {
        m_provisionalObjects->airDistributionUnit->remove();
      }
      if (m_provisionalObjects->supplyPath && m_terminal.model().getObject(m_provisionalObjects->supplyPath->handle())) {
        m_provisionalObjects->supplyPath->remove();
      }
      if (m_provisionalObjects->splitter && m_terminal.model().getObject(m_provisionalObjects->splitter->handle())) {
        m_provisionalObjects->splitter->remove();
      }
      for (auto it = m_provisionalObjects->nodes.rbegin(); it != m_provisionalObjects->nodes.rend(); ++it) {
        if (m_terminal.model().getObject(it->handle())) {
          m_terminal.model().removeObject(it->handle());
        }
      }
    }

    Node AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::resolveOrCreateProvisionalNode(const std::string& name) {
      if (auto existingNode = m_terminal.model().getConcreteModelObjectByName<Node>(name)) {
        return *existingNode;
      }

      auto node = m_terminal.model().getOrCreateTransientByName<Node>(name);
      m_provisionalObjects->nodes.push_back(node);
      return node;
    }

    std::unique_ptr<AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan>
      AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::prepare(openstudio::epmodel::Mixer& terminal, openstudio::epmodel::Node& node) {
      if (terminal.model() != node.model()) {
        return nullptr;
      }

      if (terminal.loop()) {
        return nullptr;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return nullptr;
      }

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);

      auto splitterA = airLoopImpl->zoneSplitter();
      auto mixer = airLoopImpl->zoneMixer();

      boost::optional<unsigned> branchIndex;
      const auto outlets = splitterA.outletModelObjects();
      for (unsigned i = 0; i < outlets.size(); ++i) {
        if (outlets[i] == node) {
          branchIndex = i;
          break;
        }
      }
      if (!branchIndex) {
        return nullptr;
      }

      auto mixerInlet = mixer.inletModelObject(*branchIndex);
      if (!mixerInlet) {
        return nullptr;
      }

      // Once a ThermalZone owns this branch, its supply inlet and return node
      // are intentionally distinct. Accept that canonical zone branch shape as
      // well as the initial empty splitter-to-mixer branch.
      boost::optional<ThermalZone> servedZone;
      if (*mixerInlet != node) {
        servedZone = resolveZoneServedByInletNode(node);
        auto mixerInletNode = mixerInlet->optionalCast<Node>();
        auto returnZone = mixerInletNode ? resolveZoneServedByReturnNode(*mixerInletNode) : boost::none;
        if (!servedZone || !returnZone || *servedZone != *returnZone) {
          return nullptr;
        }
      }

      auto plan =
        std::unique_ptr<DualDuctTerminalInsertionPlan>(new DualDuctTerminalInsertionPlan(terminal, node, *airLoop, splitterA, *branchIndex));

      if (!plan->prepareSecondaryDemandPath()) {
        return nullptr;
      }
      plan->prepareTerminalInletNodes();

      if (!servedZone) {
        servedZone = resolveZoneServedByInletNode(node);
      }
      if (!plan->prepareZoneEquipment(servedZone)) {
        return nullptr;
      }

      return plan;
    }

    bool AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::prepareSecondaryDemandPath() {
      auto airLoopImpl = m_airLoop.getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      const auto demandInlets = airLoopImpl->demandInletNodes();
      if (demandInlets.size() >= 2u) {
        m_secondaryDemandInletNode = demandInlets[1];
        m_secondarySplitter = airLoopImpl->zoneSplitterForDemandInletNode(demandInlets[1]);
        if (!m_secondarySplitter) {
          return false;
        }
      } else {
        m_demandInletNodeListToAppend = m_airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::DemandSideInletNodeNames);
        if (!m_demandInletNodeListToAppend) {
          return false;
        }

        const auto secondaryDemandInletName = m_airLoop.nameString() + " Demand Inlet Node 2";
        m_secondaryDemandInletNode = resolveOrCreateProvisionalNode(secondaryDemandInletName);
        for (const auto& candidate : m_terminal.model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
          auto inletNode = candidate.getImpl<detail::AirLoopHVACSupplyPath_Impl>()->supplyAirPathInletNode();
          if (inletNode && *inletNode == *m_secondaryDemandInletNode) {
            m_secondarySupplyPath = candidate;
            break;
          }
        }

        if (m_secondarySupplyPath) {
          for (const auto& component : m_secondarySupplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>()->components()) {
            if (auto splitter = component.optionalCast<AirLoopHVACZoneSplitter>()) {
              m_secondarySplitter = *splitter;
              break;
            }
          }
        }
        if (!m_secondarySplitter) {
          for (const auto& candidate : m_terminal.model().getConcreteModelObjects<AirLoopHVACZoneSplitter>()) {
            auto inletNode = candidate.getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->inletNode();
            if (inletNode && *inletNode == *m_secondaryDemandInletNode) {
              m_secondarySplitter = candidate;
              break;
            }
          }
        }

        if (!m_secondarySupplyPath) {
          m_provisionalObjects->supplyPath = AirLoopHVACSupplyPath(m_terminal.model());
          m_provisionalObjects->supplyPath->setName(m_airLoop.nameString() + " Supply Path 2");
          auto supplyPathImpl = m_provisionalObjects->supplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>();
          OS_ASSERT(supplyPathImpl);
          if (!supplyPathImpl->setSupplyAirPathInletNode(*m_secondaryDemandInletNode)) {
            return false;
          }
          m_secondarySupplyPath = *m_provisionalObjects->supplyPath;
        }

        if (!m_secondarySplitter) {
          m_provisionalObjects->splitter = AirLoopHVACZoneSplitter(m_terminal.model());
          m_provisionalObjects->splitter->setName(m_airLoop.nameString() + " Zone Splitter 2");
          auto splitterImpl = m_provisionalObjects->splitter->getImpl<detail::AirLoopHVACZoneSplitter_Impl>();
          OS_ASSERT(splitterImpl);
          if (!splitterImpl->setInletNode(*m_secondaryDemandInletNode)) {
            return false;
          }
          m_secondarySplitter = *m_provisionalObjects->splitter;
        }

        const auto supplyPathComponents = m_secondarySupplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>()->components();
        const bool supplyPathContainsSplitter =
          std::ranges::find(supplyPathComponents, m_secondarySplitter->cast<ModelObject>()) != supplyPathComponents.end();
        if (!supplyPathContainsSplitter) {
          if (!m_secondarySplitter->name() || m_secondarySplitter->name()->empty()) {
            return false;
          }
          if (m_provisionalObjects->supplyPath) {
            auto supplyPathImpl = m_secondarySupplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>();
            OS_ASSERT(supplyPathImpl);
            if (!supplyPathImpl->addComponent(*m_secondarySplitter)) {
              return false;
            }
          } else {
            m_supplyPathToAppendSplitter = *m_secondarySupplyPath;
          }
        }
      }

      // Secondary splitter rows are terminal-owned and need not match the
      // primary splitter's zone-branch ordering.
      m_secondaryBranchIndex = m_secondarySplitter->nextBranchIndex();
      return true;
    }

    void AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::prepareTerminalInletNodes() {
      const auto inletAName = m_outletNode.nameString() + " - " + m_terminal.nameString() + " Inlet 1";
      m_primaryInletNode = resolveOrCreateProvisionalNode(inletAName);
      const auto inletBName = m_outletNode.nameString() + " - " + m_terminal.nameString() + " Inlet 2";
      m_secondaryInletNode = resolveOrCreateProvisionalNode(inletBName);
    }

    bool AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::prepareZoneEquipment(const boost::optional<ThermalZone>& servedZone) {
      if (!servedZone) {
        return true;
      }

      auto connections = servedZone->getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
      if (!connections) {
        return true;
      }

      const auto equipmentList = connections->zoneHVACEquipmentList();
      const auto terminalObject = m_terminal.cast<ModelObject>();
      const auto currentEquipment = equipmentList.equipment();
      if (std::ranges::find(currentEquipment, terminalObject) == currentEquipment.end()) {
        m_equipmentListToRegister = equipmentList;
      }
      m_airDistributionUnitToSynchronize = airDistributionUnitForZoneEquipment(terminalObject);
      if (m_equipmentListToRegister && !m_airDistributionUnitToSynchronize) {
        m_provisionalObjects->airDistributionUnit = ZoneHVACAirDistributionUnit(m_terminal.model());
        if (!m_terminal.nameString().empty()) {
          m_provisionalObjects->airDistributionUnit->setName(m_terminal.nameString() + " Air Distribution Unit");
        }
        auto airDistributionUnitImpl = m_provisionalObjects->airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
        OS_ASSERT(airDistributionUnitImpl);
        if (!airDistributionUnitImpl->setAirTerminal(terminalObject) || !airDistributionUnitImpl->setOutletNode(m_outletNode)) {
          return false;
        }
        m_airDistributionUnitToSynchronize = *m_provisionalObjects->airDistributionUnit;
      }

      return true;
    }

    void AirLoopHVAC_Impl::DualDuctTerminalInsertionPlan::commit() {
      if (m_state != State::Prepared) {
        OS_ASSERT(false);
        return;
      }

      // Preparation has resolved every owner and verified every relationship.
      // Commit therefore contains only same-model pointer/list writes whose
      // preconditions are already satisfied. Evaluate each write outside its
      // assertion so release builds perform the mutation; a false result here
      // is a violated internal contract, not a recoverable insertion failure.
      if (m_supplyPathToAppendSplitter) {
        OS_ASSERT(m_secondarySplitter);
        auto supplyPathImpl = m_supplyPathToAppendSplitter->getImpl<detail::AirLoopHVACSupplyPath_Impl>();
        OS_ASSERT(supplyPathImpl);
        const bool splitterAdded = supplyPathImpl->addComponent(*m_secondarySplitter);
        OS_ASSERT(splitterAdded);
        (void)splitterAdded;
      }
      if (m_demandInletNodeListToAppend) {
        OS_ASSERT(m_secondaryDemandInletNode);
        const bool demandInletAdded = m_demandInletNodeListToAppend->getImpl<detail::NodeList_Impl>()->addNode(*m_secondaryDemandInletNode);
        OS_ASSERT(demandInletAdded);
        (void)demandInletAdded;
      }

      OS_ASSERT(m_primaryInletNode);
      OS_ASSERT(m_secondaryInletNode);
      OS_ASSERT(m_secondarySplitter);
      const bool primaryBranchConnected = m_primarySplitter.setOutletModelObject(m_primaryBranchIndex, m_primaryInletNode->cast<ModelObject>());
      OS_ASSERT(primaryBranchConnected);
      (void)primaryBranchConnected;
      const bool primaryInletConnected = m_terminal.setInletModelObject(0u, m_primaryInletNode->cast<ModelObject>());
      OS_ASSERT(primaryInletConnected);
      (void)primaryInletConnected;
      const bool outletConnected = m_terminal.setOutletModelObject(m_outletNode.cast<ModelObject>());
      OS_ASSERT(outletConnected);
      (void)outletConnected;
      const bool secondaryBranchConnected =
        m_secondarySplitter->setOutletModelObject(m_secondaryBranchIndex, m_secondaryInletNode->cast<ModelObject>());
      OS_ASSERT(secondaryBranchConnected);
      (void)secondaryBranchConnected;
      const bool secondaryInletConnected = m_terminal.setInletModelObject(1u, m_secondaryInletNode->cast<ModelObject>());
      OS_ASSERT(secondaryInletConnected);
      (void)secondaryInletConnected;

      if (m_airDistributionUnitToSynchronize) {
        auto airDistributionUnitImpl = m_airDistributionUnitToSynchronize->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
        OS_ASSERT(airDistributionUnitImpl);
        const bool outletSynchronized = airDistributionUnitImpl->setOutletNode(m_outletNode);
        OS_ASSERT(outletSynchronized);
        (void)outletSynchronized;
      }

      if (m_equipmentListToRegister) {
        const bool equipmentRegistered = m_equipmentListToRegister->addEquipment(m_terminal);
        OS_ASSERT(equipmentRegistered);
        (void)equipmentRegistered;
      }

      m_state = State::Committed;
      m_provisionalObjects.reset();

      auto airLoopImpl = m_airLoop.getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      airLoopImpl->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();
    }

    bool AirLoopHVAC_Impl::addDualDuctTerminalToNode(openstudio::epmodel::Mixer& terminal, openstudio::epmodel::Node& node) {
      auto plan = DualDuctTerminalInsertionPlan::prepare(terminal, node);
      if (!plan) {
        return false;
      }

      plan->commit();
      return true;
    }

    bool AirLoopHVAC_Impl::removeDualDuctTerminalFromAirLoopHVAC(openstudio::epmodel::Mixer& terminal) {
      const auto clearZoneEquipment = [&terminal]() {
        const auto terminalObject = terminal.cast<ModelObject>();
        std::vector<ZoneHVACAirDistributionUnit> airDistributionUnits;
        for (const auto& source : terminalObject.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
          if (auto adu = source.optionalCast<ZoneHVACAirDistributionUnit>()) {
            airDistributionUnits.push_back(*adu);
          }
        }
        for (auto& zone : terminal.model().getConcreteModelObjects<ThermalZone>()) {
          if (auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()) {
            auto equipmentList = connections->zoneHVACEquipmentList();
            equipmentList.removeEquipment(terminalObject);
          }
        }
        for (auto& airDistributionUnit : airDistributionUnits) {
          if (terminal.model().getObject(airDistributionUnit.handle())) {
            airDistributionUnit.remove();
          }
        }
      };

      auto primaryInlet = terminal.inletModelObject(0u);
      auto secondaryInlet = terminal.inletModelObject(1u);
      auto outlet = terminal.outletModelObject();

      auto airLoop = terminal.airLoopHVAC();
      if (!airLoop) {
        // A fully disconnected terminal may still have stale zone-equipment
        // bookkeeping, which remove() is expected to clean. Any surviving
        // port, however, is evidence of malformed connected topology: retain
        // the terminal and leave all ownership records untouched.
        if (primaryInlet || secondaryInlet || outlet) {
          return false;
        }
        clearZoneEquipment();
        return true;
      }

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);

      if (!primaryInlet || !secondaryInlet || !outlet) {
        return false;
      }

      auto primaryInletNode = primaryInlet->optionalCast<Node>();
      auto secondaryInletNode = secondaryInlet->optionalCast<Node>();
      auto outletNode = outlet->optionalCast<Node>();
      if (!primaryInletNode || !secondaryInletNode || !outletNode) {
        return false;
      }

      auto primarySplitter = airLoopImpl->zoneSplitter();
      const auto primaryOutlets = primarySplitter.outletModelObjects();
      const auto primaryBranchIndex = primarySplitter.branchIndexForOutletModelObject(*primaryInlet);
      if (primaryBranchIndex >= primaryOutlets.size() || !(primaryOutlets[primaryBranchIndex] == *primaryInlet)) {
        return false;
      }

      const auto demandInlets = airLoopImpl->demandInletNodes();
      if (demandInlets.size() < 2u) {
        return false;
      }

      auto secondarySplitter = airLoopImpl->zoneSplitterForDemandInletNode(demandInlets[1]);
      if (!secondarySplitter) {
        return false;
      }

      const auto secondaryOutlets = secondarySplitter->outletModelObjects();
      const auto secondaryBranchIndex = secondarySplitter->branchIndexForOutletModelObject(*secondaryInlet);
      if (secondaryBranchIndex >= secondaryOutlets.size() || !(secondaryOutlets[secondaryBranchIndex] == *secondaryInlet)) {
        return false;
      }

      // Validate the only fallible prerequisite for collapsing the final
      // secondary path before changing either terminal branch.
      if (secondaryOutlets.size() == 1u) {
        auto demandInletNodeList = airLoop->getModelObjectTarget<NodeList>(AirLoopHVACFields::DemandSideInletNodeNames);
        if (!demandInletNodeList) {
          return false;
        }
        const auto listedDemandInlets = demandInletNodeList->nodes();
        if (std::ranges::find(listedDemandInlets, demandInlets[1]) == listedDemandInlets.end()) {
          return false;
        }
      }

      // Fully detach the terminal from both demand paths before deleting any
      // transient Node. Calling Node::remove while one side is still connected
      // re-enters demand traversal against a half-mutated branch and can expose
      // invalid WorkspaceObject sources.
      if (!primarySplitter.setOutletModelObject(primaryBranchIndex, outletNode->cast<ModelObject>())) {
        return false;
      }
      terminal.resetInletModelObject(1u);
      secondarySplitter->removePortForBranch(secondaryBranchIndex);
      terminal.resetInletModelObject(0u);
      terminal.resetOutletModelObject();

      if (!airLoopImpl->collapseSecondaryDemandPathIfEmpty(demandInlets[1], *secondarySplitter)) {
        return false;
      }

      // These nodes are now detached connective tissue. Remove them directly
      // from the workspace so their StraightComponent removal path cannot try
      // to rediscover a loop that is deliberately being dismantled.
      const auto secondaryInletHandle = secondaryInletNode->handle();
      if (terminal.model().getObject(secondaryInletHandle) && !terminal.model().removeObject(secondaryInletHandle)) {
        return false;
      }
      const auto primaryInletHandle = primaryInletNode->handle();
      if (terminal.model().getObject(primaryInletHandle) && !terminal.model().removeObject(primaryInletHandle)) {
        return false;
      }

      clearZoneEquipment();
      return true;
    }

    bool AirLoopHVAC_Impl::removeBranchForZone(openstudio::epmodel::ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      auto conn = thermalZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
      if (!conn) {
        return false;
      }

      const auto zoneNodes = conn->zoneAirInletNodes();
      if (zoneNodes.empty()) {
        return false;
      }

      boost::optional<Node> zoneNode;
      boost::optional<unsigned> branchIndex;
      std::set<Handle> branchZoneInletNodeHandles;
      for (const auto& candidate : zoneNodes) {
        auto candidateBranchIndex = demandBranchIndexForZoneInletNode(candidate);
        if (candidateBranchIndex) {
          branchZoneInletNodeHandles.insert(candidate.handle());
        }
        if (candidateBranchIndex && !branchIndex) {
          branchIndex = candidateBranchIndex;
          zoneNode = candidate;
        }
      }
      if (!branchIndex) {
        const auto mixerInlets = zoneMixer().inletModelObjects();
        for (const auto& returnNode : conn->zoneReturnAirNodes()) {
          for (unsigned i = 0; i < mixerInlets.size(); ++i) {
            if (mixerInlets[i] == returnNode.cast<ModelObject>()) {
              branchIndex = i;
              zoneNode = zoneNodes.front();
              break;
            }
          }
          if (branchIndex) {
            break;
          }
        }
      }
      if (!branchIndex) {
        return false;
      }

      const auto splitterOutlets = zoneSplitter().outletModelObjects();
      if (*branchIndex >= splitterOutlets.size()) {
        return false;
      }
      auto splitterOutletNode = splitterOutlets[*branchIndex].optionalCast<openstudio::epmodel::Node>();
      if (!splitterOutletNode) {
        return false;
      }

      auto branchPath = demandComponents(*splitterOutletNode, *zoneNode, openstudio::IddObjectType::Catchall);
      if (branchPath.empty()) {
        const auto mixerInletObject = zoneMixer().inletModelObject(*branchIndex);
        auto mixerInletNode = mixerInletObject ? mixerInletObject->optionalCast<openstudio::epmodel::Node>() : boost::optional<Node>();
        if (mixerInletNode) {
          branchPath = demandComponents(*splitterOutletNode, *mixerInletNode, openstudio::IddObjectType::Catchall);
        }
      }
      if (branchPath.empty()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                 "Unable to resolve branch-local demand components for zone '" << thermalZone.nameString() << "' during removeBranchForZone.");
        return false;
      }

      std::set<Handle> branchPathHandles;
      for (const auto& component : branchPath) {
        branchPathHandles.insert(component.handle());
      }

      auto equipmentList = conn->zoneHVACEquipmentList();
      struct BranchOwnedTerminal
      {
        ModelObject terminal;
        ZoneHVACAirDistributionUnit airDistributionUnit;
      };
      std::vector<BranchOwnedTerminal> branchOwnedTerminals;
      std::set<Handle> enrolledTerminalHandles;
      for (const auto& equipment : equipmentList.equipment()) {
        auto airDistributionUnit = airDistributionUnitForZoneEquipment(equipment);
        if (!airDistributionUnit) {
          continue;
        }

        auto airTerminal = airDistributionUnit->airTerminal();
        auto outletNode = airDistributionUnit->outletNode();
        const bool equipmentOnBranch = branchPathHandles.contains(equipment.handle());
        const bool terminalOnBranch = airTerminal && branchPathHandles.contains(airTerminal->handle());
        const bool outletOnBranch = outletNode && branchZoneInletNodeHandles.contains(outletNode->handle());
        if (!airTerminal || (!equipmentOnBranch && !terminalOnBranch && !outletOnBranch)) {
          continue;
        }
        auto terminalComponent = airTerminal->optionalCast<HVACComponent>();
        if (!terminalComponent || !terminalComponent->isRemovable()) {
          return false;
        }
        if (enrolledTerminalHandles.insert(airTerminal->handle()).second) {
          branchOwnedTerminals.push_back(BranchOwnedTerminal{*airTerminal, *airDistributionUnit});
        }
      }

      // Dual-duct teardown validates both demand paths and is intentionally
      // failure-aware. Run it before changing zone equipment or ADU ownership
      // so malformed secondary topology leaves the entire zone branch intact.
      for (auto& component : branchPath) {
        const auto componentType = component.iddObject().type();
        const bool isDualDuctTerminal = componentType == openstudio::IddObjectType::AirTerminal_DualDuct_ConstantVolume
                                        || componentType == openstudio::IddObjectType::AirTerminal_DualDuct_VAV
                                        || componentType == openstudio::IddObjectType::AirTerminal_DualDuct_VAV_OutdoorAir;
        if (!isDualDuctTerminal) {
          continue;
        }

        const auto componentHandle = component.handle();
        component.remove();
        if (model().getObject(componentHandle)) {
          return false;
        }
      }

      // The terminal owns its fan, coil, and any child plant topology. Remove
      // it while its zone registration and ADU are still intact so the family
      // teardown can resolve that ownership. This is especially important for
      // a compound terminal-only branch that was claimed by a zone later: the
      // terminal may be identified by its ADU outlet even when conservative
      // branch traversal cannot prove the entire compound path.
      for (auto& owned : branchOwnedTerminals) {
        if (model().getObject(owned.terminal.handle())) {
          owned.terminal.remove();
          if (model().getObject(owned.terminal.handle())) {
            return false;
          }
        }
        if (model().getObject(owned.airDistributionUnit.handle())) {
          // Family teardown normally unregisters itself. Remove by the ADU
          // target as an idempotent cleanup for imported or partial topology.
          (void)equipmentList.removeEquipment(owned.airDistributionUnit.cast<ModelObject>());
          owned.airDistributionUnit.remove();
          if (model().getObject(owned.airDistributionUnit.handle())) {
            return false;
          }
        }
      }

      for (const auto& equipment : equipmentList.equipment()) {
        auto airDistributionUnit = airDistributionUnitForZoneEquipment(equipment);
        if (!airDistributionUnit) {
          continue;
        }

        auto airTerminal = airDistributionUnit->airTerminal();
        auto outletNode = airDistributionUnit->outletNode();
        const bool equipmentOnBranch = branchPathHandles.contains(equipment.handle());
        const bool terminalOnBranch = airTerminal && branchPathHandles.contains(airTerminal->handle());
        const bool outletOnBranch = outletNode && branchZoneInletNodeHandles.contains(outletNode->handle());
        if (!equipmentOnBranch && !terminalOnBranch && !outletOnBranch) {
          continue;
        }

        if (equipmentList.removeEquipment(equipment)) {
          airDistributionUnit->remove();
        }
      }

      for (auto& component : branchPath) {
        if (!model().getObject(component.handle())) {
          continue;
        }
        if (component.iddObject().type() == openstudio::IddObjectType::Node) {
          continue;
        }
        if (component.optionalCast<ThermalZone>()) {
          continue;
        }
        component.remove();
      }

      if (!removeDemandBranchAtIndex(*branchIndex)) {
        return false;
      }

      if (!detachZoneFromDemandNodes(*conn)) {
        return false;
      }

      syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      syncSetpointManagerMixedAirFanNodes();
      return true;
    }

    void AirLoopHVAC_Impl::syncControllerMechanicalVentilationZoneOutdoorAirEntries() {
      auto airLoop = getObject<AirLoopHVAC>();
      std::vector<std::pair<openstudio::epmodel::ThermalZone, openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>> entries;
      for (const auto& zone : airLoop.thermalZones()) {
        auto sizingZone = zone.sizingZone();
        auto dsoaSpaceList = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>()->designSpecificationOutdoorAirSpaceList();
        if (dsoaSpaceList) {
          entries.emplace_back(zone, *dsoaSpaceList);
        }
      }

      auto oaSystem = airLoopHVACOutdoorAirSystem();
      if (!oaSystem) {
        return;
      }

      auto oaController = oaSystem->getControllerOutdoorAir();
      auto cmv = oaController.getImpl<detail::ControllerOutdoorAir_Impl>()->optionalControllerMechanicalVentilation();
      if (!cmv) {
        return;
      }

      // Big picture: CMV extensible groups are not the source of truth. The
      // source of truth is ThermalZone -> Sizing:Zone ->
      // DesignSpecification:OutdoorAir:SpaceList. CMV entries are just the E+
      // runtime projection of that relationship for this air loop.
      auto cmvImpl = cmv->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>();
      OS_ASSERT(cmvImpl);
      cmvImpl->clearZoneOutdoorAirEntries();
      for (const auto& [zone, dsoaSpaceList] : entries) {
        OS_ASSERT(cmvImpl->addZoneOutdoorAirEntry(zone, dsoaSpaceList));
      }
    }

    bool AirLoopHVAC_Impl::isSupportedMixedAirFanType(openstudio::IddObjectType objectType) {
      return objectType == openstudio::IddObjectType::Fan_ConstantVolume || objectType == openstudio::IddObjectType::Fan_VariableVolume
             || objectType == openstudio::IddObjectType::Fan_SystemModel || objectType == openstudio::IddObjectType::Fan_ComponentModel;
    }

    boost::optional<HVACComponent> AirLoopHVAC_Impl::lastSupportedFan(const std::vector<ModelObject>& components) {
      for (auto it = components.rbegin(); it != components.rend(); ++it) {
        if (!isSupportedMixedAirFanType(it->iddObject().type())) {
          continue;
        }
        if (auto fan = it->optionalCast<HVACComponent>()) {
          return *fan;
        }
      }
      return boost::none;
    }

    void AirLoopHVAC_Impl::syncSetpointManagerMixedAirFanNodes() {
      auto supplyPath = supplyComponents(openstudio::IddObjectType::Catchall);

      // Mirror model intent: choose the last supply fan encountered on the
      // supply path (the one closest to supply outlet in path order).
      auto selectedFan = lastSupportedFan(supplyPath);
      if (!selectedFan) {
        return;
      }

      auto fan = selectedFan->optionalCast<StraightComponent>();
      OS_ASSERT(fan);

      auto fanInlet = fan->inletModelObject();
      auto fanOutlet = fan->outletModelObject();
      OS_ASSERT(fanInlet);
      OS_ASSERT(fanOutlet);

      auto fanInletNode = fanInlet->optionalCast<Node>();
      auto fanOutletNode = fanOutlet->optionalCast<Node>();
      OS_ASSERT(fanInletNode);
      OS_ASSERT(fanOutletNode);

      std::set<openstudio::Handle> supplyNodeHandles;
      for (const auto& object : supplyPath) {
        if (auto node = object.optionalCast<Node>()) {
          supplyNodeHandles.insert(node->handle());
        }
      }

      for (auto& mixedAirSPM : model().getConcreteModelObjects<openstudio::epmodel::SetpointManagerMixedAir>()) {
        auto setpointNode = mixedAirSPM.setpointNode();
        if (!setpointNode) {
          continue;
        }
        if (!supplyNodeHandles.contains(setpointNode->handle())) {
          continue;
        }

        auto impl = mixedAirSPM.getImpl<openstudio::epmodel::detail::SetpointManagerMixedAir_Impl>();
        OS_ASSERT(impl);
        OS_ASSERT(impl->setFanInletNode(*fanInletNode));
        OS_ASSERT(impl->setFanOutletNode(*fanOutletNode));
      }
    }

    Node AirLoopHVAC_Impl::supplyInletNode() const {
      auto node = getObject<AirLoopHVAC>().getModelObjectTarget<Node>(AirLoopHVACFields::SupplySideInletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<Node> AirLoopHVAC_Impl::supplyOutletNodes() const {
      auto airLoop = getObject<AirLoopHVAC>();
      auto nodeList = airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::SupplySideOutletNodeNames);
      OS_ASSERT(nodeList);
      const auto nodes = nodeList->nodes();
      OS_ASSERT(!nodes.empty());
      return nodes;
    }

    Node AirLoopHVAC_Impl::supplyOutletNode() const {
      return supplyOutletNodes().front();
    }

    std::vector<Node> AirLoopHVAC_Impl::demandInletNodes() const {
      auto airLoop = getObject<AirLoopHVAC>();
      auto nodeList = airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::DemandSideInletNodeNames);
      OS_ASSERT(nodeList);
      const auto nodes = nodeList->nodes();
      OS_ASSERT(!nodes.empty());
      return nodes;
    }

    Node AirLoopHVAC_Impl::demandInletNode() const {
      return demandInletNodes().front();
    }

    boost::optional<AirLoopHVACZoneSplitter>
      AirLoopHVAC_Impl::zoneSplitterForDemandInletNode(const openstudio::epmodel::Node& demandInletNode) const {
      if (demandInletNode.model() != model()) {
        return boost::none;
      }

      for (const auto& supplyPath : model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
        const auto supplyPathImpl = supplyPath.getImpl<detail::AirLoopHVACSupplyPath_Impl>();
        if (auto inletNode = supplyPathImpl->supplyAirPathInletNode()) {
          if (*inletNode != demandInletNode) {
            continue;
          }
          for (const auto& component : supplyPathImpl->components()) {
            if (auto splitter = component.optionalCast<AirLoopHVACZoneSplitter>()) {
              return splitter;
            }
          }
        }
      }

      return boost::none;
    }

    Node AirLoopHVAC_Impl::demandOutletNode() const {
      auto node = getObject<AirLoopHVAC>().getModelObjectTarget<Node>(AirLoopHVACFields::DemandSideOutletNodeName);
      OS_ASSERT(node);
      return *node;
    }

    BranchList AirLoopHVAC_Impl::branchList() const {
      auto branchList = getObject<AirLoopHVAC>().getModelObjectTarget<BranchList>(AirLoopHVACFields::BranchListName);
      OS_ASSERT(branchList);
      return *branchList;
    }

    boost::optional<Splitter> AirLoopHVAC_Impl::supplySplitter() const {
      const auto branches = branchList().branches();
      if (branches.empty()) {
        return boost::none;
      }
      const auto mainBranchHandle = branches.front().handle();
      for (const auto& splitter : model().getConcreteModelObjects<ConnectorSplitter>()) {
        auto inletBranch = splitter.getImpl<detail::ConnectorSplitter_Impl>()->inletBranch();
        if (inletBranch && inletBranch->handle() == mainBranchHandle) {
          return splitter.cast<Splitter>();
        }
      }
      return boost::none;
    }

    bool AirLoopHVAC_Impl::isDualDuct() const {
      return supplySplitter().has_value() && supplyOutletNodes().size() >= 2u;
    }

    boost::optional<Node> AirLoopHVAC_Impl::supplySplitterInletNode() const {
      if (auto splitter = supplySplitter()) {
        if (auto object = splitter->inletModelObject()) {
          return object->optionalCast<Node>();
        }
      }
      return boost::none;
    }

    std::vector<Node> AirLoopHVAC_Impl::supplySplitterOutletNodes() const {
      std::vector<Node> result;
      if (auto splitter = supplySplitter()) {
        for (const auto& object : splitter->outletModelObjects()) {
          if (auto node = object.optionalCast<Node>()) {
            result.push_back(*node);
          }
        }
      }
      return result;
    }

    bool AirLoopHVAC_Impl::makeDualDuct() {
      if (isDualDuct()) {
        return true;
      }

      auto airLoop = getObject<AirLoopHVAC>();
      auto branches = branchList().branches();
      if (branches.empty()) {
        return false;
      }

      const std::string loopName = airLoop.nameString();
      auto supplyOutletNodeList = airLoop.getModelObjectTarget<NodeList>(AirLoopHVACFields::SupplySideOutletNodeNames);
      if (!supplyOutletNodeList) {
        return false;
      }

      auto outletNodes = supplyOutletNodeList->nodes();
      while (outletNodes.size() < 2u) {
        auto node = model().getOrCreateTransientByName<Node>(loopName + " Supply Outlet Node " + std::to_string(outletNodes.size() + 1u));
        if (!supplyOutletNodeList->getImpl<detail::NodeList_Impl>()->addNode(node)) {
          return false;
        }
        outletNodes = supplyOutletNodeList->nodes();
      }

      ConnectorSplitter splitter(model());
      splitter.setName(loopName + " Supply Splitter");
      if (!splitter.getImpl<detail::ConnectorSplitter_Impl>()->setInletBranch(branches.front())) {
        return false;
      }

      auto connectorList = ModelObject::create(IddObjectType::ConnectorList, model());
      connectorList.setName(loopName + " Supply Connector List");
      airLoop.setPointer(AirLoopHVACFields::ConnectorListName, connectorList.handle());
      auto group = connectorList.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup || !workspaceGroup->setString(ConnectorListExtensibleFields::ConnectorObjectType, splitter.iddObject().name())
          || !workspaceGroup->setPointer(ConnectorListExtensibleFields::ConnectorName, splitter.handle(), false)) {
        return false;
      }

      auto branchListObject = branchList();
      auto branchListImpl = branchListObject.getImpl<detail::BranchList_Impl>();
      OS_ASSERT(branchListImpl);
      for (unsigned i = 0; i < 2u; ++i) {
        Branch branch(model());
        branch.setName(loopName + " Dual Duct Branch " + std::to_string(i + 1u));
        if (!branchListImpl->addBranch(branch) || !splitter.setOutletModelObject(i, branch.cast<ModelObject>())) {
          return false;
        }
      }

      return true;
    }

    boost::optional<Branch> AirLoopHVAC_Impl::branchForSupplyNode(const Node& node) const {
      const auto branches = branchList().branches();
      if (branches.empty()) {
        return boost::none;
      }
      if (!isDualDuct()) {
        return branches.front();
      }

      if (node == supplyInletNode() || (supplySplitterInletNode() && node == *supplySplitterInletNode())) {
        return branches.front();
      }

      const auto outletNodes = supplyOutletNodes();
      for (std::size_t i = 0; i < outletNodes.size() && (i + 1u) < branches.size(); ++i) {
        if (node == outletNodes[i]) {
          return branches[i + 1u];
        }
      }

      for (const auto& branch : branches) {
        for (unsigned i = 0; i < branch.components().size(); ++i) {
          auto inlet = branch.componentInletNode(i);
          auto outlet = branch.componentOutletNode(i);
          if ((inlet && *inlet == node) || (outlet && *outlet == node)) {
            return branch;
          }
        }
      }

      return boost::none;
    }

    AirLoopHVACReturnPath AirLoopHVAC_Impl::airLoopHVACReturnPath() const {
      // ReturnPath is associated to an AirLoopHVAC through the demand-side outlet node name.
      const auto demandOutlet = demandOutletNode();
      boost::optional<AirLoopHVACReturnPath> result;

      // First try to find an existing ReturnPath already keyed to this demand outlet node.
      for (const auto& returnPath : model().getConcreteModelObjects<AirLoopHVACReturnPath>()) {
        if (auto target = returnPath.getTarget(AirLoopHVAC_ReturnPathFields::ReturnAirPathOutletNodeName)) {
          if (*target == demandOutlet) {
            result = returnPath;
            break;
          }
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    AirLoopHVACSupplyPath AirLoopHVAC_Impl::airLoopHVACSupplyPath() const {
      // SupplyPath is associated to an AirLoopHVAC through the demand-side inlet node name.
      const auto demandInlet = demandInletNode();
      boost::optional<AirLoopHVACSupplyPath> result;

      // First try to find an existing SupplyPath already keyed to this demand inlet node.
      for (const auto& supplyPath : model().getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
        if (auto target = supplyPath.getTarget(AirLoopHVAC_SupplyPathFields::SupplyAirPathInletNodeName)) {
          if (*target == demandInlet) {
            result = supplyPath;
            break;
          }
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    AirLoopHVACZoneSplitter AirLoopHVAC_Impl::zoneSplitter() const {
      const auto supplyPath = airLoopHVACSupplyPath();
      boost::optional<AirLoopHVACZoneSplitter> result;
      for (const auto& component : supplyPath.components()) {
        if (auto splitter = component.optionalCast<AirLoopHVACZoneSplitter>()) {
          result = *splitter;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    AirLoopHVACZoneMixer AirLoopHVAC_Impl::zoneMixer() const {
      const auto returnPath = airLoopHVACReturnPath();
      boost::optional<AirLoopHVACZoneMixer> result;
      for (const auto& component : returnPath.components()) {
        if (auto mixer = component.optionalCast<AirLoopHVACZoneMixer>()) {
          result = *mixer;
          break;
        }
      }
      OS_ASSERT(result);
      return *result;
    }

    Node AirLoopHVAC_Impl::demandBranchNode() const {
      // Mirror openstudio::model demand-side topology:
      // Demand Inlet Node -> ZoneSplitter -> Branch Node -> ZoneMixer -> Demand Outlet Node
      // Canonicalization owns the repairs; this accessor expects canonicalized state.
      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();

      boost::optional<Node> branchNode;

      // Prefer splitter first outlet node target if present.
      for (const auto& group : splitter.extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        if (auto target = workspaceGroup->getTarget(AirLoopHVAC_ZoneSplitterExtensibleFields::OutletNodeName)) {
          if (auto node = target->optionalCast<Node>()) {
            branchNode = *node;
            break;
          }
        }
      }

      // Otherwise use mixer first inlet node target if present.
      if (!branchNode) {
        for (const auto& group : mixer.extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          OS_ASSERT(workspaceGroup);
          if (auto target = workspaceGroup->getTarget(AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName)) {
            if (auto node = target->optionalCast<Node>()) {
              branchNode = *node;
              break;
            }
          }
        }
      }

      if (!branchNode) {
        OS_ASSERT(false);
      }

      return *branchNode;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                                openstudio::IddObjectType type) const {
      // Build an adjacency graph from BranchList ordering and explicit node
      // links. This makes supply traversal deterministic and independent from
      // call-site assumptions about specific component classes.
      AdjacencyBuilder builder;

      const auto branches = branchList().branches();
      if (branches.empty()) {
        OS_ASSERT(false);
        return {};
      }

      auto addBranchPath = [&](const ModelObject& startObject, const Branch& branch, const ModelObject& endObject) {
        ModelObject previousObject = startObject;
        const auto components = branch.components();
        for (unsigned index = 0; index < components.size(); ++index) {
          const auto& component = components[index];
          builder.addLink(previousObject, component);
          previousObject = component;

          auto outletNode = branch.componentOutletNode(index);
          if (!outletNode) {
            OS_ASSERT(false);
            continue;
          }
          builder.addLink(previousObject, *outletNode);
          previousObject = *outletNode;
        }

        if (previousObject != endObject) {
          builder.addLink(previousObject, endObject);
        }
      };

      if (auto splitter = supplySplitter()) {
        addBranchPath(supplyInletNode(), branches.front(), *splitter);
        const auto outletNodes = supplyOutletNodes();
        for (std::size_t i = 0; i < outletNodes.size() && (i + 1u) < branches.size(); ++i) {
          addBranchPath(*splitter, branches[i + 1u], outletNodes[i]);
        }
      } else {
        addBranchPath(supplyInletNode(), branches.front(), supplyOutletNode());
      }

      // Traverse once through the canonical adjacency graph instead of
      // re-deriving branch relationships per query call.
      auto pathObjects = builder.walkPath(model(), inletComp, outletComp);

      // Type filtering is a pure view operation over the resolved path.
      if (type == openstudio::IddObjectType::Catchall) {
        return pathObjects;
      }

      std::vector<ModelObject> filtered;
      for (const auto& obj : pathObjects) {
        if (obj.iddObject().type() == type) {
          filtered.push_back(obj);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::supplyComponents(openstudio::IddObjectType type) const {
      std::vector<ModelObject> result;
      std::set<openstudio::Handle> seen;
      for (const auto& outletNode : supplyOutletNodes()) {
        for (const auto& object : supplyComponents(supplyInletNode(), outletNode, type)) {
          if (seen.insert(object.handle()).second) {
            result.push_back(object);
          }
        }
      }
      return result;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                                openstudio::IddObjectType type) const {
      const auto demandInlet = demandInletNode();
      const auto demandOutlet = demandOutletNode();
      const auto zoneSplitter = this->zoneSplitter();
      const auto zoneMixer = this->zoneMixer();

      auto buildDemandBranchLeg = [&](const ModelObject& splitterOutletObject, const ModelObject& branchReturnObject) {
        // Construct one demand leg at a time from splitter outlet to mixer
        // inlet, explicitly stitching terminal/zone objects where they can be
        // resolved. This keeps leg construction local and debuggable.
        std::vector<ModelObject> chain;
        chain.reserve(5);
        std::set<openstudio::Handle> seenInChain;

        auto appendDistinct = [&](const ModelObject& obj) {
          if (seenInChain.insert(obj.handle()).second) {
            chain.push_back(obj);
          }
        };

        auto appendZoneAirTerminals = [&](const ThermalZone& zone) {
          const auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentList();
          if (!equipmentList) {
            return;
          }

          for (const auto& equipment : equipmentList->equipment()) {
            if (equipment.optionalCast<StraightComponent>()) {
              appendDistinct(equipment);
              continue;
            }

            if (auto zoneHVAC = equipment.optionalCast<ZoneHVACComponent>()) {
              auto inletNode = zoneHVAC->inletNode();
              if (inletNode && (std::ranges::find(chain, inletNode->cast<ModelObject>()) != chain.end())) {
                appendDistinct(equipment);
              }
              continue;
            }
          }
        };

        appendDistinct(splitterOutletObject);

        // Resolve branch-local straight components through the same traversal
        // path used by removeBranchForZone. resolveDemandBranchChain returns
        // downstream-to-upstream, so append in reverse to keep loop order.
        bool zoneAdded = false;
        boost::optional<ModelObject> terminal;
        auto splitterOutletNode = splitterOutletObject.optionalCast<Node>();
        auto mixerInletNode = branchReturnObject.optionalCast<Node>();
        if (splitterOutletNode && mixerInletNode) {
          if (auto branchStraightComponents = resolveDemandBranchChain(*splitterOutletNode, *mixerInletNode)) {
            for (auto it = branchStraightComponents->rbegin(); it != branchStraightComponents->rend(); ++it) {
              appendDistinct(it->cast<ModelObject>());
            }
            if (!branchStraightComponents->empty()) {
              terminal = branchStraightComponents->front().cast<ModelObject>();
            }
          } else {
            terminal = resolveTerminalOnDemandBranchNodes(*splitterOutletNode, *mixerInletNode);
            if (terminal) {
              appendDistinct(*terminal);
            }
          }
        }
        if (terminal) {
          if (auto terminalOutlet = resolveTerminalOutletObject(*terminal)) {
            appendDistinct(*terminalOutlet);

            if (auto terminalOutletNode = terminalOutlet->optionalCast<Node>()) {
              if (auto zone = resolveZoneServedByInletNode(*terminalOutletNode)) {
                appendDistinct(zone.get().cast<ModelObject>());
                appendZoneAirTerminals(*zone);
                zoneAdded = true;
              }
            }
          }
        }

        // Fallback for incomplete terminal linkage: still anchor zone via
        // mixer-side node so demand graph remains connected.
        if (!zoneAdded) {
          if (auto branchReturnNode = branchReturnObject.optionalCast<Node>()) {
            if (auto zone = resolveZoneServedByReturnNode(*branchReturnNode)) {
              appendDistinct(zone.get().cast<ModelObject>());
              appendZoneAirTerminals(*zone);
            }
          }
        }

        // The plenum inlet or direct mixer inlet is the branch-local endpoint.
        // Shared downstream objects are appended after every branch.
        appendDistinct(branchReturnObject);

        return chain;
      };

      std::vector<ModelObject> pathObjects;
      pathObjects.reserve(64);
      pathObjects.emplace_back(demandInlet);
      pathObjects.emplace_back(zoneSplitter);

      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto mixerInlets = zoneMixer.inletModelObjects();

      struct DemandSupplyEndpoint
      {
        ModelObject splitterOutlet;
        ModelObject branchStart;
        boost::optional<AirLoopHVACSupplyPlenum> supplyPlenum;
      };
      std::vector<DemandSupplyEndpoint> supplyEndpoints;
      for (const auto& splitterOutlet : splitterOutlets) {
        boost::optional<AirLoopHVACSupplyPlenum> attachedPlenum;
        for (const auto& candidate : model().getConcreteModelObjects<AirLoopHVACSupplyPlenum>()) {
          const auto inlet = candidate.inletModelObject();
          if (inlet && (*inlet == splitterOutlet)) {
            attachedPlenum = candidate;
            break;
          }
        }
        if (attachedPlenum) {
          for (const auto& plenumOutlet : attachedPlenum->outletModelObjects()) {
            supplyEndpoints.push_back(DemandSupplyEndpoint{splitterOutlet, plenumOutlet, attachedPlenum});
          }
        } else {
          supplyEndpoints.push_back(DemandSupplyEndpoint{splitterOutlet, splitterOutlet, boost::none});
        }
      }

      std::set<Handle> bypassReturnHandles;
      for (const auto& unitary : model().getConcreteModelObjects<AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass>()) {
        if (const auto bypassReturnNode = unitary.getModelObjectTarget<Node>(unitary.plenumorMixerAirPort())) {
          bypassReturnHandles.insert(bypassReturnNode->handle());
        }
      }

      struct DemandReturnEndpoint
      {
        ModelObject mixerInlet;
        ModelObject branchReturn;
        boost::optional<AirLoopHVACReturnPlenum> returnPlenum;
      };
      std::vector<DemandReturnEndpoint> returnEndpoints;
      for (const auto& mixerInlet : mixerInlets) {
        if (bypassReturnHandles.contains(mixerInlet.handle())) {
          continue;
        }

        boost::optional<AirLoopHVACReturnPlenum> attachedPlenum;
        for (const auto& candidate : model().getConcreteModelObjects<AirLoopHVACReturnPlenum>()) {
          const auto outlet = candidate.outletModelObject();
          if (outlet && (*outlet == mixerInlet)) {
            attachedPlenum = candidate;
            break;
          }
        }

        if (attachedPlenum) {
          for (const auto& plenumInlet : attachedPlenum->inletModelObjects()) {
            if (bypassReturnHandles.contains(plenumInlet.handle())) {
              continue;
            }
            auto inletNode = plenumInlet.optionalCast<Node>();
            if (inletNode && resolveZoneServedByReturnNode(*inletNode)) {
              returnEndpoints.push_back(DemandReturnEndpoint{mixerInlet, plenumInlet, attachedPlenum});
            }
          }
        } else {
          returnEndpoints.push_back(DemandReturnEndpoint{mixerInlet, mixerInlet, boost::none});
        }
      }

      std::vector<boost::optional<DemandReturnEndpoint>> endpointByBranch(supplyEndpoints.size());
      std::vector<bool> endpointUsed(returnEndpoints.size(), false);
      for (unsigned endpointIndex = 0u; endpointIndex < returnEndpoints.size(); ++endpointIndex) {
        const auto returnNode = returnEndpoints[endpointIndex].branchReturn.optionalCast<Node>();
        const auto zone = returnNode ? resolveZoneServedByReturnNode(*returnNode) : boost::none;
        if (!zone) {
          continue;
        }
        const auto connections = zone->getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
        if (!connections) {
          continue;
        }
        for (const auto& zoneInletNode : connections->zoneAirInletNodes()) {
          for (unsigned supplyIndex = 0u; supplyIndex < supplyEndpoints.size(); ++supplyIndex) {
            if (endpointByBranch[supplyIndex]) {
              continue;
            }
            const auto branchStartNode = supplyEndpoints[supplyIndex].branchStart.optionalCast<Node>();
            if (!branchStartNode) {
              continue;
            }
            if ((*branchStartNode == zoneInletNode) || resolveDemandBranchChain(*branchStartNode, zoneInletNode)) {
              endpointByBranch[supplyIndex] = returnEndpoints[endpointIndex];
              endpointUsed[endpointIndex] = true;
              break;
            }
          }
          if (endpointUsed[endpointIndex]) {
            break;
          }
        }
      }

      unsigned nextUnusedEndpoint = 0u;
      for (unsigned branchIndex = 0u; branchIndex < endpointByBranch.size(); ++branchIndex) {
        if (!endpointByBranch[branchIndex]) {
          while ((nextUnusedEndpoint < endpointUsed.size()) && endpointUsed[nextUnusedEndpoint]) {
            ++nextUnusedEndpoint;
          }
          if (nextUnusedEndpoint < returnEndpoints.size()) {
            endpointByBranch[branchIndex] = returnEndpoints[nextUnusedEndpoint];
            endpointUsed[nextUnusedEndpoint] = true;
          }
        }
        if (!endpointByBranch[branchIndex]) {
          continue;
        }

        const auto& endpoint = *endpointByBranch[branchIndex];
        const auto& supplyEndpoint = supplyEndpoints[branchIndex];
        if (supplyEndpoint.supplyPlenum) {
          if (std::ranges::find(pathObjects, supplyEndpoint.splitterOutlet) == pathObjects.end()) {
            pathObjects.push_back(supplyEndpoint.splitterOutlet);
          }
          if (std::ranges::find(pathObjects, supplyEndpoint.supplyPlenum->cast<ModelObject>()) == pathObjects.end()) {
            pathObjects.push_back(supplyEndpoint.supplyPlenum->cast<ModelObject>());
          }
        }
        auto chain = buildDemandBranchLeg(supplyEndpoint.branchStart, endpoint.branchReturn);
        for (const auto& object : chain) {
          if (std::ranges::find(pathObjects, object) == pathObjects.end()) {
            pathObjects.push_back(object);
          }
        }
      }

      // A linear API view cannot represent the converging demand graph
      // directly. Put shared plenums and their mixer inlet nodes after all
      // branch-local objects so every served zone precedes its return plenum.
      for (const auto& endpoint : returnEndpoints) {
        if (endpoint.returnPlenum && (std::ranges::find(pathObjects, endpoint.returnPlenum->cast<ModelObject>()) == pathObjects.end())) {
          pathObjects.push_back(endpoint.returnPlenum->cast<ModelObject>());
        }
        if (std::ranges::find(pathObjects, endpoint.mixerInlet) == pathObjects.end()) {
          pathObjects.push_back(endpoint.mixerInlet);
        }
      }

      pathObjects.emplace_back(zoneMixer);
      pathObjects.emplace_back(demandOutlet);

      auto inletIt = std::find(pathObjects.begin(), pathObjects.end(), inletComp);
      if (inletIt == pathObjects.end()) {
        return {};
      }

      auto outletIt = std::find(inletIt, pathObjects.end(), outletComp);
      if (outletIt == pathObjects.end()) {
        return {};
      }

      std::vector<ModelObject> subPath(inletIt, std::next(outletIt));
      if (type == openstudio::IddObjectType::Catchall) {
        return subPath;
      }

      std::vector<ModelObject> filtered;
      filtered.reserve(subPath.size());
      for (const auto& obj : subPath) {
        if (obj.iddObject().type() == type) {
          filtered.push_back(obj);
        }
      }
      return filtered;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::demandComponents(openstudio::IddObjectType type) const {
      return demandComponents(demandInletNode(), demandOutletNode(), type);
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::oaComponents(openstudio::IddObjectType type) const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        return oaSystem->components(type);
      }
      return {};
    }

    boost::optional<Node> AirLoopHVAC_Impl::outdoorAirNode() const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        return oaSystem->outboardOANode();
      }
      return boost::none;
    }

    boost::optional<Node> AirLoopHVAC_Impl::reliefAirNode() const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        return oaSystem->outboardReliefNode();
      }
      return boost::none;
    }

    boost::optional<Node> AirLoopHVAC_Impl::mixedAirNode() const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        if (auto modelObject = oaSystem->mixedAirModelObject()) {
          return modelObject->optionalCast<Node>();
        }
      }
      return boost::none;
    }

    boost::optional<Node> AirLoopHVAC_Impl::returnAirNode() const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        if (auto modelObject = oaSystem->returnAirModelObject()) {
          return modelObject->optionalCast<Node>();
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> AirLoopHVAC_Impl::airLoopHVACOutdoorAirSystem() const {
      auto oaSystems =
        subsetCastVector<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>(supplyComponents(openstudio::IddObjectType::AirLoopHVAC_OutdoorAirSystem));
      if (oaSystems.empty()) {
        return boost::none;
      }
      OS_ASSERT(oaSystems.size() == 1u);
      return oaSystems.front();
    }

    boost::optional<HVACComponent> AirLoopHVAC_Impl::supplyFan() const {
      boost::optional<HVACComponent> start = supplyInletNode();
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        start = *oaSystem;
      }
      OS_ASSERT(start);
      return lastSupportedFan(supplyComponents(*start, supplyOutletNode(), openstudio::IddObjectType::Catchall));
    }

    boost::optional<HVACComponent> AirLoopHVAC_Impl::returnFan() const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        return lastSupportedFan(supplyComponents(supplyInletNode(), *oaSystem, openstudio::IddObjectType::Catchall));
      }
      return boost::none;
    }

    boost::optional<HVACComponent> AirLoopHVAC_Impl::reliefFan() const {
      if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
        return lastSupportedFan(oaSystem->reliefComponents());
      }
      return boost::none;
    }

    SizingSystem AirLoopHVAC_Impl::sizingSystem() const {
      const auto airLoop = getObject<AirLoopHVAC>();
      for (const auto& sizingSystem : model().getConcreteModelObjects<SizingSystem>()) {
        auto linkedAirLoop = sizingSystem.getModelObjectTarget<AirLoopHVAC>(openstudio::Sizing_SystemFields::AirLoopName);
        if (linkedAirLoop && *linkedAirLoop == airLoop) {
          return sizingSystem;
        }
      }
      OS_ASSERT(false);
      return SizingSystem(model(), airLoop);
    }

    openstudio::epmodel::Schedule AirLoopHVAC_Impl::availabilitySchedule() const {
      auto scheduledOn = availabilityScheduleManager();
      OS_ASSERT(scheduledOn);
      return scheduledOn->schedule();
    }

    bool AirLoopHVAC_Impl::setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return ensureAvailabilityScheduleManager().setSchedule(schedule);
    }

    std::vector<openstudio::epmodel::ThermalZone> AirLoopHVAC_Impl::thermalZones() const {
      auto zones = subsetCastVector<openstudio::epmodel::ThermalZone>(demandComponents(openstudio::IddObjectType::Zone));
      return zones;
    }

    std::vector<IdfObject> AirLoopHVAC_Impl::remove() {
      std::vector<IdfObject> result;
      const auto thisLoop = getObject<AirLoopHVAC>();
      const auto thisLoopName = thisLoop.nameString();

      const auto appendRemoved = [&result](std::vector<IdfObject>&& removed) { result.insert(result.end(), removed.begin(), removed.end()); };

      std::vector<SetpointManager> loopSetpointManagers;
      for (const auto& component : components(openstudio::IddObjectType::Node)) {
        auto node = component.optionalCast<Node>();
        if (!node) {
          continue;
        }
        for (const auto& setpointManager : node->setpointManagers()) {
          if (std::ranges::none_of(loopSetpointManagers,
                                   [&setpointManager](const auto& existing) { return existing.handle() == setpointManager.handle(); })) {
            loopSetpointManagers.push_back(setpointManager);
          }
        }
      }

      for (auto& setpointManager : loopSetpointManagers) {
        appendRemoved(setpointManager.remove());
      }

      const auto supplyObjects = supplyComponents(openstudio::IddObjectType::Catchall);
      for (const auto& object : supplyObjects) {
        auto waterToAir = object.optionalCast<WaterToAirComponent>();
        if (!waterToAir) {
          continue;
        }

        waterToAir->removeFromAirLoopHVAC();
        if (!waterToAir->plantLoop()) {
          appendRemoved(waterToAir->remove());
        }
      }

      const auto zones = thermalZones();
      for (auto zone : zones) {
        removeBranchForZone(zone);
      }

      for (auto& sizingSystem : model().getConcreteModelObjects<SizingSystem>()) {
        bool matches = false;
        if (auto target = sizingSystem.getModelObjectTarget<AirLoopHVAC>(openstudio::Sizing_SystemFields::AirLoopName)) {
          matches = (*target == thisLoop);
        } else if (auto airLoopName = sizingSystem.getString(openstudio::Sizing_SystemFields::AirLoopName, true)) {
          matches = !airLoopName->empty() && openstudio::istringEqual(*airLoopName, thisLoopName);
        }

        if (matches) {
          appendRemoved(sizingSystem.remove());
        }
      }

      if (auto assignmentList =
            thisLoop.getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::AirLoopHVACFields::AvailabilityManagerListName)) {
        appendRemoved(assignmentList->remove());
      }

      std::vector<ModelObject> removalObjects;
      const auto addRemovalObject = [&removalObjects](const ModelObject& object) {
        if (std::ranges::none_of(removalObjects, [&object](const auto& existing) { return existing.handle() == object.handle(); })) {
          removalObjects.push_back(object);
        }
      };

      const std::function<void(const ModelObject&)> collectRemovalObject = [&](const ModelObject& object) {
        addRemovalObject(object);

        if (auto oaSystem = object.optionalCast<AirLoopHVACOutdoorAirSystem>()) {
          if (auto controllerList =
                oaSystem->getModelObjectTarget<AirLoopHVACControllerList>(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName)) {
            for (const auto& controller : controllerList->controllers()) {
              collectRemovalObject(controller);
            }
            collectRemovalObject(controllerList->cast<ModelObject>());
          }

          if (auto equipmentList = oaSystem->getModelObjectTarget<AirLoopHVACOutdoorAirSystemEquipmentList>(
                openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName)) {
            for (const auto& equipment : equipmentList->equipment()) {
              collectRemovalObject(equipment);
            }
            collectRemovalObject(equipmentList->cast<ModelObject>());
          }
        }

        if (auto controllerList = object.optionalCast<AirLoopHVACControllerList>()) {
          for (const auto& controller : controllerList->controllers()) {
            collectRemovalObject(controller);
          }
        }

        if (auto equipmentList = object.optionalCast<AirLoopHVACOutdoorAirSystemEquipmentList>()) {
          for (const auto& equipment : equipmentList->equipment()) {
            collectRemovalObject(equipment);
          }
        }

        if (auto coilSystem = object.optionalCast<CoilSystemCoolingDX>()) {
          if (auto coolingCoil = coilSystem->getImpl<detail::CoilSystemCoolingDX_Impl>()->coolingCoil()) {
            collectRemovalObject(*coolingCoil);
          }
        }
      };

      if (auto supplyPath = boost::optional<AirLoopHVACSupplyPath>(airLoopHVACSupplyPath())) {
        for (const auto& component : supplyPath->components()) {
          collectRemovalObject(component);
        }
        collectRemovalObject(supplyPath->cast<ModelObject>());
      }

      if (auto returnPath = boost::optional<AirLoopHVACReturnPath>(airLoopHVACReturnPath())) {
        for (const auto& component : returnPath->components()) {
          collectRemovalObject(component);
        }
        collectRemovalObject(returnPath->cast<ModelObject>());
      }

      if (auto branchListTarget = thisLoop.getModelObjectTarget<BranchList>(openstudio::AirLoopHVACFields::BranchListName)) {
        for (const auto& branch : branchListTarget->branches()) {
          collectRemovalObject(branch.cast<ModelObject>());
        }
        collectRemovalObject(branchListTarget->cast<ModelObject>());
      }

      if (auto supplyOutletNodeList = thisLoop.getModelObjectTarget<NodeList>(openstudio::AirLoopHVACFields::SupplySideOutletNodeNames)) {
        collectRemovalObject(supplyOutletNodeList->cast<ModelObject>());
      }
      if (auto demandInletNodeList = thisLoop.getModelObjectTarget<NodeList>(openstudio::AirLoopHVACFields::DemandSideInletNodeNames)) {
        collectRemovalObject(demandInletNodeList->cast<ModelObject>());
      }
      if (auto connectorList = thisLoop.getModelObjectTarget<ModelObject>(openstudio::AirLoopHVACFields::ConnectorListName)) {
        collectRemovalObject(*connectorList);
      }
      if (auto controllerList = thisLoop.getModelObjectTarget<ModelObject>(openstudio::AirLoopHVACFields::ControllerListName)) {
        collectRemovalObject(*controllerList);
      }

      const auto remainingComponents = components(openstudio::IddObjectType::Catchall);
      for (const auto& object : remainingComponents) {
        collectRemovalObject(object);
      }

      std::set<Handle> loopRemovalHandles;
      for (const auto& object : removalObjects) {
        loopRemovalHandles.insert(object.handle());
      }

      for (const auto& conn : model().getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        auto equipmentList = conn.zoneHVACEquipmentList();
        for (const auto& equipment : equipmentList.equipment()) {
          auto airDistributionUnit = airDistributionUnitForZoneEquipment(equipment);
          if (!airDistributionUnit) {
            continue;
          }

          auto airTerminal = airDistributionUnit->airTerminal();
          auto outletNode = airDistributionUnit->outletNode();
          const bool equipmentOnRemovedLoop = loopRemovalHandles.contains(equipment.handle());
          const bool terminalOnRemovedLoop = airTerminal && loopRemovalHandles.contains(airTerminal->handle());
          const bool outletOnRemovedLoop = outletNode && loopRemovalHandles.contains(outletNode->handle());
          if (!equipmentOnRemovedLoop && !terminalOnRemovedLoop && !outletOnRemovedLoop) {
            continue;
          }

          if (outletNode) {
            auto connectionsImpl = conn.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
            OS_ASSERT(connectionsImpl);
            connectionsImpl->removeZoneAirInletNode(*outletNode);
          }
          if (equipmentList.removeEquipment(equipment)) {
            collectRemovalObject(airDistributionUnit->cast<ModelObject>());
          }
        }
      }

      appendRemoved(Loop_Impl::remove());

      std::set<Handle> removedHandles;
      const auto removeModelObject = [&removedHandles, &appendRemoved](ModelObject& object) {
        if (object.handle().isNull() || removedHandles.contains(object.handle())) {
          return;
        }
        removedHandles.insert(object.handle());
        appendRemoved(object.remove());
      };

      for (auto object : removalObjects) {
        if (object.optionalCast<ThermalZone>()) {
          continue;
        }
        removeModelObject(object);
      }

      return result;
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(sizingSystem());
      return result;
    }

    bool AirLoopHVAC_Impl::setNightCycleControlType(const std::string& controlType) {
      for (auto& availabilityManager : availabilityManagers()) {
        if (auto nightCycle = availabilityManager.optionalCast<AvailabilityManagerNightCycle>()) {
          return nightCycle->setControlType(controlType);
        }
      }

      AvailabilityManagerNightCycle nightCycle(model());
      if (!nightCycle.setControlType(controlType)) {
        nightCycle.remove();
        return false;
      }

      return addAvailabilityManager(nightCycle);
    }

    std::string AirLoopHVAC_Impl::nightCycleControlType() const {
      for (auto& availabilityManager : availabilityManagers()) {
        if (auto nightCycle = availabilityManager.optionalCast<AvailabilityManagerNightCycle>()) {
          return nightCycle->controlType();
        }
      }
      return "StayOff";
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
