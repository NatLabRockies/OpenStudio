/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Blind.hpp"
#include "Blind_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WindowMaterial_Blind_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Blind::Blind(const Model& model) : ModelObject(Blind::iddObjectType(), model) {}

  Blind::Blind(std::shared_ptr<detail::Blind_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Blind::iddObjectType() {
    return IddObjectType::WindowMaterial_Blind;
  }

  std::vector<std::string> Blind::slatOrientationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowMaterial_BlindFields::SlatOrientation);
  }

  std::string Blind::slatOrientation() const {
    return getImpl<detail::Blind_Impl>()->slatOrientation();
  }

  bool Blind::isSlatOrientationDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatOrientationDefaulted();
  }

  double Blind::slatWidth() const {
    return getImpl<detail::Blind_Impl>()->slatWidth();
  }

  double Blind::slatSeparation() const {
    return getImpl<detail::Blind_Impl>()->slatSeparation();
  }

  double Blind::slatThickness() const {
    return getImpl<detail::Blind_Impl>()->slatThickness();
  }

  bool Blind::isSlatThicknessDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatThicknessDefaulted();
  }

  double Blind::slatCurve() const {
    return getImpl<detail::Blind_Impl>()->slatCurve();
  }

  bool Blind::isSlatCurveDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatCurveDefaulted();
  }

  double Blind::slatAngle() const {
    return getImpl<detail::Blind_Impl>()->slatAngle();
  }

  bool Blind::isSlatAngleDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatAngleDefaulted();
  }

  double Blind::slatConductivity() const {
    return getImpl<detail::Blind_Impl>()->slatConductivity();
  }

  bool Blind::isSlatConductivityDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatConductivityDefaulted();
  }

  double Blind::slatBeamSolarTransmittance() const {
    return getImpl<detail::Blind_Impl>()->slatBeamSolarTransmittance();
  }

  bool Blind::isSlatBeamSolarTransmittanceDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatBeamSolarTransmittanceDefaulted();
  }

  double Blind::frontSideSlatBeamSolarReflectance() const {
    return getImpl<detail::Blind_Impl>()->frontSideSlatBeamSolarReflectance();
  }

  double Blind::backSideSlatBeamSolarReflectance() const {
    return getImpl<detail::Blind_Impl>()->backSideSlatBeamSolarReflectance();
  }

  double Blind::slatDiffuseSolarTransmittance() const {
    return getImpl<detail::Blind_Impl>()->slatDiffuseSolarTransmittance();
  }

  bool Blind::isSlatDiffuseSolarTransmittanceDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatDiffuseSolarTransmittanceDefaulted();
  }

  double Blind::frontSideSlatDiffuseSolarReflectance() const {
    return getImpl<detail::Blind_Impl>()->frontSideSlatDiffuseSolarReflectance();
  }

  double Blind::backSideSlatDiffuseSolarReflectance() const {
    return getImpl<detail::Blind_Impl>()->backSideSlatDiffuseSolarReflectance();
  }

  double Blind::slatBeamVisibleTransmittance() const {
    return getImpl<detail::Blind_Impl>()->slatBeamVisibleTransmittance();
  }

  boost::optional<double> Blind::frontSideSlatBeamVisibleReflectance() const {
    return getImpl<detail::Blind_Impl>()->frontSideSlatBeamVisibleReflectance();
  }

  boost::optional<double> Blind::backSideSlatBeamVisibleReflectance() const {
    return getImpl<detail::Blind_Impl>()->backSideSlatBeamVisibleReflectance();
  }

  double Blind::slatDiffuseVisibleTransmittance() const {
    return getImpl<detail::Blind_Impl>()->slatDiffuseVisibleTransmittance();
  }

  bool Blind::isSlatDiffuseVisibleTransmittanceDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatDiffuseVisibleTransmittanceDefaulted();
  }

  boost::optional<double> Blind::frontSideSlatDiffuseVisibleReflectance() const {
    return getImpl<detail::Blind_Impl>()->frontSideSlatDiffuseVisibleReflectance();
  }

  boost::optional<double> Blind::backSideSlatDiffuseVisibleReflectance() const {
    return getImpl<detail::Blind_Impl>()->backSideSlatDiffuseVisibleReflectance();
  }

  double Blind::slatInfraredHemisphericalTransmittance() const {
    return getImpl<detail::Blind_Impl>()->slatInfraredHemisphericalTransmittance();
  }

  bool Blind::isSlatInfraredHemisphericalTransmittanceDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isSlatInfraredHemisphericalTransmittanceDefaulted();
  }

  double Blind::frontSideSlatInfraredHemisphericalEmissivity() const {
    return getImpl<detail::Blind_Impl>()->frontSideSlatInfraredHemisphericalEmissivity();
  }

  bool Blind::isFrontSideSlatInfraredHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isFrontSideSlatInfraredHemisphericalEmissivityDefaulted();
  }

  double Blind::backSideSlatInfraredHemisphericalEmissivity() const {
    return getImpl<detail::Blind_Impl>()->backSideSlatInfraredHemisphericalEmissivity();
  }

  bool Blind::isBackSideSlatInfraredHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isBackSideSlatInfraredHemisphericalEmissivityDefaulted();
  }

  double Blind::blindtoGlassDistance() const {
    return getImpl<detail::Blind_Impl>()->blindtoGlassDistance();
  }

  bool Blind::isBlindtoGlassDistanceDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isBlindtoGlassDistanceDefaulted();
  }

  double Blind::blindTopOpeningMultiplier() const {
    return getImpl<detail::Blind_Impl>()->blindTopOpeningMultiplier();
  }

  bool Blind::isBlindTopOpeningMultiplierDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isBlindTopOpeningMultiplierDefaulted();
  }

  double Blind::blindBottomOpeningMultiplier() const {
    return getImpl<detail::Blind_Impl>()->blindBottomOpeningMultiplier();
  }

  bool Blind::isBlindBottomOpeningMultiplierDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isBlindBottomOpeningMultiplierDefaulted();
  }

  double Blind::blindLeftSideOpeningMultiplier() const {
    return getImpl<detail::Blind_Impl>()->blindLeftSideOpeningMultiplier();
  }

  bool Blind::isBlindLeftSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isBlindLeftSideOpeningMultiplierDefaulted();
  }

  double Blind::blindRightSideOpeningMultiplier() const {
    return getImpl<detail::Blind_Impl>()->blindRightSideOpeningMultiplier();
  }

  bool Blind::isBlindRightSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isBlindRightSideOpeningMultiplierDefaulted();
  }

  double Blind::minimumSlatAngle() const {
    return getImpl<detail::Blind_Impl>()->minimumSlatAngle();
  }

  bool Blind::isMinimumSlatAngleDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isMinimumSlatAngleDefaulted();
  }

  double Blind::maximumSlatAngle() const {
    return getImpl<detail::Blind_Impl>()->maximumSlatAngle();
  }

  bool Blind::isMaximumSlatAngleDefaulted() const {
    return getImpl<detail::Blind_Impl>()->isMaximumSlatAngleDefaulted();
  }

  bool Blind::setSlatOrientation(const std::string& slatOrientation) {
    return getImpl<detail::Blind_Impl>()->setSlatOrientation(slatOrientation);
  }

  void Blind::resetSlatOrientation() {
    getImpl<detail::Blind_Impl>()->resetSlatOrientation();
  }

  bool Blind::setSlatWidth(double slatWidth) {
    return getImpl<detail::Blind_Impl>()->setSlatWidth(slatWidth);
  }

  bool Blind::setSlatSeparation(double slatSeparation) {
    return getImpl<detail::Blind_Impl>()->setSlatSeparation(slatSeparation);
  }

  bool Blind::setSlatThickness(double slatThickness) {
    return getImpl<detail::Blind_Impl>()->setSlatThickness(slatThickness);
  }

  void Blind::resetSlatThickness() {
    getImpl<detail::Blind_Impl>()->resetSlatThickness();
  }

  bool Blind::setSlatCurve(double slatCurve) {
    return getImpl<detail::Blind_Impl>()->setSlatCurve(slatCurve);
  }

  void Blind::resetSlatCurve() {
    getImpl<detail::Blind_Impl>()->resetSlatCurve();
  }

  bool Blind::setSlatAngle(double slatAngle) {
    return getImpl<detail::Blind_Impl>()->setSlatAngle(slatAngle);
  }

  void Blind::resetSlatAngle() {
    getImpl<detail::Blind_Impl>()->resetSlatAngle();
  }

  bool Blind::setSlatConductivity(double slatConductivity) {
    return getImpl<detail::Blind_Impl>()->setSlatConductivity(slatConductivity);
  }

  void Blind::resetSlatConductivity() {
    getImpl<detail::Blind_Impl>()->resetSlatConductivity();
  }

  bool Blind::setSlatBeamSolarTransmittance(double slatBeamSolarTransmittance) {
    return getImpl<detail::Blind_Impl>()->setSlatBeamSolarTransmittance(slatBeamSolarTransmittance);
  }

  void Blind::resetSlatBeamSolarTransmittance() {
    getImpl<detail::Blind_Impl>()->resetSlatBeamSolarTransmittance();
  }

  bool Blind::setFrontSideSlatBeamSolarReflectance(double frontSideSlatBeamSolarReflectance) {
    return getImpl<detail::Blind_Impl>()->setFrontSideSlatBeamSolarReflectance(frontSideSlatBeamSolarReflectance);
  }

  bool Blind::setBackSideSlatBeamSolarReflectance(double backSideSlatBeamSolarReflectance) {
    return getImpl<detail::Blind_Impl>()->setBackSideSlatBeamSolarReflectance(backSideSlatBeamSolarReflectance);
  }

  bool Blind::setSlatDiffuseSolarTransmittance(double slatDiffuseSolarTransmittance) {
    return getImpl<detail::Blind_Impl>()->setSlatDiffuseSolarTransmittance(slatDiffuseSolarTransmittance);
  }

  void Blind::resetSlatDiffuseSolarTransmittance() {
    getImpl<detail::Blind_Impl>()->resetSlatDiffuseSolarTransmittance();
  }

  bool Blind::setFrontSideSlatDiffuseSolarReflectance(double frontSideSlatDiffuseSolarReflectance) {
    return getImpl<detail::Blind_Impl>()->setFrontSideSlatDiffuseSolarReflectance(frontSideSlatDiffuseSolarReflectance);
  }

  bool Blind::setBackSideSlatDiffuseSolarReflectance(double backSideSlatDiffuseSolarReflectance) {
    return getImpl<detail::Blind_Impl>()->setBackSideSlatDiffuseSolarReflectance(backSideSlatDiffuseSolarReflectance);
  }

  bool Blind::setSlatBeamVisibleTransmittance(double slatBeamVisibleTransmittance) {
    return getImpl<detail::Blind_Impl>()->setSlatBeamVisibleTransmittance(slatBeamVisibleTransmittance);
  }

  bool Blind::setFrontSideSlatBeamVisibleReflectance(double frontSideSlatBeamVisibleReflectance) {
    return getImpl<detail::Blind_Impl>()->setFrontSideSlatBeamVisibleReflectance(frontSideSlatBeamVisibleReflectance);
  }

  void Blind::resetFrontSideSlatBeamVisibleReflectance() {
    getImpl<detail::Blind_Impl>()->resetFrontSideSlatBeamVisibleReflectance();
  }

  bool Blind::setBackSideSlatBeamVisibleReflectance(double backSideSlatBeamVisibleReflectance) {
    return getImpl<detail::Blind_Impl>()->setBackSideSlatBeamVisibleReflectance(backSideSlatBeamVisibleReflectance);
  }

  void Blind::resetBackSideSlatBeamVisibleReflectance() {
    getImpl<detail::Blind_Impl>()->resetBackSideSlatBeamVisibleReflectance();
  }

  bool Blind::setSlatDiffuseVisibleTransmittance(double slatDiffuseVisibleTransmittance) {
    return getImpl<detail::Blind_Impl>()->setSlatDiffuseVisibleTransmittance(slatDiffuseVisibleTransmittance);
  }

  void Blind::resetSlatDiffuseVisibleTransmittance() {
    getImpl<detail::Blind_Impl>()->resetSlatDiffuseVisibleTransmittance();
  }

  bool Blind::setFrontSideSlatDiffuseVisibleReflectance(double frontSideSlatDiffuseVisibleReflectance) {
    return getImpl<detail::Blind_Impl>()->setFrontSideSlatDiffuseVisibleReflectance(frontSideSlatDiffuseVisibleReflectance);
  }

  void Blind::resetFrontSideSlatDiffuseVisibleReflectance() {
    getImpl<detail::Blind_Impl>()->resetFrontSideSlatDiffuseVisibleReflectance();
  }

  bool Blind::setBackSideSlatDiffuseVisibleReflectance(double backSideSlatDiffuseVisibleReflectance) {
    return getImpl<detail::Blind_Impl>()->setBackSideSlatDiffuseVisibleReflectance(backSideSlatDiffuseVisibleReflectance);
  }

  void Blind::resetBackSideSlatDiffuseVisibleReflectance() {
    getImpl<detail::Blind_Impl>()->resetBackSideSlatDiffuseVisibleReflectance();
  }

  bool Blind::setSlatInfraredHemisphericalTransmittance(double slatInfraredHemisphericalTransmittance) {
    return getImpl<detail::Blind_Impl>()->setSlatInfraredHemisphericalTransmittance(slatInfraredHemisphericalTransmittance);
  }

  void Blind::resetSlatInfraredHemisphericalTransmittance() {
    getImpl<detail::Blind_Impl>()->resetSlatInfraredHemisphericalTransmittance();
  }

  bool Blind::setFrontSideSlatInfraredHemisphericalEmissivity(double frontSideSlatInfraredHemisphericalEmissivity) {
    return getImpl<detail::Blind_Impl>()->setFrontSideSlatInfraredHemisphericalEmissivity(frontSideSlatInfraredHemisphericalEmissivity);
  }

  void Blind::resetFrontSideSlatInfraredHemisphericalEmissivity() {
    getImpl<detail::Blind_Impl>()->resetFrontSideSlatInfraredHemisphericalEmissivity();
  }

  bool Blind::setBackSideSlatInfraredHemisphericalEmissivity(double backSideSlatInfraredHemisphericalEmissivity) {
    return getImpl<detail::Blind_Impl>()->setBackSideSlatInfraredHemisphericalEmissivity(backSideSlatInfraredHemisphericalEmissivity);
  }

  void Blind::resetBackSideSlatInfraredHemisphericalEmissivity() {
    getImpl<detail::Blind_Impl>()->resetBackSideSlatInfraredHemisphericalEmissivity();
  }

  bool Blind::setBlindtoGlassDistance(double blindtoGlassDistance) {
    return getImpl<detail::Blind_Impl>()->setBlindtoGlassDistance(blindtoGlassDistance);
  }

  void Blind::resetBlindtoGlassDistance() {
    getImpl<detail::Blind_Impl>()->resetBlindtoGlassDistance();
  }

  bool Blind::setBlindTopOpeningMultiplier(double blindTopOpeningMultiplier) {
    return getImpl<detail::Blind_Impl>()->setBlindTopOpeningMultiplier(blindTopOpeningMultiplier);
  }

  void Blind::resetBlindTopOpeningMultiplier() {
    getImpl<detail::Blind_Impl>()->resetBlindTopOpeningMultiplier();
  }

  bool Blind::setBlindBottomOpeningMultiplier(double blindBottomOpeningMultiplier) {
    return getImpl<detail::Blind_Impl>()->setBlindBottomOpeningMultiplier(blindBottomOpeningMultiplier);
  }

  void Blind::resetBlindBottomOpeningMultiplier() {
    getImpl<detail::Blind_Impl>()->resetBlindBottomOpeningMultiplier();
  }

  bool Blind::setBlindLeftSideOpeningMultiplier(double blindLeftSideOpeningMultiplier) {
    return getImpl<detail::Blind_Impl>()->setBlindLeftSideOpeningMultiplier(blindLeftSideOpeningMultiplier);
  }

  void Blind::resetBlindLeftSideOpeningMultiplier() {
    getImpl<detail::Blind_Impl>()->resetBlindLeftSideOpeningMultiplier();
  }

  bool Blind::setBlindRightSideOpeningMultiplier(double blindRightSideOpeningMultiplier) {
    return getImpl<detail::Blind_Impl>()->setBlindRightSideOpeningMultiplier(blindRightSideOpeningMultiplier);
  }

  void Blind::resetBlindRightSideOpeningMultiplier() {
    getImpl<detail::Blind_Impl>()->resetBlindRightSideOpeningMultiplier();
  }

  bool Blind::setMinimumSlatAngle(double minimumSlatAngle) {
    return getImpl<detail::Blind_Impl>()->setMinimumSlatAngle(minimumSlatAngle);
  }

  void Blind::resetMinimumSlatAngle() {
    getImpl<detail::Blind_Impl>()->resetMinimumSlatAngle();
  }

  bool Blind::setMaximumSlatAngle(double maximumSlatAngle) {
    return getImpl<detail::Blind_Impl>()->setMaximumSlatAngle(maximumSlatAngle);
  }

  void Blind::resetMaximumSlatAngle() {
    getImpl<detail::Blind_Impl>()->resetMaximumSlatAngle();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string Blind_Impl::slatOrientation() const {
      boost::optional<std::string> value = getString(openstudio::WindowMaterial_BlindFields::SlatOrientation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatOrientation(const std::string& slatOrientation) {
      return setString(openstudio::WindowMaterial_BlindFields::SlatOrientation, slatOrientation);
    }

    void Blind_Impl::resetSlatOrientation() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatOrientation, ""));
    }

    bool Blind_Impl::isSlatOrientationDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatOrientation);
    }

    double Blind_Impl::slatWidth() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatWidth, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatWidth(double slatWidth) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatWidth, slatWidth);
      OS_ASSERT(result);
      return result;
    }

    double Blind_Impl::slatSeparation() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatSeparation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatSeparation(double slatSeparation) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatSeparation, slatSeparation);
      OS_ASSERT(result);
      return result;
    }

    double Blind_Impl::slatThickness() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatThickness, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatThickness(double slatThickness) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatThickness, slatThickness);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatThicknessDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatThickness);
    }

    void Blind_Impl::resetSlatThickness() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatThickness, ""));
    }

    double Blind_Impl::slatCurve() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatCurve(double slatCurve) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, slatCurve);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatCurveDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance);
    }

    void Blind_Impl::resetSlatCurve() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, ""));
    }

    double Blind_Impl::slatAngle() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatAngle, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatAngle(double slatAngle) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatAngle, slatAngle);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatAngleDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatAngle);
    }

    void Blind_Impl::resetSlatAngle() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatAngle, ""));
    }

    double Blind_Impl::slatConductivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatConductivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatConductivity(double slatConductivity) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatConductivity, slatConductivity);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatConductivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatConductivity);
    }

    void Blind_Impl::resetSlatConductivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatConductivity, ""));
    }

    double Blind_Impl::slatBeamSolarTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatBeamSolarTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatBeamSolarTransmittance(double slatBeamSolarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatBeamSolarTransmittance, slatBeamSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatBeamSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatBeamSolarTransmittance);
    }

    void Blind_Impl::resetSlatBeamSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatBeamSolarTransmittance, ""));
    }

    double Blind_Impl::frontSideSlatBeamSolarReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatBeamSolarReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setFrontSideSlatBeamSolarReflectance(double frontSideSlatBeamSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatBeamSolarReflectance, frontSideSlatBeamSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double Blind_Impl::backSideSlatBeamSolarReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamSolarReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBackSideSlatBeamSolarReflectance(double backSideSlatBeamSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamSolarReflectance, backSideSlatBeamSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double Blind_Impl::slatDiffuseSolarTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatDiffuseSolarTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatDiffuseSolarTransmittance(double slatDiffuseSolarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatDiffuseSolarTransmittance, slatDiffuseSolarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatDiffuseSolarTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatDiffuseSolarTransmittance);
    }

    void Blind_Impl::resetSlatDiffuseSolarTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatDiffuseSolarTransmittance, ""));
    }

    double Blind_Impl::frontSideSlatDiffuseSolarReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setFrontSideSlatDiffuseSolarReflectance(double frontSideSlatDiffuseSolarReflectance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatDiffuseSolarReflectance, frontSideSlatDiffuseSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double Blind_Impl::backSideSlatDiffuseSolarReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatDiffuseSolarReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBackSideSlatDiffuseSolarReflectance(double backSideSlatDiffuseSolarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatDiffuseSolarReflectance, backSideSlatDiffuseSolarReflectance);
      OS_ASSERT(result);
      return result;
    }

    double Blind_Impl::slatBeamVisibleTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatBeamVisibleTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatBeamVisibleTransmittance(double slatBeamVisibleTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatBeamVisibleTransmittance, slatBeamVisibleTransmittance);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> Blind_Impl::frontSideSlatBeamVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatBeamVisibleReflectance, true);
    }

    bool Blind_Impl::setFrontSideSlatBeamVisibleReflectance(double frontSideSlatBeamVisibleReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatBeamVisibleReflectance, frontSideSlatBeamVisibleReflectance);
      OS_ASSERT(result);
      return result;
    }

    void Blind_Impl::resetFrontSideSlatBeamVisibleReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::FrontSideSlatBeamVisibleReflectance, ""));
    }

    boost::optional<double> Blind_Impl::backSideSlatBeamVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, true);
    }

    bool Blind_Impl::setBackSideSlatBeamVisibleReflectance(double backSideSlatBeamVisibleReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, backSideSlatBeamVisibleReflectance);
      OS_ASSERT(result);
      return result;
    }

    void Blind_Impl::resetBackSideSlatBeamVisibleReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, ""));
    }

    double Blind_Impl::slatDiffuseVisibleTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatDiffuseVisibleTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatDiffuseVisibleTransmittance(double slatDiffuseVisibleTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::SlatDiffuseVisibleTransmittance, slatDiffuseVisibleTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatDiffuseVisibleTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatDiffuseVisibleTransmittance);
    }

    void Blind_Impl::resetSlatDiffuseVisibleTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatDiffuseVisibleTransmittance, ""));
    }

    boost::optional<double> Blind_Impl::frontSideSlatDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatDiffuseVisibleReflectance, true);
    }

    bool Blind_Impl::setFrontSideSlatDiffuseVisibleReflectance(double frontSideSlatDiffuseVisibleReflectance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatDiffuseVisibleReflectance, frontSideSlatDiffuseVisibleReflectance);
      OS_ASSERT(result);
      return result;
    }

    void Blind_Impl::resetFrontSideSlatDiffuseVisibleReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::FrontSideSlatDiffuseVisibleReflectance, ""));
    }

    boost::optional<double> Blind_Impl::backSideSlatDiffuseVisibleReflectance() const {
      return getDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatDiffuseVisibleReflectance, true);
    }

    bool Blind_Impl::setBackSideSlatDiffuseVisibleReflectance(double backSideSlatDiffuseVisibleReflectance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatDiffuseVisibleReflectance, backSideSlatDiffuseVisibleReflectance);
      OS_ASSERT(result);
      return result;
    }

    void Blind_Impl::resetBackSideSlatDiffuseVisibleReflectance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BackSideSlatDiffuseVisibleReflectance, ""));
    }

    double Blind_Impl::slatInfraredHemisphericalTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::SlatInfraredHemisphericalTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setSlatInfraredHemisphericalTransmittance(double slatInfraredHemisphericalTransmittance) {
      const bool result =
        setDouble(openstudio::WindowMaterial_BlindFields::SlatInfraredHemisphericalTransmittance, slatInfraredHemisphericalTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isSlatInfraredHemisphericalTransmittanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::SlatInfraredHemisphericalTransmittance);
    }

    void Blind_Impl::resetSlatInfraredHemisphericalTransmittance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::SlatInfraredHemisphericalTransmittance, ""));
    }

    double Blind_Impl::frontSideSlatInfraredHemisphericalEmissivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatInfraredHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setFrontSideSlatInfraredHemisphericalEmissivity(double frontSideSlatInfraredHemisphericalEmissivity) {
      const bool result =
        setDouble(openstudio::WindowMaterial_BlindFields::FrontSideSlatInfraredHemisphericalEmissivity, frontSideSlatInfraredHemisphericalEmissivity);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isFrontSideSlatInfraredHemisphericalEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::FrontSideSlatInfraredHemisphericalEmissivity);
    }

    void Blind_Impl::resetFrontSideSlatInfraredHemisphericalEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::FrontSideSlatInfraredHemisphericalEmissivity, ""));
    }

    double Blind_Impl::backSideSlatInfraredHemisphericalEmissivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatInfraredHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBackSideSlatInfraredHemisphericalEmissivity(double backSideSlatInfraredHemisphericalEmissivity) {
      const bool result =
        setDouble(openstudio::WindowMaterial_BlindFields::BackSideSlatInfraredHemisphericalEmissivity, backSideSlatInfraredHemisphericalEmissivity);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isBackSideSlatInfraredHemisphericalEmissivityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BackSideSlatInfraredHemisphericalEmissivity);
    }

    void Blind_Impl::resetBackSideSlatInfraredHemisphericalEmissivity() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BackSideSlatInfraredHemisphericalEmissivity, ""));
    }

    double Blind_Impl::blindtoGlassDistance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BlindtoGlassDistance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBlindtoGlassDistance(double blindtoGlassDistance) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BlindtoGlassDistance, blindtoGlassDistance);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isBlindtoGlassDistanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BlindtoGlassDistance);
    }

    void Blind_Impl::resetBlindtoGlassDistance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BlindtoGlassDistance, ""));
    }

    double Blind_Impl::blindTopOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BlindTopOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBlindTopOpeningMultiplier(double blindTopOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BlindTopOpeningMultiplier, blindTopOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isBlindTopOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BlindTopOpeningMultiplier);
    }

    void Blind_Impl::resetBlindTopOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BlindTopOpeningMultiplier, ""));
    }

    double Blind_Impl::blindBottomOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BlindBottomOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBlindBottomOpeningMultiplier(double blindBottomOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BlindBottomOpeningMultiplier, blindBottomOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isBlindBottomOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BlindBottomOpeningMultiplier);
    }

    void Blind_Impl::resetBlindBottomOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BlindBottomOpeningMultiplier, ""));
    }

    double Blind_Impl::blindLeftSideOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BlindLeftSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBlindLeftSideOpeningMultiplier(double blindLeftSideOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BlindLeftSideOpeningMultiplier, blindLeftSideOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isBlindLeftSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BlindLeftSideOpeningMultiplier);
    }

    void Blind_Impl::resetBlindLeftSideOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BlindLeftSideOpeningMultiplier, ""));
    }

    double Blind_Impl::blindRightSideOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::BlindRightSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setBlindRightSideOpeningMultiplier(double blindRightSideOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::BlindRightSideOpeningMultiplier, blindRightSideOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isBlindRightSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::BlindRightSideOpeningMultiplier);
    }

    void Blind_Impl::resetBlindRightSideOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::BlindRightSideOpeningMultiplier, ""));
    }

    double Blind_Impl::minimumSlatAngle() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::MinimumSlatAngle, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setMinimumSlatAngle(double minimumSlatAngle) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::MinimumSlatAngle, minimumSlatAngle);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isMinimumSlatAngleDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::MinimumSlatAngle);
    }

    void Blind_Impl::resetMinimumSlatAngle() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::MinimumSlatAngle, ""));
    }

    double Blind_Impl::maximumSlatAngle() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_BlindFields::MaximumSlatAngle, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Blind_Impl::setMaximumSlatAngle(double maximumSlatAngle) {
      const bool result = setDouble(openstudio::WindowMaterial_BlindFields::MaximumSlatAngle, maximumSlatAngle);
      OS_ASSERT(result);
      return result;
    }

    bool Blind_Impl::isMaximumSlatAngleDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_BlindFields::MaximumSlatAngle);
    }

    void Blind_Impl::resetMaximumSlatAngle() {
      OS_ASSERT(setString(openstudio::WindowMaterial_BlindFields::MaximumSlatAngle, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
