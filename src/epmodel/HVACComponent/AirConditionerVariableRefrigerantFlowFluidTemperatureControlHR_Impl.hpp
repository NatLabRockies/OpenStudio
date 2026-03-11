/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROLHR_IMPL_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOWFLUIDTEMPERATURECONTROLHR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl() override = default;

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

  std::vector<std::string> refrigerantTypeValues() const;
  std::vector<std::string> refrigerantTemperatureControlAlgorithmforIndoorUnitValues() const;
  std::vector<std::string> defrostStrategyValues() const;
  std::vector<std::string> defrostControlValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
