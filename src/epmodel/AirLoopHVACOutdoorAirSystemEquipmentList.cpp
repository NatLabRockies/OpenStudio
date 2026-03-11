/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_EquipmentList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACOutdoorAirSystemEquipmentList::AirLoopHVACOutdoorAirSystemEquipmentList(const Model& model)
  : ModelObject(AirLoopHVACOutdoorAirSystemEquipmentList::iddObjectType(), model) {
  auto impl = getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

AirLoopHVACOutdoorAirSystemEquipmentList::AirLoopHVACOutdoorAirSystemEquipmentList(
  std::shared_ptr<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACOutdoorAirSystemEquipmentList::iddObjectType() {
  return IddObjectType::AirLoopHVAC_OutdoorAirSystem_EquipmentList;
}

std::vector<ModelObject> AirLoopHVACOutdoorAirSystemEquipmentList::equipment() const {
  return getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->equipment();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystemEquipmentList_Impl::equipment() const {
  auto equipmentList = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>();
  std::vector<ModelObject> result;
  const auto groups = equipmentList.extensibleGroups();
  result.reserve(groups.size());
  for (const auto& group : groups) {
    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);
    auto target = workspaceGroup->getTarget(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName);
    OS_ASSERT(target);
    auto modelObject = target->optionalCast<ModelObject>();
    OS_ASSERT(modelObject);
    result.push_back(*modelObject);
  }
  return result;
}

bool AirLoopHVACOutdoorAirSystemEquipmentList_Impl::addEquipment(const openstudio::epmodel::ModelObject& component) {
  auto equipmentList = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>();
  auto group = equipmentList.pushExtensibleGroup();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!workspaceGroup) {
    return false;
  }
  if (!workspaceGroup->setString(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType,
                                 component.iddObject().name())) {
    return false;
  }
  return workspaceGroup->setPointer(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName, component.handle());
}

bool AirLoopHVACOutdoorAirSystemEquipmentList_Impl::removeEquipment(const openstudio::epmodel::ModelObject& component) {
  auto equipmentList = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>();
  auto groups = equipmentList.extensibleGroups();
  for (unsigned i = static_cast<unsigned>(groups.size()); i > 0u; --i) {
    const unsigned index = i - 1u;
    auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
    if (!workspaceGroup) {
      continue;
    }
    auto target = workspaceGroup->getTarget(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName);
    if (!target) {
      continue;
    }
    if (target->handle() == component.handle()) {
      equipmentList.eraseExtensibleGroup(index);
      return true;
    }
  }
  return false;
}

void AirLoopHVACOutdoorAirSystemEquipmentList_Impl::doCanonicalize(LoadContext& context) {
  auto equipmentList = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>();

  unsigned groupIndex = 0u;
  unsigned removedCount = 0u;
  for (auto& group : equipmentList.extensibleGroups()) {
    const auto componentType = group.getString(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentObjectType);
    const auto componentName = group.getString(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName);

    bool removeGroup = false;
    openstudio::IddObjectType iddType = openstudio::IddObjectType::Catchall;

    if (!componentType || componentType->empty()) {
      removeGroup = true;
      detail::addLoadWarning(context, "AirLoopHVAC:OutdoorAirSystem:EquipmentList '" + equipmentList.nameString()
                                        + "' is missing component type at extensible index " + std::to_string(groupIndex) + ".");
    } else {
      try {
        iddType = openstudio::IddObjectType(*componentType);
      } catch (const std::runtime_error&) {  // NOLINT
        removeGroup = true;
        detail::addLoadWarning(context, "AirLoopHVAC:OutdoorAirSystem:EquipmentList '" + equipmentList.nameString()
                                          + "' has invalid component type '" + *componentType + "' at extensible index "
                                          + std::to_string(groupIndex) + ".");
      }
    }

    if (!componentName || componentName->empty()) {
      removeGroup = true;
      detail::addLoadWarning(context, "AirLoopHVAC:OutdoorAirSystem:EquipmentList '" + equipmentList.nameString()
                                        + "' is missing component name at extensible index " + std::to_string(groupIndex) + ".");
    }

    auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
    OS_ASSERT(workspaceGroup);

    if (!removeGroup) {
      auto object = model().getObjectByTypeAndName(iddType, *componentName, true);
      auto component = object ? object->optionalCast<openstudio::epmodel::ModelObject>() : boost::none;
      if (!component) {
        removeGroup = true;
        detail::addLoadWarning(context, "AirLoopHVAC:OutdoorAirSystem:EquipmentList '" + equipmentList.nameString() + "' component '"
                                          + *componentName + "' (" + *componentType + ") could not be resolved at extensible index "
                                          + std::to_string(groupIndex) + ".");
      } else {
        OS_ASSERT(workspaceGroup->setPointer(openstudio::AirLoopHVAC_OutdoorAirSystem_EquipmentListExtensibleFields::ComponentName,
                                             component->handle()));
      }
    }

    if (removeGroup) {
      const unsigned eraseIndex = groupIndex - removedCount;
      equipmentList.eraseExtensibleGroup(eraseIndex);
      ++removedCount;
      detail::addLoadInfo(context, "Removed invalid AirLoopHVAC:OutdoorAirSystem:EquipmentList group at extensible index "
                                     + std::to_string(groupIndex) + " for '" + equipmentList.nameString() + "'.");
    }
    ++groupIndex;
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
