/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteHeightVariation.hpp"
#include "SiteHeightVariation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_HeightVariation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteHeightVariation::SiteHeightVariation(const Model& model) : ModelObject(SiteHeightVariation::iddObjectType(), model) {}

  SiteHeightVariation::SiteHeightVariation(std::shared_ptr<detail::SiteHeightVariation_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteHeightVariation::iddObjectType() {
    return IddObjectType::Site_HeightVariation;
  }

  double SiteHeightVariation::windSpeedProfileExponent() const {
    return getImpl<detail::SiteHeightVariation_Impl>()->windSpeedProfileExponent();
  }

  bool SiteHeightVariation::isWindSpeedProfileExponentDefaulted() const {
    return getImpl<detail::SiteHeightVariation_Impl>()->isWindSpeedProfileExponentDefaulted();
  }

  bool SiteHeightVariation::setWindSpeedProfileExponent(double windSpeedProfileExponent) {
    return getImpl<detail::SiteHeightVariation_Impl>()->setWindSpeedProfileExponent(windSpeedProfileExponent);
  }

  void SiteHeightVariation::resetWindSpeedProfileExponent() {
    getImpl<detail::SiteHeightVariation_Impl>()->resetWindSpeedProfileExponent();
  }

  double SiteHeightVariation::windSpeedProfileBoundaryLayerThickness() const {
    return getImpl<detail::SiteHeightVariation_Impl>()->windSpeedProfileBoundaryLayerThickness();
  }

  bool SiteHeightVariation::isWindSpeedProfileBoundaryLayerThicknessDefaulted() const {
    return getImpl<detail::SiteHeightVariation_Impl>()->isWindSpeedProfileBoundaryLayerThicknessDefaulted();
  }

  bool SiteHeightVariation::setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness) {
    return getImpl<detail::SiteHeightVariation_Impl>()->setWindSpeedProfileBoundaryLayerThickness(windSpeedProfileBoundaryLayerThickness);
  }

  void SiteHeightVariation::resetWindSpeedProfileBoundaryLayerThickness() {
    getImpl<detail::SiteHeightVariation_Impl>()->resetWindSpeedProfileBoundaryLayerThickness();
  }

  double SiteHeightVariation::airTemperatureGradientCoefficient() const {
    return getImpl<detail::SiteHeightVariation_Impl>()->airTemperatureGradientCoefficient();
  }

  bool SiteHeightVariation::isAirTemperatureGradientCoefficientDefaulted() const {
    return getImpl<detail::SiteHeightVariation_Impl>()->isAirTemperatureGradientCoefficientDefaulted();
  }

  bool SiteHeightVariation::setAirTemperatureGradientCoefficient(double airTemperatureGradientCoefficient) {
    return getImpl<detail::SiteHeightVariation_Impl>()->setAirTemperatureGradientCoefficient(airTemperatureGradientCoefficient);
  }

  void SiteHeightVariation::resetAirTemperatureGradientCoefficient() {
    getImpl<detail::SiteHeightVariation_Impl>()->resetAirTemperatureGradientCoefficient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SiteHeightVariation_Impl::windSpeedProfileExponent() const {
      const auto value = getDouble(openstudio::Site_HeightVariationFields::WindSpeedProfileExponent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteHeightVariation_Impl::isWindSpeedProfileExponentDefaulted() const {
      return isEmpty(openstudio::Site_HeightVariationFields::WindSpeedProfileExponent);
    }

    bool SiteHeightVariation_Impl::setWindSpeedProfileExponent(double windSpeedProfileExponent) {
      return setDouble(openstudio::Site_HeightVariationFields::WindSpeedProfileExponent, windSpeedProfileExponent);
    }

    void SiteHeightVariation_Impl::resetWindSpeedProfileExponent() {
      OS_ASSERT(setString(openstudio::Site_HeightVariationFields::WindSpeedProfileExponent, ""));
    }

    double SiteHeightVariation_Impl::windSpeedProfileBoundaryLayerThickness() const {
      const auto value = getDouble(openstudio::Site_HeightVariationFields::WindSpeedProfileBoundaryLayerThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteHeightVariation_Impl::isWindSpeedProfileBoundaryLayerThicknessDefaulted() const {
      return isEmpty(openstudio::Site_HeightVariationFields::WindSpeedProfileBoundaryLayerThickness);
    }

    bool SiteHeightVariation_Impl::setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness) {
      return setDouble(openstudio::Site_HeightVariationFields::WindSpeedProfileBoundaryLayerThickness, windSpeedProfileBoundaryLayerThickness);
    }

    void SiteHeightVariation_Impl::resetWindSpeedProfileBoundaryLayerThickness() {
      OS_ASSERT(setString(openstudio::Site_HeightVariationFields::WindSpeedProfileBoundaryLayerThickness, ""));
    }

    double SiteHeightVariation_Impl::airTemperatureGradientCoefficient() const {
      const auto value = getDouble(openstudio::Site_HeightVariationFields::AirTemperatureGradientCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteHeightVariation_Impl::isAirTemperatureGradientCoefficientDefaulted() const {
      return isEmpty(openstudio::Site_HeightVariationFields::AirTemperatureGradientCoefficient);
    }

    bool SiteHeightVariation_Impl::setAirTemperatureGradientCoefficient(double airTemperatureGradientCoefficient) {
      return setDouble(openstudio::Site_HeightVariationFields::AirTemperatureGradientCoefficient, airTemperatureGradientCoefficient);
    }

    void SiteHeightVariation_Impl::resetAirTemperatureGradientCoefficient() {
      OS_ASSERT(setString(openstudio::Site_HeightVariationFields::AirTemperatureGradientCoefficient, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
