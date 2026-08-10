/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGER_HPP
#define EPMODEL_SETPOINTMANAGER_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "StraightComponent/Node.hpp"

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManager_Impl;
  }

  class EPMODEL_API SetpointManager : public HVACComponent
  {
   public:
    virtual ~SetpointManager() override = default;
    SetpointManager(const SetpointManager& other) = default;
    SetpointManager(SetpointManager&& other) = default;
    SetpointManager& operator=(const SetpointManager&) = default;
    SetpointManager& operator=(SetpointManager&&) = default;

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::SetpointManager.
    // - Implemented Parity: Setpoint-node attachment, control-variable access, placement eligibility, and inherited loop,
    //   air-loop, plant-loop, and outdoor-air-system ownership queries follow the attached Node.
    // - Field/Storage Mapping: Concrete EnergyPlus setpoint-manager objects persist their setpoint Node field directly;
    //   reverse Node discovery and loop ownership are live relationship views over that target.
    // - Remaining Parity Work: Characterize clone/disconnect behavior and subtype-specific placement and control relationships.
    boost::optional<Node> setpointNode() const;
    std::string controlVariable() const;
    bool setControlVariable(const std::string& value);

    bool isAllowedOnPlantLoop() const;
    bool addToNode(Node& node);

   protected:
    using ImplType = detail::SetpointManager_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::SetpointManager_Impl;

    SetpointManager(IddObjectType type, const Model& model);
    explicit SetpointManager(std::shared_ptr<detail::SetpointManager_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
