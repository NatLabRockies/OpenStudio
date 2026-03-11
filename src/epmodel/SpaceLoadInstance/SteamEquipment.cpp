/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/SteamEquipment.hpp"
#include "SpaceLoadInstance/SteamEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SteamEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SteamEquipment::SteamEquipment(const Model& model) : ModelObject(SteamEquipment::iddObjectType(), model) {}

  SteamEquipment::SteamEquipment(std::shared_ptr<detail::SteamEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SteamEquipment::iddObjectType() {
    return IddObjectType::SteamEquipment;
  }

  std::vector<std::string> SteamEquipment::designLevelCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SteamEquipmentFields::DesignLevelCalculationMethod);
  }

  std::string SteamEquipment::designLevelCalculationMethod() const {
    return getImpl<detail::SteamEquipment_Impl>()->designLevelCalculationMethod();
  }

  bool SteamEquipment::isDesignLevelCalculationMethodDefaulted() const {
    return getImpl<detail::SteamEquipment_Impl>()->isDesignLevelCalculationMethodDefaulted();
  }

  bool SteamEquipment::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
    return getImpl<detail::SteamEquipment_Impl>()->setDesignLevelCalculationMethod(designLevelCalculationMethod);
  }

  void SteamEquipment::resetDesignLevelCalculationMethod() {
    getImpl<detail::SteamEquipment_Impl>()->resetDesignLevelCalculationMethod();
  }

  boost::optional<double> SteamEquipment::designLevel() const {
    return getImpl<detail::SteamEquipment_Impl>()->designLevel();
  }

  bool SteamEquipment::setDesignLevel(double designLevel) {
    return getImpl<detail::SteamEquipment_Impl>()->setDesignLevel(designLevel);
  }

  void SteamEquipment::resetDesignLevel() {
    getImpl<detail::SteamEquipment_Impl>()->resetDesignLevel();
  }

  boost::optional<double> SteamEquipment::powerPerFloorArea() const {
    return getImpl<detail::SteamEquipment_Impl>()->powerPerFloorArea();
  }

  bool SteamEquipment::setPowerPerFloorArea(double powerPerFloorArea) {
    return getImpl<detail::SteamEquipment_Impl>()->setPowerPerFloorArea(powerPerFloorArea);
  }

  void SteamEquipment::resetPowerPerFloorArea() {
    getImpl<detail::SteamEquipment_Impl>()->resetPowerPerFloorArea();
  }

  boost::optional<double> SteamEquipment::powerPerPerson() const {
    return getImpl<detail::SteamEquipment_Impl>()->powerPerPerson();
  }

  bool SteamEquipment::setPowerPerPerson(double powerPerPerson) {
    return getImpl<detail::SteamEquipment_Impl>()->setPowerPerPerson(powerPerPerson);
  }

  void SteamEquipment::resetPowerPerPerson() {
    getImpl<detail::SteamEquipment_Impl>()->resetPowerPerPerson();
  }

  double SteamEquipment::fractionLatent() const {
    return getImpl<detail::SteamEquipment_Impl>()->fractionLatent();
  }

  bool SteamEquipment::isFractionLatentDefaulted() const {
    return getImpl<detail::SteamEquipment_Impl>()->isFractionLatentDefaulted();
  }

  bool SteamEquipment::setFractionLatent(double fractionLatent) {
    return getImpl<detail::SteamEquipment_Impl>()->setFractionLatent(fractionLatent);
  }

  void SteamEquipment::resetFractionLatent() {
    getImpl<detail::SteamEquipment_Impl>()->resetFractionLatent();
  }

  double SteamEquipment::fractionRadiant() const {
    return getImpl<detail::SteamEquipment_Impl>()->fractionRadiant();
  }

  bool SteamEquipment::isFractionRadiantDefaulted() const {
    return getImpl<detail::SteamEquipment_Impl>()->isFractionRadiantDefaulted();
  }

  bool SteamEquipment::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::SteamEquipment_Impl>()->setFractionRadiant(fractionRadiant);
  }

  void SteamEquipment::resetFractionRadiant() {
    getImpl<detail::SteamEquipment_Impl>()->resetFractionRadiant();
  }

  double SteamEquipment::fractionLost() const {
    return getImpl<detail::SteamEquipment_Impl>()->fractionLost();
  }

  bool SteamEquipment::isFractionLostDefaulted() const {
    return getImpl<detail::SteamEquipment_Impl>()->isFractionLostDefaulted();
  }

  bool SteamEquipment::setFractionLost(double fractionLost) {
    return getImpl<detail::SteamEquipment_Impl>()->setFractionLost(fractionLost);
  }

  void SteamEquipment::resetFractionLost() {
    getImpl<detail::SteamEquipment_Impl>()->resetFractionLost();
  }

  std::string SteamEquipment::endUseSubcategory() const {
    return getImpl<detail::SteamEquipment_Impl>()->endUseSubcategory();
  }

  bool SteamEquipment::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::SteamEquipment_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool SteamEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::SteamEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void SteamEquipment::resetEndUseSubcategory() {
    getImpl<detail::SteamEquipment_Impl>()->resetEndUseSubcategory();
  }

  bool SteamEquipment::setMultiplier(double multiplier) {
    return getImpl<detail::SteamEquipment_Impl>()->setMultiplier(multiplier);
  }

  void SteamEquipment::resetMultiplier() {
    getImpl<detail::SteamEquipment_Impl>()->resetMultiplier();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SteamEquipment_Impl::designLevelCalculationMethod() const {
      const auto value = getString(openstudio::SteamEquipmentFields::DesignLevelCalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SteamEquipment_Impl::isDesignLevelCalculationMethodDefaulted() const {
      return isEmpty(openstudio::SteamEquipmentFields::DesignLevelCalculationMethod);
    }

    bool SteamEquipment_Impl::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
      return setString(openstudio::SteamEquipmentFields::DesignLevelCalculationMethod, designLevelCalculationMethod);
    }

    void SteamEquipment_Impl::resetDesignLevelCalculationMethod() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::DesignLevelCalculationMethod, ""));
    }

    boost::optional<double> SteamEquipment_Impl::designLevel() const {
      return getDouble(openstudio::SteamEquipmentFields::DesignLevel, true);
    }

    bool SteamEquipment_Impl::setDesignLevel(double designLevel) {
      return setDouble(openstudio::SteamEquipmentFields::DesignLevel, designLevel);
    }

    void SteamEquipment_Impl::resetDesignLevel() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::DesignLevel, ""));
    }

    boost::optional<double> SteamEquipment_Impl::powerPerFloorArea() const {
      return getDouble(openstudio::SteamEquipmentFields::PowerperFloorArea, true);
    }

    bool SteamEquipment_Impl::setPowerPerFloorArea(double powerPerFloorArea) {
      return setDouble(openstudio::SteamEquipmentFields::PowerperFloorArea, powerPerFloorArea);
    }

    void SteamEquipment_Impl::resetPowerPerFloorArea() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::PowerperFloorArea, ""));
    }

    boost::optional<double> SteamEquipment_Impl::powerPerPerson() const {
      return getDouble(openstudio::SteamEquipmentFields::PowerperPerson, true);
    }

    bool SteamEquipment_Impl::setPowerPerPerson(double powerPerPerson) {
      return setDouble(openstudio::SteamEquipmentFields::PowerperPerson, powerPerPerson);
    }

    void SteamEquipment_Impl::resetPowerPerPerson() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::PowerperPerson, ""));
    }

    double SteamEquipment_Impl::fractionLatent() const {
      const auto value = getDouble(openstudio::SteamEquipmentFields::FractionLatent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SteamEquipment_Impl::isFractionLatentDefaulted() const {
      return isEmpty(openstudio::SteamEquipmentFields::FractionLatent);
    }

    bool SteamEquipment_Impl::setFractionLatent(double fractionLatent) {
      return setDouble(openstudio::SteamEquipmentFields::FractionLatent, fractionLatent);
    }

    void SteamEquipment_Impl::resetFractionLatent() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::FractionLatent, ""));
    }

    double SteamEquipment_Impl::fractionRadiant() const {
      const auto value = getDouble(openstudio::SteamEquipmentFields::FractionRadiant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SteamEquipment_Impl::isFractionRadiantDefaulted() const {
      return isEmpty(openstudio::SteamEquipmentFields::FractionRadiant);
    }

    bool SteamEquipment_Impl::setFractionRadiant(double fractionRadiant) {
      return setDouble(openstudio::SteamEquipmentFields::FractionRadiant, fractionRadiant);
    }

    void SteamEquipment_Impl::resetFractionRadiant() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::FractionRadiant, ""));
    }

    double SteamEquipment_Impl::fractionLost() const {
      const auto value = getDouble(openstudio::SteamEquipmentFields::FractionLost, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SteamEquipment_Impl::isFractionLostDefaulted() const {
      return isEmpty(openstudio::SteamEquipmentFields::FractionLost);
    }

    bool SteamEquipment_Impl::setFractionLost(double fractionLost) {
      return setDouble(openstudio::SteamEquipmentFields::FractionLost, fractionLost);
    }

    void SteamEquipment_Impl::resetFractionLost() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::FractionLost, ""));
    }

    std::string SteamEquipment_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::SteamEquipmentFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SteamEquipment_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::SteamEquipmentFields::EndUseSubcategory);
    }

    bool SteamEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::SteamEquipmentFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void SteamEquipment_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::SteamEquipmentFields::EndUseSubcategory, ""));
    }

    bool SteamEquipment_Impl::setMultiplier(double multiplier) {
      // EnergyPlus SteamEquipment has no dedicated multiplier field. Preserve model API by
      // scaling whichever design-level scalar field(s) are currently populated.
      bool applied = false;
      bool result = true;

      if (auto value = getDouble(openstudio::SteamEquipmentFields::DesignLevel, true)) {
        const bool fieldResult = setDouble(openstudio::SteamEquipmentFields::DesignLevel, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }
      if (auto value = getDouble(openstudio::SteamEquipmentFields::PowerperFloorArea, true)) {
        const bool fieldResult = setDouble(openstudio::SteamEquipmentFields::PowerperFloorArea, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }
      if (auto value = getDouble(openstudio::SteamEquipmentFields::PowerperPerson, true)) {
        const bool fieldResult = setDouble(openstudio::SteamEquipmentFields::PowerperPerson, (*value) * multiplier);
        OS_ASSERT(fieldResult);
        result = result && fieldResult;
        applied = true;
      }

      return applied && result;
    }

    void SteamEquipment_Impl::resetMultiplier() {
      // No dedicated translated multiplier field exists on EnergyPlus SteamEquipment.
    }

    std::vector<std::string> SteamEquipment_Impl::designLevelCalculationMethodValues() const {
      return openstudio::epmodel::SteamEquipment::designLevelCalculationMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
