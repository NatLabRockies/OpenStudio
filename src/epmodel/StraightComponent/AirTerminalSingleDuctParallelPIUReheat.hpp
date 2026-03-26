/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTPARALLELPIUREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTPARALLELPIUREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctParallelPIUReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctParallelPIUReheat : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctParallelPIUReheat(const Model& model);

  virtual ~AirTerminalSingleDuctParallelPIUReheat() override = default;
  AirTerminalSingleDuctParallelPIUReheat(const AirTerminalSingleDuctParallelPIUReheat& other) = default;
  AirTerminalSingleDuctParallelPIUReheat(AirTerminalSingleDuctParallelPIUReheat&& other) = default;
  AirTerminalSingleDuctParallelPIUReheat& operator=(const AirTerminalSingleDuctParallelPIUReheat&) = default;
  AirTerminalSingleDuctParallelPIUReheat& operator=(AirTerminalSingleDuctParallelPIUReheat&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fanControlTypeValues();
  static std::vector<std::string> heatingControlTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: maximumPrimaryAirFlowRate, maximumSecondaryAirFlowRate, minimumPrimaryAirFlowFraction, fanOnFlowFraction,
  //   maximumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate, convergenceTolerance, fanControlType, minimumFanTurnDownRatio,
  //   heatingControlType, designHeatingDischargeAirTemperature, and highLimitHeatingDischargeAirTemperature map directly to
  //   EnergyPlus AirTerminal:SingleDuct:ParallelPIU:Reheat scalar fields.
  // - Field Mapping: Availability Schedule Name, node names, Zone Mixer/Fan/Reheat Coil references, and related object-type/link fields are
  //   relationship fields and intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctParallelPIUReheat writes these scalar fields directly and handles
  //   relationship fields separately.
  // - TODO(parity): Add relationship/non-scalar behavior incrementally after scalar scaffold saturation.
  boost::optional<double> maximumPrimaryAirFlowRate() const;
  bool isMaximumPrimaryAirFlowRateAutosized() const;
  bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
  void autosizeMaximumPrimaryAirFlowRate();

  boost::optional<double> maximumSecondaryAirFlowRate() const;
  bool isMaximumSecondaryAirFlowRateAutosized() const;
  bool setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate);
  void autosizeMaximumSecondaryAirFlowRate();

  boost::optional<double> minimumPrimaryAirFlowFraction() const;
  bool isMinimumPrimaryAirFlowFractionAutosized() const;
  bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
  void autosizeMinimumPrimaryAirFlowFraction();

  boost::optional<double> fanOnFlowFraction() const;
  bool isFanOnFlowFractionAutosized() const;
  bool setFanOnFlowFraction(double fanOnFlowFraction);
  void autosizeFanOnFlowFraction();

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void resetMaximumHotWaterorSteamFlowRate();
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
  void resetMinimumHotWaterorSteamFlowRate();

  double convergenceTolerance() const;
  bool isConvergenceToleranceDefaulted() const;
  bool setConvergenceTolerance(double convergenceTolerance);
  void resetConvergenceTolerance();

  std::string fanControlType() const;
  bool setFanControlType(const std::string& fanControlType);

  double minimumFanTurnDownRatio() const;
  bool setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio);

  std::string heatingControlType() const;
  bool setHeatingControlType(const std::string& heatingControlType);

  double designHeatingDischargeAirTemperature() const;
  bool setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature);

  double highLimitHeatingDischargeAirTemperature() const;
  bool setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature);

  protected:
  using ImplType = detail::AirTerminalSingleDuctParallelPIUReheat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctParallelPIUReheat(std::shared_ptr<detail::AirTerminalSingleDuctParallelPIUReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
