/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSCHEDULED_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSCHEDULED_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerScheduled_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerScheduled_Impl() override = default;

  bool isControlVariableDefaulted() const;
  void resetControlVariable();

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
