/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZonePTHP.hpp"
#include "HVACTemplateZonePTHP_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_PTHP_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateZonePTHP::HVACTemplateZonePTHP(const Model& model) : ModelObject(HVACTemplateZonePTHP::iddObjectType(), model) {}

  HVACTemplateZonePTHP::HVACTemplateZonePTHP(std::shared_ptr<detail::HVACTemplateZonePTHP_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateZonePTHP::iddObjectType() {
    return IddObjectType::HVACTemplate_Zone_PTHP;
  }

  std::vector<std::string> HVACTemplateZonePTHP::outdoorAirMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirMethod);
  }

  std::vector<std::string> HVACTemplateZonePTHP::supplyFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanPlacement);
  }

  std::vector<std::string> HVACTemplateZonePTHP::coolingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilType);
  }

  std::vector<std::string> HVACTemplateZonePTHP::heatPumpHeatingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilType);
  }

  std::vector<std::string> HVACTemplateZonePTHP::heatPumpDefrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostStrategy);
  }

  std::vector<std::string> HVACTemplateZonePTHP::heatPumpDefrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostControl);
  }

  std::vector<std::string> HVACTemplateZonePTHP::supplementalHeatingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilType);
  }

  std::vector<std::string> HVACTemplateZonePTHP::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> HVACTemplateZonePTHP::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> HVACTemplateZonePTHP::baseboardHeatingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingType);
  }

  std::vector<std::string> HVACTemplateZonePTHP::capacityControlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTHPFields::CapacityControlMethod);
  }

  boost::optional<double> HVACTemplateZonePTHP::coolingSupplyAirFlowRate() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->coolingSupplyAirFlowRate();
  }

  bool HVACTemplateZonePTHP::isCoolingSupplyAirFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingSupplyAirFlowRateDefaulted();
  }

  bool HVACTemplateZonePTHP::isCoolingSupplyAirFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingSupplyAirFlowRateAutosized();
  }

  bool HVACTemplateZonePTHP::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
  }

  void HVACTemplateZonePTHP::resetCoolingSupplyAirFlowRate() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetCoolingSupplyAirFlowRate();
  }

  void HVACTemplateZonePTHP::autosizeCoolingSupplyAirFlowRate() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeCoolingSupplyAirFlowRate();
  }

  boost::optional<double> HVACTemplateZonePTHP::heatingSupplyAirFlowRate() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatingSupplyAirFlowRate();
  }

  bool HVACTemplateZonePTHP::isHeatingSupplyAirFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatingSupplyAirFlowRateDefaulted();
  }

  bool HVACTemplateZonePTHP::isHeatingSupplyAirFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatingSupplyAirFlowRateAutosized();
  }

  bool HVACTemplateZonePTHP::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
  }

  void HVACTemplateZonePTHP::resetHeatingSupplyAirFlowRate() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatingSupplyAirFlowRate();
  }

  void HVACTemplateZonePTHP::autosizeHeatingSupplyAirFlowRate() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeHeatingSupplyAirFlowRate();
  }

  boost::optional<double> HVACTemplateZonePTHP::noLoadSupplyAirFlowRate() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->noLoadSupplyAirFlowRate();
  }

  bool HVACTemplateZonePTHP::isNoLoadSupplyAirFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isNoLoadSupplyAirFlowRateDefaulted();
  }

  bool HVACTemplateZonePTHP::isNoLoadSupplyAirFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
  }

  bool HVACTemplateZonePTHP::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
  }

  void HVACTemplateZonePTHP::resetNoLoadSupplyAirFlowRate() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetNoLoadSupplyAirFlowRate();
  }

  void HVACTemplateZonePTHP::autosizeNoLoadSupplyAirFlowRate() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeNoLoadSupplyAirFlowRate();
  }

  boost::optional<double> HVACTemplateZonePTHP::zoneHeatingSizingFactor() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneHeatingSizingFactor();
  }

  bool HVACTemplateZonePTHP::isZoneHeatingSizingFactorDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneHeatingSizingFactorDefaulted();
  }

  bool HVACTemplateZonePTHP::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
  }

  void HVACTemplateZonePTHP::resetZoneHeatingSizingFactor() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneHeatingSizingFactor();
  }

  boost::optional<double> HVACTemplateZonePTHP::zoneCoolingSizingFactor() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneCoolingSizingFactor();
  }

  bool HVACTemplateZonePTHP::isZoneCoolingSizingFactorDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneCoolingSizingFactorDefaulted();
  }

  bool HVACTemplateZonePTHP::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
  }

  void HVACTemplateZonePTHP::resetZoneCoolingSizingFactor() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneCoolingSizingFactor();
  }

  std::string HVACTemplateZonePTHP::outdoorAirMethod() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->outdoorAirMethod();
  }

  bool HVACTemplateZonePTHP::isOutdoorAirMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isOutdoorAirMethodDefaulted();
  }

  bool HVACTemplateZonePTHP::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
  }

  void HVACTemplateZonePTHP::resetOutdoorAirMethod() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetOutdoorAirMethod();
  }

  double HVACTemplateZonePTHP::outdoorAirFlowRateperPerson() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->outdoorAirFlowRateperPerson();
  }

  bool HVACTemplateZonePTHP::isOutdoorAirFlowRateperPersonDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
  }

  bool HVACTemplateZonePTHP::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
  }

  void HVACTemplateZonePTHP::resetOutdoorAirFlowRateperPerson() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetOutdoorAirFlowRateperPerson();
  }

  double HVACTemplateZonePTHP::outdoorAirFlowRateperZoneFloorArea() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->outdoorAirFlowRateperZoneFloorArea();
  }

  bool HVACTemplateZonePTHP::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
  }

  bool HVACTemplateZonePTHP::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
  }

  void HVACTemplateZonePTHP::resetOutdoorAirFlowRateperZoneFloorArea() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
  }

  double HVACTemplateZonePTHP::outdoorAirFlowRateperZone() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->outdoorAirFlowRateperZone();
  }

  bool HVACTemplateZonePTHP::isOutdoorAirFlowRateperZoneDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
  }

  bool HVACTemplateZonePTHP::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
  }

  void HVACTemplateZonePTHP::resetOutdoorAirFlowRateperZone() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetOutdoorAirFlowRateperZone();
  }

  std::string HVACTemplateZonePTHP::supplyFanPlacement() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplyFanPlacement();
  }

  bool HVACTemplateZonePTHP::isSupplyFanPlacementDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplyFanPlacementDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplyFanPlacement(supplyFanPlacement);
  }

  void HVACTemplateZonePTHP::resetSupplyFanPlacement() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplyFanPlacement();
  }

  double HVACTemplateZonePTHP::supplyFanTotalEfficiency() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplyFanTotalEfficiency();
  }

  bool HVACTemplateZonePTHP::isSupplyFanTotalEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplyFanTotalEfficiencyDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplyFanTotalEfficiency(supplyFanTotalEfficiency);
  }

  void HVACTemplateZonePTHP::resetSupplyFanTotalEfficiency() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplyFanTotalEfficiency();
  }

  double HVACTemplateZonePTHP::supplyFanDeltaPressure() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplyFanDeltaPressure();
  }

  bool HVACTemplateZonePTHP::isSupplyFanDeltaPressureDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplyFanDeltaPressureDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplyFanDeltaPressure(supplyFanDeltaPressure);
  }

  void HVACTemplateZonePTHP::resetSupplyFanDeltaPressure() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplyFanDeltaPressure();
  }

  double HVACTemplateZonePTHP::supplyFanMotorEfficiency() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplyFanMotorEfficiency();
  }

  bool HVACTemplateZonePTHP::isSupplyFanMotorEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplyFanMotorEfficiencyDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplyFanMotorEfficiency(supplyFanMotorEfficiency);
  }

  void HVACTemplateZonePTHP::resetSupplyFanMotorEfficiency() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplyFanMotorEfficiency();
  }

  std::string HVACTemplateZonePTHP::coolingCoilType() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->coolingCoilType();
  }

  bool HVACTemplateZonePTHP::isCoolingCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingCoilTypeDefaulted();
  }

  bool HVACTemplateZonePTHP::setCoolingCoilType(const std::string& coolingCoilType) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setCoolingCoilType(coolingCoilType);
  }

  void HVACTemplateZonePTHP::resetCoolingCoilType() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetCoolingCoilType();
  }

  boost::optional<double> HVACTemplateZonePTHP::coolingCoilGrossRatedTotalCapacity() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->coolingCoilGrossRatedTotalCapacity();
  }

  bool HVACTemplateZonePTHP::isCoolingCoilGrossRatedTotalCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingCoilGrossRatedTotalCapacityDefaulted();
  }

  bool HVACTemplateZonePTHP::isCoolingCoilGrossRatedTotalCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingCoilGrossRatedTotalCapacityAutosized();
  }

  bool HVACTemplateZonePTHP::setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setCoolingCoilGrossRatedTotalCapacity(coolingCoilGrossRatedTotalCapacity);
  }

  void HVACTemplateZonePTHP::resetCoolingCoilGrossRatedTotalCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetCoolingCoilGrossRatedTotalCapacity();
  }

  void HVACTemplateZonePTHP::autosizeCoolingCoilGrossRatedTotalCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeCoolingCoilGrossRatedTotalCapacity();
  }

  boost::optional<double> HVACTemplateZonePTHP::coolingCoilGrossRatedSensibleHeatRatio() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->coolingCoilGrossRatedSensibleHeatRatio();
  }

  bool HVACTemplateZonePTHP::isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingCoilGrossRatedSensibleHeatRatioDefaulted();
  }

  bool HVACTemplateZonePTHP::isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingCoilGrossRatedSensibleHeatRatioAutosized();
  }

  bool HVACTemplateZonePTHP::setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setCoolingCoilGrossRatedSensibleHeatRatio(coolingCoilGrossRatedSensibleHeatRatio);
  }

  void HVACTemplateZonePTHP::resetCoolingCoilGrossRatedSensibleHeatRatio() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetCoolingCoilGrossRatedSensibleHeatRatio();
  }

  void HVACTemplateZonePTHP::autosizeCoolingCoilGrossRatedSensibleHeatRatio() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeCoolingCoilGrossRatedSensibleHeatRatio();
  }

  double HVACTemplateZonePTHP::coolingCoilGrossRatedCOP() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->coolingCoilGrossRatedCOP();
  }

  bool HVACTemplateZonePTHP::isCoolingCoilGrossRatedCOPDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCoolingCoilGrossRatedCOPDefaulted();
  }

  bool HVACTemplateZonePTHP::setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setCoolingCoilGrossRatedCOP(coolingCoilGrossRatedCOP);
  }

  void HVACTemplateZonePTHP::resetCoolingCoilGrossRatedCOP() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetCoolingCoilGrossRatedCOP();
  }

  std::string HVACTemplateZonePTHP::heatPumpHeatingCoilType() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpHeatingCoilType();
  }

  bool HVACTemplateZonePTHP::isHeatPumpHeatingCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpHeatingCoilTypeDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpHeatingCoilType(heatPumpHeatingCoilType);
  }

  void HVACTemplateZonePTHP::resetHeatPumpHeatingCoilType() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpHeatingCoilType();
  }

  boost::optional<double> HVACTemplateZonePTHP::heatPumpHeatingCoilGrossRatedCapacity() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpHeatingCoilGrossRatedCapacity();
  }

  bool HVACTemplateZonePTHP::isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpHeatingCoilGrossRatedCapacityDefaulted();
  }

  bool HVACTemplateZonePTHP::isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpHeatingCoilGrossRatedCapacityAutosized();
  }

  bool HVACTemplateZonePTHP::setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpHeatingCoilGrossRatedCapacity(heatPumpHeatingCoilGrossRatedCapacity);
  }

  void HVACTemplateZonePTHP::resetHeatPumpHeatingCoilGrossRatedCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpHeatingCoilGrossRatedCapacity();
  }

  void HVACTemplateZonePTHP::autosizeHeatPumpHeatingCoilGrossRatedCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeHeatPumpHeatingCoilGrossRatedCapacity();
  }

  double HVACTemplateZonePTHP::heatPumpHeatingCoilGrossRatedCOP() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpHeatingCoilGrossRatedCOP();
  }

  bool HVACTemplateZonePTHP::isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpHeatingCoilGrossRatedCOPDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpHeatingCoilGrossRatedCOP(heatPumpHeatingCoilGrossRatedCOP);
  }

  void HVACTemplateZonePTHP::resetHeatPumpHeatingCoilGrossRatedCOP() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpHeatingCoilGrossRatedCOP();
  }

  double HVACTemplateZonePTHP::heatPumpHeatingMinimumOutdoorDryBulbTemperature() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpHeatingMinimumOutdoorDryBulbTemperature();
  }

  bool HVACTemplateZonePTHP::isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(
      heatPumpHeatingMinimumOutdoorDryBulbTemperature);
  }

  void HVACTemplateZonePTHP::resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature();
  }

  double HVACTemplateZonePTHP::heatPumpDefrostMaximumOutdoorDryBulbTemperature() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpDefrostMaximumOutdoorDryBulbTemperature();
  }

  bool HVACTemplateZonePTHP::isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(
      heatPumpDefrostMaximumOutdoorDryBulbTemperature);
  }

  void HVACTemplateZonePTHP::resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature();
  }

  std::string HVACTemplateZonePTHP::heatPumpDefrostStrategy() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpDefrostStrategy();
  }

  bool HVACTemplateZonePTHP::isHeatPumpDefrostStrategyDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpDefrostStrategyDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpDefrostStrategy(heatPumpDefrostStrategy);
  }

  void HVACTemplateZonePTHP::resetHeatPumpDefrostStrategy() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpDefrostStrategy();
  }

  std::string HVACTemplateZonePTHP::heatPumpDefrostControl() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpDefrostControl();
  }

  bool HVACTemplateZonePTHP::isHeatPumpDefrostControlDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpDefrostControlDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpDefrostControl(heatPumpDefrostControl);
  }

  void HVACTemplateZonePTHP::resetHeatPumpDefrostControl() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpDefrostControl();
  }

  double HVACTemplateZonePTHP::heatPumpDefrostTimePeriodFraction() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->heatPumpDefrostTimePeriodFraction();
  }

  bool HVACTemplateZonePTHP::isHeatPumpDefrostTimePeriodFractionDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isHeatPumpDefrostTimePeriodFractionDefaulted();
  }

  bool HVACTemplateZonePTHP::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setHeatPumpDefrostTimePeriodFraction(heatPumpDefrostTimePeriodFraction);
  }

  void HVACTemplateZonePTHP::resetHeatPumpDefrostTimePeriodFraction() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetHeatPumpDefrostTimePeriodFraction();
  }

  std::string HVACTemplateZonePTHP::supplementalHeatingCoilType() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplementalHeatingCoilType();
  }

  bool HVACTemplateZonePTHP::isSupplementalHeatingCoilTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplementalHeatingCoilTypeDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplementalHeatingCoilType(supplementalHeatingCoilType);
  }

  void HVACTemplateZonePTHP::resetSupplementalHeatingCoilType() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplementalHeatingCoilType();
  }

  boost::optional<double> HVACTemplateZonePTHP::supplementalHeatingCoilCapacity() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplementalHeatingCoilCapacity();
  }

  bool HVACTemplateZonePTHP::isSupplementalHeatingCoilCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplementalHeatingCoilCapacityDefaulted();
  }

  bool HVACTemplateZonePTHP::isSupplementalHeatingCoilCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplementalHeatingCoilCapacityAutosized();
  }

  bool HVACTemplateZonePTHP::setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplementalHeatingCoilCapacity(supplementalHeatingCoilCapacity);
  }

  void HVACTemplateZonePTHP::resetSupplementalHeatingCoilCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplementalHeatingCoilCapacity();
  }

  void HVACTemplateZonePTHP::autosizeSupplementalHeatingCoilCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeSupplementalHeatingCoilCapacity();
  }

  double HVACTemplateZonePTHP::supplementalHeatingCoilMaximumOutdoorDryBulbTemperature() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplementalHeatingCoilMaximumOutdoorDryBulbTemperature();
  }

  bool HVACTemplateZonePTHP::isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted();
  }

  bool
    HVACTemplateZonePTHP::setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature(double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature(
      supplementalHeatingCoilMaximumOutdoorDryBulbTemperature);
  }

  void HVACTemplateZonePTHP::resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature();
  }

  double HVACTemplateZonePTHP::supplementalGasHeatingCoilEfficiency() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplementalGasHeatingCoilEfficiency();
  }

  bool HVACTemplateZonePTHP::isSupplementalGasHeatingCoilEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplementalGasHeatingCoilEfficiencyDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplementalGasHeatingCoilEfficiency(double supplementalGasHeatingCoilEfficiency) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplementalGasHeatingCoilEfficiency(supplementalGasHeatingCoilEfficiency);
  }

  void HVACTemplateZonePTHP::resetSupplementalGasHeatingCoilEfficiency() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplementalGasHeatingCoilEfficiency();
  }

  double HVACTemplateZonePTHP::supplementalGasHeatingCoilParasiticElectricLoad() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->supplementalGasHeatingCoilParasiticElectricLoad();
  }

  bool HVACTemplateZonePTHP::isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted();
  }

  bool HVACTemplateZonePTHP::setSupplementalGasHeatingCoilParasiticElectricLoad(double supplementalGasHeatingCoilParasiticElectricLoad) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setSupplementalGasHeatingCoilParasiticElectricLoad(
      supplementalGasHeatingCoilParasiticElectricLoad);
  }

  void HVACTemplateZonePTHP::resetSupplementalGasHeatingCoilParasiticElectricLoad() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetSupplementalGasHeatingCoilParasiticElectricLoad();
  }

  std::string HVACTemplateZonePTHP::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  bool HVACTemplateZonePTHP::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
  }

  bool
    HVACTemplateZonePTHP::setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
      zoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  void HVACTemplateZonePTHP::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  double HVACTemplateZonePTHP::zoneCoolingDesignSupplyAirTemperature() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneCoolingDesignSupplyAirTemperature();
  }

  bool HVACTemplateZonePTHP::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
  }

  bool HVACTemplateZonePTHP::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
  }

  void HVACTemplateZonePTHP::resetZoneCoolingDesignSupplyAirTemperature() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
  }

  double HVACTemplateZonePTHP::zoneCoolingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
  }

  bool HVACTemplateZonePTHP::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
  }

  bool HVACTemplateZonePTHP::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
      zoneCoolingDesignSupplyAirTemperatureDifference);
  }

  void HVACTemplateZonePTHP::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
  }

  std::string HVACTemplateZonePTHP::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  bool HVACTemplateZonePTHP::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
  }

  bool
    HVACTemplateZonePTHP::setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
      zoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  void HVACTemplateZonePTHP::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  double HVACTemplateZonePTHP::zoneHeatingDesignSupplyAirTemperature() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneHeatingDesignSupplyAirTemperature();
  }

  bool HVACTemplateZonePTHP::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
  }

  bool HVACTemplateZonePTHP::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
  }

  void HVACTemplateZonePTHP::resetZoneHeatingDesignSupplyAirTemperature() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
  }

  double HVACTemplateZonePTHP::zoneHeatingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
  }

  bool HVACTemplateZonePTHP::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
  }

  bool HVACTemplateZonePTHP::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
      zoneHeatingDesignSupplyAirTemperatureDifference);
  }

  void HVACTemplateZonePTHP::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
  }

  std::string HVACTemplateZonePTHP::baseboardHeatingType() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->baseboardHeatingType();
  }

  bool HVACTemplateZonePTHP::isBaseboardHeatingTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isBaseboardHeatingTypeDefaulted();
  }

  bool HVACTemplateZonePTHP::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
  }

  void HVACTemplateZonePTHP::resetBaseboardHeatingType() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetBaseboardHeatingType();
  }

  boost::optional<double> HVACTemplateZonePTHP::baseboardHeatingCapacity() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->baseboardHeatingCapacity();
  }

  bool HVACTemplateZonePTHP::isBaseboardHeatingCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isBaseboardHeatingCapacityDefaulted();
  }

  bool HVACTemplateZonePTHP::isBaseboardHeatingCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isBaseboardHeatingCapacityAutosized();
  }

  bool HVACTemplateZonePTHP::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
  }

  void HVACTemplateZonePTHP::resetBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetBaseboardHeatingCapacity();
  }

  void HVACTemplateZonePTHP::autosizeBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->autosizeBaseboardHeatingCapacity();
  }

  std::string HVACTemplateZonePTHP::capacityControlMethod() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->capacityControlMethod();
  }

  bool HVACTemplateZonePTHP::isCapacityControlMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->isCapacityControlMethodDefaulted();
  }

  bool HVACTemplateZonePTHP::setCapacityControlMethod(const std::string& capacityControlMethod) {
    return getImpl<detail::HVACTemplateZonePTHP_Impl>()->setCapacityControlMethod(capacityControlMethod);
  }

  void HVACTemplateZonePTHP::resetCapacityControlMethod() {
    getImpl<detail::HVACTemplateZonePTHP_Impl>()->resetCapacityControlMethod();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HVACTemplateZonePTHP_Impl::coolingSupplyAirFlowRate() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate, true);
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingSupplyAirFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate);
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetCoolingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeCoolingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::heatingSupplyAirFlowRate() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate, true);
    }

    bool HVACTemplateZonePTHP_Impl::isHeatingSupplyAirFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate);
    }

    bool HVACTemplateZonePTHP_Impl::isHeatingSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetHeatingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeHeatingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::noLoadSupplyAirFlowRate() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate, true);
    }

    bool HVACTemplateZonePTHP_Impl::isNoLoadSupplyAirFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate);
    }

    bool HVACTemplateZonePTHP_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
    }

    void HVACTemplateZonePTHP_Impl::resetNoLoadSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeNoLoadSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::zoneHeatingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingSizingFactor, true);
    }

    bool HVACTemplateZonePTHP_Impl::isZoneHeatingSizingFactorDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingSizingFactor);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
    }

    void HVACTemplateZonePTHP_Impl::resetZoneHeatingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingSizingFactor, ""));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::zoneCoolingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingSizingFactor, true);
    }

    bool HVACTemplateZonePTHP_Impl::isZoneCoolingSizingFactorDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingSizingFactor);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
    }

    void HVACTemplateZonePTHP_Impl::resetZoneCoolingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingSizingFactor, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::outdoorAirMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isOutdoorAirMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirMethod);
    }

    bool HVACTemplateZonePTHP_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirMethod, outdoorAirMethod);
    }

    void HVACTemplateZonePTHP_Impl::resetOutdoorAirMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirMethod, ""));
    }

    double HVACTemplateZonePTHP_Impl::outdoorAirFlowRateperPerson() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperPerson, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperPerson);
    }

    bool HVACTemplateZonePTHP_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetOutdoorAirFlowRateperPerson() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperPerson, ""));
    }

    double HVACTemplateZonePTHP_Impl::outdoorAirFlowRateperZoneFloorArea() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZoneFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZoneFloorArea);
    }

    bool HVACTemplateZonePTHP_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZoneFloorArea, ""));
    }

    double HVACTemplateZonePTHP_Impl::outdoorAirFlowRateperZone() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZone, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZone);
    }

    bool HVACTemplateZonePTHP_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetOutdoorAirFlowRateperZone() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZone, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::supplyFanPlacement() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplyFanPlacementDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanPlacement);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanPlacement, supplyFanPlacement);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplyFanPlacement() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanPlacement, ""));
    }

    double HVACTemplateZonePTHP_Impl::supplyFanTotalEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplyFanTotalEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanTotalEfficiency);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanTotalEfficiency, supplyFanTotalEfficiency);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplyFanTotalEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanTotalEfficiency, ""));
    }

    double HVACTemplateZonePTHP_Impl::supplyFanDeltaPressure() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanDeltaPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplyFanDeltaPressureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanDeltaPressure);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanDeltaPressure, supplyFanDeltaPressure);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplyFanDeltaPressure() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanDeltaPressure, ""));
    }

    double HVACTemplateZonePTHP_Impl::supplyFanMotorEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanMotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplyFanMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanMotorEfficiency);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanMotorEfficiency, supplyFanMotorEfficiency);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplyFanMotorEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplyFanMotorEfficiency, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::coolingCoilType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilType);
    }

    bool HVACTemplateZonePTHP_Impl::setCoolingCoilType(const std::string& coolingCoilType) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilType, coolingCoilType);
    }

    void HVACTemplateZonePTHP_Impl::resetCoolingCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilType, ""));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::coolingCoilGrossRatedTotalCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity, true);
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingCoilGrossRatedTotalCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity);
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingCoilGrossRatedTotalCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity, coolingCoilGrossRatedTotalCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetCoolingCoilGrossRatedTotalCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeCoolingCoilGrossRatedTotalCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity, "autosize"));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::coolingCoilGrossRatedSensibleHeatRatio() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio, true);
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio);
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio, coolingCoilGrossRatedSensibleHeatRatio);
    }

    void HVACTemplateZonePTHP_Impl::resetCoolingCoilGrossRatedSensibleHeatRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeCoolingCoilGrossRatedSensibleHeatRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio, "autosize"));
    }

    double HVACTemplateZonePTHP_Impl::coolingCoilGrossRatedCOP() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isCoolingCoilGrossRatedCOPDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedCOP);
    }

    bool HVACTemplateZonePTHP_Impl::setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedCOP, coolingCoilGrossRatedCOP);
    }

    void HVACTemplateZonePTHP_Impl::resetCoolingCoilGrossRatedCOP() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedCOP, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::heatPumpHeatingCoilType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpHeatingCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilType);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilType, heatPumpHeatingCoilType);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpHeatingCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilType, ""));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::heatPumpHeatingCoilGrossRatedCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity, true);
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity);
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity, heatPumpHeatingCoilGrossRatedCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpHeatingCoilGrossRatedCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeHeatPumpHeatingCoilGrossRatedCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity, "autosize"));
    }

    double HVACTemplateZonePTHP_Impl::heatPumpHeatingCoilGrossRatedCOP() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCOP);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCOP, heatPumpHeatingCoilGrossRatedCOP);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpHeatingCoilGrossRatedCOP() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCOP, ""));
    }

    double HVACTemplateZonePTHP_Impl::heatPumpHeatingMinimumOutdoorDryBulbTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature,
                       heatPumpHeatingMinimumOutdoorDryBulbTemperature);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature, ""));
    }

    double HVACTemplateZonePTHP_Impl::heatPumpDefrostMaximumOutdoorDryBulbTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature,
                       heatPumpDefrostMaximumOutdoorDryBulbTemperature);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::heatPumpDefrostStrategy() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpDefrostStrategyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostStrategy);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostStrategy, heatPumpDefrostStrategy);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpDefrostStrategy() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostStrategy, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::heatPumpDefrostControl() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpDefrostControlDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostControl);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostControl, heatPumpDefrostControl);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpDefrostControl() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostControl, ""));
    }

    double HVACTemplateZonePTHP_Impl::heatPumpDefrostTimePeriodFraction() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostTimePeriodFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isHeatPumpDefrostTimePeriodFractionDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostTimePeriodFraction);
    }

    bool HVACTemplateZonePTHP_Impl::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostTimePeriodFraction, heatPumpDefrostTimePeriodFraction);
    }

    void HVACTemplateZonePTHP_Impl::resetHeatPumpDefrostTimePeriodFraction() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::HeatPumpDefrostTimePeriodFraction, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::supplementalHeatingCoilType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplementalHeatingCoilTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilType);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilType, supplementalHeatingCoilType);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplementalHeatingCoilType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilType, ""));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::supplementalHeatingCoilCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity, true);
    }

    bool HVACTemplateZonePTHP_Impl::isSupplementalHeatingCoilCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity);
    }

    bool HVACTemplateZonePTHP_Impl::isSupplementalHeatingCoilCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity, supplementalHeatingCoilCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetSupplementalHeatingCoilCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeSupplementalHeatingCoilCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity, "autosize"));
    }

    double HVACTemplateZonePTHP_Impl::supplementalHeatingCoilMaximumOutdoorDryBulbTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature(
      double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature,
                                    supplementalHeatingCoilMaximumOutdoorDryBulbTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, ""));
    }

    double HVACTemplateZonePTHP_Impl::supplementalGasHeatingCoilEfficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplementalGasHeatingCoilEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilEfficiency);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplementalGasHeatingCoilEfficiency(double supplementalGasHeatingCoilEfficiency) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilEfficiency, supplementalGasHeatingCoilEfficiency);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplementalGasHeatingCoilEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilEfficiency, ""));
    }

    double HVACTemplateZonePTHP_Impl::supplementalGasHeatingCoilParasiticElectricLoad() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilParasiticElectricLoad);
    }

    bool HVACTemplateZonePTHP_Impl::setSupplementalGasHeatingCoilParasiticElectricLoad(double supplementalGasHeatingCoilParasiticElectricLoad) {
      return setDouble(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilParasiticElectricLoad,
                       supplementalGasHeatingCoilParasiticElectricLoad);
    }

    void HVACTemplateZonePTHP_Impl::resetSupplementalGasHeatingCoilParasiticElectricLoad() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilParasiticElectricLoad, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
      const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                       zoneCoolingDesignSupplyAirTemperatureInputMethod);
    }

    void HVACTemplateZonePTHP_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
    }

    double HVACTemplateZonePTHP_Impl::zoneCoolingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperature);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperature, ""));
    }

    double HVACTemplateZonePTHP_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                    zoneCoolingDesignSupplyAirTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
      const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                       zoneHeatingDesignSupplyAirTemperatureInputMethod);
    }

    void HVACTemplateZonePTHP_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
    }

    double HVACTemplateZonePTHP_Impl::zoneHeatingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperature);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperature, ""));
    }

    double HVACTemplateZonePTHP_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
    }

    bool HVACTemplateZonePTHP_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                    zoneHeatingDesignSupplyAirTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
    }

    std::string HVACTemplateZonePTHP_Impl::baseboardHeatingType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isBaseboardHeatingTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingType);
    }

    bool HVACTemplateZonePTHP_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingType, baseboardHeatingType);
    }

    void HVACTemplateZonePTHP_Impl::resetBaseboardHeatingType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingType, ""));
    }

    boost::optional<double> HVACTemplateZonePTHP_Impl::baseboardHeatingCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity, true);
    }

    bool HVACTemplateZonePTHP_Impl::isBaseboardHeatingCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity);
    }

    bool HVACTemplateZonePTHP_Impl::isBaseboardHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZonePTHP_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZonePTHP_Impl::resetBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity, ""));
    }

    void HVACTemplateZonePTHP_Impl::autosizeBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity, "autosize"));
    }

    std::string HVACTemplateZonePTHP_Impl::capacityControlMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_PTHPFields::CapacityControlMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZonePTHP_Impl::isCapacityControlMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_PTHPFields::CapacityControlMethod);
    }

    bool HVACTemplateZonePTHP_Impl::setCapacityControlMethod(const std::string& capacityControlMethod) {
      return setString(openstudio::HVACTemplate_Zone_PTHPFields::CapacityControlMethod, capacityControlMethod);
    }

    void HVACTemplateZonePTHP_Impl::resetCapacityControlMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTHPFields::CapacityControlMethod, ""));
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::outdoorAirMethodValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::outdoorAirMethodValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::supplyFanPlacementValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::supplyFanPlacementValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::coolingCoilTypeValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::coolingCoilTypeValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::heatPumpHeatingCoilTypeValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::heatPumpHeatingCoilTypeValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::heatPumpDefrostStrategyValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::heatPumpDefrostStrategyValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::heatPumpDefrostControlValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::heatPumpDefrostControlValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::supplementalHeatingCoilTypeValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::supplementalHeatingCoilTypeValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::baseboardHeatingTypeValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::baseboardHeatingTypeValues();
    }

    std::vector<std::string> HVACTemplateZonePTHP_Impl::capacityControlMethodValues() const {
      return openstudio::epmodel::HVACTemplateZonePTHP::capacityControlMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
