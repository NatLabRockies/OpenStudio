/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolReheat : public ModelObject
{
 public:
  explicit AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model);

  virtual ~AirTerminalSingleDuctVAVHeatAndCoolReheat() override = default;
  AirTerminalSingleDuctVAVHeatAndCoolReheat(const AirTerminalSingleDuctVAVHeatAndCoolReheat& other) = default;
  AirTerminalSingleDuctVAVHeatAndCoolReheat(AirTerminalSingleDuctVAVHeatAndCoolReheat&& other) = default;
  AirTerminalSingleDuctVAVHeatAndCoolReheat& operator=(const AirTerminalSingleDuctVAVHeatAndCoolReheat&) = default;
  AirTerminalSingleDuctVAVHeatAndCoolReheat& operator=(AirTerminalSingleDuctVAVHeatAndCoolReheat&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: maximumAirFlowRate, zoneMinimumAirFlowFraction, maximumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate,
  //   convergenceTolerance, and maximumReheatAirTemperature map directly to EnergyPlus AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat fields.
  // - Field Mapping: Availability Schedule Name, Damper/Air Inlet/Air Outlet node names, Reheat Coil Object Type/Name, and
  //   Minimum Air Flow Turndown Schedule Name are relationship/target-link fields and intentionally excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctVAVHeatAndCoolReheat writes these scalar fields plus relationship links.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void autosizeMaximumAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

  boost::optional<double> maximumHotWaterorSteamFlowRate() const;
  bool isMaximumHotWaterorSteamFlowRateAutosized() const;
  bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
  void autosizeMaximumHotWaterorSteamFlowRate();

  double minimumHotWaterorSteamFlowRate() const;
  bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

  double convergenceTolerance() const;
  bool setConvergenceTolerance(double convergenceTolerance);

  double maximumReheatAirTemperature() const;
  bool setMaximumReheatAirTemperature(double maximumReheatAirTemperature);

 protected:
  using ImplType = detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctVAVHeatAndCoolReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
