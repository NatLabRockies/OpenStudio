/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceLoadInstance/ElectricEquipmentITEAirCooled.hpp"
#include "SpaceLoadInstance/ElectricEquipmentITEAirCooled_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricEquipment_ITE_AirCooled_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ElectricEquipmentITEAirCooled::ElectricEquipmentITEAirCooled(const Model& model)
  : ModelObject(ElectricEquipmentITEAirCooled::iddObjectType(), model) {}

ElectricEquipmentITEAirCooled::ElectricEquipmentITEAirCooled(std::shared_ptr<detail::ElectricEquipmentITEAirCooled_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ElectricEquipmentITEAirCooled::iddObjectType() {
  return IddObjectType::ElectricEquipment_ITE_AirCooled;
}

std::string ElectricEquipmentITEAirCooled::cPUEndUseSubcategory() const {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->cPUEndUseSubcategory();
}

bool ElectricEquipmentITEAirCooled::isCPUEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->isCPUEndUseSubcategoryDefaulted();
}

bool ElectricEquipmentITEAirCooled::setCPUEndUseSubcategory(const std::string& cPUEndUseSubcategory) {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->setCPUEndUseSubcategory(cPUEndUseSubcategory);
}

void ElectricEquipmentITEAirCooled::resetCPUEndUseSubcategory() {
  getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->resetCPUEndUseSubcategory();
}

std::string ElectricEquipmentITEAirCooled::fanEndUseSubcategory() const {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->fanEndUseSubcategory();
}

bool ElectricEquipmentITEAirCooled::isFanEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->isFanEndUseSubcategoryDefaulted();
}

bool ElectricEquipmentITEAirCooled::setFanEndUseSubcategory(const std::string& fanEndUseSubcategory) {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->setFanEndUseSubcategory(fanEndUseSubcategory);
}

void ElectricEquipmentITEAirCooled::resetFanEndUseSubcategory() {
  getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->resetFanEndUseSubcategory();
}

std::string ElectricEquipmentITEAirCooled::electricPowerSupplyEndUseSubcategory() const {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->electricPowerSupplyEndUseSubcategory();
}

bool ElectricEquipmentITEAirCooled::isElectricPowerSupplyEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->isElectricPowerSupplyEndUseSubcategoryDefaulted();
}

bool ElectricEquipmentITEAirCooled::setElectricPowerSupplyEndUseSubcategory(const std::string& electricPowerSupplyEndUseSubcategory) {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->setElectricPowerSupplyEndUseSubcategory(electricPowerSupplyEndUseSubcategory);
}

void ElectricEquipmentITEAirCooled::resetElectricPowerSupplyEndUseSubcategory() {
  getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->resetElectricPowerSupplyEndUseSubcategory();
}

bool ElectricEquipmentITEAirCooled::setMultiplier(double multiplier) {
  return getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->setMultiplier(multiplier);
}

void ElectricEquipmentITEAirCooled::resetMultiplier() {
  getImpl<detail::ElectricEquipmentITEAirCooled_Impl>()->resetMultiplier();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ElectricEquipmentITEAirCooled_Impl::cPUEndUseSubcategory() const {
  const auto value = getString(openstudio::ElectricEquipment_ITE_AirCooledFields::CPUEndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipmentITEAirCooled_Impl::isCPUEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::ElectricEquipment_ITE_AirCooledFields::CPUEndUseSubcategory);
}

bool ElectricEquipmentITEAirCooled_Impl::setCPUEndUseSubcategory(const std::string& cPUEndUseSubcategory) {
  const bool result = setString(openstudio::ElectricEquipment_ITE_AirCooledFields::CPUEndUseSubcategory, cPUEndUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ElectricEquipmentITEAirCooled_Impl::resetCPUEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::ElectricEquipment_ITE_AirCooledFields::CPUEndUseSubcategory, ""));
}

std::string ElectricEquipmentITEAirCooled_Impl::fanEndUseSubcategory() const {
  const auto value = getString(openstudio::ElectricEquipment_ITE_AirCooledFields::FanEndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipmentITEAirCooled_Impl::isFanEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::ElectricEquipment_ITE_AirCooledFields::FanEndUseSubcategory);
}

bool ElectricEquipmentITEAirCooled_Impl::setFanEndUseSubcategory(const std::string& fanEndUseSubcategory) {
  const bool result = setString(openstudio::ElectricEquipment_ITE_AirCooledFields::FanEndUseSubcategory, fanEndUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ElectricEquipmentITEAirCooled_Impl::resetFanEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::ElectricEquipment_ITE_AirCooledFields::FanEndUseSubcategory, ""));
}

std::string ElectricEquipmentITEAirCooled_Impl::electricPowerSupplyEndUseSubcategory() const {
  const auto value = getString(openstudio::ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricEquipmentITEAirCooled_Impl::isElectricPowerSupplyEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEndUseSubcategory);
}

bool ElectricEquipmentITEAirCooled_Impl::setElectricPowerSupplyEndUseSubcategory(const std::string& electricPowerSupplyEndUseSubcategory) {
  const bool result = setString(openstudio::ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEndUseSubcategory,
                                electricPowerSupplyEndUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ElectricEquipmentITEAirCooled_Impl::resetElectricPowerSupplyEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::ElectricEquipment_ITE_AirCooledFields::ElectricPowerSupplyEndUseSubcategory, ""));
}

bool ElectricEquipmentITEAirCooled_Impl::setMultiplier(double multiplier) {
  // EnergyPlus ElectricEquipment:ITE:AirCooled has no dedicated multiplier field. Preserve model API by
  // scaling design-power scalar fields that correspond to the translated multiplier behavior.
  bool applied = false;
  bool result = true;

  if (auto value = getDouble(openstudio::ElectricEquipment_ITE_AirCooledFields::WattsperUnit, true)) {
    const bool fieldResult = setDouble(openstudio::ElectricEquipment_ITE_AirCooledFields::WattsperUnit, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }

  if (auto value = getDouble(openstudio::ElectricEquipment_ITE_AirCooledFields::WattsperFloorArea, true)) {
    const bool fieldResult = setDouble(openstudio::ElectricEquipment_ITE_AirCooledFields::WattsperFloorArea, (*value) * multiplier);
    OS_ASSERT(fieldResult);
    result = result && fieldResult;
    applied = true;
  }

  return applied && result;
}

void ElectricEquipmentITEAirCooled_Impl::resetMultiplier() {
  // No dedicated translated multiplier field exists on EnergyPlus ElectricEquipment:ITE:AirCooled.
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
