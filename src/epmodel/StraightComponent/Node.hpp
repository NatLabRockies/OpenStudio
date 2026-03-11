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
  // - API: Node keeps existing topology-oriented API (`setpointManagers`, `airLoopHVACOutdoorAirSystem`) and does not add new scalar methods.
  // - Field Mapping: EnergyPlus Node has no non-name scalar fields for this pass; relationship-like topology wiring remains in implementation methods.
  // - TODO(parity): Add explicit relationship/node-link field APIs in dedicated relationship coverage work.

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
