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

  /**
   * \brief Parallel powered induction unit with a fan, reheat coil, and secondary-air exhaust path.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductparallelpiureheat,AirTerminal:SingleDuct:ParallelPIU:Reheat}.
   *
   * \par Important behavior
   * `addToNode` supports terminal-only and zone-serving demand branches. For a served zone it creates the secondary
   * inlet/mixer path, updates zone exhaust and AirDistributionUnit references, and registers equipment atomically.
   * Removal prepares the air, zone, plenum, child, and optional plant graphs before mutation.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctParallelPIUReheat`. The fan/reheat-coil relationships,
   * schedules, PIU controls, branch lifecycle, and child ownership are represented.
   *
   * \par Known limitations
   * Autosized-result query helpers are not exposed. Child replacement requires supported same-model, unconnected fan
   * and coil wrappers.
   */
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
