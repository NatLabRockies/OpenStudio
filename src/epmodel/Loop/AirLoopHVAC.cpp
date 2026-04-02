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
#include "AirLoopHVACReturnPath.hpp"
#include "AirLoopHVACReturnPath_Impl.hpp"
#include "ModelObject/AirLoopHVACSupplyPath.hpp"
#include "ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "ModelObject/ControllerMechanicalVentilation.hpp"
#include "ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "ModelObject/NodeList.hpp"
#include "ModelObject/NodeList_Impl.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
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
#include "Schedule/Schedule.hpp"

#include <algorithm>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ReturnPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_SupplyPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/Sizing_System_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/core/Logger.hpp>
#include <utilities/core/Assert.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>
#include <set>
#include <vector>

namespace openstudio {
namespace epmodel {

  AirLoopHVAC::AirLoopHVAC(const Model& model) : Loop(openstudio::IddObjectType::AirLoopHVAC, model) {
    auto impl = getImpl<detail::AirLoopHVAC_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
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

    boost::optional<ZoneHVACEquipmentConnections> AirLoopHVAC_Impl::resolveZoneConnections(const ThermalZone& zone) {
      for (const auto& conn : zone.model().getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        if (auto linkedZone = conn.thermalZone()) {
          if (*linkedZone == zone) {
            return conn;
          }
        }
      }
      return boost::none;
    }

    bool AirLoopHVAC_Impl::resolveZoneSplitterBranchNode(AirLoopHVACZoneSplitter& splitter, unsigned branchIndex, const Node& branchNode) {
      auto groups = splitter.extensibleGroups();
      IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : splitter.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ZoneSplitterExtensibleFields::OutletNodeName, branchNode.handle(), false);
    }

    bool AirLoopHVAC_Impl::resolveZoneMixerBranchNode(AirLoopHVACZoneMixer& mixer, unsigned branchIndex, const Node& branchNode) {
      auto groups = mixer.extensibleGroups();
      IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : mixer.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName, branchNode.handle(), false);
    }

    bool AirLoopHVAC_Impl::reserveDemandBranchSlot(AirLoopHVACZoneSplitter& splitter, AirLoopHVACZoneMixer& mixer, unsigned& targetBranchIndex,
                                                   boost::optional<Node>& branchNode, bool& createdNewBranch) {
      const auto splitterOutlets = splitter.outletModelObjects();
      const auto mixerInlets = mixer.inletModelObjects();

      // The default single-branch loop starts with splitter and mixer sharing
      // one branch node. Reusing that shared node preserves the canonical
      // "empty demand branch" baseline until a real second branch is needed.
      if (splitterOutlets.size() == 1u && mixerInlets.size() == 1u && splitterOutlets.front() == mixerInlets.front()) {
        targetBranchIndex = 0u;
        auto existingBranchNode = splitterOutlets.front().optionalCast<Node>();
        if (!existingBranchNode) {
          return false;
        }
        branchNode = *existingBranchNode;
        createdNewBranch = false;
        return true;
      }

      targetBranchIndex = splitter.nextBranchIndex();
      const auto branchNodeName = getObject<AirLoopHVAC>().nameString() + " Demand Branch Node " + std::to_string(targetBranchIndex + 1u);
      branchNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(branchNodeName);
      createdNewBranch = true;
      // Splitter and mixer rows must be created as a pair. If the second write
      // fails, undo the first immediately so the loop never exposes a
      // half-created demand branch.
      if (!resolveZoneSplitterBranchNode(splitter, targetBranchIndex, *branchNode)) {
        return false;
      }
      if (!resolveZoneMixerBranchNode(mixer, targetBranchIndex, *branchNode)) {
        splitter.removePortForBranch(targetBranchIndex);
        return false;
      }
      return true;
    }

    void AirLoopHVAC_Impl::rollbackReservedDemandBranchSlot(AirLoopHVACZoneSplitter& splitter, AirLoopHVACZoneMixer& mixer, unsigned targetBranchIndex,
                                                            bool createdNewBranch) {
      if (!createdNewBranch) {
        return;
      }
      splitter.removePortForBranch(targetBranchIndex);
      mixer.removePortForBranch(targetBranchIndex);
    }

    boost::optional<ThermalZone> AirLoopHVAC_Impl::resolveZoneServedByInletNode(const Node& zoneInletNode) {
      const auto& m = zoneInletNode.model();
      std::vector<ThermalZone> zones;

      const auto inletNameMatches = [&](const ZoneHVACEquipmentConnections& conn) -> bool {
        if (auto directInlet = conn.zoneAirInletNode()) {
          return (*directInlet == zoneInletNode);
        }

        const auto inletNodeOrListName = conn.getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
        if (!inletNodeOrListName || inletNodeOrListName->empty()) {
          return false;
        }

        if (openstudio::istringEqual(*inletNodeOrListName, zoneInletNode.nameString())) {
          return true;
        }

        if (auto nodeList = m.getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *inletNodeOrListName)) {
          for (const auto& group : nodeList->extensibleGroups()) {
            const auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
            if (listedNodeName && openstudio::istringEqual(*listedNodeName, zoneInletNode.nameString())) {
              return true;
            }
          }
        }

        return false;
      };

      for (const auto& conn : m.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        if (!inletNameMatches(conn)) {
          continue;
        }
        if (auto zone = conn.thermalZone()) {
          zones.push_back(*zone);
        }
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

    boost::optional<ThermalZone> AirLoopHVAC_Impl::resolveZoneServedByReturnNode(const Node& zoneReturnNode) {
      const auto& m = zoneReturnNode.model();
      std::vector<ThermalZone> zones;

      const auto outletNameMatches = [&](const ZoneHVACEquipmentConnections& conn) -> bool {
        if (auto directOutlet = conn.zoneReturnAirNode()) {
          return (*directOutlet == zoneReturnNode);
        }

        const auto outletNodeOrListName = conn.getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName);
        if (!outletNodeOrListName || outletNodeOrListName->empty()) {
          return false;
        }

        if (openstudio::istringEqual(*outletNodeOrListName, zoneReturnNode.nameString())) {
          return true;
        }

        if (auto nodeList = m.getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *outletNodeOrListName)) {
          for (const auto& group : nodeList->extensibleGroups()) {
            const auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
            if (listedNodeName && openstudio::istringEqual(*listedNodeName, zoneReturnNode.nameString())) {
              return true;
            }
          }
        }

        return false;
      };

      for (const auto& conn : m.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        if (!outletNameMatches(conn)) {
          continue;
        }
        if (auto zone = conn.thermalZone()) {
          zones.push_back(*zone);
        }
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

    boost::optional<ModelObject> AirLoopHVAC_Impl::resolveTerminalOutletObject(const ModelObject& terminalObject) {
      auto component = terminalObject.optionalCast<StraightComponent>();
      if (!component) {
        return boost::none;
      }
      return component->outletModelObject();
    }

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

    boost::optional<ModelObject> AirLoopHVAC_Impl::resolveTerminalOnDemandBranchNodes(const Node& splitterOutletNode, const Node& mixerInletNode) {
      if (auto branchComponents = resolveDemandBranchChain(splitterOutletNode, mixerInletNode)) {
        if (!branchComponents->empty()) {
          return branchComponents->back().cast<ModelObject>();
        }
      }

      for (const auto& sourceObject : splitterOutletNode.sources()) {
        if (sourceObject.optionalCast<StraightComponent>()) {
          continue;
        }
        const auto objectType = sourceObject.iddObject().type();
        if (objectType == openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter || objectType == openstudio::IddObjectType::AirLoopHVAC_ZoneMixer
            || objectType == openstudio::IddObjectType::Node) {
          continue;
        }
        LOG_FREE(Debug, "openstudio.epmodel.AirLoopHVAC",
                 "Non-StraightComponent object '" << sourceObject.nameString() << "' is not yet supported by resolveTerminalOnDemandBranchNodes.");
        break;
      }

      return boost::none;
    }

    void AirLoopHVAC_Impl::doCanonicalize(LoadContext& context) {
      auto airLoop = getObject<AirLoopHVAC>();
      OS_ASSERT(!airLoop.nameString().empty());
      const auto loopName = airLoop.nameString();

      // These keyed companions are the loop-level connective tissue later
      // queried through demand inlet/outlet association. Canonicalization keeps
      // a single canonical object for each key so const APIs never have to
      // guess which duplicate "really" belongs to the loop.
      auto removeDuplicateModelObject = [&](ModelObject duplicate, const std::string& roleDescription) {
        if (duplicate.remove().empty()) {
          detail::addLoadWarning(context, "Failed to remove duplicate " + roleDescription + " '" + duplicate.nameString() + "' for AirLoopHVAC '" + loopName
                                            + "'.");
        } else {
          detail::addLoadWarning(context, "Removed duplicate " + roleDescription + " '" + duplicate.nameString() + "' for AirLoopHVAC '" + loopName
                                            + "'.");
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

      {  // Ensure there is at least one Node between the zone splitter and mixer
        auto zs = zoneSplitter();
        auto zm = zoneMixer();

        if (zs.outletModelObjects().size() != zm.inletModelObjects().size()) {
          const auto splitterBranches = zs.outletModelObjects().size();
          const auto mixerBranches = zm.inletModelObjects().size();
          while (!zs.outletModelObjects().empty()) {
            zs.removePortForBranch(static_cast<unsigned>(zs.outletModelObjects().size() - 1u));
          }
          while (!zm.inletModelObjects().empty()) {
            zm.removePortForBranch(static_cast<unsigned>(zm.inletModelObjects().size() - 1u));
          }
          detail::addLoadWarning(context, "ZoneSplitter/ZoneMixer branch count mismatch for AirLoopHVAC '" + loopName
                                            + "' (splitter=" + std::to_string(splitterBranches) + ", mixer=" + std::to_string(mixerBranches)
                                            + "). Cleared branch node ports to rebuild.");
        }

        if (zs.outletModelObjects().empty()) {
          Node branchNode(model());
          branchNode.setName(loopName + " Demand Branch Node");
          zs.setOutletModelObject(0u, branchNode);
          zm.setInletModelObject(0u, branchNode);
          detail::addLoadInfo(context, "Created demand branch node '" + branchNode.nameString()
                                         + "' between ZoneSplitter and ZoneMixer for AirLoopHVAC '" + loopName + "'.");
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
      if (hvacComponent.model() != model()) {
        return false;
      }

      if (hvacComponent.airLoopHVAC()) {
        return false;
      }

      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      unsigned targetBranchIndex = 0u;
      boost::optional<Node> branchNode;
      bool createdNewBranch = false;
      if (!reserveDemandBranchSlot(splitter, mixer, targetBranchIndex, branchNode, createdNewBranch)) {
        return false;
      }

      if (!branchNode || !hvacComponent.addToNode(*branchNode)) {
        rollbackReservedDemandBranchSlot(splitter, mixer, targetBranchIndex, createdNewBranch);
        return false;
      }

      syncSetpointManagerMixedAirFanNodes();
      return true;
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      const auto zones = thermalZones();
      if (std::find(zones.begin(), zones.end(), thermalZone) != zones.end()) {
        return false;
      }

      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      unsigned targetBranchIndex = 0u;
      boost::optional<Node> branchNode;
      bool createdNewBranch = false;
      if (!reserveDemandBranchSlot(splitter, mixer, targetBranchIndex, branchNode, createdNewBranch)) {
        return false;
      }
      if (!branchNode || !thermalZone.addToNode(*branchNode)) {
        rollbackReservedDemandBranchSlot(splitter, mixer, targetBranchIndex, createdNewBranch);
        return false;
      }
      syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      return true;
    }

    bool AirLoopHVAC_Impl::addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, openstudio::epmodel::HVACComponent& airTerminal) {
      if (thermalZone.model() != model() || airTerminal.model() != model()) {
        return false;
      }

      const auto zones = thermalZones();
      if (std::find(zones.begin(), zones.end(), thermalZone) != zones.end()) {
        return false;
      }

      if (airTerminal.airLoopHVAC()) {
        return false;
      }

      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      unsigned targetBranchIndex = 0u;
      boost::optional<Node> branchNode;
      bool createdNewBranch = false;
      if (!reserveDemandBranchSlot(splitter, mixer, targetBranchIndex, branchNode, createdNewBranch)) {
        return false;
      }
      if (!branchNode || !thermalZone.addToNode(*branchNode)) {
        rollbackReservedDemandBranchSlot(splitter, mixer, targetBranchIndex, createdNewBranch);
        return false;
      }

      auto conn = resolveZoneConnections(thermalZone);
      if (!conn) {
        // ThermalZone::addToNode has already mutated splitter/mixer rows and
        // zone equipment connections. Reuse the normal branch-removal path to
        // unwind that partial attach instead of duplicating teardown logic.
        removeBranchForZone(thermalZone);
        return false;
      }

      auto zoneNode = conn->zoneAirInletNode();
      if (!zoneNode || !airTerminal.addToNode(*zoneNode)) {
        // Same rollback rule: once the zone is on the branch, failed terminal
        // insertion must remove the partial branch rather than only clearing
        // the reserved splitter/mixer slot.
        removeBranchForZone(thermalZone);
        return false;
      }

      syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      syncSetpointManagerMixedAirFanNodes();
      return true;
    }

    bool AirLoopHVAC_Impl::removeBranchForZone(openstudio::epmodel::ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      auto conn = resolveZoneConnections(thermalZone);
      if (!conn) {
        return false;
      }

      auto zoneNode = conn->zoneAirInletNode();
      if (!zoneNode) {
        return false;
      }

      auto splitter = zoneSplitter();
      auto mixer = zoneMixer();
      const auto mixerInlets = mixer.inletModelObjects();
      const auto splitterOutlets = splitter.outletModelObjects();
      const auto count = std::min(mixerInlets.size(), splitterOutlets.size());
      boost::optional<unsigned> branchIndex;
      for (unsigned i = 0; i < count; ++i) {
        if (mixerInlets[i] == zoneNode->cast<ModelObject>()) {
          branchIndex = i;
          break;
        }
      }
      if (!branchIndex) {
        return false;
      }

      auto splitterOutletNode = splitterOutlets[*branchIndex].optionalCast<openstudio::epmodel::Node>();
      if (!splitterOutletNode) {
        return false;
      }

      auto branchStraightComponents = resolveDemandBranchChain(*splitterOutletNode, *zoneNode);
      if (!branchStraightComponents) {
        LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVAC",
                 "Unable to resolve branch-local straight components for zone '" << thermalZone.nameString() << "' during removeBranchForZone.");
        return false;
      }

      for (auto& straightComp : *branchStraightComponents) {
        straightComp.remove();
      }

      splitter.removePortForBranch(*branchIndex);
      mixer.removePortForBranch(*branchIndex);

      if (splitter.outletModelObjects().empty()) {
        auto defaultNode =
          model().getOrCreateTransientByName<openstudio::epmodel::Node>(getObject<AirLoopHVAC>().nameString() + " Demand Branch Node");
        resolveZoneSplitterBranchNode(splitter, 0u, defaultNode);
        resolveZoneMixerBranchNode(mixer, 0u, defaultNode);
      }

      OS_ASSERT(conn->setString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, ""));
      OS_ASSERT(conn->setString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, ""));

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
      ModelObject previousObject = supplyInletNode();

      const auto branches = branchList().branches();
      if (branches.empty()) {
        OS_ASSERT(false);
        return {};
      }
      const auto& supplyBranch = branches.front();
      const auto supplyBranchComponents = supplyBranch.components();
      for (unsigned index = 0; index < supplyBranchComponents.size(); ++index) {
        const auto& supplyComponent = supplyBranchComponents[index];

        // Preserve branch ordering exactly as listed in Branch extensibles;
        // this is the canonical sequencing contract for supply traversal.
        builder.addLink(previousObject, supplyComponent);
        previousObject = supplyComponent;

        auto outletNode = supplyBranch.componentOutletNode(index);
        if (!outletNode) {
          OS_ASSERT(false);
          continue;
        }
        builder.addLink(previousObject, *outletNode);
        previousObject = *outletNode;
      }

      const auto outletNode = supplyOutletNode();
      // Default-constructed loops may still have only partial branch topology.
      // Close the chain to supply outlet so path walking always has a terminal
      // anchor even before richer supply components are added.
      if (previousObject != outletNode) {
        builder.addLink(previousObject, outletNode);
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
      return supplyComponents(supplyInletNode(), supplyOutletNode(), type);
    }

    std::vector<ModelObject> AirLoopHVAC_Impl::demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                                                openstudio::IddObjectType type) const {
      const auto demandInlet = demandInletNode();
      const auto demandOutlet = demandOutletNode();
      const auto zoneSplitter = this->zoneSplitter();
      const auto zoneMixer = this->zoneMixer();

      auto buildDemandBranchLeg = [&](const ModelObject& splitterOutletObject, const ModelObject& mixerInletObject) {
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

        appendDistinct(splitterOutletObject);

        // Resolve terminal-driven leg internals once to avoid ambiguous
        // backtracking across zone-level relationships.
        bool zoneAdded = false;
        boost::optional<ModelObject> terminal;
        auto splitterOutletNode = splitterOutletObject.optionalCast<Node>();
        auto mixerInletNode = mixerInletObject.optionalCast<Node>();
        if (splitterOutletNode && mixerInletNode) {
          terminal = resolveTerminalOnDemandBranchNodes(*splitterOutletNode, *mixerInletNode);
        }
        if (terminal) {
          appendDistinct(*terminal);

          if (auto terminalOutlet = resolveTerminalOutletObject(*terminal)) {
            appendDistinct(*terminalOutlet);

            if (auto terminalOutletNode = terminalOutlet->optionalCast<Node>()) {
              if (auto zone = resolveZoneServedByInletNode(*terminalOutletNode)) {
                appendDistinct(zone.get().cast<ModelObject>());
                zoneAdded = true;
              }
            }
          }
        }

        // Fallback for incomplete terminal linkage: still anchor zone via
        // mixer-side node so demand graph remains connected.
        if (!zoneAdded) {
          if (auto mixerInletNode = mixerInletObject.optionalCast<Node>()) {
            if (auto zone = resolveZoneServedByReturnNode(*mixerInletNode)) {
              appendDistinct(zone.get().cast<ModelObject>());
            }
          }
        }

        // Anchor each leg at mixer inlet; we intentionally do not model full
        // intra-zone graph details in this loop-level traversal API.
        appendDistinct(mixerInletObject);

        return chain;
      };

      std::vector<ModelObject> pathObjects;
      pathObjects.reserve(64);
      pathObjects.emplace_back(demandInlet);
      pathObjects.emplace_back(zoneSplitter);

      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto mixerInlets = zoneMixer.inletModelObjects();
      // Canonical demand topology keeps splitter outlets and mixer inlets in
      // lockstep. Keep traversal resilient and bounded by min().
      const auto branchCount = std::min(splitterOutlets.size(), mixerInlets.size());

      for (unsigned i = 0; i < branchCount; ++i) {
        auto chain = buildDemandBranchLeg(splitterOutlets[i], mixerInlets[i]);
        pathObjects.insert(pathObjects.end(), chain.begin(), chain.end());
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
