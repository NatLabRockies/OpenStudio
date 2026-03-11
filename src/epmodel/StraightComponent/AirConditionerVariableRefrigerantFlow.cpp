/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirConditionerVariableRefrigerantFlow::AirConditionerVariableRefrigerantFlow(const Model& model)
  : ModelObject(AirConditionerVariableRefrigerantFlow::iddObjectType(), model) {}

AirConditionerVariableRefrigerantFlow::AirConditionerVariableRefrigerantFlow(
  std::shared_ptr<detail::AirConditionerVariableRefrigerantFlow_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirConditionerVariableRefrigerantFlow::iddObjectType() {
  return IddObjectType::AirConditioner_VariableRefrigerantFlow;
}

std::vector<std::string> AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues() {
  return {"WetBulbTemperature", "DryBulbTemperature"};
}

std::vector<std::string> AirConditionerVariableRefrigerantFlow::defrostStrategyValues() {
  return {"ReverseCycle", "Resistive"};
}

std::vector<std::string> AirConditionerVariableRefrigerantFlow::condenserTypeValues() {
  return {"AirCooled", "EvaporativelyCooled", "WaterCooled"};
}

boost::optional<double> AirConditionerVariableRefrigerantFlow::grossRatedTotalCoolingCapacity() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedTotalCoolingCapacity();
}

bool AirConditionerVariableRefrigerantFlow::isGrossRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isGrossRatedTotalCoolingCapacityAutosized();
}

bool AirConditionerVariableRefrigerantFlow::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedTotalCoolingCapacity(grossRatedTotalCoolingCapacity);
}

void AirConditionerVariableRefrigerantFlow::autosizeGrossRatedTotalCoolingCapacity() {
  getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->autosizeGrossRatedTotalCoolingCapacity();
}

double AirConditionerVariableRefrigerantFlow::grossRatedCoolingCOP() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedCoolingCOP();
}

bool AirConditionerVariableRefrigerantFlow::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedCoolingCOP(grossRatedCoolingCOP);
}

boost::optional<double> AirConditionerVariableRefrigerantFlow::grossRatedHeatingCapacity() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedHeatingCapacity();
}

bool AirConditionerVariableRefrigerantFlow::isGrossRatedHeatingCapacityAutosized() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isGrossRatedHeatingCapacityAutosized();
}

bool AirConditionerVariableRefrigerantFlow::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedHeatingCapacity(grossRatedHeatingCapacity);
}

void AirConditionerVariableRefrigerantFlow::autosizeGrossRatedHeatingCapacity() {
  getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->autosizeGrossRatedHeatingCapacity();
}

double AirConditionerVariableRefrigerantFlow::ratedHeatingCapacitySizingRatio() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->ratedHeatingCapacitySizingRatio();
}

bool AirConditionerVariableRefrigerantFlow::setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setRatedHeatingCapacitySizingRatio(ratedHeatingCapacitySizingRatio);
}

std::string AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureType() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingPerformanceCurveOutdoorTemperatureType();
}

bool AirConditionerVariableRefrigerantFlow::setHeatingPerformanceCurveOutdoorTemperatureType(
  const std::string& heatingPerformanceCurveOutdoorTemperatureType) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingPerformanceCurveOutdoorTemperatureType(
    heatingPerformanceCurveOutdoorTemperatureType);
}

bool AirConditionerVariableRefrigerantFlow::heatPumpWasteHeatRecovery() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatPumpWasteHeatRecovery();
}

bool AirConditionerVariableRefrigerantFlow::setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatPumpWasteHeatRecovery(heatPumpWasteHeatRecovery);
}

int AirConditionerVariableRefrigerantFlow::numberofCompressors() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->numberofCompressors();
}

bool AirConditionerVariableRefrigerantFlow::setNumberofCompressors(int numberofCompressors) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setNumberofCompressors(numberofCompressors);
}

std::string AirConditionerVariableRefrigerantFlow::defrostStrategy() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->defrostStrategy();
}

bool AirConditionerVariableRefrigerantFlow::setDefrostStrategy(const std::string& defrostStrategy) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setDefrostStrategy(defrostStrategy);
}

std::string AirConditionerVariableRefrigerantFlow::condenserType() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->condenserType();
}

bool AirConditionerVariableRefrigerantFlow::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCondenserType(condenserType);
}

bool AirConditionerVariableRefrigerantFlow::isCondenserTypeDefaulted() const {
  return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isCondenserTypeDefaulted();
}

void AirConditionerVariableRefrigerantFlow::resetCondenserType() {
  getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCondenserType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirConditionerVariableRefrigerantFlow_Impl::grossRatedTotalCoolingCapacity() const {
  return getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true);
}

bool AirConditionerVariableRefrigerantFlow_Impl::isGrossRatedTotalCoolingCapacityAutosized() const {
  if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
  return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, grossRatedTotalCoolingCapacity);
}

void AirConditionerVariableRefrigerantFlow_Impl::autosizeGrossRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "autosize"));
}

double AirConditionerVariableRefrigerantFlow_Impl::grossRatedCoolingCOP() const {
  const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
  return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, grossRatedCoolingCOP);
}

boost::optional<double> AirConditionerVariableRefrigerantFlow_Impl::grossRatedHeatingCapacity() const {
  return getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true);
}

bool AirConditionerVariableRefrigerantFlow_Impl::isGrossRatedHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
  return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, grossRatedHeatingCapacity);
}

void AirConditionerVariableRefrigerantFlow_Impl::autosizeGrossRatedHeatingCapacity() {
  OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "autosize"));
}

double AirConditionerVariableRefrigerantFlow_Impl::ratedHeatingCapacitySizingRatio() const {
  const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio) {
  return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, ratedHeatingCapacitySizingRatio);
}

std::string AirConditionerVariableRefrigerantFlow_Impl::heatingPerformanceCurveOutdoorTemperatureType() const {
  const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingPerformanceCurveOutdoorTemperatureType(
  const std::string& heatingPerformanceCurveOutdoorTemperatureType) {
  return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType,
                   heatingPerformanceCurveOutdoorTemperatureType);
}

bool AirConditionerVariableRefrigerantFlow_Impl::heatPumpWasteHeatRecovery() const {
  const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool AirConditionerVariableRefrigerantFlow_Impl::setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery) {
  const bool result = setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery,
                                heatPumpWasteHeatRecovery ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

int AirConditionerVariableRefrigerantFlow_Impl::numberofCompressors() const {
  const auto value = getInt(openstudio::AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, true);
  OS_ASSERT(value);
  return *value;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setNumberofCompressors(int numberofCompressors) {
  return setInt(openstudio::AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, numberofCompressors);
}

std::string AirConditionerVariableRefrigerantFlow_Impl::defrostStrategy() const {
  const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, true);
  OS_ASSERT(value);
  return *value;
}

bool AirConditionerVariableRefrigerantFlow_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
  return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, defrostStrategy);
}

std::string AirConditionerVariableRefrigerantFlow_Impl::condenserType() const {
  if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, false)) {
    return *value;
  }
  return "";
}

bool AirConditionerVariableRefrigerantFlow_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, condenserType);
}

bool AirConditionerVariableRefrigerantFlow_Impl::isCondenserTypeDefaulted() const {
  return !getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, false);
}

void AirConditionerVariableRefrigerantFlow_Impl::resetCondenserType() {
  OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, ""));
}

std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::heatingPerformanceCurveOutdoorTemperatureTypeValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
}

std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::defrostStrategyValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
}

std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::condenserTypeValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::condenserTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
