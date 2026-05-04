/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctVAVNoReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVNoReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVNoReheat(const Model& model);

    virtual ~AirTerminalSingleDuctVAVNoReheat() override = default;
    AirTerminalSingleDuctVAVNoReheat(const AirTerminalSingleDuctVAVNoReheat& other) = default;
    AirTerminalSingleDuctVAVNoReheat(AirTerminalSingleDuctVAVNoReheat&& other) = default;
    AirTerminalSingleDuctVAVNoReheat& operator=(const AirTerminalSingleDuctVAVNoReheat&) = default;
    AirTerminalSingleDuctVAVNoReheat& operator=(AirTerminalSingleDuctVAVNoReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();

    bool addToNode(Node& node);

    // Connectivity Notes:
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVNoReheat.
    // - `addToNode` is scoped to an AirLoopHVAC demand-side zone branch node: it creates a terminal inlet node, rewires the
    //   ZoneSplitter branch outlet to that inlet node, points the terminal outlet at the zone air node, updates an owning ADU outlet when
    //   present, and registers the terminal on the served zone equipment list.
    // - `removeFromLoop` reverses those side effects by reconnecting the ZoneSplitter branch to the zone air node through the shared
    //   StraightComponent removal path, removing the zone equipment-list entry, clearing any ADU outlet/terminal references, clearing this
    //   terminal's node pointers, and removing the temporary inlet node.
    // - The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:NoReheat` fields; connectivity is represented by paired
    //   inlet/outlet node relationships.
    // - Documented Delta: canonical `model` accepts a broader set of demand insertion paths. This epmodel wrapper currently requires the
    //   target node to already be the ZoneSplitter/Mixer branch node produced by the epmodel AirLoopHVAC zone-branch topology.
    // - DSOA/OA-control behavior remains outside this public surface.
    // - Evidence: `src/model/AirTerminalSingleDuctVAVNoReheat.hpp`, `src/model/AirTerminalSingleDuctVAVNoReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVNoReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVNoReheat_GTest.cpp`.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<Schedule> minimumAirFlowFractionSchedule() const;
    bool setMinimumAirFlowFractionSchedule(Schedule& schedule);
    void resetMinimumAirFlowFractionSchedule();

    boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
    bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
    void resetMinimumAirFlowTurndownSchedule();

    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();
    void resetMaximumAirFlowRate();

    boost::optional<std::string> zoneMinimumAirFlowInputMethod() const;
    bool setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod);
    void resetZoneMinimumAirFlowInputMethod();

    boost::optional<double> constantMinimumAirFlowFraction() const;
    bool isConstantMinimumAirFlowFractionAutosized() const;
    bool isConstantMinimumAirFlowFractionDefaulted() const;
    bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
    void autosizeConstantMinimumAirFlowFraction();
    void resetConstantMinimumAirFlowFraction();

    boost::optional<double> fixedMinimumAirFlowRate() const;
    bool isFixedMinimumAirFlowRateAutosized() const;
    bool isFixedMinimumAirFlowRateDefaulted() const;
    bool setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate);
    void autosizeFixedMinimumAirFlowRate();
    void resetFixedMinimumAirFlowRate();

   protected:
    using ImplType = detail::AirTerminalSingleDuctVAVNoReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
