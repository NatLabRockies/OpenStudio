/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"

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
    return numNonextensibleFields() - 1u;
  }

  unsigned ConnectorSplitter::outletPort(unsigned branchIndex) const {
    return numNonextensibleFields() + branchIndex;
  }

  unsigned ConnectorSplitter::nextOutletPort() const {
    return outletPort(nextBranchIndex());
  }

  boost::optional<ModelObject> ConnectorSplitter::inletModelObject() const {
    if (auto branch = getModelObjectTarget<openstudio::epmodel::Branch>(inletPort())) {
      return branch->cast<ModelObject>();
    }
    return boost::none;
  }

  std::vector<ModelObject> ConnectorSplitter::outletModelObjects() const {
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

  unsigned ConnectorSplitter::nextBranchIndex() const {
    return static_cast<unsigned>(extensibleGroups().size());
  }

  void ConnectorSplitter::removePortForBranch(unsigned branchIndex) {
    if (branchIndex < extensibleGroups().size()) {
      eraseExtensibleGroup(branchIndex);
    }
  }

  bool ConnectorSplitter::setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
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

    boost::optional<openstudio::epmodel::Branch> ConnectorSplitter_Impl::inletBranch() const {
      return getObject<openstudio::epmodel::ConnectorSplitter>().getModelObjectTarget<openstudio::epmodel::Branch>(
        getObject<openstudio::epmodel::ConnectorSplitter>().inletPort());
    }

    bool ConnectorSplitter_Impl::setInletBranch(const openstudio::epmodel::Branch& branch) {
      auto splitter = getObject<openstudio::epmodel::ConnectorSplitter>();
      if (!setString(splitter.inletPort(), branch.nameString())) {
        return false;
      }
      return setPointer(splitter.inletPort(), branch.handle(), false);
    }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
