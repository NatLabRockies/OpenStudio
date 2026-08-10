/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACCOMPONENT_IMPL_HPP
#define EPMODEL_HVACCOMPONENT_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"
#include "../utilities/idf/IdfObject.hpp"

#include <vector>

namespace openstudio {

class AppGFuelType;
class ComponentType;
class FuelType;

namespace epmodel {
  class Node;
  class AirLoopHVAC;
  class AirLoopHVACOutdoorAirSystem;
  class HVACComponent;
  class Loop;
  class PlantLoop;
  class Splitter;
  class ZoneHVACComponent;
  namespace detail {

    class EPMODEL_API HVACComponent_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~HVACComponent_Impl() override = default;

      virtual boost::optional<Loop> loop() const;
      virtual boost::optional<AirLoopHVAC> airLoopHVAC() const;
      virtual boost::optional<PlantLoop> plantLoop() const;
      virtual boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;
      virtual boost::optional<HVACComponent> containingHVACComponent() const;
      virtual boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const;

      virtual bool addToNode(Node& node);
      virtual bool addToSplitter(Splitter& splitter);
      virtual void disconnect();
      virtual bool isRemovable() const;
      virtual std::vector<IdfObject> remove() override;
      virtual openstudio::ComponentType componentType() const;
      virtual std::vector<openstudio::FuelType> coolingFuelTypes() const;
      virtual std::vector<openstudio::FuelType> heatingFuelTypes() const;
      virtual std::vector<openstudio::AppGFuelType> appGHeatingFuelTypes() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
