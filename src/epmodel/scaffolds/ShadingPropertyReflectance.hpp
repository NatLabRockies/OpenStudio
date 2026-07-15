/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGPROPERTYREFLECTANCE_HPP
#define EPMODEL_SHADINGPROPERTYREFLECTANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ShadingPropertyReflectance_Impl;
  }

  class EPMODEL_API ShadingPropertyReflectance : public ModelObject
  {
   public:
    explicit ShadingPropertyReflectance(const Model& model);

    virtual ~ShadingPropertyReflectance() override = default;
    ShadingPropertyReflectance(const ShadingPropertyReflectance& other) = default;
    ShadingPropertyReflectance(ShadingPropertyReflectance&& other) = default;
    ShadingPropertyReflectance& operator=(const ShadingPropertyReflectance&) = default;
    ShadingPropertyReflectance& operator=(ShadingPropertyReflectance&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs below map directly to EnergyPlus ShadingProperty:Reflectance numeric fields.
    // - Field Mapping: Name is inherited from ModelObject scalar API and maps to ShadingProperty:Reflectance / Name.
    // - ForwardTranslator Evidence: ForwardTranslateShadingSurface writes this object's Shading Surface Name relationship
    //   and conditionally writes scalar fields from shading construction/material reflectance.
    // - TODO(parity): Add relationship APIs for Shading Surface Name and Glazing Construction Name when relationship parity is in scope.
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

   protected:
    using ImplType = detail::ShadingPropertyReflectance_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ShadingPropertyReflectance(std::shared_ptr<detail::ShadingPropertyReflectance_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
