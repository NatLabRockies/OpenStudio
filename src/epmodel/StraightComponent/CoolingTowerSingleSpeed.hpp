/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COOLINGTOWERSINGLESPEED_HPP
#define EPMODEL_COOLINGTOWERSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoolingTowerSingleSpeed_Impl;
}

class EPMODEL_API CoolingTowerSingleSpeed : public StraightComponent
{
 public:
  explicit CoolingTowerSingleSpeed(const Model& model);

  virtual ~CoolingTowerSingleSpeed() override = default;
  CoolingTowerSingleSpeed(const CoolingTowerSingleSpeed& other) = default;
  CoolingTowerSingleSpeed(CoolingTowerSingleSpeed&& other) = default;
  CoolingTowerSingleSpeed& operator=(const CoolingTowerSingleSpeed&) = default;
  CoolingTowerSingleSpeed& operator=(CoolingTowerSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInputMethodValues();
  static std::vector<std::string> evaporationLossModeValues();
  static std::vector<std::string> blowdownCalculationModeValues();
  static std::vector<std::string> capacityControlValues();
  static std::vector<std::string> cellControlValues();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The canonical single-speed cooling-tower scalar surface is present, while node, schedule, tank, and object-link helpers remain out of scope.
  // - Canonical Counterpart: openstudio::model::CoolingTowerSingleSpeed.
  // - Implemented Parity: The preserved scalar API matches the tower performance, flow, free-convection, and control accessors with matching autosize/default behavior.
  // - Documented Delta: Node-name, schedule, storage-tank, and other relationship helpers remain intentionally excluded from this scalar pass.
  // - Field/Storage Mapping: These accessors map directly to EnergyPlus `CoolingTower:SingleSpeed` scalar fields used by the forward translator.
  // - Evidence: `src/model/CoolingTowerSingleSpeed.hpp`, `src/model/CoolingTowerSingleSpeed.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateCoolingTowerSingleSpeed.cpp`.
  // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;
  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  boost::optional<double> designAirFlowRate() const;
  bool isDesignAirFlowRateAutosized() const;
  bool setDesignAirFlowRate(double designAirFlowRate);
  void autosizeDesignAirFlowRate();

  boost::optional<double> fanPoweratDesignAirFlowRate() const;
  bool isFanPoweratDesignAirFlowRateAutosized() const;
  bool setFanPoweratDesignAirFlowRate(double fanPoweratDesignAirFlowRate);
  void autosizeFanPoweratDesignAirFlowRate();

  boost::optional<double> uFactorTimesAreaValueatDesignAirFlowRate() const;
  bool isUFactorTimesAreaValueatDesignAirFlowRateAutosized() const;
  bool setUFactorTimesAreaValueatDesignAirFlowRate(double uFactorTimesAreaValueatDesignAirFlowRate);
  void resetUFactorTimesAreaValueatDesignAirFlowRate();
  void autosizeUFactorTimesAreaValueatDesignAirFlowRate();

  boost::optional<double> airFlowRateinFreeConvectionRegime() const;
  bool isAirFlowRateinFreeConvectionRegimeDefaulted() const;
  bool isAirFlowRateinFreeConvectionRegimeAutosized() const;
  bool setAirFlowRateinFreeConvectionRegime(double airFlowRateinFreeConvectionRegime);
  void resetAirFlowRateinFreeConvectionRegime();
  void autosizeAirFlowRateinFreeConvectionRegime();

  boost::optional<double> uFactorTimesAreaValueatFreeConvectionAirFlowRate() const;
  bool isUFactorTimesAreaValueatFreeConvectionAirFlowRateDefaulted() const;
  bool isUFactorTimesAreaValueatFreeConvectionAirFlowRateAutosized() const;
  bool setUFactorTimesAreaValueatFreeConvectionAirFlowRate(double uFactorTimesAreaValueatFreeConvectionAirFlowRate);
  void resetUFactorTimesAreaValueatFreeConvectionAirFlowRate();
  void autosizeUFactorTimesAreaValueatFreeConvectionAirFlowRate();

  std::string performanceInputMethod() const;
  bool isPerformanceInputMethodDefaulted() const;
  bool setPerformanceInputMethod(const std::string& performanceInputMethod);
  void resetPerformanceInputMethod();

  boost::optional<double> nominalCapacity() const;
  bool setNominalCapacity(double nominalCapacity);
  void resetNominalCapacity();

  boost::optional<double> freeConvectionCapacity() const;
  bool setFreeConvectionCapacity(double freeConvectionCapacity);
  void resetFreeConvectionCapacity();

  double basinHeaterCapacity() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  double basinHeaterSetpointTemperature() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  void resetBasinHeaterSetpointTemperature();

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

  std::string capacityControl() const;
  bool isCapacityControlDefaulted() const;
  bool setCapacityControl(const std::string& capacityControl);
  void resetCapacityControl();

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

  double freeConvectionAirFlowRateSizingFactor() const;
  bool setFreeConvectionAirFlowRateSizingFactor(double freeConvectionAirFlowRateSizingFactor);

  double freeConvectionUFactorTimesAreaValueSizingFactor() const;
  bool setFreeConvectionUFactorTimesAreaValueSizingFactor(double freeConvectionUFactorTimesAreaValueSizingFactor);

  double heatRejectionCapacityAndNominalCapacitySizingRatio() const;
  bool setHeatRejectionCapacityAndNominalCapacitySizingRatio(double heatRejectionCapacityAndNominalCapacitySizingRatio);

  double freeConvectionNominalCapacitySizingFactor() const;
  bool setFreeConvectionNominalCapacitySizingFactor(double freeConvectionNominalCapacitySizingFactor);

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
  using ImplType = detail::CoolingTowerSingleSpeed_Impl;

  friend class Model;

  explicit CoolingTowerSingleSpeed(std::shared_ptr<detail::CoolingTowerSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
