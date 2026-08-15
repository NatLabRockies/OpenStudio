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

    // Schema Alignment Notes:
    // - Status: Near Parity for directly stored EnergyPlus relationships, scalars, and tested dual-duct topology.
    // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctVAV.
    // - Implemented Connectivity Surface: availability, DSOA, and minimum-air-flow-turndown relationships; constructor defaults; `hotAirInletNode`; `coldAirInletNode`; and shared `addToNode`/`remove` topology are implemented here.
    // - Documented Delta: SQL-backed autosized-value convenience remains outside this direct-IDF wrapper.
    // - Field/Storage Mapping: `AvailabilityScheduleName`, `DesignSpecificationOutdoorAirObjectName`, and `MinimumAirFlowTurndownScheduleName` remain underlying relationship fields; Air Outlet/Hot Air Inlet/Cold Air Inlet node fields are surfaced through node accessors and shared AirLoopHVAC topology helpers.
    // - Evidence: `src/model/AirTerminalDualDuctVAV.cpp` and `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAV.cpp` document the canonical field mapping; `src/model/test/AirTerminalDualDuctVAV_GTest.cpp` and `src/epmodel/test/AirTerminalDualDuctVAV_GTest.cpp` cover the tested insertion, removal, reuse, and cleanup behavior.
    // - Remaining Parity Work: Add SQL-backed autosized-result convenience only when an epmodel sizing-results workflow needs it.
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
