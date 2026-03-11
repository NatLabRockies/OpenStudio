/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERSINGLESPEED_HPP
#define EPMODEL_FLUIDCOOLERSINGLESPEED_HPP

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
class FluidCoolerSingleSpeed_Impl;
}

class EPMODEL_API FluidCoolerSingleSpeed : public StraightComponent
{
 public:
  explicit FluidCoolerSingleSpeed(const Model& model);

  virtual ~FluidCoolerSingleSpeed() override = default;
  FluidCoolerSingleSpeed(const FluidCoolerSingleSpeed& other) = default;
  FluidCoolerSingleSpeed(FluidCoolerSingleSpeed&& other) = default;
  FluidCoolerSingleSpeed& operator=(const FluidCoolerSingleSpeed&) = default;
  FluidCoolerSingleSpeed& operator=(FluidCoolerSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> performanceInputMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::FluidCoolerSingleSpeed scalar accessor names/signatures.
  // - Field Mapping: preserved scalar APIs currently delegate directly to matching E+ FluidCooler:SingleSpeed fields.
  // - API: Relationship accessor outdoorAirInletNode()/setOutdoorAirInletNode()/resetOutdoorAirInletNode() is intentionally excluded in this scalar-only pass.
  // - ForwardTranslator evidence: ForwardTranslateFluidCoolerSingleSpeed.cpp maps these preserved scalar APIs to the same E+ fields.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  std::string performanceInputMethod() const;

  boost::optional<double> designAirFlowRateUfactorTimesAreaValue() const;
  bool isDesignAirFlowRateUfactorTimesAreaValueAutosized() const;

  double nominalCapacity() const;

  double designEnteringWaterTemperature() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

  boost::optional<double> designAirFlowRate() const;
  bool isDesignAirFlowRateAutosized() const;

  boost::optional<double> designAirFlowRateFanPower() const;
  bool isDesignAirFlowRateFanPowerAutosized() const;

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setDesignAirFlowRateUfactorTimesAreaValue(double designAirFlowRateUfactorTimesAreaValue);
  void autosizeDesignAirFlowRateUfactorTimesAreaValue();

  bool setNominalCapacity(double nominalCapacity);

  bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);

  bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void autosizeDesignWaterFlowRate();

  bool setDesignAirFlowRate(double designAirFlowRate);
  void autosizeDesignAirFlowRate();

  bool setDesignAirFlowRateFanPower(double designAirFlowRateFanPower);
  void autosizeDesignAirFlowRateFanPower();

  boost::optional<double> autosizedDesignAirFlowRateUfactorTimesAreaValue() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedDesignAirFlowRate() const;
  boost::optional<double> autosizedDesignAirFlowRateFanPower() const;

 protected:
  using ImplType = detail::FluidCoolerSingleSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FluidCoolerSingleSpeed(std::shared_ptr<detail::FluidCoolerSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
