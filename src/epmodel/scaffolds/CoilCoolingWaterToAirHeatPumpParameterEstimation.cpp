/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilCoolingWaterToAirHeatPumpParameterEstimation.hpp"
#include "CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_ParameterEstimation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilCoolingWaterToAirHeatPumpParameterEstimation::CoilCoolingWaterToAirHeatPumpParameterEstimation(const Model& model)
    : ModelObject(CoilCoolingWaterToAirHeatPumpParameterEstimation::iddObjectType(), model) {}

  CoilCoolingWaterToAirHeatPumpParameterEstimation::CoilCoolingWaterToAirHeatPumpParameterEstimation(
    std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoilCoolingWaterToAirHeatPumpParameterEstimation::iddObjectType() {
    return IddObjectType::Coil_Cooling_WaterToAirHeatPump_ParameterEstimation;
  }

  std::vector<std::string> CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorType);
  }

  std::string CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorType() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorType();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setCompressorType(const std::string& compressorType) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorType(compressorType);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::designSourceSideFlowRate() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->designSourceSideFlowRate();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setDesignSourceSideFlowRate(double designSourceSideFlowRate) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setDesignSourceSideFlowRate(designSourceSideFlowRate);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::nominalCoolingCoilCapacity() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->nominalCoolingCoilCapacity();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setNominalCoolingCoilCapacity(double nominalCoolingCoilCapacity) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setNominalCoolingCoilCapacity(nominalCoolingCoilCapacity);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::nominalTimeforCondensateRemovaltoBegin() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->nominalTimeforCondensateRemovaltoBegin();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::isNominalTimeforCondensateRemovaltoBeginDefaulted() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->isNominalTimeforCondensateRemovaltoBeginDefaulted();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setNominalTimeforCondensateRemovaltoBegin(
      nominalTimeforCondensateRemovaltoBegin);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetNominalTimeforCondensateRemovaltoBegin() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetNominalTimeforCondensateRemovaltoBegin();
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()
      ->ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()
      ->isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()
      ->setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()
      ->resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::highPressureCutoff() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->highPressureCutoff();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setHighPressureCutoff(double highPressureCutoff) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setHighPressureCutoff(highPressureCutoff);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::lowPressureCutoff() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->lowPressureCutoff();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setLowPressureCutoff(double lowPressureCutoff) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setLowPressureCutoff(lowPressureCutoff);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::loadSideTotalHeatTransferCoefficient() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->loadSideTotalHeatTransferCoefficient();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setLoadSideTotalHeatTransferCoefficient(double loadSideTotalHeatTransferCoefficient) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setLoadSideTotalHeatTransferCoefficient(
      loadSideTotalHeatTransferCoefficient);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::loadSideOutsideSurfaceHeatTransferCoefficient() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->loadSideOutsideSurfaceHeatTransferCoefficient();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setLoadSideOutsideSurfaceHeatTransferCoefficient(
    double loadSideOutsideSurfaceHeatTransferCoefficient) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setLoadSideOutsideSurfaceHeatTransferCoefficient(
      loadSideOutsideSurfaceHeatTransferCoefficient);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::superheatTemperatureattheEvaporatorOutlet() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->superheatTemperatureattheEvaporatorOutlet();
  }

  bool
    CoilCoolingWaterToAirHeatPumpParameterEstimation::setSuperheatTemperatureattheEvaporatorOutlet(double superheatTemperatureattheEvaporatorOutlet) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setSuperheatTemperatureattheEvaporatorOutlet(
      superheatTemperatureattheEvaporatorOutlet);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorPowerLosses() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorPowerLosses();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setCompressorPowerLosses(double compressorPowerLosses) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorPowerLosses(compressorPowerLosses);
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorEfficiency() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorEfficiency();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setCompressorEfficiency(double compressorEfficiency) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorEfficiency(compressorEfficiency);
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorPistonDisplacement() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorPistonDisplacement();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setCompressorPistonDisplacement(double compressorPistonDisplacement) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorPistonDisplacement(compressorPistonDisplacement);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetCompressorPistonDisplacement() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetCompressorPistonDisplacement();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorSuctionDischargePressureDrop() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorSuctionDischargePressureDrop();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setCompressorSuctionDischargePressureDrop(double compressorSuctionDischargePressureDrop) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorSuctionDischargePressureDrop(
      compressorSuctionDischargePressureDrop);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetCompressorSuctionDischargePressureDrop() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetCompressorSuctionDischargePressureDrop();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorClearanceFactor() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->compressorClearanceFactor();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setCompressorClearanceFactor(double compressorClearanceFactor) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setCompressorClearanceFactor(compressorClearanceFactor);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetCompressorClearanceFactor() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetCompressorClearanceFactor();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::refrigerantVolumeFlowRate() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->refrigerantVolumeFlowRate();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setRefrigerantVolumeFlowRate(double refrigerantVolumeFlowRate) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setRefrigerantVolumeFlowRate(refrigerantVolumeFlowRate);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetRefrigerantVolumeFlowRate() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetRefrigerantVolumeFlowRate();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::volumeRatio() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->volumeRatio();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setVolumeRatio(double volumeRatio) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setVolumeRatio(volumeRatio);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetVolumeRatio() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetVolumeRatio();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::leakRateCoefficient() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->leakRateCoefficient();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setLeakRateCoefficient(double leakRateCoefficient) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setLeakRateCoefficient(leakRateCoefficient);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetLeakRateCoefficient() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetLeakRateCoefficient();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::sourceSideHeatTransferCoefficient() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->sourceSideHeatTransferCoefficient();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setSourceSideHeatTransferCoefficient(
      sourceSideHeatTransferCoefficient);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetSourceSideHeatTransferCoefficient() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetSourceSideHeatTransferCoefficient();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::sourceSideHeatTransferResistance1() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->sourceSideHeatTransferResistance1();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setSourceSideHeatTransferResistance1(double sourceSideHeatTransferResistance1) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setSourceSideHeatTransferResistance1(
      sourceSideHeatTransferResistance1);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetSourceSideHeatTransferResistance1() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetSourceSideHeatTransferResistance1();
  }

  boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation::sourceSideHeatTransferResistance2() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->sourceSideHeatTransferResistance2();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setSourceSideHeatTransferResistance2(double sourceSideHeatTransferResistance2) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setSourceSideHeatTransferResistance2(
      sourceSideHeatTransferResistance2);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetSourceSideHeatTransferResistance2() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetSourceSideHeatTransferResistance2();
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::maximumCyclingRate() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->maximumCyclingRate();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::isMaximumCyclingRateDefaulted() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->isMaximumCyclingRateDefaulted();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setMaximumCyclingRate(double maximumCyclingRate) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetMaximumCyclingRate() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetMaximumCyclingRate();
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::latentCapacityTimeConstant() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->latentCapacityTimeConstant();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::isLatentCapacityTimeConstantDefaulted() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->isLatentCapacityTimeConstantDefaulted();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetLatentCapacityTimeConstant() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetLatentCapacityTimeConstant();
  }

  double CoilCoolingWaterToAirHeatPumpParameterEstimation::fanDelayTime() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->fanDelayTime();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::isFanDelayTimeDefaulted() const {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->isFanDelayTimeDefaulted();
  }

  bool CoilCoolingWaterToAirHeatPumpParameterEstimation::setFanDelayTime(double fanDelayTime) {
    return getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->setFanDelayTime(fanDelayTime);
  }

  void CoilCoolingWaterToAirHeatPumpParameterEstimation::resetFanDelayTime() {
    getImpl<detail::CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl>()->resetFanDelayTime();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorType() const {
      const auto value = getString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorType(const std::string& compressorType) {
      return setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorType, compressorType);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::designSourceSideFlowRate() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::DesignSourceSideFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setDesignSourceSideFlowRate(double designSourceSideFlowRate) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::DesignSourceSideFlowRate, designSourceSideFlowRate);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::nominalCoolingCoilCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalCoolingCoilCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setNominalCoolingCoilCapacity(double nominalCoolingCoilCapacity) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalCoolingCoilCapacity, nominalCoolingCoilCapacity);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::nominalTimeforCondensateRemovaltoBegin() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalTimeforCondensateRemovaltoBegin, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::isNominalTimeforCondensateRemovaltoBeginDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalTimeforCondensateRemovaltoBegin);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setNominalTimeforCondensateRemovaltoBegin(
      double nominalTimeforCondensateRemovaltoBegin) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalTimeforCondensateRemovaltoBegin,
                       nominalTimeforCondensateRemovaltoBegin);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetNominalTimeforCondensateRemovaltoBegin() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalTimeforCondensateRemovaltoBegin, ""));
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
      const auto value = getDouble(
        openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
        true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const {
      return isEmpty(
        openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
      return setDouble(
        openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
        ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() {
      OS_ASSERT(setString(
        openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
        ""));
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::highPressureCutoff() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::HighPressureCutoff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setHighPressureCutoff(double highPressureCutoff) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::HighPressureCutoff, highPressureCutoff);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::lowPressureCutoff() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LowPressureCutoff, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setLowPressureCutoff(double lowPressureCutoff) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LowPressureCutoff, lowPressureCutoff);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::loadSideTotalHeatTransferCoefficient() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LoadSideTotalHeatTransferCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setLoadSideTotalHeatTransferCoefficient(double loadSideTotalHeatTransferCoefficient) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LoadSideTotalHeatTransferCoefficient,
                       loadSideTotalHeatTransferCoefficient);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::loadSideOutsideSurfaceHeatTransferCoefficient() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LoadSideOutsideSurfaceHeatTransferCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setLoadSideOutsideSurfaceHeatTransferCoefficient(
      double loadSideOutsideSurfaceHeatTransferCoefficient) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LoadSideOutsideSurfaceHeatTransferCoefficient,
                       loadSideOutsideSurfaceHeatTransferCoefficient);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::superheatTemperatureattheEvaporatorOutlet() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SuperheatTemperatureattheEvaporatorOutlet, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setSuperheatTemperatureattheEvaporatorOutlet(
      double superheatTemperatureattheEvaporatorOutlet) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SuperheatTemperatureattheEvaporatorOutlet,
                       superheatTemperatureattheEvaporatorOutlet);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorPowerLosses() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPowerLosses, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorPowerLosses(double compressorPowerLosses) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPowerLosses, compressorPowerLosses);
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorEfficiency() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorEfficiency(double compressorEfficiency) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorEfficiency, compressorEfficiency);
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorPistonDisplacement() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorPistonDisplacement(double compressorPistonDisplacement) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement,
                       compressorPistonDisplacement);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetCompressorPistonDisplacement() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorSuctionDischargePressureDrop() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorSuctionDischargePressureDrop(
      double compressorSuctionDischargePressureDrop) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop,
                       compressorSuctionDischargePressureDrop);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetCompressorSuctionDischargePressureDrop() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorClearanceFactor() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setCompressorClearanceFactor(double compressorClearanceFactor) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, compressorClearanceFactor);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetCompressorClearanceFactor() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::refrigerantVolumeFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setRefrigerantVolumeFlowRate(double refrigerantVolumeFlowRate) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, refrigerantVolumeFlowRate);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetRefrigerantVolumeFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::volumeRatio() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setVolumeRatio(double volumeRatio) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, volumeRatio);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetVolumeRatio() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::leakRateCoefficient() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setLeakRateCoefficient(double leakRateCoefficient) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, leakRateCoefficient);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetLeakRateCoefficient() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::sourceSideHeatTransferCoefficient() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient,
                       sourceSideHeatTransferCoefficient);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetSourceSideHeatTransferCoefficient() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::sourceSideHeatTransferResistance1() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setSourceSideHeatTransferResistance1(double sourceSideHeatTransferResistance1) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1,
                       sourceSideHeatTransferResistance1);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetSourceSideHeatTransferResistance1() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1, ""));
    }

    boost::optional<double> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::sourceSideHeatTransferResistance2() const {
      return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2, true);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setSourceSideHeatTransferResistance2(double sourceSideHeatTransferResistance2) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2,
                       sourceSideHeatTransferResistance2);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetSourceSideHeatTransferResistance2() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2, ""));
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::maximumCyclingRate() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::MaximumCyclingRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::isMaximumCyclingRateDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::MaximumCyclingRate);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::MaximumCyclingRate, maximumCyclingRate);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetMaximumCyclingRate() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::MaximumCyclingRate, ""));
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::latentCapacityTimeConstant() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LatentCapacityTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::isLatentCapacityTimeConstantDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LatentCapacityTimeConstant);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetLatentCapacityTimeConstant() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LatentCapacityTimeConstant, ""));
    }

    double CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::fanDelayTime() const {
      const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::FanDelayTime, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::isFanDelayTimeDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::FanDelayTime);
    }

    bool CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::setFanDelayTime(double fanDelayTime) {
      return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::FanDelayTime, fanDelayTime);
    }

    void CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::resetFanDelayTime() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::FanDelayTime, ""));
    }

    std::vector<std::string> CoilCoolingWaterToAirHeatPumpParameterEstimation_Impl::compressorTypeValues() const {
      return openstudio::epmodel::CoilCoolingWaterToAirHeatPumpParameterEstimation::compressorTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
