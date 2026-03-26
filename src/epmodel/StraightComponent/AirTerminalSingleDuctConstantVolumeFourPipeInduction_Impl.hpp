/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

  boost::optional<double> maximumTotalAirFlowRate() const;
  bool isMaximumTotalAirFlowRateAutosized() const;
  bool setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate);
  void autosizeMaximumTotalAirFlowRate();

  double inductionRatio() const;
  bool isInductionRatioDefaulted() const;
  bool setInductionRatio(double inductionRatio);
  void resetInductionRatio();

  boost::optional<double> maximumHotWaterFlowRate() const;
  bool isMaximumHotWaterFlowRateAutosized() const;
  bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
  void resetMaximumHotWaterFlowRate();
  void autosizeMaximumHotWaterFlowRate();

  double minimumHotWaterFlowRate() const;
  bool isMinimumHotWaterFlowRateDefaulted() const;
  bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
  void resetMinimumHotWaterFlowRate();

  double heatingConvergenceTolerance() const;
  bool isHeatingConvergenceToleranceDefaulted() const;
  bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
  void resetHeatingConvergenceTolerance();

  boost::optional<double> maximumColdWaterFlowRate() const;
  bool isMaximumColdWaterFlowRateAutosized() const;
  bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
  void resetMaximumColdWaterFlowRate();
  void autosizeMaximumColdWaterFlowRate();

  double minimumColdWaterFlowRate() const;
  bool isMinimumColdWaterFlowRateDefaulted() const;
  bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
  void resetMinimumColdWaterFlowRate();

  double coolingConvergenceTolerance() const;
  bool isCoolingConvergenceToleranceDefaulted() const;
  bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
  void resetCoolingConvergenceTolerance();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
