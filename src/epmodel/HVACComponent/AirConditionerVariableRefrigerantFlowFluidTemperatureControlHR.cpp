/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(const Model& model)
    : ModelObject(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::iddObjectType(), model) {}

  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(
    std::shared_ptr<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::iddObjectType() {
    return IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR;
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RefrigerantType);
  }

  std::vector<std::string>
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTemperatureControlAlgorithmforIndoorUnitValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit);
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostStrategy);
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostControl);
  }

  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantType() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->refrigerantType();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setRefrigerantType(const std::string& value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setRefrigerantType(value);
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::ratedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->ratedEvaporativeCapacity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::isRatedEvaporativeCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->isRatedEvaporativeCapacityAutosized();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setRatedEvaporativeCapacity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setRatedEvaporativeCapacity(value);
  }
  void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::autosizeRatedEvaporativeCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->autosizeRatedEvaporativeCapacity();
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::ratedCompressorPowerPerUnitofRatedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->ratedCompressorPowerPerUnitofRatedEvaporativeCapacity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::minimumOutdoorAirTemperatureinCoolingOnlyMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->minimumOutdoorAirTemperatureinCoolingOnlyMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMinimumOutdoorAirTemperatureinCoolingOnlyMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMinimumOutdoorAirTemperatureinCoolingOnlyMode(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::maximumOutdoorAirTemperatureinCoolingOnlyMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->maximumOutdoorAirTemperatureinCoolingOnlyMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMaximumOutdoorAirTemperatureinCoolingOnlyMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMaximumOutdoorAirTemperatureinCoolingOnlyMode(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::minimumOutdoorAirTemperatureinHeatingOnlyMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->minimumOutdoorAirTemperatureinHeatingOnlyMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMinimumOutdoorAirTemperatureinHeatingOnlyMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMinimumOutdoorAirTemperatureinHeatingOnlyMode(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::maximumOutdoorAirTemperatureinHeatingOnlyMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->maximumOutdoorAirTemperatureinHeatingOnlyMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMaximumOutdoorAirTemperatureinHeatingOnlyMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMaximumOutdoorAirTemperatureinHeatingOnlyMode(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::minimumOutdoorTemperatureinHeatRecoveryMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->minimumOutdoorTemperatureinHeatRecoveryMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMinimumOutdoorTemperatureinHeatRecoveryMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMinimumOutdoorTemperatureinHeatRecoveryMode(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::maximumOutdoorTemperatureinHeatRecoveryMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->maximumOutdoorTemperatureinHeatRecoveryMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMaximumOutdoorTemperatureinHeatRecoveryMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMaximumOutdoorTemperatureinHeatRecoveryMode(
      value);
  }
  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTemperatureControlAlgorithmforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->refrigerantTemperatureControlAlgorithmforIndoorUnit();
  }
  bool
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setRefrigerantTemperatureControlAlgorithmforIndoorUnit(const std::string& value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setRefrigerantTemperatureControlAlgorithmforIndoorUnit(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::referenceEvaporatingTemperatureforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->referenceEvaporatingTemperatureforIndoorUnit();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setReferenceEvaporatingTemperatureforIndoorUnit(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setReferenceEvaporatingTemperatureforIndoorUnit(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::referenceCondensingTemperatureforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->referenceCondensingTemperatureforIndoorUnit();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setReferenceCondensingTemperatureforIndoorUnit(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setReferenceCondensingTemperatureforIndoorUnit(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::variableEvaporatingTemperatureMinimumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->variableEvaporatingTemperatureMinimumforIndoorUnit();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setVariableEvaporatingTemperatureMinimumforIndoorUnit(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setVariableEvaporatingTemperatureMinimumforIndoorUnit(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::variableEvaporatingTemperatureMaximumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->variableEvaporatingTemperatureMaximumforIndoorUnit();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setVariableEvaporatingTemperatureMaximumforIndoorUnit(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setVariableEvaporatingTemperatureMaximumforIndoorUnit(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::variableCondensingTemperatureMinimumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->variableCondensingTemperatureMinimumforIndoorUnit();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setVariableCondensingTemperatureMinimumforIndoorUnit(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setVariableCondensingTemperatureMinimumforIndoorUnit(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::variableCondensingTemperatureMaximumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->variableCondensingTemperatureMaximumforIndoorUnit();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setVariableCondensingTemperatureMaximumforIndoorUnit(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setVariableCondensingTemperatureMaximumforIndoorUnit(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitEvaporatorReferenceSuperheating() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->outdoorUnitEvaporatorReferenceSuperheating();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitEvaporatorReferenceSuperheating(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setOutdoorUnitEvaporatorReferenceSuperheating(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitCondenserReferenceSubcooling() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->outdoorUnitCondenserReferenceSubcooling();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitCondenserReferenceSubcooling(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setOutdoorUnitCondenserReferenceSubcooling(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitEvaporatorRatedBypassFactor() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->outdoorUnitEvaporatorRatedBypassFactor();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitEvaporatorRatedBypassFactor(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setOutdoorUnitEvaporatorRatedBypassFactor(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitCondenserRatedBypassFactor() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->outdoorUnitCondenserRatedBypassFactor();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitCondenserRatedBypassFactor(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setOutdoorUnitCondenserRatedBypassFactor(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::
    differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::
    setDifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setDifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitHeatExchangerCapacityRatio() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->outdoorUnitHeatExchangerCapacityRatio();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitHeatExchangerCapacityRatio(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setOutdoorUnitHeatExchangerCapacityRatio(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::diameterofMainPipeforSuctionGas() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->diameterofMainPipeforSuctionGas();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setDiameterofMainPipeforSuctionGas(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setDiameterofMainPipeforSuctionGas(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::diameterofMainPipeforDischargeGas() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->diameterofMainPipeforDischargeGas();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setDiameterofMainPipeforDischargeGas(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setDiameterofMainPipeforDischargeGas(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(value);
  }
  double
    AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
    double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::heightDifferenceBetweenOutdoorUnitandIndoorUnits() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->heightDifferenceBetweenOutdoorUnitandIndoorUnits();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::mainPipeInsulationThickness() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->mainPipeInsulationThickness();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMainPipeInsulationThickness(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMainPipeInsulationThickness(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::mainPipeInsulationThermalConductivity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->mainPipeInsulationThermalConductivity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMainPipeInsulationThermalConductivity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setMainPipeInsulationThermalConductivity(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::crankcaseHeaterPowerperCompressor() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->crankcaseHeaterPowerperCompressor();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setCrankcaseHeaterPowerperCompressor(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setCrankcaseHeaterPowerperCompressor(value);
  }
  int AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::numberofCompressors() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->numberofCompressors();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setNumberofCompressors(int value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setNumberofCompressors(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::ratioofCompressorSizetoTotalCompressorCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->ratioofCompressorSizetoTotalCompressorCapacity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setRatioofCompressorSizetoTotalCompressorCapacity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setRatioofCompressorSizetoTotalCompressorCapacity(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::maximumOutdoorDryBulbTemperatureforCrankcaseHeater() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->maximumOutdoorDryBulbTemperatureforCrankcaseHeater();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(value);
  }
  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostStrategy() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->defrostStrategy();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setDefrostStrategy(const std::string& value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setDefrostStrategy(value);
  }
  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostControl() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->defrostControl();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setDefrostControl(const std::string& value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setDefrostControl(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostTimePeriodFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->defrostTimePeriodFraction();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setDefrostTimePeriodFraction(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setDefrostTimePeriodFraction(value);
  }
  boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::resistiveDefrostHeaterCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->resistiveDefrostHeaterCapacity();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::isResistiveDefrostHeaterCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->isResistiveDefrostHeaterCapacityAutosized();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setResistiveDefrostHeaterCapacity(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setResistiveDefrostHeaterCapacity(value);
  }
  void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::autosizeResistiveDefrostHeaterCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->autosizeResistiveDefrostHeaterCapacity();
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::maximumOutdoorDrybulbTemperatureforDefrostOperation() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->maximumOutdoorDrybulbTemperatureforDefrostOperation();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()
      ->setMaximumOutdoorDrybulbTemperatureforDefrostOperation(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::initialHeatRecoveryCoolingCapacityFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->initialHeatRecoveryCoolingCapacityFraction();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setInitialHeatRecoveryCoolingCapacityFraction(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setInitialHeatRecoveryCoolingCapacityFraction(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::heatRecoveryCoolingCapacityTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->heatRecoveryCoolingCapacityTimeConstant();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setHeatRecoveryCoolingCapacityTimeConstant(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setHeatRecoveryCoolingCapacityTimeConstant(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::initialHeatRecoveryCoolingEnergyFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->initialHeatRecoveryCoolingEnergyFraction();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setInitialHeatRecoveryCoolingEnergyFraction(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setInitialHeatRecoveryCoolingEnergyFraction(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::heatRecoveryCoolingEnergyTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->heatRecoveryCoolingEnergyTimeConstant();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setHeatRecoveryCoolingEnergyTimeConstant(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setHeatRecoveryCoolingEnergyTimeConstant(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::initialHeatRecoveryHeatingCapacityFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->initialHeatRecoveryHeatingCapacityFraction();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setInitialHeatRecoveryHeatingCapacityFraction(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setInitialHeatRecoveryHeatingCapacityFraction(
      value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::heatRecoveryHeatingCapacityTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->heatRecoveryHeatingCapacityTimeConstant();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setHeatRecoveryHeatingCapacityTimeConstant(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setHeatRecoveryHeatingCapacityTimeConstant(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::initialHeatRecoveryHeatingEnergyFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->initialHeatRecoveryHeatingEnergyFraction();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setInitialHeatRecoveryHeatingEnergyFraction(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setInitialHeatRecoveryHeatingEnergyFraction(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::heatRecoveryHeatingEnergyTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->heatRecoveryHeatingEnergyTimeConstant();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setHeatRecoveryHeatingEnergyTimeConstant(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setHeatRecoveryHeatingEnergyTimeConstant(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::compressorMaximumDeltaPressure() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->compressorMaximumDeltaPressure();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setCompressorMaximumDeltaPressure(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setCompressorMaximumDeltaPressure(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::compressorInverterEfficiency() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->compressorInverterEfficiency();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setCompressorInverterEfficiency(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setCompressorInverterEfficiency(value);
  }
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::compressorEvaporativeCapacityCorrectionFactor() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->compressorEvaporativeCapacityCorrectionFactor();
  }
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::setCompressorEvaporativeCapacityCorrectionFactor(double value) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->setCompressorEvaporativeCapacityCorrectionFactor(
      value);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

#define REQUIRED_STRING_GETTER(Method, Field)                                                                                       \
  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                                 \
    const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true); \
    OS_ASSERT(value);                                                                                                               \
    return *value;                                                                                                                  \
  }

#define REQUIRED_DOUBLE_GETTER(Method, Field)                                                                                       \
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                                      \
    const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true); \
    OS_ASSERT(value);                                                                                                               \
    return *value;                                                                                                                  \
  }

#define REQUIRED_INT_GETTER(Method, Field)                                                                                       \
  int AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                                      \
    const auto value = getInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true); \
    OS_ASSERT(value);                                                                                                            \
    return *value;                                                                                                               \
  }

#define OPTIONAL_DOUBLE_GETTER(Method, Field)                                                                           \
  boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {         \
    return getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true); \
  }

#define STRING_SETTER(Method, Field)                                                                                     \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method(const std::string& value) {           \
    return setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, value); \
  }

#define DOUBLE_SETTER(Method, Field)                                                                                     \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method(double value) {                       \
    return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, value); \
  }

#define INT_SETTER(Method, Field)                                                                                     \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method(int value) {                       \
    return setInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, value); \
  }

    REQUIRED_STRING_GETTER(refrigerantType, RefrigerantType)
    STRING_SETTER(setRefrigerantType, RefrigerantType)

    OPTIONAL_DOUBLE_GETTER(ratedEvaporativeCapacity, RatedEvaporativeCapacity)
    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::isRatedEvaporativeCapacityAutosized() const {
      if (auto value =
            getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatedEvaporativeCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }
    DOUBLE_SETTER(setRatedEvaporativeCapacity, RatedEvaporativeCapacity)
    void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::autosizeRatedEvaporativeCapacity() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatedEvaporativeCapacity, "autosize"));
    }

    REQUIRED_DOUBLE_GETTER(ratedCompressorPowerPerUnitofRatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity)
    DOUBLE_SETTER(setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity)
    REQUIRED_DOUBLE_GETTER(minimumOutdoorAirTemperatureinCoolingOnlyMode, MinimumOutdoorAirTemperatureinCoolingOnlyMode)
    DOUBLE_SETTER(setMinimumOutdoorAirTemperatureinCoolingOnlyMode, MinimumOutdoorAirTemperatureinCoolingOnlyMode)
    REQUIRED_DOUBLE_GETTER(maximumOutdoorAirTemperatureinCoolingOnlyMode, MaximumOutdoorAirTemperatureinCoolingOnlyMode)
    DOUBLE_SETTER(setMaximumOutdoorAirTemperatureinCoolingOnlyMode, MaximumOutdoorAirTemperatureinCoolingOnlyMode)
    REQUIRED_DOUBLE_GETTER(minimumOutdoorAirTemperatureinHeatingOnlyMode, MinimumOutdoorAirTemperatureinHeatingOnlyMode)
    DOUBLE_SETTER(setMinimumOutdoorAirTemperatureinHeatingOnlyMode, MinimumOutdoorAirTemperatureinHeatingOnlyMode)
    REQUIRED_DOUBLE_GETTER(maximumOutdoorAirTemperatureinHeatingOnlyMode, MaximumOutdoorAirTemperatureinHeatingOnlyMode)
    DOUBLE_SETTER(setMaximumOutdoorAirTemperatureinHeatingOnlyMode, MaximumOutdoorAirTemperatureinHeatingOnlyMode)
    REQUIRED_DOUBLE_GETTER(minimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
    DOUBLE_SETTER(setMinimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
    REQUIRED_DOUBLE_GETTER(maximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)
    DOUBLE_SETTER(setMaximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)
    REQUIRED_STRING_GETTER(refrigerantTemperatureControlAlgorithmforIndoorUnit, RefrigerantTemperatureControlAlgorithmforIndoorUnit)
    STRING_SETTER(setRefrigerantTemperatureControlAlgorithmforIndoorUnit, RefrigerantTemperatureControlAlgorithmforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(referenceEvaporatingTemperatureforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit)
    DOUBLE_SETTER(setReferenceEvaporatingTemperatureforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(referenceCondensingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit)
    DOUBLE_SETTER(setReferenceCondensingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(variableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit)
    DOUBLE_SETTER(setVariableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(variableEvaporatingTemperatureMaximumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit)
    DOUBLE_SETTER(setVariableEvaporatingTemperatureMaximumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(variableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit)
    DOUBLE_SETTER(setVariableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(variableCondensingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit)
    DOUBLE_SETTER(setVariableCondensingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit)
    REQUIRED_DOUBLE_GETTER(outdoorUnitEvaporatorReferenceSuperheating, OutdoorUnitEvaporatorReferenceSuperheating)
    DOUBLE_SETTER(setOutdoorUnitEvaporatorReferenceSuperheating, OutdoorUnitEvaporatorReferenceSuperheating)
    REQUIRED_DOUBLE_GETTER(outdoorUnitCondenserReferenceSubcooling, OutdoorUnitCondenserReferenceSubcooling)
    DOUBLE_SETTER(setOutdoorUnitCondenserReferenceSubcooling, OutdoorUnitCondenserReferenceSubcooling)
    REQUIRED_DOUBLE_GETTER(outdoorUnitEvaporatorRatedBypassFactor, OutdoorUnitEvaporatorRatedBypassFactor)
    DOUBLE_SETTER(setOutdoorUnitEvaporatorRatedBypassFactor, OutdoorUnitEvaporatorRatedBypassFactor)
    REQUIRED_DOUBLE_GETTER(outdoorUnitCondenserRatedBypassFactor, OutdoorUnitCondenserRatedBypassFactor)
    DOUBLE_SETTER(setOutdoorUnitCondenserRatedBypassFactor, OutdoorUnitCondenserRatedBypassFactor)
    REQUIRED_DOUBLE_GETTER(differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode,
                           DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode)
    DOUBLE_SETTER(setDifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode,
                  DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode)
    REQUIRED_DOUBLE_GETTER(outdoorUnitHeatExchangerCapacityRatio, OutdoorUnitHeatExchangerCapacityRatio)
    DOUBLE_SETTER(setOutdoorUnitHeatExchangerCapacityRatio, OutdoorUnitHeatExchangerCapacityRatio)
    REQUIRED_DOUBLE_GETTER(outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity)
    DOUBLE_SETTER(setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity)
    REQUIRED_DOUBLE_GETTER(outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity)
    DOUBLE_SETTER(setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity)
    REQUIRED_DOUBLE_GETTER(diameterofMainPipeforSuctionGas, DiameterofMainPipeforSuctionGas)
    DOUBLE_SETTER(setDiameterofMainPipeforSuctionGas, DiameterofMainPipeforSuctionGas)
    REQUIRED_DOUBLE_GETTER(diameterofMainPipeforDischargeGas, DiameterofMainPipeforDischargeGas)
    DOUBLE_SETTER(setDiameterofMainPipeforDischargeGas, DiameterofMainPipeforDischargeGas)
    REQUIRED_DOUBLE_GETTER(lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
    DOUBLE_SETTER(setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
    REQUIRED_DOUBLE_GETTER(equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                           EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
    DOUBLE_SETTER(setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                  EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
    REQUIRED_DOUBLE_GETTER(heightDifferenceBetweenOutdoorUnitandIndoorUnits, HeightDifferenceBetweenOutdoorUnitandIndoorUnits)
    DOUBLE_SETTER(setHeightDifferenceBetweenOutdoorUnitandIndoorUnits, HeightDifferenceBetweenOutdoorUnitandIndoorUnits)
    REQUIRED_DOUBLE_GETTER(mainPipeInsulationThickness, MainPipeInsulationThickness)
    DOUBLE_SETTER(setMainPipeInsulationThickness, MainPipeInsulationThickness)
    REQUIRED_DOUBLE_GETTER(mainPipeInsulationThermalConductivity, MainPipeInsulationThermalConductivity)
    DOUBLE_SETTER(setMainPipeInsulationThermalConductivity, MainPipeInsulationThermalConductivity)
    REQUIRED_DOUBLE_GETTER(crankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
    DOUBLE_SETTER(setCrankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
    REQUIRED_INT_GETTER(numberofCompressors, NumberofCompressors)
    INT_SETTER(setNumberofCompressors, NumberofCompressors)
    REQUIRED_DOUBLE_GETTER(ratioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
    DOUBLE_SETTER(setRatioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
    REQUIRED_DOUBLE_GETTER(maximumOutdoorDryBulbTemperatureforCrankcaseHeater, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater)
    DOUBLE_SETTER(setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater)
    REQUIRED_STRING_GETTER(defrostStrategy, DefrostStrategy)
    STRING_SETTER(setDefrostStrategy, DefrostStrategy)
    REQUIRED_STRING_GETTER(defrostControl, DefrostControl)
    STRING_SETTER(setDefrostControl, DefrostControl)
    REQUIRED_DOUBLE_GETTER(defrostTimePeriodFraction, DefrostTimePeriodFraction)
    DOUBLE_SETTER(setDefrostTimePeriodFraction, DefrostTimePeriodFraction)
    OPTIONAL_DOUBLE_GETTER(resistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
      if (auto value =
            getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ResistiveDefrostHeaterCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }
    DOUBLE_SETTER(setResistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
    void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::autosizeResistiveDefrostHeaterCapacity() {
      OS_ASSERT(
        setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ResistiveDefrostHeaterCapacity, "autosize"));
    }
    REQUIRED_DOUBLE_GETTER(maximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
    DOUBLE_SETTER(setMaximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
    REQUIRED_DOUBLE_GETTER(initialHeatRecoveryCoolingCapacityFraction, InitialHeatRecoveryCoolingCapacityFraction)
    DOUBLE_SETTER(setInitialHeatRecoveryCoolingCapacityFraction, InitialHeatRecoveryCoolingCapacityFraction)
    REQUIRED_DOUBLE_GETTER(heatRecoveryCoolingCapacityTimeConstant, HeatRecoveryCoolingCapacityTimeConstant)
    DOUBLE_SETTER(setHeatRecoveryCoolingCapacityTimeConstant, HeatRecoveryCoolingCapacityTimeConstant)
    REQUIRED_DOUBLE_GETTER(initialHeatRecoveryCoolingEnergyFraction, InitialHeatRecoveryCoolingEnergyFraction)
    DOUBLE_SETTER(setInitialHeatRecoveryCoolingEnergyFraction, InitialHeatRecoveryCoolingEnergyFraction)
    REQUIRED_DOUBLE_GETTER(heatRecoveryCoolingEnergyTimeConstant, HeatRecoveryCoolingEnergyTimeConstant)
    DOUBLE_SETTER(setHeatRecoveryCoolingEnergyTimeConstant, HeatRecoveryCoolingEnergyTimeConstant)
    REQUIRED_DOUBLE_GETTER(initialHeatRecoveryHeatingCapacityFraction, InitialHeatRecoveryHeatingCapacityFraction)
    DOUBLE_SETTER(setInitialHeatRecoveryHeatingCapacityFraction, InitialHeatRecoveryHeatingCapacityFraction)
    REQUIRED_DOUBLE_GETTER(heatRecoveryHeatingCapacityTimeConstant, HeatRecoveryHeatingCapacityTimeConstant)
    DOUBLE_SETTER(setHeatRecoveryHeatingCapacityTimeConstant, HeatRecoveryHeatingCapacityTimeConstant)
    REQUIRED_DOUBLE_GETTER(initialHeatRecoveryHeatingEnergyFraction, InitialHeatRecoveryHeatingEnergyFraction)
    DOUBLE_SETTER(setInitialHeatRecoveryHeatingEnergyFraction, InitialHeatRecoveryHeatingEnergyFraction)
    REQUIRED_DOUBLE_GETTER(heatRecoveryHeatingEnergyTimeConstant, HeatRecoveryHeatingEnergyTimeConstant)
    DOUBLE_SETTER(setHeatRecoveryHeatingEnergyTimeConstant, HeatRecoveryHeatingEnergyTimeConstant)

    // Field-enum spelling drift: use E+ enum token CompressormaximumdeltaPressure while preserving API name.
    REQUIRED_DOUBLE_GETTER(compressorMaximumDeltaPressure, CompressormaximumdeltaPressure)
    DOUBLE_SETTER(setCompressorMaximumDeltaPressure, CompressormaximumdeltaPressure)
    REQUIRED_DOUBLE_GETTER(compressorInverterEfficiency, CompressorInverterEfficiency)
    DOUBLE_SETTER(setCompressorInverterEfficiency, CompressorInverterEfficiency)
    REQUIRED_DOUBLE_GETTER(compressorEvaporativeCapacityCorrectionFactor, CompressorEvaporativeCapacityCorrectionFactor)
    DOUBLE_SETTER(setCompressorEvaporativeCapacityCorrectionFactor, CompressorEvaporativeCapacityCorrectionFactor)

#undef REQUIRED_STRING_GETTER
#undef REQUIRED_DOUBLE_GETTER
#undef REQUIRED_INT_GETTER
#undef OPTIONAL_DOUBLE_GETTER
#undef STRING_SETTER
#undef DOUBLE_SETTER
#undef INT_SETTER

    std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::refrigerantTypeValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTypeValues();
    }

    std::vector<std::string>
      AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::refrigerantTemperatureControlAlgorithmforIndoorUnitValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::
        refrigerantTemperatureControlAlgorithmforIndoorUnitValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::defrostStrategyValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostStrategyValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::defrostControlValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostControlValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
