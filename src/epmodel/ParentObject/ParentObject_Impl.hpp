/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PARENTOBJECT_IMPL_HPP
#define EPMODEL_PARENTOBJECT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class ModelObject;

namespace detail {

class EPMODEL_API ParentObject_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ParentObject_Impl() = default;

  virtual std::vector<ModelObject> children() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
