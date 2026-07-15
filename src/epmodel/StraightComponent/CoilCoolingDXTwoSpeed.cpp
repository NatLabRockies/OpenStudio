/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXTwoSpeed.hpp"
#include "StraightComponent/CoilCoolingDXTwoSpeed_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(CoilCoolingDXTwoSpeed& coil) {
      const auto& model = coil.model();

      ScheduleConstant availability(model);
      OS_ASSERT(availability.setValue(1.0));
      OS_ASSERT(coil.setAvailabilitySchedule(availability));

      CurveBiquadratic totalCoolingCapacityFunctionOfTemperatureCurve(model);
      totalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient1Constant(0.42415);
      totalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient2x(0.04426);
      totalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient3xPOW2(-0.00042);
      totalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient4y(0.00333);
      totalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient5yPOW2(-0.00008);
      totalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient6xTIMESY(-0.00021);
      totalCoolingCapacityFunctionOfTemperatureCurve.setMinimumValueofx(17.0);
      totalCoolingCapacityFunctionOfTemperatureCurve.setMaximumValueofx(22.0);
      totalCoolingCapacityFunctionOfTemperatureCurve.setMinimumValueofy(13.0);
      totalCoolingCapacityFunctionOfTemperatureCurve.setMaximumValueofy(46.0);
      OS_ASSERT(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(totalCoolingCapacityFunctionOfTemperatureCurve));

      CurveQuadratic totalCoolingCapacityFunctionOfFlowFractionCurve(model);
      totalCoolingCapacityFunctionOfFlowFractionCurve.setCoefficient1Constant(0.77136);
      totalCoolingCapacityFunctionOfFlowFractionCurve.setCoefficient2x(0.34053);
      totalCoolingCapacityFunctionOfFlowFractionCurve.setCoefficient3xPOW2(-0.11088);
      totalCoolingCapacityFunctionOfFlowFractionCurve.setMinimumValueofx(0.75918);
      totalCoolingCapacityFunctionOfFlowFractionCurve.setMaximumValueofx(1.13877);
      OS_ASSERT(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(totalCoolingCapacityFunctionOfFlowFractionCurve));

      CurveBiquadratic energyInputRatioFunctionOfTemperatureCurve(model);
      energyInputRatioFunctionOfTemperatureCurve.setCoefficient1Constant(1.23649);
      energyInputRatioFunctionOfTemperatureCurve.setCoefficient2x(-0.02431);
      energyInputRatioFunctionOfTemperatureCurve.setCoefficient3xPOW2(0.00057);
      energyInputRatioFunctionOfTemperatureCurve.setCoefficient4y(-0.01434);
      energyInputRatioFunctionOfTemperatureCurve.setCoefficient5yPOW2(0.00063);
      energyInputRatioFunctionOfTemperatureCurve.setCoefficient6xTIMESY(-0.00038);
      energyInputRatioFunctionOfTemperatureCurve.setMinimumValueofx(17.0);
      energyInputRatioFunctionOfTemperatureCurve.setMaximumValueofx(22.0);
      energyInputRatioFunctionOfTemperatureCurve.setMinimumValueofy(13.0);
      energyInputRatioFunctionOfTemperatureCurve.setMaximumValueofy(46.0);
      OS_ASSERT(coil.setEnergyInputRatioFunctionOfTemperatureCurve(energyInputRatioFunctionOfTemperatureCurve));

      CurveQuadratic energyInputRatioFunctionOfFlowFractionCurve(model);
      energyInputRatioFunctionOfFlowFractionCurve.setCoefficient1Constant(1.20550);
      energyInputRatioFunctionOfFlowFractionCurve.setCoefficient2x(-0.32953);
      energyInputRatioFunctionOfFlowFractionCurve.setCoefficient3xPOW2(0.12308);
      energyInputRatioFunctionOfFlowFractionCurve.setMinimumValueofx(0.75918);
      energyInputRatioFunctionOfFlowFractionCurve.setMaximumValueofx(1.13877);
      OS_ASSERT(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(energyInputRatioFunctionOfFlowFractionCurve));

      CurveQuadratic partLoadFractionCorrelationCurve(model);
      partLoadFractionCorrelationCurve.setCoefficient1Constant(0.77100);
      partLoadFractionCorrelationCurve.setCoefficient2x(0.22900);
      partLoadFractionCorrelationCurve.setCoefficient3xPOW2(0.0);
      partLoadFractionCorrelationCurve.setMinimumValueofx(0.0);
      partLoadFractionCorrelationCurve.setMaximumValueofx(1.0);
      OS_ASSERT(coil.setPartLoadFractionCorrelationCurve(partLoadFractionCorrelationCurve));

      CurveBiquadratic lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(model);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient1Constant(0.42415);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient2x(0.04426);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient3xPOW2(-0.00042);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient4y(0.00333);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient5yPOW2(-0.00008);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setCoefficient6xTIMESY(-0.00021);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setMinimumValueofx(17.0);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setMaximumValueofx(22.0);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setMinimumValueofy(13.0);
      lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve.setMaximumValueofy(46.0);
      OS_ASSERT(coil.setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve));

      CurveBiquadratic lowSpeedEnergyInputRatioFunctionOfTemperatureCurve(model);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setCoefficient1Constant(1.23649);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setCoefficient2x(-0.02431);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setCoefficient3xPOW2(0.00057);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setCoefficient4y(-0.01434);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setCoefficient5yPOW2(0.00063);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setCoefficient6xTIMESY(-0.00038);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setMinimumValueofx(17.0);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setMaximumValueofx(22.0);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setMinimumValueofy(13.0);
      lowSpeedEnergyInputRatioFunctionOfTemperatureCurve.setMaximumValueofy(46.0);
      OS_ASSERT(coil.setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(lowSpeedEnergyInputRatioFunctionOfTemperatureCurve));
    }

  }  // namespace

  CoilCoolingDXTwoSpeed::CoilCoolingDXTwoSpeed(const Model& model) : StraightComponent(CoilCoolingDXTwoSpeed::iddObjectType(), model) {
    bool ok = true;
    applyConstructorDefaults(*this);

    autosizeRatedHighSpeedTotalCoolingCapacity();
    autosizeRatedHighSpeedSensibleHeatRatio();
    ok = setRatedHighSpeedCOP(3.0);
    OS_ASSERT(ok);
    autosizeRatedHighSpeedAirFlowRate();
    ok = setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);

    autosizeRatedLowSpeedTotalCoolingCapacity();
    ok = setRatedLowSpeedSensibleHeatRatio(0.69);
    OS_ASSERT(ok);
    ok = setRatedLowSpeedCOP(3.0);
    OS_ASSERT(ok);
    autosizeRatedLowSpeedAirFlowRate();
    ok = setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);

    ok = setCondenserType("AirCooled");
    OS_ASSERT(ok);

    ok = setHighSpeedEvaporativeCondenserEffectiveness(0.9);
    OS_ASSERT(ok);
    autosizeHighSpeedEvaporativeCondenserAirFlowRate();
    autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();

    ok = setLowSpeedEvaporativeCondenserEffectiveness(0.9);
    OS_ASSERT(ok);
    autosizeLowSpeedEvaporativeCondenserAirFlowRate();
    autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();

    ok = setBasinHeaterCapacity(0.0);
    OS_ASSERT(ok);
    ok = setBasinHeaterSetpointTemperature(2.0);
    OS_ASSERT(ok);

    ok = setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0);
    OS_ASSERT(ok);
    ok = setUnitInternalStaticAirPressure(773.3);
    OS_ASSERT(ok);
  }

  CoilCoolingDXTwoSpeed::CoilCoolingDXTwoSpeed(const Model& model, Schedule& availabilitySchedule, const Curve& coolingCurveFofTemp,
                                               const Curve& coolingCurveFofFlow, const Curve& energyInputRatioFofTemp,
                                               const Curve& energyInputRatioFofFlow, const Curve& partLoadFraction,
                                               const Curve& lowSpeedCoolingCurveFofTemp, const Curve& lowSpeedEnergyInputRatioFofTemp)
    : StraightComponent(CoilCoolingDXTwoSpeed::iddObjectType(), model) {
    bool ok = true;

    ok = setAvailabilitySchedule(availabilitySchedule);
    OS_ASSERT(ok);
    ok = setTotalCoolingCapacityFunctionOfTemperatureCurve(coolingCurveFofTemp);
    OS_ASSERT(ok);
    ok = setTotalCoolingCapacityFunctionOfFlowFractionCurve(coolingCurveFofFlow);
    OS_ASSERT(ok);
    ok = setEnergyInputRatioFunctionOfTemperatureCurve(energyInputRatioFofTemp);
    OS_ASSERT(ok);
    ok = setEnergyInputRatioFunctionOfFlowFractionCurve(energyInputRatioFofFlow);
    OS_ASSERT(ok);
    ok = setPartLoadFractionCorrelationCurve(partLoadFraction);
    OS_ASSERT(ok);
    ok = setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(lowSpeedCoolingCurveFofTemp);
    OS_ASSERT(ok);
    ok = setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(lowSpeedEnergyInputRatioFofTemp);
    OS_ASSERT(ok);

    autosizeRatedHighSpeedTotalCoolingCapacity();
    autosizeRatedHighSpeedSensibleHeatRatio();
    ok = setRatedHighSpeedCOP(3.0);
    OS_ASSERT(ok);
    autosizeRatedHighSpeedAirFlowRate();
    ok = setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);

    autosizeRatedLowSpeedTotalCoolingCapacity();
    ok = setRatedLowSpeedSensibleHeatRatio(0.69);
    OS_ASSERT(ok);
    ok = setRatedLowSpeedCOP(3.0);
    OS_ASSERT(ok);
    autosizeRatedLowSpeedAirFlowRate();
    ok = setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);

    ok = setCondenserType("AirCooled");
    OS_ASSERT(ok);
    ok = setHighSpeedEvaporativeCondenserEffectiveness(0.9);
    OS_ASSERT(ok);
    autosizeHighSpeedEvaporativeCondenserAirFlowRate();
    autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();
    ok = setLowSpeedEvaporativeCondenserEffectiveness(0.9);
    OS_ASSERT(ok);
    autosizeLowSpeedEvaporativeCondenserAirFlowRate();
    autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();
    ok = setBasinHeaterCapacity(0.0);
    OS_ASSERT(ok);
    ok = setBasinHeaterSetpointTemperature(2.0);
    OS_ASSERT(ok);
    ok = setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0);
    OS_ASSERT(ok);
    ok = setUnitInternalStaticAirPressure(773.3);
    OS_ASSERT(ok);
  }

  CoilCoolingDXTwoSpeed::CoilCoolingDXTwoSpeed(std::shared_ptr<detail::CoilCoolingDXTwoSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingDXTwoSpeed::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX_TwoSpeed;
  }

  std::vector<std::string> CoilCoolingDXTwoSpeed::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Cooling_DX_TwoSpeedFields::CondenserType);
  }

  Schedule CoilCoolingDXTwoSpeed::availabilitySchedule() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->availabilitySchedule();
  }

  bool CoilCoolingDXTwoSpeed::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setAvailabilitySchedule(schedule);
  }

  Curve CoilCoolingDXTwoSpeed::totalCoolingCapacityFunctionOfTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->totalCoolingCapacityFunctionOfTemperatureCurve();
  }

  bool CoilCoolingDXTwoSpeed::setTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setTotalCoolingCapacityFunctionOfTemperatureCurve(curve);
  }

  Curve CoilCoolingDXTwoSpeed::totalCoolingCapacityFunctionOfFlowFractionCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->totalCoolingCapacityFunctionOfFlowFractionCurve();
  }

  bool CoilCoolingDXTwoSpeed::setTotalCoolingCapacityFunctionOfFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setTotalCoolingCapacityFunctionOfFlowFractionCurve(curve);
  }

  Curve CoilCoolingDXTwoSpeed::energyInputRatioFunctionOfTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->energyInputRatioFunctionOfTemperatureCurve();
  }

  bool CoilCoolingDXTwoSpeed::setEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setEnergyInputRatioFunctionOfTemperatureCurve(curve);
  }

  Curve CoilCoolingDXTwoSpeed::energyInputRatioFunctionOfFlowFractionCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->energyInputRatioFunctionOfFlowFractionCurve();
  }

  bool CoilCoolingDXTwoSpeed::setEnergyInputRatioFunctionOfFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setEnergyInputRatioFunctionOfFlowFractionCurve(curve);
  }

  Curve CoilCoolingDXTwoSpeed::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilCoolingDXTwoSpeed::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  Curve CoilCoolingDXTwoSpeed::lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve();
  }

  bool CoilCoolingDXTwoSpeed::setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(curve);
  }

  Curve CoilCoolingDXTwoSpeed::lowSpeedEnergyInputRatioFunctionOfTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->lowSpeedEnergyInputRatioFunctionOfTemperatureCurve();
  }

  bool CoilCoolingDXTwoSpeed::setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(curve);
  }

  boost::optional<Schedule> CoilCoolingDXTwoSpeed::basinHeaterOperatingSchedule() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->basinHeaterOperatingSchedule();
  }

  bool CoilCoolingDXTwoSpeed::setBasinHeaterOperatingSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setBasinHeaterOperatingSchedule(schedule);
  }

  void CoilCoolingDXTwoSpeed::resetBasinHeaterOperatingSchedule() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->resetBasinHeaterOperatingSchedule();
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::ratedHighSpeedTotalCoolingCapacity() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedHighSpeedTotalCoolingCapacity();
  }
  bool CoilCoolingDXTwoSpeed::isRatedHighSpeedTotalCoolingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isRatedHighSpeedTotalCoolingCapacityAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setRatedHighSpeedTotalCoolingCapacity(double ratedHighSpeedTotalCoolingCapacity) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedHighSpeedTotalCoolingCapacity(ratedHighSpeedTotalCoolingCapacity);
  }
  void CoilCoolingDXTwoSpeed::autosizeRatedHighSpeedTotalCoolingCapacity() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeRatedHighSpeedTotalCoolingCapacity();
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::ratedHighSpeedSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedHighSpeedSensibleHeatRatio();
  }
  bool CoilCoolingDXTwoSpeed::isRatedHighSpeedSensibleHeatRatioAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isRatedHighSpeedSensibleHeatRatioAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setRatedHighSpeedSensibleHeatRatio(double ratedHighSpeedSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedHighSpeedSensibleHeatRatio(ratedHighSpeedSensibleHeatRatio);
  }
  void CoilCoolingDXTwoSpeed::autosizeRatedHighSpeedSensibleHeatRatio() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeRatedHighSpeedSensibleHeatRatio();
  }

  double CoilCoolingDXTwoSpeed::ratedHighSpeedCOP() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedHighSpeedCOP();
  }
  bool CoilCoolingDXTwoSpeed::setRatedHighSpeedCOP(double ratedHighSpeedCOP) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedHighSpeedCOP(ratedHighSpeedCOP);
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::ratedHighSpeedAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedHighSpeedAirFlowRate();
  }
  bool CoilCoolingDXTwoSpeed::isRatedHighSpeedAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isRatedHighSpeedAirFlowRateAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setRatedHighSpeedAirFlowRate(double ratedHighSpeedAirFlowRate) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedHighSpeedAirFlowRate(ratedHighSpeedAirFlowRate);
  }
  void CoilCoolingDXTwoSpeed::autosizeRatedHighSpeedAirFlowRate() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeRatedHighSpeedAirFlowRate();
  }

  double CoilCoolingDXTwoSpeed::ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017();
  }
  bool CoilCoolingDXTwoSpeed::setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(
      ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017);
  }
  double CoilCoolingDXTwoSpeed::ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023();
  }
  bool CoilCoolingDXTwoSpeed::setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(
      ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023);
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::ratedLowSpeedTotalCoolingCapacity() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedLowSpeedTotalCoolingCapacity();
  }
  bool CoilCoolingDXTwoSpeed::isRatedLowSpeedTotalCoolingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isRatedLowSpeedTotalCoolingCapacityAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setRatedLowSpeedTotalCoolingCapacity(double ratedLowSpeedTotalCoolingCapacity) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedLowSpeedTotalCoolingCapacity(ratedLowSpeedTotalCoolingCapacity);
  }
  void CoilCoolingDXTwoSpeed::autosizeRatedLowSpeedTotalCoolingCapacity() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeRatedLowSpeedTotalCoolingCapacity();
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::ratedLowSpeedSensibleHeatRatio() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedLowSpeedSensibleHeatRatio();
  }
  bool CoilCoolingDXTwoSpeed::isRatedLowSpeedSensibleHeatRatioAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isRatedLowSpeedSensibleHeatRatioAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setRatedLowSpeedSensibleHeatRatio(double ratedLowSpeedSensibleHeatRatio) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedLowSpeedSensibleHeatRatio(ratedLowSpeedSensibleHeatRatio);
  }
  void CoilCoolingDXTwoSpeed::autosizeRatedLowSpeedSensibleHeatRatio() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeRatedLowSpeedSensibleHeatRatio();
  }

  double CoilCoolingDXTwoSpeed::ratedLowSpeedCOP() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedLowSpeedCOP();
  }
  bool CoilCoolingDXTwoSpeed::setRatedLowSpeedCOP(double ratedLowSpeedCOP) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedLowSpeedCOP(ratedLowSpeedCOP);
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::ratedLowSpeedAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedLowSpeedAirFlowRate();
  }
  bool CoilCoolingDXTwoSpeed::isRatedLowSpeedAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isRatedLowSpeedAirFlowRateAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setRatedLowSpeedAirFlowRate(double ratedLowSpeedAirFlowRate) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedLowSpeedAirFlowRate(ratedLowSpeedAirFlowRate);
  }
  void CoilCoolingDXTwoSpeed::autosizeRatedLowSpeedAirFlowRate() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeRatedLowSpeedAirFlowRate();
  }

  double CoilCoolingDXTwoSpeed::ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017();
  }
  bool CoilCoolingDXTwoSpeed::setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(
      ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017);
  }
  double CoilCoolingDXTwoSpeed::ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023();
  }
  bool CoilCoolingDXTwoSpeed::setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(
      ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023);
  }

  std::string CoilCoolingDXTwoSpeed::condenserType() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->condenserType();
  }
  bool CoilCoolingDXTwoSpeed::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setCondenserType(condenserType);
  }

  double CoilCoolingDXTwoSpeed::highSpeedEvaporativeCondenserEffectiveness() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->highSpeedEvaporativeCondenserEffectiveness();
  }
  bool CoilCoolingDXTwoSpeed::setHighSpeedEvaporativeCondenserEffectiveness(double highSpeedEvaporativeCondenserEffectiveness) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setHighSpeedEvaporativeCondenserEffectiveness(highSpeedEvaporativeCondenserEffectiveness);
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::highSpeedEvaporativeCondenserAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->highSpeedEvaporativeCondenserAirFlowRate();
  }
  bool CoilCoolingDXTwoSpeed::isHighSpeedEvaporativeCondenserAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isHighSpeedEvaporativeCondenserAirFlowRateAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setHighSpeedEvaporativeCondenserAirFlowRate(double highSpeedEvaporativeCondenserAirFlowRate) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setHighSpeedEvaporativeCondenserAirFlowRate(highSpeedEvaporativeCondenserAirFlowRate);
  }
  void CoilCoolingDXTwoSpeed::autosizeHighSpeedEvaporativeCondenserAirFlowRate() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeHighSpeedEvaporativeCondenserAirFlowRate();
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::highSpeedEvaporativeCondenserPumpRatedPowerConsumption() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->highSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  }
  bool CoilCoolingDXTwoSpeed::isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized();
  }
  bool
    CoilCoolingDXTwoSpeed::setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(double highSpeedEvaporativeCondenserPumpRatedPowerConsumption) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(
      highSpeedEvaporativeCondenserPumpRatedPowerConsumption);
  }
  void CoilCoolingDXTwoSpeed::autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  }

  double CoilCoolingDXTwoSpeed::lowSpeedEvaporativeCondenserEffectiveness() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->lowSpeedEvaporativeCondenserEffectiveness();
  }
  bool CoilCoolingDXTwoSpeed::setLowSpeedEvaporativeCondenserEffectiveness(double lowSpeedEvaporativeCondenserEffectiveness) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setLowSpeedEvaporativeCondenserEffectiveness(lowSpeedEvaporativeCondenserEffectiveness);
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::lowSpeedEvaporativeCondenserAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->lowSpeedEvaporativeCondenserAirFlowRate();
  }
  bool CoilCoolingDXTwoSpeed::isLowSpeedEvaporativeCondenserAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isLowSpeedEvaporativeCondenserAirFlowRateAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setLowSpeedEvaporativeCondenserAirFlowRate(double lowSpeedEvaporativeCondenserAirFlowRate) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setLowSpeedEvaporativeCondenserAirFlowRate(lowSpeedEvaporativeCondenserAirFlowRate);
  }
  void CoilCoolingDXTwoSpeed::autosizeLowSpeedEvaporativeCondenserAirFlowRate() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeLowSpeedEvaporativeCondenserAirFlowRate();
  }

  boost::optional<double> CoilCoolingDXTwoSpeed::lowSpeedEvaporativeCondenserPumpRatedPowerConsumption() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->lowSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  }
  bool CoilCoolingDXTwoSpeed::isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized();
  }
  bool CoilCoolingDXTwoSpeed::setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(double lowSpeedEvaporativeCondenserPumpRatedPowerConsumption) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(
      lowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
  }
  void CoilCoolingDXTwoSpeed::autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption() {
    getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  }

  double CoilCoolingDXTwoSpeed::basinHeaterCapacity() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->basinHeaterCapacity();
  }
  bool CoilCoolingDXTwoSpeed::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }
  double CoilCoolingDXTwoSpeed::basinHeaterSetpointTemperature() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->basinHeaterSetpointTemperature();
  }
  bool CoilCoolingDXTwoSpeed::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }
  double CoilCoolingDXTwoSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }
  bool
    CoilCoolingDXTwoSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }
  double CoilCoolingDXTwoSpeed::unitInternalStaticAirPressure() const {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->unitInternalStaticAirPressure();
  }
  bool CoilCoolingDXTwoSpeed::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->setUnitInternalStaticAirPressure(unitInternalStaticAirPressure);
  }

  bool CoilCoolingDXTwoSpeed::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDXTwoSpeed_Impl>()->addToNode(node);
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

    Schedule CoilCoolingDXTwoSpeed_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilCoolingDXTwoSpeed_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::totalCoolingCapacityFunctionOfTemperatureCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::totalCoolingCapacityFunctionOfFlowFractionCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofFlowFractionCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setTotalCoolingCapacityFunctionOfFlowFractionCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofFlowFractionCurveName, curve.handle(), false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::energyInputRatioFunctionOfTemperatureCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::energyInputRatioFunctionOfFlowFractionCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setEnergyInputRatioFunctionOfFlowFractionCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, curve.handle(), false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::partLoadFractionCorrelationCurve() const {
      const auto curve =
        getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Coil_Cooling_DX_TwoSpeedFields::PartLoadFractionCorrelationCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::PartLoadFractionCorrelationCurveName, curve.handle(), false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, curve.handle(),
                        false);
    }

    Curve CoilCoolingDXTwoSpeed_Impl::lowSpeedEnergyInputRatioFunctionOfTemperatureCurve() const {
      const auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEnergyInputRatioFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
    }

    std::vector<ModelObject> CoilCoolingDXTwoSpeed_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(totalCoolingCapacityFunctionOfTemperatureCurve());
      result.push_back(totalCoolingCapacityFunctionOfFlowFractionCurve());
      result.push_back(energyInputRatioFunctionOfTemperatureCurve());
      result.push_back(energyInputRatioFunctionOfFlowFractionCurve());
      result.push_back(partLoadFractionCorrelationCurve());
      result.push_back(lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve());
      result.push_back(lowSpeedEnergyInputRatioFunctionOfTemperatureCurve());
      return result;
    }

    unsigned CoilCoolingDXTwoSpeed_Impl::inletPort() const {
      return openstudio::Coil_Cooling_DX_TwoSpeedFields::AirInletNodeName;
    }

    unsigned CoilCoolingDXTwoSpeed_Impl::outletPort() const {
      return openstudio::Coil_Cooling_DX_TwoSpeedFields::AirOutletNodeName;
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedTotalCoolingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isRatedHighSpeedTotalCoolingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedTotalCoolingCapacity(double ratedHighSpeedTotalCoolingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, ratedHighSpeedTotalCoolingCapacity);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeRatedHighSpeedTotalCoolingCapacity() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedSensibleHeatRatio() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isRatedHighSpeedSensibleHeatRatioAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedSensibleHeatRatio(double ratedHighSpeedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, ratedHighSpeedSensibleHeatRatio);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeRatedHighSpeedSensibleHeatRatio() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedCOP(double ratedHighSpeedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedCoolingCOP, ratedHighSpeedCOP);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isRatedHighSpeedAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedAirFlowRate(double ratedHighSpeedAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, ratedHighSpeedAirFlowRate);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeRatedHighSpeedAirFlowRate() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(
      double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017,
                       ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017);
    }

    double CoilCoolingDXTwoSpeed_Impl::ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(
      double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023,
                       ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedTotalCoolingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isRatedLowSpeedTotalCoolingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedTotalCoolingCapacity(double ratedLowSpeedTotalCoolingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, ratedLowSpeedTotalCoolingCapacity);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeRatedLowSpeedTotalCoolingCapacity() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedSensibleHeatRatio() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isRatedLowSpeedSensibleHeatRatioAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedSensibleHeatRatio(double ratedLowSpeedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, ratedLowSpeedSensibleHeatRatio);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeRatedLowSpeedSensibleHeatRatio() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedCOP() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedCOP(double ratedLowSpeedCOP) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedCoolingCOP, ratedLowSpeedCOP);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isRatedLowSpeedAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedAirFlowRate(double ratedLowSpeedAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, ratedLowSpeedAirFlowRate);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeRatedLowSpeedAirFlowRate() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(
      double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2017,
                       ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017);
    }

    double CoilCoolingDXTwoSpeed_Impl::ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(
      double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedEvaporatorFanPowerPerVolumeFlowRate2023,
                       ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023);
    }

    std::vector<std::string> CoilCoolingDXTwoSpeed_Impl::condenserTypeValues() const {
      return CoilCoolingDXTwoSpeed::condenserTypeValues();
    }

    std::string CoilCoolingDXTwoSpeed_Impl::condenserType() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_TwoSpeedFields::CondenserType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::CondenserType, condenserType);
    }

    double CoilCoolingDXTwoSpeed_Impl::highSpeedEvaporativeCondenserEffectiveness() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setHighSpeedEvaporativeCondenserEffectiveness(double highSpeedEvaporativeCondenserEffectiveness) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserEffectiveness,
                       highSpeedEvaporativeCondenserEffectiveness);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::highSpeedEvaporativeCondenserAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isHighSpeedEvaporativeCondenserAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setHighSpeedEvaporativeCondenserAirFlowRate(double highSpeedEvaporativeCondenserAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate,
                       highSpeedEvaporativeCondenserAirFlowRate);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeHighSpeedEvaporativeCondenserAirFlowRate() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::highSpeedEvaporativeCondenserPumpRatedPowerConsumption() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(
      double highSpeedEvaporativeCondenserPumpRatedPowerConsumption) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption,
                       highSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXTwoSpeed_Impl::lowSpeedEvaporativeCondenserEffectiveness() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserEffectiveness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEvaporativeCondenserEffectiveness(double lowSpeedEvaporativeCondenserEffectiveness) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserEffectiveness,
                       lowSpeedEvaporativeCondenserEffectiveness);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::lowSpeedEvaporativeCondenserAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isLowSpeedEvaporativeCondenserAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEvaporativeCondenserAirFlowRate(double lowSpeedEvaporativeCondenserAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, lowSpeedEvaporativeCondenserAirFlowRate);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeLowSpeedEvaporativeCondenserAirFlowRate() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> CoilCoolingDXTwoSpeed_Impl::lowSpeedEvaporativeCondenserPumpRatedPowerConsumption() const {
      return getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, true);
    }

    bool CoilCoolingDXTwoSpeed_Impl::isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const {
      return isAutosized(*this, openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(
      double lowSpeedEvaporativeCondenserPumpRatedPowerConsumption) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption,
                       lowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    }

    void CoilCoolingDXTwoSpeed_Impl::autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption() {
      const bool result = setString(openstudio::Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, "autosize");
      OS_ASSERT(result);
    }

    double CoilCoolingDXTwoSpeed_Impl::basinHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    double CoilCoolingDXTwoSpeed_Impl::basinHeaterSetpointTemperature() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
    }

    boost::optional<Schedule> CoilCoolingDXTwoSpeed_Impl::basinHeaterOperatingSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterOperatingScheduleName);
    }

    bool CoilCoolingDXTwoSpeed_Impl::setBasinHeaterOperatingSchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterOperatingScheduleName, schedule.handle(), false);
    }

    void CoilCoolingDXTwoSpeed_Impl::resetBasinHeaterOperatingSchedule() {
      OS_ASSERT(setPointer(openstudio::Coil_Cooling_DX_TwoSpeedFields::BasinHeaterOperatingScheduleName, Handle(), false));
    }

    double CoilCoolingDXTwoSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    double CoilCoolingDXTwoSpeed_Impl::unitInternalStaticAirPressure() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::UnitInternalStaticAirPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXTwoSpeed_Impl::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
      return setDouble(openstudio::Coil_Cooling_DX_TwoSpeedFields::UnitInternalStaticAirPressure, unitInternalStaticAirPressure);
    }

    bool CoilCoolingDXTwoSpeed_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
