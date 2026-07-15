/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoolingTowerTwoSpeed.hpp"
#include "StraightComponent/CoolingTowerTwoSpeed_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoolingTower_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CoolingTowerTwoSpeed::CoolingTowerTwoSpeed(const Model& model) : StraightComponent(CoolingTowerTwoSpeed::iddObjectType(), model) {
    autosizeDesignWaterFlowRate();
    autosizeHighFanSpeedAirFlowRate();
    autosizeHighFanSpeedFanPower();
    autosizeHighFanSpeedUFactorTimesAreaValue();
    autosizeLowFanSpeedAirFlowRate();
    autosizeLowFanSpeedFanPower();
    autosizeLowFanSpeedUFactorTimesAreaValue();
    OS_ASSERT(setSizingFactor(1.0));
    OS_ASSERT(setDesignInletAirDryBulbTemperature(35.0));
    OS_ASSERT(setDesignInletAirWetBulbTemperature(25.6));
    autosizeDesignApproachTemperature();
    autosizeDesignRangeTemperature();
    OS_ASSERT(setEndUseSubcategory("General"));
  }

  CoolingTowerTwoSpeed::CoolingTowerTwoSpeed(std::shared_ptr<detail::CoolingTowerTwoSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoolingTowerTwoSpeed::iddObjectType() {
    return IddObjectType::CoolingTower_TwoSpeed;
  }

  std::vector<std::string> CoolingTowerTwoSpeed::performanceInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_TwoSpeedFields::PerformanceInputMethod);
  }

  std::vector<std::string> CoolingTowerTwoSpeed::evaporationLossModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_TwoSpeedFields::EvaporationLossMode);
  }

  std::vector<std::string> CoolingTowerTwoSpeed::blowdownCalculationModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_TwoSpeedFields::BlowdownCalculationMode);
  }

  std::vector<std::string> CoolingTowerTwoSpeed::cellControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_TwoSpeedFields::CellControl);
  }

  boost::optional<double> CoolingTowerTwoSpeed::designWaterFlowRate() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->designWaterFlowRate();
  }

  bool CoolingTowerTwoSpeed::isDesignWaterFlowRateAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isDesignWaterFlowRateAutosized();
  }

  bool CoolingTowerTwoSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
  }

  void CoolingTowerTwoSpeed::resetDesignWaterFlowRate() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetDesignWaterFlowRate();
  }

  void CoolingTowerTwoSpeed::autosizeDesignWaterFlowRate() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeDesignWaterFlowRate();
  }

  boost::optional<double> CoolingTowerTwoSpeed::highFanSpeedAirFlowRate() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->highFanSpeedAirFlowRate();
  }

  bool CoolingTowerTwoSpeed::isHighFanSpeedAirFlowRateAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isHighFanSpeedAirFlowRateAutosized();
  }

  bool CoolingTowerTwoSpeed::setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setHighFanSpeedAirFlowRate(highFanSpeedAirFlowRate);
  }

  void CoolingTowerTwoSpeed::autosizeHighFanSpeedAirFlowRate() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeHighFanSpeedAirFlowRate();
  }

  boost::optional<double> CoolingTowerTwoSpeed::highFanSpeedFanPower() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->highFanSpeedFanPower();
  }

  bool CoolingTowerTwoSpeed::isHighFanSpeedFanPowerAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isHighFanSpeedFanPowerAutosized();
  }

  bool CoolingTowerTwoSpeed::setHighFanSpeedFanPower(double highFanSpeedFanPower) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setHighFanSpeedFanPower(highFanSpeedFanPower);
  }

  void CoolingTowerTwoSpeed::autosizeHighFanSpeedFanPower() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeHighFanSpeedFanPower();
  }

  boost::optional<double> CoolingTowerTwoSpeed::highFanSpeedUFactorTimesAreaValue() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->highFanSpeedUFactorTimesAreaValue();
  }

  bool CoolingTowerTwoSpeed::isHighFanSpeedUFactorTimesAreaValueAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isHighFanSpeedUFactorTimesAreaValueAutosized();
  }

  bool CoolingTowerTwoSpeed::setHighFanSpeedUFactorTimesAreaValue(double highFanSpeedUFactorTimesAreaValue) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setHighFanSpeedUFactorTimesAreaValue(highFanSpeedUFactorTimesAreaValue);
  }

  void CoolingTowerTwoSpeed::resetHighFanSpeedUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetHighFanSpeedUFactorTimesAreaValue();
  }

  void CoolingTowerTwoSpeed::autosizeHighFanSpeedUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeHighFanSpeedUFactorTimesAreaValue();
  }

  boost::optional<double> CoolingTowerTwoSpeed::lowFanSpeedAirFlowRate() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowFanSpeedAirFlowRate();
  }

  bool CoolingTowerTwoSpeed::isLowFanSpeedAirFlowRateAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowFanSpeedAirFlowRateAutosized();
  }

  bool CoolingTowerTwoSpeed::setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRate(lowFanSpeedAirFlowRate);
  }

  void CoolingTowerTwoSpeed::autosizeLowFanSpeedAirFlowRate() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeLowFanSpeedAirFlowRate();
  }

  double CoolingTowerTwoSpeed::lowFanSpeedAirFlowRateSizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowFanSpeedAirFlowRateSizingFactor();
  }

  bool CoolingTowerTwoSpeed::isLowFanSpeedAirFlowRateSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowFanSpeedAirFlowRateSizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRateSizingFactor(lowFanSpeedAirFlowRateSizingFactor);
  }

  void CoolingTowerTwoSpeed::resetLowFanSpeedAirFlowRateSizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetLowFanSpeedAirFlowRateSizingFactor();
  }

  boost::optional<double> CoolingTowerTwoSpeed::lowFanSpeedFanPower() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowFanSpeedFanPower();
  }

  bool CoolingTowerTwoSpeed::isLowFanSpeedFanPowerAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowFanSpeedFanPowerAutosized();
  }

  bool CoolingTowerTwoSpeed::setLowFanSpeedFanPower(double lowFanSpeedFanPower) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowFanSpeedFanPower(lowFanSpeedFanPower);
  }

  void CoolingTowerTwoSpeed::autosizeLowFanSpeedFanPower() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeLowFanSpeedFanPower();
  }

  double CoolingTowerTwoSpeed::lowFanSpeedFanPowerSizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowFanSpeedFanPowerSizingFactor();
  }

  bool CoolingTowerTwoSpeed::isLowFanSpeedFanPowerSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowFanSpeedFanPowerSizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowFanSpeedFanPowerSizingFactor(lowFanSpeedFanPowerSizingFactor);
  }

  void CoolingTowerTwoSpeed::resetLowFanSpeedFanPowerSizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetLowFanSpeedFanPowerSizingFactor();
  }

  boost::optional<double> CoolingTowerTwoSpeed::lowFanSpeedUFactorTimesAreaValue() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowFanSpeedUFactorTimesAreaValue();
  }

  bool CoolingTowerTwoSpeed::isLowFanSpeedUFactorTimesAreaValueAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowFanSpeedUFactorTimesAreaValueAutosized();
  }

  bool CoolingTowerTwoSpeed::setLowFanSpeedUFactorTimesAreaValue(double lowFanSpeedUFactorTimesAreaValue) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowFanSpeedUFactorTimesAreaValue(lowFanSpeedUFactorTimesAreaValue);
  }

  void CoolingTowerTwoSpeed::resetLowFanSpeedUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetLowFanSpeedUFactorTimesAreaValue();
  }

  void CoolingTowerTwoSpeed::autosizeLowFanSpeedUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeLowFanSpeedUFactorTimesAreaValue();
  }

  double CoolingTowerTwoSpeed::lowFanSpeedUFactorTimesAreaSizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowFanSpeedUFactorTimesAreaSizingFactor();
  }

  bool CoolingTowerTwoSpeed::isLowFanSpeedUFactorTimesAreaSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowFanSpeedUFactorTimesAreaSizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowFanSpeedUFactorTimesAreaSizingFactor(lowFanSpeedUFactorTimesAreaSizingFactor);
  }

  void CoolingTowerTwoSpeed::resetLowFanSpeedUFactorTimesAreaSizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetLowFanSpeedUFactorTimesAreaSizingFactor();
  }

  boost::optional<double> CoolingTowerTwoSpeed::freeConvectionRegimeAirFlowRate() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->freeConvectionRegimeAirFlowRate();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionRegimeAirFlowRateDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionRegimeAirFlowRateDefaulted();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionRegimeAirFlowRateAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionRegimeAirFlowRateAutosized();
  }

  bool CoolingTowerTwoSpeed::setFreeConvectionRegimeAirFlowRate(double freeConvectionRegimeAirFlowRate) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setFreeConvectionRegimeAirFlowRate(freeConvectionRegimeAirFlowRate);
  }

  void CoolingTowerTwoSpeed::resetFreeConvectionRegimeAirFlowRate() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetFreeConvectionRegimeAirFlowRate();
  }

  void CoolingTowerTwoSpeed::autosizeFreeConvectionRegimeAirFlowRate() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeFreeConvectionRegimeAirFlowRate();
  }

  double CoolingTowerTwoSpeed::freeConvectionRegimeAirFlowRateSizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->freeConvectionRegimeAirFlowRateSizingFactor();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setFreeConvectionRegimeAirFlowRateSizingFactor(double freeConvectionRegimeAirFlowRateSizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setFreeConvectionRegimeAirFlowRateSizingFactor(freeConvectionRegimeAirFlowRateSizingFactor);
  }

  void CoolingTowerTwoSpeed::resetFreeConvectionRegimeAirFlowRateSizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetFreeConvectionRegimeAirFlowRateSizingFactor();
  }

  boost::optional<double> CoolingTowerTwoSpeed::freeConvectionRegimeUFactorTimesAreaValue() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->freeConvectionRegimeUFactorTimesAreaValue();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionRegimeUFactorTimesAreaValueDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionRegimeUFactorTimesAreaValueDefaulted();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionRegimeUFactorTimesAreaValueAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionRegimeUFactorTimesAreaValueAutosized();
  }

  bool CoolingTowerTwoSpeed::setFreeConvectionRegimeUFactorTimesAreaValue(double freeConvectionRegimeUFactorTimesAreaValue) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setFreeConvectionRegimeUFactorTimesAreaValue(freeConvectionRegimeUFactorTimesAreaValue);
  }

  void CoolingTowerTwoSpeed::resetFreeConvectionRegimeUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetFreeConvectionRegimeUFactorTimesAreaValue();
  }

  void CoolingTowerTwoSpeed::autosizeFreeConvectionRegimeUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeFreeConvectionRegimeUFactorTimesAreaValue();
  }

  double CoolingTowerTwoSpeed::freeConvectionUFactorTimesAreaValueSizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->freeConvectionUFactorTimesAreaValueSizingFactor();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setFreeConvectionUFactorTimesAreaValueSizingFactor(
      freeConvectionUFactorTimesAreaValueSizingFactor);
  }

  void CoolingTowerTwoSpeed::resetFreeConvectionUFactorTimesAreaValueSizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetFreeConvectionUFactorTimesAreaValueSizingFactor();
  }

  std::string CoolingTowerTwoSpeed::performanceInputMethod() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->performanceInputMethod();
  }

  bool CoolingTowerTwoSpeed::isPerformanceInputMethodDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isPerformanceInputMethodDefaulted();
  }

  bool CoolingTowerTwoSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
  }

  void CoolingTowerTwoSpeed::resetPerformanceInputMethod() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetPerformanceInputMethod();
  }

  double CoolingTowerTwoSpeed::heatRejectionCapacityandNominalCapacitySizingRatio() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->heatRejectionCapacityandNominalCapacitySizingRatio();
  }

  bool CoolingTowerTwoSpeed::isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted();
  }

  bool CoolingTowerTwoSpeed::setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setHeatRejectionCapacityandNominalCapacitySizingRatio(
      heatRejectionCapacityandNominalCapacitySizingRatio);
  }

  void CoolingTowerTwoSpeed::resetHeatRejectionCapacityandNominalCapacitySizingRatio() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetHeatRejectionCapacityandNominalCapacitySizingRatio();
  }

  boost::optional<double> CoolingTowerTwoSpeed::highSpeedNominalCapacity() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->highSpeedNominalCapacity();
  }

  bool CoolingTowerTwoSpeed::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setHighSpeedNominalCapacity(highSpeedNominalCapacity);
  }

  void CoolingTowerTwoSpeed::resetHighSpeedNominalCapacity() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetHighSpeedNominalCapacity();
  }

  boost::optional<double> CoolingTowerTwoSpeed::lowSpeedNominalCapacity() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowSpeedNominalCapacity();
  }

  bool CoolingTowerTwoSpeed::isLowSpeedNominalCapacityAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowSpeedNominalCapacityAutosized();
  }

  bool CoolingTowerTwoSpeed::setLowSpeedNominalCapacity(double lowSpeedNominalCapacity) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowSpeedNominalCapacity(lowSpeedNominalCapacity);
  }

  void CoolingTowerTwoSpeed::resetLowSpeedNominalCapacity() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetLowSpeedNominalCapacity();
  }

  void CoolingTowerTwoSpeed::autosizeLowSpeedNominalCapacity() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeLowSpeedNominalCapacity();
  }

  double CoolingTowerTwoSpeed::lowSpeedNominalCapacitySizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->lowSpeedNominalCapacitySizingFactor();
  }

  bool CoolingTowerTwoSpeed::isLowSpeedNominalCapacitySizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isLowSpeedNominalCapacitySizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setLowSpeedNominalCapacitySizingFactor(lowSpeedNominalCapacitySizingFactor);
  }

  void CoolingTowerTwoSpeed::resetLowSpeedNominalCapacitySizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetLowSpeedNominalCapacitySizingFactor();
  }

  boost::optional<double> CoolingTowerTwoSpeed::freeConvectionNominalCapacity() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->freeConvectionNominalCapacity();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionNominalCapacityAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionNominalCapacityAutosized();
  }

  bool CoolingTowerTwoSpeed::setFreeConvectionNominalCapacity(double freeConvectionNominalCapacity) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setFreeConvectionNominalCapacity(freeConvectionNominalCapacity);
  }

  void CoolingTowerTwoSpeed::resetFreeConvectionNominalCapacity() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetFreeConvectionNominalCapacity();
  }

  void CoolingTowerTwoSpeed::autosizeFreeConvectionNominalCapacity() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeFreeConvectionNominalCapacity();
  }

  double CoolingTowerTwoSpeed::freeConvectionNominalCapacitySizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->freeConvectionNominalCapacitySizingFactor();
  }

  bool CoolingTowerTwoSpeed::isFreeConvectionNominalCapacitySizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isFreeConvectionNominalCapacitySizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setFreeConvectionNominalCapacitySizingFactor(freeConvectionNominalCapacitySizingFactor);
  }

  void CoolingTowerTwoSpeed::resetFreeConvectionNominalCapacitySizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetFreeConvectionNominalCapacitySizingFactor();
  }

  double CoolingTowerTwoSpeed::basinHeaterCapacity() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->basinHeaterCapacity();
  }

  bool CoolingTowerTwoSpeed::isBasinHeaterCapacityDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isBasinHeaterCapacityDefaulted();
  }

  bool CoolingTowerTwoSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  void CoolingTowerTwoSpeed::resetBasinHeaterCapacity() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetBasinHeaterCapacity();
  }

  double CoolingTowerTwoSpeed::basinHeaterSetpointTemperature() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->basinHeaterSetpointTemperature();
  }

  bool CoolingTowerTwoSpeed::isBasinHeaterSetpointTemperatureDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
  }

  bool CoolingTowerTwoSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  void CoolingTowerTwoSpeed::resetBasinHeaterSetpointTemperature() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetBasinHeaterSetpointTemperature();
  }

  boost::optional<Schedule> CoolingTowerTwoSpeed::basinHeaterOperatingSchedule() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->basinHeaterOperatingSchedule();
  }

  bool CoolingTowerTwoSpeed::setBasinHeaterOperatingSchedule(Schedule& basinHeaterOperatingSchedule) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setBasinHeaterOperatingSchedule(basinHeaterOperatingSchedule);
  }

  void CoolingTowerTwoSpeed::resetBasinHeaterOperatingSchedule() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetBasinHeaterOperatingSchedule();
  }

  std::string CoolingTowerTwoSpeed::evaporationLossMode() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->evaporationLossMode();
  }

  bool CoolingTowerTwoSpeed::isEvaporationLossModeDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isEvaporationLossModeDefaulted();
  }

  bool CoolingTowerTwoSpeed::setEvaporationLossMode(const std::string& evaporationLossMode) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setEvaporationLossMode(evaporationLossMode);
  }

  void CoolingTowerTwoSpeed::resetEvaporationLossMode() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetEvaporationLossMode();
  }

  double CoolingTowerTwoSpeed::evaporationLossFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->evaporationLossFactor();
  }

  bool CoolingTowerTwoSpeed::isEvaporationLossFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isEvaporationLossFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setEvaporationLossFactor(double evaporationLossFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setEvaporationLossFactor(evaporationLossFactor);
  }

  void CoolingTowerTwoSpeed::resetEvaporationLossFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetEvaporationLossFactor();
  }

  double CoolingTowerTwoSpeed::driftLossPercent() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->driftLossPercent();
  }

  bool CoolingTowerTwoSpeed::isDriftLossPercentDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isDriftLossPercentDefaulted();
  }

  bool CoolingTowerTwoSpeed::setDriftLossPercent(double driftLossPercent) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setDriftLossPercent(driftLossPercent);
  }

  void CoolingTowerTwoSpeed::resetDriftLossPercent() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetDriftLossPercent();
  }

  std::string CoolingTowerTwoSpeed::blowdownCalculationMode() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->blowdownCalculationMode();
  }

  bool CoolingTowerTwoSpeed::isBlowdownCalculationModeDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isBlowdownCalculationModeDefaulted();
  }

  bool CoolingTowerTwoSpeed::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setBlowdownCalculationMode(blowdownCalculationMode);
  }

  void CoolingTowerTwoSpeed::resetBlowdownCalculationMode() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetBlowdownCalculationMode();
  }

  double CoolingTowerTwoSpeed::blowdownConcentrationRatio() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->blowdownConcentrationRatio();
  }

  bool CoolingTowerTwoSpeed::isBlowdownConcentrationRatioDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isBlowdownConcentrationRatioDefaulted();
  }

  bool CoolingTowerTwoSpeed::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
  }

  void CoolingTowerTwoSpeed::resetBlowdownConcentrationRatio() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetBlowdownConcentrationRatio();
  }

  boost::optional<Schedule> CoolingTowerTwoSpeed::blowdownMakeupWaterUsageSchedule() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->blowdownMakeupWaterUsageSchedule();
  }

  bool CoolingTowerTwoSpeed::setBlowdownMakeupWaterUsageSchedule(Schedule& blowdownMakeupWaterUsageSchedule) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setBlowdownMakeupWaterUsageSchedule(blowdownMakeupWaterUsageSchedule);
  }

  void CoolingTowerTwoSpeed::resetBlowdownMakeupWaterUsageSchedule() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetBlowdownMakeupWaterUsageSchedule();
  }

  int CoolingTowerTwoSpeed::numberofCells() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->numberofCells();
  }

  bool CoolingTowerTwoSpeed::isNumberofCellsDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isNumberofCellsDefaulted();
  }

  bool CoolingTowerTwoSpeed::setNumberofCells(int numberofCells) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setNumberofCells(numberofCells);
  }

  void CoolingTowerTwoSpeed::resetNumberofCells() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetNumberofCells();
  }

  std::string CoolingTowerTwoSpeed::cellControl() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->cellControl();
  }

  bool CoolingTowerTwoSpeed::isCellControlDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isCellControlDefaulted();
  }

  bool CoolingTowerTwoSpeed::setCellControl(const std::string& cellControl) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setCellControl(cellControl);
  }

  void CoolingTowerTwoSpeed::resetCellControl() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetCellControl();
  }

  double CoolingTowerTwoSpeed::cellMinimumWaterFlowRateFraction() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->cellMinimumWaterFlowRateFraction();
  }

  bool CoolingTowerTwoSpeed::isCellMinimumWaterFlowRateFractionDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isCellMinimumWaterFlowRateFractionDefaulted();
  }

  bool CoolingTowerTwoSpeed::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setCellMinimumWaterFlowRateFraction(cellMinimumWaterFlowRateFraction);
  }

  void CoolingTowerTwoSpeed::resetCellMinimumWaterFlowRateFraction() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetCellMinimumWaterFlowRateFraction();
  }

  double CoolingTowerTwoSpeed::cellMaximumWaterFlowRateFraction() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->cellMaximumWaterFlowRateFraction();
  }

  bool CoolingTowerTwoSpeed::isCellMaximumWaterFlowRateFractionDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isCellMaximumWaterFlowRateFractionDefaulted();
  }

  bool CoolingTowerTwoSpeed::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setCellMaximumWaterFlowRateFraction(cellMaximumWaterFlowRateFraction);
  }

  void CoolingTowerTwoSpeed::resetCellMaximumWaterFlowRateFraction() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetCellMaximumWaterFlowRateFraction();
  }

  double CoolingTowerTwoSpeed::sizingFactor() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->sizingFactor();
  }

  bool CoolingTowerTwoSpeed::isSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isSizingFactorDefaulted();
  }

  bool CoolingTowerTwoSpeed::setSizingFactor(double sizingFactor) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setSizingFactor(sizingFactor);
  }

  void CoolingTowerTwoSpeed::resetSizingFactor() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->resetSizingFactor();
  }

  double CoolingTowerTwoSpeed::designInletAirDryBulbTemperature() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->designInletAirDryBulbTemperature();
  }

  bool CoolingTowerTwoSpeed::setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setDesignInletAirDryBulbTemperature(designInletAirDryBulbTemperature);
  }

  double CoolingTowerTwoSpeed::designInletAirWetBulbTemperature() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->designInletAirWetBulbTemperature();
  }

  bool CoolingTowerTwoSpeed::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setDesignInletAirWetBulbTemperature(designInletAirWetBulbTemperature);
  }

  boost::optional<double> CoolingTowerTwoSpeed::designApproachTemperature() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->designApproachTemperature();
  }

  bool CoolingTowerTwoSpeed::isDesignApproachTemperatureAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isDesignApproachTemperatureAutosized();
  }

  bool CoolingTowerTwoSpeed::setDesignApproachTemperature(double designApproachTemperature) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setDesignApproachTemperature(designApproachTemperature);
  }

  void CoolingTowerTwoSpeed::autosizeDesignApproachTemperature() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeDesignApproachTemperature();
  }

  boost::optional<double> CoolingTowerTwoSpeed::designRangeTemperature() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->designRangeTemperature();
  }

  bool CoolingTowerTwoSpeed::isDesignRangeTemperatureAutosized() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->isDesignRangeTemperatureAutosized();
  }

  bool CoolingTowerTwoSpeed::setDesignRangeTemperature(double designRangeTemperature) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setDesignRangeTemperature(designRangeTemperature);
  }

  void CoolingTowerTwoSpeed::autosizeDesignRangeTemperature() {
    getImpl<detail::CoolingTowerTwoSpeed_Impl>()->autosizeDesignRangeTemperature();
  }

  std::string CoolingTowerTwoSpeed::endUseSubcategory() const {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->endUseSubcategory();
  }

  bool CoolingTowerTwoSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::CoolingTowerTwoSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoolingTowerTwoSpeed_Impl::inletPort() const {
      return openstudio::CoolingTower_TwoSpeedFields::WaterInletNodeName;
    }

    unsigned CoolingTowerTwoSpeed_Impl::outletPort() const {
      return openstudio::CoolingTower_TwoSpeedFields::WaterOutletNodeName;
    }

    bool CoolingTowerTwoSpeed_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    std::vector<std::string> CoolingTowerTwoSpeed_Impl::performanceInputMethodValues() const {
      return openstudio::epmodel::CoolingTowerTwoSpeed::performanceInputMethodValues();
    }

    std::vector<std::string> CoolingTowerTwoSpeed_Impl::evaporationLossModeValues() const {
      return openstudio::epmodel::CoolingTowerTwoSpeed::evaporationLossModeValues();
    }

    std::vector<std::string> CoolingTowerTwoSpeed_Impl::blowdownCalculationModeValues() const {
      return openstudio::epmodel::CoolingTowerTwoSpeed::blowdownCalculationModeValues();
    }

    std::vector<std::string> CoolingTowerTwoSpeed_Impl::cellControlValues() const {
      return openstudio::epmodel::CoolingTowerTwoSpeed::cellControlValues();
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::designWaterFlowRate() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::DesignWaterFlowRate, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isDesignWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::DesignWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setDesignWaterFlowRate(double designWaterFlowRate) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::DesignWaterFlowRate, designWaterFlowRate);
    }

    void CoolingTowerTwoSpeed_Impl::resetDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::DesignWaterFlowRate, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::DesignWaterFlowRate, "autosize"));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::highFanSpeedAirFlowRate() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedAirFlowRate, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isHighFanSpeedAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedAirFlowRate, highFanSpeedAirFlowRate);
    }

    void CoolingTowerTwoSpeed_Impl::autosizeHighFanSpeedAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedAirFlowRate, "autosize"));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::highFanSpeedFanPower() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedFanPower, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isHighFanSpeedFanPowerAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setHighFanSpeedFanPower(double highFanSpeedFanPower) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedFanPower, highFanSpeedFanPower);
    }

    void CoolingTowerTwoSpeed_Impl::autosizeHighFanSpeedFanPower() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedFanPower, "autosize"));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::highFanSpeedUFactorTimesAreaValue() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isHighFanSpeedUFactorTimesAreaValueAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setHighFanSpeedUFactorTimesAreaValue(double highFanSpeedUFactorTimesAreaValue) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, highFanSpeedUFactorTimesAreaValue);
    }

    void CoolingTowerTwoSpeed_Impl::resetHighFanSpeedUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeHighFanSpeedUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::HighFanSpeedUFactorTimesAreaValue, "autosize"));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::lowFanSpeedAirFlowRate() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isLowFanSpeedAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, lowFanSpeedAirFlowRate);
    }

    void CoolingTowerTwoSpeed_Impl::autosizeLowFanSpeedAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRate, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::lowFanSpeedAirFlowRateSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isLowFanSpeedAirFlowRateSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, lowFanSpeedAirFlowRateSizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetLowFanSpeedAirFlowRateSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::lowFanSpeedFanPower() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isLowFanSpeedFanPowerAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setLowFanSpeedFanPower(double lowFanSpeedFanPower) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, lowFanSpeedFanPower);
    }

    void CoolingTowerTwoSpeed_Impl::autosizeLowFanSpeedFanPower() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPower, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::lowFanSpeedFanPowerSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isLowFanSpeedFanPowerSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, lowFanSpeedFanPowerSizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetLowFanSpeedFanPowerSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::lowFanSpeedUFactorTimesAreaValue() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isLowFanSpeedUFactorTimesAreaValueAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setLowFanSpeedUFactorTimesAreaValue(double lowFanSpeedUFactorTimesAreaValue) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, lowFanSpeedUFactorTimesAreaValue);
    }

    void CoolingTowerTwoSpeed_Impl::resetLowFanSpeedUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeLowFanSpeedUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaValue, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::lowFanSpeedUFactorTimesAreaSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isLowFanSpeedUFactorTimesAreaSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, lowFanSpeedUFactorTimesAreaSizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetLowFanSpeedUFactorTimesAreaSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::freeConvectionRegimeAirFlowRate() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionRegimeAirFlowRateDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate);
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionRegimeAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setFreeConvectionRegimeAirFlowRate(double freeConvectionRegimeAirFlowRate) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, freeConvectionRegimeAirFlowRate);
    }

    void CoolingTowerTwoSpeed_Impl::resetFreeConvectionRegimeAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeFreeConvectionRegimeAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRate, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::freeConvectionRegimeAirFlowRateSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setFreeConvectionRegimeAirFlowRateSizingFactor(double freeConvectionRegimeAirFlowRateSizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor,
                       freeConvectionRegimeAirFlowRateSizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetFreeConvectionRegimeAirFlowRateSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeAirFlowRateSizingFactor, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::freeConvectionRegimeUFactorTimesAreaValue() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionRegimeUFactorTimesAreaValueDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue);
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionRegimeUFactorTimesAreaValueAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setFreeConvectionRegimeUFactorTimesAreaValue(double freeConvectionRegimeUFactorTimesAreaValue) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, freeConvectionRegimeUFactorTimesAreaValue);
    }

    void CoolingTowerTwoSpeed_Impl::resetFreeConvectionRegimeUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeFreeConvectionRegimeUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionRegimeUFactorTimesAreaValue, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::freeConvectionUFactorTimesAreaValueSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor,
                       freeConvectionUFactorTimesAreaValueSizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetFreeConvectionUFactorTimesAreaValueSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionUFactorTimesAreaValueSizingFactor, ""));
    }

    std::string CoolingTowerTwoSpeed_Impl::performanceInputMethod() const {
      const auto value = getString(openstudio::CoolingTower_TwoSpeedFields::PerformanceInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isPerformanceInputMethodDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::PerformanceInputMethod);
    }

    bool CoolingTowerTwoSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
      return setString(openstudio::CoolingTower_TwoSpeedFields::PerformanceInputMethod, performanceInputMethod);
    }

    void CoolingTowerTwoSpeed_Impl::resetPerformanceInputMethod() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::PerformanceInputMethod, ""));
    }

    double CoolingTowerTwoSpeed_Impl::heatRejectionCapacityandNominalCapacitySizingRatio() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio);
    }

    bool CoolingTowerTwoSpeed_Impl::setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio,
                       heatRejectionCapacityandNominalCapacitySizingRatio);
    }

    void CoolingTowerTwoSpeed_Impl::resetHeatRejectionCapacityandNominalCapacitySizingRatio() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::highSpeedNominalCapacity() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::HighSpeedNominalCapacity, true);
    }

    bool CoolingTowerTwoSpeed_Impl::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::HighSpeedNominalCapacity, highSpeedNominalCapacity);
    }

    void CoolingTowerTwoSpeed_Impl::resetHighSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::HighSpeedNominalCapacity, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::lowSpeedNominalCapacity() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isLowSpeedNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setLowSpeedNominalCapacity(double lowSpeedNominalCapacity) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, lowSpeedNominalCapacity);
    }

    void CoolingTowerTwoSpeed_Impl::resetLowSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeLowSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacity, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::lowSpeedNominalCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isLowSpeedNominalCapacitySizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, lowSpeedNominalCapacitySizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetLowSpeedNominalCapacitySizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, ""));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::freeConvectionNominalCapacity() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setFreeConvectionNominalCapacity(double freeConvectionNominalCapacity) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, freeConvectionNominalCapacity);
    }

    void CoolingTowerTwoSpeed_Impl::resetFreeConvectionNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, ""));
    }

    void CoolingTowerTwoSpeed_Impl::autosizeFreeConvectionNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacity, "autocalculate"));
    }

    double CoolingTowerTwoSpeed_Impl::freeConvectionNominalCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isFreeConvectionNominalCapacitySizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacitySizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacitySizingFactor, freeConvectionNominalCapacitySizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetFreeConvectionNominalCapacitySizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::FreeConvectionNominalCapacitySizingFactor, ""));
    }

    double CoolingTowerTwoSpeed_Impl::basinHeaterCapacity() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isBasinHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterCapacity);
    }

    bool CoolingTowerTwoSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    void CoolingTowerTwoSpeed_Impl::resetBasinHeaterCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterCapacity, ""));
    }

    double CoolingTowerTwoSpeed_Impl::basinHeaterSetpointTemperature() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterSetpointTemperature);
    }

    bool CoolingTowerTwoSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
    }

    void CoolingTowerTwoSpeed_Impl::resetBasinHeaterSetpointTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterSetpointTemperature, ""));
    }

    boost::optional<Schedule> CoolingTowerTwoSpeed_Impl::basinHeaterOperatingSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterOperatingScheduleName);
    }

    bool CoolingTowerTwoSpeed_Impl::setBasinHeaterOperatingSchedule(Schedule& basinHeaterOperatingSchedule) {
      return setSchedule(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterOperatingScheduleName, "CoolingTowerTwoSpeed", "Basin Heater Operating",
                         basinHeaterOperatingSchedule);
    }

    void CoolingTowerTwoSpeed_Impl::resetBasinHeaterOperatingSchedule() {
      OS_ASSERT(setPointer(openstudio::CoolingTower_TwoSpeedFields::BasinHeaterOperatingScheduleName, openstudio::Handle(), false));
    }

    std::string CoolingTowerTwoSpeed_Impl::evaporationLossMode() const {
      const auto value = getString(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isEvaporationLossModeDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossMode);
    }

    bool CoolingTowerTwoSpeed_Impl::setEvaporationLossMode(const std::string& evaporationLossMode) {
      return setString(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossMode, evaporationLossMode);
    }

    void CoolingTowerTwoSpeed_Impl::resetEvaporationLossMode() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossMode, ""));
    }

    double CoolingTowerTwoSpeed_Impl::evaporationLossFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isEvaporationLossFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setEvaporationLossFactor(double evaporationLossFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossFactor, evaporationLossFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetEvaporationLossFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::EvaporationLossFactor, ""));
    }

    double CoolingTowerTwoSpeed_Impl::driftLossPercent() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::DriftLossPercent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isDriftLossPercentDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::DriftLossPercent);
    }

    bool CoolingTowerTwoSpeed_Impl::setDriftLossPercent(double driftLossPercent) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::DriftLossPercent, driftLossPercent);
    }

    void CoolingTowerTwoSpeed_Impl::resetDriftLossPercent() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::DriftLossPercent, ""));
    }

    std::string CoolingTowerTwoSpeed_Impl::blowdownCalculationMode() const {
      const auto value = getString(openstudio::CoolingTower_TwoSpeedFields::BlowdownCalculationMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isBlowdownCalculationModeDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::BlowdownCalculationMode);
    }

    bool CoolingTowerTwoSpeed_Impl::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
      return setString(openstudio::CoolingTower_TwoSpeedFields::BlowdownCalculationMode, blowdownCalculationMode);
    }

    void CoolingTowerTwoSpeed_Impl::resetBlowdownCalculationMode() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::BlowdownCalculationMode, ""));
    }

    double CoolingTowerTwoSpeed_Impl::blowdownConcentrationRatio() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::BlowdownConcentrationRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isBlowdownConcentrationRatioDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::BlowdownConcentrationRatio);
    }

    bool CoolingTowerTwoSpeed_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
    }

    void CoolingTowerTwoSpeed_Impl::resetBlowdownConcentrationRatio() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::BlowdownConcentrationRatio, ""));
    }

    boost::optional<Schedule> CoolingTowerTwoSpeed_Impl::blowdownMakeupWaterUsageSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::CoolingTower_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName);
    }

    bool CoolingTowerTwoSpeed_Impl::setBlowdownMakeupWaterUsageSchedule(Schedule& blowdownMakeupWaterUsageSchedule) {
      return setSchedule(openstudio::CoolingTower_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName, "CoolingTowerTwoSpeed",
                         "Blowdown Makeup Water Usage", blowdownMakeupWaterUsageSchedule);
    }

    void CoolingTowerTwoSpeed_Impl::resetBlowdownMakeupWaterUsageSchedule() {
      OS_ASSERT(setPointer(openstudio::CoolingTower_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName, openstudio::Handle(), false));
    }

    int CoolingTowerTwoSpeed_Impl::numberofCells() const {
      const auto value = getInt(openstudio::CoolingTower_TwoSpeedFields::NumberofCells, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isNumberofCellsDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::NumberofCells);
    }

    bool CoolingTowerTwoSpeed_Impl::setNumberofCells(int numberofCells) {
      return setInt(openstudio::CoolingTower_TwoSpeedFields::NumberofCells, numberofCells);
    }

    void CoolingTowerTwoSpeed_Impl::resetNumberofCells() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::NumberofCells, ""));
    }

    std::string CoolingTowerTwoSpeed_Impl::cellControl() const {
      if (const auto value = getString(openstudio::CoolingTower_TwoSpeedFields::CellControl, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "MinimalCell";
    }

    bool CoolingTowerTwoSpeed_Impl::isCellControlDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::CellControl);
    }

    bool CoolingTowerTwoSpeed_Impl::setCellControl(const std::string& cellControl) {
      return setString(openstudio::CoolingTower_TwoSpeedFields::CellControl, cellControl);
    }

    void CoolingTowerTwoSpeed_Impl::resetCellControl() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::CellControl, ""));
    }

    double CoolingTowerTwoSpeed_Impl::cellMinimumWaterFlowRateFraction() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::CellMinimumWaterFlowRateFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isCellMinimumWaterFlowRateFractionDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::CellMinimumWaterFlowRateFraction);
    }

    bool CoolingTowerTwoSpeed_Impl::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::CellMinimumWaterFlowRateFraction, cellMinimumWaterFlowRateFraction);
    }

    void CoolingTowerTwoSpeed_Impl::resetCellMinimumWaterFlowRateFraction() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::CellMinimumWaterFlowRateFraction, ""));
    }

    double CoolingTowerTwoSpeed_Impl::cellMaximumWaterFlowRateFraction() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::CellMaximumWaterFlowRateFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isCellMaximumWaterFlowRateFractionDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::CellMaximumWaterFlowRateFraction);
    }

    bool CoolingTowerTwoSpeed_Impl::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::CellMaximumWaterFlowRateFraction, cellMaximumWaterFlowRateFraction);
    }

    void CoolingTowerTwoSpeed_Impl::resetCellMaximumWaterFlowRateFraction() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::CellMaximumWaterFlowRateFraction, ""));
    }

    double CoolingTowerTwoSpeed_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_TwoSpeedFields::SizingFactor);
    }

    bool CoolingTowerTwoSpeed_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::SizingFactor, sizingFactor);
    }

    void CoolingTowerTwoSpeed_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::SizingFactor, ""));
    }

    double CoolingTowerTwoSpeed_Impl::designInletAirDryBulbTemperature() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::DesignInletAirDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::DesignInletAirDryBulbTemperature, designInletAirDryBulbTemperature);
    }

    double CoolingTowerTwoSpeed_Impl::designInletAirWetBulbTemperature() const {
      const auto value = getDouble(openstudio::CoolingTower_TwoSpeedFields::DesignInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::DesignInletAirWetBulbTemperature, designInletAirWetBulbTemperature);
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::designApproachTemperature() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::DesignApproachTemperature, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isDesignApproachTemperatureAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::DesignApproachTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setDesignApproachTemperature(double designApproachTemperature) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::DesignApproachTemperature, designApproachTemperature);
    }

    void CoolingTowerTwoSpeed_Impl::autosizeDesignApproachTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::DesignApproachTemperature, "autosize"));
    }

    boost::optional<double> CoolingTowerTwoSpeed_Impl::designRangeTemperature() const {
      return getDouble(openstudio::CoolingTower_TwoSpeedFields::DesignRangeTemperature, true);
    }

    bool CoolingTowerTwoSpeed_Impl::isDesignRangeTemperatureAutosized() const {
      if (auto value = getString(openstudio::CoolingTower_TwoSpeedFields::DesignRangeTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerTwoSpeed_Impl::setDesignRangeTemperature(double designRangeTemperature) {
      return setDouble(openstudio::CoolingTower_TwoSpeedFields::DesignRangeTemperature, designRangeTemperature);
    }

    void CoolingTowerTwoSpeed_Impl::autosizeDesignRangeTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_TwoSpeedFields::DesignRangeTemperature, "autosize"));
    }

    std::string CoolingTowerTwoSpeed_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::CoolingTower_TwoSpeedFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerTwoSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::CoolingTower_TwoSpeedFields::EndUseSubcategory, endUseSubcategory);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
