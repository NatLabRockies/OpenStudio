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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The base air/water topology plumbing is present, but canonical convenience and cloning behavior are not fully mirrored.
    // - Canonical Counterpart: openstudio::model::WaterToAirComponent.
    // - Implemented Parity: `airInletPort`, `airOutletPort`, `airInletModelObject`, `airOutletModelObject`, `waterInletPort`, `waterOutletPort`, `waterInletModelObject`, `waterOutletModelObject`, `airLoopHVAC`, `plantLoop`, `addToNode`, `addToSplitter`, `remove`, `disconnectWaterSide`, `disconnectAirSide`, `removeFromAirLoopHVAC`, and `removeFromPlantLoop` preserve the canonical cross-stream topology contract.
    // - Documented Delta: `clone(Model)` is not exposed in epmodel, and the wrapper stays thinner than canonical model because it does not reintroduce model-side convenience around derived object creation.
    // - Field/Storage Mapping: Air and water side links are resolved through EnergyPlus-backed node/topology ownership rather than model-side connection storage.
    // - Evidence: `src/model/WaterToAirComponent.hpp` and `src/model/WaterToAirComponent.cpp` define the canonical base behavior; `src/model/test/CoilCoolingWater_GTest.cpp`, `src/model/test/CoilHeatingWater_GTest.cpp`, and `src/epmodel/test/IDF_5ZoneAirCooled_GTest.cpp` exercise the associated topology semantics.
    // - Remaining Parity Work: Add the missing clone and any remaining canonical convenience behaviors once the derived wrapper families are fully normalized.

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
