/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(const Model& model)
  : StraightComponent(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::iddObjectType(), model) {
  // Mirror model scalar constructor defaults while excluding relationship fields.
  OS_ASSERT(setSupplyAirFanPlacement("DrawThrough"));
  OS_ASSERT(setDXHeatingCoilSizingRatio(1.0));
  autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(21.0));
  OS_ASSERT(setAuxiliaryOnCycleElectricPower(0.0));
  OS_ASSERT(setAuxiliaryOffCycleElectricPower(0.0));
  OS_ASSERT(setDesignHeatRecoveryWaterFlowRate(0.0));
  OS_ASSERT(setMaximumTemperatureforHeatRecovery(80.0));
  autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  OS_ASSERT(setNumberofSpeedsforHeating(2));
  OS_ASSERT(setNumberofSpeedsforCooling(2));
  autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();
  autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();
  autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();
  autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();
}

AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(
  std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::addToNode(Node& node) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->addToNode(node);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement);
}

std::string AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplyAirFanPlacement();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplyAirFanPlacement(supplyAirFanPlacement);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::dXHeatingCoilSizingRatio() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->dXHeatingCoilSizingRatio();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
    maximumSupplyAirTemperaturefromSupplementalHeater);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::auxiliaryOnCycleElectricPower() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->auxiliaryOnCycleElectricPower();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setAuxiliaryOnCycleElectricPower(double auxiliaryOnCycleElectricPower) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setAuxiliaryOnCycleElectricPower(auxiliaryOnCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::auxiliaryOffCycleElectricPower() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->auxiliaryOffCycleElectricPower();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setAuxiliaryOffCycleElectricPower(double auxiliaryOffCycleElectricPower) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setAuxiliaryOffCycleElectricPower(auxiliaryOffCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::designHeatRecoveryWaterFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->designHeatRecoveryWaterFlowRate();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::maximumTemperatureforHeatRecovery() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->maximumTemperatureforHeatRecovery();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setMaximumTemperatureforHeatRecovery(double maximumTemperatureforHeatRecovery) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setMaximumTemperatureforHeatRecovery(maximumTemperatureforHeatRecovery);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::numberofSpeedsforHeating() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->numberofSpeedsforHeating();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setNumberofSpeedsforHeating(int numberofSpeedsforHeating) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setNumberofSpeedsforHeating(numberofSpeedsforHeating);
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::numberofSpeedsforCooling() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->numberofSpeedsforCooling();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setNumberofSpeedsforCooling(int numberofSpeedsforCooling) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setNumberofSpeedsforCooling(numberofSpeedsforCooling);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed1SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed1SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed1SupplyAirFlowRateDuringHeatingOperation(
  double speed1SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed1SupplyAirFlowRateDuringHeatingOperation(
    speed1SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed2SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed2SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed2SupplyAirFlowRateDuringHeatingOperation(
  double speed2SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed2SupplyAirFlowRateDuringHeatingOperation(
    speed2SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed3SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed3SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed3SupplyAirFlowRateDuringHeatingOperation(
  double speed3SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed3SupplyAirFlowRateDuringHeatingOperation(
    speed3SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed4SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed4SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed4SupplyAirFlowRateDuringHeatingOperation(
  double speed4SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed4SupplyAirFlowRateDuringHeatingOperation(
    speed4SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed1SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed1SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed1SupplyAirFlowRateDuringCoolingOperation(
  double speed1SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed1SupplyAirFlowRateDuringCoolingOperation(
    speed1SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed2SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed2SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed2SupplyAirFlowRateDuringCoolingOperation(
  double speed2SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed2SupplyAirFlowRateDuringCoolingOperation(
    speed2SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed3SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed3SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed3SupplyAirFlowRateDuringCoolingOperation(
  double speed3SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed3SupplyAirFlowRateDuringCoolingOperation(
    speed3SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed4SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed4SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed4SupplyAirFlowRateDuringCoolingOperation(
  double speed4SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed4SupplyAirFlowRateDuringCoolingOperation(
    speed4SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::inletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirInletNodeName;
}

unsigned AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::outletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirOutletNodeName;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

std::string AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement, supplyAirFanPlacement);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::dXHeatingCoilSizingRatio() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DXHeatingCoilSizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                             true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                   maximumSupplyAirTemperaturefromSupplementalHeater);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  OS_ASSERT(
    setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "autosize"));
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  const auto value =
    getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
              true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::auxiliaryOnCycleElectricPower() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOnCycleElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setAuxiliaryOnCycleElectricPower(double auxiliaryOnCycleElectricPower) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOnCycleElectricPower,
                   auxiliaryOnCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::auxiliaryOffCycleElectricPower() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOffCycleElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setAuxiliaryOffCycleElectricPower(double auxiliaryOffCycleElectricPower) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOffCycleElectricPower,
                   auxiliaryOffCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::designHeatRecoveryWaterFlowRate() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DesignHeatRecoveryWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DesignHeatRecoveryWaterFlowRate,
                   designHeatRecoveryWaterFlowRate);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maximumTemperatureforHeatRecovery() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumTemperatureforHeatRecovery, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setMaximumTemperatureforHeatRecovery(double maximumTemperatureforHeatRecovery) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumTemperatureforHeatRecovery,
                   maximumTemperatureforHeatRecovery);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate,
                   supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, "autosize"));
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::numberofSpeedsforHeating() const {
  const auto value = getInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforHeating, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setNumberofSpeedsforHeating(int numberofSpeedsforHeating) {
  return setInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforHeating, numberofSpeedsforHeating);
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::numberofSpeedsforCooling() const {
  const auto value = getInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforCooling, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setNumberofSpeedsforCooling(int numberofSpeedsforCooling) {
  return setInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforCooling, numberofSpeedsforCooling);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed1SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed1SupplyAirFlowRateDuringHeatingOperation(
  double speed1SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate,
                   speed1SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed2SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed2SupplyAirFlowRateDuringHeatingOperation(
  double speed2SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate,
                   speed2SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed3SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed3SupplyAirFlowRateDuringHeatingOperation(
  double speed3SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate,
                   speed3SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed4SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed4SupplyAirFlowRateDuringHeatingOperation(
  double speed4SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate,
                   speed4SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed1SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed1SupplyAirFlowRateDuringCoolingOperation(
  double speed1SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate,
                   speed1SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed2SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed2SupplyAirFlowRateDuringCoolingOperation(
  double speed2SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate,
                   speed2SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed3SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed3SupplyAirFlowRateDuringCoolingOperation(
  double speed3SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate,
                   speed3SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed4SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed4SupplyAirFlowRateDuringCoolingOperation(
  double speed4SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate,
                   speed4SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, "autosize"));
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanPlacementValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
