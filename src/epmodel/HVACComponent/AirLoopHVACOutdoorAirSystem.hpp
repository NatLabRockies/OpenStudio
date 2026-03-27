/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Node;
  class ControllerOutdoorAir;

  namespace detail {
    class AirLoopHVACOutdoorAirSystem_Impl;
  }

  class EPMODEL_API AirLoopHVACOutdoorAirSystem : public HVACComponent
  {
   public:
    explicit AirLoopHVACOutdoorAirSystem(const Model& model);

    virtual ~AirLoopHVACOutdoorAirSystem() override = default;
    AirLoopHVACOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& other) = default;
    AirLoopHVACOutdoorAirSystem(AirLoopHVACOutdoorAirSystem&& other) = default;
    AirLoopHVACOutdoorAirSystem& operator=(const AirLoopHVACOutdoorAirSystem&) = default;
    AirLoopHVACOutdoorAirSystem& operator=(AirLoopHVACOutdoorAirSystem&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The outdoor-air-system topology surface is present, but the canonical wrapper still exposes additional convenience and distribution-node behavior.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACOutdoorAirSystem.
    // - Implemented Parity: Return/outdoor/relief/mixed air ports, node accessors, component traversal, controller wiring, and `addToNode` preserve the main canonical OA-system topology behavior.
    // - Documented Delta: epmodel still omits the canonical airloop convenience helpers and the AirflowNetwork distribution-node surface that model code exposes on this class.
    // - Field/Storage Mapping: Controller List Name and Outdoor Air Equipment List Name map to companion objects and are intentionally exposed via relationship APIs, not scalar string accessors.
    // - Evidence: `src/model/AirLoopHVACOutdoorAirSystem.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACOutdoorAirSystem.cpp`, and `src/epmodel/test/AirLoopHVACOutdoorAirSystem_GTest.cpp` show the canonical API shape and the node-level topology path.
    // - Remaining Parity Work: Add the remaining airloop convenience and distribution-node APIs once the epmodel topology layer exposes them consistently.
    // Mirroring openstudio::model API shape.
    unsigned returnAirPort() const;
    boost::optional<ModelObject> returnAirModelObject() const;

    unsigned outdoorAirPort() const;
    boost::optional<ModelObject> outdoorAirModelObject() const;

    unsigned reliefAirPort() const;
    boost::optional<ModelObject> reliefAirModelObject() const;

    unsigned mixedAirPort() const;
    boost::optional<ModelObject> mixedAirModelObject() const;

    std::vector<ModelObject> oaComponents(openstudio::IddObjectType type = openstudio::IddObjectType("Catchall")) const;
    std::vector<ModelObject> reliefComponents(openstudio::IddObjectType type = openstudio::IddObjectType("Catchall")) const;
    std::vector<ModelObject> components(openstudio::IddObjectType type = openstudio::IddObjectType("Catchall")) const;

    boost::optional<ModelObject> component(openstudio::Handle handle) const;
    boost::optional<ModelObject> oaComponent(openstudio::Handle handle) const;
    boost::optional<ModelObject> reliefComponent(openstudio::Handle handle) const;

    ControllerOutdoorAir getControllerOutdoorAir() const;
    bool setControllerOutdoorAir(const ControllerOutdoorAir& controllerOutdoorAir);

    boost::optional<Node> outboardOANode() const;
    boost::optional<Node> outboardReliefNode() const;

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirLoopHVACOutdoorAirSystem_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class openstudio::epmodel::Model;

    explicit AirLoopHVACOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACOutdoorAirSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
