/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ControllerOutdoorAir.hpp"
#include "ControllerOutdoorAir_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "AirLoopHVACControllerList.hpp"
#include "AirLoopHVACControllerList_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ControllerMechanicalVentilation.hpp"
#include "ControllerMechanicalVentilation_Impl.hpp"
#include "Model.hpp"
#include "SizingZone.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ControllerOutdoorAir::ControllerOutdoorAir(const Model& model) : ParentObject(ControllerOutdoorAir::iddObjectType(), model) {
    auto impl = getImpl<detail::ControllerOutdoorAir_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ControllerOutdoorAir::ControllerOutdoorAir(std::shared_ptr<detail::ControllerOutdoorAir_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType ControllerOutdoorAir::iddObjectType() {
    return IddObjectType::Controller_OutdoorAir;
  }

  ControllerMechanicalVentilation ControllerOutdoorAir::controllerMechanicalVentilation() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->controllerMechanicalVentilation();
  }

  bool ControllerOutdoorAir::setControllerMechanicalVentilation(const ControllerMechanicalVentilation& controllerMechanicalVentilation) {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->setControllerMechanicalVentilation(controllerMechanicalVentilation);
  }

  boost::optional<AirLoopHVACOutdoorAirSystem> ControllerOutdoorAir::airLoopHVACOutdoorAirSystem() const {
    return getImpl<detail::ControllerOutdoorAir_Impl>()->airLoopHVACOutdoorAirSystem();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> findOwningOutdoorAirSystemForCanonicalize(
        const openstudio::epmodel::ControllerOutdoorAir& controller) {
        for (const auto& oaSystem : controller.model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
          // Canonicalization path may run before OA-system invariants are fully
          // established on every instance, so use a tolerant lookup here.
          auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
            openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
          if (!controllerList) {
            continue;
          }
          auto oaController = controllerList->optionalControllerOutdoorAir();
          if (oaController && (*oaController == controller)) {
            return oaSystem;
          }
        }
        return boost::none;
      }

      bool hasServedZoneWithDesignSpecificationOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controller, LoadContext& context) {
        auto oaSystem = findOwningOutdoorAirSystemForCanonicalize(controller);
        if (!oaSystem) {
          return false;
        }

        for (const auto& zone : controller.model().getConcreteModelObjects<openstudio::epmodel::ThermalZone>()) {
          zone.getImpl<openstudio::epmodel::detail::ThermalZone_Impl>()->canonicalize(context);

          auto sizingZone = zone.sizingZone();
          if (sizingZone.getModelObjectTarget<openstudio::epmodel::ModelObject>(
                openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName)) {
            return true;
          }
        }

        return false;
      }

    }  // namespace

    boost::optional<openstudio::epmodel::ControllerMechanicalVentilation> ControllerOutdoorAir_Impl::optionalControllerMechanicalVentilation() const {
      return getObject<openstudio::epmodel::ControllerOutdoorAir>().getModelObjectTarget<openstudio::epmodel::ControllerMechanicalVentilation>(
        openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName);
    }

    openstudio::epmodel::ControllerMechanicalVentilation ControllerOutdoorAir_Impl::controllerMechanicalVentilation() const {
      if (auto result = optionalControllerMechanicalVentilation()) {
        return *result;
      }

      // Design pattern for epmodel parity:
      // - Canonicalize may synthesize Controller:MechanicalVentilation only when domain requirements warrant it
      //   (eg, zone OA specs that need mechanical ventilation behavior).
      // - This getter remains non-throwing for API parity and creates on demand when missing.
      auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      auto newController = openstudio::epmodel::ControllerMechanicalVentilation(model());
      OS_ASSERT(thisController.setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName, newController.handle()));
      return newController;
    }

    bool ControllerOutdoorAir_Impl::setControllerMechanicalVentilation(
      const openstudio::epmodel::ControllerMechanicalVentilation& controllerMechanicalVentilation) {
      const bool result = setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName,
                                     controllerMechanicalVentilation.handle(), false);
      if (result) {
        if (auto oaSystem = airLoopHVACOutdoorAirSystem()) {
          if (auto airLoop = oaSystem->airLoopHVAC()) {
            airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
          }
        }
      }
      return result;
    }

    boost::optional<openstudio::epmodel::AirLoopHVACOutdoorAirSystem> ControllerOutdoorAir_Impl::airLoopHVACOutdoorAirSystem() const {
      const auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      for (const auto& oaSystem : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
        // This accessor is used by canonicalization flows (eg CMV rebuild),
        // where other OA systems in the same model may not yet satisfy
        // getControllerOutdoorAir() invariants. Use tolerant relationship
        // lookup here to avoid cross-object canonicalization ordering asserts.
        auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
          openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
        if (!controllerList) {
          continue;
        }
        auto controller = controllerList->optionalControllerOutdoorAir();
        if (controller && (*controller == thisController)) {
          return oaSystem;
        }
      }
      return boost::none;
    }

    void ControllerOutdoorAir_Impl::doCanonicalize(LoadContext& context) {
      auto thisController = getObject<openstudio::epmodel::ControllerOutdoorAir>();
      auto target = optionalControllerMechanicalVentilation();

      if (!target && hasServedZoneWithDesignSpecificationOutdoorAir(thisController, context)) {
        auto newController = openstudio::epmodel::ControllerMechanicalVentilation(model());
        OS_ASSERT(thisController.setPointer(openstudio::Controller_OutdoorAirFields::MechanicalVentilationControllerName, newController.handle()));
        target = newController;
        detail::addLoadInfo(context, "Created Controller:MechanicalVentilation '" + newController.nameString() + "' for Controller:OutdoorAir '"
                                       + thisController.nameString() + "' because DesignSpecification:OutdoorAir assignments exist in the model.");
      }

      // Canonical OA policy:
      // - If zone OA assignments exist in the model, CMV is synthesized/maintained at canonicalization.
      // - Otherwise CMV is optional and may still be created on-demand by getter API.
      if (target) {
        target->getImpl<openstudio::epmodel::detail::ControllerMechanicalVentilation_Impl>()->canonicalize(context);
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
