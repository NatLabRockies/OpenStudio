/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctVAVNoReheat_Impl;
  }

  /**
   * \brief Variable-air-volume terminal without reheat.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductvavnoreheat,AirTerminal:SingleDuct:VAV:NoReheat}.
   *
   * \par Important behavior
   * The default constructor creates an always-on availability schedule and autosizes maximum airflow. `addToNode`
   * rewires the supported zone branch, updates AirDistributionUnit and zone-equipment references, and creates a
   * temporary inlet node that `removeFromLoop` cleans up.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctVAVNoReheat`. Schedule, airflow, and branch lifecycle
   * methods are represented.
   *
   * \par Known limitations
   * The epmodel target must already be the ZoneSplitter/ZoneMixer branch node. DesignSpecificationOutdoorAir and
   * broader Model demand insertion paths are not exposed.
   */
  class EPMODEL_API AirTerminalSingleDuctVAVNoReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVNoReheat(const Model& model);
    explicit AirTerminalSingleDuctVAVNoReheat(const Model& model, Schedule& schedule);

    virtual ~AirTerminalSingleDuctVAVNoReheat() override = default;
    AirTerminalSingleDuctVAVNoReheat(const AirTerminalSingleDuctVAVNoReheat& other) = default;
    AirTerminalSingleDuctVAVNoReheat(AirTerminalSingleDuctVAVNoReheat&& other) = default;
    AirTerminalSingleDuctVAVNoReheat& operator=(const AirTerminalSingleDuctVAVNoReheat&) = default;
    AirTerminalSingleDuctVAVNoReheat& operator=(AirTerminalSingleDuctVAVNoReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> zoneMinimumAirFlowInputMethodValues();

    bool addToNode(Node& node);

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
    void resetMaximumAirFlowRate();

    boost::optional<std::string> zoneMinimumAirFlowInputMethod() const;
    bool setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod);
    void resetZoneMinimumAirFlowInputMethod();

    boost::optional<double> constantMinimumAirFlowFraction() const;
    bool isConstantMinimumAirFlowFractionAutosized() const;
    bool isConstantMinimumAirFlowFractionDefaulted() const;
    bool setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction);
    void autosizeConstantMinimumAirFlowFraction();
    void resetConstantMinimumAirFlowFraction();

    boost::optional<double> fixedMinimumAirFlowRate() const;
    bool isFixedMinimumAirFlowRateAutosized() const;
    bool isFixedMinimumAirFlowRateDefaulted() const;
    bool setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate);
    void autosizeFixedMinimumAirFlowRate();
    void resetFixedMinimumAirFlowRate();

   protected:
    using ImplType = detail::AirTerminalSingleDuctVAVNoReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
