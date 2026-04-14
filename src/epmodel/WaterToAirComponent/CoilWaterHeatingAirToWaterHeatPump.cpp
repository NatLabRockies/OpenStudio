/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Pumped_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CoilWaterHeatingAirToWaterHeatPump::CoilWaterHeatingAirToWaterHeatPump(
  const Model& model, const Curve& heatingCapacityFunctionofTemperatureCurve, const Curve& heatingCapacityFunctionofAirFlowFractionCurve,
  const Curve& heatingCapacityFunctionofWaterFlowFractionCurve, const Curve& heatingCOPFunctionofTemperatureCurve,
  const Curve& heatingCOPFunctionofAirFlowFractionCurve, const Curve& heatingCOPFunctionofWaterFlowFractionCurve,
  const Curve& partLoadFractionCorrelationCurve)
  : WaterToAirComponent(CoilWaterHeatingAirToWaterHeatPump::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));

  OS_ASSERT(setRatedHeatingCapacity(4000.0));
  OS_ASSERT(setRatedCOP(3.2));
  OS_ASSERT(setRatedSensibleHeatRatio(0.6956));
  OS_ASSERT(setRatedEvaporatorInletAirDryBulbTemperature(29.44));
  OS_ASSERT(setRatedEvaporatorInletAirWetBulbTemperature(22.22));
  OS_ASSERT(setRatedCondenserInletWaterTemperature(55.72));
  autosizeRatedEvaporatorAirFlowRate();
  autosizeRatedCondenserWaterFlowRate();
  OS_ASSERT(setEvaporatorFanPowerIncludedinRatedCOP(false));
  OS_ASSERT(setCondenserPumpPowerIncludedinRatedCOP(false));
  OS_ASSERT(setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(false));
  OS_ASSERT(setCondenserWaterPumpPower(150.0));
  OS_ASSERT(setFractionofCondenserPumpHeattoWater(0.1));
  OS_ASSERT(setCrankcaseHeaterCapacity(100.0));
  OS_ASSERT(setMaximumAmbientTemperatureforCrankcaseHeaterOperation(5.0));
  OS_ASSERT(setEvaporatorAirTemperatureTypeforCurveObjects("WetBulbTemperature"));

  OS_ASSERT(setHeatingCapacityFunctionofTemperatureCurve(heatingCapacityFunctionofTemperatureCurve));
  OS_ASSERT(setHeatingCapacityFunctionofAirFlowFractionCurve(heatingCapacityFunctionofAirFlowFractionCurve));
  OS_ASSERT(setHeatingCapacityFunctionofWaterFlowFractionCurve(heatingCapacityFunctionofWaterFlowFractionCurve));
  OS_ASSERT(setHeatingCOPFunctionofTemperatureCurve(heatingCOPFunctionofTemperatureCurve));
  OS_ASSERT(setHeatingCOPFunctionofAirFlowFractionCurve(heatingCOPFunctionofAirFlowFractionCurve));
  OS_ASSERT(setHeatingCOPFunctionofWaterFlowFractionCurve(heatingCOPFunctionofWaterFlowFractionCurve));
  OS_ASSERT(setPartLoadFractionCorrelationCurve(partLoadFractionCorrelationCurve));
}

CoilWaterHeatingAirToWaterHeatPump::CoilWaterHeatingAirToWaterHeatPump(const Model& model)
  : WaterToAirComponent(CoilWaterHeatingAirToWaterHeatPump::iddObjectType(), model) {
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));

  OS_ASSERT(setRatedHeatingCapacity(4000.0));
  OS_ASSERT(setRatedCOP(3.2));
  OS_ASSERT(setRatedSensibleHeatRatio(0.6956));
  OS_ASSERT(setRatedEvaporatorInletAirDryBulbTemperature(29.44));
  OS_ASSERT(setRatedEvaporatorInletAirWetBulbTemperature(22.22));
  OS_ASSERT(setRatedCondenserInletWaterTemperature(55.72));
  autosizeRatedEvaporatorAirFlowRate();
  autosizeRatedCondenserWaterFlowRate();
  OS_ASSERT(setEvaporatorFanPowerIncludedinRatedCOP(false));
  OS_ASSERT(setCondenserPumpPowerIncludedinRatedCOP(false));
  OS_ASSERT(setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(false));
  OS_ASSERT(setCondenserWaterPumpPower(150.0));
  OS_ASSERT(setFractionofCondenserPumpHeattoWater(0.1));
  OS_ASSERT(setCrankcaseHeaterCapacity(100.0));
  OS_ASSERT(setMaximumAmbientTemperatureforCrankcaseHeaterOperation(5.0));
  OS_ASSERT(setEvaporatorAirTemperatureTypeforCurveObjects("WetBulbTemperature"));

  {
    CurveBiquadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(0.369827));
    OS_ASSERT(curve.setCoefficient2x(0.043341));
    OS_ASSERT(curve.setCoefficient3xPOW2(-0.00023));
    OS_ASSERT(curve.setCoefficient4y(0.000466));
    OS_ASSERT(curve.setCoefficient5yPOW2(0.000026));
    OS_ASSERT(curve.setCoefficient6xTIMESY(-0.00027));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(40.0));
    OS_ASSERT(curve.setMinimumValueofy(20.0));
    OS_ASSERT(curve.setMaximumValueofy(90.0));
    OS_ASSERT(curve.setInputUnitTypeforX("Temperature"));
    OS_ASSERT(curve.setInputUnitTypeforY("Temperature"));
    OS_ASSERT(curve.setOutputUnitType("Dimensionless"));
    OS_ASSERT(setHeatingCapacityFunctionofTemperatureCurve(curve));
  }

  {
    CurveQuadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(1.0));
    OS_ASSERT(curve.setCoefficient2x(0.0));
    OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(1.0));
    OS_ASSERT(setHeatingCapacityFunctionofAirFlowFractionCurve(curve));
  }

  {
    CurveQuadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(1.0));
    OS_ASSERT(curve.setCoefficient2x(0.0));
    OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(1.0));
    OS_ASSERT(setHeatingCapacityFunctionofWaterFlowFractionCurve(curve));
  }

  {
    CurveBiquadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(1.19713));
    OS_ASSERT(curve.setCoefficient2x(0.077849));
    OS_ASSERT(curve.setCoefficient3xPOW2(-0.0000016));
    OS_ASSERT(curve.setCoefficient4y(-0.02675));
    OS_ASSERT(curve.setCoefficient5yPOW2(0.000296));
    OS_ASSERT(curve.setCoefficient6xTIMESY(-0.00112));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(40.0));
    OS_ASSERT(curve.setMinimumValueofy(20.0));
    OS_ASSERT(curve.setMaximumValueofy(90.0));
    OS_ASSERT(curve.setInputUnitTypeforX("Temperature"));
    OS_ASSERT(curve.setInputUnitTypeforY("Temperature"));
    OS_ASSERT(curve.setOutputUnitType("Dimensionless"));
    OS_ASSERT(setHeatingCOPFunctionofTemperatureCurve(curve));
  }

  {
    CurveQuadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(1.0));
    OS_ASSERT(curve.setCoefficient2x(0.0));
    OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(1.0));
    OS_ASSERT(setHeatingCOPFunctionofAirFlowFractionCurve(curve));
  }

  {
    CurveQuadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(1.0));
    OS_ASSERT(curve.setCoefficient2x(0.0));
    OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(1.0));
    OS_ASSERT(setHeatingCOPFunctionofWaterFlowFractionCurve(curve));
  }

  {
    CurveQuadratic curve(model);
    OS_ASSERT(curve.setCoefficient1Constant(0.75));
    OS_ASSERT(curve.setCoefficient2x(0.25));
    OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(1.0));
    OS_ASSERT(setPartLoadFractionCorrelationCurve(curve));
  }
}

CoilWaterHeatingAirToWaterHeatPump::CoilWaterHeatingAirToWaterHeatPump(std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPump_Impl> impl)
  : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilWaterHeatingAirToWaterHeatPump::iddObjectType() {
  return IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Pumped;
}

std::vector<std::string> CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjectsValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects);
}

Schedule CoilWaterHeatingAirToWaterHeatPump::availabilitySchedule() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->availabilitySchedule();
}

bool CoilWaterHeatingAirToWaterHeatPump::setAvailabilitySchedule(Schedule& availabilitySchedule) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setAvailabilitySchedule(availabilitySchedule);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedHeatingCapacity() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedHeatingCapacity();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedCOP(double ratedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedCOP(ratedCOP);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedSensibleHeatRatio();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedEvaporatorInletAirDryBulbTemperature() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedEvaporatorInletAirDryBulbTemperature();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedEvaporatorInletAirDryBulbTemperature(
    ratedEvaporatorInletAirDryBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedEvaporatorInletAirWetBulbTemperature() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedEvaporatorInletAirWetBulbTemperature();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedEvaporatorInletAirWetBulbTemperature(
    ratedEvaporatorInletAirWetBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump::ratedCondenserInletWaterTemperature() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedCondenserInletWaterTemperature();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedCondenserInletWaterTemperature(ratedCondenserInletWaterTemperature);
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump::ratedEvaporatorAirFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedEvaporatorAirFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPump::isRatedEvaporatorAirFlowRateAutosized() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->isRatedEvaporatorAirFlowRateAutosized();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump::autosizeRatedEvaporatorAirFlowRate() {
  getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->autosizeRatedEvaporatorAirFlowRate();
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump::ratedCondenserWaterFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->ratedCondenserWaterFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPump::isRatedCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->isRatedCondenserWaterFlowRateAutosized();
}

bool CoilWaterHeatingAirToWaterHeatPump::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setRatedCondenserWaterFlowRate(ratedCondenserWaterFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump::autosizeRatedCondenserWaterFlowRate() {
  getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->autosizeRatedCondenserWaterFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPump::evaporatorFanPowerIncludedinRatedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->evaporatorFanPowerIncludedinRatedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setEvaporatorFanPowerIncludedinRatedCOP(
    evaporatorFanPowerIncludedinRatedCOP);
}

bool CoilWaterHeatingAirToWaterHeatPump::condenserPumpPowerIncludedinRatedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->condenserPumpPowerIncludedinRatedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCondenserPumpPowerIncludedinRatedCOP(bool condenserPumpPowerIncludedinRatedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCondenserPumpPowerIncludedinRatedCOP(
    condenserPumpPowerIncludedinRatedCOP);
}

bool CoilWaterHeatingAirToWaterHeatPump::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
  bool condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
    condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP);
}

double CoilWaterHeatingAirToWaterHeatPump::condenserWaterPumpPower() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->condenserWaterPumpPower();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCondenserWaterPumpPower(double condenserWaterPumpPower) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCondenserWaterPumpPower(condenserWaterPumpPower);
}

double CoilWaterHeatingAirToWaterHeatPump::fractionofCondenserPumpHeattoWater() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->fractionofCondenserPumpHeattoWater();
}

bool CoilWaterHeatingAirToWaterHeatPump::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setFractionofCondenserPumpHeattoWater(
    fractionofCondenserPumpHeattoWater);
}

double CoilWaterHeatingAirToWaterHeatPump::crankcaseHeaterCapacity() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->crankcaseHeaterCapacity();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
}

boost::optional<Curve> CoilWaterHeatingAirToWaterHeatPump::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(
  const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(
    crankcaseHeaterCapacityFunctionofTemperatureCurve);
}

void CoilWaterHeatingAirToWaterHeatPump::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
  getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
}

double CoilWaterHeatingAirToWaterHeatPump::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->maximumAmbientTemperatureforCrankcaseHeaterOperation();
}

bool CoilWaterHeatingAirToWaterHeatPump::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
  double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
    maximumAmbientTemperatureforCrankcaseHeaterOperation);
}

std::string CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjects() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->evaporatorAirTemperatureTypeforCurveObjects();
}

bool CoilWaterHeatingAirToWaterHeatPump::setEvaporatorAirTemperatureTypeforCurveObjects(
  const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setEvaporatorAirTemperatureTypeforCurveObjects(
    evaporatorAirTemperatureTypeforCurveObjects);
}

Curve CoilWaterHeatingAirToWaterHeatPump::heatingCapacityFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->heatingCapacityFunctionofTemperatureCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setHeatingCapacityFunctionofTemperatureCurve(const Curve& heatingCapacityFunctionofTemperatureCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setHeatingCapacityFunctionofTemperatureCurve(
    heatingCapacityFunctionofTemperatureCurve);
}

Curve CoilWaterHeatingAirToWaterHeatPump::heatingCapacityFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->heatingCapacityFunctionofAirFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setHeatingCapacityFunctionofAirFlowFractionCurve(
  const Curve& heatingCapacityFunctionofAirFlowFractionCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setHeatingCapacityFunctionofAirFlowFractionCurve(
    heatingCapacityFunctionofAirFlowFractionCurve);
}

Curve CoilWaterHeatingAirToWaterHeatPump::heatingCapacityFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->heatingCapacityFunctionofWaterFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setHeatingCapacityFunctionofWaterFlowFractionCurve(
  const Curve& heatingCapacityFunctionofWaterFlowFractionCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setHeatingCapacityFunctionofWaterFlowFractionCurve(
    heatingCapacityFunctionofWaterFlowFractionCurve);
}

Curve CoilWaterHeatingAirToWaterHeatPump::heatingCOPFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->heatingCOPFunctionofTemperatureCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setHeatingCOPFunctionofTemperatureCurve(const Curve& heatingCOPFunctionofTemperatureCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setHeatingCOPFunctionofTemperatureCurve(
    heatingCOPFunctionofTemperatureCurve);
}

Curve CoilWaterHeatingAirToWaterHeatPump::heatingCOPFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->heatingCOPFunctionofAirFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setHeatingCOPFunctionofAirFlowFractionCurve(
  const Curve& heatingCOPFunctionofAirFlowFractionCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setHeatingCOPFunctionofAirFlowFractionCurve(
    heatingCOPFunctionofAirFlowFractionCurve);
}

Curve CoilWaterHeatingAirToWaterHeatPump::heatingCOPFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->heatingCOPFunctionofWaterFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setHeatingCOPFunctionofWaterFlowFractionCurve(
  const Curve& heatingCOPFunctionofWaterFlowFractionCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setHeatingCOPFunctionofWaterFlowFractionCurve(
    heatingCOPFunctionofWaterFlowFractionCurve);
}

Curve CoilWaterHeatingAirToWaterHeatPump::partLoadFractionCorrelationCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->partLoadFractionCorrelationCurve();
}

bool CoilWaterHeatingAirToWaterHeatPump::setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->setPartLoadFractionCorrelationCurve(
    partLoadFractionCorrelationCurve);
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump::autosizedRatedEvaporatorAirFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->autosizedRatedEvaporatorAirFlowRate();
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump::autosizedRatedCondenserWaterFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPump_Impl>()->autosizedRatedCondenserWaterFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

Schedule CoilWaterHeatingAirToWaterHeatPump_Impl::availabilitySchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::AvailabilityScheduleName);
  if (!schedule) {
    LOG_FREE(Error, "openstudio.epmodel.CoilWaterHeatingAirToWaterHeatPump",
             "Required availability schedule not set, returning the model always-on discrete schedule and repairing persisted state");
    schedule = model().alwaysOnDiscreteSchedule();
    OS_ASSERT(schedule);
    OS_ASSERT(const_cast<CoilWaterHeatingAirToWaterHeatPump_Impl*>(this)->setAvailabilitySchedule(*schedule));
    schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
      openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::AvailabilityScheduleName);
  }
  OS_ASSERT(schedule);
  return *schedule;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setAvailabilitySchedule(Schedule& availabilitySchedule) {
  return setSchedule(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::AvailabilityScheduleName,
                     "CoilWaterHeatingAirToWaterHeatPump", "Availability Schedule", availabilitySchedule);
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::airInletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirInletNodeName;
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::airOutletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirOutletNodeName;
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::waterInletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterInletNodeName;
}

unsigned CoilWaterHeatingAirToWaterHeatPump_Impl::waterOutletPort() const {
  return openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterOutletNodeName;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::addToNode(Node& node) {
  (void)node;
  return false;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::addToSplitter(Splitter& splitter) {
  (void)splitter;
  return false;
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedHeatingCapacity() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedHeatingCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedHeatingCapacity, ratedHeatingCapacity);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedCOP() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedCOP(double ratedCOP) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCOP, ratedCOP);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedSensibleHeatRatio() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedSensibleHeatRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedSensibleHeatRatio, ratedSensibleHeatRatio);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedEvaporatorInletAirDryBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirDryBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirDryBulbTemperature,
                   ratedEvaporatorInletAirDryBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedEvaporatorInletAirWetBulbTemperature() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirWetBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirWetBulbTemperature,
                   ratedEvaporatorInletAirWetBulbTemperature);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::ratedCondenserInletWaterTemperature() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserInletWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedCondenserInletWaterTemperature(double ratedCondenserInletWaterTemperature) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserInletWaterTemperature,
                   ratedCondenserInletWaterTemperature);
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump_Impl::ratedEvaporatorAirFlowRate() const {
  return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, true);
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::isRatedEvaporatorAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump_Impl::autosizeRatedEvaporatorAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, "autosize"));
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump_Impl::ratedCondenserWaterFlowRate() const {
  return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, true);
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::isRatedCondenserWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setRatedCondenserWaterFlowRate(double ratedCondenserWaterFlowRate) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, ratedCondenserWaterFlowRate);
}

void CoilWaterHeatingAirToWaterHeatPump_Impl::autosizeRatedCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, "autosize"));
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::evaporatorFanPowerIncludedinRatedCOP() const {
  const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorFanPowerIncludedinRatedCOP, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP) {
  const bool result = setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorFanPowerIncludedinRatedCOP,
                                evaporatorFanPowerIncludedinRatedCOP ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::condenserPumpPowerIncludedinRatedCOP() const {
  const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpPowerIncludedinRatedCOP, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCondenserPumpPowerIncludedinRatedCOP(bool condenserPumpPowerIncludedinRatedCOP) {
  const bool result = setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpPowerIncludedinRatedCOP,
                                condenserPumpPowerIncludedinRatedCOP ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP() const {
  const auto value =
    getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(
  bool condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP) {
  const bool result = setString(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP,
    condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::condenserWaterPumpPower() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterPumpPower, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCondenserWaterPumpPower(double condenserWaterPumpPower) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterPumpPower, condenserWaterPumpPower);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::fractionofCondenserPumpHeattoWater() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::FractionofCondenserPumpHeattoWater, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setFractionofCondenserPumpHeattoWater(double fractionofCondenserPumpHeattoWater) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::FractionofCondenserPumpHeattoWater,
                   fractionofCondenserPumpHeattoWater);
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::crankcaseHeaterCapacity() const {
  const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
}

boost::optional<Curve> CoilWaterHeatingAirToWaterHeatPump_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(
  const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName,
                    crankcaseHeaterCapacityFunctionofTemperatureCurve.handle(), false);
}

void CoilWaterHeatingAirToWaterHeatPump_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
  OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, ""));
}

double CoilWaterHeatingAirToWaterHeatPump_Impl::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
  const auto value =
    getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
  double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
  return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation,
                   maximumAmbientTemperatureforCrankcaseHeaterOperation);
}

std::string CoilWaterHeatingAirToWaterHeatPump_Impl::evaporatorAirTemperatureTypeforCurveObjects() const {
  const auto value =
    getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setEvaporatorAirTemperatureTypeforCurveObjects(
  const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
  return setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects,
                   evaporatorAirTemperatureTypeforCurveObjects);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::heatingCapacityFunctionofTemperatureCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofTemperatureCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setHeatingCapacityFunctionofTemperatureCurve(const Curve& heatingCapacityFunctionofTemperatureCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofTemperatureCurveName,
                    heatingCapacityFunctionofTemperatureCurve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::heatingCapacityFunctionofAirFlowFractionCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofAirFlowFractionCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setHeatingCapacityFunctionofAirFlowFractionCurve(
  const Curve& heatingCapacityFunctionofAirFlowFractionCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofAirFlowFractionCurveName,
                    heatingCapacityFunctionofAirFlowFractionCurve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::heatingCapacityFunctionofWaterFlowFractionCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofWaterFlowFractionCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setHeatingCapacityFunctionofWaterFlowFractionCurve(
  const Curve& heatingCapacityFunctionofWaterFlowFractionCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofWaterFlowFractionCurveName,
                    heatingCapacityFunctionofWaterFlowFractionCurve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::heatingCOPFunctionofTemperatureCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofTemperatureCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setHeatingCOPFunctionofTemperatureCurve(const Curve& heatingCOPFunctionofTemperatureCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofTemperatureCurveName,
                    heatingCOPFunctionofTemperatureCurve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::heatingCOPFunctionofAirFlowFractionCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofAirFlowFractionCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setHeatingCOPFunctionofAirFlowFractionCurve(
  const Curve& heatingCOPFunctionofAirFlowFractionCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofAirFlowFractionCurveName,
                    heatingCOPFunctionofAirFlowFractionCurve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::heatingCOPFunctionofWaterFlowFractionCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofWaterFlowFractionCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setHeatingCOPFunctionofWaterFlowFractionCurve(
  const Curve& heatingCOPFunctionofWaterFlowFractionCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofWaterFlowFractionCurveName,
                    heatingCOPFunctionofWaterFlowFractionCurve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPump_Impl::partLoadFractionCorrelationCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::PartLoadFractionCorrelationCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilWaterHeatingAirToWaterHeatPump_Impl::setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve) {
  return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::PartLoadFractionCorrelationCurveName,
                    partLoadFractionCorrelationCurve.handle(), false);
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump_Impl::autosizedRatedEvaporatorAirFlowRate() const {
  return boost::none;
}

boost::optional<double> CoilWaterHeatingAirToWaterHeatPump_Impl::autosizedRatedCondenserWaterFlowRate() const {
  return boost::none;
}

std::vector<std::string> CoilWaterHeatingAirToWaterHeatPump_Impl::evaporatorAirTemperatureTypeforCurveObjectsValues() const {
  return openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjectsValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
