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

  namespace detail {

    class EPMODEL_API ZoneHVACLowTemperatureRadiantElectric_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACLowTemperatureRadiantElectric_Impl() override = default;

      boost::optional<double> maximumElectricalPowertoPanel() const;
      bool isMaximumElectricalPowertoPanelDefaulted() const;
      bool isMaximumElectricalPowertoPanelAutosized() const;
      bool setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel);
      void resetMaximumElectricalPowertoPanel();
      void autosizeMaximumElectricalPowertoPanel();

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
