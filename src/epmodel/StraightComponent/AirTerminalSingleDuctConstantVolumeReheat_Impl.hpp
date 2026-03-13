/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeReheat_Impl() override = default;

      boost::optional<double> maximumAirFlowRate() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void resetMaximumAirFlowRate();
      bool isMaximumAirFlowRateAutosized() const;
      void autosizeMaximumAirFlowRate();

      boost::optional<double> maximumHotWaterorSteamFlowRate() const;
      bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
      void resetMaximumHotWaterorSteamFlowRate();
      bool isMaximumHotWaterorSteamFlowRateAutosized() const;
      void autosizeMaximumHotWaterorSteamFlowRate();

      double minimumHotWaterorSteamFlowRate() const;
      bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
      void resetMinimumHotWaterorSteamFlowRate();
      bool isMinimumHotWaterorSteamFlowRateDefaulted() const;

      double convergenceTolerance() const;
      bool setConvergenceTolerance(double convergenceTolerance);
      void resetConvergenceTolerance();
      bool isConvergenceToleranceDefaulted() const;

      double maximumReheatAirTemperature() const;
      bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
      void resetMaximumReheatAirTemperature();
      bool isMaximumReheatAirTemperatureDefaulted() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
