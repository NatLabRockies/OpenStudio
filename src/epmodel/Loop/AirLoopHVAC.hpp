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
    // - API: Preserve openstudio::model accessor names for AirLoopHVAC scalar fields.
    // - Field Mapping: designSupplyAirFlowRate and designReturnAirFlowFractionofSupplyAirFlow map directly to
    //   AirLoopHVAC fields in E+ schema.
    // - Field Mapping: AirLoopHVAC::ConnectorListName is relationship-only and maps through branch topology helpers
    //   (zoneSplitter/zoneMixer + demand branch traversal), not scalar string accessors.
    // - Field Mapping: Connector:Splitter mapping is relationship-only. AirLoopHVAC::zoneSplitter / zoneMixer and
    //   demand branch topology APIs carry this linkage instead of scalar string accessors.
    // - Field Mapping: AvailabilityManagerListName maps to AvailabilityManagerAssignmentList relationship APIs
    //   (availabilityManagers/add/remove/priority) and is intentionally not exposed as a scalar string accessor.
    // - TODO(parity): Extend this class with additional scalar API parity where model counterparts exist.
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
    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
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
