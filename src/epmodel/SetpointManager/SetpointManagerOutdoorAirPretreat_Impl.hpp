/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_IMPL_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRPRETREAT_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerOutdoorAirPretreat_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerOutdoorAirPretreat_Impl() override = default;

  double minimumSetpointTemperature() const;
  bool isMinimumSetpointTemperatureDefaulted() const;
  double maximumSetpointTemperature() const;
  bool isMaximumSetpointTemperatureDefaulted() const;
  double minimumSetpointHumidityRatio() const;
  bool isMinimumSetpointHumidityRatioDefaulted() const;
  double maximumSetpointHumidityRatio() const;
  bool isMaximumSetpointHumidityRatioDefaulted() const;

  void resetControlVariable();

  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
  void resetMinimumSetpointTemperature();
  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
  void resetMaximumSetpointTemperature();
  bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
  void resetMinimumSetpointHumidityRatio();
  bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
  void resetMaximumSetpointHumidityRatio();

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
