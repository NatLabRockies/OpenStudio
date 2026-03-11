/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHEATING_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHEATING_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerSingleZoneHeating_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerSingleZoneHeating_Impl() override = default;

  double minimumSupplyAirTemperature() const;
  double maximumSupplyAirTemperature() const;

  bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);
  bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
