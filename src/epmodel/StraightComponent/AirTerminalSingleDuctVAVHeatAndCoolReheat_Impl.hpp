/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl() override = default;

  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void autosizeMaximumAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

  double convergenceTolerance() const;
  bool setConvergenceTolerance(double convergenceTolerance);

  double maximumReheatAirTemperature() const;
  bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
