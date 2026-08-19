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
  class AirLoopHVACDedicatedOutdoorAirSystem;

  namespace detail {
    class AirLoopHVACOutdoorAirSystem_Impl;
  }

  /** \brief Represents an outdoor-air system attached to an air loop.
   *
   * \par EnergyPlus object
   * \epobject{group-air-distribution.html#airloophvacoutdoorairsystem,AirLoopHVAC:OutdoorAirSystem}, with its
   * \epobject{group-controllers.html#controlleroutdoorair,Controller:OutdoorAir}, outdoor-air node list, and outdoor-air
   * equipment list companions.
   *
   * \par Important behavior
   * On a dual-duct air loop, <code>addToNode</code> accepts the common main supply
   * branch; the outdoor-air relationship is not moved onto an individual deck.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AirLoopHVACOutdoorAirSystem</code>.
   * <b>Not yet available:</b> <code>airLoop()</code> and the
   * <code>airflowNetworkDistributionNode()</code> and
   * <code>getAirflowNetworkDistributionNode()</code> convenience methods.
   * <b>Changed:</b> the dual-duct insertion rule is limited to the common branch
   * described above.
   *
   * \par Known limitations
   * Controller and outdoor-air equipment relationships are exposed through the
   * supported node and component APIs; unsupported air-loop shapes are rejected
   * rather than assigned ambiguous ownership.
   */
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
    boost::optional<AirLoopHVACDedicatedOutdoorAirSystem> airLoopHVACDedicatedOutdoorAirSystem() const;

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirLoopHVACOutdoorAirSystem_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit AirLoopHVACOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACOutdoorAirSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
