/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoolingTowerVariableSpeedMerkel.hpp"
#include "CoolingTowerVariableSpeedMerkel_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoolingTower_VariableSpeed_Merkel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CoolingTowerVariableSpeedMerkel::CoolingTowerVariableSpeedMerkel(const Model& model)
    : ModelObject(CoolingTowerVariableSpeedMerkel::iddObjectType(), model) {}

  CoolingTowerVariableSpeedMerkel::CoolingTowerVariableSpeedMerkel(std::shared_ptr<detail::CoolingTowerVariableSpeedMerkel_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoolingTowerVariableSpeedMerkel::iddObjectType() {
    return IddObjectType::CoolingTower_VariableSpeed_Merkel;
  }

  std::vector<std::string> CoolingTowerVariableSpeedMerkel::performanceInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoolingTower_VariableSpeed_MerkelFields::PerformanceInputMethod);
  }

  std::vector<std::string> CoolingTowerVariableSpeedMerkel::evaporationLossModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossMode);
  }

  std::vector<std::string> CoolingTowerVariableSpeedMerkel::blowdownCalculationModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownCalculationMode);
  }

  std::vector<std::string> CoolingTowerVariableSpeedMerkel::cellControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoolingTower_VariableSpeed_MerkelFields::CellControl);
  }

  std::string CoolingTowerVariableSpeedMerkel::performanceInputMethod() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->performanceInputMethod();
  }

  bool CoolingTowerVariableSpeedMerkel::isPerformanceInputMethodDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isPerformanceInputMethodDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setPerformanceInputMethod(const std::string& performanceInputMethod) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setPerformanceInputMethod(performanceInputMethod);
  }

  void CoolingTowerVariableSpeedMerkel::resetPerformanceInputMethod() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetPerformanceInputMethod();
  }

  double CoolingTowerVariableSpeedMerkel::heatRejectionCapacityandNominalCapacitySizingRatio() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->heatRejectionCapacityandNominalCapacitySizingRatio();
  }

  bool CoolingTowerVariableSpeedMerkel::isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setHeatRejectionCapacityandNominalCapacitySizingRatio(
    double heatRejectionCapacityandNominalCapacitySizingRatio) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setHeatRejectionCapacityandNominalCapacitySizingRatio(
      heatRejectionCapacityandNominalCapacitySizingRatio);
  }

  void CoolingTowerVariableSpeedMerkel::resetHeatRejectionCapacityandNominalCapacitySizingRatio() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetHeatRejectionCapacityandNominalCapacitySizingRatio();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::nominalCapacity() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->nominalCapacity();
  }

  bool CoolingTowerVariableSpeedMerkel::isNominalCapacityAutosized() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isNominalCapacityAutosized();
  }

  bool CoolingTowerVariableSpeedMerkel::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void CoolingTowerVariableSpeedMerkel::resetNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetNominalCapacity();
  }

  void CoolingTowerVariableSpeedMerkel::autosizeNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autosizeNominalCapacity();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::freeConvectionNominalCapacity() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->freeConvectionNominalCapacity();
  }

  bool CoolingTowerVariableSpeedMerkel::isFreeConvectionNominalCapacityAutocalculated() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isFreeConvectionNominalCapacityAutocalculated();
  }

  bool CoolingTowerVariableSpeedMerkel::setFreeConvectionNominalCapacity(double freeConvectionNominalCapacity) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setFreeConvectionNominalCapacity(freeConvectionNominalCapacity);
  }

  void CoolingTowerVariableSpeedMerkel::resetFreeConvectionNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetFreeConvectionNominalCapacity();
  }

  void CoolingTowerVariableSpeedMerkel::autocalculateFreeConvectionNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autocalculateFreeConvectionNominalCapacity();
  }

  double CoolingTowerVariableSpeedMerkel::freeConvectionNominalCapacitySizingFactor() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->freeConvectionNominalCapacitySizingFactor();
  }

  bool CoolingTowerVariableSpeedMerkel::isFreeConvectionNominalCapacitySizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isFreeConvectionNominalCapacitySizingFactorDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setFreeConvectionNominalCapacitySizingFactor(
      freeConvectionNominalCapacitySizingFactor);
  }

  void CoolingTowerVariableSpeedMerkel::resetFreeConvectionNominalCapacitySizingFactor() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetFreeConvectionNominalCapacitySizingFactor();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::designWaterFlowRate() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designWaterFlowRate();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignWaterFlowRateAutosized() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignWaterFlowRateAutosized();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignWaterFlowRate(double designWaterFlowRate) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
  }

  void CoolingTowerVariableSpeedMerkel::autosizeDesignWaterFlowRate() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autosizeDesignWaterFlowRate();
  }

  double CoolingTowerVariableSpeedMerkel::designWaterFlowRateperUnitofNominalCapacity() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designWaterFlowRateperUnitofNominalCapacity();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignWaterFlowRateperUnitofNominalCapacityDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignWaterFlowRateperUnitofNominalCapacityDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignWaterFlowRateperUnitofNominalCapacity(double designWaterFlowRateperUnitofNominalCapacity) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignWaterFlowRateperUnitofNominalCapacity(
      designWaterFlowRateperUnitofNominalCapacity);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignWaterFlowRateperUnitofNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignWaterFlowRateperUnitofNominalCapacity();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::designAirFlowRate() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designAirFlowRate();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignAirFlowRateAutocalculated() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignAirFlowRateAutocalculated();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignAirFlowRate(double designAirFlowRate) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignAirFlowRate(designAirFlowRate);
  }

  void CoolingTowerVariableSpeedMerkel::autocalculateDesignAirFlowRate() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autocalculateDesignAirFlowRate();
  }

  double CoolingTowerVariableSpeedMerkel::designAirFlowRatePerUnitofNominalCapacity() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designAirFlowRatePerUnitofNominalCapacity();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignAirFlowRatePerUnitofNominalCapacityDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignAirFlowRatePerUnitofNominalCapacityDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignAirFlowRatePerUnitofNominalCapacity(double designAirFlowRatePerUnitofNominalCapacity) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignAirFlowRatePerUnitofNominalCapacity(
      designAirFlowRatePerUnitofNominalCapacity);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignAirFlowRatePerUnitofNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignAirFlowRatePerUnitofNominalCapacity();
  }

  double CoolingTowerVariableSpeedMerkel::minimumAirFlowRateRatio() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->minimumAirFlowRateRatio();
  }

  bool CoolingTowerVariableSpeedMerkel::isMinimumAirFlowRateRatioDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isMinimumAirFlowRateRatioDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setMinimumAirFlowRateRatio(minimumAirFlowRateRatio);
  }

  void CoolingTowerVariableSpeedMerkel::resetMinimumAirFlowRateRatio() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetMinimumAirFlowRateRatio();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::designFanPower() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designFanPower();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignFanPowerAutocalculated() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignFanPowerAutocalculated();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignFanPower(double designFanPower) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignFanPower(designFanPower);
  }

  void CoolingTowerVariableSpeedMerkel::autocalculateDesignFanPower() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autocalculateDesignFanPower();
  }

  double CoolingTowerVariableSpeedMerkel::designFanPowerPerUnitofNominalCapacity() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designFanPowerPerUnitofNominalCapacity();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignFanPowerPerUnitofNominalCapacityDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignFanPowerPerUnitofNominalCapacityDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignFanPowerPerUnitofNominalCapacity(double designFanPowerPerUnitofNominalCapacity) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignFanPowerPerUnitofNominalCapacity(designFanPowerPerUnitofNominalCapacity);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignFanPowerPerUnitofNominalCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignFanPowerPerUnitofNominalCapacity();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::freeConvectionRegimeAirFlowRate() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->freeConvectionRegimeAirFlowRate();
  }

  bool CoolingTowerVariableSpeedMerkel::isFreeConvectionRegimeAirFlowRateAutocalculated() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isFreeConvectionRegimeAirFlowRateAutocalculated();
  }

  bool CoolingTowerVariableSpeedMerkel::setFreeConvectionRegimeAirFlowRate(double freeConvectionRegimeAirFlowRate) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setFreeConvectionRegimeAirFlowRate(freeConvectionRegimeAirFlowRate);
  }

  void CoolingTowerVariableSpeedMerkel::resetFreeConvectionRegimeAirFlowRate() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetFreeConvectionRegimeAirFlowRate();
  }

  void CoolingTowerVariableSpeedMerkel::autocalculateFreeConvectionRegimeAirFlowRate() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autocalculateFreeConvectionRegimeAirFlowRate();
  }

  double CoolingTowerVariableSpeedMerkel::freeConvectionRegimeAirFlowRateSizingFactor() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->freeConvectionRegimeAirFlowRateSizingFactor();
  }

  bool CoolingTowerVariableSpeedMerkel::isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setFreeConvectionRegimeAirFlowRateSizingFactor(double freeConvectionRegimeAirFlowRateSizingFactor) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setFreeConvectionRegimeAirFlowRateSizingFactor(
      freeConvectionRegimeAirFlowRateSizingFactor);
  }

  void CoolingTowerVariableSpeedMerkel::resetFreeConvectionRegimeAirFlowRateSizingFactor() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetFreeConvectionRegimeAirFlowRateSizingFactor();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::designAirFlowRateUFactorTimesAreaValue() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designAirFlowRateUFactorTimesAreaValue();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignAirFlowRateUFactorTimesAreaValueAutosized() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignAirFlowRateUFactorTimesAreaValueAutosized();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignAirFlowRateUFactorTimesAreaValue(double designAirFlowRateUFactorTimesAreaValue) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignAirFlowRateUFactorTimesAreaValue(designAirFlowRateUFactorTimesAreaValue);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignAirFlowRateUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignAirFlowRateUFactorTimesAreaValue();
  }

  void CoolingTowerVariableSpeedMerkel::autosizeDesignAirFlowRateUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autosizeDesignAirFlowRateUFactorTimesAreaValue();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::freeConvectionRegimeUFactorTimesAreaValue() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->freeConvectionRegimeUFactorTimesAreaValue();
  }

  bool CoolingTowerVariableSpeedMerkel::isFreeConvectionRegimeUFactorTimesAreaValueAutocalculated() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isFreeConvectionRegimeUFactorTimesAreaValueAutocalculated();
  }

  bool CoolingTowerVariableSpeedMerkel::setFreeConvectionRegimeUFactorTimesAreaValue(double freeConvectionRegimeUFactorTimesAreaValue) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setFreeConvectionRegimeUFactorTimesAreaValue(
      freeConvectionRegimeUFactorTimesAreaValue);
  }

  void CoolingTowerVariableSpeedMerkel::resetFreeConvectionRegimeUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetFreeConvectionRegimeUFactorTimesAreaValue();
  }

  void CoolingTowerVariableSpeedMerkel::autocalculateFreeConvectionRegimeUFactorTimesAreaValue() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autocalculateFreeConvectionRegimeUFactorTimesAreaValue();
  }

  double CoolingTowerVariableSpeedMerkel::freeConvectionUFactorTimesAreaValueSizingFactor() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->freeConvectionUFactorTimesAreaValueSizingFactor();
  }

  bool CoolingTowerVariableSpeedMerkel::isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setFreeConvectionUFactorTimesAreaValueSizingFactor(
      freeConvectionUFactorTimesAreaValueSizingFactor);
  }

  void CoolingTowerVariableSpeedMerkel::resetFreeConvectionUFactorTimesAreaValueSizingFactor() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetFreeConvectionUFactorTimesAreaValueSizingFactor();
  }

  double CoolingTowerVariableSpeedMerkel::designInletAirDryBulbTemperature() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designInletAirDryBulbTemperature();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignInletAirDryBulbTemperatureDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignInletAirDryBulbTemperatureDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignInletAirDryBulbTemperature(designInletAirDryBulbTemperature);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignInletAirDryBulbTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignInletAirDryBulbTemperature();
  }

  double CoolingTowerVariableSpeedMerkel::designInletAirWetBulbTemperature() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designInletAirWetBulbTemperature();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignInletAirWetBulbTemperatureDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignInletAirWetBulbTemperatureDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignInletAirWetBulbTemperature(designInletAirWetBulbTemperature);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignInletAirWetBulbTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignInletAirWetBulbTemperature();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::designApproachTemperature() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designApproachTemperature();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignApproachTemperatureDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignApproachTemperatureDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignApproachTemperatureAutosized() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignApproachTemperatureAutosized();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignApproachTemperature(double designApproachTemperature) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignApproachTemperature(designApproachTemperature);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignApproachTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignApproachTemperature();
  }

  void CoolingTowerVariableSpeedMerkel::autosizeDesignApproachTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autosizeDesignApproachTemperature();
  }

  boost::optional<double> CoolingTowerVariableSpeedMerkel::designRangeTemperature() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->designRangeTemperature();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignRangeTemperatureDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignRangeTemperatureDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::isDesignRangeTemperatureAutosized() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDesignRangeTemperatureAutosized();
  }

  bool CoolingTowerVariableSpeedMerkel::setDesignRangeTemperature(double designRangeTemperature) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDesignRangeTemperature(designRangeTemperature);
  }

  void CoolingTowerVariableSpeedMerkel::resetDesignRangeTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDesignRangeTemperature();
  }

  void CoolingTowerVariableSpeedMerkel::autosizeDesignRangeTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->autosizeDesignRangeTemperature();
  }

  double CoolingTowerVariableSpeedMerkel::basinHeaterCapacity() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->basinHeaterCapacity();
  }

  bool CoolingTowerVariableSpeedMerkel::isBasinHeaterCapacityDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isBasinHeaterCapacityDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  void CoolingTowerVariableSpeedMerkel::resetBasinHeaterCapacity() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetBasinHeaterCapacity();
  }

  double CoolingTowerVariableSpeedMerkel::basinHeaterSetpointTemperature() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->basinHeaterSetpointTemperature();
  }

  bool CoolingTowerVariableSpeedMerkel::isBasinHeaterSetpointTemperatureDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  void CoolingTowerVariableSpeedMerkel::resetBasinHeaterSetpointTemperature() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetBasinHeaterSetpointTemperature();
  }

  std::string CoolingTowerVariableSpeedMerkel::evaporationLossMode() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->evaporationLossMode();
  }

  bool CoolingTowerVariableSpeedMerkel::isEvaporationLossModeDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isEvaporationLossModeDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setEvaporationLossMode(const std::string& evaporationLossMode) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setEvaporationLossMode(evaporationLossMode);
  }

  void CoolingTowerVariableSpeedMerkel::resetEvaporationLossMode() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetEvaporationLossMode();
  }

  double CoolingTowerVariableSpeedMerkel::evaporationLossFactor() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->evaporationLossFactor();
  }

  bool CoolingTowerVariableSpeedMerkel::isEvaporationLossFactorDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isEvaporationLossFactorDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setEvaporationLossFactor(double evaporationLossFactor) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setEvaporationLossFactor(evaporationLossFactor);
  }

  void CoolingTowerVariableSpeedMerkel::resetEvaporationLossFactor() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetEvaporationLossFactor();
  }

  double CoolingTowerVariableSpeedMerkel::driftLossPercent() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->driftLossPercent();
  }

  bool CoolingTowerVariableSpeedMerkel::isDriftLossPercentDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isDriftLossPercentDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setDriftLossPercent(double driftLossPercent) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setDriftLossPercent(driftLossPercent);
  }

  void CoolingTowerVariableSpeedMerkel::resetDriftLossPercent() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetDriftLossPercent();
  }

  std::string CoolingTowerVariableSpeedMerkel::blowdownCalculationMode() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->blowdownCalculationMode();
  }

  bool CoolingTowerVariableSpeedMerkel::isBlowdownCalculationModeDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isBlowdownCalculationModeDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setBlowdownCalculationMode(blowdownCalculationMode);
  }

  void CoolingTowerVariableSpeedMerkel::resetBlowdownCalculationMode() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetBlowdownCalculationMode();
  }

  double CoolingTowerVariableSpeedMerkel::blowdownConcentrationRatio() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->blowdownConcentrationRatio();
  }

  bool CoolingTowerVariableSpeedMerkel::isBlowdownConcentrationRatioDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isBlowdownConcentrationRatioDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
  }

  void CoolingTowerVariableSpeedMerkel::resetBlowdownConcentrationRatio() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetBlowdownConcentrationRatio();
  }

  int CoolingTowerVariableSpeedMerkel::numberofCells() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->numberofCells();
  }

  bool CoolingTowerVariableSpeedMerkel::isNumberofCellsDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isNumberofCellsDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setNumberofCells(int numberofCells) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setNumberofCells(numberofCells);
  }

  void CoolingTowerVariableSpeedMerkel::resetNumberofCells() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetNumberofCells();
  }

  std::string CoolingTowerVariableSpeedMerkel::cellControl() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->cellControl();
  }

  bool CoolingTowerVariableSpeedMerkel::isCellControlDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isCellControlDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setCellControl(const std::string& cellControl) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setCellControl(cellControl);
  }

  void CoolingTowerVariableSpeedMerkel::resetCellControl() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetCellControl();
  }

  double CoolingTowerVariableSpeedMerkel::cellMinimumWaterFlowRateFraction() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->cellMinimumWaterFlowRateFraction();
  }

  bool CoolingTowerVariableSpeedMerkel::isCellMinimumWaterFlowRateFractionDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isCellMinimumWaterFlowRateFractionDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setCellMinimumWaterFlowRateFraction(cellMinimumWaterFlowRateFraction);
  }

  void CoolingTowerVariableSpeedMerkel::resetCellMinimumWaterFlowRateFraction() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetCellMinimumWaterFlowRateFraction();
  }

  double CoolingTowerVariableSpeedMerkel::cellMaximumWaterFlowRateFraction() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->cellMaximumWaterFlowRateFraction();
  }

  bool CoolingTowerVariableSpeedMerkel::isCellMaximumWaterFlowRateFractionDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isCellMaximumWaterFlowRateFractionDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setCellMaximumWaterFlowRateFraction(cellMaximumWaterFlowRateFraction);
  }

  void CoolingTowerVariableSpeedMerkel::resetCellMaximumWaterFlowRateFraction() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetCellMaximumWaterFlowRateFraction();
  }

  double CoolingTowerVariableSpeedMerkel::sizingFactor() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->sizingFactor();
  }

  bool CoolingTowerVariableSpeedMerkel::isSizingFactorDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isSizingFactorDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setSizingFactor(double sizingFactor) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setSizingFactor(sizingFactor);
  }

  void CoolingTowerVariableSpeedMerkel::resetSizingFactor() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetSizingFactor();
  }

  std::string CoolingTowerVariableSpeedMerkel::endUseSubcategory() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->endUseSubcategory();
  }

  bool CoolingTowerVariableSpeedMerkel::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool CoolingTowerVariableSpeedMerkel::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void CoolingTowerVariableSpeedMerkel::resetEndUseSubcategory() {
    getImpl<detail::CoolingTowerVariableSpeedMerkel_Impl>()->resetEndUseSubcategory();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> CoolingTowerVariableSpeedMerkel_Impl::performanceInputMethodValues() const {
      return openstudio::epmodel::CoolingTowerVariableSpeedMerkel::performanceInputMethodValues();
    }

    std::vector<std::string> CoolingTowerVariableSpeedMerkel_Impl::evaporationLossModeValues() const {
      return openstudio::epmodel::CoolingTowerVariableSpeedMerkel::evaporationLossModeValues();
    }

    std::vector<std::string> CoolingTowerVariableSpeedMerkel_Impl::blowdownCalculationModeValues() const {
      return openstudio::epmodel::CoolingTowerVariableSpeedMerkel::blowdownCalculationModeValues();
    }

    std::vector<std::string> CoolingTowerVariableSpeedMerkel_Impl::cellControlValues() const {
      return openstudio::epmodel::CoolingTowerVariableSpeedMerkel::cellControlValues();
    }

    std::string CoolingTowerVariableSpeedMerkel_Impl::performanceInputMethod() const {
      const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::PerformanceInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isPerformanceInputMethodDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::PerformanceInputMethod);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
      return setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::PerformanceInputMethod, performanceInputMethod);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetPerformanceInputMethod() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::PerformanceInputMethod, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::heatRejectionCapacityandNominalCapacitySizingRatio() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::HeatRejectionCapacityandNominalCapacitySizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::HeatRejectionCapacityandNominalCapacitySizingRatio);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setHeatRejectionCapacityandNominalCapacitySizingRatio(
      double heatRejectionCapacityandNominalCapacitySizingRatio) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::HeatRejectionCapacityandNominalCapacitySizingRatio,
                       heatRejectionCapacityandNominalCapacitySizingRatio);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetHeatRejectionCapacityandNominalCapacitySizingRatio() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::HeatRejectionCapacityandNominalCapacitySizingRatio, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::nominalCapacity() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::NominalCapacity, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isNominalCapacityAutosized() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::NominalCapacity, nominalCapacity);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::NominalCapacity, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::NominalCapacity, "autosize"));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::freeConvectionNominalCapacity() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacity, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isFreeConvectionNominalCapacityAutocalculated() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setFreeConvectionNominalCapacity(double freeConvectionNominalCapacity) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacity, freeConvectionNominalCapacity);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetFreeConvectionNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacity, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autocalculateFreeConvectionNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacity, "autocalculate"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::freeConvectionNominalCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isFreeConvectionNominalCapacitySizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacitySizingFactor);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacitySizingFactor,
                       freeConvectionNominalCapacitySizingFactor);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetFreeConvectionNominalCapacitySizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionNominalCapacitySizingFactor, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::designWaterFlowRate() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRate, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignWaterFlowRateAutosized() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignWaterFlowRate(double designWaterFlowRate) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRate, designWaterFlowRate);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autosizeDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRate, "autosize"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::designWaterFlowRateperUnitofNominalCapacity() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRateperUnitofNominalCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignWaterFlowRateperUnitofNominalCapacityDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRateperUnitofNominalCapacity);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignWaterFlowRateperUnitofNominalCapacity(double designWaterFlowRateperUnitofNominalCapacity) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRateperUnitofNominalCapacity,
                       designWaterFlowRateperUnitofNominalCapacity);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignWaterFlowRateperUnitofNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignWaterFlowRateperUnitofNominalCapacity, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::designAirFlowRate() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRate, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignAirFlowRateAutocalculated() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignAirFlowRate(double designAirFlowRate) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRate, designAirFlowRate);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autocalculateDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRate, "autocalculate"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::designAirFlowRatePerUnitofNominalCapacity() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRatePerUnitofNominalCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignAirFlowRatePerUnitofNominalCapacityDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRatePerUnitofNominalCapacity);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignAirFlowRatePerUnitofNominalCapacity(double designAirFlowRatePerUnitofNominalCapacity) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRatePerUnitofNominalCapacity,
                       designAirFlowRatePerUnitofNominalCapacity);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignAirFlowRatePerUnitofNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRatePerUnitofNominalCapacity, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::minimumAirFlowRateRatio() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::MinimumAirFlowRateRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isMinimumAirFlowRateRatioDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::MinimumAirFlowRateRatio);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::MinimumAirFlowRateRatio, minimumAirFlowRateRatio);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetMinimumAirFlowRateRatio() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::MinimumAirFlowRateRatio, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::designFanPower() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPower, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignFanPowerAutocalculated() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPower, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignFanPower(double designFanPower) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPower, designFanPower);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autocalculateDesignFanPower() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPower, "autocalculate"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::designFanPowerPerUnitofNominalCapacity() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPowerPerUnitofNominalCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignFanPowerPerUnitofNominalCapacityDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPowerPerUnitofNominalCapacity);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignFanPowerPerUnitofNominalCapacity(double designFanPowerPerUnitofNominalCapacity) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPowerPerUnitofNominalCapacity,
                       designFanPowerPerUnitofNominalCapacity);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignFanPowerPerUnitofNominalCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignFanPowerPerUnitofNominalCapacity, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::freeConvectionRegimeAirFlowRate() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRate, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isFreeConvectionRegimeAirFlowRateAutocalculated() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setFreeConvectionRegimeAirFlowRate(double freeConvectionRegimeAirFlowRate) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRate, freeConvectionRegimeAirFlowRate);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetFreeConvectionRegimeAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRate, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autocalculateFreeConvectionRegimeAirFlowRate() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRate, "autocalculate"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::freeConvectionRegimeAirFlowRateSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRateSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRateSizingFactor);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setFreeConvectionRegimeAirFlowRateSizingFactor(double freeConvectionRegimeAirFlowRateSizingFactor) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRateSizingFactor,
                       freeConvectionRegimeAirFlowRateSizingFactor);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetFreeConvectionRegimeAirFlowRateSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeAirFlowRateSizingFactor, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::designAirFlowRateUFactorTimesAreaValue() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRateUFactorTimesAreaValue, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignAirFlowRateUFactorTimesAreaValueAutosized() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRateUFactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignAirFlowRateUFactorTimesAreaValue(double designAirFlowRateUFactorTimesAreaValue) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRateUFactorTimesAreaValue,
                       designAirFlowRateUFactorTimesAreaValue);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignAirFlowRateUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRateUFactorTimesAreaValue, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autosizeDesignAirFlowRateUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignAirFlowRateUFactorTimesAreaValue, "autosize"));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::freeConvectionRegimeUFactorTimesAreaValue() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeUFactorTimesAreaValue, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isFreeConvectionRegimeUFactorTimesAreaValueAutocalculated() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeUFactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setFreeConvectionRegimeUFactorTimesAreaValue(double freeConvectionRegimeUFactorTimesAreaValue) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeUFactorTimesAreaValue,
                       freeConvectionRegimeUFactorTimesAreaValue);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetFreeConvectionRegimeUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeUFactorTimesAreaValue, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autocalculateFreeConvectionRegimeUFactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionRegimeUFactorTimesAreaValue, "autocalculate"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::freeConvectionUFactorTimesAreaValueSizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionUFactorTimesAreaValueSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionUFactorTimesAreaValueSizingFactor);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setFreeConvectionUFactorTimesAreaValueSizingFactor(
      double freeConvectionUFactorTimesAreaValueSizingFactor) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionUFactorTimesAreaValueSizingFactor,
                       freeConvectionUFactorTimesAreaValueSizingFactor);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetFreeConvectionUFactorTimesAreaValueSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::FreeConvectionUFactorTimesAreaValueSizingFactor, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::designInletAirDryBulbTemperature() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignInletAirDryBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirDryBulbTemperature);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirDryBulbTemperature, designInletAirDryBulbTemperature);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignInletAirDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirDryBulbTemperature, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::designInletAirWetBulbTemperature() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignInletAirWetBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirWetBulbTemperature);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirWetBulbTemperature, designInletAirWetBulbTemperature);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignInletAirWetBulbTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignInletAirWetBulbTemperature, ""));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::designApproachTemperature() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignApproachTemperature, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignApproachTemperatureDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignApproachTemperature);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignApproachTemperatureAutosized() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignApproachTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignApproachTemperature(double designApproachTemperature) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignApproachTemperature, designApproachTemperature);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignApproachTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignApproachTemperature, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autosizeDesignApproachTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignApproachTemperature, "autosize"));
    }

    boost::optional<double> CoolingTowerVariableSpeedMerkel_Impl::designRangeTemperature() const {
      return getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignRangeTemperature, true);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignRangeTemperatureDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignRangeTemperature);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDesignRangeTemperatureAutosized() const {
      if (const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignRangeTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDesignRangeTemperature(double designRangeTemperature) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignRangeTemperature, designRangeTemperature);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDesignRangeTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignRangeTemperature, ""));
    }

    void CoolingTowerVariableSpeedMerkel_Impl::autosizeDesignRangeTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DesignRangeTemperature, "autosize"));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::basinHeaterCapacity() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isBasinHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterCapacity);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetBasinHeaterCapacity() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterCapacity, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::basinHeaterSetpointTemperature() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterSetpointTemperature);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetBasinHeaterSetpointTemperature() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::BasinHeaterSetpointTemperature, ""));
    }

    std::string CoolingTowerVariableSpeedMerkel_Impl::evaporationLossMode() const {
      const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isEvaporationLossModeDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossMode);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setEvaporationLossMode(const std::string& evaporationLossMode) {
      return setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossMode, evaporationLossMode);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetEvaporationLossMode() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossMode, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::evaporationLossFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isEvaporationLossFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossFactor);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setEvaporationLossFactor(double evaporationLossFactor) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossFactor, evaporationLossFactor);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetEvaporationLossFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EvaporationLossFactor, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::driftLossPercent() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DriftLossPercent, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isDriftLossPercentDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::DriftLossPercent);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setDriftLossPercent(double driftLossPercent) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::DriftLossPercent, driftLossPercent);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetDriftLossPercent() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::DriftLossPercent, ""));
    }

    std::string CoolingTowerVariableSpeedMerkel_Impl::blowdownCalculationMode() const {
      const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownCalculationMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isBlowdownCalculationModeDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownCalculationMode);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
      return setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownCalculationMode, blowdownCalculationMode);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetBlowdownCalculationMode() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownCalculationMode, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::blowdownConcentrationRatio() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownConcentrationRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isBlowdownConcentrationRatioDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownConcentrationRatio);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetBlowdownConcentrationRatio() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::BlowdownConcentrationRatio, ""));
    }

    int CoolingTowerVariableSpeedMerkel_Impl::numberofCells() const {
      const auto value = getInt(openstudio::CoolingTower_VariableSpeed_MerkelFields::NumberofCells, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isNumberofCellsDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::NumberofCells);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setNumberofCells(int numberofCells) {
      return setInt(openstudio::CoolingTower_VariableSpeed_MerkelFields::NumberofCells, numberofCells);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetNumberofCells() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::NumberofCells, ""));
    }

    std::string CoolingTowerVariableSpeedMerkel_Impl::cellControl() const {
      const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isCellControlDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellControl);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setCellControl(const std::string& cellControl) {
      return setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellControl, cellControl);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetCellControl() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellControl, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::cellMinimumWaterFlowRateFraction() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMinimumWaterFlowRateFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isCellMinimumWaterFlowRateFractionDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMinimumWaterFlowRateFraction);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMinimumWaterFlowRateFraction, cellMinimumWaterFlowRateFraction);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetCellMinimumWaterFlowRateFraction() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMinimumWaterFlowRateFraction, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::cellMaximumWaterFlowRateFraction() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMaximumWaterFlowRateFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isCellMaximumWaterFlowRateFractionDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMaximumWaterFlowRateFraction);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMaximumWaterFlowRateFraction, cellMaximumWaterFlowRateFraction);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetCellMaximumWaterFlowRateFraction() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::CellMaximumWaterFlowRateFraction, ""));
    }

    double CoolingTowerVariableSpeedMerkel_Impl::sizingFactor() const {
      const auto value = getDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::SizingFactor);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::CoolingTower_VariableSpeed_MerkelFields::SizingFactor, sizingFactor);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::SizingFactor, ""));
    }

    std::string CoolingTowerVariableSpeedMerkel_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::CoolingTower_VariableSpeed_MerkelFields::EndUseSubcategory);
    }

    bool CoolingTowerVariableSpeedMerkel_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EndUseSubcategory, endUseSubcategory);
    }

    void CoolingTowerVariableSpeedMerkel_Impl::resetEndUseSubcategory() {
      OS_ASSERT(setString(openstudio::CoolingTower_VariableSpeed_MerkelFields::EndUseSubcategory, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
