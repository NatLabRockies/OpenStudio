/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingWaterToAirHeatPumpEquationFit::CoilCoolingWaterToAirHeatPumpEquationFit(const Model& model)
  : WaterToAirComponent(CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType(), model) {}

CoilCoolingWaterToAirHeatPumpEquationFit::CoilCoolingWaterToAirHeatPumpEquationFit(
  std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl> impl)
  : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType() {
  return IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit;
}

// Preserved model API name `ratedTotalCoolingCapacity` maps to E+ `GrossRatedTotalCoolingCapacity`.
boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::ratedAirFlowRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedAirFlowRate();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedAirFlowRateDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedAirFlowRateDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedAirFlowRateAutosized();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilCoolingWaterToAirHeatPumpEquationFit::resetRatedAirFlowRate() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedAirFlowRate();
}

void CoilCoolingWaterToAirHeatPumpEquationFit::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedAirFlowRate();
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::ratedWaterFlowRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedWaterFlowRate();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedWaterFlowRateDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedWaterFlowRateDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedWaterFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedWaterFlowRateAutosized();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedWaterFlowRate(double ratedWaterFlowRate) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedWaterFlowRate(ratedWaterFlowRate);
}

void CoilCoolingWaterToAirHeatPumpEquationFit::resetRatedWaterFlowRate() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedWaterFlowRate();
}

void CoilCoolingWaterToAirHeatPumpEquationFit::autosizeRatedWaterFlowRate() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedWaterFlowRate();
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedTotalCoolingCapacityDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedTotalCoolingCapacityDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedTotalCoolingCapacity(ratedTotalCoolingCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit::resetRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedTotalCoolingCapacity();
}

void CoilCoolingWaterToAirHeatPumpEquationFit::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedTotalCoolingCapacity();
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::ratedSensibleCoolingCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedSensibleCoolingCapacity();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedSensibleCoolingCapacityDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedSensibleCoolingCapacityDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedSensibleCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedSensibleCoolingCapacityAutosized();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedSensibleCoolingCapacity(ratedSensibleCoolingCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit::resetRatedSensibleCoolingCapacity() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedSensibleCoolingCapacity();
}

void CoilCoolingWaterToAirHeatPumpEquationFit::autosizeRatedSensibleCoolingCapacity() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedSensibleCoolingCapacity();
}

double CoilCoolingWaterToAirHeatPumpEquationFit::ratedCoolingCoefficientofPerformance() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedCoolingCoefficientofPerformance();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatedCoolingCoefficientofPerformanceDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isRatedCoolingCoefficientofPerformanceDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedCoolingCoefficientofPerformance(double ratedCoolingCoefficientofPerformance) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedCoolingCoefficientofPerformance(
    ratedCoolingCoefficientofPerformance);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::ratedEnteringWaterTemperature() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedEnteringWaterTemperature();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedEnteringWaterTemperature(double ratedEnteringAirDryBulbTemperature) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedEnteringWaterTemperature(
    ratedEnteringAirDryBulbTemperature);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::ratedEnteringAirDryBulbTemperature() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedEnteringAirDryBulbTemperature();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedEnteringAirDryBulbTemperature(
    ratedEnteringAirDryBulbTemperature);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::ratedEnteringAirWetBulbTemperature() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratedEnteringAirWetBulbTemperature();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedEnteringAirWetBulbTemperature(double ratedEnteringAirWetBulbTemperature) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedEnteringAirWetBulbTemperature(
    ratedEnteringAirWetBulbTemperature);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::nominalTimeforCondensateRemovaltoBegin() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->nominalTimeforCondensateRemovaltoBegin();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isNominalTimeforCondensateRemovaltoBeginDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->isNominalTimeforCondensateRemovaltoBeginDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setNominalTimeforCondensateRemovaltoBegin(
    nominalTimeforCondensateRemovaltoBegin);
}

void CoilCoolingWaterToAirHeatPumpEquationFit::resetNominalTimeforCondensateRemovaltoBegin() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->resetNominalTimeforCondensateRemovaltoBegin();
}

double CoilCoolingWaterToAirHeatPumpEquationFit::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()
    ->isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()
    ->setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit::resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() {
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
}

double CoilCoolingWaterToAirHeatPumpEquationFit::maximumCyclingRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->maximumCyclingRate();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setMaximumCyclingRate(double maximumCyclingRate) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::latentCapacityTimeConstant() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->latentCapacityTimeConstant();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::fanDelayTime() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->fanDelayTime();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setFanDelayTime(double fanDelayTime) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setFanDelayTime(fanDelayTime);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, true);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedAirFlowRateDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, ratedAirFlowRate);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, ""));
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedWaterFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, true);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedWaterFlowRate(double ratedWaterFlowRate) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, ratedWaterFlowRate);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatedWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, ""));
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedTotalCoolingCapacity, true);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedTotalCoolingCapacityDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedTotalCoolingCapacity);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedTotalCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedTotalCoolingCapacity, ratedTotalCoolingCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedTotalCoolingCapacity, ""));
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedTotalCoolingCapacity, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedSensibleCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, true);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedSensibleCoolingCapacityDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedSensibleCoolingCapacityAutosized() const {
  if (const auto value =
        getString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity,
                   ratedSensibleCoolingCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatedSensibleCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, ""));
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedSensibleCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, "autosize"));
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedCoolingCoefficientofPerformance() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedCoolingCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedCoolingCoefficientofPerformanceDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedCoolingCOP);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedCoolingCoefficientofPerformance(double ratedCoolingCoefficientofPerformance) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedCoolingCOP,
                   ratedCoolingCoefficientofPerformance);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedEnteringWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedEnteringWaterTemperature(double ratedEnteringAirDryBulbTemperature) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature,
                   ratedEnteringAirDryBulbTemperature);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedEnteringAirDryBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirDryBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirDryBulbTemperature,
                   ratedEnteringAirDryBulbTemperature);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedEnteringAirWetBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirWetBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedEnteringAirWetBulbTemperature(double ratedEnteringAirWetBulbTemperature) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirWetBulbTemperature,
                   ratedEnteringAirWetBulbTemperature);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::nominalTimeforCondensateRemovaltoBegin() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::NominalTimeforCondensateRemovaltoBegin, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isNominalTimeforCondensateRemovaltoBeginDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::NominalTimeforCondensateRemovaltoBegin);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::NominalTimeforCondensateRemovaltoBegin,
                   nominalTimeforCondensateRemovaltoBegin);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetNominalTimeforCondensateRemovaltoBegin() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::NominalTimeforCondensateRemovaltoBegin, ""));
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
  const auto value = getDouble(
    openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
  return setDouble(
    openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
    ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() {
  OS_ASSERT(
    setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
              ""));
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::maximumCyclingRate() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::MaximumCyclingRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::MaximumCyclingRate, maximumCyclingRate);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::latentCapacityTimeConstant() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::LatentCapacityTimeConstant, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::fanDelayTime() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::FanDelayTime, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setFanDelayTime(double fanDelayTime) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::FanDelayTime, fanDelayTime);
}

unsigned CoilCoolingWaterToAirHeatPumpEquationFit_Impl::airInletPort() const {
  return openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirInletNodeName;
}

unsigned CoilCoolingWaterToAirHeatPumpEquationFit_Impl::airOutletPort() const {
  return openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName;
}

unsigned CoilCoolingWaterToAirHeatPumpEquationFit_Impl::waterInletPort() const {
  return openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName;
}

unsigned CoilCoolingWaterToAirHeatPumpEquationFit_Impl::waterOutletPort() const {
  return openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
