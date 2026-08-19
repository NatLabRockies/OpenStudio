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

  /**
   * \brief Variable-air-volume terminal with a typed reheat coil.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductvavreheat,AirTerminal:SingleDuct:VAV:Reheat}.
   *
   * \par Important behavior
   * The reheat coil shares a node with the terminal damper outlet/coil inlet. Supported add/remove operations keep
   * the air-loop demand branch, AirDistributionUnit, zone equipment, and reheat-coil plant branch consistent.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctVAVReheat`. Schedule, typed reheat coil, airflow/scalar,
   * branch lifecycle, and node relationships are represented. The legacy epmodel constructor permits late coil assignment.
   *
   * \par Known limitations
   * Canonical outdoor-air export and broader demand insertion paths are not implemented in this wrapper.
   */
  class EPMODEL_API AirTerminalSingleDuctVAVReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVReheat(const Model& model);
    explicit AirTerminalSingleDuctVAVReheat(const Model& model, Schedule& availabilitySchedule, HVACComponent& coil);

    virtual ~AirTerminalSingleDuctVAVReheat() override = default;
    AirTerminalSingleDuctVAVReheat(const AirTerminalSingleDuctVAVReheat& other) = default;
    AirTerminalSingleDuctVAVReheat(AirTerminalSingleDuctVAVReheat&& other) = default;
    AirTerminalSingleDuctVAVReheat& operator=(const AirTerminalSingleDuctVAVReheat&) = default;
    AirTerminalSingleDuctVAVReheat& operator=(AirTerminalSingleDuctVAVReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();
    static std::vector<std::string> damperHeatingActionValues();

    bool addToNode(Node& node);

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
