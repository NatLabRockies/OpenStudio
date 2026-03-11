/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneDualDuct.hpp"
#include "HVACTemplateZoneDualDuct_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_DualDuct_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneDualDuct::HVACTemplateZoneDualDuct(const Model& model) : ModelObject(HVACTemplateZoneDualDuct::iddObjectType(), model) {}

HVACTemplateZoneDualDuct::HVACTemplateZoneDualDuct(std::shared_ptr<detail::HVACTemplateZoneDualDuct_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneDualDuct::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_DualDuct;
}

std::vector<std::string> HVACTemplateZoneDualDuct::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneDualDuct::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingType);
}

std::vector<std::string> HVACTemplateZoneDualDuct::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneDualDuct::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

boost::optional<double> HVACTemplateZoneDualDuct::supplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->supplyAirMaximumFlowRate();
}

boost::optional<double> HVACTemplateZoneDualDuct::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneDualDuct::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneCoolingSizingFactor();
}

double HVACTemplateZoneDualDuct::zoneMinimumAirFlowFraction() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneMinimumAirFlowFraction();
}

std::string HVACTemplateZoneDualDuct::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->outdoorAirMethod();
}

double HVACTemplateZoneDualDuct::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->outdoorAirFlowRateperPerson();
}

double HVACTemplateZoneDualDuct::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneDualDuct::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->outdoorAirFlowRateperZone();
}

std::string HVACTemplateZoneDualDuct::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->baseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneDualDuct::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->baseboardHeatingCapacity();
}

std::string HVACTemplateZoneDualDuct::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneDualDuct::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZoneDualDuct::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneDualDuct::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneDualDuct::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZoneDualDuct::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneDualDuct::isSupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneDualDuct::isSupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isSupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneDualDuct::isZoneMinimumAirFlowFractionDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneMinimumAirFlowFractionDefaulted();
}

bool HVACTemplateZoneDualDuct::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneDualDuct::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneDualDuct::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneDualDuct::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneDualDuct::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneDualDuct::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneDualDuct::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneDualDuct::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneDualDuct::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneDualDuct::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneDualDuct::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneDualDuct::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneDualDuct::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneDualDuct::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
}

bool HVACTemplateZoneDualDuct::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

bool HVACTemplateZoneDualDuct::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

bool HVACTemplateZoneDualDuct::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
}

bool HVACTemplateZoneDualDuct::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

bool HVACTemplateZoneDualDuct::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneDualDuct::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneDualDuct::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

bool HVACTemplateZoneDualDuct::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

bool HVACTemplateZoneDualDuct::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

bool HVACTemplateZoneDualDuct::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneDualDuct::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneDualDuct::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneDualDuct::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneDualDuct::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneDualDuct::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneDualDuct::resetSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneDualDuct::autosizeSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->autosizeSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneDualDuct::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneHeatingSizingFactor();
}

void HVACTemplateZoneDualDuct::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneCoolingSizingFactor();
}

void HVACTemplateZoneDualDuct::resetZoneMinimumAirFlowFraction() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneMinimumAirFlowFraction();
}

void HVACTemplateZoneDualDuct::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetOutdoorAirMethod();
}

void HVACTemplateZoneDualDuct::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetOutdoorAirFlowRateperPerson();
}

void HVACTemplateZoneDualDuct::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

void HVACTemplateZoneDualDuct::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetOutdoorAirFlowRateperZone();
}

void HVACTemplateZoneDualDuct::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetBaseboardHeatingType();
}

void HVACTemplateZoneDualDuct::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneDualDuct::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->autosizeBaseboardHeatingCapacity();
}

void HVACTemplateZoneDualDuct::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneDualDuct::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

void HVACTemplateZoneDualDuct::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

void HVACTemplateZoneDualDuct::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneDualDuct::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

void HVACTemplateZoneDualDuct::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneDualDuct_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneDualDuct_Impl::supplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::SupplyAirMaximumFlowRate, true);
}

boost::optional<double> HVACTemplateZoneDualDuct_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneDualDuct_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingSizingFactor, true);
}

double HVACTemplateZoneDualDuct_Impl::zoneMinimumAirFlowFraction() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneMinimumAirFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneDualDuct_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneDualDuct_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneDualDuct_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingCapacity, true);
}

std::string HVACTemplateZoneDualDuct_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneDualDuct_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneDualDuct_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneDualDuct_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::SupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneDualDuct_Impl::isSupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_DualDuctFields::SupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneDualDuct_Impl::isZoneMinimumAirFlowFractionDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneMinimumAirFlowFraction);
}

bool HVACTemplateZoneDualDuct_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirMethod);
}

bool HVACTemplateZoneDualDuct_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneDualDuct_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneDualDuct_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneDualDuct_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingType);
}

bool HVACTemplateZoneDualDuct_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneDualDuct_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneDualDuct_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneDualDuct_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneDualDuct_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneDualDuct_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneDualDuct_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneDualDuct_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneDualDuct_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZoneDualDuct_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZoneDualDuct_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
}

bool HVACTemplateZoneDualDuct_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZoneDualDuct_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZoneDualDuct_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneDualDuct_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperature,
                                zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneDualDuct_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperature,
                                zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneDualDuct_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneDualDuct_Impl::resetSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::SupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneDualDuct_Impl::autosizeSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::SupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneMinimumAirFlowFraction() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneMinimumAirFlowFraction, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirMethod, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingType, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneDualDuct_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::BaseboardHeatingCapacity, "autosize"));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneDualDuct_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_DualDuctFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

std::vector<std::string> HVACTemplateZoneDualDuct_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneDualDuct::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZoneDualDuct_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneDualDuct::baseboardHeatingTypeValues();
}

std::vector<std::string> HVACTemplateZoneDualDuct_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneDualDuct::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneDualDuct_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneDualDuct::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
