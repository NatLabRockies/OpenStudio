/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoolingTowerSingleSpeed.hpp"
#include "StraightComponent/CoolingTowerSingleSpeed_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoolingTower_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CoolingTowerSingleSpeed::CoolingTowerSingleSpeed(const Model& model)
  : StraightComponent(CoolingTowerSingleSpeed::iddObjectType(), model) {
  autosizeDesignWaterFlowRate();
  autosizeDesignAirFlowRate();
  autosizeFanPoweratDesignAirFlowRate();
  autosizeUFactorTimesAreaValueatDesignAirFlowRate();
  autosizeAirFlowRateinFreeConvectionRegime();
  autosizeUFactorTimesAreaValueatFreeConvectionAirFlowRate();
  OS_ASSERT(setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate"));
  OS_ASSERT(setFreeConvectionCapacity(0.0));
  OS_ASSERT(setBasinHeaterCapacity(0.0));
  OS_ASSERT(setBasinHeaterSetpointTemperature(2.0));
  OS_ASSERT(setEvaporationLossMode("LossFactor"));
  OS_ASSERT(setEvaporationLossFactor(0.2));
  OS_ASSERT(setDriftLossPercent(0.008));
  OS_ASSERT(setBlowdownCalculationMode("ConcentrationRatio"));
  OS_ASSERT(setBlowdownConcentrationRatio(3.0));
  OS_ASSERT(setCapacityControl("FanCycling"));
  OS_ASSERT(setNumberofCells(1));
  OS_ASSERT(setCellControl("MinimalCell"));
  OS_ASSERT(setCellMinimumWaterFlowRateFraction(0.33));
  OS_ASSERT(setCellMaximumWaterFlowRateFraction(2.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setFreeConvectionAirFlowRateSizingFactor(0.1));
  OS_ASSERT(setFreeConvectionUFactorTimesAreaValueSizingFactor(0.1));
  OS_ASSERT(setHeatRejectionCapacityAndNominalCapacitySizingRatio(1.25));
  OS_ASSERT(setFreeConvectionNominalCapacitySizingFactor(0.1));
  OS_ASSERT(setDesignInletAirDryBulbTemperature(35.0));
  OS_ASSERT(setDesignInletAirWetBulbTemperature(25.6));
  autosizeDesignApproachTemperature();
  autosizeDesignRangeTemperature();
  OS_ASSERT(setEndUseSubcategory("General"));
}

CoolingTowerSingleSpeed::CoolingTowerSingleSpeed(std::shared_ptr<detail::CoolingTowerSingleSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoolingTowerSingleSpeed::iddObjectType() {
  return IddObjectType::CoolingTower_SingleSpeed;
}

std::vector<std::string> CoolingTowerSingleSpeed::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_SingleSpeedFields::PerformanceInputMethod);
}

std::vector<std::string> CoolingTowerSingleSpeed::evaporationLossModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_SingleSpeedFields::EvaporationLossMode);
}

std::vector<std::string> CoolingTowerSingleSpeed::blowdownCalculationModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::CoolingTower_SingleSpeedFields::BlowdownCalculationMode);
}

std::vector<std::string> CoolingTowerSingleSpeed::capacityControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_SingleSpeedFields::CapacityControl);
}

std::vector<std::string> CoolingTowerSingleSpeed::cellControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_SingleSpeedFields::CellControl);
}

boost::optional<double> CoolingTowerSingleSpeed::designWaterFlowRate() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->designWaterFlowRate();
}

bool CoolingTowerSingleSpeed::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isDesignWaterFlowRateAutosized();
}

bool CoolingTowerSingleSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
}

void CoolingTowerSingleSpeed::resetDesignWaterFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetDesignWaterFlowRate();
}

void CoolingTowerSingleSpeed::autosizeDesignWaterFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeDesignWaterFlowRate();
}

boost::optional<double> CoolingTowerSingleSpeed::designAirFlowRate() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->designAirFlowRate();
}

bool CoolingTowerSingleSpeed::isDesignAirFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isDesignAirFlowRateAutosized();
}

bool CoolingTowerSingleSpeed::setDesignAirFlowRate(double designAirFlowRate) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDesignAirFlowRate(designAirFlowRate);
}

void CoolingTowerSingleSpeed::autosizeDesignAirFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeDesignAirFlowRate();
}

boost::optional<double> CoolingTowerSingleSpeed::fanPoweratDesignAirFlowRate() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->fanPoweratDesignAirFlowRate();
}

bool CoolingTowerSingleSpeed::isFanPoweratDesignAirFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isFanPoweratDesignAirFlowRateAutosized();
}

bool CoolingTowerSingleSpeed::setFanPoweratDesignAirFlowRate(double fanPoweratDesignAirFlowRate) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setFanPoweratDesignAirFlowRate(fanPoweratDesignAirFlowRate);
}

void CoolingTowerSingleSpeed::autosizeFanPoweratDesignAirFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeFanPoweratDesignAirFlowRate();
}

boost::optional<double> CoolingTowerSingleSpeed::uFactorTimesAreaValueatDesignAirFlowRate() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->uFactorTimesAreaValueatDesignAirFlowRate();
}

bool CoolingTowerSingleSpeed::isUFactorTimesAreaValueatDesignAirFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isUFactorTimesAreaValueatDesignAirFlowRateAutosized();
}

bool CoolingTowerSingleSpeed::setUFactorTimesAreaValueatDesignAirFlowRate(double uFactorTimesAreaValueatDesignAirFlowRate) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setUFactorTimesAreaValueatDesignAirFlowRate(uFactorTimesAreaValueatDesignAirFlowRate);
}

void CoolingTowerSingleSpeed::resetUFactorTimesAreaValueatDesignAirFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetUFactorTimesAreaValueatDesignAirFlowRate();
}

void CoolingTowerSingleSpeed::autosizeUFactorTimesAreaValueatDesignAirFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeUFactorTimesAreaValueatDesignAirFlowRate();
}

boost::optional<double> CoolingTowerSingleSpeed::airFlowRateinFreeConvectionRegime() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->airFlowRateinFreeConvectionRegime();
}

bool CoolingTowerSingleSpeed::isAirFlowRateinFreeConvectionRegimeDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isAirFlowRateinFreeConvectionRegimeDefaulted();
}

bool CoolingTowerSingleSpeed::isAirFlowRateinFreeConvectionRegimeAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isAirFlowRateinFreeConvectionRegimeAutosized();
}

bool CoolingTowerSingleSpeed::setAirFlowRateinFreeConvectionRegime(double airFlowRateinFreeConvectionRegime) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setAirFlowRateinFreeConvectionRegime(airFlowRateinFreeConvectionRegime);
}

void CoolingTowerSingleSpeed::resetAirFlowRateinFreeConvectionRegime() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetAirFlowRateinFreeConvectionRegime();
}

void CoolingTowerSingleSpeed::autosizeAirFlowRateinFreeConvectionRegime() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeAirFlowRateinFreeConvectionRegime();
}

boost::optional<double> CoolingTowerSingleSpeed::uFactorTimesAreaValueatFreeConvectionAirFlowRate() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->uFactorTimesAreaValueatFreeConvectionAirFlowRate();
}

bool CoolingTowerSingleSpeed::isUFactorTimesAreaValueatFreeConvectionAirFlowRateDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isUFactorTimesAreaValueatFreeConvectionAirFlowRateDefaulted();
}

bool CoolingTowerSingleSpeed::isUFactorTimesAreaValueatFreeConvectionAirFlowRateAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isUFactorTimesAreaValueatFreeConvectionAirFlowRateAutosized();
}

bool CoolingTowerSingleSpeed::setUFactorTimesAreaValueatFreeConvectionAirFlowRate(double uFactorTimesAreaValueatFreeConvectionAirFlowRate) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setUFactorTimesAreaValueatFreeConvectionAirFlowRate(
    uFactorTimesAreaValueatFreeConvectionAirFlowRate);
}

void CoolingTowerSingleSpeed::resetUFactorTimesAreaValueatFreeConvectionAirFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetUFactorTimesAreaValueatFreeConvectionAirFlowRate();
}

void CoolingTowerSingleSpeed::autosizeUFactorTimesAreaValueatFreeConvectionAirFlowRate() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeUFactorTimesAreaValueatFreeConvectionAirFlowRate();
}

std::string CoolingTowerSingleSpeed::performanceInputMethod() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->performanceInputMethod();
}

bool CoolingTowerSingleSpeed::isPerformanceInputMethodDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isPerformanceInputMethodDefaulted();
}

bool CoolingTowerSingleSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
}

void CoolingTowerSingleSpeed::resetPerformanceInputMethod() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetPerformanceInputMethod();
}

boost::optional<double> CoolingTowerSingleSpeed::nominalCapacity() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->nominalCapacity();
}

bool CoolingTowerSingleSpeed::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setNominalCapacity(nominalCapacity);
}

void CoolingTowerSingleSpeed::resetNominalCapacity() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetNominalCapacity();
}

boost::optional<double> CoolingTowerSingleSpeed::freeConvectionCapacity() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->freeConvectionCapacity();
}

bool CoolingTowerSingleSpeed::setFreeConvectionCapacity(double freeConvectionCapacity) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setFreeConvectionCapacity(freeConvectionCapacity);
}

void CoolingTowerSingleSpeed::resetFreeConvectionCapacity() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetFreeConvectionCapacity();
}

double CoolingTowerSingleSpeed::basinHeaterCapacity() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->basinHeaterCapacity();
}

bool CoolingTowerSingleSpeed::isBasinHeaterCapacityDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isBasinHeaterCapacityDefaulted();
}

bool CoolingTowerSingleSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

void CoolingTowerSingleSpeed::resetBasinHeaterCapacity() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetBasinHeaterCapacity();
}

double CoolingTowerSingleSpeed::basinHeaterSetpointTemperature() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->basinHeaterSetpointTemperature();
}

bool CoolingTowerSingleSpeed::isBasinHeaterSetpointTemperatureDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
}

bool CoolingTowerSingleSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

void CoolingTowerSingleSpeed::resetBasinHeaterSetpointTemperature() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetBasinHeaterSetpointTemperature();
}

boost::optional<Schedule> CoolingTowerSingleSpeed::basinHeaterOperatingSchedule() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->basinHeaterOperatingSchedule();
}

bool CoolingTowerSingleSpeed::setBasinHeaterOperatingSchedule(Schedule& basinHeaterOperatingSchedule) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setBasinHeaterOperatingSchedule(basinHeaterOperatingSchedule);
}

void CoolingTowerSingleSpeed::resetBasinHeaterOperatingSchedule() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetBasinHeaterOperatingSchedule();
}

std::string CoolingTowerSingleSpeed::evaporationLossMode() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->evaporationLossMode();
}

bool CoolingTowerSingleSpeed::isEvaporationLossModeDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isEvaporationLossModeDefaulted();
}

bool CoolingTowerSingleSpeed::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setEvaporationLossMode(evaporationLossMode);
}

void CoolingTowerSingleSpeed::resetEvaporationLossMode() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetEvaporationLossMode();
}

double CoolingTowerSingleSpeed::evaporationLossFactor() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->evaporationLossFactor();
}

bool CoolingTowerSingleSpeed::isEvaporationLossFactorDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isEvaporationLossFactorDefaulted();
}

bool CoolingTowerSingleSpeed::setEvaporationLossFactor(double evaporationLossFactor) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setEvaporationLossFactor(evaporationLossFactor);
}

void CoolingTowerSingleSpeed::resetEvaporationLossFactor() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetEvaporationLossFactor();
}

double CoolingTowerSingleSpeed::driftLossPercent() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->driftLossPercent();
}

bool CoolingTowerSingleSpeed::isDriftLossPercentDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isDriftLossPercentDefaulted();
}

bool CoolingTowerSingleSpeed::setDriftLossPercent(double driftLossPercent) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDriftLossPercent(driftLossPercent);
}

void CoolingTowerSingleSpeed::resetDriftLossPercent() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetDriftLossPercent();
}

std::string CoolingTowerSingleSpeed::blowdownCalculationMode() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->blowdownCalculationMode();
}

bool CoolingTowerSingleSpeed::isBlowdownCalculationModeDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isBlowdownCalculationModeDefaulted();
}

bool CoolingTowerSingleSpeed::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setBlowdownCalculationMode(blowdownCalculationMode);
}

void CoolingTowerSingleSpeed::resetBlowdownCalculationMode() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetBlowdownCalculationMode();
}

double CoolingTowerSingleSpeed::blowdownConcentrationRatio() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->blowdownConcentrationRatio();
}

bool CoolingTowerSingleSpeed::isBlowdownConcentrationRatioDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isBlowdownConcentrationRatioDefaulted();
}

bool CoolingTowerSingleSpeed::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
}

void CoolingTowerSingleSpeed::resetBlowdownConcentrationRatio() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetBlowdownConcentrationRatio();
}

boost::optional<Schedule> CoolingTowerSingleSpeed::blowdownMakeupWaterUsageSchedule() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->blowdownMakeupWaterUsageSchedule();
}

bool CoolingTowerSingleSpeed::setBlowdownMakeupWaterUsageSchedule(Schedule& blowdownMakeupWaterUsageSchedule) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setBlowdownMakeupWaterUsageSchedule(blowdownMakeupWaterUsageSchedule);
}

void CoolingTowerSingleSpeed::resetBlowdownMakeupWaterUsageSchedule() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetBlowdownMakeupWaterUsageSchedule();
}

std::string CoolingTowerSingleSpeed::capacityControl() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->capacityControl();
}

bool CoolingTowerSingleSpeed::isCapacityControlDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isCapacityControlDefaulted();
}

bool CoolingTowerSingleSpeed::setCapacityControl(const std::string& capacityControl) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setCapacityControl(capacityControl);
}

void CoolingTowerSingleSpeed::resetCapacityControl() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetCapacityControl();
}

int CoolingTowerSingleSpeed::numberofCells() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->numberofCells();
}

bool CoolingTowerSingleSpeed::isNumberofCellsDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isNumberofCellsDefaulted();
}

bool CoolingTowerSingleSpeed::setNumberofCells(int numberofCells) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setNumberofCells(numberofCells);
}

void CoolingTowerSingleSpeed::resetNumberofCells() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetNumberofCells();
}

std::string CoolingTowerSingleSpeed::cellControl() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->cellControl();
}

bool CoolingTowerSingleSpeed::isCellControlDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isCellControlDefaulted();
}

bool CoolingTowerSingleSpeed::setCellControl(const std::string& cellControl) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setCellControl(cellControl);
}

void CoolingTowerSingleSpeed::resetCellControl() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetCellControl();
}

double CoolingTowerSingleSpeed::cellMinimumWaterFlowRateFraction() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->cellMinimumWaterFlowRateFraction();
}

bool CoolingTowerSingleSpeed::isCellMinimumWaterFlowRateFractionDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isCellMinimumWaterFlowRateFractionDefaulted();
}

bool CoolingTowerSingleSpeed::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setCellMinimumWaterFlowRateFraction(cellMinimumWaterFlowRateFraction);
}

void CoolingTowerSingleSpeed::resetCellMinimumWaterFlowRateFraction() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetCellMinimumWaterFlowRateFraction();
}

double CoolingTowerSingleSpeed::cellMaximumWaterFlowRateFraction() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->cellMaximumWaterFlowRateFraction();
}

bool CoolingTowerSingleSpeed::isCellMaximumWaterFlowRateFractionDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isCellMaximumWaterFlowRateFractionDefaulted();
}

bool CoolingTowerSingleSpeed::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setCellMaximumWaterFlowRateFraction(cellMaximumWaterFlowRateFraction);
}

void CoolingTowerSingleSpeed::resetCellMaximumWaterFlowRateFraction() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetCellMaximumWaterFlowRateFraction();
}

double CoolingTowerSingleSpeed::sizingFactor() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->sizingFactor();
}

bool CoolingTowerSingleSpeed::isSizingFactorDefaulted() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isSizingFactorDefaulted();
}

bool CoolingTowerSingleSpeed::setSizingFactor(double sizingFactor) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setSizingFactor(sizingFactor);
}

void CoolingTowerSingleSpeed::resetSizingFactor() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->resetSizingFactor();
}

double CoolingTowerSingleSpeed::freeConvectionAirFlowRateSizingFactor() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->freeConvectionAirFlowRateSizingFactor();
}

bool CoolingTowerSingleSpeed::setFreeConvectionAirFlowRateSizingFactor(double freeConvectionAirFlowRateSizingFactor) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setFreeConvectionAirFlowRateSizingFactor(freeConvectionAirFlowRateSizingFactor);
}

double CoolingTowerSingleSpeed::freeConvectionUFactorTimesAreaValueSizingFactor() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->freeConvectionUFactorTimesAreaValueSizingFactor();
}

bool CoolingTowerSingleSpeed::setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setFreeConvectionUFactorTimesAreaValueSizingFactor(
    freeConvectionUFactorTimesAreaValueSizingFactor);
}

double CoolingTowerSingleSpeed::heatRejectionCapacityAndNominalCapacitySizingRatio() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->heatRejectionCapacityAndNominalCapacitySizingRatio();
}

bool CoolingTowerSingleSpeed::setHeatRejectionCapacityAndNominalCapacitySizingRatio(double heatRejectionCapacityAndNominalCapacitySizingRatio) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setHeatRejectionCapacityAndNominalCapacitySizingRatio(
    heatRejectionCapacityAndNominalCapacitySizingRatio);
}

double CoolingTowerSingleSpeed::freeConvectionNominalCapacitySizingFactor() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->freeConvectionNominalCapacitySizingFactor();
}

bool CoolingTowerSingleSpeed::setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setFreeConvectionNominalCapacitySizingFactor(freeConvectionNominalCapacitySizingFactor);
}

double CoolingTowerSingleSpeed::designInletAirDryBulbTemperature() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->designInletAirDryBulbTemperature();
}

bool CoolingTowerSingleSpeed::setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDesignInletAirDryBulbTemperature(designInletAirDryBulbTemperature);
}

double CoolingTowerSingleSpeed::designInletAirWetBulbTemperature() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->designInletAirWetBulbTemperature();
}

bool CoolingTowerSingleSpeed::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDesignInletAirWetBulbTemperature(designInletAirWetBulbTemperature);
}

boost::optional<double> CoolingTowerSingleSpeed::designApproachTemperature() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->designApproachTemperature();
}

bool CoolingTowerSingleSpeed::isDesignApproachTemperatureAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isDesignApproachTemperatureAutosized();
}

bool CoolingTowerSingleSpeed::setDesignApproachTemperature(double designApproachTemperature) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDesignApproachTemperature(designApproachTemperature);
}

void CoolingTowerSingleSpeed::autosizeDesignApproachTemperature() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeDesignApproachTemperature();
}

boost::optional<double> CoolingTowerSingleSpeed::designRangeTemperature() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->designRangeTemperature();
}

bool CoolingTowerSingleSpeed::isDesignRangeTemperatureAutosized() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->isDesignRangeTemperatureAutosized();
}

bool CoolingTowerSingleSpeed::setDesignRangeTemperature(double designRangeTemperature) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setDesignRangeTemperature(designRangeTemperature);
}

void CoolingTowerSingleSpeed::autosizeDesignRangeTemperature() {
  getImpl<detail::CoolingTowerSingleSpeed_Impl>()->autosizeDesignRangeTemperature();
}

std::string CoolingTowerSingleSpeed::endUseSubcategory() const {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->endUseSubcategory();
}

bool CoolingTowerSingleSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::CoolingTowerSingleSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoolingTowerSingleSpeed_Impl::inletPort() const {
  return openstudio::CoolingTower_SingleSpeedFields::WaterInletNodeName;
}

unsigned CoolingTowerSingleSpeed_Impl::outletPort() const {
  return openstudio::CoolingTower_SingleSpeedFields::WaterOutletNodeName;
}

bool CoolingTowerSingleSpeed_Impl::addToNode(Node& node) {
  if (auto plantLoop = node.plantLoop()) {
    if (plantLoop->supplyComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
  }

  return false;
}

std::vector<std::string> CoolingTowerSingleSpeed_Impl::performanceInputMethodValues() const {
  return openstudio::epmodel::CoolingTowerSingleSpeed::performanceInputMethodValues();
}

std::vector<std::string> CoolingTowerSingleSpeed_Impl::evaporationLossModeValues() const {
  return openstudio::epmodel::CoolingTowerSingleSpeed::evaporationLossModeValues();
}

std::vector<std::string> CoolingTowerSingleSpeed_Impl::blowdownCalculationModeValues() const {
  return openstudio::epmodel::CoolingTowerSingleSpeed::blowdownCalculationModeValues();
}

std::vector<std::string> CoolingTowerSingleSpeed_Impl::capacityControlValues() const {
  return openstudio::epmodel::CoolingTowerSingleSpeed::capacityControlValues();
}

std::vector<std::string> CoolingTowerSingleSpeed_Impl::cellControlValues() const {
  return openstudio::epmodel::CoolingTowerSingleSpeed::cellControlValues();
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignWaterFlowRate, true);
}

bool CoolingTowerSingleSpeed_Impl::isDesignWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::DesignWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setDesignWaterFlowRate(double designWaterFlowRate) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignWaterFlowRate, designWaterFlowRate);
}

void CoolingTowerSingleSpeed_Impl::resetDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignWaterFlowRate, ""));
}

void CoolingTowerSingleSpeed_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignWaterFlowRate, "autosize"));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::designAirFlowRate() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignAirFlowRate, true);
}

bool CoolingTowerSingleSpeed_Impl::isDesignAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::DesignAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setDesignAirFlowRate(double designAirFlowRate) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignAirFlowRate, designAirFlowRate);
}

void CoolingTowerSingleSpeed_Impl::autosizeDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignAirFlowRate, "autosize"));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::fanPoweratDesignAirFlowRate() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignFanPower, true);
}

bool CoolingTowerSingleSpeed_Impl::isFanPoweratDesignAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::DesignFanPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setFanPoweratDesignAirFlowRate(double fanPoweratDesignAirFlowRate) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignFanPower, fanPoweratDesignAirFlowRate);
}

void CoolingTowerSingleSpeed_Impl::autosizeFanPoweratDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignFanPower, "autosize"));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::uFactorTimesAreaValueatDesignAirFlowRate() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignUFactorTimesAreaValue, true);
}

bool CoolingTowerSingleSpeed_Impl::isUFactorTimesAreaValueatDesignAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::DesignUFactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setUFactorTimesAreaValueatDesignAirFlowRate(double uFactorTimesAreaValueatDesignAirFlowRate) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignUFactorTimesAreaValue, uFactorTimesAreaValueatDesignAirFlowRate);
}

void CoolingTowerSingleSpeed_Impl::resetUFactorTimesAreaValueatDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignUFactorTimesAreaValue, ""));
}

void CoolingTowerSingleSpeed_Impl::autosizeUFactorTimesAreaValueatDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignUFactorTimesAreaValue, "autosize"));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::airFlowRateinFreeConvectionRegime() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRate, true);
}

bool CoolingTowerSingleSpeed_Impl::isAirFlowRateinFreeConvectionRegimeDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRate);
}

bool CoolingTowerSingleSpeed_Impl::isAirFlowRateinFreeConvectionRegimeAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setAirFlowRateinFreeConvectionRegime(double airFlowRateinFreeConvectionRegime) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRate, airFlowRateinFreeConvectionRegime);
}

void CoolingTowerSingleSpeed_Impl::resetAirFlowRateinFreeConvectionRegime() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRate, ""));
}

void CoolingTowerSingleSpeed_Impl::autosizeAirFlowRateinFreeConvectionRegime() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRate, "autosize"));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::uFactorTimesAreaValueatFreeConvectionAirFlowRate() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, true);
}

bool CoolingTowerSingleSpeed_Impl::isUFactorTimesAreaValueatFreeConvectionAirFlowRateDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue);
}

bool CoolingTowerSingleSpeed_Impl::isUFactorTimesAreaValueatFreeConvectionAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setUFactorTimesAreaValueatFreeConvectionAirFlowRate(double uFactorTimesAreaValueatFreeConvectionAirFlowRate) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue,
                   uFactorTimesAreaValueatFreeConvectionAirFlowRate);
}

void CoolingTowerSingleSpeed_Impl::resetUFactorTimesAreaValueatFreeConvectionAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, ""));
}

void CoolingTowerSingleSpeed_Impl::autosizeUFactorTimesAreaValueatFreeConvectionAirFlowRate() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, "autosize"));
}

std::string CoolingTowerSingleSpeed_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::CoolingTower_SingleSpeedFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isPerformanceInputMethodDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::PerformanceInputMethod);
}

bool CoolingTowerSingleSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return setString(openstudio::CoolingTower_SingleSpeedFields::PerformanceInputMethod, performanceInputMethod);
}

void CoolingTowerSingleSpeed_Impl::resetPerformanceInputMethod() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::PerformanceInputMethod, ""));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::nominalCapacity() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::NominalCapacity, true);
}

bool CoolingTowerSingleSpeed_Impl::setNominalCapacity(double nominalCapacity) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::NominalCapacity, nominalCapacity);
}

void CoolingTowerSingleSpeed_Impl::resetNominalCapacity() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::NominalCapacity, ""));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::freeConvectionCapacity() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionCapacity, true);
}

bool CoolingTowerSingleSpeed_Impl::setFreeConvectionCapacity(double freeConvectionCapacity) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionCapacity, freeConvectionCapacity);
}

void CoolingTowerSingleSpeed_Impl::resetFreeConvectionCapacity() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionCapacity, ""));
}

double CoolingTowerSingleSpeed_Impl::basinHeaterCapacity() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isBasinHeaterCapacityDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterCapacity);
}

bool CoolingTowerSingleSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
}

void CoolingTowerSingleSpeed_Impl::resetBasinHeaterCapacity() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterCapacity, ""));
}

double CoolingTowerSingleSpeed_Impl::basinHeaterSetpointTemperature() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterSetpointTemperature);
}

bool CoolingTowerSingleSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

void CoolingTowerSingleSpeed_Impl::resetBasinHeaterSetpointTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterSetpointTemperature, ""));
}

boost::optional<Schedule> CoolingTowerSingleSpeed_Impl::basinHeaterOperatingSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterOperatingScheduleName);
}

bool CoolingTowerSingleSpeed_Impl::setBasinHeaterOperatingSchedule(Schedule& basinHeaterOperatingSchedule) {
  return setSchedule(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterOperatingScheduleName, "CoolingTowerSingleSpeed",
                     "Basin Heater Operating", basinHeaterOperatingSchedule);
}

void CoolingTowerSingleSpeed_Impl::resetBasinHeaterOperatingSchedule() {
  OS_ASSERT(setPointer(openstudio::CoolingTower_SingleSpeedFields::BasinHeaterOperatingScheduleName, openstudio::Handle(), false));
}

std::string CoolingTowerSingleSpeed_Impl::evaporationLossMode() const {
  const auto value = getString(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isEvaporationLossModeDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossMode);
}

bool CoolingTowerSingleSpeed_Impl::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return setString(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossMode, evaporationLossMode);
}

void CoolingTowerSingleSpeed_Impl::resetEvaporationLossMode() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossMode, ""));
}

double CoolingTowerSingleSpeed_Impl::evaporationLossFactor() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isEvaporationLossFactorDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossFactor);
}

bool CoolingTowerSingleSpeed_Impl::setEvaporationLossFactor(double evaporationLossFactor) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossFactor, evaporationLossFactor);
}

void CoolingTowerSingleSpeed_Impl::resetEvaporationLossFactor() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::EvaporationLossFactor, ""));
}

double CoolingTowerSingleSpeed_Impl::driftLossPercent() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::DriftLossPercent, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isDriftLossPercentDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::DriftLossPercent);
}

bool CoolingTowerSingleSpeed_Impl::setDriftLossPercent(double driftLossPercent) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DriftLossPercent, driftLossPercent);
}

void CoolingTowerSingleSpeed_Impl::resetDriftLossPercent() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DriftLossPercent, ""));
}

std::string CoolingTowerSingleSpeed_Impl::blowdownCalculationMode() const {
  const auto value = getString(openstudio::CoolingTower_SingleSpeedFields::BlowdownCalculationMode, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isBlowdownCalculationModeDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::BlowdownCalculationMode);
}

bool CoolingTowerSingleSpeed_Impl::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return setString(openstudio::CoolingTower_SingleSpeedFields::BlowdownCalculationMode, blowdownCalculationMode);
}

void CoolingTowerSingleSpeed_Impl::resetBlowdownCalculationMode() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::BlowdownCalculationMode, ""));
}

double CoolingTowerSingleSpeed_Impl::blowdownConcentrationRatio() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::BlowdownConcentrationRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isBlowdownConcentrationRatioDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::BlowdownConcentrationRatio);
}

bool CoolingTowerSingleSpeed_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
}

void CoolingTowerSingleSpeed_Impl::resetBlowdownConcentrationRatio() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::BlowdownConcentrationRatio, ""));
}

boost::optional<Schedule> CoolingTowerSingleSpeed_Impl::blowdownMakeupWaterUsageSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::CoolingTower_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName);
}

bool CoolingTowerSingleSpeed_Impl::setBlowdownMakeupWaterUsageSchedule(Schedule& blowdownMakeupWaterUsageSchedule) {
  return setSchedule(openstudio::CoolingTower_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName, "CoolingTowerSingleSpeed",
                     "Blowdown Makeup Water Usage", blowdownMakeupWaterUsageSchedule);
}

void CoolingTowerSingleSpeed_Impl::resetBlowdownMakeupWaterUsageSchedule() {
  OS_ASSERT(setPointer(openstudio::CoolingTower_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName, openstudio::Handle(), false));
}

std::string CoolingTowerSingleSpeed_Impl::capacityControl() const {
  const auto value = getString(openstudio::CoolingTower_SingleSpeedFields::CapacityControl, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isCapacityControlDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::CapacityControl);
}

bool CoolingTowerSingleSpeed_Impl::setCapacityControl(const std::string& capacityControl) {
  return setString(openstudio::CoolingTower_SingleSpeedFields::CapacityControl, capacityControl);
}

void CoolingTowerSingleSpeed_Impl::resetCapacityControl() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::CapacityControl, ""));
}

int CoolingTowerSingleSpeed_Impl::numberofCells() const {
  const auto value = getInt(openstudio::CoolingTower_SingleSpeedFields::NumberofCells, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isNumberofCellsDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::NumberofCells);
}

bool CoolingTowerSingleSpeed_Impl::setNumberofCells(int numberofCells) {
  return setInt(openstudio::CoolingTower_SingleSpeedFields::NumberofCells, numberofCells);
}

void CoolingTowerSingleSpeed_Impl::resetNumberofCells() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::NumberofCells, ""));
}

std::string CoolingTowerSingleSpeed_Impl::cellControl() const {
  const auto value = getString(openstudio::CoolingTower_SingleSpeedFields::CellControl, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isCellControlDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::CellControl);
}

bool CoolingTowerSingleSpeed_Impl::setCellControl(const std::string& cellControl) {
  return setString(openstudio::CoolingTower_SingleSpeedFields::CellControl, cellControl);
}

void CoolingTowerSingleSpeed_Impl::resetCellControl() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::CellControl, ""));
}

double CoolingTowerSingleSpeed_Impl::cellMinimumWaterFlowRateFraction() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::CellMinimumWaterFlowRateFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isCellMinimumWaterFlowRateFractionDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::CellMinimumWaterFlowRateFraction);
}

bool CoolingTowerSingleSpeed_Impl::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::CellMinimumWaterFlowRateFraction, cellMinimumWaterFlowRateFraction);
}

void CoolingTowerSingleSpeed_Impl::resetCellMinimumWaterFlowRateFraction() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::CellMinimumWaterFlowRateFraction, ""));
}

double CoolingTowerSingleSpeed_Impl::cellMaximumWaterFlowRateFraction() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::CellMaximumWaterFlowRateFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isCellMaximumWaterFlowRateFractionDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::CellMaximumWaterFlowRateFraction);
}

bool CoolingTowerSingleSpeed_Impl::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::CellMaximumWaterFlowRateFraction, cellMaximumWaterFlowRateFraction);
}

void CoolingTowerSingleSpeed_Impl::resetCellMaximumWaterFlowRateFraction() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::CellMaximumWaterFlowRateFraction, ""));
}

double CoolingTowerSingleSpeed_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::CoolingTower_SingleSpeedFields::SizingFactor);
}

bool CoolingTowerSingleSpeed_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::SizingFactor, sizingFactor);
}

void CoolingTowerSingleSpeed_Impl::resetSizingFactor() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::SizingFactor, ""));
}

double CoolingTowerSingleSpeed_Impl::freeConvectionAirFlowRateSizingFactor() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setFreeConvectionAirFlowRateSizingFactor(double freeConvectionAirFlowRateSizingFactor) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor,
                   freeConvectionAirFlowRateSizingFactor);
}

double CoolingTowerSingleSpeed_Impl::freeConvectionUFactorTimesAreaValueSizingFactor() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor,
                   freeConvectionUFactorTimesAreaValueSizingFactor);
}

double CoolingTowerSingleSpeed_Impl::heatRejectionCapacityAndNominalCapacitySizingRatio() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setHeatRejectionCapacityAndNominalCapacitySizingRatio(double heatRejectionCapacityAndNominalCapacitySizingRatio) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio,
                   heatRejectionCapacityAndNominalCapacitySizingRatio);
}

double CoolingTowerSingleSpeed_Impl::freeConvectionNominalCapacitySizingFactor() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionNominalCapacitySizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::FreeConvectionNominalCapacitySizingFactor,
                   freeConvectionNominalCapacitySizingFactor);
}

double CoolingTowerSingleSpeed_Impl::designInletAirDryBulbTemperature() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignInletAirDryBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignInletAirDryBulbTemperature, designInletAirDryBulbTemperature);
}

double CoolingTowerSingleSpeed_Impl::designInletAirWetBulbTemperature() const {
  const auto value = getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignInletAirWetBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignInletAirWetBulbTemperature, designInletAirWetBulbTemperature);
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::designApproachTemperature() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignApproachTemperature, true);
}

bool CoolingTowerSingleSpeed_Impl::isDesignApproachTemperatureAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::DesignApproachTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setDesignApproachTemperature(double designApproachTemperature) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignApproachTemperature, designApproachTemperature);
}

void CoolingTowerSingleSpeed_Impl::autosizeDesignApproachTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignApproachTemperature, "autosize"));
}

boost::optional<double> CoolingTowerSingleSpeed_Impl::designRangeTemperature() const {
  return getDouble(openstudio::CoolingTower_SingleSpeedFields::DesignRangeTemperature, true);
}

bool CoolingTowerSingleSpeed_Impl::isDesignRangeTemperatureAutosized() const {
  if (auto value = getString(openstudio::CoolingTower_SingleSpeedFields::DesignRangeTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoolingTowerSingleSpeed_Impl::setDesignRangeTemperature(double designRangeTemperature) {
  return setDouble(openstudio::CoolingTower_SingleSpeedFields::DesignRangeTemperature, designRangeTemperature);
}

void CoolingTowerSingleSpeed_Impl::autosizeDesignRangeTemperature() {
  OS_ASSERT(setString(openstudio::CoolingTower_SingleSpeedFields::DesignRangeTemperature, "autosize"));
}

std::string CoolingTowerSingleSpeed_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::CoolingTower_SingleSpeedFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool CoolingTowerSingleSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return setString(openstudio::CoolingTower_SingleSpeedFields::EndUseSubcategory, endUseSubcategory);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
