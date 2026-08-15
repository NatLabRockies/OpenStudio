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
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <ranges>

namespace openstudio {
namespace epmodel {

  ControllerMechanicalVentilation::ControllerMechanicalVentilation(const Model& model)
    : ModelObject(ControllerMechanicalVentilation::iddObjectType(), model) {
    auto impl = getImpl<detail::ControllerMechanicalVentilation_Impl>();
    OS_ASSERT(impl);
    auto schedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(impl->setAvailabilitySchedule(schedule));
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

  Schedule ControllerMechanicalVentilation::availabilitySchedule() const {
    return getImpl<detail::ControllerMechanicalVentilation_Impl>()->availabilitySchedule();
  }

  bool ControllerMechanicalVentilation::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ControllerMechanicalVentilation_Impl>()->setAvailabilitySchedule(schedule);
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

    ControllerMechanicalVentilation_Impl::OutdoorAirClaimFieldObservation
      ControllerMechanicalVentilation_Impl::observeOutdoorAirClaimField(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir) {
      OutdoorAirClaimFieldObservation result;
      constexpr unsigned field = openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName;
      const auto workspaceImpl = controllerOutdoorAir.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(workspaceImpl);
      result.rawTarget = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);

      const auto managedTarget = controllerOutdoorAir.getTarget(field);
      if (managedTarget) {
        result.managedTargetHandle = managedTarget->handle();
      }
      result.hasEvidence = managedTarget || (result.rawTarget && !result.rawTarget->empty());

      const auto mechanicalVentilation =
        managedTarget ? managedTarget->optionalCast<openstudio::epmodel::ControllerMechanicalVentilation>() : boost::none;
      if (!mechanicalVentilation) {
        return result;
      }

      const auto targetName = mechanicalVentilation->name();
      const bool uniqueName =
        targetName && !targetName->empty()
        && std::ranges::count_if(controllerOutdoorAir.model().getConcreteModelObjects<openstudio::epmodel::ControllerMechanicalVentilation>(),
                                 [&mechanicalVentilation, &targetName](const auto& candidate) {
                                   const auto candidateName = candidate.name();
                                   return candidateName && openstudio::istringEqual(*candidateName, *targetName)
                                          && candidate.handle() != mechanicalVentilation->handle();
                                 })
             == 0;
      // A hydrated Workspace relationship stores its identity in the managed pointer.
      // Non-empty backing text alongside that pointer is conflicting persisted evidence.
      result.canonical = uniqueName && (!result.rawTarget || result.rawTarget->empty());
      return result;
    }

    bool ControllerMechanicalVentilation_Impl::clearOutdoorAirClaimField(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir) {
      constexpr unsigned field = openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName;
      const auto workspaceImpl = controllerOutdoorAir.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(workspaceImpl);
      return workspaceImpl->setPointer(field, Handle(), false) && workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false);
    }

    ControllerMechanicalVentilation_Impl::OutdoorAirClaimInspection ControllerMechanicalVentilation_Impl::outdoorAirClaimInspection() const {
      OutdoorAirClaimInspection result;
      const auto thisController = getObject<openstudio::epmodel::ControllerMechanicalVentilation>();
      const auto thisName = thisController.name();

      for (const auto& oaController : model().getConcreteModelObjects<openstudio::epmodel::ControllerOutdoorAir>()) {
        const auto observation = observeOutdoorAirClaimField(oaController);
        const bool managedClaim = observation.managedTargetHandle && *observation.managedTargetHandle == thisController.handle();
        const bool rawClaim = observation.rawTarget && !observation.rawTarget->empty()
                              && (openstudio::toUUID(*observation.rawTarget) == thisController.handle()
                                  || (thisName && openstudio::istringEqual(*observation.rawTarget, *thisName)));
        if (managedClaim && observation.canonical) {
          result.canonicalClaimantHandles.push_back(oaController.handle());
        } else if (managedClaim || rawClaim) {
          result.hasMalformedClaim = true;
          result.malformedClaimantHandles.push_back(oaController.handle());
        }
      }

      std::ranges::sort(result.canonicalClaimantHandles);
      std::ranges::sort(result.malformedClaimantHandles);
      return result;
    }

    boost::optional<openstudio::epmodel::ControllerOutdoorAir> ControllerMechanicalVentilation_Impl::controllerOutdoorAir() const {
      const auto claims = outdoorAirClaimInspection();
      if (claims.hasMalformedClaim || claims.canonicalClaimantHandles.size() != 1u) {
        return boost::none;
      }
      return model().getModelObject<openstudio::epmodel::ControllerOutdoorAir>(claims.canonicalClaimantHandles.front());
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

    Schedule ControllerMechanicalVentilation_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Controller_MechanicalVentilationFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool ControllerMechanicalVentilation_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Controller_MechanicalVentilationFields::AvailabilityScheduleName,
                                           "ControllerMechanicalVentilation", "Availability Schedule", schedule);
    }

    bool
      ControllerMechanicalVentilation_Impl::addZoneOutdoorAirEntry(const openstudio::epmodel::ThermalZone& zone,
                                                                   const openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList& dsoaSpaceList) {
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

      ModelObject_Impl::doCanonicalize(context);

      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Controller_MechanicalVentilationFields::AvailabilityScheduleName);
      if (!(schedule && setAvailabilitySchedule(*schedule))) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        OS_ASSERT(setAvailabilitySchedule(alwaysOn));
        detail::addLoadInfo(context, "Attached the always-on schedule to mechanical ventilation controller '" + thisController.nameString() + "'.");
      }

      if (!getString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, true)) {
        OS_ASSERT(setString(openstudio::Controller_MechanicalVentilationFields::DemandControlledVentilation, "No"));
        detail::addLoadInfo(context, "Set default Demand Controlled Ventilation to 'No' for Controller:MechanicalVentilation '"
                                       + thisController.nameString() + "'.");
      }

      if (!getString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, true)) {
        OS_ASSERT(setString(openstudio::Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, "Standard62.1VentilationRateProcedure"));
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
