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

/** \brief A transient node wrapper for HVAC topology.
 *
 * \par EnergyPlus object
 * No standalone EnergyPlus object. EnergyPlus stores node names in the inlet,
 * outlet, sensor, and setpoint fields of HVAC and control objects; this wrapper
 * exposes a named point assembled from those references.
 *
 * \par Important behavior
 * EnergyPlus has no persisted Node object; this wrapper resolves node names and branch relationships while exposing setpoint-manager and outdoor-air-system traversal.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::Node</code>.
 *
 * - <b>Not yet available:</b>
 *   <code>getAirflowNetworkDistributionNode()</code> and
 *   <code>airflowNetworkDistributionNode()</code>.
 * - <b>Added:</b> <code>airLoopHVACOutdoorAirSystem()</code> traverses from the
 *   node to its outdoor-air system when one exists.
 *
 * \par Known limitations
 * A node exists only while the surrounding EnergyPlus-backed HVAC topology
 * refers to its name; it is not persisted as an independent object.
 */
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
