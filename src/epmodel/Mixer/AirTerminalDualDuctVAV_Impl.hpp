/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAV_IMPL_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAV_IMPL_HPP

#include "Mixer/Mixer_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirTerminalDualDuctVAV_Impl : public Mixer_Impl
{
 public:
  using Mixer_Impl::Mixer_Impl;
  virtual ~AirTerminalDualDuctVAV_Impl() override = default;

  unsigned outletPort() const override;
  unsigned inletPort(unsigned branchIndex) const override;
  bool addToNode(openstudio::epmodel::Node& node) override;
  boost::optional<openstudio::epmodel::Node> hotAirInletNode() const;
  boost::optional<openstudio::epmodel::Node> coldAirInletNode() const;
  boost::optional<double> maximumDamperAirFlowRate() const;
  bool setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate);
  bool isMaximumDamperAirFlowRateAutosized() const;
  void autosizeMaximumDamperAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
