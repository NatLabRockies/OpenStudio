/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROLHR_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROLHR_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Curve;
  class Schedule;
  class ZoneHVACTerminalUnitVariableRefrigerantFlow;

  namespace detail {
    class AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR : public HVACComponent
  {
   public:
    explicit AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(const Model& model);

    virtual ~AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR() override = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(const AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR& other) =
      default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR&& other) = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR&
      operator=(const AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR&) = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR&
      operator=(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> refrigerantTypeValues();
    static std::vector<std::string> refrigerantTemperatureControlAlgorithmforIndoorUnitValues();
    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> defrostControlValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The long scalar VRF heat-recovery surface, terminal ownership, and outdoor-unit curve relationships are aligned. Canonical loading rows exist in EnergyPlus storage but do not yet have a Model-shaped public API.
    // - Canonical Counterpart: openstudio::model::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.
    // - Implemented Parity: The preserved scalar API surface mirrors the canonical heat-recovery, refrigerant, defrost, pipe, and compressor-field contract exposed in the model type. The constructor creates the two required outdoor-unit curves, three complete compressor-loading rows, and one shared built-in refrigerant dataset through `Model`.
    // - Documented Delta: epmodel does not expose a Model-shaped `LoadingIndex` API or autosized-result conveniences yet.
    // - Field/Storage Mapping: The preserved scalars and three outdoor-unit curve relationships map directly to EnergyPlus
    //   `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` storage. Terminal ownership is stored in the referenced
    //   `ZoneTerminalUnitList`; refrigerant tables remain model-owned EnergyPlus objects and survive consumer removal.
    // - Evidence: `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp`, `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.cpp`, `src/epmodel/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_GTest.cpp`, and `src/model/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted loading-index API when a workflow requires mutation beyond the complete default graph.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    bool addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal);
    void removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal);
    void removeAllTerminals();
    std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> terminals() const;

    std::string refrigerantType() const;
    bool setRefrigerantType(const std::string& refrigerantType);

    boost::optional<double> ratedEvaporativeCapacity() const;
    bool isRatedEvaporativeCapacityAutosized() const;
    bool setRatedEvaporativeCapacity(double ratedEvaporativeCapacity);
    void autosizeRatedEvaporativeCapacity();

    double ratedCompressorPowerPerUnitofRatedEvaporativeCapacity() const;
    bool setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(double ratedCompressorPowerPerUnitofRatedEvaporativeCapacity);

    double minimumOutdoorAirTemperatureinCoolingOnlyMode() const;
    bool setMinimumOutdoorAirTemperatureinCoolingOnlyMode(double minimumOutdoorAirTemperatureinCoolingOnlyMode);

    double maximumOutdoorAirTemperatureinCoolingOnlyMode() const;
    bool setMaximumOutdoorAirTemperatureinCoolingOnlyMode(double maximumOutdoorAirTemperatureinCoolingOnlyMode);

    double minimumOutdoorAirTemperatureinHeatingOnlyMode() const;
    bool setMinimumOutdoorAirTemperatureinHeatingOnlyMode(double minimumOutdoorAirTemperatureinHeatingOnlyMode);

    double maximumOutdoorAirTemperatureinHeatingOnlyMode() const;
    bool setMaximumOutdoorAirTemperatureinHeatingOnlyMode(double maximumOutdoorAirTemperatureinHeatingOnlyMode);

    double minimumOutdoorTemperatureinHeatRecoveryMode() const;
    bool setMinimumOutdoorTemperatureinHeatRecoveryMode(double minimumOutdoorTemperatureinHeatRecoveryMode);

    double maximumOutdoorTemperatureinHeatRecoveryMode() const;
    bool setMaximumOutdoorTemperatureinHeatRecoveryMode(double maximumOutdoorTemperatureinHeatRecoveryMode);

    std::string refrigerantTemperatureControlAlgorithmforIndoorUnit() const;
    bool setRefrigerantTemperatureControlAlgorithmforIndoorUnit(const std::string& refrigerantTemperatureControlAlgorithmforIndoorUnit);

    double referenceEvaporatingTemperatureforIndoorUnit() const;
    bool setReferenceEvaporatingTemperatureforIndoorUnit(double referenceEvaporatingTemperatureforIndoorUnit);

    double referenceCondensingTemperatureforIndoorUnit() const;
    bool setReferenceCondensingTemperatureforIndoorUnit(double referenceCondensingTemperatureforIndoorUnit);

    double variableEvaporatingTemperatureMinimumforIndoorUnit() const;
    bool setVariableEvaporatingTemperatureMinimumforIndoorUnit(double variableEvaporatingTemperatureMinimumforIndoorUnit);

    double variableEvaporatingTemperatureMaximumforIndoorUnit() const;
    bool setVariableEvaporatingTemperatureMaximumforIndoorUnit(double variableEvaporatingTemperatureMaximumforIndoorUnit);

    double variableCondensingTemperatureMinimumforIndoorUnit() const;
    bool setVariableCondensingTemperatureMinimumforIndoorUnit(double variableCondensingTemperatureMinimumforIndoorUnit);

    double variableCondensingTemperatureMaximumforIndoorUnit() const;
    bool setVariableCondensingTemperatureMaximumforIndoorUnit(double variableCondensingTemperatureMaximumforIndoorUnit);

    double outdoorUnitEvaporatorReferenceSuperheating() const;
    bool setOutdoorUnitEvaporatorReferenceSuperheating(double outdoorUnitEvaporatorReferenceSuperheating);

    double outdoorUnitCondenserReferenceSubcooling() const;
    bool setOutdoorUnitCondenserReferenceSubcooling(double outdoorUnitCondenserReferenceSubcooling);

    double outdoorUnitEvaporatorRatedBypassFactor() const;
    bool setOutdoorUnitEvaporatorRatedBypassFactor(double outdoorUnitEvaporatorRatedBypassFactor);

    double outdoorUnitCondenserRatedBypassFactor() const;
    bool setOutdoorUnitCondenserRatedBypassFactor(double outdoorUnitCondenserRatedBypassFactor);

    double differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode() const;
    bool setDifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode(
      double differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode);

    double outdoorUnitHeatExchangerCapacityRatio() const;
    bool setOutdoorUnitHeatExchangerCapacityRatio(double outdoorUnitHeatExchangerCapacityRatio);

    double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity() const;
    bool setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity);

    double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity() const;
    bool setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity);

    Curve outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve() const;
    bool setOutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(const Curve& curve);

    Curve outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const;
    bool setOutdoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve);

    double diameterofMainPipeforSuctionGas() const;
    bool setDiameterofMainPipeforSuctionGas(double diameterofMainPipeforSuctionGas);

    double diameterofMainPipeforDischargeGas() const;
    bool setDiameterofMainPipeforDischargeGas(double diameterofMainPipeforDischargeGas);

    double lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const;
    bool setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(double lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);

    double equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const;
    bool setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
      double equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);

    double heightDifferenceBetweenOutdoorUnitandIndoorUnits() const;
    bool setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(double heightDifferenceBetweenOutdoorUnitandIndoorUnits);

    double mainPipeInsulationThickness() const;
    bool setMainPipeInsulationThickness(double mainPipeInsulationThickness);

    double mainPipeInsulationThermalConductivity() const;
    bool setMainPipeInsulationThermalConductivity(double mainPipeInsulationThermalConductivity);

    double crankcaseHeaterPowerperCompressor() const;
    bool setCrankcaseHeaterPowerperCompressor(double crankcaseHeaterPowerperCompressor);

    int numberofCompressors() const;
    bool setNumberofCompressors(int numberofCompressors);

    double ratioofCompressorSizetoTotalCompressorCapacity() const;
    bool setRatioofCompressorSizetoTotalCompressorCapacity(double ratioofCompressorSizetoTotalCompressorCapacity);

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeater() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(double maximumOutdoorDryBulbTemperatureforCrankcaseHeater);

    std::string defrostStrategy() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);

    std::string defrostControl() const;
    bool setDefrostControl(const std::string& defrostControl);

    boost::optional<Curve> defrostEnergyInputRatioModifierFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve);
    void resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();

    double defrostTimePeriodFraction() const;
    bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

    boost::optional<double> resistiveDefrostHeaterCapacity() const;
    bool isResistiveDefrostHeaterCapacityAutosized() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    void autosizeResistiveDefrostHeaterCapacity();

    double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
    bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);

    double initialHeatRecoveryCoolingCapacityFraction() const;
    bool setInitialHeatRecoveryCoolingCapacityFraction(double initialHeatRecoveryCoolingCapacityFraction);

    double heatRecoveryCoolingCapacityTimeConstant() const;
    bool setHeatRecoveryCoolingCapacityTimeConstant(double heatRecoveryCoolingCapacityTimeConstant);

    double initialHeatRecoveryCoolingEnergyFraction() const;
    bool setInitialHeatRecoveryCoolingEnergyFraction(double initialHeatRecoveryCoolingEnergyFraction);

    double heatRecoveryCoolingEnergyTimeConstant() const;
    bool setHeatRecoveryCoolingEnergyTimeConstant(double heatRecoveryCoolingEnergyTimeConstant);

    double initialHeatRecoveryHeatingCapacityFraction() const;
    bool setInitialHeatRecoveryHeatingCapacityFraction(double initialHeatRecoveryHeatingCapacityFraction);

    double heatRecoveryHeatingCapacityTimeConstant() const;
    bool setHeatRecoveryHeatingCapacityTimeConstant(double heatRecoveryHeatingCapacityTimeConstant);

    double initialHeatRecoveryHeatingEnergyFraction() const;
    bool setInitialHeatRecoveryHeatingEnergyFraction(double initialHeatRecoveryHeatingEnergyFraction);

    double heatRecoveryHeatingEnergyTimeConstant() const;
    bool setHeatRecoveryHeatingEnergyTimeConstant(double heatRecoveryHeatingEnergyTimeConstant);

    double compressorMaximumDeltaPressure() const;
    bool setCompressorMaximumDeltaPressure(double compressorMaximumDeltaPressure);

    double compressorInverterEfficiency() const;
    bool setCompressorInverterEfficiency(double compressorInverterEfficiency);

    double compressorEvaporativeCapacityCorrectionFactor() const;
    bool setCompressorEvaporativeCapacityCorrectionFactor(double compressorEvaporativeCapacityCorrectionFactor);

   protected:
    using ImplType = detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(
      std::shared_ptr<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
