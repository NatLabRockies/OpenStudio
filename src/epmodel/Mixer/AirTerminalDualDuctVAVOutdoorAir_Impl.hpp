/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_IMPL_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalDualDuctVAVOutdoorAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirTerminalDualDuctVAVOutdoorAir_Impl() override = default;

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
