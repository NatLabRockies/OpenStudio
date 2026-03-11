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
  // - API: Preserve openstudio::model API names/signatures and existing non-scalar behavior for this model-counterpart class.
  // - API: This class intentionally fronts `AirLoopHVAC:OutdoorAirSystem` while delegating node-port semantics to its contained `OutdoorAir:Mixer`.
  // - Field Mapping: Controller List Name and Outdoor Air Equipment List Name map to companion objects and are intentionally exposed via relationship APIs.
  // - Field Mapping: `outboardOANode()` provides the OA node used by ForwardTranslator when emitting `OutdoorAir:NodeList`.
  // - Field Mapping: This E+ object has no class-specific simple scalar fields beyond Name; scalar saturation therefore relies on generic name accessors.
  // - ForwardTranslator evidence: ForwardTranslateAirLoopHVACOutdoorAirSystem.cpp writes OutdoorAir:Mixer node fields from this API shape.
  // - TODO(parity): Keep adding non-scalar parity behaviors incrementally without breaking existing API signatures.
  // Mirroring openstudio::model API shape.
  unsigned returnAirPort() const;
  unsigned outdoorAirPort() const;
  unsigned reliefAirPort() const;
  unsigned mixedAirPort() const;

  boost::optional<ModelObject> returnAirModelObject() const;
  boost::optional<ModelObject> outdoorAirModelObject() const;
  boost::optional<ModelObject> reliefAirModelObject() const;
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
