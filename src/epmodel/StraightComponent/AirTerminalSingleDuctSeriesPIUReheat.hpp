/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTSERIESPIUREHEAT_HPP

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
    class AirTerminalSingleDuctSeriesPIUReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctSeriesPIUReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctSeriesPIUReheat(const Model& model);
    explicit AirTerminalSingleDuctSeriesPIUReheat(const Model& model, HVACComponent& fan, HVACComponent& reheatCoil);

    virtual ~AirTerminalSingleDuctSeriesPIUReheat() override = default;
    AirTerminalSingleDuctSeriesPIUReheat(const AirTerminalSingleDuctSeriesPIUReheat& other) = default;
    AirTerminalSingleDuctSeriesPIUReheat(AirTerminalSingleDuctSeriesPIUReheat&& other) = default;
    AirTerminalSingleDuctSeriesPIUReheat& operator=(const AirTerminalSingleDuctSeriesPIUReheat&) = default;
    AirTerminalSingleDuctSeriesPIUReheat& operator=(AirTerminalSingleDuctSeriesPIUReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanControlTypeValues();
    static std::vector<std::string> heatingControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. Terminal-only and zone-serving demand-branch insertion/removal are aligned, while the broader canonical
    //   plenum/clone/autosized-result surface remains narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctSeriesPIUReheat.
    // - Implemented Parity: The canonical `(Model, HVACComponent fan, HVACComponent reheatCoil)` constructor establishes both required child
    //   relationships. `availabilitySchedule`, validated `fan` and `reheatCoil` relationships, and PIU control scalars are preserved.
    //   `addToNode` atomically supports both terminal-only splitter-to-mixer branches and zone-serving branches; only a served zone receives
    //   secondary-air exhaust, equipment, and ADU projections. `remove()` and `removeFromLoop()` preserve canonical ownership semantics.
    // - Documented Delta: The legacy `(Model)` constructor remains available for incremental object assembly and does not establish the fan
    //   or reheat coil. epmodel still omits `secondaryAirInletPort`, `setInducedAirPlenumZone(ThermalZone&)`, `clone(...)`, autosized-result
    //   convenience helpers. AirLoop-level attachment of a zone to an already inserted single-duct terminal is shared AirLoopHVAC work.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:SeriesPIU:Reheat` fields; epmodel rewires the zone branch through a terminal-owned inlet node, persists a distinct secondary inlet node on the same object, records that node on the owning zone exhaust-node list, on `addToNode` synchronizes the PIU fan availability to the serving air loop, and cleans zone, ADU, secondary-air, and plant references in the supported teardown paths.
    // - Evidence: `src/model/AirTerminalSingleDuctSeriesPIUReheat.hpp`, `src/model/AirTerminalSingleDuctSeriesPIUReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctSeriesPIUReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctSeriesPIUReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted plenum, clone, secondary-port, and autosized-result helpers if a later campaign needs the broader canonical surface.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    bool addToNode(Node& node);

    HVACComponent fan() const;
    bool setFan(const HVACComponent& fan);

    HVACComponent reheatCoil() const;
    bool setReheatCoil(const HVACComponent& coil);

    boost::optional<Node> secondaryAirInletNode() const;

    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();

    boost::optional<double> maximumPrimaryAirFlowRate() const;
    bool isMaximumPrimaryAirFlowRateAutosized() const;
    bool setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate);
    void autosizeMaximumPrimaryAirFlowRate();

    boost::optional<double> minimumPrimaryAirFlowFraction() const;
    bool isMinimumPrimaryAirFlowFractionAutosized() const;
    bool setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction);
    void autosizeMinimumPrimaryAirFlowFraction();

    boost::optional<double> maximumHotWaterorSteamFlowRate() const;
    bool isMaximumHotWaterorSteamFlowRateAutosized() const;
    bool setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate);
    void resetMaximumHotWaterorSteamFlowRate();
    void autosizeMaximumHotWaterorSteamFlowRate();

    double minimumHotWaterorSteamFlowRate() const;
    bool setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate);

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);

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
    using ImplType = detail::AirTerminalSingleDuctSeriesPIUReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctSeriesPIUReheat(std::shared_ptr<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
