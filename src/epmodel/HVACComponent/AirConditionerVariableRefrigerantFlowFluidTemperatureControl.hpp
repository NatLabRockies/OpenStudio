/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

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
    class AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlowFluidTemperatureControl : public HVACComponent
  {
   public:
    explicit AirConditionerVariableRefrigerantFlowFluidTemperatureControl(const Model& model);

    virtual ~AirConditionerVariableRefrigerantFlowFluidTemperatureControl() override = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControl(const AirConditionerVariableRefrigerantFlowFluidTemperatureControl& other) = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControl(AirConditionerVariableRefrigerantFlowFluidTemperatureControl&& other) = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControl&
      operator=(const AirConditionerVariableRefrigerantFlowFluidTemperatureControl&) = default;
    AirConditionerVariableRefrigerantFlowFluidTemperatureControl& operator=(AirConditionerVariableRefrigerantFlowFluidTemperatureControl&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> refrigerantTypeValues();
    static std::vector<std::string> refrigerantTemperatureControlAlgorithmforIndoorUnitValues();
    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> defrostControlValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The long scalar VRF surface, terminal ownership, outdoor-unit curves, and constructor-default compressor loading
    //   rows are aligned.
    // - Canonical Counterpart: openstudio::model::AirConditionerVariableRefrigerantFlowFluidTemperatureControl.
    // - Implemented Parity: The preserved scalar API surface mirrors the canonical VRF cooling/heating, refrigerant, defrost, pipe, and heat-recovery fields exposed in the model type. The constructor and refrigerant setter ensure one shared built-in property dataset through `Model`.
    // - Documented Delta: Loading indexes are stored directly as EnergyPlus extensible rows rather than transient Model `LoadingIndex` objects.
    // - Field/Storage Mapping: Scalars and the three public outdoor-unit curve relationships map directly to EnergyPlus
    //   `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl` storage; the constructor creates three loading rows referencing six
    //   `Curve:Biquadratic` objects. Refrigerant tables remain model-owned EnergyPlus objects and survive consumer removal.
    // - Evidence: `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp`, `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlowFluidTemperatureControl.cpp`, `src/epmodel/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_GTest.cpp`, and `src/model/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_GTest.cpp`.
    // - Remaining Parity Work: Add a Model-shaped public loading-index API and autosized-result conveniences.

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

    double minimumOutdoorAirTemperatureinCoolingMode() const;
    bool setMinimumOutdoorAirTemperatureinCoolingMode(double minimumOutdoorAirTemperatureinCoolingMode);

    double maximumOutdoorAirTemperatureinCoolingMode() const;
    bool setMaximumOutdoorAirTemperatureinCoolingMode(double maximumOutdoorAirTemperatureinCoolingMode);

    double minimumOutdoorAirTemperatureinHeatingMode() const;
    bool setMinimumOutdoorAirTemperatureinHeatingMode(double minimumOutdoorAirTemperatureinHeatingMode);

    double maximumOutdoorAirTemperatureinHeatingMode() const;
    bool setMaximumOutdoorAirTemperatureinHeatingMode(double maximumOutdoorAirTemperatureinHeatingMode);

    double referenceOutdoorUnitSuperheating() const;
    bool setReferenceOutdoorUnitSuperheating(double referenceOutdoorUnitSuperheating);

    double referenceOutdoorUnitSubcooling() const;
    bool setReferenceOutdoorUnitSubcooling(double referenceOutdoorUnitSubcooling);

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

    double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity() const;
    bool setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity);

    double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity() const;
    bool setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity);

    Curve outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve() const;
    bool setOutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(const Curve& curve);

    Curve outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const;
    bool setOutdoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve);

    double diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const;
    bool setDiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(double diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);

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

    double compressorMaximumDeltaPressure() const;
    bool setCompressorMaximumDeltaPressure(double compressorMaximumDeltaPressure);

   protected:
    using ImplType = detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirConditionerVariableRefrigerantFlowFluidTemperatureControl(
      std::shared_ptr<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
