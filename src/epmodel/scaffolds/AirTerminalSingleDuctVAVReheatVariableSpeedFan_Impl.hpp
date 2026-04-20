/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl() override = default;

      boost::optional<double> maximumCoolingAirFlowRate() const;
      bool setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate);
      bool isMaximumCoolingAirFlowRateAutosized() const;
      void autosizeMaximumCoolingAirFlowRate();

      boost::optional<double> maximumHeatingAirFlowRate() const;
      bool setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate);
      bool isMaximumHeatingAirFlowRateAutosized() const;
      void autosizeMaximumHeatingAirFlowRate();

      double zoneMinimumAirFlowFraction() const;
      bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

      boost::optional<double> maximumHotWaterorSteamFlowRate() const;
      bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
      bool isMaximumHotWaterorSteamFlowRateAutosized() const;
      void autosizeMaximumHotWaterorSteamFlowRate();

      double minimumHotWaterorSteamFlowRate() const;
      bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
      bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
      void resetMinimumHotWaterorSteamFlowRate();

      double heatingConvergenceTolerance() const;
      bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
      bool isHeatingConvergenceToleranceDefaulted() const;
      void resetHeatingConvergenceTolerance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
