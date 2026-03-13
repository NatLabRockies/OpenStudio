/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYSURROUNDINGSURFACES_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYSURROUNDINGSURFACES_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API SurfacePropertySurroundingSurfaces_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertySurroundingSurfaces_Impl() override = default;

      boost::optional<double> skyViewFactor() const;
      bool setSkyViewFactor(double skyViewFactor);
      bool isSkyViewFactorAutocalculated() const;
      void autocalculateSkyViewFactor();

      boost::optional<double> groundViewFactor() const;
      bool setGroundViewFactor(double groundViewFactor);
      bool isGroundViewFactorAutocalculated() const;
      void autocalculateGroundViewFactor();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
