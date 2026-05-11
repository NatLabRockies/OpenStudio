/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LAYEREDCONSTRUCTION_IMPL_HPP
#define EPMODEL_LAYEREDCONSTRUCTION_IMPL_HPP

#include "ConstructionBase/ConstructionBase_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API LayeredConstruction_Impl : public ConstructionBase_Impl
    {
     public:
      using ConstructionBase_Impl::ConstructionBase_Impl;
      virtual ~LayeredConstruction_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
