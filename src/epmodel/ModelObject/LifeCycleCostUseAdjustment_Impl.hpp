/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTUSEADJUSTMENT_IMPL_HPP
#define EPMODEL_LIFECYCLECOSTUSEADJUSTMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API LifeCycleCostUseAdjustment_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~LifeCycleCostUseAdjustment_Impl() override = default;

  std::string resource() const;

  bool setResource(const std::string& resource);

  std::vector<std::string> resourceValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
