/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationRangeBasedScheme.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationRangeBasedScheme_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject/PlantEquipmentList.hpp"
#include "ModelObject/PlantEquipmentList_Impl.hpp"

#include <algorithm>

#include <utilities/core/Assert.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>
#include <utilities/math/FloatCompare.hpp>

namespace openstudio {
namespace epmodel {

  namespace {
    enum LoadExtensibleFields
    {
      LOADRANGEFIELDS_LOWERLIMIT,
      LOADRANGEFIELDS_UPPERLIMIT,
      LOADRANGEFIELDS_RANGEEQUIPMENTLISTNAME
    };
  }

  namespace detail {

    namespace {

      boost::optional<openstudio::epmodel::PlantEquipmentList> rangeEquipmentList(const openstudio::WorkspaceExtensibleGroup& group,
                                                                                  const openstudio::epmodel::Model& model) {
        if (auto target = group.getTarget(LOADRANGEFIELDS_RANGEEQUIPMENTLISTNAME)) {
          if (auto list = target->optionalCast<openstudio::epmodel::PlantEquipmentList>()) {
            return *list;
          }
        }

        const auto name = group.getString(LOADRANGEFIELDS_RANGEEQUIPMENTLISTNAME, true);
        if (name && !name->empty()) {
          for (const auto& candidate : model.getObjectsByName(*name, true, true)) {
            if (auto list = candidate.optionalCast<openstudio::epmodel::PlantEquipmentList>()) {
              return *list;
            }
          }
        }

        return boost::none;
      }

      bool setRangeEquipmentList(openstudio::WorkspaceExtensibleGroup& group, const openstudio::epmodel::PlantEquipmentList& equipmentList) {
        return group.setPointer(LOADRANGEFIELDS_RANGEEQUIPMENTLISTNAME, equipmentList.handle(), false);
      }

      std::vector<openstudio::epmodel::HVACComponent> uniqueEquipment(const std::vector<openstudio::epmodel::HVACComponent>& equipment) {
        std::vector<openstudio::epmodel::HVACComponent> result;
        for (const auto& component : equipment) {
          if (std::find(result.begin(), result.end(), component) == result.end()) {
            result.push_back(component);
          }
        }
        return result;
      }

    }  // namespace

    PlantEquipmentOperationRangeBasedScheme_Impl::PlantEquipmentOperationRangeBasedScheme_Impl(const openstudio::IdfObject& idfObject,
                                                                                               Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(idfObject, model, keepHandle) {}

    PlantEquipmentOperationRangeBasedScheme_Impl::PlantEquipmentOperationRangeBasedScheme_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                               Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {}

    PlantEquipmentOperationRangeBasedScheme_Impl::PlantEquipmentOperationRangeBasedScheme_Impl(
      const PlantEquipmentOperationRangeBasedScheme_Impl& other, Model_Impl* model, bool keepHandle)
      : PlantEquipmentOperationScheme_Impl(other, model, keepHandle) {}

    double PlantEquipmentOperationRangeBasedScheme_Impl::maximumUpperLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 1E9;
      }
      const auto value = groups.back().getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    double PlantEquipmentOperationRangeBasedScheme_Impl::minimumLowerLimit() const {
      const auto groups = extensibleGroups();
      if (groups.empty()) {
        return 0.0;
      }
      const auto value = groups.front().getDouble(LOADRANGEFIELDS_LOWERLIMIT, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::addLoadRange(double upperLimit,
                                                                    const std::vector<openstudio::epmodel::HVACComponent>& equipment) {
      if (upperLimit < minimumLowerLimit()) {
        return false;
      }

      auto scheme = getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>();
      const auto groups = scheme.extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        auto group = groups[i].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!group) {
          continue;
        }

        const auto currentUpperLimit = group->getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        const auto currentLowerLimit = group->getDouble(LOADRANGEFIELDS_LOWERLIMIT, true);
        OS_ASSERT(currentUpperLimit);
        OS_ASSERT(currentLowerLimit);

        if (upperLimit < *currentUpperLimit) {
          if (!group->setDouble(LOADRANGEFIELDS_LOWERLIMIT, upperLimit)) {
            return false;
          }

          auto newGroup = scheme.insertExtensibleGroup(i).optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!newGroup) {
            return false;
          }

          openstudio::epmodel::PlantEquipmentList equipmentList(model());
          equipmentList.setName(scheme.nameString() + " Load Range " + std::to_string(i + 1u) + " Equipment List");
          if (!equipmentList.replaceEquipment(uniqueEquipment(equipment))) {
            scheme.eraseExtensibleGroup(i);
            return false;
          }

          OS_ASSERT(newGroup->setDouble(LOADRANGEFIELDS_LOWERLIMIT, *currentLowerLimit));
          OS_ASSERT(newGroup->setDouble(LOADRANGEFIELDS_UPPERLIMIT, upperLimit));
          OS_ASSERT(setRangeEquipmentList(*newGroup, equipmentList));
          return true;
        }
      }

      return false;
    }

    std::vector<openstudio::epmodel::HVACComponent> PlantEquipmentOperationRangeBasedScheme_Impl::removeLoadRange(double upperLimit) {
      auto scheme = getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>();
      auto groups = scheme.extensibleGroups();
      if (groups.size() <= 1u || upperLimit >= maximumUpperLimit()) {
        return {};
      }

      for (auto it = groups.begin(); it != groups.end(); ++it) {
        auto group = it->optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!group) {
          continue;
        }

        const auto currentUpperLimit = group->getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        OS_ASSERT(currentUpperLimit);
        if (!openstudio::equal(*currentUpperLimit, upperLimit)) {
          continue;
        }

        const auto currentLowerLimit = group->getDouble(LOADRANGEFIELDS_LOWERLIMIT, true);
        OS_ASSERT(currentLowerLimit);
        auto nextIt = it + 1;
        OS_ASSERT(nextIt != groups.end());
        auto nextGroup = nextIt->optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(nextGroup);
        OS_ASSERT(nextGroup->setDouble(LOADRANGEFIELDS_LOWERLIMIT, *currentLowerLimit));

        std::vector<openstudio::epmodel::HVACComponent> result;
        if (auto list = rangeEquipmentList(*group, model())) {
          result = list->equipment();
        }
        scheme.eraseExtensibleGroup(group->groupIndex());
        return result;
      }

      return {};
    }

    std::vector<double> PlantEquipmentOperationRangeBasedScheme_Impl::loadRangeUpperLimits() const {
      std::vector<double> result;
      for (const auto& group : getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>().extensibleGroups()) {
        const auto value = group.getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        OS_ASSERT(value);
        result.push_back(*value);
      }
      return result;
    }

    std::vector<openstudio::epmodel::HVACComponent> PlantEquipmentOperationRangeBasedScheme_Impl::equipment(double upperLimit) const {
      for (const auto& group : getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>().extensibleGroups()) {
        const auto value = group.getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        OS_ASSERT(value);
        if (!openstudio::equal(*value, upperLimit)) {
          continue;
        }

        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        if (auto list = rangeEquipmentList(*workspaceGroup, model())) {
          return list->equipment();
        }
        return {};
      }

      return {};
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::addEquipment(double upperLimit, const openstudio::epmodel::HVACComponent& equipment) {
      for (const auto& group : getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>().extensibleGroups()) {
        const auto value = group.getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        OS_ASSERT(value);
        if (!openstudio::equal(*value, upperLimit)) {
          continue;
        }

        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        if (auto list = rangeEquipmentList(*workspaceGroup, model())) {
          return list->addEquipment(equipment);
        }
        return false;
      }

      return false;
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::addEquipment(const openstudio::epmodel::HVACComponent& equipment) {
      const auto upperLimits = loadRangeUpperLimits();
      OS_ASSERT(!upperLimits.empty());
      return addEquipment(upperLimits.back(), equipment);
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::replaceEquipment(double upperLimit,
                                                                        const std::vector<openstudio::epmodel::HVACComponent>& equipment) {
      for (const auto& group : getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>().extensibleGroups()) {
        const auto value = group.getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        OS_ASSERT(value);
        if (!openstudio::equal(*value, upperLimit)) {
          continue;
        }

        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        if (auto list = rangeEquipmentList(*workspaceGroup, model())) {
          return list->replaceEquipment(equipment);
        }
        return false;
      }

      return false;
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::replaceEquipment(const std::vector<openstudio::epmodel::HVACComponent>& equipment) {
      const auto upperLimits = loadRangeUpperLimits();
      OS_ASSERT(!upperLimits.empty());
      return replaceEquipment(upperLimits.back(), equipment);
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::removeEquipment(double upperLimit, const openstudio::epmodel::HVACComponent& equipment) {
      for (const auto& group : getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>().extensibleGroups()) {
        const auto value = group.getDouble(LOADRANGEFIELDS_UPPERLIMIT, true);
        OS_ASSERT(value);
        if (!openstudio::equal(*value, upperLimit)) {
          continue;
        }

        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(workspaceGroup);
        if (auto list = rangeEquipmentList(*workspaceGroup, model())) {
          return list->removeEquipment(equipment);
        }
        return false;
      }

      return false;
    }

    bool PlantEquipmentOperationRangeBasedScheme_Impl::removeEquipment(const openstudio::epmodel::HVACComponent& equipment) {
      bool result = false;
      for (const auto upperLimit : loadRangeUpperLimits()) {
        if (removeEquipment(upperLimit, equipment)) {
          result = true;
        }
      }
      return result;
    }

    void PlantEquipmentOperationRangeBasedScheme_Impl::clearLoadRanges() {
      const double lowerLimit = minimumLowerLimit();
      const double upperLimit = maximumUpperLimit();
      auto scheme = getObject<openstudio::epmodel::PlantEquipmentOperationRangeBasedScheme>();
      scheme.clearExtensibleGroups();

      openstudio::epmodel::PlantEquipmentList equipmentList(model());
      equipmentList.setName(scheme.nameString() + " Equipment List");
      auto group = scheme.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      OS_ASSERT(group);
      OS_ASSERT(group->setDouble(LOADRANGEFIELDS_LOWERLIMIT, lowerLimit));
      OS_ASSERT(group->setDouble(LOADRANGEFIELDS_UPPERLIMIT, upperLimit));
      OS_ASSERT(setRangeEquipmentList(*group, equipmentList));
    }

  }  // namespace detail

  PlantEquipmentOperationRangeBasedScheme::PlantEquipmentOperationRangeBasedScheme(IddObjectType type, const Model& model)
    : PlantEquipmentOperationScheme(type, model) {
    OS_ASSERT(getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>());
    clearLoadRanges();
  }

  PlantEquipmentOperationRangeBasedScheme::PlantEquipmentOperationRangeBasedScheme(
    std::shared_ptr<detail::PlantEquipmentOperationRangeBasedScheme_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  double PlantEquipmentOperationRangeBasedScheme::maximumUpperLimit() const {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->maximumUpperLimit();
  }

  double PlantEquipmentOperationRangeBasedScheme::minimumLowerLimit() const {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->minimumLowerLimit();
  }

  bool PlantEquipmentOperationRangeBasedScheme::addLoadRange(double upperLimit, const std::vector<HVACComponent>& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->addLoadRange(upperLimit, equipment);
  }

  std::vector<HVACComponent> PlantEquipmentOperationRangeBasedScheme::removeLoadRange(double upperLimit) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->removeLoadRange(upperLimit);
  }

  std::vector<double> PlantEquipmentOperationRangeBasedScheme::loadRangeUpperLimits() const {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->loadRangeUpperLimits();
  }

  std::vector<HVACComponent> PlantEquipmentOperationRangeBasedScheme::equipment(double upperLimit) const {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->equipment(upperLimit);
  }

  bool PlantEquipmentOperationRangeBasedScheme::addEquipment(double upperLimit, const HVACComponent& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->addEquipment(upperLimit, equipment);
  }

  bool PlantEquipmentOperationRangeBasedScheme::addEquipment(const HVACComponent& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->addEquipment(equipment);
  }

  bool PlantEquipmentOperationRangeBasedScheme::replaceEquipment(double upperLimit, const std::vector<HVACComponent>& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->replaceEquipment(upperLimit, equipment);
  }

  bool PlantEquipmentOperationRangeBasedScheme::replaceEquipment(const std::vector<HVACComponent>& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->replaceEquipment(equipment);
  }

  bool PlantEquipmentOperationRangeBasedScheme::removeEquipment(double upperLimit, const HVACComponent& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->removeEquipment(upperLimit, equipment);
  }

  bool PlantEquipmentOperationRangeBasedScheme::removeEquipment(const HVACComponent& equipment) {
    return getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->removeEquipment(equipment);
  }

  void PlantEquipmentOperationRangeBasedScheme::clearLoadRanges() {
    getImpl<detail::PlantEquipmentOperationRangeBasedScheme_Impl>()->clearLoadRanges();
  }

}  // namespace epmodel
}  // namespace openstudio
