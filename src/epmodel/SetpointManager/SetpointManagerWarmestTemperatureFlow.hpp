/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERWARMESTTEMPERATUREFLOW_HPP
#define EPMODEL_SETPOINTMANAGERWARMESTTEMPERATUREFLOW_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerWarmestTemperatureFlow_Impl;
  }

  class EPMODEL_API SetpointManagerWarmestTemperatureFlow : public SetpointManager
  {
   public:
    explicit SetpointManagerWarmestTemperatureFlow(const Model& model);

    virtual ~SetpointManagerWarmestTemperatureFlow() override = default;
    SetpointManagerWarmestTemperatureFlow(const SetpointManagerWarmestTemperatureFlow& other) = default;
    SetpointManagerWarmestTemperatureFlow(SetpointManagerWarmestTemperatureFlow&& other) = default;
    SetpointManagerWarmestTemperatureFlow& operator=(const SetpointManagerWarmestTemperatureFlow&) = default;
    SetpointManagerWarmestTemperatureFlow& operator=(SetpointManagerWarmestTemperatureFlow&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> strategyValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSetpointTemperature, maximumSetpointTemperature, strategy, and minimumTurndownRatio
    //   map directly to E+ SetpointManager:WarmestTemperatureFlow scalar fields.
    // - Field Mapping: Relationship fields Setpoint Node or NodeList Name and HVAC Air Loop Name are intentionally
    //   excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for node and air-loop linkage in a follow-up pass.
    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

    std::string strategy() const;
    bool setStrategy(const std::string& strategy);

    double minimumTurndownRatio() const;
    bool setMinimumTurndownRatio(double minimumTurndownRatio);

   protected:
    using ImplType = detail::SetpointManagerWarmestTemperatureFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerWarmestTemperatureFlow(std::shared_ptr<detail::SetpointManagerWarmestTemperatureFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
