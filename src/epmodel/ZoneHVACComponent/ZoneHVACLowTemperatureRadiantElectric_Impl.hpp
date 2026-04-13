/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_IMPL_HPP
#define EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class Surface;
  class ZoneHVACLowTemperatureRadiantSurfaceGroup;

  namespace detail {

    class EPMODEL_API ZoneHVACLowTemperatureRadiantElectric_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACLowTemperatureRadiantElectric_Impl() override = default;

      unsigned inletPort() const;
      unsigned outletPort() const;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      Schedule heatingSetpointTemperatureSchedule() const;
      bool setHeatingSetpointTemperatureSchedule(Schedule& schedule);

      boost::optional<std::string> radiantSurfaceType() const;
      bool setRadiantSurfaceType(const std::string& radiantSurfaceType);
      void resetRadiantSurfaceType();
      std::vector<Surface> surfaces() const;
      boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> surfaceGroup() const;
      ZoneHVACLowTemperatureRadiantSurfaceGroup ensureSurfaceGroup();

      boost::optional<double> maximumElectricalPowertoPanel() const;
      bool isMaximumElectricalPowertoPanelDefaulted() const;
      bool isMaximumElectricalPowertoPanelAutosized() const;
      bool setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel);
      void resetMaximumElectricalPowertoPanel();
      void autosizeMaximumElectricalPowertoPanel();
      boost::optional<double> autosizedMaximumElectricalPowertoPanel() const;

      std::string temperatureControlType() const;
      bool isTemperatureControlTypeDefaulted() const;
      bool setTemperatureControlType(const std::string& temperatureControlType);
      void resetTemperatureControlType();

      std::string setpointControlType() const;
      bool isSetpointControlTypeDefaulted() const;
      bool setSetpointControlType(const std::string& setpointControlType);
      void resetSetpointControlType();

      double heatingThrottlingRange() const;
      bool isHeatingThrottlingRangeDefaulted() const;
      bool setHeatingThrottlingRange(double heatingThrottlingRange);
      void resetHeatingThrottlingRange();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
