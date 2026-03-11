/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilHeatingWaterToAirHeatPumpParameterEstimation.hpp"
#include "CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_ParameterEstimation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilHeatingWaterToAirHeatPumpParameterEstimation::CoilHeatingWaterToAirHeatPumpParameterEstimation(const Model& model)
  : ModelObject(CoilHeatingWaterToAirHeatPumpParameterEstimation::iddObjectType(), model) {}

CoilHeatingWaterToAirHeatPumpParameterEstimation::CoilHeatingWaterToAirHeatPumpParameterEstimation(
  std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilHeatingWaterToAirHeatPumpParameterEstimation::iddObjectType() {
  return IddObjectType::Coil_Heating_WaterToAirHeatPump_ParameterEstimation;
}

std::vector<std::string> CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorType);
}

std::string CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorType() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorType();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setCompressorType(const std::string& compressorType) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorType(compressorType);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::designSourceSideFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->designSourceSideFlowRate();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setDesignSourceSideFlowRate(double designSourceSideFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setDesignSourceSideFlowRate(designSourceSideFlowRate);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::grossRatedHeatingCapacity() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->grossRatedHeatingCapacity();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setGrossRatedHeatingCapacity(grossRatedHeatingCapacity);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::highPressureCutoff() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->highPressureCutoff();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setHighPressureCutoff(double highPressureCutoff) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setHighPressureCutoff(highPressureCutoff);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::lowPressureCutoff() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->lowPressureCutoff();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setLowPressureCutoff(double lowPressureCutoff) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setLowPressureCutoff(lowPressureCutoff);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::loadSideTotalHeatTransferCoefficient() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->loadSideTotalHeatTransferCoefficient();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setLoadSideTotalHeatTransferCoefficient(double loadSideTotalHeatTransferCoefficient) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setLoadSideTotalHeatTransferCoefficient(
    loadSideTotalHeatTransferCoefficient);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::superheatTemperatureattheEvaporatorOutlet() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->superheatTemperatureattheEvaporatorOutlet();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setSuperheatTemperatureattheEvaporatorOutlet(
  double superheatTemperatureattheEvaporatorOutlet) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setSuperheatTemperatureattheEvaporatorOutlet(
    superheatTemperatureattheEvaporatorOutlet);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorPowerLosses() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorPowerLosses();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setCompressorPowerLosses(double compressorPowerLosses) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorPowerLosses(compressorPowerLosses);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorEfficiency() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorEfficiency();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setCompressorEfficiency(double compressorEfficiency) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorEfficiency(compressorEfficiency);
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorPistonDisplacement() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorPistonDisplacement();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setCompressorPistonDisplacement(double compressorPistonDisplacement) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorPistonDisplacement(compressorPistonDisplacement);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetCompressorPistonDisplacement() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetCompressorPistonDisplacement();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorSuctionDischargePressureDrop() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorSuctionDischargePressureDrop();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setCompressorSuctionDischargePressureDrop(double compressorSuctionDischargePressureDrop) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorSuctionDischargePressureDrop(
    compressorSuctionDischargePressureDrop);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetCompressorSuctionDischargePressureDrop() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetCompressorSuctionDischargePressureDrop();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorClearanceFactor() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorClearanceFactor();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setCompressorClearanceFactor(double compressorClearanceFactor) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorClearanceFactor(compressorClearanceFactor);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetCompressorClearanceFactor() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetCompressorClearanceFactor();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::refrigerantVolumeFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->refrigerantVolumeFlowRate();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setRefrigerantVolumeFlowRate(double refrigerantVolumeFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setRefrigerantVolumeFlowRate(refrigerantVolumeFlowRate);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetRefrigerantVolumeFlowRate() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetRefrigerantVolumeFlowRate();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::volumeRatio() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->volumeRatio();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setVolumeRatio(double volumeRatio) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setVolumeRatio(volumeRatio);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetVolumeRatio() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetVolumeRatio();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::leakRateCoefficient() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->leakRateCoefficient();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setLeakRateCoefficient(double leakRateCoefficient) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setLeakRateCoefficient(leakRateCoefficient);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetLeakRateCoefficient() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetLeakRateCoefficient();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::sourceSideHeatTransferCoefficient() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->sourceSideHeatTransferCoefficient();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setSourceSideHeatTransferCoefficient(
    sourceSideHeatTransferCoefficient);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetSourceSideHeatTransferCoefficient() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetSourceSideHeatTransferCoefficient();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::sourceSideHeatTransferResistance1() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->sourceSideHeatTransferResistance1();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setSourceSideHeatTransferResistance1(double sourceSideHeatTransferResistance1) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setSourceSideHeatTransferResistance1(
    sourceSideHeatTransferResistance1);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetSourceSideHeatTransferResistance1() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetSourceSideHeatTransferResistance1();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation::sourceSideHeatTransferResistance2() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->sourceSideHeatTransferResistance2();
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation::setSourceSideHeatTransferResistance2(double sourceSideHeatTransferResistance2) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->setSourceSideHeatTransferResistance2(
    sourceSideHeatTransferResistance2);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation::resetSourceSideHeatTransferResistance2() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl>()->resetSourceSideHeatTransferResistance2();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorType() const {
  const auto value = getString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorType(const std::string& compressorType) {
  return setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorType, compressorType);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::designSourceSideFlowRate() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::DesignSourceSideFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setDesignSourceSideFlowRate(double designSourceSideFlowRate) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::DesignSourceSideFlowRate, designSourceSideFlowRate);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::grossRatedHeatingCapacity() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::GrossRatedHeatingCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::GrossRatedHeatingCapacity,
                   grossRatedHeatingCapacity);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::highPressureCutoff() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::HighPressureCutoff, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setHighPressureCutoff(double highPressureCutoff) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::HighPressureCutoff, highPressureCutoff);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::lowPressureCutoff() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LowPressureCutoff, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setLowPressureCutoff(double lowPressureCutoff) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LowPressureCutoff, lowPressureCutoff);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::loadSideTotalHeatTransferCoefficient() const {
  const auto value =
    getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LoadSideTotalHeatTransferCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setLoadSideTotalHeatTransferCoefficient(double loadSideTotalHeatTransferCoefficient) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LoadSideTotalHeatTransferCoefficient,
                   loadSideTotalHeatTransferCoefficient);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::superheatTemperatureattheEvaporatorOutlet() const {
  const auto value =
    getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SuperheatTemperatureattheEvaporatorOutlet, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setSuperheatTemperatureattheEvaporatorOutlet(
  double superheatTemperatureattheEvaporatorOutlet) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SuperheatTemperatureattheEvaporatorOutlet,
                   superheatTemperatureattheEvaporatorOutlet);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorPowerLosses() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPowerLosses, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorPowerLosses(double compressorPowerLosses) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPowerLosses, compressorPowerLosses);
}

double CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorEfficiency() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorEfficiency(double compressorEfficiency) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorEfficiency, compressorEfficiency);
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorPistonDisplacement() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorPistonDisplacement(double compressorPistonDisplacement) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement,
                   compressorPistonDisplacement);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetCompressorPistonDisplacement() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorSuctionDischargePressureDrop() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorSuctionDischargePressureDrop(
  double compressorSuctionDischargePressureDrop) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop,
                   compressorSuctionDischargePressureDrop);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetCompressorSuctionDischargePressureDrop() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorClearanceFactor() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorClearanceFactor(double compressorClearanceFactor) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, compressorClearanceFactor);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetCompressorClearanceFactor() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::refrigerantVolumeFlowRate() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setRefrigerantVolumeFlowRate(double refrigerantVolumeFlowRate) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, refrigerantVolumeFlowRate);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetRefrigerantVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::volumeRatio() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setVolumeRatio(double volumeRatio) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, volumeRatio);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetVolumeRatio() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::leakRateCoefficient() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setLeakRateCoefficient(double leakRateCoefficient) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, leakRateCoefficient);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetLeakRateCoefficient() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::sourceSideHeatTransferCoefficient() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient,
                   sourceSideHeatTransferCoefficient);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetSourceSideHeatTransferCoefficient() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::sourceSideHeatTransferResistance1() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setSourceSideHeatTransferResistance1(double sourceSideHeatTransferResistance1) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1,
                   sourceSideHeatTransferResistance1);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetSourceSideHeatTransferResistance1() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1, ""));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::sourceSideHeatTransferResistance2() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2, true);
}

bool CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::setSourceSideHeatTransferResistance2(double sourceSideHeatTransferResistance2) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2,
                   sourceSideHeatTransferResistance2);
}

void CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::resetSourceSideHeatTransferResistance2() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2, ""));
}

std::vector<std::string> CoilHeatingWaterToAirHeatPumpParameterEstimation_Impl::compressorTypeValues() const {
  return openstudio::epmodel::CoilHeatingWaterToAirHeatPumpParameterEstimation::compressorTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
