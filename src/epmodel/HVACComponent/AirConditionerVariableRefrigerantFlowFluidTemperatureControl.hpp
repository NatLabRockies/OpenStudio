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
    // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: Preserved scalar APIs map directly to matching E+ AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl fields.
    // - Field Mapping: Relationship-like fields (schedule/curves/lists/nodes) are intentionally excluded in this scalar scaffold phase.
    // - TODO(parity): Add non-scalar relationship API parity incrementally after scalar saturation.

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
