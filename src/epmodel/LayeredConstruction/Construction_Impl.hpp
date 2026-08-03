/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTION_IMPL_HPP
#define EPMODEL_CONSTRUCTION_IMPL_HPP

#include "LayeredConstruction/LayeredConstruction_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Construction_Impl : public LayeredConstruction_Impl
    {
     public:
      using LayeredConstruction_Impl::LayeredConstruction_Impl;
      virtual ~Construction_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
