/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeInduction : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model);

    virtual ~AirTerminalSingleDuctConstantVolumeFourPipeInduction() override = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction(const AirTerminalSingleDuctConstantVolumeFourPipeInduction& other) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction(AirTerminalSingleDuctConstantVolumeFourPipeInduction&& other) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction& operator=(const AirTerminalSingleDuctConstantVolumeFourPipeInduction&) = default;
    AirTerminalSingleDuctConstantVolumeFourPipeInduction& operator=(AirTerminalSingleDuctConstantVolumeFourPipeInduction&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: maximumTotalAirFlowRate, inductionRatio, maximumHotWaterFlowRate, minimumHotWaterFlowRate,
    //   heatingConvergenceTolerance, maximumColdWaterFlowRate, minimumColdWaterFlowRate, and coolingConvergenceTolerance
    //   map directly to E+ AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction scalar fields.
    // - Field Mapping: schedule, coil, node, and zone mixer fields are relationship fields and are intentionally excluded.
    // - ForwardTranslator evidence: translateAirTerminalSingleDuctConstantVolumeFourPipeInduction writes these scalar fields directly.
    // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.

    boost::optional<double> maximumTotalAirFlowRate() const;
    bool setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate);
    bool isMaximumTotalAirFlowRateAutosized() const;
    void autosizeMaximumTotalAirFlowRate();

    double inductionRatio() const;
    bool setInductionRatio(double inductionRatio);
    bool isInductionRatioDefaulted() const;
    void resetInductionRatio();

    boost::optional<double> maximumHotWaterFlowRate() const;
    bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
    bool isMaximumHotWaterFlowRateAutosized() const;
    void resetMaximumHotWaterFlowRate();
    void autosizeMaximumHotWaterFlowRate();

    double minimumHotWaterFlowRate() const;
    bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
    bool isMinimumHotWaterFlowRateDefaulted() const;
    void resetMinimumHotWaterFlowRate();

    double heatingConvergenceTolerance() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
    bool isHeatingConvergenceToleranceDefaulted() const;
    void resetHeatingConvergenceTolerance();

    boost::optional<double> maximumColdWaterFlowRate() const;
    bool setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate);
    bool isMaximumColdWaterFlowRateAutosized() const;
    void resetMaximumColdWaterFlowRate();
    void autosizeMaximumColdWaterFlowRate();

    double minimumColdWaterFlowRate() const;
    bool setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate);
    bool isMinimumColdWaterFlowRateDefaulted() const;
    void resetMinimumColdWaterFlowRate();

    double coolingConvergenceTolerance() const;
    bool setCoolingConvergenceTolerance(double coolingConvergenceTolerance);
    bool isCoolingConvergenceToleranceDefaulted() const;
    void resetCoolingConvergenceTolerance();

  protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeFourPipeInduction(
      std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
