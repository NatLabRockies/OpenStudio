/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRIC_IMPL_HPP
#define EPMODEL_CHILLERELECTRIC_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ChillerElectric_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ChillerElectric_Impl() override = default;

  std::string condenserType() const;
  bool isCondenserTypeDefaulted() const;
  bool setCondenserType(const std::string& condenserType);
  void resetCondenserType();

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;
  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  double nominalCOP() const;
  bool setNominalCOP(double nominalCOP);

  boost::optional<double> minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  boost::optional<double> maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  void resetMaximumPartLoadRatio();

  boost::optional<double> optimumPartLoadRatio() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  void resetOptimumPartLoadRatio();

  boost::optional<double> designCondenserInletTemperature() const;
  bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);
  void resetDesignCondenserInletTemperature();

  double temperatureRiseCoefficient() const;
  bool setTemperatureRiseCoefficient(double temperatureRiseCoefficient);

  boost::optional<double> designChilledWaterOutletTemperature() const;
  bool setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature);
  void resetDesignChilledWaterOutletTemperature();

  boost::optional<double> designChilledWaterFlowRate() const;
  bool isDesignChilledWaterFlowRateAutosized() const;
  bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
  void resetDesignChilledWaterFlowRate();
  void autosizeDesignChilledWaterFlowRate();

  boost::optional<double> designCondenserFluidFlowRate() const;
  bool isDesignCondenserFluidFlowRateAutosized() const;
  bool setDesignCondenserFluidFlowRate(double designCondenserFluidFlowRate);
  void resetDesignCondenserFluidFlowRate();
  void autosizeDesignCondenserFluidFlowRate();

  boost::optional<double> coefficient1ofCapacityRatioCurve() const;
  bool setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve);
  void resetCoefficient1ofCapacityRatioCurve();

  boost::optional<double> coefficient2ofCapacityRatioCurve() const;
  bool setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve);
  void resetCoefficient2ofCapacityRatioCurve();

  boost::optional<double> coefficient3ofCapacityRatioCurve() const;
  bool setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve);
  void resetCoefficient3ofCapacityRatioCurve();

  boost::optional<double> coefficient1ofPowerRatioCurve() const;
  bool setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve);
  void resetCoefficient1ofPowerRatioCurve();

  boost::optional<double> coefficient2ofPowerRatioCurve() const;
  bool setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve);
  void resetCoefficient2ofPowerRatioCurve();

  boost::optional<double> coefficient3ofPowerRatioCurve() const;
  bool setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve);
  void resetCoefficient3ofPowerRatioCurve();

  boost::optional<double> coefficient1ofFullLoadRatioCurve() const;
  bool setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve);
  void resetCoefficient1ofFullLoadRatioCurve();

  boost::optional<double> coefficient2ofFullLoadRatioCurve() const;
  bool setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve);
  void resetCoefficient2ofFullLoadRatioCurve();

  boost::optional<double> coefficient3ofFullLoadRatioCurve() const;
  bool setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve);
  void resetCoefficient3ofFullLoadRatioCurve();

  boost::optional<double> chilledWaterOutletTemperatureLowerLimit() const;
  bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);
  void resetChilledWaterOutletTemperatureLowerLimit();

  std::string chillerFlowMode() const;
  bool isChillerFlowModeDefaulted() const;
  bool setChillerFlowMode(const std::string& chillerFlowMode);
  void resetChillerFlowMode();

  boost::optional<double> designHeatRecoveryWaterFlowRate() const;
  bool isDesignHeatRecoveryWaterFlowRateAutosized() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
  void resetDesignHeatRecoveryWaterFlowRate();
  void autosizeDesignHeatRecoveryWaterFlowRate();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  double basinHeaterCapacity() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  double basinHeaterSetpointTemperature() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  void resetBasinHeaterSetpointTemperature();

  boost::optional<double> condenserHeatRecoveryRelativeCapacityFraction() const;
  bool setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction);
  void resetCondenserHeatRecoveryRelativeCapacityFraction();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  double thermosiphonMinimumTemperatureDifference() const;
  bool isThermosiphonMinimumTemperatureDifferenceDefaulted() const;
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);
  void resetThermosiphonMinimumTemperatureDifference();

  std::vector<std::string> condenserTypeValues() const;
  std::vector<std::string> chillerFlowModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
