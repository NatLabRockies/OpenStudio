/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API EnergyManagementSystemProgramCallingManager_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~EnergyManagementSystemProgramCallingManager_Impl() override = default;

  std::vector<std::string> validCallingPointValues() const;

  std::string callingPoint() const;
  bool setCallingPoint(const std::string& callingPoint);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
