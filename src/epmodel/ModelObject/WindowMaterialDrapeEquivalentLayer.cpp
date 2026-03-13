/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowMaterialDrapeEquivalentLayer.hpp"
#include "WindowMaterialDrapeEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_Drape_EquivalentLayer_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialDrapeEquivalentLayer::WindowMaterialDrapeEquivalentLayer(const Model& model)
    : ModelObject(WindowMaterialDrapeEquivalentLayer::iddObjectType(), model) {}

  WindowMaterialDrapeEquivalentLayer::WindowMaterialDrapeEquivalentLayer(std::shared_ptr<detail::WindowMaterialDrapeEquivalentLayer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialDrapeEquivalentLayer::iddObjectType() {
    return IddObjectType::WindowMaterial_Drape_EquivalentLayer;
  }

  double WindowMaterialDrapeEquivalentLayer::drapeBeamBeamSolarTransmittanceAtNormalIncidence() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->drapeBeamBeamSolarTransmittanceAtNormalIncidence();
  }

  bool WindowMaterialDrapeEquivalentLayer::isDrapeBeamBeamSolarTransmittanceAtNormalIncidenceDefaulted() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->isDrapeBeamBeamSolarTransmittanceAtNormalIncidenceDefaulted();
  }

  bool
    WindowMaterialDrapeEquivalentLayer::setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(double drapeBeamBeamSolarTransmittanceAtNormalIncidence) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(
      drapeBeamBeamSolarTransmittanceAtNormalIncidence);
  }

  void WindowMaterialDrapeEquivalentLayer::resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence();
  }

  double WindowMaterialDrapeEquivalentLayer::frontSideDrapeBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->frontSideDrapeBeamDiffuseSolarTransmittance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setFrontSideDrapeBeamDiffuseSolarTransmittance(double frontSideDrapeBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setFrontSideDrapeBeamDiffuseSolarTransmittance(
      frontSideDrapeBeamDiffuseSolarTransmittance);
  }

  double WindowMaterialDrapeEquivalentLayer::backSideDrapeBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->backSideDrapeBeamDiffuseSolarTransmittance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setBackSideDrapeBeamDiffuseSolarTransmittance(double backSideDrapeBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setBackSideDrapeBeamDiffuseSolarTransmittance(
      backSideDrapeBeamDiffuseSolarTransmittance);
  }

  double WindowMaterialDrapeEquivalentLayer::frontSideDrapeBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->frontSideDrapeBeamDiffuseSolarReflectance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setFrontSideDrapeBeamDiffuseSolarReflectance(double frontSideDrapeBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setFrontSideDrapeBeamDiffuseSolarReflectance(
      frontSideDrapeBeamDiffuseSolarReflectance);
  }

  double WindowMaterialDrapeEquivalentLayer::backSideDrapeBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->backSideDrapeBeamDiffuseSolarReflectance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setBackSideDrapeBeamDiffuseSolarReflectance(double backSideDrapeBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setBackSideDrapeBeamDiffuseSolarReflectance(
      backSideDrapeBeamDiffuseSolarReflectance);
  }

  boost::optional<double> WindowMaterialDrapeEquivalentLayer::drapeBeamBeamVisibleTransmittance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->drapeBeamBeamVisibleTransmittance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setDrapeBeamBeamVisibleTransmittance(double drapeBeamBeamVisibleTransmittance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setDrapeBeamBeamVisibleTransmittance(drapeBeamBeamVisibleTransmittance);
  }

  void WindowMaterialDrapeEquivalentLayer::resetDrapeBeamBeamVisibleTransmittance() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetDrapeBeamBeamVisibleTransmittance();
  }

  boost::optional<double> WindowMaterialDrapeEquivalentLayer::drapeBeamDiffuseVisibleTransmittance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->drapeBeamDiffuseVisibleTransmittance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setDrapeBeamDiffuseVisibleTransmittance(double drapeBeamDiffuseVisibleTransmittance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setDrapeBeamDiffuseVisibleTransmittance(drapeBeamDiffuseVisibleTransmittance);
  }

  void WindowMaterialDrapeEquivalentLayer::resetDrapeBeamDiffuseVisibleTransmittance() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetDrapeBeamDiffuseVisibleTransmittance();
  }

  boost::optional<double> WindowMaterialDrapeEquivalentLayer::drapeBeamDiffuseVisibleReflectance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->drapeBeamDiffuseVisibleReflectance();
  }

  bool WindowMaterialDrapeEquivalentLayer::setDrapeBeamDiffuseVisibleReflectance(double drapeBeamDiffuseVisibleReflectance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setDrapeBeamDiffuseVisibleReflectance(drapeBeamDiffuseVisibleReflectance);
  }

  void WindowMaterialDrapeEquivalentLayer::resetDrapeBeamDiffuseVisibleReflectance() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetDrapeBeamDiffuseVisibleReflectance();
  }

  double WindowMaterialDrapeEquivalentLayer::drapeMaterialInfraredTransmittance() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->drapeMaterialInfraredTransmittance();
  }

  bool WindowMaterialDrapeEquivalentLayer::isDrapeMaterialInfraredTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->isDrapeMaterialInfraredTransmittanceDefaulted();
  }

  bool WindowMaterialDrapeEquivalentLayer::setDrapeMaterialInfraredTransmittance(double drapeMaterialInfraredTransmittance) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setDrapeMaterialInfraredTransmittance(drapeMaterialInfraredTransmittance);
  }

  void WindowMaterialDrapeEquivalentLayer::resetDrapeMaterialInfraredTransmittance() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetDrapeMaterialInfraredTransmittance();
  }

  double WindowMaterialDrapeEquivalentLayer::frontSideDrapeMaterialInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->frontSideDrapeMaterialInfraredEmissivity();
  }

  bool WindowMaterialDrapeEquivalentLayer::isFrontSideDrapeMaterialInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->isFrontSideDrapeMaterialInfraredEmissivityDefaulted();
  }

  bool WindowMaterialDrapeEquivalentLayer::setFrontSideDrapeMaterialInfraredEmissivity(double frontSideDrapeMaterialInfraredEmissivity) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setFrontSideDrapeMaterialInfraredEmissivity(
      frontSideDrapeMaterialInfraredEmissivity);
  }

  void WindowMaterialDrapeEquivalentLayer::resetFrontSideDrapeMaterialInfraredEmissivity() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetFrontSideDrapeMaterialInfraredEmissivity();
  }

  double WindowMaterialDrapeEquivalentLayer::backSideDrapeMaterialInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->backSideDrapeMaterialInfraredEmissivity();
  }

  bool WindowMaterialDrapeEquivalentLayer::isBackSideDrapeMaterialInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->isBackSideDrapeMaterialInfraredEmissivityDefaulted();
  }

  bool WindowMaterialDrapeEquivalentLayer::setBackSideDrapeMaterialInfraredEmissivity(double backSideDrapeMaterialInfraredEmissivity) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setBackSideDrapeMaterialInfraredEmissivity(
      backSideDrapeMaterialInfraredEmissivity);
  }

  void WindowMaterialDrapeEquivalentLayer::resetBackSideDrapeMaterialInfraredEmissivity() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetBackSideDrapeMaterialInfraredEmissivity();
  }

  double WindowMaterialDrapeEquivalentLayer::widthOfPleatedFabric() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->widthOfPleatedFabric();
  }

  bool WindowMaterialDrapeEquivalentLayer::isWidthOfPleatedFabricDefaulted() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->isWidthOfPleatedFabricDefaulted();
  }

  bool WindowMaterialDrapeEquivalentLayer::setWidthOfPleatedFabric(double widthOfPleatedFabric) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setWidthOfPleatedFabric(widthOfPleatedFabric);
  }

  void WindowMaterialDrapeEquivalentLayer::resetWidthOfPleatedFabric() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetWidthOfPleatedFabric();
  }

  double WindowMaterialDrapeEquivalentLayer::lengthOfPleatedFabric() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->lengthOfPleatedFabric();
  }

  bool WindowMaterialDrapeEquivalentLayer::isLengthOfPleatedFabricDefaulted() const {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->isLengthOfPleatedFabricDefaulted();
  }

  bool WindowMaterialDrapeEquivalentLayer::setLengthOfPleatedFabric(double lengthOfPleatedFabric) {
    return getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->setLengthOfPleatedFabric(lengthOfPleatedFabric);
  }

  void WindowMaterialDrapeEquivalentLayer::resetLengthOfPleatedFabric() {
    getImpl<detail::WindowMaterialDrapeEquivalentLayer_Impl>()->resetLengthOfPleatedFabric();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double WindowMaterialDrapeEquivalentLayer_Impl::drapeBeamBeamSolarTransmittanceAtNormalIncidence() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamSolarTransmittanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::isDrapeBeamBeamSolarTransmittanceAtNormalIncidenceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamSolarTransmittanceatNormalIncidence);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setDrapeBeamBeamSolarTransmittanceAtNormalIncidence(
      double drapeBeamBeamSolarTransmittanceAtNormalIncidence) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamSolarTransmittanceatNormalIncidence,
                       drapeBeamBeamSolarTransmittanceAtNormalIncidence);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetDrapeBeamBeamSolarTransmittanceAtNormalIncidence() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamSolarTransmittanceatNormalIncidence, "");
      OS_ASSERT(result);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::frontSideDrapeBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setFrontSideDrapeBeamDiffuseSolarTransmittance(double frontSideDrapeBeamDiffuseSolarTransmittance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeBeamDiffuseSolarTransmittance,
                       frontSideDrapeBeamDiffuseSolarTransmittance);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::backSideDrapeBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setBackSideDrapeBeamDiffuseSolarTransmittance(double backSideDrapeBeamDiffuseSolarTransmittance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeBeamDiffuseSolarTransmittance,
                       backSideDrapeBeamDiffuseSolarTransmittance);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::frontSideDrapeBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setFrontSideDrapeBeamDiffuseSolarReflectance(double frontSideDrapeBeamDiffuseSolarReflectance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeBeamDiffuseSolarReflectance,
                       frontSideDrapeBeamDiffuseSolarReflectance);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::backSideDrapeBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setBackSideDrapeBeamDiffuseSolarReflectance(double backSideDrapeBeamDiffuseSolarReflectance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeBeamDiffuseSolarReflectance,
                       backSideDrapeBeamDiffuseSolarReflectance);
    }

    boost::optional<double> WindowMaterialDrapeEquivalentLayer_Impl::drapeBeamBeamVisibleTransmittance() const {
      return getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamVisibleTransmittance, true);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setDrapeBeamBeamVisibleTransmittance(double drapeBeamBeamVisibleTransmittance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamVisibleTransmittance, drapeBeamBeamVisibleTransmittance);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetDrapeBeamBeamVisibleTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamVisibleTransmittance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WindowMaterialDrapeEquivalentLayer_Impl::drapeBeamDiffuseVisibleTransmittance() const {
      return getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleTransmittance, true);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setDrapeBeamDiffuseVisibleTransmittance(double drapeBeamDiffuseVisibleTransmittance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleTransmittance,
                       drapeBeamDiffuseVisibleTransmittance);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetDrapeBeamDiffuseVisibleTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleTransmittance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> WindowMaterialDrapeEquivalentLayer_Impl::drapeBeamDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleReflectance, true);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setDrapeBeamDiffuseVisibleReflectance(double drapeBeamDiffuseVisibleReflectance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleReflectance,
                       drapeBeamDiffuseVisibleReflectance);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetDrapeBeamDiffuseVisibleReflectance() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleReflectance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::drapeMaterialInfraredTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeMaterialInfraredTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::isDrapeMaterialInfraredTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeMaterialInfraredTransmittance);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setDrapeMaterialInfraredTransmittance(double drapeMaterialInfraredTransmittance) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeMaterialInfraredTransmittance,
                       drapeMaterialInfraredTransmittance);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetDrapeMaterialInfraredTransmittance() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::DrapeMaterialInfraredTransmittance, "");
      OS_ASSERT(result);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::frontSideDrapeMaterialInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeMaterialInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::isFrontSideDrapeMaterialInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeMaterialInfraredEmissivity);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setFrontSideDrapeMaterialInfraredEmissivity(double frontSideDrapeMaterialInfraredEmissivity) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeMaterialInfraredEmissivity,
                       frontSideDrapeMaterialInfraredEmissivity);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetFrontSideDrapeMaterialInfraredEmissivity() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeMaterialInfraredEmissivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::backSideDrapeMaterialInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeMaterialInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::isBackSideDrapeMaterialInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeMaterialInfraredEmissivity);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setBackSideDrapeMaterialInfraredEmissivity(double backSideDrapeMaterialInfraredEmissivity) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeMaterialInfraredEmissivity,
                       backSideDrapeMaterialInfraredEmissivity);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetBackSideDrapeMaterialInfraredEmissivity() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeMaterialInfraredEmissivity, "");
      OS_ASSERT(result);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::widthOfPleatedFabric() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::WidthofPleatedFabric, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::isWidthOfPleatedFabricDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Drape_EquivalentLayerFields::WidthofPleatedFabric);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setWidthOfPleatedFabric(double widthOfPleatedFabric) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::WidthofPleatedFabric, widthOfPleatedFabric);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetWidthOfPleatedFabric() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::WidthofPleatedFabric, "");
      OS_ASSERT(result);
    }

    double WindowMaterialDrapeEquivalentLayer_Impl::lengthOfPleatedFabric() const {
      const auto value = getDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::LengthofPleatedFabric, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::isLengthOfPleatedFabricDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Drape_EquivalentLayerFields::LengthofPleatedFabric);
    }

    bool WindowMaterialDrapeEquivalentLayer_Impl::setLengthOfPleatedFabric(double lengthOfPleatedFabric) {
      return setDouble(openstudio::WindowMaterial_Drape_EquivalentLayerFields::LengthofPleatedFabric, lengthOfPleatedFabric);
    }

    void WindowMaterialDrapeEquivalentLayer_Impl::resetLengthOfPleatedFabric() {
      const bool result = setString(openstudio::WindowMaterial_Drape_EquivalentLayerFields::LengthofPleatedFabric, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
