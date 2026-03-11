/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLTHERMOSTATTHERMALCOMFORT_HPP
#define EPMODEL_ZONECONTROLTHERMOSTATTHERMALCOMFORT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneControlThermostatThermalComfort_Impl;
  }

  class EPMODEL_API ZoneControlThermostatThermalComfort : public ModelObject
  {
   public:
    explicit ZoneControlThermostatThermalComfort(const Model& model);

    virtual ~ZoneControlThermostatThermalComfort() override = default;
    ZoneControlThermostatThermalComfort(const ZoneControlThermostatThermalComfort& other) = default;
    ZoneControlThermostatThermalComfort(ZoneControlThermostatThermalComfort&& other) = default;
    ZoneControlThermostatThermalComfort& operator=(const ZoneControlThermostatThermalComfort&) = default;
    ZoneControlThermostatThermalComfort& operator=(ZoneControlThermostatThermalComfort&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> averagingMethodValues();

    // Schema Alignment Notes:
    // - API: Scalar accessors map directly to ZoneControl:Thermostat:ThermalComfort fields (Averaging Method, Minimum Dry-Bulb Temperature Setpoint, Maximum Dry-Bulb Temperature Setpoint).
    // - Field Mapping: Name, Zone or ZoneList Name, Thermal Comfort Control Type Schedule Name, and the extensible Thermal Comfort Control object-Type/Name pairs are relationship-like fields intentionally excluded from scalar accessors.
    // - Field Mapping: Numeric bounds return optional getters/reset helpers so IDD defaults (0/50 °C) are preserved implicitly while the Averaging Method mirrors the default PeopleAverage token for Ruby parity.
    std::string averagingMethod() const;
    bool setAveragingMethod(const std::string& averagingMethod);
    bool isAveragingMethodDefaulted() const;
    void resetAveragingMethod();

    boost::optional<double> minimumDryBulbTemperatureSetpoint() const;
    bool setMinimumDryBulbTemperatureSetpoint(double minimumDryBulbTemperatureSetpoint);
    bool isMinimumDryBulbTemperatureSetpointDefaulted() const;
    void resetMinimumDryBulbTemperatureSetpoint();

    boost::optional<double> maximumDryBulbTemperatureSetpoint() const;
    bool setMaximumDryBulbTemperatureSetpoint(double maximumDryBulbTemperatureSetpoint);
    bool isMaximumDryBulbTemperatureSetpointDefaulted() const;
    void resetMaximumDryBulbTemperatureSetpoint();

   protected:
    using ImplType = detail::ZoneControlThermostatThermalComfort_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlThermostatThermalComfort(std::shared_ptr<detail::ZoneControlThermostatThermalComfort_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
