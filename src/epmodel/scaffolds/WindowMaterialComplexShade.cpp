/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "WindowMaterialComplexShade.hpp"
#include "WindowMaterialComplexShade_Impl.hpp"

#include "Model.hpp"

#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WindowMaterial_ComplexShade_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialComplexShade::WindowMaterialComplexShade(const Model& model) : ModelObject(WindowMaterialComplexShade::iddObjectType(), model) {}

  WindowMaterialComplexShade::WindowMaterialComplexShade(std::shared_ptr<detail::WindowMaterialComplexShade_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialComplexShade::iddObjectType() {
    return IddObjectType::WindowMaterial_ComplexShade;
  }

  std::vector<std::string> WindowMaterialComplexShade::layerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_ComplexShadeFields::LayerType);
  }

  std::string WindowMaterialComplexShade::layerType() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->layerType();
  }
  bool WindowMaterialComplexShade::isLayerTypeDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isLayerTypeDefaulted();
  }
  bool WindowMaterialComplexShade::setLayerType(const std::string& layerType) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setLayerType(layerType);
  }
  void WindowMaterialComplexShade::resetLayerType() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetLayerType();
  }

  double WindowMaterialComplexShade::thickness() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->thickness();
  }
  bool WindowMaterialComplexShade::isThicknessDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isThicknessDefaulted();
  }
  bool WindowMaterialComplexShade::setThickness(double thickness) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setThickness(thickness);
  }
  void WindowMaterialComplexShade::resetThickness() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetThickness();
  }

  double WindowMaterialComplexShade::conductivity() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->conductivity();
  }
  bool WindowMaterialComplexShade::isConductivityDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isConductivityDefaulted();
  }
  bool WindowMaterialComplexShade::setConductivity(double conductivity) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setConductivity(conductivity);
  }
  void WindowMaterialComplexShade::resetConductivity() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetConductivity();
  }

  double WindowMaterialComplexShade::irTransmittance() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->irTransmittance();
  }
  bool WindowMaterialComplexShade::isIrTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isIrTransmittanceDefaulted();
  }
  bool WindowMaterialComplexShade::setIrTransmittance(double irTransmittance) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setIrTransmittance(irTransmittance);
  }
  void WindowMaterialComplexShade::resetIrTransmittance() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetIrTransmittance();
  }

  double WindowMaterialComplexShade::frontEmissivity() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->frontEmissivity();
  }
  bool WindowMaterialComplexShade::isFrontEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isFrontEmissivityDefaulted();
  }
  bool WindowMaterialComplexShade::setFrontEmissivity(double frontEmissivity) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setFrontEmissivity(frontEmissivity);
  }
  void WindowMaterialComplexShade::resetFrontEmissivity() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetFrontEmissivity();
  }

  double WindowMaterialComplexShade::backEmissivity() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->backEmissivity();
  }
  bool WindowMaterialComplexShade::isBackEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isBackEmissivityDefaulted();
  }
  bool WindowMaterialComplexShade::setBackEmissivity(double backEmissivity) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setBackEmissivity(backEmissivity);
  }
  void WindowMaterialComplexShade::resetBackEmissivity() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetBackEmissivity();
  }

  double WindowMaterialComplexShade::topOpeningMultiplier() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->topOpeningMultiplier();
  }
  bool WindowMaterialComplexShade::isTopOpeningMultiplierDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isTopOpeningMultiplierDefaulted();
  }
  bool WindowMaterialComplexShade::setTopOpeningMultiplier(double topOpeningMultiplier) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setTopOpeningMultiplier(topOpeningMultiplier);
  }
  void WindowMaterialComplexShade::resetTopOpeningMultiplier() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetTopOpeningMultiplier();
  }

  double WindowMaterialComplexShade::bottomOpeningMultiplier() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->bottomOpeningMultiplier();
  }
  bool WindowMaterialComplexShade::isBottomOpeningMultiplierDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isBottomOpeningMultiplierDefaulted();
  }
  bool WindowMaterialComplexShade::setBottomOpeningMultiplier(double bottomOpeningMultiplier) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setBottomOpeningMultiplier(bottomOpeningMultiplier);
  }
  void WindowMaterialComplexShade::resetBottomOpeningMultiplier() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetBottomOpeningMultiplier();
  }

  double WindowMaterialComplexShade::leftSideOpeningMultiplier() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->leftSideOpeningMultiplier();
  }
  bool WindowMaterialComplexShade::isLeftSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isLeftSideOpeningMultiplierDefaulted();
  }
  bool WindowMaterialComplexShade::setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setLeftSideOpeningMultiplier(leftSideOpeningMultiplier);
  }
  void WindowMaterialComplexShade::resetLeftSideOpeningMultiplier() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetLeftSideOpeningMultiplier();
  }

  double WindowMaterialComplexShade::rightSideOpeningMultiplier() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->rightSideOpeningMultiplier();
  }
  bool WindowMaterialComplexShade::isRightSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isRightSideOpeningMultiplierDefaulted();
  }
  bool WindowMaterialComplexShade::setRightSideOpeningMultiplier(double rightSideOpeningMultiplier) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setRightSideOpeningMultiplier(rightSideOpeningMultiplier);
  }
  void WindowMaterialComplexShade::resetRightSideOpeningMultiplier() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetRightSideOpeningMultiplier();
  }

  double WindowMaterialComplexShade::frontOpeningMultiplier() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->frontOpeningMultiplier();
  }
  bool WindowMaterialComplexShade::isFrontOpeningMultiplierDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isFrontOpeningMultiplierDefaulted();
  }
  bool WindowMaterialComplexShade::setFrontOpeningMultiplier(double frontOpeningMultiplier) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setFrontOpeningMultiplier(frontOpeningMultiplier);
  }
  void WindowMaterialComplexShade::resetFrontOpeningMultiplier() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetFrontOpeningMultiplier();
  }

  double WindowMaterialComplexShade::slatWidth() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->slatWidth();
  }
  bool WindowMaterialComplexShade::isSlatWidthDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isSlatWidthDefaulted();
  }
  bool WindowMaterialComplexShade::setSlatWidth(double slatWidth) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setSlatWidth(slatWidth);
  }
  void WindowMaterialComplexShade::resetSlatWidth() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetSlatWidth();
  }

  double WindowMaterialComplexShade::slatSpacing() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->slatSpacing();
  }
  bool WindowMaterialComplexShade::isSlatSpacingDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isSlatSpacingDefaulted();
  }
  bool WindowMaterialComplexShade::setSlatSpacing(double slatSpacing) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setSlatSpacing(slatSpacing);
  }
  void WindowMaterialComplexShade::resetSlatSpacing() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetSlatSpacing();
  }

  double WindowMaterialComplexShade::slatThickness() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->slatThickness();
  }
  bool WindowMaterialComplexShade::isSlatThicknessDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isSlatThicknessDefaulted();
  }
  bool WindowMaterialComplexShade::setSlatThickness(double slatThickness) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setSlatThickness(slatThickness);
  }
  void WindowMaterialComplexShade::resetSlatThickness() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetSlatThickness();
  }

  double WindowMaterialComplexShade::slatAngle() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->slatAngle();
  }
  bool WindowMaterialComplexShade::isSlatAngleDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isSlatAngleDefaulted();
  }
  bool WindowMaterialComplexShade::setSlatAngle(double slatAngle) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setSlatAngle(slatAngle);
  }
  void WindowMaterialComplexShade::resetSlatAngle() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetSlatAngle();
  }

  double WindowMaterialComplexShade::slatConductivity() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->slatConductivity();
  }
  bool WindowMaterialComplexShade::isSlatConductivityDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isSlatConductivityDefaulted();
  }
  bool WindowMaterialComplexShade::setSlatConductivity(double slatConductivity) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setSlatConductivity(slatConductivity);
  }
  void WindowMaterialComplexShade::resetSlatConductivity() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetSlatConductivity();
  }

  double WindowMaterialComplexShade::slatCurve() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->slatCurve();
  }
  bool WindowMaterialComplexShade::isSlatCurveDefaulted() const {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->isSlatCurveDefaulted();
  }
  bool WindowMaterialComplexShade::setSlatCurve(double slatCurve) {
    return getImpl<detail::WindowMaterialComplexShade_Impl>()->setSlatCurve(slatCurve);
  }
  void WindowMaterialComplexShade::resetSlatCurve() {
    getImpl<detail::WindowMaterialComplexShade_Impl>()->resetSlatCurve();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {
    std::string WindowMaterialComplexShade_Impl::layerType() const {
      const auto value = getString(openstudio::WindowMaterial_ComplexShadeFields::LayerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isLayerTypeDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::LayerType);
    }

    bool WindowMaterialComplexShade_Impl::setLayerType(const std::string& layerType) {
      return setString(openstudio::WindowMaterial_ComplexShadeFields::LayerType, layerType);
    }

    void WindowMaterialComplexShade_Impl::resetLayerType() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::LayerType, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::thickness() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isThicknessDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::Thickness);
    }

    bool WindowMaterialComplexShade_Impl::setThickness(double thickness) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::Thickness, thickness);
    }

    void WindowMaterialComplexShade_Impl::resetThickness() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::Thickness, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::conductivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::Conductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isConductivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::Conductivity);
    }

    bool WindowMaterialComplexShade_Impl::setConductivity(double conductivity) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::Conductivity, conductivity);
    }

    void WindowMaterialComplexShade_Impl::resetConductivity() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::Conductivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::irTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::IRTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isIrTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::IRTransmittance);
    }

    bool WindowMaterialComplexShade_Impl::setIrTransmittance(double irTransmittance) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::IRTransmittance, irTransmittance);
    }

    void WindowMaterialComplexShade_Impl::resetIrTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::IRTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::frontEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::FrontEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isFrontEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::FrontEmissivity);
    }

    bool WindowMaterialComplexShade_Impl::setFrontEmissivity(double frontEmissivity) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::FrontEmissivity, frontEmissivity);
    }

    void WindowMaterialComplexShade_Impl::resetFrontEmissivity() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::FrontEmissivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::backEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::BackEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isBackEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::BackEmissivity);
    }

    bool WindowMaterialComplexShade_Impl::setBackEmissivity(double backEmissivity) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::BackEmissivity, backEmissivity);
    }

    void WindowMaterialComplexShade_Impl::resetBackEmissivity() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::BackEmissivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::topOpeningMultiplier() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::TopOpeningMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isTopOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::TopOpeningMultiplier);
    }

    bool WindowMaterialComplexShade_Impl::setTopOpeningMultiplier(double topOpeningMultiplier) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::TopOpeningMultiplier, topOpeningMultiplier);
    }

    void WindowMaterialComplexShade_Impl::resetTopOpeningMultiplier() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::TopOpeningMultiplier, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::bottomOpeningMultiplier() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::BottomOpeningMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isBottomOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::BottomOpeningMultiplier);
    }

    bool WindowMaterialComplexShade_Impl::setBottomOpeningMultiplier(double bottomOpeningMultiplier) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::BottomOpeningMultiplier, bottomOpeningMultiplier);
    }

    void WindowMaterialComplexShade_Impl::resetBottomOpeningMultiplier() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::BottomOpeningMultiplier, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::leftSideOpeningMultiplier() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::LeftSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isLeftSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::LeftSideOpeningMultiplier);
    }

    bool WindowMaterialComplexShade_Impl::setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::LeftSideOpeningMultiplier, leftSideOpeningMultiplier);
    }

    void WindowMaterialComplexShade_Impl::resetLeftSideOpeningMultiplier() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::LeftSideOpeningMultiplier, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::rightSideOpeningMultiplier() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::RightSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isRightSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::RightSideOpeningMultiplier);
    }

    bool WindowMaterialComplexShade_Impl::setRightSideOpeningMultiplier(double rightSideOpeningMultiplier) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::RightSideOpeningMultiplier, rightSideOpeningMultiplier);
    }

    void WindowMaterialComplexShade_Impl::resetRightSideOpeningMultiplier() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::RightSideOpeningMultiplier, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::frontOpeningMultiplier() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::FrontOpeningMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isFrontOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::FrontOpeningMultiplier);
    }

    bool WindowMaterialComplexShade_Impl::setFrontOpeningMultiplier(double frontOpeningMultiplier) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::FrontOpeningMultiplier, frontOpeningMultiplier);
    }

    void WindowMaterialComplexShade_Impl::resetFrontOpeningMultiplier() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::FrontOpeningMultiplier, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::slatWidth() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatWidth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isSlatWidthDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::SlatWidth);
    }

    bool WindowMaterialComplexShade_Impl::setSlatWidth(double slatWidth) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatWidth, slatWidth);
    }

    void WindowMaterialComplexShade_Impl::resetSlatWidth() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::SlatWidth, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::slatSpacing() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatSpacing, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isSlatSpacingDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::SlatSpacing);
    }

    bool WindowMaterialComplexShade_Impl::setSlatSpacing(double slatSpacing) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatSpacing, slatSpacing);
    }

    void WindowMaterialComplexShade_Impl::resetSlatSpacing() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::SlatSpacing, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::slatThickness() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isSlatThicknessDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::SlatThickness);
    }

    bool WindowMaterialComplexShade_Impl::setSlatThickness(double slatThickness) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatThickness, slatThickness);
    }

    void WindowMaterialComplexShade_Impl::resetSlatThickness() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::SlatThickness, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::slatAngle() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isSlatAngleDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::SlatAngle);
    }

    bool WindowMaterialComplexShade_Impl::setSlatAngle(double slatAngle) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatAngle, slatAngle);
    }

    void WindowMaterialComplexShade_Impl::resetSlatAngle() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::SlatAngle, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::slatConductivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isSlatConductivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::SlatConductivity);
    }

    bool WindowMaterialComplexShade_Impl::setSlatConductivity(double slatConductivity) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatConductivity, slatConductivity);
    }

    void WindowMaterialComplexShade_Impl::resetSlatConductivity() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::SlatConductivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialComplexShade_Impl::slatCurve() const {
      const auto value = getDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatCurve, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialComplexShade_Impl::isSlatCurveDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ComplexShadeFields::SlatCurve);
    }

    bool WindowMaterialComplexShade_Impl::setSlatCurve(double slatCurve) {
      return setDouble(openstudio::WindowMaterial_ComplexShadeFields::SlatCurve, slatCurve);
    }

    void WindowMaterialComplexShade_Impl::resetSlatCurve() {
      const bool result = setString(openstudio::WindowMaterial_ComplexShadeFields::SlatCurve, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
