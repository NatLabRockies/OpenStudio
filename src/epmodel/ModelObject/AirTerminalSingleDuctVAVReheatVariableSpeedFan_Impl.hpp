/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl() override = default;

  boost::optional<double> maximumCoolingAirFlowRate() const;
  bool isMaximumCoolingAirFlowRateAutosized() const;
  bool setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate);
  void autosizeMaximumCoolingAirFlowRate();

  boost::optional<double> maximumHeatingAirFlowRate() const;
  bool isMaximumHeatingAirFlowRateAutosized() const;
  bool setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate);
  void autosizeMaximumHeatingAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
  void resetMinimumHotWaterorSteamFlowRate();

  double heatingConvergenceTolerance() const;
  bool isHeatingConvergenceToleranceDefaulted() const;
  bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
  void resetHeatingConvergenceTolerance();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
