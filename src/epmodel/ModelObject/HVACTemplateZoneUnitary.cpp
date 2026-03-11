/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneUnitary.hpp"
#include "HVACTemplateZoneUnitary_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_Unitary_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneUnitary::HVACTemplateZoneUnitary(const Model& model)
  : ModelObject(HVACTemplateZoneUnitary::iddObjectType(), model) {}

HVACTemplateZoneUnitary::HVACTemplateZoneUnitary(std::shared_ptr<detail::HVACTemplateZoneUnitary_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneUnitary::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_Unitary;
}

std::vector<std::string> HVACTemplateZoneUnitary::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneUnitary::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType);
}

std::vector<std::string> HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

boost::optional<double> HVACTemplateZoneUnitary::supplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->supplyAirMaximumFlowRate();
}

boost::optional<double> HVACTemplateZoneUnitary::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneUnitary::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingSizingFactor();
}

std::string HVACTemplateZoneUnitary::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirMethod();
}

double HVACTemplateZoneUnitary::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirFlowRateperPerson();
}

double HVACTemplateZoneUnitary::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneUnitary::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirFlowRateperZone();
}

std::string HVACTemplateZoneUnitary::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->baseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneUnitary::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->baseboardHeatingCapacity();
}

std::string HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneUnitary::isSupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneUnitary::isSupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isSupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneUnitary::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneUnitary::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneUnitary::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneUnitary::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneUnitary::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneUnitary::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneUnitary::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneUnitary::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneUnitary::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneUnitary::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneUnitary::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneUnitary::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneUnitary::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneUnitary::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
}

bool HVACTemplateZoneUnitary::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

bool HVACTemplateZoneUnitary::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

bool HVACTemplateZoneUnitary::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

bool HVACTemplateZoneUnitary::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneUnitary::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneUnitary::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

bool HVACTemplateZoneUnitary::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

bool HVACTemplateZoneUnitary::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

bool HVACTemplateZoneUnitary::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneUnitary::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneUnitary::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneUnitary::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneUnitary::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneUnitary::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneUnitary::resetSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneUnitary::autosizeSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->autosizeSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneUnitary::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingSizingFactor();
}

void HVACTemplateZoneUnitary::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingSizingFactor();
}

void HVACTemplateZoneUnitary::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirMethod();
}

void HVACTemplateZoneUnitary::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirFlowRateperPerson();
}

void HVACTemplateZoneUnitary::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

void HVACTemplateZoneUnitary::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirFlowRateperZone();
}

void HVACTemplateZoneUnitary::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetBaseboardHeatingType();
}

void HVACTemplateZoneUnitary::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneUnitary::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->autosizeBaseboardHeatingCapacity();
}

void HVACTemplateZoneUnitary::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneUnitary::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

void HVACTemplateZoneUnitary::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

void HVACTemplateZoneUnitary::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneUnitary::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

void HVACTemplateZoneUnitary::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneUnitary_Impl::supplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, true);
}

boost::optional<double> HVACTemplateZoneUnitary_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneUnitary_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingSizingFactor, true);
}

std::string HVACTemplateZoneUnitary_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneUnitary_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneUnitary_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, true);
}

std::string HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneUnitary_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneUnitary_Impl::isSupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneUnitary_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod);
}

bool HVACTemplateZoneUnitary_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneUnitary_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneUnitary_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneUnitary_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType);
}

bool HVACTemplateZoneUnitary_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneUnitary_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneUnitary_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneUnitary_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneUnitary_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneUnitary_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneUnitary_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneUnitary_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneUnitary_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZoneUnitary_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZoneUnitary_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZoneUnitary_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZoneUnitary_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneUnitary_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneUnitary_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneUnitary_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneUnitary_Impl::resetSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneUnitary_Impl::autosizeSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneUnitary_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZoneUnitary_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZoneUnitary_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod, ""));
}

void HVACTemplateZoneUnitary_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZoneUnitary_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZoneUnitary_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZoneUnitary_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType, ""));
}

void HVACTemplateZoneUnitary_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneUnitary_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, "autosize"));
}

void HVACTemplateZoneUnitary_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneUnitary_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneUnitary_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneUnitary_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneUnitary_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneUnitary_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

std::vector<std::string> HVACTemplateZoneUnitary_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneUnitary::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZoneUnitary_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneUnitary::baseboardHeatingTypeValues();
}

std::vector<std::string> HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
