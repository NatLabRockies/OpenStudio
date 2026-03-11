/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingWaterToAirHeatPumpEquationFit::CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model)
  : ModelObject(CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType(), model) {}

CoilHeatingWaterToAirHeatPumpEquationFit::CoilHeatingWaterToAirHeatPumpEquationFit(
  std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType() {
  return IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit;
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit::ratedAirFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratedAirFlowRate();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedAirFlowRateDefaulted() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedAirFlowRateDefaulted();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedAirFlowRateAutosized();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilHeatingWaterToAirHeatPumpEquationFit::resetRatedAirFlowRate() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedAirFlowRate();
}

void CoilHeatingWaterToAirHeatPumpEquationFit::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedAirFlowRate();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit::ratedWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratedWaterFlowRate();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedWaterFlowRateDefaulted() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedWaterFlowRateDefaulted();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedWaterFlowRateAutosized() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedWaterFlowRateAutosized();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedWaterFlowRate(boost::optional<double> ratedWaterFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedWaterFlowRate(ratedWaterFlowRate);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedWaterFlowRate(double ratedWaterFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedWaterFlowRate(ratedWaterFlowRate);
}

void CoilHeatingWaterToAirHeatPumpEquationFit::resetRatedWaterFlowRate() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedWaterFlowRate();
}

void CoilHeatingWaterToAirHeatPumpEquationFit::autosizeRatedWaterFlowRate() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedWaterFlowRate();
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit::ratedHeatingCapacity() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratedHeatingCapacity();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedHeatingCapacityDefaulted() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedHeatingCapacityDefaulted();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedHeatingCapacityAutosized() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedHeatingCapacityAutosized();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedHeatingCapacity(boost::optional<double> ratedHeatingCapacity) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
}

void CoilHeatingWaterToAirHeatPumpEquationFit::resetRatedHeatingCapacity() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedHeatingCapacity();
}

void CoilHeatingWaterToAirHeatPumpEquationFit::autosizeRatedHeatingCapacity() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->autosizeRatedHeatingCapacity();
}

double CoilHeatingWaterToAirHeatPumpEquationFit::ratedHeatingCoefficientofPerformance() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratedHeatingCoefficientofPerformance();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::isRatedHeatingCoefficientofPerformanceDefaulted() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->isRatedHeatingCoefficientofPerformanceDefaulted();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedHeatingCoefficientofPerformance(double ratedHeatingCoefficientofPerformance) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedHeatingCoefficientofPerformance(
    ratedHeatingCoefficientofPerformance);
}

void CoilHeatingWaterToAirHeatPumpEquationFit::resetRatedHeatingCoefficientofPerformance() {
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->resetRatedHeatingCoefficientofPerformance();
}

double CoilHeatingWaterToAirHeatPumpEquationFit::ratedEnteringWaterTemperature() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratedEnteringWaterTemperature();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedEnteringWaterTemperature(ratedEnteringWaterTemperature);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::ratedEnteringAirDryBulbTemperature() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratedEnteringAirDryBulbTemperature();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatedEnteringAirDryBulbTemperature(
    ratedEnteringAirDryBulbTemperature);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratioofRatedHeatingCapacitytoRatedCoolingCapacity();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(
  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(
    ratioofRatedHeatingCapacitytoRatedCoolingCapacity);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratedAirFlowRate() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, true);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedAirFlowRateDefaulted() const {
  return isEmpty(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate) {
  if (ratedAirFlowRate) {
    return setRatedAirFlowRate(*ratedAirFlowRate);
  }
  resetRatedAirFlowRate();
  return true;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, ratedAirFlowRate);
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::resetRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, ""));
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, "autosize"));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratedWaterFlowRate() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, true);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedWaterFlowRate(boost::optional<double> ratedWaterFlowRate) {
  if (ratedWaterFlowRate) {
    return setRatedWaterFlowRate(*ratedWaterFlowRate);
  }
  resetRatedWaterFlowRate();
  return true;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedWaterFlowRate(double ratedWaterFlowRate) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, ratedWaterFlowRate);
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::resetRatedWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, ""));
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, "autosize"));
}

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratedHeatingCapacity() const {
  return getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, true);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedHeatingCapacityDefaulted() const {
  return isEmpty(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedHeatingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedHeatingCapacity(boost::optional<double> ratedHeatingCapacity) {
  if (ratedHeatingCapacity) {
    return setRatedHeatingCapacity(*ratedHeatingCapacity);
  }
  resetRatedHeatingCapacity();
  return true;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, ratedHeatingCapacity);
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::resetRatedHeatingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, ""));
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedHeatingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, "autosize"));
}

double CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratedHeatingCoefficientofPerformance() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::isRatedHeatingCoefficientofPerformanceDefaulted() const {
  return isEmpty(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCOP);
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedHeatingCoefficientofPerformance(double ratedHeatingCoefficientofPerformance) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCOP,
                   ratedHeatingCoefficientofPerformance);
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::resetRatedHeatingCoefficientofPerformance() {
  OS_ASSERT(setString(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCOP, ""));
}

double CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratedEnteringWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, ratedEnteringWaterTemperature);
}

double CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratedEnteringAirDryBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirDryBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirDryBulbTemperature,
                   ratedEnteringAirDryBulbTemperature);
}

double CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const {
  const auto value = getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatioofRatedHeatingCapacitytoRatedCoolingCapacity,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(
  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatioofRatedHeatingCapacitytoRatedCoolingCapacity,
                   ratioofRatedHeatingCapacitytoRatedCoolingCapacity);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
