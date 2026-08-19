/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAV_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAV_HPP

#include "EPModelAPI.hpp"
#include "Mixer/Mixer.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class DesignSpecificationOutdoorAir;

  namespace detail {
    class AirTerminalDualDuctVAV_Impl;
  }

  /** \brief Represents a variable-air-volume dual-duct air terminal.
   *
   * \par EnergyPlus object
   * \epobject{group-air-distribution-equipment.html#airterminaldualductvav,AirTerminal:DualDuct:VAV}.
   *
   * \par Important behavior
   * Separate terminal inlet and outlet node relationships follow the supported dual-duct air-loop insertion and removal topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirTerminalDualDuctVAV</code>.
   * <b>Not yet available: the SQL-backed <code>autosizedMaximumDamperAirFlowRate()</code> result helper.</b>
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API AirTerminalDualDuctVAV : public Mixer
  {
   public:
    explicit AirTerminalDualDuctVAV(const Model& model);

    virtual ~AirTerminalDualDuctVAV() override = default;
    AirTerminalDualDuctVAV(const AirTerminalDualDuctVAV& other) = default;
    AirTerminalDualDuctVAV(AirTerminalDualDuctVAV&& other) = default;
    AirTerminalDualDuctVAV& operator=(const AirTerminalDualDuctVAV&) = default;
    AirTerminalDualDuctVAV& operator=(AirTerminalDualDuctVAV&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<DesignSpecificationOutdoorAir> designSpecificationOutdoorAirObject() const;
    bool setDesignSpecificationOutdoorAirObject(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);
    void resetDesignSpecificationOutdoorAirObject();

    boost::optional<Schedule> minimumAirFlowTurndownSchedule() const;
    bool setMinimumAirFlowTurndownSchedule(Schedule& schedule);
    void resetMinimumAirFlowTurndownSchedule();

    boost::optional<double> maximumDamperAirFlowRate() const;
    bool isMaximumDamperAirFlowRateAutosized() const;
    bool setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate);
    void autosizeMaximumDamperAirFlowRate();

    double zoneMinimumAirFlowFraction() const;
    bool setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction);
    boost::optional<Node> hotAirInletNode() const;
    boost::optional<Node> coldAirInletNode() const;
    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirTerminalDualDuctVAV_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalDualDuctVAV(std::shared_ptr<detail::AirTerminalDualDuctVAV_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
