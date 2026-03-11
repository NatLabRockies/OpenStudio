/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowMaterialScreenEquivalentLayer.hpp"
#include "WindowMaterialScreenEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowMaterial_Screen_EquivalentLayer_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialScreenEquivalentLayer::WindowMaterialScreenEquivalentLayer(const Model& model)
    : ModelObject(WindowMaterialScreenEquivalentLayer::iddObjectType(), model) {}

  WindowMaterialScreenEquivalentLayer::WindowMaterialScreenEquivalentLayer(std::shared_ptr<detail::WindowMaterialScreenEquivalentLayer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialScreenEquivalentLayer::iddObjectType() {
    return IddObjectType::WindowMaterial_Screen_EquivalentLayer;
  }

  boost::optional<double> WindowMaterialScreenEquivalentLayer::screenBeamBeamSolarTransmittance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenBeamBeamSolarTransmittance();
  }

  bool WindowMaterialScreenEquivalentLayer::isScreenBeamBeamSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->isScreenBeamBeamSolarTransmittanceDefaulted();
  }

  bool WindowMaterialScreenEquivalentLayer::isScreenBeamBeamSolarTransmittanceAutocalculated() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->isScreenBeamBeamSolarTransmittanceAutocalculated();
  }

  double WindowMaterialScreenEquivalentLayer::screenBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenBeamDiffuseSolarTransmittance();
  }

  double WindowMaterialScreenEquivalentLayer::screenBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenBeamDiffuseSolarReflectance();
  }

  double WindowMaterialScreenEquivalentLayer::screenBeamBeamVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenBeamBeamVisibleSolarTransmittance();
  }

  double WindowMaterialScreenEquivalentLayer::screenBeamDiffuseVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenBeamDiffuseVisibleSolarTransmittance();
  }

  double WindowMaterialScreenEquivalentLayer::screenBeamDiffuseVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenBeamDiffuseVisibleSolarReflectance();
  }

  double WindowMaterialScreenEquivalentLayer::screenInfraredTransmittance() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenInfraredTransmittance();
  }

  bool WindowMaterialScreenEquivalentLayer::isScreenInfraredTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->isScreenInfraredTransmittanceDefaulted();
  }

  double WindowMaterialScreenEquivalentLayer::screenInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenInfraredEmissivity();
  }

  bool WindowMaterialScreenEquivalentLayer::isScreenInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->isScreenInfraredEmissivityDefaulted();
  }

  double WindowMaterialScreenEquivalentLayer::screenWireSpacing() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenWireSpacing();
  }

  bool WindowMaterialScreenEquivalentLayer::isScreenWireSpacingDefaulted() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->isScreenWireSpacingDefaulted();
  }

  double WindowMaterialScreenEquivalentLayer::screenWireDiameter() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->screenWireDiameter();
  }

  bool WindowMaterialScreenEquivalentLayer::isScreenWireDiameterDefaulted() const {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->isScreenWireDiameterDefaulted();
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenBeamBeamSolarTransmittance(double screenBeamBeamSolarTransmittance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenBeamBeamSolarTransmittance(screenBeamBeamSolarTransmittance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenBeamDiffuseSolarTransmittance(double screenBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenBeamDiffuseSolarTransmittance(screenBeamDiffuseSolarTransmittance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenBeamDiffuseSolarReflectance(double screenBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenBeamDiffuseSolarReflectance(screenBeamDiffuseSolarReflectance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenBeamBeamVisibleSolarTransmittance(double screenBeamBeamVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenBeamBeamVisibleSolarTransmittance(
      screenBeamBeamVisibleSolarTransmittance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenBeamDiffuseVisibleSolarTransmittance(double screenBeamDiffuseVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenBeamDiffuseVisibleSolarTransmittance(
      screenBeamDiffuseVisibleSolarTransmittance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenBeamDiffuseVisibleSolarReflectance(double screenBeamDiffuseVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenBeamDiffuseVisibleSolarReflectance(
      screenBeamDiffuseVisibleSolarReflectance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenInfraredTransmittance(double screenInfraredTransmittance) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenInfraredTransmittance(screenInfraredTransmittance);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenInfraredEmissivity(double screenInfraredEmissivity) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenInfraredEmissivity(screenInfraredEmissivity);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenWireSpacing(double screenWireSpacing) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenWireSpacing(screenWireSpacing);
  }

  bool WindowMaterialScreenEquivalentLayer::setScreenWireDiameter(double screenWireDiameter) {
    return getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->setScreenWireDiameter(screenWireDiameter);
  }

  void WindowMaterialScreenEquivalentLayer::resetScreenBeamBeamSolarTransmittance() {
    getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->resetScreenBeamBeamSolarTransmittance();
  }

  void WindowMaterialScreenEquivalentLayer::autocalculateScreenBeamBeamSolarTransmittance() {
    getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->autocalculateScreenBeamBeamSolarTransmittance();
  }

  void WindowMaterialScreenEquivalentLayer::resetScreenInfraredTransmittance() {
    getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->resetScreenInfraredTransmittance();
  }

  void WindowMaterialScreenEquivalentLayer::resetScreenInfraredEmissivity() {
    getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->resetScreenInfraredEmissivity();
  }

  void WindowMaterialScreenEquivalentLayer::resetScreenWireSpacing() {
    getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->resetScreenWireSpacing();
  }

  void WindowMaterialScreenEquivalentLayer::resetScreenWireDiameter() {
    getImpl<detail::WindowMaterialScreenEquivalentLayer_Impl>()->resetScreenWireDiameter();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> WindowMaterialScreenEquivalentLayer_Impl::screenBeamBeamSolarTransmittance() const {
      return getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamSolarTransmittance, true);
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::isScreenBeamBeamSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamSolarTransmittance);
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::isScreenBeamBeamSolarTransmittanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamSolarTransmittance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenBeamBeamSolarTransmittance(double screenBeamBeamSolarTransmittance) {
      return setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamSolarTransmittance, screenBeamBeamSolarTransmittance);
    }

    void WindowMaterialScreenEquivalentLayer_Impl::resetScreenBeamBeamSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamSolarTransmittance, ""));
    }

    void WindowMaterialScreenEquivalentLayer_Impl::autocalculateScreenBeamBeamSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamSolarTransmittance, "autocalculate"));
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenBeamDiffuseSolarTransmittance(double screenBeamDiffuseSolarTransmittance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseSolarTransmittance, screenBeamDiffuseSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenBeamDiffuseSolarReflectance(double screenBeamDiffuseSolarReflectance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseSolarReflectance, screenBeamDiffuseSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenBeamBeamVisibleSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamVisibleTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenBeamBeamVisibleSolarTransmittance(double screenBeamBeamVisibleSolarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamBeamVisibleTransmittance,
                                    screenBeamBeamVisibleSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenBeamDiffuseVisibleSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseVisibleTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenBeamDiffuseVisibleSolarTransmittance(double screenBeamDiffuseVisibleSolarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseVisibleTransmittance,
                                    screenBeamDiffuseVisibleSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenBeamDiffuseVisibleSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseVisibleReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenBeamDiffuseVisibleSolarReflectance(double screenBeamDiffuseVisibleSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenBeamDiffuseVisibleReflectance,
                                    screenBeamDiffuseVisibleSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenInfraredTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::isScreenInfraredTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredTransmittance);
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenInfraredTransmittance(double screenInfraredTransmittance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredTransmittance, screenInfraredTransmittance);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialScreenEquivalentLayer_Impl::resetScreenInfraredTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredTransmittance, ""));
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::isScreenInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredEmissivity);
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenInfraredEmissivity(double screenInfraredEmissivity) {
      const bool result = setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredEmissivity, screenInfraredEmissivity);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialScreenEquivalentLayer_Impl::resetScreenInfraredEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenInfraredEmissivity, ""));
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenWireSpacing() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireSpacing, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::isScreenWireSpacingDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireSpacing);
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenWireSpacing(double screenWireSpacing) {
      const bool result = setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireSpacing, screenWireSpacing);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialScreenEquivalentLayer_Impl::resetScreenWireSpacing() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireSpacing, ""));
    }

    double WindowMaterialScreenEquivalentLayer_Impl::screenWireDiameter() const {
      const auto value = getDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::isScreenWireDiameterDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireDiameter);
    }

    bool WindowMaterialScreenEquivalentLayer_Impl::setScreenWireDiameter(double screenWireDiameter) {
      const bool result = setDouble(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireDiameter, screenWireDiameter);
      OS_ASSERT(result);
      return result;
    }

    void WindowMaterialScreenEquivalentLayer_Impl::resetScreenWireDiameter() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Screen_EquivalentLayerFields::ScreenWireDiameter, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
