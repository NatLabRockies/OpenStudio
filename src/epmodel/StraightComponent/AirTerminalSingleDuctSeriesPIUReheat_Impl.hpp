/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalSingleDuctSeriesPIUReheat_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirTerminalSingleDuctSeriesPIUReheat_Impl() override = default;

  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void autosizeMaximumAirFlowRate();

  boost::optional<double> maximumPrimaryAirFlowRate() const;
  bool isMaximumPrimaryAirFlowRateAutosized() const;
  bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
  void autosizeMaximumPrimaryAirFlowRate();

  boost::optional<double> minimumPrimaryAirFlowFraction() const;
  bool isMinimumPrimaryAirFlowFractionAutosized() const;
  bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
  void autosizeMinimumPrimaryAirFlowFraction();

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void resetMaximumHotWaterorSteamFlowRate();
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

  double convergenceTolerance() const;
  bool setConvergenceTolerance(double convergenceTolerance);

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
