/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_IMPL_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API EvaporativeFluidCoolerSingleSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~EvaporativeFluidCoolerSingleSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::vector<std::string> performanceInputMethodValues() const;
  std::vector<std::string> capacityControlValues() const;
  std::vector<std::string> evaporationLossModeValues() const;
  std::vector<std::string> blowdownCalculationModeValues() const;

  boost::optional<double> designAirFlowRate() const;
  bool isDesignAirFlowRateAutosized() const;

  boost::optional<double> fanPoweratDesignAirFlowRate() const;
  bool isFanPoweratDesignAirFlowRateAutosized() const;

  double designSprayWaterFlowRate() const;

  std::string performanceInputMethod() const;

  double heatRejectionCapacityandNominalCapacitySizingRatio() const;

  boost::optional<double> standardDesignCapacity() const;

  boost::optional<double> ufactorTimesAreaValueatDesignAirFlowRate() const;
  bool isUfactorTimesAreaValueatDesignAirFlowRateAutosized() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

  boost::optional<double> userSpecifiedDesignCapacity() const;

  boost::optional<double> designEnteringWaterTemperature() const;
  bool isDesignEnteringWaterTemperatureAutosized() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  std::string capacityControl() const;
  bool isCapacityControlDefaulted() const;

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;

  std::string evaporationLossMode() const;
  bool isEvaporationLossModeDefaulted() const;

  boost::optional<double> evaporationLossFactor() const;

  double driftLossPercent() const;
  bool isDriftLossPercentDefaulted() const;

  std::string blowdownCalculationMode() const;
  bool isBlowdownCalculationModeDefaulted() const;

  double blowdownConcentrationRatio() const;
  bool isBlowdownConcentrationRatioDefaulted() const;

  bool setDesignAirFlowRate(boost::optional<double> designAirFlowRate);
  void autosizeDesignAirFlowRate();

  bool setFanPoweratDesignAirFlowRate(boost::optional<double> fanPoweratDesignAirFlowRate);
  void autosizeFanPoweratDesignAirFlowRate();

  bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

  bool setStandardDesignCapacity(boost::optional<double> standardDesignCapacity);
  void resetStandardDesignCapacity();

  bool setUfactorTimesAreaValueatDesignAirFlowRate(boost::optional<double> ufactorTimesAreaValueatDesignAirFlowRate);
  void resetUfactorTimesAreaValueatDesignAirFlowRate();
  void autosizeUfactorTimesAreaValueatDesignAirFlowRate();

  bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  bool setUserSpecifiedDesignCapacity(boost::optional<double> userSpecifiedDesignCapacity);
  void resetUserSpecifiedDesignCapacity();

  bool setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature);
  void autosizeDesignEnteringWaterTemperature();

  bool setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature);

  bool setCapacityControl(const std::string& capacityControl);
  void resetCapacityControl();

  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  bool setEvaporationLossMode(const std::string& evaporationLossMode);
  void resetEvaporationLossMode();

  bool setEvaporationLossFactor(boost::optional<double> evaporationLossFactor);
  void resetEvaporationLossFactor();

  bool setDriftLossPercent(double driftLossPercent);
  void resetDriftLossPercent();

  bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);
  void resetBlowdownCalculationMode();

  bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);
  void resetBlowdownConcentrationRatio();

  boost::optional<double> autosizedDesignAirFlowRate() const;
  boost::optional<double> autosizedFanPoweratDesignAirFlowRate() const;
  boost::optional<double> autosizedUfactorTimesAreaValueatDesignAirFlowRate() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedDesignEnteringWaterTemperature() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
