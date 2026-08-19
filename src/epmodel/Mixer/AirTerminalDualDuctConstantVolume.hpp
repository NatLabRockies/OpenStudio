/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTCONSTANTVOLUME_HPP
#define EPMODEL_AIRTERMINALDUALDUCTCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "Mixer/Mixer.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalDualDuctConstantVolume_Impl;
  }

  /** \brief Represents a constant-volume dual-duct air terminal.
   *
   * \par EnergyPlus object
   * \epobject{group-air-distribution-equipment.html#airterminaldualductconstantvolume,AirTerminal:DualDuct:ConstantVolume}.
   *
   * \par Important behavior
   * Separate terminal inlet and outlet node relationships follow the supported dual-duct air-loop insertion and removal topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirTerminalDualDuctConstantVolume</code>.
   * <b>Not yet available: the SQL-backed <code>autosizedMaximumAirFlowRate()</code> result helper.</b>
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API AirTerminalDualDuctConstantVolume : public Mixer
  {
   public:
    explicit AirTerminalDualDuctConstantVolume(const Model& model);

    virtual ~AirTerminalDualDuctConstantVolume() override = default;
    AirTerminalDualDuctConstantVolume(const AirTerminalDualDuctConstantVolume& other) = default;
    AirTerminalDualDuctConstantVolume(AirTerminalDualDuctConstantVolume&& other) = default;
    AirTerminalDualDuctConstantVolume& operator=(const AirTerminalDualDuctConstantVolume&) = default;
    AirTerminalDualDuctConstantVolume& operator=(AirTerminalDualDuctConstantVolume&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    bool isMaximumAirFlowRateAutosized() const;
    void autosizeMaximumAirFlowRate();
    boost::optional<Node> hotAirInletNode() const;
    boost::optional<Node> coldAirInletNode() const;
    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirTerminalDualDuctConstantVolume_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalDualDuctConstantVolume(std::shared_ptr<detail::AirTerminalDualDuctConstantVolume_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
