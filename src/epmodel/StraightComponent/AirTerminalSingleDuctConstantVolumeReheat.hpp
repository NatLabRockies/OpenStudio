/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class HVACComponent;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctConstantVolumeReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeReheat(const Model& model);
    AirTerminalSingleDuctConstantVolumeReheat(const Model& model, Schedule& availabilitySchedule, HVACComponent& reheatCoil);

    virtual ~AirTerminalSingleDuctConstantVolumeReheat() override = default;
    AirTerminalSingleDuctConstantVolumeReheat(const AirTerminalSingleDuctConstantVolumeReheat& other) = default;
    AirTerminalSingleDuctConstantVolumeReheat(AirTerminalSingleDuctConstantVolumeReheat&& other) = default;
    AirTerminalSingleDuctConstantVolumeReheat& operator=(const AirTerminalSingleDuctConstantVolumeReheat&) = default;
    AirTerminalSingleDuctConstantVolumeReheat& operator=(AirTerminalSingleDuctConstantVolumeReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. Constructor, availability-schedule, reheat-coil, scalar field behavior, and loop-context insertion are aligned,
    //   while autosized-result query helpers are not yet exposed in the public epmodel API.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeReheat.
    // - Implemented Parity: The schedule-and-coil constructor, `availabilitySchedule`, validated `setReheatCoil`, the scalar accessors for
    //   `maximumAirFlowRate`, `maximumHotWaterorSteamFlowRate`, `minimumHotWaterorSteamFlowRate`, `convergenceTolerance`, and
    //   `maximumReheatAirTemperature`, the wrapper-specific `addToNode`, and `removeFromLoop` cover the current epmodel zone-branch
    //   insertion/removal path and zone-equipment registration cleanup through the shared helper.
    // - Documented Delta: The `epmodel`-only default constructor is preserved, and the family-specific autosized-result query helpers are not
    //   yet surfaced in the public API until shared sizing-result infrastructure exists.
    // - Field/Storage Mapping: The availability-schedule pointer, reheat-coil pointer, preserved scalar fields, and the inherited
    //   straight-component inlet/outlet node fields all store directly on the same EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:Reheat`
    //   object. If persisted availability-schedule storage is cleared, `availabilitySchedule()` repairs that stored pointer by rebinding the
    //   model always-on discrete schedule onto the same object before returning it. `addToNode` wires the same object onto the current
    //   epmodel zone-branch path, updates any linked `ZoneHVAC:AirDistributionUnit` outlet node to match the branch node, and registers the
    //   terminal on the owning thermal-zone equipment list via the shared helper. `removeFromLoop` reverses those references, removes the
    //   temporary terminal inlet node, and removes a plant-connected reheat coil from its demand branch. Canonical model still accepts a
    //   broader local-topology insertion surface than this wrapper-specific path.
    // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeReheat.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctConstantVolumeReheat_GTest.cpp`.
    // - Remaining Parity Work: Expose the autosized-result query helpers once shared sizing-result plumbing exists.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent reheatCoil() const;
    bool setReheatCoil(const HVACComponent& coil);
    void resetReheatCoil();

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
