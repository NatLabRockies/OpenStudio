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

    // Schema Alignment Notes:
    // - Status: Partial Parity. This wrapper is closer to parity on constructors, availability-schedule handling and canonicalization behavior,
    //   and maximum-air-flow-rate scalar/autosize surface, but `addToNode` remains narrower than the canonical model's insertion behavior.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeNoReheat.
    // - Implemented Parity: The canonical model exposes the schedule-taking constructor; `epmodel` retains that constructor and also adds a default
    //   constructor that canonicalizes to `Model::alwaysOnDiscreteSchedule()` plus autosized maximum flow. `availabilitySchedule`,
    //   `maximumAirFlowRate`, its autosize state mutators, and `autosizedMaximumAirFlowRate` preserve the remaining public contract, and
    //   `availabilitySchedule()` intentionally repairs a missing required reference back to `Model::alwaysOnDiscreteSchedule()` in the same
    //   OpenStudio style used by the canonical wrapper family.
    // - Documented Delta: `autosizedMaximumAirFlowRate` is currently a typed `boost::none` stub because `epmodel` does not yet expose family-specific sizing
    //   result lookup without shared-file work outside this wrapper. `addToNode` is also intentionally narrower than the canonical model: it currently
    //   requires a demand-side drop node tied to an existing splitter/mixer branch pairing instead of supporting the canonical wrapper's broader node insertion paths.
    // - Field/Storage Mapping: The preserved schedule relationship and maximum-air-flow-rate field map directly to EnergyPlus
    //   `AirTerminal:SingleDuct:ConstantVolume:NoReheat` storage; when the required schedule pointer is missing, the getter canonicalizes the stored state
    //   by reattaching the model's always-on discrete schedule before returning it.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeNoReheat.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeNoReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeNoReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctConstantVolumeNoReheat_GTest.cpp`.
    // - Remaining Parity Work: Replace the `autosizedMaximumAirFlowRate` stub once `epmodel` can read this family's sizing results.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();
    boost::optional<double> autosizedMaximumAirFlowRate() const;

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl;

    friend class openstudio::epmodel::Model;

    explicit AirTerminalSingleDuctConstantVolumeNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
