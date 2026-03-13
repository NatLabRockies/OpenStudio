/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/SurfacePropertyOtherSideCoefficients.hpp"
#include "ResourceObject/SurfacePropertyOtherSideCoefficients_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SurfaceProperty_OtherSideCoefficients_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    boost::optional<double> SurfacePropertyOtherSideCoefficients_Impl::combinedConvectiveRadiativeFilmCoefficient() const {
      return getDouble(SurfaceProperty_OtherSideCoefficientsFields::CombinedConvective_RadiativeFilmCoefficient, true);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setCombinedConvectiveRadiativeFilmCoefficient(double combinedConvectiveRadiativeFilmCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::CombinedConvective_RadiativeFilmCoefficient,
                       combinedConvectiveRadiativeFilmCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetCombinedConvectiveRadiativeFilmCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::CombinedConvective_RadiativeFilmCoefficient, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::constantTemperature() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isConstantTemperatureDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperature);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setConstantTemperature(double constantTemperature) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperature, constantTemperature);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetConstantTemperature() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperature, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::constantTemperatureCoefficient() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperatureCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isConstantTemperatureCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperatureCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setConstantTemperatureCoefficient(double constantTemperatureCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperatureCoefficient, constantTemperatureCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetConstantTemperatureCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::ConstantTemperatureCoefficient, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::externalDryBulbTemperatureCoefficient() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::ExternalDryBulbTemperatureCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isExternalDryBulbTemperatureCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::ExternalDryBulbTemperatureCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setExternalDryBulbTemperatureCoefficient(double externalDryBulbTemperatureCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::ExternalDryBulbTemperatureCoefficient, externalDryBulbTemperatureCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetExternalDryBulbTemperatureCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::ExternalDryBulbTemperatureCoefficient, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::groundTemperatureCoefficient() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::GroundTemperatureCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isGroundTemperatureCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::GroundTemperatureCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setGroundTemperatureCoefficient(double groundTemperatureCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::GroundTemperatureCoefficient, groundTemperatureCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetGroundTemperatureCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::GroundTemperatureCoefficient, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::windSpeedCoefficient() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::WindSpeedCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isWindSpeedCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::WindSpeedCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setWindSpeedCoefficient(double windSpeedCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::WindSpeedCoefficient, windSpeedCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetWindSpeedCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::WindSpeedCoefficient, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::zoneAirTemperatureCoefficient() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::ZoneAirTemperatureCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isZoneAirTemperatureCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::ZoneAirTemperatureCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setZoneAirTemperatureCoefficient(double zoneAirTemperatureCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::ZoneAirTemperatureCoefficient, zoneAirTemperatureCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetZoneAirTemperatureCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::ZoneAirTemperatureCoefficient, ""));
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::sinusoidalVariationofConstantTemperatureCoefficient() const {
      auto value = getString(SurfaceProperty_OtherSideCoefficientsFields::SinusoidalVariationofConstantTemperatureCoefficient, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(value.get(), "Yes");
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isSinusoidalVariationofConstantTemperatureCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::SinusoidalVariationofConstantTemperatureCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setSinusoidalVariationofConstantTemperatureCoefficient(
      bool sinusoidalVariationofConstantTemperatureCoefficient) {
      if (sinusoidalVariationofConstantTemperatureCoefficient) {
        return setString(SurfaceProperty_OtherSideCoefficientsFields::SinusoidalVariationofConstantTemperatureCoefficient, "Yes");
      }
      return setString(SurfaceProperty_OtherSideCoefficientsFields::SinusoidalVariationofConstantTemperatureCoefficient, "No");
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetSinusoidalVariationofConstantTemperatureCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::SinusoidalVariationofConstantTemperatureCoefficient, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::periodofSinusoidalVariation() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::PeriodofSinusoidalVariation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isPeriodofSinusoidalVariationDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::PeriodofSinusoidalVariation);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setPeriodofSinusoidalVariation(double periodofSinusoidalVariation) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::PeriodofSinusoidalVariation, periodofSinusoidalVariation);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetPeriodofSinusoidalVariation() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::PeriodofSinusoidalVariation, ""));
    }

    double SurfacePropertyOtherSideCoefficients_Impl::previousOtherSideTemperatureCoefficient() const {
      auto value = getDouble(SurfaceProperty_OtherSideCoefficientsFields::PreviousOtherSideTemperatureCoefficient, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::isPreviousOtherSideTemperatureCoefficientDefaulted() const {
      return isEmpty(SurfaceProperty_OtherSideCoefficientsFields::PreviousOtherSideTemperatureCoefficient);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setPreviousOtherSideTemperatureCoefficient(double previousOtherSideTemperatureCoefficient) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::PreviousOtherSideTemperatureCoefficient, previousOtherSideTemperatureCoefficient);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetPreviousOtherSideTemperatureCoefficient() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::PreviousOtherSideTemperatureCoefficient, ""));
    }

    boost::optional<double> SurfacePropertyOtherSideCoefficients_Impl::minimumOtherSideTemperatureLimit() const {
      return getDouble(SurfaceProperty_OtherSideCoefficientsFields::MinimumOtherSideTemperatureLimit, true);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setMinimumOtherSideTemperatureLimit(double minimumOtherSideTemperatureLimit) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::MinimumOtherSideTemperatureLimit, minimumOtherSideTemperatureLimit);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetMinimumOtherSideTemperatureLimit() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::MinimumOtherSideTemperatureLimit, ""));
    }

    boost::optional<double> SurfacePropertyOtherSideCoefficients_Impl::maximumOtherSideTemperatureLimit() const {
      return getDouble(SurfaceProperty_OtherSideCoefficientsFields::MaximumOtherSideTemperatureLimit, true);
    }

    bool SurfacePropertyOtherSideCoefficients_Impl::setMaximumOtherSideTemperatureLimit(double maximumOtherSideTemperatureLimit) {
      return setDouble(SurfaceProperty_OtherSideCoefficientsFields::MaximumOtherSideTemperatureLimit, maximumOtherSideTemperatureLimit);
    }

    void SurfacePropertyOtherSideCoefficients_Impl::resetMaximumOtherSideTemperatureLimit() {
      OS_ASSERT(setString(SurfaceProperty_OtherSideCoefficientsFields::MaximumOtherSideTemperatureLimit, ""));
    }

  }  // namespace detail

  SurfacePropertyOtherSideCoefficients::SurfacePropertyOtherSideCoefficients(const Model& model)
    : ModelObject(SurfacePropertyOtherSideCoefficients::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>());
  }

  IddObjectType SurfacePropertyOtherSideCoefficients::iddObjectType() {
    return IddObjectType::SurfaceProperty_OtherSideCoefficients;
  }

  boost::optional<double> SurfacePropertyOtherSideCoefficients::combinedConvectiveRadiativeFilmCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->combinedConvectiveRadiativeFilmCoefficient();
  }

  double SurfacePropertyOtherSideCoefficients::constantTemperature() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->constantTemperature();
  }

  bool SurfacePropertyOtherSideCoefficients::isConstantTemperatureDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isConstantTemperatureDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::constantTemperatureCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->constantTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isConstantTemperatureCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isConstantTemperatureCoefficientDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::externalDryBulbTemperatureCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->externalDryBulbTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isExternalDryBulbTemperatureCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isExternalDryBulbTemperatureCoefficientDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::groundTemperatureCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->groundTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isGroundTemperatureCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isGroundTemperatureCoefficientDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::windSpeedCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->windSpeedCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isWindSpeedCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isWindSpeedCoefficientDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::zoneAirTemperatureCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->zoneAirTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isZoneAirTemperatureCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isZoneAirTemperatureCoefficientDefaulted();
  }

  bool SurfacePropertyOtherSideCoefficients::sinusoidalVariationofConstantTemperatureCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->sinusoidalVariationofConstantTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isSinusoidalVariationofConstantTemperatureCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isSinusoidalVariationofConstantTemperatureCoefficientDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::periodofSinusoidalVariation() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->periodofSinusoidalVariation();
  }

  bool SurfacePropertyOtherSideCoefficients::isPeriodofSinusoidalVariationDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isPeriodofSinusoidalVariationDefaulted();
  }

  double SurfacePropertyOtherSideCoefficients::previousOtherSideTemperatureCoefficient() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->previousOtherSideTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::isPreviousOtherSideTemperatureCoefficientDefaulted() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->isPreviousOtherSideTemperatureCoefficientDefaulted();
  }

  boost::optional<double> SurfacePropertyOtherSideCoefficients::minimumOtherSideTemperatureLimit() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->minimumOtherSideTemperatureLimit();
  }

  boost::optional<double> SurfacePropertyOtherSideCoefficients::maximumOtherSideTemperatureLimit() const {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->maximumOtherSideTemperatureLimit();
  }

  bool SurfacePropertyOtherSideCoefficients::setCombinedConvectiveRadiativeFilmCoefficient(double combinedConvectiveRadiativeFilmCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setCombinedConvectiveRadiativeFilmCoefficient(
      combinedConvectiveRadiativeFilmCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetCombinedConvectiveRadiativeFilmCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetCombinedConvectiveRadiativeFilmCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setConstantTemperature(double constantTemperature) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setConstantTemperature(constantTemperature);
  }

  void SurfacePropertyOtherSideCoefficients::resetConstantTemperature() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetConstantTemperature();
  }

  bool SurfacePropertyOtherSideCoefficients::setConstantTemperatureCoefficient(double constantTemperatureCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setConstantTemperatureCoefficient(constantTemperatureCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetConstantTemperatureCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetConstantTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setExternalDryBulbTemperatureCoefficient(double externalDryBulbTemperatureCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setExternalDryBulbTemperatureCoefficient(
      externalDryBulbTemperatureCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetExternalDryBulbTemperatureCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetExternalDryBulbTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setGroundTemperatureCoefficient(double groundTemperatureCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setGroundTemperatureCoefficient(groundTemperatureCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetGroundTemperatureCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetGroundTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setWindSpeedCoefficient(double windSpeedCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setWindSpeedCoefficient(windSpeedCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetWindSpeedCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetWindSpeedCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setZoneAirTemperatureCoefficient(double zoneAirTemperatureCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setZoneAirTemperatureCoefficient(zoneAirTemperatureCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetZoneAirTemperatureCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetZoneAirTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setSinusoidalVariationofConstantTemperatureCoefficient(
    bool sinusoidalVariationofConstantTemperatureCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setSinusoidalVariationofConstantTemperatureCoefficient(
      sinusoidalVariationofConstantTemperatureCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetSinusoidalVariationofConstantTemperatureCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetSinusoidalVariationofConstantTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setPeriodofSinusoidalVariation(double periodofSinusoidalVariation) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setPeriodofSinusoidalVariation(periodofSinusoidalVariation);
  }

  void SurfacePropertyOtherSideCoefficients::resetPeriodofSinusoidalVariation() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetPeriodofSinusoidalVariation();
  }

  bool SurfacePropertyOtherSideCoefficients::setPreviousOtherSideTemperatureCoefficient(double previousOtherSideTemperatureCoefficient) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setPreviousOtherSideTemperatureCoefficient(
      previousOtherSideTemperatureCoefficient);
  }

  void SurfacePropertyOtherSideCoefficients::resetPreviousOtherSideTemperatureCoefficient() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetPreviousOtherSideTemperatureCoefficient();
  }

  bool SurfacePropertyOtherSideCoefficients::setMinimumOtherSideTemperatureLimit(double minimumOtherSideTemperatureLimit) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setMinimumOtherSideTemperatureLimit(minimumOtherSideTemperatureLimit);
  }

  void SurfacePropertyOtherSideCoefficients::resetMinimumOtherSideTemperatureLimit() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetMinimumOtherSideTemperatureLimit();
  }

  bool SurfacePropertyOtherSideCoefficients::setMaximumOtherSideTemperatureLimit(double maximumOtherSideTemperatureLimit) {
    return getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->setMaximumOtherSideTemperatureLimit(maximumOtherSideTemperatureLimit);
  }

  void SurfacePropertyOtherSideCoefficients::resetMaximumOtherSideTemperatureLimit() {
    getImpl<detail::SurfacePropertyOtherSideCoefficients_Impl>()->resetMaximumOtherSideTemperatureLimit();
  }

  SurfacePropertyOtherSideCoefficients::SurfacePropertyOtherSideCoefficients(std::shared_ptr<detail::SurfacePropertyOtherSideCoefficients_Impl> impl)
    : ModelObject(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio
