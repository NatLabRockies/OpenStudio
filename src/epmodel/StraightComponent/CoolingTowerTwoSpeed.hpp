/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COOLINGTOWERTWOSPEED_HPP
#define EPMODEL_COOLINGTOWERTWOSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;

namespace detail {
class CoolingTowerTwoSpeed_Impl;
}

class EPMODEL_API CoolingTowerTwoSpeed : public StraightComponent
{
 public:
  explicit CoolingTowerTwoSpeed(const Model& model);

  virtual ~CoolingTowerTwoSpeed() override = default;
  CoolingTowerTwoSpeed(const CoolingTowerTwoSpeed& other) = default;
  CoolingTowerTwoSpeed(CoolingTowerTwoSpeed&& other) = default;
  CoolingTowerTwoSpeed& operator=(const CoolingTowerTwoSpeed&) = default;
  CoolingTowerTwoSpeed& operator=(CoolingTowerTwoSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInputMethodValues();
  static std::vector<std::string> evaporationLossModeValues();
  static std::vector<std::string> blowdownCalculationModeValues();
  static std::vector<std::string> cellControlValues();

  // Schema Alignment Notes:
  // - Status: Parity with documented deltas. The canonical two-speed cooling-tower scalar surface, plant-supply insertion rule, and schedule relationships are present, while the storage-tank object link remains out of scope.
  // - Canonical Counterpart: openstudio::model::CoolingTowerTwoSpeed.
  // - Implemented Parity: The preserved API covers the canonical tower performance, fan-power, flow, blowdown, cell-control, basin-heater, thermal-design, and end-use fields with matching default/autosize behavior, and the basin/blowdown schedule relationships plus plant supply `addToNode(...)` path match the current canonical slice.
  // - Documented Delta: The supply-water-storage-tank object link remains intentionally excluded from this pass.
  // - Field/Storage Mapping: These accessors map directly to EnergyPlus `CoolingTower:TwoSpeed` scalar fields used by the forward translator.
  // - Evidence: `src/model/CoolingTowerTwoSpeed.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerTwoSpeed.cpp`.
  // - Remaining Parity Work: None within the current canonical public surface; the non-public storage-tank linkage remains intentionally excluded.
  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;
  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  boost::optional<double> highFanSpeedAirFlowRate() const;
  bool isHighFanSpeedAirFlowRateAutosized() const;
  bool setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate);
  void autosizeHighFanSpeedAirFlowRate();

  boost::optional<double> highFanSpeedFanPower() const;
  bool isHighFanSpeedFanPowerAutosized() const;
  bool setHighFanSpeedFanPower(double highFanSpeedFanPower);
  void autosizeHighFanSpeedFanPower();

  boost::optional<double> highFanSpeedUFactorTimesAreaValue() const;
  bool isHighFanSpeedUFactorTimesAreaValueAutosized() const;
  bool setHighFanSpeedUFactorTimesAreaValue(double highFanSpeedUFactorTimesAreaValue);
  void resetHighFanSpeedUFactorTimesAreaValue();
  void autosizeHighFanSpeedUFactorTimesAreaValue();

  boost::optional<double> lowFanSpeedAirFlowRate() const;
  bool isLowFanSpeedAirFlowRateAutosized() const;
  bool setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate);
  void autosizeLowFanSpeedAirFlowRate();

  double lowFanSpeedAirFlowRateSizingFactor() const;
  bool isLowFanSpeedAirFlowRateSizingFactorDefaulted() const;
  bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);
  void resetLowFanSpeedAirFlowRateSizingFactor();

  boost::optional<double> lowFanSpeedFanPower() const;
  bool isLowFanSpeedFanPowerAutosized() const;
  bool setLowFanSpeedFanPower(double lowFanSpeedFanPower);
  void autosizeLowFanSpeedFanPower();

  double lowFanSpeedFanPowerSizingFactor() const;
  bool isLowFanSpeedFanPowerSizingFactorDefaulted() const;
  bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);
  void resetLowFanSpeedFanPowerSizingFactor();

  boost::optional<double> lowFanSpeedUFactorTimesAreaValue() const;
  bool isLowFanSpeedUFactorTimesAreaValueAutosized() const;
  bool setLowFanSpeedUFactorTimesAreaValue(double lowFanSpeedUFactorTimesAreaValue);
  void resetLowFanSpeedUFactorTimesAreaValue();
  void autosizeLowFanSpeedUFactorTimesAreaValue();

  double lowFanSpeedUFactorTimesAreaSizingFactor() const;
  bool isLowFanSpeedUFactorTimesAreaSizingFactorDefaulted() const;
  bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);
  void resetLowFanSpeedUFactorTimesAreaSizingFactor();

  boost::optional<double> freeConvectionRegimeAirFlowRate() const;
  bool isFreeConvectionRegimeAirFlowRateDefaulted() const;
  bool isFreeConvectionRegimeAirFlowRateAutosized() const;
  bool setFreeConvectionRegimeAirFlowRate(double freeConvectionRegimeAirFlowRate);
  void resetFreeConvectionRegimeAirFlowRate();
  void autosizeFreeConvectionRegimeAirFlowRate();

  double freeConvectionRegimeAirFlowRateSizingFactor() const;
  bool isFreeConvectionRegimeAirFlowRateSizingFactorDefaulted() const;
  bool setFreeConvectionRegimeAirFlowRateSizingFactor(double freeConvectionRegimeAirFlowRateSizingFactor);
  void resetFreeConvectionRegimeAirFlowRateSizingFactor();

  boost::optional<double> freeConvectionRegimeUFactorTimesAreaValue() const;
  bool isFreeConvectionRegimeUFactorTimesAreaValueDefaulted() const;
  bool isFreeConvectionRegimeUFactorTimesAreaValueAutosized() const;
  bool setFreeConvectionRegimeUFactorTimesAreaValue(double freeConvectionRegimeUFactorTimesAreaValue);
  void resetFreeConvectionRegimeUFactorTimesAreaValue();
  void autosizeFreeConvectionRegimeUFactorTimesAreaValue();

  double freeConvectionUFactorTimesAreaValueSizingFactor() const;
  bool isFreeConvectionUFactorTimesAreaValueSizingFactorDefaulted() const;
  bool setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor);
  void resetFreeConvectionUFactorTimesAreaValueSizingFactor();

  std::string performanceInputMethod() const;
  bool isPerformanceInputMethodDefaulted() const;
  bool setPerformanceInputMethod(const std::string& performanceInputMethod);
  void resetPerformanceInputMethod();

  double heatRejectionCapacityandNominalCapacitySizingRatio() const;
  bool isHeatRejectionCapacityandNominalCapacitySizingRatioDefaulted() const;
  bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);
  void resetHeatRejectionCapacityandNominalCapacitySizingRatio();

  boost::optional<double> highSpeedNominalCapacity() const;
  bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);
  void resetHighSpeedNominalCapacity();

  boost::optional<double> lowSpeedNominalCapacity() const;
  bool isLowSpeedNominalCapacityAutosized() const;
  bool setLowSpeedNominalCapacity(double lowSpeedNominalCapacity);
  void resetLowSpeedNominalCapacity();
  void autosizeLowSpeedNominalCapacity();

  double lowSpeedNominalCapacitySizingFactor() const;
  bool isLowSpeedNominalCapacitySizingFactorDefaulted() const;
  bool setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor);
  void resetLowSpeedNominalCapacitySizingFactor();

  boost::optional<double> freeConvectionNominalCapacity() const;
  bool isFreeConvectionNominalCapacityAutosized() const;
  bool setFreeConvectionNominalCapacity(double freeConvectionNominalCapacity);
  void resetFreeConvectionNominalCapacity();
  void autosizeFreeConvectionNominalCapacity();

  double freeConvectionNominalCapacitySizingFactor() const;
  bool isFreeConvectionNominalCapacitySizingFactorDefaulted() const;
  bool setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor);
  void resetFreeConvectionNominalCapacitySizingFactor();

  double basinHeaterCapacity() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  double basinHeaterSetpointTemperature() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  void resetBasinHeaterSetpointTemperature();
  boost::optional<Schedule> basinHeaterOperatingSchedule() const;
  bool setBasinHeaterOperatingSchedule(Schedule& basinHeaterOperatingSchedule);
  void resetBasinHeaterOperatingSchedule();

  std::string evaporationLossMode() const;
  bool isEvaporationLossModeDefaulted() const;
  bool setEvaporationLossMode(const std::string& evaporationLossMode);
  void resetEvaporationLossMode();

  double evaporationLossFactor() const;
  bool isEvaporationLossFactorDefaulted() const;
  bool setEvaporationLossFactor(double evaporationLossFactor);
  void resetEvaporationLossFactor();

  double driftLossPercent() const;
  bool isDriftLossPercentDefaulted() const;
  bool setDriftLossPercent(double driftLossPercent);
  void resetDriftLossPercent();

  std::string blowdownCalculationMode() const;
  bool isBlowdownCalculationModeDefaulted() const;
  bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);
  void resetBlowdownCalculationMode();

  double blowdownConcentrationRatio() const;
  bool isBlowdownConcentrationRatioDefaulted() const;
  bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
  void resetBlowdownConcentrationRatio();
  boost::optional<Schedule> blowdownMakeupWaterUsageSchedule() const;
  bool setBlowdownMakeupWaterUsageSchedule(Schedule& blowdownMakeupWaterUsageSchedule);
  void resetBlowdownMakeupWaterUsageSchedule();

  int numberofCells() const;
  bool isNumberofCellsDefaulted() const;
  bool setNumberofCells(int numberofCells);
  void resetNumberofCells();

  std::string cellControl() const;
  bool isCellControlDefaulted() const;
  bool setCellControl(const std::string& cellControl);
  void resetCellControl();

  double cellMinimumWaterFlowRateFraction() const;
  bool isCellMinimumWaterFlowRateFractionDefaulted() const;
  bool setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction);
  void resetCellMinimumWaterFlowRateFraction();

  double cellMaximumWaterFlowRateFraction() const;
  bool isCellMaximumWaterFlowRateFractionDefaulted() const;
  bool setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction);
  void resetCellMaximumWaterFlowRateFraction();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  double designInletAirDryBulbTemperature() const;
  bool setDesignInletAirDryBulbTemperature(double designInletAirDryBulbTemperature);

  double designInletAirWetBulbTemperature() const;
  bool setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature);

  boost::optional<double> designApproachTemperature() const;
  bool isDesignApproachTemperatureAutosized() const;
  bool setDesignApproachTemperature(double designApproachTemperature);
  void autosizeDesignApproachTemperature();

  boost::optional<double> designRangeTemperature() const;
  bool isDesignRangeTemperatureAutosized() const;
  bool setDesignRangeTemperature(double designRangeTemperature);
  void autosizeDesignRangeTemperature();

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

 protected:
  using ImplType = detail::CoolingTowerTwoSpeed_Impl;

  friend class Model;

  explicit CoolingTowerTwoSpeed(std::shared_ptr<detail::CoolingTowerTwoSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
