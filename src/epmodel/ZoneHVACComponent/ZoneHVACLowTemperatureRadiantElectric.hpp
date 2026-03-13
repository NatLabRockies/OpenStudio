/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_HPP
#define EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACLowTemperatureRadiantElectric_Impl;
  }

  class EPMODEL_API ZoneHVACLowTemperatureRadiantElectric : public ModelObject
  {
   public:
    explicit ZoneHVACLowTemperatureRadiantElectric(const Model& model);

    virtual ~ZoneHVACLowTemperatureRadiantElectric() override = default;
    ZoneHVACLowTemperatureRadiantElectric(const ZoneHVACLowTemperatureRadiantElectric& other) = default;
    ZoneHVACLowTemperatureRadiantElectric(ZoneHVACLowTemperatureRadiantElectric&& other) = default;
    ZoneHVACLowTemperatureRadiantElectric& operator=(const ZoneHVACLowTemperatureRadiantElectric&) = default;
    ZoneHVACLowTemperatureRadiantElectric& operator=(ZoneHVACLowTemperatureRadiantElectric&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> temperatureControlTypeValues();

    // Schema Alignment Notes:
    // - API: maximumElectricalPowertoPanel, temperatureControlType, setpointControlType, and heatingThrottlingRange map
    //   directly to the EnergyPlus ZoneHVAC:LowTemperatureRadiant:Electric fields enumerated by
    //   ZoneHVAC_LowTemperatureRadiant_ElectricFields in ForwardTranslateZoneHVACLowTemperatureRadiantElectric.cpp.
    //   Surface/relationship fields remain excluded from this scalar-focused API.

    // Maximum electrical power-to-panel accessors
    boost::optional<double> maximumElectricalPowertoPanel() const;
    bool isMaximumElectricalPowertoPanelDefaulted() const;
    bool isMaximumElectricalPowertoPanelAutosized() const;
    bool setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel);
    void resetMaximumElectricalPowertoPanel();
    void autosizeMaximumElectricalPowertoPanel();

    // Temperature control type accessors
    std::string temperatureControlType() const;
    bool isTemperatureControlTypeDefaulted() const;
    bool setTemperatureControlType(const std::string& temperatureControlType);
    void resetTemperatureControlType();

    // Setpoint control type accessors
    std::string setpointControlType() const;
    bool isSetpointControlTypeDefaulted() const;
    bool setSetpointControlType(const std::string& setpointControlType);
    void resetSetpointControlType();

    // Heating throttling range accessors
    double heatingThrottlingRange() const;
    bool isHeatingThrottlingRangeDefaulted() const;
    bool setHeatingThrottlingRange(double heatingThrottlingRange);
    void resetHeatingThrottlingRange();

   protected:
    using ImplType = detail::ZoneHVACLowTemperatureRadiantElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTemperatureRadiantElectric(std::shared_ptr<detail::ZoneHVACLowTemperatureRadiantElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
