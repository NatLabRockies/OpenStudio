/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTINLETSIDEMIXER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class AirTerminalSingleDuctInletSideMixer_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctInletSideMixer : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctInletSideMixer(const Model& model);

    virtual ~AirTerminalSingleDuctInletSideMixer() override = default;
    AirTerminalSingleDuctInletSideMixer(const AirTerminalSingleDuctInletSideMixer& other) = default;
    AirTerminalSingleDuctInletSideMixer(AirTerminalSingleDuctInletSideMixer&& other) = default;
    AirTerminalSingleDuctInletSideMixer& operator=(const AirTerminalSingleDuctInletSideMixer&) = default;
    AirTerminalSingleDuctInletSideMixer& operator=(AirTerminalSingleDuctInletSideMixer&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> perPersonVentilationRateModeValues();
    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The persisted mixer node/object references plus the bounded epmodel zone-branch add/remove path are aligned,
    //   but the broader canonical local-topology surface and the OS-only outdoor-air control API remain intentionally narrower.
    // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctInletSideMixer.
    // - Implemented Parity: `perPersonVentilationRateMode`, `secondaryAirInletNode`, `addToNode`, and `removeFromLoop` preserve the
    //   current epmodel AirLoopHVAC zone-branch contract for this `AirTerminal:SingleDuct:Mixer` wrapper.
    // - Topology Gate: `addToNode` only accepts a node that is already the matched ZoneSplitter/ZoneMixer branch node for an AirLoopHVAC demand branch;
    //   it rejects foreign-model, non-loop, and mismatched-branch nodes, then rewires the splitter outlet, terminal inlet/outlet, ADU outlet, and zone equipment list.
    // - Cleanup Surface: `remove` and `removeFromLoop` reverse those entity-owned branch side effects by restoring the original branch node, clearing stale ADU and zone-equipment references,
    //   and deleting the transient inlet node when this wrapper created it.
    // - Documented Delta: This wrapper keeps the same default-constructor shape as the canonical model object, but it intentionally omits the canonical
    //   `controlForOutdoorAir` API plus the associated DesignSpecificationOutdoorAir export path from the openstudio::model surface. It is explicitly
    //   unsupported as an implicit AirLoopHVAC clone-last source because its secondary inlet may be owned by downstream ZoneHVAC equipment that cannot
    //   be re-homed transactionally by the current epmodel topology API.
    // - Field/Storage Mapping: The preserved scalar and direct object links map directly to the EnergyPlus `AirTerminal:SingleDuct:Mixer` fields,
    //   while the connectivity methods update those node/object references to match the current zone-branch topology.
    // - Evidence: `src/model/AirTerminalSingleDuctInletSideMixer.hpp`, `src/model/AirTerminalSingleDuctInletSideMixer.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctInletSideMixer.cpp`, and `src/epmodel/test/AirTerminalSingleDuctInletSideMixer_GTest.cpp`.
    // - Remaining Parity Work: Broaden the local-topology surface only if canonical insertion behavior needs to be mirrored more fully.

    /** @name Per Person Ventilation Rate Mode */
    //@{
    std::string perPersonVentilationRateMode() const;
    bool setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode);
    //@}

    /** @name Secondary Air */
    //@{
    unsigned secondaryAirInletPort() const;
    boost::optional<Node> secondaryAirInletNode() const;
    //@}

   protected:
    using ImplType = detail::AirTerminalSingleDuctInletSideMixer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctInletSideMixer(std::shared_ptr<detail::AirTerminalSingleDuctInletSideMixer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
