/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Wrapped_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilWaterHeatingAirToWaterHeatPumpWrapped::CoilWaterHeatingAirToWaterHeatPumpWrapped(const Model& model)
    : StraightComponent(CoilWaterHeatingAirToWaterHeatPumpWrapped::iddObjectType(), model) {
    auto alwaysOn = const_cast<Model&>(model).alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
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
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName, schedule.handle(), false);
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

    std::vector<std::string> CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl::evaporatorAirTemperatureTypeforCurveObjectsValues() const {
      return openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorAirTemperatureTypeforCurveObjectsValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
