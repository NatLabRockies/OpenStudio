/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRHEATING_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Curve;
class PlantLoop;
class Node;
class HeatPumpPlantLoopEIRCooling;

namespace detail {
class HeatPumpPlantLoopEIRHeating_Impl;
}

class EPMODEL_API HeatPumpPlantLoopEIRHeating : public WaterToWaterComponent
{
 public:
  explicit HeatPumpPlantLoopEIRHeating(const Model& model, const Curve& capacityModifierFunctionofTemperatureCurve,
                                       const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve,
                                       const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve);
  explicit HeatPumpPlantLoopEIRHeating(const Model& model);

  virtual ~HeatPumpPlantLoopEIRHeating() override = default;
  HeatPumpPlantLoopEIRHeating(const HeatPumpPlantLoopEIRHeating& other) = default;
  HeatPumpPlantLoopEIRHeating(HeatPumpPlantLoopEIRHeating&& other) = default;
  HeatPumpPlantLoopEIRHeating& operator=(const HeatPumpPlantLoopEIRHeating&) = default;
  HeatPumpPlantLoopEIRHeating& operator=(HeatPumpPlantLoopEIRHeating&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validCondenserTypeValues();
  static std::vector<std::string> condenserTypeValues();

  // Schema Alignment Notes:
  // - Status: Parity with documented deltas. The canonical curve, companion, and loop/node convenience surface is preserved here.
  // - Canonical Counterpart: openstudio::model::HeatPumpPlantLoopEIRHeating.
  // - Implemented Parity: Canonical constructors, condenser/source-loop coupling, companion heat-pump linkage, required and optional curve
  //   relationships, load/source/heat-recovery loop conveniences, node conveniences, and scalar accessors preserve the model-side API shape.
  // - Documented Delta: Autosized-value query helpers still return `none` until epmodel grows canonical SQL-backed autosized result support.
  // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `HeatPump:PlantLoop:EIR:Heating` fields directly, including autosized flow/capacity behavior.
  // - Evidence: `src/model/HeatPumpPlantLoopEIRHeating.hpp`, `src/model/HeatPumpPlantLoopEIRHeating.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpPlantLoopEIRHeating.cpp`.
  // - Remaining Parity Work: Any further work should focus on shared water-to-water base behavior only if multiple wrappers need the same fix.
  std::string condenserType() const;
  bool setCondenserType(const std::string& condenserType);

  boost::optional<HeatPumpPlantLoopEIRCooling> companionCoolingHeatPump() const;
  bool setCompanionCoolingHeatPump(const HeatPumpPlantLoopEIRCooling& companionCoolingHeatPump);

  boost::optional<double> loadSideReferenceFlowRate() const;
  bool isLoadSideReferenceFlowRateAutosized() const;
  bool setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate);
  void autosizeLoadSideReferenceFlowRate();
  boost::optional<double> autosizedLoadSideReferenceFlowRate() const;

  boost::optional<double> sourceSideReferenceFlowRate() const;
  bool isSourceSideReferenceFlowRateAutosized() const;
  bool setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate);
  void autosizeSourceSideReferenceFlowRate();
  boost::optional<double> autosizedSourceSideReferenceFlowRate() const;

  boost::optional<double> heatRecoveryReferenceFlowRate() const;
  bool isHeatRecoveryReferenceFlowRateAutosized() const;
  bool setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate);
  void autosizeHeatRecoveryReferenceFlowRate();
  boost::optional<double> autosizedHeatRecoveryReferenceFlowRate() const;

  boost::optional<double> referenceCapacity() const;
  bool isReferenceCapacityAutosized() const;
  bool setReferenceCapacity(double referenceCapacity);
  void autosizeReferenceCapacity();
  boost::optional<double> autosizedReferenceCapacity() const;

  double referenceCoefficientofPerformance() const;
  bool setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance);

  double sizingFactor() const;
  bool setSizingFactor(double sizingFactor);

  Curve capacityModifierFunctionofTemperatureCurve() const;
  bool setCapacityModifierFunctionofTemperatureCurve(const Curve& capacityModifierFunctionofTemperatureCurve);

  Curve electricInputtoOutputRatioModifierFunctionofTemperatureCurve() const;
  bool setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve);

  Curve electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve() const;
  bool setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve);

  double heatingToCoolingCapacitySizingRatio() const;
  bool setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio);

  std::string heatPumpSizingMethod() const;
  bool setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod);

  std::string controlType() const;
  bool setControlType(const std::string& controlType);

  std::string flowMode() const;
  bool setFlowMode(const std::string& flowMode);

  double minimumPartLoadRatio() const;
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

  double minimumSourceInletTemperature() const;
  bool setMinimumSourceInletTemperature(double minimumSourceInletTemperature);

  double maximumSourceInletTemperature() const;
  bool setMaximumSourceInletTemperature(double maximumSourceInletTemperature);

  boost::optional<Curve> minimumSupplyWaterTemperatureCurve() const;
  bool setMinimumSupplyWaterTemperatureCurve(const Curve& minimumSupplyWaterTemperatureCurve);
  void resetMinimumSupplyWaterTemperatureCurve();

  boost::optional<Curve> maximumSupplyWaterTemperatureCurve() const;
  bool setMaximumSupplyWaterTemperatureCurve(const Curve& maximumSupplyWaterTemperatureCurve);
  void resetMaximumSupplyWaterTemperatureCurve();

  boost::optional<Curve> dryOutdoorCorrectionFactorCurve() const;
  bool setDryOutdoorCorrectionFactorCurve(const Curve& dryOutdoorCorrectionFactorCurve);
  void resetDryOutdoorCorrectionFactorCurve();

  double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);

  std::string heatPumpDefrostControl() const;
  bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);

  double heatPumpDefrostTimePeriodFraction() const;
  bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);

  boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
  bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve);
  void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

  boost::optional<Curve> timedEmpiricalDefrostFrequencyCurve() const;
  bool setTimedEmpiricalDefrostFrequencyCurve(const Curve& timedEmpiricalDefrostFrequencyCurve);
  void resetTimedEmpiricalDefrostFrequencyCurve();

  boost::optional<Curve> timedEmpiricalDefrostHeatLoadPenaltyCurve() const;
  bool setTimedEmpiricalDefrostHeatLoadPenaltyCurve(const Curve& timedEmpiricalDefrostHeatLoadPenaltyCurve);
  void resetTimedEmpiricalDefrostHeatLoadPenaltyCurve();

  boost::optional<Curve> timedEmpiricalDefrostHeatInputEnergyFractionCurve() const;
  bool setTimedEmpiricalDefrostHeatInputEnergyFractionCurve(const Curve& timedEmpiricalDefrostHeatInputEnergyFractionCurve);
  void resetTimedEmpiricalDefrostHeatInputEnergyFractionCurve();

  double minimumHeatRecoveryOutletTemperature() const;
  bool setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature);

  boost::optional<Curve> heatRecoveryCapacityModifierFunctionofTemperatureCurve() const;
  bool setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(const Curve& heatRecoveryCapacityModifierFunctionofTemperatureCurve);
  void resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();

  boost::optional<Curve> heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() const;
  bool setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
    const Curve& heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve);
  void resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();

  boost::optional<PlantLoop> loadSideWaterLoop() const;
  boost::optional<PlantLoop> sourceSideWaterLoop() const;
  boost::optional<PlantLoop> heatRecoveryLoop() const;

  boost::optional<Node> sourceSideWaterInletNode() const;
  boost::optional<Node> sourceSideWaterOutletNode() const;
  boost::optional<Node> loadSideWaterInletNode() const;
  boost::optional<Node> loadSideWaterOutletNode() const;
  boost::optional<Node> heatRecoveryInletNode() const;
  boost::optional<Node> heatRecoveryOutletNode() const;

 protected:
  using ImplType = detail::HeatPumpPlantLoopEIRHeating_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatPumpPlantLoopEIRHeating(std::shared_ptr<detail::HeatPumpPlantLoopEIRHeating_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
