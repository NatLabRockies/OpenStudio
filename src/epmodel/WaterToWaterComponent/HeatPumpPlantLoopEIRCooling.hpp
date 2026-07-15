/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_HPP
#define EPMODEL_HEATPUMPPLANTLOOPEIRCOOLING_HPP

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
  class HeatPumpPlantLoopEIRHeating;

  namespace detail {
    class HeatPumpPlantLoopEIRCooling_Impl;
  }

  class EPMODEL_API HeatPumpPlantLoopEIRCooling : public WaterToWaterComponent
  {
   public:
    explicit HeatPumpPlantLoopEIRCooling(const Model& model, const Curve& capacityModifierFunctionofTemperatureCurve,
                                         const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve,
                                         const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve);
    explicit HeatPumpPlantLoopEIRCooling(const Model& model);

    virtual ~HeatPumpPlantLoopEIRCooling() override = default;
    HeatPumpPlantLoopEIRCooling(const HeatPumpPlantLoopEIRCooling& other) = default;
    HeatPumpPlantLoopEIRCooling(HeatPumpPlantLoopEIRCooling&& other) = default;
    HeatPumpPlantLoopEIRCooling& operator=(const HeatPumpPlantLoopEIRCooling&) = default;
    HeatPumpPlantLoopEIRCooling& operator=(HeatPumpPlantLoopEIRCooling&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validCondenserTypeValues();
    static std::vector<std::string> condenserTypeValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical curve, companion, and loop/node convenience surface is preserved here.
    // - Canonical Counterpart: openstudio::model::HeatPumpPlantLoopEIRCooling.
    // - Implemented Parity: Canonical constructors, condenser/source-loop coupling, companion heat-pump linkage, required and optional curve
    //   relationships, load/source/heat-recovery loop conveniences, node conveniences, and scalar accessors preserve the model-side API shape.
    // - Documented Delta: Autosized-value query helpers still return `none` until epmodel grows canonical SQL-backed autosized result support.
    // - Field/Storage Mapping: Scalar wrappers target EnergyPlus `HeatPump:PlantLoop:EIR:Cooling` fields directly, including persisted autosize sentinels for
    //   the flow/capacity fields.
    // - Evidence: `src/model/HeatPumpPlantLoopEIRCooling.hpp`, `src/model/HeatPumpPlantLoopEIRCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpPlantLoopEIRCooling.cpp`.
    // - Remaining Parity Work: Any further work should focus on shared water-to-water base behavior only if multiple wrappers need the same fix.
    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    boost::optional<HeatPumpPlantLoopEIRHeating> companionHeatingHeatPump() const;
    bool setCompanionHeatingHeatPump(const HeatPumpPlantLoopEIRHeating& companionHeatingHeatPump);

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
    bool
      setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve);

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

    double maximumHeatRecoveryOutletTemperature() const;
    bool setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature);

    boost::optional<Curve> heatRecoveryCapacityModifierFunctionofTemperatureCurve() const;
    bool setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(const Curve& heatRecoveryCapacityModifierFunctionofTemperatureCurve);
    void resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();

    boost::optional<Curve> heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() const;
    bool setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
      const Curve& heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve);
    void resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();

    boost::optional<Curve> thermosiphonCapacityFractionCurve() const;
    bool setThermosiphonCapacityFractionCurve(const Curve& thermosiphonCapacityFractionCurve);
    void resetThermosiphonCapacityFractionCurve();

    double thermosiphonMinimumTemperatureDifference() const;
    bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);

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
    using ImplType = detail::HeatPumpPlantLoopEIRCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpPlantLoopEIRCooling(std::shared_ptr<detail::HeatPumpPlantLoopEIRCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
