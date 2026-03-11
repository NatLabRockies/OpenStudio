/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/WaterUseEquipment.hpp"
#include "SpaceLoadInstance/WaterUseEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WaterUse_Equipment_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WaterUseEquipment::WaterUseEquipment(const Model& model) : ModelObject(WaterUseEquipment::iddObjectType(), model) {}

  WaterUseEquipment::WaterUseEquipment(std::shared_ptr<detail::WaterUseEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WaterUseEquipment::iddObjectType() {
    return IddObjectType::WaterUse_Equipment;
  }

  std::string WaterUseEquipment::endUseSubcategory() const {
    return getImpl<detail::WaterUseEquipment_Impl>()->endUseSubcategory();
  }

  bool WaterUseEquipment::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::WaterUseEquipment_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool WaterUseEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::WaterUseEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void WaterUseEquipment::resetEndUseSubcategory() {
    getImpl<detail::WaterUseEquipment_Impl>()->resetEndUseSubcategory();
  }

  double WaterUseEquipment::peakFlowRate() const {
    return getImpl<detail::WaterUseEquipment_Impl>()->peakFlowRate();
  }

  bool WaterUseEquipment::setPeakFlowRate(double peakFlowRate) {
    return getImpl<detail::WaterUseEquipment_Impl>()->setPeakFlowRate(peakFlowRate);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WaterUseEquipment_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::WaterUse_EquipmentFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterUseEquipment_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::WaterUse_EquipmentFields::EndUseSubcategory);
    }

    bool WaterUseEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::WaterUse_EquipmentFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void WaterUseEquipment_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::WaterUse_EquipmentFields::EndUseSubcategory, ""));
    }

    double WaterUseEquipment_Impl::peakFlowRate() const {
      const auto value = getDouble(openstudio::WaterUse_EquipmentFields::PeakFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterUseEquipment_Impl::setPeakFlowRate(double peakFlowRate) {
      return setDouble(openstudio::WaterUse_EquipmentFields::PeakFlowRate, peakFlowRate);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
