/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DesignSpecificationAirTerminalSizing.hpp"
#include "DesignSpecificationAirTerminalSizing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DesignSpecification_AirTerminal_Sizing_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DesignSpecificationAirTerminalSizing::DesignSpecificationAirTerminalSizing(const Model& model)
  : ModelObject(DesignSpecificationAirTerminalSizing::iddObjectType(), model) {}

DesignSpecificationAirTerminalSizing::DesignSpecificationAirTerminalSizing(std::shared_ptr<detail::DesignSpecificationAirTerminalSizing_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DesignSpecificationAirTerminalSizing::iddObjectType() {
  return IddObjectType::DesignSpecification_AirTerminal_Sizing;
}

double DesignSpecificationAirTerminalSizing::fractionofDesignCoolingLoad() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->fractionofDesignCoolingLoad();
}

bool DesignSpecificationAirTerminalSizing::isFractionofDesignCoolingLoadDefaulted() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->isFractionofDesignCoolingLoadDefaulted();
}

bool DesignSpecificationAirTerminalSizing::setFractionofDesignCoolingLoad(double fractionofDesignCoolingLoad) {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->setFractionofDesignCoolingLoad(fractionofDesignCoolingLoad);
}

void DesignSpecificationAirTerminalSizing::resetFractionofDesignCoolingLoad() {
  getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->resetFractionofDesignCoolingLoad();
}

double DesignSpecificationAirTerminalSizing::coolingDesignSupplyAirTemperatureDifferenceRatio() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->coolingDesignSupplyAirTemperatureDifferenceRatio();
}

bool DesignSpecificationAirTerminalSizing::isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted();
}

bool DesignSpecificationAirTerminalSizing::setCoolingDesignSupplyAirTemperatureDifferenceRatio(double coolingDesignSupplyAirTemperatureDifferenceRatio) {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->setCoolingDesignSupplyAirTemperatureDifferenceRatio(
    coolingDesignSupplyAirTemperatureDifferenceRatio);
}

void DesignSpecificationAirTerminalSizing::resetCoolingDesignSupplyAirTemperatureDifferenceRatio() {
  getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->resetCoolingDesignSupplyAirTemperatureDifferenceRatio();
}

double DesignSpecificationAirTerminalSizing::fractionofDesignHeatingLoad() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->fractionofDesignHeatingLoad();
}

bool DesignSpecificationAirTerminalSizing::isFractionofDesignHeatingLoadDefaulted() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->isFractionofDesignHeatingLoadDefaulted();
}

bool DesignSpecificationAirTerminalSizing::setFractionofDesignHeatingLoad(double fractionofDesignHeatingLoad) {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->setFractionofDesignHeatingLoad(fractionofDesignHeatingLoad);
}

void DesignSpecificationAirTerminalSizing::resetFractionofDesignHeatingLoad() {
  getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->resetFractionofDesignHeatingLoad();
}

double DesignSpecificationAirTerminalSizing::heatingDesignSupplyAirTemperatureDifferenceRatio() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->heatingDesignSupplyAirTemperatureDifferenceRatio();
}

bool DesignSpecificationAirTerminalSizing::isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted();
}

bool DesignSpecificationAirTerminalSizing::setHeatingDesignSupplyAirTemperatureDifferenceRatio(double heatingDesignSupplyAirTemperatureDifferenceRatio) {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->setHeatingDesignSupplyAirTemperatureDifferenceRatio(
    heatingDesignSupplyAirTemperatureDifferenceRatio);
}

void DesignSpecificationAirTerminalSizing::resetHeatingDesignSupplyAirTemperatureDifferenceRatio() {
  getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->resetHeatingDesignSupplyAirTemperatureDifferenceRatio();
}

double DesignSpecificationAirTerminalSizing::fractionofMinimumOutdoorAirFlow() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->fractionofMinimumOutdoorAirFlow();
}

bool DesignSpecificationAirTerminalSizing::isFractionofMinimumOutdoorAirFlowDefaulted() const {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->isFractionofMinimumOutdoorAirFlowDefaulted();
}

bool DesignSpecificationAirTerminalSizing::setFractionofMinimumOutdoorAirFlow(double fractionofMinimumOutdoorAirFlow) {
  return getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->setFractionofMinimumOutdoorAirFlow(fractionofMinimumOutdoorAirFlow);
}

void DesignSpecificationAirTerminalSizing::resetFractionofMinimumOutdoorAirFlow() {
  getImpl<detail::DesignSpecificationAirTerminalSizing_Impl>()->resetFractionofMinimumOutdoorAirFlow();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double DesignSpecificationAirTerminalSizing_Impl::fractionofDesignCoolingLoad() const {
  const auto value = getDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignCoolingLoad, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationAirTerminalSizing_Impl::isFractionofDesignCoolingLoadDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignCoolingLoad);
}

bool DesignSpecificationAirTerminalSizing_Impl::setFractionofDesignCoolingLoad(double fractionofDesignCoolingLoad) {
  return setDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignCoolingLoad, fractionofDesignCoolingLoad);
}

void DesignSpecificationAirTerminalSizing_Impl::resetFractionofDesignCoolingLoad() {
  OS_ASSERT(setString(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignCoolingLoad, ""));
}

double DesignSpecificationAirTerminalSizing_Impl::coolingDesignSupplyAirTemperatureDifferenceRatio() const {
  const auto value = getDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::CoolingDesignSupplyAirTemperatureDifferenceRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationAirTerminalSizing_Impl::isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_AirTerminal_SizingFields::CoolingDesignSupplyAirTemperatureDifferenceRatio);
}

bool DesignSpecificationAirTerminalSizing_Impl::setCoolingDesignSupplyAirTemperatureDifferenceRatio(
  double coolingDesignSupplyAirTemperatureDifferenceRatio) {
  return setDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::CoolingDesignSupplyAirTemperatureDifferenceRatio,
                   coolingDesignSupplyAirTemperatureDifferenceRatio);
}

void DesignSpecificationAirTerminalSizing_Impl::resetCoolingDesignSupplyAirTemperatureDifferenceRatio() {
  OS_ASSERT(setString(openstudio::DesignSpecification_AirTerminal_SizingFields::CoolingDesignSupplyAirTemperatureDifferenceRatio, ""));
}

double DesignSpecificationAirTerminalSizing_Impl::fractionofDesignHeatingLoad() const {
  const auto value = getDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignHeatingLoad, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationAirTerminalSizing_Impl::isFractionofDesignHeatingLoadDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignHeatingLoad);
}

bool DesignSpecificationAirTerminalSizing_Impl::setFractionofDesignHeatingLoad(double fractionofDesignHeatingLoad) {
  return setDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignHeatingLoad, fractionofDesignHeatingLoad);
}

void DesignSpecificationAirTerminalSizing_Impl::resetFractionofDesignHeatingLoad() {
  OS_ASSERT(setString(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofDesignHeatingLoad, ""));
}

double DesignSpecificationAirTerminalSizing_Impl::heatingDesignSupplyAirTemperatureDifferenceRatio() const {
  const auto value = getDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::HeatingDesignSupplyAirTemperatureDifferenceRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationAirTerminalSizing_Impl::isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_AirTerminal_SizingFields::HeatingDesignSupplyAirTemperatureDifferenceRatio);
}

bool DesignSpecificationAirTerminalSizing_Impl::setHeatingDesignSupplyAirTemperatureDifferenceRatio(
  double heatingDesignSupplyAirTemperatureDifferenceRatio) {
  return setDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::HeatingDesignSupplyAirTemperatureDifferenceRatio,
                   heatingDesignSupplyAirTemperatureDifferenceRatio);
}

void DesignSpecificationAirTerminalSizing_Impl::resetHeatingDesignSupplyAirTemperatureDifferenceRatio() {
  OS_ASSERT(setString(openstudio::DesignSpecification_AirTerminal_SizingFields::HeatingDesignSupplyAirTemperatureDifferenceRatio, ""));
}

double DesignSpecificationAirTerminalSizing_Impl::fractionofMinimumOutdoorAirFlow() const {
  const auto value = getDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofMinimumOutdoorAirFlow, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignSpecificationAirTerminalSizing_Impl::isFractionofMinimumOutdoorAirFlowDefaulted() const {
  return isEmpty(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofMinimumOutdoorAirFlow);
}

bool DesignSpecificationAirTerminalSizing_Impl::setFractionofMinimumOutdoorAirFlow(double fractionofMinimumOutdoorAirFlow) {
  return setDouble(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofMinimumOutdoorAirFlow, fractionofMinimumOutdoorAirFlow);
}

void DesignSpecificationAirTerminalSizing_Impl::resetFractionofMinimumOutdoorAirFlow() {
  OS_ASSERT(setString(openstudio::DesignSpecification_AirTerminal_SizingFields::FractionofMinimumOutdoorAirFlow, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
