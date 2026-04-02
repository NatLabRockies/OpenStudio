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
