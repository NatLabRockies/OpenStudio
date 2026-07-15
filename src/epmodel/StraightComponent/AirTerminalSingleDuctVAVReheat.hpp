/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVREHEAT_HPP

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
    class AirTerminalSingleDuctVAVReheat_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctVAVReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVReheat(const Model& model);

    virtual ~AirTerminalSingleDuctVAVReheat() override = default;
    AirTerminalSingleDuctVAVReheat(const AirTerminalSingleDuctVAVReheat& other) = default;
    AirTerminalSingleDuctVAVReheat(AirTerminalSingleDuctVAVReheat&& other) = default;
    AirTerminalSingleDuctVAVReheat& operator=(const AirTerminalSingleDuctVAVReheat&) = default;
    AirTerminalSingleDuctVAVReheat& operator=(AirTerminalSingleDuctVAVReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();
    static std::vector<std::string> damperHeatingActionValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Connectivity Parity for the current epmodel zone-branch topology.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctVAVReheat.
    // - Implemented Parity: `addToNode`, `remove`, and `removeFromLoop` preserve terminal node wiring, AirLoopHVAC demand continuity, ZoneHVAC equipment registration, existing ADU references, temporary inlet-node cleanup, and reheat-coil plant branch cleanup.
    // - Documented Delta: Canonical OS-only outdoor-air export behavior is not implemented in this epmodel wrapper.
    // - Field/Storage Mapping: Scalars and links map directly to EnergyPlus `AirTerminal:SingleDuct:VAV:Reheat` and `ZoneHVAC:AirDistributionUnit` fields; node links are resolved through epmodel transient Node targets.
    // - Evidence: `src/model/AirTerminalSingleDuctVAVReheat.hpp`, `src/model/AirTerminalSingleDuctVAVReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctVAVReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctVAVReheat_GTest.cpp`.
    // - Remaining Campaign Verification: Translator-specific regression coverage is out of scope unless EnergyPlus forward-translation assertions are authorized.
    HVACComponent reheatCoil() const;
    bool setReheatCoil(HVACComponent& coil);

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

    std::string zoneMinimumAirFlowInputMethod();
    bool setZoneMinimumAirFlowInputMethod(const std::string& value);

    std::string zoneMinimumAirFlowMethod();
    bool setZoneMinimumAirFlowMethod(const std::string& value);

    boost::optional<double> constantMinimumAirFlowFraction() const;
    bool isConstantMinimumAirFlowFractionAutosized() const;
    bool setConstantMinimumAirFlowFraction(double value);
    void autosizeConstantMinimumAirFlowFraction();

    boost::optional<double> fixedMinimumAirFlowRate() const;
    bool isFixedMinimumAirFlowRateAutosized() const;
    bool setFixedMinimumAirFlowRate(double value);
    void autosizeFixedMinimumAirFlowRate();

    boost::optional<double> maximumHotWaterOrSteamFlowRate();
    bool isMaximumHotWaterOrSteamFlowRateAutosized() const;
    bool setMaximumHotWaterOrSteamFlowRate(double value);
    void autosizeMaximumHotWaterOrSteamFlowRate();

    double minimumHotWaterOrSteamFlowRate();
    bool setMinimumHotWaterOrStreamFlowRate(double value);

    double convergenceTolerance();
    bool setConvergenceTolerance(double value);

    std::string damperHeatingAction();
    bool setDamperHeatingAction(const std::string& value);

    boost::optional<double> maximumFlowPerZoneFloorAreaDuringReheat();
    bool isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const;
    bool setMaximumFlowPerZoneFloorAreaDuringReheat(double value);
    void autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
    void resetMaximumFlowPerZoneFloorAreaDuringReheat();

    boost::optional<double> maximumFlowFractionDuringReheat();
    bool isMaximumFlowFractionDuringReheatAutosized() const;
    bool setMaximumFlowFractionDuringReheat(double value);
    void autosizeMaximumFlowFractionDuringReheat();
    void resetMaximumFlowFractionDuringReheat();

    double maximumReheatAirTemperature();
    bool setMaximumReheatAirTemperature(double value);

   protected:
    using ImplType = detail::AirTerminalSingleDuctVAVReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
