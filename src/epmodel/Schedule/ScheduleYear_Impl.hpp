/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEYEAR_IMPL_HPP
#define EPMODEL_SCHEDULEYEAR_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ScheduleYear_Impl : public Schedule_Impl
    {
     public:
      using Schedule_Impl::Schedule_Impl;
      virtual ~ScheduleYear_Impl() override = default;

     protected:
      boost::optional<unsigned> scheduleTypeLimitsFieldIndex() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
