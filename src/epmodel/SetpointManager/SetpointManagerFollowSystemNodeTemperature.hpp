/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerFollowSystemNodeTemperature_Impl;
  }

  class EPMODEL_API SetpointManagerFollowSystemNodeTemperature : public SetpointManager
  {
   public:
    explicit SetpointManagerFollowSystemNodeTemperature(const Model& model);

    virtual ~SetpointManagerFollowSystemNodeTemperature() override = default;
    SetpointManagerFollowSystemNodeTemperature(const SetpointManagerFollowSystemNodeTemperature& other) = default;
    SetpointManagerFollowSystemNodeTemperature(SetpointManagerFollowSystemNodeTemperature&& other) = default;
    SetpointManagerFollowSystemNodeTemperature& operator=(const SetpointManagerFollowSystemNodeTemperature&) = default;
    SetpointManagerFollowSystemNodeTemperature& operator=(SetpointManagerFollowSystemNodeTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> referenceTemperatureTypeValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. The scalar follow rule, reference-node relationship, and inherited setpoint-node attachment are aligned.
    // - Canonical Counterpart: openstudio::model::SetpointManagerFollowSystemNodeTemperature.
    // - Implemented Parity: Preserves the canonical scalar accessors, reference-node relationship, and inherited setpoint-node attachment.
    // - Field Mapping: referenceTemperatureType, offsetTemperatureDifference, maximumLimitSetpointTemperature, and
    //   minimumLimitSetpointTemperature map directly to E+ SetpointManager:FollowSystemNodeTemperature fields.
    // - Field/Storage Mapping: referenceNode maps directly to E+ Reference Node Name; inherited addToNode/setpointNode behavior maps
    //   Setpoint Node or NodeList Name.
    // - Canonicalization: Load resolves persisted reference and setpoint node names once; ordinary relationship getters are observational.
    // - Evidence: Relationship tests cover validation, persisted-name repair, save/load mutation, reset, and removal.
    // - Remaining Parity Work: Broader clone and workflow evidence remains demand-driven.

    boost::optional<Node> referenceNode() const;
    bool setReferenceNode(const Node& node);
    void resetReferenceNode();

    std::string referenceTemperatureType() const;
    bool setReferenceTemperatureType(const std::string& referenceTemperatureType);

    double offsetTemperatureDifference() const;
    bool setOffsetTemperatureDifference(double offsetTemperatureDifference);

    double maximumLimitSetpointTemperature() const;
    bool setMaximumLimitSetpointTemperature(double maximumLimitSetpointTemperature);

    double minimumLimitSetpointTemperature() const;
    bool setMinimumLimitSetpointTemperature(double minimumLimitSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerFollowSystemNodeTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerFollowSystemNodeTemperature(std::shared_ptr<detail::SetpointManagerFollowSystemNodeTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
