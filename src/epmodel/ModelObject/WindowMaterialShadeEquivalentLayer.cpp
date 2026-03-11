/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowMaterialShadeEquivalentLayer.hpp"
#include "WindowMaterialShadeEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowMaterial_Shade_EquivalentLayer_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialShadeEquivalentLayer::WindowMaterialShadeEquivalentLayer(const Model& model)
    : ModelObject(WindowMaterialShadeEquivalentLayer::iddObjectType(), model) {}

  WindowMaterialShadeEquivalentLayer::WindowMaterialShadeEquivalentLayer(std::shared_ptr<detail::WindowMaterialShadeEquivalentLayer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialShadeEquivalentLayer::iddObjectType() {
    return IddObjectType::WindowMaterial_Shade_EquivalentLayer;
  }

  double WindowMaterialShadeEquivalentLayer::shadeBeamBeamSolarTransmittance() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->shadeBeamBeamSolarTransmittance();
  }

  bool WindowMaterialShadeEquivalentLayer::isShadeBeamBeamSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->isShadeBeamBeamSolarTransmittanceDefaulted();
  }

  double WindowMaterialShadeEquivalentLayer::frontSideShadeBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->frontSideShadeBeamDiffuseSolarTransmittance();
  }

  double WindowMaterialShadeEquivalentLayer::backSideShadeBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->backSideShadeBeamDiffuseSolarTransmittance();
  }

  double WindowMaterialShadeEquivalentLayer::frontSideShadeBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->frontSideShadeBeamDiffuseSolarReflectance();
  }

  double WindowMaterialShadeEquivalentLayer::backSideShadeBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->backSideShadeBeamDiffuseSolarReflectance();
  }

  boost::optional<double> WindowMaterialShadeEquivalentLayer::shadeBeamBeamVisibleTransmittanceAtNormalIncidence() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->shadeBeamBeamVisibleTransmittanceAtNormalIncidence();
  }

  boost::optional<double> WindowMaterialShadeEquivalentLayer::shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence();
  }

  boost::optional<double> WindowMaterialShadeEquivalentLayer::shadeBeamDiffuseVisibleReflectanceAtNormalIncidence() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->shadeBeamDiffuseVisibleReflectanceAtNormalIncidence();
  }

  double WindowMaterialShadeEquivalentLayer::shadeMaterialInfraredTransmittance() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->shadeMaterialInfraredTransmittance();
  }

  bool WindowMaterialShadeEquivalentLayer::isShadeMaterialInfraredTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->isShadeMaterialInfraredTransmittanceDefaulted();
  }

  double WindowMaterialShadeEquivalentLayer::frontSideShadeMaterialInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->frontSideShadeMaterialInfraredEmissivity();
  }

  bool WindowMaterialShadeEquivalentLayer::isFrontSideShadeMaterialInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->isFrontSideShadeMaterialInfraredEmissivityDefaulted();
  }

  double WindowMaterialShadeEquivalentLayer::backSideShadeMaterialInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->backSideShadeMaterialInfraredEmissivity();
  }

  bool WindowMaterialShadeEquivalentLayer::isBackSideShadeMaterialInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->isBackSideShadeMaterialInfraredEmissivityDefaulted();
  }

  bool WindowMaterialShadeEquivalentLayer::setShadeBeamBeamSolarTransmittance(double shadeBeamBeamSolarTransmittance) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setShadeBeamBeamSolarTransmittance(shadeBeamBeamSolarTransmittance);
  }

  bool WindowMaterialShadeEquivalentLayer::setFrontSideShadeBeamDiffuseSolarTransmittance(double frontSideShadeBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setFrontSideShadeBeamDiffuseSolarTransmittance(
      frontSideShadeBeamDiffuseSolarTransmittance);
  }

  bool WindowMaterialShadeEquivalentLayer::setBackSideShadeBeamDiffuseSolarTransmittance(double backSideShadeBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setBackSideShadeBeamDiffuseSolarTransmittance(
      backSideShadeBeamDiffuseSolarTransmittance);
  }

  bool WindowMaterialShadeEquivalentLayer::setFrontSideShadeBeamDiffuseSolarReflectance(double frontSideShadeBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setFrontSideShadeBeamDiffuseSolarReflectance(
      frontSideShadeBeamDiffuseSolarReflectance);
  }

  bool WindowMaterialShadeEquivalentLayer::setBackSideShadeBeamDiffuseSolarReflectance(double backSideShadeBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setBackSideShadeBeamDiffuseSolarReflectance(
      backSideShadeBeamDiffuseSolarReflectance);
  }

  bool WindowMaterialShadeEquivalentLayer::setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(
    double shadeBeamBeamVisibleTransmittanceAtNormalIncidence) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(
      shadeBeamBeamVisibleTransmittanceAtNormalIncidence);
  }

  bool WindowMaterialShadeEquivalentLayer::setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(
    double shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(
      shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence);
  }

  bool WindowMaterialShadeEquivalentLayer::setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(
    double shadeBeamDiffuseVisibleReflectanceAtNormalIncidence) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(
      shadeBeamDiffuseVisibleReflectanceAtNormalIncidence);
  }

  bool WindowMaterialShadeEquivalentLayer::setShadeMaterialInfraredTransmittance(double shadeMaterialInfraredTransmittance) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setShadeMaterialInfraredTransmittance(shadeMaterialInfraredTransmittance);
  }

  bool WindowMaterialShadeEquivalentLayer::setFrontSideShadeMaterialInfraredEmissivity(double frontSideShadeMaterialInfraredEmissivity) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setFrontSideShadeMaterialInfraredEmissivity(
      frontSideShadeMaterialInfraredEmissivity);
  }

  bool WindowMaterialShadeEquivalentLayer::setBackSideShadeMaterialInfraredEmissivity(double backSideShadeMaterialInfraredEmissivity) {
    return getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->setBackSideShadeMaterialInfraredEmissivity(
      backSideShadeMaterialInfraredEmissivity);
  }

  void WindowMaterialShadeEquivalentLayer::resetShadeBeamBeamSolarTransmittance() {
    getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->resetShadeBeamBeamSolarTransmittance();
  }

  void WindowMaterialShadeEquivalentLayer::resetShadeMaterialInfraredTransmittance() {
    getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->resetShadeMaterialInfraredTransmittance();
  }

  void WindowMaterialShadeEquivalentLayer::resetFrontSideShadeMaterialInfraredEmissivity() {
    getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->resetFrontSideShadeMaterialInfraredEmissivity();
  }

  void WindowMaterialShadeEquivalentLayer::resetBackSideShadeMaterialInfraredEmissivity() {
    getImpl<detail::WindowMaterialShadeEquivalentLayer_Impl>()->resetBackSideShadeMaterialInfraredEmissivity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowMaterialShadeEquivalentLayer_Impl::shadeBeamBeamSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::isShadeBeamBeamSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamSolarTransmittance);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setShadeBeamBeamSolarTransmittance(double shadeBeamBeamSolarTransmittance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamSolarTransmittance, shadeBeamBeamSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialShadeEquivalentLayer_Impl::resetShadeBeamBeamSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamSolarTransmittance, ""));
    }

    double WindowMaterialShadeEquivalentLayer_Impl::frontSideShadeBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setFrontSideShadeBeamDiffuseSolarTransmittance(double frontSideShadeBeamDiffuseSolarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeBeamDiffuseSolarTransmittance,
                                    frontSideShadeBeamDiffuseSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialShadeEquivalentLayer_Impl::backSideShadeBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setBackSideShadeBeamDiffuseSolarTransmittance(double backSideShadeBeamDiffuseSolarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeBeamDiffuseSolarTransmittance,
                                    backSideShadeBeamDiffuseSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialShadeEquivalentLayer_Impl::frontSideShadeBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setFrontSideShadeBeamDiffuseSolarReflectance(double frontSideShadeBeamDiffuseSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeBeamDiffuseSolarReflectance,
                                    frontSideShadeBeamDiffuseSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialShadeEquivalentLayer_Impl::backSideShadeBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setBackSideShadeBeamDiffuseSolarReflectance(double backSideShadeBeamDiffuseSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeBeamDiffuseSolarReflectance,
                                    backSideShadeBeamDiffuseSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> WindowMaterialShadeEquivalentLayer_Impl::shadeBeamBeamVisibleTransmittanceAtNormalIncidence() const {
      return getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamVisibleTransmittanceatNormalIncidence, true);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setShadeBeamBeamVisibleTransmittanceAtNormalIncidence(
      double shadeBeamBeamVisibleTransmittanceAtNormalIncidence) {
      return setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamVisibleTransmittanceatNormalIncidence,
                       shadeBeamBeamVisibleTransmittanceAtNormalIncidence);
    }

    boost::optional<double> WindowMaterialShadeEquivalentLayer_Impl::shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence() const {
      return getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamDiffuseVisibleTransmittanceatNormalIncidence, true);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setShadeBeamDiffuseVisibleTransmittanceAtNormalIncidence(
      double shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence) {
      return setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamDiffuseVisibleTransmittanceatNormalIncidence,
                       shadeBeamDiffuseVisibleTransmittanceAtNormalIncidence);
    }

    boost::optional<double> WindowMaterialShadeEquivalentLayer_Impl::shadeBeamDiffuseVisibleReflectanceAtNormalIncidence() const {
      return getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamDiffuseVisibleReflectanceatNormalIncidence, true);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setShadeBeamDiffuseVisibleReflectanceAtNormalIncidence(
      double shadeBeamDiffuseVisibleReflectanceAtNormalIncidence) {
      return setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamDiffuseVisibleReflectanceatNormalIncidence,
                       shadeBeamDiffuseVisibleReflectanceAtNormalIncidence);
    }

    double WindowMaterialShadeEquivalentLayer_Impl::shadeMaterialInfraredTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeMaterialInfraredTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::isShadeMaterialInfraredTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeMaterialInfraredTransmittance);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setShadeMaterialInfraredTransmittance(double shadeMaterialInfraredTransmittance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeMaterialInfraredTransmittance, shadeMaterialInfraredTransmittance);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialShadeEquivalentLayer_Impl::resetShadeMaterialInfraredTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Shade_EquivalentLayerFields::ShadeMaterialInfraredTransmittance, ""));
    }

    double WindowMaterialShadeEquivalentLayer_Impl::frontSideShadeMaterialInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeMaterialInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::isFrontSideShadeMaterialInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeMaterialInfraredEmissivity);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setFrontSideShadeMaterialInfraredEmissivity(double frontSideShadeMaterialInfraredEmissivity) {
      const bool result = setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeMaterialInfraredEmissivity,
                                    frontSideShadeMaterialInfraredEmissivity);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialShadeEquivalentLayer_Impl::resetFrontSideShadeMaterialInfraredEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeMaterialInfraredEmissivity, ""));
    }

    double WindowMaterialShadeEquivalentLayer_Impl::backSideShadeMaterialInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeMaterialInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::isBackSideShadeMaterialInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeMaterialInfraredEmissivity);
    }

    bool WindowMaterialShadeEquivalentLayer_Impl::setBackSideShadeMaterialInfraredEmissivity(double backSideShadeMaterialInfraredEmissivity) {
      const bool result = setDouble(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeMaterialInfraredEmissivity,
                                    backSideShadeMaterialInfraredEmissivity);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialShadeEquivalentLayer_Impl::resetBackSideShadeMaterialInfraredEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeMaterialInfraredEmissivity, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
