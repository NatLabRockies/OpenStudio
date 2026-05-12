/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULECOMPACT_IMPL_HPP
#define EPMODEL_SCHEDULECOMPACT_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ScheduleCompact_Impl : public Schedule_Impl
    {
     public:
      using Schedule_Impl::Schedule_Impl;
      virtual ~ScheduleCompact_Impl() override = default;

      /** @name Constant value scalar accessors */
      //@{
      bool setToConstantValue(double value);
      bool isConstantValue() const;
      boost::optional<double> constantValue() const;
      //@}

     protected:
      boost::optional<unsigned> scheduleTypeLimitsFieldIndex() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
