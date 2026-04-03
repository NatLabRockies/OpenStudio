/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;
class HVACComponent;

namespace detail {
class AirTerminalSingleDuctConstantVolumeReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctConstantVolumeReheat(const Model& model);

  virtual ~AirTerminalSingleDuctConstantVolumeReheat() override = default;
  AirTerminalSingleDuctConstantVolumeReheat(const AirTerminalSingleDuctConstantVolumeReheat& other) = default;
  AirTerminalSingleDuctConstantVolumeReheat(AirTerminalSingleDuctConstantVolumeReheat&& other) = default;
  AirTerminalSingleDuctConstantVolumeReheat& operator=(const AirTerminalSingleDuctConstantVolumeReheat&) = default;
  AirTerminalSingleDuctConstantVolumeReheat& operator=(AirTerminalSingleDuctConstantVolumeReheat&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The constant-volume reheat scalar surface is aligned, while schedule, node-link, and coil helpers remain intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeReheat.
  // - Implemented Parity: `maximumAirFlowRate`, `maximumHotWaterorSteamFlowRate`, `minimumHotWaterorSteamFlowRate`, `convergenceTolerance`, and `maximumReheatAirTemperature` preserve the canonical scalar contract.
  // - Documented Delta: Inlet and outlet node conveniences continue to come from the shared straight-component topology.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:Reheat` fields, while the translator wires the topology links separately.
  // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeReheat.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctConstantVolumeReheat_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, node-link, and coil helpers when relationship parity expands.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  HVACComponent reheatCoil() const;
  bool setReheatCoil(const HVACComponent& coil);
  void resetReheatCoil();

  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void resetMaximumAirFlowRate();
  void autosizeMaximumAirFlowRate();

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

  double maximumReheatAirTemperature() const;
  bool isMaximumReheatAirTemperatureDefaulted() const;
  bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);
  void resetMaximumReheatAirTemperature();

 protected:
  using ImplType = detail::AirTerminalSingleDuctConstantVolumeReheat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctConstantVolumeReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
