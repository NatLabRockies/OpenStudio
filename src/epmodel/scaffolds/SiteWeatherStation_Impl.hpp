/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEWEATHERSTATION_IMPL_HPP
#define EPMODEL_SITEWEATHERSTATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteWeatherStation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteWeatherStation_Impl() override = default;

      double windSensorHeightAboveGround() const;
      bool isWindSensorHeightAboveGroundDefaulted() const;
      bool setWindSensorHeightAboveGround(double windSensorHeightAboveGround);
      void resetWindSensorHeightAboveGround();

      double windSpeedProfileExponent() const;
      bool isWindSpeedProfileExponentDefaulted() const;
      bool setWindSpeedProfileExponent(double windSpeedProfileExponent);
      void resetWindSpeedProfileExponent();

      double windSpeedProfileBoundaryLayerThickness() const;
      bool isWindSpeedProfileBoundaryLayerThicknessDefaulted() const;
      bool setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness);
      void resetWindSpeedProfileBoundaryLayerThickness();

      double airTemperatureSensorHeightAboveGround() const;
      bool isAirTemperatureSensorHeightAboveGroundDefaulted() const;
      bool setAirTemperatureSensorHeightAboveGround(double airTemperatureSensorHeightAboveGround);
      void resetAirTemperatureSensorHeightAboveGround();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
