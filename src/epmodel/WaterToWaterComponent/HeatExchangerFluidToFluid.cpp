/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatExchangerFluidToFluid.hpp"
#include "WaterToWaterComponent/HeatExchangerFluidToFluid_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/HeatExchanger_FluidToFluid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

HeatExchangerFluidToFluid::HeatExchangerFluidToFluid(const Model& model)
  : WaterToWaterComponent(HeatExchangerFluidToFluid::iddObjectType(), model) {
  // Keep required scalar fields populated for strict non-optional getters.
  autosizeLoopDemandSideDesignFlowRate();
  autosizeLoopSupplySideDesignFlowRate();
  OS_ASSERT(setHeatExchangeModelType("Ideal"));
  autosizeHeatExchangerUFactorTimesAreaValue();
  OS_ASSERT(setControlType("UncontrolledOn"));
  OS_ASSERT(setMinimumTemperatureDifferencetoActivateHeatExchanger(0.01));
  OS_ASSERT(setHeatTransferMeteringEndUseType("LoopToLoop"));
  OS_ASSERT(setComponentOverrideCoolingControlTemperatureMode("Loop"));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setOperationMinimumTemperatureLimit(0.0));
  OS_ASSERT(setOperationMaximumTemperatureLimit(100.0));
}

HeatExchangerFluidToFluid::HeatExchangerFluidToFluid(std::shared_ptr<detail::HeatExchangerFluidToFluid_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType HeatExchangerFluidToFluid::iddObjectType() {
  return IddObjectType::HeatExchanger_FluidToFluid;
}

std::vector<std::string> HeatExchangerFluidToFluid::heatExchangeModelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatExchanger_FluidToFluidFields::HeatExchangeModelType);
}

std::vector<std::string> HeatExchangerFluidToFluid::controlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatExchanger_FluidToFluidFields::ControlType);
}

std::vector<std::string> HeatExchangerFluidToFluid::heatTransferMeteringEndUseTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType);
}

std::vector<std::string> HeatExchangerFluidToFluid::componentOverrideCoolingControlTemperatureModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode);
}

boost::optional<Schedule> HeatExchangerFluidToFluid::availabilitySchedule() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->availabilitySchedule();
}

bool HeatExchangerFluidToFluid::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setAvailabilitySchedule(schedule);
}

void HeatExchangerFluidToFluid::resetAvailabilitySchedule() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetAvailabilitySchedule();
}

boost::optional<double> HeatExchangerFluidToFluid::loopDemandSideDesignFlowRate() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->loopDemandSideDesignFlowRate();
}

bool HeatExchangerFluidToFluid::isLoopDemandSideDesignFlowRateAutosized() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isLoopDemandSideDesignFlowRateAutosized();
}

bool HeatExchangerFluidToFluid::setLoopDemandSideDesignFlowRate(double loopDemandSideDesignFlowRate) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setLoopDemandSideDesignFlowRate(loopDemandSideDesignFlowRate);
}

void HeatExchangerFluidToFluid::autosizeLoopDemandSideDesignFlowRate() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->autosizeLoopDemandSideDesignFlowRate();
}

boost::optional<double> HeatExchangerFluidToFluid::loopSupplySideDesignFlowRate() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->loopSupplySideDesignFlowRate();
}

bool HeatExchangerFluidToFluid::isLoopSupplySideDesignFlowRateAutosized() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isLoopSupplySideDesignFlowRateAutosized();
}

bool HeatExchangerFluidToFluid::setLoopSupplySideDesignFlowRate(double loopSupplySideDesignFlowRate) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setLoopSupplySideDesignFlowRate(loopSupplySideDesignFlowRate);
}

void HeatExchangerFluidToFluid::autosizeLoopSupplySideDesignFlowRate() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->autosizeLoopSupplySideDesignFlowRate();
}

std::string HeatExchangerFluidToFluid::heatExchangeModelType() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->heatExchangeModelType();
}

bool HeatExchangerFluidToFluid::isHeatExchangeModelTypeDefaulted() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isHeatExchangeModelTypeDefaulted();
}

bool HeatExchangerFluidToFluid::setHeatExchangeModelType(const std::string& heatExchangeModelType) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setHeatExchangeModelType(heatExchangeModelType);
}

void HeatExchangerFluidToFluid::resetHeatExchangeModelType() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetHeatExchangeModelType();
}

boost::optional<double> HeatExchangerFluidToFluid::heatExchangerUFactorTimesAreaValue() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->heatExchangerUFactorTimesAreaValue();
}

bool HeatExchangerFluidToFluid::isHeatExchangerUFactorTimesAreaValueAutosized() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isHeatExchangerUFactorTimesAreaValueAutosized();
}

bool HeatExchangerFluidToFluid::setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setHeatExchangerUFactorTimesAreaValue(heatExchangerUFactorTimesAreaValue);
}

void HeatExchangerFluidToFluid::autosizeHeatExchangerUFactorTimesAreaValue() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->autosizeHeatExchangerUFactorTimesAreaValue();
}

std::string HeatExchangerFluidToFluid::controlType() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->controlType();
}

bool HeatExchangerFluidToFluid::isControlTypeDefaulted() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isControlTypeDefaulted();
}

bool HeatExchangerFluidToFluid::setControlType(const std::string& controlType) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setControlType(controlType);
}

void HeatExchangerFluidToFluid::resetControlType() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetControlType();
}

double HeatExchangerFluidToFluid::minimumTemperatureDifferencetoActivateHeatExchanger() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->minimumTemperatureDifferencetoActivateHeatExchanger();
}

bool HeatExchangerFluidToFluid::isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted();
}

bool HeatExchangerFluidToFluid::setMinimumTemperatureDifferencetoActivateHeatExchanger(double minimumTemperatureDifferencetoActivateHeatExchanger) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setMinimumTemperatureDifferencetoActivateHeatExchanger(
    minimumTemperatureDifferencetoActivateHeatExchanger);
}

void HeatExchangerFluidToFluid::resetMinimumTemperatureDifferencetoActivateHeatExchanger() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetMinimumTemperatureDifferencetoActivateHeatExchanger();
}

std::string HeatExchangerFluidToFluid::heatTransferMeteringEndUseType() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->heatTransferMeteringEndUseType();
}

bool HeatExchangerFluidToFluid::isHeatTransferMeteringEndUseTypeDefaulted() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isHeatTransferMeteringEndUseTypeDefaulted();
}

bool HeatExchangerFluidToFluid::setHeatTransferMeteringEndUseType(const std::string& heatTransferMeteringEndUseType) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setHeatTransferMeteringEndUseType(heatTransferMeteringEndUseType);
}

void HeatExchangerFluidToFluid::resetHeatTransferMeteringEndUseType() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetHeatTransferMeteringEndUseType();
}

boost::optional<Node> HeatExchangerFluidToFluid::componentOverrideLoopSupplySideInletNode() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->componentOverrideLoopSupplySideInletNode();
}

bool HeatExchangerFluidToFluid::setComponentOverrideLoopSupplySideInletNode(const Node& node) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setComponentOverrideLoopSupplySideInletNode(node);
}

void HeatExchangerFluidToFluid::resetComponentOverrideLoopSupplySideInletNode() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetComponentOverrideLoopSupplySideInletNode();
}

boost::optional<Node> HeatExchangerFluidToFluid::componentOverrideLoopDemandSideInletNode() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->componentOverrideLoopDemandSideInletNode();
}

bool HeatExchangerFluidToFluid::setComponentOverrideLoopDemandSideInletNode(const Node& node) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setComponentOverrideLoopDemandSideInletNode(node);
}

void HeatExchangerFluidToFluid::resetComponentOverrideLoopDemandSideInletNode() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetComponentOverrideLoopDemandSideInletNode();
}

std::string HeatExchangerFluidToFluid::componentOverrideCoolingControlTemperatureMode() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->componentOverrideCoolingControlTemperatureMode();
}

bool HeatExchangerFluidToFluid::isComponentOverrideCoolingControlTemperatureModeDefaulted() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isComponentOverrideCoolingControlTemperatureModeDefaulted();
}

bool HeatExchangerFluidToFluid::setComponentOverrideCoolingControlTemperatureMode(
  const std::string& componentOverrideCoolingControlTemperatureMode) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setComponentOverrideCoolingControlTemperatureMode(
    componentOverrideCoolingControlTemperatureMode);
}

void HeatExchangerFluidToFluid::resetComponentOverrideCoolingControlTemperatureMode() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetComponentOverrideCoolingControlTemperatureMode();
}

double HeatExchangerFluidToFluid::sizingFactor() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->sizingFactor();
}

bool HeatExchangerFluidToFluid::isSizingFactorDefaulted() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->isSizingFactorDefaulted();
}

bool HeatExchangerFluidToFluid::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setSizingFactor(sizingFactor);
}

void HeatExchangerFluidToFluid::resetSizingFactor() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetSizingFactor();
}

boost::optional<double> HeatExchangerFluidToFluid::operationMinimumTemperatureLimit() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->operationMinimumTemperatureLimit();
}

bool HeatExchangerFluidToFluid::setOperationMinimumTemperatureLimit(double operationMinimumTemperatureLimit) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setOperationMinimumTemperatureLimit(operationMinimumTemperatureLimit);
}

void HeatExchangerFluidToFluid::resetOperationMinimumTemperatureLimit() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetOperationMinimumTemperatureLimit();
}

boost::optional<double> HeatExchangerFluidToFluid::operationMaximumTemperatureLimit() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->operationMaximumTemperatureLimit();
}

bool HeatExchangerFluidToFluid::setOperationMaximumTemperatureLimit(double operationMaximumTemperatureLimit) {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->setOperationMaximumTemperatureLimit(operationMaximumTemperatureLimit);
}

void HeatExchangerFluidToFluid::resetOperationMaximumTemperatureLimit() {
  getImpl<detail::HeatExchangerFluidToFluid_Impl>()->resetOperationMaximumTemperatureLimit();
}

boost::optional<double> HeatExchangerFluidToFluid::autosizedLoopDemandSideDesignFlowRate() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->autosizedLoopDemandSideDesignFlowRate();
}

boost::optional<double> HeatExchangerFluidToFluid::autosizedLoopSupplySideDesignFlowRate() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->autosizedLoopSupplySideDesignFlowRate();
}

boost::optional<double> HeatExchangerFluidToFluid::autosizedHeatExchangerUFactorTimesAreaValue() const {
  return getImpl<detail::HeatExchangerFluidToFluid_Impl>()->autosizedHeatExchangerUFactorTimesAreaValue();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<Schedule> HeatExchangerFluidToFluid_Impl::availabilitySchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::HeatExchanger_FluidToFluidFields::AvailabilityScheduleName);
}

bool HeatExchangerFluidToFluid_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::HeatExchanger_FluidToFluidFields::AvailabilityScheduleName, "HeatExchangerFluidToFluid", "Availability", schedule);
}

void HeatExchangerFluidToFluid_Impl::resetAvailabilitySchedule() {
  OS_ASSERT(setString(openstudio::HeatExchanger_FluidToFluidFields::AvailabilityScheduleName, ""));
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::loopDemandSideDesignFlowRate() const {
  return getDouble(openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideDesignFlowRate, true);
}

bool HeatExchangerFluidToFluid_Impl::isLoopDemandSideDesignFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideDesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatExchangerFluidToFluid_Impl::setLoopDemandSideDesignFlowRate(double loopDemandSideDesignFlowRate) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideDesignFlowRate, loopDemandSideDesignFlowRate);
}

void HeatExchangerFluidToFluid_Impl::autosizeLoopDemandSideDesignFlowRate() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideDesignFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::loopSupplySideDesignFlowRate() const {
  return getDouble(openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideDesignFlowRate, true);
}

bool HeatExchangerFluidToFluid_Impl::isLoopSupplySideDesignFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideDesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatExchangerFluidToFluid_Impl::setLoopSupplySideDesignFlowRate(double loopSupplySideDesignFlowRate) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideDesignFlowRate, loopSupplySideDesignFlowRate);
}

void HeatExchangerFluidToFluid_Impl::autosizeLoopSupplySideDesignFlowRate() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideDesignFlowRate, "Autosize");
  OS_ASSERT(result);
}

std::string HeatExchangerFluidToFluid_Impl::heatExchangeModelType() const {
  const auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangeModelType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatExchangerFluidToFluid_Impl::isHeatExchangeModelTypeDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangeModelType);
}

bool HeatExchangerFluidToFluid_Impl::setHeatExchangeModelType(const std::string& heatExchangeModelType) {
  return setString(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangeModelType, heatExchangeModelType);
}

void HeatExchangerFluidToFluid_Impl::resetHeatExchangeModelType() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangeModelType, "");
  OS_ASSERT(result);
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::heatExchangerUFactorTimesAreaValue() const {
  return getDouble(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangerUFactorTimesAreaValue, true);
}

bool HeatExchangerFluidToFluid_Impl::isHeatExchangerUFactorTimesAreaValueAutosized() const {
  if (auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangerUFactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatExchangerFluidToFluid_Impl::setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangerUFactorTimesAreaValue, heatExchangerUFactorTimesAreaValue);
}

void HeatExchangerFluidToFluid_Impl::autosizeHeatExchangerUFactorTimesAreaValue() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::HeatExchangerUFactorTimesAreaValue, "Autosize");
  OS_ASSERT(result);
}

std::string HeatExchangerFluidToFluid_Impl::controlType() const {
  const auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatExchangerFluidToFluid_Impl::isControlTypeDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_FluidToFluidFields::ControlType);
}

bool HeatExchangerFluidToFluid_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::HeatExchanger_FluidToFluidFields::ControlType, controlType);
}

void HeatExchangerFluidToFluid_Impl::resetControlType() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::ControlType, "");
  OS_ASSERT(result);
}

double HeatExchangerFluidToFluid_Impl::minimumTemperatureDifferencetoActivateHeatExchanger() const {
  const auto value = getDouble(openstudio::HeatExchanger_FluidToFluidFields::MinimumTemperatureDifferencetoActivateHeatExchanger, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatExchangerFluidToFluid_Impl::isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_FluidToFluidFields::MinimumTemperatureDifferencetoActivateHeatExchanger);
}

bool HeatExchangerFluidToFluid_Impl::setMinimumTemperatureDifferencetoActivateHeatExchanger(
  double minimumTemperatureDifferencetoActivateHeatExchanger) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::MinimumTemperatureDifferencetoActivateHeatExchanger,
                   minimumTemperatureDifferencetoActivateHeatExchanger);
}

void HeatExchangerFluidToFluid_Impl::resetMinimumTemperatureDifferencetoActivateHeatExchanger() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::MinimumTemperatureDifferencetoActivateHeatExchanger, "");
  OS_ASSERT(result);
}

std::string HeatExchangerFluidToFluid_Impl::heatTransferMeteringEndUseType() const {
  const auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatExchangerFluidToFluid_Impl::isHeatTransferMeteringEndUseTypeDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType);
}

bool HeatExchangerFluidToFluid_Impl::setHeatTransferMeteringEndUseType(const std::string& heatTransferMeteringEndUseType) {
  return setString(openstudio::HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType, heatTransferMeteringEndUseType);
}

void HeatExchangerFluidToFluid_Impl::resetHeatTransferMeteringEndUseType() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::HeatTransferMeteringEndUseType, "");
  OS_ASSERT(result);
}

boost::optional<Node> HeatExchangerFluidToFluid_Impl::componentOverrideLoopSupplySideInletNode() const {
  return getObject<ModelObject>().getModelObjectTarget<Node>(
    openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideLoopSupplySideInletNodeName);
}

bool HeatExchangerFluidToFluid_Impl::setComponentOverrideLoopSupplySideInletNode(const Node& node) {
  return setPointer(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideLoopSupplySideInletNodeName, node.handle());
}

void HeatExchangerFluidToFluid_Impl::resetComponentOverrideLoopSupplySideInletNode() {
  OS_ASSERT(setPointer(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideLoopSupplySideInletNodeName, Handle(), false));
}

boost::optional<Node> HeatExchangerFluidToFluid_Impl::componentOverrideLoopDemandSideInletNode() const {
  return getObject<ModelObject>().getModelObjectTarget<Node>(
    openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideLoopDemandSideInletNodeName);
}

bool HeatExchangerFluidToFluid_Impl::setComponentOverrideLoopDemandSideInletNode(const Node& node) {
  return setPointer(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideLoopDemandSideInletNodeName, node.handle());
}

void HeatExchangerFluidToFluid_Impl::resetComponentOverrideLoopDemandSideInletNode() {
  OS_ASSERT(setPointer(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideLoopDemandSideInletNodeName, Handle(), false));
}

std::string HeatExchangerFluidToFluid_Impl::componentOverrideCoolingControlTemperatureMode() const {
  const auto value = getString(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatExchangerFluidToFluid_Impl::isComponentOverrideCoolingControlTemperatureModeDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode);
}

bool HeatExchangerFluidToFluid_Impl::setComponentOverrideCoolingControlTemperatureMode(
  const std::string& componentOverrideCoolingControlTemperatureMode) {
  return setString(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode,
                   componentOverrideCoolingControlTemperatureMode);
}

void HeatExchangerFluidToFluid_Impl::resetComponentOverrideCoolingControlTemperatureMode() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::ComponentOverrideCoolingControlTemperatureMode, "");
  OS_ASSERT(result);
}

double HeatExchangerFluidToFluid_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatExchanger_FluidToFluidFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatExchangerFluidToFluid_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::HeatExchanger_FluidToFluidFields::SizingFactor);
}

bool HeatExchangerFluidToFluid_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::SizingFactor, sizingFactor);
}

void HeatExchangerFluidToFluid_Impl::resetSizingFactor() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::SizingFactor, "");
  OS_ASSERT(result);
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::operationMinimumTemperatureLimit() const {
  return getDouble(openstudio::HeatExchanger_FluidToFluidFields::OperationMinimumTemperatureLimit, true);
}

bool HeatExchangerFluidToFluid_Impl::setOperationMinimumTemperatureLimit(double operationMinimumTemperatureLimit) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::OperationMinimumTemperatureLimit, operationMinimumTemperatureLimit);
}

void HeatExchangerFluidToFluid_Impl::resetOperationMinimumTemperatureLimit() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::OperationMinimumTemperatureLimit, "");
  OS_ASSERT(result);
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::operationMaximumTemperatureLimit() const {
  return getDouble(openstudio::HeatExchanger_FluidToFluidFields::OperationMaximumTemperatureLimit, true);
}

bool HeatExchangerFluidToFluid_Impl::setOperationMaximumTemperatureLimit(double operationMaximumTemperatureLimit) {
  return setDouble(openstudio::HeatExchanger_FluidToFluidFields::OperationMaximumTemperatureLimit, operationMaximumTemperatureLimit);
}

void HeatExchangerFluidToFluid_Impl::resetOperationMaximumTemperatureLimit() {
  bool result = setString(openstudio::HeatExchanger_FluidToFluidFields::OperationMaximumTemperatureLimit, "");
  OS_ASSERT(result);
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::autosizedLoopDemandSideDesignFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::autosizedLoopSupplySideDesignFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatExchangerFluidToFluid_Impl::autosizedHeatExchangerUFactorTimesAreaValue() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

std::vector<std::string> HeatExchangerFluidToFluid_Impl::heatExchangeModelTypeValues() const {
  return openstudio::epmodel::HeatExchangerFluidToFluid::heatExchangeModelTypeValues();
}

std::vector<std::string> HeatExchangerFluidToFluid_Impl::controlTypeValues() const {
  return openstudio::epmodel::HeatExchangerFluidToFluid::controlTypeValues();
}

std::vector<std::string> HeatExchangerFluidToFluid_Impl::heatTransferMeteringEndUseTypeValues() const {
  return openstudio::epmodel::HeatExchangerFluidToFluid::heatTransferMeteringEndUseTypeValues();
}

std::vector<std::string> HeatExchangerFluidToFluid_Impl::componentOverrideCoolingControlTemperatureModeValues() const {
  return openstudio::epmodel::HeatExchangerFluidToFluid::componentOverrideCoolingControlTemperatureModeValues();
}

openstudio::ComponentType HeatExchangerFluidToFluid_Impl::componentType() const {
  const auto currentControlType = controlType();

  if (openstudio::istringEqual(currentControlType, "HeatingSetpointModulated")
      || openstudio::istringEqual(currentControlType, "HeatingSetpointOnOff")) {
    return openstudio::ComponentType::Heating;
  }

  if (openstudio::istringEqual(currentControlType, "CoolingSetpointModulated")
      || openstudio::istringEqual(currentControlType, "CoolingSetpointOnOff")
      || openstudio::istringEqual(currentControlType, "CoolingDifferentialOnOff")
      || openstudio::istringEqual(currentControlType, "CoolingSetpointOnOffWithComponentOverride")) {
    return openstudio::ComponentType::Cooling;
  }

  if (openstudio::istringEqual(currentControlType, "DualDeadbandSetpointModulated")
      || openstudio::istringEqual(currentControlType, "DualDeadbandSetpointOnOff")) {
    return openstudio::ComponentType::Both;
  }

  if (openstudio::istringEqual(currentControlType, "UncontrolledOn")) {
    if (auto secondaryLoop = secondaryPlantLoop()) {
      return secondaryLoop->componentType();
    }
    return openstudio::ComponentType::None;
  }

  return openstudio::ComponentType::Both;
}

std::vector<openstudio::FuelType> HeatExchangerFluidToFluid_Impl::coolingFuelTypes() const {
  const auto currentControlType = controlType();
  if (openstudio::istringEqual(currentControlType, "HeatingSetpointModulated")
      || openstudio::istringEqual(currentControlType, "HeatingSetpointOnOff")) {
    return {};
  }

  if (auto secondaryLoop = secondaryPlantLoop()) {
    return secondaryLoop->coolingFuelTypes();
  }

  return {};
}

std::vector<openstudio::FuelType> HeatExchangerFluidToFluid_Impl::heatingFuelTypes() const {
  const auto currentControlType = controlType();
  if (openstudio::istringEqual(currentControlType, "CoolingSetpointModulated")
      || openstudio::istringEqual(currentControlType, "CoolingSetpointOnOff")
      || openstudio::istringEqual(currentControlType, "CoolingDifferentialOnOff")
      || openstudio::istringEqual(currentControlType, "CoolingSetpointOnOffWithComponentOverride")) {
    return {};
  }

  if (auto secondaryLoop = secondaryPlantLoop()) {
    return secondaryLoop->heatingFuelTypes();
  }

  return {};
}

std::vector<openstudio::AppGFuelType> HeatExchangerFluidToFluid_Impl::appGHeatingFuelTypes() const {
  const auto currentControlType = controlType();
  if (openstudio::istringEqual(currentControlType, "CoolingSetpointModulated")
      || openstudio::istringEqual(currentControlType, "CoolingSetpointOnOff")
      || openstudio::istringEqual(currentControlType, "CoolingDifferentialOnOff")
      || openstudio::istringEqual(currentControlType, "CoolingSetpointOnOffWithComponentOverride")) {
    return {};
  }

  if (auto secondaryLoop = secondaryPlantLoop()) {
    return secondaryLoop->appGHeatingFuelTypes();
  }

  return {};
}

unsigned HeatExchangerFluidToFluid_Impl::supplyInletPort() const {
  return openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideInletNodeName;
}

unsigned HeatExchangerFluidToFluid_Impl::supplyOutletPort() const {
  return openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideOutletNodeName;
}

unsigned HeatExchangerFluidToFluid_Impl::demandInletPort() const {
  return openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideInletNodeName;
}

unsigned HeatExchangerFluidToFluid_Impl::demandOutletPort() const {
  return openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
