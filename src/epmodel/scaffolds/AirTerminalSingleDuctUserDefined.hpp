/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class AirTerminalSingleDuctUserDefined_Impl;
  }

  class EPMODEL_API AirTerminalSingleDuctUserDefined : public StraightComponent
  {
   public:
    explicit AirTerminalSingleDuctUserDefined(const Model& model);

    virtual ~AirTerminalSingleDuctUserDefined() override = default;
    AirTerminalSingleDuctUserDefined(const AirTerminalSingleDuctUserDefined& other) = default;
    AirTerminalSingleDuctUserDefined(AirTerminalSingleDuctUserDefined&& other) = default;
    AirTerminalSingleDuctUserDefined& operator=(const AirTerminalSingleDuctUserDefined&) = default;
    AirTerminalSingleDuctUserDefined& operator=(AirTerminalSingleDuctUserDefined&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Connectivity-focused parity for the current epmodel single-duct zone-branch topology.
    // - Canonical Counterpart: No direct openstudio::model wrapper exists; this entity follows the tested epmodel
    //   single-duct straight-component terminal contract used by nearby air terminals.
    // - Implemented Parity: `addToNode` and the inherited removal path (`remove`/`removeFromLoop`) preserve
    //   primary-air node wiring, AirLoopHVAC demand continuity, ZoneHVAC equipment registration cleanup,
    //   conditional transient inlet-node cleanup, and ADU outlet/terminal cleanup for the supported zone-branch
    //   insertion paths, with best-effort rollback of observed intermediate `addToNode` mutations on the tested
    //   failure path.
    // - Documented Delta: Public parity here stays intentionally narrow. It is explicitly unsupported as an implicit
    //   AirLoopHVAC clone-last source because no canonical model wrapper defines ownership and reconnection semantics
    //   for its optional plant, program, tank, and secondary-air relationships. Secondary-air nodes, plant-connection
    //   node relationships, program-calling-manager relationships, tank relationships, and ambient-zone
    //   convenience are not exposed yet beyond the stored scalar count.
    // - Field Mapping: `numberofPlantLoopConnections` maps directly to E+ AirTerminal:SingleDuct:UserDefined
    //   Number of Plant Loop Connections. Primary air inlet/outlet node fields participate in the shared
    //   straight-component topology contract.
    /** @name Number of Plant Loop Connections */
    //@{
    int numberofPlantLoopConnections() const;
    bool setNumberofPlantLoopConnections(int numberofPlantLoopConnections);
    //@}

   protected:
    using ImplType = detail::AirTerminalSingleDuctUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirTerminalSingleDuctUserDefined(std::shared_ptr<detail::AirTerminalSingleDuctUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
