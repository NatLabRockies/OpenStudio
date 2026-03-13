/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneVAV.hpp"
#include "HVACTemplateZoneVAV_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_VAV_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateZoneVAV::HVACTemplateZoneVAV(const Model& model) : ModelObject(HVACTemplateZoneVAV::iddObjectType(), model) {}

  HVACTemplateZoneVAV::HVACTemplateZoneVAV(std::shared_ptr<detail::HVACTemplateZoneVAV_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateZoneVAV::iddObjectType() {
    return IddObjectType::HVACTemplate_Zone_VAV;
  }

  std::vector<std::string> HVACTemplateZoneVAV::zoneMinimumAirFlowInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_VAVFields::ZoneMinimumAirFlowInputMethod);
  }

  std::vector<std::string> HVACTemplateZoneVAV::outdoorAirMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirMethod);
  }

  std::vector<std::string> HVACTemplateZoneVAV::reheatCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VAVFields::ReheatCoilType);
  }

  std::vector<std::string> HVACTemplateZoneVAV::damperHeatingActionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VAVFields::DamperHeatingAction);
  }

  std::vector<std::string> HVACTemplateZoneVAV::baseboardHeatingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingType);
  }

  std::vector<std::string> HVACTemplateZoneVAV::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> HVACTemplateZoneVAV::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  boost::optional<double> HVACTemplateZoneVAV::supplyAirMaximumFlowRate() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->supplyAirMaximumFlowRate();
  }

  bool HVACTemplateZoneVAV::isSupplyAirMaximumFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
  }

  bool HVACTemplateZoneVAV::isSupplyAirMaximumFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isSupplyAirMaximumFlowRateAutosized();
  }

  bool HVACTemplateZoneVAV::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
  }

  void HVACTemplateZoneVAV::resetSupplyAirMaximumFlowRate() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetSupplyAirMaximumFlowRate();
  }

  void HVACTemplateZoneVAV::autosizeSupplyAirMaximumFlowRate() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->autosizeSupplyAirMaximumFlowRate();
  }

  boost::optional<double> HVACTemplateZoneVAV::zoneHeatingSizingFactor() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneHeatingSizingFactor();
  }

  bool HVACTemplateZoneVAV::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
  }

  void HVACTemplateZoneVAV::resetZoneHeatingSizingFactor() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneHeatingSizingFactor();
  }

  boost::optional<double> HVACTemplateZoneVAV::zoneCoolingSizingFactor() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneCoolingSizingFactor();
  }

  bool HVACTemplateZoneVAV::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
  }

  void HVACTemplateZoneVAV::resetZoneCoolingSizingFactor() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneCoolingSizingFactor();
  }

  std::string HVACTemplateZoneVAV::zoneMinimumAirFlowInputMethod() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneMinimumAirFlowInputMethod();
  }

  bool HVACTemplateZoneVAV::isZoneMinimumAirFlowInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneMinimumAirFlowInputMethodDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneMinimumAirFlowInputMethod(zoneMinimumAirFlowInputMethod);
  }

  void HVACTemplateZoneVAV::resetZoneMinimumAirFlowInputMethod() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneMinimumAirFlowInputMethod();
  }

  double HVACTemplateZoneVAV::constantMinimumAirFlowFraction() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->constantMinimumAirFlowFraction();
  }

  bool HVACTemplateZoneVAV::isConstantMinimumAirFlowFractionDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isConstantMinimumAirFlowFractionDefaulted();
  }

  bool HVACTemplateZoneVAV::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setConstantMinimumAirFlowFraction(constantMinimumAirFlowFraction);
  }

  void HVACTemplateZoneVAV::resetConstantMinimumAirFlowFraction() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetConstantMinimumAirFlowFraction();
  }

  boost::optional<double> HVACTemplateZoneVAV::fixedMinimumAirFlowRate() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->fixedMinimumAirFlowRate();
  }

  bool HVACTemplateZoneVAV::isFixedMinimumAirFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isFixedMinimumAirFlowRateDefaulted();
  }

  bool HVACTemplateZoneVAV::setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setFixedMinimumAirFlowRate(fixedMinimumAirFlowRate);
  }

  void HVACTemplateZoneVAV::resetFixedMinimumAirFlowRate() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetFixedMinimumAirFlowRate();
  }

  std::string HVACTemplateZoneVAV::outdoorAirMethod() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->outdoorAirMethod();
  }

  bool HVACTemplateZoneVAV::isOutdoorAirMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isOutdoorAirMethodDefaulted();
  }

  bool HVACTemplateZoneVAV::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
  }

  void HVACTemplateZoneVAV::resetOutdoorAirMethod() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetOutdoorAirMethod();
  }

  double HVACTemplateZoneVAV::outdoorAirFlowRateperPerson() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->outdoorAirFlowRateperPerson();
  }

  bool HVACTemplateZoneVAV::isOutdoorAirFlowRateperPersonDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
  }

  bool HVACTemplateZoneVAV::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
  }

  void HVACTemplateZoneVAV::resetOutdoorAirFlowRateperPerson() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetOutdoorAirFlowRateperPerson();
  }

  double HVACTemplateZoneVAV::outdoorAirFlowRateperZoneFloorArea() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->outdoorAirFlowRateperZoneFloorArea();
  }

  bool HVACTemplateZoneVAV::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
  }

  bool HVACTemplateZoneVAV::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
  }

  void HVACTemplateZoneVAV::resetOutdoorAirFlowRateperZoneFloorArea() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
  }

  double HVACTemplateZoneVAV::outdoorAirFlowRateperZone() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->outdoorAirFlowRateperZone();
  }

  bool HVACTemplateZoneVAV::isOutdoorAirFlowRateperZoneDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
  }

  bool HVACTemplateZoneVAV::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
  }

  void HVACTemplateZoneVAV::resetOutdoorAirFlowRateperZone() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetOutdoorAirFlowRateperZone();
  }

  std::string HVACTemplateZoneVAV::reheatCoilType() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->reheatCoilType();
  }

  bool HVACTemplateZoneVAV::isReheatCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isReheatCoilTypeDefaulted();
  }

  bool HVACTemplateZoneVAV::setReheatCoilType(const std::string& reheatCoilType) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setReheatCoilType(reheatCoilType);
  }

  void HVACTemplateZoneVAV::resetReheatCoilType() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetReheatCoilType();
  }

  std::string HVACTemplateZoneVAV::damperHeatingAction() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->damperHeatingAction();
  }

  bool HVACTemplateZoneVAV::isDamperHeatingActionDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isDamperHeatingActionDefaulted();
  }

  bool HVACTemplateZoneVAV::setDamperHeatingAction(const std::string& damperHeatingAction) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setDamperHeatingAction(damperHeatingAction);
  }

  void HVACTemplateZoneVAV::resetDamperHeatingAction() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetDamperHeatingAction();
  }

  boost::optional<double> HVACTemplateZoneVAV::maximumFlowperZoneFloorAreaDuringReheat() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->maximumFlowperZoneFloorAreaDuringReheat();
  }

  bool HVACTemplateZoneVAV::isMaximumFlowperZoneFloorAreaDuringReheatDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isMaximumFlowperZoneFloorAreaDuringReheatDefaulted();
  }

  bool HVACTemplateZoneVAV::isMaximumFlowperZoneFloorAreaDuringReheatAutocalculated() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isMaximumFlowperZoneFloorAreaDuringReheatAutocalculated();
  }

  bool HVACTemplateZoneVAV::setMaximumFlowperZoneFloorAreaDuringReheat(double maximumFlowperZoneFloorAreaDuringReheat) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setMaximumFlowperZoneFloorAreaDuringReheat(maximumFlowperZoneFloorAreaDuringReheat);
  }

  void HVACTemplateZoneVAV::resetMaximumFlowperZoneFloorAreaDuringReheat() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetMaximumFlowperZoneFloorAreaDuringReheat();
  }

  void HVACTemplateZoneVAV::autocalculateMaximumFlowperZoneFloorAreaDuringReheat() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->autocalculateMaximumFlowperZoneFloorAreaDuringReheat();
  }

  boost::optional<double> HVACTemplateZoneVAV::maximumFlowFractionDuringReheat() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->maximumFlowFractionDuringReheat();
  }

  bool HVACTemplateZoneVAV::isMaximumFlowFractionDuringReheatDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isMaximumFlowFractionDuringReheatDefaulted();
  }

  bool HVACTemplateZoneVAV::isMaximumFlowFractionDuringReheatAutocalculated() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isMaximumFlowFractionDuringReheatAutocalculated();
  }

  bool HVACTemplateZoneVAV::setMaximumFlowFractionDuringReheat(double maximumFlowFractionDuringReheat) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setMaximumFlowFractionDuringReheat(maximumFlowFractionDuringReheat);
  }

  void HVACTemplateZoneVAV::resetMaximumFlowFractionDuringReheat() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetMaximumFlowFractionDuringReheat();
  }

  void HVACTemplateZoneVAV::autocalculateMaximumFlowFractionDuringReheat() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->autocalculateMaximumFlowFractionDuringReheat();
  }

  boost::optional<double> HVACTemplateZoneVAV::maximumReheatAirTemperature() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->maximumReheatAirTemperature();
  }

  bool HVACTemplateZoneVAV::isMaximumReheatAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isMaximumReheatAirTemperatureDefaulted();
  }

  bool HVACTemplateZoneVAV::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
  }

  void HVACTemplateZoneVAV::resetMaximumReheatAirTemperature() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetMaximumReheatAirTemperature();
  }

  std::string HVACTemplateZoneVAV::baseboardHeatingType() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->baseboardHeatingType();
  }

  bool HVACTemplateZoneVAV::isBaseboardHeatingTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isBaseboardHeatingTypeDefaulted();
  }

  bool HVACTemplateZoneVAV::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
  }

  void HVACTemplateZoneVAV::resetBaseboardHeatingType() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetBaseboardHeatingType();
  }

  boost::optional<double> HVACTemplateZoneVAV::baseboardHeatingCapacity() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->baseboardHeatingCapacity();
  }

  bool HVACTemplateZoneVAV::isBaseboardHeatingCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isBaseboardHeatingCapacityDefaulted();
  }

  bool HVACTemplateZoneVAV::isBaseboardHeatingCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isBaseboardHeatingCapacityAutosized();
  }

  bool HVACTemplateZoneVAV::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
  }

  void HVACTemplateZoneVAV::resetBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetBaseboardHeatingCapacity();
  }

  void HVACTemplateZoneVAV::autosizeBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->autosizeBaseboardHeatingCapacity();
  }

  std::string HVACTemplateZoneVAV::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  bool HVACTemplateZoneVAV::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
      zoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  void HVACTemplateZoneVAV::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  double HVACTemplateZoneVAV::zoneCoolingDesignSupplyAirTemperature() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneCoolingDesignSupplyAirTemperature();
  }

  bool HVACTemplateZoneVAV::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
  }

  void HVACTemplateZoneVAV::resetZoneCoolingDesignSupplyAirTemperature() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
  }

  double HVACTemplateZoneVAV::zoneCoolingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
  }

  bool HVACTemplateZoneVAV::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
      zoneCoolingDesignSupplyAirTemperatureDifference);
  }

  void HVACTemplateZoneVAV::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
  }

  std::string HVACTemplateZoneVAV::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  bool HVACTemplateZoneVAV::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
      zoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  void HVACTemplateZoneVAV::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  double HVACTemplateZoneVAV::zoneHeatingDesignSupplyAirTemperature() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneHeatingDesignSupplyAirTemperature();
  }

  bool HVACTemplateZoneVAV::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
  }

  void HVACTemplateZoneVAV::resetZoneHeatingDesignSupplyAirTemperature() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
  }

  double HVACTemplateZoneVAV::zoneHeatingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
  }

  bool HVACTemplateZoneVAV::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
  }

  bool HVACTemplateZoneVAV::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
    return getImpl<detail::HVACTemplateZoneVAV_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
      zoneHeatingDesignSupplyAirTemperatureDifference);
  }

  void HVACTemplateZoneVAV::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
    getImpl<detail::HVACTemplateZoneVAV_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HVACTemplateZoneVAV_Impl::supplyAirMaximumFlowRate() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate, true);
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::zoneHeatingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingSizingFactor, true);
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::zoneCoolingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingSizingFactor, true);
    }

    std::string HVACTemplateZoneVAV_Impl::zoneMinimumAirFlowInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::ZoneMinimumAirFlowInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::constantMinimumAirFlowFraction() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::ConstantMinimumAirFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::fixedMinimumAirFlowRate() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::FixedMinimumAirFlowRate, true);
    }

    std::string HVACTemplateZoneVAV_Impl::outdoorAirMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::outdoorAirFlowRateperPerson() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperPerson, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::outdoorAirFlowRateperZoneFloorArea() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZoneFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::outdoorAirFlowRateperZone() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZone, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplateZoneVAV_Impl::reheatCoilType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::ReheatCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplateZoneVAV_Impl::damperHeatingAction() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::DamperHeatingAction, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::maximumFlowperZoneFloorAreaDuringReheat() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat, true);
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::maximumFlowFractionDuringReheat() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat, true);
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::maximumReheatAirTemperature() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::MaximumReheatAirTemperature, true);
    }

    std::string HVACTemplateZoneVAV_Impl::baseboardHeatingType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingType, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> HVACTemplateZoneVAV_Impl::baseboardHeatingCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity, true);
    }

    std::string HVACTemplateZoneVAV_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::zoneCoolingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplateZoneVAV_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::zoneHeatingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplateZoneVAV_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneVAV_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate);
    }

    bool HVACTemplateZoneVAV_Impl::isSupplyAirMaximumFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZoneVAV_Impl::isZoneMinimumAirFlowInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneMinimumAirFlowInputMethod);
    }

    bool HVACTemplateZoneVAV_Impl::isConstantMinimumAirFlowFractionDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ConstantMinimumAirFlowFraction);
    }

    bool HVACTemplateZoneVAV_Impl::isFixedMinimumAirFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::FixedMinimumAirFlowRate);
    }

    bool HVACTemplateZoneVAV_Impl::isOutdoorAirMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirMethod);
    }

    bool HVACTemplateZoneVAV_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperPerson);
    }

    bool HVACTemplateZoneVAV_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZoneFloorArea);
    }

    bool HVACTemplateZoneVAV_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZone);
    }

    bool HVACTemplateZoneVAV_Impl::isReheatCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ReheatCoilType);
    }

    bool HVACTemplateZoneVAV_Impl::isDamperHeatingActionDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::DamperHeatingAction);
    }

    bool HVACTemplateZoneVAV_Impl::isMaximumFlowperZoneFloorAreaDuringReheatDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat);
    }

    bool HVACTemplateZoneVAV_Impl::isMaximumFlowperZoneFloorAreaDuringReheatAutocalculated() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool HVACTemplateZoneVAV_Impl::isMaximumFlowFractionDuringReheatDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat);
    }

    bool HVACTemplateZoneVAV_Impl::isMaximumFlowFractionDuringReheatAutocalculated() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool HVACTemplateZoneVAV_Impl::isMaximumReheatAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::MaximumReheatAirTemperature);
    }

    bool HVACTemplateZoneVAV_Impl::isBaseboardHeatingTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingType);
    }

    bool HVACTemplateZoneVAV_Impl::isBaseboardHeatingCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity);
    }

    bool HVACTemplateZoneVAV_Impl::isBaseboardHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZoneVAV_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZoneVAV_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperature);
    }

    bool HVACTemplateZoneVAV_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
    }

    bool HVACTemplateZoneVAV_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZoneVAV_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperature);
    }

    bool HVACTemplateZoneVAV_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
    }

    bool HVACTemplateZoneVAV_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
    }

    bool HVACTemplateZoneVAV_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
    }

    bool HVACTemplateZoneVAV_Impl::setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneMinimumAirFlowInputMethod, zoneMinimumAirFlowInputMethod);
    }

    bool HVACTemplateZoneVAV_Impl::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
      return setDouble(openstudio::HVACTemplate_Zone_VAVFields::ConstantMinimumAirFlowFraction, constantMinimumAirFlowFraction);
    }

    bool HVACTemplateZoneVAV_Impl::setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::FixedMinimumAirFlowRate, fixedMinimumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirMethod, outdoorAirMethod);
    }

    bool HVACTemplateZoneVAV_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setReheatCoilType(const std::string& reheatCoilType) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::ReheatCoilType, reheatCoilType);
    }

    bool HVACTemplateZoneVAV_Impl::setDamperHeatingAction(const std::string& damperHeatingAction) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::DamperHeatingAction, damperHeatingAction);
    }

    bool HVACTemplateZoneVAV_Impl::setMaximumFlowperZoneFloorAreaDuringReheat(double maximumFlowperZoneFloorAreaDuringReheat) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat, maximumFlowperZoneFloorAreaDuringReheat);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setMaximumFlowFractionDuringReheat(double maximumFlowFractionDuringReheat) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat, maximumFlowFractionDuringReheat);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
      return setDouble(openstudio::HVACTemplate_Zone_VAVFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
    }

    bool HVACTemplateZoneVAV_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingType, baseboardHeatingType);
    }

    bool HVACTemplateZoneVAV_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
      const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                       zoneCoolingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZoneVAV_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                    zoneCoolingDesignSupplyAirTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
      const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                       zoneHeatingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZoneVAV_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplateZoneVAV_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                    zoneHeatingDesignSupplyAirTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneVAV_Impl::resetSupplyAirMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate, ""));
    }

    void HVACTemplateZoneVAV_Impl::autosizeSupplyAirMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate, "autosize"));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneHeatingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingSizingFactor, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneCoolingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingSizingFactor, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneMinimumAirFlowInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneMinimumAirFlowInputMethod, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetConstantMinimumAirFlowFraction() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ConstantMinimumAirFlowFraction, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetFixedMinimumAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::FixedMinimumAirFlowRate, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetOutdoorAirMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirMethod, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetOutdoorAirFlowRateperPerson() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperPerson, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZoneFloorArea, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetOutdoorAirFlowRateperZone() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZone, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetReheatCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ReheatCoilType, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetDamperHeatingAction() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::DamperHeatingAction, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetMaximumFlowperZoneFloorAreaDuringReheat() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat, ""));
    }

    void HVACTemplateZoneVAV_Impl::autocalculateMaximumFlowperZoneFloorAreaDuringReheat() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat, "autocalculate"));
    }

    void HVACTemplateZoneVAV_Impl::resetMaximumFlowFractionDuringReheat() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat, ""));
    }

    void HVACTemplateZoneVAV_Impl::autocalculateMaximumFlowFractionDuringReheat() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat, "autocalculate"));
    }

    void HVACTemplateZoneVAV_Impl::resetMaximumReheatAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::MaximumReheatAirTemperature, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetBaseboardHeatingType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingType, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity, ""));
    }

    void HVACTemplateZoneVAV_Impl::autosizeBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity, "autosize"));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperature, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperature, ""));
    }

    void HVACTemplateZoneVAV_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::zoneMinimumAirFlowInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::zoneMinimumAirFlowInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::outdoorAirMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::outdoorAirMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::reheatCoilTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::reheatCoilTypeValues();
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::damperHeatingActionValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::damperHeatingActionValues();
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::baseboardHeatingTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::baseboardHeatingTypeValues();
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneVAV_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVAV::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
