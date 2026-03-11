/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingWater.hpp"
#include "StraightComponent/CoilSystemCoolingWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilSystemCoolingWater::CoilSystemCoolingWater(const Model& model) : StraightComponent(CoilSystemCoolingWater::iddObjectType(), model) {
  // Keep strict scalar getters populated for model-parity behavior.
  OS_ASSERT(setDehumidificationControlType("None"));
  OS_ASSERT(setRunonSensibleLoad(true));
  OS_ASSERT(setRunonLatentLoad(false));
  OS_ASSERT(setMinimumAirToWaterTemperatureOffset(0.0));
  OS_ASSERT(setEconomizerLockout(true));
  OS_ASSERT(setMinimumWaterLoopTemperatureForHeatRecovery(0.0));
}

CoilSystemCoolingWater::CoilSystemCoolingWater(std::shared_ptr<detail::CoilSystemCoolingWater_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType CoilSystemCoolingWater::iddObjectType() {
  return IddObjectType::CoilSystem_Cooling_Water;
}

std::vector<std::string> CoilSystemCoolingWater::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::CoilSystem_Cooling_WaterFields::DehumidificationControlType);
}

std::string CoilSystemCoolingWater::dehumidificationControlType() const {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->dehumidificationControlType();
}

bool CoilSystemCoolingWater::runonSensibleLoad() const {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->runonSensibleLoad();
}

bool CoilSystemCoolingWater::runonLatentLoad() const {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->runonLatentLoad();
}

double CoilSystemCoolingWater::minimumAirToWaterTemperatureOffset() const {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->minimumAirToWaterTemperatureOffset();
}

bool CoilSystemCoolingWater::economizerLockout() const {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->economizerLockout();
}

double CoilSystemCoolingWater::minimumWaterLoopTemperatureForHeatRecovery() const {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->minimumWaterLoopTemperatureForHeatRecovery();
}

bool CoilSystemCoolingWater::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

bool CoilSystemCoolingWater::setRunonSensibleLoad(bool runonSensibleLoad) {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->setRunonSensibleLoad(runonSensibleLoad);
}

bool CoilSystemCoolingWater::setRunonLatentLoad(bool runonLatentLoad) {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->setRunonLatentLoad(runonLatentLoad);
}

bool CoilSystemCoolingWater::setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset) {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->setMinimumAirToWaterTemperatureOffset(minimumAirToWaterTemperatureOffset);
}

bool CoilSystemCoolingWater::setEconomizerLockout(bool economizerLockout) {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->setEconomizerLockout(economizerLockout);
}

bool CoilSystemCoolingWater::setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery) {
  return getImpl<detail::CoilSystemCoolingWater_Impl>()->setMinimumWaterLoopTemperatureForHeatRecovery(
    minimumWaterLoopTemperatureForHeatRecovery);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
  const auto value = impl.getString(fieldIndex, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "yes");
}

bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
  return impl.setString(fieldIndex, value ? "Yes" : "No");
}

}  // namespace

unsigned CoilSystemCoolingWater_Impl::inletPort() const {
  return openstudio::CoilSystem_Cooling_WaterFields::AirInletNodeName;
}

unsigned CoilSystemCoolingWater_Impl::outletPort() const {
  return openstudio::CoilSystem_Cooling_WaterFields::AirOutletNodeName;
}

std::string CoilSystemCoolingWater_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::CoilSystem_Cooling_WaterFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemCoolingWater_Impl::runonSensibleLoad() const {
  return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonSensibleLoad);
}

bool CoilSystemCoolingWater_Impl::runonLatentLoad() const {
  return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonLatentLoad);
}

double CoilSystemCoolingWater_Impl::minimumAirToWaterTemperatureOffset() const {
  const auto value = getDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemCoolingWater_Impl::economizerLockout() const {
  return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::EconomizerLockout);
}

double CoilSystemCoolingWater_Impl::minimumWaterLoopTemperatureForHeatRecovery() const {
  const auto value = getDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemCoolingWater_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::CoilSystem_Cooling_WaterFields::DehumidificationControlType, dehumidificationControlType);
}

bool CoilSystemCoolingWater_Impl::setRunonSensibleLoad(bool runonSensibleLoad) {
  const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonSensibleLoad, runonSensibleLoad);
  OS_ASSERT(result);
  return result;
}

bool CoilSystemCoolingWater_Impl::setRunonLatentLoad(bool runonLatentLoad) {
  const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonLatentLoad, runonLatentLoad);
  OS_ASSERT(result);
  return result;
}

bool CoilSystemCoolingWater_Impl::setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset) {
  return setDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, minimumAirToWaterTemperatureOffset);
}

bool CoilSystemCoolingWater_Impl::setEconomizerLockout(bool economizerLockout) {
  const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::EconomizerLockout, economizerLockout);
  OS_ASSERT(result);
  return result;
}

bool CoilSystemCoolingWater_Impl::setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery) {
  const bool result =
    setDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, minimumWaterLoopTemperatureForHeatRecovery);
  OS_ASSERT(result);
  return result;
}

std::vector<std::string> CoilSystemCoolingWater_Impl::dehumidificationControlTypeValues() const {
  return openstudio::epmodel::CoilSystemCoolingWater::dehumidificationControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
