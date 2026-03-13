/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingSystem.hpp"
#include "SizingSystem_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Sizing_System_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SizingSystem::SizingSystem(const Model& model, const AirLoopHVAC& airLoopHVAC) : ModelObject(SizingSystem::iddObjectType(), model) {
  auto impl = getImpl<detail::SizingSystem_Impl>();
  OS_ASSERT(impl);

  OS_ASSERT(impl->setAirLoopHVAC(airLoopHVAC));

  OS_ASSERT(setCentralHeatingMaximumSystemAirFlowRatio(0.3));
  OS_ASSERT(setPreheatDesignTemperature(7.0));
  OS_ASSERT(setPreheatDesignHumidityRatio(0.008));
  OS_ASSERT(setPrecoolDesignTemperature(12.8));
  OS_ASSERT(setPrecoolDesignHumidityRatio(0.008));
  OS_ASSERT(setCentralCoolingDesignSupplyAirTemperature(12.8));
  OS_ASSERT(setCentralHeatingDesignSupplyAirTemperature(16.7));
  OS_ASSERT(setAllOutdoorAirinCooling(true));
  OS_ASSERT(setAllOutdoorAirinHeating(true));
  OS_ASSERT(setCentralCoolingDesignSupplyAirHumidityRatio(0.0085));
  OS_ASSERT(setZoneMaximumOutdoorAirFraction(1.0));
  OS_ASSERT(setCoolingSupplyAirFlowRatePerFloorArea(9.9676501E-3));
  OS_ASSERT(setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(1.0));
  OS_ASSERT(setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(3.9475456E-5));
  OS_ASSERT(setHeatingSupplyAirFlowRatePerFloorArea(9.9676501E-3));
  OS_ASSERT(setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(1.0));
  OS_ASSERT(setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(1.0));
  OS_ASSERT(setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(3.1588213E-5));
  OS_ASSERT(setCoolingDesignCapacityMethod("CoolingDesignCapacity"));
  autosizeCoolingDesignCapacity();
  OS_ASSERT(setCoolingDesignCapacityPerFloorArea(234.7));
  OS_ASSERT(setFractionofAutosizedCoolingDesignCapacity(1.0));
  OS_ASSERT(setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
  autosizeHeatingDesignCapacity();
  OS_ASSERT(setHeatingDesignCapacityPerFloorArea(157.0));
  OS_ASSERT(setFractionofAutosizedHeatingDesignCapacity(1.0));
  OS_ASSERT(setCentralCoolingCapacityControlMethod("OnOff"));
  autosizeOccupantDiversity();
  OS_ASSERT(setHeatingCoilSizingMethod("None"));
  OS_ASSERT(setMaximumHeatingCapacityToCoolingCapacitySizingRatio(1.0));
}

SizingSystem::SizingSystem(std::shared_ptr<detail::SizingSystem_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType SizingSystem::iddObjectType() {
  return IddObjectType::Sizing_System;
}

std::vector<std::string> SizingSystem::validTypeofLoadtoSizeOnValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_SystemFields::TypeofLoadtoSizeOn);
}

std::vector<std::string> SizingSystem::validSizingOptionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_SystemFields::TypeofZoneSumtoUse);
}

std::vector<std::string> SizingSystem::validCoolingDesignAirFlowMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRateMethod);
}

std::vector<std::string> SizingSystem::validHeatingDesignAirFlowMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRateMethod);
}

std::vector<std::string> SizingSystem::validSystemOutdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_SystemFields::SystemOutdoorAirMethod);
}

std::vector<std::string> SizingSystem::heatingCoilSizingMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Sizing_SystemFields::HeatingCoilSizingMethod);
}

std::string SizingSystem::typeofLoadtoSizeOn() const {
  return getImpl<detail::SizingSystem_Impl>()->typeofLoadtoSizeOn();
}

bool SizingSystem::isTypeofLoadtoSizeOnDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isTypeofLoadtoSizeOnDefaulted();
}

boost::optional<double> SizingSystem::designOutdoorAirFlowRate() const {
  return getImpl<detail::SizingSystem_Impl>()->designOutdoorAirFlowRate();
}

bool SizingSystem::isDesignOutdoorAirFlowRateDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isDesignOutdoorAirFlowRateDefaulted();
}

bool SizingSystem::isDesignOutdoorAirFlowRateAutosized() const {
  return getImpl<detail::SizingSystem_Impl>()->isDesignOutdoorAirFlowRateAutosized();
}

boost::optional<double> SizingSystem::centralHeatingMaximumSystemAirFlowRatio() const {
  return getImpl<detail::SizingSystem_Impl>()->centralHeatingMaximumSystemAirFlowRatio();
}

bool SizingSystem::isCentralHeatingMaximumSystemAirFlowRatioDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isCentralHeatingMaximumSystemAirFlowRatioDefaulted();
}

bool SizingSystem::isCentralHeatingMaximumSystemAirFlowRatioAutosized() const {
  return getImpl<detail::SizingSystem_Impl>()->isCentralHeatingMaximumSystemAirFlowRatioAutosized();
}

double SizingSystem::preheatDesignTemperature() const {
  return getImpl<detail::SizingSystem_Impl>()->preheatDesignTemperature();
}

double SizingSystem::preheatDesignHumidityRatio() const {
  return getImpl<detail::SizingSystem_Impl>()->preheatDesignHumidityRatio();
}

double SizingSystem::precoolDesignTemperature() const {
  return getImpl<detail::SizingSystem_Impl>()->precoolDesignTemperature();
}

double SizingSystem::precoolDesignHumidityRatio() const {
  return getImpl<detail::SizingSystem_Impl>()->precoolDesignHumidityRatio();
}

double SizingSystem::centralCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::SizingSystem_Impl>()->centralCoolingDesignSupplyAirTemperature();
}

double SizingSystem::centralHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::SizingSystem_Impl>()->centralHeatingDesignSupplyAirTemperature();
}

std::string SizingSystem::sizingOption() const {
  return getImpl<detail::SizingSystem_Impl>()->sizingOption();
}

bool SizingSystem::isSizingOptionDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isSizingOptionDefaulted();
}

bool SizingSystem::allOutdoorAirinCooling() const {
  return getImpl<detail::SizingSystem_Impl>()->allOutdoorAirinCooling();
}

bool SizingSystem::isAllOutdoorAirinCoolingDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isAllOutdoorAirinCoolingDefaulted();
}

bool SizingSystem::allOutdoorAirinHeating() const {
  return getImpl<detail::SizingSystem_Impl>()->allOutdoorAirinHeating();
}

bool SizingSystem::isAllOutdoorAirinHeatingDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isAllOutdoorAirinHeatingDefaulted();
}

double SizingSystem::centralCoolingDesignSupplyAirHumidityRatio() const {
  return getImpl<detail::SizingSystem_Impl>()->centralCoolingDesignSupplyAirHumidityRatio();
}

bool SizingSystem::isCentralCoolingDesignSupplyAirHumidityRatioDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isCentralCoolingDesignSupplyAirHumidityRatioDefaulted();
}

double SizingSystem::centralHeatingDesignSupplyAirHumidityRatio() const {
  return getImpl<detail::SizingSystem_Impl>()->centralHeatingDesignSupplyAirHumidityRatio();
}

bool SizingSystem::isCentralHeatingDesignSupplyAirHumidityRatioDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isCentralHeatingDesignSupplyAirHumidityRatioDefaulted();
}

std::string SizingSystem::coolingDesignAirFlowMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingDesignAirFlowMethod();
}

bool SizingSystem::isCoolingDesignAirFlowMethodDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isCoolingDesignAirFlowMethodDefaulted();
}

double SizingSystem::coolingDesignAirFlowRate() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingDesignAirFlowRate();
}

bool SizingSystem::isCoolingDesignAirFlowRateDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isCoolingDesignAirFlowRateDefaulted();
}

std::string SizingSystem::heatingDesignAirFlowMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingDesignAirFlowMethod();
}

bool SizingSystem::isHeatingDesignAirFlowMethodDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isHeatingDesignAirFlowMethodDefaulted();
}

double SizingSystem::heatingDesignAirFlowRate() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingDesignAirFlowRate();
}

bool SizingSystem::isHeatingDesignAirFlowRateDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isHeatingDesignAirFlowRateDefaulted();
}

std::string SizingSystem::systemOutdoorAirMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->systemOutdoorAirMethod();
}

bool SizingSystem::isSystemOutdoorAirMethodDefaulted() const {
  return getImpl<detail::SizingSystem_Impl>()->isSystemOutdoorAirMethodDefaulted();
}

double SizingSystem::zoneMaximumOutdoorAirFraction() const {
  return getImpl<detail::SizingSystem_Impl>()->zoneMaximumOutdoorAirFraction();
}

double SizingSystem::coolingSupplyAirFlowRatePerFloorArea() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingSupplyAirFlowRatePerFloorArea();
}

double SizingSystem::coolingFractionofAutosizedCoolingSupplyAirFlowRate() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingFractionofAutosizedCoolingSupplyAirFlowRate();
}

double SizingSystem::coolingSupplyAirFlowRatePerUnitCoolingCapacity() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingSupplyAirFlowRatePerUnitCoolingCapacity();
}

double SizingSystem::heatingSupplyAirFlowRatePerFloorArea() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingSupplyAirFlowRatePerFloorArea();
}

double SizingSystem::heatingFractionofAutosizedHeatingSupplyAirFlowRate() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingFractionofAutosizedHeatingSupplyAirFlowRate();
}

double SizingSystem::heatingFractionofAutosizedCoolingSupplyAirFlowRate() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingFractionofAutosizedCoolingSupplyAirFlowRate();
}

double SizingSystem::heatingSupplyAirFlowRatePerUnitHeatingCapacity() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingSupplyAirFlowRatePerUnitHeatingCapacity();
}

std::string SizingSystem::coolingDesignCapacityMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingDesignCapacityMethod();
}

boost::optional<double> SizingSystem::coolingDesignCapacity() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingDesignCapacity();
}

bool SizingSystem::isCoolingDesignCapacityAutosized() const {
  return getImpl<detail::SizingSystem_Impl>()->isCoolingDesignCapacityAutosized();
}

double SizingSystem::coolingDesignCapacityPerFloorArea() const {
  return getImpl<detail::SizingSystem_Impl>()->coolingDesignCapacityPerFloorArea();
}

double SizingSystem::fractionofAutosizedCoolingDesignCapacity() const {
  return getImpl<detail::SizingSystem_Impl>()->fractionofAutosizedCoolingDesignCapacity();
}

std::string SizingSystem::heatingDesignCapacityMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingDesignCapacityMethod();
}

boost::optional<double> SizingSystem::heatingDesignCapacity() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingDesignCapacity();
}

bool SizingSystem::isHeatingDesignCapacityAutosized() const {
  return getImpl<detail::SizingSystem_Impl>()->isHeatingDesignCapacityAutosized();
}

double SizingSystem::heatingDesignCapacityPerFloorArea() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingDesignCapacityPerFloorArea();
}

double SizingSystem::fractionofAutosizedHeatingDesignCapacity() const {
  return getImpl<detail::SizingSystem_Impl>()->fractionofAutosizedHeatingDesignCapacity();
}

std::string SizingSystem::centralCoolingCapacityControlMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->centralCoolingCapacityControlMethod();
}

boost::optional<double> SizingSystem::occupantDiversity() const {
  return getImpl<detail::SizingSystem_Impl>()->occupantDiversity();
}

bool SizingSystem::isOccupantDiversityAutosized() const {
  return getImpl<detail::SizingSystem_Impl>()->isOccupantDiversityAutosized();
}

std::string SizingSystem::heatingCoilSizingMethod() const {
  return getImpl<detail::SizingSystem_Impl>()->heatingCoilSizingMethod();
}

double SizingSystem::maximumHeatingCapacityToCoolingCapacitySizingRatio() const {
  return getImpl<detail::SizingSystem_Impl>()->maximumHeatingCapacityToCoolingCapacitySizingRatio();
}

bool SizingSystem::setTypeofLoadtoSizeOn(const std::string& typeofLoadtoSizeOn) {
  return getImpl<detail::SizingSystem_Impl>()->setTypeofLoadtoSizeOn(typeofLoadtoSizeOn);
}

void SizingSystem::resetTypeofLoadtoSizeOn() {
  getImpl<detail::SizingSystem_Impl>()->resetTypeofLoadtoSizeOn();
}

bool SizingSystem::setDesignOutdoorAirFlowRate(double designOutdoorAirFlowRate) {
  return getImpl<detail::SizingSystem_Impl>()->setDesignOutdoorAirFlowRate(designOutdoorAirFlowRate);
}

void SizingSystem::resetDesignOutdoorAirFlowRate() {
  getImpl<detail::SizingSystem_Impl>()->resetDesignOutdoorAirFlowRate();
}

void SizingSystem::autosizeDesignOutdoorAirFlowRate() {
  getImpl<detail::SizingSystem_Impl>()->autosizeDesignOutdoorAirFlowRate();
}

bool SizingSystem::setCentralHeatingMaximumSystemAirFlowRatio(double centralHeatingMaximumSystemAirFlowRatio) {
  return getImpl<detail::SizingSystem_Impl>()->setCentralHeatingMaximumSystemAirFlowRatio(centralHeatingMaximumSystemAirFlowRatio);
}

void SizingSystem::resetCentralHeatingMaximumSystemAirFlowRatio() {
  getImpl<detail::SizingSystem_Impl>()->resetCentralHeatingMaximumSystemAirFlowRatio();
}

void SizingSystem::autosizeCentralHeatingMaximumSystemAirFlowRatio() {
  getImpl<detail::SizingSystem_Impl>()->autosizeCentralHeatingMaximumSystemAirFlowRatio();
}

bool SizingSystem::setPreheatDesignTemperature(double preheatDesignTemperature) {
  return getImpl<detail::SizingSystem_Impl>()->setPreheatDesignTemperature(preheatDesignTemperature);
}

bool SizingSystem::setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio) {
  return getImpl<detail::SizingSystem_Impl>()->setPreheatDesignHumidityRatio(preheatDesignHumidityRatio);
}

bool SizingSystem::setPrecoolDesignTemperature(double precoolDesignTemperature) {
  return getImpl<detail::SizingSystem_Impl>()->setPrecoolDesignTemperature(precoolDesignTemperature);
}

bool SizingSystem::setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio) {
  return getImpl<detail::SizingSystem_Impl>()->setPrecoolDesignHumidityRatio(precoolDesignHumidityRatio);
}

bool SizingSystem::setCentralCoolingDesignSupplyAirTemperature(double centralCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::SizingSystem_Impl>()->setCentralCoolingDesignSupplyAirTemperature(centralCoolingDesignSupplyAirTemperature);
}

bool SizingSystem::setCentralHeatingDesignSupplyAirTemperature(double centralHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::SizingSystem_Impl>()->setCentralHeatingDesignSupplyAirTemperature(centralHeatingDesignSupplyAirTemperature);
}

bool SizingSystem::setSizingOption(const std::string& sizingOption) {
  return getImpl<detail::SizingSystem_Impl>()->setSizingOption(sizingOption);
}

void SizingSystem::resetSizingOption() {
  getImpl<detail::SizingSystem_Impl>()->resetSizingOption();
}

bool SizingSystem::setAllOutdoorAirinCooling(bool allOutdoorAirinCooling) {
  return getImpl<detail::SizingSystem_Impl>()->setAllOutdoorAirinCooling(allOutdoorAirinCooling);
}

void SizingSystem::resetAllOutdoorAirinCooling() {
  getImpl<detail::SizingSystem_Impl>()->resetAllOutdoorAirinCooling();
}

bool SizingSystem::setAllOutdoorAirinHeating(bool allOutdoorAirinHeating) {
  return getImpl<detail::SizingSystem_Impl>()->setAllOutdoorAirinHeating(allOutdoorAirinHeating);
}

void SizingSystem::resetAllOutdoorAirinHeating() {
  getImpl<detail::SizingSystem_Impl>()->resetAllOutdoorAirinHeating();
}

bool SizingSystem::setCentralCoolingDesignSupplyAirHumidityRatio(double centralCoolingDesignSupplyAirHumidityRatio) {
  return getImpl<detail::SizingSystem_Impl>()->setCentralCoolingDesignSupplyAirHumidityRatio(centralCoolingDesignSupplyAirHumidityRatio);
}

void SizingSystem::resetCentralCoolingDesignSupplyAirHumidityRatio() {
  getImpl<detail::SizingSystem_Impl>()->resetCentralCoolingDesignSupplyAirHumidityRatio();
}

bool SizingSystem::setCentralHeatingDesignSupplyAirHumidityRatio(double centralHeatingDesignSupplyAirHumidityRatio) {
  return getImpl<detail::SizingSystem_Impl>()->setCentralHeatingDesignSupplyAirHumidityRatio(centralHeatingDesignSupplyAirHumidityRatio);
}

void SizingSystem::resetCentralHeatingDesignSupplyAirHumidityRatio() {
  getImpl<detail::SizingSystem_Impl>()->resetCentralHeatingDesignSupplyAirHumidityRatio();
}

bool SizingSystem::setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingDesignAirFlowMethod(coolingDesignAirFlowMethod);
}

void SizingSystem::resetCoolingDesignAirFlowMethod() {
  getImpl<detail::SizingSystem_Impl>()->resetCoolingDesignAirFlowMethod();
}

bool SizingSystem::setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingDesignAirFlowRate(coolingDesignAirFlowRate);
}

void SizingSystem::resetCoolingDesignAirFlowRate() {
  getImpl<detail::SizingSystem_Impl>()->resetCoolingDesignAirFlowRate();
}

bool SizingSystem::setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingDesignAirFlowMethod(heatingDesignAirFlowMethod);
}

void SizingSystem::resetHeatingDesignAirFlowMethod() {
  getImpl<detail::SizingSystem_Impl>()->resetHeatingDesignAirFlowMethod();
}

bool SizingSystem::setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingDesignAirFlowRate(heatingDesignAirFlowRate);
}

void SizingSystem::resetHeatingDesignAirFlowRate() {
  getImpl<detail::SizingSystem_Impl>()->resetHeatingDesignAirFlowRate();
}

bool SizingSystem::setSystemOutdoorAirMethod(const std::string& systemOutdoorAirMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setSystemOutdoorAirMethod(systemOutdoorAirMethod);
}

void SizingSystem::resetSystemOutdoorAirMethod() {
  getImpl<detail::SizingSystem_Impl>()->resetSystemOutdoorAirMethod();
}

bool SizingSystem::setZoneMaximumOutdoorAirFraction(double zoneMaximumOutdoorAirFraction) {
  return getImpl<detail::SizingSystem_Impl>()->setZoneMaximumOutdoorAirFraction(zoneMaximumOutdoorAirFraction);
}

bool SizingSystem::setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingSupplyAirFlowRatePerFloorArea(coolingSupplyAirFlowRatePerFloorArea);
}

bool SizingSystem::setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(
    coolingFractionofAutosizedCoolingSupplyAirFlowRate);
}

bool SizingSystem::setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(coolingSupplyAirFlowRatePerUnitCoolingCapacity);
}

bool SizingSystem::setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingSupplyAirFlowRatePerFloorArea(heatingSupplyAirFlowRatePerFloorArea);
}

bool SizingSystem::setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(double heatingFractionofAutosizedHeatingSupplyAirFlowRate) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(
    heatingFractionofAutosizedHeatingSupplyAirFlowRate);
}

bool SizingSystem::setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(double heatingFractionofAutosizedCoolingSupplyAirFlowRate) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(
    heatingFractionofAutosizedCoolingSupplyAirFlowRate);
}

bool SizingSystem::setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(heatingSupplyAirFlowRatePerUnitHeatingCapacity);
}

bool SizingSystem::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
}

bool SizingSystem::setCoolingDesignCapacity(double coolingDesignCapacity) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
}

void SizingSystem::autosizeCoolingDesignCapacity() {
  getImpl<detail::SizingSystem_Impl>()->autosizeCoolingDesignCapacity();
}

bool SizingSystem::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
  return getImpl<detail::SizingSystem_Impl>()->setCoolingDesignCapacityPerFloorArea(coolingDesignCapacityPerFloorArea);
}

bool SizingSystem::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
  return getImpl<detail::SizingSystem_Impl>()->setFractionofAutosizedCoolingDesignCapacity(fractionofAutosizedCoolingDesignCapacity);
}

bool SizingSystem::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
}

bool SizingSystem::setHeatingDesignCapacity(double heatingDesignCapacity) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
}

void SizingSystem::autosizeHeatingDesignCapacity() {
  getImpl<detail::SizingSystem_Impl>()->autosizeHeatingDesignCapacity();
}

bool SizingSystem::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
}

bool SizingSystem::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return getImpl<detail::SizingSystem_Impl>()->setFractionofAutosizedHeatingDesignCapacity(fractionofAutosizedHeatingDesignCapacity);
}

bool SizingSystem::setCentralCoolingCapacityControlMethod(const std::string& centralCoolingCapacityControlMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setCentralCoolingCapacityControlMethod(centralCoolingCapacityControlMethod);
}

bool SizingSystem::setOccupantDiversity(double occupantDiversity) {
  return getImpl<detail::SizingSystem_Impl>()->setOccupantDiversity(occupantDiversity);
}

void SizingSystem::autosizeOccupantDiversity() {
  getImpl<detail::SizingSystem_Impl>()->autosizeOccupantDiversity();
}

bool SizingSystem::setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod) {
  return getImpl<detail::SizingSystem_Impl>()->setHeatingCoilSizingMethod(heatingCoilSizingMethod);
}

bool SizingSystem::setMaximumHeatingCapacityToCoolingCapacitySizingRatio(double maximumHeatingCapacityToCoolingCapacitySizingRatio) {
  return getImpl<detail::SizingSystem_Impl>()->setMaximumHeatingCapacityToCoolingCapacitySizingRatio(
    maximumHeatingCapacityToCoolingCapacitySizingRatio);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string SizingSystem_Impl::typeofLoadtoSizeOn() const {
  auto value = getString(openstudio::Sizing_SystemFields::TypeofLoadtoSizeOn, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isTypeofLoadtoSizeOnDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::TypeofLoadtoSizeOn);
}

bool SizingSystem_Impl::setTypeofLoadtoSizeOn(const std::string& typeofLoadtoSizeOn) {
  return setString(openstudio::Sizing_SystemFields::TypeofLoadtoSizeOn, typeofLoadtoSizeOn);
}

void SizingSystem_Impl::resetTypeofLoadtoSizeOn() {
  bool result = setString(openstudio::Sizing_SystemFields::TypeofLoadtoSizeOn, "");
  OS_ASSERT(result);
}

boost::optional<double> SizingSystem_Impl::designOutdoorAirFlowRate() const {
  return getDouble(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate, true);
}

bool SizingSystem_Impl::isDesignOutdoorAirFlowRateDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate);
}

bool SizingSystem_Impl::isDesignOutdoorAirFlowRateAutosized() const {
  auto value = getString(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool SizingSystem_Impl::setDesignOutdoorAirFlowRate(boost::optional<double> designOutdoorAirFlowRate) {
  if (designOutdoorAirFlowRate) {
    return setDouble(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate, *designOutdoorAirFlowRate);
  }
  return setString(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate, "");
}

void SizingSystem_Impl::resetDesignOutdoorAirFlowRate() {
  bool result = setString(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate, "");
  OS_ASSERT(result);
}

void SizingSystem_Impl::autosizeDesignOutdoorAirFlowRate() {
  bool result = setString(openstudio::Sizing_SystemFields::DesignOutdoorAirFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> SizingSystem_Impl::centralHeatingMaximumSystemAirFlowRatio() const {
  return getDouble(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, true);
}

bool SizingSystem_Impl::isCentralHeatingMaximumSystemAirFlowRatioDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio);
}

bool SizingSystem_Impl::isCentralHeatingMaximumSystemAirFlowRatioAutosized() const {
  auto value = getString(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool SizingSystem_Impl::setCentralHeatingMaximumSystemAirFlowRatio(boost::optional<double> centralHeatingMaximumSystemAirFlowRatio) {
  if (centralHeatingMaximumSystemAirFlowRatio) {
    return setDouble(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, *centralHeatingMaximumSystemAirFlowRatio);
  }
  return setString(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, "");
}

void SizingSystem_Impl::resetCentralHeatingMaximumSystemAirFlowRatio() {
  bool result = setString(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, "");
  OS_ASSERT(result);
}

void SizingSystem_Impl::autosizeCentralHeatingMaximumSystemAirFlowRatio() {
  bool result = setString(openstudio::Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, "Autosize");
  OS_ASSERT(result);
}

double SizingSystem_Impl::preheatDesignTemperature() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::PreheatDesignTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setPreheatDesignTemperature(double preheatDesignTemperature) {
  bool result = setDouble(openstudio::Sizing_SystemFields::PreheatDesignTemperature, preheatDesignTemperature);
  OS_ASSERT(result);
  return result;
}

double SizingSystem_Impl::preheatDesignHumidityRatio() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::PreheatDesignHumidityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio) {
  bool result = setDouble(openstudio::Sizing_SystemFields::PreheatDesignHumidityRatio, preheatDesignHumidityRatio);
  OS_ASSERT(result);
  return result;
}

double SizingSystem_Impl::precoolDesignTemperature() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::PrecoolDesignTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setPrecoolDesignTemperature(double precoolDesignTemperature) {
  bool result = setDouble(openstudio::Sizing_SystemFields::PrecoolDesignTemperature, precoolDesignTemperature);
  OS_ASSERT(result);
  return result;
}

double SizingSystem_Impl::precoolDesignHumidityRatio() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::PrecoolDesignHumidityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio) {
  bool result = setDouble(openstudio::Sizing_SystemFields::PrecoolDesignHumidityRatio, precoolDesignHumidityRatio);
  OS_ASSERT(result);
  return result;
}

double SizingSystem_Impl::centralCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CentralCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCentralCoolingDesignSupplyAirTemperature(double centralCoolingDesignSupplyAirTemperature) {
  bool result = setDouble(openstudio::Sizing_SystemFields::CentralCoolingDesignSupplyAirTemperature, centralCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

double SizingSystem_Impl::centralHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CentralHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCentralHeatingDesignSupplyAirTemperature(double centralHeatingDesignSupplyAirTemperature) {
  bool result = setDouble(openstudio::Sizing_SystemFields::CentralHeatingDesignSupplyAirTemperature, centralHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

std::string SizingSystem_Impl::sizingOption() const {
  auto value = getString(openstudio::Sizing_SystemFields::TypeofZoneSumtoUse, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isSizingOptionDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::TypeofZoneSumtoUse);
}

bool SizingSystem_Impl::setSizingOption(const std::string& sizingOption) {
  return setString(openstudio::Sizing_SystemFields::TypeofZoneSumtoUse, sizingOption);
}

void SizingSystem_Impl::resetSizingOption() {
  bool result = setString(openstudio::Sizing_SystemFields::TypeofZoneSumtoUse, "");
  OS_ASSERT(result);
}

bool SizingSystem_Impl::allOutdoorAirinCooling() const {
  auto value = getString(openstudio::Sizing_SystemFields::AllOutdoorAirinCooling, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SizingSystem_Impl::isAllOutdoorAirinCoolingDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::AllOutdoorAirinCooling);
}

bool SizingSystem_Impl::setAllOutdoorAirinCooling(bool allOutdoorAirinCooling) {
  bool result = setString(openstudio::Sizing_SystemFields::AllOutdoorAirinCooling, allOutdoorAirinCooling ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void SizingSystem_Impl::resetAllOutdoorAirinCooling() {
  bool result = setString(openstudio::Sizing_SystemFields::AllOutdoorAirinCooling, "");
  OS_ASSERT(result);
}

bool SizingSystem_Impl::allOutdoorAirinHeating() const {
  auto value = getString(openstudio::Sizing_SystemFields::AllOutdoorAirinHeating, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SizingSystem_Impl::isAllOutdoorAirinHeatingDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::AllOutdoorAirinHeating);
}

bool SizingSystem_Impl::setAllOutdoorAirinHeating(bool allOutdoorAirinHeating) {
  bool result = setString(openstudio::Sizing_SystemFields::AllOutdoorAirinHeating, allOutdoorAirinHeating ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void SizingSystem_Impl::resetAllOutdoorAirinHeating() {
  bool result = setString(openstudio::Sizing_SystemFields::AllOutdoorAirinHeating, "");
  OS_ASSERT(result);
}

double SizingSystem_Impl::centralCoolingDesignSupplyAirHumidityRatio() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CentralCoolingDesignSupplyAirHumidityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isCentralCoolingDesignSupplyAirHumidityRatioDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::CentralCoolingDesignSupplyAirHumidityRatio);
}

bool SizingSystem_Impl::setCentralCoolingDesignSupplyAirHumidityRatio(double centralCoolingDesignSupplyAirHumidityRatio) {
  bool result =
    setDouble(openstudio::Sizing_SystemFields::CentralCoolingDesignSupplyAirHumidityRatio, centralCoolingDesignSupplyAirHumidityRatio);
  OS_ASSERT(result);
  return result;
}

void SizingSystem_Impl::resetCentralCoolingDesignSupplyAirHumidityRatio() {
  bool result = setString(openstudio::Sizing_SystemFields::CentralCoolingDesignSupplyAirHumidityRatio, "");
  OS_ASSERT(result);
}

double SizingSystem_Impl::centralHeatingDesignSupplyAirHumidityRatio() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CentralHeatingDesignSupplyAirHumidityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isCentralHeatingDesignSupplyAirHumidityRatioDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::CentralHeatingDesignSupplyAirHumidityRatio);
}

bool SizingSystem_Impl::setCentralHeatingDesignSupplyAirHumidityRatio(double centralHeatingDesignSupplyAirHumidityRatio) {
  bool result =
    setDouble(openstudio::Sizing_SystemFields::CentralHeatingDesignSupplyAirHumidityRatio, centralHeatingDesignSupplyAirHumidityRatio);
  OS_ASSERT(result);
  return result;
}

void SizingSystem_Impl::resetCentralHeatingDesignSupplyAirHumidityRatio() {
  bool result = setString(openstudio::Sizing_SystemFields::CentralHeatingDesignSupplyAirHumidityRatio, "");
  OS_ASSERT(result);
}

std::string SizingSystem_Impl::coolingDesignAirFlowMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isCoolingDesignAirFlowMethodDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRateMethod);
}

bool SizingSystem_Impl::setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod) {
  return setString(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRateMethod, coolingDesignAirFlowMethod);
}

void SizingSystem_Impl::resetCoolingDesignAirFlowMethod() {
  bool result = setString(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRateMethod, "");
  OS_ASSERT(result);
}

double SizingSystem_Impl::coolingDesignAirFlowRate() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isCoolingDesignAirFlowRateDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRate);
}

bool SizingSystem_Impl::setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate) {
  return setDouble(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRate, coolingDesignAirFlowRate);
}

void SizingSystem_Impl::resetCoolingDesignAirFlowRate() {
  bool result = setString(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRate, "");
  OS_ASSERT(result);
}

std::string SizingSystem_Impl::heatingDesignAirFlowMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isHeatingDesignAirFlowMethodDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRateMethod);
}

bool SizingSystem_Impl::setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod) {
  return setString(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRateMethod, heatingDesignAirFlowMethod);
}

void SizingSystem_Impl::resetHeatingDesignAirFlowMethod() {
  bool result = setString(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRateMethod, "");
  OS_ASSERT(result);
}

double SizingSystem_Impl::heatingDesignAirFlowRate() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isHeatingDesignAirFlowRateDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRate);
}

bool SizingSystem_Impl::setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate) {
  return setDouble(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRate, heatingDesignAirFlowRate);
}

void SizingSystem_Impl::resetHeatingDesignAirFlowRate() {
  bool result = setString(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRate, "");
  OS_ASSERT(result);
}

std::string SizingSystem_Impl::systemOutdoorAirMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::SystemOutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::isSystemOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::Sizing_SystemFields::SystemOutdoorAirMethod);
}

bool SizingSystem_Impl::setSystemOutdoorAirMethod(const std::string& systemOutdoorAirMethod) {
  return setString(openstudio::Sizing_SystemFields::SystemOutdoorAirMethod, systemOutdoorAirMethod);
}

void SizingSystem_Impl::resetSystemOutdoorAirMethod() {
  bool result = setString(openstudio::Sizing_SystemFields::SystemOutdoorAirMethod, "");
  OS_ASSERT(result);
}

double SizingSystem_Impl::zoneMaximumOutdoorAirFraction() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::ZoneMaximumOutdoorAirFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setZoneMaximumOutdoorAirFraction(double zoneMaximumOutdoorAirFraction) {
  return setDouble(openstudio::Sizing_SystemFields::ZoneMaximumOutdoorAirFraction, zoneMaximumOutdoorAirFraction);
}

double SizingSystem_Impl::coolingSupplyAirFlowRatePerFloorArea() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRatePerFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea) {
  return setDouble(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRatePerFloorArea, coolingSupplyAirFlowRatePerFloorArea);
}

double SizingSystem_Impl::coolingFractionofAutosizedCoolingSupplyAirFlowRate() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate) {
  return setDouble(openstudio::Sizing_SystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate,
                   coolingFractionofAutosizedCoolingSupplyAirFlowRate);
}

double SizingSystem_Impl::coolingSupplyAirFlowRatePerUnitCoolingCapacity() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity) {
  return setDouble(openstudio::Sizing_SystemFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, coolingSupplyAirFlowRatePerUnitCoolingCapacity);
}

double SizingSystem_Impl::heatingSupplyAirFlowRatePerFloorArea() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRatePerFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea) {
  return setDouble(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRatePerFloorArea, heatingSupplyAirFlowRatePerFloorArea);
}

double SizingSystem_Impl::heatingFractionofAutosizedHeatingSupplyAirFlowRate() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(double heatingFractionofAutosizedHeatingSupplyAirFlowRate) {
  return setDouble(openstudio::Sizing_SystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate,
                   heatingFractionofAutosizedHeatingSupplyAirFlowRate);
}

double SizingSystem_Impl::heatingFractionofAutosizedCoolingSupplyAirFlowRate() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::HeatingFractionofAutosizedCoolingSupplyAirFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(double heatingFractionofAutosizedCoolingSupplyAirFlowRate) {
  return setDouble(openstudio::Sizing_SystemFields::HeatingFractionofAutosizedCoolingSupplyAirFlowRate,
                   heatingFractionofAutosizedCoolingSupplyAirFlowRate);
}

double SizingSystem_Impl::heatingSupplyAirFlowRatePerUnitHeatingCapacity() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity) {
  return setDouble(openstudio::Sizing_SystemFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, heatingSupplyAirFlowRatePerUnitHeatingCapacity);
}

std::string SizingSystem_Impl::coolingDesignCapacityMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::CoolingDesignCapacityMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
  return setString(openstudio::Sizing_SystemFields::CoolingDesignCapacityMethod, coolingDesignCapacityMethod);
}

boost::optional<double> SizingSystem_Impl::coolingDesignCapacity() const {
  return getDouble(openstudio::Sizing_SystemFields::CoolingDesignCapacity, true);
}

bool SizingSystem_Impl::isCoolingDesignCapacityAutosized() const {
  auto value = getString(openstudio::Sizing_SystemFields::CoolingDesignCapacity, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool SizingSystem_Impl::setCoolingDesignCapacity(boost::optional<double> coolingDesignCapacity) {
  if (coolingDesignCapacity) {
    return setDouble(openstudio::Sizing_SystemFields::CoolingDesignCapacity, *coolingDesignCapacity);
  }
  return false;
}

void SizingSystem_Impl::autosizeCoolingDesignCapacity() {
  bool result = setString(openstudio::Sizing_SystemFields::CoolingDesignCapacity, "autosize");
  OS_ASSERT(result);
}

double SizingSystem_Impl::coolingDesignCapacityPerFloorArea() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::CoolingDesignCapacityPerFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
  return setDouble(openstudio::Sizing_SystemFields::CoolingDesignCapacityPerFloorArea, coolingDesignCapacityPerFloorArea);
}

double SizingSystem_Impl::fractionofAutosizedCoolingDesignCapacity() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::FractionofAutosizedCoolingDesignCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
  return setDouble(openstudio::Sizing_SystemFields::FractionofAutosizedCoolingDesignCapacity, fractionofAutosizedCoolingDesignCapacity);
}

std::string SizingSystem_Impl::heatingDesignCapacityMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::HeatingDesignCapacityMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
  return setString(openstudio::Sizing_SystemFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
}

boost::optional<double> SizingSystem_Impl::heatingDesignCapacity() const {
  return getDouble(openstudio::Sizing_SystemFields::HeatingDesignCapacity, true);
}

bool SizingSystem_Impl::isHeatingDesignCapacityAutosized() const {
  auto value = getString(openstudio::Sizing_SystemFields::HeatingDesignCapacity, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool SizingSystem_Impl::setHeatingDesignCapacity(boost::optional<double> heatingDesignCapacity) {
  if (heatingDesignCapacity) {
    return setDouble(openstudio::Sizing_SystemFields::HeatingDesignCapacity, *heatingDesignCapacity);
  }
  return false;
}

void SizingSystem_Impl::autosizeHeatingDesignCapacity() {
  bool result = setString(openstudio::Sizing_SystemFields::HeatingDesignCapacity, "autosize");
  OS_ASSERT(result);
}

double SizingSystem_Impl::heatingDesignCapacityPerFloorArea() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::HeatingDesignCapacityPerFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
  return setDouble(openstudio::Sizing_SystemFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
}

double SizingSystem_Impl::fractionofAutosizedHeatingDesignCapacity() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::FractionofAutosizedHeatingDesignCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
  return setDouble(openstudio::Sizing_SystemFields::FractionofAutosizedHeatingDesignCapacity, fractionofAutosizedHeatingDesignCapacity);
}

std::string SizingSystem_Impl::centralCoolingCapacityControlMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::CentralCoolingCapacityControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setCentralCoolingCapacityControlMethod(const std::string& centralCoolingCapacityControlMethod) {
  return setString(openstudio::Sizing_SystemFields::CentralCoolingCapacityControlMethod, centralCoolingCapacityControlMethod);
}

boost::optional<double> SizingSystem_Impl::occupantDiversity() const {
  return getDouble(openstudio::Sizing_SystemFields::OccupantDiversity, true);
}

bool SizingSystem_Impl::isOccupantDiversityAutosized() const {
  auto value = getString(openstudio::Sizing_SystemFields::OccupantDiversity, true);
  return value && openstudio::istringEqual(*value, "autosize");
}

bool SizingSystem_Impl::setOccupantDiversity(double occupantDiversity) {
  return setDouble(openstudio::Sizing_SystemFields::OccupantDiversity, occupantDiversity);
}

void SizingSystem_Impl::autosizeOccupantDiversity() {
  bool result = setString(openstudio::Sizing_SystemFields::OccupantDiversity, "autosize");
  OS_ASSERT(result);
}

std::string SizingSystem_Impl::heatingCoilSizingMethod() const {
  auto value = getString(openstudio::Sizing_SystemFields::HeatingCoilSizingMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod) {
  return setString(openstudio::Sizing_SystemFields::HeatingCoilSizingMethod, heatingCoilSizingMethod);
}

double SizingSystem_Impl::maximumHeatingCapacityToCoolingCapacitySizingRatio() const {
  auto value = getDouble(openstudio::Sizing_SystemFields::MaximumHeatingCapacityToCoolingCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingSystem_Impl::setMaximumHeatingCapacityToCoolingCapacitySizingRatio(double maximumHeatingCapacityToCoolingCapacitySizingRatio) {
  return setDouble(openstudio::Sizing_SystemFields::MaximumHeatingCapacityToCoolingCapacitySizingRatio,
                   maximumHeatingCapacityToCoolingCapacitySizingRatio);
}

bool SizingSystem_Impl::setAirLoopHVAC(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC) {
  if (model() != airLoopHVAC.model()) {
    return false;
  }
  bool result = setPointer(openstudio::Sizing_SystemFields::AirLoopName, airLoopHVAC.handle(), false);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
