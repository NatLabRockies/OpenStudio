/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"

#include "Model.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"
#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "Space.hpp"
#include "Space_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SizingZone::SizingZone(const Model& model, const ThermalZone& thermalZone) : ModelObject(SizingZone::iddObjectType(), model) {
  auto impl = getImpl<detail::SizingZone_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(impl->setPointer(openstudio::Sizing_ZoneFields::ZoneorZoneListName, thermalZone.handle(), false));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SizingZone::SizingZone(std::shared_ptr<detail::SizingZone_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType SizingZone::iddObjectType() {
  return IddObjectType::Sizing_Zone;
}

ThermalZone SizingZone::thermalZone() const {
  return getImpl<detail::SizingZone_Impl>()->thermalZone();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<openstudio::epmodel::ThermalZone> SizingZone_Impl::optionalThermalZone() const {
  return getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(
    openstudio::Sizing_ZoneFields::ZoneorZoneListName);
}

openstudio::epmodel::ThermalZone SizingZone_Impl::thermalZone() const {
  auto result = optionalThermalZone();
  OS_ASSERT(result);
  return *result;
}

boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> SizingZone_Impl::designSpecificationOutdoorAirSpaceList() const {
  if (auto result = getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
        openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName)) {
    return result->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
  }
  return boost::none;
}

bool SizingZone_Impl::setDesignSpecificationOutdoorAirSpaceList(
  const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& designSpecificationOutdoorAirSpaceList) {
  return setPointer(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName, designSpecificationOutdoorAirSpaceList.handle(),
                    false);
}

void SizingZone_Impl::doCanonicalize(LoadContext& context) {
  auto thisSizingZone = getObject<openstudio::epmodel::SizingZone>();
  auto zoneOrZoneListTarget = thisSizingZone.getModelObjectTarget<openstudio::epmodel::ModelObject>(
    openstudio::Sizing_ZoneFields::ZoneorZoneListName);
  auto zone = optionalThermalZone();
  if (!zone) {
    if (zoneOrZoneListTarget) {
      detail::addLoadWarning(
        context, "Sizing:Zone '" + thisSizingZone.nameString()
                   + "' references a non-ThermalZone target for Zone or ZoneList Name. ZoneList normalization is not yet implemented.");
    }
    return;
  }
  // Canonical prerequisite: zone-level OA normalization depends on Space -> ThermalZone links.
  // We canonicalize the owning ThermalZone first so downstream lookups are stable.
  zone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>()->canonicalize(context);

  boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> directDSOA;
  if (auto dsoaObject = getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
        openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName)) {
    directDSOA = dsoaObject->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAir>();
  }
  auto sourceSpaceList = designSpecificationOutdoorAirSpaceList();
  if (!directDSOA && !sourceSpaceList) {
    return;
  }

  std::vector<openstudio::epmodel::Space> zoneSpaces;
  for (const auto& space : model().getConcreteModelObjects<openstudio::epmodel::Space>()) {
    auto spaceZone = space.thermalZone();
    if (spaceZone && (*spaceZone == *zone)) {
      zoneSpaces.push_back(space);
    }
  }
  if (zoneSpaces.empty()) {
    return;
  }

  // Canonical OA representation in epmodel:
  // If a zone has spaces and any zone OA assignment exists, represent it as
  // DesignSpecification:OutdoorAir:SpaceList (one extensible assignment per Space).
  //
  // We intentionally do not branch on "all spaces share the same DSOA".
  // A single representation avoids API/behavior divergence and keeps getter
  // semantics deterministic after canonicalization.
  std::vector<std::pair<openstudio::epmodel::Space, boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir>>> assignments;
  assignments.reserve(zoneSpaces.size());
  for (const auto& space : zoneSpaces) {
    auto assignedDSOA = sourceSpaceList ? sourceSpaceList->designSpecificationOutdoorAir(space) : boost::none;
    if (!assignedDSOA && directDSOA) {
      assignedDSOA = directDSOA;
    }
    assignments.emplace_back(space, assignedDSOA);
  }

  const auto canonicalSpaceListName = zone->nameString() + " DSOA Space List";
  boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> canonicalSpaceList = sourceSpaceList;
  if (!canonicalSpaceList) {
    canonicalSpaceList = model().getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(canonicalSpaceListName);
  }
  if (!canonicalSpaceList) {
    canonicalSpaceList = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(model());
    canonicalSpaceList->setName(canonicalSpaceListName);
    detail::addLoadInfo(context, "Created DesignSpecification:OutdoorAir:SpaceList '" + canonicalSpaceList->nameString()
                                   + "' for Sizing:Zone '" + thisSizingZone.nameString() + "'.");
  }
  OS_ASSERT(canonicalSpaceList);

  while (canonicalSpaceList->numExtensibleGroups() > 0u) {
    canonicalSpaceList->eraseExtensibleGroup(0u);
  }

  // Rebuild groups from current zone-space membership and resolved assignments.
  // Rebuild (instead of patching) keeps canonicalization idempotent and eliminates
  // stale groups for spaces that moved across zones.
  bool populatedAny = false;
  for (const auto& [space, assignedDSOA] : assignments) {
    if (!assignedDSOA) {
      continue;
    }
    OS_ASSERT(canonicalSpaceList->getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()
                ->setDesignSpecificationOutdoorAir(space, *assignedDSOA));
    populatedAny = true;
  }

  if (!populatedAny) {
    return;
  }

  // Canonical postcondition: Sizing:Zone points at the canonical SpaceList object.
  // Direct DSOA on Sizing:Zone remains non-canonical and is normalized away here.
  if (setDesignSpecificationOutdoorAirSpaceList(*canonicalSpaceList)) {
    if (directDSOA) {
      detail::addLoadInfo(context, "Normalized Sizing:Zone '" + thisSizingZone.nameString()
                                   + "' OA reference to DesignSpecification:OutdoorAir:SpaceList '" + canonicalSpaceList->nameString() + "'.");
    }
    canonicalSpaceList->getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->canonicalize(context);
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
