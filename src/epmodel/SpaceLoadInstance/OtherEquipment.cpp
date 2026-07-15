/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/OtherEquipment.hpp"
#include "SpaceLoadInstance/OtherEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OtherEquipment_FieldEnums.hxx>

#include "../utilities/data/DataEnums.hpp"
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  OtherEquipment::OtherEquipment(const Model& model) : ModelObject(OtherEquipment::iddObjectType(), model) {}

  OtherEquipment::OtherEquipment(std::shared_ptr<detail::OtherEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OtherEquipment::iddObjectType() {
    return IddObjectType::OtherEquipment;
  }

  std::vector<std::string> OtherEquipment::designLevelCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::OtherEquipmentFields::DesignLevelCalculationMethod);
  }

  std::vector<std::string> OtherEquipment::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::OtherEquipmentFields::FuelType);
  }

  std::vector<std::string> OtherEquipment::validFuelTypeValues() {
    return fuelTypeValues();
  }

  std::string OtherEquipment::designLevelCalculationMethod() const {
    return getImpl<detail::OtherEquipment_Impl>()->designLevelCalculationMethod();
  }

  bool OtherEquipment::isDesignLevelCalculationMethodDefaulted() const {
    return getImpl<detail::OtherEquipment_Impl>()->isDesignLevelCalculationMethodDefaulted();
  }

  bool OtherEquipment::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
    return getImpl<detail::OtherEquipment_Impl>()->setDesignLevelCalculationMethod(designLevelCalculationMethod);
  }

  void OtherEquipment::resetDesignLevelCalculationMethod() {
    getImpl<detail::OtherEquipment_Impl>()->resetDesignLevelCalculationMethod();
  }

  boost::optional<double> OtherEquipment::designLevel() const {
    return getImpl<detail::OtherEquipment_Impl>()->designLevel();
  }

  bool OtherEquipment::setDesignLevel(double designLevel) {
    return getImpl<detail::OtherEquipment_Impl>()->setDesignLevel(designLevel);
  }

  void OtherEquipment::resetDesignLevel() {
    getImpl<detail::OtherEquipment_Impl>()->resetDesignLevel();
  }

  boost::optional<double> OtherEquipment::powerPerFloorArea() const {
    return getImpl<detail::OtherEquipment_Impl>()->powerPerFloorArea();
  }

  bool OtherEquipment::setPowerPerFloorArea(double powerPerFloorArea) {
    return getImpl<detail::OtherEquipment_Impl>()->setPowerPerFloorArea(powerPerFloorArea);
  }

  void OtherEquipment::resetPowerPerFloorArea() {
    getImpl<detail::OtherEquipment_Impl>()->resetPowerPerFloorArea();
  }

  boost::optional<double> OtherEquipment::powerPerPerson() const {
    return getImpl<detail::OtherEquipment_Impl>()->powerPerPerson();
  }

  bool OtherEquipment::setPowerPerPerson(double powerPerPerson) {
    return getImpl<detail::OtherEquipment_Impl>()->setPowerPerPerson(powerPerPerson);
  }

  void OtherEquipment::resetPowerPerPerson() {
    getImpl<detail::OtherEquipment_Impl>()->resetPowerPerPerson();
  }

  double OtherEquipment::fractionLatent() const {
    return getImpl<detail::OtherEquipment_Impl>()->fractionLatent();
  }

  bool OtherEquipment::isFractionLatentDefaulted() const {
    return getImpl<detail::OtherEquipment_Impl>()->isFractionLatentDefaulted();
  }

  bool OtherEquipment::setFractionLatent(double fractionLatent) {
    return getImpl<detail::OtherEquipment_Impl>()->setFractionLatent(fractionLatent);
  }

  void OtherEquipment::resetFractionLatent() {
    getImpl<detail::OtherEquipment_Impl>()->resetFractionLatent();
  }

  double OtherEquipment::fractionRadiant() const {
    return getImpl<detail::OtherEquipment_Impl>()->fractionRadiant();
  }

  bool OtherEquipment::isFractionRadiantDefaulted() const {
    return getImpl<detail::OtherEquipment_Impl>()->isFractionRadiantDefaulted();
  }

  bool OtherEquipment::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::OtherEquipment_Impl>()->setFractionRadiant(fractionRadiant);
  }

  void OtherEquipment::resetFractionRadiant() {
    getImpl<detail::OtherEquipment_Impl>()->resetFractionRadiant();
  }

  double OtherEquipment::fractionLost() const {
    return getImpl<detail::OtherEquipment_Impl>()->fractionLost();
  }

  bool OtherEquipment::isFractionLostDefaulted() const {
    return getImpl<detail::OtherEquipment_Impl>()->isFractionLostDefaulted();
  }

  bool OtherEquipment::setFractionLost(double fractionLost) {
    return getImpl<detail::OtherEquipment_Impl>()->setFractionLost(fractionLost);
  }

  void OtherEquipment::resetFractionLost() {
    getImpl<detail::OtherEquipment_Impl>()->resetFractionLost();
  }

  std::string OtherEquipment::fuelType() const {
    return getImpl<detail::OtherEquipment_Impl>()->fuelType();
  }

  bool OtherEquipment::isFuelTypeDefaulted() const {
    return getImpl<detail::OtherEquipment_Impl>()->isFuelTypeDefaulted();
  }

  bool OtherEquipment::setFuelType(const FuelType& fuelType) {
    return getImpl<detail::OtherEquipment_Impl>()->setFuelType(fuelType.valueDescription());
  }

  bool OtherEquipment::setFuelType(const std::string& fuelType) {
    if (openstudio::istringEqual("None", fuelType)) {
      return getImpl<detail::OtherEquipment_Impl>()->setFuelType("None");
    }
    try {
      return setFuelType(FuelType{fuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  void OtherEquipment::resetFuelType() {
    getImpl<detail::OtherEquipment_Impl>()->resetFuelType();
  }

  std::string OtherEquipment::endUseSubcategory() const {
    return getImpl<detail::OtherEquipment_Impl>()->endUseSubcategory();
  }

  bool OtherEquipment::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::OtherEquipment_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool OtherEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::OtherEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void OtherEquipment::resetEndUseSubcategory() {
    getImpl<detail::OtherEquipment_Impl>()->resetEndUseSubcategory();
  }

  bool OtherEquipment::setMultiplier(double multiplier) {
    return getImpl<detail::OtherEquipment_Impl>()->setMultiplier(multiplier);
  }

  void OtherEquipment::resetMultiplier() {
    getImpl<detail::OtherEquipment_Impl>()->resetMultiplier();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OtherEquipment_Impl::designLevelCalculationMethod() const {
      const auto value = getString(openstudio::OtherEquipmentFields::DesignLevelCalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OtherEquipment_Impl::isDesignLevelCalculationMethodDefaulted() const {
      return isEmpty(openstudio::OtherEquipmentFields::DesignLevelCalculationMethod);
    }

    bool OtherEquipment_Impl::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
      return setString(openstudio::OtherEquipmentFields::DesignLevelCalculationMethod, designLevelCalculationMethod);
    }

    void OtherEquipment_Impl::resetDesignLevelCalculationMethod() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::DesignLevelCalculationMethod, ""));
    }

    boost::optional<double> OtherEquipment_Impl::designLevel() const {
      return getDouble(openstudio::OtherEquipmentFields::DesignLevel, true);
    }

    bool OtherEquipment_Impl::setDesignLevel(double designLevel) {
      return setDouble(openstudio::OtherEquipmentFields::DesignLevel, designLevel);
    }

    void OtherEquipment_Impl::resetDesignLevel() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::DesignLevel, ""));
    }

    boost::optional<double> OtherEquipment_Impl::powerPerFloorArea() const {
      return getDouble(openstudio::OtherEquipmentFields::PowerperFloorArea, true);
    }

    bool OtherEquipment_Impl::setPowerPerFloorArea(double powerPerFloorArea) {
      return setDouble(openstudio::OtherEquipmentFields::PowerperFloorArea, powerPerFloorArea);
    }

    void OtherEquipment_Impl::resetPowerPerFloorArea() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::PowerperFloorArea, ""));
    }

    boost::optional<double> OtherEquipment_Impl::powerPerPerson() const {
      return getDouble(openstudio::OtherEquipmentFields::PowerperPerson, true);
    }

    bool OtherEquipment_Impl::setPowerPerPerson(double powerPerPerson) {
      return setDouble(openstudio::OtherEquipmentFields::PowerperPerson, powerPerPerson);
    }

    void OtherEquipment_Impl::resetPowerPerPerson() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::PowerperPerson, ""));
    }

    double OtherEquipment_Impl::fractionLatent() const {
      const auto value = getDouble(openstudio::OtherEquipmentFields::FractionLatent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OtherEquipment_Impl::isFractionLatentDefaulted() const {
      return isEmpty(openstudio::OtherEquipmentFields::FractionLatent);
    }

    bool OtherEquipment_Impl::setFractionLatent(double fractionLatent) {
      return setDouble(openstudio::OtherEquipmentFields::FractionLatent, fractionLatent);
    }

    void OtherEquipment_Impl::resetFractionLatent() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::FractionLatent, ""));
    }

    double OtherEquipment_Impl::fractionRadiant() const {
      const auto value = getDouble(openstudio::OtherEquipmentFields::FractionRadiant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OtherEquipment_Impl::isFractionRadiantDefaulted() const {
      return isEmpty(openstudio::OtherEquipmentFields::FractionRadiant);
    }

    bool OtherEquipment_Impl::setFractionRadiant(double fractionRadiant) {
      return setDouble(openstudio::OtherEquipmentFields::FractionRadiant, fractionRadiant);
    }

    void OtherEquipment_Impl::resetFractionRadiant() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::FractionRadiant, ""));
    }

    double OtherEquipment_Impl::fractionLost() const {
      const auto value = getDouble(openstudio::OtherEquipmentFields::FractionLost, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OtherEquipment_Impl::isFractionLostDefaulted() const {
      return isEmpty(openstudio::OtherEquipmentFields::FractionLost);
    }

    bool OtherEquipment_Impl::setFractionLost(double fractionLost) {
      return setDouble(openstudio::OtherEquipmentFields::FractionLost, fractionLost);
    }

    void OtherEquipment_Impl::resetFractionLost() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::FractionLost, ""));
    }

    std::string OtherEquipment_Impl::fuelType() const {
      const auto value = getString(openstudio::OtherEquipmentFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OtherEquipment_Impl::isFuelTypeDefaulted() const {
      return isEmpty(openstudio::OtherEquipmentFields::FuelType);
    }

    bool OtherEquipment_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::OtherEquipmentFields::FuelType, fuelType);
    }

    void OtherEquipment_Impl::resetFuelType() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::FuelType, ""));
    }

    std::string OtherEquipment_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::OtherEquipmentFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OtherEquipment_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::OtherEquipmentFields::EndUseSubcategory);
    }

    bool OtherEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::OtherEquipmentFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void OtherEquipment_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::OtherEquipmentFields::EndUseSubcategory, ""));
    }

    bool OtherEquipment_Impl::setMultiplier(double multiplier) {
      // EnergyPlus OtherEquipment has no dedicated multiplier field. Preserve model API by
      // scaling whichever design-level scalar field(s) are currently populated.
      bool applied = false;
      bool result = true;

      if (auto value = getDouble(openstudio::OtherEquipmentFields::DesignLevel, true)) {
        const bool fieldResult = setDouble(openstudio::OtherEquipmentFields::DesignLevel, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }
      if (auto value = getDouble(openstudio::OtherEquipmentFields::PowerperFloorArea, true)) {
        const bool fieldResult = setDouble(openstudio::OtherEquipmentFields::PowerperFloorArea, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }
      if (auto value = getDouble(openstudio::OtherEquipmentFields::PowerperPerson, true)) {
        const bool fieldResult = setDouble(openstudio::OtherEquipmentFields::PowerperPerson, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }

      return applied && result;
    }

    void OtherEquipment_Impl::resetMultiplier() {
      // No dedicated translated multiplier field exists on EnergyPlus OtherEquipment.
    }

    std::vector<std::string> OtherEquipment_Impl::designLevelCalculationMethodValues() const {
      return openstudio::epmodel::OtherEquipment::designLevelCalculationMethodValues();
    }

    std::vector<std::string> OtherEquipment_Impl::fuelTypeValues() const {
      return openstudio::epmodel::OtherEquipment::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
