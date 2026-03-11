/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYLOCALENVIRONMENT_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYLOCALENVIRONMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyLocalEnvironment_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyLocalEnvironment_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
