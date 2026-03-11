/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVAC_IMPL_HPP
#define EPMODEL_AIRLOOPHVAC_IMPL_HPP

#include "Loop_Impl.hpp"
#include "BranchList.hpp"
#include "HVACComponent.hpp"
#include "ModelObject.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class AirLoopHVACReturnPath;
  class AirLoopHVACSupplyPath;
  class AvailabilityManager;
  class AvailabilityManagerAssignmentList;
  class AirLoopHVACOutdoorAirSystem;
  class ThermalZone;
  class AirLoopHVACZoneMixer;
  class AirLoopHVACZoneSplitter;
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
      boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
      std::vector<openstudio::epmodel::ThermalZone> thermalZones() const;
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
      static boost::optional<std::vector<openstudio::epmodel::StraightComponent>> resolveDemandBranchChain(
        const openstudio::epmodel::Node& branchStartNode, const openstudio::epmodel::Node& branchEndNode);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
