/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVAC_IMPL_HPP
#define EPMODEL_AIRLOOPHVAC_IMPL_HPP

#include "Loop/Loop_Impl.hpp"
#include "BranchList.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {
  class AirLoopHVACReturnPath;
  class AirLoopHVACSupplyPath;
  class AvailabilityManager;
  class AvailabilityManagerScheduledOn;
  class AvailabilityManagerAssignmentList;
  class AirLoopHVACOutdoorAirSystem;
  class Schedule;
  class ThermalZone;
  class AirLoopHVACZoneMixer;
  class Mixer;
  class AirLoopHVACZoneSplitter;
  class Splitter;
  class SizingSystem;
  class Node;
  class StraightComponent;
  class ZoneHVACEquipmentConnections;
}  // namespace epmodel
namespace epmodel {
  namespace detail {
    struct LoadContext;

    class EPMODEL_API AirLoopHVAC_Impl : public Loop_Impl
    {
     public:
      using Loop_Impl::Loop_Impl;
      virtual ~AirLoopHVAC_Impl() override = default;
      boost::optional<double> designSupplyAirFlowRate() const;
      bool isDesignSupplyAirFlowRateAutosized() const;
      bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
      void resetDesignSupplyAirFlowRate();
      void autosizeDesignSupplyAirFlowRate();
      double designReturnAirFlowFractionofSupplyAirFlow() const;
      bool setDesignReturnAirFlowFractionofSupplyAirFlow(double designReturnAirFlowFractionofSupplyAirFlow);
      openstudio::epmodel::Node supplyInletNode() const override;
      openstudio::epmodel::Node supplyOutletNode() const override;
      std::vector<openstudio::epmodel::Node> supplyOutletNodes() const override;
      openstudio::epmodel::Node demandInletNode() const override;
      openstudio::epmodel::Node demandOutletNode() const override;
      std::vector<openstudio::epmodel::Node> demandInletNodes() const override;
      openstudio::epmodel::BranchList branchList() const;
      bool isDualDuct() const;
      boost::optional<openstudio::epmodel::Splitter> supplySplitter() const;
      boost::optional<openstudio::epmodel::Node> supplySplitterInletNode() const;
      std::vector<openstudio::epmodel::Node> supplySplitterOutletNodes() const;
      bool makeDualDuct();
      boost::optional<openstudio::epmodel::Branch> branchForSupplyNode(const openstudio::epmodel::Node& node) const;
      static bool addDualDuctTerminalToNode(openstudio::epmodel::Mixer& terminal, openstudio::epmodel::Node& node);
      static bool removeDualDuctTerminalFromAirLoopHVAC(openstudio::epmodel::Mixer& terminal);
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(openstudio::IddObjectType type) const override;
      std::vector<openstudio::IdfObject> remove() override;
      std::vector<openstudio::epmodel::ModelObject> oaComponents(openstudio::IddObjectType type) const;
      boost::optional<openstudio::epmodel::Node> outdoorAirNode() const;
      boost::optional<openstudio::epmodel::Node> reliefAirNode() const;
      boost::optional<openstudio::epmodel::Node> mixedAirNode() const;
      boost::optional<openstudio::epmodel::Node> returnAirNode() const;
      boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
      boost::optional<openstudio::epmodel::HVACComponent> supplyFan() const;
      boost::optional<openstudio::epmodel::HVACComponent> returnFan() const;
      boost::optional<openstudio::epmodel::HVACComponent> reliefFan() const;
      openstudio::epmodel::SizingSystem sizingSystem() const;
      openstudio::epmodel::Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);
      std::vector<openstudio::epmodel::ThermalZone> thermalZones() const;
      std::vector<openstudio::epmodel::ModelObject> children() const override;
      // Schema Alignment Notes:
      // - Field Mapping: AirLoopHVAC::AvailabilityManagerListName stores a relationship target.
      // - API: preserve model-style availability manager list operations via AvailabilityManagerAssignmentList object API.
      openstudio::epmodel::AvailabilityManagerAssignmentList availabilityManagerAssignmentList() const;
      std::vector<openstudio::epmodel::AvailabilityManager> availabilityManagers() const;
      bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
      bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);
      bool setAvailabilityManagers(const std::vector<openstudio::epmodel::AvailabilityManager>& availabilityManagers);
      void resetAvailabilityManagers();
      bool removeAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
      bool removeAvailabilityManager(unsigned priority);
      bool setAvailabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);
      unsigned availabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager) const;
      bool setNightCycleControlType(const std::string& controlType);
      std::string nightCycleControlType() const;
      enum class DualDuctZoneAttachmentFailureStage
      {
        None,
        AfterProvisionalObjectsPrepared,
      };
      enum class DemandBranchAttachmentFailureStage
      {
        None,
        AfterTerminalClonePrepared,
        AfterFirstPlantReconnectionPrepared,
        AfterPlantReconnectionPrepared,
        AfterReservationPrepared,
        AfterZonePrepared,
        AfterTerminalZoneProjectionPrepared,
        BeforeTerminalAttachment,
        AfterDualDuctTerminalPrepared,
      };
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone);
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, DualDuctZoneAttachmentFailureStage failureStage);
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, DemandBranchAttachmentFailureStage failureStage);
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, openstudio::epmodel::HVACComponent& airTerminal);
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, openstudio::epmodel::HVACComponent& airTerminal,
                            DemandBranchAttachmentFailureStage failureStage);
      bool addBranchForHVACComponent(openstudio::epmodel::HVACComponent& hvacComponent);
      bool addBranchForHVACComponent(openstudio::epmodel::HVACComponent& hvacComponent, DemandBranchAttachmentFailureStage failureStage);
      bool removeBranchForZone(openstudio::epmodel::ThermalZone& thermalZone);
      boost::optional<openstudio::epmodel::Node> effectiveDemandReturnNodeForBranchStart(const openstudio::epmodel::Node& branchStartNode) const;
      bool isDemandBranchStartComponent(const openstudio::epmodel::StraightComponent& component) const;
      bool bypassDemandBranchStartComponent(const openstudio::epmodel::StraightComponent& component);
      void syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      void syncSetpointManagerMixedAirFanNodes();
      void syncSupplyWaterCoilControllers();

      openstudio::epmodel::AirLoopHVACReturnPath airLoopHVACReturnPath() const;
      openstudio::epmodel::AirLoopHVACSupplyPath airLoopHVACSupplyPath() const;
      openstudio::epmodel::AirLoopHVACZoneSplitter zoneSplitter() const;
      openstudio::epmodel::AirLoopHVACZoneMixer zoneMixer() const;
      openstudio::epmodel::Node demandBranchNode() const;
      void doCanonicalize(LoadContext& context) override;

     private:
      friend class ThermalZone_Impl;
      class DemandBranchAttachmentPlan;
      class TerminalZoneProjectionPlan;
      class SingleDuctTerminalClonePlan;
      class DualDuctZoneAttachment;
      class DualDuctTerminalInsertionPlan;
      class DemandTopologySnapshot;
      class DemandBranchComponentLocation;
      static boost::optional<openstudio::epmodel::ModelObject> resolveTerminalOnDemandBranchNodes(const openstudio::epmodel::Node& splitterOutletNode,
                                                                                                  const openstudio::epmodel::Node& mixerInletNode);
      static boost::optional<openstudio::epmodel::ModelObject> resolveTerminalOutletObject(const openstudio::epmodel::ModelObject& terminalObject);
      static boost::optional<openstudio::epmodel::ThermalZone> resolveZoneServedByInletNode(const openstudio::epmodel::Node& zoneInletNode);
      static boost::optional<openstudio::epmodel::ThermalZone> resolveZoneServedByReturnNode(const openstudio::epmodel::Node& zoneReturnNode);
      bool isTerminalTypeValid(const openstudio::epmodel::HVACComponent& airTerminal) const;
      boost::optional<openstudio::epmodel::HVACComponent> reusableSingleDuctTerminalForZone() const;
      boost::optional<openstudio::epmodel::StraightComponent> lastSingleDuctTerminalForClone() const;
      boost::optional<openstudio::epmodel::HVACComponent> cloneLastDualDuctTerminalForBranch() const;
      DemandTopologySnapshot demandTopologySnapshot() const;
      std::unique_ptr<DemandBranchComponentLocation> demandBranchComponentLocation(const openstudio::epmodel::StraightComponent& component) const;
      boost::optional<openstudio::epmodel::ModelObject> effectiveDemandBranchStartForZone(const openstudio::epmodel::ThermalZone& thermalZone) const;
      boost::optional<openstudio::epmodel::Node> effectiveDemandReturnNodeForZone(const openstudio::epmodel::ThermalZone& thermalZone) const;
      bool removeDemandBranch(const openstudio::epmodel::ModelObject& splitterOutlet, const openstudio::epmodel::ModelObject& mixerInlet);
      bool collapseSecondaryDemandPathIfEmpty(openstudio::epmodel::Node secondaryDemandInletNode,
                                              openstudio::epmodel::AirLoopHVACZoneSplitter secondarySplitter);
      boost::optional<openstudio::epmodel::Mixer> reusableDualDuctTerminalForZone() const;
      bool detachZoneFromDemandNodes(openstudio::epmodel::ZoneHVACEquipmentConnections& connections);
      boost::optional<openstudio::epmodel::AirLoopHVACZoneSplitter>
        zoneSplitterForDemandInletNode(const openstudio::epmodel::Node& demandInletNode) const;
      static bool isSupportedMixedAirFanType(openstudio::IddObjectType objectType);
      static boost::optional<openstudio::epmodel::HVACComponent> lastSupportedFan(const std::vector<openstudio::epmodel::ModelObject>& components);
      // AirLoopHVAC availability-schedule APIs are mapped onto one canonical
      // AvailabilityManager:ScheduledOn entry in the loop assignment list.
      // These helpers centralize that policy so public APIs and availability
      // manager mutators preserve the same invariant.
      boost::optional<openstudio::epmodel::AvailabilityManagerScheduledOn> availabilityScheduleManager() const;
      openstudio::epmodel::AvailabilityManagerScheduledOn ensureAvailabilityScheduleManager();
      // Schema Alignment Notes:
      // - Field Mapping: AirLoopHVAC::ConnectorListName stores branch connector relationships, not scalar data.
      // - API: AirLoopHVAC exposes Connector:Splitter behavior through zoneSplitter()/zoneMixer() and demand topology traversal.
      // - Field Mapping: Connector:Splitter Inlet/Outlet Branch rows are represented by branch node wiring and
      //   AirLoopHVAC:ZoneSplitter/AirLoopHVAC:ZoneMixer relationships, not scalar accessors.
      static boost::optional<std::vector<openstudio::epmodel::StraightComponent>>
        resolveDemandBranchChain(const openstudio::epmodel::Node& branchStartNode, const openstudio::epmodel::Node& branchEndNode);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
