/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemIntegratedHeatPumpAirSource.hpp"
#include "StraightComponent/CoilSystemIntegratedHeatPumpAirSource_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_IntegratedHeatPump_AirSource_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilSystemIntegratedHeatPumpAirSource::CoilSystemIntegratedHeatPumpAirSource(const Model& model)
  : StraightComponent(CoilSystemIntegratedHeatPumpAirSource::iddObjectType(), model) {
  OS_ASSERT(setIndoorTemperatureLimitForSCWHMode(20.0));
  OS_ASSERT(setAmbientTemperatureLimitForSCWHMode(27.0));
  OS_ASSERT(setIndoorTemperatureAboveWhichWHHasHigherPriority(20.0));
  OS_ASSERT(setAmbientTemperatureAboveWhichWHHasHigherPriority(20.0));
  OS_ASSERT(setFlagtoIndicateLoadControlInSCWHMode(0));
  OS_ASSERT(setMinimumSpeedLevelForSCWHMode(1));
  OS_ASSERT(setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(0.0));
  OS_ASSERT(setMinimumSpeedLevelForSCDWHMode(1));
  OS_ASSERT(setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(360.0));
  OS_ASSERT(setMinimumSpeedLevelForSHDWHMode(1));
}

CoilSystemIntegratedHeatPumpAirSource::CoilSystemIntegratedHeatPumpAirSource(
  std::shared_ptr<detail::CoilSystemIntegratedHeatPumpAirSource_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilSystemIntegratedHeatPumpAirSource::iddObjectType() {
  return IddObjectType::CoilSystem_IntegratedHeatPump_AirSource;
}

double CoilSystemIntegratedHeatPumpAirSource::indoorTemperatureLimitForSCWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->indoorTemperatureLimitForSCWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setIndoorTemperatureLimitForSCWHMode(double indoorTemperatureLimitForSCWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setIndoorTemperatureLimitForSCWHMode(indoorTemperatureLimitForSCWHMode);
}

double CoilSystemIntegratedHeatPumpAirSource::ambientTemperatureLimitForSCWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->ambientTemperatureLimitForSCWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setAmbientTemperatureLimitForSCWHMode(double ambientTemperatureLimitForSCWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setAmbientTemperatureLimitForSCWHMode(ambientTemperatureLimitForSCWHMode);
}

double CoilSystemIntegratedHeatPumpAirSource::indoorTemperatureAboveWhichWHHasHigherPriority() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->indoorTemperatureAboveWhichWHHasHigherPriority();
}

bool CoilSystemIntegratedHeatPumpAirSource::setIndoorTemperatureAboveWhichWHHasHigherPriority(
  double indoorTemperatureAboveWhichWHHasHigherPriority) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setIndoorTemperatureAboveWhichWHHasHigherPriority(
    indoorTemperatureAboveWhichWHHasHigherPriority);
}

double CoilSystemIntegratedHeatPumpAirSource::ambientTemperatureAboveWhichWHHasHigherPriority() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->ambientTemperatureAboveWhichWHHasHigherPriority();
}

bool CoilSystemIntegratedHeatPumpAirSource::setAmbientTemperatureAboveWhichWHHasHigherPriority(
  double ambientTemperatureAboveWhichWHHasHigherPriority) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setAmbientTemperatureAboveWhichWHHasHigherPriority(
    ambientTemperatureAboveWhichWHHasHigherPriority);
}

int CoilSystemIntegratedHeatPumpAirSource::flagtoIndicateLoadControlInSCWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->flagtoIndicateLoadControlInSCWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setFlagtoIndicateLoadControlInSCWHMode(int flagtoIndicateLoadControlInSCWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setFlagtoIndicateLoadControlInSCWHMode(
    flagtoIndicateLoadControlInSCWHMode);
}

int CoilSystemIntegratedHeatPumpAirSource::minimumSpeedLevelForSCWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->minimumSpeedLevelForSCWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setMinimumSpeedLevelForSCWHMode(int minimumSpeedLevelForSCWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setMinimumSpeedLevelForSCWHMode(minimumSpeedLevelForSCWHMode);
}

double CoilSystemIntegratedHeatPumpAirSource::maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(
  double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(
    maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode);
}

int CoilSystemIntegratedHeatPumpAirSource::minimumSpeedLevelForSCDWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->minimumSpeedLevelForSCDWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setMinimumSpeedLevelForSCDWHMode(int minimumSpeedLevelForSCDWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setMinimumSpeedLevelForSCDWHMode(minimumSpeedLevelForSCDWHMode);
}

double CoilSystemIntegratedHeatPumpAirSource::maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(
  double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(
    maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode);
}

int CoilSystemIntegratedHeatPumpAirSource::minimumSpeedLevelForSHDWHMode() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->minimumSpeedLevelForSHDWHMode();
}

bool CoilSystemIntegratedHeatPumpAirSource::setMinimumSpeedLevelForSHDWHMode(int minimumSpeedLevelForSHDWHMode) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setMinimumSpeedLevelForSHDWHMode(minimumSpeedLevelForSHDWHMode);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilSystemIntegratedHeatPumpAirSource_Impl::inletPort() const {
  // EnergyPlus CoilSystem:IntegratedHeatPump:AirSource has no direct inlet/outlet node fields.
  return 0;
}

unsigned CoilSystemIntegratedHeatPumpAirSource_Impl::outletPort() const {
  // Node connectivity is delegated to referenced component coils.
  return 0;
}

double CoilSystemIntegratedHeatPumpAirSource_Impl::indoorTemperatureLimitForSCWHMode() const {
  const auto value = getDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureLimitforSCWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setIndoorTemperatureLimitForSCWHMode(double indoorTemperatureLimitForSCWHMode) {
  const bool result = setDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureLimitforSCWHMode,
                                indoorTemperatureLimitForSCWHMode);
  OS_ASSERT(result);
  return result;
}

double CoilSystemIntegratedHeatPumpAirSource_Impl::ambientTemperatureLimitForSCWHMode() const {
  const auto value = getDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureLimitforSCWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setAmbientTemperatureLimitForSCWHMode(double ambientTemperatureLimitForSCWHMode) {
  const bool result =
    setDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureLimitforSCWHMode, ambientTemperatureLimitForSCWHMode);
  OS_ASSERT(result);
  return result;
}

double CoilSystemIntegratedHeatPumpAirSource_Impl::indoorTemperatureAboveWhichWHHasHigherPriority() const {
  const auto value =
    getDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureaboveWhichWHhasHigherPriority, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setIndoorTemperatureAboveWhichWHHasHigherPriority(
  double indoorTemperatureAboveWhichWHHasHigherPriority) {
  const bool result =
    setDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureaboveWhichWHhasHigherPriority,
              indoorTemperatureAboveWhichWHHasHigherPriority);
  OS_ASSERT(result);
  return result;
}

double CoilSystemIntegratedHeatPumpAirSource_Impl::ambientTemperatureAboveWhichWHHasHigherPriority() const {
  const auto value =
    getDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureaboveWhichWHhasHigherPriority, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setAmbientTemperatureAboveWhichWHHasHigherPriority(
  double ambientTemperatureAboveWhichWHHasHigherPriority) {
  const bool result =
    setDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureaboveWhichWHhasHigherPriority,
              ambientTemperatureAboveWhichWHHasHigherPriority);
  OS_ASSERT(result);
  return result;
}

int CoilSystemIntegratedHeatPumpAirSource_Impl::flagtoIndicateLoadControlInSCWHMode() const {
  const auto value = getInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::FlagtoIndicateLoadControlinSCWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setFlagtoIndicateLoadControlInSCWHMode(int flagtoIndicateLoadControlInSCWHMode) {
  const bool result =
    setInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::FlagtoIndicateLoadControlinSCWHMode, flagtoIndicateLoadControlInSCWHMode);
  OS_ASSERT(result);
  return result;
}

int CoilSystemIntegratedHeatPumpAirSource_Impl::minimumSpeedLevelForSCWHMode() const {
  const auto value = getInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setMinimumSpeedLevelForSCWHMode(int minimumSpeedLevelForSCWHMode) {
  const bool result =
    setInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCWHMode, minimumSpeedLevelForSCWHMode);
  OS_ASSERT(result);
  return result;
}

double CoilSystemIntegratedHeatPumpAirSource_Impl::maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode() const {
  const auto value =
    getDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(
  double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode) {
  const bool result =
    setDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode,
              maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode);
  OS_ASSERT(result);
  return result;
}

int CoilSystemIntegratedHeatPumpAirSource_Impl::minimumSpeedLevelForSCDWHMode() const {
  const auto value = getInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCDWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setMinimumSpeedLevelForSCDWHMode(int minimumSpeedLevelForSCDWHMode) {
  const bool result =
    setInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCDWHMode, minimumSpeedLevelForSCDWHMode);
  OS_ASSERT(result);
  return result;
}

double CoilSystemIntegratedHeatPumpAirSource_Impl::maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode() const {
  const auto value = getDouble(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(
  double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode) {
  const bool result = setDouble(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode,
    maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode);
  OS_ASSERT(result);
  return result;
}

int CoilSystemIntegratedHeatPumpAirSource_Impl::minimumSpeedLevelForSHDWHMode() const {
  const auto value = getInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSHDWHMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setMinimumSpeedLevelForSHDWHMode(int minimumSpeedLevelForSHDWHMode) {
  const bool result =
    setInt(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSHDWHMode, minimumSpeedLevelForSHDWHMode);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
