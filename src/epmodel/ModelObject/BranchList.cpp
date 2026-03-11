/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "BranchList.hpp"
#include "BranchList_Impl.hpp"

#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

BranchList::BranchList(const Model& model) : ModelObject(BranchList::iddObjectType(), model) {
  auto impl = getImpl<detail::BranchList_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

BranchList::BranchList(std::shared_ptr<detail::BranchList_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType BranchList::iddObjectType() {
  return IddObjectType::BranchList;
}

std::vector<Branch> BranchList::branches() const {
  return getImpl<detail::BranchList_Impl>()->branches();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

void BranchList_Impl::doCanonicalize(LoadContext& context) {
  const auto object = workspace().getObject(handle());
  if (!object) {
    return;
  }
  auto branchList = object->optionalCast<openstudio::epmodel::BranchList>();
  if (!branchList) {
    return;
  }

  if (!branchList->name() || branchList->name()->empty()) {
    if (context.repairEnabled()) {
      const auto branchListName = context.model.nextName(openstudio::IddObjectType::BranchList, true);
      if (branchList->setName(branchListName)) {
        detail::addLoadInfo(context, "Assigned missing BranchList name '" + branchListName + "'.");
      } else {
        detail::addLoadError(context, "Failed assigning missing name on a BranchList object.");
      }
    } else {
      detail::addLoadWarning(context, "BranchList has missing/empty name.");
    }
  }

  if ((branchList->numExtensibleGroups() == 0u) && context.repairEnabled()) {
    openstudio::epmodel::Branch branch(context.model);
    if (!branch.name() || branch.name()->empty()) {
      branch.setName(context.model.nextName(openstudio::IddObjectType::Branch, true));
    }
    if (addBranch(branch)) {
      detail::addLoadInfo(context, "Inserted missing Branch '" + branch.nameString() + "' into BranchList '" + branchList->nameString() + "'.");
    } else {
      detail::addLoadError(context, "Failed adding default Branch to BranchList '" + branchList->nameString() + "'.");
    }
  }

  // Erase/repair in-place while keeping one pass over surviving rows.
  // Re-reading extensible groups each iteration avoids stale indices after
  // erase and keeps diagnostics aligned with final retained ordering.
  unsigned groupIndex = 0u;
  while (groupIndex < branchList->numExtensibleGroups()) {
    auto groups = branchList->extensibleGroups();
    if (groupIndex >= groups.size()) {
      break;
    }
    auto group = groups[groupIndex];

    auto branchName = group.getString(openstudio::BranchListExtensibleFields::BranchName);
    if (!(branchName && !branchName->empty())) {
      detail::addLoadWarning(context, "BranchList '" + branchList->nameString() + "' has an unnamed Branch reference at extensible index "
                                       + std::to_string(groupIndex) + ".");
      if (context.repairEnabled()) {
        const auto generatedName = context.model.nextName(openstudio::IddObjectType::Branch, true);
        if (group.setString(openstudio::BranchListExtensibleFields::BranchName, generatedName)) {
          branchName = generatedName;
          detail::addLoadInfo(context, "Assigned missing BranchList branch name '" + generatedName + "'.");
        } else {
          detail::addLoadError(context, "Failed assigning missing BranchList branch name.");
        }
      }
    }

    if (!(branchName && !branchName->empty())) {
      ++groupIndex;
      continue;
    }

    // BranchList is a name-index of Branch objects. If a referenced Branch is
    // missing, repair mode synthesizes one so downstream traversal APIs can
    // trust that every row resolves to a concrete Branch.
    auto branchObject = context.model.getObjectByTypeAndName(openstudio::IddObjectType::Branch, *branchName);
    if (!branchObject) {
      detail::addLoadWarning(context, "BranchList '" + branchList->nameString() + "' references missing Branch '" + *branchName + "'.");
      if (context.repairEnabled()) {
        openstudio::epmodel::Branch branch(context.model);
        if (!branch.setName(*branchName)) {
          branch.setName(context.model.nextName(openstudio::IddObjectType::Branch, true));
          if (auto assignedName = branch.name()) {
            group.setString(openstudio::BranchListExtensibleFields::BranchName, *assignedName);
            detail::addLoadWarning(context, "Branch name collision for '" + *branchName + "', rewired to '" + *assignedName + "'.");
          }
        }
        detail::addLoadInfo(context,
                            "Created missing Branch '" + branch.nameString() + "' for BranchList '" + branchList->nameString() + "'.");
        if (auto branchImpl = branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()) {
          branchImpl->canonicalize(context);
        }
      }
      ++groupIndex;
      continue;
    }

    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (workspaceGroup && !workspaceGroup->setPointer(openstudio::BranchListExtensibleFields::BranchName, branchObject->handle())) {
      detail::addLoadWarning(context, "Failed to set BranchList pointer to Branch '" + *branchName + "'.");
    }

    if (auto branch = branchObject->optionalCast<openstudio::epmodel::Branch>()) {
      if (auto branchImpl = branch->getImpl<openstudio::epmodel::detail::Branch_Impl>()) {
        branchImpl->canonicalize(context);
      }
    } else {
      detail::addLoadWarning(context, "Object named '" + *branchName + "' is not an epmodel::Branch.");
    }

    ++groupIndex;
  }

}

std::vector<openstudio::epmodel::Branch> BranchList_Impl::branches() const {
  std::vector<openstudio::epmodel::Branch> result;
  const auto groups = extensibleGroups();
  result.reserve(groups.size());
  for (const auto& group : groups) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);
    auto target = workspaceGroup->getTarget(openstudio::BranchListExtensibleFields::BranchName);
    OS_ASSERT(target);
    auto branch = target->optionalCast<openstudio::epmodel::Branch>();
    OS_ASSERT(branch);
    result.push_back(*branch);
  }
  return result;
}

bool BranchList_Impl::addBranch(const openstudio::epmodel::Branch& branch) {
  if (branch.model() != model()) {
    return false;
  }
  if (!branch.name() || branch.name()->empty()) {
    return false;
  }

  for (const auto& existing : branches()) {
    if (existing == branch) {
      return true;
    }
  }

  auto branchList = getObject<openstudio::epmodel::BranchList>();
  auto group = branchList.pushExtensibleGroup();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!workspaceGroup) {
    return false;
  }
  return workspaceGroup->setPointer(openstudio::BranchListExtensibleFields::BranchName, branch.handle());
}

bool BranchList_Impl::removeBranch(const openstudio::epmodel::Branch& branch) {
  auto groups = extensibleGroups();
  for (unsigned i = 0; i < groups.size(); ++i) {
    auto workspaceGroup = groups[i].optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (workspaceGroup) {
      if (auto target = workspaceGroup->getTarget(openstudio::BranchListExtensibleFields::BranchName)) {
        if (target->handle() == branch.handle()) {
          return !eraseExtensibleGroup(i).empty();
        }
      }
    }
  }
  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
