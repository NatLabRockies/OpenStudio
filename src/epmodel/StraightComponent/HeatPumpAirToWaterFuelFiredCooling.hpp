/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDCOOLING_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDCOOLING_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Curve;
  class HeatPumpAirToWaterFuelFiredHeating;
  class Model;

  namespace detail {
    class HeatPumpAirToWaterFuelFiredCooling_Impl;
  }

  class EPMODEL_API HeatPumpAirToWaterFuelFiredCooling : public StraightComponent
  {
   public:
    explicit HeatPumpAirToWaterFuelFiredCooling(const Model& model);
    explicit HeatPumpAirToWaterFuelFiredCooling(const Model& model, const Curve& normalizedCapacityFunctionofTemperatureCurve,
                                                const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve,
                                                const Curve& fuelEnergyInputRatioFunctionofPLRCurve);

    virtual ~HeatPumpAirToWaterFuelFiredCooling() override = default;
    HeatPumpAirToWaterFuelFiredCooling(const HeatPumpAirToWaterFuelFiredCooling& other) = default;
    HeatPumpAirToWaterFuelFiredCooling(HeatPumpAirToWaterFuelFiredCooling&& other) = default;
    HeatPumpAirToWaterFuelFiredCooling& operator=(const HeatPumpAirToWaterFuelFiredCooling&) = default;
    HeatPumpAirToWaterFuelFiredCooling& operator=(HeatPumpAirToWaterFuelFiredCooling&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fuelTypeValues();
    static std::vector<std::string> flowModeValues();
    static std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues();
    static std::vector<std::string> waterTemperatureCurveInputVariableValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::HeatPumpAirToWaterFuelFiredCooling.
    // - Implemented Parity: Preserves the canonical constructor defaults, the companion-heating relationship, required/optional curve target helpers, the plant-supply-only `addToNode(...)` contract, and the scalar fuel, capacity, COP, flow, sizing, temperature, and power APIs with matching autosize/default behavior.
    // - Documented Delta: Air-source node handling remains intentionally omitted because epmodel does not currently project the translator-created `OutdoorAir:Node` companion object into a canonical wrapper-level helper.
    // - Field/Storage Mapping: Scalar and object-target accessors map directly to persisted `HeatPump:AirToWater:FuelFired:Cooling` fields, while plant connectivity stays on the cooling object's water node fields.
    // - Evidence: `src/model/HeatPumpAirToWaterFuelFiredCooling.hpp`, `src/model/HeatPumpAirToWaterFuelFiredCooling.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHeatPumpAirToWaterFuelFiredCooling.cpp`.
    // - Remaining Parity Work: Add the omitted air-source-node helper if epmodel later chooses to model the translator-emitted `OutdoorAir:Node` companion relationship directly.
    boost::optional<HeatPumpAirToWaterFuelFiredHeating> companionHeatingHeatPump() const;
    bool setCompanionHeatingHeatPump(const HeatPumpAirToWaterFuelFiredHeating& heatPumpAirToWaterFuelFiredHeating);
    void resetCompanionHeatingHeatPump();

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    boost::optional<double> nominalCoolingCapacity() const;
    bool isNominalCoolingCapacityAutosized() const;
    boost::optional<double> autosizedNominalCoolingCapacity();
    bool setNominalCoolingCapacity(double nominalCoolingCapacity);
    void resetNominalCoolingCapacity();
    void autosizeNominalCoolingCapacity();

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
    using ImplType = detail::HeatPumpAirToWaterFuelFiredCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpAirToWaterFuelFiredCooling(std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
