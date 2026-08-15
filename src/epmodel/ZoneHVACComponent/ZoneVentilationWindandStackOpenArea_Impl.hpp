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

  class Schedule;
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

      void doCanonicalize(LoadContext& context) override;

      double openingArea() const;
      bool setOpeningArea(double openingArea);
      Schedule openingAreaFractionSchedule() const;
      bool setOpeningAreaFractionSchedule(Schedule& schedule);

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
      boost::optional<Schedule> minimumIndoorTemperatureSchedule() const;
      bool setMinimumIndoorTemperatureSchedule(Schedule& schedule);
      void resetMinimumIndoorTemperatureSchedule();

      double maximumIndoorTemperature() const;
      bool setMaximumIndoorTemperature(double maximumIndoorTemperature);
      boost::optional<Schedule> maximumIndoorTemperatureSchedule() const;
      bool setMaximumIndoorTemperatureSchedule(Schedule& schedule);
      void resetMaximumIndoorTemperatureSchedule();

      double deltaTemperature() const;
      bool setDeltaTemperature(double deltaTemperature);
      boost::optional<Schedule> deltaTemperatureSchedule() const;
      bool setDeltaTemperatureSchedule(Schedule& schedule);
      void resetDeltaTemperatureSchedule();

      double minimumOutdoorTemperature() const;
      bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);
      boost::optional<Schedule> minimumOutdoorTemperatureSchedule() const;
      bool setMinimumOutdoorTemperatureSchedule(Schedule& schedule);
      void resetMinimumOutdoorTemperatureSchedule();

      double maximumOutdoorTemperature() const;
      bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);
      boost::optional<Schedule> maximumOutdoorTemperatureSchedule() const;
      bool setMaximumOutdoorTemperatureSchedule(Schedule& schedule);
      void resetMaximumOutdoorTemperatureSchedule();

      double maximumWindSpeed() const;
      bool setMaximumWindSpeed(double maximumWindSpeed);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
