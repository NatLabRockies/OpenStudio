/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEFILESHADING_IMPL_HPP
#define EPMODEL_SCHEDULEFILESHADING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ScheduleFileShading_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ScheduleFileShading_Impl() override = default;

  std::string fileName() const;
  bool setFileName(const std::string& fileName);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
