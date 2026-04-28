/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "WindowThermalModelParams.hpp"
#include "WindowThermalModelParams_Impl.hpp"

#include "Model.hpp"

#include <utility>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WindowThermalModel_Params_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WindowThermalModelParams::WindowThermalModelParams(const Model& model) : ModelObject(WindowThermalModelParams::iddObjectType(), model) {}

  WindowThermalModelParams::WindowThermalModelParams(std::shared_ptr<detail::WindowThermalModelParams_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WindowThermalModelParams::iddObjectType() {
    return IddObjectType::WindowThermalModel_Params;
  }

  std::vector<std::string> WindowThermalModelParams::standardValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowThermalModel_ParamsFields::standard);
  }

  std::vector<std::string> WindowThermalModelParams::thermalModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowThermalModel_ParamsFields::ThermalModel);
  }

  std::vector<std::string> WindowThermalModelParams::deflectionModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WindowThermalModel_ParamsFields::DeflectionModel);
  }

  std::string WindowThermalModelParams::standard() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->standard();
  }

  bool WindowThermalModelParams::isStandardDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isStandardDefaulted();
  }

  bool WindowThermalModelParams::setStandard(const std::string& standard) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setStandard(standard);
  }

  void WindowThermalModelParams::resetStandard() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetStandard();
  }

  std::string WindowThermalModelParams::thermalModel() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->thermalModel();
  }

  bool WindowThermalModelParams::isThermalModelDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isThermalModelDefaulted();
  }

  bool WindowThermalModelParams::setThermalModel(const std::string& thermalModel) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setThermalModel(thermalModel);
  }

  void WindowThermalModelParams::resetThermalModel() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetThermalModel();
  }

  double WindowThermalModelParams::sdScalar() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->sdScalar();
  }

  bool WindowThermalModelParams::isSdScalarDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isSdScalarDefaulted();
  }

  bool WindowThermalModelParams::setSdScalar(double sdScalar) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setSdScalar(sdScalar);
  }

  void WindowThermalModelParams::resetSdScalar() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetSdScalar();
  }

  std::string WindowThermalModelParams::deflectionModel() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->deflectionModel();
  }

  bool WindowThermalModelParams::isDeflectionModelDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isDeflectionModelDefaulted();
  }

  bool WindowThermalModelParams::setDeflectionModel(const std::string& deflectionModel) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setDeflectionModel(deflectionModel);
  }

  void WindowThermalModelParams::resetDeflectionModel() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetDeflectionModel();
  }

  double WindowThermalModelParams::vacuumPressureLimit() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->vacuumPressureLimit();
  }

  bool WindowThermalModelParams::isVacuumPressureLimitDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isVacuumPressureLimitDefaulted();
  }

  bool WindowThermalModelParams::setVacuumPressureLimit(double vacuumPressureLimit) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setVacuumPressureLimit(vacuumPressureLimit);
  }

  void WindowThermalModelParams::resetVacuumPressureLimit() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetVacuumPressureLimit();
  }

  double WindowThermalModelParams::initialTemperature() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->initialTemperature();
  }

  bool WindowThermalModelParams::isInitialTemperatureDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isInitialTemperatureDefaulted();
  }

  bool WindowThermalModelParams::setInitialTemperature(double initialTemperature) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setInitialTemperature(initialTemperature);
  }

  void WindowThermalModelParams::resetInitialTemperature() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetInitialTemperature();
  }

  double WindowThermalModelParams::initialPressure() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->initialPressure();
  }

  bool WindowThermalModelParams::isInitialPressureDefaulted() const {
    return getImpl<detail::WindowThermalModelParams_Impl>()->isInitialPressureDefaulted();
  }

  bool WindowThermalModelParams::setInitialPressure(double initialPressure) {
    return getImpl<detail::WindowThermalModelParams_Impl>()->setInitialPressure(initialPressure);
  }

  void WindowThermalModelParams::resetInitialPressure() {
    getImpl<detail::WindowThermalModelParams_Impl>()->resetInitialPressure();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string WindowThermalModelParams_Impl::standard() const {
      const auto value = getString(openstudio::WindowThermalModel_ParamsFields::standard, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isStandardDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::standard);
    }

    bool WindowThermalModelParams_Impl::setStandard(const std::string& standard) {
      return setString(openstudio::WindowThermalModel_ParamsFields::standard, standard);
    }

    void WindowThermalModelParams_Impl::resetStandard() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::standard, ""));
    }

    std::string WindowThermalModelParams_Impl::thermalModel() const {
      const auto value = getString(openstudio::WindowThermalModel_ParamsFields::ThermalModel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isThermalModelDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::ThermalModel);
    }

    bool WindowThermalModelParams_Impl::setThermalModel(const std::string& thermalModel) {
      return setString(openstudio::WindowThermalModel_ParamsFields::ThermalModel, thermalModel);
    }

    void WindowThermalModelParams_Impl::resetThermalModel() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::ThermalModel, ""));
    }

    double WindowThermalModelParams_Impl::sdScalar() const {
      const auto value = getDouble(openstudio::WindowThermalModel_ParamsFields::SDScalar, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isSdScalarDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::SDScalar);
    }

    bool WindowThermalModelParams_Impl::setSdScalar(double sdScalar) {
      const bool result = setDouble(openstudio::WindowThermalModel_ParamsFields::SDScalar, sdScalar);
      OS_ASSERT(result);
      return result;
    }

    void WindowThermalModelParams_Impl::resetSdScalar() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::SDScalar, ""));
    }

    std::string WindowThermalModelParams_Impl::deflectionModel() const {
      const auto value = getString(openstudio::WindowThermalModel_ParamsFields::DeflectionModel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isDeflectionModelDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::DeflectionModel);
    }

    bool WindowThermalModelParams_Impl::setDeflectionModel(const std::string& deflectionModel) {
      return setString(openstudio::WindowThermalModel_ParamsFields::DeflectionModel, deflectionModel);
    }

    void WindowThermalModelParams_Impl::resetDeflectionModel() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::DeflectionModel, ""));
    }

    double WindowThermalModelParams_Impl::vacuumPressureLimit() const {
      const auto value = getDouble(openstudio::WindowThermalModel_ParamsFields::VacuumPressureLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isVacuumPressureLimitDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::VacuumPressureLimit);
    }

    bool WindowThermalModelParams_Impl::setVacuumPressureLimit(double vacuumPressureLimit) {
      const bool result = setDouble(openstudio::WindowThermalModel_ParamsFields::VacuumPressureLimit, vacuumPressureLimit);
      OS_ASSERT(result);
      return result;
    }

    void WindowThermalModelParams_Impl::resetVacuumPressureLimit() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::VacuumPressureLimit, ""));
    }

    double WindowThermalModelParams_Impl::initialTemperature() const {
      const auto value = getDouble(openstudio::WindowThermalModel_ParamsFields::Initialtemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isInitialTemperatureDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::Initialtemperature);
    }

    bool WindowThermalModelParams_Impl::setInitialTemperature(double initialTemperature) {
      const bool result = setDouble(openstudio::WindowThermalModel_ParamsFields::Initialtemperature, initialTemperature);
      OS_ASSERT(result);
      return result;
    }

    void WindowThermalModelParams_Impl::resetInitialTemperature() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::Initialtemperature, ""));
    }

    double WindowThermalModelParams_Impl::initialPressure() const {
      const auto value = getDouble(openstudio::WindowThermalModel_ParamsFields::Initialpressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WindowThermalModelParams_Impl::isInitialPressureDefaulted() const {
      return isEmpty(openstudio::WindowThermalModel_ParamsFields::Initialpressure);
    }

    bool WindowThermalModelParams_Impl::setInitialPressure(double initialPressure) {
      const bool result = setDouble(openstudio::WindowThermalModel_ParamsFields::Initialpressure, initialPressure);
      OS_ASSERT(result);
      return result;
    }

    void WindowThermalModelParams_Impl::resetInitialPressure() {
      OS_ASSERT(setString(openstudio::WindowThermalModel_ParamsFields::Initialpressure, ""));
    }

    std::vector<std::string> WindowThermalModelParams_Impl::standardValues() const {
      return openstudio::epmodel::WindowThermalModelParams::standardValues();
    }

    std::vector<std::string> WindowThermalModelParams_Impl::thermalModelValues() const {
      return openstudio::epmodel::WindowThermalModelParams::thermalModelValues();
    }

    std::vector<std::string> WindowThermalModelParams_Impl::deflectionModelValues() const {
      return openstudio::epmodel::WindowThermalModelParams::deflectionModelValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
