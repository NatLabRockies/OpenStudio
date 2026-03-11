/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULECOMPACT_IMPL_HPP
#define EPMODEL_SCHEDULECOMPACT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ScheduleCompact_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ScheduleCompact_Impl() override = default;

  bool setToConstantValue(double value);
  bool isConstantValue() const;
  boost::optional<double> constantValue() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
