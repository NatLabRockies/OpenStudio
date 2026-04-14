/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveLinear.hpp"
#include "Curve/CurveLinear_Impl.hpp"
#include "Curve/CurveQuadLinear.hpp"
#include "Curve/CurveQuadLinear_Impl.hpp"
#include "Curve/CurveQuintLinear.hpp"
#include "Curve/CurveQuintLinear_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idd/Curve_Linear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <cmath>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

CoilCoolingWaterToAirHeatPumpEquationFit::CoilCoolingWaterToAirHeatPumpEquationFit(
  const Model& model, const Curve& totalCoolingCapacityCurve, const Curve& sensibleCoolingCapacityCurve, const Curve& coolingPowerConsumptionCurve)
  : WaterToAirComponent(CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setTotalCoolingCapacityCurve(totalCoolingCapacityCurve));
  OS_ASSERT(setSensibleCoolingCapacityCurve(sensibleCoolingCapacityCurve));
  OS_ASSERT(setCoolingPowerConsumptionCurve(coolingPowerConsumptionCurve));
  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setConstructorSharedDefaults(model);
}

CoilCoolingWaterToAirHeatPumpEquationFit::CoilCoolingWaterToAirHeatPumpEquationFit(const Model& model)
  : WaterToAirComponent(CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));

  CurveQuadLinear totalCoolingCapacityCurve(model);
  totalCoolingCapacityCurve.setName("TotCoolCapCurve");
  OS_ASSERT(totalCoolingCapacityCurve.setCoefficient1Constant(-0.68126221));
  OS_ASSERT(totalCoolingCapacityCurve.setCoefficient2w(1.99529297));
  OS_ASSERT(totalCoolingCapacityCurve.setCoefficient3x(-0.93611888));
  OS_ASSERT(totalCoolingCapacityCurve.setCoefficient4y(0.02081177));
  OS_ASSERT(totalCoolingCapacityCurve.setCoefficient5z(0.008438868));
  OS_ASSERT(setTotalCoolingCapacityCurve(totalCoolingCapacityCurve));

  CurveQuintLinear sensibleCoolingCapacityCurve(model);
  sensibleCoolingCapacityCurve.setName("SensCoolCapCurve");
  OS_ASSERT(sensibleCoolingCapacityCurve.setCoefficient1Constant(2.24209455));
  OS_ASSERT(sensibleCoolingCapacityCurve.setCoefficient2v(7.28913391));
  OS_ASSERT(sensibleCoolingCapacityCurve.setCoefficient3w(-9.06079896));
  OS_ASSERT(sensibleCoolingCapacityCurve.setCoefficient4x(-0.36729404));
  OS_ASSERT(sensibleCoolingCapacityCurve.setCoefficient5y(0.218826161));
  OS_ASSERT(sensibleCoolingCapacityCurve.setCoefficient6z(0.00901534));
  OS_ASSERT(setSensibleCoolingCapacityCurve(sensibleCoolingCapacityCurve));

  CurveQuadLinear coolingPowerConsumptionCurve(model);
  coolingPowerConsumptionCurve.setName("CoolingPowerConsumptionCurve");
  OS_ASSERT(coolingPowerConsumptionCurve.setCoefficient1Constant(-3.20456384));
  OS_ASSERT(coolingPowerConsumptionCurve.setCoefficient2w(0.47656454));
  OS_ASSERT(coolingPowerConsumptionCurve.setCoefficient3x(3.16734236));
  OS_ASSERT(coolingPowerConsumptionCurve.setCoefficient4y(0.10244637));
  OS_ASSERT(coolingPowerConsumptionCurve.setCoefficient5z(-0.038132556));
  OS_ASSERT(setCoolingPowerConsumptionCurve(coolingPowerConsumptionCurve));

  getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setConstructorSharedDefaults(model);
}

CoilCoolingWaterToAirHeatPumpEquationFit::CoilCoolingWaterToAirHeatPumpEquationFit(
  std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl> impl)
  : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType() {
  return IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit;
}

Schedule CoilCoolingWaterToAirHeatPumpEquationFit::availabilitySchedule() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->availabilitySchedule();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setAvailabilitySchedule(schedule);
}

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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::autosizedRatedAirFlowRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedAirFlowRate();
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::autosizedRatedWaterFlowRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedWaterFlowRate();
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::autosizedRatedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedTotalCoolingCapacity();
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit::autosizedRatedSensibleCoolingCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedSensibleCoolingCapacity();
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

bool CoilCoolingWaterToAirHeatPumpEquationFit::setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setRatedEnteringWaterTemperature(ratedEnteringWaterTemperature);
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

Curve CoilCoolingWaterToAirHeatPumpEquationFit::totalCoolingCapacityCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->totalCoolingCapacityCurve();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setTotalCoolingCapacityCurve(const Curve& totalCoolingCapacityCurve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setTotalCoolingCapacityCurve(totalCoolingCapacityCurve);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::totalCoolingCapacityCoefficient1() const {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.coefficient1Constant();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setTotalCoolingCapacityCoefficient1(double totalCoolingCapacityCoefficient1) {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient1Constant(totalCoolingCapacityCoefficient1);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::totalCoolingCapacityCoefficient2() const {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.coefficient2w();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setTotalCoolingCapacityCoefficient2(double totalCoolingCapacityCoefficient2) {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient2w(totalCoolingCapacityCoefficient2);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::totalCoolingCapacityCoefficient3() const {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.coefficient3x();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setTotalCoolingCapacityCoefficient3(double totalCoolingCapacityCoefficient3) {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient3x(totalCoolingCapacityCoefficient3);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::totalCoolingCapacityCoefficient4() const {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.coefficient4y();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setTotalCoolingCapacityCoefficient4(double totalCoolingCapacityCoefficient4) {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient4y(totalCoolingCapacityCoefficient4);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::totalCoolingCapacityCoefficient5() const {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.coefficient5z();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setTotalCoolingCapacityCoefficient5(double totalCoolingCapacityCoefficient5) {
  auto curve = totalCoolingCapacityCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient5z(totalCoolingCapacityCoefficient5);
}

Curve CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->sensibleCoolingCapacityCurve();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCurve(const Curve& sensibleCoolingCapacityCurve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setSensibleCoolingCapacityCurve(sensibleCoolingCapacityCurve);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCoefficient1() const {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.coefficient1Constant();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCoefficient1(double sensibleCoolingCapacityCoefficient1) {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.setCoefficient1Constant(sensibleCoolingCapacityCoefficient1);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCoefficient2() const {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.coefficient2v();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCoefficient2(double sensibleCoolingCapacityCoefficient2) {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.setCoefficient2v(sensibleCoolingCapacityCoefficient2);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCoefficient3() const {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.coefficient3w();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCoefficient3(double sensibleCoolingCapacityCoefficient3) {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.setCoefficient3w(sensibleCoolingCapacityCoefficient3);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCoefficient4() const {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.coefficient4x();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCoefficient4(double sensibleCoolingCapacityCoefficient4) {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.setCoefficient4x(sensibleCoolingCapacityCoefficient4);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCoefficient5() const {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.coefficient5y();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCoefficient5(double sensibleCoolingCapacityCoefficient5) {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.setCoefficient5y(sensibleCoolingCapacityCoefficient5);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::sensibleCoolingCapacityCoefficient6() const {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.coefficient6z();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setSensibleCoolingCapacityCoefficient6(double sensibleCoolingCapacityCoefficient6) {
  auto curve = sensibleCoolingCapacityCurve().cast<CurveQuintLinear>();
  return curve.setCoefficient6z(sensibleCoolingCapacityCoefficient6);
}

Curve CoilCoolingWaterToAirHeatPumpEquationFit::coolingPowerConsumptionCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->coolingPowerConsumptionCurve();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setCoolingPowerConsumptionCurve(const Curve& coolingPowerConsumptionCurve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setCoolingPowerConsumptionCurve(coolingPowerConsumptionCurve);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::coolingPowerConsumptionCoefficient1() const {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.coefficient1Constant();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setCoolingPowerConsumptionCoefficient1(double coolingPowerConsumptionCoefficient1) {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient1Constant(coolingPowerConsumptionCoefficient1);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::coolingPowerConsumptionCoefficient2() const {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.coefficient2w();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setCoolingPowerConsumptionCoefficient2(double coolingPowerConsumptionCoefficient2) {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient2w(coolingPowerConsumptionCoefficient2);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::coolingPowerConsumptionCoefficient3() const {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.coefficient3x();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setCoolingPowerConsumptionCoefficient3(double coolingPowerConsumptionCoefficient3) {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient3x(coolingPowerConsumptionCoefficient3);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::coolingPowerConsumptionCoefficient4() const {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.coefficient4y();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setCoolingPowerConsumptionCoefficient4(double coolingPowerConsumptionCoefficient4) {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient4y(coolingPowerConsumptionCoefficient4);
}

double CoilCoolingWaterToAirHeatPumpEquationFit::coolingPowerConsumptionCoefficient5() const {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.coefficient5z();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setCoolingPowerConsumptionCoefficient5(double coolingPowerConsumptionCoefficient5) {
  auto curve = coolingPowerConsumptionCurve().cast<CurveQuadLinear>();
  return curve.setCoefficient5z(coolingPowerConsumptionCoefficient5);
}

Curve CoilCoolingWaterToAirHeatPumpEquationFit::partLoadFractionCorrelationCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->partLoadFractionCorrelationCurve();
}

bool CoilCoolingWaterToAirHeatPumpEquationFit::setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpEquationFit_Impl>()->setPartLoadFractionCorrelationCurve(partLoadFractionCorrelationCurve);
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

Schedule CoilCoolingWaterToAirHeatPumpEquationFit_Impl::availabilitySchedule() const {
  auto schedule =
    getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName);
  if (!schedule) {
    LOG_FREE(Error, "openstudio.epmodel.CoilCoolingWaterToAirHeatPumpEquationFit",
             "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
    schedule = model().alwaysOnDiscreteSchedule();
    const bool ok = const_cast<CoilCoolingWaterToAirHeatPumpEquationFit_Impl*>(this)->setAvailabilitySchedule(*schedule);
    OS_ASSERT(ok);
    schedule =
      getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName);
  }
  OS_ASSERT(schedule);
  return *schedule;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName,
                     "CoilCoolingWaterToAirHeatPumpEquationFit", "Availability Schedule", schedule);
}

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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedAirFlowRate() const {
  return boost::none;
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedWaterFlowRate() const {
  return boost::none;
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

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedTotalCoolingCapacity() const {
  return boost::none;
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedSensibleCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, true);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedSensibleCoolingCapacityDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatedSensibleCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedSensibleCoolingCapacity(double ratedSensibleCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, ratedSensibleCoolingCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatedSensibleCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, ""));
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizeRatedSensibleCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedSensibleCoolingCapacity, "autosize"));
}

boost::optional<double> CoilCoolingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedSensibleCoolingCapacity() const {
  return boost::none;
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
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::GrossRatedCoolingCOP, ratedCoolingCoefficientofPerformance);
}

double CoilCoolingWaterToAirHeatPumpEquationFit_Impl::ratedEnteringWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, ratedEnteringWaterTemperature);
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

Curve CoilCoolingWaterToAirHeatPumpEquationFit_Impl::totalCoolingCapacityCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Cooling water-to-air heat pump equation-fit coil is missing its total cooling capacity curve.");
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setTotalCoolingCapacityCurve(const Curve& totalCoolingCapacityCurve) {
  return setPointer(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCurveName,
                    totalCoolingCapacityCurve.handle());
}

Curve CoilCoolingWaterToAirHeatPumpEquationFit_Impl::sensibleCoolingCapacityCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Cooling water-to-air heat pump equation-fit coil is missing its sensible cooling capacity curve.");
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setSensibleCoolingCapacityCurve(const Curve& sensibleCoolingCapacityCurve) {
  return setPointer(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCurveName,
                    sensibleCoolingCapacityCurve.handle());
}

Curve CoilCoolingWaterToAirHeatPumpEquationFit_Impl::coolingPowerConsumptionCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Cooling water-to-air heat pump equation-fit coil is missing its cooling power consumption curve.");
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setCoolingPowerConsumptionCurve(const Curve& coolingPowerConsumptionCurve) {
  return setPointer(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCurveName,
                    coolingPowerConsumptionCurve.handle());
}

Curve CoilCoolingWaterToAirHeatPumpEquationFit_Impl::partLoadFractionCorrelationCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::PartLoadFractionCorrelationCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Cooling water-to-air heat pump equation-fit coil is missing its part load fraction correlation curve.");
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve) {
  return setPointer(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::PartLoadFractionCorrelationCurveName,
                    partLoadFractionCorrelationCurve.handle());
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
  const auto value =
    getDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted() const {
  return isEmpty(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

bool CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
  double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
  return setDouble(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
                   ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
}

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
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

void CoilCoolingWaterToAirHeatPumpEquationFit_Impl::setConstructorSharedDefaults(const Model& model) {
  OS_ASSERT(setRatedEnteringWaterTemperature(30.0));
  OS_ASSERT(setRatedEnteringAirDryBulbTemperature(27.0));
  OS_ASSERT(setRatedEnteringAirWetBulbTemperature(19.0));

  constexpr double maximumCyclingRatePerHour = 2.5;
  constexpr double heatPumpTimeConstantSeconds = 60.0;
  const double a = 4.0 * (heatPumpTimeConstantSeconds / 3600.0) * maximumCyclingRatePerHour;
  const double cd = a * (1.0 - std::exp(-1.0 / a));

  CurveLinear partLoadFractionCurve(model);
  partLoadFractionCurve.setName("PLFCorrelationCurve");
  OS_ASSERT(partLoadFractionCurve.setDouble(openstudio::Curve_LinearFields::Coefficient1Constant, 1.0 - cd));
  OS_ASSERT(partLoadFractionCurve.setDouble(openstudio::Curve_LinearFields::Coefficient2x, cd));
  OS_ASSERT(partLoadFractionCurve.setDouble(openstudio::Curve_LinearFields::MinimumValueofx, 0.0));
  OS_ASSERT(partLoadFractionCurve.setDouble(openstudio::Curve_LinearFields::MaximumValueofx, 1.0));
  OS_ASSERT(partLoadFractionCurve.setDouble(openstudio::Curve_LinearFields::MinimumCurveOutput, 0.0));
  OS_ASSERT(partLoadFractionCurve.setDouble(openstudio::Curve_LinearFields::MaximumCurveOutput, 1.0));
  OS_ASSERT(partLoadFractionCurve.setString(openstudio::Curve_LinearFields::InputUnitTypeforX, "Dimensionless"));
  OS_ASSERT(partLoadFractionCurve.setString(openstudio::Curve_LinearFields::OutputUnitType, "Dimensionless"));
  OS_ASSERT(setPartLoadFractionCorrelationCurve(partLoadFractionCurve));

  OS_ASSERT(setMaximumCyclingRate(maximumCyclingRatePerHour));
  OS_ASSERT(setLatentCapacityTimeConstant(heatPumpTimeConstantSeconds));
  OS_ASSERT(setFanDelayTime(60.0));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
