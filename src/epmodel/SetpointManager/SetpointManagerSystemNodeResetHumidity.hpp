/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSystemNodeResetHumidity_Impl;
  }

  class EPMODEL_API SetpointManagerSystemNodeResetHumidity : public SetpointManager
  {
   public:
    explicit SetpointManagerSystemNodeResetHumidity(const Model& model);

    virtual ~SetpointManagerSystemNodeResetHumidity() override = default;
    SetpointManagerSystemNodeResetHumidity(const SetpointManagerSystemNodeResetHumidity& other) = default;
    SetpointManagerSystemNodeResetHumidity(SetpointManagerSystemNodeResetHumidity&& other) = default;
    SetpointManagerSystemNodeResetHumidity& operator=(const SetpointManagerSystemNodeResetHumidity&) = default;
    SetpointManagerSystemNodeResetHumidity& operator=(SetpointManagerSystemNodeResetHumidity&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: setpointatLowReferenceHumidityRatio, setpointatHighReferenceHumidityRatio,
    //   lowReferenceHumidityRatio, and highReferenceHumidityRatio map directly to
    //   E+ SetpointManager:SystemNodeReset:Humidity scalar fields.
    // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSystemNodeResetHumidity writes these exact
    //   scalar fields plus control variable using preserved model API names.
    // - Field Mapping: Relationship fields Reference Node Name and Setpoint Node or NodeList Name are intentionally
    //   excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for explicit reference-node linkage in a follow-up pass.
    double setpointatLowReferenceHumidityRatio() const;
    bool setSetpointatLowReferenceHumidityRatio(double setpointatLowReferenceHumidityRatio);

    double setpointatHighReferenceHumidityRatio() const;
    bool setSetpointatHighReferenceHumidityRatio(double setpointatHighReferenceHumidityRatio);

    double lowReferenceHumidityRatio() const;
    bool setLowReferenceHumidityRatio(double lowReferenceHumidityRatio);

    double highReferenceHumidityRatio() const;
    bool setHighReferenceHumidityRatio(double highReferenceHumidityRatio);

   protected:
    using ImplType = detail::SetpointManagerSystemNodeResetHumidity_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSystemNodeResetHumidity(std::shared_ptr<detail::SetpointManagerSystemNodeResetHumidity_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
