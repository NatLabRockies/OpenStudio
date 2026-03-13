/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir_Impl.hpp"

#include "Model.hpp"
#include "Node.hpp"
#include "Loop/AirLoopHVAC.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatPump_AirToAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitaryHeatPumpAirToAir::AirLoopHVACUnitaryHeatPumpAirToAir(const Model& model)
  : StraightComponent(AirLoopHVACUnitaryHeatPumpAirToAir::iddObjectType(), model) {
  // Mirror model constructor behavior for required scalar initialization.
  OS_ASSERT(setDXHeatingCoilSizingRatio(1.0));
}

AirLoopHVACUnitaryHeatPumpAirToAir::AirLoopHVACUnitaryHeatPumpAirToAir(
  std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatPumpAirToAir::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::addToNode(Node& node) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->addToNode(node);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir::validFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir::validDehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
    supplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeSupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFlowRateDuringHeatingOperation(double n2) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(n2);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeSupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
    maximumSupplyAirTemperaturefromSupplementalHeater);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
}

double AirLoopHVACUnitaryHeatPumpAirToAir::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir::fanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->fanPlacement();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isFanPlacementDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isFanPlacementDefaulted();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setFanPlacement(const std::string& fanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setFanPlacement(fanPlacement);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetFanPlacement() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetFanPlacement();
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir::dehumidificationControlType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->dehumidificationControlType();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isDehumidificationControlTypeDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isDehumidificationControlTypeDefaulted();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetDehumidificationControlType() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetDehumidificationControlType();
}

double AirLoopHVACUnitaryHeatPumpAirToAir::dXHeatingCoilSizingRatio() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->dXHeatingCoilSizingRatio();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirLoopHVACUnitaryHeatPumpAirToAir_Impl::inletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AirInletNodeName;
}

unsigned AirLoopHVACUnitaryHeatPumpAirToAir_Impl::outletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AirOutletNodeName;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFlowRateDuringHeatingOperation(double n2) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, n2);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate,
                   supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  const bool result = setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                maximumSupplyAirTemperaturefromSupplementalHeater);
  OS_ASSERT(result);
  return result;
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "autosize"));
}

double AirLoopHVACUnitaryHeatPumpAirToAir_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
  OS_ASSERT(
    setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, ""));
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir_Impl::fanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isFanPlacementDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setFanPlacement(const std::string& fanPlacement) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, fanPlacement);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetFanPlacement() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, ""));
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isDehumidificationControlTypeDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, dehumidificationControlType);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetDehumidificationControlType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, ""));
}

double AirLoopHVACUnitaryHeatPumpAirToAir_Impl::dXHeatingCoilSizingRatio() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DXHeatingCoilSizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::validFanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpAirToAir::validFanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::validDehumidificationControlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpAirToAir::validDehumidificationControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
