/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMIXEDAIR_HPP
#define EPMODEL_SETPOINTMANAGERMIXEDAIR_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class SetpointManagerMixedAir_Impl;
}

class EPMODEL_API SetpointManagerMixedAir : public SetpointManager
{
 public:
  explicit SetpointManagerMixedAir(const Model& model);

  virtual ~SetpointManagerMixedAir() override = default;
  SetpointManagerMixedAir(const SetpointManagerMixedAir& other) = default;
  SetpointManagerMixedAir(SetpointManagerMixedAir&& other) = default;
  SetpointManagerMixedAir& operator=(const SetpointManagerMixedAir&) = default;
  SetpointManagerMixedAir& operator=(SetpointManagerMixedAir&&) = default;

  static IddObjectType iddObjectType();

  boost::optional<Node> referenceSetpointNode() const;
  boost::optional<Node> fanInletNode() const;
  boost::optional<Node> fanOutletNode() const;

 protected:
  using ImplType = detail::SetpointManagerMixedAir_Impl;

  friend class Model;

  explicit SetpointManagerMixedAir(std::shared_ptr<detail::SetpointManagerMixedAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
