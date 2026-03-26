/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ThermalStorageChilledWaterStratified.hpp"
#include "WaterToWaterComponent/ThermalStorageChilledWaterStratified_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermalStorageChilledWaterStratified::ThermalStorageChilledWaterStratified(const Model& model)
    : WaterToWaterComponent(ThermalStorageChilledWaterStratified::iddObjectType(), model) {}

  ThermalStorageChilledWaterStratified::ThermalStorageChilledWaterStratified(std::shared_ptr<detail::ThermalStorageChilledWaterStratified_Impl> impl)
    : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType ThermalStorageChilledWaterStratified::iddObjectType() {
    return IddObjectType::ThermalStorage_ChilledWater_Stratified;
  }

  std::vector<std::string> ThermalStorageChilledWaterStratified::tankShapeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankShape);
  }

  std::vector<std::string> ThermalStorageChilledWaterStratified::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureIndicator);
  }

  std::vector<std::string> ThermalStorageChilledWaterStratified::inletModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_ChilledWater_StratifiedFields::InletMode);
  }

  double ThermalStorageChilledWaterStratified::tankVolume() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->tankVolume();
  }

  bool ThermalStorageChilledWaterStratified::setTankVolume(double tankVolume) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setTankVolume(tankVolume);
  }

  double ThermalStorageChilledWaterStratified::tankHeight() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->tankHeight();
  }

  bool ThermalStorageChilledWaterStratified::setTankHeight(double tankHeight) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setTankHeight(tankHeight);
  }

  std::string ThermalStorageChilledWaterStratified::tankShape() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->tankShape();
  }

  bool ThermalStorageChilledWaterStratified::setTankShape(const std::string& tankShape) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setTankShape(tankShape);
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::tankPerimeter() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->tankPerimeter();
  }

  bool ThermalStorageChilledWaterStratified::setTankPerimeter(double tankPerimeter) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setTankPerimeter(tankPerimeter);
  }

  void ThermalStorageChilledWaterStratified::resetTankPerimeter() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetTankPerimeter();
  }

  double ThermalStorageChilledWaterStratified::deadbandTemperatureDifference() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->deadbandTemperatureDifference();
  }

  bool ThermalStorageChilledWaterStratified::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setDeadbandTemperatureDifference(deadbandTemperatureDifference);
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::temperatureSensorHeight() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->temperatureSensorHeight();
  }

  bool ThermalStorageChilledWaterStratified::setTemperatureSensorHeight(double temperatureSensorHeight) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setTemperatureSensorHeight(temperatureSensorHeight);
  }

  void ThermalStorageChilledWaterStratified::resetTemperatureSensorHeight() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetTemperatureSensorHeight();
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::minimumTemperatureLimit() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->minimumTemperatureLimit();
  }

  bool ThermalStorageChilledWaterStratified::setMinimumTemperatureLimit(double minimumTemperatureLimit) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setMinimumTemperatureLimit(minimumTemperatureLimit);
  }

  void ThermalStorageChilledWaterStratified::resetMinimumTemperatureLimit() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetMinimumTemperatureLimit();
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::nominalCoolingCapacity() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->nominalCoolingCapacity();
  }

  bool ThermalStorageChilledWaterStratified::setNominalCoolingCapacity(double nominalCoolingCapacity) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNominalCoolingCapacity(nominalCoolingCapacity);
  }

  bool ThermalStorageChilledWaterStratified::isNominalCoolingCapacityAutosized() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isNominalCoolingCapacityAutosized();
  }

  void ThermalStorageChilledWaterStratified::autosizeNominalCoolingCapacity() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->autosizeNominalCoolingCapacity();
  }

  std::string ThermalStorageChilledWaterStratified::ambientTemperatureIndicator() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->ambientTemperatureIndicator();
  }

  bool ThermalStorageChilledWaterStratified::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setAmbientTemperatureIndicator(ambientTemperatureIndicator);
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->uniformSkinLossCoefficientperUnitAreatoAmbientTemperature();
  }

  bool ThermalStorageChilledWaterStratified::setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(
    double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(
      uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
  }

  void ThermalStorageChilledWaterStratified::resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();
  }

  double ThermalStorageChilledWaterStratified::useSideHeatTransferEffectiveness() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->useSideHeatTransferEffectiveness();
  }

  bool ThermalStorageChilledWaterStratified::setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setUseSideHeatTransferEffectiveness(useSideHeatTransferEffectiveness);
  }

  bool ThermalStorageChilledWaterStratified::isUseSideHeatTransferEffectivenessDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isUseSideHeatTransferEffectivenessDefaulted();
  }

  void ThermalStorageChilledWaterStratified::resetUseSideHeatTransferEffectiveness() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetUseSideHeatTransferEffectiveness();
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::useSideInletHeight() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->useSideInletHeight();
  }

  bool ThermalStorageChilledWaterStratified::setUseSideInletHeight(double useSideInletHeight) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setUseSideInletHeight(useSideInletHeight);
  }

  bool ThermalStorageChilledWaterStratified::isUseSideInletHeightAutocalculated() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isUseSideInletHeightAutocalculated();
  }

  void ThermalStorageChilledWaterStratified::autocalculateUseSideInletHeight() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->autocalculateUseSideInletHeight();
  }

  double ThermalStorageChilledWaterStratified::useSideOutletHeight() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->useSideOutletHeight();
  }

  bool ThermalStorageChilledWaterStratified::setUseSideOutletHeight(double useSideOutletHeight) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setUseSideOutletHeight(useSideOutletHeight);
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::useSideDesignFlowRate() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->useSideDesignFlowRate();
  }

  bool ThermalStorageChilledWaterStratified::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setUseSideDesignFlowRate(useSideDesignFlowRate);
  }

  bool ThermalStorageChilledWaterStratified::isUseSideDesignFlowRateDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isUseSideDesignFlowRateDefaulted();
  }

  bool ThermalStorageChilledWaterStratified::isUseSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isUseSideDesignFlowRateAutosized();
  }

  void ThermalStorageChilledWaterStratified::resetUseSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetUseSideDesignFlowRate();
  }

  void ThermalStorageChilledWaterStratified::autosizeUseSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->autosizeUseSideDesignFlowRate();
  }

  double ThermalStorageChilledWaterStratified::sourceSideHeatTransferEffectiveness() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->sourceSideHeatTransferEffectiveness();
  }

  bool ThermalStorageChilledWaterStratified::setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setSourceSideHeatTransferEffectiveness(sourceSideHeatTransferEffectiveness);
  }

  bool ThermalStorageChilledWaterStratified::isSourceSideHeatTransferEffectivenessDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isSourceSideHeatTransferEffectivenessDefaulted();
  }

  void ThermalStorageChilledWaterStratified::resetSourceSideHeatTransferEffectiveness() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetSourceSideHeatTransferEffectiveness();
  }

  double ThermalStorageChilledWaterStratified::sourceSideInletHeight() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->sourceSideInletHeight();
  }

  bool ThermalStorageChilledWaterStratified::setSourceSideInletHeight(double sourceSideInletHeight) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setSourceSideInletHeight(sourceSideInletHeight);
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::sourceSideOutletHeight() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->sourceSideOutletHeight();
  }

  bool ThermalStorageChilledWaterStratified::setSourceSideOutletHeight(double sourceSideOutletHeight) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setSourceSideOutletHeight(sourceSideOutletHeight);
  }

  bool ThermalStorageChilledWaterStratified::isSourceSideOutletHeightAutocalculated() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isSourceSideOutletHeightAutocalculated();
  }

  void ThermalStorageChilledWaterStratified::autocalculateSourceSideOutletHeight() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->autocalculateSourceSideOutletHeight();
  }

  boost::optional<double> ThermalStorageChilledWaterStratified::sourceSideDesignFlowRate() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->sourceSideDesignFlowRate();
  }

  bool ThermalStorageChilledWaterStratified::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setSourceSideDesignFlowRate(sourceSideDesignFlowRate);
  }

  bool ThermalStorageChilledWaterStratified::isSourceSideDesignFlowRateDefaulted() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isSourceSideDesignFlowRateDefaulted();
  }

  bool ThermalStorageChilledWaterStratified::isSourceSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->isSourceSideDesignFlowRateAutosized();
  }

  void ThermalStorageChilledWaterStratified::resetSourceSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->resetSourceSideDesignFlowRate();
  }

  void ThermalStorageChilledWaterStratified::autosizeSourceSideDesignFlowRate() {
    getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->autosizeSourceSideDesignFlowRate();
  }

  double ThermalStorageChilledWaterStratified::tankRecoveryTime() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->tankRecoveryTime();
  }

  bool ThermalStorageChilledWaterStratified::setTankRecoveryTime(double tankRecoveryTime) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setTankRecoveryTime(tankRecoveryTime);
  }

  std::string ThermalStorageChilledWaterStratified::inletMode() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->inletMode();
  }

  bool ThermalStorageChilledWaterStratified::setInletMode(const std::string& inletMode) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setInletMode(inletMode);
  }

  int ThermalStorageChilledWaterStratified::numberofNodes() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->numberofNodes();
  }

  bool ThermalStorageChilledWaterStratified::setNumberofNodes(int numberofNodes) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNumberofNodes(numberofNodes);
  }

  double ThermalStorageChilledWaterStratified::additionalDestratificationConductivity() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->additionalDestratificationConductivity();
  }

  bool ThermalStorageChilledWaterStratified::setAdditionalDestratificationConductivity(double additionalDestratificationConductivity) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setAdditionalDestratificationConductivity(
      additionalDestratificationConductivity);
  }

  double ThermalStorageChilledWaterStratified::node1AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node1AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode1AdditionalLossCoefficient(node1AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node2AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node2AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode2AdditionalLossCoefficient(node2AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node3AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node3AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode3AdditionalLossCoefficient(node3AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node4AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node4AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode4AdditionalLossCoefficient(node4AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node5AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node5AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode5AdditionalLossCoefficient(node5AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node6AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node6AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode6AdditionalLossCoefficient(node6AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node7AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node7AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode7AdditionalLossCoefficient(node7AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node8AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node8AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode8AdditionalLossCoefficient(node8AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node9AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node9AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode9AdditionalLossCoefficient(node9AdditionalLossCoefficient);
  }

  double ThermalStorageChilledWaterStratified::node10AdditionalLossCoefficient() const {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->node10AdditionalLossCoefficient();
  }

  bool ThermalStorageChilledWaterStratified::setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient) {
    return getImpl<detail::ThermalStorageChilledWaterStratified_Impl>()->setNode10AdditionalLossCoefficient(node10AdditionalLossCoefficient);
  }

  namespace detail {

    double ThermalStorageChilledWaterStratified_Impl::tankVolume() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankVolume, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setTankVolume(double tankVolume) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankVolume, tankVolume);
    }

    double ThermalStorageChilledWaterStratified_Impl::tankHeight() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setTankHeight(double tankHeight) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankHeight, tankHeight);
    }

    std::string ThermalStorageChilledWaterStratified_Impl::tankShape() const {
      auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankShape, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setTankShape(const std::string& tankShape) {
      return setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankShape, tankShape);
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::tankPerimeter() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankPerimeter, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setTankPerimeter(double tankPerimeter) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankPerimeter, tankPerimeter);
    }

    void ThermalStorageChilledWaterStratified_Impl::resetTankPerimeter() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankPerimeter, ""));
    }

    double ThermalStorageChilledWaterStratified_Impl::deadbandTemperatureDifference() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::DeadbandTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::DeadbandTemperatureDifference, deadbandTemperatureDifference);
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::temperatureSensorHeight() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TemperatureSensorHeight, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setTemperatureSensorHeight(double temperatureSensorHeight) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TemperatureSensorHeight, temperatureSensorHeight);
    }

    void ThermalStorageChilledWaterStratified_Impl::resetTemperatureSensorHeight() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TemperatureSensorHeight, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::minimumTemperatureLimit() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::MinimumTemperatureLimit, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setMinimumTemperatureLimit(double minimumTemperatureLimit) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::MinimumTemperatureLimit, minimumTemperatureLimit);
    }

    void ThermalStorageChilledWaterStratified_Impl::resetMinimumTemperatureLimit() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::MinimumTemperatureLimit, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::nominalCoolingCapacity() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNominalCoolingCapacity(double nominalCoolingCapacity) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity, nominalCoolingCapacity);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isNominalCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageChilledWaterStratified_Impl::autosizeNominalCoolingCapacity() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::NominalCoolingCapacity, "autosize"));
    }

    std::string ThermalStorageChilledWaterStratified_Impl::ambientTemperatureIndicator() const {
      auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureIndicator, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      return setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::AmbientTemperatureIndicator, ambientTemperatureIndicator);
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(
      double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature,
                       uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
    }

    void ThermalStorageChilledWaterStratified_Impl::resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, ""));
    }

    double ThermalStorageChilledWaterStratified_Impl::useSideHeatTransferEffectiveness() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness, useSideHeatTransferEffectiveness);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isUseSideHeatTransferEffectivenessDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness);
    }

    void ThermalStorageChilledWaterStratified_Impl::resetUseSideHeatTransferEffectiveness() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideHeatTransferEffectiveness, ""));
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::useSideInletHeight() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setUseSideInletHeight(double useSideInletHeight) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, useSideInletHeight);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isUseSideInletHeightAutocalculated() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void ThermalStorageChilledWaterStratified_Impl::autocalculateUseSideInletHeight() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideInletHeight, "autocalculate"));
    }

    double ThermalStorageChilledWaterStratified_Impl::useSideOutletHeight() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setUseSideOutletHeight(double useSideOutletHeight) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletHeight, useSideOutletHeight);
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::useSideDesignFlowRate() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, useSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isUseSideDesignFlowRateDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isUseSideDesignFlowRateAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageChilledWaterStratified_Impl::resetUseSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, ""));
    }

    void ThermalStorageChilledWaterStratified_Impl::autosizeUseSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideDesignFlowRate, "autosize"));
    }

    double ThermalStorageChilledWaterStratified_Impl::sourceSideHeatTransferEffectiveness() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness,
                       sourceSideHeatTransferEffectiveness);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isSourceSideHeatTransferEffectivenessDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness);
    }

    void ThermalStorageChilledWaterStratified_Impl::resetSourceSideHeatTransferEffectiveness() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideHeatTransferEffectiveness, ""));
    }

    double ThermalStorageChilledWaterStratified_Impl::sourceSideInletHeight() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setSourceSideInletHeight(double sourceSideInletHeight) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletHeight, sourceSideInletHeight);
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::sourceSideOutletHeight() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setSourceSideOutletHeight(double sourceSideOutletHeight) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, sourceSideOutletHeight);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isSourceSideOutletHeightAutocalculated() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void ThermalStorageChilledWaterStratified_Impl::autocalculateSourceSideOutletHeight() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletHeight, "autocalculate"));
    }

    boost::optional<double> ThermalStorageChilledWaterStratified_Impl::sourceSideDesignFlowRate() const {
      return getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, true);
    }

    bool ThermalStorageChilledWaterStratified_Impl::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, sourceSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isSourceSideDesignFlowRateDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate);
    }

    bool ThermalStorageChilledWaterStratified_Impl::isSourceSideDesignFlowRateAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageChilledWaterStratified_Impl::resetSourceSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, ""));
    }

    void ThermalStorageChilledWaterStratified_Impl::autosizeSourceSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideDesignFlowRate, "autosize"));
    }

    double ThermalStorageChilledWaterStratified_Impl::tankRecoveryTime() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankRecoveryTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setTankRecoveryTime(double tankRecoveryTime) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::TankRecoveryTime, tankRecoveryTime);
    }

    std::string ThermalStorageChilledWaterStratified_Impl::inletMode() const {
      auto value = getString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::InletMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setInletMode(const std::string& inletMode) {
      return setString(openstudio::ThermalStorage_ChilledWater_StratifiedFields::InletMode, inletMode);
    }

    int ThermalStorageChilledWaterStratified_Impl::numberofNodes() const {
      auto value = getInt(openstudio::ThermalStorage_ChilledWater_StratifiedFields::NumberofNodes, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNumberofNodes(int numberofNodes) {
      return setInt(openstudio::ThermalStorage_ChilledWater_StratifiedFields::NumberofNodes, numberofNodes);
    }

    double ThermalStorageChilledWaterStratified_Impl::additionalDestratificationConductivity() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::AdditionalDestratificationConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setAdditionalDestratificationConductivity(double additionalDestratificationConductivity) {
      return setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::AdditionalDestratificationConductivity,
                       additionalDestratificationConductivity);
    }

    double ThermalStorageChilledWaterStratified_Impl::node1AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node1AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node1AdditionalLossCoefficient, node1AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node2AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node2AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node2AdditionalLossCoefficient, node2AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node3AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node3AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node3AdditionalLossCoefficient, node3AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node4AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node4AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node4AdditionalLossCoefficient, node4AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node5AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node5AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node5AdditionalLossCoefficient, node5AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node6AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node6AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node6AdditionalLossCoefficient, node6AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node7AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node7AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node7AdditionalLossCoefficient, node7AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node8AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node8AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node8AdditionalLossCoefficient, node8AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node9AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node9AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node9AdditionalLossCoefficient, node9AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    double ThermalStorageChilledWaterStratified_Impl::node10AdditionalLossCoefficient() const {
      auto value = getDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node10AdditionalLossCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageChilledWaterStratified_Impl::setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient) {
      auto result =
        setDouble(openstudio::ThermalStorage_ChilledWater_StratifiedFields::Node10AdditionalLossCoefficient, node10AdditionalLossCoefficient);
      OS_ASSERT(result);
      return result;
    }

    unsigned ThermalStorageChilledWaterStratified_Impl::supplyInletPort() const {
      return openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideInletNodeName;
    }

    unsigned ThermalStorageChilledWaterStratified_Impl::supplyOutletPort() const {
      return openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletNodeName;
    }

    unsigned ThermalStorageChilledWaterStratified_Impl::demandInletPort() const {
      return openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletNodeName;
    }

    unsigned ThermalStorageChilledWaterStratified_Impl::demandOutletPort() const {
      return openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
