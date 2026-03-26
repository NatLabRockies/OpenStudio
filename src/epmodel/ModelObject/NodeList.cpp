/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "NodeList.hpp"
#include "NodeList_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

NodeList::NodeList(const Model& model) : ModelObject(NodeList::iddObjectType(), model) {
  auto impl = getImpl<detail::NodeList_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

NodeList::NodeList(std::shared_ptr<detail::NodeList_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType NodeList::iddObjectType() {
  return IddObjectType::NodeList;
}

std::vector<Node> NodeList::nodes() const {
  return getImpl<detail::NodeList_Impl>()->nodes();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

openstudio::epmodel::NodeList NodeList_Impl::ensureAttachedNodeList(LoadContext& context, openstudio::epmodel::ModelObject& owner,
                                                                     const unsigned fieldIndex, const std::string& listSuffix,
                                                                     const std::string& nodeSuffix, const std::size_t expectedMaxNodes) {
  // Canonical contract for NodeList-backed fields:
  // - owner fieldIndex points to a NodeList object (not a bare Node name),
  // - that NodeList has at least one concrete Node entry.
  // Some imported IDF content stores a single Node in this slot; we normalize
  // that legacy shape into an explicit NodeList so downstream APIs can assume
  // one representation.
  const auto ownerName = owner.nameString();
  if (auto nodeList = owner.getModelObjectTarget<openstudio::epmodel::NodeList>(fieldIndex)) {
    const auto existingNodes = nodeList->nodes();
    if (existingNodes.empty()) {
      openstudio::epmodel::Node node(owner.model());
      node.setName(ownerName + nodeSuffix);
      if (!nodeList->getImpl<openstudio::epmodel::detail::NodeList_Impl>()->addNode(node)) {
        LOG_FREE_AND_THROW("openstudio.epmodel.NodeList",
                           "Failed to add node '" << node.nameString() << "' to NodeList '" << nodeList->nameString() << "'.");
      }
      detail::addLoadWarning(context, "NodeList '" + nodeList->nameString() + "' was empty for '" + ownerName + "'. Added node '"
                                       + node.nameString() + "'.");
    } else if (existingNodes.size() > expectedMaxNodes) {
      detail::addLoadWarning(context, "NodeList '" + nodeList->nameString() + "' has " + std::to_string(existingNodes.size()) + " entries for '"
                                       + ownerName + "' (expected at most " + std::to_string(expectedMaxNodes) + ").");
    }
    return *nodeList;
  }

  auto singleNode = owner.getModelObjectTarget<openstudio::epmodel::Node>(fieldIndex);
  if (!singleNode) {
    const auto singleNodeName = owner.getString(fieldIndex);
    if (singleNodeName && !singleNodeName->empty()) {
      // Respect existing by-name node identity first; only synthesize transient
      // nodes when the name exists but the object has not yet been materialized.
      if (auto object = owner.workspace().getObjectByTypeAndName(openstudio::IddObjectType::Node, *singleNodeName, true)) {
        singleNode = object->optionalCast<openstudio::epmodel::Node>();
      }
      if (!singleNode) {
        singleNode = owner.model().getOrCreateTransientByName<openstudio::epmodel::Node>(*singleNodeName);
      }
    }
  }
  auto nodeList = openstudio::epmodel::NodeList(owner.model());
  const auto nodeListName = ownerName + listSuffix;
  if (!nodeList.setName(nodeListName)) {
    LOG_FREE(Warn, "openstudio.epmodel.NodeList", "Failed to set NodeList name to '" << nodeListName << "' for '" << ownerName << "'.");
  }
  if (!owner.setPointer(fieldIndex, nodeList.handle())) {
    LOG_FREE_AND_THROW("openstudio.epmodel.NodeList", "Failed to set pointer at field index " << fieldIndex << " to NodeList '"
                                                                                                 << nodeList.nameString() << "' on '" << ownerName
                                                                                                 << "'.");
  }

  if (singleNode) {
    if (!nodeList.getImpl<openstudio::epmodel::detail::NodeList_Impl>()->addNode(*singleNode)) {
      LOG_FREE_AND_THROW("openstudio.epmodel.NodeList", "Failed to add existing node '" << singleNode->nameString() << "' to NodeList '"
                                                                                           << nodeList.nameString() << "'.");
    }
    detail::addLoadWarning(context, "Expanded single node reference '" + singleNode->nameString() + "' to NodeList '" + nodeList.nameString()
                                     + "' for '" + ownerName + "'.");
    return nodeList;
  }

  openstudio::epmodel::Node createdNode(owner.model());
  createdNode.setName(ownerName + nodeSuffix);
  if (!nodeList.getImpl<openstudio::epmodel::detail::NodeList_Impl>()->addNode(createdNode)) {
    LOG_FREE_AND_THROW("openstudio.epmodel.NodeList",
                       "Failed to add created node '" << createdNode.nameString() << "' to NodeList '" << nodeList.nameString() << "'.");
  }
  detail::addLoadInfo(context, "Created NodeList '" + nodeList.nameString() + "' and node '" + createdNode.nameString() + "' for '" + ownerName
                                 + "'.");
  return nodeList;
}

std::vector<openstudio::epmodel::Node> NodeList_Impl::nodes() const {
  std::vector<openstudio::epmodel::Node> result;
  const auto groups = extensibleGroups();
  result.reserve(groups.size());
  for (const auto& group : groups) {
    if (auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>()) {
      if (auto nodeObject = workspaceGroup->getTarget(openstudio::NodeListExtensibleFields::NodeName)) {
        if (auto node = nodeObject->optionalCast<openstudio::epmodel::Node>()) {
          result.push_back(*node);
        }
      }
    }
  }
  return result;
}

bool NodeList_Impl::addNode(const openstudio::epmodel::Node& node) {
  if (node.model() != model()) {
    return false;
  }
  if (!node.name() || node.name()->empty()) {
    return false;
  }

  for (const auto& existing : nodes()) {
    if (existing == node) {
      return true;
    }
  }

  auto nodeList = getObject<openstudio::epmodel::NodeList>();
  auto group = nodeList.pushExtensibleGroup();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!workspaceGroup) {
    return false;
  }
  return workspaceGroup->setPointer(openstudio::NodeListExtensibleFields::NodeName, node.handle());
}

bool NodeList_Impl::removeNode(const openstudio::epmodel::Node& node) {
  // Remove first matching row only; NodeList semantics treat rows as unique
  // entries and addNode already suppresses duplicates.
  auto groups = extensibleGroups();
  for (unsigned i = 0; i < groups.size(); ++i) {
    auto workspaceGroup = groups[i].optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (!workspaceGroup) {
      continue;
    }
    if (auto target = workspaceGroup->getTarget(openstudio::NodeListExtensibleFields::NodeName)) {
      if (*target == node) {
        return !eraseExtensibleGroup(i).empty();
      }
    }
  }
  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
