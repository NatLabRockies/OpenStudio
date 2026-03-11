/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVAC_HPP
#define EPMODEL_AIRLOOPHVAC_HPP

#include "EPModelAPI.hpp"
#include "Loop.hpp"

#include "../utilities/core/Logger.hpp"
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
