/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpWaterToWaterParameterEstimationHeating.hpp"
#include "HeatPumpWaterToWaterParameterEstimationHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatPump_WaterToWater_ParameterEstimation_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

HeatPumpWaterToWaterParameterEstimationHeating::HeatPumpWaterToWaterParameterEstimationHeating(const Model& model)
  : ModelObject(HeatPumpWaterToWaterParameterEstimationHeating::iddObjectType(), model) {}

HeatPumpWaterToWaterParameterEstimationHeating::HeatPumpWaterToWaterParameterEstimationHeating(
  std::shared_ptr<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HeatPumpWaterToWaterParameterEstimationHeating::iddObjectType() {
  return IddObjectType::HeatPump_WaterToWater_ParameterEstimation_Heating;
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::nominalCOP() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->nominalCOP();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::nominalCapacity() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->nominalCapacity();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->minimumPartLoadRatio();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::maximumPartLoadRatio() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->maximumPartLoadRatio();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::optimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->optimumPartLoadRatio();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::loadSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->loadSideFlowRate();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::sourceSideFlowRate() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->sourceSideFlowRate();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::loadSideHeatTransferCoefficient() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->loadSideHeatTransferCoefficient();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::sourceSideHeatTransferCoefficient() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->sourceSideHeatTransferCoefficient();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::pistonDisplacement() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->pistonDisplacement();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::compressorClearanceFactor() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->compressorClearanceFactor();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::compressorSuctionandDischargePressureDrop() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->compressorSuctionandDischargePressureDrop();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::superheating() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->superheating();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::constantPartofElectromechanicalPowerLosses() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->constantPartofElectromechanicalPowerLosses();
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating::lossFactor() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->lossFactor();
}

double HeatPumpWaterToWaterParameterEstimationHeating::highPressureCutOff() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->highPressureCutOff();
}

bool HeatPumpWaterToWaterParameterEstimationHeating::isHighPressureCutOffDefaulted() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->isHighPressureCutOffDefaulted();
}

double HeatPumpWaterToWaterParameterEstimationHeating::lowPressureCutOff() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->lowPressureCutOff();
}

bool HeatPumpWaterToWaterParameterEstimationHeating::isLowPressureCutOffDefaulted() const {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->isLowPressureCutOffDefaulted();
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setNominalCOP(double nominalCOP) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setNominalCOP(nominalCOP);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setNominalCapacity(nominalCapacity);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setLoadSideFlowRate(double loadSideFlowRate) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLoadSideFlowRate(loadSideFlowRate);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setSourceSideFlowRate(double sourceSideFlowRate) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setSourceSideFlowRate(sourceSideFlowRate);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLoadSideHeatTransferCoefficient(loadSideHeatTransferCoefficient);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setSourceSideHeatTransferCoefficient(
    sourceSideHeatTransferCoefficient);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setPistonDisplacement(double pistonDisplacement) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setPistonDisplacement(pistonDisplacement);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setCompressorClearanceFactor(double compressorClearanceFactor) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setCompressorClearanceFactor(compressorClearanceFactor);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setCompressorSuctionandDischargePressureDrop(
  double compressorSuctionandDischargePressureDrop) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setCompressorSuctionandDischargePressureDrop(
    compressorSuctionandDischargePressureDrop);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setSuperheating(double superheating) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setSuperheating(superheating);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setConstantPartofElectromechanicalPowerLosses(
  double constantPartofElectromechanicalPowerLosses) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setConstantPartofElectromechanicalPowerLosses(
    constantPartofElectromechanicalPowerLosses);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setLossFactor(double lossFactor) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLossFactor(lossFactor);
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setHighPressureCutOff(double highPressureCutOff) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setHighPressureCutOff(highPressureCutOff);
}

void HeatPumpWaterToWaterParameterEstimationHeating::resetHighPressureCutOff() {
  getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->resetHighPressureCutOff();
}

bool HeatPumpWaterToWaterParameterEstimationHeating::setLowPressureCutOff(double lowPressureCutOff) {
  return getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->setLowPressureCutOff(lowPressureCutOff);
}

void HeatPumpWaterToWaterParameterEstimationHeating::resetLowPressureCutOff() {
  getImpl<detail::HeatPumpWaterToWaterParameterEstimationHeating_Impl>()->resetLowPressureCutOff();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::nominalCOP() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCOP, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::nominalCapacity() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCapacity, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::minimumPartLoadRatio() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MinimumPartLoadRatio, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::maximumPartLoadRatio() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MaximumPartLoadRatio, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::optimumPartLoadRatio() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::OptimumPartLoadRatio, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::loadSideFlowRate() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideFlowRate, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::sourceSideFlowRate() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideFlowRate, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::loadSideHeatTransferCoefficient() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideHeatTransferCoefficient, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::sourceSideHeatTransferCoefficient() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideHeatTransferCoefficient, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::pistonDisplacement() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::PistonDisplacement, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::compressorClearanceFactor() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorClearanceFactor, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::compressorSuctionandDischargePressureDrop() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorSuctionandDischargePressureDrop, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::superheating() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::Superheating, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::constantPartofElectromechanicalPowerLosses() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::ConstantPartofElectromechanicalPowerLosses, true);
}

boost::optional<double> HeatPumpWaterToWaterParameterEstimationHeating_Impl::lossFactor() const {
  return getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LossFactor, true);
}

double HeatPumpWaterToWaterParameterEstimationHeating_Impl::highPressureCutOff() const {
  const auto value = getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::isHighPressureCutOffDefaulted() const {
  return isEmpty(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff);
}

double HeatPumpWaterToWaterParameterEstimationHeating_Impl::lowPressureCutOff() const {
  const auto value = getDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::isLowPressureCutOffDefaulted() const {
  return isEmpty(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setNominalCOP(double nominalCOP) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCOP, nominalCOP);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setNominalCapacity(double nominalCapacity) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCapacity, nominalCapacity);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::OptimumPartLoadRatio, optimumPartLoadRatio);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLoadSideFlowRate(double loadSideFlowRate) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideFlowRate, loadSideFlowRate);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setSourceSideFlowRate(double sourceSideFlowRate) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideFlowRate, sourceSideFlowRate);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideHeatTransferCoefficient,
                   loadSideHeatTransferCoefficient);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideHeatTransferCoefficient,
                   sourceSideHeatTransferCoefficient);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setPistonDisplacement(double pistonDisplacement) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::PistonDisplacement, pistonDisplacement);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setCompressorClearanceFactor(double compressorClearanceFactor) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorClearanceFactor, compressorClearanceFactor);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setCompressorSuctionandDischargePressureDrop(
  double compressorSuctionandDischargePressureDrop) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorSuctionandDischargePressureDrop,
                   compressorSuctionandDischargePressureDrop);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setSuperheating(double superheating) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::Superheating, superheating);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setConstantPartofElectromechanicalPowerLosses(
  double constantPartofElectromechanicalPowerLosses) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::ConstantPartofElectromechanicalPowerLosses,
                   constantPartofElectromechanicalPowerLosses);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLossFactor(double lossFactor) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LossFactor, lossFactor);
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setHighPressureCutOff(double highPressureCutOff) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, highPressureCutOff);
}

void HeatPumpWaterToWaterParameterEstimationHeating_Impl::resetHighPressureCutOff() {
  OS_ASSERT(setString(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, ""));
}

bool HeatPumpWaterToWaterParameterEstimationHeating_Impl::setLowPressureCutOff(double lowPressureCutOff) {
  return setDouble(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, lowPressureCutOff);
}

void HeatPumpWaterToWaterParameterEstimationHeating_Impl::resetLowPressureCutOff() {
  OS_ASSERT(setString(openstudio::HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
