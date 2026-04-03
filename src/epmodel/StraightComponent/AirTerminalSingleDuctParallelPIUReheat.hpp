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
class Schedule;
class HVACComponent;
class Node;

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
  // - Status: Partial Parity. The scalar parallel-PIU controls are aligned, but the schedule and coupled-component surface remains intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctParallelPIUReheat.
  // - Implemented Parity: `maximumPrimaryAirFlowRate`, `maximumSecondaryAirFlowRate`, `minimumPrimaryAirFlowFraction`, `fanOnFlowFraction`, `maximumHotWaterorSteamFlowRate`, `minimumHotWaterorSteamFlowRate`, `convergenceTolerance`, `fanControlType`, `minimumFanTurnDownRatio`, `heatingControlType`, `designHeatingDischargeAirTemperature`, and `highLimitHeatingDischargeAirTemperature` preserve the canonical contract.
  // - Documented Delta: Node names and the zone-mixer object-link surface remain outside this pass.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:ParallelPIU:Reheat` fields; the translator wires the coupled components separately.
  // - Evidence: `src/model/AirTerminalSingleDuctParallelPIUReheat.hpp`, `src/model/AirTerminalSingleDuctParallelPIUReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctParallelPIUReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctParallelPIUReheat_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, node, and coupled-component helpers when relationship parity expands.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  HVACComponent fan() const;
  bool setFan(HVACComponent& hvacComponent);

  HVACComponent reheatCoil() const;
  bool setReheatCoil(HVACComponent& hvacComponent);

  boost::optional<Node> secondaryAirInletNode() const;

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
