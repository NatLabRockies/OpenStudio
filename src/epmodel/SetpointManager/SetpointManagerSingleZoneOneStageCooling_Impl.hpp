/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGECOOLING_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGECOOLING_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerSingleZoneOneStageCooling_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerSingleZoneOneStageCooling_Impl() override = default;

  double coolingStageOnSupplyAirSetpointTemperature() const;
  double coolingStageOffSupplyAirSetpointTemperature() const;

  bool setCoolingStageOnSupplyAirSetpointTemperature(double coolingStageOnSupplyAirSetpointTemperature);
  bool setCoolingStageOffSupplyAirSetpointTemperature(double coolingStageOffSupplyAirSetpointTemperature);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
