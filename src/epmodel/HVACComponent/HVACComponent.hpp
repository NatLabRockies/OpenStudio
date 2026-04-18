/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACCOMPONENT_HPP
#define EPMODEL_HVACCOMPONENT_HPP

#include "ParentObject/ParentObject.hpp"

#include "../utilities/idf/IdfObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <vector>

namespace openstudio {

class AppGFuelType;
class ComponentType;
class FuelType;

namespace epmodel {

  class AirLoopHVAC;
  class Loop;
  class Model;
  class Node;
  class PlantLoop;
  class Splitter;
  class StraightComponent;
  class ZoneHVACComponent;

  namespace detail {
    class HVACComponent_Impl;
  }

  class EPMODEL_API HVACComponent : public ParentObject
  {
   public:
    virtual ~HVACComponent() override = default;
    HVACComponent(const HVACComponent& other) = default;
    HVACComponent(HVACComponent&& other) = default;
    HVACComponent& operator=(const HVACComponent&) = default;
    HVACComponent& operator=(HVACComponent&&) = default;

    // Schema Alignment Notes:
    // - Status: Partial Parity. Core loop-membership, containment, connection-mutation, removability, and component/fuel-type helper APIs are present,
    //   but the canonical HVACComponent surface is still narrower in epmodel.
    // - Canonical Counterpart: openstudio::model::HVACComponent.
    // - Implemented Parity: `loop`, `airLoopHVAC`, `plantLoop`, `containingHVACComponent`, `containingZoneHVACComponent`, `addToNode`, `addToSplitter`,
    //   `disconnect`, `isRemovable`, `remove`, and the component/fuel-type helper accessors preserve the canonical model-facing topology contract.
    // - Documented Delta: Public parity still stops short of exposing `airLoopHVACOutdoorAirSystem`, `containingStraightComponent`,
    //   and autosizing/apply-sizing helpers because epmodel topology coverage is not broad enough to support them with canonical semantics yet.
    // - Field/Storage Mapping: Relationship queries are resolved from EnergyPlus-backed loop topology and transient epmodel connective-tissue objects rather than OpenStudio's `Connection`-based storage model.
    // - Evidence: `src/model/HVACComponent.hpp` and `src/model/HVACComponent.cpp` define the canonical surface and topology behavior that this wrapper is matching selectively.
    // - Remaining Parity Work: Add the omitted outdoor-air-system, containing-straight-component, sizing, and component/fuel-type APIs once topology and containment coverage can support canonical behavior.
    boost::optional<Loop> loop() const;
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    boost::optional<PlantLoop> plantLoop() const;
    // boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
    // Placeholder for API parity with model::HVACComponent. Not implemented yet.

    boost::optional<HVACComponent> containingHVACComponent() const;
    boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const;
    // TODO: Implement containingStraightComponent once containment tracking is ready.
    // boost::optional<StraightComponent> containingStraightComponent() const;

    bool addToNode(Node& node);
    bool addToSplitter(Splitter& splitter);
    void disconnect();
    bool isRemovable() const;
    std::vector<IdfObject> remove();
    // void autosize();
    // void applySizingValues();
    ComponentType componentType() const;
    std::vector<FuelType> coolingFuelTypes() const;
    std::vector<FuelType> heatingFuelTypes() const;
    std::vector<AppGFuelType> appGHeatingFuelTypes() const;

   protected:
    HVACComponent(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    using ImplType = detail::HVACComponent_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit HVACComponent(std::shared_ptr<detail::HVACComponent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
