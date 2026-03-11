/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeatPumpAirToWater.hpp"
#include "StraightComponent/HeatPumpAirToWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatPump_AirToWater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HeatPumpAirToWater::HeatPumpAirToWater(const Model& model) : StraightComponent(HeatPumpAirToWater::iddObjectType(), model) {
  // Mirror model constructor defaults for preserved scalar API behavior.
  bool ok = true;
  ok &= setOperatingModeControlMethod("Load");
  ok &= setOperatingModeControlOptionforMultipleUnit("SingleMode");
  ok &= setMinimumPartLoadRatio(0.0);
  ok &= setMaximumOutdoorDryBulbTemperatureForDefrostOperation(10.0);
  ok &= setHeatPumpDefrostControl("None");
  ok &= setHeatPumpDefrostTimePeriodFraction(0.058333);
  ok &= setResistiveDefrostHeaterCapacity(0.0);
  ok &= setHeatPumpMultiplier(1);
  ok &= setControlType("VariableSpeed");
  ok &= setCrankcaseHeaterCapacity(0.0);
  ok &= setMaximumAmbientTemperatureforCrankcaseHeaterOperation(10.0);
  OS_ASSERT(ok);
}

HeatPumpAirToWater::HeatPumpAirToWater(std::shared_ptr<detail::HeatPumpAirToWater_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType HeatPumpAirToWater::iddObjectType() {
  return IddObjectType::HeatPump_AirToWater;
}

std::vector<std::string> HeatPumpAirToWater::operatingModeControlMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWaterFields::OperatingModeControlMethod);
}

std::vector<std::string> HeatPumpAirToWater::operatingModeControlOptionforMultipleUnitValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit);
}

std::vector<std::string> HeatPumpAirToWater::heatPumpDefrostControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostControl);
}

std::vector<std::string> HeatPumpAirToWater::controlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_AirToWaterFields::ControlType);
}

std::string HeatPumpAirToWater::operatingModeControlMethod() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->operatingModeControlMethod();
}

bool HeatPumpAirToWater::isOperatingModeControlMethodDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isOperatingModeControlMethodDefaulted();
}

bool HeatPumpAirToWater::setOperatingModeControlMethod(const std::string& operatingModeControlMethod) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setOperatingModeControlMethod(operatingModeControlMethod);
}

void HeatPumpAirToWater::resetOperatingModeControlMethod() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetOperatingModeControlMethod();
}

std::string HeatPumpAirToWater::operatingModeControlOptionforMultipleUnit() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->operatingModeControlOptionforMultipleUnit();
}

bool HeatPumpAirToWater::isOperatingModeControlOptionforMultipleUnitDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isOperatingModeControlOptionforMultipleUnitDefaulted();
}

bool HeatPumpAirToWater::setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setOperatingModeControlOptionforMultipleUnit(operatingModeControlOptionforMultipleUnit);
}

void HeatPumpAirToWater::resetOperatingModeControlOptionforMultipleUnit() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetOperatingModeControlOptionforMultipleUnit();
}

double HeatPumpAirToWater::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->minimumPartLoadRatio();
}

bool HeatPumpAirToWater::isMinimumPartLoadRatioDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isMinimumPartLoadRatioDefaulted();
}

bool HeatPumpAirToWater::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

void HeatPumpAirToWater::resetMinimumPartLoadRatio() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetMinimumPartLoadRatio();
}

double HeatPumpAirToWater::maximumOutdoorDryBulbTemperatureForDefrostOperation() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->maximumOutdoorDryBulbTemperatureForDefrostOperation();
}

bool HeatPumpAirToWater::isMaximumOutdoorDryBulbTemperatureForDefrostOperationDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isMaximumOutdoorDryBulbTemperatureForDefrostOperationDefaulted();
}

bool HeatPumpAirToWater::setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setMaximumOutdoorDryBulbTemperatureForDefrostOperation(
    maximumOutdoorDryBulbTemperatureForDefrostOperation);
}

void HeatPumpAirToWater::resetMaximumOutdoorDryBulbTemperatureForDefrostOperation() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetMaximumOutdoorDryBulbTemperatureForDefrostOperation();
}

std::string HeatPumpAirToWater::heatPumpDefrostControl() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->heatPumpDefrostControl();
}

bool HeatPumpAirToWater::isHeatPumpDefrostControlDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isHeatPumpDefrostControlDefaulted();
}

bool HeatPumpAirToWater::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setHeatPumpDefrostControl(heatPumpDefrostControl);
}

void HeatPumpAirToWater::resetHeatPumpDefrostControl() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetHeatPumpDefrostControl();
}

double HeatPumpAirToWater::heatPumpDefrostTimePeriodFraction() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->heatPumpDefrostTimePeriodFraction();
}

bool HeatPumpAirToWater::isHeatPumpDefrostTimePeriodFractionDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isHeatPumpDefrostTimePeriodFractionDefaulted();
}

bool HeatPumpAirToWater::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setHeatPumpDefrostTimePeriodFraction(heatPumpDefrostTimePeriodFraction);
}

void HeatPumpAirToWater::resetHeatPumpDefrostTimePeriodFraction() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetHeatPumpDefrostTimePeriodFraction();
}

double HeatPumpAirToWater::resistiveDefrostHeaterCapacity() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->resistiveDefrostHeaterCapacity();
}

bool HeatPumpAirToWater::isResistiveDefrostHeaterCapacityDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isResistiveDefrostHeaterCapacityDefaulted();
}

bool HeatPumpAirToWater::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity);
}

void HeatPumpAirToWater::resetResistiveDefrostHeaterCapacity() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetResistiveDefrostHeaterCapacity();
}

int HeatPumpAirToWater::heatPumpMultiplier() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->heatPumpMultiplier();
}

bool HeatPumpAirToWater::isHeatPumpMultiplierDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isHeatPumpMultiplierDefaulted();
}

bool HeatPumpAirToWater::setHeatPumpMultiplier(int heatPumpMultiplier) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setHeatPumpMultiplier(heatPumpMultiplier);
}

void HeatPumpAirToWater::resetHeatPumpMultiplier() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetHeatPumpMultiplier();
}

std::string HeatPumpAirToWater::controlType() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->controlType();
}

bool HeatPumpAirToWater::isControlTypeDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isControlTypeDefaulted();
}

bool HeatPumpAirToWater::setControlType(const std::string& controlType) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setControlType(controlType);
}

void HeatPumpAirToWater::resetControlType() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetControlType();
}

double HeatPumpAirToWater::crankcaseHeaterCapacity() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->crankcaseHeaterCapacity();
}

bool HeatPumpAirToWater::isCrankcaseHeaterCapacityDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isCrankcaseHeaterCapacityDefaulted();
}

bool HeatPumpAirToWater::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

void HeatPumpAirToWater::resetCrankcaseHeaterCapacity() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetCrankcaseHeaterCapacity();
}

double HeatPumpAirToWater::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->maximumAmbientTemperatureforCrankcaseHeaterOperation();
}

bool HeatPumpAirToWater::isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted();
}

bool HeatPumpAirToWater::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::HeatPumpAirToWater_Impl>()->setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
    maximumAmbientTemperatureforCrankcaseHeaterOperation);
}

void HeatPumpAirToWater::resetMaximumAmbientTemperatureforCrankcaseHeaterOperation() {
  getImpl<detail::HeatPumpAirToWater_Impl>()->resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned HeatPumpAirToWater_Impl::inletPort() const {
  return openstudio::HeatPump_AirToWaterFields::AirInletNodeName;
}

unsigned HeatPumpAirToWater_Impl::outletPort() const {
  return openstudio::HeatPump_AirToWaterFields::AirOutletNodeName;
}

std::string HeatPumpAirToWater_Impl::operatingModeControlMethod() const {
  const auto value = getString(openstudio::HeatPump_AirToWaterFields::OperatingModeControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isOperatingModeControlMethodDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::OperatingModeControlMethod);
}

bool HeatPumpAirToWater_Impl::setOperatingModeControlMethod(const std::string& operatingModeControlMethod) {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::OperatingModeControlMethod, operatingModeControlMethod);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetOperatingModeControlMethod() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::OperatingModeControlMethod, "");
  OS_ASSERT(result);
}

std::string HeatPumpAirToWater_Impl::operatingModeControlOptionforMultipleUnit() const {
  const auto value = getString(openstudio::HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isOperatingModeControlOptionforMultipleUnitDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit);
}

bool HeatPumpAirToWater_Impl::setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit) {
  const bool result =
    setString(openstudio::HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit, operatingModeControlOptionforMultipleUnit);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetOperatingModeControlOptionforMultipleUnit() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::OperatingModeControlOptionforMultipleUnit, "");
  OS_ASSERT(result);
}

double HeatPumpAirToWater_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWaterFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isMinimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::MinimumPartLoadRatio);
}

bool HeatPumpAirToWater_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  const bool result = setDouble(openstudio::HeatPump_AirToWaterFields::MinimumPartLoadRatio, minimumPartLoadRatio);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetMinimumPartLoadRatio() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::MinimumPartLoadRatio, "");
  OS_ASSERT(result);
}

double HeatPumpAirToWater_Impl::maximumOutdoorDryBulbTemperatureForDefrostOperation() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isMaximumOutdoorDryBulbTemperatureForDefrostOperationDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation);
}

bool HeatPumpAirToWater_Impl::setMaximumOutdoorDryBulbTemperatureForDefrostOperation(
  double maximumOutdoorDryBulbTemperatureForDefrostOperation) {
  const bool result = setDouble(openstudio::HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation,
                                maximumOutdoorDryBulbTemperatureForDefrostOperation);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetMaximumOutdoorDryBulbTemperatureForDefrostOperation() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation, "");
  OS_ASSERT(result);
}

std::string HeatPumpAirToWater_Impl::heatPumpDefrostControl() const {
  const auto value = getString(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostControl, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isHeatPumpDefrostControlDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostControl);
}

bool HeatPumpAirToWater_Impl::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostControl, heatPumpDefrostControl);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetHeatPumpDefrostControl() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostControl, "");
  OS_ASSERT(result);
}

double HeatPumpAirToWater_Impl::heatPumpDefrostTimePeriodFraction() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isHeatPumpDefrostTimePeriodFractionDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction);
}

bool HeatPumpAirToWater_Impl::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
  const bool result = setDouble(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction, heatPumpDefrostTimePeriodFraction);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetHeatPumpDefrostTimePeriodFraction() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::HeatPumpDefrostTimePeriodFraction, "");
  OS_ASSERT(result);
}

double HeatPumpAirToWater_Impl::resistiveDefrostHeaterCapacity() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isResistiveDefrostHeaterCapacityDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity);
}

bool HeatPumpAirToWater_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
  const bool result = setDouble(openstudio::HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetResistiveDefrostHeaterCapacity() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::ResistiveDefrostHeaterCapacity, "");
  OS_ASSERT(result);
}

int HeatPumpAirToWater_Impl::heatPumpMultiplier() const {
  const auto value = getInt(openstudio::HeatPump_AirToWaterFields::HeatPumpMultiplier, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isHeatPumpMultiplierDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::HeatPumpMultiplier);
}

bool HeatPumpAirToWater_Impl::setHeatPumpMultiplier(int heatPumpMultiplier) {
  const bool result = setInt(openstudio::HeatPump_AirToWaterFields::HeatPumpMultiplier, heatPumpMultiplier);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetHeatPumpMultiplier() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::HeatPumpMultiplier, "");
  OS_ASSERT(result);
}

std::string HeatPumpAirToWater_Impl::controlType() const {
  const auto value = getString(openstudio::HeatPump_AirToWaterFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isControlTypeDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::ControlType);
}

bool HeatPumpAirToWater_Impl::setControlType(const std::string& controlType) {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::ControlType, controlType);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetControlType() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::ControlType, "");
  OS_ASSERT(result);
}

double HeatPumpAirToWater_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWaterFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isCrankcaseHeaterCapacityDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::CrankcaseHeaterCapacity);
}

bool HeatPumpAirToWater_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  const bool result = setDouble(openstudio::HeatPump_AirToWaterFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetCrankcaseHeaterCapacity() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::CrankcaseHeaterCapacity, "");
  OS_ASSERT(result);
}

double HeatPumpAirToWater_Impl::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWater_Impl::isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation);
}

bool HeatPumpAirToWater_Impl::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
  double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
  const bool result = setDouble(openstudio::HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation,
                                maximumAmbientTemperatureforCrankcaseHeaterOperation);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWater_Impl::resetMaximumAmbientTemperatureforCrankcaseHeaterOperation() {
  const bool result = setString(openstudio::HeatPump_AirToWaterFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, "");
  OS_ASSERT(result);
}

std::vector<std::string> HeatPumpAirToWater_Impl::operatingModeControlMethodValues() const {
  return openstudio::epmodel::HeatPumpAirToWater::operatingModeControlMethodValues();
}

std::vector<std::string> HeatPumpAirToWater_Impl::operatingModeControlOptionforMultipleUnitValues() const {
  return openstudio::epmodel::HeatPumpAirToWater::operatingModeControlOptionforMultipleUnitValues();
}

std::vector<std::string> HeatPumpAirToWater_Impl::heatPumpDefrostControlValues() const {
  return openstudio::epmodel::HeatPumpAirToWater::heatPumpDefrostControlValues();
}

std::vector<std::string> HeatPumpAirToWater_Impl::controlTypeValues() const {
  return openstudio::epmodel::HeatPumpAirToWater::controlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
