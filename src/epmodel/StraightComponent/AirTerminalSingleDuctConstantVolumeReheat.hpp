/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctConstantVolumeReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat : public ModelObject
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
  // - API: Preserve openstudio::model scalar accessor names for this model-counterpart class.
  // - Field Mapping: maximumAirFlowRate, maximumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate, convergenceTolerance,
  //   and maximumReheatAirTemperature map directly to EnergyPlus AirTerminal:SingleDuct:ConstantVolume:Reheat fields.
  // - Field Mapping: Availability Schedule Name, Air Inlet Node Name, Air Outlet Node Name, and Reheat Coil Name are relationship
  //   fields and are intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctConstantVolumeReheat writes those relationship fields and these scalar fields.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
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
