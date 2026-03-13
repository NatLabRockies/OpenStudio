/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl() override = default;

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
