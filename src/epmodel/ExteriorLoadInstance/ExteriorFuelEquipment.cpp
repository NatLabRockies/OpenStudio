/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExteriorLoadInstance/ExteriorFuelEquipment.hpp"
#include "ExteriorLoadInstance/ExteriorFuelEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Exterior_FuelEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

#include "../utilities/data/DataEnums.hpp"
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  ExteriorFuelEquipment::ExteriorFuelEquipment(const Model& model) : ModelObject(ExteriorFuelEquipment::iddObjectType(), model) {
    // Keep scalar getters with required/defaulted semantics stable on a default-constructed instance.
    OS_ASSERT(setFuelType("Electricity"));
    OS_ASSERT(setMultiplier(1.0));
    OS_ASSERT(setEndUseSubcategory("General"));
  }

  ExteriorFuelEquipment::ExteriorFuelEquipment(std::shared_ptr<detail::ExteriorFuelEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ExteriorFuelEquipment::iddObjectType() {
    return IddObjectType::Exterior_FuelEquipment;
  }

  std::vector<std::string> ExteriorFuelEquipment::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Exterior_FuelEquipmentFields::FuelUseType);
  }

  std::vector<std::string> ExteriorFuelEquipment::validFuelTypeValues() {
    return ExteriorFuelEquipment::fuelTypeValues();
  }

  std::string ExteriorFuelEquipment::fuelType() const {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->fuelType();
  }

  bool ExteriorFuelEquipment::setFuelType(const FuelType& fuelType) {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->setFuelType(fuelType.valueDescription());
  }

  bool ExteriorFuelEquipment::setFuelType(const std::string& fuelType) {
    try {
      return setFuelType(FuelType{fuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  double ExteriorFuelEquipment::multiplier() const {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->multiplier();
  }

  bool ExteriorFuelEquipment::isMultiplierDefaulted() const {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->isMultiplierDefaulted();
  }

  bool ExteriorFuelEquipment::setMultiplier(double multiplier) {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->setMultiplier(multiplier);
  }

  void ExteriorFuelEquipment::resetMultiplier() {
    getImpl<detail::ExteriorFuelEquipment_Impl>()->resetMultiplier();
  }

  std::string ExteriorFuelEquipment::endUseSubcategory() const {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->endUseSubcategory();
  }

  bool ExteriorFuelEquipment::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool ExteriorFuelEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::ExteriorFuelEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void ExteriorFuelEquipment::resetEndUseSubcategory() {
    getImpl<detail::ExteriorFuelEquipment_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ExteriorFuelEquipment_Impl::fuelType() const {
      const auto value = getString(openstudio::Exterior_FuelEquipmentFields::FuelUseType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExteriorFuelEquipment_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Exterior_FuelEquipmentFields::FuelUseType, fuelType);
    }

    double ExteriorFuelEquipment_Impl::multiplier() const {
      const auto value = getDouble(openstudio::Exterior_FuelEquipmentFields::DesignLevel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExteriorFuelEquipment_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::Exterior_FuelEquipmentFields::DesignLevel);
    }

    bool ExteriorFuelEquipment_Impl::setMultiplier(double multiplier) {
      return setDouble(openstudio::Exterior_FuelEquipmentFields::DesignLevel, multiplier);
    }

    void ExteriorFuelEquipment_Impl::resetMultiplier() {
      const bool result = setString(openstudio::Exterior_FuelEquipmentFields::DesignLevel, "");
      OS_ASSERT(result);
    }

    std::string ExteriorFuelEquipment_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Exterior_FuelEquipmentFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ExteriorFuelEquipment_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Exterior_FuelEquipmentFields::EndUseSubcategory);
    }

    bool ExteriorFuelEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Exterior_FuelEquipmentFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void ExteriorFuelEquipment_Impl::resetEndUseSubcategory() {
      const bool result = setString(openstudio::Exterior_FuelEquipmentFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> ExteriorFuelEquipment_Impl::fuelTypeValues() const {
      return openstudio::epmodel::ExteriorFuelEquipment::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
