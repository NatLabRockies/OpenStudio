/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/GasEquipment.hpp"
#include "SpaceLoadInstance/GasEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GasEquipment_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GasEquipment::GasEquipment(const Model& model) : ModelObject(GasEquipment::iddObjectType(), model) {}

GasEquipment::GasEquipment(std::shared_ptr<detail::GasEquipment_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GasEquipment::iddObjectType() {
  return IddObjectType::GasEquipment;
}

std::vector<std::string> GasEquipment::designLevelCalculationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::GasEquipmentFields::DesignLevelCalculationMethod);
}

std::string GasEquipment::designLevelCalculationMethod() const {
  return getImpl<detail::GasEquipment_Impl>()->designLevelCalculationMethod();
}

bool GasEquipment::isDesignLevelCalculationMethodDefaulted() const {
  return getImpl<detail::GasEquipment_Impl>()->isDesignLevelCalculationMethodDefaulted();
}

bool GasEquipment::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
  return getImpl<detail::GasEquipment_Impl>()->setDesignLevelCalculationMethod(designLevelCalculationMethod);
}

void GasEquipment::resetDesignLevelCalculationMethod() {
  getImpl<detail::GasEquipment_Impl>()->resetDesignLevelCalculationMethod();
}

boost::optional<double> GasEquipment::designLevel() const {
  return getImpl<detail::GasEquipment_Impl>()->designLevel();
}

bool GasEquipment::setDesignLevel(double designLevel) {
  return getImpl<detail::GasEquipment_Impl>()->setDesignLevel(designLevel);
}

void GasEquipment::resetDesignLevel() {
  getImpl<detail::GasEquipment_Impl>()->resetDesignLevel();
}

boost::optional<double> GasEquipment::powerPerFloorArea() const {
  return getImpl<detail::GasEquipment_Impl>()->powerPerFloorArea();
}

bool GasEquipment::setPowerPerFloorArea(double powerPerFloorArea) {
  return getImpl<detail::GasEquipment_Impl>()->setPowerPerFloorArea(powerPerFloorArea);
}

void GasEquipment::resetPowerPerFloorArea() {
  getImpl<detail::GasEquipment_Impl>()->resetPowerPerFloorArea();
}

boost::optional<double> GasEquipment::powerPerPerson() const {
  return getImpl<detail::GasEquipment_Impl>()->powerPerPerson();
}

bool GasEquipment::setPowerPerPerson(double powerPerPerson) {
  return getImpl<detail::GasEquipment_Impl>()->setPowerPerPerson(powerPerPerson);
}

void GasEquipment::resetPowerPerPerson() {
  getImpl<detail::GasEquipment_Impl>()->resetPowerPerPerson();
}

double GasEquipment::fractionLatent() const {
  return getImpl<detail::GasEquipment_Impl>()->fractionLatent();
}

bool GasEquipment::isFractionLatentDefaulted() const {
  return getImpl<detail::GasEquipment_Impl>()->isFractionLatentDefaulted();
}

bool GasEquipment::setFractionLatent(double fractionLatent) {
  return getImpl<detail::GasEquipment_Impl>()->setFractionLatent(fractionLatent);
}

void GasEquipment::resetFractionLatent() {
  getImpl<detail::GasEquipment_Impl>()->resetFractionLatent();
}

double GasEquipment::fractionRadiant() const {
  return getImpl<detail::GasEquipment_Impl>()->fractionRadiant();
}

bool GasEquipment::isFractionRadiantDefaulted() const {
  return getImpl<detail::GasEquipment_Impl>()->isFractionRadiantDefaulted();
}

bool GasEquipment::setFractionRadiant(double fractionRadiant) {
  return getImpl<detail::GasEquipment_Impl>()->setFractionRadiant(fractionRadiant);
}

void GasEquipment::resetFractionRadiant() {
  getImpl<detail::GasEquipment_Impl>()->resetFractionRadiant();
}

double GasEquipment::fractionLost() const {
  return getImpl<detail::GasEquipment_Impl>()->fractionLost();
}

bool GasEquipment::isFractionLostDefaulted() const {
  return getImpl<detail::GasEquipment_Impl>()->isFractionLostDefaulted();
}

bool GasEquipment::setFractionLost(double fractionLost) {
  return getImpl<detail::GasEquipment_Impl>()->setFractionLost(fractionLost);
}

void GasEquipment::resetFractionLost() {
  getImpl<detail::GasEquipment_Impl>()->resetFractionLost();
}

double GasEquipment::carbonDioxideGenerationRate() const {
  return getImpl<detail::GasEquipment_Impl>()->carbonDioxideGenerationRate();
}

bool GasEquipment::isCarbonDioxideGenerationRateDefaulted() const {
  return getImpl<detail::GasEquipment_Impl>()->isCarbonDioxideGenerationRateDefaulted();
}

bool GasEquipment::setCarbonDioxideGenerationRate(double carbonDioxideGenerationRate) {
  return getImpl<detail::GasEquipment_Impl>()->setCarbonDioxideGenerationRate(carbonDioxideGenerationRate);
}

void GasEquipment::resetCarbonDioxideGenerationRate() {
  getImpl<detail::GasEquipment_Impl>()->resetCarbonDioxideGenerationRate();
}

std::string GasEquipment::endUseSubcategory() const {
  return getImpl<detail::GasEquipment_Impl>()->endUseSubcategory();
}

bool GasEquipment::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::GasEquipment_Impl>()->isEndUseSubcategoryDefaulted();
}

bool GasEquipment::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::GasEquipment_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void GasEquipment::resetEndUseSubcategory() {
  getImpl<detail::GasEquipment_Impl>()->resetEndUseSubcategory();
}

bool GasEquipment::setMultiplier(double multiplier) {
  return getImpl<detail::GasEquipment_Impl>()->setMultiplier(multiplier);
}

void GasEquipment::resetMultiplier() {
  getImpl<detail::GasEquipment_Impl>()->resetMultiplier();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string GasEquipment_Impl::designLevelCalculationMethod() const {
  const auto value = getString(openstudio::GasEquipmentFields::DesignLevelCalculationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool GasEquipment_Impl::isDesignLevelCalculationMethodDefaulted() const {
  return isEmpty(openstudio::GasEquipmentFields::DesignLevelCalculationMethod);
}

bool GasEquipment_Impl::setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod) {
  return setString(openstudio::GasEquipmentFields::DesignLevelCalculationMethod, designLevelCalculationMethod);
}

void GasEquipment_Impl::resetDesignLevelCalculationMethod() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::DesignLevelCalculationMethod, ""));
}

boost::optional<double> GasEquipment_Impl::designLevel() const {
  return getDouble(openstudio::GasEquipmentFields::DesignLevel, true);
}

bool GasEquipment_Impl::setDesignLevel(double designLevel) {
  return setDouble(openstudio::GasEquipmentFields::DesignLevel, designLevel);
}

void GasEquipment_Impl::resetDesignLevel() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::DesignLevel, ""));
}

boost::optional<double> GasEquipment_Impl::powerPerFloorArea() const {
  return getDouble(openstudio::GasEquipmentFields::PowerperFloorArea, true);
}

bool GasEquipment_Impl::setPowerPerFloorArea(double powerPerFloorArea) {
  return setDouble(openstudio::GasEquipmentFields::PowerperFloorArea, powerPerFloorArea);
}

void GasEquipment_Impl::resetPowerPerFloorArea() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::PowerperFloorArea, ""));
}

boost::optional<double> GasEquipment_Impl::powerPerPerson() const {
  return getDouble(openstudio::GasEquipmentFields::PowerperPerson, true);
}

bool GasEquipment_Impl::setPowerPerPerson(double powerPerPerson) {
  return setDouble(openstudio::GasEquipmentFields::PowerperPerson, powerPerPerson);
}

void GasEquipment_Impl::resetPowerPerPerson() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::PowerperPerson, ""));
}

double GasEquipment_Impl::fractionLatent() const {
  const auto value = getDouble(openstudio::GasEquipmentFields::FractionLatent, true);
  OS_ASSERT(value);
  return *value;
}

bool GasEquipment_Impl::isFractionLatentDefaulted() const {
  return isEmpty(openstudio::GasEquipmentFields::FractionLatent);
}

bool GasEquipment_Impl::setFractionLatent(double fractionLatent) {
  return setDouble(openstudio::GasEquipmentFields::FractionLatent, fractionLatent);
}

void GasEquipment_Impl::resetFractionLatent() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::FractionLatent, ""));
}

double GasEquipment_Impl::fractionRadiant() const {
  const auto value = getDouble(openstudio::GasEquipmentFields::FractionRadiant, true);
  OS_ASSERT(value);
  return *value;
}

bool GasEquipment_Impl::isFractionRadiantDefaulted() const {
  return isEmpty(openstudio::GasEquipmentFields::FractionRadiant);
}

bool GasEquipment_Impl::setFractionRadiant(double fractionRadiant) {
  return setDouble(openstudio::GasEquipmentFields::FractionRadiant, fractionRadiant);
}

void GasEquipment_Impl::resetFractionRadiant() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::FractionRadiant, ""));
}

double GasEquipment_Impl::fractionLost() const {
  const auto value = getDouble(openstudio::GasEquipmentFields::FractionLost, true);
  OS_ASSERT(value);
  return *value;
}

bool GasEquipment_Impl::isFractionLostDefaulted() const {
  return isEmpty(openstudio::GasEquipmentFields::FractionLost);
}

bool GasEquipment_Impl::setFractionLost(double fractionLost) {
  return setDouble(openstudio::GasEquipmentFields::FractionLost, fractionLost);
}

void GasEquipment_Impl::resetFractionLost() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::FractionLost, ""));
}

double GasEquipment_Impl::carbonDioxideGenerationRate() const {
  const auto value = getDouble(openstudio::GasEquipmentFields::CarbonDioxideGenerationRate, true);
  OS_ASSERT(value);
  return *value;
}

bool GasEquipment_Impl::isCarbonDioxideGenerationRateDefaulted() const {
  return isEmpty(openstudio::GasEquipmentFields::CarbonDioxideGenerationRate);
}

bool GasEquipment_Impl::setCarbonDioxideGenerationRate(double carbonDioxideGenerationRate) {
  return setDouble(openstudio::GasEquipmentFields::CarbonDioxideGenerationRate, carbonDioxideGenerationRate);
}

void GasEquipment_Impl::resetCarbonDioxideGenerationRate() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::CarbonDioxideGenerationRate, ""));
}

std::string GasEquipment_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::GasEquipmentFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool GasEquipment_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::GasEquipmentFields::EndUseSubcategory);
}

bool GasEquipment_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::GasEquipmentFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void GasEquipment_Impl::resetEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::GasEquipmentFields::EndUseSubcategory, ""));
}

bool GasEquipment_Impl::setMultiplier(double multiplier) {
  // EnergyPlus GasEquipment has no dedicated multiplier field. Preserve model API by
  // scaling whichever design-level scalar field(s) are currently populated.
  bool applied = false;
  bool result = true;

  if (auto value = getDouble(openstudio::GasEquipmentFields::DesignLevel, true)) {
    const bool fieldResult = setDouble(openstudio::GasEquipmentFields::DesignLevel, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::GasEquipmentFields::PowerperFloorArea, true)) {
    const bool fieldResult = setDouble(openstudio::GasEquipmentFields::PowerperFloorArea, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }
  if (auto value = getDouble(openstudio::GasEquipmentFields::PowerperPerson, true)) {
    const bool fieldResult = setDouble(openstudio::GasEquipmentFields::PowerperPerson, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }

  return applied && result;
}

void GasEquipment_Impl::resetMultiplier() {
  // No dedicated translated multiplier field exists on EnergyPlus GasEquipment.
}

std::vector<std::string> GasEquipment_Impl::designLevelCalculationMethodValues() const {
  return openstudio::epmodel::GasEquipment::designLevelCalculationMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
