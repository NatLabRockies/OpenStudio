/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICREFORMULATEDEIR_HPP
#define EPMODEL_CHILLERELECTRICREFORMULATEDEIR_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerElectricReformulatedEIR_Impl;
}

class EPMODEL_API ChillerElectricReformulatedEIR : public WaterToWaterComponent
{
 public:
  explicit ChillerElectricReformulatedEIR(const Model& model);

  virtual ~ChillerElectricReformulatedEIR() override = default;
  ChillerElectricReformulatedEIR(const ChillerElectricReformulatedEIR& other) = default;
  ChillerElectricReformulatedEIR(ChillerElectricReformulatedEIR&& other) = default;
  ChillerElectricReformulatedEIR& operator=(const ChillerElectricReformulatedEIR&) = default;
  ChillerElectricReformulatedEIR& operator=(ChillerElectricReformulatedEIR&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validChillerFlowModeValues();
  static std::vector<std::string> validCondenserFlowControlValues();
  static std::vector<std::string> validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus Chiller:Electric:ReformulatedEIR fields.
  // - Field Mapping: chillerFlowMode* maps to EnergyPlus field ChillerFlowModeType (API name preserved from model counterpart).
  // - Field Mapping: Relationship fields (curve/schedule/node/object-list targets) are excluded from this scalar-only scaffold.
  // - Field Mapping: ForwardTranslator evidence confirms direct mapping and autosize string behavior for capacity/flow fields.
  // - TODO(parity): Add excluded relationship APIs and loop behavior in a dedicated parity pass.
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

 protected:
  using ImplType = detail::ChillerElectricReformulatedEIR_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerElectricReformulatedEIR(std::shared_ptr<detail::ChillerElectricReformulatedEIR_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
