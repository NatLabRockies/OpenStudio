/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTTABLESUMMARYREPORTS_IMPL_HPP
#define EPMODEL_OUTPUTTABLESUMMARYREPORTS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API OutputTableSummaryReports_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~OutputTableSummaryReports_Impl() override = default;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
