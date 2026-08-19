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

/** \brief Controls economizer and humidity limits for a zone energy-recovery ventilator.
 *
 * \par EnergyPlus object
 * \epobject{group-controllers.html#zonehvacenergyrecoveryventilatorcontroller,ZoneHVAC:EnergyRecoveryVentilator:Controller}
 *
 * \par Important behavior
 * Enthalpy-curve, time-of-day schedule, temperature/enthalpy/dewpoint limits, exhaust-air limits, and humidity-control fields map directly to the controller object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACEnergyRecoveryVentilatorController</code>.
 * <b>Renamed:</b> EPModel uses <code>controlHighIndoorHumidityBasedOnOutdoorHumidityRatio()</code> and its setter; Model spells <code>On</code> as <code>controlHighIndoorHumidityBasedonOutdoorHumidityRatio()</code>.
 *
 * \par Known limitations
 * The controller does not own the parent energy-recovery ventilator; parent equipment relationships are managed by the ventilator object.
 */
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
