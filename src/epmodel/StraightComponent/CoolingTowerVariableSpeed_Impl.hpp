/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COOLINGTOWERVARIABLESPEED_IMPL_HPP
#define EPMODEL_COOLINGTOWERVARIABLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoolingTowerVariableSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoolingTowerVariableSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::vector<std::string> modelTypeValues() const;
  std::vector<std::string> evaporationLossModeValues() const;
  std::vector<std::string> blowdownCalculationModeValues() const;
  std::vector<std::string> cellControlValues() const;

  boost::optional<std::string> modelType() const;
  bool setModelType(const std::string& modelType);
  void resetModelType();

  boost::optional<double> designInletAirWetBulbTemperature() const;
  bool setDesignInletAirWetBulbTemperature(double designInletAirWetBulbTemperature);
  void resetDesignInletAirWetBulbTemperature();

  boost::optional<double> designApproachTemperature() const;
  bool setDesignApproachTemperature(double designApproachTemperature);
  void resetDesignApproachTemperature();

  boost::optional<double> designRangeTemperature() const;
  bool setDesignRangeTemperature(double designRangeTemperature);
  void resetDesignRangeTemperature();

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;
  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void autosizeDesignWaterFlowRate();

  boost::optional<double> designAirFlowRate() const;
  bool isDesignAirFlowRateAutosized() const;
  bool setDesignAirFlowRate(double designAirFlowRate);
  void autosizeDesignAirFlowRate();

  boost::optional<double> designFanPower() const;
  bool isDesignFanPowerAutosized() const;
  bool setDesignFanPower(double designFanPower);
  void autosizeDesignFanPower();

  boost::optional<double> minimumAirFlowRateRatio() const;
  bool setMinimumAirFlowRateRatio(double minimumAirFlowRateRatio);
  void resetMinimumAirFlowRateRatio();

  boost::optional<double> fractionofTowerCapacityinFreeConvectionRegime() const;
  bool setFractionofTowerCapacityinFreeConvectionRegime(double fractionofTowerCapacityinFreeConvectionRegime);
  void resetFractionofTowerCapacityinFreeConvectionRegime();

  boost::optional<double> basinHeaterCapacity() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  boost::optional<double> basinHeaterSetpointTemperature() const;
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

  boost::optional<double> driftLossPercent() const;
  bool setDriftLossPercent(double driftLossPercent);
  void resetDriftLossPercent();

  std::string blowdownCalculationMode() const;
  bool isBlowdownCalculationModeDefaulted() const;
  bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);
  void resetBlowdownCalculationMode();

  boost::optional<double> blowdownConcentrationRatio() const;
  bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
  void resetBlowdownConcentrationRatio();

  boost::optional<int> numberofCells() const;
  bool setNumberofCells(int numberofCells);
  void resetNumberofCells();

  std::string cellControl() const;
  bool isCellControlDefaulted() const;
  bool setCellControl(const std::string& cellControl);
  void resetCellControl();

  boost::optional<double> cellMinimumWaterFlowRateFraction() const;
  bool setCellMinimumWaterFlowRateFraction(double cellMinimumWaterFlowRateFraction);
  void resetCellMinimumWaterFlowRateFraction();

  boost::optional<double> cellMaximumWaterFlowRateFraction() const;
  bool setCellMaximumWaterFlowRateFraction(double cellMaximumWaterFlowRateFraction);
  void resetCellMaximumWaterFlowRateFraction();

  boost::optional<double> sizingFactor() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
