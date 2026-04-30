/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACSupplyPath.hpp"
#include "AirLoopHVACSupplyPath_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirLoopHVAC_SupplyPath_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACSupplyPath::AirLoopHVACSupplyPath(const Model& model) : ModelObject(AirLoopHVACSupplyPath::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACSupplyPath_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACSupplyPath::AirLoopHVACSupplyPath(std::shared_ptr<detail::AirLoopHVACSupplyPath_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACSupplyPath::iddObjectType() {
    return IddObjectType::AirLoopHVAC_SupplyPath;
  }

  boost::optional<openstudio::epmodel::AirLoopHVAC> AirLoopHVACSupplyPath::airLoopHVAC() const {
    return getImpl<detail::AirLoopHVACSupplyPath_Impl>()->airLoopHVAC();
  }

  std::vector<openstudio::epmodel::ModelObject> AirLoopHVACSupplyPath::components() const {
    return getImpl<detail::AirLoopHVACSupplyPath_Impl>()->components();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::AirLoopHVAC> AirLoopHVACSupplyPath_Impl::airLoopHVAC() const {
      auto inletNode = supplyAirPathInletNode();
      if (!inletNode) {
        return boost::none;
      }

      const auto airLoops = model().getModelObjects<openstudio::epmodel::AirLoopHVAC>();
      const auto it = std::ranges::find_if(airLoops, [&](const openstudio::epmodel::AirLoopHVAC& airLoop) {
        const auto demandInlets = airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->demandInletNodes();
        return std::ranges::find(demandInlets, *inletNode) != demandInlets.end();
      });
      if (it != airLoops.end()) {
        return *it;
      }

      return boost::none;
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACSupplyPath_Impl::components() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      for (const auto& group : extensibleGroups()) {
        const auto componentName = group.getString(openstudio::AirLoopHVAC_SupplyPathExtensibleFields::ComponentName);
        if (!componentName || componentName->empty()) {
          continue;
        }

        const auto componentType = group.getString(openstudio::AirLoopHVAC_SupplyPathExtensibleFields::ComponentObjectType).value_or("");
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

    bool AirLoopHVACSupplyPath_Impl::addComponent(const openstudio::epmodel::ModelObject& component) {
      auto supplyPath = getObject<openstudio::epmodel::AirLoopHVACSupplyPath>();
      if (component.model() != supplyPath.model()) {
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

      auto group = supplyPath.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      if (!workspaceGroup->setString(openstudio::AirLoopHVAC_SupplyPathExtensibleFields::ComponentObjectType, component.iddObject().name())) {
        return false;
      }
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_SupplyPathExtensibleFields::ComponentName, component.handle());
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACSupplyPath_Impl::supplyAirPathInletNode() const {
      return resolvedNodeTarget(openstudio::AirLoopHVAC_SupplyPathFields::SupplyAirPathInletNodeName);
    }

    bool AirLoopHVACSupplyPath_Impl::setSupplyAirPathInletNode(const openstudio::epmodel::Node& node) {
      return setPointer(openstudio::AirLoopHVAC_SupplyPathFields::SupplyAirPathInletNodeName, node.handle(), false);
    }

    void AirLoopHVACSupplyPath_Impl::doCanonicalize(LoadContext& context) {
      auto inletNode = supplyAirPathInletNode();
      if (!inletNode) {
        return;
      }

      // Canonical goal: each extensible row must resolve to a real component.
      // Invalid rows are removed so const traversal code can assume that name
      // + type pairs are meaningful and pointer wiring can be re-applied.
      auto supplyPath = getObject<openstudio::epmodel::AirLoopHVACSupplyPath>();
      unsigned groupIndex = 0u;
      while (groupIndex < supplyPath.numExtensibleGroups()) {
        auto groups = supplyPath.extensibleGroups();
        if (groupIndex >= groups.size()) {
          break;
        }
        const auto& group = groups[groupIndex];

        const auto componentType = group.getString(openstudio::AirLoopHVAC_SupplyPathExtensibleFields::ComponentObjectType);
        const auto componentName = group.getString(openstudio::AirLoopHVAC_SupplyPathExtensibleFields::ComponentName);

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
          LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVACSupplyPath",
                   "Removing invalid SupplyPath component group on '" << supplyPath.nameString() << "'.");
          supplyPath.eraseExtensibleGroup(groupIndex);
          continue;
        }

        ++groupIndex;
      }

      // In E+ schema the SupplyPath does not directly own a splitter pointer;
      // node-name linkage is the association contract. Recover that contract
      // here so later topology calls can rely on a complete path record.
      boost::optional<openstudio::epmodel::AirLoopHVACZoneSplitter> zoneSplitter;
      for (const auto& splitter : model().getModelObjects<openstudio::epmodel::AirLoopHVACZoneSplitter>()) {
        if (auto splitterInlet = splitter.getImpl<openstudio::epmodel::detail::AirLoopHVACZoneSplitter_Impl>()->inletNode()) {
          if (*splitterInlet == *inletNode) {
            zoneSplitter = splitter;
            break;
          }
        }
      }

      if (!zoneSplitter) {
        LOG_FREE(Warn, "openstudio.epmodel.AirLoopHVACSupplyPath",
                 "No AirLoopHVAC:ZoneSplitter found for SupplyPath '" << getObject<openstudio::epmodel::AirLoopHVACSupplyPath>().nameString()
                                                                      << "' via Supply Air Path Inlet Node association. This is likely problematic, "
                                                                         "and no repair was applied.");
      }

      // Keep SupplyPath component membership self-contained: once we identify
      // the linked splitter, it should also appear in this component list.
      // This prevents topology code from having to merge two sources of truth.
      if (zoneSplitter) {
        const auto components = supplyPath.components();
        const bool listed = std::ranges::any_of(components, [&](const auto& component) { return component == *zoneSplitter; });

        if (!listed) {
          if (addComponent(*zoneSplitter)) {
            detail::addLoadInfo(context, "Added missing AirLoopHVAC:ZoneSplitter '" + zoneSplitter->nameString() + "' to SupplyPath '"
                                           + supplyPath.nameString() + "'.");
          } else {
            detail::addLoadWarning(context, "Failed to add missing AirLoopHVAC:ZoneSplitter '" + zoneSplitter->nameString() + "' to SupplyPath '"
                                              + supplyPath.nameString() + "'.");
          }
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
