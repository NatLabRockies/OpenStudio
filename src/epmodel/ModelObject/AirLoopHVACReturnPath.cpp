/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACReturnPath.hpp"
#include "AirLoopHVACReturnPath_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ReturnPath_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACReturnPath::AirLoopHVACReturnPath(const Model& model) : ModelObject(AirLoopHVACReturnPath::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACReturnPath_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACReturnPath::AirLoopHVACReturnPath(std::shared_ptr<detail::AirLoopHVACReturnPath_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACReturnPath::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ReturnPath;
  }

  boost::optional<openstudio::epmodel::AirLoopHVAC> AirLoopHVACReturnPath::airLoopHVAC() const {
    return getImpl<detail::AirLoopHVACReturnPath_Impl>()->airLoopHVAC();
  }

  std::vector<openstudio::epmodel::ModelObject> AirLoopHVACReturnPath::components() const {
    return getImpl<detail::AirLoopHVACReturnPath_Impl>()->components();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::AirLoopHVAC> AirLoopHVACReturnPath_Impl::airLoopHVAC() const {
      auto outletNode = returnAirPathOutletNode();
      if (!outletNode) {
        return boost::none;
      }

      const auto airLoops = model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>();
      const auto it = std::ranges::find_if(airLoops, [&](const openstudio::epmodel::AirLoopHVAC& airLoop) {
        if (auto demandOutlet = airLoop.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::AirLoopHVACFields::DemandSideOutletNodeName)) {
          return *demandOutlet == *outletNode;
        }
        return false;
      });
      if (it != airLoops.end()) {
        return *it;
      }

      return boost::none;
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACReturnPath_Impl::components() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      for (const auto& group : extensibleGroups()) {
        const auto componentName = group.getString(openstudio::AirLoopHVAC_ReturnPathExtensibleFields::ComponentName);
        if (!componentName || componentName->empty()) {
          continue;
        }

        const auto componentType = group.getString(openstudio::AirLoopHVAC_ReturnPathExtensibleFields::ComponentObjectType).value_or("");
        if (componentType.empty()) {
          OS_ASSERT(false);
          continue;
        }

        try {
          auto iddType = openstudio::IddObjectType(componentType);
          if (auto wo = model().getObjectByTypeAndName(iddType, *componentName)) {
            if (auto object = wo->optionalCast<openstudio::epmodel::ModelObject>()) {
              result.push_back(*object);
            } else {
              OS_ASSERT(false);
              continue;
            }
          } else {
            OS_ASSERT(false);
            continue;
          }
        } catch (...) {  // NOLINT
          OS_ASSERT(false);
          continue;
        }
      }

      return result;
    }

    bool AirLoopHVACReturnPath_Impl::addComponent(const openstudio::epmodel::ModelObject& component) {
      auto returnPath = getObject<openstudio::epmodel::AirLoopHVACReturnPath>();
      if (component.model() != returnPath.model()) {
        return false;
      }
      if (!component.name() || component.name()->empty()) {
        return false;
      }

      for (const auto& existing : components()) {
        if (existing == component) {
          return true;
        }
      }

      auto group = returnPath.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      if (!workspaceGroup->setString(openstudio::AirLoopHVAC_ReturnPathExtensibleFields::ComponentObjectType, component.iddObject().name())) {
        return false;
      }
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ReturnPathExtensibleFields::ComponentName, component.handle());
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACReturnPath_Impl::returnAirPathOutletNode() const {
      return getObject<openstudio::epmodel::AirLoopHVACReturnPath>()
        .getImpl<openstudio::epmodel::detail::AirLoopHVACReturnPath_Impl>()
        ->resolvedNodeTarget(openstudio::AirLoopHVAC_ReturnPathFields::ReturnAirPathOutletNodeName);
    }

    bool AirLoopHVACReturnPath_Impl::setReturnAirPathOutletNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::AirLoopHVAC_ReturnPathFields::ReturnAirPathOutletNodeName, node.handle(), false);
    }

    void AirLoopHVACReturnPath_Impl::doCanonicalize(LoadContext& context) {
      auto outletNode = returnAirPathOutletNode();
      if (!outletNode) {
        return;
      }

      // Canonical goal: each extensible row must resolve to a real component.
      // Invalid rows are removed so const traversal code can assume the return
      // path list is executable without fallback string-resolution branches.
      auto returnPath = getObject<openstudio::epmodel::AirLoopHVACReturnPath>();
      unsigned groupIndex = 0u;
      while (groupIndex < returnPath.numExtensibleGroups()) {
        auto groups = returnPath.extensibleGroups();
        if (groupIndex >= groups.size()) {
          break;
        }
        const auto& group = groups[groupIndex];

        const auto componentType = group.getString(openstudio::AirLoopHVAC_ReturnPathExtensibleFields::ComponentObjectType);
        const auto componentName = group.getString(openstudio::AirLoopHVAC_ReturnPathExtensibleFields::ComponentName);

        bool valid = componentType && !componentType->empty() && componentName && !componentName->empty();
        openstudio::IddObjectType componentIddType = openstudio::IddObjectType::Catchall;
        if (valid) {
          try {
            componentIddType = openstudio::IddObjectType(*componentType);
          } catch (...) {
            valid = false;
          }
        }
        if (valid && !model().getObjectByTypeAndName(componentIddType, *componentName)) {
          valid = false;
        }

        if (!valid) {
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVACReturnPath",
                   "Removing invalid ReturnPath component group on '" << returnPath.nameString() << "'.");
          returnPath.eraseExtensibleGroup(groupIndex);
          continue;
        }

        ++groupIndex;
      }

      // ReturnPath <-> ZoneMixer association is node-driven in E+ representation.
      // Re-establish that association here so demand-side traversal has a stable
      // anchor object.
      boost::optional<openstudio::epmodel::AirLoopHVACZoneMixer> zoneMixer;
      for (const auto& mixer : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACZoneMixer>()) {
        if (auto mixerOutlet = mixer.getImpl<openstudio::epmodel::detail::AirLoopHVACZoneMixer_Impl>()->outletNode()) {
          if (*mixerOutlet == *outletNode) {
            zoneMixer = mixer;
            break;
          }
        }
      }

      if (!zoneMixer) {
        LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVACReturnPath",
                 "No AirLoopHVAC:ZoneMixer found for ReturnPath '" << returnPath.nameString()
                                                                   << "' via Return Air Path Outlet Node association. This is likely problematic, "
                                                                      "and no repair was applied.");
      }

      // Once linked, keep the mixer explicitly listed on ReturnPath components so
      // callers can reason from a single path source of truth.
      if (zoneMixer) {
        const auto components = returnPath.components();
        const bool listed = std::ranges::any_of(components, [&](const auto& component) { return component == *zoneMixer; });

        if (!listed) {
          if (addComponent(*zoneMixer)) {
            detail::addLoadInfo(context, "Added missing AirLoopHVAC:ZoneMixer '" + zoneMixer->nameString() + "' to ReturnPath '"
                                           + returnPath.nameString() + "'.");
          } else {
            detail::addLoadWarning(context, "Failed to add missing AirLoopHVAC:ZoneMixer '" + zoneMixer->nameString() + "' to ReturnPath '"
                                              + returnPath.nameString() + "'.");
          }
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
