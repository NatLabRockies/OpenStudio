/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/PlantEquipmentList.hpp"
#include "ModelObject/PlantEquipmentList_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "Model.hpp"

#include <algorithm>
#include <stdexcept>

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PlantEquipmentList_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  PlantEquipmentList::PlantEquipmentList(const Model& model) : ModelObject(PlantEquipmentList::iddObjectType(), model) {}

  PlantEquipmentList::PlantEquipmentList(std::shared_ptr<detail::PlantEquipmentList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType PlantEquipmentList::iddObjectType() {
    return IddObjectType::PlantEquipmentList;
  }

  std::vector<HVACComponent> PlantEquipmentList::equipment() const {
    return getImpl<detail::PlantEquipmentList_Impl>()->equipment();
  }

  bool PlantEquipmentList::addEquipment(const HVACComponent& equipment) {
    return getImpl<detail::PlantEquipmentList_Impl>()->addEquipment(equipment);
  }

  bool PlantEquipmentList::removeEquipment(const HVACComponent& equipment) {
    return getImpl<detail::PlantEquipmentList_Impl>()->removeEquipment(equipment);
  }

  void PlantEquipmentList::removeAllEquipment() {
    getImpl<detail::PlantEquipmentList_Impl>()->removeAllEquipment();
  }

  bool PlantEquipmentList::replaceEquipment(const std::vector<HVACComponent>& equipment) {
    return getImpl<detail::PlantEquipmentList_Impl>()->replaceEquipment(equipment);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      boost::optional<openstudio::epmodel::HVACComponent> resolveEquipmentTarget(const openstudio::WorkspaceExtensibleGroup& group,
                                                                                 const openstudio::epmodel::Model& model) {
        if (auto target = group.getTarget(openstudio::PlantEquipmentListExtensibleFields::EquipmentName)) {
          if (auto component = target->optionalCast<openstudio::epmodel::HVACComponent>()) {
            return *component;
          }
        }

        const auto objectType = group.getString(openstudio::PlantEquipmentListExtensibleFields::EquipmentObjectType, true);
        const auto name = group.getString(openstudio::PlantEquipmentListExtensibleFields::EquipmentName, true);
        if (!objectType || objectType->empty() || !name || name->empty()) {
          return boost::none;
        }

        try {
          const auto iddType = openstudio::IddObjectType(*objectType);
          if (auto object = model.getObjectByTypeAndName(iddType, *name, true)) {
            if (auto component = object->optionalCast<openstudio::epmodel::HVACComponent>()) {
              return *component;
            }
          }
        } catch (const std::runtime_error&) {  // NOLINT
          return boost::none;
        }

        return boost::none;
      }

      bool setEquipmentTarget(openstudio::WorkspaceExtensibleGroup& group, const openstudio::epmodel::HVACComponent& component) {
        if (!group.setString(openstudio::PlantEquipmentListExtensibleFields::EquipmentObjectType, component.iddObject().name(), false)) {
          return false;
        }

        return group.setPointer(openstudio::PlantEquipmentListExtensibleFields::EquipmentName, component.handle(), false);
      }

      boost::optional<openstudio::WorkspaceExtensibleGroup> groupForEquipment(const openstudio::epmodel::PlantEquipmentList& equipmentList,
                                                                              const openstudio::epmodel::HVACComponent& equipment) {
        for (const auto& group : equipmentList.extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }

          auto target = resolveEquipmentTarget(*workspaceGroup, equipmentList.model());
          if (target && (*target == equipment)) {
            return workspaceGroup;
          }
        }
        return boost::none;
      }

    }  // namespace

    std::vector<openstudio::epmodel::HVACComponent> PlantEquipmentList_Impl::equipment() const {
      std::vector<openstudio::epmodel::HVACComponent> result;
      for (const auto& group : getObject<openstudio::epmodel::PlantEquipmentList>().extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto target = resolveEquipmentTarget(*workspaceGroup, model());
        if (target) {
          result.push_back(*target);
        }
      }
      return result;
    }

    bool PlantEquipmentList_Impl::addEquipment(const openstudio::epmodel::HVACComponent& equipment) {
      if (equipment.model() != model()) {
        return false;
      }

      auto list = getObject<openstudio::epmodel::PlantEquipmentList>();
      if (groupForEquipment(list, equipment)) {
        return false;
      }

      auto group = list.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!group) {
        return false;
      }

      if (!setEquipmentTarget(*group, equipment)) {
        list.eraseExtensibleGroup(group->groupIndex());
        return false;
      }

      return true;
    }

    bool PlantEquipmentList_Impl::removeEquipment(const openstudio::epmodel::HVACComponent& equipment) {
      auto list = getObject<openstudio::epmodel::PlantEquipmentList>();
      auto group = groupForEquipment(list, equipment);
      if (!group) {
        return false;
      }

      list.eraseExtensibleGroup(group->groupIndex());
      return true;
    }

    void PlantEquipmentList_Impl::removeAllEquipment() {
      getObject<openstudio::epmodel::PlantEquipmentList>().clearExtensibleGroups();
    }

    bool PlantEquipmentList_Impl::replaceEquipment(const std::vector<openstudio::epmodel::HVACComponent>& equipment) {
      for (const auto& component : equipment) {
        if (component.model() != model()) {
          return false;
        }
      }

      std::vector<openstudio::epmodel::HVACComponent> uniqueEquipment;
      for (const auto& component : equipment) {
        if (std::find(uniqueEquipment.begin(), uniqueEquipment.end(), component) == uniqueEquipment.end()) {
          uniqueEquipment.push_back(component);
        }
      }

      removeAllEquipment();
      for (const auto& component : uniqueEquipment) {
        if (!addEquipment(component)) {
          return false;
        }
      }

      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
