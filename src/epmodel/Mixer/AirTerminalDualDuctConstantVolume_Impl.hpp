/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTCONSTANTVOLUME_IMPL_HPP
#define EPMODEL_AIRTERMINALDUALDUCTCONSTANTVOLUME_IMPL_HPP

#include "Mixer/Mixer_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalDualDuctConstantVolume_Impl : public Mixer_Impl
    {
     public:
      using Mixer_Impl::Mixer_Impl;
      virtual ~AirTerminalDualDuctConstantVolume_Impl() override = default;

  unsigned outletPort() const override;
  unsigned inletPort(unsigned branchIndex) const override;
  bool addToNode(openstudio::epmodel::Node& node) override;
  std::vector<openstudio::IdfObject> remove() override;
  boost::optional<openstudio::epmodel::Node> hotAirInletNode() const;
  boost::optional<openstudio::epmodel::Node> coldAirInletNode() const;
      boost::optional<double> maximumAirFlowRate() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      bool isMaximumAirFlowRateAutosized() const;
      void autosizeMaximumAirFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
