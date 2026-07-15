/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGPROPERTYREFLECTANCE_IMPL_HPP
#define EPMODEL_SHADINGPROPERTYREFLECTANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ShadingPropertyReflectance_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ShadingPropertyReflectance_Impl() override = default;

      double diffuseSolarReflectanceofUnglazedPartofShadingSurface() const;
      bool isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted() const;
      bool setDiffuseSolarReflectanceofUnglazedPartofShadingSurface(double diffuseSolarReflectanceofUnglazedPartofShadingSurface);
      void resetDiffuseSolarReflectanceofUnglazedPartofShadingSurface();

      double diffuseVisibleReflectanceofUnglazedPartofShadingSurface() const;
      bool isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted() const;
      bool setDiffuseVisibleReflectanceofUnglazedPartofShadingSurface(double diffuseVisibleReflectanceofUnglazedPartofShadingSurface);
      void resetDiffuseVisibleReflectanceofUnglazedPartofShadingSurface();

      double fractionofShadingSurfaceThatIsGlazed() const;
      bool isFractionofShadingSurfaceThatIsGlazedDefaulted() const;
      bool setFractionofShadingSurfaceThatIsGlazed(double fractionofShadingSurfaceThatIsGlazed);
      void resetFractionofShadingSurfaceThatIsGlazed();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
