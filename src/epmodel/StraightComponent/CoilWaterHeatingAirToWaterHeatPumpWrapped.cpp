/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Wrapped_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  CoilWaterHeatingAirToWaterHeatPumpWrapped::CoilWaterHeatingAirToWaterHeatPumpWrapped(const Model& model)
    : StraightComponent(CoilWaterHeatingAirToWaterHeatPumpWrapped::iddObjectType(), model) {
    auto impl = getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  CoilWaterHeatingAirToWaterHeatPumpWrapped::CoilWaterHeatingAirToWaterHeatPumpWrapped(
    std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilWaterHeatingAirToWaterHeatPumpWrapped::iddObjectType() {
    return IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped;
  }

  std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorAirTemperatureTypeforCurveObjectsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects);
  }

  Schedule CoilWaterHeatingAirToWaterHeatPumpWrapped::availabilitySchedule() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->availabilitySchedule();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setAvailabilitySchedule(schedule);
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedHeatingCapacity() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedHeatingCapacity();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedHeatingCapacity(double ratedHeatingCapacity) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedHeatingCapacity(ratedHeatingCapacity);
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedCOP() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedCOP();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isRatedCOPDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isRatedCOPDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedCOP(double ratedCOP) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedCOP(ratedCOP);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetRatedCOP() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetRatedCOP();
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedSensibleHeatRatio() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedSensibleHeatRatio();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isRatedSensibleHeatRatioDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isRatedSensibleHeatRatioDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetRatedSensibleHeatRatio() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetRatedSensibleHeatRatio();
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedEvaporatorInletAirDryBulbTemperature() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedEvaporatorInletAirDryBulbTemperature();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isRatedEvaporatorInletAirDryBulbTemperatureDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isRatedEvaporatorInletAirDryBulbTemperatureDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedEvaporatorInletAirDryBulbTemperature(
      ratedEvaporatorInletAirDryBulbTemperature);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetRatedEvaporatorInletAirDryBulbTemperature() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetRatedEvaporatorInletAirDryBulbTemperature();
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedEvaporatorInletAirWetBulbTemperature() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedEvaporatorInletAirWetBulbTemperature();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isRatedEvaporatorInletAirWetBulbTemperatureDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isRatedEvaporatorInletAirWetBulbTemperatureDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedEvaporatorInletAirWetBulbTemperature(
      ratedEvaporatorInletAirWetBulbTemperature);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetRatedEvaporatorInletAirWetBulbTemperature() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetRatedEvaporatorInletAirWetBulbTemperature();
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedCondenserWaterTemperature() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedCondenserWaterTemperature();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isRatedCondenserWaterTemperatureDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isRatedCondenserWaterTemperatureDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedCondenserWaterTemperature(double ratedCondenserWaterTemperature) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedCondenserWaterTemperature(ratedCondenserWaterTemperature);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetRatedCondenserWaterTemperature() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetRatedCondenserWaterTemperature();
  }

  boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpWrapped::ratedEvaporatorAirFlowRate() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->ratedEvaporatorAirFlowRate();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isRatedEvaporatorAirFlowRateAutocalculated() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isRatedEvaporatorAirFlowRateAutocalculated();
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::autocalculateRatedEvaporatorAirFlowRate() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->autocalculateRatedEvaporatorAirFlowRate();
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetRatedEvaporatorAirFlowRate() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetRatedEvaporatorAirFlowRate();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorFanPowerIncludedinRatedCOP() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->evaporatorFanPowerIncludedinRatedCOP();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isEvaporatorFanPowerIncludedinRatedCOPDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isEvaporatorFanPowerIncludedinRatedCOPDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setEvaporatorFanPowerIncludedinRatedCOP(
      evaporatorFanPowerIncludedinRatedCOP);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetEvaporatorFanPowerIncludedinRatedCOP() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetEvaporatorFanPowerIncludedinRatedCOP();
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->crankcaseHeaterCapacity();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isCrankcaseHeaterCapacityDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isCrankcaseHeaterCapacityDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetCrankcaseHeaterCapacity() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetCrankcaseHeaterCapacity();
  }

  boost::optional<Curve> CoilWaterHeatingAirToWaterHeatPumpWrapped::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(curve);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  double CoilWaterHeatingAirToWaterHeatPumpWrapped::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->maximumAmbientTemperatureforCrankcaseHeaterOperation();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
    double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
      maximumAmbientTemperatureforCrankcaseHeaterOperation);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetMaximumAmbientTemperatureforCrankcaseHeaterOperation() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();
  }

  std::string CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorAirTemperatureTypeforCurveObjects() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->evaporatorAirTemperatureTypeforCurveObjects();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setEvaporatorAirTemperatureTypeforCurveObjects(
    const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setEvaporatorAirTemperatureTypeforCurveObjects(
      evaporatorAirTemperatureTypeforCurveObjects);
  }

  void CoilWaterHeatingAirToWaterHeatPumpWrapped::resetEvaporatorAirTemperatureTypeforCurveObjects() {
    getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->resetEvaporatorAirTemperatureTypeforCurveObjects();
  }

  Curve CoilWaterHeatingAirToWaterHeatPumpWrapped::heatingCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->heatingCapacityFunctionofTemperatureCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setHeatingCapacityFunctionofTemperatureCurve(curve);
  }

  Curve CoilWaterHeatingAirToWaterHeatPumpWrapped::heatingCapacityFunctionofAirFlowFractionCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->heatingCapacityFunctionofAirFlowFractionCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setHeatingCapacityFunctionofAirFlowFractionCurve(curve);
  }

  Curve CoilWaterHeatingAirToWaterHeatPumpWrapped::heatingCOPFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->heatingCOPFunctionofTemperatureCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setHeatingCOPFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setHeatingCOPFunctionofTemperatureCurve(curve);
  }

  Curve CoilWaterHeatingAirToWaterHeatPumpWrapped::heatingCOPFunctionofAirFlowFractionCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->heatingCOPFunctionofAirFlowFractionCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setHeatingCOPFunctionofAirFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setHeatingCOPFunctionofAirFlowFractionCurve(curve);
  }

  Curve CoilWaterHeatingAirToWaterHeatPumpWrapped::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilWaterHeatingAirToWaterHeatPumpWrapped::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::inletPort() const {
      return openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirInletNodeName;
    }

    unsigned CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::outletPort() const {
      return openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirOutletNodeName;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::addToNode(Node& node) {
      (void)node;
      return false;
    }

    Schedule CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::availabilitySchedule() const {
      constexpr auto field = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName;
      const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
      OS_ASSERT(!raw || raw->empty());
      const auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(field);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName,
                                           "CoilWaterHeatingAirToWaterHeatPumpWrapped", "Availability Schedule", schedule);
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedHeatingCapacity() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedHeatingCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedHeatingCapacity(double ratedHeatingCapacity) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedHeatingCapacity, ratedHeatingCapacity);
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedCOP() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isRatedCOPDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCOP);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedCOP(double ratedCOP) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCOP, ratedCOP);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetRatedCOP() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCOP, ""));
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedSensibleHeatRatio() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedSensibleHeatRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isRatedSensibleHeatRatioDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedSensibleHeatRatio);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedSensibleHeatRatio, ratedSensibleHeatRatio);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetRatedSensibleHeatRatio() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedSensibleHeatRatio, ""));
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedEvaporatorInletAirDryBulbTemperature() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirDryBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isRatedEvaporatorInletAirDryBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirDryBulbTemperature);
    }

    bool
      CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedEvaporatorInletAirDryBulbTemperature(double ratedEvaporatorInletAirDryBulbTemperature) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirDryBulbTemperature,
                       ratedEvaporatorInletAirDryBulbTemperature);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetRatedEvaporatorInletAirDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirDryBulbTemperature, ""));
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedEvaporatorInletAirWetBulbTemperature() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirWetBulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isRatedEvaporatorInletAirWetBulbTemperatureDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirWetBulbTemperature);
    }

    bool
      CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedEvaporatorInletAirWetBulbTemperature(double ratedEvaporatorInletAirWetBulbTemperature) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirWetBulbTemperature,
                       ratedEvaporatorInletAirWetBulbTemperature);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetRatedEvaporatorInletAirWetBulbTemperature() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirWetBulbTemperature, ""));
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedCondenserWaterTemperature() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCondenserWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isRatedCondenserWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCondenserWaterTemperature);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedCondenserWaterTemperature(double ratedCondenserWaterTemperature) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCondenserWaterTemperature,
                       ratedCondenserWaterTemperature);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetRatedCondenserWaterTemperature() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCondenserWaterTemperature, ""));
    }

    boost::optional<double> CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::ratedEvaporatorAirFlowRate() const {
      return getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, true);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isRatedEvaporatorAirFlowRateAutocalculated() const {
      if (const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::autocalculateRatedEvaporatorAirFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, "autocalculate"));
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetRatedEvaporatorAirFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, ""));
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::evaporatorFanPowerIncludedinRatedCOP() const {
      const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isEvaporatorFanPowerIncludedinRatedCOPDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setEvaporatorFanPowerIncludedinRatedCOP(bool evaporatorFanPowerIncludedinRatedCOP) {
      const bool result = setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP,
                                    evaporatorFanPowerIncludedinRatedCOP ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetEvaporatorFanPowerIncludedinRatedCOP() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP, ""));
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isCrankcaseHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacity);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetCrankcaseHeaterCapacity() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacity, ""));
    }

    boost::optional<Curve> CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setValidatedCurve(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName,
                               curve, "crankcase heater capacity temperature curve");
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
      constexpr auto field = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::maximumAmbientTemperatureforCrankcaseHeaterOperation() const {
      const auto value =
        getDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setMaximumAmbientTemperatureforCrankcaseHeaterOperation(
      double maximumAmbientTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation,
                       maximumAmbientTemperatureforCrankcaseHeaterOperation);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetMaximumAmbientTemperatureforCrankcaseHeaterOperation() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, ""));
    }

    std::string CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::evaporatorAirTemperatureTypeforCurveObjects() const {
      const auto value = getString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted() const {
      return isEmpty(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects);
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setEvaporatorAirTemperatureTypeforCurveObjects(
      const std::string& evaporatorAirTemperatureTypeforCurveObjects) {
      return setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects,
                       evaporatorAirTemperatureTypeforCurveObjects);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::resetEvaporatorAirTemperatureTypeforCurveObjects() {
      OS_ASSERT(setString(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects, ""));
    }

    Curve CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::heatingCapacityFunctionofTemperatureCurve() const {
      const auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setValidatedCurve(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofTemperatureCurveName, curve,
                               "heating capacity temperature curve");
    }

    Curve CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::heatingCapacityFunctionofAirFlowFractionCurve() const {
      const auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
      return setValidatedCurve(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName,
                               curve, "heating capacity air-flow-fraction curve");
    }

    Curve CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::heatingCOPFunctionofTemperatureCurve() const {
      const auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofTemperatureCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setHeatingCOPFunctionofTemperatureCurve(const Curve& curve) {
      return setValidatedCurve(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofTemperatureCurveName, curve,
                               "heating COP temperature curve");
    }

    Curve CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::heatingCOPFunctionofAirFlowFractionCurve() const {
      const auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofAirFlowFractionCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setHeatingCOPFunctionofAirFlowFractionCurve(const Curve& curve) {
      return setValidatedCurve(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofAirFlowFractionCurveName, curve,
                               "heating COP air-flow-fraction curve");
    }

    Curve CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::partLoadFractionCorrelationCurve() const {
      const auto value = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::PartLoadFractionCorrelationCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setValidatedCurve(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::PartLoadFractionCorrelationCurveName, curve,
                               "part-load fraction correlation curve");
    }

    std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::evaporatorAirTemperatureTypeforCurveObjectsValues() const {
      return openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorAirTemperatureTypeforCurveObjectsValues();
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setValidatedCurve(unsigned field, const Curve& curve, const char* relationshipName) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilWaterHeatingAirToWaterHeatPumpWrapped",
                 "Cannot set the " << relationshipName << " because the curve belongs to a different model.");
        return false;
      }
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilWaterHeatingAirToWaterHeatPumpWrapped",
                 "Cannot set the " << relationshipName << " because curve type '" << curve.iddObject().type().valueName()
                                   << "' is not accepted by the Coil:WaterHeating:AirToWaterHeatPump:Wrapped field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      const auto object = getObject<ModelObject>();
      const auto objectName = object.nameString();

      constexpr auto availabilityField = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName;
      const auto availabilityRaw = openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true);
      if (availabilityRaw && !availabilityRaw->empty()) {
        detail::addLoadWarning(context, "Preserved unresolved, ambiguous, or otherwise noncanonical availability schedule evidence '"
                                          + *availabilityRaw + "' on wrapped water-heating coil '" + objectName + "'.");
      } else if (!object.getModelObjectTarget<Schedule>(availabilityField)) {
        if (context.repairEnabled()) {
          auto alwaysOn = model().alwaysOnDiscreteSchedule();
          if (setAvailabilitySchedule(alwaysOn)) {
            detail::addLoadInfo(context, "Attached the always-on schedule to wrapped water-heating coil '" + objectName + "'.");
          } else {
            detail::addLoadError(context, "Failed to attach the always-on schedule to wrapped water-heating coil '" + objectName + "'.");
          }
        } else {
          detail::addLoadWarning(context, "Wrapped water-heating coil '" + objectName + "' has a blank availability schedule.");
        }
      }

      auto needsCurveRepair = [&](unsigned field, const char* relationshipName) {
        const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (raw && !raw->empty()) {
          detail::addLoadWarning(context, "Preserved unresolved, ambiguous, or ineligible " + std::string(relationshipName) + " '" + *raw
                                            + "' on wrapped water-heating coil '" + objectName + "'.");
          return false;
        }
        if (const auto curve = object.getModelObjectTarget<Curve>(field)) {
          if (model().canBeTarget(curve->handle(), iddObject().objectLists(field))) {
            return false;
          }
          detail::addLoadWarning(context,
                                 "Preserved ineligible " + std::string(relationshipName) + " on wrapped water-heating coil '" + objectName + "'.");
          return false;
        }
        if (!context.repairEnabled()) {
          detail::addLoadWarning(context, "Wrapped water-heating coil '" + objectName + "' has a blank " + relationshipName + ".");
          return false;
        }
        return true;
      };

      auto recordCurveRepair = [&](bool result, Curve& curve, const char* relationshipName) {
        if (result) {
          detail::addLoadInfo(context,
                              "Attached the canonical " + std::string(relationshipName) + " to wrapped water-heating coil '" + objectName + "'.");
        } else {
          curve.remove();
          detail::addLoadError(context, "Failed to attach the canonical " + std::string(relationshipName) + " to wrapped water-heating coil '"
                                          + objectName + "'.");
        }
      };

      constexpr auto capacityTemperatureField =
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofTemperatureCurveName;
      if (needsCurveRepair(capacityTemperatureField, "heating capacity temperature curve")) {
        CurveBiquadratic curve(model());
        OS_ASSERT(curve.setName("HPWH-Htg-Cap-fT"));
        OS_ASSERT(curve.setCoefficient1Constant(0.563));
        OS_ASSERT(curve.setCoefficient2x(0.0437));
        OS_ASSERT(curve.setCoefficient3xPOW2(0.000039));
        OS_ASSERT(curve.setCoefficient4y(0.0055));
        OS_ASSERT(curve.setCoefficient5yPOW2(-0.000148));
        OS_ASSERT(curve.setCoefficient6xTIMESY(-0.000145));
        OS_ASSERT(curve.setMinimumValueofx(0.0));
        OS_ASSERT(curve.setMaximumValueofx(100.0));
        OS_ASSERT(curve.setMinimumValueofy(0.0));
        OS_ASSERT(curve.setMaximumValueofy(100.0));
        OS_ASSERT(curve.setMinimumCurveOutput(0.0));
        Curve genericCurve = curve;
        recordCurveRepair(setHeatingCapacityFunctionofTemperatureCurve(genericCurve), genericCurve, "heating capacity temperature curve");
      }

      constexpr auto capacityAirFlowField =
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName;
      if (needsCurveRepair(capacityAirFlowField, "heating capacity air-flow-fraction curve")) {
        CurveCubic curve(model());
        OS_ASSERT(curve.setName("HPWH-Htg-Cap-FF"));
        OS_ASSERT(curve.setCoefficient1Constant(1.0));
        OS_ASSERT(curve.setCoefficient2x(0.0));
        OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
        OS_ASSERT(curve.setCoefficient4xPOW3(0.0));
        OS_ASSERT(curve.setMinimumValueofx(0.0));
        OS_ASSERT(curve.setMaximumValueofx(100.0));
        Curve genericCurve = curve;
        recordCurveRepair(setHeatingCapacityFunctionofAirFlowFractionCurve(genericCurve), genericCurve, "heating capacity air-flow-fraction curve");
      }

      constexpr auto copTemperatureField = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofTemperatureCurveName;
      if (needsCurveRepair(copTemperatureField, "heating COP temperature curve")) {
        CurveBiquadratic curve(model());
        OS_ASSERT(curve.setName("HPWH-Htg-COP-fT"));
        OS_ASSERT(curve.setCoefficient1Constant(1.1332));
        OS_ASSERT(curve.setCoefficient2x(0.063));
        OS_ASSERT(curve.setCoefficient3xPOW2(-0.0000979));
        OS_ASSERT(curve.setCoefficient4y(-0.00972));
        OS_ASSERT(curve.setCoefficient5yPOW2(-0.0000214));
        OS_ASSERT(curve.setCoefficient6xTIMESY(-0.000686));
        OS_ASSERT(curve.setMinimumValueofx(0.0));
        OS_ASSERT(curve.setMaximumValueofx(100.0));
        OS_ASSERT(curve.setMinimumValueofy(0.0));
        OS_ASSERT(curve.setMaximumValueofy(100.0));
        Curve genericCurve = curve;
        recordCurveRepair(setHeatingCOPFunctionofTemperatureCurve(genericCurve), genericCurve, "heating COP temperature curve");
      }

      constexpr auto copAirFlowField = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofAirFlowFractionCurveName;
      if (needsCurveRepair(copAirFlowField, "heating COP air-flow-fraction curve")) {
        CurveCubic curve(model());
        OS_ASSERT(curve.setName("HPWH-Htg-COP-FF"));
        OS_ASSERT(curve.setCoefficient1Constant(1.0));
        OS_ASSERT(curve.setCoefficient2x(0.0));
        OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
        OS_ASSERT(curve.setCoefficient4xPOW3(0.0));
        OS_ASSERT(curve.setMinimumValueofx(0.0));
        OS_ASSERT(curve.setMaximumValueofx(100.0));
        Curve genericCurve = curve;
        recordCurveRepair(setHeatingCOPFunctionofAirFlowFractionCurve(genericCurve), genericCurve, "heating COP air-flow-fraction curve");
      }

      constexpr auto partLoadField = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::PartLoadFractionCorrelationCurveName;
      if (needsCurveRepair(partLoadField, "part-load fraction correlation curve")) {
        CurveCubic curve(model());
        OS_ASSERT(curve.setName("HPWH-COP-fPLR"));
        OS_ASSERT(curve.setCoefficient1Constant(1.0));
        OS_ASSERT(curve.setCoefficient2x(0.0));
        OS_ASSERT(curve.setCoefficient3xPOW2(0.0));
        OS_ASSERT(curve.setCoefficient4xPOW3(0.0));
        OS_ASSERT(curve.setMinimumValueofx(0.0));
        OS_ASSERT(curve.setMaximumValueofx(1.0));
        Curve genericCurve = curve;
        recordCurveRepair(setPartLoadFractionCorrelationCurve(genericCurve), genericCurve, "part-load fraction correlation curve");
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
