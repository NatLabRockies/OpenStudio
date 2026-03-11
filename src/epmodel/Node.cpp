/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Node.hpp"
#include "Node_Impl.hpp"

#include "Loop.hpp"
#include "Loop_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "AirLoopHVACZoneSplitter.hpp"
#include "AirLoopHVACZoneMixer.hpp"
#include "BranchList.hpp"
#include "BranchList_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/core/Compare.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  Node::Node(const Model& model) : StraightComponent(Node::iddObjectType(), model, false, true) {
    auto impl = getImpl<detail::Node_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  Node::Node(std::shared_ptr<detail::Node_Impl> impl) : StraightComponent(std::move(impl)) {}

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
      for (const auto& airLoop : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
        if (thisNode == airLoop.supplyInletNode()) {
          return airLoop;
        }

        const auto supplyOutlets = airLoop.supplyOutletNodes();
        if (std::ranges::find(supplyOutlets, thisNode) != supplyOutlets.end()) {
          return airLoop;
        }

        const auto demandInlets = airLoop.demandInletNodes();
        if (std::ranges::find(demandInlets, thisNode) != demandInlets.end()) {
          return airLoop;
        }

        if (thisNode == airLoop.demandOutletNode()) {
          return airLoop;
        }

        const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
        if (std::ranges::find(splitterOutlets, thisNode.cast<ModelObject>()) != splitterOutlets.end()) {
          return airLoop;
        }

        const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
        if (std::ranges::find(mixerInlets, thisNode.cast<ModelObject>()) != mixerInlets.end()) {
          return airLoop;
        }

        auto branchList = airLoop.getModelObjectTarget<openstudio::epmodel::BranchList>(openstudio::AirLoopHVACFields::BranchListName);
        if (!branchList) {
          continue;
        }

        for (const auto& branch : branchList->branches()) {
          for (const auto& group : branch.extensibleGroups()) {
            auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
            if (!workspaceGroup) {
              continue;
            }

            if (auto inletTarget = workspaceGroup->getTarget(openstudio::BranchExtensibleFields::ComponentInletNodeName)) {
              if (inletTarget->handle() == thisNode.handle()) {
                return airLoop;
              }
            }
            if (auto outletTarget = workspaceGroup->getTarget(openstudio::BranchExtensibleFields::ComponentOutletNodeName)) {
              if (outletTarget->handle() == thisNode.handle()) {
                return airLoop;
              }
            }
          }
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
