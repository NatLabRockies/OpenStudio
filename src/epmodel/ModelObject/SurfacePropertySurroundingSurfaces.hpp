/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYSURROUNDINGSURFACES_HPP
#define EPMODEL_SURFACEPROPERTYSURROUNDINGSURFACES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertySurroundingSurfaces_Impl;
  }

  class EPMODEL_API SurfacePropertySurroundingSurfaces : public ModelObject
  {
   public:
    explicit SurfacePropertySurroundingSurfaces(const Model& model);

    virtual ~SurfacePropertySurroundingSurfaces() override = default;
    SurfacePropertySurroundingSurfaces(const SurfacePropertySurroundingSurfaces& other) = default;
    SurfacePropertySurroundingSurfaces(SurfacePropertySurroundingSurfaces&& other) = default;
    SurfacePropertySurroundingSurfaces& operator=(const SurfacePropertySurroundingSurfaces&) = default;
    SurfacePropertySurroundingSurfaces& operator=(SurfacePropertySurroundingSurfaces&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves the openstudio::model scalar API names (skyViewFactor / groundViewFactor plus autocalculate helpers) while keeping the object-name API on ModelObject.
    // - Field Mapping: ForwardTranslateSurfacePropertySurroundingSurfaces.cpp proves that skyViewFactor and groundViewFactor map directly to
    //   EnergyPlus SurfaceProperty_SurroundingSurfaces fields SkyViewFactor and GroundViewFactor.
    // - Field Mapping: SkyTemperatureScheduleName, GroundTemperatureScheduleName, and the SurroundingSurface extensible groups are relationship fields
    //   (schedule pointers and extensible links) and are intentionally excluded from the scalar API surface here.
    boost::optional<double> skyViewFactor() const;
    bool isSkyViewFactorAutocalculated() const;
    bool setSkyViewFactor(double skyViewFactor);
    void autocalculateSkyViewFactor();

    boost::optional<double> groundViewFactor() const;
    bool isGroundViewFactorAutocalculated() const;
    bool setGroundViewFactor(double groundViewFactor);
    void autocalculateGroundViewFactor();

   protected:
    using ImplType = detail::SurfacePropertySurroundingSurfaces_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertySurroundingSurfaces(std::shared_ptr<detail::SurfacePropertySurroundingSurfaces_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
