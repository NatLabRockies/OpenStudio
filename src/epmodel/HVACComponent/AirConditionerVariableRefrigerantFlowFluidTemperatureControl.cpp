/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirConditionerVariableRefrigerantFlowFluidTemperatureControl::AirConditionerVariableRefrigerantFlowFluidTemperatureControl(const Model& model)
    : ModelObject(AirConditionerVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), model) {}

  AirConditionerVariableRefrigerantFlowFluidTemperatureControl::AirConditionerVariableRefrigerantFlowFluidTemperatureControl(
    std::shared_ptr<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirConditionerVariableRefrigerantFlowFluidTemperatureControl::iddObjectType() {
    return IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl;
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::refrigerantTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantType);
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::refrigerantTemperatureControlAlgorithmforIndoorUnitValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit);
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostStrategy);
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostControl);
  }

  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl::refrigerantType() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->refrigerantType();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setRefrigerantType(const std::string& refrigerantType) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRefrigerantType(refrigerantType);
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::ratedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->ratedEvaporativeCapacity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::isRatedEvaporativeCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->isRatedEvaporativeCapacityAutosized();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setRatedEvaporativeCapacity(double ratedEvaporativeCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRatedEvaporativeCapacity(
      ratedEvaporativeCapacity);
  }

  void AirConditionerVariableRefrigerantFlowFluidTemperatureControl::autosizeRatedEvaporativeCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->autosizeRatedEvaporativeCapacity();
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::ratedCompressorPowerPerUnitofRatedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->ratedCompressorPowerPerUnitofRatedEvaporativeCapacity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(
    double ratedCompressorPowerPerUnitofRatedEvaporativeCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(ratedCompressorPowerPerUnitofRatedEvaporativeCapacity);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::minimumOutdoorAirTemperatureinCoolingMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->minimumOutdoorAirTemperatureinCoolingMode();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMinimumOutdoorAirTemperatureinCoolingMode(
    double minimumOutdoorAirTemperatureinCoolingMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setMinimumOutdoorAirTemperatureinCoolingMode(
      minimumOutdoorAirTemperatureinCoolingMode);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::maximumOutdoorAirTemperatureinCoolingMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->maximumOutdoorAirTemperatureinCoolingMode();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMaximumOutdoorAirTemperatureinCoolingMode(
    double maximumOutdoorAirTemperatureinCoolingMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setMaximumOutdoorAirTemperatureinCoolingMode(
      maximumOutdoorAirTemperatureinCoolingMode);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::minimumOutdoorAirTemperatureinHeatingMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->minimumOutdoorAirTemperatureinHeatingMode();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMinimumOutdoorAirTemperatureinHeatingMode(
    double minimumOutdoorAirTemperatureinHeatingMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setMinimumOutdoorAirTemperatureinHeatingMode(
      minimumOutdoorAirTemperatureinHeatingMode);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::maximumOutdoorAirTemperatureinHeatingMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->maximumOutdoorAirTemperatureinHeatingMode();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMaximumOutdoorAirTemperatureinHeatingMode(
    double maximumOutdoorAirTemperatureinHeatingMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setMaximumOutdoorAirTemperatureinHeatingMode(
      maximumOutdoorAirTemperatureinHeatingMode);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::referenceOutdoorUnitSuperheating() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->referenceOutdoorUnitSuperheating();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setReferenceOutdoorUnitSuperheating(double referenceOutdoorUnitSuperheating) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setReferenceOutdoorUnitSuperheating(
      referenceOutdoorUnitSuperheating);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::referenceOutdoorUnitSubcooling() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->referenceOutdoorUnitSubcooling();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setReferenceOutdoorUnitSubcooling(double referenceOutdoorUnitSubcooling) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setReferenceOutdoorUnitSubcooling(
      referenceOutdoorUnitSubcooling);
  }

  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl::refrigerantTemperatureControlAlgorithmforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->refrigerantTemperatureControlAlgorithmforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setRefrigerantTemperatureControlAlgorithmforIndoorUnit(
    const std::string& refrigerantTemperatureControlAlgorithmforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setRefrigerantTemperatureControlAlgorithmforIndoorUnit(refrigerantTemperatureControlAlgorithmforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::referenceEvaporatingTemperatureforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->referenceEvaporatingTemperatureforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setReferenceEvaporatingTemperatureforIndoorUnit(
    double referenceEvaporatingTemperatureforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setReferenceEvaporatingTemperatureforIndoorUnit(
      referenceEvaporatingTemperatureforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::referenceCondensingTemperatureforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->referenceCondensingTemperatureforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setReferenceCondensingTemperatureforIndoorUnit(
    double referenceCondensingTemperatureforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setReferenceCondensingTemperatureforIndoorUnit(
      referenceCondensingTemperatureforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::variableEvaporatingTemperatureMinimumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->variableEvaporatingTemperatureMinimumforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setVariableEvaporatingTemperatureMinimumforIndoorUnit(
    double variableEvaporatingTemperatureMinimumforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setVariableEvaporatingTemperatureMinimumforIndoorUnit(variableEvaporatingTemperatureMinimumforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::variableEvaporatingTemperatureMaximumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->variableEvaporatingTemperatureMaximumforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setVariableEvaporatingTemperatureMaximumforIndoorUnit(
    double variableEvaporatingTemperatureMaximumforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setVariableEvaporatingTemperatureMaximumforIndoorUnit(variableEvaporatingTemperatureMaximumforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::variableCondensingTemperatureMinimumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->variableCondensingTemperatureMinimumforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setVariableCondensingTemperatureMinimumforIndoorUnit(
    double variableCondensingTemperatureMinimumforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setVariableCondensingTemperatureMinimumforIndoorUnit(
      variableCondensingTemperatureMinimumforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::variableCondensingTemperatureMaximumforIndoorUnit() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->variableCondensingTemperatureMaximumforIndoorUnit();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setVariableCondensingTemperatureMaximumforIndoorUnit(
    double variableCondensingTemperatureMaximumforIndoorUnit) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setVariableCondensingTemperatureMaximumforIndoorUnit(
      variableCondensingTemperatureMaximumforIndoorUnit);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(
    double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(
    double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setDiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
    double diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setDiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
    double lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
    double equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::heightDifferenceBetweenOutdoorUnitandIndoorUnits() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->heightDifferenceBetweenOutdoorUnitandIndoorUnits();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(
    double heightDifferenceBetweenOutdoorUnitandIndoorUnits) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(
      heightDifferenceBetweenOutdoorUnitandIndoorUnits);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::mainPipeInsulationThickness() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->mainPipeInsulationThickness();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMainPipeInsulationThickness(double mainPipeInsulationThickness) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setMainPipeInsulationThickness(
      mainPipeInsulationThickness);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::mainPipeInsulationThermalConductivity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->mainPipeInsulationThermalConductivity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMainPipeInsulationThermalConductivity(
    double mainPipeInsulationThermalConductivity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setMainPipeInsulationThermalConductivity(
      mainPipeInsulationThermalConductivity);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::crankcaseHeaterPowerperCompressor() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->crankcaseHeaterPowerperCompressor();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setCrankcaseHeaterPowerperCompressor(double crankcaseHeaterPowerperCompressor) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setCrankcaseHeaterPowerperCompressor(
      crankcaseHeaterPowerperCompressor);
  }

  int AirConditionerVariableRefrigerantFlowFluidTemperatureControl::numberofCompressors() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->numberofCompressors();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setNumberofCompressors(int numberofCompressors) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setNumberofCompressors(numberofCompressors);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::ratioofCompressorSizetoTotalCompressorCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->ratioofCompressorSizetoTotalCompressorCapacity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setRatioofCompressorSizetoTotalCompressorCapacity(
    double ratioofCompressorSizetoTotalCompressorCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRatioofCompressorSizetoTotalCompressorCapacity(
      ratioofCompressorSizetoTotalCompressorCapacity);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::maximumOutdoorDryBulbTemperatureforCrankcaseHeater() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeater();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(
    double maximumOutdoorDryBulbTemperatureforCrankcaseHeater) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(maximumOutdoorDryBulbTemperatureforCrankcaseHeater);
  }

  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostStrategy() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->defrostStrategy();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setDefrostStrategy(const std::string& defrostStrategy) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setDefrostStrategy(defrostStrategy);
  }

  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostControl() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->defrostControl();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setDefrostControl(const std::string& defrostControl) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setDefrostControl(defrostControl);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostTimePeriodFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->defrostTimePeriodFraction();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setDefrostTimePeriodFraction(
      defrostTimePeriodFraction);
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::resistiveDefrostHeaterCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->resistiveDefrostHeaterCapacity();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::isResistiveDefrostHeaterCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->isResistiveDefrostHeaterCapacityAutosized();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setResistiveDefrostHeaterCapacity(
      resistiveDefrostHeaterCapacity);
  }

  void AirConditionerVariableRefrigerantFlowFluidTemperatureControl::autosizeResistiveDefrostHeaterCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->autosizeResistiveDefrostHeaterCapacity();
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::maximumOutdoorDrybulbTemperatureforDefrostOperation() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->maximumOutdoorDrybulbTemperatureforDefrostOperation();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setMaximumOutdoorDrybulbTemperatureforDefrostOperation(
    double maximumOutdoorDrybulbTemperatureforDefrostOperation) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setMaximumOutdoorDrybulbTemperatureforDefrostOperation(maximumOutdoorDrybulbTemperatureforDefrostOperation);
  }

  double AirConditionerVariableRefrigerantFlowFluidTemperatureControl::compressorMaximumDeltaPressure() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->compressorMaximumDeltaPressure();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setCompressorMaximumDeltaPressure(double compressorMaximumDeltaPressure) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setCompressorMaximumDeltaPressure(
      compressorMaximumDeltaPressure);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::refrigerantType() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setRefrigerantType(const std::string& refrigerantType) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantType, refrigerantType);
    }

    boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::ratedEvaporativeCapacity() const {
      return getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedEvaporativeCapacity, true);
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::isRatedEvaporativeCapacityAutosized() const {
      if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedEvaporativeCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatedEvaporativeCapacity(double ratedEvaporativeCapacity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedEvaporativeCapacity,
                       ratedEvaporativeCapacity);
    }

    void AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::autosizeRatedEvaporativeCapacity() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedEvaporativeCapacity, "autosize"));
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::ratedCompressorPowerPerUnitofRatedEvaporativeCapacity() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedCompressorPowerPerUnitofRatedEvaporativeCapacity,
        true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(
      double ratedCompressorPowerPerUnitofRatedEvaporativeCapacity) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedCompressorPowerPerUnitofRatedEvaporativeCapacity,
        ratedCompressorPowerPerUnitofRatedEvaporativeCapacity);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::minimumOutdoorAirTemperatureinCoolingMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MinimumOutdoorAirTemperatureinCoolingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMinimumOutdoorAirTemperatureinCoolingMode(
      double minimumOutdoorAirTemperatureinCoolingMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MinimumOutdoorAirTemperatureinCoolingMode,
                       minimumOutdoorAirTemperatureinCoolingMode);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::maximumOutdoorAirTemperatureinCoolingMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorAirTemperatureinCoolingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMaximumOutdoorAirTemperatureinCoolingMode(
      double maximumOutdoorAirTemperatureinCoolingMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorAirTemperatureinCoolingMode,
                       maximumOutdoorAirTemperatureinCoolingMode);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::minimumOutdoorAirTemperatureinHeatingMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MinimumOutdoorAirTemperatureinHeatingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMinimumOutdoorAirTemperatureinHeatingMode(
      double minimumOutdoorAirTemperatureinHeatingMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MinimumOutdoorAirTemperatureinHeatingMode,
                       minimumOutdoorAirTemperatureinHeatingMode);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::maximumOutdoorAirTemperatureinHeatingMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorAirTemperatureinHeatingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMaximumOutdoorAirTemperatureinHeatingMode(
      double maximumOutdoorAirTemperatureinHeatingMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorAirTemperatureinHeatingMode,
                       maximumOutdoorAirTemperatureinHeatingMode);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::referenceOutdoorUnitSuperheating() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceOutdoorUnitSuperheating, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setReferenceOutdoorUnitSuperheating(
      double referenceOutdoorUnitSuperheating) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceOutdoorUnitSuperheating,
                       referenceOutdoorUnitSuperheating);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::referenceOutdoorUnitSubcooling() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceOutdoorUnitSubcooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setReferenceOutdoorUnitSubcooling(double referenceOutdoorUnitSubcooling) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceOutdoorUnitSubcooling,
                       referenceOutdoorUnitSubcooling);
    }

    std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::refrigerantTemperatureControlAlgorithmforIndoorUnit() const {
      const auto value = getString(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setRefrigerantTemperatureControlAlgorithmforIndoorUnit(
      const std::string& refrigerantTemperatureControlAlgorithmforIndoorUnit) {
      return setString(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit,
        refrigerantTemperatureControlAlgorithmforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::referenceEvaporatingTemperatureforIndoorUnit() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceEvaporatingTemperatureforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setReferenceEvaporatingTemperatureforIndoorUnit(
      double referenceEvaporatingTemperatureforIndoorUnit) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceEvaporatingTemperatureforIndoorUnit,
                       referenceEvaporatingTemperatureforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::referenceCondensingTemperatureforIndoorUnit() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceCondensingTemperatureforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setReferenceCondensingTemperatureforIndoorUnit(
      double referenceCondensingTemperatureforIndoorUnit) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceCondensingTemperatureforIndoorUnit,
                       referenceCondensingTemperatureforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::variableEvaporatingTemperatureMinimumforIndoorUnit() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableEvaporatingTemperatureMinimumforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setVariableEvaporatingTemperatureMinimumforIndoorUnit(
      double variableEvaporatingTemperatureMinimumforIndoorUnit) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableEvaporatingTemperatureMinimumforIndoorUnit,
        variableEvaporatingTemperatureMinimumforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::variableEvaporatingTemperatureMaximumforIndoorUnit() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableEvaporatingTemperatureMaximumforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setVariableEvaporatingTemperatureMaximumforIndoorUnit(
      double variableEvaporatingTemperatureMaximumforIndoorUnit) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableEvaporatingTemperatureMaximumforIndoorUnit,
        variableEvaporatingTemperatureMaximumforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::variableCondensingTemperatureMinimumforIndoorUnit() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableCondensingTemperatureMinimumforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setVariableCondensingTemperatureMinimumforIndoorUnit(
      double variableCondensingTemperatureMinimumforIndoorUnit) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableCondensingTemperatureMinimumforIndoorUnit,
        variableCondensingTemperatureMinimumforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::variableCondensingTemperatureMaximumforIndoorUnit() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableCondensingTemperatureMaximumforIndoorUnit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setVariableCondensingTemperatureMaximumforIndoorUnit(
      double variableCondensingTemperatureMaximumforIndoorUnit) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableCondensingTemperatureMaximumforIndoorUnit,
        variableCondensingTemperatureMaximumforIndoorUnit);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity(
      double outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity,
        outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity,
        true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity(
      double outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity,
        outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                                     DiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                                   true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setDiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
      double diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                         DiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                       diameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
        true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
      double lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
        lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint()
      const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                                     EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                                   true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint(
      double equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                         EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                       equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::heightDifferenceBetweenOutdoorUnitandIndoorUnits() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::HeightDifferenceBetweenOutdoorUnitandIndoorUnits, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setHeightDifferenceBetweenOutdoorUnitandIndoorUnits(
      double heightDifferenceBetweenOutdoorUnitandIndoorUnits) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::HeightDifferenceBetweenOutdoorUnitandIndoorUnits,
        heightDifferenceBetweenOutdoorUnitandIndoorUnits);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::mainPipeInsulationThickness() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MainPipeInsulationThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMainPipeInsulationThickness(double mainPipeInsulationThickness) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MainPipeInsulationThickness,
                       mainPipeInsulationThickness);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::mainPipeInsulationThermalConductivity() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MainPipeInsulationThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMainPipeInsulationThermalConductivity(
      double mainPipeInsulationThermalConductivity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MainPipeInsulationThermalConductivity,
                       mainPipeInsulationThermalConductivity);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::crankcaseHeaterPowerperCompressor() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CrankcaseHeaterPowerperCompressor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setCrankcaseHeaterPowerperCompressor(
      double crankcaseHeaterPowerperCompressor) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CrankcaseHeaterPowerperCompressor,
                       crankcaseHeaterPowerperCompressor);
    }

    int AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::numberofCompressors() const {
      const auto value = getInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::NumberofCompressors, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setNumberofCompressors(int numberofCompressors) {
      return setInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::NumberofCompressors, numberofCompressors);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::ratioofCompressorSizetoTotalCompressorCapacity() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatioofCompressorSizetoTotalCompressorCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatioofCompressorSizetoTotalCompressorCapacity(
      double ratioofCompressorSizetoTotalCompressorCapacity) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatioofCompressorSizetoTotalCompressorCapacity,
        ratioofCompressorSizetoTotalCompressorCapacity);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeater() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater(
      double maximumOutdoorDryBulbTemperatureforCrankcaseHeater) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeater,
        maximumOutdoorDryBulbTemperatureforCrankcaseHeater);
    }

    std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::defrostStrategy() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostStrategy, defrostStrategy);
    }

    std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::defrostControl() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setDefrostControl(const std::string& defrostControl) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostControl, defrostControl);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::defrostTimePeriodFraction() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostTimePeriodFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostTimePeriodFraction,
                       defrostTimePeriodFraction);
    }

    boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::resistiveDefrostHeaterCapacity() const {
      return getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ResistiveDefrostHeaterCapacity, true);
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
      if (auto value =
            getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ResistiveDefrostHeaterCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ResistiveDefrostHeaterCapacity,
                       resistiveDefrostHeaterCapacity);
    }

    void AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::autosizeResistiveDefrostHeaterCapacity() {
      OS_ASSERT(
        setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ResistiveDefrostHeaterCapacity, "autosize"));
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::maximumOutdoorDrybulbTemperatureforDefrostOperation() const {
      const auto value = getDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setMaximumOutdoorDrybulbTemperatureforDefrostOperation(
      double maximumOutdoorDrybulbTemperatureforDefrostOperation) {
      return setDouble(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation,
        maximumOutdoorDrybulbTemperatureforDefrostOperation);
    }

    double AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::compressorMaximumDeltaPressure() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressormaximumdeltaPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setCompressorMaximumDeltaPressure(double compressorMaximumDeltaPressure) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressormaximumdeltaPressure,
                       compressorMaximumDeltaPressure);
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::refrigerantTypeValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControl::refrigerantTypeValues();
    }

    std::vector<std::string>
      AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::refrigerantTemperatureControlAlgorithmforIndoorUnitValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControl::
        refrigerantTemperatureControlAlgorithmforIndoorUnitValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::defrostStrategyValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostStrategyValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::defrostControlValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControl::defrostControlValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
