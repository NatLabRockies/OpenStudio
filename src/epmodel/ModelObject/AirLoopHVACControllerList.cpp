/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACControllerList.hpp"
#include "AirLoopHVACControllerList_Impl.hpp"

#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/core/Containers.hpp>
#include <utilities/idd/AirLoopHVAC_ControllerList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  AirLoopHVACControllerList::AirLoopHVACControllerList(const Model& model) : ModelObject(AirLoopHVACControllerList::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACControllerList_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACControllerList::AirLoopHVACControllerList(std::shared_ptr<detail::AirLoopHVACControllerList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACControllerList::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ControllerList;
  }

  std::vector<ModelObject> AirLoopHVACControllerList::controllers() const {
    return getImpl<detail::AirLoopHVACControllerList_Impl>()->controllers();
  }

  boost::optional<ControllerOutdoorAir> AirLoopHVACControllerList::optionalControllerOutdoorAir() const {
    return getImpl<detail::AirLoopHVACControllerList_Impl>()->optionalControllerOutdoorAir();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACControllerList_Impl::controllers() const {
      auto controllerList = getObject<openstudio::epmodel::AirLoopHVACControllerList>();
      std::vector<openstudio::epmodel::ModelObject> result;

      const auto groups = controllerList.extensibleGroups();
      result.reserve(groups.size());
      for (const auto& group : groups) {
        // Canonical relationship linkage is via pointer target on ControllerName.
        // We intentionally ignore string-only rows here; canonicalization repairs or
        // removes those rows before normal API traversal.
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerName);
        if (!target) {
          continue;
        }
        auto modelObject = target->optionalCast<openstudio::epmodel::ModelObject>();
        if (!modelObject) {
          continue;
        }
        result.push_back(*modelObject);
      }
      return result;
    }

    bool AirLoopHVACControllerList_Impl::addController(const openstudio::epmodel::ModelObject& controller) {
      auto controllerList = getObject<openstudio::epmodel::AirLoopHVACControllerList>();

      if (controller.model() != model()) {
        return false;
      }

      const auto existingControllers = controllers();
      if (std::ranges::any_of(existingControllers,
                              [&controller](const auto& existingController) { return existingController.handle() == controller.handle(); })) {
        return true;
      }

      auto group = controllerList.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      if (!workspaceGroup->setString(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerObjectType, controller.iddObject().name())) {
        return false;
      }
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerName, controller.handle());
    }

    bool AirLoopHVACControllerList_Impl::removeController(const openstudio::epmodel::ModelObject& controller) {
      auto controllerList = getObject<openstudio::epmodel::AirLoopHVACControllerList>();
      auto groups = controllerList.extensibleGroups();

      for (unsigned i = static_cast<unsigned>(groups.size()); i > 0u; --i) {
        const unsigned index = i - 1u;
        auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerName);
        if (!target) {
          continue;
        }
        if (target->handle() == controller.handle()) {
          controllerList.eraseExtensibleGroup(index);
          return true;
        }
      }
      return false;
    }

    boost::optional<openstudio::epmodel::ControllerOutdoorAir> AirLoopHVACControllerList_Impl::optionalControllerOutdoorAir() const {
      auto oaControllers = subsetCastVector<openstudio::epmodel::ControllerOutdoorAir>(controllers());
      if (!oaControllers.empty()) {
        return oaControllers.front();
      }
      return boost::none;
    }

    bool AirLoopHVACControllerList_Impl::setControllerOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir) {
      if (controllerOutdoorAir.model() != model()) {
        return false;
      }

      // Keep a single OA controller row by replacing any existing OA entry.
      // This mirrors OA-controller semantics while reusing generic add/remove APIs.
      if (auto existing = optionalControllerOutdoorAir()) {
        if (*existing == controllerOutdoorAir) {
          return true;
        }
        if (!removeController(existing->cast<openstudio::epmodel::ModelObject>())) {
          return false;
        }
      }

      return addController(controllerOutdoorAir.cast<openstudio::epmodel::ModelObject>());
    }

    void AirLoopHVACControllerList_Impl::doCanonicalize(LoadContext& context) {
      auto controllerList = getObject<openstudio::epmodel::AirLoopHVACControllerList>();

      unsigned groupIndex = 0u;
      while (groupIndex < controllerList.numExtensibleGroups()) {
        // Canonicalization treats ControllerList rows as an all-or-nothing record.
        // When we erase an invalid row, downstream rows shift left; holding a stale
        // snapshot can skip validation or overrun. Re-reading each iteration and
        // only incrementing for kept rows guarantees every remaining row is checked
        // exactly once.
        auto groups = controllerList.extensibleGroups();
        if (groupIndex >= groups.size()) {
          break;
        }
        auto group = groups[groupIndex];
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          controllerList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed invalid extensible group in AirLoopHVAC:ControllerList '" + controllerList.nameString() + "'.");
          continue;
        }

        auto objectType = group.getString(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerObjectType, true);
        auto controllerName = group.getString(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerName, true);
        if (!objectType || objectType->empty() || !controllerName || controllerName->empty()) {
          controllerList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed incomplete controller entry in AirLoopHVAC:ControllerList '" + controllerList.nameString() + "'.");
          continue;
        }

        openstudio::IddObjectType iddType = openstudio::IddObjectType::Catchall;
        try {
          iddType = openstudio::IddObjectType(*objectType);
        } catch (const std::runtime_error&) {  // NOLINT
          controllerList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed invalid controller object type '" + *objectType + "' in AirLoopHVAC:ControllerList '"
                                            + controllerList.nameString() + "'.");
          continue;
        }

        auto controllerObject = model().getObjectByTypeAndName(iddType, *controllerName, true);
        auto controller = controllerObject ? controllerObject->optionalCast<openstudio::epmodel::ModelObject>() : boost::none;
        if (!controller) {
          controllerList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed missing controller '" + *controllerName + "' (" + *objectType
                                            + ") from AirLoopHVAC:ControllerList '" + controllerList.nameString() + "'.");
          continue;
        }

        // Canonical postcondition: keep pointer linkage authoritative so downstream
        // rename tracking and typed target resolution are stable.
        OS_ASSERT(workspaceGroup->setPointer(openstudio::AirLoopHVAC_ControllerListExtensibleFields::ControllerName, controller->handle()));
        ++groupIndex;
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
