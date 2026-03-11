/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORINTERNALCOMBUSTIONENGINE_IMPL_HPP
#define EPMODEL_GENERATORINTERNALCOMBUSTIONENGINE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GeneratorInternalCombustionEngine_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GeneratorInternalCombustionEngine_Impl() override = default;

  boost::optional<double> ratedPowerOutput() const;
  bool setRatedPowerOutput(double ratedPowerOutput);

  boost::optional<double> minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  boost::optional<double> maximumPartLoadRatio() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

  boost::optional<double> optimumPartLoadRatio() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);

  boost::optional<double> coefficient1ofUFactorTimesAreaCurve() const;
  bool setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve);

  boost::optional<double> coefficient2ofUFactorTimesAreaCurve() const;
  bool setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve);

  boost::optional<double> maximumExhaustFlowperUnitofPowerOutput() const;
  bool setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput);

  boost::optional<double> designMinimumExhaustTemperature() const;
  bool setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature);

  boost::optional<double> fuelHigherHeatingValue() const;
  bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);

  double designHeatRecoveryWaterFlowRate() const;
  bool isDesignHeatRecoveryWaterFlowRateDefaulted() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
  void resetDesignHeatRecoveryWaterFlowRate();

  std::string fuelType() const;
  bool isFuelTypeDefaulted() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  double heatRecoveryMaximumTemperature() const;
  bool isHeatRecoveryMaximumTemperatureDefaulted() const;
  bool setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature);
  void resetHeatRecoveryMaximumTemperature();

  std::vector<std::string> fuelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
