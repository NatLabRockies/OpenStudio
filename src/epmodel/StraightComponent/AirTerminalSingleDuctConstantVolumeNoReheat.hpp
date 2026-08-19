/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalSingleDuctConstantVolumeNoReheat_Impl;
  }

  /**
   * \brief Constant-volume single-duct terminal without reheat.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-air-distribution-equipment.html#airterminalsingleductconstantvolumenoreheat,AirTerminal:SingleDuct:ConstantVolume:NoReheat}.
   *
   * \par Important behavior
   * The availability schedule is required for translation; constructors seed it and the getter repairs missing
   * persisted state. `addToNode` and `removeFromLoop` operate on the existing AirLoopHVAC zone branch and maintain
   * paired terminal inlet/outlet nodes and zone-equipment registration.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirTerminalSingleDuctConstantVolumeNoReheat`. The schedule and airflow APIs
   * are represented, including autosizing controls. The epmodel default constructor additionally seeds the schedule.
   *
   * \par Known limitations
   * The terminal must be added to an existing epmodel ZoneSplitter/ZoneMixer branch; broader family-specific topology insertion paths are not exposed.
   */
  class EPMODEL_API AirTerminalSingleDuctConstantVolumeNoReheat : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model);
    AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model, Schedule& availabilitySchedule);

    virtual ~AirTerminalSingleDuctConstantVolumeNoReheat() override = default;
    AirTerminalSingleDuctConstantVolumeNoReheat(const AirTerminalSingleDuctConstantVolumeNoReheat& other) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat(AirTerminalSingleDuctConstantVolumeNoReheat&& other) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat& operator=(const AirTerminalSingleDuctConstantVolumeNoReheat&) = default;
    AirTerminalSingleDuctConstantVolumeNoReheat& operator=(AirTerminalSingleDuctConstantVolumeNoReheat&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();
    boost::optional<double> autosizedMaximumAirFlowRate() const;

   protected:
    using ImplType = detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctConstantVolumeNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
