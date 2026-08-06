/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLREHEAT_HPP

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
    class AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model);
    explicit AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model, const HVACComponent& reheatCoil);

    virtual ~AirTerminalSingleDuctVAVHeatAndCoolReheat() override = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat(const AirTerminalSingleDuctVAVHeatAndCoolReheat& other) = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat(AirTerminalSingleDuctVAVHeatAndCoolReheat&& other) = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat& operator=(const AirTerminalSingleDuctVAVHeatAndCoolReheat&) = default;
    AirTerminalSingleDuctVAVHeatAndCoolReheat& operator=(AirTerminalSingleDuctVAVHeatAndCoolReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Near Parity.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVHeatAndCoolReheat.
    // - Implemented Parity: The canonical `(Model, HVACComponent)` constructor establishes the required reheat-coil relationship. `addToNode`,
    //   zone equipment registration/cleanup, splitter/mixer branch rewiring, ADU outlet synchronization, reheat-coil child ownership, and
    //   terminal removal implement canonical-style zone-branch connectivity behavior, including rollback of
    //   entity-local `addToNode()` mutations on late failure, with epmodel-specific guards for already-connected terminals and mismatched
    //   splitter/mixer branches plus explicit `removeFromLoop()` cleanup after supported detach or stale-reference recovery paths.
    // - Documented Delta: The legacy `(Model)` constructor remains available for incremental object assembly and allows late coil assignment
    //   through `setReheatCoil`; this wrapper does not claim broader autosizing or clone-helper parity.
    // - Field/Storage Mapping: Scalars and relationships map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:HeatAndCool:Reheat` and
    //   `ZoneHVAC:AirDistributionUnit` fields; node links are represented by tracked epmodel Node targets.
    // - Evidence: `src/model/AirTerminalSingleDuctVAVHeatAndCoolReheat.cpp`,
    //   `src/epmodel/StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVHeatAndCoolReheat.cpp`, and
    //   `src/epmodel/test/AirTerminalSingleDuctVAVHeatAndCoolReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the remaining canonical autosized-result and deep-clone helper behavior.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    HVACComponent reheatCoil() const;
    bool setReheatCoil(const HVACComponent& heatingCoilName);

    boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
    bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
    void resetMinimumAirFlowTurndownSchedule();

    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();

    double zoneMinimumAirFlowFraction() const;
    bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

    boost::optional<double> maximumHotWaterorSteamFlowRate() const;
    bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
    bool isMaximumHotWaterorSteamFlowRateAutosized() const;
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
