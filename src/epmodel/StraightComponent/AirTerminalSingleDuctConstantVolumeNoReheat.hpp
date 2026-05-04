/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeNoReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeNoReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model);
    AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model, Schedule& availabilitySchedule);

    virtual ~AirTerminalSingleDuctConstantVolumeNoReheat() override = default;
    AirTerminalSingleDuctConstantVolumeNoReheat(const AirTerminalSingleDuctConstantVolumeNoReheat& other) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat(AirTerminalSingleDuctConstantVolumeNoReheat&& other) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat& operator=(const AirTerminalSingleDuctConstantVolumeNoReheat&) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat& operator=(AirTerminalSingleDuctConstantVolumeNoReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Connectivity Notes:
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeNoReheat.
    // - `addToNode` is intentionally scoped to an AirLoopHVAC demand-side zone branch node: it creates a terminal inlet node, rewires the
    //   ZoneSplitter branch outlet to that inlet node, points the terminal outlet at the zone air node, updates an owning ADU outlet when
    //   present, and registers the terminal on the served zone equipment list.
    // - `removeFromLoop` reverses the entity-owned side effects by reconnecting the ZoneSplitter branch to the zone air node through the
    //   shared StraightComponent removal path, removing the zone equipment-list entry, clearing any ADU outlet/terminal references, and
    //   clearing this terminal's node pointers.
    // - The availability schedule remains a required object relationship: constructors seed it, the getter repairs missing persisted state,
    //   and translation depends on it. Node connectivity is likewise treated as a paired inlet/outlet relationship.
    // - Documented Delta: canonical `model` accepts a broader set of demand insertion paths. This epmodel wrapper currently requires the
    //   target node to already be the ZoneSplitter/Mixer branch node produced by the epmodel AirLoopHVAC zone-branch topology.
    // - Scalar Delta: `autosizedMaximumAirFlowRate` remains a typed `boost::none` stub until epmodel exposes family-specific sizing results.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();
    boost::optional<double> autosizedMaximumAirFlowRate() const;

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
