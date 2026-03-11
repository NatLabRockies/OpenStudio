/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

HeatPumpPlantLoopEIRHeating::HeatPumpPlantLoopEIRHeating(const Model& model)
  : ModelObject(HeatPumpPlantLoopEIRHeating::iddObjectType(), model) {
  // Keep required scalar fields populated for strict non-optional getters.
  OS_ASSERT(setCondenserType("AirSource"));
  autosizeLoadSideReferenceFlowRate();
  autosizeSourceSideReferenceFlowRate();
  autosizeHeatRecoveryReferenceFlowRate();
  autosizeReferenceCapacity();
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setHeatingToCoolingCapacitySizingRatio(1.0));
  OS_ASSERT(setHeatPumpSizingMethod("CoolingCapacity"));
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setFlowMode("ConstantFlow"));
  OS_ASSERT(setMinimumPartLoadRatio(0.0));
  OS_ASSERT(setMinimumSourceInletTemperature(-100.0));
  OS_ASSERT(setMaximumSourceInletTemperature(100.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureForDefrostOperation(10.0));
  OS_ASSERT(setHeatPumpDefrostControl("None"));
  OS_ASSERT(setHeatPumpDefrostTimePeriodFraction(0.058333));
  OS_ASSERT(setMinimumHeatRecoveryOutletTemperature(4.5));
}

HeatPumpPlantLoopEIRHeating::HeatPumpPlantLoopEIRHeating(std::shared_ptr<detail::HeatPumpPlantLoopEIRHeating_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HeatPumpPlantLoopEIRHeating::iddObjectType() {
  return IddObjectType::HeatPump_PlantLoop_EIR_Heating;
}

std::vector<std::string> HeatPumpPlantLoopEIRHeating::validCondenserTypeValues() {
  return HeatPumpPlantLoopEIRHeating::condenserTypeValues();
}

std::vector<std::string> HeatPumpPlantLoopEIRHeating::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType);
}

std::string HeatPumpPlantLoopEIRHeating::condenserType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->condenserType();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::loadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->loadSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::isLoadSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isLoadSideReferenceFlowRateAutosized();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::sourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sourceSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::isSourceSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isSourceSideReferenceFlowRateAutosized();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::heatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::isHeatRecoveryReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isHeatRecoveryReferenceFlowRateAutosized();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::referenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->referenceCapacity();
}

bool HeatPumpPlantLoopEIRHeating::isReferenceCapacityAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isReferenceCapacityAutosized();
}

double HeatPumpPlantLoopEIRHeating::referenceCoefficientofPerformance() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->referenceCoefficientofPerformance();
}

double HeatPumpPlantLoopEIRHeating::sizingFactor() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sizingFactor();
}

double HeatPumpPlantLoopEIRHeating::heatingToCoolingCapacitySizingRatio() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatingToCoolingCapacitySizingRatio();
}

std::string HeatPumpPlantLoopEIRHeating::heatPumpSizingMethod() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatPumpSizingMethod();
}

std::string HeatPumpPlantLoopEIRHeating::controlType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->controlType();
}

std::string HeatPumpPlantLoopEIRHeating::flowMode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->flowMode();
}

double HeatPumpPlantLoopEIRHeating::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumPartLoadRatio();
}

double HeatPumpPlantLoopEIRHeating::minimumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumSourceInletTemperature();
}

double HeatPumpPlantLoopEIRHeating::maximumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->maximumSourceInletTemperature();
}

double HeatPumpPlantLoopEIRHeating::maximumOutdoorDryBulbTemperatureForDefrostOperation() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->maximumOutdoorDryBulbTemperatureForDefrostOperation();
}

std::string HeatPumpPlantLoopEIRHeating::heatPumpDefrostControl() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatPumpDefrostControl();
}

double HeatPumpPlantLoopEIRHeating::heatPumpDefrostTimePeriodFraction() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatPumpDefrostTimePeriodFraction();
}

double HeatPumpPlantLoopEIRHeating::minimumHeatRecoveryOutletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumHeatRecoveryOutletTemperature();
}

bool HeatPumpPlantLoopEIRHeating::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setCondenserType(condenserType);
}

bool HeatPumpPlantLoopEIRHeating::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setLoadSideReferenceFlowRate(loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating::autosizeLoadSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeLoadSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setSourceSideReferenceFlowRate(sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating::autosizeSourceSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeSourceSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatRecoveryReferenceFlowRate(heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating::autosizeHeatRecoveryReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeHeatRecoveryReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::setReferenceCapacity(double referenceCapacity) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setReferenceCapacity(referenceCapacity);
}

void HeatPumpPlantLoopEIRHeating::autosizeReferenceCapacity() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeReferenceCapacity();
}

bool HeatPumpPlantLoopEIRHeating::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
}

bool HeatPumpPlantLoopEIRHeating::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setSizingFactor(sizingFactor);
}

bool HeatPumpPlantLoopEIRHeating::setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatingToCoolingCapacitySizingRatio(heatingToCoolingCapacitySizingRatio);
}

bool HeatPumpPlantLoopEIRHeating::setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatPumpSizingMethod(heatPumpSizingMethod);
}

bool HeatPumpPlantLoopEIRHeating::setControlType(const std::string& controlType) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setControlType(controlType);
}

bool HeatPumpPlantLoopEIRHeating::setFlowMode(const std::string& flowMode) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setFlowMode(flowMode);
}

bool HeatPumpPlantLoopEIRHeating::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

bool HeatPumpPlantLoopEIRHeating::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumSourceInletTemperature(minimumSourceInletTemperature);
}

bool HeatPumpPlantLoopEIRHeating::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMaximumSourceInletTemperature(maximumSourceInletTemperature);
}

bool HeatPumpPlantLoopEIRHeating::setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMaximumOutdoorDryBulbTemperatureForDefrostOperation(
    maximumOutdoorDryBulbTemperatureForDefrostOperation);
}

bool HeatPumpPlantLoopEIRHeating::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatPumpDefrostControl(heatPumpDefrostControl);
}

bool HeatPumpPlantLoopEIRHeating::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatPumpDefrostTimePeriodFraction(heatPumpDefrostTimePeriodFraction);
}

bool HeatPumpPlantLoopEIRHeating::setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumHeatRecoveryOutletTemperature(minimumHeatRecoveryOutletTemperature);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedLoadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedSourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedHeatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedReferenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedReferenceCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HeatPumpPlantLoopEIRHeating_Impl::condenserType() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::loadSideReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isLoadSideReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::sourceSideReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isSourceSideReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isHeatRecoveryReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::referenceCapacity() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isReferenceCapacityAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

double HeatPumpPlantLoopEIRHeating_Impl::referenceCoefficientofPerformance() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::heatingToCoolingCapacitySizingRatio() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatingToCoolingCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeatPumpPlantLoopEIRHeating_Impl::heatPumpSizingMethod() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpSizingMethod, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeatPumpPlantLoopEIRHeating_Impl::controlType() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeatPumpPlantLoopEIRHeating_Impl::flowMode() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::FlowMode, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::minimumSourceInletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSourceInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::maximumSourceInletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSourceInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::maximumOutdoorDryBulbTemperatureForDefrostOperation() const {
  const auto value =
    getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeatPumpPlantLoopEIRHeating_Impl::heatPumpDefrostControl() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostControl, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::heatPumpDefrostTimePeriodFraction() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostTimePeriodFraction, true);
  OS_ASSERT(value);
  return *value;
}

double HeatPumpPlantLoopEIRHeating_Impl::minimumHeatRecoveryOutletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumHeatRecoveryOutletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, condenserType);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeLoadSideReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeSourceSideReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeHeatRecoveryReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setReferenceCapacity(double referenceCapacity) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, referenceCapacity);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeReferenceCapacity() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, "Autosize");
  OS_ASSERT(result);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, sizingFactor);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatingToCoolingCapacitySizingRatio, heatingToCoolingCapacitySizingRatio);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpSizingMethod, heatPumpSizingMethod);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ControlType, controlType);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setFlowMode(const std::string& flowMode) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::FlowMode, flowMode);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSourceInletTemperature, minimumSourceInletTemperature);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSourceInletTemperature, maximumSourceInletTemperature);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMaximumOutdoorDryBulbTemperatureForDefrostOperation(
  double maximumOutdoorDryBulbTemperatureForDefrostOperation) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation,
                   maximumOutdoorDryBulbTemperatureForDefrostOperation);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostControl, heatPumpDefrostControl);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostTimePeriodFraction, heatPumpDefrostTimePeriodFraction);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumHeatRecoveryOutletTemperature, minimumHeatRecoveryOutletTemperature);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedLoadSideReferenceFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedSourceSideReferenceFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedHeatRecoveryReferenceFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedReferenceCapacity() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

std::vector<std::string> HeatPumpPlantLoopEIRHeating_Impl::condenserTypeValues() const {
  return openstudio::epmodel::HeatPumpPlantLoopEIRHeating::condenserTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
