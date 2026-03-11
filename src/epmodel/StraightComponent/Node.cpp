/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"

#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "SetpointManager/SetpointManager.hpp"
#include "SetpointManager/SetpointManager_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/core/Logger.hpp>

namespace openstudio {
namespace epmodel {

  Node::Node(const Model& model) : StraightComponent(Node::iddObjectType(), model, false, true) {
    auto impl = getImpl<detail::Node_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  Node::Node(std::shared_ptr<detail::Node_Impl> impl) : StraightComponent(std::move(impl)) {}

  std::vector<SetpointManager> Node::setpointManagers() const {
    std::vector<SetpointManager> result;
    for (const auto& object : model().objects()) {
      auto spm = object.optionalCast<SetpointManager>();
      if (!spm) {
        continue;
      }
      auto setpointNode = spm->setpointNode();
      if (setpointNode && (*setpointNode == *this)) {
        result.push_back(*spm);
      }
    }
    return result;
  }

  boost::optional<AirLoopHVACOutdoorAirSystem> Node::airLoopHVACOutdoorAirSystem() const {
    auto impl = getImpl<detail::Node_Impl>();
    OS_ASSERT(impl);
    return impl->airLoopHVACOutdoorAirSystem();
  }

  IddObjectType Node::iddObjectType() {
    return IddObjectType::Node;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      boost::optional<openstudio::epmodel::ModelObject> findAdjacentInPath(const std::vector<openstudio::epmodel::ModelObject>& path,
                                                                           const openstudio::epmodel::ModelObject& node, bool upstream) {
        std::vector<std::size_t> matches;
        for (std::size_t i = 0; i < path.size(); ++i) {
          if (path[i] == node) {
            matches.push_back(i);
          }
        }

        if (matches.empty()) {
          return boost::none;
        }

        const auto index = matches.front();
        if (matches.size() > 1u) {
          LOG_FREE(Warn, "openstudio.epmodel.Node", "Node appears multiple times in AirLoopHVAC supplyComponents path; using first occurrence.");
        }

        if (upstream) {
          if (index == 0u) {
            return boost::none;
          }
          return path[index - 1];
        } else {
          if (index + 1 >= path.size()) {
            return boost::none;
          }
          return path[index + 1];
        }

        return boost::none;
      }

    }  // namespace

    Node_Impl::Node_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(idfObject, model, keepHandle) {}

    Node_Impl::Node_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {}

    Node_Impl::Node_Impl(const Node_Impl& other, Model_Impl* model, bool keepHandle) : StraightComponent_Impl(other, model, keepHandle) {}

    boost::optional<AirLoopHVAC> Node_Impl::airLoopHVAC() const {
      const auto thisNode = getObject<openstudio::epmodel::Node>();
      const auto thisNodeObject = thisNode.cast<openstudio::epmodel::ModelObject>();
      for (const auto& airLoop : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
        // Use loop-owned traversal APIs as the single source of truth for
        // topology membership instead of duplicating node-role checks here.
        if (airLoop.component(thisNode.handle())) {
          return airLoop;
        }
        // Demand-side branch mutators temporarily reference splitter/mixer
        // branch nodes that are not always on the currently selected
        // demandComponents traversal path; include direct branch node
        // membership checks so addToNode-style operations can resolve loop
        // ownership for any active branch.
        const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
        if (std::ranges::find(splitterOutlets, thisNodeObject) != splitterOutlets.end()) {
          return airLoop;
        }
        const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
        if (std::ranges::find(mixerInlets, thisNodeObject) != mixerInlets.end()) {
          return airLoop;
        }
        if (auto oaSystem = airLoop.airLoopHVACOutdoorAirSystem()) {
          if (oaSystem->component(thisNode.handle())) {
            return airLoop;
          }
        }
      }
      return boost::none;
    }

    boost::optional<AirLoopHVACOutdoorAirSystem> Node_Impl::airLoopHVACOutdoorAirSystem() const {
      const auto thisNode = getObject<openstudio::epmodel::Node>();
      const auto thisNodeObject = thisNode.cast<ModelObject>();

      // Temporary ownership heuristic until full OA incoming/relief stream
      // topology is modeled in epmodel. For now, treat any node that is one of
      // the OA mixer ports or part of OA/relief component chains as belonging
      // to that OA system.
      for (const auto& oaSystem : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
        if (auto returnNode = oaSystem.returnAirModelObject(); returnNode && (*returnNode == thisNodeObject)) {
          return oaSystem;
        }
        if (auto mixedNode = oaSystem.mixedAirModelObject(); mixedNode && (*mixedNode == thisNodeObject)) {
          return oaSystem;
        }
        if (auto outdoorNode = oaSystem.outdoorAirModelObject(); outdoorNode && (*outdoorNode == thisNodeObject)) {
          return oaSystem;
        }
        if (auto reliefNode = oaSystem.reliefAirModelObject(); reliefNode && (*reliefNode == thisNodeObject)) {
          return oaSystem;
        }
        if (oaSystem.component(thisNode.handle())) {
          return oaSystem;
        }
      }

      return boost::none;
    }

    boost::optional<ModelObject> Node_Impl::inletModelObject() const {
      boost::optional<ModelObject> result;
      // We derive adjacency from loop-level canonical supply ordering instead of
      // storing node neighbors directly. This keeps Node wiring consistent with
      // Branch/Path source-of-truth, at the cost of a relatively expensive walk.
      // The call graph currently avoids recursion through this API; if loop
      // traversal later depends on Node adjacency, this path must be revisited.
      const auto loop_ = loop();

      if (loop_) {
        const auto thisNode = getObject<openstudio::epmodel::Node>();
        const auto path = loop_->supplyComponents(loop_->supplyInletNode(), thisNode, openstudio::IddObjectType::Catchall);
        result = findAdjacentInPath(path, thisNode, true);
      }

      return result;
    }

    boost::optional<ModelObject> Node_Impl::outletModelObject() const {
      boost::optional<ModelObject> result;
      // Mirror inletModelObject rationale: compute adjacency from canonical loop
      // traversal so Node APIs stay aligned with loop topology source-of-truth.
      // This remains intentionally derived (not cached) to avoid duplicate
      // connectivity state that can drift.
      const auto loop_ = loop();

      if (loop_) {
        const auto thisNode = getObject<openstudio::epmodel::Node>();
        const auto path = loop_->supplyComponents(thisNode, loop_->supplyOutletNode(), openstudio::IddObjectType::Catchall);
        result = findAdjacentInPath(path, thisNode, false);
      }

      return result;
    }

    unsigned Node_Impl::inletPort() const {
      // Node is treated as a topology anchor rather than a multi-port
      // component; port indexing is not meaningful for this type.
      return 0;
    }

    unsigned Node_Impl::outletPort() const {
      // Node is treated as a topology anchor rather than a multi-port
      // component; port indexing is not meaningful for this type.
      return 0;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
