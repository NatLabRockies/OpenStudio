/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICEIR_HPP
#define EPMODEL_CHILLERELECTRICEIR_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ChillerElectricEIR_Impl;
}

class EPMODEL_API ChillerElectricEIR : public WaterToWaterComponent
{
 public:
  explicit ChillerElectricEIR(const Model& model);

  virtual ~ChillerElectricEIR() override = default;
  ChillerElectricEIR(const ChillerElectricEIR& other) = default;
  ChillerElectricEIR(ChillerElectricEIR&& other) = default;
  ChillerElectricEIR& operator=(const ChillerElectricEIR&) = default;
  ChillerElectricEIR& operator=(ChillerElectricEIR&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> condenserTypeValues();
  static std::vector<std::string> chillerFlowModeValues();
  static std::vector<std::string> condenserFlowControlValues();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The EIR chiller scalar surface is aligned, while curve, schedule, and node/link behavior remains excluded.
  // - Canonical Counterpart: openstudio::model::ChillerElectricEIR.
  // - Implemented Parity: Scalar accessors for capacity, COP, flow rates, PLR limits, condenser behavior, heat recovery, and sizing preserve the canonical model API shape.
  // - Documented Delta: Relationship fields such as curves, schedules, and node/object-link targets are intentionally excluded in this pass.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `Chiller:Electric:EIR` fields directly, and autosize/autocalculate behavior follows the canonical translator contract.
  // - Evidence: `src/model/ChillerElectricEIR.hpp`, `src/model/ChillerElectricEIR.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricEIR.cpp`.
  // - Remaining Parity Work: Add the excluded relationship APIs and any remaining loop behavior only if the family moves beyond scalar parity.
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

  double referenceEnteringCondenserFluidTemperature() const;
  bool isReferenceEnteringCondenserFluidTemperatureDefaulted() const;
  bool setReferenceEnteringCondenserFluidTemperature(double referenceEnteringCondenserFluidTemperature);
  void resetReferenceEnteringCondenserFluidTemperature();

  boost::optional<double> referenceChilledWaterFlowRate() const;
  bool isReferenceChilledWaterFlowRateAutosized() const;
  bool setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate);
  bool setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate);
  void resetReferenceChilledWaterFlowRate();
  void autosizeReferenceChilledWaterFlowRate();

  boost::optional<double> referenceCondenserFluidFlowRate() const;
  bool isReferenceCondenserFluidFlowRateAutosized() const;
  bool setReferenceCondenserFluidFlowRate(boost::optional<double> referenceCondenserFluidFlowRate);
  bool setReferenceCondenserFluidFlowRate(double referenceCondenserFluidFlowRate);
  void resetReferenceCondenserFluidFlowRate();
  void autosizeReferenceCondenserFluidFlowRate();

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

  std::string condenserType() const;
  bool isCondenserTypeDefaulted() const;
  bool setCondenserType(const std::string& condenserType);
  void resetCondenserType();

  double condenserFanPowerRatio() const;
  bool isCondenserFanPowerRatioDefaulted() const;
  bool setCondenserFanPowerRatio(double condenserFanPowerRatio);
  void resetCondenserFanPowerRatio();

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

  double basinHeaterCapacity() const;
  bool isBasinHeaterCapacityDefaulted() const;
  bool setBasinHeaterCapacity(double basinHeaterCapacity);
  void resetBasinHeaterCapacity();

  double basinHeaterSetpointTemperature() const;
  bool isBasinHeaterSetpointTemperatureDefaulted() const;
  bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
  void resetBasinHeaterSetpointTemperature();

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
  using ImplType = detail::ChillerElectricEIR_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ChillerElectricEIR(std::shared_ptr<detail::ChillerElectricEIR_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
