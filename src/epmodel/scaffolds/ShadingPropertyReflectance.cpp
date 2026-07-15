/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingPropertyReflectance.hpp"
#include "ShadingPropertyReflectance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ShadingProperty_Reflectance_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ShadingPropertyReflectance::ShadingPropertyReflectance(const Model& model) : ModelObject(ShadingPropertyReflectance::iddObjectType(), model) {}

  ShadingPropertyReflectance::ShadingPropertyReflectance(std::shared_ptr<detail::ShadingPropertyReflectance_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ShadingPropertyReflectance::iddObjectType() {
    return IddObjectType::ShadingProperty_Reflectance;
  }

  double ShadingPropertyReflectance::diffuseSolarReflectanceofUnglazedPartofShadingSurface() const {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->diffuseSolarReflectanceofUnglazedPartofShadingSurface();
  }

  bool ShadingPropertyReflectance::isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted() const {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted();
  }

  bool ShadingPropertyReflectance::setDiffuseSolarReflectanceofUnglazedPartofShadingSurface(
    double diffuseSolarReflectanceofUnglazedPartofShadingSurface) {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->setDiffuseSolarReflectanceofUnglazedPartofShadingSurface(
      diffuseSolarReflectanceofUnglazedPartofShadingSurface);
  }

  void ShadingPropertyReflectance::resetDiffuseSolarReflectanceofUnglazedPartofShadingSurface() {
    getImpl<detail::ShadingPropertyReflectance_Impl>()->resetDiffuseSolarReflectanceofUnglazedPartofShadingSurface();
  }

  double ShadingPropertyReflectance::diffuseVisibleReflectanceofUnglazedPartofShadingSurface() const {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->diffuseVisibleReflectanceofUnglazedPartofShadingSurface();
  }

  bool ShadingPropertyReflectance::isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted() const {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted();
  }

  bool ShadingPropertyReflectance::setDiffuseVisibleReflectanceofUnglazedPartofShadingSurface(
    double diffuseVisibleReflectanceofUnglazedPartofShadingSurface) {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->setDiffuseVisibleReflectanceofUnglazedPartofShadingSurface(
      diffuseVisibleReflectanceofUnglazedPartofShadingSurface);
  }

  void ShadingPropertyReflectance::resetDiffuseVisibleReflectanceofUnglazedPartofShadingSurface() {
    getImpl<detail::ShadingPropertyReflectance_Impl>()->resetDiffuseVisibleReflectanceofUnglazedPartofShadingSurface();
  }

  double ShadingPropertyReflectance::fractionofShadingSurfaceThatIsGlazed() const {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->fractionofShadingSurfaceThatIsGlazed();
  }

  bool ShadingPropertyReflectance::isFractionofShadingSurfaceThatIsGlazedDefaulted() const {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->isFractionofShadingSurfaceThatIsGlazedDefaulted();
  }

  bool ShadingPropertyReflectance::setFractionofShadingSurfaceThatIsGlazed(double fractionofShadingSurfaceThatIsGlazed) {
    return getImpl<detail::ShadingPropertyReflectance_Impl>()->setFractionofShadingSurfaceThatIsGlazed(fractionofShadingSurfaceThatIsGlazed);
  }

  void ShadingPropertyReflectance::resetFractionofShadingSurfaceThatIsGlazed() {
    getImpl<detail::ShadingPropertyReflectance_Impl>()->resetFractionofShadingSurfaceThatIsGlazed();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ShadingPropertyReflectance_Impl::diffuseSolarReflectanceofUnglazedPartofShadingSurface() const {
      const auto value = getDouble(openstudio::ShadingProperty_ReflectanceFields::DiffuseSolarReflectanceofUnglazedPartofShadingSurface, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingPropertyReflectance_Impl::isDiffuseSolarReflectanceofUnglazedPartofShadingSurfaceDefaulted() const {
      return !getDouble(openstudio::ShadingProperty_ReflectanceFields::DiffuseSolarReflectanceofUnglazedPartofShadingSurface, false);
    }

    bool ShadingPropertyReflectance_Impl::setDiffuseSolarReflectanceofUnglazedPartofShadingSurface(
      double diffuseSolarReflectanceofUnglazedPartofShadingSurface) {
      return setDouble(openstudio::ShadingProperty_ReflectanceFields::DiffuseSolarReflectanceofUnglazedPartofShadingSurface,
                       diffuseSolarReflectanceofUnglazedPartofShadingSurface);
    }

    void ShadingPropertyReflectance_Impl::resetDiffuseSolarReflectanceofUnglazedPartofShadingSurface() {
      OS_ASSERT(setString(openstudio::ShadingProperty_ReflectanceFields::DiffuseSolarReflectanceofUnglazedPartofShadingSurface, ""));
    }

    double ShadingPropertyReflectance_Impl::diffuseVisibleReflectanceofUnglazedPartofShadingSurface() const {
      const auto value = getDouble(openstudio::ShadingProperty_ReflectanceFields::DiffuseVisibleReflectanceofUnglazedPartofShadingSurface, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingPropertyReflectance_Impl::isDiffuseVisibleReflectanceofUnglazedPartofShadingSurfaceDefaulted() const {
      return !getDouble(openstudio::ShadingProperty_ReflectanceFields::DiffuseVisibleReflectanceofUnglazedPartofShadingSurface, false);
    }

    bool ShadingPropertyReflectance_Impl::setDiffuseVisibleReflectanceofUnglazedPartofShadingSurface(
      double diffuseVisibleReflectanceofUnglazedPartofShadingSurface) {
      return setDouble(openstudio::ShadingProperty_ReflectanceFields::DiffuseVisibleReflectanceofUnglazedPartofShadingSurface,
                       diffuseVisibleReflectanceofUnglazedPartofShadingSurface);
    }

    void ShadingPropertyReflectance_Impl::resetDiffuseVisibleReflectanceofUnglazedPartofShadingSurface() {
      OS_ASSERT(setString(openstudio::ShadingProperty_ReflectanceFields::DiffuseVisibleReflectanceofUnglazedPartofShadingSurface, ""));
    }

    double ShadingPropertyReflectance_Impl::fractionofShadingSurfaceThatIsGlazed() const {
      const auto value = getDouble(openstudio::ShadingProperty_ReflectanceFields::FractionofShadingSurfaceThatIsGlazed, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ShadingPropertyReflectance_Impl::isFractionofShadingSurfaceThatIsGlazedDefaulted() const {
      return !getDouble(openstudio::ShadingProperty_ReflectanceFields::FractionofShadingSurfaceThatIsGlazed, false);
    }

    bool ShadingPropertyReflectance_Impl::setFractionofShadingSurfaceThatIsGlazed(double fractionofShadingSurfaceThatIsGlazed) {
      return setDouble(openstudio::ShadingProperty_ReflectanceFields::FractionofShadingSurfaceThatIsGlazed, fractionofShadingSurfaceThatIsGlazed);
    }

    void ShadingPropertyReflectance_Impl::resetFractionofShadingSurfaceThatIsGlazed() {
      OS_ASSERT(setString(openstudio::ShadingProperty_ReflectanceFields::FractionofShadingSurfaceThatIsGlazed, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
