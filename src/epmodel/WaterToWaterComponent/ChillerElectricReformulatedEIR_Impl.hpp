/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICREFORMULATEDEIR_IMPL_HPP
#define EPMODEL_CHILLERELECTRICREFORMULATEDEIR_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ChillerElectricReformulatedEIR_Impl : public WaterToWaterComponent_Impl
{
 public:
  using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
  virtual ~ChillerElectricReformulatedEIR_Impl() override = default;

  unsigned supplyInletPort() const override;
  unsigned supplyOutletPort() const override;
  unsigned demandInletPort() const override;
  unsigned demandOutletPort() const override;
  unsigned tertiaryInletPort() const override;
  unsigned tertiaryOutletPort() const override;

  boost::optional<double> referenceCapacity() const;
  bool isReferenceCapacityAutosized() const;
  bool setReferenceCapacity(boost::optional<double> referenceCapacity);
  bool setReferenceCapacity(double referenceCapacity);
  void autosizeReferenceCapacity();

  double referenceCOP() const;
  bool setReferenceCOP(double referenceCOP);

  double referenceLeavingChilledWaterTemperature() const;
  bool isReferenceLeavingChilledWaterTemperatureDefaulted() const;
  bool setReferenceLeavingChilledWaterTemperature(double referenceLeavingChilledWaterTemperature);
  void resetReferenceLeavingChilledWaterTemperature();

  double referenceLeavingCondenserWaterTemperature() const;
  bool isReferenceLeavingCondenserWaterTemperatureDefaulted() const;
  bool setReferenceLeavingCondenserWaterTemperature(double referenceLeavingCondenserWaterTemperature);
  void resetReferenceLeavingCondenserWaterTemperature();

  boost::optional<double> referenceChilledWaterFlowRate() const;
  bool isReferenceChilledWaterFlowRateAutosized() const;
  bool setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate);
  bool setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate);
  void resetReferenceChilledWaterFlowRate();
  void autosizeReferenceChilledWaterFlowRate();

  boost::optional<double> referenceCondenserWaterFlowRate() const;
  bool isReferenceCondenserWaterFlowRateAutosized() const;
  bool setReferenceCondenserWaterFlowRate(boost::optional<double> referenceCondenserWaterFlowRate);
  bool setReferenceCondenserWaterFlowRate(double referenceCondenserWaterFlowRate);
  void resetReferenceCondenserWaterFlowRate();
  void autosizeReferenceCondenserWaterFlowRate();

  std::string electricInputToCoolingOutputRatioFunctionOfPLRType() const;
  bool setElectricInputToCoolingOutputRatioFunctionOfPLRType(const std::string& electricInputToCoolingOutputRatioFunctionOfPLRType);
  void resetElectricInputToCoolingOutputRatioFunctionOfPLRType();

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

  double minimumUnloadingRatio() const;
  bool isMinimumUnloadingRatioDefaulted() const;
  bool setMinimumUnloadingRatio(double minimumUnloadingRatio);
  void resetMinimumUnloadingRatio();

  double fractionofCompressorElectricConsumptionRejectedbyCondenser() const;
  bool isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted() const;
  bool setFractionofCompressorElectricConsumptionRejectedbyCondenser(double fractionofCompressorElectricConsumptionRejectedbyCondenser);
  void resetFractionofCompressorElectricConsumptionRejectedbyCondenser();

  double leavingChilledWaterLowerTemperatureLimit() const;
  bool isLeavingChilledWaterLowerTemperatureLimitDefaulted() const;
  bool setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit);
  void resetLeavingChilledWaterLowerTemperatureLimit();

  std::string chillerFlowMode() const;
  bool isChillerFlowModeDefaulted() const;
  bool setChillerFlowMode(const std::string& chillerFlowMode);
  void resetChillerFlowMode();

  boost::optional<double> designHeatRecoveryWaterFlowRate() const;
  bool isDesignHeatRecoveryWaterFlowRateAutosized() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);
  void autosizeDesignHeatRecoveryWaterFlowRate();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  double condenserHeatRecoveryRelativeCapacityFraction() const;
  bool setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  std::string condenserFlowControl() const;
  bool setCondenserFlowControl(const std::string& condenserFlowControl);

  double condenserMinimumFlowFraction() const;
  bool setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction);

  double thermosiphonMinimumTemperatureDifference() const;
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

  std::vector<std::string> validChillerFlowModeValues() const;
  std::vector<std::string> validCondenserFlowControlValues() const;
  std::vector<std::string> validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
