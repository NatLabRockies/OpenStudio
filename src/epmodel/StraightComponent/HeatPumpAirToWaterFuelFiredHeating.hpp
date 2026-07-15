/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Curve;
  class HeatPumpAirToWaterFuelFiredCooling;
  class Model;

  namespace detail {
    class HeatPumpAirToWaterFuelFiredHeating_Impl;
  }

  class EPMODEL_API HeatPumpAirToWaterFuelFiredHeating : public StraightComponent
  {
   public:
    explicit HeatPumpAirToWaterFuelFiredHeating(const Model& model);
    explicit HeatPumpAirToWaterFuelFiredHeating(const Model& model, const Curve& normalizedCapacityFunctionofTemperatureCurve,
                                                const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve,
                                                const Curve& fuelEnergyInputRatioFunctionofPLRCurve);

    virtual ~HeatPumpAirToWaterFuelFiredHeating() override = default;
    HeatPumpAirToWaterFuelFiredHeating(const HeatPumpAirToWaterFuelFiredHeating& other) = default;
    HeatPumpAirToWaterFuelFiredHeating(HeatPumpAirToWaterFuelFiredHeating&& other) = default;
    HeatPumpAirToWaterFuelFiredHeating& operator=(const HeatPumpAirToWaterFuelFiredHeating&) = default;
    HeatPumpAirToWaterFuelFiredHeating& operator=(HeatPumpAirToWaterFuelFiredHeating&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fuelTypeValues();
    static std::vector<std::string> flowModeValues();
    static std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues();
    static std::vector<std::string> waterTemperatureCurveInputVariableValues();
    static std::vector<std::string> defrostControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::HeatPumpAirToWaterFuelFiredHeating.
    // - Implemented Parity: Preserves the canonical constructor defaults, the companion-cooling relationship, required/optional curve target helpers, the plant-supply-only `addToNode(...)` contract, and the scalar fuel, capacity, COP, flow, sizing, defrost, temperature, and power APIs with matching autosize/default behavior.
    // - Documented Delta: Air-source node handling remains intentionally omitted because epmodel does not currently project the translator-created `OutdoorAir:Node` companion object into a canonical wrapper-level helper.
    // - Field/Storage Mapping: Scalar and object-target accessors map directly to persisted `HeatPump:AirToWater:FuelFired:Heating` fields, while plant connectivity stays on the heating object's water node fields.
    // - Evidence: `src/model/HeatPumpAirToWaterFuelFiredHeating.hpp`, `src/model/HeatPumpAirToWaterFuelFiredHeating.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWaterFuelFiredHeating.cpp`.
    // - Remaining Parity Work: Add the omitted air-source-node helper if epmodel later chooses to model the translator-emitted `OutdoorAir:Node` companion relationship directly.
    boost::optional<HeatPumpAirToWaterFuelFiredCooling> companionCoolingHeatPump() const;
    bool setCompanionCoolingHeatPump(const HeatPumpAirToWaterFuelFiredCooling& heatPumpAirToWaterFuelFiredCooling);
    void resetCompanionCoolingHeatPump();

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    boost::optional<double> nominalHeatingCapacity() const;
    bool isNominalHeatingCapacityAutosized() const;
    boost::optional<double> autosizedNominalHeatingCapacity();
    bool setNominalHeatingCapacity(double nominalHeatingCapacity);
    void resetNominalHeatingCapacity();
    void autosizeNominalHeatingCapacity();

    double nominalCOP() const;
    bool setNominalCOP(double nominalCOP);

    boost::optional<double> designFlowRate() const;
    bool isDesignFlowRateAutosized() const;
    boost::optional<double> autosizedDesignFlowRate();
    bool setDesignFlowRate(double designFlowRate);
    void resetDesignFlowRate();
    void autosizeDesignFlowRate();

    double designSupplyTemperature() const;
    bool setDesignSupplyTemperature(double designSupplyTemperature);

    boost::optional<double> designTemperatureLift() const;
    bool isDesignTemperatureLiftAutosized() const;
    boost::optional<double> autosizedDesignTemperatureLift();
    bool setDesignTemperatureLift(double designTemperatureLift);
    void autosizeDesignTemperatureLift();

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    std::string flowMode() const;
    bool setFlowMode(const std::string& flowMode);

    std::string outdoorAirTemperatureCurveInputVariable() const;
    bool setOutdoorAirTemperatureCurveInputVariable(const std::string& outdoorAirTemperatureCurveInputVariable);

    std::string waterTemperatureCurveInputVariable() const;
    bool setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable);

    Curve normalizedCapacityFunctionofTemperatureCurve() const;
    bool setNormalizedCapacityFunctionofTemperatureCurve(const Curve& normalizedCapacityFunctionofTemperatureCurve);

    Curve fuelEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setFuelEnergyInputRatioFunctionofTemperatureCurve(const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve);

    Curve fuelEnergyInputRatioFunctionofPLRCurve() const;
    bool setFuelEnergyInputRatioFunctionofPLRCurve(const Curve& fuelEnergyInputRatioFunctionofPLRCurve);

    double minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

    double maximumPartLoadRatio() const;
    bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

    std::string defrostControlType() const;
    bool setDefrostControlType(const std::string& defrostControlType);

    double defrostOperationTimeFraction() const;
    bool setDefrostOperationTimeFraction(double defrostOperationTimeFraction);

    boost::optional<Curve> fuelEnergyInputRatioDefrostAdjustmentCurve() const;
    bool setFuelEnergyInputRatioDefrostAdjustmentCurve(const Curve& fuelEnergyInputRatioDefrostAdjustmentCurve);
    void resetFuelEnergyInputRatioDefrostAdjustmentCurve();

    double resistiveDefrostHeaterCapacity() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);

    double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
    bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);

    boost::optional<Curve> cyclingRatioFactorCurve() const;
    bool setCyclingRatioFactorCurve(const Curve& cyclingRatioFactorCurve);
    void resetCyclingRatioFactorCurve();

    double nominalAuxiliaryElectricPower() const;
    bool setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower);

    boost::optional<Curve> auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(const Curve& auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve);
    void resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();

    boost::optional<Curve> auxiliaryElectricEnergyInputRatioFunctionofPLRCurve() const;
    bool setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(const Curve& auxiliaryElectricEnergyInputRatioFunctionofPLRCurve);
    void resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve();

    double standbyElectricPower() const;
    bool setStandbyElectricPower(double standbyElectricPower);

    double minimumUnloadingRatio() const;
    bool setMinimumUnloadingRatio(double minimumUnloadingRatio);

   protected:
    using ImplType = detail::HeatPumpAirToWaterFuelFiredHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpAirToWaterFuelFiredHeating(std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
