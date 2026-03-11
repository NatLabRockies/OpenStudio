/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULECONSTANT_IMPL_HPP
#define EPMODEL_SCHEDULECONSTANT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ScheduleConstant_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ScheduleConstant_Impl() override = default;

  double value() const;
  bool setValue(double value);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
