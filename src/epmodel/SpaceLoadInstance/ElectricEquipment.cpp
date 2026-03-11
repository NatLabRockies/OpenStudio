/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/ElectricEquipment.hpp"
#include "SpaceLoadInstance/ElectricEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

ElectricEquipment::ElectricEquipment(const Model& model) : ModelObject(ElectricEquipment::iddObjectType(), model) {}

ElectricEquipment::ElectricEquipment(std::shared_ptr<detail::ElectricEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ElectricEquipment::iddObjectType() {
  return IddObjectType::ElectricEquipment;
}

std::vector<std::string> ElectricEquipment::designLevelCalculationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ElectricEquipmentFields::DesignLevelCalculationMethod);
}

std::string ElectricEquipment::designLevelCalculationMethod() const {
  return getImpl<detail::ElectricEquipment_Impl>()->designLevelCalculationMethod();
}

bool ElectricEquipment::isDesignLevelCalculationMethodDefaulted() const {
  return getImpl<detail::ElectricEquipment_Impl>()->isDesignLevelCalculationMethodDefaulted();
}

bool ElectricEquipment::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
  return getImpl<detail::ElectricEquipment_Impl>()->setDesignLevelCalculationMethod(designLevelCalculationMethod);
}

void ElectricEquipment::resetDesignLevelCalculationMethod() {
  getImpl<detail::ElectricEquipment_Impl>()->resetDesignLevelCalculationMethod();
}

boost::optional<double> ElectricEquipment::designLevel() const {
  return getImpl<detail::ElectricEquipment_Impl>()->designLevel();
}

bool ElectricEquipment::setDesignLevel(double designLevel) {
  return getImpl<detail::ElectricEquipment_Impl>()->setDesignLevel(designLevel);
}

void ElectricEquipment::resetDesignLevel() {
  getImpl<detail::ElectricEquipment_Impl>()->resetDesignLevel();
}

boost::optional<double> ElectricEquipment::powerPerFloorArea() const {
  return getImpl<detail::ElectricEquipment_Impl>()->powerPerFloorArea();
}

bool ElectricEquipment::setPowerPerFloorArea(double powerPerFloorArea) {
  return getImpl<detail::ElectricEquipment_Impl>()->setPowerPerFloorArea(powerPerFloorArea);
}

void ElectricEquipment::resetPowerPerFloorArea() {
  getImpl<detail::ElectricEquipment_Impl>()->resetPowerPerFloorArea();
}

boost::optional<double> ElectricEquipment::powerPerPerson() const {
  return getImpl<detail::ElectricEquipment_Impl>()->powerPerPerson();
}

bool ElectricEquipment::setPowerPerPerson(double powerPerPerson) {
  return getImpl<detail::ElectricEquipment_Impl>()->setPowerPerPerson(powerPerPerson);
}

void ElectricEquipment::resetPowerPerPerson() {
  getImpl<detail::ElectricEquipment_Impl>()->resetPowerPerPerson();
}

double ElectricEquipment::fractionLatent() const {
  return getImpl<detail::ElectricEquipment_Impl>()->fractionLatent();
}

bool ElectricEquipment::isFractionLatentDefaulted() const {
  return getImpl<detail::ElectricEquipment_Impl>()->isFractionLatentDefaulted();
}

bool ElectricEquipment::setFractionLatent(double fractionLatent) {
  return getImpl<detail::ElectricEquipment_Impl>()->setFractionLatent(fractionLatent);
}

void ElectricEquipment::resetFractionLatent() {
  getImpl<detail::ElectricEquipment_Impl>()->resetFractionLatent();
}

double ElectricEquipment::fractionRadiant() const {
  return getImpl<detail::ElectricEquipment_Impl>()->fractionRadiant();
}

bool ElectricEquipment::isFractionRadiantDefaulted() const {
  return getImpl<detail::ElectricEquipment_Impl>()->isFractionRadiantDefaulted();
}

bool ElectricEquipment::setFractionRadiant(double fractionRadiant) {
  return getImpl<detail::ElectricEquipment_Impl>()->setFractionRadiant(fractionRadiant);
}

void ElectricEquipment::resetFractionRadiant() {
  getImpl<detail::ElectricEquipment_Impl>()->resetFractionRadiant();
}

double ElectricEquipment::fractionLost() const {
  return getImpl<detail::ElectricEquipment_Impl>()->fractionLost();
}

bool ElectricEquipment::isFractionLostDefaulted() const {
  return getImpl<detail::ElectricEquipment_Impl>()->isFractionLostDefaulted();
}

bool ElectricEquipment::setFractionLost(double fractionLost) {
  return getImpl<detail::ElectricEquipment_Impl>()->setFractionLost(fractionLost);
}

void ElectricEquipment::resetFractionLost() {
  getImpl<detail::ElectricEquipment_Impl>()->resetFractionLost();
}

std::string ElectricEquipment::endUseSubcategory() const {
  return getImpl<detail::ElectricEquipment_Impl>()->endUseSubcategory();
}

bool ElectricEquipment::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ElectricEquipment_Impl>()->isEndUseSubcategoryDefaulted();
}

bool ElectricEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::ElectricEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void ElectricEquipment::resetEndUseSubcategory() {
  getImpl<detail::ElectricEquipment_Impl>()->resetEndUseSubcategory();
}

bool ElectricEquipment::setMultiplier(double multiplier) {
  return getImpl<detail::ElectricEquipment_Impl>()->setMultiplier(multiplier);
}

void ElectricEquipment::resetMultiplier() {
  getImpl<detail::ElectricEquipment_Impl>()->resetMultiplier();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ElectricEquipment_Impl::designLevelCalculationMethod() const {
  const auto value = getString(openstudio::ElectricEquipmentFields::DesignLevelCalculationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipment_Impl::isDesignLevelCalculationMethodDefaulted() const {
  return isEmpty(openstudio::ElectricEquipmentFields::DesignLevelCalculationMethod);
}

bool ElectricEquipment_Impl::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
  return setString(openstudio::ElectricEquipmentFields::DesignLevelCalculationMethod, designLevelCalculationMethod);
}

void ElectricEquipment_Impl::resetDesignLevelCalculationMethod() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::DesignLevelCalculationMethod, ""));
}

boost::optional<double> ElectricEquipment_Impl::designLevel() const {
  return getDouble(openstudio::ElectricEquipmentFields::DesignLevel, true);
}

bool ElectricEquipment_Impl::setDesignLevel(double designLevel) {
  return setDouble(openstudio::ElectricEquipmentFields::DesignLevel, designLevel);
}

void ElectricEquipment_Impl::resetDesignLevel() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::DesignLevel, ""));
}

boost::optional<double> ElectricEquipment_Impl::powerPerFloorArea() const {
  return getDouble(openstudio::ElectricEquipmentFields::WattsperFloorArea, true);
}

bool ElectricEquipment_Impl::setPowerPerFloorArea(double powerPerFloorArea) {
  return setDouble(openstudio::ElectricEquipmentFields::WattsperFloorArea, powerPerFloorArea);
}

void ElectricEquipment_Impl::resetPowerPerFloorArea() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::WattsperFloorArea, ""));
}

boost::optional<double> ElectricEquipment_Impl::powerPerPerson() const {
  return getDouble(openstudio::ElectricEquipmentFields::WattsperPerson, true);
}

bool ElectricEquipment_Impl::setPowerPerPerson(double powerPerPerson) {
  return setDouble(openstudio::ElectricEquipmentFields::WattsperPerson, powerPerPerson);
}

void ElectricEquipment_Impl::resetPowerPerPerson() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::WattsperPerson, ""));
}

double ElectricEquipment_Impl::fractionLatent() const {
  const auto value = getDouble(openstudio::ElectricEquipmentFields::FractionLatent, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipment_Impl::isFractionLatentDefaulted() const {
  return isEmpty(openstudio::ElectricEquipmentFields::FractionLatent);
}

bool ElectricEquipment_Impl::setFractionLatent(double fractionLatent) {
  return setDouble(openstudio::ElectricEquipmentFields::FractionLatent, fractionLatent);
}

void ElectricEquipment_Impl::resetFractionLatent() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::FractionLatent, ""));
}

double ElectricEquipment_Impl::fractionRadiant() const {
  const auto value = getDouble(openstudio::ElectricEquipmentFields::FractionRadiant, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipment_Impl::isFractionRadiantDefaulted() const {
  return isEmpty(openstudio::ElectricEquipmentFields::FractionRadiant);
}

bool ElectricEquipment_Impl::setFractionRadiant(double fractionRadiant) {
  return setDouble(openstudio::ElectricEquipmentFields::FractionRadiant, fractionRadiant);
}

void ElectricEquipment_Impl::resetFractionRadiant() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::FractionRadiant, ""));
}

double ElectricEquipment_Impl::fractionLost() const {
  const auto value = getDouble(openstudio::ElectricEquipmentFields::FractionLost, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipment_Impl::isFractionLostDefaulted() const {
  return isEmpty(openstudio::ElectricEquipmentFields::FractionLost);
}

bool ElectricEquipment_Impl::setFractionLost(double fractionLost) {
  return setDouble(openstudio::ElectricEquipmentFields::FractionLost, fractionLost);
}

void ElectricEquipment_Impl::resetFractionLost() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::FractionLost, ""));
}

std::string ElectricEquipment_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::ElectricEquipmentFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipment_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::ElectricEquipmentFields::EndUseSubcategory);
}

bool ElectricEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::ElectricEquipmentFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ElectricEquipment_Impl::resetEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::ElectricEquipmentFields::EndUseSubcategory, ""));
}

bool ElectricEquipment_Impl::setMultiplier(double multiplier) {
  // EnergyPlus ElectricEquipment has no dedicated multiplier field. Preserve model API by
  // scaling whichever design-level scalar field(s) are currently populated.
  bool applied = false;
  bool result = true;

  if (auto value = getDouble(openstudio::ElectricEquipmentFields::DesignLevel, true)) {
    const bool fieldResult = setDouble(openstudio::ElectricEquipmentFields::DesignLevel, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::ElectricEquipmentFields::WattsperFloorArea, true)) {
    const bool fieldResult = setDouble(openstudio::ElectricEquipmentFields::WattsperFloorArea, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::ElectricEquipmentFields::WattsperPerson, true)) {
    const bool fieldResult = setDouble(openstudio::ElectricEquipmentFields::WattsperPerson, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }

  return applied && result;
}

void ElectricEquipment_Impl::resetMultiplier() {
  // No dedicated translated multiplier field exists on EnergyPlus ElectricEquipment.
}

std::vector<std::string> ElectricEquipment_Impl::designLevelCalculationMethodValues() const {
  return openstudio::epmodel::ElectricEquipment::designLevelCalculationMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
