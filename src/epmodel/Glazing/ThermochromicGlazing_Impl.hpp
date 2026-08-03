/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOCHROMICGLAZING_IMPL_HPP
#define EPMODEL_THERMOCHROMICGLAZING_IMPL_HPP

#include "Glazing/Glazing_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermochromicGlazing_Impl : public Glazing_Impl
    {
     public:
      using Glazing_Impl::Glazing_Impl;
      virtual ~ThermochromicGlazing_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_THERMOCHROMICGLAZING_IMPL_HPP
