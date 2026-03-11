/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerSystemNodeResetTemperature_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerSystemNodeResetTemperature_Impl() override = default;

  double setpointatLowReferenceTemperature() const;
  double setpointatHighReferenceTemperature() const;
  double lowReferenceTemperature() const;
  double highReferenceTemperature() const;

  bool setSetpointatLowReferenceTemperature(double setpointatLowReferenceTemperature);
  bool setSetpointatHighReferenceTemperature(double setpointatHighReferenceTemperature);
  bool setLowReferenceTemperature(double lowReferenceTemperature);
  bool setHighReferenceTemperature(double highReferenceTemperature);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
