/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTION_IMPL_HPP
#define EPMODEL_CHILLERABSORPTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ChillerAbsorption_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ChillerAbsorption_Impl() override = default;

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;

  boost::optional<double> nominalPumpingPower() const;
  bool isNominalPumpingPowerAutosized() const;

  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double designCondenserInletTemperature() const;

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;

  boost::optional<double> designCondenserWaterFlowRate() const;
  bool isDesignCondenserWaterFlowRateAutosized() const;

  double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve() const;
  double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve() const;
  double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve() const;

  double coefficient1ofthePumpElectricUsePartLoadRatioCurve() const;
  double coefficient2ofthePumpElectricUsePartLoadRatioCurve() const;
  double coefficient3ofthePumpElectricUsePartLoadRatioCurve() const;

  double chilledWaterOutletTemperatureLowerLimit() const;

  std::string chillerFlowMode() const;
  std::string generatorHeatSourceType() const;

  boost::optional<double> designGeneratorFluidFlowRate() const;
  bool isDesignGeneratorFluidFlowRateAutosized() const;

  double degreeofSubcoolinginSteamGenerator() const;
  double sizingFactor() const;

  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  bool setNominalPumpingPower(double nominalPumpingPower);
  void autosizeNominalPumpingPower();

  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);

  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void autosizeDesignChilledWaterFlowRate();

  bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
  void autosizeDesignCondenserWaterFlowRate();

  bool setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve);
  bool setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve);
  bool setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve);

  bool setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(double coefficient1ofthePumpElectricUsePartLoadRatioCurve);
  bool setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(double coefficient2ofthePumpElectricUsePartLoadRatioCurve);
  bool setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(double coefficient3ofthePumpElectricUsePartLoadRatioCurve);

  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

  bool setChillerFlowMode(const std::string& chillerFlowMode);
  bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

  bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
  void autosizeDesignGeneratorFluidFlowRate();

  bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);
  bool setSizingFactor(double sizingFactor);

  std::vector<std::string> chillerFlowModeValues() const;
  std::vector<std::string> generatorHeatSourceTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
