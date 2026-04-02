/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULESET_IMPL_HPP
#define EPMODEL_SCHEDULERULESET_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ScheduleRuleset_Impl : public Schedule_Impl
{
 public:
  using Schedule_Impl::Schedule_Impl;
  virtual ~ScheduleRuleset_Impl() override = default;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
