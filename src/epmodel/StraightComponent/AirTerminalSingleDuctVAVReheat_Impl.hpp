/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEAT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVReheat_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctVAVReheat_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::vector<std::string> zoneMinimumAirFlowInputMethodValues() const;

      boost::optional<double> maximumAirFlowRate() const;
      bool isMaximumAirFlowRateAutosized() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void autosizeMaximumAirFlowRate();

      std::string zoneMinimumAirFlowInputMethod();
      bool setZoneMinimumAirFlowInputMethod(const std::string& value);

      boost::optional<double> constantMinimumAirFlowFraction() const;
      bool isConstantMinimumAirFlowFractionAutosized() const;
      bool setConstantMinimumAirFlowFraction(double value);
      void autosizeConstantMinimumAirFlowFraction();

      boost::optional<double> fixedMinimumAirFlowRate() const;
      bool isFixedMinimumAirFlowRateAutosized() const;
      bool setFixedMinimumAirFlowRate(double value);
      void autosizeFixedMinimumAirFlowRate();

      boost::optional<double> maximumHotWaterOrSteamFlowRate();
      bool isMaximumHotWaterOrSteamFlowRateAutosized() const;
      bool setMaximumHotWaterOrSteamFlowRate(double value);
      void autosizeMaximumHotWaterOrSteamFlowRate();

      double minimumHotWaterOrSteamFlowRate();
      bool setMinimumHotWaterOrStreamFlowRate(double value);

      double convergenceTolerance();
      bool setConvergenceTolerance(double value);

      std::string damperHeatingAction();
      bool setDamperHeatingAction(const std::string& value);
      std::vector<std::string> damperHeatingActionValues() const;

      boost::optional<double> maximumFlowPerZoneFloorAreaDuringReheat();
      bool isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const;
      bool setMaximumFlowPerZoneFloorAreaDuringReheat(double value);
      void autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
      void resetMaximumFlowPerZoneFloorAreaDuringReheat();

      boost::optional<double> maximumFlowFractionDuringReheat();
      bool isMaximumFlowFractionDuringReheatAutosized() const;
      bool setMaximumFlowFractionDuringReheat(double value);
      void autosizeMaximumFlowFractionDuringReheat();
      void resetMaximumFlowFractionDuringReheat();

      double maximumReheatAirTemperature();
      bool setMaximumReheatAirTemperature(double value);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
