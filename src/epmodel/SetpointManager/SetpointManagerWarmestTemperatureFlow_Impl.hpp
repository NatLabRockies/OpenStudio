/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERWARMESTTEMPERATUREFLOW_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERWARMESTTEMPERATUREFLOW_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerWarmestTemperatureFlow_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerWarmestTemperatureFlow_Impl() override = default;

  double minimumSetpointTemperature() const;
  double maximumSetpointTemperature() const;
  std::string strategy() const;
  double minimumTurndownRatio() const;

  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
  bool setStrategy(const std::string& strategy);
  bool setMinimumTurndownRatio(double minimumTurndownRatio);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
