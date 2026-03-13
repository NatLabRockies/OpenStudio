/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEHEIGHTVARIATION_IMPL_HPP
#define EPMODEL_SITEHEIGHTVARIATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteHeightVariation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteHeightVariation_Impl() override = default;

      // WindSpeedProfileExponent accessors
      double windSpeedProfileExponent() const;
      bool isWindSpeedProfileExponentDefaulted() const;
      bool setWindSpeedProfileExponent(double windSpeedProfileExponent);
      void resetWindSpeedProfileExponent();

      // WindSpeedProfileBoundaryLayerThickness accessors
      double windSpeedProfileBoundaryLayerThickness() const;
      bool isWindSpeedProfileBoundaryLayerThicknessDefaulted() const;
      bool setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness);
      void resetWindSpeedProfileBoundaryLayerThickness();

      // AirTemperatureGradientCoefficient accessors
      double airTemperatureGradientCoefficient() const;
      bool isAirTemperatureGradientCoefficientDefaulted() const;
      bool setAirTemperatureGradientCoefficient(double airTemperatureGradientCoefficient);
      void resetAirTemperatureGradientCoefficient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
