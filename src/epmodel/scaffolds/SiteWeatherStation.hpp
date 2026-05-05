/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEWEATHERSTATION_HPP
#define EPMODEL_SITEWEATHERSTATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteWeatherStation_Impl;
  }

  class EPMODEL_API SiteWeatherStation : public ModelObject
  {
   public:
    explicit SiteWeatherStation(const Model& model);

    virtual ~SiteWeatherStation() override = default;
    SiteWeatherStation(const SiteWeatherStation& other) = default;
    SiteWeatherStation(SiteWeatherStation&& other) = default;
    SiteWeatherStation& operator=(const SiteWeatherStation&) = default;
    SiteWeatherStation& operator=(SiteWeatherStation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Site:WeatherStation scalar fields.
    // - TODO(parity): Add non-scalar parity only if future schema changes introduce relationship-like fields.
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

   protected:
    using ImplType = detail::SiteWeatherStation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteWeatherStation(std::shared_ptr<detail::SiteWeatherStation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
