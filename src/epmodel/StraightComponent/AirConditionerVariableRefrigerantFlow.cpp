/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <array>
#include <set>

namespace openstudio {
namespace epmodel {

  AirConditionerVariableRefrigerantFlow::AirConditionerVariableRefrigerantFlow(const Model& model)
    : StraightComponent(AirConditionerVariableRefrigerantFlow::iddObjectType(), model) {
    auto impl = getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>();
    OS_ASSERT(impl);
    auto availability = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(impl->setAvailabilitySchedule(availability));
    OS_ASSERT(impl->ensureTerminalUnitList());
    OS_ASSERT(impl->setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(30.0));
    OS_ASSERT(impl->setVerticalHeightusedforPipingCorrectionFactor(10.0));
    OS_ASSERT(impl->setPipingCorrectionFactorforHeightinCoolingModeCoefficient(-0.000386));
    OS_ASSERT(impl->setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(30.0));
    OS_ASSERT(impl->setPipingCorrectionFactorforHeightinHeatingModeCoefficient(0.0));
    OS_ASSERT(impl->setMinimumOutdoorTemperatureinHeatRecoveryMode(0.0));
    OS_ASSERT(impl->setMaximumOutdoorTemperatureinHeatRecoveryMode(20.0));
    OS_ASSERT(impl->setInitialHeatRecoveryCoolingCapacityFraction(0.5));
    OS_ASSERT(impl->setHeatRecoveryCoolingCapacityTimeConstant(0.083));
    OS_ASSERT(impl->setInitialHeatRecoveryCoolingEnergyFraction(1.0));
    OS_ASSERT(impl->setHeatRecoveryCoolingEnergyTimeConstant(0.0));
    OS_ASSERT(impl->setInitialHeatRecoveryHeatingCapacityFraction(0.5));
    OS_ASSERT(impl->setHeatRecoveryHeatingCapacityTimeConstant(0.083));
    OS_ASSERT(impl->setInitialHeatRecoveryHeatingEnergyFraction(0.5));
    OS_ASSERT(impl->setHeatRecoveryHeatingEnergyTimeConstant(0.0));
  }

  AirConditionerVariableRefrigerantFlow::AirConditionerVariableRefrigerantFlow(
    std::shared_ptr<detail::AirConditionerVariableRefrigerantFlow_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirConditionerVariableRefrigerantFlow::iddObjectType() {
    return IddObjectType::AirConditioner_VariableRefrigerantFlow;
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues() {
    return {"WetBulbTemperature", "DryBulbTemperature"};
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlow::defrostStrategyValues() {
    return {"ReverseCycle", "Resistive"};
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlow::condenserTypeValues() {
    return {"AirCooled", "EvaporativelyCooled", "WaterCooled"};
  }

  bool AirConditionerVariableRefrigerantFlow::addToNode(Node& node) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->addToNode(node);
  }

  bool AirConditionerVariableRefrigerantFlow::addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->addTerminal(terminal);
  }

  void AirConditionerVariableRefrigerantFlow::removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->removeTerminal(terminal);
  }

  void AirConditionerVariableRefrigerantFlow::removeAllTerminals() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->removeAllTerminals();
  }

  std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> AirConditionerVariableRefrigerantFlow::terminals() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->terminals();
  }

  Schedule AirConditionerVariableRefrigerantFlow::availabilitySchedule() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->availabilitySchedule();
  }

  bool AirConditionerVariableRefrigerantFlow::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<ThermalZone> AirConditionerVariableRefrigerantFlow::zoneforMasterThermostatLocation() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->zoneforMasterThermostatLocation();
  }

  bool AirConditionerVariableRefrigerantFlow::setZoneforMasterThermostatLocation(const ThermalZone& zone) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setZoneforMasterThermostatLocation(zone);
  }

  void AirConditionerVariableRefrigerantFlow::resetZoneforMasterThermostatLocation() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetZoneforMasterThermostatLocation();
  }

  boost::optional<Schedule> AirConditionerVariableRefrigerantFlow::thermostatPrioritySchedule() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->thermostatPrioritySchedule();
  }

  bool AirConditionerVariableRefrigerantFlow::setThermostatPrioritySchedule(Schedule& schedule) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setThermostatPrioritySchedule(schedule);
  }

  void AirConditionerVariableRefrigerantFlow::resetThermostatPrioritySchedule() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetThermostatPrioritySchedule();
  }

  boost::optional<Schedule> AirConditionerVariableRefrigerantFlow::basinHeaterOperatingSchedule() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->basinHeaterOperatingSchedule();
  }

  bool AirConditionerVariableRefrigerantFlow::setBasinHeaterOperatingSchedule(Schedule& schedule) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setBasinHeaterOperatingSchedule(schedule);
  }

  void AirConditionerVariableRefrigerantFlow::resetBasinHeaterOperatingSchedule() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetBasinHeaterOperatingSchedule();
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlow::grossRatedTotalCoolingCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedTotalCoolingCapacity();
  }

  bool AirConditionerVariableRefrigerantFlow::isGrossRatedTotalCoolingCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isGrossRatedTotalCoolingCapacityAutosized();
  }

  bool AirConditionerVariableRefrigerantFlow::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedTotalCoolingCapacity(grossRatedTotalCoolingCapacity);
  }

  void AirConditionerVariableRefrigerantFlow::autosizeGrossRatedTotalCoolingCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->autosizeGrossRatedTotalCoolingCapacity();
  }

  double AirConditionerVariableRefrigerantFlow::grossRatedCoolingCOP() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedCoolingCOP();
  }

  bool AirConditionerVariableRefrigerantFlow::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedCoolingCOP(grossRatedCoolingCOP);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingCapacityRatioModifierFunctionofLowTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingCapacityRatioModifierFunctionofLowTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingCapacityRatioModifierFunctionofLowTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingCapacityRatioModifierFunctionofLowTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingCapacityRatioBoundaryCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingCapacityRatioBoundaryCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingCapacityRatioBoundaryCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingCapacityRatioBoundaryCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingCapacityRatioBoundaryCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingCapacityRatioBoundaryCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingCapacityRatioModifierFunctionofHighTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingCapacityRatioModifierFunctionofHighTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingCapacityRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingCapacityRatioModifierFunctionofHighTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingCapacityRatioModifierFunctionofHighTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingCapacityRatioModifierFunctionofHighTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingEnergyInputRatioBoundaryCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingEnergyInputRatioBoundaryCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingEnergyInputRatioBoundaryCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingEnergyInputRatioBoundaryCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingEnergyInputRatioBoundaryCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingEnergyInputRatioBoundaryCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingCombinationRatioCorrectionFactorCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingCombinationRatioCorrectionFactorCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingCombinationRatioCorrectionFactorCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingCombinationRatioCorrectionFactorCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingCombinationRatioCorrectionFactorCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingCombinationRatioCorrectionFactorCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::coolingPartLoadFractionCorrelationCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->coolingPartLoadFractionCorrelationCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setCoolingPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCoolingPartLoadFractionCorrelationCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetCoolingPartLoadFractionCorrelationCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCoolingPartLoadFractionCorrelationCurve();
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlow::grossRatedHeatingCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedHeatingCapacity();
  }

  bool AirConditionerVariableRefrigerantFlow::isGrossRatedHeatingCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isGrossRatedHeatingCapacityAutosized();
  }

  bool AirConditionerVariableRefrigerantFlow::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedHeatingCapacity(grossRatedHeatingCapacity);
  }

  void AirConditionerVariableRefrigerantFlow::autosizeGrossRatedHeatingCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->autosizeGrossRatedHeatingCapacity();
  }

  double AirConditionerVariableRefrigerantFlow::ratedHeatingCapacitySizingRatio() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->ratedHeatingCapacitySizingRatio();
  }

  bool AirConditionerVariableRefrigerantFlow::setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setRatedHeatingCapacitySizingRatio(ratedHeatingCapacitySizingRatio);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingCapacityRatioModifierFunctionofLowTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingCapacityRatioModifierFunctionofLowTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingCapacityRatioModifierFunctionofLowTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingCapacityRatioModifierFunctionofLowTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingCapacityRatioBoundaryCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingCapacityRatioBoundaryCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingCapacityRatioBoundaryCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingCapacityRatioBoundaryCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingCapacityRatioBoundaryCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingCapacityRatioBoundaryCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingCapacityRatioModifierFunctionofHighTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingCapacityRatioModifierFunctionofHighTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingCapacityRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingCapacityRatioModifierFunctionofHighTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingCapacityRatioModifierFunctionofHighTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingCapacityRatioModifierFunctionofHighTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingEnergyInputRatioBoundaryCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingEnergyInputRatioBoundaryCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingEnergyInputRatioBoundaryCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingEnergyInputRatioBoundaryCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingEnergyInputRatioBoundaryCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingEnergyInputRatioBoundaryCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve();
  }

  std::string AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureType() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingPerformanceCurveOutdoorTemperatureType();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingPerformanceCurveOutdoorTemperatureType(
    const std::string& heatingPerformanceCurveOutdoorTemperatureType) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingPerformanceCurveOutdoorTemperatureType(
      heatingPerformanceCurveOutdoorTemperatureType);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingCombinationRatioCorrectionFactorCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingCombinationRatioCorrectionFactorCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingCombinationRatioCorrectionFactorCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingCombinationRatioCorrectionFactorCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingCombinationRatioCorrectionFactorCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingCombinationRatioCorrectionFactorCurve();
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatingPartLoadFractionCorrelationCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingPartLoadFractionCorrelationCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingPartLoadFractionCorrelationCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatingPartLoadFractionCorrelationCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatingPartLoadFractionCorrelationCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::heatPumpWasteHeatRecovery() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatPumpWasteHeatRecovery();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatPumpWasteHeatRecovery(heatPumpWasteHeatRecovery);
  }

  double AirConditionerVariableRefrigerantFlow::equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode();
  }

  bool AirConditionerVariableRefrigerantFlow::setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(
    double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(
      equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode);
  }

  double AirConditionerVariableRefrigerantFlow::verticalHeightusedforPipingCorrectionFactor() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->verticalHeightusedforPipingCorrectionFactor();
  }

  bool AirConditionerVariableRefrigerantFlow::setVerticalHeightusedforPipingCorrectionFactor(double verticalHeightusedforPipingCorrectionFactor) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setVerticalHeightusedforPipingCorrectionFactor(
      verticalHeightusedforPipingCorrectionFactor);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::pipingCorrectionFactorforLengthinCoolingModeCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->pipingCorrectionFactorforLengthinCoolingModeCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setPipingCorrectionFactorforLengthinCoolingModeCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setPipingCorrectionFactorforLengthinCoolingModeCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetPipingCorrectionFactorforLengthinCoolingModeCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetPipingCorrectionFactorforLengthinCoolingModeCurve();
  }

  double AirConditionerVariableRefrigerantFlow::pipingCorrectionFactorforHeightinCoolingModeCoefficient() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->pipingCorrectionFactorforHeightinCoolingModeCoefficient();
  }

  bool AirConditionerVariableRefrigerantFlow::setPipingCorrectionFactorforHeightinCoolingModeCoefficient(
    double pipingCorrectionFactorforHeightinCoolingModeCoefficient) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setPipingCorrectionFactorforHeightinCoolingModeCoefficient(
      pipingCorrectionFactorforHeightinCoolingModeCoefficient);
  }

  double AirConditionerVariableRefrigerantFlow::equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode();
  }

  bool AirConditionerVariableRefrigerantFlow::setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(
    double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(
      equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::pipingCorrectionFactorforLengthinHeatingModeCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->pipingCorrectionFactorforLengthinHeatingModeCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setPipingCorrectionFactorforLengthinHeatingModeCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setPipingCorrectionFactorforLengthinHeatingModeCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetPipingCorrectionFactorforLengthinHeatingModeCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetPipingCorrectionFactorforLengthinHeatingModeCurve();
  }

  double AirConditionerVariableRefrigerantFlow::pipingCorrectionFactorforHeightinHeatingModeCoefficient() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->pipingCorrectionFactorforHeightinHeatingModeCoefficient();
  }

  bool AirConditionerVariableRefrigerantFlow::setPipingCorrectionFactorforHeightinHeatingModeCoefficient(
    double pipingCorrectionFactorforHeightinHeatingModeCoefficient) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setPipingCorrectionFactorforHeightinHeatingModeCoefficient(
      pipingCorrectionFactorforHeightinHeatingModeCoefficient);
  }

  int AirConditionerVariableRefrigerantFlow::numberofCompressors() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->numberofCompressors();
  }

  bool AirConditionerVariableRefrigerantFlow::setNumberofCompressors(int numberofCompressors) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setNumberofCompressors(numberofCompressors);
  }

  std::string AirConditionerVariableRefrigerantFlow::defrostStrategy() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->defrostStrategy();
  }

  bool AirConditionerVariableRefrigerantFlow::setDefrostStrategy(const std::string& defrostStrategy) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setDefrostStrategy(defrostStrategy);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::defrostEnergyInputRatioModifierFunctionofTemperatureCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->defrostEnergyInputRatioModifierFunctionofTemperatureCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();
  }

  std::string AirConditionerVariableRefrigerantFlow::condenserType() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->condenserType();
  }

  bool AirConditionerVariableRefrigerantFlow::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCondenserType(condenserType);
  }

  bool AirConditionerVariableRefrigerantFlow::isCondenserTypeDefaulted() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isCondenserTypeDefaulted();
  }

  void AirConditionerVariableRefrigerantFlow::resetCondenserType() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCondenserType();
  }

  double AirConditionerVariableRefrigerantFlow::minimumOutdoorTemperatureinHeatRecoveryMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->minimumOutdoorTemperatureinHeatRecoveryMode();
  }

  bool AirConditionerVariableRefrigerantFlow::setMinimumOutdoorTemperatureinHeatRecoveryMode(double minimumOutdoorTemperatureinHeatRecoveryMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setMinimumOutdoorTemperatureinHeatRecoveryMode(
      minimumOutdoorTemperatureinHeatRecoveryMode);
  }

  double AirConditionerVariableRefrigerantFlow::maximumOutdoorTemperatureinHeatRecoveryMode() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->maximumOutdoorTemperatureinHeatRecoveryMode();
  }

  bool AirConditionerVariableRefrigerantFlow::setMaximumOutdoorTemperatureinHeatRecoveryMode(double maximumOutdoorTemperatureinHeatRecoveryMode) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setMaximumOutdoorTemperatureinHeatRecoveryMode(
      maximumOutdoorTemperatureinHeatRecoveryMode);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatRecoveryCoolingCapacityModifierCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryCoolingCapacityModifierCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryCoolingCapacityModifierCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryCoolingCapacityModifierCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatRecoveryCoolingCapacityModifierCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatRecoveryCoolingCapacityModifierCurve();
  }

  double AirConditionerVariableRefrigerantFlow::initialHeatRecoveryCoolingCapacityFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->initialHeatRecoveryCoolingCapacityFraction();
  }

  bool AirConditionerVariableRefrigerantFlow::setInitialHeatRecoveryCoolingCapacityFraction(double initialHeatRecoveryCoolingCapacityFraction) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setInitialHeatRecoveryCoolingCapacityFraction(
      initialHeatRecoveryCoolingCapacityFraction);
  }

  double AirConditionerVariableRefrigerantFlow::heatRecoveryCoolingCapacityTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryCoolingCapacityTimeConstant();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryCoolingCapacityTimeConstant(double heatRecoveryCoolingCapacityTimeConstant) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryCoolingCapacityTimeConstant(
      heatRecoveryCoolingCapacityTimeConstant);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatRecoveryCoolingEnergyModifierCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryCoolingEnergyModifierCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryCoolingEnergyModifierCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryCoolingEnergyModifierCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatRecoveryCoolingEnergyModifierCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatRecoveryCoolingEnergyModifierCurve();
  }

  double AirConditionerVariableRefrigerantFlow::initialHeatRecoveryCoolingEnergyFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->initialHeatRecoveryCoolingEnergyFraction();
  }

  bool AirConditionerVariableRefrigerantFlow::setInitialHeatRecoveryCoolingEnergyFraction(double initialHeatRecoveryCoolingEnergyFraction) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setInitialHeatRecoveryCoolingEnergyFraction(
      initialHeatRecoveryCoolingEnergyFraction);
  }

  double AirConditionerVariableRefrigerantFlow::heatRecoveryCoolingEnergyTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryCoolingEnergyTimeConstant();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryCoolingEnergyTimeConstant(double heatRecoveryCoolingEnergyTimeConstant) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryCoolingEnergyTimeConstant(
      heatRecoveryCoolingEnergyTimeConstant);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatRecoveryHeatingCapacityModifierCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryHeatingCapacityModifierCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryHeatingCapacityModifierCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryHeatingCapacityModifierCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatRecoveryHeatingCapacityModifierCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatRecoveryHeatingCapacityModifierCurve();
  }

  double AirConditionerVariableRefrigerantFlow::initialHeatRecoveryHeatingCapacityFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->initialHeatRecoveryHeatingCapacityFraction();
  }

  bool AirConditionerVariableRefrigerantFlow::setInitialHeatRecoveryHeatingCapacityFraction(double initialHeatRecoveryHeatingCapacityFraction) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setInitialHeatRecoveryHeatingCapacityFraction(
      initialHeatRecoveryHeatingCapacityFraction);
  }

  double AirConditionerVariableRefrigerantFlow::heatRecoveryHeatingCapacityTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryHeatingCapacityTimeConstant();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryHeatingCapacityTimeConstant(double heatRecoveryHeatingCapacityTimeConstant) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryHeatingCapacityTimeConstant(
      heatRecoveryHeatingCapacityTimeConstant);
  }

  boost::optional<Curve> AirConditionerVariableRefrigerantFlow::heatRecoveryHeatingEnergyModifierCurve() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryHeatingEnergyModifierCurve();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryHeatingEnergyModifierCurve(const Curve& curve) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryHeatingEnergyModifierCurve(curve);
  }

  void AirConditionerVariableRefrigerantFlow::resetHeatRecoveryHeatingEnergyModifierCurve() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetHeatRecoveryHeatingEnergyModifierCurve();
  }

  double AirConditionerVariableRefrigerantFlow::initialHeatRecoveryHeatingEnergyFraction() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->initialHeatRecoveryHeatingEnergyFraction();
  }

  bool AirConditionerVariableRefrigerantFlow::setInitialHeatRecoveryHeatingEnergyFraction(double initialHeatRecoveryHeatingEnergyFraction) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setInitialHeatRecoveryHeatingEnergyFraction(
      initialHeatRecoveryHeatingEnergyFraction);
  }

  double AirConditionerVariableRefrigerantFlow::heatRecoveryHeatingEnergyTimeConstant() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatRecoveryHeatingEnergyTimeConstant();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatRecoveryHeatingEnergyTimeConstant(double heatRecoveryHeatingEnergyTimeConstant) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatRecoveryHeatingEnergyTimeConstant(
      heatRecoveryHeatingEnergyTimeConstant);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    Schedule AirConditionerVariableRefrigerantFlow_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName,
                                           "AirConditionerVariableRefrigerantFlow", "Availability Schedule", schedule);
    }

    boost::optional<ThermalZone> AirConditionerVariableRefrigerantFlow_Impl::zoneforMasterThermostatLocation() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setZoneforMasterThermostatLocation(const ThermalZone& zone) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation;
      if (zone.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirConditionerVariableRefrigerantFlow",
                 "Cannot set the master thermostat zone because it belongs to a different model.");
        return false;
      }
      if (!model().canBeTarget(zone.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.AirConditionerVariableRefrigerantFlow",
                 "Cannot set the master thermostat zone because ThermalZone is not accepted by the VRF field.");
        return false;
      }
      return setPointer(field, zone.handle(), false);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetZoneforMasterThermostatLocation() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> AirConditionerVariableRefrigerantFlow_Impl::thermostatPrioritySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::ThermostatPriorityScheduleName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setThermostatPrioritySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirConditioner_VariableRefrigerantFlowFields::ThermostatPriorityScheduleName,
                                           "AirConditionerVariableRefrigerantFlow", "Thermostat Priority Schedule", schedule);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetThermostatPrioritySchedule() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::ThermostatPriorityScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> AirConditionerVariableRefrigerantFlow_Impl::basinHeaterOperatingSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingScheduleName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setBasinHeaterOperatingSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingScheduleName,
                                           "AirConditionerVariableRefrigerantFlow", "Basin Heater Operating Schedule", schedule);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetBasinHeaterOperatingSchedule() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<ModelObject> AirConditionerVariableRefrigerantFlow_Impl::terminalUnitList() const {
      auto list = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
      if (list && list->iddObject().type() == openstudio::IddObjectType::ZoneTerminalUnitList) {
        return list;
      }
      return boost::none;
    }

    boost::optional<ModelObject> AirConditionerVariableRefrigerantFlow_Impl::ensureTerminalUnitList() {
      if (auto list = terminalUnitList()) {
        return list;
      }

      auto owner = getObject<ModelObject>();
      if (!owner.name()) {
        owner.createName();
      }
      if (!owner.name()) {
        return boost::none;
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
      if (!setPointer(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName, list->handle(), false)) {
        list->remove();
        return boost::none;
      }
      return list;
    }

    std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> AirConditionerVariableRefrigerantFlow_Impl::terminals() const {
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

    bool AirConditionerVariableRefrigerantFlow_Impl::addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
      if (terminal.model() != model()) {
        return false;
      }
      auto terminalImpl = terminal.getImpl<ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>();
      OS_ASSERT(terminalImpl);
      if (terminalImpl->isFluidTemperatureControl()) {
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

    void AirConditionerVariableRefrigerantFlow_Impl::removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
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

    void AirConditionerVariableRefrigerantFlow_Impl::removeAllTerminals() {
      auto list = terminalUnitList();
      if (!list) {
        return;
      }
      while (!list->extensibleGroups().empty()) {
        list->eraseExtensibleGroup(static_cast<unsigned>(list->extensibleGroups().size() - 1u));
      }
    }

    std::vector<IdfObject> AirConditionerVariableRefrigerantFlow_Impl::remove() {
      auto list = terminalUnitList();
      auto removedParent = StraightComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<IdfObject> result;
      if (list) {
        auto removedList = list->remove();
        result.insert(result.end(), removedList.begin(), removedList.end());
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    void AirConditionerVariableRefrigerantFlow_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      constexpr auto availabilityField = openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName;
      const auto rawAvailability = openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true);
      if ((!rawAvailability || rawAvailability->empty()) && !getObject<ModelObject>().getModelObjectTarget<Schedule>(availabilityField)) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        if (setAvailabilitySchedule(alwaysOn)) {
          detail::addLoadInfo(context, "Attached the always-on availability schedule to AirConditioner:VariableRefrigerantFlow '"
                                         + getObject<ModelObject>().nameString() + "'.");
        } else {
          detail::addLoadError(context, "Failed to attach the always-on availability schedule to AirConditioner:VariableRefrigerantFlow '"
                                          + getObject<ModelObject>().nameString() + "'.");
        }
      }

      struct CanonicalScalar
      {
        unsigned field;
        double value;
        const char* name;
      };
      constexpr std::array<CanonicalScalar, 15> canonicalScalars = {{
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, 30.0,
         "cooling equivalent piping length"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::VerticalHeightusedforPipingCorrectionFactor, 10.0,
         "piping correction vertical height"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinCoolingModeCoefficient, -0.000386,
         "cooling piping height coefficient"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, 30.0,
         "heating equivalent piping length"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinHeatingModeCoefficient, 0.0,
         "heating piping height coefficient"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::MinimumCondenserInletNodeTemperatureinHeatRecoveryMode, 0.0,
         "minimum heat-recovery outdoor temperature"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::MaximumCondenserInletNodeTemperatureinHeatRecoveryMode, 20.0,
         "maximum heat-recovery outdoor temperature"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingCapacityFraction, 0.5,
         "initial heat-recovery cooling capacity fraction"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityTimeConstant, 0.083,
         "heat-recovery cooling capacity time constant"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingEnergyFraction, 1.0,
         "initial heat-recovery cooling energy fraction"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyTimeConstant, 0.0,
         "heat-recovery cooling energy time constant"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingCapacityFraction, 0.5,
         "initial heat-recovery heating capacity fraction"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityTimeConstant, 0.083,
         "heat-recovery heating capacity time constant"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingEnergyFraction, 0.5,
         "initial heat-recovery heating energy fraction"},
        {openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyTimeConstant, 0.0,
         "heat-recovery heating energy time constant"},
      }};

      for (const auto& scalar : canonicalScalars) {
        // Inspect raw concrete storage so configured EnergyPlus defaults cannot mask canonical Model values.
        const auto raw = openstudio::detail::IdfObject_Impl::getString(scalar.field, false, true);
        if (raw && !raw->empty()) {
          continue;
        }
        if (setDouble(scalar.field, scalar.value)) {
          detail::addLoadInfo(context, "Restored the canonical " + std::string(scalar.name) + " on AirConditioner:VariableRefrigerantFlow '"
                                         + getObject<ModelObject>().nameString() + "'.");
        } else {
          detail::addLoadError(context, "Failed to restore the canonical " + std::string(scalar.name) + " on AirConditioner:VariableRefrigerantFlow '"
                                          + getObject<ModelObject>().nameString() + "'.");
        }
      }
    }

    boost::optional<double> AirConditionerVariableRefrigerantFlow_Impl::grossRatedTotalCoolingCapacity() const {
      return getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::isGrossRatedTotalCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, grossRatedTotalCoolingCapacity);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::autosizeGrossRatedTotalCoolingCapacity() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "autosize"));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::grossRatedCoolingCOP() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, grossRatedCoolingCOP);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setValidatedCurve(unsigned field, const Curve& curve, const char* relationshipName) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirConditionerVariableRefrigerantFlow",
                 "Cannot set the " << relationshipName << " because the curve belongs to a different model.");
        return false;
      }
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.AirConditionerVariableRefrigerantFlow",
                 "Cannot set the " << relationshipName << " because curve type '" << curve.iddObject().type().valueName()
                                   << "' is not accepted by the AirConditioner:VariableRefrigerantFlow field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingCapacityRatioModifierFunctionofLowTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName;
      return setValidatedCurve(field, curve, "cooling capacity ratio low-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingCapacityRatioModifierFunctionofLowTemperatureCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingCapacityRatioBoundaryCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioBoundaryCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingCapacityRatioBoundaryCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioBoundaryCurveName;
      return setValidatedCurve(field, curve, "cooling capacity ratio boundary curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingCapacityRatioBoundaryCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioBoundaryCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingCapacityRatioModifierFunctionofHighTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingCapacityRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName;
      return setValidatedCurve(field, curve, "cooling capacity ratio high-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingCapacityRatioModifierFunctionofHighTemperatureCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName;
      return setValidatedCurve(field, curve, "cooling energy input ratio low-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingEnergyInputRatioBoundaryCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioBoundaryCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingEnergyInputRatioBoundaryCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioBoundaryCurveName;
      return setValidatedCurve(field, curve, "cooling energy input ratio boundary curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingEnergyInputRatioBoundaryCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioBoundaryCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName;
      return setValidatedCurve(field, curve, "cooling energy input ratio high-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName;
      return setValidatedCurve(field, curve, "cooling energy input ratio low-part-load modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName;
      return setValidatedCurve(field, curve, "cooling energy input ratio high-part-load modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingCombinationRatioCorrectionFactorCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCombinationRatioCorrectionFactorCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingCombinationRatioCorrectionFactorCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCombinationRatioCorrectionFactorCurveName;
      return setValidatedCurve(field, curve, "cooling combination ratio correction factor curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingCombinationRatioCorrectionFactorCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCombinationRatioCorrectionFactorCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::coolingPartLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingPartLoadFractionCorrelationCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCoolingPartLoadFractionCorrelationCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingPartLoadFractionCorrelationCurveName;
      return setValidatedCurve(field, curve, "cooling part-load fraction correlation curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCoolingPartLoadFractionCorrelationCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingPartLoadFractionCorrelationCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<double> AirConditionerVariableRefrigerantFlow_Impl::grossRatedHeatingCapacity() const {
      return getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::isGrossRatedHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, grossRatedHeatingCapacity);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::autosizeGrossRatedHeatingCapacity() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "autosize"));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::ratedHeatingCapacitySizingRatio() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, ratedHeatingCapacitySizingRatio);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingCapacityRatioModifierFunctionofLowTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName;
      return setValidatedCurve(field, curve, "heating capacity ratio low-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingCapacityRatioModifierFunctionofLowTemperatureCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingCapacityRatioBoundaryCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioBoundaryCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingCapacityRatioBoundaryCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioBoundaryCurveName;
      return setValidatedCurve(field, curve, "heating capacity ratio boundary curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingCapacityRatioBoundaryCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioBoundaryCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingCapacityRatioModifierFunctionofHighTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingCapacityRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName;
      return setValidatedCurve(field, curve, "heating capacity ratio high-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingCapacityRatioModifierFunctionofHighTemperatureCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName;
      return setValidatedCurve(field, curve, "heating energy input ratio low-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingEnergyInputRatioBoundaryCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioBoundaryCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingEnergyInputRatioBoundaryCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioBoundaryCurveName;
      return setValidatedCurve(field, curve, "heating energy input ratio boundary curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingEnergyInputRatioBoundaryCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioBoundaryCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName;
      return setValidatedCurve(field, curve, "heating energy input ratio high-temperature modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    std::string AirConditionerVariableRefrigerantFlow_Impl::heatingPerformanceCurveOutdoorTemperatureType() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingPerformanceCurveOutdoorTemperatureType(
      const std::string& heatingPerformanceCurveOutdoorTemperatureType) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType,
                       heatingPerformanceCurveOutdoorTemperatureType);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName;
      return setValidatedCurve(field, curve, "heating energy input ratio low-part-load modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(const Curve& curve) {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName;
      return setValidatedCurve(field, curve, "heating energy input ratio high-part-load modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve() {
      constexpr auto field =
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingCombinationRatioCorrectionFactorCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCombinationRatioCorrectionFactorCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingCombinationRatioCorrectionFactorCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCombinationRatioCorrectionFactorCurveName;
      return setValidatedCurve(field, curve, "heating combination ratio correction factor curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingCombinationRatioCorrectionFactorCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCombinationRatioCorrectionFactorCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatingPartLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPartLoadFractionCorrelationCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingPartLoadFractionCorrelationCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPartLoadFractionCorrelationCurveName;
      return setValidatedCurve(field, curve, "heating part-load fraction correlation curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatingPartLoadFractionCorrelationCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPartLoadFractionCorrelationCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::heatPumpWasteHeatRecovery() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery) {
      const bool result =
        setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, heatPumpWasteHeatRecovery ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    double AirConditionerVariableRefrigerantFlow_Impl::equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(
      double equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode,
                       equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::verticalHeightusedforPipingCorrectionFactor() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::VerticalHeightusedforPipingCorrectionFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      AirConditionerVariableRefrigerantFlow_Impl::setVerticalHeightusedforPipingCorrectionFactor(double verticalHeightusedforPipingCorrectionFactor) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::VerticalHeightusedforPipingCorrectionFactor,
                       verticalHeightusedforPipingCorrectionFactor);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::pipingCorrectionFactorforLengthinCoolingModeCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinCoolingModeCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setPipingCorrectionFactorforLengthinCoolingModeCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinCoolingModeCurveName;
      return setValidatedCurve(field, curve, "cooling piping length correction curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetPipingCorrectionFactorforLengthinCoolingModeCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinCoolingModeCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::pipingCorrectionFactorforHeightinCoolingModeCoefficient() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinCoolingModeCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setPipingCorrectionFactorforHeightinCoolingModeCoefficient(
      double pipingCorrectionFactorforHeightinCoolingModeCoefficient) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinCoolingModeCoefficient,
                       pipingCorrectionFactorforHeightinCoolingModeCoefficient);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(
      double equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode,
                       equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::pipingCorrectionFactorforLengthinHeatingModeCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinHeatingModeCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setPipingCorrectionFactorforLengthinHeatingModeCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinHeatingModeCurveName;
      return setValidatedCurve(field, curve, "heating piping length correction curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetPipingCorrectionFactorforLengthinHeatingModeCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinHeatingModeCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::pipingCorrectionFactorforHeightinHeatingModeCoefficient() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinHeatingModeCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setPipingCorrectionFactorforHeightinHeatingModeCoefficient(
      double pipingCorrectionFactorforHeightinHeatingModeCoefficient) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinHeatingModeCoefficient,
                       pipingCorrectionFactorforHeightinHeatingModeCoefficient);
    }

    int AirConditionerVariableRefrigerantFlow_Impl::numberofCompressors() const {
      const auto value = getInt(openstudio::AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setNumberofCompressors(int numberofCompressors) {
      return setInt(openstudio::AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, numberofCompressors);
    }

    std::string AirConditionerVariableRefrigerantFlow_Impl::defrostStrategy() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, defrostStrategy);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::defrostEnergyInputRatioModifierFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName;
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirConditionerVariableRefrigerantFlow",
                 "Cannot set the defrost energy input ratio modifier curve because it belongs to a different model.");
        return false;
      }
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.AirConditionerVariableRefrigerantFlow",
                 "Cannot set the defrost energy input ratio modifier curve because curve type '" << curve.iddObject().type().valueName()
                                                                                                 << "' is not accepted by the VRF field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    std::string AirConditionerVariableRefrigerantFlow_Impl::condenserType() const {
      if (!isCondenserTypeDefaulted()) {
        if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, false)) {
          return *value;
        }
      }
      return plantLoop() ? "WaterCooled" : "AirCooled";
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, condenserType);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCondenserType() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, ""));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::minimumOutdoorTemperatureinHeatRecoveryMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::MinimumCondenserInletNodeTemperatureinHeatRecoveryMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      AirConditionerVariableRefrigerantFlow_Impl::setMinimumOutdoorTemperatureinHeatRecoveryMode(double minimumOutdoorTemperatureinHeatRecoveryMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::MinimumCondenserInletNodeTemperatureinHeatRecoveryMode,
                       minimumOutdoorTemperatureinHeatRecoveryMode);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::maximumOutdoorTemperatureinHeatRecoveryMode() const {
      const auto value =
        getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::MaximumCondenserInletNodeTemperatureinHeatRecoveryMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      AirConditionerVariableRefrigerantFlow_Impl::setMaximumOutdoorTemperatureinHeatRecoveryMode(double maximumOutdoorTemperatureinHeatRecoveryMode) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::MaximumCondenserInletNodeTemperatureinHeatRecoveryMode,
                       maximumOutdoorTemperatureinHeatRecoveryMode);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryCoolingCapacityModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityModifierCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryCoolingCapacityModifierCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityModifierCurveName;
      return setValidatedCurve(field, curve, "heat-recovery cooling capacity modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatRecoveryCoolingCapacityModifierCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityModifierCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::initialHeatRecoveryCoolingCapacityFraction() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingCapacityFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      AirConditionerVariableRefrigerantFlow_Impl::setInitialHeatRecoveryCoolingCapacityFraction(double initialHeatRecoveryCoolingCapacityFraction) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingCapacityFraction,
                       initialHeatRecoveryCoolingCapacityFraction);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryCoolingCapacityTimeConstant() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryCoolingCapacityTimeConstant(double heatRecoveryCoolingCapacityTimeConstant) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityTimeConstant,
                       heatRecoveryCoolingCapacityTimeConstant);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryCoolingEnergyModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyModifierCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryCoolingEnergyModifierCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyModifierCurveName;
      return setValidatedCurve(field, curve, "heat-recovery cooling energy modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatRecoveryCoolingEnergyModifierCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyModifierCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::initialHeatRecoveryCoolingEnergyFraction() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingEnergyFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setInitialHeatRecoveryCoolingEnergyFraction(double initialHeatRecoveryCoolingEnergyFraction) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingEnergyFraction,
                       initialHeatRecoveryCoolingEnergyFraction);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryCoolingEnergyTimeConstant() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryCoolingEnergyTimeConstant(double heatRecoveryCoolingEnergyTimeConstant) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyTimeConstant,
                       heatRecoveryCoolingEnergyTimeConstant);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryHeatingCapacityModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityModifierCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryHeatingCapacityModifierCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityModifierCurveName;
      return setValidatedCurve(field, curve, "heat-recovery heating capacity modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatRecoveryHeatingCapacityModifierCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityModifierCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::initialHeatRecoveryHeatingCapacityFraction() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingCapacityFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      AirConditionerVariableRefrigerantFlow_Impl::setInitialHeatRecoveryHeatingCapacityFraction(double initialHeatRecoveryHeatingCapacityFraction) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingCapacityFraction,
                       initialHeatRecoveryHeatingCapacityFraction);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryHeatingCapacityTimeConstant() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryHeatingCapacityTimeConstant(double heatRecoveryHeatingCapacityTimeConstant) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityTimeConstant,
                       heatRecoveryHeatingCapacityTimeConstant);
    }

    boost::optional<Curve> AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryHeatingEnergyModifierCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyModifierCurveName);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryHeatingEnergyModifierCurve(const Curve& curve) {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyModifierCurveName;
      return setValidatedCurve(field, curve, "heat-recovery heating energy modifier curve");
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetHeatRecoveryHeatingEnergyModifierCurve() {
      constexpr auto field = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyModifierCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::initialHeatRecoveryHeatingEnergyFraction() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingEnergyFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setInitialHeatRecoveryHeatingEnergyFraction(double initialHeatRecoveryHeatingEnergyFraction) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingEnergyFraction,
                       initialHeatRecoveryHeatingEnergyFraction);
    }

    double AirConditionerVariableRefrigerantFlow_Impl::heatRecoveryHeatingEnergyTimeConstant() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatRecoveryHeatingEnergyTimeConstant(double heatRecoveryHeatingEnergyTimeConstant) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyTimeConstant,
                       heatRecoveryHeatingEnergyTimeConstant);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::addToNode(Node& node) {
      auto plantLoop_ = node.plantLoop();
      if (!plantLoop_ || !plantLoop_->demandComponent(node.handle())) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::heatingPerformanceCurveOutdoorTemperatureTypeValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::defrostStrategyValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::condenserTypeValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::condenserTypeValues();
    }

    unsigned AirConditionerVariableRefrigerantFlow_Impl::inletPort() const {
      return openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserInletNodeName;
    }

    unsigned AirConditionerVariableRefrigerantFlow_Impl::outletPort() const {
      return openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
