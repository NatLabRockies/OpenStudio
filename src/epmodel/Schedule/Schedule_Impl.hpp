/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULE_IMPL_HPP
#define EPMODEL_SCHEDULE_IMPL_HPP

#include "ScheduleBase/ScheduleBase_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API Schedule_Impl : public ScheduleBase_Impl
    {
     public:
      using ScheduleBase_Impl::ScheduleBase_Impl;
      virtual ~Schedule_Impl() override = default;

      std::vector<double> values() const override;
      void ensureNoLeapDays() override;

     protected:
      virtual unsigned scheduleTypeLimitsFieldIndex() const = 0;
      bool candidateIsCompatibleWithCurrentUse(const ScheduleTypeLimits& candidate) const override;
      bool okToResetScheduleTypeLimits() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
