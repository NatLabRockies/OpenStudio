/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDEBUGGINGDATA_IMPL_HPP
#define EPMODEL_OUTPUTDEBUGGINGDATA_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputDebuggingData_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputDebuggingData_Impl() override = default;

  bool reportDebuggingData() const;
  bool reportDuringWarmup() const;

  bool setReportDebuggingData(bool reportDebuggingData);
  bool setReportDuringWarmup(bool reportDuringWarmup);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
