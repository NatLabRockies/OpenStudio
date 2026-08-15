/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"

#include "Model.hpp"
#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  CoilCoolingDXCurveFitPerformance::CoilCoolingDXCurveFitPerformance(const Model& model)
    : ModelObject(CoilCoolingDXCurveFitPerformance::iddObjectType(), model) {
    auto basinHeaterSchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setEvaporativeCondenserBasinHeaterOperatingSchedule(basinHeaterSchedule));
  }

  CoilCoolingDXCurveFitPerformance::CoilCoolingDXCurveFitPerformance(const Model& model, const CoilCoolingDXCurveFitOperatingMode& baseOperatingMode)
    : ModelObject(CoilCoolingDXCurveFitPerformance::iddObjectType(), model) {
    if (baseOperatingMode.model() != model) {
      remove();
      throw std::invalid_argument("The base operating mode must belong to the same model as the curve-fit performance object.");
    }

    OS_ASSERT(setCrankcaseHeaterCapacity(0.0));
    OS_ASSERT(setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0));
    OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
    OS_ASSERT(setUnitInternalStaticAirPressure(773.3));
    OS_ASSERT(setCapacityControlMethod("Discrete"));
    OS_ASSERT(setEvaporativeCondenserBasinHeaterCapacity(0.0));
    OS_ASSERT(setEvaporativeCondenserBasinHeaterSetpointTemperature(2.0));
    auto basinHeaterSchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setEvaporativeCondenserBasinHeaterOperatingSchedule(basinHeaterSchedule));
    OS_ASSERT(setCompressorFuelType("Electricity"));
    if (!setBaseOperatingMode(baseOperatingMode)) {
      remove();
      throw std::runtime_error("Unable to attach the base operating mode to the curve-fit performance object.");
    }
  }

  CoilCoolingDXCurveFitPerformance::CoilCoolingDXCurveFitPerformance(std::shared_ptr<detail::CoilCoolingDXCurveFitPerformance_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoilCoolingDXCurveFitPerformance::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX_CurveFit_Performance;
  }

  std::vector<std::string> CoilCoolingDXCurveFitPerformance::capacityControlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod);
  }

  std::vector<std::string> CoilCoolingDXCurveFitPerformance::compressorFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType);
  }

  std::vector<std::string> CoilCoolingDXCurveFitPerformance::validCapacityControlMethodValues() {
    return capacityControlMethodValues();
  }

  std::vector<std::string> CoilCoolingDXCurveFitPerformance::validCompressorFuelTypeValues() {
    return compressorFuelTypeValues();
  }

  double CoilCoolingDXCurveFitPerformance::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->crankcaseHeaterCapacity();
  }

  bool CoilCoolingDXCurveFitPerformance::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  boost::optional<Curve> CoilCoolingDXCurveFitPerformance::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  bool CoilCoolingDXCurveFitPerformance::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(curve);
  }

  void CoilCoolingDXCurveFitPerformance::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
    getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  double CoilCoolingDXCurveFitPerformance::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  bool CoilCoolingDXCurveFitPerformance::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  double CoilCoolingDXCurveFitPerformance::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }

  bool CoilCoolingDXCurveFitPerformance::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  }

  double CoilCoolingDXCurveFitPerformance::unitInternalStaticAirPressure() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->unitInternalStaticAirPressure();
  }

  bool CoilCoolingDXCurveFitPerformance::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setUnitInternalStaticAirPressure(unitInternalStaticAirPressure);
  }

  std::string CoilCoolingDXCurveFitPerformance::capacityControlMethod() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->capacityControlMethod();
  }

  bool CoilCoolingDXCurveFitPerformance::setCapacityControlMethod(const std::string& capacityControlMethod) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCapacityControlMethod(capacityControlMethod);
  }

  double CoilCoolingDXCurveFitPerformance::evaporativeCondenserBasinHeaterCapacity() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->evaporativeCondenserBasinHeaterCapacity();
  }

  bool CoilCoolingDXCurveFitPerformance::setEvaporativeCondenserBasinHeaterCapacity(double evaporativeCondenserBasinHeaterCapacity) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setEvaporativeCondenserBasinHeaterCapacity(
      evaporativeCondenserBasinHeaterCapacity);
  }

  double CoilCoolingDXCurveFitPerformance::evaporativeCondenserBasinHeaterSetpointTemperature() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->evaporativeCondenserBasinHeaterSetpointTemperature();
  }

  bool CoilCoolingDXCurveFitPerformance::setEvaporativeCondenserBasinHeaterSetpointTemperature(
    double evaporativeCondenserBasinHeaterSetpointTemperature) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setEvaporativeCondenserBasinHeaterSetpointTemperature(
      evaporativeCondenserBasinHeaterSetpointTemperature);
  }

  Schedule CoilCoolingDXCurveFitPerformance::evaporativeCondenserBasinHeaterOperatingSchedule() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->evaporativeCondenserBasinHeaterOperatingSchedule();
  }

  bool CoilCoolingDXCurveFitPerformance::setEvaporativeCondenserBasinHeaterOperatingSchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setEvaporativeCondenserBasinHeaterOperatingSchedule(schedule);
  }

  std::string CoilCoolingDXCurveFitPerformance::compressorFuelType() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->compressorFuelType();
  }

  bool CoilCoolingDXCurveFitPerformance::setCompressorFuelType(const std::string& compressorFuelType) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setCompressorFuelType(compressorFuelType);
  }

  CoilCoolingDXCurveFitOperatingMode CoilCoolingDXCurveFitPerformance::baseOperatingMode() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->baseOperatingMode();
  }

  bool CoilCoolingDXCurveFitPerformance::setBaseOperatingMode(const CoilCoolingDXCurveFitOperatingMode& baseOperatingMode) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setBaseOperatingMode(baseOperatingMode);
  }

  boost::optional<CoilCoolingDXCurveFitOperatingMode> CoilCoolingDXCurveFitPerformance::alternativeOperatingMode1() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->alternativeOperatingMode1();
  }

  bool CoilCoolingDXCurveFitPerformance::setAlternativeOperatingMode1(const CoilCoolingDXCurveFitOperatingMode& alternativeOperatingMode1) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setAlternativeOperatingMode1(alternativeOperatingMode1);
  }

  void CoilCoolingDXCurveFitPerformance::resetAlternativeOperatingMode1() {
    getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->resetAlternativeOperatingMode1();
  }

  boost::optional<CoilCoolingDXCurveFitOperatingMode> CoilCoolingDXCurveFitPerformance::alternativeOperatingMode2() const {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->alternativeOperatingMode2();
  }

  bool CoilCoolingDXCurveFitPerformance::setAlternativeOperatingMode2(const CoilCoolingDXCurveFitOperatingMode& alternativeOperatingMode2) {
    return getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setAlternativeOperatingMode2(alternativeOperatingMode2);
  }

  void CoilCoolingDXCurveFitPerformance::resetAlternativeOperatingMode2() {
    getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->resetAlternativeOperatingMode2();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CoilCoolingDXCurveFitPerformance_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    boost::optional<Curve> CoilCoolingDXCurveFitPerformance_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingDXCurveFitPerformance",
                 "Cannot set the crankcase-heater capacity temperature curve because it belongs to a different model.");
        return false;
      }
      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingDXCurveFitPerformance",
                 "Cannot set the crankcase-heater capacity temperature curve because curve type '" << curve.iddObject().type().valueName()
                                                                                                   << "' is not accepted by the field.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void CoilCoolingDXCurveFitPerformance_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    double CoilCoolingDXCurveFitPerformance_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    double CoilCoolingDXCurveFitPerformance_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    double CoilCoolingDXCurveFitPerformance_Impl::unitInternalStaticAirPressure() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::UnitInternalStaticAirPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::UnitInternalStaticAirPressure, unitInternalStaticAirPressure);
    }

    std::string CoilCoolingDXCurveFitPerformance_Impl::capacityControlMethod() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setCapacityControlMethod(const std::string& capacityControlMethod) {
      return setString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CapacityControlMethod, capacityControlMethod);
    }

    double CoilCoolingDXCurveFitPerformance_Impl::evaporativeCondenserBasinHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setEvaporativeCondenserBasinHeaterCapacity(double evaporativeCondenserBasinHeaterCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterCapacity,
                       evaporativeCondenserBasinHeaterCapacity);
    }

    double CoilCoolingDXCurveFitPerformance_Impl::evaporativeCondenserBasinHeaterSetpointTemperature() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setEvaporativeCondenserBasinHeaterSetpointTemperature(
      double evaporativeCondenserBasinHeaterSetpointTemperature) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterSetpointTemperature,
                       evaporativeCondenserBasinHeaterSetpointTemperature);
    }

    Schedule CoilCoolingDXCurveFitPerformance_Impl::evaporativeCondenserBasinHeaterOperatingSchedule() const {
      const auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setEvaporativeCondenserBasinHeaterOperatingSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName,
        "CoilCoolingDXCurveFitPerformance", "Evaporative Condenser Basin Heater Operating Schedule", schedule);
    }

    std::string CoilCoolingDXCurveFitPerformance_Impl::compressorFuelType() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setCompressorFuelType(const std::string& compressorFuelType) {
      return setString(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CompressorFuelType, compressorFuelType);
    }

    CoilCoolingDXCurveFitOperatingMode CoilCoolingDXCurveFitPerformance_Impl::baseOperatingMode() const {
      const auto value = getObject<ModelObject>().getModelObjectTarget<CoilCoolingDXCurveFitOperatingMode>(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::BaseOperatingMode);
      if (!value) {
        throw std::runtime_error("Curve-fit performance object does not have a valid base operating mode.");
      }
      return *value;
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setBaseOperatingMode(const CoilCoolingDXCurveFitOperatingMode& baseOperatingMode) {
      return baseOperatingMode.model() == model()
             && setPointer(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::BaseOperatingMode, baseOperatingMode.handle(), false);
    }

    boost::optional<CoilCoolingDXCurveFitOperatingMode> CoilCoolingDXCurveFitPerformance_Impl::alternativeOperatingMode1() const {
      return getObject<ModelObject>().getModelObjectTarget<CoilCoolingDXCurveFitOperatingMode>(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode1);
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setAlternativeOperatingMode1(const CoilCoolingDXCurveFitOperatingMode& alternativeOperatingMode1) {
      if (alternativeOperatingMode1.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingDXCurveFitPerformance",
                 "Cannot set alternative operating mode 1 because it belongs to a different model.");
        return false;
      }
      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode1;
      if (!model().canBeTarget(alternativeOperatingMode1.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingDXCurveFitPerformance",
                 "Cannot set alternative operating mode 1 because object type '" << alternativeOperatingMode1.iddObject().type().valueName()
                                                                                 << "' is not accepted by the field.");
        return false;
      }
      return setPointer(field, alternativeOperatingMode1.handle(), false);
    }

    void CoilCoolingDXCurveFitPerformance_Impl::resetAlternativeOperatingMode1() {
      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode1;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<CoilCoolingDXCurveFitOperatingMode> CoilCoolingDXCurveFitPerformance_Impl::alternativeOperatingMode2() const {
      return getObject<ModelObject>().getModelObjectTarget<CoilCoolingDXCurveFitOperatingMode>(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode2);
    }

    bool CoilCoolingDXCurveFitPerformance_Impl::setAlternativeOperatingMode2(const CoilCoolingDXCurveFitOperatingMode& alternativeOperatingMode2) {
      if (alternativeOperatingMode2.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingDXCurveFitPerformance",
                 "Cannot set alternative operating mode 2 because it belongs to a different model.");
        return false;
      }
      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode2;
      if (!model().canBeTarget(alternativeOperatingMode2.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilCoolingDXCurveFitPerformance",
                 "Cannot set alternative operating mode 2 because object type '" << alternativeOperatingMode2.iddObject().type().valueName()
                                                                                 << "' is not accepted by the field.");
        return false;
      }
      return setPointer(field, alternativeOperatingMode2.handle(), false);
    }

    void CoilCoolingDXCurveFitPerformance_Impl::resetAlternativeOperatingMode2() {
      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode2;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    void CoilCoolingDXCurveFitPerformance_Impl::doCanonicalize(LoadContext& context) {
      ModelObject_Impl::doCanonicalize(context);

      constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName;
      const auto raw = openstudio::detail::IdfObject_Impl::getString(field, false, true);
      if (raw && !raw->empty()) {
        return;
      }
      if (getObject<ModelObject>().getModelObjectTarget<Schedule>(field)) {
        return;
      }

      auto alwaysOn = model().alwaysOnDiscreteSchedule();
      if (setEvaporativeCondenserBasinHeaterOperatingSchedule(alwaysOn)) {
        detail::addLoadInfo(context, "Attached the always-on basin-heater schedule to curve-fit DX cooling performance '"
                                       + getObject<ModelObject>().nameString() + "'.");
      } else {
        detail::addLoadError(context, "Failed to attach the always-on basin-heater schedule to curve-fit DX cooling performance '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    std::vector<std::string> CoilCoolingDXCurveFitPerformance_Impl::capacityControlMethodValues() const {
      return openstudio::epmodel::CoilCoolingDXCurveFitPerformance::capacityControlMethodValues();
    }

    std::vector<std::string> CoilCoolingDXCurveFitPerformance_Impl::compressorFuelTypeValues() const {
      return openstudio::epmodel::CoilCoolingDXCurveFitPerformance::compressorFuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
