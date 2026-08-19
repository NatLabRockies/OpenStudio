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

  /**
   * \brief Variable-refrigerant-flow outdoor unit with typed performance curves and terminal-unit membership.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-variable-refrigerant-flow-equipment.html#airconditionervariablerefrigerantflow,AirConditioner:VariableRefrigerantFlow}.
   *
   * \par Important behavior
   * Terminal membership is exclusive and duplicate-safe. `addToNode` inserts the unit on the plant-loop demand side;
   * terminal and performance-curve relationships are maintained as typed references, including the optional piping,
   * heat-recovery, and defrost curves.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirConditionerVariableRefrigerantFlow`. The epmodel API covers the scalar,
   * schedule, curve, master-thermostat, and terminal relationships. It also exposes the internal terminal/plant
   * topology through `addToNode` and `terminals()`.
   *
   * \par Known limitations
   * The EPModel constructor does not create the Model API's optional default cooling/heating and cooling-piping
   * correction curves. The Model-only fuel/defrost, basin/crankcase, evaporative- or water-condenser, and resistive-
   * defrost field groups are not carried yet, nor are their autosize helpers. Broader AirLoopHVAC/VRF coupling and
   * family-specific autosized-result helpers are not exposed.
   */
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

    boost::optional<Curve> heatingCapacityRatioModifierFunctionofLowTemperatureCurve() const;
    bool setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(const Curve& curve);
    void resetHeatingCapacityRatioModifierFunctionofLowTemperatureCurve();

    boost::optional<Curve> heatingCapacityRatioBoundaryCurve() const;
    bool setHeatingCapacityRatioBoundaryCurve(const Curve& curve);
    void resetHeatingCapacityRatioBoundaryCurve();

    boost::optional<Curve> heatingCapacityRatioModifierFunctionofHighTemperatureCurve() const;
    bool setHeatingCapacityRatioModifierFunctionofHighTemperatureCurve(const Curve& curve);
    void resetHeatingCapacityRatioModifierFunctionofHighTemperatureCurve();

    boost::optional<Curve> heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve() const;
    bool setHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve(const Curve& curve);
    void resetHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve();

    boost::optional<Curve> heatingEnergyInputRatioBoundaryCurve() const;
    bool setHeatingEnergyInputRatioBoundaryCurve(const Curve& curve);
    void resetHeatingEnergyInputRatioBoundaryCurve();

    boost::optional<Curve> heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve() const;
    bool setHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve(const Curve& curve);
    void resetHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve();

    std::string heatingPerformanceCurveOutdoorTemperatureType() const;
    bool setHeatingPerformanceCurveOutdoorTemperatureType(const std::string& heatingPerformanceCurveOutdoorTemperatureType);

    boost::optional<Curve> heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() const;
    bool setHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(const Curve& curve);
    void resetHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();

    boost::optional<Curve> heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() const;
    bool setHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(const Curve& curve);
    void resetHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();

    boost::optional<Curve> heatingCombinationRatioCorrectionFactorCurve() const;
    bool setHeatingCombinationRatioCorrectionFactorCurve(const Curve& curve);
    void resetHeatingCombinationRatioCorrectionFactorCurve();

    boost::optional<Curve> heatingPartLoadFractionCorrelationCurve() const;
    bool setHeatingPartLoadFractionCorrelationCurve(const Curve& curve);
    void resetHeatingPartLoadFractionCorrelationCurve();

    bool heatPumpWasteHeatRecovery() const;
    bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);

    double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode() const;
    bool setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode);

    double verticalHeightusedforPipingCorrectionFactor() const;
    bool setVerticalHeightusedforPipingCorrectionFactor(double verticalHeightusedforPipingCorrectionFactor);

    boost::optional<Curve> pipingCorrectionFactorforLengthinCoolingModeCurve() const;
    bool setPipingCorrectionFactorforLengthinCoolingModeCurve(const Curve& curve);
    void resetPipingCorrectionFactorforLengthinCoolingModeCurve();

    double pipingCorrectionFactorforHeightinCoolingModeCoefficient() const;
    bool setPipingCorrectionFactorforHeightinCoolingModeCoefficient(double pipingCorrectionFactorforHeightinCoolingModeCoefficient);

    double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode() const;
    bool setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode);

    boost::optional<Curve> pipingCorrectionFactorforLengthinHeatingModeCurve() const;
    bool setPipingCorrectionFactorforLengthinHeatingModeCurve(const Curve& curve);
    void resetPipingCorrectionFactorforLengthinHeatingModeCurve();

    double pipingCorrectionFactorforHeightinHeatingModeCoefficient() const;
    bool setPipingCorrectionFactorforHeightinHeatingModeCoefficient(double pipingCorrectionFactorforHeightinHeatingModeCoefficient);

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

    double minimumOutdoorTemperatureinHeatRecoveryMode() const;
    bool setMinimumOutdoorTemperatureinHeatRecoveryMode(double minimumOutdoorTemperatureinHeatRecoveryMode);

    double maximumOutdoorTemperatureinHeatRecoveryMode() const;
    bool setMaximumOutdoorTemperatureinHeatRecoveryMode(double maximumOutdoorTemperatureinHeatRecoveryMode);

    boost::optional<Curve> heatRecoveryCoolingCapacityModifierCurve() const;
    bool setHeatRecoveryCoolingCapacityModifierCurve(const Curve& curve);
    void resetHeatRecoveryCoolingCapacityModifierCurve();

    double initialHeatRecoveryCoolingCapacityFraction() const;
    bool setInitialHeatRecoveryCoolingCapacityFraction(double initialHeatRecoveryCoolingCapacityFraction);

    double heatRecoveryCoolingCapacityTimeConstant() const;
    bool setHeatRecoveryCoolingCapacityTimeConstant(double heatRecoveryCoolingCapacityTimeConstant);

    boost::optional<Curve> heatRecoveryCoolingEnergyModifierCurve() const;
    bool setHeatRecoveryCoolingEnergyModifierCurve(const Curve& curve);
    void resetHeatRecoveryCoolingEnergyModifierCurve();

    double initialHeatRecoveryCoolingEnergyFraction() const;
    bool setInitialHeatRecoveryCoolingEnergyFraction(double initialHeatRecoveryCoolingEnergyFraction);

    double heatRecoveryCoolingEnergyTimeConstant() const;
    bool setHeatRecoveryCoolingEnergyTimeConstant(double heatRecoveryCoolingEnergyTimeConstant);

    boost::optional<Curve> heatRecoveryHeatingCapacityModifierCurve() const;
    bool setHeatRecoveryHeatingCapacityModifierCurve(const Curve& curve);
    void resetHeatRecoveryHeatingCapacityModifierCurve();

    double initialHeatRecoveryHeatingCapacityFraction() const;
    bool setInitialHeatRecoveryHeatingCapacityFraction(double initialHeatRecoveryHeatingCapacityFraction);

    double heatRecoveryHeatingCapacityTimeConstant() const;
    bool setHeatRecoveryHeatingCapacityTimeConstant(double heatRecoveryHeatingCapacityTimeConstant);

    boost::optional<Curve> heatRecoveryHeatingEnergyModifierCurve() const;
    bool setHeatRecoveryHeatingEnergyModifierCurve(const Curve& curve);
    void resetHeatRecoveryHeatingEnergyModifierCurve();

    double initialHeatRecoveryHeatingEnergyFraction() const;
    bool setInitialHeatRecoveryHeatingEnergyFraction(double initialHeatRecoveryHeatingEnergyFraction);

    double heatRecoveryHeatingEnergyTimeConstant() const;
    bool setHeatRecoveryHeatingEnergyTimeConstant(double heatRecoveryHeatingEnergyTimeConstant);

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
