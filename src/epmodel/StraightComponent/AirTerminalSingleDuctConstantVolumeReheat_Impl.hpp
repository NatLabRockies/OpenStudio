/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirTerminalSingleDuctConstantVolumeReheat_Impl() override = default;

  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void resetMaximumAirFlowRate();
  void autosizeMaximumAirFlowRate();

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

  double maximumReheatAirTemperature() const;
  bool isMaximumReheatAirTemperatureDefaulted() const;
  bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
  void resetMaximumReheatAirTemperature();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
