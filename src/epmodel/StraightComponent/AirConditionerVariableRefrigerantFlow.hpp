/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Curve;
  class Schedule;
  class ThermalZone;
  class ZoneHVACTerminalUnitVariableRefrigerantFlow;

  namespace detail {
    class AirConditionerVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlow : public StraightComponent
  {
   public:
    explicit AirConditionerVariableRefrigerantFlow(const Model& model);

    virtual ~AirConditionerVariableRefrigerantFlow() override = default;
    AirConditionerVariableRefrigerantFlow(const AirConditionerVariableRefrigerantFlow& other) = default;
    AirConditionerVariableRefrigerantFlow(AirConditionerVariableRefrigerantFlow&& other) = default;
    AirConditionerVariableRefrigerantFlow& operator=(const AirConditionerVariableRefrigerantFlow&) = default;
    AirConditionerVariableRefrigerantFlow& operator=(AirConditionerVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingPerformanceCurveOutdoorTemperatureTypeValues();
    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> condenserTypeValues();

    bool addToNode(Node& node);

    bool addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal);
    void removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal);
    void removeAllTerminals();
    std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> terminals() const;

    // Schema Alignment Notes:
    // - Status: Partial Parity. Core VRF scalar controls, sizing/performance fields, direct schedule/zone relationships, the standard cooling
    //   performance curves, the defrost EIR curve, and the standard VRF terminal relationship are aligned.
    // - Canonical Counterpart: openstudio::model::AirConditionerVariableRefrigerantFlow.
    // - Implemented Parity: The selected scalar methods, availability/thermostat-priority/basin schedules, master-thermostat zone, ten standard
    //   cooling-curve relationships, terminal relationship, and demand-side `addToNode` preserve the canonical contract and current plant-loop
    //   insertion behavior. Terminal membership is deliberately exclusive and duplicate-safe rather than reproducing the canonical wrapper's
    //   duplicate and competing-list inconsistencies.
    // - Documented Delta: The canonical Model constructor creates default objects for the ten cooling-curve relationships, while the EPModel
    //   constructor deliberately leaves these optional EnergyPlus fields blank pending a separate default-curve and canonicalization decision.
    //   Other curve helpers remain omitted. `addToNode` is intentionally limited to PlantLoop demand-side insertion, and no broader VRF topology
    //   or coupling between the optional thermostat relationships and priority-control scalar is claimed here.
    // - Field/Storage Mapping: Most preserved scalar methods map directly to EnergyPlus `AirConditioner:VariableRefrigerantFlow` fields. Terminal
    //   membership uses the EnergyPlus `ZoneTerminalUnitList` object with pointer-backed extensible entries. Cooling temperature modifiers and
    //   the defrost EIR curve use `BivariateFunctions`; cooling boundary, part-load, and combination curves use `UnivariateFunctions`.
    //   `condenserType()` follows the canonical defaulted readback behavior by deriving `AirCooled` versus `WaterCooled` from current plant-loop
    //   attachment when blank.
    // - Ownership: VRF removal owns only its terminal list and deliberately preserves every referenced standard-VRF performance curve, including
    //   the defrost EIR curve; full all-curve ownership remains deferred.
    // - Evidence: `src/model/AirConditionerVariableRefrigerantFlow.hpp`, `src/model/AirConditionerVariableRefrigerantFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlow.cpp`, and `src/epmodel/test/AirConditionerVariableRefrigerantFlow_GTest.cpp`.
    // - Remaining Parity Work: Add the heating, heat-recovery, and piping curve accessors and decide the cooling default-curve construction and
    //   any full all-curve ownership contract separately.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<ThermalZone> zoneforMasterThermostatLocation() const;
    bool setZoneforMasterThermostatLocation(const ThermalZone& zone);
    void resetZoneforMasterThermostatLocation();

    boost::optional<Schedule> thermostatPrioritySchedule() const;
    bool setThermostatPrioritySchedule(Schedule& schedule);
    void resetThermostatPrioritySchedule();

    boost::optional<Schedule> basinHeaterOperatingSchedule() const;
    bool setBasinHeaterOperatingSchedule(Schedule& schedule);
    void resetBasinHeaterOperatingSchedule();

    boost::optional<double> grossRatedTotalCoolingCapacity() const;
    bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
    bool isGrossRatedTotalCoolingCapacityAutosized() const;
    void autosizeGrossRatedTotalCoolingCapacity();

    double grossRatedCoolingCOP() const;
    bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

    boost::optional<Curve> coolingCapacityRatioModifierFunctionofLowTemperatureCurve() const;
    bool setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(const Curve& curve);
    void resetCoolingCapacityRatioModifierFunctionofLowTemperatureCurve();

    boost::optional<Curve> coolingCapacityRatioBoundaryCurve() const;
    bool setCoolingCapacityRatioBoundaryCurve(const Curve& curve);
    void resetCoolingCapacityRatioBoundaryCurve();

    boost::optional<Curve> coolingCapacityRatioModifierFunctionofHighTemperatureCurve() const;
    bool setCoolingCapacityRatioModifierFunctionofHighTemperatureCurve(const Curve& curve);
    void resetCoolingCapacityRatioModifierFunctionofHighTemperatureCurve();

    boost::optional<Curve> coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve() const;
    bool setCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve(const Curve& curve);
    void resetCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve();

    boost::optional<Curve> coolingEnergyInputRatioBoundaryCurve() const;
    bool setCoolingEnergyInputRatioBoundaryCurve(const Curve& curve);
    void resetCoolingEnergyInputRatioBoundaryCurve();

    boost::optional<Curve> coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve() const;
    bool setCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve(const Curve& curve);
    void resetCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve();

    boost::optional<Curve> coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() const;
    bool setCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(const Curve& curve);
    void resetCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();

    boost::optional<Curve> coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() const;
    bool setCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(const Curve& curve);
    void resetCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();

    boost::optional<Curve> coolingCombinationRatioCorrectionFactorCurve() const;
    bool setCoolingCombinationRatioCorrectionFactorCurve(const Curve& curve);
    void resetCoolingCombinationRatioCorrectionFactorCurve();

    boost::optional<Curve> coolingPartLoadFractionCorrelationCurve() const;
    bool setCoolingPartLoadFractionCorrelationCurve(const Curve& curve);
    void resetCoolingPartLoadFractionCorrelationCurve();

    boost::optional<double> grossRatedHeatingCapacity() const;
    bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
    bool isGrossRatedHeatingCapacityAutosized() const;
    void autosizeGrossRatedHeatingCapacity();

    double ratedHeatingCapacitySizingRatio() const;
    bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);

    std::string heatingPerformanceCurveOutdoorTemperatureType() const;
    bool setHeatingPerformanceCurveOutdoorTemperatureType(const std::string& heatingPerformanceCurveOutdoorTemperatureType);

    bool heatPumpWasteHeatRecovery() const;
    bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);

    int numberofCompressors() const;
    bool setNumberofCompressors(int numberofCompressors);

    std::string defrostStrategy() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);

    boost::optional<Curve> defrostEnergyInputRatioModifierFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve);
    void resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);
    bool isCondenserTypeDefaulted() const;
    void resetCondenserType();

   protected:
    using ImplType = detail::AirConditionerVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirConditionerVariableRefrigerantFlow(std::shared_ptr<detail::AirConditionerVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
