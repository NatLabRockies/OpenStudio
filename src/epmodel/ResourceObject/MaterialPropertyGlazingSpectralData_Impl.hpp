/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYGLAZINGSPECTRALDATA_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYGLAZINGSPECTRALDATA_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyGlazingSpectralData_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyGlazingSpectralData_Impl() override = default;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
