/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertySurroundingSurfaces.hpp"
#include "SurfacePropertySurroundingSurfaces_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceProperty_SurroundingSurfaces_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertySurroundingSurfaces::SurfacePropertySurroundingSurfaces(const Model& model)
    : ModelObject(SurfacePropertySurroundingSurfaces::iddObjectType(), model) {}

  SurfacePropertySurroundingSurfaces::SurfacePropertySurroundingSurfaces(std::shared_ptr<detail::SurfacePropertySurroundingSurfaces_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertySurroundingSurfaces::iddObjectType() {
    return IddObjectType::SurfaceProperty_SurroundingSurfaces;
  }

  boost::optional<double> SurfacePropertySurroundingSurfaces::skyViewFactor() const {
    return getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->skyViewFactor();
  }

  bool SurfacePropertySurroundingSurfaces::isSkyViewFactorAutocalculated() const {
    return getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->isSkyViewFactorAutocalculated();
  }

  bool SurfacePropertySurroundingSurfaces::setSkyViewFactor(double skyViewFactor) {
    return getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->setSkyViewFactor(skyViewFactor);
  }

  void SurfacePropertySurroundingSurfaces::autocalculateSkyViewFactor() {
    getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->autocalculateSkyViewFactor();
  }

  boost::optional<double> SurfacePropertySurroundingSurfaces::groundViewFactor() const {
    return getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->groundViewFactor();
  }

  bool SurfacePropertySurroundingSurfaces::isGroundViewFactorAutocalculated() const {
    return getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->isGroundViewFactorAutocalculated();
  }

  bool SurfacePropertySurroundingSurfaces::setGroundViewFactor(double groundViewFactor) {
    return getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->setGroundViewFactor(groundViewFactor);
  }

  void SurfacePropertySurroundingSurfaces::autocalculateGroundViewFactor() {
    getImpl<detail::SurfacePropertySurroundingSurfaces_Impl>()->autocalculateGroundViewFactor();
  }

  namespace detail {

    boost::optional<double> SurfacePropertySurroundingSurfaces_Impl::skyViewFactor() const {
      return getDouble(openstudio::SurfaceProperty_SurroundingSurfacesFields::SkyViewFactor, true);
    }

    bool SurfacePropertySurroundingSurfaces_Impl::isSkyViewFactorAutocalculated() const {
      return isEmpty(openstudio::SurfaceProperty_SurroundingSurfacesFields::SkyViewFactor);
    }

    bool SurfacePropertySurroundingSurfaces_Impl::setSkyViewFactor(double skyViewFactor) {
      return setDouble(openstudio::SurfaceProperty_SurroundingSurfacesFields::SkyViewFactor, skyViewFactor);
    }

    void SurfacePropertySurroundingSurfaces_Impl::autocalculateSkyViewFactor() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_SurroundingSurfacesFields::SkyViewFactor, ""));
    }

    boost::optional<double> SurfacePropertySurroundingSurfaces_Impl::groundViewFactor() const {
      return getDouble(openstudio::SurfaceProperty_SurroundingSurfacesFields::GroundViewFactor, true);
    }

    bool SurfacePropertySurroundingSurfaces_Impl::isGroundViewFactorAutocalculated() const {
      return isEmpty(openstudio::SurfaceProperty_SurroundingSurfacesFields::GroundViewFactor);
    }

    bool SurfacePropertySurroundingSurfaces_Impl::setGroundViewFactor(double groundViewFactor) {
      return setDouble(openstudio::SurfaceProperty_SurroundingSurfacesFields::GroundViewFactor, groundViewFactor);
    }

    void SurfacePropertySurroundingSurfaces_Impl::autocalculateGroundViewFactor() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_SurroundingSurfacesFields::GroundViewFactor, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
