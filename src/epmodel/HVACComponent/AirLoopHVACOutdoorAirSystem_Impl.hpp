/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEM_IMPL_HPP
#define EPMODEL_AIRLOOPHVACOUTDOORAIRSYSTEM_IMPL_HPP

#include "HVACComponent_Impl.hpp"

#include <utility>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class Node;
  class OutdoorAirMixer;
  class AirLoopHVACOutdoorAirSystemEquipmentList;
  class AirLoopHVACControllerList;
  class ControllerOutdoorAir;

  namespace detail {

    class EPMODEL_API AirLoopHVACOutdoorAirSystem_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~AirLoopHVACOutdoorAirSystem_Impl() override = default;

      // Schema Alignment Notes:
      // - API: Keep openstudio::model AirLoopHVACOutdoorAirSystem method names and signatures stable.
      // - Field Mapping: Outdoor/relief/return/mixed node-port lookups delegate to the owned OutdoorAir:Mixer object.
      // - Field Mapping: `outboardOANode()` is the canonical source for ForwardTranslator `OutdoorAir:NodeList` emission.

      unsigned returnAirPort() const;
      unsigned outdoorAirPort() const;
      unsigned reliefAirPort() const;
      unsigned mixedAirPort() const;
      openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList airLoopHVACOutdoorAirSystemEquipmentList() const;
      openstudio::epmodel::OutdoorAirMixer outdoorAirMixer() const;

      boost::optional<openstudio::epmodel::ModelObject> returnAirModelObject() const;
      boost::optional<openstudio::epmodel::ModelObject> outdoorAirModelObject() const;
      boost::optional<openstudio::epmodel::ModelObject> reliefAirModelObject() const;
      boost::optional<openstudio::epmodel::ModelObject> mixedAirModelObject() const;

      std::vector<openstudio::epmodel::ModelObject> oaComponents(openstudio::IddObjectType type) const;
      std::vector<openstudio::epmodel::ModelObject> reliefComponents(openstudio::IddObjectType type) const;
      std::vector<openstudio::epmodel::ModelObject> components(openstudio::IddObjectType type) const;

      boost::optional<openstudio::epmodel::ModelObject> component(openstudio::Handle handle) const;
      boost::optional<openstudio::epmodel::ModelObject> oaComponent(openstudio::Handle handle) const;
      boost::optional<openstudio::epmodel::ModelObject> reliefComponent(openstudio::Handle handle) const;
      openstudio::epmodel::ControllerOutdoorAir getControllerOutdoorAir() const;
      bool setControllerOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir);

      boost::optional<openstudio::epmodel::Node> outboardOANode() const;
      boost::optional<openstudio::epmodel::Node> outboardReliefNode() const;

      void doCanonicalize(LoadContext& context) override;
      bool addToNode(Node& node);
      bool setOutdoorAirStreamNode(const Node& node);
      bool setReliefAirStreamNode(const Node& node);
      bool updateOutdoorAirStreamInletNode(const ModelObject& object, const Node& node);
      bool updateOutdoorAirStreamOutletNode(const ModelObject& object, const Node& node);
      bool updateReliefAirStreamInletNode(const ModelObject& object, const Node& node);
      bool updateReliefAirStreamOutletNode(const ModelObject& object, const Node& node);
      bool rewriteEquipmentListOrder();
      bool rewriteEquipmentListOrder(LoadContext& context);

     private:
      // These remaining helpers are the core OA topology extractors and mutators reused across
      // navigation, canonicalization, and stream mutation. The smaller plumbing that used to sit
      // around them has been pushed back into the owning methods so the implementation reads more
      // directly from the public behavior.
      enum class OAStream
      {
        OutdoorAir,
        ReliefAir,
      };

      openstudio::epmodel::AirLoopHVACControllerList airLoopHVACControllerList() const;
      boost::optional<std::pair<Node, Node>> streamNodesFor(const ModelObject& object, OAStream stream) const;
      std::vector<openstudio::epmodel::ModelObject> walkOutdoorAirStream() const;
      std::vector<openstudio::epmodel::ModelObject> walkReliefAirStream() const;
      bool rewriteEquipmentListOrder(LoadContext* context);
      static bool updateAdjacentStreamNode(const ModelObject& object, OAStream stream, bool updateInlet, const Node& node);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
