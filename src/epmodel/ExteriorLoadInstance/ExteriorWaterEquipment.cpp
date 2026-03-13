/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExteriorLoadInstance/ExteriorWaterEquipment.hpp"
#include "ExteriorLoadInstance/ExteriorWaterEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Exterior_WaterEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ExteriorWaterEquipment::ExteriorWaterEquipment(const Model& model) : ModelObject(ExteriorWaterEquipment::iddObjectType(), model) {
    // Keep scalar getter behavior stable on a default-constructed instance.
    OS_ASSERT(setMultiplier(1.0));
    OS_ASSERT(setEndUseSubcategory("General"));
  }

  ExteriorWaterEquipment::ExteriorWaterEquipment(std::shared_ptr<detail::ExteriorWaterEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ExteriorWaterEquipment::iddObjectType() {
    return IddObjectType::Exterior_WaterEquipment;
  }

  double ExteriorWaterEquipment::multiplier() const {
    return getImpl<detail::ExteriorWaterEquipment_Impl>()->multiplier();
  }

  bool ExteriorWaterEquipment::isMultiplierDefaulted() const {
    return getImpl<detail::ExteriorWaterEquipment_Impl>()->isMultiplierDefaulted();
  }

  bool ExteriorWaterEquipment::setMultiplier(double multiplier) {
    return getImpl<detail::ExteriorWaterEquipment_Impl>()->setMultiplier(multiplier);
  }

  void ExteriorWaterEquipment::resetMultiplier() {
    getImpl<detail::ExteriorWaterEquipment_Impl>()->resetMultiplier();
  }

  std::string ExteriorWaterEquipment::endUseSubcategory() const {
    return getImpl<detail::ExteriorWaterEquipment_Impl>()->endUseSubcategory();
  }

  bool ExteriorWaterEquipment::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::ExteriorWaterEquipment_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool ExteriorWaterEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::ExteriorWaterEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void ExteriorWaterEquipment::resetEndUseSubcategory() {
    getImpl<detail::ExteriorWaterEquipment_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ExteriorWaterEquipment_Impl::multiplier() const {
      if (const auto value = getDouble(openstudio::Exterior_WaterEquipmentFields::DesignLevel, true)) {
        return *value;
      }
      return 1.0;
    }

    bool ExteriorWaterEquipment_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::Exterior_WaterEquipmentFields::DesignLevel);
    }

    bool ExteriorWaterEquipment_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::Exterior_WaterEquipmentFields::DesignLevel, multiplier);
    }

    void ExteriorWaterEquipment_Impl::resetMultiplier() {
      OS_ASSERT(setString(openstudio::Exterior_WaterEquipmentFields::DesignLevel, ""));
    }

    std::string ExteriorWaterEquipment_Impl::endUseSubcategory() const {
      if (const auto value = getString(openstudio::Exterior_WaterEquipmentFields::EndUseSubcategory, true)) {
        return *value;
      }
      return "General";
    }

    bool ExteriorWaterEquipment_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Exterior_WaterEquipmentFields::EndUseSubcategory);
    }

    bool ExteriorWaterEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Exterior_WaterEquipmentFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void ExteriorWaterEquipment_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::Exterior_WaterEquipmentFields::EndUseSubcategory, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
