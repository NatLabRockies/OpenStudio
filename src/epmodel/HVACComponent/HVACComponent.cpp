/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent.hpp"
#include "HVACComponent_Impl.hpp"
#include "Model.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Node.hpp"
#include "Splitter/Splitter.hpp"
#include "StraightComponent/StraightComponent.hpp"

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

  boost::optional<HVACComponent> HVACComponent::containingHVACComponent() const {
    return boost::none;
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
      const auto airLoops = model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>();
      for (const auto& airLoop : airLoops) {
        const auto components = airLoop.components(openstudio::IddObjectType::Catchall);
        for (const auto& component : components) {
          if (component.handle() == handle()) {
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

    bool HVACComponent_Impl::addToNode(Node& /*node*/) {
      return false;
    }

    bool HVACComponent_Impl::addToSplitter(Splitter& /*splitter*/) {
      return false;
    }

    void HVACComponent_Impl::disconnect() {}

    bool HVACComponent_Impl::isRemovable() const {
      return true;
    }

    std::vector<IdfObject> HVACComponent_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }
      disconnect();
      return ParentObject_Impl::remove();
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
