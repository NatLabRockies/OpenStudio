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
