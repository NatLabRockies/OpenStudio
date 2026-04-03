/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULE_IMPL_HPP
#define EPMODEL_SCHEDULE_IMPL_HPP

#include "ModelObject_Impl.hpp"
#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
class ScheduleTypeLimits;
namespace detail {

class EPMODEL_API Schedule_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~Schedule_Impl() override = default;

  boost::optional<openstudio::epmodel::ScheduleTypeLimits> scheduleTypeLimits() const;
  bool setScheduleTypeLimits(const openstudio::epmodel::ScheduleTypeLimits& scheduleTypeLimits);
  bool resetScheduleTypeLimits();

 private:
  boost::optional<unsigned> scheduleTypeLimitsFieldIndex() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
