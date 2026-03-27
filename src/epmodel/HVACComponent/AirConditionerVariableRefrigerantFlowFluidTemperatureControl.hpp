/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlowFluidTemperatureControl : public ModelObject
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
    // - Status: Scalar Parity. The long scalar VRF surface is aligned, while terminal, loading-index, and other relationship APIs are still omitted.
    // - Canonical Counterpart: openstudio::model::AirConditionerVariableRefrigerantFlowFluidTemperatureControl.
    // - Implemented Parity: The preserved scalar API surface mirrors the canonical VRF cooling/heating, refrigerant, defrost, pipe, and heat-recovery fields exposed in the model type.
    // - Documented Delta: epmodel currently models this object as a `ModelObject` wrapper and does not expose terminal, loading-index, or curve/list relationship APIs yet.
    // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl` storage.
    // - Evidence: `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp`, `src/model/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlowFluidTemperatureControl.cpp`, `src/epmodel/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_GTest.cpp`, and `src/model/test/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted terminal, loading-index, and curve/list relationship APIs after the relationship layer is available.

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
