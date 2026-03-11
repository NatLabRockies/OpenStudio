/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneConstantVolume.hpp"
#include "HVACTemplateZoneConstantVolume_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZoneConstantVolume::HVACTemplateZoneConstantVolume(const Model& model)
  : ModelObject(HVACTemplateZoneConstantVolume::iddObjectType(), model) {}

HVACTemplateZoneConstantVolume::HVACTemplateZoneConstantVolume(std::shared_ptr<detail::HVACTemplateZoneConstantVolume_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZoneConstantVolume::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_ConstantVolume;
}

std::vector<std::string> HVACTemplateZoneConstantVolume::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZoneConstantVolume::reheatCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_ConstantVolumeFields::ReheatCoilType);
}

std::vector<std::string> HVACTemplateZoneConstantVolume::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingType);
}

std::vector<std::string> HVACTemplateZoneConstantVolume::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZoneConstantVolume::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

boost::optional<double> HVACTemplateZoneConstantVolume::supplyAirMaximumFlowRate() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->supplyAirMaximumFlowRate();
}

boost::optional<double> HVACTemplateZoneConstantVolume::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZoneConstantVolume::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneCoolingSizingFactor();
}

std::string HVACTemplateZoneConstantVolume::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->outdoorAirMethod();
}

double HVACTemplateZoneConstantVolume::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->outdoorAirFlowRateperPerson();
}

double HVACTemplateZoneConstantVolume::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZoneConstantVolume::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->outdoorAirFlowRateperZone();
}

std::string HVACTemplateZoneConstantVolume::reheatCoilType() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->reheatCoilType();
}

boost::optional<double> HVACTemplateZoneConstantVolume::maximumReheatAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->maximumReheatAirTemperature();
}

std::string HVACTemplateZoneConstantVolume::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->baseboardHeatingType();
}

boost::optional<double> HVACTemplateZoneConstantVolume::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->baseboardHeatingCapacity();
}

std::string HVACTemplateZoneConstantVolume::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneConstantVolume::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZoneConstantVolume::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZoneConstantVolume::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZoneConstantVolume::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZoneConstantVolume::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZoneConstantVolume::isSupplyAirMaximumFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
}

bool HVACTemplateZoneConstantVolume::isSupplyAirMaximumFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isSupplyAirMaximumFlowRateAutosized();
}

bool HVACTemplateZoneConstantVolume::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZoneConstantVolume::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZoneConstantVolume::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZoneConstantVolume::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZoneConstantVolume::isReheatCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isReheatCoilTypeDefaulted();
}

bool HVACTemplateZoneConstantVolume::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZoneConstantVolume::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZoneConstantVolume::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZoneConstantVolume::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneConstantVolume::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneConstantVolume::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneConstantVolume::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZoneConstantVolume::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZoneConstantVolume::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZoneConstantVolume::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
}

bool HVACTemplateZoneConstantVolume::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

bool HVACTemplateZoneConstantVolume::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

bool HVACTemplateZoneConstantVolume::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

bool HVACTemplateZoneConstantVolume::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneConstantVolume::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneConstantVolume::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

bool HVACTemplateZoneConstantVolume::setReheatCoilType(const std::string& reheatCoilType) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setReheatCoilType(reheatCoilType);
}

bool HVACTemplateZoneConstantVolume::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
}

bool HVACTemplateZoneConstantVolume::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

bool HVACTemplateZoneConstantVolume::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

bool HVACTemplateZoneConstantVolume::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneConstantVolume::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneConstantVolume::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneConstantVolume::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneConstantVolume::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneConstantVolume::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZoneConstantVolume::resetSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneConstantVolume::autosizeSupplyAirMaximumFlowRate() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->autosizeSupplyAirMaximumFlowRate();
}

void HVACTemplateZoneConstantVolume::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneHeatingSizingFactor();
}

void HVACTemplateZoneConstantVolume::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneCoolingSizingFactor();
}

void HVACTemplateZoneConstantVolume::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetOutdoorAirMethod();
}

void HVACTemplateZoneConstantVolume::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetOutdoorAirFlowRateperPerson();
}

void HVACTemplateZoneConstantVolume::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

void HVACTemplateZoneConstantVolume::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetOutdoorAirFlowRateperZone();
}

void HVACTemplateZoneConstantVolume::resetReheatCoilType() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetReheatCoilType();
}

void HVACTemplateZoneConstantVolume::resetMaximumReheatAirTemperature() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetMaximumReheatAirTemperature();
}

void HVACTemplateZoneConstantVolume::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetBaseboardHeatingType();
}

void HVACTemplateZoneConstantVolume::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZoneConstantVolume::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->autosizeBaseboardHeatingCapacity();
}

void HVACTemplateZoneConstantVolume::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneConstantVolume::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

void HVACTemplateZoneConstantVolume::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

void HVACTemplateZoneConstantVolume::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

void HVACTemplateZoneConstantVolume::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

void HVACTemplateZoneConstantVolume::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZoneConstantVolume_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HVACTemplateZoneConstantVolume_Impl::supplyAirMaximumFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::SupplyAirMaximumFlowRate, true);
}

boost::optional<double> HVACTemplateZoneConstantVolume_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZoneConstantVolume_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingSizingFactor, true);
}

std::string HVACTemplateZoneConstantVolume_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneConstantVolume_Impl::reheatCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ReheatCoilType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneConstantVolume_Impl::maximumReheatAirTemperature() const {
  return getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::MaximumReheatAirTemperature, true);
}

std::string HVACTemplateZoneConstantVolume_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZoneConstantVolume_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingCapacity, true);
}

std::string HVACTemplateZoneConstantVolume_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZoneConstantVolume_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZoneConstantVolume_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZoneConstantVolume_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::SupplyAirMaximumFlowRate);
}

bool HVACTemplateZoneConstantVolume_Impl::isSupplyAirMaximumFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::SupplyAirMaximumFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneConstantVolume_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirMethod);
}

bool HVACTemplateZoneConstantVolume_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZoneConstantVolume_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZoneConstantVolume_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZoneConstantVolume_Impl::isReheatCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ReheatCoilType);
}

bool HVACTemplateZoneConstantVolume_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingType);
}

bool HVACTemplateZoneConstantVolume_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZoneConstantVolume_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZoneConstantVolume_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneConstantVolume_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneConstantVolume_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneConstantVolume_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneConstantVolume_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZoneConstantVolume_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZoneConstantVolume_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZoneConstantVolume_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZoneConstantVolume_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setReheatCoilType(const std::string& reheatCoilType) {
  return setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ReheatCoilType, reheatCoilType);
}

bool HVACTemplateZoneConstantVolume_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
}

bool HVACTemplateZoneConstantVolume_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZoneConstantVolume_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZoneConstantVolume_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

void HVACTemplateZoneConstantVolume_Impl::resetSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::SupplyAirMaximumFlowRate, ""));
}

void HVACTemplateZoneConstantVolume_Impl::autosizeSupplyAirMaximumFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::SupplyAirMaximumFlowRate, "autosize"));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirMethod, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetReheatCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ReheatCoilType, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetMaximumReheatAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::MaximumReheatAirTemperature, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingType, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZoneConstantVolume_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::BaseboardHeatingCapacity, "autosize"));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZoneConstantVolume_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_ConstantVolumeFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

std::vector<std::string> HVACTemplateZoneConstantVolume_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneConstantVolume::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZoneConstantVolume_Impl::reheatCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneConstantVolume::reheatCoilTypeValues();
}

std::vector<std::string> HVACTemplateZoneConstantVolume_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZoneConstantVolume::baseboardHeatingTypeValues();
}

std::vector<std::string> HVACTemplateZoneConstantVolume_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneConstantVolume::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZoneConstantVolume_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZoneConstantVolume::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
