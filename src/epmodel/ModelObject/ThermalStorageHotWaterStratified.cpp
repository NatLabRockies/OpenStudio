/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermalStorageHotWaterStratified.hpp"
#include "ThermalStorageHotWaterStratified_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ThermalStorage_HotWater_Stratified_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  ThermalStorageHotWaterStratified::ThermalStorageHotWaterStratified(const Model& model)
    : ModelObject(ThermalStorageHotWaterStratified::iddObjectType(), model) {}

  ThermalStorageHotWaterStratified::ThermalStorageHotWaterStratified(std::shared_ptr<detail::ThermalStorageHotWaterStratified_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ThermalStorageHotWaterStratified::iddObjectType() {
    return IddObjectType::ThermalStorage_HotWater_Stratified;
  }

  std::vector<std::string> ThermalStorageHotWaterStratified::tankShapeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ThermalStorage_HotWater_StratifiedFields::TankShape);
  }

  std::vector<std::string> ThermalStorageHotWaterStratified::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ThermalStorage_HotWater_StratifiedFields::AmbientTemperatureIndicator);
  }

  std::vector<std::string> ThermalStorageHotWaterStratified::inletModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ThermalStorage_HotWater_StratifiedFields::InletMode);
  }

  double ThermalStorageHotWaterStratified::tankVolume() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->tankVolume();
  }

  bool ThermalStorageHotWaterStratified::setTankVolume(double tankVolume) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setTankVolume(tankVolume);
  }

  double ThermalStorageHotWaterStratified::tankHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->tankHeight();
  }

  bool ThermalStorageHotWaterStratified::setTankHeight(double tankHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setTankHeight(tankHeight);
  }

  std::string ThermalStorageHotWaterStratified::tankShape() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->tankShape();
  }

  bool ThermalStorageHotWaterStratified::setTankShape(const std::string& tankShape) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setTankShape(tankShape);
  }

  bool ThermalStorageHotWaterStratified::isTankShapeDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isTankShapeDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetTankShape() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetTankShape();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::tankPerimeter() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->tankPerimeter();
  }

  bool ThermalStorageHotWaterStratified::setTankPerimeter(double tankPerimeter) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setTankPerimeter(tankPerimeter);
  }

  void ThermalStorageHotWaterStratified::resetTankPerimeter() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetTankPerimeter();
  }

  double ThermalStorageHotWaterStratified::deadbandTemperatureDifference() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->deadbandTemperatureDifference();
  }

  bool ThermalStorageHotWaterStratified::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setDeadbandTemperatureDifference(deadbandTemperatureDifference);
  }

  bool ThermalStorageHotWaterStratified::isDeadbandTemperatureDifferenceDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isDeadbandTemperatureDifferenceDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetDeadbandTemperatureDifference() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetDeadbandTemperatureDifference();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::topTemperatureSensorHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->topTemperatureSensorHeight();
  }

  bool ThermalStorageHotWaterStratified::setTopTemperatureSensorHeight(double topTemperatureSensorHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setTopTemperatureSensorHeight(topTemperatureSensorHeight);
  }

  void ThermalStorageHotWaterStratified::resetTopTemperatureSensorHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetTopTemperatureSensorHeight();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::bottomTemperatureSensorHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->bottomTemperatureSensorHeight();
  }

  bool ThermalStorageHotWaterStratified::setBottomTemperatureSensorHeight(double bottomTemperatureSensorHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setBottomTemperatureSensorHeight(bottomTemperatureSensorHeight);
  }

  void ThermalStorageHotWaterStratified::resetBottomTemperatureSensorHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetBottomTemperatureSensorHeight();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::maximumTemperatureLimit() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->maximumTemperatureLimit();
  }

  bool ThermalStorageHotWaterStratified::setMaximumTemperatureLimit(double maximumTemperatureLimit) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setMaximumTemperatureLimit(maximumTemperatureLimit);
  }

  void ThermalStorageHotWaterStratified::resetMaximumTemperatureLimit() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetMaximumTemperatureLimit();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::nominalHeatingCapacity() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->nominalHeatingCapacity();
  }

  bool ThermalStorageHotWaterStratified::setNominalHeatingCapacity(double nominalHeatingCapacity) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNominalHeatingCapacity(nominalHeatingCapacity);
  }

  bool ThermalStorageHotWaterStratified::isNominalHeatingCapacityDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNominalHeatingCapacityDefaulted();
  }

  bool ThermalStorageHotWaterStratified::isNominalHeatingCapacityAutosized() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNominalHeatingCapacityAutosized();
  }

  void ThermalStorageHotWaterStratified::resetNominalHeatingCapacity() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNominalHeatingCapacity();
  }

  void ThermalStorageHotWaterStratified::autosizeNominalHeatingCapacity() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->autosizeNominalHeatingCapacity();
  }

  std::string ThermalStorageHotWaterStratified::ambientTemperatureIndicator() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->ambientTemperatureIndicator();
  }

  bool ThermalStorageHotWaterStratified::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setAmbientTemperatureIndicator(ambientTemperatureIndicator);
  }

  boost::optional<double> ThermalStorageHotWaterStratified::uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature();
  }

  bool ThermalStorageHotWaterStratified::setUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature(
    double uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature(
      uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature);
  }

  void ThermalStorageHotWaterStratified::resetUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature();
  }

  boost::optional<std::string> ThermalStorageHotWaterStratified::useSideFlowDirectionSchedule() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->useSideFlowDirectionSchedule();
  }

  bool ThermalStorageHotWaterStratified::setUseSideFlowDirectionSchedule(const std::string& useSideFlowDirectionSchedule) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setUseSideFlowDirectionSchedule(useSideFlowDirectionSchedule);
  }

  void ThermalStorageHotWaterStratified::resetUseSideFlowDirectionSchedule() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetUseSideFlowDirectionSchedule();
  }

  double ThermalStorageHotWaterStratified::useSideHeatTransferEffectiveness() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->useSideHeatTransferEffectiveness();
  }

  bool ThermalStorageHotWaterStratified::setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setUseSideHeatTransferEffectiveness(useSideHeatTransferEffectiveness);
  }

  bool ThermalStorageHotWaterStratified::isUseSideHeatTransferEffectivenessDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isUseSideHeatTransferEffectivenessDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetUseSideHeatTransferEffectiveness() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetUseSideHeatTransferEffectiveness();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::useSideInletHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->useSideInletHeight();
  }

  bool ThermalStorageHotWaterStratified::setUseSideInletHeight(double useSideInletHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setUseSideInletHeight(useSideInletHeight);
  }

  bool ThermalStorageHotWaterStratified::isUseSideInletHeightDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isUseSideInletHeightDefaulted();
  }

  bool ThermalStorageHotWaterStratified::isUseSideInletHeightAutocalculated() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isUseSideInletHeightAutocalculated();
  }

  void ThermalStorageHotWaterStratified::resetUseSideInletHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetUseSideInletHeight();
  }

  void ThermalStorageHotWaterStratified::autocalculateUseSideInletHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->autocalculateUseSideInletHeight();
  }

  double ThermalStorageHotWaterStratified::useSideOutletHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->useSideOutletHeight();
  }

  bool ThermalStorageHotWaterStratified::setUseSideOutletHeight(double useSideOutletHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setUseSideOutletHeight(useSideOutletHeight);
  }

  bool ThermalStorageHotWaterStratified::isUseSideOutletHeightDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isUseSideOutletHeightDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetUseSideOutletHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetUseSideOutletHeight();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::useSideDesignFlowRate() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->useSideDesignFlowRate();
  }

  bool ThermalStorageHotWaterStratified::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setUseSideDesignFlowRate(useSideDesignFlowRate);
  }

  bool ThermalStorageHotWaterStratified::isUseSideDesignFlowRateDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isUseSideDesignFlowRateDefaulted();
  }

  bool ThermalStorageHotWaterStratified::isUseSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isUseSideDesignFlowRateAutosized();
  }

  void ThermalStorageHotWaterStratified::resetUseSideDesignFlowRate() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetUseSideDesignFlowRate();
  }

  void ThermalStorageHotWaterStratified::autosizeUseSideDesignFlowRate() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->autosizeUseSideDesignFlowRate();
  }

  boost::optional<std::string> ThermalStorageHotWaterStratified::sourceSideFlowDirectionSchedule() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->sourceSideFlowDirectionSchedule();
  }

  bool ThermalStorageHotWaterStratified::setSourceSideFlowDirectionSchedule(const std::string& sourceSideFlowDirectionSchedule) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setSourceSideFlowDirectionSchedule(sourceSideFlowDirectionSchedule);
  }

  void ThermalStorageHotWaterStratified::resetSourceSideFlowDirectionSchedule() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetSourceSideFlowDirectionSchedule();
  }

  double ThermalStorageHotWaterStratified::sourceSideHeatTransferEffectiveness() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->sourceSideHeatTransferEffectiveness();
  }

  bool ThermalStorageHotWaterStratified::setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setSourceSideHeatTransferEffectiveness(sourceSideHeatTransferEffectiveness);
  }

  bool ThermalStorageHotWaterStratified::isSourceSideHeatTransferEffectivenessDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isSourceSideHeatTransferEffectivenessDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetSourceSideHeatTransferEffectiveness() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetSourceSideHeatTransferEffectiveness();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::sourceSideInletHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->sourceSideInletHeight();
  }

  bool ThermalStorageHotWaterStratified::setSourceSideInletHeight(double sourceSideInletHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setSourceSideInletHeight(sourceSideInletHeight);
  }

  bool ThermalStorageHotWaterStratified::isSourceSideInletHeightDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isSourceSideInletHeightDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetSourceSideInletHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetSourceSideInletHeight();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::sourceSideOutletHeight() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->sourceSideOutletHeight();
  }

  bool ThermalStorageHotWaterStratified::setSourceSideOutletHeight(double sourceSideOutletHeight) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setSourceSideOutletHeight(sourceSideOutletHeight);
  }

  bool ThermalStorageHotWaterStratified::isSourceSideOutletHeightDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isSourceSideOutletHeightDefaulted();
  }

  bool ThermalStorageHotWaterStratified::isSourceSideOutletHeightAutocalculated() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isSourceSideOutletHeightAutocalculated();
  }

  void ThermalStorageHotWaterStratified::resetSourceSideOutletHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetSourceSideOutletHeight();
  }

  void ThermalStorageHotWaterStratified::autocalculateSourceSideOutletHeight() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->autocalculateSourceSideOutletHeight();
  }

  boost::optional<double> ThermalStorageHotWaterStratified::sourceSideDesignFlowRate() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->sourceSideDesignFlowRate();
  }

  bool ThermalStorageHotWaterStratified::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setSourceSideDesignFlowRate(sourceSideDesignFlowRate);
  }

  bool ThermalStorageHotWaterStratified::isSourceSideDesignFlowRateDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isSourceSideDesignFlowRateDefaulted();
  }

  bool ThermalStorageHotWaterStratified::isSourceSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isSourceSideDesignFlowRateAutosized();
  }

  void ThermalStorageHotWaterStratified::resetSourceSideDesignFlowRate() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetSourceSideDesignFlowRate();
  }

  void ThermalStorageHotWaterStratified::autosizeSourceSideDesignFlowRate() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->autosizeSourceSideDesignFlowRate();
  }

  double ThermalStorageHotWaterStratified::tankRecoveryTime() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->tankRecoveryTime();
  }

  bool ThermalStorageHotWaterStratified::setTankRecoveryTime(double tankRecoveryTime) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setTankRecoveryTime(tankRecoveryTime);
  }

  bool ThermalStorageHotWaterStratified::isTankRecoveryTimeDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isTankRecoveryTimeDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetTankRecoveryTime() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetTankRecoveryTime();
  }

  std::string ThermalStorageHotWaterStratified::inletMode() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->inletMode();
  }

  bool ThermalStorageHotWaterStratified::setInletMode(const std::string& inletMode) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setInletMode(inletMode);
  }

  bool ThermalStorageHotWaterStratified::isInletModeDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isInletModeDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetInletMode() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetInletMode();
  }

  int ThermalStorageHotWaterStratified::numberOfNodes() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->numberOfNodes();
  }

  bool ThermalStorageHotWaterStratified::setNumberOfNodes(int numberOfNodes) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNumberOfNodes(numberOfNodes);
  }

  bool ThermalStorageHotWaterStratified::isNumberOfNodesDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNumberOfNodesDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNumberOfNodes() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNumberOfNodes();
  }

  double ThermalStorageHotWaterStratified::additionalDestratificationConductivity() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->additionalDestratificationConductivity();
  }

  bool ThermalStorageHotWaterStratified::setAdditionalDestratificationConductivity(double additionalDestratificationConductivity) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setAdditionalDestratificationConductivity(
      additionalDestratificationConductivity);
  }

  bool ThermalStorageHotWaterStratified::isAdditionalDestratificationConductivityDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isAdditionalDestratificationConductivityDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetAdditionalDestratificationConductivity() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetAdditionalDestratificationConductivity();
  }

  double ThermalStorageHotWaterStratified::node1AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node1AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode1AdditionalLossCoefficient(node1AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode1AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode1AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode1AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode1AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node2AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node2AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode2AdditionalLossCoefficient(node2AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode2AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode2AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode2AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode2AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node3AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node3AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode3AdditionalLossCoefficient(node3AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode3AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode3AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode3AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode3AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node4AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node4AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode4AdditionalLossCoefficient(node4AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode4AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode4AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode4AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode4AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node5AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node5AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode5AdditionalLossCoefficient(node5AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode5AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode5AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode5AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode5AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node6AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node6AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode6AdditionalLossCoefficient(node6AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode6AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode6AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode6AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode6AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node7AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node7AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode7AdditionalLossCoefficient(node7AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode7AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode7AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode7AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode7AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node8AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node8AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode8AdditionalLossCoefficient(node8AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode8AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode8AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode8AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode8AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node9AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node9AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode9AdditionalLossCoefficient(node9AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode9AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode9AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode9AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode9AdditionalLossCoefficient();
  }

  double ThermalStorageHotWaterStratified::node10AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->node10AdditionalLossCoefficient();
  }

  bool ThermalStorageHotWaterStratified::setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->setNode10AdditionalLossCoefficient(node10AdditionalLossCoefficient);
  }

  bool ThermalStorageHotWaterStratified::isNode10AdditionalLossCoefficientDefaulted() const {
    return getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->isNode10AdditionalLossCoefficientDefaulted();
  }

  void ThermalStorageHotWaterStratified::resetNode10AdditionalLossCoefficient() {
    getImpl<detail::ThermalStorageHotWaterStratified_Impl>()->resetNode10AdditionalLossCoefficient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ThermalStorageHotWaterStratified_Impl::tankVolume() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::TankVolume, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setTankVolume(double tankVolume) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::TankVolume, tankVolume);
    }

    double ThermalStorageHotWaterStratified_Impl::tankHeight() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::TankHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setTankHeight(double tankHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::TankHeight, tankHeight);
    }

    std::string ThermalStorageHotWaterStratified_Impl::tankShape() const {
      const auto value = getString(ThermalStorage_HotWater_StratifiedFields::TankShape, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setTankShape(const std::string& tankShape) {
      return setString(ThermalStorage_HotWater_StratifiedFields::TankShape, tankShape);
    }

    bool ThermalStorageHotWaterStratified_Impl::isTankShapeDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::TankShape);
    }

    void ThermalStorageHotWaterStratified_Impl::resetTankShape() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::TankShape, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::tankPerimeter() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::TankPerimeter, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setTankPerimeter(double tankPerimeter) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::TankPerimeter, tankPerimeter);
    }

    void ThermalStorageHotWaterStratified_Impl::resetTankPerimeter() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::TankPerimeter, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::deadbandTemperatureDifference() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::DeadbandTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::DeadbandTemperatureDifference, deadbandTemperatureDifference);
    }

    bool ThermalStorageHotWaterStratified_Impl::isDeadbandTemperatureDifferenceDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::DeadbandTemperatureDifference);
    }

    void ThermalStorageHotWaterStratified_Impl::resetDeadbandTemperatureDifference() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::DeadbandTemperatureDifference, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::topTemperatureSensorHeight() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::TopTemperatureSensorHeight, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setTopTemperatureSensorHeight(double topTemperatureSensorHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::TopTemperatureSensorHeight, topTemperatureSensorHeight);
    }

    void ThermalStorageHotWaterStratified_Impl::resetTopTemperatureSensorHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::TopTemperatureSensorHeight, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::bottomTemperatureSensorHeight() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::BottomTemperatureSensorHeight, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setBottomTemperatureSensorHeight(double bottomTemperatureSensorHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::BottomTemperatureSensorHeight, bottomTemperatureSensorHeight);
    }

    void ThermalStorageHotWaterStratified_Impl::resetBottomTemperatureSensorHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::BottomTemperatureSensorHeight, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::maximumTemperatureLimit() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::MaximumTemperatureLimit, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setMaximumTemperatureLimit(double maximumTemperatureLimit) {
      const bool result = setDouble(ThermalStorage_HotWater_StratifiedFields::MaximumTemperatureLimit, maximumTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void ThermalStorageHotWaterStratified_Impl::resetMaximumTemperatureLimit() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::MaximumTemperatureLimit, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::nominalHeatingCapacity() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::NominalHeatingCapacity, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setNominalHeatingCapacity(double nominalHeatingCapacity) {
      const bool result = setDouble(ThermalStorage_HotWater_StratifiedFields::NominalHeatingCapacity, nominalHeatingCapacity);
      OS_ASSERT(result);
      return result;
    }

    bool ThermalStorageHotWaterStratified_Impl::isNominalHeatingCapacityDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::NominalHeatingCapacity);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNominalHeatingCapacityAutosized() const {
      if (auto value = getString(ThermalStorage_HotWater_StratifiedFields::NominalHeatingCapacity, true)) {
        return istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageHotWaterStratified_Impl::resetNominalHeatingCapacity() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::NominalHeatingCapacity, ""));
    }

    void ThermalStorageHotWaterStratified_Impl::autosizeNominalHeatingCapacity() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::NominalHeatingCapacity, "autosize"));
    }

    std::string ThermalStorageHotWaterStratified_Impl::ambientTemperatureIndicator() const {
      const auto value = getString(ThermalStorage_HotWater_StratifiedFields::AmbientTemperatureIndicator, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      return setString(ThermalStorage_HotWater_StratifiedFields::AmbientTemperatureIndicator, ambientTemperatureIndicator);
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature(
      double uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature,
                       uniformSkinLossCoefficientPerUnitAreaToAmbientTemperature);
    }

    void ThermalStorageHotWaterStratified_Impl::resetUniformSkinLossCoefficientPerUnitAreaToAmbientTemperature() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, ""));
    }

    boost::optional<std::string> ThermalStorageHotWaterStratified_Impl::useSideFlowDirectionSchedule() const {
      return getString(ThermalStorage_HotWater_StratifiedFields::UseSideFlowDirectionSchedule, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setUseSideFlowDirectionSchedule(const std::string& useSideFlowDirectionSchedule) {
      return setString(ThermalStorage_HotWater_StratifiedFields::UseSideFlowDirectionSchedule, useSideFlowDirectionSchedule);
    }

    void ThermalStorageHotWaterStratified_Impl::resetUseSideFlowDirectionSchedule() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideFlowDirectionSchedule, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::useSideHeatTransferEffectiveness() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::UseSideHeatTransferEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::UseSideHeatTransferEffectiveness, useSideHeatTransferEffectiveness);
    }

    bool ThermalStorageHotWaterStratified_Impl::isUseSideHeatTransferEffectivenessDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::UseSideHeatTransferEffectiveness);
    }

    void ThermalStorageHotWaterStratified_Impl::resetUseSideHeatTransferEffectiveness() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideHeatTransferEffectiveness, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::useSideInletHeight() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::UseSideInletHeight, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setUseSideInletHeight(double useSideInletHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::UseSideInletHeight, useSideInletHeight);
    }

    bool ThermalStorageHotWaterStratified_Impl::isUseSideInletHeightDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::UseSideInletHeight);
    }

    bool ThermalStorageHotWaterStratified_Impl::isUseSideInletHeightAutocalculated() const {
      if (auto value = getString(ThermalStorage_HotWater_StratifiedFields::UseSideInletHeight, true)) {
        return istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void ThermalStorageHotWaterStratified_Impl::resetUseSideInletHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideInletHeight, ""));
    }

    void ThermalStorageHotWaterStratified_Impl::autocalculateUseSideInletHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideInletHeight, "autocalculate"));
    }

    double ThermalStorageHotWaterStratified_Impl::useSideOutletHeight() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::UseSideOutletHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setUseSideOutletHeight(double useSideOutletHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::UseSideOutletHeight, useSideOutletHeight);
    }

    bool ThermalStorageHotWaterStratified_Impl::isUseSideOutletHeightDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::UseSideOutletHeight);
    }

    void ThermalStorageHotWaterStratified_Impl::resetUseSideOutletHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideOutletHeight, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::useSideDesignFlowRate() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::UseSideDesignFlowRate, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::UseSideDesignFlowRate, useSideDesignFlowRate);
    }

    bool ThermalStorageHotWaterStratified_Impl::isUseSideDesignFlowRateDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::UseSideDesignFlowRate);
    }

    bool ThermalStorageHotWaterStratified_Impl::isUseSideDesignFlowRateAutosized() const {
      if (auto value = getString(ThermalStorage_HotWater_StratifiedFields::UseSideDesignFlowRate, true)) {
        return istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageHotWaterStratified_Impl::resetUseSideDesignFlowRate() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideDesignFlowRate, ""));
    }

    void ThermalStorageHotWaterStratified_Impl::autosizeUseSideDesignFlowRate() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::UseSideDesignFlowRate, "autosize"));
    }

    boost::optional<std::string> ThermalStorageHotWaterStratified_Impl::sourceSideFlowDirectionSchedule() const {
      return getString(ThermalStorage_HotWater_StratifiedFields::SourceSideFlowDirectionSchedule, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setSourceSideFlowDirectionSchedule(const std::string& sourceSideFlowDirectionSchedule) {
      return setString(ThermalStorage_HotWater_StratifiedFields::SourceSideFlowDirectionSchedule, sourceSideFlowDirectionSchedule);
    }

    void ThermalStorageHotWaterStratified_Impl::resetSourceSideFlowDirectionSchedule() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideFlowDirectionSchedule, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::sourceSideHeatTransferEffectiveness() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideHeatTransferEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideHeatTransferEffectiveness, sourceSideHeatTransferEffectiveness);
    }

    bool ThermalStorageHotWaterStratified_Impl::isSourceSideHeatTransferEffectivenessDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::SourceSideHeatTransferEffectiveness);
    }

    void ThermalStorageHotWaterStratified_Impl::resetSourceSideHeatTransferEffectiveness() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideHeatTransferEffectiveness, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::sourceSideInletHeight() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideInletHeight, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setSourceSideInletHeight(double sourceSideInletHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideInletHeight, sourceSideInletHeight);
    }

    bool ThermalStorageHotWaterStratified_Impl::isSourceSideInletHeightDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::SourceSideInletHeight);
    }

    void ThermalStorageHotWaterStratified_Impl::resetSourceSideInletHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideInletHeight, ""));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::sourceSideOutletHeight() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideOutletHeight, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setSourceSideOutletHeight(double sourceSideOutletHeight) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideOutletHeight, sourceSideOutletHeight);
    }

    bool ThermalStorageHotWaterStratified_Impl::isSourceSideOutletHeightDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::SourceSideOutletHeight);
    }

    bool ThermalStorageHotWaterStratified_Impl::isSourceSideOutletHeightAutocalculated() const {
      if (auto value = getString(ThermalStorage_HotWater_StratifiedFields::SourceSideOutletHeight, true)) {
        return istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void ThermalStorageHotWaterStratified_Impl::resetSourceSideOutletHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideOutletHeight, ""));
    }

    void ThermalStorageHotWaterStratified_Impl::autocalculateSourceSideOutletHeight() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideOutletHeight, "autocalculate"));
    }

    boost::optional<double> ThermalStorageHotWaterStratified_Impl::sourceSideDesignFlowRate() const {
      return getDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideDesignFlowRate, true);
    }

    bool ThermalStorageHotWaterStratified_Impl::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::SourceSideDesignFlowRate, sourceSideDesignFlowRate);
    }

    bool ThermalStorageHotWaterStratified_Impl::isSourceSideDesignFlowRateDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::SourceSideDesignFlowRate);
    }

    bool ThermalStorageHotWaterStratified_Impl::isSourceSideDesignFlowRateAutosized() const {
      if (auto value = getString(ThermalStorage_HotWater_StratifiedFields::SourceSideDesignFlowRate, true)) {
        return istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageHotWaterStratified_Impl::resetSourceSideDesignFlowRate() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideDesignFlowRate, ""));
    }

    void ThermalStorageHotWaterStratified_Impl::autosizeSourceSideDesignFlowRate() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::SourceSideDesignFlowRate, "autosize"));
    }

    double ThermalStorageHotWaterStratified_Impl::tankRecoveryTime() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::TankRecoveryTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setTankRecoveryTime(double tankRecoveryTime) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::TankRecoveryTime, tankRecoveryTime);
    }

    bool ThermalStorageHotWaterStratified_Impl::isTankRecoveryTimeDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::TankRecoveryTime);
    }

    void ThermalStorageHotWaterStratified_Impl::resetTankRecoveryTime() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::TankRecoveryTime, ""));
    }

    std::string ThermalStorageHotWaterStratified_Impl::inletMode() const {
      const auto value = getString(ThermalStorage_HotWater_StratifiedFields::InletMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setInletMode(const std::string& inletMode) {
      return setString(ThermalStorage_HotWater_StratifiedFields::InletMode, inletMode);
    }

    bool ThermalStorageHotWaterStratified_Impl::isInletModeDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::InletMode);
    }

    void ThermalStorageHotWaterStratified_Impl::resetInletMode() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::InletMode, ""));
    }

    int ThermalStorageHotWaterStratified_Impl::numberOfNodes() const {
      const auto value = getInt(ThermalStorage_HotWater_StratifiedFields::NumberofNodes, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNumberOfNodes(int numberOfNodes) {
      return setInt(ThermalStorage_HotWater_StratifiedFields::NumberofNodes, numberOfNodes);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNumberOfNodesDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::NumberofNodes);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNumberOfNodes() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::NumberofNodes, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::additionalDestratificationConductivity() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::AdditionalDestratificationConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setAdditionalDestratificationConductivity(double additionalDestratificationConductivity) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::AdditionalDestratificationConductivity, additionalDestratificationConductivity);
    }

    bool ThermalStorageHotWaterStratified_Impl::isAdditionalDestratificationConductivityDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::AdditionalDestratificationConductivity);
    }

    void ThermalStorageHotWaterStratified_Impl::resetAdditionalDestratificationConductivity() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::AdditionalDestratificationConductivity, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node1AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node1AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node1AdditionalLossCoefficient, node1AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode1AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node1AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode1AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node1AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node2AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node2AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node2AdditionalLossCoefficient, node2AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode2AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node2AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode2AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node2AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node3AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node3AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node3AdditionalLossCoefficient, node3AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode3AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node3AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode3AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node3AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node4AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node4AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node4AdditionalLossCoefficient, node4AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode4AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node4AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode4AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node4AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node5AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node5AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node5AdditionalLossCoefficient, node5AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode5AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node5AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode5AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node5AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node6AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node6AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node6AdditionalLossCoefficient, node6AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode6AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node6AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode6AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node6AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node7AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node7AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node7AdditionalLossCoefficient, node7AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode7AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node7AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode7AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node7AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node8AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node8AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node8AdditionalLossCoefficient, node8AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode8AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node8AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode8AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node8AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node9AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node9AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node9AdditionalLossCoefficient, node9AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode9AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node9AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode9AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node9AdditionalLossCoefficient, ""));
    }

    double ThermalStorageHotWaterStratified_Impl::node10AdditionalLossCoefficient() const {
      const auto value = getDouble(ThermalStorage_HotWater_StratifiedFields::Node10AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageHotWaterStratified_Impl::setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient) {
      return setDouble(ThermalStorage_HotWater_StratifiedFields::Node10AdditionalLossCoefficient, node10AdditionalLossCoefficient);
    }

    bool ThermalStorageHotWaterStratified_Impl::isNode10AdditionalLossCoefficientDefaulted() const {
      return isEmpty(ThermalStorage_HotWater_StratifiedFields::Node10AdditionalLossCoefficient);
    }

    void ThermalStorageHotWaterStratified_Impl::resetNode10AdditionalLossCoefficient() {
      OS_ASSERT(setString(ThermalStorage_HotWater_StratifiedFields::Node10AdditionalLossCoefficient, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
