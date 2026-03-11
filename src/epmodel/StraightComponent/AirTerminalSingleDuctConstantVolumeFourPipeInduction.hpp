/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEINDUCTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeInduction : public ModelObject
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
