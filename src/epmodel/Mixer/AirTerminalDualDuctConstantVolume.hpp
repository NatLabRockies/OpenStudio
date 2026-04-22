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

  namespace detail {
    class AirTerminalDualDuctConstantVolume_Impl;
  }

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

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The scalar surface is aligned, but the canonical wrapper still exposes schedule and node-relationship convenience APIs that epmodel has not reintroduced.
    // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctConstantVolume.
    // - Implemented Parity: `maximumAirFlowRate`, autosize support, and the core scalar value semantics match the canonical dual-duct constant-volume terminal.
    // - Documented Delta: epmodel still omits the availability-schedule and hot/cold inlet convenience accessors that canonical model code exposes.
    // - Field/Storage Mapping: Availability Schedule Name, Air Outlet Node Name, Hot Air Inlet Node Name, and Cold Air Inlet Node Name are relationship fields and are intentionally excluded from scalar accessors.
    // - Evidence: `src/model/AirTerminalDualDuctConstantVolume.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctConstantVolume.cpp`, and `src/epmodel/test/AirTerminalDualDuctConstantVolume_GTest.cpp` show the same scalar mapping and missing relationship surface.
    // - Remaining Parity Work: Reintroduce the availability-schedule and node-relationship wrappers if epmodel needs full model-side parity here.
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
