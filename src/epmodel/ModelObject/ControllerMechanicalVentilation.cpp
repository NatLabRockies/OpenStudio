/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ControllerMechanicalVentilation.hpp"
#include "ControllerMechanicalVentilation_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "DesignSpecificationOutdoorAirSpaceList.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

ControllerMechanicalVentilation::ControllerMechanicalVentilation(const Model& model)
  : ModelObject(ControllerMechanicalVentilation::iddObjectType(), model) {
  auto impl = getImpl<detail::ControllerMechanicalVentilation_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

ControllerMechanicalVentilation::ControllerMechanicalVentilation(std::shared_ptr<detail::ControllerMechanicalVentilation_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ControllerMechanicalVentilation::iddObjectType() {
  return IddObjectType::Controller_MechanicalVentilation;
}

std::vector<std::string> ControllerMechanicalVentilation::systemOutdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod);
}

bool ControllerMechanicalVentilation::demandControlledVentilation() const {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->demandControlledVentilation();
}

bool ControllerMechanicalVentilation::isDemandControlledVentilationDefaulted() const {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->isDemandControlledVentilationDefaulted();
}

bool ControllerMechanicalVentilation::setDemandControlledVentilation(bool value) {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->setDemandControlledVentilation(value);
}

void ControllerMechanicalVentilation::setDemandControlledVentilationNoFail(bool value) {
  const bool result = setDemandControlledVentilation(value);
  OS_ASSERT(result);
}

void ControllerMechanicalVentilation::resetDemandControlledVentilation() {
  getImpl<detail::ControllerMechanicalVentilation_Impl>()->resetDemandControlledVentilation();
}

std::string ControllerMechanicalVentilation::systemOutdoorAirMethod() const {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->systemOutdoorAirMethod();
}

bool ControllerMechanicalVentilation::isSystemOutdoorAirMethodDefaulted() const {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->isSystemOutdoorAirMethodDefaulted();
}

bool ControllerMechanicalVentilation::setSystemOutdoorAirMethod(const std::string& value) {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->setSystemOutdoorAirMethod(value);
}

void ControllerMechanicalVentilation::resetSystemOutdoorAirMethod() {
  getImpl<detail::ControllerMechanicalVentilation_Impl>()->resetSystemOutdoorAirMethod();
}

boost::optional<ControllerOutdoorAir> ControllerMechanicalVentilation::controllerOutdoorAir() const {
  return getImpl<detail::ControllerMechanicalVentilation_Impl>()->controllerOutdoorAir();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool ControllerMechanicalVentilation_Impl::demandControlledVentilation() const {
  if (auto value = getString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, true)) {
    return openstudio::istringEqual(*value, "Yes");
  }
  return false;
}

bool ControllerMechanicalVentilation_Impl::setDemandControlledVentilation(bool value) {
  return setString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, value ? "Yes" : "No");
}

bool ControllerMechanicalVentilation_Impl::isDemandControlledVentilationDefaulted() const {
  return isEmpty(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation);
}

void ControllerMechanicalVentilation_Impl::resetDemandControlledVentilation() {
  const bool result = setString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, "");
  OS_ASSERT(result);
}

std::string ControllerMechanicalVentilation_Impl::systemOutdoorAirMethod() const {
  if (auto value = getString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, true)) {
    if (!value->empty()) {
      return *value;
    }
  }
  return "Standard62.1VentilationRateProcedure";
}

bool ControllerMechanicalVentilation_Impl::setSystemOutdoorAirMethod(const std::string& value) {
  return setString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, value);
}

bool ControllerMechanicalVentilation_Impl::isSystemOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod);
}

void ControllerMechanicalVentilation_Impl::resetSystemOutdoorAirMethod() {
  const bool result = setString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, "");
  OS_ASSERT(result);
}

std::vector<std::string> ControllerMechanicalVentilation_Impl::systemOutdoorAirMethodValues() const {
  return openstudio::epmodel::ControllerMechanicalVentilation::systemOutdoorAirMethodValues();
}

boost::optional<openstudio::epmodel::ControllerOutdoorAir> ControllerMechanicalVentilation_Impl::controllerOutdoorAir() const {
  const auto thisController = getObject<openstudio::epmodel::ControllerMechanicalVentilation>();
  // There is no direct inverse pointer from CMV -> Controller:OutdoorAir in the
  // EnergyPlus schema, so this relationship is resolved by scanning OA
  // controllers for one that points at this CMV.
  // Use the impl-only optional lookup to avoid side effects from the public
  // ControllerOutdoorAir::controllerMechanicalVentilation() getter, which can
  // synthesize a CMV on demand.
  for (const auto& oaController : model().getConcreteModelObjects<openstudio::epmodel::ControllerOutdoorAir>()) {
    if (auto target = oaController.getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>()->optionalControllerMechanicalVentilation()) {
      if (*target == thisController) {
        return oaController;
      }
    }
  }
  return boost::none;
}

std::vector<std::pair<openstudio::epmodel::ThermalZone, openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>>
  ControllerMechanicalVentilation_Impl::zoneOutdoorAirEntries() const {
  std::vector<std::pair<openstudio::epmodel::ThermalZone, openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>> result;
  for (const auto& group : getObject<openstudio::epmodel::ControllerMechanicalVentilation>().extensibleGroups()) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (!workspaceGroup) {
      continue;
    }
    auto zoneTarget = workspaceGroup->getTarget(openstudio::Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName);
    auto dsoaTarget =
      workspaceGroup->getTarget(openstudio::Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
    if (!zoneTarget || !dsoaTarget) {
      continue;
    }
    auto zone = zoneTarget->optionalCast<openstudio::epmodel::ThermalZone>();
    auto dsoaSpaceList = dsoaTarget->optionalCast<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>();
    if (!zone || !dsoaSpaceList) {
      continue;
    }
    result.emplace_back(*zone, *dsoaSpaceList);
  }
  return result;
}

void ControllerMechanicalVentilation_Impl::clearZoneOutdoorAirEntries() {
  auto controller = getObject<openstudio::epmodel::ControllerMechanicalVentilation>();
  while (controller.numExtensibleGroups() > 0u) {
    controller.eraseExtensibleGroup(0u);
  }
}

bool ControllerMechanicalVentilation_Impl::addZoneOutdoorAirEntry(
  const openstudio::epmodel::ThermalZone& zone, const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& dsoaSpaceList) {
  auto controller = getObject<openstudio::epmodel::ControllerMechanicalVentilation>();
  auto group = controller.pushExtensibleGroup();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  OS_ASSERT(workspaceGroup);
  OS_ASSERT(group.setString(openstudio::Controller_MechanicalVentilationExtensibleFields::DesignSpecificationZoneAirDistributionObjectName, ""));
  OS_ASSERT(workspaceGroup->setPointer(openstudio::Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName, zone.handle()));
  OS_ASSERT(workspaceGroup->setPointer(openstudio::Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName,
                                       dsoaSpaceList.handle()));
  return true;
}

void ControllerMechanicalVentilation_Impl::doCanonicalize(LoadContext& context) {
  auto thisController = getObject<openstudio::epmodel::ControllerMechanicalVentilation>();

  if (!getString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, true)) {
    OS_ASSERT(setString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, "No"));
    detail::addLoadInfo(context, "Set default Demand Controlled Ventilation to 'No' for Controller:MechanicalVentilation '"
                                 + thisController.nameString() + "'.");
  }

  if (!getString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, true)) {
    OS_ASSERT(
      setString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, "Standard62.1VentilationRateProcedure"));
    detail::addLoadInfo(context, "Set default System Outdoor Air Method to 'Standard62.1VentilationRateProcedure' for "
                                 "Controller:MechanicalVentilation '"
                                   + thisController.nameString() + "'.");
  }

  // CMV canonicalization is intentionally local-only. OA-system canonicalization
  // owns served-zone DSOA derivation and CMV entry synchronization.
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
