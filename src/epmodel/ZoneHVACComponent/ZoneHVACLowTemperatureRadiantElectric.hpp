/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_HPP
#define EPMODEL_ZONEHVACLOWTEMPERATURERADIANTELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

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

  class EPMODEL_API ZoneHVACLowTemperatureRadiantElectric : public ZoneHVACComponent
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
    // - Status: Partial Parity. The scalar radiant-electric fields are aligned, but the surface/relationship links stay outside the public wrapper.
    // - Canonical Counterpart: openstudio::model::ZoneHVACLowTemperatureRadiantElectric.
    // - Implemented Parity: `maximumElectricalPowertoPanel`, `temperatureControlType`, `setpointControlType`, and `heatingThrottlingRange` map directly to the EnergyPlus object.
    // - Documented Delta: Surface and relationship fields remain excluded from this scalar-focused API.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while surface links are handled through explicit topology state.
    // - Evidence: `src/model/ZoneHVACLowTemperatureRadiantElectric.hpp`, `src/model/ZoneHVACLowTemperatureRadiantElectric.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACLowTemperatureRadiantElectric.cpp`, and `src/epmodel/test/ZoneHVACLowTemperatureRadiantElectric_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers only if the canonical wrapper still exposes them directly.

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
