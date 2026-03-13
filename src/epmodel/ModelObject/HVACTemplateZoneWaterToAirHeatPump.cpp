/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneWaterToAirHeatPump.hpp"
#include "HVACTemplateZoneWaterToAirHeatPump_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_WaterToAirHeatPump_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneWaterToAirHeatPump::HVACTemplateZoneWaterToAirHeatPump(const Model& model) : ModelObject(HVACTemplateZoneWaterToAirHeatPump::iddObjectType(), model) {}

HVACTemplateZoneWaterToAirHeatPump::HVACTemplateZoneWaterToAirHeatPump(std::shared_ptr<detail::HVACTemplateZoneWaterToAirHeatPump_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneWaterToAirHeatPump::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_WaterToAirHeatPump;
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::supplyFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanPlacement);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::coolingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilType);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::heatPumpHeatingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilType);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::supplementalHeatingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilType);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::heatPumpCoilWaterFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode);
}

std::vector<std::string> HVACTemplateZoneWaterToAirHeatPump::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingType);
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::coolingSupplyAirFlowRate() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->coolingSupplyAirFlowRate();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingSupplyAirFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingSupplyAirFlowRateDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingSupplyAirFlowRateAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
}

void HVACTemplateZoneWaterToAirHeatPump::resetCoolingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetCoolingSupplyAirFlowRate();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeCoolingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeCoolingSupplyAirFlowRate();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::heatingSupplyAirFlowRate() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->heatingSupplyAirFlowRate();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatingSupplyAirFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatingSupplyAirFlowRateDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatingSupplyAirFlowRateAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
}

void HVACTemplateZoneWaterToAirHeatPump::resetHeatingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetHeatingSupplyAirFlowRate();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeHeatingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeHeatingSupplyAirFlowRate();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::noLoadSupplyAirFlowRate() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->noLoadSupplyAirFlowRate();
}

bool HVACTemplateZoneWaterToAirHeatPump::isNoLoadSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
}

void HVACTemplateZoneWaterToAirHeatPump::resetNoLoadSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetNoLoadSupplyAirFlowRate();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeNoLoadSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeNoLoadSupplyAirFlowRate();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneHeatingSizingFactor();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneCoolingSizingFactor();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneCoolingSizingFactor();
}

std::string HVACTemplateZoneWaterToAirHeatPump::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->outdoorAirMethod();
}

bool HVACTemplateZoneWaterToAirHeatPump::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

void HVACTemplateZoneWaterToAirHeatPump::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetOutdoorAirMethod();
}

double HVACTemplateZoneWaterToAirHeatPump::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->outdoorAirFlowRateperPerson();
}

bool HVACTemplateZoneWaterToAirHeatPump::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

void HVACTemplateZoneWaterToAirHeatPump::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateperPerson();
}

double HVACTemplateZoneWaterToAirHeatPump::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

bool HVACTemplateZoneWaterToAirHeatPump::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

void HVACTemplateZoneWaterToAirHeatPump::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneWaterToAirHeatPump::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->outdoorAirFlowRateperZone();
}

bool HVACTemplateZoneWaterToAirHeatPump::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

void HVACTemplateZoneWaterToAirHeatPump::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateperZone();
}

std::string HVACTemplateZoneWaterToAirHeatPump::supplyFanPlacement() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->supplyFanPlacement();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplyFanPlacementDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplyFanPlacementDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setSupplyFanPlacement(supplyFanPlacement);
}

void HVACTemplateZoneWaterToAirHeatPump::resetSupplyFanPlacement() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetSupplyFanPlacement();
}

double HVACTemplateZoneWaterToAirHeatPump::supplyFanTotalEfficiency() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->supplyFanTotalEfficiency();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplyFanTotalEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplyFanTotalEfficiencyDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setSupplyFanTotalEfficiency(supplyFanTotalEfficiency);
}

void HVACTemplateZoneWaterToAirHeatPump::resetSupplyFanTotalEfficiency() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetSupplyFanTotalEfficiency();
}

double HVACTemplateZoneWaterToAirHeatPump::supplyFanDeltaPressure() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->supplyFanDeltaPressure();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplyFanDeltaPressureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplyFanDeltaPressureDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setSupplyFanDeltaPressure(supplyFanDeltaPressure);
}

void HVACTemplateZoneWaterToAirHeatPump::resetSupplyFanDeltaPressure() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetSupplyFanDeltaPressure();
}

double HVACTemplateZoneWaterToAirHeatPump::supplyFanMotorEfficiency() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->supplyFanMotorEfficiency();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplyFanMotorEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplyFanMotorEfficiencyDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setSupplyFanMotorEfficiency(supplyFanMotorEfficiency);
}

void HVACTemplateZoneWaterToAirHeatPump::resetSupplyFanMotorEfficiency() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetSupplyFanMotorEfficiency();
}

std::string HVACTemplateZoneWaterToAirHeatPump::coolingCoilType() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->coolingCoilType();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingCoilTypeDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setCoolingCoilType(const std::string& coolingCoilType) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setCoolingCoilType(coolingCoilType);
}

void HVACTemplateZoneWaterToAirHeatPump::resetCoolingCoilType() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetCoolingCoilType();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::coolingCoilGrossRatedTotalCapacity() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->coolingCoilGrossRatedTotalCapacity();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingCoilGrossRatedTotalCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingCoilGrossRatedTotalCapacityDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingCoilGrossRatedTotalCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingCoilGrossRatedTotalCapacityAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setCoolingCoilGrossRatedTotalCapacity(coolingCoilGrossRatedTotalCapacity);
}

void HVACTemplateZoneWaterToAirHeatPump::resetCoolingCoilGrossRatedTotalCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetCoolingCoilGrossRatedTotalCapacity();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeCoolingCoilGrossRatedTotalCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeCoolingCoilGrossRatedTotalCapacity();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::coolingCoilGrossRatedSensibleHeatRatio() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->coolingCoilGrossRatedSensibleHeatRatio();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingCoilGrossRatedSensibleHeatRatioDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingCoilGrossRatedSensibleHeatRatioAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setCoolingCoilGrossRatedSensibleHeatRatio(coolingCoilGrossRatedSensibleHeatRatio);
}

void HVACTemplateZoneWaterToAirHeatPump::resetCoolingCoilGrossRatedSensibleHeatRatio() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetCoolingCoilGrossRatedSensibleHeatRatio();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeCoolingCoilGrossRatedSensibleHeatRatio() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeCoolingCoilGrossRatedSensibleHeatRatio();
}

double HVACTemplateZoneWaterToAirHeatPump::coolingCoilGrossRatedCOP() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->coolingCoilGrossRatedCOP();
}

bool HVACTemplateZoneWaterToAirHeatPump::isCoolingCoilGrossRatedCOPDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isCoolingCoilGrossRatedCOPDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setCoolingCoilGrossRatedCOP(coolingCoilGrossRatedCOP);
}

void HVACTemplateZoneWaterToAirHeatPump::resetCoolingCoilGrossRatedCOP() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetCoolingCoilGrossRatedCOP();
}

std::string HVACTemplateZoneWaterToAirHeatPump::heatPumpHeatingCoilType() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->heatPumpHeatingCoilType();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatPumpHeatingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatPumpHeatingCoilTypeDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setHeatPumpHeatingCoilType(heatPumpHeatingCoilType);
}

void HVACTemplateZoneWaterToAirHeatPump::resetHeatPumpHeatingCoilType() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetHeatPumpHeatingCoilType();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::heatPumpHeatingCoilGrossRatedCapacity() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->heatPumpHeatingCoilGrossRatedCapacity();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatPumpHeatingCoilGrossRatedCapacityDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatPumpHeatingCoilGrossRatedCapacityAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setHeatPumpHeatingCoilGrossRatedCapacity(heatPumpHeatingCoilGrossRatedCapacity);
}

void HVACTemplateZoneWaterToAirHeatPump::resetHeatPumpHeatingCoilGrossRatedCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetHeatPumpHeatingCoilGrossRatedCapacity();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeHeatPumpHeatingCoilGrossRatedCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeHeatPumpHeatingCoilGrossRatedCapacity();
}

double HVACTemplateZoneWaterToAirHeatPump::heatPumpHeatingCoilGrossRatedCOP() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->heatPumpHeatingCoilGrossRatedCOP();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatPumpHeatingCoilGrossRatedCOPDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setHeatPumpHeatingCoilGrossRatedCOP(heatPumpHeatingCoilGrossRatedCOP);
}

void HVACTemplateZoneWaterToAirHeatPump::resetHeatPumpHeatingCoilGrossRatedCOP() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetHeatPumpHeatingCoilGrossRatedCOP();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::supplementalHeatingCoilCapacity() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->supplementalHeatingCoilCapacity();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplementalHeatingCoilCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplementalHeatingCoilCapacityDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplementalHeatingCoilCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplementalHeatingCoilCapacityAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setSupplementalHeatingCoilCapacity(supplementalHeatingCoilCapacity);
}

void HVACTemplateZoneWaterToAirHeatPump::resetSupplementalHeatingCoilCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetSupplementalHeatingCoilCapacity();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeSupplementalHeatingCoilCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeSupplementalHeatingCoilCapacity();
}

double HVACTemplateZoneWaterToAirHeatPump::maximumCyclingRate() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->maximumCyclingRate();
}

bool HVACTemplateZoneWaterToAirHeatPump::isMaximumCyclingRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isMaximumCyclingRateDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setMaximumCyclingRate(double maximumCyclingRate) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
}

void HVACTemplateZoneWaterToAirHeatPump::resetMaximumCyclingRate() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetMaximumCyclingRate();
}

double HVACTemplateZoneWaterToAirHeatPump::latentCapacityTimeConstant() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->latentCapacityTimeConstant();
}

bool HVACTemplateZoneWaterToAirHeatPump::isLatentCapacityTimeConstantDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isLatentCapacityTimeConstantDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
}

void HVACTemplateZoneWaterToAirHeatPump::resetLatentCapacityTimeConstant() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetLatentCapacityTimeConstant();
}

double HVACTemplateZoneWaterToAirHeatPump::heatPumpFanDelayTime() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->heatPumpFanDelayTime();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatPumpFanDelayTimeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatPumpFanDelayTimeDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setHeatPumpFanDelayTime(double heatPumpFanDelayTime) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setHeatPumpFanDelayTime(heatPumpFanDelayTime);
}

void HVACTemplateZoneWaterToAirHeatPump::resetHeatPumpFanDelayTime() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetHeatPumpFanDelayTime();
}

std::string HVACTemplateZoneWaterToAirHeatPump::supplementalHeatingCoilType() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->supplementalHeatingCoilType();
}

bool HVACTemplateZoneWaterToAirHeatPump::isSupplementalHeatingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isSupplementalHeatingCoilTypeDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setSupplementalHeatingCoilType(supplementalHeatingCoilType);
}

void HVACTemplateZoneWaterToAirHeatPump::resetSupplementalHeatingCoilType() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetSupplementalHeatingCoilType();
}

std::string HVACTemplateZoneWaterToAirHeatPump::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

bool HVACTemplateZoneWaterToAirHeatPump::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneWaterToAirHeatPump::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

bool HVACTemplateZoneWaterToAirHeatPump::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZoneWaterToAirHeatPump::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneWaterToAirHeatPump::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(zoneCoolingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneWaterToAirHeatPump::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

bool HVACTemplateZoneWaterToAirHeatPump::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneWaterToAirHeatPump::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

bool HVACTemplateZoneWaterToAirHeatPump::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZoneWaterToAirHeatPump::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneWaterToAirHeatPump::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneWaterToAirHeatPump::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneWaterToAirHeatPump::heatPumpCoilWaterFlowMode() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->heatPumpCoilWaterFlowMode();
}

bool HVACTemplateZoneWaterToAirHeatPump::isHeatPumpCoilWaterFlowModeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isHeatPumpCoilWaterFlowModeDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setHeatPumpCoilWaterFlowMode(heatPumpCoilWaterFlowMode);
}

void HVACTemplateZoneWaterToAirHeatPump::resetHeatPumpCoilWaterFlowMode() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetHeatPumpCoilWaterFlowMode();
}

std::string HVACTemplateZoneWaterToAirHeatPump::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->baseboardHeatingType();
}

bool HVACTemplateZoneWaterToAirHeatPump::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

void HVACTemplateZoneWaterToAirHeatPump::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetBaseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->baseboardHeatingCapacity();
}

bool HVACTemplateZoneWaterToAirHeatPump::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneWaterToAirHeatPump::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneWaterToAirHeatPump::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

void HVACTemplateZoneWaterToAirHeatPump::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneWaterToAirHeatPump::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneWaterToAirHeatPump_Impl>()->autosizeBaseboardHeatingCapacity();
}


}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::coolingSupplyAirFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingSupplyAirFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::heatingSupplyAirFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatingSupplyAirFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::noLoadSupplyAirFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "autosize"));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingSizingFactor, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingSizingFactor, ""));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingSizingFactor, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingSizingFactor, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirMethod);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirMethod, outdoorAirMethod);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirMethod, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperPerson, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZone, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::supplyFanPlacement() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplyFanPlacementDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanPlacement);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanPlacement, supplyFanPlacement);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetSupplyFanPlacement() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanPlacement, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::supplyFanTotalEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplyFanTotalEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanTotalEfficiency);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanTotalEfficiency, supplyFanTotalEfficiency);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetSupplyFanTotalEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanTotalEfficiency, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::supplyFanDeltaPressure() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanDeltaPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplyFanDeltaPressureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanDeltaPressure);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanDeltaPressure, supplyFanDeltaPressure);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetSupplyFanDeltaPressure() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanDeltaPressure, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::supplyFanMotorEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanMotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplyFanMotorEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanMotorEfficiency);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanMotorEfficiency, supplyFanMotorEfficiency);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetSupplyFanMotorEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanMotorEfficiency, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::coolingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilType);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setCoolingCoilType(const std::string& coolingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilType, coolingCoilType);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetCoolingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilType, ""));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::coolingCoilGrossRatedTotalCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingCoilGrossRatedTotalCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingCoilGrossRatedTotalCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity, coolingCoilGrossRatedTotalCapacity);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetCoolingCoilGrossRatedTotalCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeCoolingCoilGrossRatedTotalCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity, "autosize"));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::coolingCoilGrossRatedSensibleHeatRatio() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio, coolingCoilGrossRatedSensibleHeatRatio);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetCoolingCoilGrossRatedSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeCoolingCoilGrossRatedSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio, "autosize"));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::coolingCoilGrossRatedCOP() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isCoolingCoilGrossRatedCOPDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedCOP);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedCOP, coolingCoilGrossRatedCOP);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetCoolingCoilGrossRatedCOP() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedCOP, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::heatPumpHeatingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatPumpHeatingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilType);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilType, heatPumpHeatingCoilType);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetHeatPumpHeatingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilType, ""));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::heatPumpHeatingCoilGrossRatedCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity, heatPumpHeatingCoilGrossRatedCapacity);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetHeatPumpHeatingCoilGrossRatedCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeHeatPumpHeatingCoilGrossRatedCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity, "autosize"));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::heatPumpHeatingCoilGrossRatedCOP() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCOP);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCOP, heatPumpHeatingCoilGrossRatedCOP);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetHeatPumpHeatingCoilGrossRatedCOP() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCOP, ""));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::supplementalHeatingCoilCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplementalHeatingCoilCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplementalHeatingCoilCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity, supplementalHeatingCoilCapacity);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetSupplementalHeatingCoilCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeSupplementalHeatingCoilCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity, "autosize"));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::maximumCyclingRate() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isMaximumCyclingRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::MaximumCyclingRate);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::MaximumCyclingRate, maximumCyclingRate);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetMaximumCyclingRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::MaximumCyclingRate, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::latentCapacityTimeConstant() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isLatentCapacityTimeConstantDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::LatentCapacityTimeConstant);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetLatentCapacityTimeConstant() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::LatentCapacityTimeConstant, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::heatPumpFanDelayTime() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpFanDelayTime, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatPumpFanDelayTimeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpFanDelayTime);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setHeatPumpFanDelayTime(double heatPumpFanDelayTime) {
  return setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpFanDelayTime, heatPumpFanDelayTime);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetHeatPumpFanDelayTime() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpFanDelayTime, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::supplementalHeatingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isSupplementalHeatingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilType);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilType, supplementalHeatingCoilType);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetSupplementalHeatingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilType, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureDifference, zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

double HVACTemplateZoneWaterToAirHeatPump_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureDifference, zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::heatPumpCoilWaterFlowMode() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isHeatPumpCoilWaterFlowModeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, heatPumpCoilWaterFlowMode);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetHeatPumpCoilWaterFlowMode() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, ""));
}

std::string HVACTemplateZoneWaterToAirHeatPump_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingType);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingType, baseboardHeatingType);
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingType, ""));
}

boost::optional<double> HVACTemplateZoneWaterToAirHeatPump_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity, true);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneWaterToAirHeatPump_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneWaterToAirHeatPump_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity, "autosize"));
}


}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
