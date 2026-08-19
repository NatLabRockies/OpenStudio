/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERTOWATERCOMPONENT_HPP
#define EPMODEL_WATERTOWATERCOMPONENT_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent/HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class PlantLoop;

  namespace detail {
    class WaterToWaterComponent_Impl;
  }

  /** \brief Base class for equipment connected to two or more plant-side flow paths.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. This class represents the shared topology
   * surface of concrete water-to-water equipment, whose primary objects are
   * described by the derived classes.
   *
   * \par Important behavior
   * The supply and demand sides correspond to the primary and secondary plant
   * loops. The optional tertiary side supports equipment such as heat-recovery
   * chillers.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::WaterToWaterComponent</code>.
   *
   * - <b>Not yet available:</b> <code>clone(...)</code> from the Model base
   *   API. The inherited EPModel <code>addToNode(...)</code> and
   *   <code>remove()</code> methods provide the corresponding topology
   *   operations.
   * - <b>Added:</b> Typed <code>tertiaryInletPort()</code> and
   *   <code>tertiaryOutletPort()</code> accessors.
   *
   * \par Known limitations
   * Loop and port operations are interpreted from EnergyPlus plant topology;
   * this base does not provide a separate OpenStudio connection graph.
   */
  class EPMODEL_API WaterToWaterComponent : public HVACComponent
  {
   public:
    virtual ~WaterToWaterComponent() override = default;
    WaterToWaterComponent(const WaterToWaterComponent& other) = default;
    WaterToWaterComponent(WaterToWaterComponent&& other) = default;
    WaterToWaterComponent& operator=(const WaterToWaterComponent&) = default;
    WaterToWaterComponent& operator=(WaterToWaterComponent&&) = default;

    unsigned supplyInletPort() const;
    unsigned supplyOutletPort() const;

    boost::optional<ModelObject> supplyInletModelObject() const;
    boost::optional<ModelObject> supplyOutletModelObject() const;

    unsigned demandInletPort() const;
    unsigned demandOutletPort() const;

    boost::optional<ModelObject> demandInletModelObject() const;
    boost::optional<ModelObject> demandOutletModelObject() const;

    // For water-to-water equipment, plantLoop refers to the supply-side loop and
    // secondaryPlantLoop refers to the demand-side loop, following the model API.
    boost::optional<PlantLoop> plantLoop() const;
    boost::optional<PlantLoop> secondaryPlantLoop() const;
    bool removeFromPlantLoop();
    bool removeFromSecondaryPlantLoop();

    unsigned tertiaryInletPort() const;
    unsigned tertiaryOutletPort() const;

    boost::optional<ModelObject> tertiaryInletModelObject() const;
    boost::optional<ModelObject> tertiaryOutletModelObject() const;

    boost::optional<PlantLoop> tertiaryPlantLoop() const;
    bool removeFromTertiaryPlantLoop();
    bool addToTertiaryNode(Node& node);

   protected:
    using ImplType = detail::WaterToWaterComponent_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterToWaterComponent(std::shared_ptr<detail::WaterToWaterComponent_Impl> impl);
    WaterToWaterComponent(IddObjectType type, const Model& model);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
