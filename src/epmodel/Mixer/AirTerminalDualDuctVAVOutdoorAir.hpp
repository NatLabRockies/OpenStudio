/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_HPP
#define EPMODEL_AIRTERMINALDUALDUCTVAVOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "Mixer/Mixer.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;

  namespace detail {
    class AirTerminalDualDuctVAVOutdoorAir_Impl;
  }

  class EPMODEL_API AirTerminalDualDuctVAVOutdoorAir : public Mixer
  {
   public:
    explicit AirTerminalDualDuctVAVOutdoorAir(const Model& model);

    virtual ~AirTerminalDualDuctVAVOutdoorAir() override = default;
    AirTerminalDualDuctVAVOutdoorAir(const AirTerminalDualDuctVAVOutdoorAir& other) = default;
    AirTerminalDualDuctVAVOutdoorAir(AirTerminalDualDuctVAVOutdoorAir&& other) = default;
    AirTerminalDualDuctVAVOutdoorAir& operator=(const AirTerminalDualDuctVAVOutdoorAir&) = default;
    AirTerminalDualDuctVAVOutdoorAir& operator=(AirTerminalDualDuctVAVOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> perPersonVentilationRateModeValues();

    // Schema Alignment Notes:
    // - Status: Near Parity for directly stored EnergyPlus fields and tested dual-duct topology.
    // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctVAVOutdoorAir.
    // - Implemented Connectivity Surface: availability-schedule access, constructor defaults, `outdoorAirInletNode`, `recirculatedAirInletNode`, and the shared `addToNode`/`remove` topology behavior are implemented here.
    // - Documented Delta: epmodel does not mirror the OpenStudio-side `controlForOutdoorAir` flag that derives a zone DSOA during forward translation, and SQL-backed autosized-result convenience remains outside this direct-IDF wrapper.
    // - Field/Storage Mapping: `AvailabilityScheduleName` remains an underlying relationship field; Air Outlet/Outdoor Air Inlet/Recirculated Air Inlet node fields are surfaced through node accessors and
    //   shared AirLoopHVAC topology helpers; `DesignSpecificationOutdoorAirObjectName` remains the direct EnergyPlus-facing field and is not wrapped by this epmodel API.
    // - Evidence: `src/model/AirTerminalDualDuctVAVOutdoorAir.cpp`, `src/model/test/AirTerminalDualDuctVAVOutdoorAir_GTest.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAVOutdoorAir.cpp` document the canonical outdoor-air-control and DSOA mapping; `src/epmodel/test/AirTerminalDualDuctVAVOutdoorAir_GTest.cpp`
    //   covers the supported epmodel constructor storage plus insertion, removal, reuse, and cleanup behavior.
    // - Remaining Parity Work: Define an EnergyPlus-backed equivalent before exposing `controlForOutdoorAir`; add SQL-backed autosized-result convenience only when a sizing-results workflow needs it.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumTerminalAirFlowRate() const;
    bool setMaximumTerminalAirFlowRate(double maximumTerminalAirFlowRate);
    void autosizeMaximumTerminalAirFlowRate();
    bool isMaximumTerminalAirFlowRateAutosized() const;

    std::string perPersonVentilationRateMode() const;
    bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
    boost::optional<Node> outdoorAirInletNode() const;
    boost::optional<Node> recirculatedAirInletNode() const;
    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirTerminalDualDuctVAVOutdoorAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalDualDuctVAVOutdoorAir(std::shared_ptr<detail::AirTerminalDualDuctVAVOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
