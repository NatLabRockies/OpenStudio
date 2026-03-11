/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMAXIMUM_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMAXIMUM_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerMultiZoneHumidityMaximum_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerMultiZoneHumidityMaximum_Impl() override = default;

  double minimumSetpointHumidityRatio() const;
  double maximumSetpointHumidityRatio() const;

  bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
  bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
