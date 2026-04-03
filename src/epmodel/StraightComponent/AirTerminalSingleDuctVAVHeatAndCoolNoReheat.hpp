/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;

namespace detail {
class AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolNoReheat : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const Model& model);

  virtual ~AirTerminalSingleDuctVAVHeatAndCoolNoReheat() override = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const AirTerminalSingleDuctVAVHeatAndCoolNoReheat& other) = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat(AirTerminalSingleDuctVAVHeatAndCoolNoReheat&& other) = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat& operator=(const AirTerminalSingleDuctVAVHeatAndCoolNoReheat&) = default;
  AirTerminalSingleDuctVAVHeatAndCoolNoReheat& operator=(AirTerminalSingleDuctVAVHeatAndCoolNoReheat&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The scalar VAV heat-and-cool no-reheat contract is aligned; relationship and node plumbing remain narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVHeatAndCoolNoReheat.
  // - Implemented Parity: `maximumAirFlowRate` and `zoneMinimumAirFlowFraction` preserve the canonical scalar contract.
  // - Documented Delta: Air inlet/outlet node names remain outside this public surface.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat` fields; the translator handles links separately.
  // - Evidence: `src/model/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp`, `src/model/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVHeatAndCoolNoReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVHeatAndCoolNoReheat_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted relationship helpers when this type moves beyond scalar parity.
  boost::optional<Schedule> availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);
  void resetAvailabilitySchedule();

  boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
  bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
  void resetMinimumAirFlowTurndownSchedule();

  boost::optional<double> maximumAirFlowRate() const;
  bool isMaximumAirFlowRateAutosized() const;
  bool setMaximumAirFlowRate(double maximumAirFlowRate);
  void autosizeMaximumAirFlowRate();

  double zoneMinimumAirFlowFraction() const;
  bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

protected:
  using ImplType = detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctVAVHeatAndCoolNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
