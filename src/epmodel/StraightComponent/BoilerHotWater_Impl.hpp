/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BOILERHOTWATER_IMPL_HPP
#define EPMODEL_BOILERHOTWATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API BoilerHotWater_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~BoilerHotWater_Impl() override = default;

  std::string fuelType() const;
  bool setFuelType(const std::string& fuelType);

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;
  bool setNominalCapacity(double nominalCapacity);
  void resetNominalCapacity();
  void autosizeNominalCapacity();

  double nominalThermalEfficiency() const;
  bool setNominalThermalEfficiency(double nominalThermalEfficiency);

  boost::optional<std::string> efficiencyCurveTemperatureEvaluationVariable() const;
  bool setEfficiencyCurveTemperatureEvaluationVariable(const std::string& efficiencyCurveTemperatureEvaluationVariable);
  void resetEfficiencyCurveTemperatureEvaluationVariable();

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;
  bool setDesignWaterFlowRate(double designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  double minimumPartLoadRatio() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  void resetMinimumPartLoadRatio();

  double maximumPartLoadRatio() const;
  bool isMaximumPartLoadRatioDefaulted() const;
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  void resetMaximumPartLoadRatio();

  double optimumPartLoadRatio() const;
  bool isOptimumPartLoadRatioDefaulted() const;
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  void resetOptimumPartLoadRatio();

  double waterOutletUpperTemperatureLimit() const;
  bool isWaterOutletUpperTemperatureLimitDefaulted() const;
  bool setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit);
  void resetWaterOutletUpperTemperatureLimit();

  std::string boilerFlowMode() const;
  bool isBoilerFlowModeDefaulted() const;
  bool setBoilerFlowMode(const std::string& boilerFlowMode);
  void resetBoilerFlowMode();

  boost::optional<double> parasiticElectricLoad() const;
  bool setParasiticElectricLoad(double parasiticElectricLoad);
  void resetParasiticElectricLoad();

  double onCycleParasiticElectricLoad() const;
  bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  double offCycleParasiticFuelLoad() const;
  bool setOffCycleParasiticFuelLoad(double offCycleParasiticFuelLoad);

  std::vector<std::string> fuelTypeValues() const;
  std::vector<std::string> efficiencyCurveTemperatureEvaluationVariableValues() const;
  std::vector<std::string> boilerFlowModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
