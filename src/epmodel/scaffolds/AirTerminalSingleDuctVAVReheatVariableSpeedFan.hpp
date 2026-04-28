/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl;
}

class EPMODEL_API AirTerminalSingleDuctVAVReheatVariableSpeedFan : public ModelObject
{
 public:
  explicit AirTerminalSingleDuctVAVReheatVariableSpeedFan(const Model& model);

  virtual ~AirTerminalSingleDuctVAVReheatVariableSpeedFan() override = default;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan(const AirTerminalSingleDuctVAVReheatVariableSpeedFan& other) = default;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan(AirTerminalSingleDuctVAVReheatVariableSpeedFan&& other) = default;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan& operator=(const AirTerminalSingleDuctVAVReheatVariableSpeedFan&) = default;
  AirTerminalSingleDuctVAVReheatVariableSpeedFan& operator=(AirTerminalSingleDuctVAVReheatVariableSpeedFan&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart exists, so this class uses IDD-derived scalar accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus AirTerminal:SingleDuct:VAV:Reheat:VariableSpeedFan fields.
  // - Field Mapping: Availability Schedule Name, Air Inlet Node Name, Air Outlet Node Name, Fan Object Type,
  //   Fan Name, Heating Coil Object Type, Heating Coil Name, and Minimum Air Flow Turndown Schedule Name are
  //   relationship/target-link fields and intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship/non-scalar behavior incrementally after scalar scaffold saturation.
  boost::optional<double> maximumCoolingAirFlowRate() const;
  bool isMaximumCoolingAirFlowRateAutosized() const;
  bool setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate);
  void autosizeMaximumCoolingAirFlowRate();

  boost::optional<double> maximumHeatingAirFlowRate() const;
  bool isMaximumHeatingAirFlowRateAutosized() const;
  bool setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate);
  void autosizeMaximumHeatingAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool isMinimumHotWaterorSteamFlowRateDefaulted() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);
  void resetMinimumHotWaterorSteamFlowRate();

  double heatingConvergenceTolerance() const;
  bool isHeatingConvergenceToleranceDefaulted() const;
  bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
  void resetHeatingConvergenceTolerance();

 protected:
  using ImplType = detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctVAVReheatVariableSpeedFan(std::shared_ptr<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
