/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACLowTempRadiantVarFlow::ZoneHVACLowTempRadiantVarFlow(const Model& model)
    : ZoneHVACComponent(ZoneHVACLowTempRadiantVarFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>());
  }

  ZoneHVACLowTempRadiantVarFlow::ZoneHVACLowTempRadiantVarFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantVarFlow_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACLowTempRadiantVarFlow::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::numberofCircuitsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::fluidtoRadiantSurfaceHeatTransferModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::TemperatureControlType);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::setpointControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::SetpointControlType);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::HeatingDesignCapacityMethod);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantVarFlow::condensationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design).get(),
                          ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType);
  }

  unsigned detail::ZoneHVACLowTempRadiantVarFlow_Impl::inletPort() const {
    return 0u;
  }

  unsigned detail::ZoneHVACLowTempRadiantVarFlow_Impl::outletPort() const {
    return 0u;
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::hydronicTubingLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingLength();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingLengthAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingLengthAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingLength(double hydronicTubingLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingLength(hydronicTubingLength);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeHydronicTubingLength() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeHydronicTubingLength();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeHeatingDesignCapacity();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::maximumHotWaterFlow() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->maximumHotWaterFlow();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isMaximumHotWaterFlowAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isMaximumHotWaterFlowAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setMaximumHotWaterFlow(double maximumHotWaterFlow) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setMaximumHotWaterFlow(maximumHotWaterFlow);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeMaximumHotWaterFlow() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeMaximumHotWaterFlow();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCoolingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCoolingDesignCapacityAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingDesignCapacity(double coolingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacity(coolingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeCoolingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeCoolingDesignCapacity();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::maximumColdWaterFlow() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->maximumColdWaterFlow();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isMaximumColdWaterFlowAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isMaximumColdWaterFlowAutosized();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setMaximumColdWaterFlow(double maximumColdWaterFlow) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setMaximumColdWaterFlow(maximumColdWaterFlow);
  }

  void ZoneHVACLowTempRadiantVarFlow::autosizeMaximumColdWaterFlow() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->autosizeMaximumColdWaterFlow();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::numberofCircuits() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->numberofCircuits();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isNumberofCircuitsDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isNumberofCircuitsDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setNumberofCircuits(const std::string& numberofCircuits) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setNumberofCircuits(numberofCircuits);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetNumberofCircuits() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetNumberofCircuits();
  }

  double ZoneHVACLowTempRadiantVarFlow::circuitLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->circuitLength();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCircuitLengthDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCircuitLengthDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCircuitLength(double circuitLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCircuitLength(circuitLength);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCircuitLength() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCircuitLength();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::fluidtoRadiantSurfaceHeatTransferModel() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(fluidtoRadiantSurfaceHeatTransferModel);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetFluidtoRadiantSurfaceHeatTransferModel() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
  }

  double ZoneHVACLowTempRadiantVarFlow::hydronicTubingInsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingInsideDiameter();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingInsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingInsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHydronicTubingInsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHydronicTubingInsideDiameter();
  }

  double ZoneHVACLowTempRadiantVarFlow::hydronicTubingOutsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingOutsideDiameter();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingOutsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHydronicTubingOutsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHydronicTubingOutsideDiameter();
  }

  double ZoneHVACLowTempRadiantVarFlow::hydronicTubingConductivity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->hydronicTubingConductivity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHydronicTubingConductivityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHydronicTubingConductivityDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHydronicTubingConductivity(double hydronicTubingConductivity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHydronicTubingConductivity(hydronicTubingConductivity);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHydronicTubingConductivity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHydronicTubingConductivity();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetTemperatureControlType();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::setpointControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setpointControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isSetpointControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isSetpointControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setSetpointControlType(const std::string& setpointControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setSetpointControlType(setpointControlType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetSetpointControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetSetpointControlType();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHeatingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHeatingDesignCapacityMethodDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingDesignCapacityPerFloorArea();
  }

  double ZoneHVACLowTempRadiantVarFlow::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isFractionofAutosizedHeatingDesignCapacityDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetFractionofAutosizedHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetFractionofAutosizedHeatingDesignCapacity();
  }

  double ZoneHVACLowTempRadiantVarFlow::heatingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->heatingControlThrottlingRange();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isHeatingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isHeatingControlThrottlingRangeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setHeatingControlThrottlingRange(double heatingControlThrottlingRange) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setHeatingControlThrottlingRange(heatingControlThrottlingRange);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetHeatingControlThrottlingRange() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetHeatingControlThrottlingRange();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingDesignCapacityMethod();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCoolingDesignCapacityMethodDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCoolingDesignCapacityMethodDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacityMethod(coolingDesignCapacityMethod);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::coolingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingDesignCapacityPerFloorArea(coolingDesignCapacityPerFloorArea);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingDesignCapacityPerFloorArea();
  }

  boost::optional<double> ZoneHVACLowTempRadiantVarFlow::fractionofAutosizedCoolingDesignCapacity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->fractionofAutosizedCoolingDesignCapacity();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setFractionofAutosizedCoolingDesignCapacity(
      fractionofAutosizedCoolingDesignCapacity);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetFractionofAutosizedCoolingDesignCapacity() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetFractionofAutosizedCoolingDesignCapacity();
  }

  double ZoneHVACLowTempRadiantVarFlow::coolingControlThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->coolingControlThrottlingRange();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCoolingControlThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCoolingControlThrottlingRangeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCoolingControlThrottlingRange(coolingControlThrottlingRange);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCoolingControlThrottlingRange() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCoolingControlThrottlingRange();
  }

  std::string ZoneHVACLowTempRadiantVarFlow::condensationControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->condensationControlType();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCondensationControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCondensationControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCondensationControlType(const std::string& condensationControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCondensationControlType(condensationControlType);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCondensationControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCondensationControlType();
  }

  double ZoneHVACLowTempRadiantVarFlow::condensationControlDewpointOffset() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->condensationControlDewpointOffset();
  }

  bool ZoneHVACLowTempRadiantVarFlow::isCondensationControlDewpointOffsetDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->isCondensationControlDewpointOffsetDefaulted();
  }

  bool ZoneHVACLowTempRadiantVarFlow::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
    return getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->setCondensationControlDewpointOffset(condensationControlDewpointOffset);
  }

  void ZoneHVACLowTempRadiantVarFlow::resetCondensationControlDewpointOffset() {
    getImpl<detail::ZoneHVACLowTempRadiantVarFlow_Impl>()->resetCondensationControlDewpointOffset();
  }

  namespace detail {

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingLength() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingLengthAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingLength(double hydronicTubingLength) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, hydronicTubingLength);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeHydronicTubingLength() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HydronicTubingLength, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHeatingDesignCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeHeatingDesignCapacity() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::HeatingDesignCapacity, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::maximumHotWaterFlow() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isMaximumHotWaterFlowAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setMaximumHotWaterFlow(double maximumHotWaterFlow) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, maximumHotWaterFlow);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeMaximumHotWaterFlow() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumHotWaterFlow, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::coolingDesignCapacity() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCoolingDesignCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingDesignCapacity(double coolingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, coolingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeCoolingDesignCapacity() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::maximumColdWaterFlow() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, true);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isMaximumColdWaterFlowAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setMaximumColdWaterFlow(double maximumColdWaterFlow) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, maximumColdWaterFlow);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::autosizeMaximumColdWaterFlow() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, "Autosize", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::numberofCircuits() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isNumberofCircuitsDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setNumberofCircuits(const std::string& numberofCircuits) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, numberofCircuits, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetNumberofCircuits() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::NumberofCircuits, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::circuitLength() const {
      auto value = getDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCircuitLengthDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength);
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCircuitLength(double circuitLength) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, circuitLength, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCircuitLength() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CircuitLength, "", false);
      OS_ASSERT(result);
    }

    namespace {
      constexpr const char* kDefaultFluidtoRadiantSurfaceHeatTransferModel = "ConvectionOnly";
      constexpr const char* kDefaultTemperatureControlType = "MeanAirTemperature";
      constexpr const char* kDefaultSetpointControlType = "HalfFlowPower";
      constexpr const char* kDefaultHeatingDesignCapacityMethod = "HeatingDesignCapacity";
      constexpr const char* kDefaultCoolingDesignCapacityMethod = "CoolingDesignCapacity";
      constexpr const char* kDefaultCondensationControlType = "SimpleOff";
      constexpr double kDefaultHydronicTubingInsideDiameter = 0.013;
      constexpr double kDefaultHydronicTubingOutsideDiameter = 0.016;
      constexpr double kDefaultHydronicTubingConductivity = 0.35;
      constexpr double kDefaultFractionofAutosizedHeatingDesignCapacity = 1.0;
      constexpr double kDefaultHeatingControlThrottlingRange = 0.5;
      constexpr double kDefaultCoolingControlThrottlingRange = 0.5;
      constexpr double kDefaultCondensationControlDewpointOffset = 1.0;
    }  // namespace

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
      return m_fluidtoRadiantSurfaceHeatTransferModel ? m_fluidtoRadiantSurfaceHeatTransferModel.get()
                                                      : kDefaultFluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
      return !m_fluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
      m_fluidtoRadiantSurfaceHeatTransferModel = fluidtoRadiantSurfaceHeatTransferModel;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
      m_fluidtoRadiantSurfaceHeatTransferModel = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingInsideDiameter() const {
      return m_hydronicTubingInsideDiameter ? m_hydronicTubingInsideDiameter.get() : kDefaultHydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingInsideDiameterDefaulted() const {
      return !m_hydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
      m_hydronicTubingInsideDiameter = hydronicTubingInsideDiameter;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHydronicTubingInsideDiameter() {
      m_hydronicTubingInsideDiameter = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingOutsideDiameter() const {
      return m_hydronicTubingOutsideDiameter ? m_hydronicTubingOutsideDiameter.get() : kDefaultHydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
      return !m_hydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
      m_hydronicTubingOutsideDiameter = hydronicTubingOutsideDiameter;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHydronicTubingOutsideDiameter() {
      m_hydronicTubingOutsideDiameter = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::hydronicTubingConductivity() const {
      return m_hydronicTubingConductivity ? m_hydronicTubingConductivity.get() : kDefaultHydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHydronicTubingConductivityDefaulted() const {
      return !m_hydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHydronicTubingConductivity(double hydronicTubingConductivity) {
      m_hydronicTubingConductivity = hydronicTubingConductivity;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHydronicTubingConductivity() {
      m_hydronicTubingConductivity = boost::none;
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::temperatureControlType() const {
      return m_temperatureControlType ? m_temperatureControlType.get() : kDefaultTemperatureControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isTemperatureControlTypeDefaulted() const {
      return !m_temperatureControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      m_temperatureControlType = temperatureControlType;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetTemperatureControlType() {
      m_temperatureControlType = boost::none;
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::setpointControlType() const {
      return m_setpointControlType ? m_setpointControlType.get() : kDefaultSetpointControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isSetpointControlTypeDefaulted() const {
      return !m_setpointControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setSetpointControlType(const std::string& setpointControlType) {
      m_setpointControlType = setpointControlType;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetSetpointControlType() {
      m_setpointControlType = boost::none;
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::heatingDesignCapacityMethod() const {
      return m_heatingDesignCapacityMethod ? m_heatingDesignCapacityMethod.get() : kDefaultHeatingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHeatingDesignCapacityMethodDefaulted() const {
      return !m_heatingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
      m_heatingDesignCapacityMethod = heatingDesignCapacityMethod;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingDesignCapacityMethod() {
      m_heatingDesignCapacityMethod = boost::none;
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::heatingDesignCapacityPerFloorArea() const {
      return m_heatingDesignCapacityPerFloorArea;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
      m_heatingDesignCapacityPerFloorArea = heatingDesignCapacityPerFloorArea;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingDesignCapacityPerFloorArea() {
      m_heatingDesignCapacityPerFloorArea = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      return m_fractionofAutosizedHeatingDesignCapacity ? m_fractionofAutosizedHeatingDesignCapacity.get()
                                                        : kDefaultFractionofAutosizedHeatingDesignCapacity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
      return !m_fractionofAutosizedHeatingDesignCapacity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
      m_fractionofAutosizedHeatingDesignCapacity = fractionofAutosizedHeatingDesignCapacity;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetFractionofAutosizedHeatingDesignCapacity() {
      m_fractionofAutosizedHeatingDesignCapacity = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::heatingControlThrottlingRange() const {
      return m_heatingControlThrottlingRange ? m_heatingControlThrottlingRange.get() : kDefaultHeatingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isHeatingControlThrottlingRangeDefaulted() const {
      return !m_heatingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setHeatingControlThrottlingRange(double heatingControlThrottlingRange) {
      m_heatingControlThrottlingRange = heatingControlThrottlingRange;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetHeatingControlThrottlingRange() {
      m_heatingControlThrottlingRange = boost::none;
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::coolingDesignCapacityMethod() const {
      return m_coolingDesignCapacityMethod ? m_coolingDesignCapacityMethod.get() : kDefaultCoolingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCoolingDesignCapacityMethodDefaulted() const {
      return !m_coolingDesignCapacityMethod;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod) {
      m_coolingDesignCapacityMethod = coolingDesignCapacityMethod;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingDesignCapacityMethod() {
      m_coolingDesignCapacityMethod = boost::none;
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::coolingDesignCapacityPerFloorArea() const {
      return m_coolingDesignCapacityPerFloorArea;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea) {
      m_coolingDesignCapacityPerFloorArea = coolingDesignCapacityPerFloorArea;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingDesignCapacityPerFloorArea() {
      m_coolingDesignCapacityPerFloorArea = boost::none;
    }

    boost::optional<double> ZoneHVACLowTempRadiantVarFlow_Impl::fractionofAutosizedCoolingDesignCapacity() const {
      return m_fractionofAutosizedCoolingDesignCapacity;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity) {
      m_fractionofAutosizedCoolingDesignCapacity = fractionofAutosizedCoolingDesignCapacity;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetFractionofAutosizedCoolingDesignCapacity() {
      m_fractionofAutosizedCoolingDesignCapacity = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::coolingControlThrottlingRange() const {
      return m_coolingControlThrottlingRange ? m_coolingControlThrottlingRange.get() : kDefaultCoolingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCoolingControlThrottlingRangeDefaulted() const {
      return !m_coolingControlThrottlingRange;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCoolingControlThrottlingRange(double coolingControlThrottlingRange) {
      m_coolingControlThrottlingRange = coolingControlThrottlingRange;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCoolingControlThrottlingRange() {
      m_coolingControlThrottlingRange = boost::none;
    }

    std::string ZoneHVACLowTempRadiantVarFlow_Impl::condensationControlType() const {
      return m_condensationControlType ? m_condensationControlType.get() : kDefaultCondensationControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCondensationControlTypeDefaulted() const {
      return !m_condensationControlType;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCondensationControlType(const std::string& condensationControlType) {
      m_condensationControlType = condensationControlType;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCondensationControlType() {
      m_condensationControlType = boost::none;
    }

    double ZoneHVACLowTempRadiantVarFlow_Impl::condensationControlDewpointOffset() const {
      return m_condensationControlDewpointOffset ? m_condensationControlDewpointOffset.get() : kDefaultCondensationControlDewpointOffset;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::isCondensationControlDewpointOffsetDefaulted() const {
      return !m_condensationControlDewpointOffset;
    }

    bool ZoneHVACLowTempRadiantVarFlow_Impl::setCondensationControlDewpointOffset(double condensationControlDewpointOffset) {
      m_condensationControlDewpointOffset = condensationControlDewpointOffset;
      return true;
    }

    void ZoneHVACLowTempRadiantVarFlow_Impl::resetCondensationControlDewpointOffset() {
      m_condensationControlDewpointOffset = boost::none;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
