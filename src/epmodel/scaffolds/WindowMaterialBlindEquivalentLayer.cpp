/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowMaterialBlindEquivalentLayer.hpp"
#include "WindowMaterialBlindEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WindowMaterial_Blind_EquivalentLayer_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialBlindEquivalentLayer::WindowMaterialBlindEquivalentLayer(const Model& model)
    : ModelObject(WindowMaterialBlindEquivalentLayer::iddObjectType(), model) {
    OS_ASSERT(setSlatWidth(0.01));
    OS_ASSERT(setSlatSeparation(0.02));
    OS_ASSERT(setFrontSideSlatBeamDiffuseSolarReflectance(0.4));
    OS_ASSERT(setBackSideSlatBeamDiffuseSolarReflectance(0.4));
    OS_ASSERT(setFrontSideSlatDiffuseDiffuseSolarReflectance(0.4));
    OS_ASSERT(setBackSideSlatDiffuseDiffuseSolarReflectance(0.4));
  }

  WindowMaterialBlindEquivalentLayer::WindowMaterialBlindEquivalentLayer(std::shared_ptr<detail::WindowMaterialBlindEquivalentLayer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialBlindEquivalentLayer::iddObjectType() {
    return IddObjectType::WindowMaterial_Blind_EquivalentLayer;
  }

  std::vector<std::string> WindowMaterialBlindEquivalentLayer::slatOrientationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatOrientation);
  }

  std::vector<std::string> WindowMaterialBlindEquivalentLayer::slatAngleControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngleControl);
  }

  std::string WindowMaterialBlindEquivalentLayer::slatOrientation() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatOrientation();
  }
  bool WindowMaterialBlindEquivalentLayer::isSlatOrientationDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isSlatOrientationDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatOrientation(const std::string& slatOrientation) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatOrientation(slatOrientation);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatOrientation() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatOrientation();
  }

  double WindowMaterialBlindEquivalentLayer::slatWidth() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatWidth();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatWidth(double slatWidth) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatWidth(slatWidth);
  }

  double WindowMaterialBlindEquivalentLayer::slatSeparation() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatSeparation();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatSeparation(double slatSeparation) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatSeparation(slatSeparation);
  }

  double WindowMaterialBlindEquivalentLayer::slatCrown() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatCrown();
  }
  bool WindowMaterialBlindEquivalentLayer::isSlatCrownDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isSlatCrownDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatCrown(double slatCrown) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatCrown(slatCrown);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatCrown() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatCrown();
  }

  double WindowMaterialBlindEquivalentLayer::slatAngle() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatAngle();
  }
  bool WindowMaterialBlindEquivalentLayer::isSlatAngleDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isSlatAngleDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatAngle(double slatAngle) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatAngle(slatAngle);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatAngle() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatAngle();
  }

  double WindowMaterialBlindEquivalentLayer::frontSideSlatBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatBeamDiffuseSolarTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::isFrontSideSlatBeamDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isFrontSideSlatBeamDiffuseSolarTransmittanceDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatBeamDiffuseSolarTransmittance(double frontSideSlatBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatBeamDiffuseSolarTransmittance(
      frontSideSlatBeamDiffuseSolarTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetFrontSideSlatBeamDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetFrontSideSlatBeamDiffuseSolarTransmittance();
  }

  double WindowMaterialBlindEquivalentLayer::backSideSlatBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatBeamDiffuseSolarTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::isBackSideSlatBeamDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isBackSideSlatBeamDiffuseSolarTransmittanceDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatBeamDiffuseSolarTransmittance(double backSideSlatBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatBeamDiffuseSolarTransmittance(
      backSideSlatBeamDiffuseSolarTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetBackSideSlatBeamDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetBackSideSlatBeamDiffuseSolarTransmittance();
  }

  double WindowMaterialBlindEquivalentLayer::frontSideSlatBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatBeamDiffuseSolarReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatBeamDiffuseSolarReflectance(double frontSideSlatBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatBeamDiffuseSolarReflectance(
      frontSideSlatBeamDiffuseSolarReflectance);
  }

  double WindowMaterialBlindEquivalentLayer::backSideSlatBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatBeamDiffuseSolarReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatBeamDiffuseSolarReflectance(double backSideSlatBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatBeamDiffuseSolarReflectance(
      backSideSlatBeamDiffuseSolarReflectance);
  }

  double WindowMaterialBlindEquivalentLayer::frontSideSlatBeamDiffuseVisibleTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatBeamDiffuseVisibleTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::isFrontSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isFrontSideSlatBeamDiffuseVisibleTransmittanceDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatBeamDiffuseVisibleTransmittance(double frontSideSlatBeamDiffuseVisibleTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatBeamDiffuseVisibleTransmittance(
      frontSideSlatBeamDiffuseVisibleTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetFrontSideSlatBeamDiffuseVisibleTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetFrontSideSlatBeamDiffuseVisibleTransmittance();
  }

  double WindowMaterialBlindEquivalentLayer::backSideSlatBeamDiffuseVisibleTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatBeamDiffuseVisibleTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::isBackSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isBackSideSlatBeamDiffuseVisibleTransmittanceDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatBeamDiffuseVisibleTransmittance(double backSideSlatBeamDiffuseVisibleTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatBeamDiffuseVisibleTransmittance(
      backSideSlatBeamDiffuseVisibleTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetBackSideSlatBeamDiffuseVisibleTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetBackSideSlatBeamDiffuseVisibleTransmittance();
  }

  boost::optional<double> WindowMaterialBlindEquivalentLayer::frontSideSlatBeamDiffuseVisibleReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatBeamDiffuseVisibleReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatBeamDiffuseVisibleReflectance(double frontSideSlatBeamDiffuseVisibleReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatBeamDiffuseVisibleReflectance(
      frontSideSlatBeamDiffuseVisibleReflectance);
  }
  void WindowMaterialBlindEquivalentLayer::resetFrontSideSlatBeamDiffuseVisibleReflectance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetFrontSideSlatBeamDiffuseVisibleReflectance();
  }

  boost::optional<double> WindowMaterialBlindEquivalentLayer::backSideSlatBeamDiffuseVisibleReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatBeamDiffuseVisibleReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatBeamDiffuseVisibleReflectance(double backSideSlatBeamDiffuseVisibleReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatBeamDiffuseVisibleReflectance(
      backSideSlatBeamDiffuseVisibleReflectance);
  }
  void WindowMaterialBlindEquivalentLayer::resetBackSideSlatBeamDiffuseVisibleReflectance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetBackSideSlatBeamDiffuseVisibleReflectance();
  }

  double WindowMaterialBlindEquivalentLayer::slatDiffuseDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatDiffuseDiffuseSolarTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::isSlatDiffuseDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isSlatDiffuseDiffuseSolarTransmittanceDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatDiffuseDiffuseSolarTransmittance(double slatDiffuseDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatDiffuseDiffuseSolarTransmittance(slatDiffuseDiffuseSolarTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatDiffuseDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatDiffuseDiffuseSolarTransmittance();
  }

  double WindowMaterialBlindEquivalentLayer::frontSideSlatDiffuseDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatDiffuseDiffuseSolarReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatDiffuseDiffuseSolarReflectance(double frontSideSlatDiffuseDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatDiffuseDiffuseSolarReflectance(
      frontSideSlatDiffuseDiffuseSolarReflectance);
  }

  double WindowMaterialBlindEquivalentLayer::backSideSlatDiffuseDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatDiffuseDiffuseSolarReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatDiffuseDiffuseSolarReflectance(double backSideSlatDiffuseDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatDiffuseDiffuseSolarReflectance(
      backSideSlatDiffuseDiffuseSolarReflectance);
  }

  boost::optional<double> WindowMaterialBlindEquivalentLayer::slatDiffuseDiffuseVisibleTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatDiffuseDiffuseVisibleTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatDiffuseDiffuseVisibleTransmittance(double slatDiffuseDiffuseVisibleTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatDiffuseDiffuseVisibleTransmittance(
      slatDiffuseDiffuseVisibleTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatDiffuseDiffuseVisibleTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatDiffuseDiffuseVisibleTransmittance();
  }

  boost::optional<double> WindowMaterialBlindEquivalentLayer::frontSideSlatDiffuseDiffuseVisibleReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatDiffuseDiffuseVisibleReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatDiffuseDiffuseVisibleReflectance(double frontSideSlatDiffuseDiffuseVisibleReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatDiffuseDiffuseVisibleReflectance(
      frontSideSlatDiffuseDiffuseVisibleReflectance);
  }
  void WindowMaterialBlindEquivalentLayer::resetFrontSideSlatDiffuseDiffuseVisibleReflectance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetFrontSideSlatDiffuseDiffuseVisibleReflectance();
  }

  boost::optional<double> WindowMaterialBlindEquivalentLayer::backSideSlatDiffuseDiffuseVisibleReflectance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatDiffuseDiffuseVisibleReflectance();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatDiffuseDiffuseVisibleReflectance(double backSideSlatDiffuseDiffuseVisibleReflectance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatDiffuseDiffuseVisibleReflectance(
      backSideSlatDiffuseDiffuseVisibleReflectance);
  }
  void WindowMaterialBlindEquivalentLayer::resetBackSideSlatDiffuseDiffuseVisibleReflectance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetBackSideSlatDiffuseDiffuseVisibleReflectance();
  }

  double WindowMaterialBlindEquivalentLayer::slatInfraredTransmittance() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatInfraredTransmittance();
  }
  bool WindowMaterialBlindEquivalentLayer::isSlatInfraredTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isSlatInfraredTransmittanceDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatInfraredTransmittance(double slatInfraredTransmittance) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatInfraredTransmittance(slatInfraredTransmittance);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatInfraredTransmittance() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatInfraredTransmittance();
  }

  double WindowMaterialBlindEquivalentLayer::frontSideSlatInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->frontSideSlatInfraredEmissivity();
  }
  bool WindowMaterialBlindEquivalentLayer::isFrontSideSlatInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isFrontSideSlatInfraredEmissivityDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setFrontSideSlatInfraredEmissivity(double frontSideSlatInfraredEmissivity) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setFrontSideSlatInfraredEmissivity(frontSideSlatInfraredEmissivity);
  }
  void WindowMaterialBlindEquivalentLayer::resetFrontSideSlatInfraredEmissivity() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetFrontSideSlatInfraredEmissivity();
  }

  double WindowMaterialBlindEquivalentLayer::backSideSlatInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->backSideSlatInfraredEmissivity();
  }
  bool WindowMaterialBlindEquivalentLayer::isBackSideSlatInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isBackSideSlatInfraredEmissivityDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setBackSideSlatInfraredEmissivity(double backSideSlatInfraredEmissivity) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setBackSideSlatInfraredEmissivity(backSideSlatInfraredEmissivity);
  }
  void WindowMaterialBlindEquivalentLayer::resetBackSideSlatInfraredEmissivity() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetBackSideSlatInfraredEmissivity();
  }

  std::string WindowMaterialBlindEquivalentLayer::slatAngleControl() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->slatAngleControl();
  }
  bool WindowMaterialBlindEquivalentLayer::isSlatAngleControlDefaulted() const {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->isSlatAngleControlDefaulted();
  }
  bool WindowMaterialBlindEquivalentLayer::setSlatAngleControl(const std::string& slatAngleControl) {
    return getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->setSlatAngleControl(slatAngleControl);
  }
  void WindowMaterialBlindEquivalentLayer::resetSlatAngleControl() {
    getImpl<detail::WindowMaterialBlindEquivalentLayer_Impl>()->resetSlatAngleControl();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WindowMaterialBlindEquivalentLayer_Impl::slatOrientation() const {
      const auto value = getString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatOrientation, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isSlatOrientationDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatOrientation);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatOrientation(const std::string& slatOrientation) {
      return setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatOrientation, slatOrientation);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatOrientation() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatOrientation, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::slatWidth() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatWidth, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatWidth(double slatWidth) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatWidth, slatWidth);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::slatSeparation() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatSeparation, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatSeparation(double slatSeparation) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatSeparation, slatSeparation);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::slatCrown() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatCrown, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isSlatCrownDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatCrown);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatCrown(double slatCrown) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatCrown, slatCrown);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatCrown() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatCrown, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::slatAngle() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngle, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isSlatAngleDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngle);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatAngle(double slatAngle) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngle, slatAngle);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatAngle() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngle, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isFrontSideSlatBeamDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarTransmittance);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatBeamDiffuseSolarTransmittance(double frontSideSlatBeamDiffuseSolarTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarTransmittance,
                       frontSideSlatBeamDiffuseSolarTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetFrontSideSlatBeamDiffuseSolarTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::backSideSlatBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isBackSideSlatBeamDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarTransmittance);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatBeamDiffuseSolarTransmittance(double backSideSlatBeamDiffuseSolarTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarTransmittance,
                       backSideSlatBeamDiffuseSolarTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetBackSideSlatBeamDiffuseSolarTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatBeamDiffuseSolarReflectance(double frontSideSlatBeamDiffuseSolarReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarReflectance,
                       frontSideSlatBeamDiffuseSolarReflectance);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::backSideSlatBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatBeamDiffuseSolarReflectance(double backSideSlatBeamDiffuseSolarReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarReflectance,
                       backSideSlatBeamDiffuseSolarReflectance);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatBeamDiffuseVisibleTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isFrontSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleTransmittance);
    }
    bool
      WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatBeamDiffuseVisibleTransmittance(double frontSideSlatBeamDiffuseVisibleTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleTransmittance,
                       frontSideSlatBeamDiffuseVisibleTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetFrontSideSlatBeamDiffuseVisibleTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::backSideSlatBeamDiffuseVisibleTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isBackSideSlatBeamDiffuseVisibleTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleTransmittance);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatBeamDiffuseVisibleTransmittance(double backSideSlatBeamDiffuseVisibleTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleTransmittance,
                       backSideSlatBeamDiffuseVisibleTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetBackSideSlatBeamDiffuseVisibleTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleTransmittance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatBeamDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleReflectance, true);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatBeamDiffuseVisibleReflectance(double frontSideSlatBeamDiffuseVisibleReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleReflectance,
                       frontSideSlatBeamDiffuseVisibleReflectance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetFrontSideSlatBeamDiffuseVisibleReflectance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleReflectance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WindowMaterialBlindEquivalentLayer_Impl::backSideSlatBeamDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleReflectance, true);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatBeamDiffuseVisibleReflectance(double backSideSlatBeamDiffuseVisibleReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleReflectance,
                       backSideSlatBeamDiffuseVisibleReflectance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetBackSideSlatBeamDiffuseVisibleReflectance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleReflectance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::slatDiffuseDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isSlatDiffuseDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseSolarTransmittance);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatDiffuseDiffuseSolarTransmittance(double slatDiffuseDiffuseSolarTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseSolarTransmittance,
                       slatDiffuseDiffuseSolarTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatDiffuseDiffuseSolarTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseSolarTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatDiffuseDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatDiffuseDiffuseSolarReflectance(double frontSideSlatDiffuseDiffuseSolarReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseSolarReflectance,
                       frontSideSlatDiffuseDiffuseSolarReflectance);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::backSideSlatDiffuseDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatDiffuseDiffuseSolarReflectance(double backSideSlatDiffuseDiffuseSolarReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseSolarReflectance,
                       backSideSlatDiffuseDiffuseSolarReflectance);
    }

    boost::optional<double> WindowMaterialBlindEquivalentLayer_Impl::slatDiffuseDiffuseVisibleTransmittance() const {
      return getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseVisibleTransmittance, true);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatDiffuseDiffuseVisibleTransmittance(double slatDiffuseDiffuseVisibleTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseVisibleTransmittance,
                       slatDiffuseDiffuseVisibleTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatDiffuseDiffuseVisibleTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseVisibleTransmittance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatDiffuseDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseVisibleReflectance, true);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatDiffuseDiffuseVisibleReflectance(
      double frontSideSlatDiffuseDiffuseVisibleReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseVisibleReflectance,
                       frontSideSlatDiffuseDiffuseVisibleReflectance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetFrontSideSlatDiffuseDiffuseVisibleReflectance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseVisibleReflectance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WindowMaterialBlindEquivalentLayer_Impl::backSideSlatDiffuseDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseVisibleReflectance, true);
    }
    bool
      WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatDiffuseDiffuseVisibleReflectance(double backSideSlatDiffuseDiffuseVisibleReflectance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseVisibleReflectance,
                       backSideSlatDiffuseDiffuseVisibleReflectance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetBackSideSlatDiffuseDiffuseVisibleReflectance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseVisibleReflectance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::slatInfraredTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatInfraredTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isSlatInfraredTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatInfraredTransmittance);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatInfraredTransmittance(double slatInfraredTransmittance) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatInfraredTransmittance, slatInfraredTransmittance);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatInfraredTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatInfraredTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::frontSideSlatInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isFrontSideSlatInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatInfraredEmissivity);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setFrontSideSlatInfraredEmissivity(double frontSideSlatInfraredEmissivity) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatInfraredEmissivity, frontSideSlatInfraredEmissivity);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetFrontSideSlatInfraredEmissivity() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatInfraredEmissivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialBlindEquivalentLayer_Impl::backSideSlatInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isBackSideSlatInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatInfraredEmissivity);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setBackSideSlatInfraredEmissivity(double backSideSlatInfraredEmissivity) {
      return setDouble(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatInfraredEmissivity, backSideSlatInfraredEmissivity);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetBackSideSlatInfraredEmissivity() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatInfraredEmissivity, "");
      OS_ASSERT(result);
    }

    std::string WindowMaterialBlindEquivalentLayer_Impl::slatAngleControl() const {
      const auto value = getString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngleControl, true);
      OS_ASSERT(value);
      return *value;
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::isSlatAngleControlDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngleControl);
    }
    bool WindowMaterialBlindEquivalentLayer_Impl::setSlatAngleControl(const std::string& slatAngleControl) {
      return setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngleControl, slatAngleControl);
    }
    void WindowMaterialBlindEquivalentLayer_Impl::resetSlatAngleControl() {
      const bool result = setString(openstudio::WindowMaterial_Blind_EquivalentLayerFields::SlatAngleControl, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
