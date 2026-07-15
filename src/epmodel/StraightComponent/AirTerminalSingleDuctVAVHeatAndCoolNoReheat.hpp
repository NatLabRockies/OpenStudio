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
  class Node;
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

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Connectivity Parity for the current epmodel zone-branch topology.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVHeatAndCoolNoReheat.
    // - Implemented Parity: `addToNode`, inherited `remove`, and `removeFromLoop` preserve terminal node wiring, AirLoopHVAC demand continuity, ZoneHVAC equipment registration, existing ADU references, and temporary inlet-node cleanup.
    // - Documented Delta: canonical `model` accepts a broader set of demand insertion paths. This epmodel wrapper currently requires the target node to already be the ZoneSplitter/Mixer branch node produced by the epmodel AirLoopHVAC zone-branch topology.
    // - Field/Storage Mapping: Scalars and links map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat` and `ZoneHVAC:AirDistributionUnit` fields; node links are resolved through epmodel transient Node targets.
    // - Evidence: `src/model/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp`, `src/model/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVHeatAndCoolNoReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVHeatAndCoolNoReheat_GTest.cpp`.
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
