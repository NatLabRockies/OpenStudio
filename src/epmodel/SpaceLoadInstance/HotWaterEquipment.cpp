/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/HotWaterEquipment.hpp"
#include "SpaceLoadInstance/HotWaterEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HotWaterEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HotWaterEquipment::HotWaterEquipment(const Model& model) : ModelObject(HotWaterEquipment::iddObjectType(), model) {}

HotWaterEquipment::HotWaterEquipment(std::shared_ptr<detail::HotWaterEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HotWaterEquipment::iddObjectType() {
  return IddObjectType::HotWaterEquipment;
}

std::vector<std::string> HotWaterEquipment::designLevelCalculationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HotWaterEquipmentFields::DesignLevelCalculationMethod);
}

std::string HotWaterEquipment::designLevelCalculationMethod() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->designLevelCalculationMethod();
}

bool HotWaterEquipment::isDesignLevelCalculationMethodDefaulted() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->isDesignLevelCalculationMethodDefaulted();
}

bool HotWaterEquipment::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setDesignLevelCalculationMethod(designLevelCalculationMethod);
}

void HotWaterEquipment::resetDesignLevelCalculationMethod() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetDesignLevelCalculationMethod();
}

boost::optional<double> HotWaterEquipment::designLevel() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->designLevel();
}

bool HotWaterEquipment::setDesignLevel(double designLevel) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setDesignLevel(designLevel);
}

void HotWaterEquipment::resetDesignLevel() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetDesignLevel();
}

boost::optional<double> HotWaterEquipment::powerPerFloorArea() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->powerPerFloorArea();
}

bool HotWaterEquipment::setPowerPerFloorArea(double powerPerFloorArea) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setPowerPerFloorArea(powerPerFloorArea);
}

void HotWaterEquipment::resetPowerPerFloorArea() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetPowerPerFloorArea();
}

boost::optional<double> HotWaterEquipment::powerPerPerson() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->powerPerPerson();
}

bool HotWaterEquipment::setPowerPerPerson(double powerPerPerson) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setPowerPerPerson(powerPerPerson);
}

void HotWaterEquipment::resetPowerPerPerson() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetPowerPerPerson();
}

double HotWaterEquipment::fractionLatent() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->fractionLatent();
}

bool HotWaterEquipment::isFractionLatentDefaulted() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->isFractionLatentDefaulted();
}

bool HotWaterEquipment::setFractionLatent(double fractionLatent) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setFractionLatent(fractionLatent);
}

void HotWaterEquipment::resetFractionLatent() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetFractionLatent();
}

double HotWaterEquipment::fractionRadiant() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->fractionRadiant();
}

bool HotWaterEquipment::isFractionRadiantDefaulted() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->isFractionRadiantDefaulted();
}

bool HotWaterEquipment::setFractionRadiant(double fractionRadiant) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setFractionRadiant(fractionRadiant);
}

void HotWaterEquipment::resetFractionRadiant() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetFractionRadiant();
}

double HotWaterEquipment::fractionLost() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->fractionLost();
}

bool HotWaterEquipment::isFractionLostDefaulted() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->isFractionLostDefaulted();
}

bool HotWaterEquipment::setFractionLost(double fractionLost) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setFractionLost(fractionLost);
}

void HotWaterEquipment::resetFractionLost() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetFractionLost();
}

std::string HotWaterEquipment::endUseSubcategory() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->endUseSubcategory();
}

bool HotWaterEquipment::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::HotWaterEquipment_Impl>()->isEndUseSubcategoryDefaulted();
}

bool HotWaterEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void HotWaterEquipment::resetEndUseSubcategory() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetEndUseSubcategory();
}

bool HotWaterEquipment::setMultiplier(double multiplier) {
  return getImpl<detail::HotWaterEquipment_Impl>()->setMultiplier(multiplier);
}

void HotWaterEquipment::resetMultiplier() {
  getImpl<detail::HotWaterEquipment_Impl>()->resetMultiplier();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HotWaterEquipment_Impl::designLevelCalculationMethod() const {
  const auto value = getString(openstudio::HotWaterEquipmentFields::DesignLevelCalculationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HotWaterEquipment_Impl::isDesignLevelCalculationMethodDefaulted() const {
  return isEmpty(openstudio::HotWaterEquipmentFields::DesignLevelCalculationMethod);
}

bool HotWaterEquipment_Impl::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
  return setString(openstudio::HotWaterEquipmentFields::DesignLevelCalculationMethod, designLevelCalculationMethod);
}

void HotWaterEquipment_Impl::resetDesignLevelCalculationMethod() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::DesignLevelCalculationMethod, ""));
}

boost::optional<double> HotWaterEquipment_Impl::designLevel() const {
  return getDouble(openstudio::HotWaterEquipmentFields::DesignLevel, true);
}

bool HotWaterEquipment_Impl::setDesignLevel(double designLevel) {
  return setDouble(openstudio::HotWaterEquipmentFields::DesignLevel, designLevel);
}

void HotWaterEquipment_Impl::resetDesignLevel() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::DesignLevel, ""));
}

boost::optional<double> HotWaterEquipment_Impl::powerPerFloorArea() const {
  return getDouble(openstudio::HotWaterEquipmentFields::PowerperFloorArea, true);
}

bool HotWaterEquipment_Impl::setPowerPerFloorArea(double powerPerFloorArea) {
  return setDouble(openstudio::HotWaterEquipmentFields::PowerperFloorArea, powerPerFloorArea);
}

void HotWaterEquipment_Impl::resetPowerPerFloorArea() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::PowerperFloorArea, ""));
}

boost::optional<double> HotWaterEquipment_Impl::powerPerPerson() const {
  return getDouble(openstudio::HotWaterEquipmentFields::PowerperPerson, true);
}

bool HotWaterEquipment_Impl::setPowerPerPerson(double powerPerPerson) {
  return setDouble(openstudio::HotWaterEquipmentFields::PowerperPerson, powerPerPerson);
}

void HotWaterEquipment_Impl::resetPowerPerPerson() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::PowerperPerson, ""));
}

double HotWaterEquipment_Impl::fractionLatent() const {
  const auto value = getDouble(openstudio::HotWaterEquipmentFields::FractionLatent, true);
  OS_ASSERT(value);
  return *value;
}

bool HotWaterEquipment_Impl::isFractionLatentDefaulted() const {
  return isEmpty(openstudio::HotWaterEquipmentFields::FractionLatent);
}

bool HotWaterEquipment_Impl::setFractionLatent(double fractionLatent) {
  return setDouble(openstudio::HotWaterEquipmentFields::FractionLatent, fractionLatent);
}

void HotWaterEquipment_Impl::resetFractionLatent() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::FractionLatent, ""));
}

double HotWaterEquipment_Impl::fractionRadiant() const {
  const auto value = getDouble(openstudio::HotWaterEquipmentFields::FractionRadiant, true);
  OS_ASSERT(value);
  return *value;
}

bool HotWaterEquipment_Impl::isFractionRadiantDefaulted() const {
  return isEmpty(openstudio::HotWaterEquipmentFields::FractionRadiant);
}

bool HotWaterEquipment_Impl::setFractionRadiant(double fractionRadiant) {
  return setDouble(openstudio::HotWaterEquipmentFields::FractionRadiant, fractionRadiant);
}

void HotWaterEquipment_Impl::resetFractionRadiant() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::FractionRadiant, ""));
}

double HotWaterEquipment_Impl::fractionLost() const {
  const auto value = getDouble(openstudio::HotWaterEquipmentFields::FractionLost, true);
  OS_ASSERT(value);
  return *value;
}

bool HotWaterEquipment_Impl::isFractionLostDefaulted() const {
  return isEmpty(openstudio::HotWaterEquipmentFields::FractionLost);
}

bool HotWaterEquipment_Impl::setFractionLost(double fractionLost) {
  return setDouble(openstudio::HotWaterEquipmentFields::FractionLost, fractionLost);
}

void HotWaterEquipment_Impl::resetFractionLost() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::FractionLost, ""));
}

std::string HotWaterEquipment_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::HotWaterEquipmentFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool HotWaterEquipment_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::HotWaterEquipmentFields::EndUseSubcategory);
}

bool HotWaterEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::HotWaterEquipmentFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void HotWaterEquipment_Impl::resetEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::HotWaterEquipmentFields::EndUseSubcategory, ""));
}

bool HotWaterEquipment_Impl::setMultiplier(double multiplier) {
  // EnergyPlus HotWaterEquipment has no dedicated multiplier field. Preserve model API by
  // scaling whichever design-level scalar field(s) are currently populated.
  bool applied = false;
  bool result = true;

  if (auto value = getDouble(openstudio::HotWaterEquipmentFields::DesignLevel, true)) {
    const bool fieldResult = setDouble(openstudio::HotWaterEquipmentFields::DesignLevel, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::HotWaterEquipmentFields::PowerperFloorArea, true)) {
    const bool fieldResult = setDouble(openstudio::HotWaterEquipmentFields::PowerperFloorArea, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::HotWaterEquipmentFields::PowerperPerson, true)) {
    const bool fieldResult = setDouble(openstudio::HotWaterEquipmentFields::PowerperPerson, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }

  return applied && result;
}

void HotWaterEquipment_Impl::resetMultiplier() {
  // No dedicated translated multiplier field exists on EnergyPlus HotWaterEquipment.
}

std::vector<std::string> HotWaterEquipment_Impl::designLevelCalculationMethodValues() const {
  return openstudio::epmodel::HotWaterEquipment::designLevelCalculationMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
