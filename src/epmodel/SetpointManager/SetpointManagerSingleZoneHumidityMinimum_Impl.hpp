/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMINIMUM_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHUMIDITYMINIMUM_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerSingleZoneHumidityMinimum_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerSingleZoneHumidityMinimum_Impl() override = default;

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
