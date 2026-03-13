/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVNoReheat_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirTerminalSingleDuctVAVNoReheat_Impl() override = default;

      std::vector<std::string> zoneMinimumAirFlowInputMethodValues() const;

      boost::optional<double> maximumAirFlowRate() const;
      bool isMaximumAirFlowRateAutosized() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void resetMaximumAirFlowRate();
      void autosizeMaximumAirFlowRate();

      boost::optional<std::string> zoneMinimumAirFlowInputMethod() const;
      bool setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod);
      void resetZoneMinimumAirFlowInputMethod();

      boost::optional<double> constantMinimumAirFlowFraction() const;
      bool isConstantMinimumAirFlowFractionAutosized() const;
      bool isConstantMinimumAirFlowFractionDefaulted() const;
      bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
      void autosizeConstantMinimumAirFlowFraction();
      void resetConstantMinimumAirFlowFraction();

      boost::optional<double> fixedMinimumAirFlowRate() const;
      bool isFixedMinimumAirFlowRateAutosized() const;
      bool isFixedMinimumAirFlowRateDefaulted() const;
      bool setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate);
      void autosizeFixedMinimumAirFlowRate();
      void resetFixedMinimumAirFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
