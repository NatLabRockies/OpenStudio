/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVAC_HPP
#define EPMODEL_AIRLOOPHVAC_HPP

#include "EPModelAPI.hpp"
#include "Loop/Loop.hpp"

#include <utilities/core/Logger.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Node;
  class AirLoopHVACOutdoorAirSystem;
  class AvailabilityManager;
  class AirLoopHVACZoneMixer;
  class AirLoopHVACZoneSplitter;
  class SizingSystem;
  class ThermalZone;

  namespace detail {
    class AirLoopHVAC_Impl;
  }

  class Model;

  class EPMODEL_API AirLoopHVAC : public Loop
  {
   public:
    explicit AirLoopHVAC(const Model& model);

    ~AirLoopHVAC() override = default;
    AirLoopHVAC(const AirLoopHVAC& other) = default;
    AirLoopHVAC(AirLoopHVAC&& other) = default;
    AirLoopHVAC& operator=(const AirLoopHVAC&) = default;
    AirLoopHVAC& operator=(AirLoopHVAC&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. Core scalar accessors, node/traversal APIs, branch mutation, outdoor-air-system lookup, air-side convenience APIs, sizing ownership, and night-cycle wiring are present, but the canonical AirLoopHVAC surface is still incomplete.
    // - Canonical Counterpart: openstudio::model::AirLoopHVAC.
    // - Implemented Parity: `designSupplyAirFlowRate`, `designReturnAirFlowFractionofSupplyAirFlow`, supply/demand node accessors, `zoneSplitter`, `zoneMixer`, `supplyComponents`, `demandComponents`, `airLoopHVACOutdoorAirSystem`, `thermalZones`, and availability-manager APIs preserve the main single-duct loop-topology contract used by canonical model code.
    // - Documented Delta: Public dual-duct helpers (`isDualDuct`, supply splitter helpers, multi-splitter surfaces) and availability-schedule APIs are still not exposed even though related topology and availability-manager storage exist in epmodel.
    // - Field/Storage Mapping: Connector-list and splitter/mixer linkage remain relationship-driven through EnergyPlus branch topology helpers instead of scalar string accessors for `ConnectorListName` and related node names.
    // - Evidence: `src/model/AirLoopHVAC.hpp`, the air-loop forward/reverse translator files, and `src/epmodel/test/IDF_SmallOffice_GTest.cpp` define the canonical loop traversal and topology expectations this wrapper is partially matching.
    // - Remaining Parity Work: Add the remaining dual-duct, outdoor-air-node, and higher-level convenience APIs after the topology anchor types and zone-side branching helpers are fully normalized.
    boost::optional<double> designSupplyAirFlowRate() const;
    bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
    void resetDesignSupplyAirFlowRate();
    bool isDesignSupplyAirFlowRateAutosized() const;
    void autosizeDesignSupplyAirFlowRate();
    double designReturnAirFlowFractionofSupplyAirFlow() const;
    bool setDesignReturnAirFlowFractionofSupplyAirFlow(double designReturnAirFlowFractionofSupplyAirFlow);

    Node supplyInletNode() const override;
    Node supplyOutletNode() const override;
    std::vector<Node> supplyOutletNodes() const override;

    Node demandInletNode() const override;
    Node demandOutletNode() const override;
    std::vector<Node> demandInletNodes() const override;
    AirLoopHVACZoneSplitter zoneSplitter() const;
    AirLoopHVACZoneMixer zoneMixer() const;

    std::vector<ModelObject> supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                              openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;
    std::vector<ModelObject> supplyComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;

    std::vector<ModelObject> demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                              openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;
    std::vector<ModelObject> demandComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;
    std::vector<ModelObject> oaComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const;
    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> reliefAirNode() const;
    boost::optional<Node> mixedAirNode() const;
    boost::optional<Node> returnAirNode() const;
    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
    boost::optional<HVACComponent> supplyFan() const;
    boost::optional<HVACComponent> returnFan() const;
    boost::optional<HVACComponent> reliefFan() const;
    SizingSystem sizingSystem() const;
    std::vector<ThermalZone> thermalZones() const;
    std::vector<AvailabilityManager> availabilityManagers() const;

    bool addAvailabilityManager(const AvailabilityManager& availabilityManager);
    bool addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority);
    bool setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers);
    void resetAvailabilityManagers();
    bool removeAvailabilityManager(const AvailabilityManager& availabilityManager);
    bool removeAvailabilityManager(unsigned priority);
    bool setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority);
    unsigned availabilityManagerPriority(const AvailabilityManager& availabilityManager) const;
    bool setNightCycleControlType(const std::string& controlType);
    std::string nightCycleControlType() const;

    bool addBranchForZone(ThermalZone& thermalZone);
    bool addBranchForZone(ThermalZone& thermalZone, HVACComponent& airTerminal);
    bool addBranchForHVACComponent(HVACComponent& hvacComponent);
    bool removeBranchForZone(ThermalZone& thermalZone);

   protected:
    using ImplType = detail::AirLoopHVAC_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class openstudio::epmodel::Model;

    explicit AirLoopHVAC(std::shared_ptr<detail::AirLoopHVAC_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.AirLoopHVAC");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
