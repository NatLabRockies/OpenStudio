/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManagerAssignmentList.hpp"
#include "AvailabilityManagerAssignmentList_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"
#include "AvailabilityManager/AvailabilityManager_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AvailabilityManagerAssignmentList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  AvailabilityManagerAssignmentList::AvailabilityManagerAssignmentList(const Model& model)
    : ModelObject(AvailabilityManagerAssignmentList::iddObjectType(), model) {
    auto impl = getImpl<detail::AvailabilityManagerAssignmentList_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AvailabilityManagerAssignmentList::AvailabilityManagerAssignmentList(std::shared_ptr<detail::AvailabilityManagerAssignmentList_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AvailabilityManagerAssignmentList::iddObjectType() {
    return IddObjectType::AvailabilityManagerAssignmentList;
  }

  std::vector<AvailabilityManager> AvailabilityManagerAssignmentList::availabilityManagers() const {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->availabilityManagers();
  }

  bool AvailabilityManagerAssignmentList::addAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->addAvailabilityManager(availabilityManager);
  }

  bool AvailabilityManagerAssignmentList::addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->addAvailabilityManager(availabilityManager, priority);
  }

  bool AvailabilityManagerAssignmentList::setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers) {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->setAvailabilityManagers(availabilityManagers);
  }

  void AvailabilityManagerAssignmentList::resetAvailabilityManagers() {
    getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->resetAvailabilityManagers();
  }

  bool AvailabilityManagerAssignmentList::removeAvailabilityManager(const AvailabilityManager& availabilityManager) {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->removeAvailabilityManager(availabilityManager);
  }

  bool AvailabilityManagerAssignmentList::removeAvailabilityManager(unsigned priority) {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->removeAvailabilityManager(priority);
  }

  bool AvailabilityManagerAssignmentList::setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority) {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->setAvailabilityManagerPriority(availabilityManager, priority);
  }

  unsigned AvailabilityManagerAssignmentList::availabilityManagerPriority(const AvailabilityManager& availabilityManager) const {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->availabilityManagerPriority(availabilityManager);
  }

  boost::optional<Loop> AvailabilityManagerAssignmentList::loop() const {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->loop();
  }

  boost::optional<AirLoopHVAC> AvailabilityManagerAssignmentList::airLoopHVAC() const {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->airLoopHVAC();
  }

  boost::optional<PlantLoop> AvailabilityManagerAssignmentList::plantLoop() const {
    return getImpl<detail::AvailabilityManagerAssignmentList_Impl>()->plantLoop();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<openstudio::epmodel::AvailabilityManager> AvailabilityManagerAssignmentList_Impl::availabilityManagers() const {
      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();
      std::vector<openstudio::epmodel::AvailabilityManager> result;

      const auto groups = assignmentList.extensibleGroups();
      result.reserve(groups.size());
      for (const auto& group : groups) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);

        auto target = workspaceGroup->getTarget(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName);
        if (!target) {
          continue;
        }

        auto availabilityManager = target->optionalCast<openstudio::epmodel::AvailabilityManager>();
        if (!availabilityManager) {
          continue;
        }

        result.push_back(*availabilityManager);
      }
      return result;
    }

    bool AvailabilityManagerAssignmentList_Impl::addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager) {
      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();

      if (availabilityManager.model() != model()) {
        return false;
      }

      const auto currentManagers = availabilityManagers();
      if (std::ranges::find(currentManagers, availabilityManager) != currentManagers.end()) {
        return true;
      }

      auto group = assignmentList.pushExtensibleGroup();
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      OS_ASSERT(workspaceGroup);

      if (!workspaceGroup->setString(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerObjectType,
                                     availabilityManager.iddObject().name())) {
        return false;
      }

      return workspaceGroup->setPointer(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName,
                                        availabilityManager.handle());
    }

    bool AvailabilityManagerAssignmentList_Impl::addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager,
                                                                        unsigned priority) {
      if (!addAvailabilityManager(availabilityManager)) {
        return false;
      }
      return setAvailabilityManagerPriority(availabilityManager, priority);
    }

    bool AvailabilityManagerAssignmentList_Impl::setAvailabilityManagers(
      const std::vector<openstudio::epmodel::AvailabilityManager>& availabilityManagers) {
      for (const auto& availabilityManager : availabilityManagers) {
        if (availabilityManager.model() != model()) {
          return false;
        }
      }

      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();
      assignmentList.clearExtensibleGroups();
      for (const auto& availabilityManager : availabilityManagers) {
        OS_ASSERT(addAvailabilityManager(availabilityManager));
      }
      return true;
    }

    void AvailabilityManagerAssignmentList_Impl::resetAvailabilityManagers() {
      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();
      assignmentList.clearExtensibleGroups();
    }

    bool AvailabilityManagerAssignmentList_Impl::removeAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager) {
      auto currentManagers = availabilityManagers();
      const auto it = std::find(currentManagers.begin(), currentManagers.end(), availabilityManager);
      if (it == currentManagers.end()) {
        return false;
      }

      currentManagers.erase(it);
      return setAvailabilityManagers(currentManagers);
    }

    bool AvailabilityManagerAssignmentList_Impl::removeAvailabilityManager(unsigned priority) {
      auto currentManagers = availabilityManagers();
      if ((priority < 1u) || (priority > currentManagers.size())) {
        return false;
      }

      currentManagers.erase(currentManagers.begin() + static_cast<long>(priority - 1u));
      return setAvailabilityManagers(currentManagers);
    }

    bool AvailabilityManagerAssignmentList_Impl::setAvailabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager,
                                                                                unsigned priority) {
      auto currentManagers = availabilityManagers();
      const auto it = std::find(currentManagers.begin(), currentManagers.end(), availabilityManager);
      if (it == currentManagers.end()) {
        return false;
      }

      auto value = *it;
      currentManagers.erase(it);

      if (priority < 1u) {
        priority = 1u;
      }
      if (priority > currentManagers.size() + 1u) {
        priority = static_cast<unsigned>(currentManagers.size() + 1u);
      }

      currentManagers.insert(currentManagers.begin() + static_cast<long>(priority - 1u), value);
      return setAvailabilityManagers(currentManagers);
    }

    unsigned
      AvailabilityManagerAssignmentList_Impl::availabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager) const {
      const auto currentManagers = availabilityManagers();
      const auto it = std::find(currentManagers.begin(), currentManagers.end(), availabilityManager);
      OS_ASSERT(it != currentManagers.end());
      return static_cast<unsigned>(std::distance(currentManagers.begin(), it) + 1);
    }

    boost::optional<openstudio::epmodel::Loop> AvailabilityManagerAssignmentList_Impl::loop() const {
      if (auto result = airLoopHVAC()) {
        auto loop = result->optionalCast<openstudio::epmodel::Loop>();
        OS_ASSERT(loop);
        return *loop;
      }
      if (auto result = plantLoop()) {
        auto loop = result->optionalCast<openstudio::epmodel::Loop>();
        OS_ASSERT(loop);
        return *loop;
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::AirLoopHVAC> AvailabilityManagerAssignmentList_Impl::airLoopHVAC() const {
      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();
      boost::optional<openstudio::epmodel::AirLoopHVAC> result;

      for (const auto& airLoop : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
        auto target = airLoop.getModelObjectTarget<openstudio::epmodel::AvailabilityManagerAssignmentList>(
          openstudio::AirLoopHVACFields::AvailabilityManagerListName);
        if (!target) {
          continue;
        }
        if (*target == assignmentList) {
          OS_ASSERT(!result);
          result = airLoop;
        }
      }

      return result;
    }

    boost::optional<openstudio::epmodel::PlantLoop> AvailabilityManagerAssignmentList_Impl::plantLoop() const {
      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();
      boost::optional<openstudio::epmodel::PlantLoop> result;

      for (const auto& plantLoop : model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>()) {
        auto target = plantLoop.getModelObjectTarget<openstudio::epmodel::AvailabilityManagerAssignmentList>(
          openstudio::PlantLoopFields::AvailabilityManagerListName);
        if (!target) {
          continue;
        }
        if (*target == assignmentList) {
          OS_ASSERT(!result);
          result = plantLoop;
        }
      }

      return result;
    }

    void AvailabilityManagerAssignmentList_Impl::doCanonicalize(LoadContext& context) {
      auto assignmentList = getObject<openstudio::epmodel::AvailabilityManagerAssignmentList>();

      unsigned groupIndex = 0u;
      while (groupIndex < assignmentList.numExtensibleGroups()) {
        auto groups = assignmentList.extensibleGroups();
        if (groupIndex >= groups.size()) {
          break;
        }

        auto group = groups[groupIndex];
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          assignmentList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context,
                                 "Removed invalid extensible group in AvailabilityManagerAssignmentList '" + assignmentList.nameString() + "'.");
          continue;
        }

        auto objectType = group.getString(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerObjectType, true);
        auto objectName = group.getString(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName, true);
        if (!objectType || objectType->empty() || !objectName || objectName->empty()) {
          assignmentList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed incomplete availability manager entry in AvailabilityManagerAssignmentList '"
                                            + assignmentList.nameString() + "'.");
          continue;
        }

        openstudio::IddObjectType iddType = openstudio::IddObjectType::Catchall;
        try {
          iddType = openstudio::IddObjectType(*objectType);
        } catch (const std::runtime_error&) {  // NOLINT
          assignmentList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed invalid availability manager object type '" + *objectType
                                            + "' in AvailabilityManagerAssignmentList '" + assignmentList.nameString() + "'.");
          continue;
        }

        auto candidateObject = model().getObjectByTypeAndName(iddType, *objectName);
        auto availabilityManager = candidateObject ? candidateObject->optionalCast<openstudio::epmodel::AvailabilityManager>() : boost::none;
        if (!availabilityManager) {
          assignmentList.eraseExtensibleGroup(groupIndex);
          detail::addLoadWarning(context, "Removed missing availability manager '" + *objectName + "' (" + *objectType
                                            + ") from AvailabilityManagerAssignmentList '" + assignmentList.nameString() + "'.");
          continue;
        }

        // Canonical postcondition: pointer linkage on extensible rows is authoritative
        // for rename propagation and typed target APIs.
        OS_ASSERT(workspaceGroup->setPointer(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName,
                                             availabilityManager->handle()));

        // Keep object-type field aligned with the resolved target object.
        OS_ASSERT(workspaceGroup->setString(openstudio::AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerObjectType,
                                            availabilityManager->iddObject().name()));

        ++groupIndex;
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
