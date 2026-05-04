/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTPARALLELPIUREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTPARALLELPIUREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class HVACComponent;
  class Node;

  namespace detail {
    class AirTerminalSingleDuctParallelPIUReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctParallelPIUReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctParallelPIUReheat(const Model& model);
    AirTerminalSingleDuctParallelPIUReheat(const Model& model, Schedule& schedule, HVACComponent& fan, HVACComponent& reheatCoil);

    virtual ~AirTerminalSingleDuctParallelPIUReheat() override = default;
    AirTerminalSingleDuctParallelPIUReheat(const AirTerminalSingleDuctParallelPIUReheat& other) = default;
    AirTerminalSingleDuctParallelPIUReheat(AirTerminalSingleDuctParallelPIUReheat&& other) = default;
    AirTerminalSingleDuctParallelPIUReheat& operator=(const AirTerminalSingleDuctParallelPIUReheat&) = default;
    AirTerminalSingleDuctParallelPIUReheat& operator=(AirTerminalSingleDuctParallelPIUReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanControlTypeValues();
    static std::vector<std::string> heatingControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Connectivity parity is implemented for the current epmodel zone-branch insertion/removal path, including add/remove cleanup, child ownership, and secondary-air exhaust wiring.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctParallelPIUReheat.
    // - Implemented Parity: The `(Model, Schedule, HVACComponent fan, HVACComponent reheatCoil)` constructor, `availabilitySchedule`, `fan`, `reheatCoil`, `secondaryAirInletNode`, `secondaryAirInletPort`, `addToNode`, the custom `removeFromLoop` cleanup path, child ownership, and the preserved PIU control scalars follow the canonical terminal behavior used by current epmodel loop and translator code.
    // - Documented Delta: epmodel currently omits the canonical autosized-result query helpers and `setInducedAirPlenumZone(ThermalZone&)` until the shared sizing and plenum infrastructure are broad enough to support them without stubs or local workarounds.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:ParallelPIU:Reheat` fields; epmodel rewires the zone branch through a terminal-owned inlet node, persists a distinct secondary inlet node, records that node on the zone exhaust `NodeList`, synchronizes fan availability to the serving air loop, and cleans zone, ADU, and plant references in the supported `remove()`/`removeFromLoop()` teardown paths, including the stale-zone cleanup regression path.
    // - Evidence: `src/model/AirTerminalSingleDuctParallelPIUReheat.hpp`, `src/model/AirTerminalSingleDuctParallelPIUReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctParallelPIUReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctParallelPIUReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted autosized-result helpers if a later campaign needs sizing-result convenience parity.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    bool addToNode(Node& node);

    HVACComponent fan() const;
    bool setFan(HVACComponent& hvacComponent);

    HVACComponent reheatCoil() const;
    bool setReheatCoil(HVACComponent& hvacComponent);

    boost::optional<Node> secondaryAirInletNode() const;
    unsigned secondaryAirInletPort() const;

    boost::optional<double> maximumPrimaryAirFlowRate() const;
    bool isMaximumPrimaryAirFlowRateAutosized() const;
    bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
    void autosizeMaximumPrimaryAirFlowRate();

    boost::optional<double> maximumSecondaryAirFlowRate() const;
    bool isMaximumSecondaryAirFlowRateAutosized() const;
    bool setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate);
    void autosizeMaximumSecondaryAirFlowRate();

    boost::optional<double> minimumPrimaryAirFlowFraction() const;
    bool isMinimumPrimaryAirFlowFractionAutosized() const;
    bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
    void autosizeMinimumPrimaryAirFlowFraction();

    boost::optional<double> fanOnFlowFraction() const;
    bool isFanOnFlowFractionAutosized() const;
    bool setFanOnFlowFraction(double fanOnFlowFraction);
    void autosizeFanOnFlowFraction();

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

    std::string fanControlType() const;
    bool setFanControlType(const std::string& fanControlType);

    double minimumFanTurnDownRatio() const;
    bool setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio);

    std::string heatingControlType() const;
    bool setHeatingControlType(const std::string& heatingControlType);

    double designHeatingDischargeAirTemperature() const;
    bool setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature);

    double highLimitHeatingDischargeAirTemperature() const;
    bool setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature);

   protected:
    using ImplType = detail::AirTerminalSingleDuctParallelPIUReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctParallelPIUReheat(std::shared_ptr<detail::AirTerminalSingleDuctParallelPIUReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
