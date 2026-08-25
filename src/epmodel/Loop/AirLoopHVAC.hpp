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
  class AirLoopHVACDedicatedOutdoorAirSystem;
  class AirLoopHVACOutdoorAirSystem;
  class AvailabilityManager;
  class AvailabilityManagerScheduledOn;
  class AirLoopHVACZoneMixer;
  class AirLoopHVACZoneSplitter;
  class Schedule;
  class SizingSystem;
  class Splitter;
  class ThermalZone;

  namespace detail {
    class AirLoopHVAC_Impl;
  }

  class Model;

  /** \brief Represents an air-side HVAC loop and its supply and demand branches.
   *
   * \par EnergyPlus object
   * \epobject{group-air-distribution.html#airloophvac,AirLoopHVAC}.
   *
   * \par Important behavior
   * A loop may be constructed as single-duct or dual-duct. Dual-duct operations maintain the common return and both supply paths as one topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVAC</code>.
   * <b>Not yet available: several SQL autosized-result helpers, <code>clone()</code>, <code>multiAddBranchForZone()</code>, <code>removeSupplySplitter()</code>, and broad multi-splitter conveniences.</b>
   *
   * \par Known limitations
   * Inlet-side mixers and user-defined terminal shapes without unambiguous branch ownership are rejected by supported topology mutators.
   */
  class EPMODEL_API AirLoopHVAC : public Loop
  {
   public:
    explicit AirLoopHVAC(const Model& model, bool dualDuct = false);

    ~AirLoopHVAC() override = default;
    AirLoopHVAC(const AirLoopHVAC& other) = default;
    AirLoopHVAC(AirLoopHVAC&& other) = default;
    AirLoopHVAC& operator=(const AirLoopHVAC&) = default;
    AirLoopHVAC& operator=(AirLoopHVAC&&) = default;

    static IddObjectType iddObjectType();

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
    bool isDualDuct() const;
    boost::optional<Splitter> supplySplitter() const;
    boost::optional<Node> supplySplitterInletNode() const;
    std::vector<Node> supplySplitterOutletNodes() const;
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
    boost::optional<AirLoopHVACDedicatedOutdoorAirSystem> airLoopHVACDedicatedOutdoorAirSystem() const;
    boost::optional<HVACComponent> supplyFan() const;
    boost::optional<HVACComponent> returnFan() const;
    boost::optional<HVACComponent> reliefFan() const;
    SizingSystem sizingSystem() const;
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
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
    friend class Model;

    explicit AirLoopHVAC(std::shared_ptr<detail::AirLoopHVAC_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.AirLoopHVAC");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
