/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLEROUTDOORAIR_HPP
#define EPMODEL_CONTROLLEROUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ParentObject.hpp"

#include <utilities/core/Deprecated.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;
  class ThermalZone;
  class ControllerMechanicalVentilation;
  class AirLoopHVACOutdoorAirSystem;

  namespace detail {
    class ControllerOutdoorAir_Impl;
  }

  class EPMODEL_API ControllerOutdoorAir : public ParentObject
  {
   public:
    explicit ControllerOutdoorAir(const Model& model);

    virtual ~ControllerOutdoorAir() override = default;
    ControllerOutdoorAir(const ControllerOutdoorAir& other) = default;
    ControllerOutdoorAir(ControllerOutdoorAir&& other) = default;
    ControllerOutdoorAir& operator=(const ControllerOutdoorAir&) = default;
    ControllerOutdoorAir& operator=(ControllerOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> economizerControlTypeValues();
    static std::vector<std::string> economizerControlActionTypeValues();
    static std::vector<std::string> lockoutTypeValues();
    static std::vector<std::string> minimumLimitTypeValues();
    static std::vector<std::string> heatRecoveryBypassControlTypeValues();
    static std::vector<std::string> economizerOperationStagingValues();

    // Schema Alignment Notes:
    // - API: Preserves the openstudio::model::ControllerOutdoorAir scalar, schedule, curve, humidistat-zone, mechanical-ventilation,
    //   and ordinary outdoor-air-system relationship signatures.
    // - Field Mapping: These APIs map directly to EnergyPlus Controller:OutdoorAir fields and configured object lists.
    // - Load Repair: Optional schedule, curve, and zone references are resolved observationally; invalid references are cleared, and
    //   High Humidity Control is normalized with the humidistat-zone relationship. Valid shared imported mechanical-ventilation controllers
    //   are cloned per outdoor-air-controller owner; malformed relationship evidence is cleared before any required replacement is created.
    // - Ownership: Mechanical-ventilation assignment enforces one exact raw-and-managed owner and preserves replaced CMVs. Direct deletion
    //   semantics for Controller:OutdoorAir and Controller:MechanicalVentilation remain deferred.
    // - Documented Delta: An active dedicated-outdoor-air-system projection keeps its Controller:OutdoorAir transient, so these
    //   relationship fields remain in memory only until the controller is returned to ordinary persisted ownership.

    boost::optional<Schedule> minimumOutdoorAirSchedule() const;
    bool setMinimumOutdoorAirSchedule(Schedule& schedule);
    void resetMinimumOutdoorAirSchedule();

    boost::optional<Schedule> minimumFractionofOutdoorAirSchedule() const;
    bool setMinimumFractionofOutdoorAirSchedule(Schedule& schedule);
    void resetMinimumFractionofOutdoorAirSchedule();

    boost::optional<Schedule> maximumFractionofOutdoorAirSchedule() const;
    bool setMaximumFractionofOutdoorAirSchedule(Schedule& schedule);
    void resetMaximumFractionofOutdoorAirSchedule();

    boost::optional<Schedule> timeofDayEconomizerControlSchedule() const;
    bool setTimeofDayEconomizerControlSchedule(Schedule& schedule);
    void resetTimeofDayEconomizerControlSchedule();

    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void autosizeMinimumOutdoorAirFlowRate();

    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();

    std::string getEconomizerControlType() const;
    bool setEconomizerControlType(const std::string& value);

    std::string getEconomizerControlActionType() const;
    bool setEconomizerControlActionType(const std::string& value);

    boost::optional<double> getEconomizerMaximumLimitDryBulbTemperature() const;
    bool setEconomizerMaximumLimitDryBulbTemperature(double value);
    void resetEconomizerMaximumLimitDryBulbTemperature();

    boost::optional<double> getEconomizerMaximumLimitEnthalpy() const;
    bool setEconomizerMaximumLimitEnthalpy(double value);
    void resetEconomizerMaximumLimitEnthalpy();

    boost::optional<double> getEconomizerMaximumLimitDewpointTemperature() const;
    bool setEconomizerMaximumLimitDewpointTemperature(double value);
    void resetEconomizerMaximumLimitDewpointTemperature();

    boost::optional<Curve> electronicEnthalpyLimitCurve() const;
    bool setElectronicEnthalpyLimitCurve(const Curve& curve);
    void resetElectronicEnthalpyLimitCurve();

    boost::optional<double> getEconomizerMinimumLimitDryBulbTemperature() const;
    bool setEconomizerMinimumLimitDryBulbTemperature(double value);
    void resetEconomizerMinimumLimitDryBulbTemperature();

    std::string getLockoutType() const;
    bool setLockoutType(const std::string& value);

    std::string getMinimumLimitType() const;
    bool setMinimumLimitType(const std::string& value);

    boost::optional<bool> getHighHumidityControl() const;
    OS_DEPRECATED(3, 8, 0) bool setHighHumidityControl(bool val);

    boost::optional<ThermalZone> humidistatControlZone() const;
    bool setHumidistatControlZone(const ThermalZone& thermalZone);
    void resetHumidistatControlZone();

    double getHighHumidityOutdoorAirFlowRatio() const;
    bool setHighHumidityOutdoorAirFlowRatio(double v);

    bool getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const;
    bool setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool v);

    boost::optional<std::string> getHeatRecoveryBypassControlType() const;
    bool setHeatRecoveryBypassControlType(const std::string& v);

    std::string economizerOperationStaging() const;
    bool setEconomizerOperationStaging(const std::string& v);

    ControllerMechanicalVentilation controllerMechanicalVentilation() const;
    bool setControllerMechanicalVentilation(const ControllerMechanicalVentilation& controllerMechanicalVentilation);

    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

   protected:
    using ImplType = detail::ControllerOutdoorAir_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ControllerOutdoorAir(std::shared_ptr<detail::ControllerOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
