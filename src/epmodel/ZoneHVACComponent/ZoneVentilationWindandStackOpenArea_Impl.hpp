/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_IMPL_HPP
#define EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ThermalZone;

  namespace detail {

    class EPMODEL_API ZoneVentilationWindandStackOpenArea_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneVentilationWindandStackOpenArea_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      boost::optional<ThermalZone> thermalZone() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;

      double openingArea() const;
      bool setOpeningArea(double openingArea);

      boost::optional<double> openingEffectiveness() const;
      bool setOpeningEffectiveness(double openingEffectiveness);
      bool isOpeningEffectivenessAutocalculated() const;
      void autocalculateOpeningEffectiveness();

      double effectiveAngle() const;
      bool setEffectiveAngle(double effectiveAngle);

      double heightDifference() const;
      bool setHeightDifference(double heightDifference);

      boost::optional<double> dischargeCoefficientforOpening() const;
      bool setDischargeCoefficientforOpening(double dischargeCoefficientforOpening);
      bool isDischargeCoefficientforOpeningAutocalculated() const;
      void autocalculateDischargeCoefficientforOpening();

      double minimumIndoorTemperature() const;
      bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

      double maximumIndoorTemperature() const;
      bool setMaximumIndoorTemperature(double maximumIndoorTemperature);

      double deltaTemperature() const;
      bool setDeltaTemperature(double deltaTemperature);

      double minimumOutdoorTemperature() const;
      bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

      double maximumOutdoorTemperature() const;
      bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

      double maximumWindSpeed() const;
      bool setMaximumWindSpeed(double maximumWindSpeed);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
