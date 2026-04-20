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
class Curve;
class Schedule;
class Node;
class PlantLoop;

namespace detail {
class ChillerElectricEIR_Impl;
}

class EPMODEL_API ChillerElectricEIR : public WaterToWaterComponent
{
 public:
  explicit ChillerElectricEIR(const Model& model, const Curve& CCFofT, const Curve& EItoCORFofT, const Curve& EItoCORFofPLR);
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
  // - Status: Parity with documented deltas. The canonical scalar, curve, schedule, and loop convenience surface is aligned.
  // - Canonical Counterpart: openstudio::model::ChillerElectricEIR.
  // - Implemented Parity: Canonical constructor defaults, required and optional relationship fields, chilled/condenser/heat-recovery loop conveniences,
  //   loop-aware condenser-type restrictions, and shared tertiary-routing behavior preserve the model-side API shape.
  // - Documented Delta: Autosized-value helpers remain epmodel stubs that return `none` until autosized results are surfaced here, and the static
  //   enum-helper names are `*Values()` instead of the canonical `valid*Values()` names.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `Chiller:Electric:EIR` fields directly, while curve, schedule, and node relationships are
  //   persisted as ordinary object links on the same object and interpreted through the shared water-to-water topology layer.
  // - Evidence: `src/model/ChillerElectricEIR.hpp`, `src/model/ChillerElectricEIR.cpp`,
  //   `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricEIR.cpp`, and `src/epmodel/test/ChillerElectricEIR_GTest.cpp`.
  // - Remaining Parity Work: Surface real autosized values for the condenser-flow and heat-recovery sizing helpers instead of the current `none` stubs.
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

  Curve coolingCapacityFunctionOfTemperature() const;
  bool setCoolingCapacityFunctionOfTemperature(const Curve& curve);

  Curve electricInputToCoolingOutputRatioFunctionOfTemperature() const;
  bool setElectricInputToCoolingOutputRatioFunctionOfTemperature(const Curve& curve);

  Curve electricInputToCoolingOutputRatioFunctionOfPLR() const;
  bool setElectricInputToCoolingOutputRatioFunctionOfPLR(const Curve& curve);

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

  boost::optional<Schedule> basinHeaterSchedule() const;
  bool setBasinHeaterSchedule(Schedule& schedule);
  void resetBasinHeaterSchedule();

  double condenserHeatRecoveryRelativeCapacityFraction() const;
  bool setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction);

  boost::optional<Schedule> heatRecoveryInletHighTemperatureLimitSchedule() const;
  bool setHeatRecoveryInletHighTemperatureLimitSchedule(Schedule& schedule);
  void resetHeatRecoveryInletHighTemperatureLimitSchedule();

  boost::optional<Node> heatRecoveryLeavingTemperatureSetpointNode() const;
  bool setHeatRecoveryLeavingTemperatureSetpointNode(const Node& node);
  void resetHeatRecoveryLeavingTemperatureSetpointNode();

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  std::string condenserFlowControl() const;
  bool setCondenserFlowControl(const std::string& condenserFlowControl);

  boost::optional<Curve> condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve() const;
  bool setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(const Curve& curve);
  void resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve();

  boost::optional<Schedule> temperatureDifferenceAcrossCondenserSchedule() const;
  bool setTemperatureDifferenceAcrossCondenserSchedule(Schedule& schedule);
  void resetTemperatureDifferenceAcrossCondenserSchedule();

  double condenserMinimumFlowFraction() const;
  bool setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction);

  boost::optional<Curve> thermosiphonCapacityFractionCurve() const;
  bool setThermosiphonCapacityFractionCurve(const Curve& curve);
  void resetThermosiphonCapacityFractionCurve();

  double thermosiphonMinimumTemperatureDifference() const;
  bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

  boost::optional<double> autosizedReferenceCapacity() const;
  boost::optional<double> autosizedReferenceChilledWaterFlowRate() const;
  boost::optional<double> autosizedReferenceCondenserFluidFlowRate() const;
  boost::optional<double> autosizedDesignHeatRecoveryWaterFlowRate() const;

  boost::optional<PlantLoop> chilledWaterLoop() const;
  boost::optional<Node> chilledWaterInletNode() const;
  boost::optional<Node> chilledWaterOutletNode() const;

  boost::optional<PlantLoop> condenserWaterLoop() const;
  boost::optional<Node> condenserInletNode() const;
  boost::optional<Node> condenserOutletNode() const;

  boost::optional<PlantLoop> heatRecoveryLoop() const;
  boost::optional<Node> heatRecoveryInletNode() const;
  boost::optional<Node> heatRecoveryOutletNode() const;

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
