/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <array>
#include <set>

namespace openstudio {
namespace epmodel {

  AirConditionerVariableRefrigerantFlowFluidTemperatureControl::AirConditionerVariableRefrigerantFlowFluidTemperatureControl(const Model& model)
    : HVACComponent(AirConditionerVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), model) {
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    auto impl = getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>();
    OS_ASSERT(impl->ensureTerminalUnitList());
    impl->createDefaultPerformance();
  }

  AirConditionerVariableRefrigerantFlowFluidTemperatureControl::AirConditionerVariableRefrigerantFlowFluidTemperatureControl(
    std::shared_ptr<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl> impl)
    : HVACComponent(std::move(impl)) {}

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

  Schedule AirConditionerVariableRefrigerantFlowFluidTemperatureControl::availabilitySchedule() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->availabilitySchedule();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setAvailabilitySchedule(schedule);
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->addTerminal(terminal);
  }

  void AirConditionerVariableRefrigerantFlowFluidTemperatureControl::removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
    getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->removeTerminal(terminal);
  }

  void AirConditionerVariableRefrigerantFlowFluidTemperatureControl::removeAllTerminals() {
    getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->removeAllTerminals();
  }

  std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> AirConditionerVariableRefrigerantFlowFluidTemperatureControl::terminals() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()->terminals();
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

  Curve AirConditionerVariableRefrigerantFlowFluidTemperatureControl::outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve();
  }

  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setOutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(
    const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setOutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(curve);
  }

  Curve AirConditionerVariableRefrigerantFlowFluidTemperatureControl::outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve();
  }

  bool
    AirConditionerVariableRefrigerantFlowFluidTemperatureControl::setOutdoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setOutdoorUnitCondensingTemperatureFunctionofSubcoolingCurve(curve);
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

    void AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::createDefaultPerformance() {
      const auto systemName = nameString();

      CurveQuadratic evaporatingTemperatureCurve(model());
      OS_ASSERT(evaporatingTemperatureCurve.setName(systemName + " OUEvapTempCurve"));
      OS_ASSERT(evaporatingTemperatureCurve.setCoefficient1Constant(0.0));
      OS_ASSERT(evaporatingTemperatureCurve.setCoefficient2x(0.605));
      OS_ASSERT(evaporatingTemperatureCurve.setCoefficient3xPOW2(0.025));
      OS_ASSERT(evaporatingTemperatureCurve.setMinimumValueofx(0.0));
      OS_ASSERT(evaporatingTemperatureCurve.setMaximumValueofx(15.0));
      OS_ASSERT(setOutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(evaporatingTemperatureCurve));

      CurveQuadratic condensingTemperatureCurve(model());
      OS_ASSERT(condensingTemperatureCurve.setName(systemName + " OUCondTempCurve"));
      OS_ASSERT(condensingTemperatureCurve.setCoefficient1Constant(0.0));
      OS_ASSERT(condensingTemperatureCurve.setCoefficient2x(-2.91));
      OS_ASSERT(condensingTemperatureCurve.setCoefficient3xPOW2(1.180));
      OS_ASSERT(condensingTemperatureCurve.setMinimumValueofx(0.0));
      OS_ASSERT(condensingTemperatureCurve.setMaximumValueofx(5.0));
      OS_ASSERT(setOutdoorUnitCondensingTemperatureFunctionofSubcoolingCurve(condensingTemperatureCurve));

      struct LoadingCurveDefinition
      {
        const char* nameSuffix;
        std::array<double, 6> coefficients;
      };

      const std::array<LoadingCurveDefinition, 6> definitions = {{
        {" MinSpdCooling", {0.319, -0.00126, -0.0000215, 0.012, 0.000105, -0.0000866}},
        {" MinSpdPower", {0.0879, -0.000172, 0.0000693, -0.0000338, -0.00000810, -0.0000104}},
        {" Spd1Cooling", {0.812, -0.00423, -0.0000411, 0.0297, 0.000267, -0.000223}},
        {" Spd1Power", {0.326, -0.00220, 0.000142, 0.00282, 0.0000286, -0.0000350}},
        {" Spd2Cooling", {1.32, -0.00620, -0.0000710, 0.0489, 0.000459, -0.000367}},
        {" Spd2Power", {0.656, -0.00371, 0.000207, 0.0105, 0.0000736, -0.000157}},
      }};

      std::vector<CurveBiquadratic> loadingCurves;
      loadingCurves.reserve(definitions.size());
      for (const auto& definition : definitions) {
        CurveBiquadratic curve(model());
        OS_ASSERT(curve.setName(systemName + definition.nameSuffix));
        OS_ASSERT(curve.setCoefficient1Constant(definition.coefficients[0]));
        OS_ASSERT(curve.setCoefficient2x(definition.coefficients[1]));
        OS_ASSERT(curve.setCoefficient3xPOW2(definition.coefficients[2]));
        OS_ASSERT(curve.setCoefficient4y(definition.coefficients[3]));
        OS_ASSERT(curve.setCoefficient5yPOW2(definition.coefficients[4]));
        OS_ASSERT(curve.setCoefficient6xTIMESY(definition.coefficients[5]));
        OS_ASSERT(curve.setMinimumValueofx(15.0));
        OS_ASSERT(curve.setMaximumValueofx(65.0));
        OS_ASSERT(curve.setMinimumValueofy(-30.0));
        OS_ASSERT(curve.setMaximumValueofy(15.0));
        loadingCurves.push_back(curve);
      }

      const std::array<double, 3> compressorSpeeds = {1500.0, 3600.0, 6000.0};
      OS_ASSERT(setInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::NumberofCompressorLoadingIndexEntries,
                       static_cast<int>(compressorSpeeds.size())));

      auto system = getObject<ModelObject>();
      for (size_t i = 0; i < compressorSpeeds.size(); ++i) {
        auto group = system.pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(
          group.setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::CompressorSpeedatLoadingIndex,
                          compressorSpeeds[i]));
        OS_ASSERT(group.setPointer(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                                     LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName,
                                   loadingCurves[2 * i].handle(), false));
        OS_ASSERT(group.setPointer(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                                     LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName,
                                   loadingCurves[2 * i + 1].handle(), false));
      }
    }

    boost::optional<ModelObject> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::terminalUnitList() const {
      auto list = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ZoneTerminalUnitListName);
      if (list && list->iddObject().type() == openstudio::IddObjectType::ZoneTerminalUnitList) {
        return list;
      }
      return boost::none;
    }

    boost::optional<ModelObject> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::ensureTerminalUnitList() {
      if (auto list = terminalUnitList()) {
        return list;
      }

      IdfObject listIdfObject(openstudio::IddObjectType::ZoneTerminalUnitList);
      if (!listIdfObject.setName(model().nextName(openstudio::IddObjectType::ZoneTerminalUnitList, true))) {
        return boost::none;
      }
      auto addedObject = model().addObject(listIdfObject);
      if (!addedObject) {
        return boost::none;
      }
      auto list = addedObject->optionalCast<ModelObject>();
      if (!list) {
        addedObject->remove();
        return boost::none;
      }
      if (!setPointer(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ZoneTerminalUnitListName, list->handle(),
                      false)) {
        list->remove();
        return boost::none;
      }
      return list;
    }

    Schedule AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::AvailabilityScheduleName, schedule.handle(),
                        false);
    }

    std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::terminals() const {
      std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> result;
      auto list = terminalUnitList();
      if (!list) {
        return result;
      }

      std::set<Handle> seen;
      for (const auto& group : list->extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
        if (!target) {
          continue;
        }
        auto terminal = target->optionalCast<ZoneHVACTerminalUnitVariableRefrigerantFlow>();
        if (terminal && seen.insert(terminal->handle()).second) {
          result.push_back(*terminal);
        }
      }
      return result;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
      if (terminal.model() != model()) {
        return false;
      }
      auto terminalImpl = terminal.getImpl<ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>();
      OS_ASSERT(terminalImpl);
      if (!terminalImpl->isFluidTemperatureControl()) {
        return false;
      }

      if (auto currentSystem = terminal.vrfSystem()) {
        if (currentSystem->handle() != handle()) {
          return false;
        }
        return true;
      }

      auto list = ensureTerminalUnitList();
      if (!list) {
        return false;
      }
      auto group = list->pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!group) {
        return false;
      }
      if (!group->setPointer(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName, terminal.handle())) {
        list->eraseExtensibleGroup(static_cast<unsigned>(list->extensibleGroups().size() - 1u));
        return false;
      }
      return true;
    }

    void AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
      auto list = terminalUnitList();
      if (!list) {
        return;
      }
      auto groups = list->extensibleGroups();
      for (unsigned i = static_cast<unsigned>(groups.size()); i > 0u; --i) {
        const auto index = i - 1u;
        auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
        if (target && target->handle() == terminal.handle()) {
          list->eraseExtensibleGroup(index);
        }
      }
    }

    void AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::removeAllTerminals() {
      auto list = terminalUnitList();
      if (!list) {
        return;
      }
      while (!list->extensibleGroups().empty()) {
        list->eraseExtensibleGroup(static_cast<unsigned>(list->extensibleGroups().size() - 1u));
      }
    }

    std::vector<IdfObject> AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::remove() {
      Model owningModel = model();
      auto list = terminalUnitList();
      std::vector<ModelObject> performanceCurves;
      std::set<Handle> seenCurves;

      const auto system = getObject<ModelObject>();
      for (const auto field : {
             openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
               OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName,
             openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
               OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName,
           }) {
        if (auto curve = system.getModelObjectTarget<ModelObject>(field)) {
          if (seenCurves.insert(curve->handle()).second) {
            performanceCurves.push_back(*curve);
          }
        }
      }
      for (const auto& extensibleGroup : system.extensibleGroups()) {
        auto group = extensibleGroup.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!group) {
          continue;
        }
        for (const auto field : {
               openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                 LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName,
               openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                 LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName,
             }) {
          if (auto target = group->getTarget(field)) {
            if (auto curve = target->optionalCast<ModelObject>()) {
              if (seenCurves.insert(curve->handle()).second) {
                performanceCurves.push_back(*curve);
              }
            }
          }
        }
      }

      auto removedParent = HVACComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<IdfObject> result;
      if (list) {
        auto removedList = list->remove();
        result.insert(result.end(), removedList.begin(), removedList.end());
      }
      for (auto& curve : performanceCurves) {
        if (owningModel.getObject(curve.handle()) && curve.sources().empty()) {
          auto removedCurve = curve.remove();
          result.insert(result.end(), removedCurve.begin(), removedCurve.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

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

    Curve AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve() const {
      auto curve =
        getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                                                               OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setOutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve(
      const Curve& curve) {
      return setPointer(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                          OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName,
                        curve.handle(), false);
    }

    Curve AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const {
      auto curve =
        getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                                                               OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl::setOutdoorUnitCondensingTemperatureFunctionofSubcoolingCurve(
      const Curve& curve) {
      return setPointer(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::
                          OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName,
                        curve.handle(), false);
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
