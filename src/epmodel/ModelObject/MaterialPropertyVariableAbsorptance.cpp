/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/MaterialPropertyVariableAbsorptance.hpp"
#include "ModelObject/MaterialPropertyVariableAbsorptance_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/MaterialProperty_VariableAbsorptance_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyVariableAbsorptance::MaterialPropertyVariableAbsorptance(const Model& model)
    : ModelObject(MaterialPropertyVariableAbsorptance::iddObjectType(), model) {}

  MaterialPropertyVariableAbsorptance::MaterialPropertyVariableAbsorptance(std::shared_ptr<detail::MaterialPropertyVariableAbsorptance_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyVariableAbsorptance::iddObjectType() {
    return IddObjectType::MaterialProperty_VariableAbsorptance;
  }

  std::vector<std::string> MaterialPropertyVariableAbsorptance::controlSignalValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::MaterialProperty_VariableAbsorptanceFields::ControlSignal);
  }

  std::string MaterialPropertyVariableAbsorptance::controlSignal() const {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->controlSignal();
  }

  bool MaterialPropertyVariableAbsorptance::isControlSignalDefaulted() const {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->isControlSignalDefaulted();
  }

  bool MaterialPropertyVariableAbsorptance::setControlSignal(const std::string& controlSignal) {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->setControlSignal(controlSignal);
  }

  void MaterialPropertyVariableAbsorptance::resetControlSignal() {
    getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->resetControlSignal();
  }

  boost::optional<std::string> MaterialPropertyVariableAbsorptance::thermalAbsorptanceFunctionName() const {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->thermalAbsorptanceFunctionName();
  }

  bool MaterialPropertyVariableAbsorptance::setThermalAbsorptanceFunctionName(const std::string& thermalAbsorptanceFunctionName) {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->setThermalAbsorptanceFunctionName(thermalAbsorptanceFunctionName);
  }

  void MaterialPropertyVariableAbsorptance::resetThermalAbsorptanceFunctionName() {
    getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->resetThermalAbsorptanceFunctionName();
  }

  boost::optional<std::string> MaterialPropertyVariableAbsorptance::thermalAbsorptanceScheduleName() const {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->thermalAbsorptanceScheduleName();
  }

  bool MaterialPropertyVariableAbsorptance::setThermalAbsorptanceScheduleName(const std::string& thermalAbsorptanceScheduleName) {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->setThermalAbsorptanceScheduleName(thermalAbsorptanceScheduleName);
  }

  void MaterialPropertyVariableAbsorptance::resetThermalAbsorptanceScheduleName() {
    getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->resetThermalAbsorptanceScheduleName();
  }

  boost::optional<std::string> MaterialPropertyVariableAbsorptance::solarAbsorptanceFunctionName() const {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->solarAbsorptanceFunctionName();
  }

  bool MaterialPropertyVariableAbsorptance::setSolarAbsorptanceFunctionName(const std::string& solarAbsorptanceFunctionName) {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->setSolarAbsorptanceFunctionName(solarAbsorptanceFunctionName);
  }

  void MaterialPropertyVariableAbsorptance::resetSolarAbsorptanceFunctionName() {
    getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->resetSolarAbsorptanceFunctionName();
  }

  boost::optional<std::string> MaterialPropertyVariableAbsorptance::solarAbsorptanceScheduleName() const {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->solarAbsorptanceScheduleName();
  }

  bool MaterialPropertyVariableAbsorptance::setSolarAbsorptanceScheduleName(const std::string& solarAbsorptanceScheduleName) {
    return getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->setSolarAbsorptanceScheduleName(solarAbsorptanceScheduleName);
  }

  void MaterialPropertyVariableAbsorptance::resetSolarAbsorptanceScheduleName() {
    getImpl<detail::MaterialPropertyVariableAbsorptance_Impl>()->resetSolarAbsorptanceScheduleName();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string MaterialPropertyVariableAbsorptance_Impl::controlSignal() const {
      if (isEmpty(openstudio::MaterialProperty_VariableAbsorptanceFields::ControlSignal)) {
        return "SurfaceTemperature";
      }
      if (auto value = getString(openstudio::MaterialProperty_VariableAbsorptanceFields::ControlSignal, false)) {
        return *value;
      }
      return "SurfaceTemperature";
    }

    bool MaterialPropertyVariableAbsorptance_Impl::isControlSignalDefaulted() const {
      return isEmpty(openstudio::MaterialProperty_VariableAbsorptanceFields::ControlSignal);
    }

    bool MaterialPropertyVariableAbsorptance_Impl::setControlSignal(const std::string& controlSignal) {
      return setString(openstudio::MaterialProperty_VariableAbsorptanceFields::ControlSignal, controlSignal);
    }

    void MaterialPropertyVariableAbsorptance_Impl::resetControlSignal() {
      OS_ASSERT(setString(openstudio::MaterialProperty_VariableAbsorptanceFields::ControlSignal, ""));
    }

    std::vector<std::string> MaterialPropertyVariableAbsorptance_Impl::controlSignalValues() const {
      return MaterialPropertyVariableAbsorptance::controlSignalValues();
    }

    boost::optional<std::string> MaterialPropertyVariableAbsorptance_Impl::thermalAbsorptanceFunctionName() const {
      if (isEmpty(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceFunctionName)) {
        return boost::none;
      }
      if (auto value = getString(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceFunctionName, false)) {
        return *value;
      }
      return boost::none;
    }

    bool MaterialPropertyVariableAbsorptance_Impl::setThermalAbsorptanceFunctionName(const std::string& thermalAbsorptanceFunctionName) {
      return setString(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceFunctionName, thermalAbsorptanceFunctionName);
    }

    void MaterialPropertyVariableAbsorptance_Impl::resetThermalAbsorptanceFunctionName() {
      OS_ASSERT(setString(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceFunctionName, ""));
    }

    boost::optional<std::string> MaterialPropertyVariableAbsorptance_Impl::thermalAbsorptanceScheduleName() const {
      if (isEmpty(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceScheduleName)) {
        return boost::none;
      }
      if (auto value = getString(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceScheduleName, false)) {
        return *value;
      }
      return boost::none;
    }

    bool MaterialPropertyVariableAbsorptance_Impl::setThermalAbsorptanceScheduleName(const std::string& thermalAbsorptanceScheduleName) {
      return setString(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceScheduleName, thermalAbsorptanceScheduleName);
    }

    void MaterialPropertyVariableAbsorptance_Impl::resetThermalAbsorptanceScheduleName() {
      OS_ASSERT(setString(openstudio::MaterialProperty_VariableAbsorptanceFields::ThermalAbsorptanceScheduleName, ""));
    }

    boost::optional<std::string> MaterialPropertyVariableAbsorptance_Impl::solarAbsorptanceFunctionName() const {
      if (isEmpty(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceFunctionName)) {
        return boost::none;
      }
      if (auto value = getString(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceFunctionName, false)) {
        return *value;
      }
      return boost::none;
    }

    bool MaterialPropertyVariableAbsorptance_Impl::setSolarAbsorptanceFunctionName(const std::string& solarAbsorptanceFunctionName) {
      return setString(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceFunctionName, solarAbsorptanceFunctionName);
    }

    void MaterialPropertyVariableAbsorptance_Impl::resetSolarAbsorptanceFunctionName() {
      OS_ASSERT(setString(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceFunctionName, ""));
    }

    boost::optional<std::string> MaterialPropertyVariableAbsorptance_Impl::solarAbsorptanceScheduleName() const {
      if (isEmpty(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceScheduleName)) {
        return boost::none;
      }
      if (auto value = getString(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceScheduleName, false)) {
        return *value;
      }
      return boost::none;
    }

    bool MaterialPropertyVariableAbsorptance_Impl::setSolarAbsorptanceScheduleName(const std::string& solarAbsorptanceScheduleName) {
      return setString(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceScheduleName, solarAbsorptanceScheduleName);
    }

    void MaterialPropertyVariableAbsorptance_Impl::resetSolarAbsorptanceScheduleName() {
      OS_ASSERT(setString(openstudio::MaterialProperty_VariableAbsorptanceFields::SolarAbsorptanceScheduleName, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
