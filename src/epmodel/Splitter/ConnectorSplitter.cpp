/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  ConnectorSplitter::ConnectorSplitter(const Model& model) : Splitter(ConnectorSplitter::iddObjectType(), model) {
    auto impl = getImpl<detail::ConnectorSplitter_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ConnectorSplitter::ConnectorSplitter(std::shared_ptr<detail::ConnectorSplitter_Impl> impl) : Splitter(std::move(impl)) {}

  IddObjectType ConnectorSplitter::iddObjectType() {
    return IddObjectType::Connector_Splitter;
  }

  unsigned ConnectorSplitter::inletPort() const {
    return getImpl<detail::ConnectorSplitter_Impl>()->inletPort();
  }

  unsigned ConnectorSplitter::outletPort(unsigned branchIndex) const {
    return getImpl<detail::ConnectorSplitter_Impl>()->outletPort(branchIndex);
  }

  unsigned ConnectorSplitter::nextOutletPort() const {
    return getImpl<detail::ConnectorSplitter_Impl>()->nextOutletPort();
  }

  boost::optional<ModelObject> ConnectorSplitter::inletModelObject() const {
    return getImpl<detail::ConnectorSplitter_Impl>()->inletModelObject();
  }

  std::vector<ModelObject> ConnectorSplitter::outletModelObjects() const {
    return getImpl<detail::ConnectorSplitter_Impl>()->outletModelObjects();
  }

  unsigned ConnectorSplitter::nextBranchIndex() const {
    return getImpl<detail::ConnectorSplitter_Impl>()->nextBranchIndex();
  }

  void ConnectorSplitter::removePortForBranch(unsigned branchIndex) {
    return getImpl<detail::ConnectorSplitter_Impl>()->removePortForBranch(branchIndex);
  }

  bool ConnectorSplitter::setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    return getImpl<detail::ConnectorSplitter_Impl>()->setOutletModelObject(branchIndex, modelObject);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

    unsigned ConnectorSplitter_Impl::inletPort() const {
      return getObject<openstudio::epmodel::ConnectorSplitter>().numNonextensibleFields() - 1u;
    }

    unsigned ConnectorSplitter_Impl::outletPort(unsigned branchIndex) const {
      return getObject<openstudio::epmodel::ConnectorSplitter>().numNonextensibleFields() + branchIndex;
    }

    boost::optional<openstudio::epmodel::ModelObject> ConnectorSplitter_Impl::inletModelObject() const {
      for (const auto& loop : model().getConcreteModelObjects<AirLoopHVAC>()) {
        auto loopImpl = loop.getImpl<detail::AirLoopHVAC_Impl>();
        auto splitter = loopImpl->supplySplitter();
        if (!(splitter && splitter->handle() == handle())) {
          continue;
        }
        const auto branch = loopImpl->branchList().branches().front();
        const auto components = branch.components();
        if (components.empty()) {
          return loopImpl->supplyInletNode().cast<ModelObject>();
        }
        if (auto node = branch.componentOutletNode(static_cast<unsigned>(components.size() - 1u))) {
          return node->cast<ModelObject>();
        }
      }
      if (auto loop = plantLoop()) {
        auto loopImpl = loop->getImpl<detail::PlantLoop_Impl>();
        const bool isSupplySplitter = (loop->supplySplitter().handle() == handle());
        const bool isDemandSplitter = (loop->demandSplitter().handle() == handle());
        OS_ASSERT(isSupplySplitter || isDemandSplitter);

        if (isSupplySplitter) {
          const auto branch = loopImpl->supplyInletBranch();
          const auto components = branch.components();
          if (components.empty()) {
            return loopImpl->supplyInletNode().cast<ModelObject>();
          }
          if (auto node = branch.componentOutletNode(static_cast<unsigned>(components.size() - 1u))) {
            return node->cast<ModelObject>();
          }
        } else {
          const auto branch = loopImpl->demandInletBranch();
          const auto components = branch.components();
          if (components.empty()) {
            return loopImpl->demandInletNode().cast<ModelObject>();
          }
          if (auto node = branch.componentOutletNode(static_cast<unsigned>(components.size() - 1u))) {
            return node->cast<ModelObject>();
          }
        }
      }
      return boost::none;
    }

    std::vector<openstudio::epmodel::ModelObject> ConnectorSplitter_Impl::outletModelObjects() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      for (const auto& loop : model().getConcreteModelObjects<AirLoopHVAC>()) {
        auto loopImpl = loop.getImpl<detail::AirLoopHVAC_Impl>();
        auto splitter = loopImpl->supplySplitter();
        if (!(splitter && splitter->handle() == handle())) {
          continue;
        }
        const auto branches = loopImpl->branchList().branches();
        const auto outletNodes = loopImpl->supplyOutletNodes();
        for (std::size_t i = 0; i < outletNodes.size() && (i + 1u) < branches.size(); ++i) {
          const auto components = branches[i + 1u].components();
          if (components.empty()) {
            result.emplace_back(outletNodes[i].cast<ModelObject>());
          } else if (auto node = branches[i + 1u].componentInletNode(0u)) {
            result.emplace_back(node->cast<ModelObject>());
          }
        }
        return result;
      }
      if (auto loop = plantLoop()) {
        auto loopImpl = loop->getImpl<detail::PlantLoop_Impl>();
        const bool isSupplySplitter = (loop->supplySplitter().handle() == handle());
        const bool isDemandSplitter = (loop->demandSplitter().handle() == handle());
        OS_ASSERT(isSupplySplitter || isDemandSplitter);
        const auto branches = isSupplySplitter ? loopImpl->supplyEquipmentBranches() : loopImpl->demandEquipmentBranches();

        for (const auto& branch : branches) {
          const auto components = branch.components();
          if (components.empty()) {
            const auto branchNodeName = branch.nameString() + " Node";
            auto branchNode = model().getModelObjectByName<Node>(branchNodeName);
            OS_ASSERT(branchNode);
            result.emplace_back(branchNode->cast<ModelObject>());
            continue;
          }
          if (auto node = branch.componentInletNode(0u)) {
            result.emplace_back(node->cast<ModelObject>());
            continue;
          }
          OS_ASSERT(false);
          break;
        }
      }
      return result;
    }

    unsigned ConnectorSplitter_Impl::nextBranchIndex() const {
      return static_cast<unsigned>(getObject<openstudio::epmodel::ConnectorSplitter>().extensibleGroups().size());
    }

    void ConnectorSplitter_Impl::removePortForBranch(unsigned branchIndex) {
      auto splitter = getObject<openstudio::epmodel::ConnectorSplitter>();
      if (branchIndex < splitter.extensibleGroups().size()) {
        splitter.eraseExtensibleGroup(branchIndex);
      }
    }

    bool ConnectorSplitter_Impl::setOutletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) {
      auto splitter = getObject<openstudio::epmodel::ConnectorSplitter>();
      if (modelObject.model() != splitter.model()) {
        return false;
      }

      auto branch = modelObject.optionalCast<openstudio::epmodel::Branch>();
      if (!branch) {
        return false;
      }

      auto groups = splitter.extensibleGroups();
      IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : splitter.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(0u, branch->handle(), false);
    }

    boost::optional<openstudio::epmodel::Branch> ConnectorSplitter_Impl::inletBranch() const {
      return getObject<openstudio::epmodel::ConnectorSplitter>().getModelObjectTarget<openstudio::epmodel::Branch>(
        getObject<openstudio::epmodel::ConnectorSplitter>().inletPort());
    }

    bool ConnectorSplitter_Impl::setInletBranch(const openstudio::epmodel::Branch& branch) {
      auto splitter = getObject<openstudio::epmodel::ConnectorSplitter>();
      return setPointer(splitter.inletPort(), branch.handle(), false);
    }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
