/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneFanCoil.hpp"
#include "HVACTemplateZoneFanCoil_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_FanCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneFanCoil::HVACTemplateZoneFanCoil(const Model& model) : ModelObject(HVACTemplateZoneFanCoil::iddObjectType(), model) {}

HVACTemplateZoneFanCoil::HVACTemplateZoneFanCoil(std::shared_ptr<detail::HVACTemplateZoneFanCoil_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneFanCoil::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_FanCoil;
}

std::vector<std::string> HVACTemplateZoneFanCoil::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneFanCoil::coolingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilType);
}

std::vector<std::string> HVACTemplateZoneFanCoil::heatingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilType);
}

std::vector<std::string> HVACTemplateZoneFanCoil::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneFanCoil::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneFanCoil::capacityControlMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_FanCoilFields::CapacityControlMethod);
}

std::vector<std::string> HVACTemplateZoneFanCoil::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingType);
}

boost::optional<double> HVACTemplateZoneFanCoil::supplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->supplyAirMaximumFlowRate();
}

boost::optional<double> HVACTemplateZoneFanCoil::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->zoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneFanCoil::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->zoneCoolingSizingFactor();
}

std::string HVACTemplateZoneFanCoil::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->outdoorAirMethod();
}

double HVACTemplateZoneFanCoil::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->outdoorAirFlowRateperPerson();
}

double HVACTemplateZoneFanCoil::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneFanCoil::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->outdoorAirFlowRateperZone();
}

double HVACTemplateZoneFanCoil::supplyFanTotalEfficiency() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->supplyFanTotalEfficiency();
}

double HVACTemplateZoneFanCoil::supplyFanDeltaPressure() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->supplyFanDeltaPressure();
}

double HVACTemplateZoneFanCoil::supplyFanMotorEfficiency() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->supplyFanMotorEfficiency();
}

double HVACTemplateZoneFanCoil::supplyFanMotorinAirStreamFraction() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->supplyFanMotorinAirStreamFraction();
}

std::string HVACTemplateZoneFanCoil::coolingCoilType() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->coolingCoilType();
}

double HVACTemplateZoneFanCoil::coolingCoilDesignSetpoint() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->coolingCoilDesignSetpoint();
}

std::string HVACTemplateZoneFanCoil::heatingCoilType() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->heatingCoilType();
}

double HVACTemplateZoneFanCoil::heatingCoilDesignSetpoint() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->heatingCoilDesignSetpoint();
}

std::string HVACTemplateZoneFanCoil::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneFanCoil::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneFanCoil::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneFanCoil::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

boost::optional<std::string> HVACTemplateZoneFanCoil::capacityControlMethod() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->capacityControlMethod();
}

double HVACTemplateZoneFanCoil::lowSpeedSupplyAirFlowRatio() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->lowSpeedSupplyAirFlowRatio();
}

double HVACTemplateZoneFanCoil::mediumSpeedSupplyAirFlowRatio() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->mediumSpeedSupplyAirFlowRatio();
}

std::string HVACTemplateZoneFanCoil::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->baseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneFanCoil::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->baseboardHeatingCapacity();
}

bool HVACTemplateZoneFanCoil::isSupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneFanCoil::isSupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isSupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneFanCoil::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneFanCoil::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneFanCoil::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneFanCoil::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneFanCoil::isSupplyFanTotalEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isSupplyFanTotalEfficiencyDefaulted();
}

bool HVACTemplateZoneFanCoil::isSupplyFanDeltaPressureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isSupplyFanDeltaPressureDefaulted();
}

bool HVACTemplateZoneFanCoil::isSupplyFanMotorEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isSupplyFanMotorEfficiencyDefaulted();
}

bool HVACTemplateZoneFanCoil::isSupplyFanMotorinAirStreamFractionDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isSupplyFanMotorinAirStreamFractionDefaulted();
}

bool HVACTemplateZoneFanCoil::isCoolingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isCoolingCoilTypeDefaulted();
}

bool HVACTemplateZoneFanCoil::isCoolingCoilDesignSetpointDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isCoolingCoilDesignSetpointDefaulted();
}

bool HVACTemplateZoneFanCoil::isHeatingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isHeatingCoilTypeDefaulted();
}

bool HVACTemplateZoneFanCoil::isHeatingCoilDesignSetpointDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isHeatingCoilDesignSetpointDefaulted();
}

bool HVACTemplateZoneFanCoil::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneFanCoil::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneFanCoil::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneFanCoil::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneFanCoil::isLowSpeedSupplyAirFlowRatioDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isLowSpeedSupplyAirFlowRatioDefaulted();
}

bool HVACTemplateZoneFanCoil::isMediumSpeedSupplyAirFlowRatioDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isMediumSpeedSupplyAirFlowRatioDefaulted();
}

bool HVACTemplateZoneFanCoil::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneFanCoil::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneFanCoil::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneFanCoil::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
}

bool HVACTemplateZoneFanCoil::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

bool HVACTemplateZoneFanCoil::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

bool HVACTemplateZoneFanCoil::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

bool HVACTemplateZoneFanCoil::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneFanCoil::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneFanCoil::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

bool HVACTemplateZoneFanCoil::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setSupplyFanTotalEfficiency(supplyFanTotalEfficiency);
}

bool HVACTemplateZoneFanCoil::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setSupplyFanDeltaPressure(supplyFanDeltaPressure);
}

bool HVACTemplateZoneFanCoil::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setSupplyFanMotorEfficiency(supplyFanMotorEfficiency);
}

bool HVACTemplateZoneFanCoil::setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setSupplyFanMotorinAirStreamFraction(supplyFanMotorinAirStreamFraction);
}

bool HVACTemplateZoneFanCoil::setCoolingCoilType(const std::string& coolingCoilType) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setCoolingCoilType(coolingCoilType);
}

bool HVACTemplateZoneFanCoil::setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setCoolingCoilDesignSetpoint(coolingCoilDesignSetpoint);
}

bool HVACTemplateZoneFanCoil::setHeatingCoilType(const std::string& heatingCoilType) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setHeatingCoilType(heatingCoilType);
}

bool HVACTemplateZoneFanCoil::setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setHeatingCoilDesignSetpoint(heatingCoilDesignSetpoint);
}

bool HVACTemplateZoneFanCoil::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneFanCoil::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneFanCoil::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneFanCoil::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneFanCoil::setCapacityControlMethod(const std::string& capacityControlMethod) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setCapacityControlMethod(capacityControlMethod);
}

bool HVACTemplateZoneFanCoil::setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setLowSpeedSupplyAirFlowRatio(lowSpeedSupplyAirFlowRatio);
}

bool HVACTemplateZoneFanCoil::setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setMediumSpeedSupplyAirFlowRatio(mediumSpeedSupplyAirFlowRatio);
}

bool HVACTemplateZoneFanCoil::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

bool HVACTemplateZoneFanCoil::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

void HVACTemplateZoneFanCoil::resetSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneFanCoil::autosizeSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->autosizeSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneFanCoil::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetZoneHeatingSizingFactor();
}

void HVACTemplateZoneFanCoil::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetZoneCoolingSizingFactor();
}

void HVACTemplateZoneFanCoil::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetOutdoorAirMethod();
}

void HVACTemplateZoneFanCoil::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetOutdoorAirFlowRateperPerson();
}

void HVACTemplateZoneFanCoil::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

void HVACTemplateZoneFanCoil::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetOutdoorAirFlowRateperZone();
}

void HVACTemplateZoneFanCoil::resetSupplyFanTotalEfficiency() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetSupplyFanTotalEfficiency();
}

void HVACTemplateZoneFanCoil::resetSupplyFanDeltaPressure() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetSupplyFanDeltaPressure();
}

void HVACTemplateZoneFanCoil::resetSupplyFanMotorEfficiency() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetSupplyFanMotorEfficiency();
}

void HVACTemplateZoneFanCoil::resetSupplyFanMotorinAirStreamFraction() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetSupplyFanMotorinAirStreamFraction();
}

void HVACTemplateZoneFanCoil::resetCoolingCoilType() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetCoolingCoilType();
}

void HVACTemplateZoneFanCoil::resetCoolingCoilDesignSetpoint() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetCoolingCoilDesignSetpoint();
}

void HVACTemplateZoneFanCoil::resetHeatingCoilType() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetHeatingCoilType();
}

void HVACTemplateZoneFanCoil::resetHeatingCoilDesignSetpoint() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetHeatingCoilDesignSetpoint();
}

void HVACTemplateZoneFanCoil::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneFanCoil::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

void HVACTemplateZoneFanCoil::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneFanCoil::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

void HVACTemplateZoneFanCoil::resetCapacityControlMethod() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetCapacityControlMethod();
}

void HVACTemplateZoneFanCoil::resetLowSpeedSupplyAirFlowRatio() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetLowSpeedSupplyAirFlowRatio();
}

void HVACTemplateZoneFanCoil::resetMediumSpeedSupplyAirFlowRatio() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetMediumSpeedSupplyAirFlowRatio();
}

void HVACTemplateZoneFanCoil::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetBaseboardHeatingType();
}

void HVACTemplateZoneFanCoil::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneFanCoil::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneFanCoil_Impl>()->autosizeBaseboardHeatingCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneFanCoil_Impl::supplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate, true);
}

boost::optional<double> HVACTemplateZoneFanCoil_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneFanCoil_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingSizingFactor, true);
}

std::string HVACTemplateZoneFanCoil_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::supplyFanTotalEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::supplyFanDeltaPressure() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanDeltaPressure, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::supplyFanMotorEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::supplyFanMotorinAirStreamFraction() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorinAirStreamFraction, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneFanCoil_Impl::coolingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::coolingCoilDesignSetpoint() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilDesignSetpoint, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneFanCoil_Impl::heatingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::heatingCoilDesignSetpoint() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilDesignSetpoint, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneFanCoil_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneFanCoil_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<std::string> HVACTemplateZoneFanCoil_Impl::capacityControlMethod() const {
  return getString(openstudio::HVACTemplate_Zone_FanCoilFields::CapacityControlMethod, true);
}

double HVACTemplateZoneFanCoil_Impl::lowSpeedSupplyAirFlowRatio() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::LowSpeedSupplyAirFlowRatio, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneFanCoil_Impl::mediumSpeedSupplyAirFlowRatio() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::MediumSpeedSupplyAirFlowRatio, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneFanCoil_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneFanCoil_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity, true);
}

bool HVACTemplateZoneFanCoil_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneFanCoil_Impl::isSupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneFanCoil_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirMethod);
}

bool HVACTemplateZoneFanCoil_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneFanCoil_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneFanCoil_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneFanCoil_Impl::isSupplyFanTotalEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanTotalEfficiency);
}

bool HVACTemplateZoneFanCoil_Impl::isSupplyFanDeltaPressureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanDeltaPressure);
}

bool HVACTemplateZoneFanCoil_Impl::isSupplyFanMotorEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorEfficiency);
}

bool HVACTemplateZoneFanCoil_Impl::isSupplyFanMotorinAirStreamFractionDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorinAirStreamFraction);
}

bool HVACTemplateZoneFanCoil_Impl::isCoolingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilType);
}

bool HVACTemplateZoneFanCoil_Impl::isCoolingCoilDesignSetpointDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilDesignSetpoint);
}

bool HVACTemplateZoneFanCoil_Impl::isHeatingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilType);
}

bool HVACTemplateZoneFanCoil_Impl::isHeatingCoilDesignSetpointDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilDesignSetpoint);
}

bool HVACTemplateZoneFanCoil_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneFanCoil_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneFanCoil_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneFanCoil_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneFanCoil_Impl::isLowSpeedSupplyAirFlowRatioDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::LowSpeedSupplyAirFlowRatio);
}

bool HVACTemplateZoneFanCoil_Impl::isMediumSpeedSupplyAirFlowRatioDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::MediumSpeedSupplyAirFlowRatio);
}

bool HVACTemplateZoneFanCoil_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingType);
}

bool HVACTemplateZoneFanCoil_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneFanCoil_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneFanCoil_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZoneFanCoil_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZoneFanCoil_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZoneFanCoil_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanTotalEfficiency, supplyFanTotalEfficiency);
}

bool HVACTemplateZoneFanCoil_Impl::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanDeltaPressure, supplyFanDeltaPressure);
}

bool HVACTemplateZoneFanCoil_Impl::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorEfficiency, supplyFanMotorEfficiency);
}

bool HVACTemplateZoneFanCoil_Impl::setSupplyFanMotorinAirStreamFraction(double supplyFanMotorinAirStreamFraction) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorinAirStreamFraction, supplyFanMotorinAirStreamFraction);
}

bool HVACTemplateZoneFanCoil_Impl::setCoolingCoilType(const std::string& coolingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilType, coolingCoilType);
}

bool HVACTemplateZoneFanCoil_Impl::setCoolingCoilDesignSetpoint(double coolingCoilDesignSetpoint) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilDesignSetpoint, coolingCoilDesignSetpoint);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setHeatingCoilType(const std::string& heatingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilType, heatingCoilType);
}

bool HVACTemplateZoneFanCoil_Impl::setHeatingCoilDesignSetpoint(double heatingCoilDesignSetpoint) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilDesignSetpoint, heatingCoilDesignSetpoint);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneFanCoil_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneFanCoil_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneFanCoil_Impl::setCapacityControlMethod(const std::string& capacityControlMethod) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::CapacityControlMethod, capacityControlMethod);
}

bool HVACTemplateZoneFanCoil_Impl::setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::LowSpeedSupplyAirFlowRatio, lowSpeedSupplyAirFlowRatio);
}

bool HVACTemplateZoneFanCoil_Impl::setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio) {
  return setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::MediumSpeedSupplyAirFlowRatio, mediumSpeedSupplyAirFlowRatio);
}

bool HVACTemplateZoneFanCoil_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZoneFanCoil_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneFanCoil_Impl::resetSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneFanCoil_Impl::autosizeSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneFanCoil_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirMethod, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetSupplyFanTotalEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanTotalEfficiency, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetSupplyFanDeltaPressure() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanDeltaPressure, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetSupplyFanMotorEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorEfficiency, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetSupplyFanMotorinAirStreamFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::SupplyFanMotorinAirStreamFraction, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetCoolingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilType, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetCoolingCoilDesignSetpoint() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::CoolingCoilDesignSetpoint, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetHeatingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilType, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetHeatingCoilDesignSetpoint() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::HeatingCoilDesignSetpoint, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetCapacityControlMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::CapacityControlMethod, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetLowSpeedSupplyAirFlowRatio() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::LowSpeedSupplyAirFlowRatio, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetMediumSpeedSupplyAirFlowRatio() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::MediumSpeedSupplyAirFlowRatio, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingType, ""));
}

void HVACTemplateZoneFanCoil_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneFanCoil_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity, "autosize"));
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::coolingCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::coolingCoilTypeValues();
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::heatingCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::heatingCoilTypeValues();
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::capacityControlMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::capacityControlMethodValues();
}

std::vector<std::string> HVACTemplateZoneFanCoil_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneFanCoil::baseboardHeatingTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
