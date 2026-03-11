/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAV_IMPL_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAV_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalDualDuctVAV_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirTerminalDualDuctVAV_Impl() override = default;

  boost::optional<double> maximumDamperAirFlowRate() const;
  bool isMaximumDamperAirFlowRateAutosized() const;
  bool setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate);
  void autosizeMaximumDamperAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
