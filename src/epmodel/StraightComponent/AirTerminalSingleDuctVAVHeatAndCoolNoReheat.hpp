/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTVAVHEATANDCOOLNOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl;
  }

  /**
   * \brief Variable-air-volume terminal that supports heating and cooling without a reheat coil.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductvavheatandcoolnoreheat,AirTerminal:SingleDuct:VAV:HeatAndCool:NoReheat}.
   *
   * \par Important behavior
   * Branch insertion rewires the terminal inlet/outlet, AirDistributionUnit outlet, and zone equipment registration;
   * removal clears those references and the temporary inlet node.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctVAVHeatAndCoolNoReheat`. The schedule, turndown schedule,
   * airflow, control, and supported zone-branch insertion APIs are represented.
   *
   * \par Known limitations
   * `addToNode` currently requires the target to be the epmodel AirLoopHVAC ZoneSplitter/ZoneMixer branch node;
   * broader Model insertion paths are not exposed.
   */
  class EPMODEL_API AirTerminalSingleDuctVAVHeatAndCoolNoReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const Model& model);

    virtual ~AirTerminalSingleDuctVAVHeatAndCoolNoReheat() override = default;
    AirTerminalSingleDuctVAVHeatAndCoolNoReheat(const AirTerminalSingleDuctVAVHeatAndCoolNoReheat& other) = default;
    AirTerminalSingleDuctVAVHeatAndCoolNoReheat(AirTerminalSingleDuctVAVHeatAndCoolNoReheat&& other) = default;
    AirTerminalSingleDuctVAVHeatAndCoolNoReheat& operator=(const AirTerminalSingleDuctVAVHeatAndCoolNoReheat&) = default;
    AirTerminalSingleDuctVAVHeatAndCoolNoReheat& operator=(AirTerminalSingleDuctVAVHeatAndCoolNoReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
    bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
    void resetMinimumAirFlowTurndownSchedule();

    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();

    double zoneMinimumAirFlowFraction() const;
    bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);

   protected:
    using ImplType = detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctVAVHeatAndCoolNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
