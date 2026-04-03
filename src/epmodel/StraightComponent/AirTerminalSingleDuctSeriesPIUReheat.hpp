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

    virtual ~AirTerminalSingleDuctSeriesPIUReheat() override = default;
    AirTerminalSingleDuctSeriesPIUReheat(const AirTerminalSingleDuctSeriesPIUReheat& other) = default;
    AirTerminalSingleDuctSeriesPIUReheat(AirTerminalSingleDuctSeriesPIUReheat&& other) = default;
    AirTerminalSingleDuctSeriesPIUReheat& operator=(const AirTerminalSingleDuctSeriesPIUReheat&) = default;
    AirTerminalSingleDuctSeriesPIUReheat& operator=(AirTerminalSingleDuctSeriesPIUReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanControlTypeValues();
    static std::vector<std::string> heatingControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar Series PIU reheat contract is aligned, but the coupled schedule/node surface remains intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctSeriesPIUReheat.
    // - Implemented Parity: `maximumAirFlowRate`, `maximumPrimaryAirFlowRate`, `minimumPrimaryAirFlowFraction`, `maximumHotWaterorSteamFlowRate`, `minimumHotWaterorSteamFlowRate`, `convergenceTolerance`, `fanControlType`, `minimumFanTurnDownRatio`, `heatingControlType`, `designHeatingDischargeAirTemperature`, and `highLimitHeatingDischargeAirTemperature` preserve the canonical scalar contract.
    // - Documented Delta: Node names and the zone-mixer object-link surface remain outside this pass.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:SeriesPIU:Reheat` fields; the translator wires the coupled components separately.
    // - Evidence: `src/model/AirTerminalSingleDuctSeriesPIUReheat.hpp`, `src/model/AirTerminalSingleDuctSeriesPIUReheat.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctSeriesPIUReheat.cpp`, and `src/epmodel/test/AirTerminalSingleDuctSeriesPIUReheat_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, node, and coupled-component helpers when relationship parity expands.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

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
