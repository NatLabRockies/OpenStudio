/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAY_IMPL_HPP
#define EPMODEL_SCHEDULEDAY_IMPL_HPP

#include "ScheduleBase/ScheduleBase_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ScheduleDay_Impl : public ScheduleBase_Impl
    {
     public:
      using ScheduleBase_Impl::ScheduleBase_Impl;
      virtual ~ScheduleDay_Impl() override = default;

      std::string interpolatetoTimestep() const;
      bool setInterpolatetoTimestep(const std::string& interpolatetoTimestep);
      bool isInterpolatetoTimestepDefaulted() const;
      void resetInterpolatetoTimestep();

      std::vector<double> values() const override;
      void ensureNoLeapDays() override;

     protected:
      boost::optional<unsigned> scheduleTypeLimitsFieldIndex() const override;
      bool candidateIsCompatibleWithCurrentUse(const ScheduleTypeLimits& candidate) const override;
      bool okToResetScheduleTypeLimits() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
