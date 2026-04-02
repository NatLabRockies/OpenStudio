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
  class AirLoopHVACZoneSplitter;
  class SizingSystem;
  class ZoneHVACEquipmentConnections;
  class Node;
  class StraightComponent;
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
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(openstudio::IddObjectType type) const override;
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
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone);
      bool addBranchForZone(openstudio::epmodel::ThermalZone& thermalZone, openstudio::epmodel::HVACComponent& airTerminal);
      bool addBranchForHVACComponent(openstudio::epmodel::HVACComponent& hvacComponent);
      bool removeBranchForZone(openstudio::epmodel::ThermalZone& thermalZone);
      void syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      void syncSetpointManagerMixedAirFanNodes();

      openstudio::epmodel::AirLoopHVACReturnPath airLoopHVACReturnPath() const;
      openstudio::epmodel::AirLoopHVACSupplyPath airLoopHVACSupplyPath() const;
      openstudio::epmodel::AirLoopHVACZoneSplitter zoneSplitter() const;
      openstudio::epmodel::AirLoopHVACZoneMixer zoneMixer() const;
      openstudio::epmodel::Node demandBranchNode() const;
      void doCanonicalize(LoadContext& context) override;

     private:
      static boost::optional<openstudio::epmodel::ModelObject> resolveTerminalOnDemandBranchNodes(
        const openstudio::epmodel::Node& splitterOutletNode, const openstudio::epmodel::Node& mixerInletNode);
      static boost::optional<openstudio::epmodel::ModelObject> resolveTerminalOutletObject(
        const openstudio::epmodel::ModelObject& terminalObject);
      static boost::optional<openstudio::epmodel::ThermalZone> resolveZoneServedByInletNode(const openstudio::epmodel::Node& zoneInletNode);
      static boost::optional<openstudio::epmodel::ThermalZone> resolveZoneServedByReturnNode(const openstudio::epmodel::Node& zoneReturnNode);
      static boost::optional<openstudio::epmodel::ZoneHVACEquipmentConnections> resolveZoneConnections(
        const openstudio::epmodel::ThermalZone& zone);
      static bool resolveZoneSplitterBranchNode(openstudio::epmodel::AirLoopHVACZoneSplitter& splitter, unsigned branchIndex,
                                                const openstudio::epmodel::Node& branchNode);
      static bool resolveZoneMixerBranchNode(openstudio::epmodel::AirLoopHVACZoneMixer& mixer, unsigned branchIndex,
                                             const openstudio::epmodel::Node& branchNode);
      // Demand-side branch mutation always starts by reserving a splitter/mixer
      // branch slot. For the default one-branch loop we reuse the shared
      // splitter<->mixer node; once real branching already exists we allocate a
      // new branch row and transient node as one unit so later rollback can
      // cleanly remove only the newly introduced topology.
      bool reserveDemandBranchSlot(openstudio::epmodel::AirLoopHVACZoneSplitter& splitter, openstudio::epmodel::AirLoopHVACZoneMixer& mixer,
                                   unsigned& targetBranchIndex, boost::optional<openstudio::epmodel::Node>& branchNode, bool& createdNewBranch);
      // Undo only the reservation work performed by reserveDemandBranchSlot().
      // This intentionally does not try to remove any component or zone that
      // was successfully attached later in the mutation flow.
      void rollbackReservedDemandBranchSlot(openstudio::epmodel::AirLoopHVACZoneSplitter& splitter, openstudio::epmodel::AirLoopHVACZoneMixer& mixer,
                                            unsigned targetBranchIndex, bool createdNewBranch);
      static bool isSupportedMixedAirFanType(openstudio::IddObjectType objectType);
      static boost::optional<openstudio::epmodel::HVACComponent> lastSupportedFan(
        const std::vector<openstudio::epmodel::ModelObject>& components);
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
      static boost::optional<std::vector<openstudio::epmodel::StraightComponent>> resolveDemandBranchChain(
        const openstudio::epmodel::Node& branchStartNode, const openstudio::epmodel::Node& branchEndNode);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
