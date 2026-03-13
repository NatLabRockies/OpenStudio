/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERCOLDEST_HPP
#define EPMODEL_SETPOINTMANAGERCOLDEST_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerColdest_Impl;
  }

  class EPMODEL_API SetpointManagerColdest : public SetpointManager
  {
   public:
    explicit SetpointManagerColdest(const Model& model);

    virtual ~SetpointManagerColdest() override = default;
    SetpointManagerColdest(const SetpointManagerColdest& other) = default;
    SetpointManagerColdest(SetpointManagerColdest&& other) = default;
    SetpointManagerColdest& operator=(const SetpointManagerColdest&) = default;
    SetpointManagerColdest& operator=(SetpointManagerColdest&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> strategyValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSetpointTemperature, maximumSetpointTemperature, and strategy map directly to E+ SetpointManager:Coldest fields.
    // - Field Mapping: Relationship fields Setpoint Node or NodeList Name and HVAC Air Loop Name are intentionally excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for loop/name linkage in a follow-up pass.

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

    std::string strategy() const;
    bool setStrategy(const std::string& strategy);

   protected:
    using ImplType = detail::SetpointManagerColdest_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerColdest(std::shared_ptr<detail::SetpointManagerColdest_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
