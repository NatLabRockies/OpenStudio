/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_NODE_HPP
#define EPMODEL_NODE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class SetpointManager;
  class AirLoopHVACOutdoorAirSystem;

  namespace detail {
    class Node_Impl;
  }

  class EPMODEL_API Node : public StraightComponent
  {
   public:
    static constexpr bool is_transient = true;  // This is a Transient ModelObject

    virtual ~Node() = default;
    Node(const Node& other) = default;
    Node(Node&& other) = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;
    explicit Node(const Model& model);

    std::vector<SetpointManager> setpointManagers() const;
    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical node-facing topology API is present for setpoint-manager attachment, but node-adjacent convenience APIs remain incomplete.
    // - Canonical Counterpart: openstudio::model::Node.
    // - Implemented Parity: `setpointManagers` preserves the main canonical node control-surface behavior, and `Node` remains a topology object rather than a scalar wrapper.
    // - Documented Delta: epmodel exposes `airLoopHVACOutdoorAirSystem` as a direct topology convenience while omitting the canonical AirflowNetwork distribution-node helpers because epmodel does not yet carry the corresponding OpenStudio-side abstractions.
    // - Field/Storage Mapping: EnergyPlus has no persisted `Node` object, so epmodel keeps `Node` as transient topology connective tissue layered over EnergyPlus-backed branch/node-name relationships.
    // - Evidence: `src/model/Node.hpp` defines the canonical wrapper surface, while `src/epmodel/test/IDF_SmallOffice_GTest.cpp` exercises node-adjacent topology traversal in the current epmodel implementation.
    // - Remaining Parity Work: Add the missing airflow-network and richer node-link convenience APIs once the corresponding epmodel relationship abstractions exist.

   protected:
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    using ImplType = detail::Node_Impl;

    explicit Node(std::shared_ptr<detail::Node_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
