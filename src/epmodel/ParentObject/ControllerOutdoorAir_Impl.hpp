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

namespace detail {

class EPMODEL_API ControllerOutdoorAir_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~ControllerOutdoorAir_Impl() override = default;

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

  boost::optional<double> getEconomizerMinimumLimitDryBulbTemperature() const;
  bool setEconomizerMinimumLimitDryBulbTemperature(boost::optional<double> value);

  std::string getLockoutType() const;
  bool setLockoutType(const std::string& value);

  std::string getMinimumLimitType() const;
  bool setMinimumLimitType(const std::string& value);

  boost::optional<bool> getHighHumidityControl() const;

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
  boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
