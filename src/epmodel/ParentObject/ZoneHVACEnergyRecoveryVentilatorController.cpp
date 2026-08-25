/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp"
#include "ParentObject/ZoneHVACEnergyRecoveryVentilatorController_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_Controller_FieldEnums.hxx>

#include <utility>
#include <vector>

namespace openstudio {
namespace epmodel {

  ZoneHVACEnergyRecoveryVentilatorController::ZoneHVACEnergyRecoveryVentilatorController(const Model& model)
    : ParentObject(ZoneHVACEnergyRecoveryVentilatorController::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>();
    OS_ASSERT(impl);
  }

  ZoneHVACEnergyRecoveryVentilatorController::ZoneHVACEnergyRecoveryVentilatorController(
    std::shared_ptr<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl> impl)
    : ParentObject(std::move(impl)) {}

  IddObjectType ZoneHVACEnergyRecoveryVentilatorController::iddObjectType() {
    return IddObjectType::ZoneHVAC_EnergyRecoveryVentilator_Controller;
  }

  std::vector<std::string> ZoneHVACEnergyRecoveryVentilatorController::exhaustAirTemperatureLimitValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirTemperatureLimit);
  }

  std::vector<std::string> ZoneHVACEnergyRecoveryVentilatorController::exhaustAirEnthalpyLimitValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirEnthalpyLimit);
  }

  boost::optional<Curve> ZoneHVACEnergyRecoveryVentilatorController::electronicEnthalpyLimitCurve() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->electronicEnthalpyLimitCurve();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setElectronicEnthalpyLimitCurve(const Curve& curve) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setElectronicEnthalpyLimitCurve(curve);
  }

  void ZoneHVACEnergyRecoveryVentilatorController::resetElectronicEnthalpyLimitCurve() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->resetElectronicEnthalpyLimitCurve();
  }

  boost::optional<Schedule> ZoneHVACEnergyRecoveryVentilatorController::timeofDayEconomizerFlowControlSchedule() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->timeofDayEconomizerFlowControlSchedule();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setTimeofDayEconomizerFlowControlSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setTimeofDayEconomizerFlowControlSchedule(schedule);
  }

  void ZoneHVACEnergyRecoveryVentilatorController::resetTimeofDayEconomizerFlowControlSchedule() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->resetTimeofDayEconomizerFlowControlSchedule();
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController::temperatureHighLimit() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->temperatureHighLimit();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setTemperatureHighLimit(double temperatureHighLimit) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setTemperatureHighLimit(temperatureHighLimit);
  }

  void ZoneHVACEnergyRecoveryVentilatorController::resetTemperatureHighLimit() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->resetTemperatureHighLimit();
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController::temperatureLowLimit() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->temperatureLowLimit();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setTemperatureLowLimit(double temperatureLowLimit) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setTemperatureLowLimit(temperatureLowLimit);
  }

  void ZoneHVACEnergyRecoveryVentilatorController::resetTemperatureLowLimit() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->resetTemperatureLowLimit();
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController::enthalpyHighLimit() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->enthalpyHighLimit();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setEnthalpyHighLimit(double enthalpyHighLimit) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setEnthalpyHighLimit(enthalpyHighLimit);
  }

  void ZoneHVACEnergyRecoveryVentilatorController::resetEnthalpyHighLimit() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->resetEnthalpyHighLimit();
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController::dewpointTemperatureLimit() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->dewpointTemperatureLimit();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setDewpointTemperatureLimit(double dewpointTemperatureLimit) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setDewpointTemperatureLimit(dewpointTemperatureLimit);
  }

  void ZoneHVACEnergyRecoveryVentilatorController::resetDewpointTemperatureLimit() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->resetDewpointTemperatureLimit();
  }

  std::string ZoneHVACEnergyRecoveryVentilatorController::exhaustAirTemperatureLimit() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->exhaustAirTemperatureLimit();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setExhaustAirTemperatureLimit(const std::string& value) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setExhaustAirTemperatureLimit(value);
  }

  std::string ZoneHVACEnergyRecoveryVentilatorController::exhaustAirEnthalpyLimit() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->exhaustAirEnthalpyLimit();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setExhaustAirEnthalpyLimit(const std::string& value) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setExhaustAirEnthalpyLimit(value);
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::highHumidityControlFlag() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->highHumidityControlFlag();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setHighHumidityControlFlag(bool highHumidityControlFlag) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setHighHumidityControlFlag(highHumidityControlFlag);
  }

  double ZoneHVACEnergyRecoveryVentilatorController::highHumidityOutdoorAirFlowRatio() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->highHumidityOutdoorAirFlowRatio();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setHighHumidityOutdoorAirFlowRatio(double highHumidityOutdoorAirFlowRatio) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setHighHumidityOutdoorAirFlowRatio(highHumidityOutdoorAirFlowRatio);
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::controlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->controlHighIndoorHumidityBasedOnOutdoorHumidityRatio();
  }

  bool ZoneHVACEnergyRecoveryVentilatorController::setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool value) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilatorController_Impl>()->setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(value);
  }

  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ZoneHVACEnergyRecoveryVentilatorController_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "Yes");
      }

      bool setBooleanFieldValue(ZoneHVACEnergyRecoveryVentilatorController_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    boost::optional<Curve> ZoneHVACEnergyRecoveryVentilatorController_Impl::electronicEnthalpyLimitCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ElectronicEnthalpyLimitCurveName);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setElectronicEnthalpyLimitCurve(const Curve& curve) {
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ZoneHVACEnergyRecoveryVentilatorController",
                 "Cannot set the electronic enthalpy limit curve because it belongs to a different model.");
        return false;
      }

      constexpr auto field = openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ElectronicEnthalpyLimitCurveName;
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.ZoneHVACEnergyRecoveryVentilatorController",
                 "Cannot set the electronic enthalpy limit curve because curve type '"
                   << curve.iddObject().type().valueName() << "' is not accepted by the ZoneHVAC:EnergyRecoveryVentilator:Controller field.");
        return false;
      }

      if (!setPointer(field, curve.handle(), false)) {
        LOG_FREE(Warn, "openstudio.epmodel.ZoneHVACEnergyRecoveryVentilatorController",
                 "Failed to set the electronic enthalpy limit curve relationship.");
        return false;
      }
      return true;
    }

    void ZoneHVACEnergyRecoveryVentilatorController_Impl::resetElectronicEnthalpyLimitCurve() {
      constexpr auto field = openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ElectronicEnthalpyLimitCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<Schedule> ZoneHVACEnergyRecoveryVentilatorController_Impl::timeofDayEconomizerFlowControlSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TimeofDayEconomizerFlowControlScheduleName);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setTimeofDayEconomizerFlowControlSchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.ZoneHVACEnergyRecoveryVentilatorController",
                 "Cannot set the time-of-day economizer flow control schedule because it belongs to a different model.");
        return false;
      }

      if (!setSchedule(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TimeofDayEconomizerFlowControlScheduleName,
                       "ZoneHVACEnergyRecoveryVentilatorController", "Time of Day Economizer Flow Control", schedule)) {
        LOG_FREE(Warn, "openstudio.epmodel.ZoneHVACEnergyRecoveryVentilatorController",
                 "Cannot set the time-of-day economizer flow control schedule because its schedule type limits are incompatible.");
        return false;
      }
      return true;
    }

    void ZoneHVACEnergyRecoveryVentilatorController_Impl::resetTimeofDayEconomizerFlowControlSchedule() {
      constexpr auto field = openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TimeofDayEconomizerFlowControlScheduleName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController_Impl::temperatureHighLimit() const {
      return getDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureHighLimit, true);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setTemperatureHighLimit(double temperatureHighLimit) {
      const bool result = setDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureHighLimit, temperatureHighLimit);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACEnergyRecoveryVentilatorController_Impl::resetTemperatureHighLimit() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureHighLimit, ""));
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController_Impl::temperatureLowLimit() const {
      return getDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureLowLimit, true);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setTemperatureLowLimit(double temperatureLowLimit) {
      const bool result = setDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureLowLimit, temperatureLowLimit);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACEnergyRecoveryVentilatorController_Impl::resetTemperatureLowLimit() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TemperatureLowLimit, ""));
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController_Impl::enthalpyHighLimit() const {
      return getDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::EnthalpyHighLimit, true);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setEnthalpyHighLimit(double enthalpyHighLimit) {
      const bool result = setDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::EnthalpyHighLimit, enthalpyHighLimit);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACEnergyRecoveryVentilatorController_Impl::resetEnthalpyHighLimit() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::EnthalpyHighLimit, ""));
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilatorController_Impl::dewpointTemperatureLimit() const {
      return getDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::DewpointTemperatureLimit, true);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setDewpointTemperatureLimit(double dewpointTemperatureLimit) {
      const bool result =
        setDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::DewpointTemperatureLimit, dewpointTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACEnergyRecoveryVentilatorController_Impl::resetDewpointTemperatureLimit() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::DewpointTemperatureLimit, ""));
    }

    std::string ZoneHVACEnergyRecoveryVentilatorController_Impl::exhaustAirTemperatureLimit() const {
      const auto value = getString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirTemperatureLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setExhaustAirTemperatureLimit(const std::string& value) {
      return setString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirTemperatureLimit, value);
    }

    std::string ZoneHVACEnergyRecoveryVentilatorController_Impl::exhaustAirEnthalpyLimit() const {
      const auto value = getString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirEnthalpyLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setExhaustAirEnthalpyLimit(const std::string& value) {
      return setString(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ExhaustAirEnthalpyLimit, value);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::highHumidityControlFlag() const {
      return getBooleanFieldValue(*this, openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HighHumidityControlFlag);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setHighHumidityControlFlag(bool highHumidityControlFlag) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HighHumidityControlFlag, highHumidityControlFlag);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACEnergyRecoveryVentilatorController_Impl::highHumidityOutdoorAirFlowRatio() const {
      const auto value = getDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HighHumidityOutdoorAirFlowRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setHighHumidityOutdoorAirFlowRatio(double highHumidityOutdoorAirFlowRatio) {
      const bool result =
        setDouble(openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::HighHumidityOutdoorAirFlowRatio, highHumidityOutdoorAirFlowRatio);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::controlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const {
      return getBooleanFieldValue(
        *this, openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio);
    }

    bool ZoneHVACEnergyRecoveryVentilatorController_Impl::setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool value) {
      const bool result = setBooleanFieldValue(
        *this, openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ControlHighIndoorHumidityBasedonOutdoorHumidityRatio, value);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
