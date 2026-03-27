/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACEquipmentList.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentList_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  ZoneHVACEquipmentList::ZoneHVACEquipmentList(const Model& model) : ModelObject(ZoneHVACEquipmentList::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACEquipmentList_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ZoneHVACEquipmentList::ZoneHVACEquipmentList(std::shared_ptr<detail::ZoneHVACEquipmentList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACEquipmentList::iddObjectType() {
    return IddObjectType::ZoneHVAC_EquipmentList;
  }

  std::vector<std::string> ZoneHVACEquipmentList::loadDistributionSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme);
  }

  std::vector<std::string> ZoneHVACEquipmentList::validLoadDistributionSchemeValues() {
    return loadDistributionSchemeValues();
  }

  std::string ZoneHVACEquipmentList::loadDistributionScheme() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->loadDistributionScheme();
  }

  bool ZoneHVACEquipmentList::isLoadDistributionSchemeDefaulted() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->isLoadDistributionSchemeDefaulted();
  }

  bool ZoneHVACEquipmentList::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->setLoadDistributionScheme(loadDistributionScheme);
  }

  void ZoneHVACEquipmentList::resetLoadDistributionScheme() {
    getImpl<detail::ZoneHVACEquipmentList_Impl>()->resetLoadDistributionScheme();
  }

  std::vector<ModelObject> ZoneHVACEquipmentList::equipment() const {
    return getImpl<detail::ZoneHVACEquipmentList_Impl>()->equipment();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneHVACEquipmentList_Impl::loadDistributionScheme() const {
      const auto value = getString(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEquipmentList_Impl::isLoadDistributionSchemeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme);
    }

    bool ZoneHVACEquipmentList_Impl::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
      auto thisScheme = loadDistributionScheme;
      if (openstudio::istringEqual(thisScheme, "Sequential")) {
        thisScheme = "SequentialLoad";
      } else if (openstudio::istringEqual(thisScheme, "Uniform")) {
        thisScheme = "UniformLoad";
      }

      const bool result = setString(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme, thisScheme, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACEquipmentList_Impl::resetLoadDistributionScheme() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EquipmentListFields::LoadDistributionScheme, "", false));
    }

    std::vector<openstudio::epmodel::ModelObject> ZoneHVACEquipmentList_Impl::equipment() const {
      std::vector<openstudio::epmodel::ModelObject> result;
      for (const auto& group : getObject<openstudio::epmodel::ZoneHVACEquipmentList>().extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto target = workspaceGroup->getTarget(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName);
        if (!target) {
          continue;
        }

        if (auto modelObject = target->optionalCast<openstudio::epmodel::ModelObject>()) {
          result.push_back(*modelObject);
        }
      }
      return result;
    }

    bool ZoneHVACEquipmentList_Impl::addEquipment(const openstudio::epmodel::ModelObject& component) {
      if (component.model() != model()) {
        return false;
      }

      auto currentEquipment = equipment();
      if (std::ranges::find(currentEquipment, component) != currentEquipment.end()) {
        return true;
      }

      auto equipmentList = getObject<openstudio::epmodel::ZoneHVACEquipmentList>();
      auto group = equipmentList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!group) {
        return false;
      }

      if (!group->setString(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentObjectType, component.iddObject().name())) {
        return false;
      }
      if (!group->setPointer(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName, component.handle())) {
        return false;
      }

      const unsigned priority = static_cast<unsigned>(currentEquipment.size() + 1u);
      if (!group->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, priority)) {
        return false;
      }
      return group->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, priority);
    }

    bool ZoneHVACEquipmentList_Impl::removeEquipment(const openstudio::epmodel::ModelObject& component) {
      auto equipmentList = getObject<openstudio::epmodel::ZoneHVACEquipmentList>();
      const auto groups = equipmentList.extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        auto workspaceGroup = groups[i].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }

        auto target = workspaceGroup->getTarget(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentName);
        if (!target || !(*target == component)) {
          continue;
        }

        equipmentList.eraseExtensibleGroup(i);

        auto remainingGroups = equipmentList.extensibleGroups();
        for (unsigned j = 0; j < remainingGroups.size(); ++j) {
          auto remainingGroup = remainingGroups[j].optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!remainingGroup) {
            continue;
          }
          const unsigned priority = j + 1u;
          OS_ASSERT(remainingGroup->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence,
                                                priority));
          OS_ASSERT(remainingGroup->setUnsigned(openstudio::ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence,
                                                priority));
        }
        return true;
      }
      return false;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
