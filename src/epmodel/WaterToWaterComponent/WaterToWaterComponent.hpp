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

// Water-to-water equipment can participate in more than one plant-side flow
// path. The common case is a load side and a source or condenser side. This
// base class makes those two sides explicit so concrete equipment can expose
// meaningful topology navigation without each wrapper reimplementing the same
// port and loop plumbing.
class EPMODEL_API WaterToWaterComponent : public HVACComponent
{
 public:
  virtual ~WaterToWaterComponent() override = default;
  WaterToWaterComponent(const WaterToWaterComponent& other) = default;
  WaterToWaterComponent(WaterToWaterComponent&& other) = default;
  WaterToWaterComponent& operator=(const WaterToWaterComponent&) = default;
  WaterToWaterComponent& operator=(WaterToWaterComponent&&) = default;

  // Schema Alignment Notes:
  // - Status: Partial Parity. The shared two- and three-loop topology surface is present, but the canonical convenience API on the model side is broader than the base epmodel wrapper.
  // - Canonical Counterpart: openstudio::model::WaterToWaterComponent.
  // - Implemented Parity: Supply/demand/tertiary port accessors, loop accessors, removal helpers, and tertiary-node attachment preserve the canonical topology contract for water-to-water equipment.
  // - Documented Delta: The epmodel base stays focused on topology plumbing; derived types own most scalar and equipment-specific parity notes.
  // - Field/Storage Mapping: Public loop accessors resolve against EnergyPlus-backed plant topology rather than a persisted OpenStudio-side connection graph.
  // - Evidence: `src/model/WaterToWaterComponent.hpp` and `src/model/WaterToWaterComponent.cpp` define the canonical shared behavior and topology expectations.
  // - Remaining Parity Work: Expand only if new shared water-to-water convenience behavior becomes necessary across multiple derived wrappers.
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
