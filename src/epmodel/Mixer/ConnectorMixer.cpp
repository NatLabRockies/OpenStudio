/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"

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
    return numNonextensibleFields() - 1u;
  }

  unsigned ConnectorMixer::inletPort(unsigned branchIndex) const {
    return numNonextensibleFields() + branchIndex;
  }

  unsigned ConnectorMixer::nextInletPort() const {
    return inletPort(nextBranchIndex());
  }

  boost::optional<ModelObject> ConnectorMixer::outletModelObject() const {
    if (auto branch = getModelObjectTarget<openstudio::epmodel::Branch>(outletPort())) {
      return branch->cast<ModelObject>();
    }
    return boost::none;
  }

  std::vector<ModelObject> ConnectorMixer::inletModelObjects() const {
    std::vector<ModelObject> result;
    for (const auto& group : extensibleGroups()) {
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        continue;
      }
      auto target = workspaceGroup->getTarget(0u);
      if (!target) {
        continue;
      }
      auto branch = target->optionalCast<openstudio::epmodel::Branch>();
      if (!branch) {
        continue;
      }
      result.emplace_back(branch->cast<ModelObject>());
    }
    return result;
  }

  unsigned ConnectorMixer::nextBranchIndex() const {
    return static_cast<unsigned>(extensibleGroups().size());
  }

  void ConnectorMixer::removePortForBranch(unsigned branchIndex) {
    if (branchIndex < extensibleGroups().size()) {
      eraseExtensibleGroup(branchIndex);
    }
  }

  bool ConnectorMixer::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    if (modelObject.model() != model()) {
      return false;
    }

    auto branch = modelObject.optionalCast<openstudio::epmodel::Branch>();
    if (!branch) {
      return false;
    }

    auto groups = extensibleGroups();
    IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : pushExtensibleGroup();
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (!workspaceGroup) {
      return false;
    }
    if (!workspaceGroup->setString(0u, branch->nameString())) {
      return false;
    }
    return workspaceGroup->setPointer(0u, branch->handle(), false);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

    boost::optional<openstudio::epmodel::Branch> ConnectorMixer_Impl::outletBranch() const {
      return getObject<openstudio::epmodel::ConnectorMixer>().getModelObjectTarget<openstudio::epmodel::Branch>(
        getObject<openstudio::epmodel::ConnectorMixer>().outletPort());
    }

    bool ConnectorMixer_Impl::setOutletBranch(const openstudio::epmodel::Branch& branch) {
      auto mixer = getObject<openstudio::epmodel::ConnectorMixer>();
      if (!setString(mixer.outletPort(), branch.nameString())) {
        return false;
      }
      return setPointer(mixer.outletPort(), branch.handle(), false);
    }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
