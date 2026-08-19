/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERTOAIRCOMPONENT_HPP
#define EPMODEL_WATERTOAIRCOMPONENT_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent/HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Splitter;
  class AirLoopHVAC;
  class PlantLoop;

  namespace detail {
    class WaterToAirComponent_Impl;
  }

  // Water coils interact with two separate streams: an air side and a water side.
  // This base class makes that contract explicit so concrete coils can expose the
  // same side-specific navigation surface as model::WaterToAirComponent without
  // each wrapper reimplementing the same plumbing.
  /** \brief Base class for components with separate air-side and water-side connections.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. It supplies shared navigation
   * and topology operations for concrete water-to-air component objects such as
   * \epobject{group-heating-and-cooling-coils.html#coilcoolingwater,Coil:Cooling:Water} and
   * \epobject{group-heating-and-cooling-coils.html#coilheatingwater,Coil:Heating:Water}.
   *
   * \par Important behavior
   * The side-specific ports and loop queries are resolved from EnergyPlus node,
   * branch, and loop topology. Supported add, disconnect, and remove operations
   * update that persisted topology rather than an OpenStudio connection graph.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::WaterToAirComponent</code>.
   *
   * - <b>Not yet available:</b> <code>clone(Model)</code>.
   *
   * \par Known limitations
   * Topology operations require the component to be in a supported EnergyPlus
   * air and plant arrangement; they do not create a general-purpose connection
   * graph.
   */
  class EPMODEL_API WaterToAirComponent : public HVACComponent
  {
   public:
    virtual ~WaterToAirComponent() override = default;
    WaterToAirComponent(const WaterToAirComponent& other) = default;
    WaterToAirComponent(WaterToAirComponent&& other) = default;
    WaterToAirComponent& operator=(const WaterToAirComponent&) = default;
    WaterToAirComponent& operator=(WaterToAirComponent&&) = default;

    unsigned airInletPort() const;
    unsigned airOutletPort() const;

    boost::optional<ModelObject> airInletModelObject() const;
    boost::optional<ModelObject> airOutletModelObject() const;

    unsigned waterInletPort() const;
    unsigned waterOutletPort() const;

    boost::optional<ModelObject> waterInletModelObject() const;
    boost::optional<ModelObject> waterOutletModelObject() const;

    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    boost::optional<PlantLoop> plantLoop() const;

    bool addToNode(Node& node);
    bool addToSplitter(Splitter& splitter);

    std::vector<IdfObject> remove();

    void disconnectWaterSide();
    void disconnectAirSide();

    bool removeFromAirLoopHVAC();
    bool removeFromPlantLoop();

   protected:
    using ImplType = detail::WaterToAirComponent_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterToAirComponent(std::shared_ptr<detail::WaterToAirComponent_Impl> impl);
    WaterToAirComponent(IddObjectType type, const Model& model);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
