/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerSystemNodeResetHumidity_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerSystemNodeResetHumidity_Impl() override = default;

  double setpointatLowReferenceHumidityRatio() const;
  double setpointatHighReferenceHumidityRatio() const;
  double lowReferenceHumidityRatio() const;
  double highReferenceHumidityRatio() const;

  bool setSetpointatLowReferenceHumidityRatio(double setpointatLowReferenceHumidityRatio);
  bool setSetpointatHighReferenceHumidityRatio(double setpointatHighReferenceHumidityRatio);
  bool setLowReferenceHumidityRatio(double lowReferenceHumidityRatio);
  bool setHighReferenceHumidityRatio(double highReferenceHumidityRatio);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
