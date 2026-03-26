/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> maximumAirFlowRate() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      bool isMaximumAirFlowRateAutosized() const;
      void autosizeMaximumAirFlowRate();

      double zoneMinimumAirFlowFraction() const;
      bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
