/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZonePTAC.hpp"
#include "HVACTemplateZonePTAC_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_PTAC_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateZonePTAC::HVACTemplateZonePTAC(const Model& model) : ModelObject(HVACTemplateZonePTAC::iddObjectType(), model) {}

HVACTemplateZonePTAC::HVACTemplateZonePTAC(std::shared_ptr<detail::HVACTemplateZonePTAC_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateZonePTAC::iddObjectType() {
  return IddObjectType::HVACTemplate_Zone_PTAC;
}

std::vector<std::string> HVACTemplateZonePTAC::outdoorAirMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirMethod);
}

std::vector<std::string> HVACTemplateZonePTAC::supplyFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTACFields::SupplyFanPlacement);
}

std::vector<std::string> HVACTemplateZonePTAC::coolingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilType);
}

std::vector<std::string> HVACTemplateZonePTAC::heatingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilType);
}

std::vector<std::string> HVACTemplateZonePTAC::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZonePTAC::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

std::vector<std::string> HVACTemplateZonePTAC::baseboardHeatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingType);
}

std::vector<std::string> HVACTemplateZonePTAC::capacityControlMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_PTACFields::CapacityControlMethod);
}



boost::optional<double> HVACTemplateZonePTAC::coolingSupplyAirFlowRate() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->coolingSupplyAirFlowRate();
}

bool HVACTemplateZonePTAC::isCoolingSupplyAirFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingSupplyAirFlowRateDefaulted();
}

bool HVACTemplateZonePTAC::isCoolingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingSupplyAirFlowRateAutosized();
}

bool HVACTemplateZonePTAC::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setCoolingSupplyAirFlowRate(coolingSupplyAirFlowRate);
}

void HVACTemplateZonePTAC::resetCoolingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetCoolingSupplyAirFlowRate();
}

void HVACTemplateZonePTAC::autosizeCoolingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeCoolingSupplyAirFlowRate();
}

boost::optional<double> HVACTemplateZonePTAC::heatingSupplyAirFlowRate() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->heatingSupplyAirFlowRate();
}

bool HVACTemplateZonePTAC::isHeatingSupplyAirFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isHeatingSupplyAirFlowRateDefaulted();
}

bool HVACTemplateZonePTAC::isHeatingSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isHeatingSupplyAirFlowRateAutosized();
}

bool HVACTemplateZonePTAC::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setHeatingSupplyAirFlowRate(heatingSupplyAirFlowRate);
}

void HVACTemplateZonePTAC::resetHeatingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetHeatingSupplyAirFlowRate();
}

void HVACTemplateZonePTAC::autosizeHeatingSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeHeatingSupplyAirFlowRate();
}

boost::optional<double> HVACTemplateZonePTAC::noLoadSupplyAirFlowRate() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->noLoadSupplyAirFlowRate();
}

bool HVACTemplateZonePTAC::isNoLoadSupplyAirFlowRateDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isNoLoadSupplyAirFlowRateDefaulted();
}

bool HVACTemplateZonePTAC::isNoLoadSupplyAirFlowRateAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isNoLoadSupplyAirFlowRateAutosized();
}

bool HVACTemplateZonePTAC::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setNoLoadSupplyAirFlowRate(noLoadSupplyAirFlowRate);
}

void HVACTemplateZonePTAC::resetNoLoadSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetNoLoadSupplyAirFlowRate();
}

void HVACTemplateZonePTAC::autosizeNoLoadSupplyAirFlowRate() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeNoLoadSupplyAirFlowRate();
}

boost::optional<double> HVACTemplateZonePTAC::zoneHeatingSizingFactor() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneHeatingSizingFactor();
}

bool HVACTemplateZonePTAC::isZoneHeatingSizingFactorDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneHeatingSizingFactorDefaulted();
}

bool HVACTemplateZonePTAC::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
}

void HVACTemplateZonePTAC::resetZoneHeatingSizingFactor() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneHeatingSizingFactor();
}

boost::optional<double> HVACTemplateZonePTAC::zoneCoolingSizingFactor() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneCoolingSizingFactor();
}

bool HVACTemplateZonePTAC::isZoneCoolingSizingFactorDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneCoolingSizingFactorDefaulted();
}

bool HVACTemplateZonePTAC::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
}

void HVACTemplateZonePTAC::resetZoneCoolingSizingFactor() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneCoolingSizingFactor();
}

std::string HVACTemplateZonePTAC::outdoorAirMethod() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->outdoorAirMethod();
}

bool HVACTemplateZonePTAC::isOutdoorAirMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isOutdoorAirMethodDefaulted();
}

bool HVACTemplateZonePTAC::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

void HVACTemplateZonePTAC::resetOutdoorAirMethod() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetOutdoorAirMethod();
}

double HVACTemplateZonePTAC::outdoorAirFlowRateperPerson() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->outdoorAirFlowRateperPerson();
}

bool HVACTemplateZonePTAC::isOutdoorAirFlowRateperPersonDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
}

bool HVACTemplateZonePTAC::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
}

void HVACTemplateZonePTAC::resetOutdoorAirFlowRateperPerson() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetOutdoorAirFlowRateperPerson();
}

double HVACTemplateZonePTAC::outdoorAirFlowRateperZoneFloorArea() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->outdoorAirFlowRateperZoneFloorArea();
}

bool HVACTemplateZonePTAC::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
}

bool HVACTemplateZonePTAC::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
}

void HVACTemplateZonePTAC::resetOutdoorAirFlowRateperZoneFloorArea() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
}

double HVACTemplateZonePTAC::outdoorAirFlowRateperZone() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->outdoorAirFlowRateperZone();
}

bool HVACTemplateZonePTAC::isOutdoorAirFlowRateperZoneDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
}

bool HVACTemplateZonePTAC::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
}

void HVACTemplateZonePTAC::resetOutdoorAirFlowRateperZone() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetOutdoorAirFlowRateperZone();
}

std::string HVACTemplateZonePTAC::supplyFanPlacement() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->supplyFanPlacement();
}

bool HVACTemplateZonePTAC::isSupplyFanPlacementDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isSupplyFanPlacementDefaulted();
}

bool HVACTemplateZonePTAC::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setSupplyFanPlacement(supplyFanPlacement);
}

void HVACTemplateZonePTAC::resetSupplyFanPlacement() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetSupplyFanPlacement();
}

double HVACTemplateZonePTAC::supplyFanTotalEfficiency() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->supplyFanTotalEfficiency();
}

bool HVACTemplateZonePTAC::isSupplyFanTotalEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isSupplyFanTotalEfficiencyDefaulted();
}

bool HVACTemplateZonePTAC::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setSupplyFanTotalEfficiency(supplyFanTotalEfficiency);
}

void HVACTemplateZonePTAC::resetSupplyFanTotalEfficiency() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetSupplyFanTotalEfficiency();
}

double HVACTemplateZonePTAC::supplyFanDeltaPressure() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->supplyFanDeltaPressure();
}

bool HVACTemplateZonePTAC::isSupplyFanDeltaPressureDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isSupplyFanDeltaPressureDefaulted();
}

bool HVACTemplateZonePTAC::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setSupplyFanDeltaPressure(supplyFanDeltaPressure);
}

void HVACTemplateZonePTAC::resetSupplyFanDeltaPressure() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetSupplyFanDeltaPressure();
}

double HVACTemplateZonePTAC::supplyFanMotorEfficiency() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->supplyFanMotorEfficiency();
}

bool HVACTemplateZonePTAC::isSupplyFanMotorEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isSupplyFanMotorEfficiencyDefaulted();
}

bool HVACTemplateZonePTAC::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setSupplyFanMotorEfficiency(supplyFanMotorEfficiency);
}

void HVACTemplateZonePTAC::resetSupplyFanMotorEfficiency() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetSupplyFanMotorEfficiency();
}

std::string HVACTemplateZonePTAC::coolingCoilType() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->coolingCoilType();
}

bool HVACTemplateZonePTAC::isCoolingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingCoilTypeDefaulted();
}

bool HVACTemplateZonePTAC::setCoolingCoilType(const std::string& coolingCoilType) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setCoolingCoilType(coolingCoilType);
}

void HVACTemplateZonePTAC::resetCoolingCoilType() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetCoolingCoilType();
}

boost::optional<double> HVACTemplateZonePTAC::coolingCoilGrossRatedTotalCapacity() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->coolingCoilGrossRatedTotalCapacity();
}

bool HVACTemplateZonePTAC::isCoolingCoilGrossRatedTotalCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingCoilGrossRatedTotalCapacityDefaulted();
}

bool HVACTemplateZonePTAC::isCoolingCoilGrossRatedTotalCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingCoilGrossRatedTotalCapacityAutosized();
}

bool HVACTemplateZonePTAC::setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setCoolingCoilGrossRatedTotalCapacity(coolingCoilGrossRatedTotalCapacity);
}

void HVACTemplateZonePTAC::resetCoolingCoilGrossRatedTotalCapacity() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetCoolingCoilGrossRatedTotalCapacity();
}

void HVACTemplateZonePTAC::autosizeCoolingCoilGrossRatedTotalCapacity() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeCoolingCoilGrossRatedTotalCapacity();
}

boost::optional<double> HVACTemplateZonePTAC::coolingCoilGrossRatedSensibleHeatRatio() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->coolingCoilGrossRatedSensibleHeatRatio();
}

bool HVACTemplateZonePTAC::isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingCoilGrossRatedSensibleHeatRatioDefaulted();
}

bool HVACTemplateZonePTAC::isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingCoilGrossRatedSensibleHeatRatioAutosized();
}

bool HVACTemplateZonePTAC::setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setCoolingCoilGrossRatedSensibleHeatRatio(coolingCoilGrossRatedSensibleHeatRatio);
}

void HVACTemplateZonePTAC::resetCoolingCoilGrossRatedSensibleHeatRatio() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetCoolingCoilGrossRatedSensibleHeatRatio();
}

void HVACTemplateZonePTAC::autosizeCoolingCoilGrossRatedSensibleHeatRatio() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeCoolingCoilGrossRatedSensibleHeatRatio();
}

double HVACTemplateZonePTAC::coolingCoilGrossRatedCoolingCOP() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->coolingCoilGrossRatedCoolingCOP();
}

bool HVACTemplateZonePTAC::isCoolingCoilGrossRatedCoolingCOPDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCoolingCoilGrossRatedCoolingCOPDefaulted();
}

bool HVACTemplateZonePTAC::setCoolingCoilGrossRatedCoolingCOP(double coolingCoilGrossRatedCoolingCOP) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setCoolingCoilGrossRatedCoolingCOP(coolingCoilGrossRatedCoolingCOP);
}

void HVACTemplateZonePTAC::resetCoolingCoilGrossRatedCoolingCOP() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetCoolingCoilGrossRatedCoolingCOP();
}

std::string HVACTemplateZonePTAC::heatingCoilType() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->heatingCoilType();
}

bool HVACTemplateZonePTAC::isHeatingCoilTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isHeatingCoilTypeDefaulted();
}

bool HVACTemplateZonePTAC::setHeatingCoilType(const std::string& heatingCoilType) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setHeatingCoilType(heatingCoilType);
}

void HVACTemplateZonePTAC::resetHeatingCoilType() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetHeatingCoilType();
}

boost::optional<double> HVACTemplateZonePTAC::heatingCoilCapacity() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->heatingCoilCapacity();
}

bool HVACTemplateZonePTAC::isHeatingCoilCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isHeatingCoilCapacityDefaulted();
}

bool HVACTemplateZonePTAC::isHeatingCoilCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isHeatingCoilCapacityAutosized();
}

bool HVACTemplateZonePTAC::setHeatingCoilCapacity(double heatingCoilCapacity) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setHeatingCoilCapacity(heatingCoilCapacity);
}

void HVACTemplateZonePTAC::resetHeatingCoilCapacity() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetHeatingCoilCapacity();
}

void HVACTemplateZonePTAC::autosizeHeatingCoilCapacity() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeHeatingCoilCapacity();
}

double HVACTemplateZonePTAC::gasHeatingCoilEfficiency() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->gasHeatingCoilEfficiency();
}

bool HVACTemplateZonePTAC::isGasHeatingCoilEfficiencyDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isGasHeatingCoilEfficiencyDefaulted();
}

bool HVACTemplateZonePTAC::setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setGasHeatingCoilEfficiency(gasHeatingCoilEfficiency);
}

void HVACTemplateZonePTAC::resetGasHeatingCoilEfficiency() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetGasHeatingCoilEfficiency();
}

double HVACTemplateZonePTAC::gasHeatingCoilParasiticElectricLoad() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->gasHeatingCoilParasiticElectricLoad();
}

bool HVACTemplateZonePTAC::isGasHeatingCoilParasiticElectricLoadDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isGasHeatingCoilParasiticElectricLoadDefaulted();
}

bool HVACTemplateZonePTAC::setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setGasHeatingCoilParasiticElectricLoad(gasHeatingCoilParasiticElectricLoad);
}

void HVACTemplateZonePTAC::resetGasHeatingCoilParasiticElectricLoad() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetGasHeatingCoilParasiticElectricLoad();
}

std::string HVACTemplateZonePTAC::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
}

bool HVACTemplateZonePTAC::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZonePTAC::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZonePTAC::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZonePTAC::zoneCoolingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneCoolingDesignSupplyAirTemperature();
}

bool HVACTemplateZonePTAC::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZonePTAC::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
}

void HVACTemplateZonePTAC::resetZoneCoolingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
}

double HVACTemplateZonePTAC::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZonePTAC::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZonePTAC::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
    zoneCoolingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZonePTAC::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZonePTAC::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
}

bool HVACTemplateZonePTAC::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
}

bool HVACTemplateZonePTAC::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

void HVACTemplateZonePTAC::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
}

double HVACTemplateZonePTAC::zoneHeatingDesignSupplyAirTemperature() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneHeatingDesignSupplyAirTemperature();
}

bool HVACTemplateZonePTAC::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
}

bool HVACTemplateZonePTAC::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
}

void HVACTemplateZonePTAC::resetZoneHeatingDesignSupplyAirTemperature() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
}

double HVACTemplateZonePTAC::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
}

bool HVACTemplateZonePTAC::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
}

bool HVACTemplateZonePTAC::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
    zoneHeatingDesignSupplyAirTemperatureDifference);
}

void HVACTemplateZonePTAC::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
}

std::string HVACTemplateZonePTAC::baseboardHeatingType() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->baseboardHeatingType();
}

bool HVACTemplateZonePTAC::isBaseboardHeatingTypeDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isBaseboardHeatingTypeDefaulted();
}

bool HVACTemplateZonePTAC::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
}

void HVACTemplateZonePTAC::resetBaseboardHeatingType() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetBaseboardHeatingType();
}

boost::optional<double> HVACTemplateZonePTAC::baseboardHeatingCapacity() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->baseboardHeatingCapacity();
}

bool HVACTemplateZonePTAC::isBaseboardHeatingCapacityDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isBaseboardHeatingCapacityDefaulted();
}

bool HVACTemplateZonePTAC::isBaseboardHeatingCapacityAutosized() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isBaseboardHeatingCapacityAutosized();
}

bool HVACTemplateZonePTAC::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
}

void HVACTemplateZonePTAC::resetBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetBaseboardHeatingCapacity();
}

void HVACTemplateZonePTAC::autosizeBaseboardHeatingCapacity() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->autosizeBaseboardHeatingCapacity();
}

std::string HVACTemplateZonePTAC::capacityControlMethod() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->capacityControlMethod();
}

bool HVACTemplateZonePTAC::isCapacityControlMethodDefaulted() const {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->isCapacityControlMethodDefaulted();
}

bool HVACTemplateZonePTAC::setCapacityControlMethod(const std::string& capacityControlMethod) {
  return getImpl<detail::HVACTemplateZonePTAC_Impl>()->setCapacityControlMethod(capacityControlMethod);
}

void HVACTemplateZonePTAC::resetCapacityControlMethod() {
  getImpl<detail::HVACTemplateZonePTAC_Impl>()->resetCapacityControlMethod();
}

namespace detail {

boost::optional<double> HVACTemplateZonePTAC_Impl::coolingSupplyAirFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingSupplyAirFlowRate, true);
}

boost::optional<double> HVACTemplateZonePTAC_Impl::heatingSupplyAirFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::HeatingSupplyAirFlowRate, true);
}

boost::optional<double> HVACTemplateZonePTAC_Impl::noLoadSupplyAirFlowRate() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::NoLoadSupplyAirFlowRate, true);
}

boost::optional<double> HVACTemplateZonePTAC_Impl::zoneHeatingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingSizingFactor, true);
}

boost::optional<double> HVACTemplateZonePTAC_Impl::zoneCoolingSizingFactor() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingSizingFactor, true);
}

std::string HVACTemplateZonePTAC_Impl::outdoorAirMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::outdoorAirFlowRateperPerson() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperPerson, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::outdoorAirFlowRateperZoneFloorArea() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZoneFloorArea, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::outdoorAirFlowRateperZone() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZone, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZonePTAC_Impl::supplyFanPlacement() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::supplyFanTotalEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::supplyFanDeltaPressure() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanDeltaPressure, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::supplyFanMotorEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanMotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZonePTAC_Impl::coolingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZonePTAC_Impl::coolingCoilGrossRatedTotalCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedTotalCapacity, true);
}

boost::optional<double> HVACTemplateZonePTAC_Impl::coolingCoilGrossRatedSensibleHeatRatio() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedSensibleHeatRatio, true);
}

double HVACTemplateZonePTAC_Impl::coolingCoilGrossRatedCoolingCOP() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZonePTAC_Impl::heatingCoilType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZonePTAC_Impl::heatingCoilCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilCapacity, true);
}

double HVACTemplateZonePTAC_Impl::gasHeatingCoilEfficiency() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::gasHeatingCoilParasiticElectricLoad() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilParasiticElectricLoad, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZonePTAC_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::zoneCoolingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZonePTAC_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::zoneHeatingDesignSupplyAirTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplateZonePTAC_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
  auto value = getDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplateZonePTAC_Impl::baseboardHeatingType() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HVACTemplateZonePTAC_Impl::baseboardHeatingCapacity() const {
  return getDouble(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingCapacity, true);
}

std::string HVACTemplateZonePTAC_Impl::capacityControlMethod() const {
  auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::CapacityControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplateZonePTAC_Impl::isCoolingSupplyAirFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::CoolingSupplyAirFlowRate);
}

bool HVACTemplateZonePTAC_Impl::isCoolingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isHeatingSupplyAirFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::HeatingSupplyAirFlowRate);
}

bool HVACTemplateZonePTAC_Impl::isHeatingSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isNoLoadSupplyAirFlowRateDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::NoLoadSupplyAirFlowRate);
}

bool HVACTemplateZonePTAC_Impl::isNoLoadSupplyAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isZoneHeatingSizingFactorDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingSizingFactor);
}

bool HVACTemplateZonePTAC_Impl::isZoneCoolingSizingFactorDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingSizingFactor);
}

bool HVACTemplateZonePTAC_Impl::isOutdoorAirMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirMethod);
}

bool HVACTemplateZonePTAC_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperPerson);
}

bool HVACTemplateZonePTAC_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZoneFloorArea);
}

bool HVACTemplateZonePTAC_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZone);
}

bool HVACTemplateZonePTAC_Impl::isSupplyFanPlacementDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanPlacement);
}

bool HVACTemplateZonePTAC_Impl::isSupplyFanTotalEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanTotalEfficiency);
}

bool HVACTemplateZonePTAC_Impl::isSupplyFanDeltaPressureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanDeltaPressure);
}

bool HVACTemplateZonePTAC_Impl::isSupplyFanMotorEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanMotorEfficiency);
}

bool HVACTemplateZonePTAC_Impl::isCoolingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilType);
}

bool HVACTemplateZonePTAC_Impl::isCoolingCoilGrossRatedTotalCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedTotalCapacity);
}

bool HVACTemplateZonePTAC_Impl::isCoolingCoilGrossRatedTotalCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedTotalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedSensibleHeatRatio);
}

bool HVACTemplateZonePTAC_Impl::isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isCoolingCoilGrossRatedCoolingCOPDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedCoolingCOP);
}

bool HVACTemplateZonePTAC_Impl::isHeatingCoilTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilType);
}

bool HVACTemplateZonePTAC_Impl::isHeatingCoilCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilCapacity);
}

bool HVACTemplateZonePTAC_Impl::isHeatingCoilCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isGasHeatingCoilEfficiencyDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilEfficiency);
}

bool HVACTemplateZonePTAC_Impl::isGasHeatingCoilParasiticElectricLoadDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilParasiticElectricLoad);
}

bool HVACTemplateZonePTAC_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZonePTAC_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperature);
}

bool HVACTemplateZonePTAC_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZonePTAC_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZonePTAC_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperature);
}

bool HVACTemplateZonePTAC_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
}

bool HVACTemplateZonePTAC_Impl::isBaseboardHeatingTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingType);
}

bool HVACTemplateZonePTAC_Impl::isBaseboardHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingCapacity);
}

bool HVACTemplateZonePTAC_Impl::isBaseboardHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool HVACTemplateZonePTAC_Impl::isCapacityControlMethodDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Zone_PTACFields::CapacityControlMethod);
}

bool HVACTemplateZonePTAC_Impl::setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::NoLoadSupplyAirFlowRate, noLoadSupplyAirFlowRate);
}

bool HVACTemplateZonePTAC_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
}

bool HVACTemplateZonePTAC_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
}

bool HVACTemplateZonePTAC_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirMethod, outdoorAirMethod);
}

bool HVACTemplateZonePTAC_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setSupplyFanPlacement(const std::string& supplyFanPlacement) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanPlacement, supplyFanPlacement);
}

bool HVACTemplateZonePTAC_Impl::setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanTotalEfficiency, supplyFanTotalEfficiency);
}

bool HVACTemplateZonePTAC_Impl::setSupplyFanDeltaPressure(double supplyFanDeltaPressure) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanDeltaPressure, supplyFanDeltaPressure);
}

bool HVACTemplateZonePTAC_Impl::setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanMotorEfficiency, supplyFanMotorEfficiency);
}

bool HVACTemplateZonePTAC_Impl::setCoolingCoilType(const std::string& coolingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilType, coolingCoilType);
}

bool HVACTemplateZonePTAC_Impl::setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedTotalCapacity, coolingCoilGrossRatedTotalCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedSensibleHeatRatio, coolingCoilGrossRatedSensibleHeatRatio);
}

bool HVACTemplateZonePTAC_Impl::setCoolingCoilGrossRatedCoolingCOP(double coolingCoilGrossRatedCoolingCOP) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedCoolingCOP, coolingCoilGrossRatedCoolingCOP);
}

bool HVACTemplateZonePTAC_Impl::setHeatingCoilType(const std::string& heatingCoilType) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilType, heatingCoilType);
}

bool HVACTemplateZonePTAC_Impl::setHeatingCoilCapacity(double heatingCoilCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilCapacity, heatingCoilCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilEfficiency, gasHeatingCoilEfficiency);
}

bool HVACTemplateZonePTAC_Impl::setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad) {
  return setDouble(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilParasiticElectricLoad, gasHeatingCoilParasiticElectricLoad);
}

bool HVACTemplateZonePTAC_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZonePTAC_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                zoneCoolingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
  const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod);
}

bool HVACTemplateZonePTAC_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
  const bool result =
    setDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                zoneHeatingDesignSupplyAirTemperatureDifference);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingType, baseboardHeatingType);
}

bool HVACTemplateZonePTAC_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
  const bool result = setDouble(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplateZonePTAC_Impl::setCapacityControlMethod(const std::string& capacityControlMethod) {
  return setString(openstudio::HVACTemplate_Zone_PTACFields::CapacityControlMethod, capacityControlMethod);
}

void HVACTemplateZonePTAC_Impl::resetCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingSupplyAirFlowRate, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingSupplyAirFlowRate, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::HeatingSupplyAirFlowRate, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::HeatingSupplyAirFlowRate, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::NoLoadSupplyAirFlowRate, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeNoLoadSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::NoLoadSupplyAirFlowRate, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetZoneHeatingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingSizingFactor, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneCoolingSizingFactor() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingSizingFactor, ""));
}

void HVACTemplateZonePTAC_Impl::resetOutdoorAirMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirMethod, ""));
}

void HVACTemplateZonePTAC_Impl::resetOutdoorAirFlowRateperPerson() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperPerson, ""));
}

void HVACTemplateZonePTAC_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZoneFloorArea, ""));
}

void HVACTemplateZonePTAC_Impl::resetOutdoorAirFlowRateperZone() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::OutdoorAirFlowRateperZone, ""));
}

void HVACTemplateZonePTAC_Impl::resetSupplyFanPlacement() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanPlacement, ""));
}

void HVACTemplateZonePTAC_Impl::resetSupplyFanTotalEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanTotalEfficiency, ""));
}

void HVACTemplateZonePTAC_Impl::resetSupplyFanDeltaPressure() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanDeltaPressure, ""));
}

void HVACTemplateZonePTAC_Impl::resetSupplyFanMotorEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::SupplyFanMotorEfficiency, ""));
}

void HVACTemplateZonePTAC_Impl::resetCoolingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilType, ""));
}

void HVACTemplateZonePTAC_Impl::resetCoolingCoilGrossRatedTotalCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedTotalCapacity, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeCoolingCoilGrossRatedTotalCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedTotalCapacity, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetCoolingCoilGrossRatedSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedSensibleHeatRatio, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeCoolingCoilGrossRatedSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedSensibleHeatRatio, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetCoolingCoilGrossRatedCoolingCOP() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CoolingCoilGrossRatedCoolingCOP, ""));
}

void HVACTemplateZonePTAC_Impl::resetHeatingCoilType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilType, ""));
}

void HVACTemplateZonePTAC_Impl::resetHeatingCoilCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilCapacity, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeHeatingCoilCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::HeatingCoilCapacity, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetGasHeatingCoilEfficiency() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilEfficiency, ""));
}

void HVACTemplateZonePTAC_Impl::resetGasHeatingCoilParasiticElectricLoad() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::GasHeatingCoilParasiticElectricLoad, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperature, ""));
}

void HVACTemplateZonePTAC_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
}

void HVACTemplateZonePTAC_Impl::resetBaseboardHeatingType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingType, ""));
}

void HVACTemplateZonePTAC_Impl::resetBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingCapacity, ""));
}

void HVACTemplateZonePTAC_Impl::autosizeBaseboardHeatingCapacity() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::BaseboardHeatingCapacity, "autosize"));
}

void HVACTemplateZonePTAC_Impl::resetCapacityControlMethod() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Zone_PTACFields::CapacityControlMethod, ""));
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::outdoorAirMethodValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::outdoorAirMethodValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::supplyFanPlacementValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::supplyFanPlacementValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::coolingCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::coolingCoilTypeValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::heatingCoilTypeValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::heatingCoilTypeValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::baseboardHeatingTypeValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::baseboardHeatingTypeValues();
}

std::vector<std::string> HVACTemplateZonePTAC_Impl::capacityControlMethodValues() const {
  return openstudio::epmodel::HVACTemplateZonePTAC::capacityControlMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
