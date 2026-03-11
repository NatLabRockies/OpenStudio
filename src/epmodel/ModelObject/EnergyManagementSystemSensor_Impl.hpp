/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMSENSOR_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMSENSOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API EnergyManagementSystemSensor_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EnergyManagementSystemSensor_Impl() override = default;

  boost::optional<std::string> keyName() const;
  bool setKeyName(const std::string& keyName);
  void resetKeyName();

  std::string outputVariableOrMeterName() const;
  bool setOutputVariableOrMeterName(const std::string& outputVariableOrMeterName);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
