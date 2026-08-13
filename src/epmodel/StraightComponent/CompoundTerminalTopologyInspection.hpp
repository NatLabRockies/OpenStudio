/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPOUNDTERMINALTOPOLOGYINSPECTION_HPP
#define EPMODEL_COMPOUNDTERMINALTOPOLOGYINSPECTION_HPP

#include "HVACComponent/HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/NodeList.hpp"
#include "Node.hpp"

#include <algorithm>
#include <utility>
#include <vector>

#include <utilities/core/Assert.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Read-only field inspection for compound-terminal removal preflight.
    // These helpers never use getOrCreateTarget and never attach a raw node
    // name to the live pointer graph.
    struct ExistingObjectField
    {
      bool set = false;
      boost::optional<ModelObject> object;
    };

    inline ExistingObjectField existingObjectField(const ModelObject& owner, unsigned field) {
      ExistingObjectField result;
      const auto managedValue = owner.getField(field, false);
      auto workspaceImpl = owner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(workspaceImpl);
      const auto rawValue = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
      if ((!managedValue || managedValue->empty()) && (!rawValue || rawValue->empty())) {
        return result;
      }

      result.set = true;
      if (!managedValue || managedValue->empty()) {
        return result;
      }
      const auto targetHandle = toUUID(*managedValue);
      if (targetHandle.isNull()) {
        return result;
      }
      if (auto target = owner.model().getObject(targetHandle)) {
        result.object = target->optionalCast<ModelObject>();
      }
      return result;
    }

    struct ExistingNodeField
    {
      bool set = false;
      boost::optional<Node> node;
    };

    inline ExistingNodeField existingNodeField(const ModelObject& owner, unsigned field) {
      const auto objectField = existingObjectField(owner, field);
      return ExistingNodeField{objectField.set, objectField.object ? objectField.object->optionalCast<Node>() : boost::none};
    }

    struct ExistingNodeRows
    {
      bool valid = true;
      std::vector<std::pair<unsigned, Node>> rows;
    };

    inline ExistingNodeRows existingNodeRows(const ModelObject& owner, unsigned extensibleField) {
      ExistingNodeRows result;
      const auto groups = owner.extensibleGroups();
      result.rows.reserve(groups.size());
      for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
        const auto absoluteIndex = owner.iddObject().index(openstudio::ExtensibleIndex(groupIndex, extensibleField));
        const auto nodeField = existingNodeField(owner, absoluteIndex);
        if (!nodeField.set || !nodeField.node) {
          result.valid = false;
          continue;
        }
        result.rows.emplace_back(groupIndex, *nodeField.node);
      }
      return result;
    }

    inline bool hasExactSources(const ModelObject& object, const std::vector<Handle>& expectedHandles) {
      const auto sources = object.sources();
      if (sources.size() != expectedHandles.size()) {
        return false;
      }
      return std::ranges::all_of(expectedHandles, [&](const auto& handle) {
        return std::ranges::count_if(sources, [&](const auto& source) { return source.handle() == handle; }) == 1;
      });
    }

    inline bool isSoleOwnedChild(const ModelObject& terminal, const HVACComponent& child) {
      unsigned occurrences = 0u;
      boost::optional<Handle> ownerHandle;
      for (const auto& component : terminal.model().getModelObjects<HVACComponent>()) {
        const auto children = component.children();
        const auto count =
          static_cast<unsigned>(std::ranges::count_if(children, [&](const auto& candidate) { return candidate.handle() == child.handle(); }));
        if (count > 0u) {
          occurrences += count;
          ownerHandle = component.handle();
        }
      }
      return occurrences == 1u && ownerHandle && *ownerHandle == terminal.handle();
    }

    struct ExistingNodeCollectionField
    {
      bool valid = true;
      bool set = false;
      boost::optional<ModelObject> target;
      std::vector<Node> nodes;
    };

    inline ExistingNodeCollectionField existingNodeCollectionField(const ModelObject& owner, unsigned field) {
      ExistingNodeCollectionField result;
      const auto objectField = existingObjectField(owner, field);
      result.set = objectField.set;
      result.target = objectField.object;
      if (!objectField.set) {
        return result;
      }
      if (!objectField.object) {
        result.valid = false;
        return result;
      }
      if (auto node = objectField.object->optionalCast<Node>()) {
        result.nodes.push_back(*node);
        return result;
      }
      if (auto nodeList = objectField.object->optionalCast<NodeList>()) {
        auto nodeListWorkspaceImpl = nodeList->getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(nodeListWorkspaceImpl);
        const auto groups = nodeList->extensibleGroups();
        result.nodes.reserve(groups.size());
        for (unsigned groupIndex = 0u; groupIndex < groups.size(); ++groupIndex) {
          const auto absoluteIndex =
            nodeList->iddObject().index(openstudio::ExtensibleIndex(groupIndex, openstudio::NodeListExtensibleFields::NodeName));
          const auto managedNodeValue = nodeList->getField(absoluteIndex, false);
          const auto rawNodeValue = nodeListWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(absoluteIndex, false, true);

          boost::optional<Node> resolvedNode;
          if (managedNodeValue && !managedNodeValue->empty()) {
            const auto nodeHandle = toUUID(*managedNodeValue);
            if (!nodeHandle.isNull()) {
              if (auto nodeObject = owner.model().getObject(nodeHandle)) {
                resolvedNode = nodeObject->optionalCast<Node>();
              }
            }
          }
          if (!resolvedNode && rawNodeValue && !rawNodeValue->empty()) {
            resolvedNode = owner.model().getConcreteModelObjectByName<Node>(*rawNodeValue);
          }
          if (!resolvedNode) {
            result.valid = false;
            result.nodes.clear();
            return result;
          }
          result.nodes.push_back(*resolvedNode);
        }
        return result;
      }
      result.valid = false;
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
