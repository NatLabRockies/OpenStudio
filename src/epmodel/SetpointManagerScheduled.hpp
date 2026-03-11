/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSCHEDULED_HPP
#define EPMODEL_SETPOINTMANAGERSCHEDULED_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class ModelObject;

namespace detail {
class SetpointManagerScheduled_Impl;
}

class EPMODEL_API SetpointManagerScheduled : public SetpointManager
{
 public:
  explicit SetpointManagerScheduled(const Model& model);

  virtual ~SetpointManagerScheduled() override = default;
  SetpointManagerScheduled(const SetpointManagerScheduled& other) = default;
  SetpointManagerScheduled(SetpointManagerScheduled&& other) = default;
  SetpointManagerScheduled& operator=(const SetpointManagerScheduled&) = default;
  SetpointManagerScheduled& operator=(SetpointManagerScheduled&&) = default;

  static IddObjectType iddObjectType();

  bool hasSchedule() const;
  boost::optional<ModelObject> scheduleAsModelObject() const;

 protected:
  using ImplType = detail::SetpointManagerScheduled_Impl;

  friend class Model;

  explicit SetpointManagerScheduled(std::shared_ptr<detail::SetpointManagerScheduled_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
