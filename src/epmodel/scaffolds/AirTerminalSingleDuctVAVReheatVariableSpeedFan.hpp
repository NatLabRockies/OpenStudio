/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEATVARIABLESPEEDFAN_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class HVACComponent;
  class Node;

  namespace detail {
    class AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVReheatVariableSpeedFan : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVReheatVariableSpeedFan(const Model& model);

    virtual ~AirTerminalSingleDuctVAVReheatVariableSpeedFan() override = default;
    AirTerminalSingleDuctVAVReheatVariableSpeedFan(const AirTerminalSingleDuctVAVReheatVariableSpeedFan& other) = default;
    AirTerminalSingleDuctVAVReheatVariableSpeedFan(AirTerminalSingleDuctVAVReheatVariableSpeedFan&& other) = default;
    AirTerminalSingleDuctVAVReheatVariableSpeedFan& operator=(const AirTerminalSingleDuctVAVReheatVariableSpeedFan&) = default;
    AirTerminalSingleDuctVAVReheatVariableSpeedFan& operator=(AirTerminalSingleDuctVAVReheatVariableSpeedFan&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Connectivity-focused parity for the current epmodel zone-branch topology.
    // - Canonical Counterpart: No direct openstudio::model wrapper exists; this entity follows the established epmodel
    //   single-duct VAV/reheat terminal contract used by nearby straight-component air terminals.
    // - Implemented Parity: `addToNode`, `remove`, and `removeFromLoop` preserve terminal node wiring,
    //   AirLoopHVAC demand continuity, ZoneHVAC equipment registration, temporary inlet-node cleanup, heating-coil
    //   plant branch cleanup, and both ADU-backed and stale ADU-only detach behavior for the supported zone-branch
    //   insertion paths, including the explicit same-model/already-connected/zone-branch add guards covered by the
    //   local connectivity tests.
    // - Documented Delta: This wrapper still exposes only the bounded scalar and relationship surface needed for
    //   connectivity parity; broader canonical-style clone/autosized-result convenience helpers are not claimed.
    // - Field/Storage Mapping: Scalars map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:Reheat:VariableSpeedFan`
    //   fields; availability schedule, fan, heating coil, and node links are typed object relationships resolved through
    //   epmodel transient loop topology.
    // - Evidence: Nearby single-duct precedent in `src/epmodel/StraightComponent/AirTerminalSingleDuctVAVReheat.cpp`
    //   and focused local coverage in `src/epmodel/test/AirTerminalSingleDuctVAVReheatVariableSpeedFan_GTest.cpp`.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent fan() const;
    bool setFan(HVACComponent& fan);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(HVACComponent& coil);

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
