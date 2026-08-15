/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLEROUTDOORAIR_IMPL_HPP
#define EPMODEL_CONTROLLEROUTDOORAIR_IMPL_HPP

#include "ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class ControllerMechanicalVentilation;
  class AirLoopHVACOutdoorAirSystem;
  class Schedule;
  class Curve;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API ControllerOutdoorAir_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~ControllerOutdoorAir_Impl() override = default;

      boost::optional<openstudio::epmodel::Schedule> minimumOutdoorAirSchedule() const;
      bool setMinimumOutdoorAirSchedule(openstudio::epmodel::Schedule& schedule);
      void resetMinimumOutdoorAirSchedule();

      boost::optional<openstudio::epmodel::Schedule> minimumFractionofOutdoorAirSchedule() const;
      bool setMinimumFractionofOutdoorAirSchedule(openstudio::epmodel::Schedule& schedule);
      void resetMinimumFractionofOutdoorAirSchedule();

      boost::optional<openstudio::epmodel::Schedule> maximumFractionofOutdoorAirSchedule() const;
      bool setMaximumFractionofOutdoorAirSchedule(openstudio::epmodel::Schedule& schedule);
      void resetMaximumFractionofOutdoorAirSchedule();

      boost::optional<openstudio::epmodel::Schedule> timeofDayEconomizerControlSchedule() const;
      bool setTimeofDayEconomizerControlSchedule(openstudio::epmodel::Schedule& schedule);
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
      bool setEconomizerMaximumLimitDryBulbTemperature(boost::optional<double> value);

      boost::optional<double> getEconomizerMaximumLimitEnthalpy() const;
      bool setEconomizerMaximumLimitEnthalpy(boost::optional<double> value);

      boost::optional<double> getEconomizerMaximumLimitDewpointTemperature() const;
      bool setEconomizerMaximumLimitDewpointTemperature(boost::optional<double> value);

      boost::optional<openstudio::epmodel::Curve> electronicEnthalpyLimitCurve() const;
      bool setElectronicEnthalpyLimitCurve(const openstudio::epmodel::Curve& curve);
      void resetElectronicEnthalpyLimitCurve();

      boost::optional<double> getEconomizerMinimumLimitDryBulbTemperature() const;
      bool setEconomizerMinimumLimitDryBulbTemperature(boost::optional<double> value);

      std::string getLockoutType() const;
      bool setLockoutType(const std::string& value);

      std::string getMinimumLimitType() const;
      bool setMinimumLimitType(const std::string& value);

      boost::optional<bool> getHighHumidityControl() const;

      boost::optional<openstudio::epmodel::ThermalZone> humidistatControlZone() const;
      bool setHumidistatControlZone(const openstudio::epmodel::ThermalZone& thermalZone);
      void resetHumidistatControlZone();

      double getHighHumidityOutdoorAirFlowRatio() const;
      bool setHighHumidityOutdoorAirFlowRatio(double v);

      bool getControlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const;
      bool setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool v);

      boost::optional<std::string> getHeatRecoveryBypassControlType() const;
      bool setHeatRecoveryBypassControlType(const std::string& v);

      std::string economizerOperationStaging() const;
      bool setEconomizerOperationStaging(const std::string& v);

      std::vector<std::string> economizerControlTypeValues() const;
      std::vector<std::string> economizerControlActionTypeValues() const;
      std::vector<std::string> lockoutTypeValues() const;
      std::vector<std::string> minimumLimitTypeValues() const;
      std::vector<std::string> heatRecoveryBypassControlTypeValues() const;
      std::vector<std::string> economizerOperationStagingValues() const;

      boost::optional<openstudio::epmodel::ControllerMechanicalVentilation> optionalControllerMechanicalVentilation() const;
      openstudio::epmodel::ControllerMechanicalVentilation controllerMechanicalVentilation() const;
      bool setControllerMechanicalVentilation(const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation);
      bool setControllerMechanicalVentilation(const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation,
                                              bool syncRows);
      boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
