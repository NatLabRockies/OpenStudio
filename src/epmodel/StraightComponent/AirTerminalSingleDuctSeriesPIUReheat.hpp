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

  /**
   * \brief Series powered induction unit with a fan, reheat coil, and secondary-air exhaust path.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductseriespiureheat,AirTerminal:SingleDuct:SeriesPIU:Reheat}.
   *
   * \par Important behavior
   * `addToNode` supports terminal-only and served-zone branches. A served zone receives secondary-air exhaust,
   * equipment, and AirDistributionUnit projections; removal reverses those links and cleans child and plant paths.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctSeriesPIUReheat`. The fan/reheat-coil relationships,
   * schedule, PIU scalar controls, and supported branch lifecycle are represented.
   *
   * \par Known limitations
   * The legacy Model-only assembly constructor remains available, but epmodel does not expose `secondaryAirInletPort`,
   * `clone`, or autosized-result helpers. Broader AirLoop-level zone attachment is separate work.
   */
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
