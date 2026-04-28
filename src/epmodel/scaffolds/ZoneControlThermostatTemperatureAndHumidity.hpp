/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLTHERMOSTATTEMPERATUREANDHUMIDITY_HPP
#define EPMODEL_ZONECONTROLTHERMOSTATTEMPERATUREANDHUMIDITY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneControlThermostatTemperatureAndHumidity_Impl;
  }

  class EPMODEL_API ZoneControlThermostatTemperatureAndHumidity : public ModelObject
  {
   public:
    explicit ZoneControlThermostatTemperatureAndHumidity(const Model& model);

    virtual ~ZoneControlThermostatTemperatureAndHumidity() override = default;
    ZoneControlThermostatTemperatureAndHumidity(const ZoneControlThermostatTemperatureAndHumidity& other) = default;
    ZoneControlThermostatTemperatureAndHumidity(ZoneControlThermostatTemperatureAndHumidity&& other) = default;
    ZoneControlThermostatTemperatureAndHumidity& operator=(const ZoneControlThermostatTemperatureAndHumidity&) = default;
    ZoneControlThermostatTemperatureAndHumidity& operator=(ZoneControlThermostatTemperatureAndHumidity&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> overcoolRangeInputMethodValues();

    // Schema Alignment Notes:
    // - API: Scalar accessors map directly to ZoneControl:Thermostat:TemperatureAndHumidity fields (Dehumidification Control Type, Overcool Range Input Method, Overcool Constant Range, Overcool Control Ratio).
    // - Field Mapping: Thermostat Name, Dehumidifying Relative Humidity Setpoint Schedule Name, and Overcool Range Schedule Name remain relationship-style object-list fields and are intentionally excluded.
    // - Field Mapping: Optional numeric fields expose presence/reset helpers consistent with the Ruby generator metadata and default to the IDD-defined constants when blank.
    // - TODO(parity): Add humidity schedule relationship helpers once scalar saturation completes.
    std::string dehumidificationControlType() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    bool isDehumidificationControlTypeDefaulted() const;
    void resetDehumidificationControlType();

    std::string overcoolRangeInputMethod() const;
    bool setOvercoolRangeInputMethod(const std::string& overcoolRangeInputMethod);
    bool isOvercoolRangeInputMethodDefaulted() const;
    void resetOvercoolRangeInputMethod();

    boost::optional<double> overcoolConstantRange() const;
    bool setOvercoolConstantRange(double overcoolConstantRange);
    bool isOvercoolConstantRangeDefaulted() const;
    void resetOvercoolConstantRange();

    boost::optional<double> overcoolControlRatio() const;
    bool setOvercoolControlRatio(double overcoolControlRatio);
    bool isOvercoolControlRatioDefaulted() const;
    void resetOvercoolControlRatio();

   protected:
    using ImplType = detail::ZoneControlThermostatTemperatureAndHumidity_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlThermostatTemperatureAndHumidity(std::shared_ptr<detail::ZoneControlThermostatTemperatureAndHumidity_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
