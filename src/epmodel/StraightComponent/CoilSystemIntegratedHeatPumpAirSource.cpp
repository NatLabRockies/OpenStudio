/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemIntegratedHeatPumpAirSource.hpp"
#include "StraightComponent/CoilSystemIntegratedHeatPumpAirSource_Impl.hpp"

#include "StraightComponent/CoilCoolingDXVariableSpeed.hpp"
#include "StraightComponent/CoilHeatingDXVariableSpeed.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/OS_CoilSystem_IntegratedHeatPump_AirSource_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_IntegratedHeatPump_AirSource_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilSystemIntegratedHeatPumpAirSource::CoilSystemIntegratedHeatPumpAirSource(const Model& model)
  : StraightComponent(CoilSystemIntegratedHeatPumpAirSource::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>());

  CoilCoolingDXVariableSpeed spaceCoolingCoil(model);
  OS_ASSERT(spaceCoolingCoil.setName("CoilSystemIntegratedHeatPumpAirSource Space Cooling Coil"));
  CoilHeatingDXVariableSpeed spaceHeatingCoil(model);
  OS_ASSERT(spaceHeatingCoil.setName("CoilSystemIntegratedHeatPumpAirSource Space Heating Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed dedicatedWaterHeatingCoil(model);
  OS_ASSERT(dedicatedWaterHeatingCoil.setName("CoilSystemIntegratedHeatPumpAirSource Dedicated Water Heating Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed scwhCoil(model);
  OS_ASSERT(scwhCoil.setName("CoilSystemIntegratedHeatPumpAirSource SCWH Coil"));
  CoilCoolingDXVariableSpeed scdwhCoolingCoil(model);
  OS_ASSERT(scdwhCoolingCoil.setName("CoilSystemIntegratedHeatPumpAirSource SCDWH Cooling Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed scdwhWaterHeatingCoil(model);
  OS_ASSERT(scdwhWaterHeatingCoil.setName("CoilSystemIntegratedHeatPumpAirSource SCDWH Water Heating Coil"));
  CoilHeatingDXVariableSpeed shdwhHeatingCoil(model);
  OS_ASSERT(shdwhHeatingCoil.setName("CoilSystemIntegratedHeatPumpAirSource SHDWH Heating Coil"));
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed shdwhWaterHeatingCoil(model);
  OS_ASSERT(shdwhWaterHeatingCoil.setName("CoilSystemIntegratedHeatPumpAirSource SHDWH Water Heating Coil"));

  OS_ASSERT(setSpaceCoolingCoil(spaceCoolingCoil));
  OS_ASSERT(setSpaceHeatingCoil(spaceHeatingCoil));
  OS_ASSERT(setDedicatedWaterHeatingCoil(dedicatedWaterHeatingCoil));
  OS_ASSERT(setSCWHCoil(scwhCoil));
  OS_ASSERT(setSCDWHCoolingCoil(scdwhCoolingCoil));
  OS_ASSERT(setSCDWHWaterHeatingCoil(scdwhWaterHeatingCoil));
  OS_ASSERT(setSHDWHHeatingCoil(shdwhHeatingCoil));
  OS_ASSERT(setSHDWHWaterHeatingCoil(shdwhWaterHeatingCoil));
  OS_ASSERT(setIndoorTemperatureLimitForSCWHMode(20.0));
  OS_ASSERT(setAmbientTemperatureLimitForSCWHMode(27.0));
  OS_ASSERT(setAmbientTemperatureAboveWhichWHHasHigherPriority(20.0));
  OS_ASSERT(setMinimumSpeedLevelForSCWHMode(1));
  OS_ASSERT(setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(0.0));
  OS_ASSERT(setMinimumSpeedLevelForSCDWHMode(1));
  OS_ASSERT(setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(360.0));
  OS_ASSERT(setMinimumSpeedLevelForSHDWHMode(1));
}

CoilSystemIntegratedHeatPumpAirSource::CoilSystemIntegratedHeatPumpAirSource(
  const Model& model, const StraightComponent& spaceCoolingCoil, const StraightComponent& spaceHeatingCoil,
  const HVACComponent& dedicatedWaterHeatingCoil, const HVACComponent& scwhCoil, const StraightComponent& scdwhCoolingCoil,
  const HVACComponent& scdwhWaterHeatingCoil, const StraightComponent& shdwhHeatingCoil, const HVACComponent& shdwhWaterHeatingCoil)
  : StraightComponent(CoilSystemIntegratedHeatPumpAirSource::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>());

  OS_ASSERT(setSpaceCoolingCoil(spaceCoolingCoil));
  OS_ASSERT(setSpaceHeatingCoil(spaceHeatingCoil));
  OS_ASSERT(setDedicatedWaterHeatingCoil(dedicatedWaterHeatingCoil));
  OS_ASSERT(setSCWHCoil(scwhCoil));
  OS_ASSERT(setSCDWHCoolingCoil(scdwhCoolingCoil));
  OS_ASSERT(setSCDWHWaterHeatingCoil(scdwhWaterHeatingCoil));
  OS_ASSERT(setSHDWHHeatingCoil(shdwhHeatingCoil));
  OS_ASSERT(setSHDWHWaterHeatingCoil(shdwhWaterHeatingCoil));
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

StraightComponent CoilSystemIntegratedHeatPumpAirSource::spaceCoolingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->spaceCoolingCoil();
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource::spaceHeatingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->spaceHeatingCoil();
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource::dedicatedWaterHeatingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->dedicatedWaterHeatingCoil();
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource::scwhCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->scwhCoil();
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource::scdwhCoolingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->scdwhCoolingCoil();
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource::scdwhWaterHeatingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->scdwhWaterHeatingCoil();
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource::shdwhHeatingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->shdwhHeatingCoil();
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource::shdwhWaterHeatingCoil() const {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->shdwhWaterHeatingCoil();
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

bool CoilSystemIntegratedHeatPumpAirSource::setSpaceCoolingCoil(const StraightComponent& spaceCoolingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSpaceCoolingCoil(spaceCoolingCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setSpaceHeatingCoil(const StraightComponent& spaceHeatingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSpaceHeatingCoil(spaceHeatingCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setDedicatedWaterHeatingCoil(const HVACComponent& dedicatedWaterHeatingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setDedicatedWaterHeatingCoil(dedicatedWaterHeatingCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setSCWHCoil(const HVACComponent& scwhCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSCWHCoil(scwhCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setSCDWHCoolingCoil(const StraightComponent& scdwhCoolingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSCDWHCoolingCoil(scdwhCoolingCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setSCDWHWaterHeatingCoil(const HVACComponent& scdwhWaterHeatingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSCDWHWaterHeatingCoil(scdwhWaterHeatingCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setSHDWHHeatingCoil(const StraightComponent& shdwhHeatingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSHDWHHeatingCoil(shdwhHeatingCoil);
}

bool CoilSystemIntegratedHeatPumpAirSource::setSHDWHWaterHeatingCoil(const HVACComponent& shdwhWaterHeatingCoil) {
  return getImpl<detail::CoilSystemIntegratedHeatPumpAirSource_Impl>()->setSHDWHWaterHeatingCoil(shdwhWaterHeatingCoil);
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

bool CoilSystemIntegratedHeatPumpAirSource_Impl::addToNode(Node& /*node*/) {
  return false;
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
  const bool result = setDouble(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureaboveWhichWHhasHigherPriority,
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

std::vector<ModelObject> CoilSystemIntegratedHeatPumpAirSource_Impl::children() const {
  std::vector<ModelObject> result;

  boost::optional<StraightComponent> straightComponent;
  boost::optional<HVACComponent> hvacComponent;

  straightComponent = optionalSpaceCoolingCoil();
  if (straightComponent) {
    result.push_back(straightComponent.get());
  }

  straightComponent = optionalSpaceHeatingCoil();
  if (straightComponent) {
    result.push_back(straightComponent.get());
  }

  hvacComponent = optionalDedicatedWaterHeatingCoil();
  if (hvacComponent) {
    result.push_back(hvacComponent.get());
  }

  hvacComponent = optionalScwhCoil();
  if (hvacComponent) {
    result.push_back(hvacComponent.get());
  }

  straightComponent = optionalScdwhCoolingCoil();
  if (straightComponent) {
    result.push_back(straightComponent.get());
  }

  hvacComponent = optionalScdwhWaterHeatingCoil();
  if (hvacComponent) {
    result.push_back(hvacComponent.get());
  }

  straightComponent = optionalShdwhHeatingCoil();
  if (straightComponent) {
    result.push_back(straightComponent.get());
  }

  hvacComponent = optionalShdwhWaterHeatingCoil();
  if (hvacComponent) {
    result.push_back(hvacComponent.get());
  }

  return result;
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource_Impl::spaceCoolingCoil() const {
  boost::optional<StraightComponent> value = optionalSpaceCoolingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<StraightComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalSpaceCoolingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<StraightComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceCoolingCoilName);
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource_Impl::spaceHeatingCoil() const {
  boost::optional<StraightComponent> value = optionalSpaceHeatingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<StraightComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalSpaceHeatingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<StraightComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceHeatingCoilName);
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource_Impl::dedicatedWaterHeatingCoil() const {
  auto value = optionalDedicatedWaterHeatingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<HVACComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalDedicatedWaterHeatingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::DedicatedWaterHeatingCoilName);
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource_Impl::scwhCoil() const {
  auto value = optionalScwhCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<HVACComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalScwhCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SCWHCoilName);
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource_Impl::scdwhCoolingCoil() const {
  auto value = optionalScdwhCoolingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<StraightComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalScdwhCoolingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<StraightComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHCoolingCoilName);
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource_Impl::scdwhWaterHeatingCoil() const {
  auto value = optionalScdwhWaterHeatingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<HVACComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalScdwhWaterHeatingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHWaterHeatingCoilName);
}

StraightComponent CoilSystemIntegratedHeatPumpAirSource_Impl::shdwhHeatingCoil() const {
  auto value = optionalShdwhHeatingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<StraightComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalShdwhHeatingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<StraightComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHHeatingCoilName);
}

HVACComponent CoilSystemIntegratedHeatPumpAirSource_Impl::shdwhWaterHeatingCoil() const {
  auto value = optionalShdwhWaterHeatingCoil();
  OS_ASSERT(value);
  return *value;
}

boost::optional<HVACComponent> CoilSystemIntegratedHeatPumpAirSource_Impl::optionalShdwhWaterHeatingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHWaterHeatingCoilName);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSpaceCoolingCoil(const StraightComponent& spaceCoolingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceCoolingCoilName, spaceCoolingCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSpaceHeatingCoil(const StraightComponent& spaceHeatingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceHeatingCoilName, spaceHeatingCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setDedicatedWaterHeatingCoil(const HVACComponent& dedicatedWaterHeatingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::DedicatedWaterHeatingCoilName,
                    dedicatedWaterHeatingCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSCWHCoil(const HVACComponent& scwhCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SCWHCoilName, scwhCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSCDWHCoolingCoil(const StraightComponent& scdwhCoolingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHCoolingCoilName, scdwhCoolingCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSCDWHWaterHeatingCoil(const HVACComponent& scdwhWaterHeatingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHWaterHeatingCoilName, scdwhWaterHeatingCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSHDWHHeatingCoil(const StraightComponent& shdwhHeatingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHHeatingCoilName, shdwhHeatingCoil.handle(), false);
}

bool CoilSystemIntegratedHeatPumpAirSource_Impl::setSHDWHWaterHeatingCoil(const HVACComponent& shdwhWaterHeatingCoil) {
  return setPointer(openstudio::CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHWaterHeatingCoilName, shdwhWaterHeatingCoil.handle(), false);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
