/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerSystemNodeResetTemperature_Impl;
  }

  class EPMODEL_API SetpointManagerSystemNodeResetTemperature : public SetpointManager
  {
   public:
    explicit SetpointManagerSystemNodeResetTemperature(const Model& model);

    virtual ~SetpointManagerSystemNodeResetTemperature() override = default;
    SetpointManagerSystemNodeResetTemperature(const SetpointManagerSystemNodeResetTemperature& other) = default;
    SetpointManagerSystemNodeResetTemperature(SetpointManagerSystemNodeResetTemperature&& other) = default;
    SetpointManagerSystemNodeResetTemperature& operator=(const SetpointManagerSystemNodeResetTemperature&) = default;
    SetpointManagerSystemNodeResetTemperature& operator=(SetpointManagerSystemNodeResetTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. The scalar reset rule, reference-node relationship, and inherited setpoint-node attachment are aligned.
    // - Canonical Counterpart: openstudio::model::SetpointManagerSystemNodeResetTemperature.
    // - Implemented Parity: Preserves the canonical scalar accessors, reference-node relationship, and inherited setpoint-node attachment.
    // - Field Mapping: setpointatLowReferenceTemperature, setpointatHighReferenceTemperature,
    //   lowReferenceTemperature, and highReferenceTemperature map directly to
    //   E+ SetpointManager:SystemNodeReset:Temperature scalar fields.
    // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSystemNodeResetTemperature writes these exact
    //   scalar fields plus control variable using preserved model API names.
    // - Field Mapping: referenceNode maps directly to E+ Reference Node Name; inherited addToNode/setpointNode behavior maps
    //   Setpoint Node or NodeList Name.
    // - Canonicalization: Load resolves persisted reference and setpoint node names once; ordinary relationship getters are observational.
    // - Remaining Parity Work: Broader clone and workflow evidence remains demand-driven.
    double setpointatLowReferenceTemperature() const;
    bool setSetpointatLowReferenceTemperature(double setpointatLowReferenceTemperature);

    double setpointatHighReferenceTemperature() const;
    bool setSetpointatHighReferenceTemperature(double setpointatHighReferenceTemperature);

    double lowReferenceTemperature() const;
    bool setLowReferenceTemperature(double lowReferenceTemperature);

    double highReferenceTemperature() const;
    bool setHighReferenceTemperature(double highReferenceTemperature);

    boost::optional<Node> referenceNode() const;
    bool setReferenceNode(const Node& node);
    void resetReferenceNode();

   protected:
    using ImplType = detail::SetpointManagerSystemNodeResetTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSystemNodeResetTemperature(std::shared_ptr<detail::SetpointManagerSystemNodeResetTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
