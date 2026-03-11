/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API SetpointManagerFollowGroundTemperature_Impl : public SetpointManager_Impl
{
 public:
  using SetpointManager_Impl::SetpointManager_Impl;
  virtual ~SetpointManagerFollowGroundTemperature_Impl() override = default;

  std::string referenceGroundTemperatureObjectType() const;
  double offsetTemperatureDifference() const;
  double maximumSetpointTemperature() const;
  double minimumSetpointTemperature() const;

  bool setReferenceGroundTemperatureObjectType(const std::string& groundTemperatureObjType);
  bool setOffsetTemperatureDifference(double offsetTemperatureDifference);
  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

 protected:
  unsigned setpointNodeFieldIndex() const override;
  unsigned controlVariableFieldIndex() const override;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
