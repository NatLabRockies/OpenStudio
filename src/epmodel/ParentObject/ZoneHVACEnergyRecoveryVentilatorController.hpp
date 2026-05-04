/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATORCONTROLLER_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATORCONTROLLER_HPP

#include "EPModelAPI.hpp"
#include "ParentObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACEnergyRecoveryVentilatorController_Impl;
  }

  class EPMODEL_API ZoneHVACEnergyRecoveryVentilatorController : public ParentObject
  {
   public:
    explicit ZoneHVACEnergyRecoveryVentilatorController(const Model& model);

    virtual ~ZoneHVACEnergyRecoveryVentilatorController() override = default;
    ZoneHVACEnergyRecoveryVentilatorController(const ZoneHVACEnergyRecoveryVentilatorController& other) = default;
    ZoneHVACEnergyRecoveryVentilatorController(ZoneHVACEnergyRecoveryVentilatorController&& other) = default;
    ZoneHVACEnergyRecoveryVentilatorController& operator=(const ZoneHVACEnergyRecoveryVentilatorController&) = default;
    ZoneHVACEnergyRecoveryVentilatorController& operator=(ZoneHVACEnergyRecoveryVentilatorController&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> exhaustAirTemperatureLimitValues();
    static std::vector<std::string> exhaustAirEnthalpyLimitValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ZoneHVACEnergyRecoveryVentilatorController scalar accessor names/signatures.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus ZoneHVAC:EnergyRecoveryVentilator:Controller fields (temperature limits, exhaust limit choices, and humidity control flags).
    // - Field Mapping: Relationship-like fields (Electronic Enthalpy Limit Curve Name, Time of Day Economizer Flow Control Schedule Name, Humidistat Control Zone Name) remain excluded from this scalar API surface.
    // - ForwardTranslator evidence: ForwardTranslateZoneHVACEnergyRecoveryVentilatorController.cpp writes these scalar fields for the model counterpart.
    boost::optional<double> temperatureHighLimit() const;
    bool setTemperatureHighLimit(double temperatureHighLimit);
    void resetTemperatureHighLimit();

    boost::optional<double> temperatureLowLimit() const;
    bool setTemperatureLowLimit(double temperatureLowLimit);
    void resetTemperatureLowLimit();

    boost::optional<double> enthalpyHighLimit() const;
    bool setEnthalpyHighLimit(double enthalpyHighLimit);
    void resetEnthalpyHighLimit();

    boost::optional<double> dewpointTemperatureLimit() const;
    bool setDewpointTemperatureLimit(double dewpointTemperatureLimit);
    void resetDewpointTemperatureLimit();

    std::string exhaustAirTemperatureLimit() const;
    bool setExhaustAirTemperatureLimit(const std::string& value);

    std::string exhaustAirEnthalpyLimit() const;
    bool setExhaustAirEnthalpyLimit(const std::string& value);

    bool highHumidityControlFlag() const;
    bool setHighHumidityControlFlag(bool highHumidityControlFlag);

    double highHumidityOutdoorAirFlowRatio() const;
    bool setHighHumidityOutdoorAirFlowRatio(double highHumidityOutdoorAirFlowRatio);

    bool controlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const;
    bool setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool value);

   protected:
    using ImplType = detail::ZoneHVACEnergyRecoveryVentilatorController_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ZoneHVACEnergyRecoveryVentilatorController(std::shared_ptr<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
