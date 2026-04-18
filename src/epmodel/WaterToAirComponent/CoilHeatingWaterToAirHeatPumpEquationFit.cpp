/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveLinear.hpp"
#include "Curve/CurveLinear_Impl.hpp"
#include "Curve/CurveQuadLinear.hpp"
#include "Curve/CurveQuadLinear_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil.hpp"
#include "ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirflowNetwork_Distribution_Component_Coil_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idd/Curve_Linear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <cmath>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

namespace {

std::vector<AirflowNetworkDistributionComponentCoil> attachedAirflowNetworkDistributionComponentCoils(const ModelObject& object) {
  std::vector<AirflowNetworkDistributionComponentCoil> result;
  for (const auto& source : object.getSources(AirflowNetworkDistributionComponentCoil::iddObjectType())) {
    if (auto afnComponent = source.optionalCast<AirflowNetworkDistributionComponentCoil>()) {
      result.push_back(*afnComponent);
    }
  }
  return result;
}

}  // namespace

CoilHeatingWaterToAirHeatPumpEquationFit::CoilHeatingWaterToAirHeatPumpEquationFit(
  const Model& model, const Curve& heatingCapacityCurve, const Curve& heatingPowerConsumptionCurve)
  : WaterToAirComponent(CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setHeatingCapacityCurve(heatingCapacityCurve));
  OS_ASSERT(setHeatingPowerConsumptionCurve(heatingPowerConsumptionCurve));
  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setConstructorSharedDefaults(model);
}

CoilHeatingWaterToAirHeatPumpEquationFit::CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model)
  : WaterToAirComponent(CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));

  CurveQuadLinear heatingCapacityCurve(model);
  heatingCapacityCurve.setName("HeatingCapacityCurve");
  OS_ASSERT(heatingCapacityCurve.setCoefficient1Constant(-5.50102734));
  OS_ASSERT(heatingCapacityCurve.setCoefficient2w(-0.96688754));
  OS_ASSERT(heatingCapacityCurve.setCoefficient3x(7.70755007));
  OS_ASSERT(heatingCapacityCurve.setCoefficient4y(0.031928881));
  OS_ASSERT(heatingCapacityCurve.setCoefficient5z(0.028112522));
  OS_ASSERT(setHeatingCapacityCurve(heatingCapacityCurve));

  CurveQuadLinear heatingPowerConsumptionCurve(model);
  heatingPowerConsumptionCurve.setName("HeatingPowerConsumptionCurve");
  OS_ASSERT(heatingPowerConsumptionCurve.setCoefficient1Constant(-7.47517858));
  OS_ASSERT(heatingPowerConsumptionCurve.setCoefficient2w(6.40876653));
  OS_ASSERT(heatingPowerConsumptionCurve.setCoefficient3x(1.99711665));
  OS_ASSERT(heatingPowerConsumptionCurve.setCoefficient4y(-0.050682973));
  OS_ASSERT(heatingPowerConsumptionCurve.setCoefficient5z(0.011385145));
  OS_ASSERT(setHeatingPowerConsumptionCurve(heatingPowerConsumptionCurve));

  getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setConstructorSharedDefaults(model);
}

CoilHeatingWaterToAirHeatPumpEquationFit::CoilHeatingWaterToAirHeatPumpEquationFit(
  std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl> impl)
  : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType() {
  return IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit;
}

Schedule CoilHeatingWaterToAirHeatPumpEquationFit::availabilitySchedule() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->availabilitySchedule();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setAvailabilitySchedule(schedule);
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

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit::autosizedRatedAirFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedAirFlowRate();
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

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit::autosizedRatedWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedWaterFlowRate();
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

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit::autosizedRatedHeatingCapacity() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->autosizedRatedHeatingCapacity();
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

Curve CoilHeatingWaterToAirHeatPumpEquationFit::heatingCapacityCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->heatingCapacityCurve();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingCapacityCurve(const Curve& heatingCapacityCurve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setHeatingCapacityCurve(heatingCapacityCurve);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingCapacityCoefficient1() const {
  return heatingCapacityCurve().cast<CurveQuadLinear>().coefficient1Constant();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingCapacityCoefficient1(double heatingCapacityCoefficient1) {
  return heatingCapacityCurve().cast<CurveQuadLinear>().setCoefficient1Constant(heatingCapacityCoefficient1);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingCapacityCoefficient2() const {
  return heatingCapacityCurve().cast<CurveQuadLinear>().coefficient2w();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingCapacityCoefficient2(double heatingCapacityCoefficient2) {
  return heatingCapacityCurve().cast<CurveQuadLinear>().setCoefficient2w(heatingCapacityCoefficient2);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingCapacityCoefficient3() const {
  return heatingCapacityCurve().cast<CurveQuadLinear>().coefficient3x();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingCapacityCoefficient3(double heatingCapacityCoefficient3) {
  return heatingCapacityCurve().cast<CurveQuadLinear>().setCoefficient3x(heatingCapacityCoefficient3);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingCapacityCoefficient4() const {
  return heatingCapacityCurve().cast<CurveQuadLinear>().coefficient4y();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingCapacityCoefficient4(double heatingCapacityCoefficient4) {
  return heatingCapacityCurve().cast<CurveQuadLinear>().setCoefficient4y(heatingCapacityCoefficient4);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingCapacityCoefficient5() const {
  return heatingCapacityCurve().cast<CurveQuadLinear>().coefficient5z();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingCapacityCoefficient5(double heatingCapacityCoefficient5) {
  return heatingCapacityCurve().cast<CurveQuadLinear>().setCoefficient5z(heatingCapacityCoefficient5);
}

Curve CoilHeatingWaterToAirHeatPumpEquationFit::heatingPowerConsumptionCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->heatingPowerConsumptionCurve();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingPowerConsumptionCurve(const Curve& heatingPowerConsumptionCurve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setHeatingPowerConsumptionCurve(heatingPowerConsumptionCurve);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingPowerConsumptionCoefficient1() const {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().coefficient1Constant();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingPowerConsumptionCoefficient1(double heatingPowerConsumptionCoefficient1) {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().setCoefficient1Constant(heatingPowerConsumptionCoefficient1);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingPowerConsumptionCoefficient2() const {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().coefficient2w();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingPowerConsumptionCoefficient2(double heatingPowerConsumptionCoefficient2) {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().setCoefficient2w(heatingPowerConsumptionCoefficient2);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingPowerConsumptionCoefficient3() const {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().coefficient3x();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingPowerConsumptionCoefficient3(double heatingPowerConsumptionCoefficient3) {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().setCoefficient3x(heatingPowerConsumptionCoefficient3);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingPowerConsumptionCoefficient4() const {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().coefficient4y();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingPowerConsumptionCoefficient4(double heatingPowerConsumptionCoefficient4) {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().setCoefficient4y(heatingPowerConsumptionCoefficient4);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::heatingPowerConsumptionCoefficient5() const {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().coefficient5z();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setHeatingPowerConsumptionCoefficient5(double heatingPowerConsumptionCoefficient5) {
  return heatingPowerConsumptionCurve().cast<CurveQuadLinear>().setCoefficient5z(heatingPowerConsumptionCoefficient5);
}

Curve CoilHeatingWaterToAirHeatPumpEquationFit::partLoadFractionCorrelationCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->partLoadFractionCorrelationCurve();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setPartLoadFractionCorrelationCurve(partLoadFractionCorrelationCurve);
}

double CoilHeatingWaterToAirHeatPumpEquationFit::ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->ratioofRatedHeatingCapacitytoRatedCoolingCapacity();
}

bool CoilHeatingWaterToAirHeatPumpEquationFit::setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(
  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(
    ratioofRatedHeatingCapacitytoRatedCoolingCapacity);
}

AirflowNetworkDistributionComponentCoil CoilHeatingWaterToAirHeatPumpEquationFit::getAirflowNetworkEquivalentDuct(double length,
                                                                                                                   double diameter) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->getAirflowNetworkEquivalentDuct(length, diameter);
}

boost::optional<AirflowNetworkDistributionComponentCoil> CoilHeatingWaterToAirHeatPumpEquationFit::airflowNetworkEquivalentDuct() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl>()->airflowNetworkEquivalentDuct();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingWaterToAirHeatPumpEquationFit_Impl::airInletPort() const {
  return openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirInletNodeName;
}

unsigned CoilHeatingWaterToAirHeatPumpEquationFit_Impl::airOutletPort() const {
  return openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName;
}

unsigned CoilHeatingWaterToAirHeatPumpEquationFit_Impl::waterInletPort() const {
  return openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName;
}

unsigned CoilHeatingWaterToAirHeatPumpEquationFit_Impl::waterOutletPort() const {
  return openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName;
}

Schedule CoilHeatingWaterToAirHeatPumpEquationFit_Impl::availabilitySchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName);
  if (!schedule) {
    LOG_FREE(Error, "openstudio.epmodel.CoilHeatingWaterToAirHeatPumpEquationFit",
             "Required availability schedule not set, returning the model always-on discrete schedule and repairing persisted state");
    schedule = model().alwaysOnDiscreteSchedule();
    OS_ASSERT(schedule);
    OS_ASSERT(const_cast<CoilHeatingWaterToAirHeatPumpEquationFit_Impl*>(this)->setAvailabilitySchedule(*schedule));
    schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
      openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName);
  }
  OS_ASSERT(schedule);
  return *schedule;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName,
                     "CoilHeatingWaterToAirHeatPumpEquationFit", "Availability Schedule", schedule);
}

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

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedAirFlowRate() const {
  return boost::none;
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

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedWaterFlowRate() const {
  return boost::none;
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

boost::optional<double> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::autosizedRatedHeatingCapacity() const {
  return boost::none;
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

Curve CoilHeatingWaterToAirHeatPumpEquationFit_Impl::heatingCapacityCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Heating water-to-air heat pump equation-fit coil is missing its heating capacity curve.");
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setHeatingCapacityCurve(const Curve& heatingCapacityCurve) {
  return setPointer(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCurveName, heatingCapacityCurve.handle());
}

Curve CoilHeatingWaterToAirHeatPumpEquationFit_Impl::heatingPowerConsumptionCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Heating water-to-air heat pump equation-fit coil is missing its heating power consumption curve.");
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setHeatingPowerConsumptionCurve(const Curve& heatingPowerConsumptionCurve) {
  return setPointer(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCurveName,
                    heatingPowerConsumptionCurve.handle());
}

Curve CoilHeatingWaterToAirHeatPumpEquationFit_Impl::partLoadFractionCorrelationCurve() const {
  if (auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::PartLoadFractionCorrelationCurveName)) {
    return *curve;
  }
  throw std::runtime_error("Heating water-to-air heat pump equation-fit coil is missing its part load fraction correlation curve.");
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve) {
  return setPointer(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::PartLoadFractionCorrelationCurveName,
                    partLoadFractionCorrelationCurve.handle());
}

double CoilHeatingWaterToAirHeatPumpEquationFit_Impl::ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const {
  const auto value =
    getDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatioofRatedHeatingCapacitytoRatedCoolingCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(
  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity) {
  return setDouble(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatioofRatedHeatingCapacitytoRatedCoolingCapacity,
                   ratioofRatedHeatingCapacitytoRatedCoolingCapacity);
}

std::vector<ModelObject> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::children() const {
  std::vector<ModelObject> result;
  for (const auto& afnComponent : attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>())) {
    result.push_back(afnComponent);
  }
  return result;
}

AirflowNetworkDistributionComponentCoil CoilHeatingWaterToAirHeatPumpEquationFit_Impl::getAirflowNetworkEquivalentDuct(double length,
                                                                                                                         double diameter) {
  if (auto component = airflowNetworkEquivalentDuct()) {
    if (component->airPathLength() != length) {
      component->setAirPathLength(length);
    }
    if (component->airPathHydraulicDiameter() != diameter) {
      component->setAirPathHydraulicDiameter(diameter);
    }
    return *component;
  }

  AirflowNetworkDistributionComponentCoil component(model());
  OS_ASSERT(component.setPointer(openstudio::AirflowNetwork_Distribution_Component_CoilFields::CoilName, handle()));
  OS_ASSERT(component.setCoilObjectType("Coil:Heating:WaterToAirHeatPump:EquationFit"));
  OS_ASSERT(component.setAirPathLength(length));
  OS_ASSERT(component.setAirPathHydraulicDiameter(diameter));
  return component;
}

boost::optional<AirflowNetworkDistributionComponentCoil> CoilHeatingWaterToAirHeatPumpEquationFit_Impl::airflowNetworkEquivalentDuct() const {
  auto afnComponents = attachedAirflowNetworkDistributionComponentCoils(getObject<ModelObject>());
  if (afnComponents.size() == 1u) {
    return afnComponents.front();
  }
  if (afnComponents.size() > 1u) {
    LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingWaterToAirHeatPumpEquationFit",
             briefDescription() << " has more than one AirflowNetwork distribution component coil attached, returning first.");
    return afnComponents.front();
  }
  return boost::none;
}

void CoilHeatingWaterToAirHeatPumpEquationFit_Impl::setConstructorSharedDefaults(const Model& model) {
  OS_ASSERT(setRatedEnteringWaterTemperature(20.0));
  OS_ASSERT(setRatedEnteringAirDryBulbTemperature(20.0));
  OS_ASSERT(setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(1.0));

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
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
