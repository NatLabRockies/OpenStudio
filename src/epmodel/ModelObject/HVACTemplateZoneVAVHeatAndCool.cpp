/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneVAVHeatAndCool.hpp"
#include "HVACTemplateZoneVAVHeatAndCool_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_VAV_HeatAndCool_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneVAVHeatAndCool::HVACTemplateZoneVAVHeatAndCool(const Model& model)
  : ModelObject(HVACTemplateZoneVAVHeatAndCool::iddObjectType(), model) {}

HVACTemplateZoneVAVHeatAndCool::HVACTemplateZoneVAVHeatAndCool(std::shared_ptr<detail::HVACTemplateZoneVAVHeatAndCool_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneVAVHeatAndCool::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_VAV_HeatAndCool;
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool::reheatCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilType);
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingType);
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool::supplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->supplyAirMaximumFlowRate();
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneCoolingSizingFactor();
}

double HVACTemplateZoneVAVHeatAndCool::constantMinimumAirFlowFraction() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->constantMinimumAirFlowFraction();
}

std::string HVACTemplateZoneVAVHeatAndCool::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->outdoorAirMethod();
}

double HVACTemplateZoneVAVHeatAndCool::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->outdoorAirFlowRateperPerson();
}

double HVACTemplateZoneVAVHeatAndCool::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneVAVHeatAndCool::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->outdoorAirFlowRateperZone();
}

std::string HVACTemplateZoneVAVHeatAndCool::reheatCoilType() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->reheatCoilType();
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool::maximumReheatAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->maximumReheatAirTemperature();
}

std::string HVACTemplateZoneVAVHeatAndCool::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->baseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->baseboardHeatingCapacity();
}

std::string HVACTemplateZoneVAVHeatAndCool::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneVAVHeatAndCool::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZoneVAVHeatAndCool::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneVAVHeatAndCool::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneVAVHeatAndCool::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZoneVAVHeatAndCool::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneVAVHeatAndCool::isSupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isSupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isSupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneVAVHeatAndCool::isConstantMinimumAirFlowFractionDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isConstantMinimumAirFlowFractionDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isReheatCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isReheatCoilTypeDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneVAVHeatAndCool::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneVAVHeatAndCool::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

bool HVACTemplateZoneVAVHeatAndCool::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setConstantMinimumAirFlowFraction(constantMinimumAirFlowFraction);
}

bool HVACTemplateZoneVAVHeatAndCool::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

bool HVACTemplateZoneVAVHeatAndCool::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneVAVHeatAndCool::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneVAVHeatAndCool::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

bool HVACTemplateZoneVAVHeatAndCool::setReheatCoilType(const std::string& reheatCoilType) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setReheatCoilType(reheatCoilType);
}

bool HVACTemplateZoneVAVHeatAndCool::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
}

bool HVACTemplateZoneVAVHeatAndCool::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

bool HVACTemplateZoneVAVHeatAndCool::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneVAVHeatAndCool::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneVAVHeatAndCool::resetSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneVAVHeatAndCool::autosizeSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->autosizeSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneHeatingSizingFactor();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneCoolingSizingFactor();
}

void HVACTemplateZoneVAVHeatAndCool::resetConstantMinimumAirFlowFraction() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetConstantMinimumAirFlowFraction();
}

void HVACTemplateZoneVAVHeatAndCool::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetOutdoorAirMethod();
}

void HVACTemplateZoneVAVHeatAndCool::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetOutdoorAirFlowRateperPerson();
}

void HVACTemplateZoneVAVHeatAndCool::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

void HVACTemplateZoneVAVHeatAndCool::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetOutdoorAirFlowRateperZone();
}

void HVACTemplateZoneVAVHeatAndCool::resetReheatCoilType() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetReheatCoilType();
}

void HVACTemplateZoneVAVHeatAndCool::resetMaximumReheatAirTemperature() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetMaximumReheatAirTemperature();
}

void HVACTemplateZoneVAVHeatAndCool::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetBaseboardHeatingType();
}

void HVACTemplateZoneVAVHeatAndCool::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneVAVHeatAndCool::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->autosizeBaseboardHeatingCapacity();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

void HVACTemplateZoneVAVHeatAndCool::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneVAVHeatAndCool_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneVAVHeatAndCool_Impl::supplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate, true);
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingSizingFactor, true);
}

double HVACTemplateZoneVAVHeatAndCool_Impl::constantMinimumAirFlowFraction() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ConstantMinimumAirFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneVAVHeatAndCool_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneVAVHeatAndCool_Impl::reheatCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool_Impl::maximumReheatAirTemperature() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::MaximumReheatAirTemperature, true);
}

std::string HVACTemplateZoneVAVHeatAndCool_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneVAVHeatAndCool_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity, true);
}

std::string HVACTemplateZoneVAVHeatAndCool_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneVAVHeatAndCool_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneVAVHeatAndCool_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isSupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isConstantMinimumAirFlowFractionDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ConstantMinimumAirFlowFraction);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirMethod);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isReheatCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilType);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingType);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ConstantMinimumAirFlowFraction, constantMinimumAirFlowFraction);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setReheatCoilType(const std::string& reheatCoilType) {
  return setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilType, reheatCoilType);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneVAVHeatAndCool_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::autosizeSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetConstantMinimumAirFlowFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ConstantMinimumAirFlowFraction, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirMethod, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetReheatCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilType, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetMaximumReheatAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::MaximumReheatAirTemperature, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingType, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity, "autosize"));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneVAVHeatAndCool_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVHeatAndCool::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool_Impl::reheatCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVHeatAndCool::reheatCoilTypeValues();
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVHeatAndCool::baseboardHeatingTypeValues();
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVHeatAndCool::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneVAVHeatAndCool_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneVAVHeatAndCool::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
