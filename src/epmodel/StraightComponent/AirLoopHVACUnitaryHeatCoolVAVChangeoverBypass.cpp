/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model)
  : StraightComponent(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType(), model) {
  // Keep required scalar fields populated for strict non-optional getters.
  OS_ASSERT(setSupplyAirFanPlacement("DrawThrough"));
  OS_ASSERT(setPriorityControlMode("ZonePriority"));
  OS_ASSERT(setMinimumOutletAirTemperatureDuringCoolingOperation(8.0));
  OS_ASSERT(setMaximumOutletAirTemperatureDuringHeatingOperation(50.0));
  OS_ASSERT(setDehumidificationControlType("None"));
  OS_ASSERT(setMinimumRuntimeBeforeOperatingModeChange(0.0));

  // Mirror model default constructor autosize behavior for scalar flow-rate fields.
  autosizeSystemAirFlowRateDuringCoolingOperation();
  autosizeSystemAirFlowRateDuringHeatingOperation();
  autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
  autosizeOutdoorAirFlowRateDuringCoolingOperation();
  autosizeOutdoorAirFlowRateDuringHeatingOperation();
  autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(
  std::shared_ptr<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass;
}

std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::priorityControlModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::addToNode(Node& node) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->addToNode(node);
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::systemAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->systemAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isSystemAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isSystemAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSystemAirFlowRateDuringCoolingOperation(double systemAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSystemAirFlowRateDuringCoolingOperation(
    systemAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeSystemAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeSystemAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::systemAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->systemAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isSystemAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isSystemAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSystemAirFlowRateDuringHeatingOperation(double systemAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSystemAirFlowRateDuringHeatingOperation(
    systemAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeSystemAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeSystemAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::systemAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->systemAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double systemAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(
    systemAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateDuringCoolingOperation(
  double outdoorAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
    outdoorAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateDuringHeatingOperation(
  double outdoorAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
    outdoorAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->supplyAirFanPlacement();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSupplyAirFanPlacement(supplyAirFanPlacement);
}

std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::priorityControlMode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->priorityControlMode();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setPriorityControlMode(const std::string& priorityControlMode) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setPriorityControlMode(priorityControlMode);
}

double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::minimumOutletAirTemperatureDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->minimumOutletAirTemperatureDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setMinimumOutletAirTemperatureDuringCoolingOperation(
  double minimumOutletAirTemperatureDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setMinimumOutletAirTemperatureDuringCoolingOperation(
    minimumOutletAirTemperatureDuringCoolingOperation);
}

double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::maximumOutletAirTemperatureDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->maximumOutletAirTemperatureDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setMaximumOutletAirTemperatureDuringHeatingOperation(
  double maximumOutletAirTemperatureDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setMaximumOutletAirTemperatureDuringHeatingOperation(
    maximumOutletAirTemperatureDuringHeatingOperation);
}

std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::dehumidificationControlType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->dehumidificationControlType();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::minimumRuntimeBeforeOperatingModeChange() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->minimumRuntimeBeforeOperatingModeChange();
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setMinimumRuntimeBeforeOperatingModeChange(double runtime) {
  return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setMinimumRuntimeBeforeOperatingModeChange(runtime);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::inletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AirInletNodeName;
}

unsigned AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AirOutletNodeName;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  return StraightComponent_Impl::addToNode(node);
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::systemAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isSystemAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSystemAirFlowRateDuringCoolingOperation(double systemAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate,
                   systemAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeSystemAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::systemAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isSystemAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSystemAirFlowRateDuringHeatingOperation(double systemAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate,
                   systemAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeSystemAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::systemAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double systemAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate,
                   systemAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate,
                   outdoorAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate,
                   outdoorAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate,
                   outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, "autosize"));
}

std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::supplyAirFanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement, supplyAirFanPlacement);
}

std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::priorityControlMode() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setPriorityControlMode(const std::string& priorityControlMode) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode, priorityControlMode);
}

double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::minimumOutletAirTemperatureDuringCoolingOperation() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumOutletAirTemperatureDuringCoolingOperation,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setMinimumOutletAirTemperatureDuringCoolingOperation(
  double minimumOutletAirTemperatureDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumOutletAirTemperatureDuringCoolingOperation,
                   minimumOutletAirTemperatureDuringCoolingOperation);
}

double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::maximumOutletAirTemperatureDuringHeatingOperation() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MaximumOutletAirTemperatureDuringHeatingOperation,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setMaximumOutletAirTemperatureDuringHeatingOperation(
  double maximumOutletAirTemperatureDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MaximumOutletAirTemperatureDuringHeatingOperation,
                   maximumOutletAirTemperatureDuringHeatingOperation);
}

std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType,
                   dehumidificationControlType);
}

double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::minimumRuntimeBeforeOperatingModeChange() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumRuntimeBeforeOperatingModeChange, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setMinimumRuntimeBeforeOperatingModeChange(double runtime) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumRuntimeBeforeOperatingModeChange, runtime);
}

std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::supplyAirFanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::priorityControlModeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::priorityControlModeValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::dehumidificationControlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::dehumidificationControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
