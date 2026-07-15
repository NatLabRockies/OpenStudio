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
    // - Status: Partial Parity. epmodel preserves the scalar surface plus tested dual-duct node connectivity, but it does not expose the canonical availability-schedule convenience accessors.
    // - Canonical Counterpart: openstudio::model::AirTerminalDualDuctConstantVolume.
    // - Implemented Parity: `maximumAirFlowRate`, autosize support, constructor defaults, `hotAirInletNode`, `coldAirInletNode`, and the tested dual-duct `addToNode`/`remove` connectivity path are implemented here.
    // - Documented Delta: epmodel does not expose canonical `availabilitySchedule()` / `setAvailabilitySchedule()` wrappers even though the underlying schedule relationship is still stored.
    // - Field/Storage Mapping: `AvailabilityScheduleName` remains an underlying IDD relationship field used by the constructor and translator; Air Outlet/Hot Air Inlet/Cold Air Inlet node fields are surfaced through the preserved node accessors and shared AirLoopHVAC topology helpers.
    // - Evidence: `src/model/AirTerminalDualDuctConstantVolume.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalDualDuctConstantVolume.cpp`, and `src/epmodel/test/AirTerminalDualDuctConstantVolume_GTest.cpp` cover the same scalar mapping plus supported connectivity.
    // - Remaining Parity Work: Reintroduce the availability-schedule wrappers if full model-side API parity is needed.
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
