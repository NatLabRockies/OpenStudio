/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_IMPL_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_IMPL_HPP

#include "Mixer/Mixer_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalDualDuctVAVOutdoorAir_Impl : public Mixer_Impl
    {
     public:
      using Mixer_Impl::Mixer_Impl;
      virtual ~AirTerminalDualDuctVAVOutdoorAir_Impl() override = default;

      unsigned outletPort() const override;
      unsigned inletPort(unsigned branchIndex) const override;
      bool addToNode(openstudio::epmodel::Node& node) override;
      std::vector<openstudio::IdfObject> remove() override;
      boost::optional<openstudio::epmodel::Node> outdoorAirInletNode() const;
      boost::optional<openstudio::epmodel::Node> recirculatedAirInletNode() const;
      boost::optional<double> maximumTerminalAirFlowRate() const;
      bool setMaximumTerminalAirFlowRate(double maximumTerminalAirFlowRate);
      void autosizeMaximumTerminalAirFlowRate();
      bool isMaximumTerminalAirFlowRateAutosized() const;

      std::string perPersonVentilationRateMode() const;
      bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
