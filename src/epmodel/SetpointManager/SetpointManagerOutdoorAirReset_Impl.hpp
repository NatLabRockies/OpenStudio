/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_IMPL_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerOutdoorAirReset_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerOutdoorAirReset_Impl() override = default;

  bool isControlVariableDefaulted() const;

  double setpointatOutdoorLowTemperature() const;
  double outdoorLowTemperature() const;
  double setpointatOutdoorHighTemperature() const;
  double outdoorHighTemperature() const;

  boost::optional<double> setpointatOutdoorLowTemperature2() const;
  boost::optional<double> outdoorLowTemperature2() const;
  boost::optional<double> setpointatOutdoorHighTemperature2() const;
  boost::optional<double> outdoorHighTemperature2() const;

  void resetControlVariable();

  bool setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature);
  bool setOutdoorLowTemperature(double outdoorLowTemperature);
  bool setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature);
  bool setOutdoorHighTemperature(double outdoorHighTemperature);

  bool setSetpointatOutdoorLowTemperature2(boost::optional<double> setpointatOutdoorLowTemperature2);
  void resetSetpointatOutdoorLowTemperature2();
  bool setOutdoorLowTemperature2(boost::optional<double> outdoorLowTemperature2);
  void resetOutdoorLowTemperature2();
  bool setSetpointatOutdoorHighTemperature2(boost::optional<double> setpointatOutdoorHighTemperature2);
  void resetSetpointatOutdoorHighTemperature2();
  bool setOutdoorHighTemperature2(boost::optional<double> outdoorHighTemperature2);
  void resetOutdoorHighTemperature2();

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
