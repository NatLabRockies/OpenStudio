/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Cooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

HeatPumpPlantLoopEIRCooling::HeatPumpPlantLoopEIRCooling(const Model& model)
  : WaterToWaterComponent(HeatPumpPlantLoopEIRCooling::iddObjectType(), model) {
  // Keep required scalar fields populated for strict non-optional getters.
  OS_ASSERT(setCondenserType("AirSource"));
  autosizeLoadSideReferenceFlowRate();
  autosizeSourceSideReferenceFlowRate();
  autosizeHeatRecoveryReferenceFlowRate();
  autosizeReferenceCapacity();
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setFlowMode("ConstantFlow"));
  OS_ASSERT(setMinimumPartLoadRatio(0.0));
  OS_ASSERT(setMinimumSourceInletTemperature(-100.0));
  OS_ASSERT(setMaximumSourceInletTemperature(100.0));
  OS_ASSERT(setMaximumHeatRecoveryOutletTemperature(60.0));
  OS_ASSERT(setThermosiphonMinimumTemperatureDifference(0.0));
}

HeatPumpPlantLoopEIRCooling::HeatPumpPlantLoopEIRCooling(std::shared_ptr<detail::HeatPumpPlantLoopEIRCooling_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType HeatPumpPlantLoopEIRCooling::iddObjectType() {
  return IddObjectType::HeatPump_PlantLoop_EIR_Cooling;
}

std::vector<std::string> HeatPumpPlantLoopEIRCooling::validCondenserTypeValues() {
  return HeatPumpPlantLoopEIRCooling::condenserTypeValues();
}

std::vector<std::string> HeatPumpPlantLoopEIRCooling::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType);
}

std::string HeatPumpPlantLoopEIRCooling::condenserType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->condenserType();
}

bool HeatPumpPlantLoopEIRCooling::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setCondenserType(condenserType);
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::loadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->loadSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRCooling::isLoadSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isLoadSideReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setLoadSideReferenceFlowRate(loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling::autosizeLoadSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedLoadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::sourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sourceSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRCooling::isSourceSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isSourceSideReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setSourceSideReferenceFlowRate(sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling::autosizeSourceSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedSourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::heatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRCooling::isHeatRecoveryReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isHeatRecoveryReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setHeatRecoveryReferenceFlowRate(heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling::autosizeHeatRecoveryReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedHeatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::referenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->referenceCapacity();
}

bool HeatPumpPlantLoopEIRCooling::isReferenceCapacityAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isReferenceCapacityAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setReferenceCapacity(double referenceCapacity) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setReferenceCapacity(referenceCapacity);
}

void HeatPumpPlantLoopEIRCooling::autosizeReferenceCapacity() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeReferenceCapacity();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedReferenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedReferenceCapacity();
}

double HeatPumpPlantLoopEIRCooling::referenceCoefficientofPerformance() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->referenceCoefficientofPerformance();
}

bool HeatPumpPlantLoopEIRCooling::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
}

double HeatPumpPlantLoopEIRCooling::sizingFactor() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sizingFactor();
}

bool HeatPumpPlantLoopEIRCooling::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setSizingFactor(sizingFactor);
}

std::string HeatPumpPlantLoopEIRCooling::controlType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->controlType();
}

bool HeatPumpPlantLoopEIRCooling::setControlType(const std::string& controlType) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setControlType(controlType);
}

std::string HeatPumpPlantLoopEIRCooling::flowMode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->flowMode();
}

bool HeatPumpPlantLoopEIRCooling::setFlowMode(const std::string& flowMode) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setFlowMode(flowMode);
}

double HeatPumpPlantLoopEIRCooling::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->minimumPartLoadRatio();
}

bool HeatPumpPlantLoopEIRCooling::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double HeatPumpPlantLoopEIRCooling::minimumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->minimumSourceInletTemperature();
}

bool HeatPumpPlantLoopEIRCooling::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMinimumSourceInletTemperature(minimumSourceInletTemperature);
}

double HeatPumpPlantLoopEIRCooling::maximumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->maximumSourceInletTemperature();
}

bool HeatPumpPlantLoopEIRCooling::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMaximumSourceInletTemperature(maximumSourceInletTemperature);
}

double HeatPumpPlantLoopEIRCooling::maximumHeatRecoveryOutletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->maximumHeatRecoveryOutletTemperature();
}

bool HeatPumpPlantLoopEIRCooling::setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMaximumHeatRecoveryOutletTemperature(maximumHeatRecoveryOutletTemperature);
}

double HeatPumpPlantLoopEIRCooling::thermosiphonMinimumTemperatureDifference() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->thermosiphonMinimumTemperatureDifference();
}

bool HeatPumpPlantLoopEIRCooling::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setThermosiphonMinimumTemperatureDifference(thermosiphonMinimumTemperatureDifference);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

  std::string HeatPumpPlantLoopEIRCooling_Impl::condenserType() const {
    const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, true);
    OS_ASSERT(value);
    return *value;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::loadSideReferenceFlowRate() const {
    return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, true);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::isLoadSideReferenceFlowRateAutosized() const {
    if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, true)) {
      return openstudio::istringEqual(*value, "Autosize");
    }
    return false;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::sourceSideReferenceFlowRate() const {
    return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, true);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::isSourceSideReferenceFlowRateAutosized() const {
    if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, true)) {
      return openstudio::istringEqual(*value, "Autosize");
    }
    return false;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryReferenceFlowRate() const {
    return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, true);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::isHeatRecoveryReferenceFlowRateAutosized() const {
    if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, true)) {
      return openstudio::istringEqual(*value, "Autosize");
    }
    return false;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::referenceCapacity() const {
    return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, true);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::isReferenceCapacityAutosized() const {
    if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, true)) {
      return openstudio::istringEqual(*value, "Autosize");
    }
    return false;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::referenceCoefficientofPerformance() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCoefficientofPerformance, true);
    OS_ASSERT(value);
    return *value;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::sizingFactor() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SizingFactor, true);
    OS_ASSERT(value);
    return *value;
  }

  std::string HeatPumpPlantLoopEIRCooling_Impl::controlType() const {
    const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ControlType, true);
    OS_ASSERT(value);
    return *value;
  }

  std::string HeatPumpPlantLoopEIRCooling_Impl::flowMode() const {
    const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::FlowMode, true);
    OS_ASSERT(value);
    return *value;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::minimumPartLoadRatio() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumPartLoadRatio, true);
    OS_ASSERT(value);
    return *value;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::minimumSourceInletTemperature() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSourceInletTemperature, true);
    OS_ASSERT(value);
    return *value;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::maximumSourceInletTemperature() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSourceInletTemperature, true);
    OS_ASSERT(value);
    return *value;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::maximumHeatRecoveryOutletTemperature() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumHeatRecoveryOutletTemperature, true);
    OS_ASSERT(value);
    return *value;
  }

  double HeatPumpPlantLoopEIRCooling_Impl::thermosiphonMinimumTemperatureDifference() const {
    const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonMinimumTemperatureDifference, true);
    OS_ASSERT(value);
    return *value;
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setCondenserType(const std::string& condenserType) {
    return setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, condenserType);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, loadSideReferenceFlowRate);
  }

  void HeatPumpPlantLoopEIRCooling_Impl::autosizeLoadSideReferenceFlowRate() {
    const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, "Autosize");
    OS_ASSERT(result);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, sourceSideReferenceFlowRate);
  }

  void HeatPumpPlantLoopEIRCooling_Impl::autosizeSourceSideReferenceFlowRate() {
    const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, "Autosize");
    OS_ASSERT(result);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, heatRecoveryReferenceFlowRate);
  }

  void HeatPumpPlantLoopEIRCooling_Impl::autosizeHeatRecoveryReferenceFlowRate() {
    const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, "Autosize");
    OS_ASSERT(result);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setReferenceCapacity(double referenceCapacity) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, referenceCapacity);
  }

  void HeatPumpPlantLoopEIRCooling_Impl::autosizeReferenceCapacity() {
    const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, "Autosize");
    OS_ASSERT(result);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setSizingFactor(double sizingFactor) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SizingFactor, sizingFactor);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setControlType(const std::string& controlType) {
    return setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ControlType, controlType);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setFlowMode(const std::string& flowMode) {
    return setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::FlowMode, flowMode);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSourceInletTemperature, minimumSourceInletTemperature);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSourceInletTemperature, maximumSourceInletTemperature);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumHeatRecoveryOutletTemperature, maximumHeatRecoveryOutletTemperature);
  }

  bool HeatPumpPlantLoopEIRCooling_Impl::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
    return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonMinimumTemperatureDifference,
                     thermosiphonMinimumTemperatureDifference);
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedLoadSideReferenceFlowRate() const {
    // epmodel does not currently resolve autosized values from SQL results.
    return boost::none;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedSourceSideReferenceFlowRate() const {
    // epmodel does not currently resolve autosized values from SQL results.
    return boost::none;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedHeatRecoveryReferenceFlowRate() const {
    // epmodel does not currently resolve autosized values from SQL results.
    return boost::none;
  }

  boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedReferenceCapacity() const {
    // epmodel does not currently resolve autosized values from SQL results.
    return boost::none;
  }

  std::vector<std::string> HeatPumpPlantLoopEIRCooling_Impl::condenserTypeValues() const {
    return openstudio::epmodel::HeatPumpPlantLoopEIRCooling::condenserTypeValues();
  }

  unsigned HeatPumpPlantLoopEIRCooling_Impl::supplyInletPort() const {
    return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideInletNodeName;
  }

  unsigned HeatPumpPlantLoopEIRCooling_Impl::supplyOutletPort() const {
    return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideOutletNodeName;
  }

  unsigned HeatPumpPlantLoopEIRCooling_Impl::demandInletPort() const {
    return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName;
  }

  unsigned HeatPumpPlantLoopEIRCooling_Impl::demandOutletPort() const {
    return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName;
  }

  unsigned HeatPumpPlantLoopEIRCooling_Impl::tertiaryInletPort() const {
    return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName;
  }

  unsigned HeatPumpPlantLoopEIRCooling_Impl::tertiaryOutletPort() const {
    return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName;
  }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
