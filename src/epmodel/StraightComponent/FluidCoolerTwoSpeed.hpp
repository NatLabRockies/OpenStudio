/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERTWOSPEED_HPP
#define EPMODEL_FLUIDCOOLERTWOSPEED_HPP

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
class FluidCoolerTwoSpeed_Impl;
}

class EPMODEL_API FluidCoolerTwoSpeed : public StraightComponent
{
 public:
  explicit FluidCoolerTwoSpeed(const Model& model);

  virtual ~FluidCoolerTwoSpeed() override = default;
  FluidCoolerTwoSpeed(const FluidCoolerTwoSpeed& other) = default;
  FluidCoolerTwoSpeed(FluidCoolerTwoSpeed&& other) = default;
  FluidCoolerTwoSpeed& operator=(const FluidCoolerTwoSpeed&) = default;
  FluidCoolerTwoSpeed& operator=(FluidCoolerTwoSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInputMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::FluidCoolerTwoSpeed scalar accessor names/signatures.
  // - Field Mapping: Preserved scalar APIs currently delegate directly to matching E+ FluidCooler:TwoSpeed scalar fields.
  // - API: Relationship accessors outdoorAirInletNode()/setOutdoorAirInletNode()/resetOutdoorAirInletNode() are intentionally excluded in this scalar-only pass.
  // - ForwardTranslator evidence: ForwardTranslateFluidCoolerTwoSpeed.cpp maps these preserved scalar APIs to the same E+ fields.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  std::string performanceInputMethod() const;

  boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
  bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;

  boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
  bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;

  double lowFanSpeedUFactorTimesAreaSizingFactor() const;

  double highSpeedNominalCapacity() const;

  boost::optional<double> lowSpeedNominalCapacity() const;
  bool isLowSpeedNominalCapacityAutosized() const;

  double lowSpeedNominalCapacitySizingFactor() const;

  double designEnteringWaterTemperature() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

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

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue);
  void autosizeHighFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue);
  void autosizeLowFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

  bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);

  bool setLowSpeedNominalCapacity(double lowSpeedNominalCapacity);
  void autosizeLowSpeedNominalCapacity();

  bool setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor);

  bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);

  bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void autosizeDesignWaterFlowRate();

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

  boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedLowSpeedNominalCapacity() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedHighFanSpeedFanPower() const;
  boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedLowFanSpeedFanPower() const;

 protected:
  using ImplType = detail::FluidCoolerTwoSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FluidCoolerTwoSpeed(std::shared_ptr<detail::FluidCoolerTwoSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
