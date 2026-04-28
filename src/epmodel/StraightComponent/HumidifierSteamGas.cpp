/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HumidifierSteamGas.hpp"
#include "StraightComponent/HumidifierSteamGas_Impl.hpp"

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Humidifier_Steam_Gas_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

HumidifierSteamGas::HumidifierSteamGas(const Model& model) : StraightComponent(HumidifierSteamGas::iddObjectType(), model) {
  autosizeRatedCapacity();
  setRatedGasUseRate(104000.0);
  setString(openstudio::Humidifier_Steam_GasFields::WaterStorageTankName, "");
}

HumidifierSteamGas::HumidifierSteamGas(std::shared_ptr<detail::HumidifierSteamGas_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType HumidifierSteamGas::iddObjectType() {
  return IddObjectType::Humidifier_Steam_Gas;
}

bool HumidifierSteamGas::addToNode(Node& node) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->addToNode(node);
}

boost::optional<Schedule> HumidifierSteamGas::availabilitySchedule() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->availabilitySchedule();
}

bool HumidifierSteamGas::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setAvailabilitySchedule(schedule);
}

void HumidifierSteamGas::resetAvailabilitySchedule() {
  getImpl<detail::HumidifierSteamGas_Impl>()->resetAvailabilitySchedule();
}

std::vector<std::string> HumidifierSteamGas::inletWaterTemperatureOptionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Humidifier_Steam_GasFields::InletWaterTemperatureOption);
}

boost::optional<double> HumidifierSteamGas::ratedCapacity() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->ratedCapacity();
}

bool HumidifierSteamGas::isRatedCapacityAutosized() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->isRatedCapacityAutosized();
}

bool HumidifierSteamGas::setRatedCapacity(double ratedCapacity) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setRatedCapacity(ratedCapacity);
}

void HumidifierSteamGas::autosizeRatedCapacity() {
  getImpl<detail::HumidifierSteamGas_Impl>()->autosizeRatedCapacity();
}

boost::optional<double> HumidifierSteamGas::autosizedRatedCapacity() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->autosizedRatedCapacity();
}

boost::optional<double> HumidifierSteamGas::ratedGasUseRate() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->ratedGasUseRate();
}

bool HumidifierSteamGas::isRatedGasUseRateAutosized() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->isRatedGasUseRateAutosized();
}

bool HumidifierSteamGas::setRatedGasUseRate(double ratedGasUseRate) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setRatedGasUseRate(ratedGasUseRate);
}

void HumidifierSteamGas::resetRatedGasUseRate() {
  getImpl<detail::HumidifierSteamGas_Impl>()->resetRatedGasUseRate();
}

void HumidifierSteamGas::autosizeRatedGasUseRate() {
  getImpl<detail::HumidifierSteamGas_Impl>()->autosizeRatedGasUseRate();
}

boost::optional<double> HumidifierSteamGas::autosizedRatedGasUseRate() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->autosizedRatedGasUseRate();
}

double HumidifierSteamGas::thermalEfficiency() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->thermalEfficiency();
}

bool HumidifierSteamGas::isThermalEfficiencyDefaulted() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->isThermalEfficiencyDefaulted();
}

bool HumidifierSteamGas::setThermalEfficiency(double thermalEfficiency) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setThermalEfficiency(thermalEfficiency);
}

void HumidifierSteamGas::resetThermalEfficiency() {
  getImpl<detail::HumidifierSteamGas_Impl>()->resetThermalEfficiency();
}

boost::optional<double> HumidifierSteamGas::ratedFanPower() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->ratedFanPower();
}

bool HumidifierSteamGas::setRatedFanPower(double ratedFanPower) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setRatedFanPower(ratedFanPower);
}

void HumidifierSteamGas::resetRatedFanPower() {
  getImpl<detail::HumidifierSteamGas_Impl>()->resetRatedFanPower();
}

double HumidifierSteamGas::auxiliaryElectricPower() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->auxiliaryElectricPower();
}

bool HumidifierSteamGas::isAuxiliaryElectricPowerDefaulted() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->isAuxiliaryElectricPowerDefaulted();
}

bool HumidifierSteamGas::setAuxiliaryElectricPower(double auxiliaryElectricPower) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setAuxiliaryElectricPower(auxiliaryElectricPower);
}

void HumidifierSteamGas::resetAuxiliaryElectricPower() {
  getImpl<detail::HumidifierSteamGas_Impl>()->resetAuxiliaryElectricPower();
}

std::string HumidifierSteamGas::inletWaterTemperatureOption() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->inletWaterTemperatureOption();
}

bool HumidifierSteamGas::isInletWaterTemperatureOptionDefaulted() const {
  return getImpl<detail::HumidifierSteamGas_Impl>()->isInletWaterTemperatureOptionDefaulted();
}

bool HumidifierSteamGas::setInletWaterTemperatureOption(const std::string& inletWaterTemperatureOption) {
  return getImpl<detail::HumidifierSteamGas_Impl>()->setInletWaterTemperatureOption(inletWaterTemperatureOption);
}

void HumidifierSteamGas::resetInletWaterTemperatureOption() {
  getImpl<detail::HumidifierSteamGas_Impl>()->resetInletWaterTemperatureOption();
}
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned HumidifierSteamGas_Impl::inletPort() const {
  return openstudio::Humidifier_Steam_GasFields::AirInletNodeName;
}

unsigned HumidifierSteamGas_Impl::outletPort() const {
  return openstudio::Humidifier_Steam_GasFields::AirOutletNodeName;
}

bool HumidifierSteamGas_Impl::addToNode(Node& node) {
  if (node.airLoopHVACOutdoorAirSystem()) {
    return StraightComponent_Impl::addToNode(node);
  }

  auto airLoop = node.airLoopHVAC();

  // This family is intentionally limited to air-loop supply placement unless it is being
  // inserted onto an OA-system outboard stream node through the shared straight-component path.
  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

boost::optional<Schedule> HumidifierSteamGas_Impl::availabilitySchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Humidifier_Steam_GasFields::AvailabilityScheduleName);
}

bool HumidifierSteamGas_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::Humidifier_Steam_GasFields::AvailabilityScheduleName, "HumidifierSteamGas", "Availability", schedule);
}

void HumidifierSteamGas_Impl::resetAvailabilitySchedule() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::AvailabilityScheduleName, ""));
}

boost::optional<double> HumidifierSteamGas_Impl::ratedCapacity() const {
  return getDouble(openstudio::Humidifier_Steam_GasFields::RatedCapacity, true);
}

bool HumidifierSteamGas_Impl::isRatedCapacityAutosized() const {
  if (const auto value = getString(openstudio::Humidifier_Steam_GasFields::RatedCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HumidifierSteamGas_Impl::setRatedCapacity(double ratedCapacity) {
  return setDouble(openstudio::Humidifier_Steam_GasFields::RatedCapacity, ratedCapacity);
}

void HumidifierSteamGas_Impl::autosizeRatedCapacity() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::RatedCapacity, "Autosize"));
}

boost::optional<double> HumidifierSteamGas_Impl::autosizedRatedCapacity() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HumidifierSteamGas_Impl::ratedGasUseRate() const {
  return getDouble(openstudio::Humidifier_Steam_GasFields::RatedGasUseRate, true);
}

bool HumidifierSteamGas_Impl::isRatedGasUseRateAutosized() const {
  if (const auto value = getString(openstudio::Humidifier_Steam_GasFields::RatedGasUseRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HumidifierSteamGas_Impl::setRatedGasUseRate(double ratedGasUseRate) {
  return setDouble(openstudio::Humidifier_Steam_GasFields::RatedGasUseRate, ratedGasUseRate);
}

void HumidifierSteamGas_Impl::resetRatedGasUseRate() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::RatedGasUseRate, ""));
}

void HumidifierSteamGas_Impl::autosizeRatedGasUseRate() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::RatedGasUseRate, "Autosize"));
}

boost::optional<double> HumidifierSteamGas_Impl::autosizedRatedGasUseRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

double HumidifierSteamGas_Impl::thermalEfficiency() const {
  const auto value = getDouble(openstudio::Humidifier_Steam_GasFields::ThermalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool HumidifierSteamGas_Impl::isThermalEfficiencyDefaulted() const {
  return isEmpty(openstudio::Humidifier_Steam_GasFields::ThermalEfficiency);
}

bool HumidifierSteamGas_Impl::setThermalEfficiency(double thermalEfficiency) {
  return setDouble(openstudio::Humidifier_Steam_GasFields::ThermalEfficiency, thermalEfficiency);
}

void HumidifierSteamGas_Impl::resetThermalEfficiency() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::ThermalEfficiency, ""));
}

boost::optional<double> HumidifierSteamGas_Impl::ratedFanPower() const {
  return getDouble(openstudio::Humidifier_Steam_GasFields::RatedFanPower, true);
}

bool HumidifierSteamGas_Impl::setRatedFanPower(double ratedFanPower) {
  return setDouble(openstudio::Humidifier_Steam_GasFields::RatedFanPower, ratedFanPower);
}

void HumidifierSteamGas_Impl::resetRatedFanPower() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::RatedFanPower, ""));
}

double HumidifierSteamGas_Impl::auxiliaryElectricPower() const {
  const auto value = getDouble(openstudio::Humidifier_Steam_GasFields::AuxiliaryElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool HumidifierSteamGas_Impl::isAuxiliaryElectricPowerDefaulted() const {
  return isEmpty(openstudio::Humidifier_Steam_GasFields::AuxiliaryElectricPower);
}

bool HumidifierSteamGas_Impl::setAuxiliaryElectricPower(double auxiliaryElectricPower) {
  return setDouble(openstudio::Humidifier_Steam_GasFields::AuxiliaryElectricPower, auxiliaryElectricPower);
}

void HumidifierSteamGas_Impl::resetAuxiliaryElectricPower() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::AuxiliaryElectricPower, ""));
}

std::string HumidifierSteamGas_Impl::inletWaterTemperatureOption() const {
  const auto value = getString(openstudio::Humidifier_Steam_GasFields::InletWaterTemperatureOption, true);
  OS_ASSERT(value);
  return *value;
}

bool HumidifierSteamGas_Impl::isInletWaterTemperatureOptionDefaulted() const {
  return isEmpty(openstudio::Humidifier_Steam_GasFields::InletWaterTemperatureOption);
}

bool HumidifierSteamGas_Impl::setInletWaterTemperatureOption(const std::string& inletWaterTemperatureOption) {
  return setString(openstudio::Humidifier_Steam_GasFields::InletWaterTemperatureOption, inletWaterTemperatureOption);
}

void HumidifierSteamGas_Impl::resetInletWaterTemperatureOption() {
  OS_ASSERT(setString(openstudio::Humidifier_Steam_GasFields::InletWaterTemperatureOption, ""));
}

std::vector<std::string> HumidifierSteamGas_Impl::inletWaterTemperatureOptionValues() const {
  return HumidifierSteamGas::inletWaterTemperatureOptionValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
