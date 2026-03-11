/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTIONINDIRECT_IMPL_HPP
#define EPMODEL_CHILLERABSORPTIONINDIRECT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ChillerAbsorptionIndirect_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ChillerAbsorptionIndirect_Impl() override = default;

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;

  boost::optional<double> nominalPumpingPower() const;
  bool isNominalPumpingPowerAutosized() const;

  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double designCondenserInletTemperature() const;
  double condenserInletTemperatureLowerLimit() const;
  double chilledWaterOutletTemperatureLowerLimit() const;

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;

  std::string chillerFlowMode() const;
  std::string generatorHeatSourceType() const;

  boost::optional<double> designGeneratorFluidFlowRate() const;
  bool isDesignGeneratorFluidFlowRateAutosized() const;

  double temperatureLowerLimitGeneratorInlet() const;
  double degreeofSubcoolinginSteamGenerator() const;
  double degreeofSubcoolinginSteamCondensateLoop() const;
  double sizingFactor() const;

  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  bool setNominalPumpingPower(double nominalPumpingPower);
  void autosizeNominalPumpingPower();

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);
  bool setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit);
  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void autosizeDesignChilledWaterFlowRate();

  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void autosizeDesignCondenserWaterFlowRate();

  bool setChillerFlowMode(const std::string& chillerFlowMode);
  bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

  bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
  void autosizeDesignGeneratorFluidFlowRate();

  bool setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet);
  bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);
  bool setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop);
  bool setSizingFactor(double sizingFactor);

  std::vector<std::string> chillerFlowModeValues() const;
  std::vector<std::string> generatorHeatSourceTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
