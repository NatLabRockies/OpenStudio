/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent.hpp"
#include "HVACComponent_Impl.hpp"
#include "Model.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Node.hpp"
#include "Splitter/Splitter.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <utilities/data/DataEnums.hpp>

#include <algorithm>
namespace openstudio {
namespace epmodel {

  HVACComponent::HVACComponent(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : ParentObject(type, model, fastName, isTransient) {}

  HVACComponent::HVACComponent(std::shared_ptr<detail::HVACComponent_Impl> impl) : ParentObject(std::move(impl)) {}

  boost::optional<Loop> HVACComponent::loop() const {
    return getImpl<detail::HVACComponent_Impl>()->loop();
  }

  boost::optional<AirLoopHVAC> HVACComponent::airLoopHVAC() const {
    return getImpl<detail::HVACComponent_Impl>()->airLoopHVAC();
  }

  boost::optional<PlantLoop> HVACComponent::plantLoop() const {
    return getImpl<detail::HVACComponent_Impl>()->plantLoop();
  }

  boost::optional<AirLoopHVACOutdoorAirSystem> HVACComponent::airLoopHVACOutdoorAirSystem() const {
    return getImpl<detail::HVACComponent_Impl>()->airLoopHVACOutdoorAirSystem();
  }

  boost::optional<HVACComponent> HVACComponent::containingHVACComponent() const {
    return getImpl<detail::HVACComponent_Impl>()->containingHVACComponent();
  }

  boost::optional<ZoneHVACComponent> HVACComponent::containingZoneHVACComponent() const {
    return getImpl<detail::HVACComponent_Impl>()->containingZoneHVACComponent();
  }

  // TODO: Implement containingStraightComponent once containment tracking is ready.
  // boost::optional<StraightComponent> HVACComponent::containingStraightComponent() const {
  //   return boost::none;
  // }

  bool HVACComponent::addToNode(Node& node) {
    return getImpl<detail::HVACComponent_Impl>()->addToNode(node);
  }

  bool HVACComponent::addToSplitter(Splitter& splitter) {
    return getImpl<detail::HVACComponent_Impl>()->addToSplitter(splitter);
  }

  void HVACComponent::disconnect() {
    getImpl<detail::HVACComponent_Impl>()->disconnect();
  }

  bool HVACComponent::isRemovable() const {
    return getImpl<detail::HVACComponent_Impl>()->isRemovable();
  }

  std::vector<IdfObject> HVACComponent::remove() {
    return getImpl<detail::HVACComponent_Impl>()->remove();
  }

  ComponentType HVACComponent::componentType() const {
    return getImpl<detail::HVACComponent_Impl>()->componentType();
  }

  std::vector<FuelType> HVACComponent::coolingFuelTypes() const {
    return getImpl<detail::HVACComponent_Impl>()->coolingFuelTypes();
  }

  std::vector<FuelType> HVACComponent::heatingFuelTypes() const {
    return getImpl<detail::HVACComponent_Impl>()->heatingFuelTypes();
  }

  std::vector<AppGFuelType> HVACComponent::appGHeatingFuelTypes() const {
    return getImpl<detail::HVACComponent_Impl>()->appGHeatingFuelTypes();
  }

  namespace detail {

    boost::optional<Loop> HVACComponent_Impl::loop() const {
      if (auto airLoop = airLoopHVAC()) {
        return airLoop->optionalCast<openstudio::epmodel::Loop>();
      }
      if (auto plantLoop_ = plantLoop()) {
        return plantLoop_->optionalCast<openstudio::epmodel::Loop>();
      }
      return boost::none;
    }

    boost::optional<AirLoopHVAC> HVACComponent_Impl::airLoopHVAC() const {
      // Resolve ownership through AirLoopHVAC traversal APIs so topology logic
      // remains centralized in supply/demand components implementations.
      const auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      const auto airLoops = model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>();
      for (const auto& airLoop : airLoops) {
        if (airLoop.component(thisObject.handle())) {
          return airLoop;
        }

        if (auto oaSystem = airLoop.airLoopHVACOutdoorAirSystem()) {
          if (oaSystem->component(thisObject.handle())) {
            return airLoop;
          }
        }
      }
      return boost::none;
    }

    boost::optional<PlantLoop> HVACComponent_Impl::plantLoop() const {
      const auto plantLoops = model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>();
      for (const auto& plantLoop : plantLoops) {
        const auto supplyComponents = plantLoop.supplyComponents(openstudio::IddObjectType::Catchall);
        if (std::ranges::find_if(supplyComponents, [&](const auto& component) { return component.handle() == handle(); }) != supplyComponents.end()) {
          return plantLoop;
        }

        const auto demandComponents = plantLoop.demandComponents(openstudio::IddObjectType::Catchall);
        if (std::ranges::find_if(demandComponents, [&](const auto& component) { return component.handle() == handle(); }) != demandComponents.end()) {
          return plantLoop;
        }
      }
      return boost::none;
    }

    boost::optional<AirLoopHVACOutdoorAirSystem> HVACComponent_Impl::airLoopHVACOutdoorAirSystem() const {
      const auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& oaSystem : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
        if (oaSystem.component(thisObject.handle())) {
          return oaSystem;
        }
      }
      return boost::none;
    }

    boost::optional<ZoneHVACComponent> HVACComponent_Impl::containingZoneHVACComponent() const {
      const auto thisObject = getObject<ModelObject>();
      for (const auto& zoneEquipment : model().getModelObjects<openstudio::epmodel::ZoneHVACComponent>()) {
        const auto children = zoneEquipment.children();
        if (std::ranges::find(children, thisObject) != children.end()) {
          return zoneEquipment;
        }
      }
      return boost::none;
    }

    boost::optional<HVACComponent> HVACComponent_Impl::containingHVACComponent() const {
      const auto thisObject = getObject<ModelObject>();
      for (const auto& component : model().getModelObjects<openstudio::epmodel::HVACComponent>()) {
        if (component.handle() == thisObject.handle()) {
          continue;
        }

        const auto children = component.children();
        if (std::ranges::find(children, thisObject) != children.end()) {
          return component;
        }
      }
      return boost::none;
    }

    bool HVACComponent_Impl::addToNode(Node& /*node*/) {
      return false;
    }

    bool HVACComponent_Impl::addToSplitter(Splitter& /*splitter*/) {
      return false;
    }

    void HVACComponent_Impl::disconnect() {}

    bool HVACComponent_Impl::isRemovable() const {
      return !containingHVACComponent();
    }

    std::vector<IdfObject> HVACComponent_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }
      disconnect();
      return ParentObject_Impl::remove();
    }

    openstudio::ComponentType HVACComponent_Impl::componentType() const {
      return openstudio::ComponentType();
    }

    std::vector<openstudio::FuelType> HVACComponent_Impl::coolingFuelTypes() const {
      return {};
    }

    std::vector<openstudio::FuelType> HVACComponent_Impl::heatingFuelTypes() const {
      return {};
    }

    std::vector<openstudio::AppGFuelType> HVACComponent_Impl::appGHeatingFuelTypes() const {
      return {};
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
