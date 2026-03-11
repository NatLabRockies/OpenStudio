/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONECOOLINGAVERAGE_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONECOOLINGAVERAGE_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerMultiZoneCoolingAverage_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerMultiZoneCoolingAverage_Impl() override = default;

  double minimumSetpointTemperature() const;
  double maximumSetpointTemperature() const;

  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
