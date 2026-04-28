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
    // - Status: Scalar Parity. The scalar surface is aligned, but the canonical wrapper still exposes schedule, node, and DSOA-control convenience APIs that epmodel has not reintroduced.
    // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctVAVOutdoorAir.
    // - Implemented Parity: `maximumTerminalAirFlowRate` and `perPersonVentilationRateMode` preserve the canonical scalar behavior and autosize semantics.
    // - Documented Delta: epmodel still omits the availability-schedule, node, DSOA, and `controlForOutdoorAir` wrappers that canonical model code exposes.
    // - Field/Storage Mapping: Availability Schedule Name, Air Outlet Node Name, Outdoor Air Inlet Node Name, Recirculated Air Inlet Node Name, and Design Specification Outdoor Air Object Name are relationship fields and intentionally excluded from scalar accessors.
    // - Evidence: `src/model/AirTerminalDualDuctVAVOutdoorAir.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctVAVOutdoorAir.cpp`, and `src/epmodel/test/AirTerminalDualDuctVAVOutdoorAir_GTest.cpp` show the same scalar mapping and omitted relationship surface.
    // - Remaining Parity Work: Reintroduce the schedule, DSOA, outdoor-air control, and node-relationship wrappers if full model-side parity is needed.
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
