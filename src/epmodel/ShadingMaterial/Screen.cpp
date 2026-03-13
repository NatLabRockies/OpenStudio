/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Screen.hpp"
#include "Screen_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WindowMaterial_Screen_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Screen::Screen(const Model& model) : ModelObject(iddObjectType(), model) {}

  Screen::Screen(std::shared_ptr<detail::Screen_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Screen::iddObjectType() {
    return IddObjectType::WindowMaterial_Screen;
  }

  std::vector<std::string> Screen::reflectedBeamTransmittanceAccountingMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod);
  }

  std::vector<std::string> Screen::angleofResolutionforScreenTransmittanceOutputMapValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap);
  }

  double Screen::thermalConductivity() const {
    return getImpl<detail::Screen_Impl>()->thermalConductivity();
  }

  double Screen::thermalConductance() const {
    return getImpl<detail::Screen_Impl>()->thermalConductance();
  }

  double Screen::thermalResistivity() const {
    return getImpl<detail::Screen_Impl>()->thermalResistivity();
  }

  double Screen::thermalResistance() const {
    return getImpl<detail::Screen_Impl>()->thermalResistance();
  }

  std::string Screen::reflectedBeamTransmittanceAccountingMethod() const {
    return getImpl<detail::Screen_Impl>()->reflectedBeamTransmittanceAccountingMethod();
  }

  bool Screen::isReflectedBeamTransmittanceAccountingMethodDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isReflectedBeamTransmittanceAccountingMethodDefaulted();
  }

  bool Screen::setReflectedBeamTransmittanceAccountingMethod(const std::string& reflectedBeamTransmittanceAccountingMethod) {
    return getImpl<detail::Screen_Impl>()->setReflectedBeamTransmittanceAccountingMethod(reflectedBeamTransmittanceAccountingMethod);
  }

  void Screen::resetReflectedBeamTransmittanceAccountingMethod() {
    getImpl<detail::Screen_Impl>()->resetReflectedBeamTransmittanceAccountingMethod();
  }

  double Screen::diffuseSolarReflectance() const {
    return getImpl<detail::Screen_Impl>()->diffuseSolarReflectance();
  }

  bool Screen::setDiffuseSolarReflectance(double diffuseSolarReflectance) {
    return getImpl<detail::Screen_Impl>()->setDiffuseSolarReflectance(diffuseSolarReflectance);
  }

  double Screen::diffuseVisibleReflectance() const {
    return getImpl<detail::Screen_Impl>()->diffuseVisibleReflectance();
  }

  bool Screen::setDiffuseVisibleReflectance(double diffuseVisibleReflectance) {
    return getImpl<detail::Screen_Impl>()->setDiffuseVisibleReflectance(diffuseVisibleReflectance);
  }

  double Screen::thermalHemisphericalEmissivity() const {
    return getImpl<detail::Screen_Impl>()->thermalHemisphericalEmissivity();
  }

  bool Screen::isThermalHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isThermalHemisphericalEmissivityDefaulted();
  }

  bool Screen::setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity) {
    return getImpl<detail::Screen_Impl>()->setThermalHemisphericalEmissivity(thermalHemisphericalEmissivity);
  }

  void Screen::resetThermalHemisphericalEmissivity() {
    getImpl<detail::Screen_Impl>()->resetThermalHemisphericalEmissivity();
  }

  double Screen::conductivity() const {
    return getImpl<detail::Screen_Impl>()->conductivity();
  }

  bool Screen::isConductivityDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isConductivityDefaulted();
  }

  bool Screen::setConductivity(double conductivity) {
    return getImpl<detail::Screen_Impl>()->setConductivity(conductivity);
  }

  void Screen::resetConductivity() {
    getImpl<detail::Screen_Impl>()->resetConductivity();
  }

  bool Screen::setThermalConductivity(double value) {
    return getImpl<detail::Screen_Impl>()->setThermalConductivity(value);
  }

  bool Screen::setThermalResistivity(double value) {
    return getImpl<detail::Screen_Impl>()->setThermalResistivity(value);
  }

  double Screen::screenMaterialSpacing() const {
    return getImpl<detail::Screen_Impl>()->screenMaterialSpacing();
  }

  bool Screen::setScreenMaterialSpacing(double screenMaterialSpacing) {
    return getImpl<detail::Screen_Impl>()->setScreenMaterialSpacing(screenMaterialSpacing);
  }

  double Screen::screenMaterialDiameter() const {
    return getImpl<detail::Screen_Impl>()->screenMaterialDiameter();
  }

  bool Screen::setScreenMaterialDiameter(double screenMaterialDiameter) {
    return getImpl<detail::Screen_Impl>()->setScreenMaterialDiameter(screenMaterialDiameter);
  }

  double Screen::screentoGlassDistance() const {
    return getImpl<detail::Screen_Impl>()->screentoGlassDistance();
  }

  bool Screen::isScreentoGlassDistanceDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isScreentoGlassDistanceDefaulted();
  }

  bool Screen::setScreentoGlassDistance(double screentoGlassDistance) {
    return getImpl<detail::Screen_Impl>()->setScreentoGlassDistance(screentoGlassDistance);
  }

  void Screen::resetScreentoGlassDistance() {
    getImpl<detail::Screen_Impl>()->resetScreentoGlassDistance();
  }

  double Screen::topOpeningMultiplier() const {
    return getImpl<detail::Screen_Impl>()->topOpeningMultiplier();
  }

  bool Screen::isTopOpeningMultiplierDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isTopOpeningMultiplierDefaulted();
  }

  bool Screen::setTopOpeningMultiplier(double topOpeningMultiplier) {
    return getImpl<detail::Screen_Impl>()->setTopOpeningMultiplier(topOpeningMultiplier);
  }

  void Screen::resetTopOpeningMultiplier() {
    getImpl<detail::Screen_Impl>()->resetTopOpeningMultiplier();
  }

  double Screen::bottomOpeningMultiplier() const {
    return getImpl<detail::Screen_Impl>()->bottomOpeningMultiplier();
  }

  bool Screen::isBottomOpeningMultiplierDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isBottomOpeningMultiplierDefaulted();
  }

  bool Screen::setBottomOpeningMultiplier(double bottomOpeningMultiplier) {
    return getImpl<detail::Screen_Impl>()->setBottomOpeningMultiplier(bottomOpeningMultiplier);
  }

  void Screen::resetBottomOpeningMultiplier() {
    getImpl<detail::Screen_Impl>()->resetBottomOpeningMultiplier();
  }

  double Screen::leftSideOpeningMultiplier() const {
    return getImpl<detail::Screen_Impl>()->leftSideOpeningMultiplier();
  }

  bool Screen::isLeftSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isLeftSideOpeningMultiplierDefaulted();
  }

  bool Screen::setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier) {
    return getImpl<detail::Screen_Impl>()->setLeftSideOpeningMultiplier(leftSideOpeningMultiplier);
  }

  void Screen::resetLeftSideOpeningMultiplier() {
    getImpl<detail::Screen_Impl>()->resetLeftSideOpeningMultiplier();
  }

  double Screen::rightSideOpeningMultiplier() const {
    return getImpl<detail::Screen_Impl>()->rightSideOpeningMultiplier();
  }

  bool Screen::isRightSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isRightSideOpeningMultiplierDefaulted();
  }

  bool Screen::setRightSideOpeningMultiplier(double rightSideOpeningMultiplier) {
    return getImpl<detail::Screen_Impl>()->setRightSideOpeningMultiplier(rightSideOpeningMultiplier);
  }

  void Screen::resetRightSideOpeningMultiplier() {
    getImpl<detail::Screen_Impl>()->resetRightSideOpeningMultiplier();
  }

  std::string Screen::angleofResolutionforScreenTransmittanceOutputMap() const {
    return getImpl<detail::Screen_Impl>()->angleofResolutionforScreenTransmittanceOutputMap();
  }

  bool Screen::isAngleofResolutionforScreenTransmittanceOutputMapDefaulted() const {
    return getImpl<detail::Screen_Impl>()->isAngleofResolutionforScreenTransmittanceOutputMapDefaulted();
  }

  bool Screen::setAngleofResolutionforScreenTransmittanceOutputMap(const std::string& angleofResolutionforScreenTransmittanceOutputMap) {
    return getImpl<detail::Screen_Impl>()->setAngleofResolutionforScreenTransmittanceOutputMap(angleofResolutionforScreenTransmittanceOutputMap);
  }

  void Screen::resetAngleofResolutionforScreenTransmittanceOutputMap() {
    getImpl<detail::Screen_Impl>()->resetAngleofResolutionforScreenTransmittanceOutputMap();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double Screen_Impl::thermalConductivity() const {
      return conductivity();
    }

    double Screen_Impl::thermalConductance() const {
      const double diameter = screenMaterialDiameter();
      OS_ASSERT(diameter > 0.0);
      return thermalConductivity() / diameter;
    }

    double Screen_Impl::thermalResistivity() const {
      const double clamp = thermalConductivity();
      OS_ASSERT(clamp > 0.0);
      return 1.0 / clamp;
    }

    double Screen_Impl::thermalResistance() const {
      const double conductance = thermalConductance();
      OS_ASSERT(conductance > 0.0);
      return 1.0 / conductance;
    }

    std::string Screen_Impl::reflectedBeamTransmittanceAccountingMethod() const {
      boost::optional<std::string> value = getString(openstudio::WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isReflectedBeamTransmittanceAccountingMethodDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod);
    }

    bool Screen_Impl::setReflectedBeamTransmittanceAccountingMethod(const std::string& reflectedBeamTransmittanceAccountingMethod) {
      const bool result =
        setString(openstudio::WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod, reflectedBeamTransmittanceAccountingMethod);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetReflectedBeamTransmittanceAccountingMethod() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod, ""));
    }

    double Screen_Impl::diffuseSolarReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::DiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::setDiffuseSolarReflectance(double diffuseSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::DiffuseSolarReflectance, diffuseSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double Screen_Impl::diffuseVisibleReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::DiffuseVisibleReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::setDiffuseVisibleReflectance(double diffuseVisibleReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::DiffuseVisibleReflectance, diffuseVisibleReflectance);
      OS_ASSERT(result);
      return result;
    }

    double Screen_Impl::thermalHemisphericalEmissivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::ThermalHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isThermalHemisphericalEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::ThermalHemisphericalEmissivity);
    }

    bool Screen_Impl::setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::ThermalHemisphericalEmissivity, thermalHemisphericalEmissivity);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetThermalHemisphericalEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::ThermalHemisphericalEmissivity, ""));
    }

    double Screen_Impl::conductivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::Conductivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isConductivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::Conductivity);
    }

    bool Screen_Impl::setConductivity(double conductivity) {
      return setThermalConductivity(conductivity);
    }

    void Screen_Impl::resetConductivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::Conductivity, ""));
    }

    bool Screen_Impl::setThermalConductivity(double value) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::Conductivity, value);
      OS_ASSERT(result);
      return result;
    }

    bool Screen_Impl::setThermalResistivity(double value) {
      OS_ASSERT(value != 0.0);
      return setThermalConductivity(1.0 / value);
    }

    double Screen_Impl::screenMaterialSpacing() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::ScreenMaterialSpacing, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::setScreenMaterialSpacing(double screenMaterialSpacing) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::ScreenMaterialSpacing, screenMaterialSpacing);
      OS_ASSERT(result);
      return result;
    }

    double Screen_Impl::screenMaterialDiameter() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::ScreenMaterialDiameter, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::setScreenMaterialDiameter(double screenMaterialDiameter) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::ScreenMaterialDiameter, screenMaterialDiameter);
      OS_ASSERT(result);
      return result;
    }

    double Screen_Impl::screentoGlassDistance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::ScreentoGlassDistance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isScreentoGlassDistanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::ScreentoGlassDistance);
    }

    bool Screen_Impl::setScreentoGlassDistance(double screentoGlassDistance) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::ScreentoGlassDistance, screentoGlassDistance);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetScreentoGlassDistance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::ScreentoGlassDistance, ""));
    }

    double Screen_Impl::topOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::TopOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isTopOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::TopOpeningMultiplier);
    }

    bool Screen_Impl::setTopOpeningMultiplier(double topOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::TopOpeningMultiplier, topOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetTopOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::TopOpeningMultiplier, ""));
    }

    double Screen_Impl::bottomOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::BottomOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isBottomOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::BottomOpeningMultiplier);
    }

    bool Screen_Impl::setBottomOpeningMultiplier(double bottomOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::BottomOpeningMultiplier, bottomOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetBottomOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::BottomOpeningMultiplier, ""));
    }

    double Screen_Impl::leftSideOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::LeftSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isLeftSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::LeftSideOpeningMultiplier);
    }

    bool Screen_Impl::setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::LeftSideOpeningMultiplier, leftSideOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetLeftSideOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::LeftSideOpeningMultiplier, ""));
    }

    double Screen_Impl::rightSideOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ScreenFields::RightSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isRightSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::RightSideOpeningMultiplier);
    }

    bool Screen_Impl::setRightSideOpeningMultiplier(double rightSideOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ScreenFields::RightSideOpeningMultiplier, rightSideOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetRightSideOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::RightSideOpeningMultiplier, ""));
    }

    std::string Screen_Impl::angleofResolutionforScreenTransmittanceOutputMap() const {
      boost::optional<std::string> value = getString(openstudio::WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Screen_Impl::isAngleofResolutionforScreenTransmittanceOutputMapDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap);
    }

    bool Screen_Impl::setAngleofResolutionforScreenTransmittanceOutputMap(const std::string& angleofResolutionforScreenTransmittanceOutputMap) {
      const bool result = setString(openstudio::WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap,
                                    angleofResolutionforScreenTransmittanceOutputMap);
      OS_ASSERT(result);
      return result;
    }

    void Screen_Impl::resetAngleofResolutionforScreenTransmittanceOutputMap() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap, ""));
    }

    std::vector<std::string> Screen_Impl::reflectedBeamTransmittanceAccountingMethodValues() const {
      return Screen::reflectedBeamTransmittanceAccountingMethodValues();
    }

    std::vector<std::string> Screen_Impl::angleofResolutionforScreenTransmittanceOutputMapValues() const {
      return Screen::angleofResolutionforScreenTransmittanceOutputMapValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
