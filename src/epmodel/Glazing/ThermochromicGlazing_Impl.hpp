/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOCHROMICGLAZING_IMPL_HPP
#define EPMODEL_THERMOCHROMICGLAZING_IMPL_HPP

#include "Material/Material_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermochromicGlazing_Impl : public Material_Impl
    {
     public:
      using Material_Impl::Material_Impl;
      virtual ~ThermochromicGlazing_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_THERMOCHROMICGLAZING_IMPL_HPP
