/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_IMPL_HPP
#define EPMODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API RunPeriodControlDaylightSavingTime_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~RunPeriodControlDaylightSavingTime_Impl() override = default;

  std::string startDate() const;
  std::string endDate() const;

  bool setStartDate(const std::string& startDate);
  bool setEndDate(const std::string& endDate);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
