/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/AirLoopHVACUnitarySystem.hpp"
#include "ZoneHVACComponent/AirLoopHVACUnitarySystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitarySystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitarySystem::AirLoopHVACUnitarySystem(const Model& model) : ModelObject(AirLoopHVACUnitarySystem::iddObjectType(), model) {
  // Mirror model constructor defaults for scalar fields with strict/non-optional getters.
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setDehumidificationControlType("None"));
  OS_ASSERT(setDXHeatingCoilSizingRatio(1.0));
  OS_ASSERT(setUseDOASDXCoolingCoil(false));
  OS_ASSERT(setDOASDXCoolingCoilLeavingMinimumAirTemperature(2.0));
  OS_ASSERT(setLatentLoadControl("SensibleOnlyLoadControl"));
  OS_ASSERT(setSupplyAirFlowRateMethodDuringCoolingOperation("None"));
  OS_ASSERT(setSupplyAirFlowRateMethodDuringHeatingOperation("None"));
  OS_ASSERT(setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired("None"));
  OS_ASSERT(setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  OS_ASSERT(setMaximumSupplyAirTemperature(80.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(21.0));
  OS_ASSERT(setAncilliaryOnCycleElectricPower(0.0));
  OS_ASSERT(setAncilliaryOffCycleElectricPower(0.0));
}

AirLoopHVACUnitarySystem::AirLoopHVACUnitarySystem(std::shared_ptr<detail::AirLoopHVACUnitarySystem_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACUnitarySystem::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitarySystem;
}

std::vector<std::string> AirLoopHVACUnitarySystem::controlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitarySystemFields::ControlType);
}

std::vector<std::string> AirLoopHVACUnitarySystem::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType);
}

std::vector<std::string> AirLoopHVACUnitarySystem::fanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement);
}

std::vector<std::string> AirLoopHVACUnitarySystem::latentLoadControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl);
}

std::vector<std::string> AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringCoolingOperationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod);
}

std::vector<std::string> AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringHeatingOperationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod);
}

std::vector<std::string> AirLoopHVACUnitarySystem::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod);
}

std::string AirLoopHVACUnitarySystem::controlType() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->controlType();
}

bool AirLoopHVACUnitarySystem::isControlTypeDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isControlTypeDefaulted();
}

bool AirLoopHVACUnitarySystem::setControlType(const std::string& controlType) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setControlType(controlType);
}

void AirLoopHVACUnitarySystem::resetControlType() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetControlType();
}

std::string AirLoopHVACUnitarySystem::dehumidificationControlType() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->dehumidificationControlType();
}

bool AirLoopHVACUnitarySystem::isDehumidificationControlTypeDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDehumidificationControlTypeDefaulted();
}

bool AirLoopHVACUnitarySystem::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

void AirLoopHVACUnitarySystem::resetDehumidificationControlType() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDehumidificationControlType();
}

boost::optional<std::string> AirLoopHVACUnitarySystem::fanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fanPlacement();
}

bool AirLoopHVACUnitarySystem::setFanPlacement(const std::string& fanPlacement) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFanPlacement(fanPlacement);
}

void AirLoopHVACUnitarySystem::resetFanPlacement() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFanPlacement();
}

double AirLoopHVACUnitarySystem::dXHeatingCoilSizingRatio() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->dXHeatingCoilSizingRatio();
}

bool AirLoopHVACUnitarySystem::isDXHeatingCoilSizingRatioDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDXHeatingCoilSizingRatioDefaulted();
}

bool AirLoopHVACUnitarySystem::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
}

void AirLoopHVACUnitarySystem::resetDXHeatingCoilSizingRatio() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDXHeatingCoilSizingRatio();
}

bool AirLoopHVACUnitarySystem::useDOASDXCoolingCoil() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->useDOASDXCoolingCoil();
}

bool AirLoopHVACUnitarySystem::isUseDOASDXCoolingCoilDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isUseDOASDXCoolingCoilDefaulted();
}

bool AirLoopHVACUnitarySystem::setUseDOASDXCoolingCoil(bool useDOASDXCoolingCoil) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setUseDOASDXCoolingCoil(useDOASDXCoolingCoil);
}

void AirLoopHVACUnitarySystem::resetUseDOASDXCoolingCoil() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetUseDOASDXCoolingCoil();
}

double AirLoopHVACUnitarySystem::dOASDXCoolingCoilLeavingMinimumAirTemperature() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->dOASDXCoolingCoilLeavingMinimumAirTemperature();
}

bool AirLoopHVACUnitarySystem::isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted();
}

bool AirLoopHVACUnitarySystem::isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized();
}

bool AirLoopHVACUnitarySystem::setDOASDXCoolingCoilLeavingMinimumAirTemperature(double dOASDXCoolingCoilLeavingMinimumAirTemperature) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDOASDXCoolingCoilLeavingMinimumAirTemperature(
    dOASDXCoolingCoilLeavingMinimumAirTemperature);
}

void AirLoopHVACUnitarySystem::resetDOASDXCoolingCoilLeavingMinimumAirTemperature() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDOASDXCoolingCoilLeavingMinimumAirTemperature();
}

void AirLoopHVACUnitarySystem::autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature();
}

std::string AirLoopHVACUnitarySystem::latentLoadControl() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->latentLoadControl();
}

bool AirLoopHVACUnitarySystem::isLatentLoadControlDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isLatentLoadControlDefaulted();
}

bool AirLoopHVACUnitarySystem::setLatentLoadControl(const std::string& latentLoadControl) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setLatentLoadControl(latentLoadControl);
}

void AirLoopHVACUnitarySystem::resetLatentLoadControl() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetLatentLoadControl();
}

std::string AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateMethodDuringCoolingOperation();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateMethodDuringCoolingOperation(const std::string& supplyAirFlowRateMethodDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateMethodDuringCoolingOperation(
    supplyAirFlowRateMethodDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateMethodDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateMethodDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitarySystem::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(supplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateDuringCoolingOperation();
}

void AirLoopHVACUnitarySystem::autosizeSupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRatePerFloorAreaDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRatePerFloorAreaDuringCoolingOperation();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(double supplyAirFlowRatePerFloorAreaDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(
    supplyAirFlowRatePerFloorAreaDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignCoolingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignCoolingSupplyAirFlowRate();
}

bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignCoolingSupplyAirFlowRate(double fractionofAutosizedDesignCoolingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignCoolingSupplyAirFlowRate(
    fractionofAutosizedDesignCoolingSupplyAirFlowRate);
}

void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignCoolingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignCoolingSupplyAirFlowRate();
}

boost::optional<double> AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation();
}

bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(
  double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(
    designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation();
}

std::string AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateMethodDuringHeatingOperation();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateMethodDuringHeatingOperation(const std::string& supplyAirFlowRateMethodDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateMethodDuringHeatingOperation(
    supplyAirFlowRateMethodDuringHeatingOperation);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateMethodDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateMethodDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitarySystem::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(supplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateDuringHeatingOperation();
}

void AirLoopHVACUnitarySystem::autosizeSupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRatePerFloorAreaduringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRatePerFloorAreaduringHeatingOperation();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(double supplyAirFlowRatePerFloorAreaduringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(
    supplyAirFlowRatePerFloorAreaduringHeatingOperation);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignHeatingSupplyAirFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignHeatingSupplyAirFlowRate();
}

bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignHeatingSupplyAirFlowRate(double fractionofAutosizedDesignHeatingSupplyAirFlowRate) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignHeatingSupplyAirFlowRate(
    fractionofAutosizedDesignHeatingSupplyAirFlowRate);
}

void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignHeatingSupplyAirFlowRate() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignHeatingSupplyAirFlowRate();
}

boost::optional<double> AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation();
}

bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(
  double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(
    designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation);
}

void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation();
}

std::string AirLoopHVACUnitarySystem::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(const std::string& noCoolHeatMethod) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(noCoolHeatMethod);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired();
}

boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(double supplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    supplyAirFlowRateWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

void AirLoopHVACUnitarySystem::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(
  double supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(
    supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem::resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();
}

boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
  double fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
  double fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
}

boost::optional<double> AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired()
  const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
    ->designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
  double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
    ->setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
      designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();
}

boost::optional<double> AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired()
  const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
    ->designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
  double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
    ->setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
      designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();
}

bool AirLoopHVACUnitarySystem::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
}

bool AirLoopHVACUnitarySystem::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
    noLoadSupplyAirFlowRateControlSetToLowSpeed);
}

boost::optional<double> AirLoopHVACUnitarySystem::maximumSupplyAirTemperature() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->maximumSupplyAirTemperature();
}

bool AirLoopHVACUnitarySystem::isMaximumSupplyAirTemperatureDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
}

bool AirLoopHVACUnitarySystem::isMaximumSupplyAirTemperatureAutosized() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isMaximumSupplyAirTemperatureAutosized();
}

bool AirLoopHVACUnitarySystem::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
}

void AirLoopHVACUnitarySystem::resetMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetMaximumSupplyAirTemperature();
}

void AirLoopHVACUnitarySystem::autosizeMaximumSupplyAirTemperature() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeMaximumSupplyAirTemperature();
}

double AirLoopHVACUnitarySystem::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

bool AirLoopHVACUnitarySystem::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
}

bool AirLoopHVACUnitarySystem::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

void AirLoopHVACUnitarySystem::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

double AirLoopHVACUnitarySystem::ancilliaryOnCycleElectricPower() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->ancilliaryOnCycleElectricPower();
}

bool AirLoopHVACUnitarySystem::isAncilliaryOnCycleElectricPowerDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isAncilliaryOnCycleElectricPowerDefaulted();
}

bool AirLoopHVACUnitarySystem::setAncilliaryOnCycleElectricPower(double ancilliaryOnCycleElectricPower) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setAncilliaryOnCycleElectricPower(ancilliaryOnCycleElectricPower);
}

void AirLoopHVACUnitarySystem::resetAncilliaryOnCycleElectricPower() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetAncilliaryOnCycleElectricPower();
}

double AirLoopHVACUnitarySystem::ancilliaryOffCycleElectricPower() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->ancilliaryOffCycleElectricPower();
}

bool AirLoopHVACUnitarySystem::isAncilliaryOffCycleElectricPowerDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isAncilliaryOffCycleElectricPowerDefaulted();
}

bool AirLoopHVACUnitarySystem::setAncilliaryOffCycleElectricPower(double ancilliaryOffCycleElectricPower) {
  return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setAncilliaryOffCycleElectricPower(ancilliaryOffCycleElectricPower);
}

void AirLoopHVACUnitarySystem::resetAncilliaryOffCycleElectricPower() {
  getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetAncilliaryOffCycleElectricPower();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string AirLoopHVACUnitarySystem_Impl::controlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isControlTypeDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType);
}

bool AirLoopHVACUnitarySystem_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType, controlType);
}

void AirLoopHVACUnitarySystem_Impl::resetControlType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType, ""));
}

std::string AirLoopHVACUnitarySystem_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isDehumidificationControlTypeDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType);
}

bool AirLoopHVACUnitarySystem_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, dehumidificationControlType);
}

void AirLoopHVACUnitarySystem_Impl::resetDehumidificationControlType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, ""));
}

boost::optional<std::string> AirLoopHVACUnitarySystem_Impl::fanPlacement() const {
  return getString(openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement, true);
}

bool AirLoopHVACUnitarySystem_Impl::setFanPlacement(const std::string& fanPlacement) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement, fanPlacement);
}

void AirLoopHVACUnitarySystem_Impl::resetFanPlacement() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement, ""));
}

double AirLoopHVACUnitarySystem_Impl::dXHeatingCoilSizingRatio() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isDXHeatingCoilSizingRatioDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio);
}

bool AirLoopHVACUnitarySystem_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
}

void AirLoopHVACUnitarySystem_Impl::resetDXHeatingCoilSizingRatio() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, ""));
}

bool AirLoopHVACUnitarySystem_Impl::useDOASDXCoolingCoil() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, true)) {
    return openstudio::istringEqual(*value, "yes");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::isUseDOASDXCoolingCoilDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil);
}

bool AirLoopHVACUnitarySystem_Impl::setUseDOASDXCoolingCoil(bool useDOASDXCoolingCoil) {
  const bool result = setString(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, useDOASDXCoolingCoil ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void AirLoopHVACUnitarySystem_Impl::resetUseDOASDXCoolingCoil() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, ""));
}

double AirLoopHVACUnitarySystem_Impl::dOASDXCoolingCoilLeavingMinimumAirTemperature() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature);
}

bool AirLoopHVACUnitarySystem_Impl::isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::setDOASDXCoolingCoilLeavingMinimumAirTemperature(double dOASDXCoolingCoilLeavingMinimumAirTemperature) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, dOASDXCoolingCoilLeavingMinimumAirTemperature);
}

void AirLoopHVACUnitarySystem_Impl::resetDOASDXCoolingCoilLeavingMinimumAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, ""));
}

void AirLoopHVACUnitarySystem_Impl::autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, "autosize"));
}

std::string AirLoopHVACUnitarySystem_Impl::latentLoadControl() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isLatentLoadControlDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl);
}

bool AirLoopHVACUnitarySystem_Impl::setLatentLoadControl(const std::string& latentLoadControl) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl, latentLoadControl);
}

void AirLoopHVACUnitarySystem_Impl::resetLatentLoadControl() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl, ""));
}

std::string AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringCoolingOperation() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateMethodDuringCoolingOperation(
  const std::string& supplyAirFlowRateMethodDuringCoolingOperation) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, supplyAirFlowRateMethodDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateMethodDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitarySystem_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRatePerFloorAreaDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea, true);
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(double supplyAirFlowRatePerFloorAreaDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea, supplyAirFlowRatePerFloorAreaDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignCoolingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignCoolingSupplyAirFlowRate(double fractionofAutosizedDesignCoolingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate,
                   fractionofAutosizedDesignCoolingSupplyAirFlowRate);
}

void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignCoolingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity, true);
}

bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(
  double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity,
                   designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity, ""));
}

std::string AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringHeatingOperation() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateMethodDuringHeatingOperation(
  const std::string& supplyAirFlowRateMethodDuringHeatingOperation) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, supplyAirFlowRateMethodDuringHeatingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateMethodDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitarySystem_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRatePerFloorAreaduringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea, true);
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(double supplyAirFlowRatePerFloorAreaduringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea, supplyAirFlowRatePerFloorAreaduringHeatingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignHeatingSupplyAirFlowRate() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignHeatingSupplyAirFlowRate(double fractionofAutosizedDesignHeatingSupplyAirFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate,
                   fractionofAutosizedDesignHeatingSupplyAirFlowRate);
}

void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignHeatingSupplyAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity, true);
}

bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(
  double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity,
                   designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity, ""));
}

std::string AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(const std::string& noCoolHeatMethod) {
  return setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, noCoolHeatMethod);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(double supplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitarySystem_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea, true);
}

bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(
  double supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea,
                   supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
  double fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate,
                   fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate, ""));
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
  double fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate,
                   fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate, ""));
}

boost::optional<double>
  AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, true);
}

bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
  double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation,
                   designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, ""));
}

boost::optional<double>
  AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, true);
}

bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
  double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation,
                   designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired);
}

void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, ""));
}

bool AirLoopHVACUnitarySystem_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed, true)) {
    return openstudio::istringEqual(*value, "yes");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
  const bool result = setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

boost::optional<double> AirLoopHVACUnitarySystem_Impl::maximumSupplyAirTemperature() const {
  return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, true);
}

bool AirLoopHVACUnitarySystem_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature);
}

bool AirLoopHVACUnitarySystem_Impl::isMaximumSupplyAirTemperatureAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitarySystem_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
}

void AirLoopHVACUnitarySystem_Impl::resetMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, ""));
}

void AirLoopHVACUnitarySystem_Impl::autosizeMaximumSupplyAirTemperature() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, "autosize"));
}

double AirLoopHVACUnitarySystem_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  const auto value =
    getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

bool AirLoopHVACUnitarySystem_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

void AirLoopHVACUnitarySystem_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, ""));
}

double AirLoopHVACUnitarySystem_Impl::ancilliaryOnCycleElectricPower() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isAncilliaryOnCycleElectricPowerDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower);
}

bool AirLoopHVACUnitarySystem_Impl::setAncilliaryOnCycleElectricPower(double ancilliaryOnCycleElectricPower) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, ancilliaryOnCycleElectricPower);
}

void AirLoopHVACUnitarySystem_Impl::resetAncilliaryOnCycleElectricPower() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, ""));
}

double AirLoopHVACUnitarySystem_Impl::ancilliaryOffCycleElectricPower() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitarySystem_Impl::isAncilliaryOffCycleElectricPowerDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower);
}

bool AirLoopHVACUnitarySystem_Impl::setAncilliaryOffCycleElectricPower(double ancilliaryOffCycleElectricPower) {
  return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, ancilliaryOffCycleElectricPower);
}

void AirLoopHVACUnitarySystem_Impl::resetAncilliaryOffCycleElectricPower() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, ""));
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::controlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::controlTypeValues();
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::dehumidificationControlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::dehumidificationControlTypeValues();
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::fanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::fanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::latentLoadControlValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::latentLoadControlValues();
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringCoolingOperationValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringCoolingOperationValues();
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringHeatingOperationValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringHeatingOperationValues();
}

std::vector<std::string> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues() const {
  return openstudio::epmodel::AirLoopHVACUnitarySystem::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
