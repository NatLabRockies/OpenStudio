/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"

#include "Model.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "Space.hpp"
#include "Space_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DesignSpecification_ZoneAirDistribution_FieldEnums.hxx>
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

double SizingZone::designZoneAirDistributionEffectivenessinCoolingMode() const {
  return getImpl<detail::SizingZone_Impl>()->designZoneAirDistributionEffectivenessinCoolingMode();
}

bool SizingZone::isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const {
  return getImpl<detail::SizingZone_Impl>()->isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted();
}

double SizingZone::designZoneAirDistributionEffectivenessinHeatingMode() const {
  return getImpl<detail::SizingZone_Impl>()->designZoneAirDistributionEffectivenessinHeatingMode();
}

bool SizingZone::isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const {
  return getImpl<detail::SizingZone_Impl>()->isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted();
}

double SizingZone::designZoneSecondaryRecirculationFraction() const {
  return getImpl<detail::SizingZone_Impl>()->designZoneSecondaryRecirculationFraction();
}

bool SizingZone::isDesignZoneSecondaryRecirculationFractionDefaulted() const {
  return getImpl<detail::SizingZone_Impl>()->isDesignZoneSecondaryRecirculationFractionDefaulted();
}

double SizingZone::designMinimumZoneVentilationEfficiency() const {
  return getImpl<detail::SizingZone_Impl>()->designMinimumZoneVentilationEfficiency();
}

bool SizingZone::isDesignMinimumZoneVentilationEfficiencyDefaulted() const {
  return getImpl<detail::SizingZone_Impl>()->isDesignMinimumZoneVentilationEfficiencyDefaulted();
}

bool SizingZone::setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode) {
  return getImpl<detail::SizingZone_Impl>()->setDesignZoneAirDistributionEffectivenessinCoolingMode(
    designZoneAirDistributionEffectivenessinCoolingMode);
}

void SizingZone::resetDesignZoneAirDistributionEffectivenessinCoolingMode() {
  getImpl<detail::SizingZone_Impl>()->resetDesignZoneAirDistributionEffectivenessinCoolingMode();
}

bool SizingZone::setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode) {
  return getImpl<detail::SizingZone_Impl>()->setDesignZoneAirDistributionEffectivenessinHeatingMode(
    designZoneAirDistributionEffectivenessinHeatingMode);
}

void SizingZone::resetDesignZoneAirDistributionEffectivenessinHeatingMode() {
  getImpl<detail::SizingZone_Impl>()->resetDesignZoneAirDistributionEffectivenessinHeatingMode();
}

bool SizingZone::setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction) {
  return getImpl<detail::SizingZone_Impl>()->setDesignZoneSecondaryRecirculationFraction(designZoneSecondaryRecirculationFraction);
}

void SizingZone::resetDesignZoneSecondaryRecirculationFraction() {
  getImpl<detail::SizingZone_Impl>()->resetDesignZoneSecondaryRecirculationFraction();
}

bool SizingZone::setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency) {
  return getImpl<detail::SizingZone_Impl>()->setDesignMinimumZoneVentilationEfficiency(designMinimumZoneVentilationEfficiency);
}

void SizingZone::resetDesignMinimumZoneVentilationEfficiency() {
  getImpl<detail::SizingZone_Impl>()->resetDesignMinimumZoneVentilationEfficiency();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

constexpr double kDefaultDesignZoneAirDistributionEffectivenessinCoolingMode = 1.0;
constexpr double kDefaultDesignZoneAirDistributionEffectivenessinHeatingMode = 1.0;
constexpr double kDefaultDesignZoneSecondaryRecirculationFraction = 0.0;
constexpr double kDefaultDesignMinimumZoneVentilationEfficiency = 0.0;

}  // namespace

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

boost::optional<openstudio::epmodel::ModelObject> SizingZone_Impl::designSpecificationZoneAirDistribution() const {
  if (auto result = getObject<openstudio::epmodel::SizingZone>().getModelObjectTarget<openstudio::epmodel::ModelObject>(
        openstudio::Sizing_ZoneFields::DesignSpecificationZoneAirDistributionObjectName)) {
    if (result->iddObject().type() == openstudio::IddObjectType::DesignSpecification_ZoneAirDistribution) {
      return result;
    }
  }
  return boost::none;
}

boost::optional<openstudio::epmodel::ModelObject> SizingZone_Impl::getOrCreateDesignSpecificationZoneAirDistribution() {
  if (auto existing = designSpecificationZoneAirDistribution()) {
    return existing;
  }

  auto designSpecificationZoneAirDistribution =
    openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::DesignSpecification_ZoneAirDistribution, model(), true);

  if (auto zone = optionalThermalZone()) {
    (void)designSpecificationZoneAirDistribution.setName(zone->nameString() + " Design Spec Zone Air Dist");
  }

  if (!setPointer(openstudio::Sizing_ZoneFields::DesignSpecificationZoneAirDistributionObjectName,
                  designSpecificationZoneAirDistribution.handle(), false)) {
    return boost::none;
  }
  return designSpecificationZoneAirDistribution;
}

double SizingZone_Impl::designZoneAirDistributionEffectivenessinCoolingMode() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    if (auto value = designSpecification->getDouble(
          openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode, false)) {
      return *value;
    }
  }
  return kDefaultDesignZoneAirDistributionEffectivenessinCoolingMode;
}

bool SizingZone_Impl::isDesignZoneAirDistributionEffectivenessinCoolingModeDefaulted() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    return !designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode,
                                           false);
  }
  return true;
}

double SizingZone_Impl::designZoneAirDistributionEffectivenessinHeatingMode() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    if (auto value = designSpecification->getDouble(
          openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode, false)) {
      return *value;
    }
  }
  return kDefaultDesignZoneAirDistributionEffectivenessinHeatingMode;
}

bool SizingZone_Impl::isDesignZoneAirDistributionEffectivenessinHeatingModeDefaulted() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    return !designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode,
                                           false);
  }
  return true;
}

double SizingZone_Impl::designZoneSecondaryRecirculationFraction() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    if (auto value = designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction,
                                                    false)) {
      return *value;
    }
  }
  return kDefaultDesignZoneSecondaryRecirculationFraction;
}

bool SizingZone_Impl::isDesignZoneSecondaryRecirculationFractionDefaulted() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    return !designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction, false);
  }
  return true;
}

double SizingZone_Impl::designMinimumZoneVentilationEfficiency() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    if (auto value = designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency,
                                                    false)) {
      return *value;
    }
  }
  return kDefaultDesignMinimumZoneVentilationEfficiency;
}

bool SizingZone_Impl::isDesignMinimumZoneVentilationEfficiencyDefaulted() const {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    return !designSpecification->getDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency, false);
  }
  return true;
}

bool SizingZone_Impl::setDesignZoneAirDistributionEffectivenessinCoolingMode(double designZoneAirDistributionEffectivenessinCoolingMode) {
  auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
  if (!designSpecification) {
    return false;
  }
  return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode,
                                        designZoneAirDistributionEffectivenessinCoolingMode);
}

void SizingZone_Impl::resetDesignZoneAirDistributionEffectivenessinCoolingMode() {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    bool result = designSpecification->setString(
      openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinCoolingMode, "");
    OS_ASSERT(result);
  }
}

bool SizingZone_Impl::setDesignZoneAirDistributionEffectivenessinHeatingMode(double designZoneAirDistributionEffectivenessinHeatingMode) {
  auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
  if (!designSpecification) {
    return false;
  }
  return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode,
                                        designZoneAirDistributionEffectivenessinHeatingMode);
}

void SizingZone_Impl::resetDesignZoneAirDistributionEffectivenessinHeatingMode() {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    bool result = designSpecification->setString(
      openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneAirDistributionEffectivenessinHeatingMode, "");
    OS_ASSERT(result);
  }
}

bool SizingZone_Impl::setDesignZoneSecondaryRecirculationFraction(double designZoneSecondaryRecirculationFraction) {
  auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
  if (!designSpecification) {
    return false;
  }
  return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction,
                                        designZoneSecondaryRecirculationFraction);
}

void SizingZone_Impl::resetDesignZoneSecondaryRecirculationFraction() {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    bool result = designSpecification->setString(openstudio::DesignSpecification_ZoneAirDistributionFields::ZoneSecondaryRecirculationFraction, "");
    OS_ASSERT(result);
  }
}

bool SizingZone_Impl::setDesignMinimumZoneVentilationEfficiency(double designMinimumZoneVentilationEfficiency) {
  auto designSpecification = getOrCreateDesignSpecificationZoneAirDistribution();
  if (!designSpecification) {
    return false;
  }
  return designSpecification->setDouble(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency,
                                        designMinimumZoneVentilationEfficiency);
}

void SizingZone_Impl::resetDesignMinimumZoneVentilationEfficiency() {
  if (auto designSpecification = designSpecificationZoneAirDistribution()) {
    bool result = designSpecification->setString(openstudio::DesignSpecification_ZoneAirDistributionFields::MinimumZoneVentilationEfficiency, "");
    OS_ASSERT(result);
  }
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
