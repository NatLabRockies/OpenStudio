/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "StraightComponent/CoilHeatingDXSingleSpeed_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingDXSingleSpeed::CoilHeatingDXSingleSpeed(const Model& model, Schedule& availabilitySchedule,
                                                     Curve& totalHeatingCapacityFunctionofTemperatureCurve,
                                                     Curve& totalHeatingCapacityFunctionofFlowFractionCurve,
                                                     Curve& energyInputRatioFunctionofTemperatureCurve,
                                                     Curve& energyInputRatioFunctionofFlowFractionCurve, Curve& partLoadFractionCorrelationCurve)
    : StraightComponent(CoilHeatingDXSingleSpeed::iddObjectType(), model) {
    bool ok = true;

    ok = setAvailabilitySchedule(availabilitySchedule);
    OS_ASSERT(ok);
    ok = setTotalHeatingCapacityFunctionofTemperatureCurve(totalHeatingCapacityFunctionofTemperatureCurve);
    OS_ASSERT(ok);
    ok = setTotalHeatingCapacityFunctionofFlowFractionCurve(totalHeatingCapacityFunctionofFlowFractionCurve);
    OS_ASSERT(ok);
    ok = setEnergyInputRatioFunctionofTemperatureCurve(energyInputRatioFunctionofTemperatureCurve);
    OS_ASSERT(ok);
    ok = setEnergyInputRatioFunctionofFlowFractionCurve(energyInputRatioFunctionofFlowFractionCurve);
    OS_ASSERT(ok);
    ok = setPartLoadFractionCorrelationCurve(partLoadFractionCorrelationCurve);
    OS_ASSERT(ok);

    autosizeRatedTotalHeatingCapacity();
    autosizeRatedAirFlowRate();

    ok = setRatedSupplyFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedSupplyFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);
    ok = setRatedCOP(5.0);
    OS_ASSERT(ok);

    ok = setDefrostStrategy("Resistive");
    OS_ASSERT(ok);
    ok = setDefrostControl("Timed");
    OS_ASSERT(ok);
    ok = setDefrostTimePeriodFraction(0.166667);
    OS_ASSERT(ok);
    ok = setResistiveDefrostHeaterCapacity(2000.0);
    OS_ASSERT(ok);
  }

  CoilHeatingDXSingleSpeed::CoilHeatingDXSingleSpeed(const Model& model) : StraightComponent(CoilHeatingDXSingleSpeed::iddObjectType(), model) {
    bool ok = true;

    auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(availabilitySchedule);
    OS_ASSERT(ok);

    CurveCubic totalHeatingCapacityFunctionofTemperatureCurve(model);
    ok = totalHeatingCapacityFunctionofTemperatureCurve.setCoefficient1Constant(0.758746);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofTemperatureCurve.setCoefficient2x(0.027626);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofTemperatureCurve.setCoefficient3xPOW2(0.000148716);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofTemperatureCurve.setCoefficient4xPOW3(0.0000034992);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofTemperatureCurve.setMinimumValueofx(-20.0);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofTemperatureCurve.setMaximumValueofx(20.0);
    OS_ASSERT(ok);

    CurveCubic totalHeatingCapacityFunctionofFlowFractionCurve(model);
    ok = totalHeatingCapacityFunctionofFlowFractionCurve.setCoefficient1Constant(0.84);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofFlowFractionCurve.setCoefficient2x(0.16);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofFlowFractionCurve.setCoefficient3xPOW2(0.0);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofFlowFractionCurve.setCoefficient4xPOW3(0.0);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofFlowFractionCurve.setMinimumValueofx(0.5);
    OS_ASSERT(ok);
    ok = totalHeatingCapacityFunctionofFlowFractionCurve.setMaximumValueofx(1.5);
    OS_ASSERT(ok);

    CurveCubic energyInputRatioFunctionofTemperatureCurve(model);
    ok = energyInputRatioFunctionofTemperatureCurve.setCoefficient1Constant(1.19248);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofTemperatureCurve.setCoefficient2x(-0.0300438);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofTemperatureCurve.setCoefficient3xPOW2(0.00103745);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofTemperatureCurve.setCoefficient4xPOW3(-0.000023328);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofTemperatureCurve.setMinimumValueofx(-20.0);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofTemperatureCurve.setMaximumValueofx(20.0);
    OS_ASSERT(ok);

    CurveQuadratic energyInputRatioFunctionofFlowFractionCurve(model);
    ok = energyInputRatioFunctionofFlowFractionCurve.setCoefficient1Constant(1.3824);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofFlowFractionCurve.setCoefficient2x(-0.4336);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofFlowFractionCurve.setCoefficient3xPOW2(0.0512);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofFlowFractionCurve.setMinimumValueofx(0.0);
    OS_ASSERT(ok);
    ok = energyInputRatioFunctionofFlowFractionCurve.setMaximumValueofx(1.0);
    OS_ASSERT(ok);

    CurveQuadratic partLoadFractionCorrelationCurve(model);
    ok = partLoadFractionCorrelationCurve.setCoefficient1Constant(0.75);
    OS_ASSERT(ok);
    ok = partLoadFractionCorrelationCurve.setCoefficient2x(0.25);
    OS_ASSERT(ok);
    ok = partLoadFractionCorrelationCurve.setCoefficient3xPOW2(0.0);
    OS_ASSERT(ok);
    ok = partLoadFractionCorrelationCurve.setMinimumValueofx(0.0);
    OS_ASSERT(ok);
    ok = partLoadFractionCorrelationCurve.setMaximumValueofx(1.0);
    OS_ASSERT(ok);

    ok = setTotalHeatingCapacityFunctionofTemperatureCurve(totalHeatingCapacityFunctionofTemperatureCurve);
    OS_ASSERT(ok);
    ok = setTotalHeatingCapacityFunctionofFlowFractionCurve(totalHeatingCapacityFunctionofFlowFractionCurve);
    OS_ASSERT(ok);
    ok = setEnergyInputRatioFunctionofTemperatureCurve(energyInputRatioFunctionofTemperatureCurve);
    OS_ASSERT(ok);
    ok = setEnergyInputRatioFunctionofFlowFractionCurve(energyInputRatioFunctionofFlowFractionCurve);
    OS_ASSERT(ok);
    ok = setPartLoadFractionCorrelationCurve(partLoadFractionCorrelationCurve);
    OS_ASSERT(ok);

    autosizeRatedTotalHeatingCapacity();
    autosizeRatedAirFlowRate();

    ok = setRatedSupplyFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedSupplyFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);
    ok = setRatedCOP(5.0);
    OS_ASSERT(ok);

    ok = setDefrostStrategy("Resistive");
    OS_ASSERT(ok);
    ok = setDefrostControl("Timed");
    OS_ASSERT(ok);
    ok = setDefrostTimePeriodFraction(0.166667);
    OS_ASSERT(ok);
    ok = setResistiveDefrostHeaterCapacity(2000.0);
    OS_ASSERT(ok);
  }

  CoilHeatingDXSingleSpeed::CoilHeatingDXSingleSpeed(std::shared_ptr<detail::CoilHeatingDXSingleSpeed_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingDXSingleSpeed::iddObjectType() {
    return IddObjectType::Coil_Heating_DX_SingleSpeed;
  }

  std::vector<std::string> CoilHeatingDXSingleSpeed::validDefrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy);
  }

  std::vector<std::string> CoilHeatingDXSingleSpeed::validDefrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl);
  }

  Schedule CoilHeatingDXSingleSpeed::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingDXSingleSpeed::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setAvailabilitySchedule(schedule);
  }

  Curve CoilHeatingDXSingleSpeed::totalHeatingCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->totalHeatingCapacityFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXSingleSpeed::setTotalHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setTotalHeatingCapacityFunctionofTemperatureCurve(curve);
  }

  Curve CoilHeatingDXSingleSpeed::totalHeatingCapacityFunctionofFlowFractionCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->totalHeatingCapacityFunctionofFlowFractionCurve();
  }

  bool CoilHeatingDXSingleSpeed::setTotalHeatingCapacityFunctionofFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setTotalHeatingCapacityFunctionofFlowFractionCurve(curve);
  }

  Curve CoilHeatingDXSingleSpeed::energyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->energyInputRatioFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXSingleSpeed::setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setEnergyInputRatioFunctionofTemperatureCurve(curve);
  }

  Curve CoilHeatingDXSingleSpeed::energyInputRatioFunctionofFlowFractionCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->energyInputRatioFunctionofFlowFractionCurve();
  }

  bool CoilHeatingDXSingleSpeed::setEnergyInputRatioFunctionofFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setEnergyInputRatioFunctionofFlowFractionCurve(curve);
  }

  Curve CoilHeatingDXSingleSpeed::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilHeatingDXSingleSpeed::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  boost::optional<Curve> CoilHeatingDXSingleSpeed::defrostEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostEnergyInputRatioFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostEnergyInputRatioFunctionofTemperatureCurve(curve);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostEnergyInputRatioFunctionofTemperatureCurve() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  }

  boost::optional<double> CoilHeatingDXSingleSpeed::ratedTotalHeatingCapacity() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedTotalHeatingCapacity();
  }

  bool CoilHeatingDXSingleSpeed::isRatedTotalHeatingCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isRatedTotalHeatingCapacityAutosized();
  }

  bool CoilHeatingDXSingleSpeed::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedTotalHeatingCapacity(ratedTotalHeatingCapacity);
  }

  void CoilHeatingDXSingleSpeed::autosizeRatedTotalHeatingCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->autosizeRatedTotalHeatingCapacity();
  }

  double CoilHeatingDXSingleSpeed::ratedCOP() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedCOP();
  }

  bool CoilHeatingDXSingleSpeed::setRatedCOP(double ratedCOP) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedCOP(ratedCOP);
  }

  boost::optional<double> CoilHeatingDXSingleSpeed::ratedAirFlowRate() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedAirFlowRate();
  }

  bool CoilHeatingDXSingleSpeed::isRatedAirFlowRateAutosized() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isRatedAirFlowRateAutosized();
  }

  bool CoilHeatingDXSingleSpeed::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void CoilHeatingDXSingleSpeed::autosizeRatedAirFlowRate() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->autosizeRatedAirFlowRate();
  }

  double CoilHeatingDXSingleSpeed::ratedSupplyFanPowerPerVolumeFlowRate() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedSupplyFanPowerPerVolumeFlowRate2017();
  }

  double CoilHeatingDXSingleSpeed::ratedSupplyFanPowerPerVolumeFlowRate2017() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedSupplyFanPowerPerVolumeFlowRate2017();
  }

  bool CoilHeatingDXSingleSpeed::setRatedSupplyFanPowerPerVolumeFlowRate(double ratedSupplyFanPowerPerVolumeFlowRate) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedSupplyFanPowerPerVolumeFlowRate2017(ratedSupplyFanPowerPerVolumeFlowRate);
  }

  bool CoilHeatingDXSingleSpeed::setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedSupplyFanPowerPerVolumeFlowRate2017(ratedSupplyFanPowerPerVolumeFlowRate2017);
  }

  double CoilHeatingDXSingleSpeed::ratedSupplyFanPowerPerVolumeFlowRate2023() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedSupplyFanPowerPerVolumeFlowRate2023();
  }

  bool CoilHeatingDXSingleSpeed::setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedSupplyFanPowerPerVolumeFlowRate2023(ratedSupplyFanPowerPerVolumeFlowRate2023);
  }

  double CoilHeatingDXSingleSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  bool CoilHeatingDXSingleSpeed::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  void CoilHeatingDXSingleSpeed::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  double CoilHeatingDXSingleSpeed::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforDefrostOperation();
  }

  bool CoilHeatingDXSingleSpeed::isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
      maximumOutdoorDryBulbTemperatureforDefrostOperation);
  }

  void CoilHeatingDXSingleSpeed::resetMaximumOutdoorDryBulbTemperatureforDefrostOperation() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();
  }

  double CoilHeatingDXSingleSpeed::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->crankcaseHeaterCapacity();
  }

  bool CoilHeatingDXSingleSpeed::isCrankcaseHeaterCapacityDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isCrankcaseHeaterCapacityDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  void CoilHeatingDXSingleSpeed::resetCrankcaseHeaterCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetCrankcaseHeaterCapacity();
  }

  boost::optional<Curve> CoilHeatingDXSingleSpeed::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXSingleSpeed::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(curve);
  }

  void CoilHeatingDXSingleSpeed::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  double CoilHeatingDXSingleSpeed::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }

  bool CoilHeatingDXSingleSpeed::isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  }

  void CoilHeatingDXSingleSpeed::resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }

  std::string CoilHeatingDXSingleSpeed::defrostStrategy() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostStrategy();
  }

  bool CoilHeatingDXSingleSpeed::isDefrostStrategyDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isDefrostStrategyDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostStrategy(const std::string& defrostStrategy) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostStrategy(defrostStrategy);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostStrategy() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostStrategy();
  }

  std::string CoilHeatingDXSingleSpeed::defrostControl() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostControl();
  }

  bool CoilHeatingDXSingleSpeed::isDefrostControlDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isDefrostControlDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostControl(const std::string& defrostControl) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostControl(defrostControl);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostControl() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostControl();
  }

  double CoilHeatingDXSingleSpeed::defrostTimePeriodFraction() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostTimePeriodFraction();
  }

  bool CoilHeatingDXSingleSpeed::isDefrostTimePeriodFractionDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isDefrostTimePeriodFractionDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostTimePeriodFraction(defrostTimePeriodFraction);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostTimePeriodFraction() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostTimePeriodFraction();
  }

  boost::optional<double> CoilHeatingDXSingleSpeed::resistiveDefrostHeaterCapacity() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resistiveDefrostHeaterCapacity();
  }

  bool CoilHeatingDXSingleSpeed::isResistiveDefrostHeaterCapacityDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isResistiveDefrostHeaterCapacityDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::isResistiveDefrostHeaterCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isResistiveDefrostHeaterCapacityAutosized();
  }

  bool CoilHeatingDXSingleSpeed::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity);
  }

  void CoilHeatingDXSingleSpeed::resetResistiveDefrostHeaterCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetResistiveDefrostHeaterCapacity();
  }

  bool CoilHeatingDXSingleSpeed::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->addToNode(node);
  }

  void CoilHeatingDXSingleSpeed::autosizeResistiveDefrostHeaterCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->autosizeResistiveDefrostHeaterCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
        if (const auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

    }  // namespace

    bool CoilHeatingDXSingleSpeed_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    unsigned CoilHeatingDXSingleSpeed_Impl::inletPort() const {
      return openstudio::Coil_Heating_DX_SingleSpeedFields::AirInletNodeName;
    }

    unsigned CoilHeatingDXSingleSpeed_Impl::outletPort() const {
      return openstudio::Coil_Heating_DX_SingleSpeedFields::AirOutletNodeName;
    }

    Schedule CoilHeatingDXSingleSpeed_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilHeatingDXSingleSpeed_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    Curve CoilHeatingDXSingleSpeed_Impl::totalHeatingCapacityFunctionofTemperatureCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXSingleSpeed_Impl::setTotalHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
    }

    Curve CoilHeatingDXSingleSpeed_Impl::totalHeatingCapacityFunctionofFlowFractionCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofFlowFractionCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXSingleSpeed_Impl::setTotalHeatingCapacityFunctionofFlowFractionCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofFlowFractionCurveName, curve.handle(), false);
    }

    Curve CoilHeatingDXSingleSpeed_Impl::energyInputRatioFunctionofTemperatureCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXSingleSpeed_Impl::setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
    }

    Curve CoilHeatingDXSingleSpeed_Impl::energyInputRatioFunctionofFlowFractionCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXSingleSpeed_Impl::setEnergyInputRatioFunctionofFlowFractionCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, curve.handle(), false);
    }

    Curve CoilHeatingDXSingleSpeed_Impl::partLoadFractionCorrelationCurve() const {
      const auto curve =
        getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Coil_Heating_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXSingleSpeed_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName, curve.handle(), false);
    }

    boost::optional<Curve> CoilHeatingDXSingleSpeed_Impl::defrostEnergyInputRatioFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostEnergyInputRatioFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, Handle(), false));
    }

    std::vector<ModelObject> CoilHeatingDXSingleSpeed_Impl::children() const {
      std::vector<ModelObject> result{
        totalHeatingCapacityFunctionofTemperatureCurve(),
        totalHeatingCapacityFunctionofFlowFractionCurve(),
        energyInputRatioFunctionofTemperatureCurve(),
        energyInputRatioFunctionofFlowFractionCurve(),
        partLoadFractionCorrelationCurve(),
      };
      if (auto crankcaseCurve = crankcaseHeaterCapacityFunctionofTemperatureCurve()) {
        result.push_back(*crankcaseCurve);
      }
      return result;
    }

    boost::optional<double> CoilHeatingDXSingleSpeed_Impl::ratedTotalHeatingCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, true);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isRatedTotalHeatingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity);
    }

    double CoilHeatingDXSingleSpeed_Impl::ratedCOP() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> CoilHeatingDXSingleSpeed_Impl::ratedAirFlowRate() const {
      return getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, true);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isRatedAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate);
    }

    double CoilHeatingDXSingleSpeed_Impl::ratedSupplyFanPowerPerVolumeFlowRate2017() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2017, true);
      OS_ASSERT(value);
      return *value;
    }

    double CoilHeatingDXSingleSpeed_Impl::ratedSupplyFanPowerPerVolumeFlowRate2023() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2023, true);
      OS_ASSERT(value);
      return *value;
    }

    double CoilHeatingDXSingleSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    double CoilHeatingDXSingleSpeed_Impl::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation);
    }

    double CoilHeatingDXSingleSpeed_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isCrankcaseHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity);
    }

    double CoilHeatingDXSingleSpeed_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    std::vector<std::string> CoilHeatingDXSingleSpeed_Impl::validDefrostStrategyValues() const {
      return CoilHeatingDXSingleSpeed::validDefrostStrategyValues();
    }

    std::string CoilHeatingDXSingleSpeed_Impl::defrostStrategy() const {
      const auto value = getString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isDefrostStrategyDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy);
    }

    std::vector<std::string> CoilHeatingDXSingleSpeed_Impl::validDefrostControlValues() const {
      return CoilHeatingDXSingleSpeed::validDefrostControlValues();
    }

    std::string CoilHeatingDXSingleSpeed_Impl::defrostControl() const {
      const auto value = getString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isDefrostControlDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl);
    }

    double CoilHeatingDXSingleSpeed_Impl::defrostTimePeriodFraction() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isDefrostTimePeriodFractionDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction);
    }

    boost::optional<double> CoilHeatingDXSingleSpeed_Impl::resistiveDefrostHeaterCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, true);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isResistiveDefrostHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, ratedTotalHeatingCapacity);
    }

    void CoilHeatingDXSingleSpeed_Impl::autosizeRatedTotalHeatingCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, "autosize");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedCOP(double ratedCOP) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCOP, ratedCOP);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, ratedAirFlowRate);
    }

    void CoilHeatingDXSingleSpeed_Impl::autosizeRatedAirFlowRate() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2017,
                       ratedSupplyFanPowerPerVolumeFlowRate2017);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2023,
                       ratedSupplyFanPowerPerVolumeFlowRate2023);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
      double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation,
                       maximumOutdoorDryBulbTemperatureforDefrostOperation);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetMaximumOutdoorDryBulbTemperatureforDefrostOperation() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetCrankcaseHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, "");
      OS_ASSERT(result);
    }

    boost::optional<Curve> CoilHeatingDXSingleSpeed_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, curve.handle(), false);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, Handle(), false));
    }

    bool CoilHeatingDXSingleSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
      return setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, defrostStrategy);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostStrategy() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostControl(const std::string& defrostControl) {
      return setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl, defrostControl);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostControl() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, defrostTimePeriodFraction);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostTimePeriodFraction() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetResistiveDefrostHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, "");
      OS_ASSERT(result);
    }

    void CoilHeatingDXSingleSpeed_Impl::autosizeResistiveDefrostHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, "autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
