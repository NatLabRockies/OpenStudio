/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class EvaporativeFluidCoolerTwoSpeed_Impl;
}

class EPMODEL_API EvaporativeFluidCoolerTwoSpeed : public StraightComponent
{
 public:
  explicit EvaporativeFluidCoolerTwoSpeed(const Model& model);

  virtual ~EvaporativeFluidCoolerTwoSpeed() override = default;
  EvaporativeFluidCoolerTwoSpeed(const EvaporativeFluidCoolerTwoSpeed& other) = default;
  EvaporativeFluidCoolerTwoSpeed(EvaporativeFluidCoolerTwoSpeed&& other) = default;
  EvaporativeFluidCoolerTwoSpeed& operator=(const EvaporativeFluidCoolerTwoSpeed&) = default;
  EvaporativeFluidCoolerTwoSpeed& operator=(EvaporativeFluidCoolerTwoSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInputMethodValues();
  static std::vector<std::string> evaporationLossModeValues();
  static std::vector<std::string> blowdownCalculationModeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::EvaporativeFluidCoolerTwoSpeed scalar accessor names/signatures.
  // - Field Mapping: Scalar APIs map directly to E+ EvaporativeFluidCooler:TwoSpeed scalar fields.
  // - Field Mapping: Relationship-like fields (node/schedule/storage-tank links) are excluded from this scalar-only pass.
  // - ForwardTranslator evidence: ForwardTranslateEvaporativeFluidCoolerTwoSpeed.cpp maps these preserved scalar APIs to matching E+ fields.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  boost::optional<double> highFanSpeedAirFlowRate() const;
  bool isHighFanSpeedAirFlowRateAutosized() const;

  boost::optional<double> highFanSpeedFanPower() const;
  bool isHighFanSpeedFanPowerAutosized() const;

  boost::optional<double> lowFanSpeedAirFlowRate() const;
  bool isLowFanSpeedAirFlowRateAutosized() const;

  double lowFanSpeedAirFlowRateSizingFactor() const;

  boost::optional<double> lowFanSpeedFanPower() const;
  bool isLowFanSpeedFanPowerAutosized() const;

  double lowFanSpeedFanPowerSizingFactor() const;

  double designSprayWaterFlowRate() const;

  std::string performanceInputMethod() const;

  double heatRejectionCapacityandNominalCapacitySizingRatio() const;

  boost::optional<double> highSpeedStandardDesignCapacity() const;

  boost::optional<double> lowSpeedStandardDesignCapacity() const;
  bool isLowSpeedStandardDesignCapacityAutosized() const;

  double lowSpeedStandardCapacitySizingFactor() const;

  boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
  bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;

  boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
  bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;

  double lowFanSpeedUFactorTimesAreaSizingFactor() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

  boost::optional<double> highSpeedUserSpecifiedDesignCapacity() const;

  boost::optional<double> lowSpeedUserSpecifiedDesignCapacity() const;
  bool isLowSpeedUserSpecifiedDesignCapacityAutosized() const;

  double lowSpeedUserSpecifiedDesignCapacitySizingFactor() const;

  boost::optional<double> designEnteringWaterTemperature() const;
  bool isDesignEnteringWaterTemperatureAutosized() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  double highSpeedSizingFactor() const;

  std::string evaporationLossMode() const;

  boost::optional<double> evaporationLossFactor() const;

  double driftLossPercent() const;

  std::string blowdownCalculationMode() const;

  double blowdownConcentrationRatio() const;

  bool setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate);
  void autosizeHighFanSpeedAirFlowRate();

  bool setHighFanSpeedFanPower(double highFanSpeedFanPower);
  void autosizeHighFanSpeedFanPower();

  bool setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate);
  void autosizeLowFanSpeedAirFlowRate();

  bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);

  bool setLowFanSpeedFanPower(double lowFanSpeedFanPower);
  void autosizeLowFanSpeedFanPower();

  bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);

  bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

  bool setHighSpeedStandardDesignCapacity(double highSpeedStandardDesignCapacity);
  void resetHighSpeedStandardDesignCapacity();

  bool setLowSpeedStandardDesignCapacity(double lowSpeedStandardDesignCapacity);
  void resetLowSpeedStandardDesignCapacity();
  void autosizeLowSpeedStandardDesignCapacity();

  bool setLowSpeedStandardCapacitySizingFactor(double lowSpeedStandardCapacitySizingFactor);

  bool setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue);
  void resetHighFanSpeedUfactorTimesAreaValue();
  void autosizeHighFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue);
  void resetLowFanSpeedUfactorTimesAreaValue();
  void autosizeLowFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  bool setHighSpeedUserSpecifiedDesignCapacity(double highSpeedUserSpecifiedDesignCapacity);
  void resetHighSpeedUserSpecifiedDesignCapacity();

  bool setLowSpeedUserSpecifiedDesignCapacity(double lowSpeedUserSpecifiedDesignCapacity);
  void resetLowSpeedUserSpecifiedDesignCapacity();
  void autosizeLowSpeedUserSpecifiedDesignCapacity();

  bool setLowSpeedUserSpecifiedDesignCapacitySizingFactor(double lowSpeedUserSpecifiedDesignCapacitySizingFactor);

  bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);
  void autosizeDesignEnteringWaterTemperature();

  bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

  bool setHighSpeedSizingFactor(double highSpeedSizingFactor);

  bool setEvaporationLossMode(const std::string& evaporationLossMode);

  bool setEvaporationLossFactor(double evaporationLossFactor);
  void resetEvaporationLossFactor();

  bool setDriftLossPercent(double driftLossPercent);

  bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);

  bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);

  boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedHighFanSpeedFanPower() const;
  boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedLowFanSpeedFanPower() const;
  boost::optional<double> autosizedLowSpeedStandardDesignCapacity() const;
  boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedLowSpeedUserSpecifiedDesignCapacity() const;
  boost::optional<double> autosizedDesignEnteringWaterTemperature() const;

 protected:
  using ImplType = detail::EvaporativeFluidCoolerTwoSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EvaporativeFluidCoolerTwoSpeed(std::shared_ptr<detail::EvaporativeFluidCoolerTwoSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
