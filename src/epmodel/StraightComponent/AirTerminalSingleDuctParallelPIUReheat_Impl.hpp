/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTPARALLELPIUREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTPARALLELPIUREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Schedule;
class HVACComponent;
class Node;

namespace detail {

class EPMODEL_API AirTerminalSingleDuctParallelPIUReheat_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~AirTerminalSingleDuctParallelPIUReheat_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  HVACComponent fan() const;
  bool setFan(HVACComponent& hvacComponent);

  HVACComponent reheatCoil() const;
  bool setReheatCoil(HVACComponent& hvacComponent);

  boost::optional<Node> secondaryAirInletNode() const;

  boost::optional<double> maximumPrimaryAirFlowRate() const;
  bool isMaximumPrimaryAirFlowRateAutosized() const;
  bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
  void autosizeMaximumPrimaryAirFlowRate();

  boost::optional<double> maximumSecondaryAirFlowRate() const;
  bool isMaximumSecondaryAirFlowRateAutosized() const;
  bool setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate);
  void autosizeMaximumSecondaryAirFlowRate();

  boost::optional<double> minimumPrimaryAirFlowFraction() const;
  bool isMinimumPrimaryAirFlowFractionAutosized() const;
  bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
  void autosizeMinimumPrimaryAirFlowFraction();

  boost::optional<double> fanOnFlowFraction() const;
  bool isFanOnFlowFractionAutosized() const;
  bool setFanOnFlowFraction(double fanOnFlowFraction);
  void autosizeFanOnFlowFraction();

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void resetMaximumHotWaterorSteamFlowRate();
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
  void resetMinimumHotWaterorSteamFlowRate();

  double convergenceTolerance() const;
  bool isConvergenceToleranceDefaulted() const;
  bool setConvergenceTolerance(double convergenceTolerance);
  void resetConvergenceTolerance();

  std::string fanControlType() const;
  bool setFanControlType(const std::string& fanControlType);

  double minimumFanTurnDownRatio() const;
  bool setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio);

  std::string heatingControlType() const;
  bool setHeatingControlType(const std::string& heatingControlType);

  double designHeatingDischargeAirTemperature() const;
  bool setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature);

  double highLimitHeatingDischargeAirTemperature() const;
  bool setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature);

  std::vector<std::string> fanControlTypeValues() const;
  std::vector<std::string> heatingControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
