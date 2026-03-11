/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERSINGLESPEED_HPP

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
class EvaporativeFluidCoolerSingleSpeed_Impl;
}

class EPMODEL_API EvaporativeFluidCoolerSingleSpeed : public StraightComponent
{
 public:
  explicit EvaporativeFluidCoolerSingleSpeed(const Model& model);

  virtual ~EvaporativeFluidCoolerSingleSpeed() override = default;
  EvaporativeFluidCoolerSingleSpeed(const EvaporativeFluidCoolerSingleSpeed& other) = default;
  EvaporativeFluidCoolerSingleSpeed(EvaporativeFluidCoolerSingleSpeed&& other) = default;
  EvaporativeFluidCoolerSingleSpeed& operator=(const EvaporativeFluidCoolerSingleSpeed&) = default;
  EvaporativeFluidCoolerSingleSpeed& operator=(EvaporativeFluidCoolerSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInputMethodValues();
  static std::vector<std::string> capacityControlValues();
  static std::vector<std::string> evaporationLossModeValues();
  static std::vector<std::string> blowdownCalculationModeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::EvaporativeFluidCoolerSingleSpeed scalar accessor names/signatures.
  // - Field Mapping: fanPoweratDesignAirFlowRate maps to E+ field DesignAirFlowRateFanPower.
  // - Field Mapping: ufactorTimesAreaValueatDesignAirFlowRate maps to E+ field DesignAirFlowRateUfactorTimesAreaValue.
  // - Field Mapping: all other scalar APIs map directly to matching E+ EvaporativeFluidCooler:SingleSpeed fields.
  // - Field Mapping: node/schedule/storage-tank relationship-like fields are intentionally excluded from this scalar-only pass.
  // - ForwardTranslator evidence: ForwardTranslateEvaporativeFluidCoolerSingleSpeed.cpp maps preserved scalar APIs to these fields.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
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

  bool setDesignAirFlowRate(double designAirFlowRate);
  void autosizeDesignAirFlowRate();

  bool setFanPoweratDesignAirFlowRate(double fanPoweratDesignAirFlowRate);
  void autosizeFanPoweratDesignAirFlowRate();

  bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

  bool setStandardDesignCapacity(double standardDesignCapacity);
  void resetStandardDesignCapacity();

  bool setUfactorTimesAreaValueatDesignAirFlowRate(double ufactorTimesAreaValueatDesignAirFlowRate);
  void resetUfactorTimesAreaValueatDesignAirFlowRate();
  void autosizeUfactorTimesAreaValueatDesignAirFlowRate();

  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  bool setUserSpecifiedDesignCapacity(double userSpecifiedDesignCapacity);
  void resetUserSpecifiedDesignCapacity();

  bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);
  void autosizeDesignEnteringWaterTemperature();

  bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

  bool setCapacityControl(const std::string& capacityControl);
  void resetCapacityControl();

  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  bool setEvaporationLossMode(const std::string& evaporationLossMode);
  void resetEvaporationLossMode();

  bool setEvaporationLossFactor(double evaporationLossFactor);
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

 protected:
  using ImplType = detail::EvaporativeFluidCoolerSingleSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit EvaporativeFluidCoolerSingleSpeed(std::shared_ptr<detail::EvaporativeFluidCoolerSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
