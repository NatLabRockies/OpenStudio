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
  class Curve;
  class Schedule;

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
    // - Status: Partial Parity. The scalar controls plus the optional electronic-enthalpy curve and time-of-day economizer schedule are aligned.
    // - Canonical Counterpart: openstudio::model::ZoneHVACEnergyRecoveryVentilatorController.
    // - Implemented Parity: The direct scalar fields and the two exposed optional relationships preserve canonical assignment, validation,
    //   reset, and reload behavior.
    // - Lifecycle Boundary: Current EPModel removal preserves the referenced curve and schedule resources; canonical recursive child deletion is
    //   deferred with the broader ERV ownership lifecycle.
    // - Documented Delta: The EnergyPlus-only Humidistat Control Zone Name field remains outside the canonical public API and is not exposed.
    // - Field/Storage Mapping: Scalars, the UnivariateFunctions curve reference, and the bounded continuous schedule reference map directly to
    //   EnergyPlus ZoneHVAC:EnergyRecoveryVentilator:Controller fields.
    // - Evidence: `src/model/ZoneHVACEnergyRecoveryVentilatorController.hpp`, `src/model/ZoneHVACEnergyRecoveryVentilatorController.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACEnergyRecoveryVentilatorController.cpp`, and the epmodel controller tests.
    // - Remaining Parity Work: Keep broader ERV ownership, child deletion, and topology behavior with the owning ZoneHVACEnergyRecoveryVentilator.

    boost::optional<Curve> electronicEnthalpyLimitCurve() const;
    bool setElectronicEnthalpyLimitCurve(const Curve& curve);
    void resetElectronicEnthalpyLimitCurve();

    boost::optional<Schedule> timeofDayEconomizerFlowControlSchedule() const;
    bool setTimeofDayEconomizerFlowControlSchedule(Schedule& schedule);
    void resetTimeofDayEconomizerFlowControlSchedule();

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
