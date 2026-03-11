/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAYLIST_IMPL_HPP
#define EPMODEL_SCHEDULEDAYLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ScheduleDayList_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ScheduleDayList_Impl() override = default;

  std::string interpolatetoTimestep() const;
  bool isInterpolatetoTimestepDefaulted() const;
  boost::optional<int> minutesperItem() const;

  bool setInterpolatetoTimestep(const std::string& interpolatetoTimestep);
  void resetInterpolatetoTimestep();
  bool setMinutesperItem(int minutesperItem);
  void resetMinutesperItem();

  std::vector<std::string> interpolatetoTimestepValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
