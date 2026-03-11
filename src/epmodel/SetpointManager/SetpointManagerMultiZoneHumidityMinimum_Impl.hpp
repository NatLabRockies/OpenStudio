/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMINIMUM_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMINIMUM_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerMultiZoneHumidityMinimum_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerMultiZoneHumidityMinimum_Impl() override = default;

  double minimumSetpointHumidityRatio() const;
  bool isMinimumSetpointHumidityRatioDefaulted() const;
  double maximumSetpointHumidityRatio() const;
  bool isMaximumSetpointHumidityRatioDefaulted() const;

  bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
  void resetMinimumSetpointHumidityRatio();
  bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
  void resetMaximumSetpointHumidityRatio();

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
