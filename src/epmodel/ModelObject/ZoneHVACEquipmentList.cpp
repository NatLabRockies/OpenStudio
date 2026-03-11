/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACEquipmentList.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentList_FieldEnums.hxx>

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

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
