/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROLHR_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROLHR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR : public ModelObject
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
    // - Status: Scalar Parity. The long scalar VRF heat-recovery surface is aligned, while terminal, loading-index, and other relationship APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.
    // - Implemented Parity: The preserved scalar API surface mirrors the canonical heat-recovery, refrigerant, defrost, pipe, and compressor-field contract exposed in the model type.
    // - Documented Delta: epmodel currently models this object as a `ModelObject` wrapper and does not expose terminal, loading-index, or curve/list relationship APIs yet.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR` storage.
    // - Evidence: `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp`, `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.cpp`, `src/epmodel/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_GTest.cpp`, and `src/model/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted terminal, loading-index, and curve/list relationship APIs after the relationship layer is available.
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
