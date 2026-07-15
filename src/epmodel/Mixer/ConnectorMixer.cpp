/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
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

  ConnectorMixer::ConnectorMixer(const Model& model) : Mixer(ConnectorMixer::iddObjectType(), model) {
    auto impl = getImpl<detail::ConnectorMixer_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ConnectorMixer::ConnectorMixer(std::shared_ptr<detail::ConnectorMixer_Impl> impl) : Mixer(std::move(impl)) {}

  IddObjectType ConnectorMixer::iddObjectType() {
    return IddObjectType::Connector_Mixer;
  }

  unsigned ConnectorMixer::outletPort() const {
    return getImpl<detail::ConnectorMixer_Impl>()->outletPort();
  }

  unsigned ConnectorMixer::inletPort(unsigned branchIndex) const {
    return getImpl<detail::ConnectorMixer_Impl>()->inletPort(branchIndex);
  }

  unsigned ConnectorMixer::nextInletPort() const {
    return getImpl<detail::ConnectorMixer_Impl>()->nextInletPort();
  }

  boost::optional<ModelObject> ConnectorMixer::outletModelObject() const {
    return getImpl<detail::ConnectorMixer_Impl>()->outletModelObject();
  }

  std::vector<ModelObject> ConnectorMixer::inletModelObjects() const {
    return getImpl<detail::ConnectorMixer_Impl>()->inletModelObjects();
  }

  unsigned ConnectorMixer::nextBranchIndex() const {
    return getImpl<detail::ConnectorMixer_Impl>()->nextBranchIndex();
  }

  void ConnectorMixer::removePortForBranch(unsigned branchIndex) {
    return getImpl<detail::ConnectorMixer_Impl>()->removePortForBranch(branchIndex);
  }

  bool ConnectorMixer::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    return getImpl<detail::ConnectorMixer_Impl>()->setInletModelObject(branchIndex, modelObject);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned ConnectorMixer_Impl::outletPort() const {
      return getObject<openstudio::epmodel::ConnectorMixer>().numNonextensibleFields() - 1u;
    }

    unsigned ConnectorMixer_Impl::inletPort(unsigned branchIndex) const {
      return getObject<openstudio::epmodel::ConnectorMixer>().numNonextensibleFields() + branchIndex;
    }

    boost::optional<openstudio::epmodel::ModelObject> ConnectorMixer_Impl::outletModelObject() const {
      if (auto loop = plantLoop()) {
        auto loopImpl = loop->getImpl<detail::PlantLoop_Impl>();
        const bool isSupplyMixer = (loop->supplyMixer().handle() == handle());
        const bool isDemandMixer = (loop->demandMixer().handle() == handle());
        OS_ASSERT(isSupplyMixer || isDemandMixer);

        if (isSupplyMixer) {
          const auto branch = loopImpl->supplyOutletBranch();
          const auto components = branch.components();
          if (components.empty()) {
            return loopImpl->supplyOutletNode().cast<ModelObject>();
          }
          if (auto node = branch.componentInletNode(0u)) {
            return node->cast<ModelObject>();
          }
        } else {
          const auto branch = loopImpl->demandOutletBranch();
          const auto components = branch.components();
          if (components.empty()) {
            return loopImpl->demandOutletNode().cast<ModelObject>();
          }
          if (auto node = branch.componentInletNode(0u)) {
            return node->cast<ModelObject>();
          }
        }
      }
      return boost::none;
    }

    std::vector<openstudio::epmodel::ModelObject> ConnectorMixer_Impl::inletModelObjects() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      if (auto loop = plantLoop()) {
        auto loopImpl = loop->getImpl<detail::PlantLoop_Impl>();
        const bool isSupplyMixer = (loop->supplyMixer().handle() == handle());
        const bool isDemandMixer = (loop->demandMixer().handle() == handle());
        OS_ASSERT(isSupplyMixer || isDemandMixer);
        const auto branches = isSupplyMixer ? loopImpl->supplyEquipmentBranches() : loopImpl->demandEquipmentBranches();

        for (const auto& branch : branches) {
          const auto components = branch.components();
          if (components.empty()) {
            const auto branchNodeName = branch.nameString() + " Node";
            auto branchNode = model().getModelObjectByName<Node>(branchNodeName);
            OS_ASSERT(branchNode);
            result.emplace_back(branchNode->cast<ModelObject>());
            continue;
          }
          if (auto node = branch.componentOutletNode(static_cast<unsigned>(components.size() - 1u))) {
            result.emplace_back(node->cast<ModelObject>());
            continue;
          }
          OS_ASSERT(false);
          break;
        }
      }
      return result;
    }

    unsigned ConnectorMixer_Impl::nextBranchIndex() const {
      return static_cast<unsigned>(getObject<openstudio::epmodel::ConnectorMixer>().extensibleGroups().size());
    }

    void ConnectorMixer_Impl::removePortForBranch(unsigned branchIndex) {
      auto mixer = getObject<openstudio::epmodel::ConnectorMixer>();
      if (branchIndex < mixer.extensibleGroups().size()) {
        mixer.eraseExtensibleGroup(branchIndex);
      }
    }

    bool ConnectorMixer_Impl::setInletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) {
      auto mixer = getObject<openstudio::epmodel::ConnectorMixer>();
      if (modelObject.model() != mixer.model()) {
        return false;
      }

      auto branch = modelObject.optionalCast<openstudio::epmodel::Branch>();
      if (!branch) {
        return false;
      }

      auto groups = mixer.extensibleGroups();
      IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : mixer.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(0u, branch->handle(), false);
    }

    boost::optional<openstudio::epmodel::Branch> ConnectorMixer_Impl::outletBranch() const {
      return getObject<openstudio::epmodel::ConnectorMixer>().getModelObjectTarget<openstudio::epmodel::Branch>(
        getObject<openstudio::epmodel::ConnectorMixer>().outletPort());
    }

    bool ConnectorMixer_Impl::setOutletBranch(const openstudio::epmodel::Branch& branch) {
      auto mixer = getObject<openstudio::epmodel::ConnectorMixer>();
      return setPointer(mixer.outletPort(), branch.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
