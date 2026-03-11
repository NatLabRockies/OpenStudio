/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WindowMaterialGlazingEquivalentLayer.hpp"
#include "WindowMaterialGlazingEquivalentLayer_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowMaterial_Glazing_EquivalentLayer_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowMaterialGlazingEquivalentLayer::WindowMaterialGlazingEquivalentLayer(const Model& model)
    : ModelObject(WindowMaterialGlazingEquivalentLayer::iddObjectType(), model) {
    OS_ASSERT(setOpticalDataType("SpectralAverage"));
    OS_ASSERT(setFrontSideBeamBeamSolarTransmittance(0.0));
    OS_ASSERT(setBackSideBeamBeamSolarTransmittance(0.0));
    OS_ASSERT(setFrontSideBeamBeamSolarReflectance(0.0));
    OS_ASSERT(setBackSideBeamBeamSolarReflectance(0.0));
  }

  WindowMaterialGlazingEquivalentLayer::WindowMaterialGlazingEquivalentLayer(std::shared_ptr<detail::WindowMaterialGlazingEquivalentLayer_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType WindowMaterialGlazingEquivalentLayer::iddObjectType() {
    return IddObjectType::WindowMaterial_Glazing_EquivalentLayer;
  }

  std::vector<std::string> WindowMaterialGlazingEquivalentLayer::opticalDataTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WindowMaterial_Glazing_EquivalentLayerFields::OpticalDataType);
  }

  std::string WindowMaterialGlazingEquivalentLayer::opticalDataType() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->opticalDataType();
  }

  bool WindowMaterialGlazingEquivalentLayer::isOpticalDataTypeDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isOpticalDataTypeDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamBeamSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamBeamSolarTransmittance();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamBeamSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamBeamSolarTransmittance();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamBeamSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamBeamSolarReflectance();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamBeamSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamBeamSolarReflectance();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamBeamVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamBeamVisibleSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideBeamBeamVisibleSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideBeamBeamVisibleSolarTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamBeamVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamBeamVisibleSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideBeamBeamVisibleSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideBeamBeamVisibleSolarTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamBeamVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamBeamVisibleSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideBeamBeamVisibleSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideBeamBeamVisibleSolarReflectanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamBeamVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamBeamVisibleSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideBeamBeamVisibleSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideBeamBeamVisibleSolarReflectanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamDiffuseSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideBeamDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideBeamDiffuseSolarTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamDiffuseSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideBeamDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideBeamDiffuseSolarTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamDiffuseSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideBeamDiffuseSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideBeamDiffuseSolarReflectanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamDiffuseSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideBeamDiffuseSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideBeamDiffuseSolarReflectanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamDiffuseVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamDiffuseVisibleSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideBeamDiffuseVisibleSolarTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamDiffuseVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamDiffuseVisibleSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideBeamDiffuseVisibleSolarTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideBeamDiffuseVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideBeamDiffuseVisibleSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideBeamDiffuseVisibleSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideBeamDiffuseVisibleSolarReflectanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideBeamDiffuseVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideBeamDiffuseVisibleSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideBeamDiffuseVisibleSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideBeamDiffuseVisibleSolarReflectanceDefaulted();
  }

  boost::optional<double> WindowMaterialGlazingEquivalentLayer::diffuseDiffuseSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->diffuseDiffuseSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isDiffuseDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isDiffuseDiffuseSolarTransmittanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::isDiffuseDiffuseSolarTransmittanceAutocalculated() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isDiffuseDiffuseSolarTransmittanceAutocalculated();
  }

  boost::optional<double> WindowMaterialGlazingEquivalentLayer::frontSideDiffuseDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideDiffuseDiffuseSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideDiffuseDiffuseSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideDiffuseDiffuseSolarReflectanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideDiffuseDiffuseSolarReflectanceAutocalculated() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideDiffuseDiffuseSolarReflectanceAutocalculated();
  }

  boost::optional<double> WindowMaterialGlazingEquivalentLayer::backSideDiffuseDiffuseSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideDiffuseDiffuseSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideDiffuseDiffuseSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideDiffuseDiffuseSolarReflectanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideDiffuseDiffuseSolarReflectanceAutocalculated() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideDiffuseDiffuseSolarReflectanceAutocalculated();
  }

  boost::optional<double> WindowMaterialGlazingEquivalentLayer::diffuseDiffuseVisibleSolarTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->diffuseDiffuseVisibleSolarTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isDiffuseDiffuseVisibleSolarTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isDiffuseDiffuseVisibleSolarTransmittanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::isDiffuseDiffuseVisibleSolarTransmittanceAutocalculated() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isDiffuseDiffuseVisibleSolarTransmittanceAutocalculated();
  }

  boost::optional<double> WindowMaterialGlazingEquivalentLayer::frontSideDiffuseDiffuseVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideDiffuseDiffuseVisibleSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideDiffuseDiffuseVisibleSolarReflectanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated();
  }

  boost::optional<double> WindowMaterialGlazingEquivalentLayer::backSideDiffuseDiffuseVisibleSolarReflectance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideDiffuseDiffuseVisibleSolarReflectance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideDiffuseDiffuseVisibleSolarReflectanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated();
  }

  double WindowMaterialGlazingEquivalentLayer::infraredTransmittance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->infraredTransmittance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isInfraredTransmittanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isInfraredTransmittanceDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::frontSideInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->frontSideInfraredEmissivity();
  }

  bool WindowMaterialGlazingEquivalentLayer::isFrontSideInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isFrontSideInfraredEmissivityDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::backSideInfraredEmissivity() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->backSideInfraredEmissivity();
  }

  bool WindowMaterialGlazingEquivalentLayer::isBackSideInfraredEmissivityDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isBackSideInfraredEmissivityDefaulted();
  }

  double WindowMaterialGlazingEquivalentLayer::thermalResistance() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->thermalResistance();
  }

  bool WindowMaterialGlazingEquivalentLayer::isThermalResistanceDefaulted() const {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->isThermalResistanceDefaulted();
  }

  bool WindowMaterialGlazingEquivalentLayer::setOpticalDataType(const std::string& opticalDataType) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setOpticalDataType(opticalDataType);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamBeamSolarTransmittance(double frontSideBeamBeamSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamBeamSolarTransmittance(frontSideBeamBeamSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamBeamSolarTransmittance(double backSideBeamBeamSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamBeamSolarTransmittance(backSideBeamBeamSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamBeamSolarReflectance(double frontSideBeamBeamSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamBeamSolarReflectance(frontSideBeamBeamSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamBeamSolarReflectance(double backSideBeamBeamSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamBeamSolarReflectance(backSideBeamBeamSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamBeamVisibleSolarTransmittance(double frontSideBeamBeamVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamBeamVisibleSolarTransmittance(
      frontSideBeamBeamVisibleSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamBeamVisibleSolarTransmittance(double backSideBeamBeamVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamBeamVisibleSolarTransmittance(
      backSideBeamBeamVisibleSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamBeamVisibleSolarReflectance(double frontSideBeamBeamVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamBeamVisibleSolarReflectance(
      frontSideBeamBeamVisibleSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamBeamVisibleSolarReflectance(double backSideBeamBeamVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamBeamVisibleSolarReflectance(
      backSideBeamBeamVisibleSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamDiffuseSolarTransmittance(double frontSideBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamDiffuseSolarTransmittance(
      frontSideBeamDiffuseSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamDiffuseSolarTransmittance(double backSideBeamDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamDiffuseSolarTransmittance(
      backSideBeamDiffuseSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamDiffuseSolarReflectance(double frontSideBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamDiffuseSolarReflectance(
      frontSideBeamDiffuseSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamDiffuseSolarReflectance(double backSideBeamDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamDiffuseSolarReflectance(backSideBeamDiffuseSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamDiffuseVisibleSolarTransmittance(double frontSideBeamDiffuseVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamDiffuseVisibleSolarTransmittance(
      frontSideBeamDiffuseVisibleSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamDiffuseVisibleSolarTransmittance(double backSideBeamDiffuseVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamDiffuseVisibleSolarTransmittance(
      backSideBeamDiffuseVisibleSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideBeamDiffuseVisibleSolarReflectance(double frontSideBeamDiffuseVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideBeamDiffuseVisibleSolarReflectance(
      frontSideBeamDiffuseVisibleSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideBeamDiffuseVisibleSolarReflectance(double backSideBeamDiffuseVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideBeamDiffuseVisibleSolarReflectance(
      backSideBeamDiffuseVisibleSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setDiffuseDiffuseSolarTransmittance(double diffuseDiffuseSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setDiffuseDiffuseSolarTransmittance(diffuseDiffuseSolarTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideDiffuseDiffuseSolarReflectance(double frontSideDiffuseDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideDiffuseDiffuseSolarReflectance(
      frontSideDiffuseDiffuseSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideDiffuseDiffuseSolarReflectance(double backSideDiffuseDiffuseSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideDiffuseDiffuseSolarReflectance(
      backSideDiffuseDiffuseSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setDiffuseDiffuseVisibleSolarTransmittance(double diffuseDiffuseVisibleSolarTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setDiffuseDiffuseVisibleSolarTransmittance(
      diffuseDiffuseVisibleSolarTransmittance);
  }

  bool
    WindowMaterialGlazingEquivalentLayer::setFrontSideDiffuseDiffuseVisibleSolarReflectance(double frontSideDiffuseDiffuseVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideDiffuseDiffuseVisibleSolarReflectance(
      frontSideDiffuseDiffuseVisibleSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideDiffuseDiffuseVisibleSolarReflectance(double backSideDiffuseDiffuseVisibleSolarReflectance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideDiffuseDiffuseVisibleSolarReflectance(
      backSideDiffuseDiffuseVisibleSolarReflectance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setInfraredTransmittance(double infraredTransmittance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setInfraredTransmittance(infraredTransmittance);
  }

  bool WindowMaterialGlazingEquivalentLayer::setFrontSideInfraredEmissivity(double frontSideInfraredEmissivity) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setFrontSideInfraredEmissivity(frontSideInfraredEmissivity);
  }

  bool WindowMaterialGlazingEquivalentLayer::setBackSideInfraredEmissivity(double backSideInfraredEmissivity) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setBackSideInfraredEmissivity(backSideInfraredEmissivity);
  }

  bool WindowMaterialGlazingEquivalentLayer::setThermalResistance(double thermalResistance) {
    return getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->setThermalResistance(thermalResistance);
  }

  void WindowMaterialGlazingEquivalentLayer::resetOpticalDataType() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetOpticalDataType();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideBeamBeamVisibleSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideBeamBeamVisibleSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideBeamBeamVisibleSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideBeamBeamVisibleSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideBeamBeamVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideBeamBeamVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideBeamBeamVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideBeamBeamVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideBeamDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideBeamDiffuseSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideBeamDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideBeamDiffuseSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideBeamDiffuseSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideBeamDiffuseSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideBeamDiffuseSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideBeamDiffuseSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideBeamDiffuseVisibleSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideBeamDiffuseVisibleSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideBeamDiffuseVisibleSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideBeamDiffuseVisibleSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideBeamDiffuseVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideBeamDiffuseVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideBeamDiffuseVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideBeamDiffuseVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetDiffuseDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetDiffuseDiffuseSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideDiffuseDiffuseSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideDiffuseDiffuseSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideDiffuseDiffuseSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideDiffuseDiffuseSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetDiffuseDiffuseVisibleSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetDiffuseDiffuseVisibleSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideDiffuseDiffuseVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideDiffuseDiffuseVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideDiffuseDiffuseVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideDiffuseDiffuseVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetInfraredTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetInfraredTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::resetFrontSideInfraredEmissivity() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetFrontSideInfraredEmissivity();
  }

  void WindowMaterialGlazingEquivalentLayer::resetBackSideInfraredEmissivity() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetBackSideInfraredEmissivity();
  }

  void WindowMaterialGlazingEquivalentLayer::resetThermalResistance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->resetThermalResistance();
  }

  void WindowMaterialGlazingEquivalentLayer::autocalculateDiffuseDiffuseSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->autocalculateDiffuseDiffuseSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::autocalculateFrontSideDiffuseDiffuseSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->autocalculateFrontSideDiffuseDiffuseSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::autocalculateBackSideDiffuseDiffuseSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->autocalculateBackSideDiffuseDiffuseSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::autocalculateDiffuseDiffuseVisibleSolarTransmittance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->autocalculateDiffuseDiffuseVisibleSolarTransmittance();
  }

  void WindowMaterialGlazingEquivalentLayer::autocalculateFrontSideDiffuseDiffuseVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->autocalculateFrontSideDiffuseDiffuseVisibleSolarReflectance();
  }

  void WindowMaterialGlazingEquivalentLayer::autocalculateBackSideDiffuseDiffuseVisibleSolarReflectance() {
    getImpl<detail::WindowMaterialGlazingEquivalentLayer_Impl>()->autocalculateBackSideDiffuseDiffuseVisibleSolarReflectance();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WindowMaterialGlazingEquivalentLayer_Impl::opticalDataType() const {
      const auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::OpticalDataType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isOpticalDataTypeDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::OpticalDataType);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setOpticalDataType(const std::string& opticalDataType) {
      return setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::OpticalDataType, opticalDataType);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetOpticalDataType() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::OpticalDataType, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamBeamSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamBeamSolarTransmittance(double value) {
      const bool result = setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamSolarTransmittance, value);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamBeamSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamBeamSolarTransmittance(double value) {
      const bool result = setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamSolarTransmittance, value);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamBeamSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamBeamSolarReflectance(double value) {
      const bool result = setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamSolarReflectance, value);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamBeamSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamBeamSolarReflectance(double value) {
      const bool result = setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamSolarReflectance, value);
      OS_ASSERT(result);
      return result;
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamBeamVisibleSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideBeamBeamVisibleSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamBeamVisibleSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideBeamBeamVisibleSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarTransmittance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamBeamVisibleSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideBeamBeamVisibleSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamBeamVisibleSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideBeamBeamVisibleSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarTransmittance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamBeamVisibleSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideBeamBeamVisibleSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamBeamVisibleSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideBeamBeamVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarReflectance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamBeamVisibleSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideBeamBeamVisibleSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamBeamVisibleSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideBeamBeamVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarReflectance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideBeamDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamDiffuseSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideBeamDiffuseSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarTransmittance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamDiffuseSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideBeamDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamDiffuseSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideBeamDiffuseSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarTransmittance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideBeamDiffuseSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamDiffuseSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideBeamDiffuseSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarReflectance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamDiffuseSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideBeamDiffuseSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamDiffuseSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideBeamDiffuseSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarReflectance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamDiffuseVisibleSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamDiffuseVisibleSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideBeamDiffuseVisibleSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarTransmittance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamDiffuseVisibleSolarTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideBeamDiffuseVisibleSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamDiffuseVisibleSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideBeamDiffuseVisibleSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarTransmittance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideBeamDiffuseVisibleSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideBeamDiffuseVisibleSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideBeamDiffuseVisibleSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideBeamDiffuseVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarReflectance, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideBeamDiffuseVisibleSolarReflectance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarReflectance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideBeamDiffuseVisibleSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideBeamDiffuseVisibleSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideBeamDiffuseVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarReflectance, ""));
    }

    boost::optional<double> WindowMaterialGlazingEquivalentLayer_Impl::diffuseDiffuseSolarTransmittance() const {
      return getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance, true);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isDiffuseDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isDiffuseDiffuseSolarTransmittanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setDiffuseDiffuseSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetDiffuseDiffuseSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance, ""));
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::autocalculateDiffuseDiffuseSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance, "autocalculate"));
    }

    boost::optional<double> WindowMaterialGlazingEquivalentLayer_Impl::frontSideDiffuseDiffuseSolarReflectance() const {
      return getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance, true);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideDiffuseDiffuseSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideDiffuseDiffuseSolarReflectanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideDiffuseDiffuseSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideDiffuseDiffuseSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance, ""));
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::autocalculateFrontSideDiffuseDiffuseSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance, "autocalculate"));
    }

    boost::optional<double> WindowMaterialGlazingEquivalentLayer_Impl::backSideDiffuseDiffuseSolarReflectance() const {
      return getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance, true);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideDiffuseDiffuseSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideDiffuseDiffuseSolarReflectanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideDiffuseDiffuseSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideDiffuseDiffuseSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance, ""));
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::autocalculateBackSideDiffuseDiffuseSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance, "autocalculate"));
    }

    boost::optional<double> WindowMaterialGlazingEquivalentLayer_Impl::diffuseDiffuseVisibleSolarTransmittance() const {
      return getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance, true);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isDiffuseDiffuseVisibleSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isDiffuseDiffuseVisibleSolarTransmittanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setDiffuseDiffuseVisibleSolarTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetDiffuseDiffuseVisibleSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance, ""));
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::autocalculateDiffuseDiffuseVisibleSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance, "autocalculate"));
    }

    boost::optional<double> WindowMaterialGlazingEquivalentLayer_Impl::frontSideDiffuseDiffuseVisibleSolarReflectance() const {
      return getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance, true);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideDiffuseDiffuseVisibleSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideDiffuseDiffuseVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance, ""));
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::autocalculateFrontSideDiffuseDiffuseVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance, "autocalculate"));
    }

    boost::optional<double> WindowMaterialGlazingEquivalentLayer_Impl::backSideDiffuseDiffuseVisibleSolarReflectance() const {
      return getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance, true);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideDiffuseDiffuseVisibleSolarReflectanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideDiffuseDiffuseVisibleSolarReflectanceAutocalculated() const {
      if (auto value = getString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideDiffuseDiffuseVisibleSolarReflectance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideDiffuseDiffuseVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance, ""));
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::autocalculateBackSideDiffuseDiffuseVisibleSolarReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance, "autocalculate"));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::infraredTransmittance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::InfraredTransmittance_appliestofrontandback_, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isInfraredTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::InfraredTransmittance_appliestofrontandback_);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setInfraredTransmittance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::InfraredTransmittance_appliestofrontandback_, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetInfraredTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::InfraredTransmittance_appliestofrontandback_, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::frontSideInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isFrontSideInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideInfraredEmissivity);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setFrontSideInfraredEmissivity(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideInfraredEmissivity, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetFrontSideInfraredEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::FrontSideInfraredEmissivity, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::backSideInfraredEmissivity() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideInfraredEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isBackSideInfraredEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideInfraredEmissivity);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setBackSideInfraredEmissivity(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideInfraredEmissivity, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetBackSideInfraredEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::BackSideInfraredEmissivity, ""));
    }

    double WindowMaterialGlazingEquivalentLayer_Impl::thermalResistance() const {
      const auto value = getDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::ThermalResistance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::isThermalResistanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::ThermalResistance);
    }

    bool WindowMaterialGlazingEquivalentLayer_Impl::setThermalResistance(double value) {
      return setDouble(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::ThermalResistance, value);
    }

    void WindowMaterialGlazingEquivalentLayer_Impl::resetThermalResistance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_Glazing_EquivalentLayerFields::ThermalResistance, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
