/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Branch.hpp"
#include "Branch_Impl.hpp"

#include "Model.hpp"
#include "ModelObject_Impl.hpp"
#include "Node.hpp"

#include <utilities/core/Logger.hpp>
#include "utilities/core/Assert.hpp"

#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  Branch::Branch(const Model& model) : ModelObject(Branch::iddObjectType(), model) {
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    getImpl<detail::Branch_Impl>()->canonicalize(context);
  }

  Branch::Branch(std::shared_ptr<detail::Branch_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Branch::iddObjectType() {
    return IddObjectType::Branch;
  }

  std::vector<ModelObject> Branch::components() const {
    return getImpl<detail::Branch_Impl>()->components();
  }

  boost::optional<Node> Branch::componentInletNode(unsigned index) const {
    return getImpl<detail::Branch_Impl>()->componentInletNode(index);
  }

  boost::optional<Node> Branch::componentOutletNode(unsigned index) const {
    return getImpl<detail::Branch_Impl>()->componentOutletNode(index);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    void Branch_Impl::doCanonicalize(LoadContext& context) {
      auto branch = getObject<openstudio::epmodel::Branch>();

      OS_ASSERT(!branch.nameString().empty());

      unsigned groupIndex = 0u;
      unsigned removedCount = 0u;
      for (auto& group : branch.extensibleGroups()) {
        const auto componentType = group.getString(openstudio::BranchExtensibleFields::ComponentObjectType);
        const auto componentName = group.getString(openstudio::BranchExtensibleFields::ComponentName);

        bool removeGroup = false;
        openstudio::IddObjectType iddType = openstudio::IddObjectType::Catchall;

        if (componentType) {
          try {
            iddType = openstudio::IddObjectType(*componentType);
          } catch (const std::runtime_error&) {  // NOLINT
            removeGroup = true;
            detail::addLoadWarning(context, "Branch '" + branch.nameString() + "' has invalid component type '" + *componentType
                                              + "' at extensible index " + std::to_string(groupIndex) + ".");
          }
        } else {
          removeGroup = true;
          detail::addLoadWarning(context, "Branch '" + branch.nameString() + "' is missing component type at extensible index "
                                            + std::to_string(groupIndex) + ".");
        }

        if (!componentName || componentName->empty()) {
          removeGroup = true;
          detail::addLoadWarning(context, "Branch '" + branch.nameString() + "' is missing component name at extensible index "
                                            + std::to_string(groupIndex) + ".");
        }

        if (!removeGroup && !model().getObjectByTypeAndName(iddType, *componentName)) {
          removeGroup = true;
          detail::addLoadWarning(context, "Branch '" + branch.nameString() + "' component '" + *componentName + "' (" + componentType.get()
                                            + ") references an object that could not be found in the model at extensible index "
                                            + std::to_string(groupIndex) + ".");
        }

        // We intentionally do not synthesize inlet/outlet node names here.
        // Branch extensible rows do not encode enough component semantics to
        // safely infer missing node topology without risking wrong graph wiring;
        // repairs belong in higher-level component canonicalizers that know
        // port contracts.
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        auto inletTarget = workspaceGroup->getTarget(BranchExtensibleFields::ComponentInletNodeName);
        auto inletNode = inletTarget ? inletTarget->optionalCast<Node>() : boost::none;
        if (!inletNode) {
          detail::addLoadWarning(context, "Branch '" + branch.nameString() + "' has an unresolved inlet node target at extensible index "
                                            + std::to_string(groupIndex) + ".");
        }

        auto outletTarget = workspaceGroup->getTarget(BranchExtensibleFields::ComponentOutletNodeName);
        auto outletNode = outletTarget ? outletTarget->optionalCast<Node>() : boost::none;
        if (!outletNode) {
          detail::addLoadWarning(context, "Branch '" + branch.nameString() + "' has an unresolved outlet node target at extensible index "
                                            + std::to_string(groupIndex) + ".");
        }

        if (removeGroup) {
          const unsigned eraseIndex = groupIndex - removedCount;
          branch.eraseExtensibleGroup(eraseIndex);
          ++removedCount;
          detail::addLoadInfo(context, "Removed invalid Branch component group at extensible index " + std::to_string(groupIndex) + " for '"
                                         + branch.nameString() + "'.");
        }
        ++groupIndex;
      }
    }

    std::vector<openstudio::epmodel::ModelObject> Branch_Impl::components() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      const auto groups = extensibleGroups();
      result.reserve(groups.size());
      for (const auto& group : groups) {
        if (auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>()) {
          if (auto target = workspaceGroup->getTarget(BranchExtensibleFields::ComponentName)) {
            if (auto component = target->optionalCast<openstudio::epmodel::ModelObject>()) {
              result.push_back(*component);
              continue;
            }
          }
        }

        const auto componentType = group.getString(BranchExtensibleFields::ComponentObjectType);
        const auto componentName = group.getString(BranchExtensibleFields::ComponentName);
        if (!componentType || !componentName || componentName->empty()) {
          continue;
        }

        try {
          const openstudio::IddObjectType iddType(*componentType);
          if (auto component = model().getObjectByTypeAndName(iddType, *componentName)) {
            if (auto modelObject = component->optionalCast<openstudio::epmodel::ModelObject>()) {
              result.push_back(*modelObject);
            }
          }
        } catch (const std::runtime_error&) {
          continue;
        }
      }
      return result;
    }

    bool Branch_Impl::insertComponent(unsigned index, const ModelObject& component, const std::string& inletNodeName,
                                      const std::string& outletNodeName) {
      if (!component.name()) {
        return false;
      }

      auto groups = extensibleGroups();
      if (index > groups.size()) {
        return false;
      }

      auto group = insertExtensibleGroup(index, std::vector<std::string>{}, false);
      group.setString(BranchExtensibleFields::ComponentObjectType, component.iddObject().name());

      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(inletNodeName);
      auto outletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(outletNodeName);
      workspaceGroup->setPointer(BranchExtensibleFields::ComponentName, component.handle());
      workspaceGroup->setPointer(BranchExtensibleFields::ComponentInletNodeName, inletNode.handle());
      workspaceGroup->setPointer(BranchExtensibleFields::ComponentOutletNodeName, outletNode.handle());
      group.setString(BranchExtensibleFields::ComponentName, component.nameString());
      group.setString(BranchExtensibleFields::ComponentInletNodeName, inletNodeName);
      group.setString(BranchExtensibleFields::ComponentOutletNodeName, outletNodeName);
      return true;
    }

    bool Branch_Impl::appendComponent(const ModelObject& component, const std::string& inletNodeName, const std::string& outletNodeName) {
      return insertComponent(static_cast<unsigned>(extensibleGroups().size()), component, inletNodeName, outletNodeName);
    }

    bool Branch_Impl::removeComponent(unsigned index) {
      auto branch = getObject<openstudio::epmodel::Branch>();
      const auto groups = branch.extensibleGroups();
      if (index >= groups.size()) {
        return false;
      }
      return !branch.eraseExtensibleGroup(index).empty();
    }

    void Branch_Impl::clearComponents() {
      auto branch = getObject<openstudio::epmodel::Branch>();
      while (!branch.extensibleGroups().empty()) {
        const auto index = static_cast<unsigned>(branch.extensibleGroups().size() - 1u);
        branch.eraseExtensibleGroup(index);
      }
    }

    boost::optional<Node> Branch_Impl::componentInletNode(unsigned index) const {
      auto groups = extensibleGroups();
      if (index >= groups.size()) {
        return boost::none;
      }
      auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return boost::none;
      }
      auto target = workspaceGroup->getTarget(BranchExtensibleFields::ComponentInletNodeName);
      return target ? target->optionalCast<Node>() : boost::none;
    }

    bool Branch_Impl::setComponentInletNode(unsigned index, const Node& node) {
      auto groups = extensibleGroups();
      if (index >= groups.size()) {
        return false;
      }
      auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(BranchExtensibleFields::ComponentInletNodeName, node.handle());
    }

    boost::optional<Node> Branch_Impl::componentOutletNode(unsigned index) const {
      auto groups = extensibleGroups();
      if (index >= groups.size()) {
        return boost::none;
      }
      auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return boost::none;
      }
      auto target = workspaceGroup->getTarget(BranchExtensibleFields::ComponentOutletNodeName);
      return target ? target->optionalCast<Node>() : boost::none;
    }

    bool Branch_Impl::setComponentOutletNode(unsigned index, const Node& node) {
      auto groups = extensibleGroups();
      if (index >= groups.size()) {
        return false;
      }
      auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(BranchExtensibleFields::ComponentOutletNodeName, node.handle());
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
