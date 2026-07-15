/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DehumidifierDesiccantNoFans.hpp"
#include "DehumidifierDesiccantNoFans_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Dehumidifier_Desiccant_NoFans_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  DehumidifierDesiccantNoFans::DehumidifierDesiccantNoFans(const Model& model) : ModelObject(DehumidifierDesiccantNoFans::iddObjectType(), model) {}

  DehumidifierDesiccantNoFans::DehumidifierDesiccantNoFans(std::shared_ptr<detail::DehumidifierDesiccantNoFans_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType DehumidifierDesiccantNoFans::iddObjectType() {
    return IddObjectType::Dehumidifier_Desiccant_NoFans;
  }

  std::vector<std::string> DehumidifierDesiccantNoFans::controlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Dehumidifier_Desiccant_NoFansFields::ControlType);
  }

  std::vector<std::string> DehumidifierDesiccantNoFans::regenerationCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationCoilObjectType);
  }

  std::vector<std::string> DehumidifierDesiccantNoFans::regenerationFanObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationFanObjectType);
  }

  std::vector<std::string> DehumidifierDesiccantNoFans::performanceModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Dehumidifier_Desiccant_NoFansFields::PerformanceModelType);
  }

  boost::optional<std::string> DehumidifierDesiccantNoFans::controlType() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->controlType();
  }

  bool DehumidifierDesiccantNoFans::setControlType(const std::string& controlType) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setControlType(controlType);
  }

  void DehumidifierDesiccantNoFans::resetControlType() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetControlType();
  }

  boost::optional<double> DehumidifierDesiccantNoFans::leavingMaximumHumidityRatioSetpoint() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->leavingMaximumHumidityRatioSetpoint();
  }

  bool DehumidifierDesiccantNoFans::setLeavingMaximumHumidityRatioSetpoint(double leavingMaximumHumidityRatioSetpoint) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setLeavingMaximumHumidityRatioSetpoint(leavingMaximumHumidityRatioSetpoint);
  }

  void DehumidifierDesiccantNoFans::resetLeavingMaximumHumidityRatioSetpoint() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetLeavingMaximumHumidityRatioSetpoint();
  }

  boost::optional<double> DehumidifierDesiccantNoFans::nominalProcessAirFlowRate() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->nominalProcessAirFlowRate();
  }

  bool DehumidifierDesiccantNoFans::setNominalProcessAirFlowRate(double nominalProcessAirFlowRate) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setNominalProcessAirFlowRate(nominalProcessAirFlowRate);
  }

  void DehumidifierDesiccantNoFans::resetNominalProcessAirFlowRate() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetNominalProcessAirFlowRate();
  }

  boost::optional<double> DehumidifierDesiccantNoFans::nominalProcessAirVelocity() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->nominalProcessAirVelocity();
  }

  bool DehumidifierDesiccantNoFans::setNominalProcessAirVelocity(double nominalProcessAirVelocity) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setNominalProcessAirVelocity(nominalProcessAirVelocity);
  }

  void DehumidifierDesiccantNoFans::resetNominalProcessAirVelocity() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetNominalProcessAirVelocity();
  }

  boost::optional<double> DehumidifierDesiccantNoFans::rotorPower() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->rotorPower();
  }

  bool DehumidifierDesiccantNoFans::setRotorPower(double rotorPower) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setRotorPower(rotorPower);
  }

  void DehumidifierDesiccantNoFans::resetRotorPower() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetRotorPower();
  }

  boost::optional<std::string> DehumidifierDesiccantNoFans::regenerationCoilObjectType() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->regenerationCoilObjectType();
  }

  bool DehumidifierDesiccantNoFans::setRegenerationCoilObjectType(const std::string& regenerationCoilObjectType) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setRegenerationCoilObjectType(regenerationCoilObjectType);
  }

  void DehumidifierDesiccantNoFans::resetRegenerationCoilObjectType() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetRegenerationCoilObjectType();
  }

  boost::optional<std::string> DehumidifierDesiccantNoFans::regenerationFanObjectType() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->regenerationFanObjectType();
  }

  bool DehumidifierDesiccantNoFans::setRegenerationFanObjectType(const std::string& regenerationFanObjectType) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setRegenerationFanObjectType(regenerationFanObjectType);
  }

  void DehumidifierDesiccantNoFans::resetRegenerationFanObjectType() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetRegenerationFanObjectType();
  }

  boost::optional<std::string> DehumidifierDesiccantNoFans::performanceModelType() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->performanceModelType();
  }

  bool DehumidifierDesiccantNoFans::setPerformanceModelType(const std::string& performanceModelType) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setPerformanceModelType(performanceModelType);
  }

  void DehumidifierDesiccantNoFans::resetPerformanceModelType() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetPerformanceModelType();
  }

  boost::optional<double> DehumidifierDesiccantNoFans::nominalRegenerationTemperature() const {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->nominalRegenerationTemperature();
  }

  bool DehumidifierDesiccantNoFans::setNominalRegenerationTemperature(double nominalRegenerationTemperature) {
    return getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->setNominalRegenerationTemperature(nominalRegenerationTemperature);
  }

  void DehumidifierDesiccantNoFans::resetNominalRegenerationTemperature() {
    getImpl<detail::DehumidifierDesiccantNoFans_Impl>()->resetNominalRegenerationTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> DehumidifierDesiccantNoFans_Impl::controlType() const {
      return getString(openstudio::Dehumidifier_Desiccant_NoFansFields::ControlType, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setControlType(const std::string& controlType) {
      return setString(openstudio::Dehumidifier_Desiccant_NoFansFields::ControlType, controlType);
    }

    void DehumidifierDesiccantNoFans_Impl::resetControlType() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::ControlType, ""));
    }

    boost::optional<double> DehumidifierDesiccantNoFans_Impl::leavingMaximumHumidityRatioSetpoint() const {
      return getDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::LeavingMaximumHumidityRatioSetpoint, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setLeavingMaximumHumidityRatioSetpoint(double leavingMaximumHumidityRatioSetpoint) {
      return setDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::LeavingMaximumHumidityRatioSetpoint, leavingMaximumHumidityRatioSetpoint);
    }

    void DehumidifierDesiccantNoFans_Impl::resetLeavingMaximumHumidityRatioSetpoint() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::LeavingMaximumHumidityRatioSetpoint, ""));
    }

    boost::optional<double> DehumidifierDesiccantNoFans_Impl::nominalProcessAirFlowRate() const {
      return getDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalProcessAirFlowRate, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setNominalProcessAirFlowRate(double nominalProcessAirFlowRate) {
      return setDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalProcessAirFlowRate, nominalProcessAirFlowRate);
    }

    void DehumidifierDesiccantNoFans_Impl::resetNominalProcessAirFlowRate() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalProcessAirFlowRate, ""));
    }

    boost::optional<double> DehumidifierDesiccantNoFans_Impl::nominalProcessAirVelocity() const {
      return getDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalProcessAirVelocity, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setNominalProcessAirVelocity(double nominalProcessAirVelocity) {
      return setDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalProcessAirVelocity, nominalProcessAirVelocity);
    }

    void DehumidifierDesiccantNoFans_Impl::resetNominalProcessAirVelocity() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalProcessAirVelocity, ""));
    }

    boost::optional<double> DehumidifierDesiccantNoFans_Impl::rotorPower() const {
      return getDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::RotorPower, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setRotorPower(double rotorPower) {
      return setDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::RotorPower, rotorPower);
    }

    void DehumidifierDesiccantNoFans_Impl::resetRotorPower() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::RotorPower, ""));
    }

    boost::optional<std::string> DehumidifierDesiccantNoFans_Impl::regenerationCoilObjectType() const {
      return getString(openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationCoilObjectType, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setRegenerationCoilObjectType(const std::string& regenerationCoilObjectType) {
      return setString(openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationCoilObjectType, regenerationCoilObjectType);
    }

    void DehumidifierDesiccantNoFans_Impl::resetRegenerationCoilObjectType() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationCoilObjectType, ""));
    }

    boost::optional<std::string> DehumidifierDesiccantNoFans_Impl::regenerationFanObjectType() const {
      return getString(openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationFanObjectType, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setRegenerationFanObjectType(const std::string& regenerationFanObjectType) {
      return setString(openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationFanObjectType, regenerationFanObjectType);
    }

    void DehumidifierDesiccantNoFans_Impl::resetRegenerationFanObjectType() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::RegenerationFanObjectType, ""));
    }

    boost::optional<std::string> DehumidifierDesiccantNoFans_Impl::performanceModelType() const {
      return getString(openstudio::Dehumidifier_Desiccant_NoFansFields::PerformanceModelType, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setPerformanceModelType(const std::string& performanceModelType) {
      return setString(openstudio::Dehumidifier_Desiccant_NoFansFields::PerformanceModelType, performanceModelType);
    }

    void DehumidifierDesiccantNoFans_Impl::resetPerformanceModelType() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::PerformanceModelType, ""));
    }

    boost::optional<double> DehumidifierDesiccantNoFans_Impl::nominalRegenerationTemperature() const {
      return getDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalRegenerationTemperature, true);
    }

    bool DehumidifierDesiccantNoFans_Impl::setNominalRegenerationTemperature(double nominalRegenerationTemperature) {
      return setDouble(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalRegenerationTemperature, nominalRegenerationTemperature);
    }

    void DehumidifierDesiccantNoFans_Impl::resetNominalRegenerationTemperature() {
      OS_ASSERT(setString(openstudio::Dehumidifier_Desiccant_NoFansFields::NominalRegenerationTemperature, ""));
    }

    std::vector<std::string> DehumidifierDesiccantNoFans_Impl::controlTypeValues() const {
      return openstudio::epmodel::DehumidifierDesiccantNoFans::controlTypeValues();
    }

    std::vector<std::string> DehumidifierDesiccantNoFans_Impl::regenerationCoilObjectTypeValues() const {
      return openstudio::epmodel::DehumidifierDesiccantNoFans::regenerationCoilObjectTypeValues();
    }

    std::vector<std::string> DehumidifierDesiccantNoFans_Impl::regenerationFanObjectTypeValues() const {
      return openstudio::epmodel::DehumidifierDesiccantNoFans::regenerationFanObjectTypeValues();
    }

    std::vector<std::string> DehumidifierDesiccantNoFans_Impl::performanceModelTypeValues() const {
      return openstudio::epmodel::DehumidifierDesiccantNoFans::performanceModelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
