/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_IMPL_HPP

#include "AvailabilityManager_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class AirLoopHVAC;

namespace detail {

class EPMODEL_API AvailabilityManagerNightCycle_Impl : public AvailabilityManager_Impl
{
 public:
  using AvailabilityManager_Impl::AvailabilityManager_Impl;
  virtual ~AvailabilityManagerNightCycle_Impl() override = default;

  boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;

  std::string controlType() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();
  bool isControlTypeDefaulted() const;

  std::vector<std::string> controlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
