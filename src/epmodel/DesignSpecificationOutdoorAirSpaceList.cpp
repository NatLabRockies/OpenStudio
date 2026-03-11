/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DesignSpecificationOutdoorAirSpaceList.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"

#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "Model.hpp"
#include "Space.hpp"
#include "Space_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DesignSpecification_OutdoorAir_SpaceList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

DesignSpecificationOutdoorAirSpaceList::DesignSpecificationOutdoorAirSpaceList(const Model& model)
  : ModelObject(DesignSpecificationOutdoorAirSpaceList::iddObjectType(), model) {
  auto impl = getImpl<detail::DesignSpecificationOutdoorAirSpaceList_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

DesignSpecificationOutdoorAirSpaceList::DesignSpecificationOutdoorAirSpaceList(
  std::shared_ptr<detail::DesignSpecificationOutdoorAirSpaceList_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DesignSpecificationOutdoorAirSpaceList::iddObjectType() {
  return IddObjectType::DesignSpecification_OutdoorAir_SpaceList;
}

std::vector<Space> DesignSpecificationOutdoorAirSpaceList::spaces() const {
  return getImpl<detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->spaces();
}

boost::optional<DesignSpecificationOutdoorAir> DesignSpecificationOutdoorAirSpaceList::designSpecificationOutdoorAir(const Space& space) const {
  return getImpl<detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->designSpecificationOutdoorAir(space);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::vector<openstudio::epmodel::Space> DesignSpecificationOutdoorAirSpaceList_Impl::spaces() const {
  std::vector<openstudio::epmodel::Space> result;
  auto list = getObject<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
  const auto groups = list.extensibleGroups();
  result.reserve(groups.size());
  for (const auto& group : groups) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);
    auto target = workspaceGroup->getTarget(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName);
    OS_ASSERT(target);
    auto space = target->optionalCast<openstudio::epmodel::Space>();
    OS_ASSERT(space);
    result.push_back(*space);
  }
  return result;
}

boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir>
  DesignSpecificationOutdoorAirSpaceList_Impl::designSpecificationOutdoorAir(const openstudio::epmodel::Space& space) const {
  auto list = getObject<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
  const auto groups = list.extensibleGroups();
  for (const auto& group : groups) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);
    auto spaceTarget = workspaceGroup->getTarget(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName);
    OS_ASSERT(spaceTarget);
    auto groupSpace = spaceTarget->optionalCast<openstudio::epmodel::Space>();
    OS_ASSERT(groupSpace);
    if (*groupSpace != space) {
      continue;
    }
    auto dsoaTarget = workspaceGroup->getTarget(
      openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName);
    OS_ASSERT(dsoaTarget);
    auto dsoa = dsoaTarget->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAir>();
    OS_ASSERT(dsoa);
    return dsoa;
  }
  return boost::none;
}

bool DesignSpecificationOutdoorAirSpaceList_Impl::setDesignSpecificationOutdoorAir(
  const openstudio::epmodel::Space& space, const openstudio::epmodel::DesignSpecificationOutdoorAir& designSpecificationOutdoorAir) {
  // Impl-only connective-tissue mutator:
  // Public callers should mutate DSOA assignment through the Space-level DSOA setter API.
  // This setter is internal scaffolding used by canonicalization and other model-internal
  // wiring paths to materialize DesignSpecification:OutdoorAir:SpaceList extensible groups.
  if (space.model() != model()) {
    return false;
  }
  if (designSpecificationOutdoorAir.model() != model()) {
    return false;
  }

  auto list = getObject<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
  auto groups = list.extensibleGroups();
  // Upsert semantics for the extensible table:
  // 1) if an entry already exists for this space, replace its DSOA target.
  // 2) otherwise append a new extensible group at the end.
  for (const auto& group : groups) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);
    auto spaceTarget = workspaceGroup->getTarget(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName);
    OS_ASSERT(spaceTarget);
    auto groupSpace = spaceTarget->optionalCast<openstudio::epmodel::Space>();
    OS_ASSERT(groupSpace);
    if (*groupSpace != space) {
      continue;
    }
    if (!workspaceGroup->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space.handle())) {
      return false;
    }
    if (!workspaceGroup->setPointer(
          openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName,
          designSpecificationOutdoorAir.handle())) {
      return false;
    }
    return true;
  }

  // New entry path: set object pointers directly (pointer linkage is authoritative for
  // rename tracking and robust target resolution in canonicalized state).
  auto group = list.pushExtensibleGroup();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  OS_ASSERT(workspaceGroup);
  OS_ASSERT(workspaceGroup->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space.handle()));
  OS_ASSERT(workspaceGroup->setPointer(
    openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName,
    designSpecificationOutdoorAir.handle()));
  return true;
}

void DesignSpecificationOutdoorAirSpaceList_Impl::clearDesignSpecificationOutdoorAirEntries() {
  auto list = getObject<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
  while (list.numExtensibleGroups() > 0u) {
    list.eraseExtensibleGroup(0u);
  }
}

bool DesignSpecificationOutdoorAirSpaceList_Impl::removeSpace(const openstudio::epmodel::Space& space) {
  auto list = getObject<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
  std::vector<std::pair<openstudio::epmodel::Space, openstudio::epmodel::DesignSpecificationOutdoorAir>> remaining;
  remaining.reserve(list.numExtensibleGroups());

  bool removed = false;
  for (const auto& currentSpace : spaces()) {
    auto dsoa = designSpecificationOutdoorAir(currentSpace);
    OS_ASSERT(dsoa);
    if (currentSpace == space) {
      removed = true;
      continue;
    }
    remaining.emplace_back(currentSpace, *dsoa);
  }

  if (!removed) {
    return false;
  }

  clearDesignSpecificationOutdoorAirEntries();
  for (const auto& [currentSpace, dsoa] : remaining) {
    OS_ASSERT(setDesignSpecificationOutdoorAir(currentSpace, dsoa));
  }
  return true;
}

void DesignSpecificationOutdoorAirSpaceList_Impl::doCanonicalize(LoadContext& context) {
  auto list = getObject<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();

  // Canonical form for this list:
  // 1) each extensible group resolves to a concrete Space and DSOA object;
  // 2) the handle pointers are populated for both targets.
  // Invalid groups are removed here so downstream API code can rely on assertions.
  unsigned groupIndex = 0u;
  unsigned removedCount = 0u;
  for (auto& group : list.extensibleGroups()) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);

    bool removeGroup = false;

    auto spaceObject = workspaceGroup->getTarget(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName);
    auto dsoaObject = workspaceGroup->getTarget(
      openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName);

    auto space = spaceObject ? spaceObject->optionalCast<openstudio::epmodel::Space>() : boost::none;
    auto dsoa = dsoaObject ? dsoaObject->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAir>() : boost::none;

    if (!space) {
      removeGroup = true;
      detail::addLoadWarning(context, "DesignSpecification:OutdoorAir:SpaceList '" + list.nameString()
                                       + "' has an unresolved Space reference at extensible index " + std::to_string(groupIndex) + ".");
    }
    if (!dsoa) {
      removeGroup = true;
      detail::addLoadWarning(context, "DesignSpecification:OutdoorAir:SpaceList '" + list.nameString()
                                       + "' has an unresolved DSOA reference at extensible index " + std::to_string(groupIndex) + ".");
    }

    if (!removeGroup) {
      // Keep pointer fields authoritative in canonicalized state (not just names).
      OS_ASSERT(workspaceGroup->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space->handle()));
      OS_ASSERT(workspaceGroup->setPointer(
        openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName, dsoa->handle()));
      dsoa->getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAir_Impl>()->canonicalize(context);
    }

    if (removeGroup) {
      const unsigned eraseIndex = groupIndex - removedCount;
      list.eraseExtensibleGroup(eraseIndex);
      ++removedCount;
      detail::addLoadInfo(context, "Removed invalid DesignSpecification:OutdoorAir:SpaceList group at extensible index "
                                     + std::to_string(groupIndex) + " for '" + list.nameString() + "'.");
    }
    ++groupIndex;
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
