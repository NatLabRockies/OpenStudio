/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACCOMPONENT_HPP
#define EPMODEL_HVACCOMPONENT_HPP

#include "ParentObject.hpp"

#include "../utilities/idf/IdfObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class Loop;
  class Model;
  class Node;
  class Splitter;
  class StraightComponent;

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

    boost::optional<Loop> loop() const;
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    // boost::optional<PlantLoop> plantLoop() const;
    // Placeholder for API parity with model::HVACComponent. Not implemented yet.
    // boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
    // Placeholder for API parity with model::HVACComponent. Not implemented yet.

    boost::optional<HVACComponent> containingHVACComponent() const;
    // boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const;
    // Placeholder for API parity with model::HVACComponent. Not implemented yet.
    // TODO: Implement containingStraightComponent once containment tracking is ready.
    // boost::optional<StraightComponent> containingStraightComponent() const;

    bool addToNode(Node& node);
    // TODO: Provide implementations for these HVACComponent APIs.
    // bool addToSplitter(Splitter& splitter);
    // void disconnect();
    // bool isRemovable() const;
    // std::vector<IdfObject> remove();
    // void autosize();
    // void applySizingValues();
    // ComponentType componentType() const;
    // std::vector<FuelType> coolingFuelTypes() const;
    // std::vector<FuelType> heatingFuelTypes() const;
    // std::vector<AppGFuelType> appGHeatingFuelTypes() const;

   protected:
    HVACComponent(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    explicit HVACComponent(std::shared_ptr<detail::HVACComponent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
