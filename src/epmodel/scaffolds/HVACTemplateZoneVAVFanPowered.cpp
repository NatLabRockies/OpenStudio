/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneVAVFanPowered.hpp"
#include "HVACTemplateZoneVAVFanPowered_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_VAV_FanPowered_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneVAVFanPowered::HVACTemplateZoneVAVFanPowered(const Model& model)
  : ModelObject(HVACTemplateZoneVAVFanPowered::iddObjectType(), model) {}

HVACTemplateZoneVAVFanPowered::HVACTemplateZoneVAVFanPowered(std::shared_ptr<detail::HVACTemplateZoneVAVFanPowered_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneVAVFanPowered::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_VAV_FanPowered;
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered::flowTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FlowType);
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered::reheatCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType);
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType);
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::primarySupplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->primarySupplyAirMaximumFlowRate();
}

bool HVACTemplateZoneVAVFanPowered::isPrimarySupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isPrimarySupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::isPrimarySupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isPrimarySupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneVAVFanPowered::setPrimarySupplyAirMaximumFlowRate(double primarySupplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setPrimarySupplyAirMaximumFlowRate(primarySupplyAirMaximumFlowRate);
}

void HVACTemplateZoneVAVFanPowered::resetPrimarySupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetPrimarySupplyAirMaximumFlowRate();
}

void HVACTemplateZoneVAVFanPowered::autosizePrimarySupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->autosizePrimarySupplyAirMaximumFlowRate();
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneHeatingSizingFactor();
}

bool HVACTemplateZoneVAVFanPowered::isZoneHeatingSizingFactorDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneHeatingSizingFactorDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

void HVACTemplateZoneVAVFanPowered::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneCoolingSizingFactor();
}

bool HVACTemplateZoneVAVFanPowered::isZoneCoolingSizingFactorDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneCoolingSizingFactorDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

void HVACTemplateZoneVAVFanPowered::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneCoolingSizingFactor();
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::primarySupplyAirMinimumFlowFraction() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->primarySupplyAirMinimumFlowFraction();
}

bool HVACTemplateZoneVAVFanPowered::isPrimarySupplyAirMinimumFlowFractionDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isPrimarySupplyAirMinimumFlowFractionDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::isPrimarySupplyAirMinimumFlowFractionAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isPrimarySupplyAirMinimumFlowFractionAutosized();
}

bool HVACTemplateZoneVAVFanPowered::setPrimarySupplyAirMinimumFlowFraction(double primarySupplyAirMinimumFlowFraction) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setPrimarySupplyAirMinimumFlowFraction(primarySupplyAirMinimumFlowFraction);
}

void HVACTemplateZoneVAVFanPowered::resetPrimarySupplyAirMinimumFlowFraction() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetPrimarySupplyAirMinimumFlowFraction();
}

void HVACTemplateZoneVAVFanPowered::autosizePrimarySupplyAirMinimumFlowFraction() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->autosizePrimarySupplyAirMinimumFlowFraction();
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::secondarySupplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->secondarySupplyAirMaximumFlowRate();
}

bool HVACTemplateZoneVAVFanPowered::isSecondarySupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isSecondarySupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::isSecondarySupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isSecondarySupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneVAVFanPowered::setSecondarySupplyAirMaximumFlowRate(double secondarySupplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setSecondarySupplyAirMaximumFlowRate(secondarySupplyAirMaximumFlowRate);
}

void HVACTemplateZoneVAVFanPowered::resetSecondarySupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetSecondarySupplyAirMaximumFlowRate();
}

void HVACTemplateZoneVAVFanPowered::autosizeSecondarySupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->autosizeSecondarySupplyAirMaximumFlowRate();
}

std::string HVACTemplateZoneVAVFanPowered::flowType() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->flowType();
}

bool HVACTemplateZoneVAVFanPowered::isFlowTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isFlowTypeDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setFlowType(const std::string& flowType) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setFlowType(flowType);
}

void HVACTemplateZoneVAVFanPowered::resetFlowType() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetFlowType();
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::parallelFanOnFlowFraction() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->parallelFanOnFlowFraction();
}

bool HVACTemplateZoneVAVFanPowered::isParallelFanOnFlowFractionDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isParallelFanOnFlowFractionDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::isParallelFanOnFlowFractionAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isParallelFanOnFlowFractionAutosized();
}

bool HVACTemplateZoneVAVFanPowered::setParallelFanOnFlowFraction(double parallelFanOnFlowFraction) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setParallelFanOnFlowFraction(parallelFanOnFlowFraction);
}

void HVACTemplateZoneVAVFanPowered::resetParallelFanOnFlowFraction() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetParallelFanOnFlowFraction();
}

void HVACTemplateZoneVAVFanPowered::autosizeParallelFanOnFlowFraction() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->autosizeParallelFanOnFlowFraction();
}

std::string HVACTemplateZoneVAVFanPowered::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->outdoorAirMethod();
}

bool HVACTemplateZoneVAVFanPowered::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

void HVACTemplateZoneVAVFanPowered::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetOutdoorAirMethod();
}

double HVACTemplateZoneVAVFanPowered::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->outdoorAirFlowRateperPerson();
}

bool HVACTemplateZoneVAVFanPowered::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

void HVACTemplateZoneVAVFanPowered::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetOutdoorAirFlowRateperPerson();
}

double HVACTemplateZoneVAVFanPowered::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

bool HVACTemplateZoneVAVFanPowered::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

void HVACTemplateZoneVAVFanPowered::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneVAVFanPowered::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->outdoorAirFlowRateperZone();
}

bool HVACTemplateZoneVAVFanPowered::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

void HVACTemplateZoneVAVFanPowered::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetOutdoorAirFlowRateperZone();
}

std::string HVACTemplateZoneVAVFanPowered::reheatCoilType() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->reheatCoilType();
}

bool HVACTemplateZoneVAVFanPowered::isReheatCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isReheatCoilTypeDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setReheatCoilType(const std::string& reheatCoilType) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setReheatCoilType(reheatCoilType);
}

void HVACTemplateZoneVAVFanPowered::resetReheatCoilType() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetReheatCoilType();
}

double HVACTemplateZoneVAVFanPowered::fanTotalEfficiency() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->fanTotalEfficiency();
}

bool HVACTemplateZoneVAVFanPowered::isFanTotalEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isFanTotalEfficiencyDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setFanTotalEfficiency(double fanTotalEfficiency) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
}

void HVACTemplateZoneVAVFanPowered::resetFanTotalEfficiency() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetFanTotalEfficiency();
}

double HVACTemplateZoneVAVFanPowered::fanDeltaPressure() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->fanDeltaPressure();
}

bool HVACTemplateZoneVAVFanPowered::isFanDeltaPressureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isFanDeltaPressureDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setFanDeltaPressure(double fanDeltaPressure) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setFanDeltaPressure(fanDeltaPressure);
}

void HVACTemplateZoneVAVFanPowered::resetFanDeltaPressure() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetFanDeltaPressure();
}

double HVACTemplateZoneVAVFanPowered::fanMotorEfficiency() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->fanMotorEfficiency();
}

bool HVACTemplateZoneVAVFanPowered::isFanMotorEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isFanMotorEfficiencyDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setFanMotorEfficiency(double fanMotorEfficiency) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setFanMotorEfficiency(fanMotorEfficiency);
}

void HVACTemplateZoneVAVFanPowered::resetFanMotorEfficiency() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetFanMotorEfficiency();
}

std::string HVACTemplateZoneVAVFanPowered::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->baseboardHeatingType();
}

bool HVACTemplateZoneVAVFanPowered::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

void HVACTemplateZoneVAVFanPowered::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetBaseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneVAVFanPowered::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->baseboardHeatingCapacity();
}

bool HVACTemplateZoneVAVFanPowered::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneVAVFanPowered::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

void HVACTemplateZoneVAVFanPowered::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneVAVFanPowered::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->autosizeBaseboardHeatingCapacity();
}

std::string HVACTemplateZoneVAVFanPowered::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

bool HVACTemplateZoneVAVFanPowered::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZoneVAVFanPowered::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneVAVFanPowered::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

bool HVACTemplateZoneVAVFanPowered::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

void HVACTemplateZoneVAVFanPowered::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZoneVAVFanPowered::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneVAVFanPowered::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneVAVFanPowered::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneVAVFanPowered::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

bool HVACTemplateZoneVAVFanPowered::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZoneVAVFanPowered::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneVAVFanPowered::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

bool HVACTemplateZoneVAVFanPowered::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

void HVACTemplateZoneVAVFanPowered::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZoneVAVFanPowered::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneVAVFanPowered::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneVAVFanPowered::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneVAVFanPowered::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneVAVFanPowered_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::primarySupplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, true);
}

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::primarySupplyAirMinimumFlowFraction() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, true);
}

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::secondarySupplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate, true);
}

std::string HVACTemplateZoneVAVFanPowered_Impl::flowType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FlowType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::parallelFanOnFlowFraction() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, true);
}

std::string HVACTemplateZoneVAVFanPowered_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneVAVFanPowered_Impl::reheatCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::fanTotalEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::fanDeltaPressure() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanDeltaPressure, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::fanMotorEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanMotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneVAVFanPowered_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneVAVFanPowered_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, true);
}

std::string HVACTemplateZoneVAVFanPowered_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneVAVFanPowered_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVFanPowered_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneVAVFanPowered_Impl::isPrimarySupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isPrimarySupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneHeatingSizingFactorDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingSizingFactor);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneCoolingSizingFactorDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingSizingFactor);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isPrimarySupplyAirMinimumFlowFractionDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isPrimarySupplyAirMinimumFlowFractionAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVFanPowered_Impl::isSecondarySupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isSecondarySupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVFanPowered_Impl::isFlowTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FlowType);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isParallelFanOnFlowFractionDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isParallelFanOnFlowFractionAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVFanPowered_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isReheatCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isFanTotalEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanTotalEfficiency);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isFanDeltaPressureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanDeltaPressure);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isFanMotorEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanMotorEfficiency);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneVAVFanPowered_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setPrimarySupplyAirMaximumFlowRate(double primarySupplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, primarySupplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setPrimarySupplyAirMinimumFlowFraction(double primarySupplyAirMinimumFlowFraction) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, primarySupplyAirMinimumFlowFraction);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setSecondarySupplyAirMaximumFlowRate(double secondarySupplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate,
                                secondarySupplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setFlowType(const std::string& flowType) {
  return setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FlowType, flowType);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setParallelFanOnFlowFraction(double parallelFanOnFlowFraction) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, parallelFanOnFlowFraction);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setReheatCoilType(const std::string& reheatCoilType) {
  return setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType, reheatCoilType);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanTotalEfficiency, fanTotalEfficiency);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setFanDeltaPressure(double fanDeltaPressure) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanDeltaPressure, fanDeltaPressure);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setFanMotorEfficiency(double fanMotorEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanMotorEfficiency, fanMotorEfficiency);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperature,
                                zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperature,
                                zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVFanPowered_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneVAVFanPowered_Impl::resetPrimarySupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::autosizePrimarySupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetPrimarySupplyAirMinimumFlowFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::autosizePrimarySupplyAirMinimumFlowFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, "autosize"));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetSecondarySupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::autosizeSecondarySupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetFlowType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FlowType, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetParallelFanOnFlowFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::autosizeParallelFanOnFlowFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, "autosize"));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetReheatCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetFanTotalEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanTotalEfficiency, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetFanDeltaPressure() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanDeltaPressure, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetFanMotorEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::FanMotorEfficiency, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, "autosize"));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneVAVFanPowered_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered_Impl::flowTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVFanPowered::flowTypeValues();
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVFanPowered::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered_Impl::reheatCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVFanPowered::reheatCoilTypeValues();
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVFanPowered::baseboardHeatingTypeValues();
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVFanPowered::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneVAVFanPowered_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVFanPowered::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
