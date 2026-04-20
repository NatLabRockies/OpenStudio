/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlThermostatTemperatureAndHumidity.hpp"
#include "ZoneControlThermostatTemperatureAndHumidity_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneControl_Thermostat_TemperatureAndHumidity_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneControlThermostatTemperatureAndHumidity::ZoneControlThermostatTemperatureAndHumidity(const Model& model)
    : ModelObject(ZoneControlThermostatTemperatureAndHumidity::iddObjectType(), model) {
    OS_ASSERT(setDehumidificationControlType("Overcool"));
    OS_ASSERT(setOvercoolRangeInputMethod("Constant"));
  }

  ZoneControlThermostatTemperatureAndHumidity::ZoneControlThermostatTemperatureAndHumidity(
    std::shared_ptr<detail::ZoneControlThermostatTemperatureAndHumidity_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlThermostatTemperatureAndHumidity::iddObjectType() {
    return IddObjectType::ZoneControl_Thermostat_TemperatureAndHumidity;
  }

  std::vector<std::string> ZoneControlThermostatTemperatureAndHumidity::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::DehumidificationControlType);
  }

  std::vector<std::string> ZoneControlThermostatTemperatureAndHumidity::overcoolRangeInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolRangeInputMethod);
  }

  std::string ZoneControlThermostatTemperatureAndHumidity::dehumidificationControlType() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->dehumidificationControlType();
  }

  bool ZoneControlThermostatTemperatureAndHumidity::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  bool ZoneControlThermostatTemperatureAndHumidity::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  void ZoneControlThermostatTemperatureAndHumidity::resetDehumidificationControlType() {
    getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->resetDehumidificationControlType();
  }

  std::string ZoneControlThermostatTemperatureAndHumidity::overcoolRangeInputMethod() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->overcoolRangeInputMethod();
  }

  bool ZoneControlThermostatTemperatureAndHumidity::setOvercoolRangeInputMethod(const std::string& overcoolRangeInputMethod) {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->setOvercoolRangeInputMethod(overcoolRangeInputMethod);
  }

  bool ZoneControlThermostatTemperatureAndHumidity::isOvercoolRangeInputMethodDefaulted() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->isOvercoolRangeInputMethodDefaulted();
  }

  void ZoneControlThermostatTemperatureAndHumidity::resetOvercoolRangeInputMethod() {
    getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->resetOvercoolRangeInputMethod();
  }

  boost::optional<double> ZoneControlThermostatTemperatureAndHumidity::overcoolConstantRange() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->overcoolConstantRange();
  }

  bool ZoneControlThermostatTemperatureAndHumidity::setOvercoolConstantRange(double overcoolConstantRange) {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->setOvercoolConstantRange(overcoolConstantRange);
  }

  bool ZoneControlThermostatTemperatureAndHumidity::isOvercoolConstantRangeDefaulted() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->isOvercoolConstantRangeDefaulted();
  }

  void ZoneControlThermostatTemperatureAndHumidity::resetOvercoolConstantRange() {
    getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->resetOvercoolConstantRange();
  }

  boost::optional<double> ZoneControlThermostatTemperatureAndHumidity::overcoolControlRatio() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->overcoolControlRatio();
  }

  bool ZoneControlThermostatTemperatureAndHumidity::setOvercoolControlRatio(double overcoolControlRatio) {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->setOvercoolControlRatio(overcoolControlRatio);
  }

  bool ZoneControlThermostatTemperatureAndHumidity::isOvercoolControlRatioDefaulted() const {
    return getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->isOvercoolControlRatioDefaulted();
  }

  void ZoneControlThermostatTemperatureAndHumidity::resetOvercoolControlRatio() {
    getImpl<detail::ZoneControlThermostatTemperatureAndHumidity_Impl>()->resetOvercoolControlRatio();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneControlThermostatTemperatureAndHumidity_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      const bool result =
        setString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::DehumidificationControlType, dehumidificationControlType);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::DehumidificationControlType);
    }

    void ZoneControlThermostatTemperatureAndHumidity_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::DehumidificationControlType, ""));
    }

    std::string ZoneControlThermostatTemperatureAndHumidity_Impl::overcoolRangeInputMethod() const {
      const auto value = getString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolRangeInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::setOvercoolRangeInputMethod(const std::string& overcoolRangeInputMethod) {
      const bool result =
        setString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolRangeInputMethod, overcoolRangeInputMethod);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::isOvercoolRangeInputMethodDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolRangeInputMethod);
    }

    void ZoneControlThermostatTemperatureAndHumidity_Impl::resetOvercoolRangeInputMethod() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolRangeInputMethod, ""));
    }

    boost::optional<double> ZoneControlThermostatTemperatureAndHumidity_Impl::overcoolConstantRange() const {
      return getDouble(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolConstantRange, true);
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::setOvercoolConstantRange(double overcoolConstantRange) {
      const bool result = setDouble(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolConstantRange, overcoolConstantRange);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::isOvercoolConstantRangeDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolConstantRange);
    }

    void ZoneControlThermostatTemperatureAndHumidity_Impl::resetOvercoolConstantRange() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolConstantRange, ""));
    }

    boost::optional<double> ZoneControlThermostatTemperatureAndHumidity_Impl::overcoolControlRatio() const {
      return getDouble(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolControlRatio, true);
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::setOvercoolControlRatio(double overcoolControlRatio) {
      const bool result = setDouble(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolControlRatio, overcoolControlRatio);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneControlThermostatTemperatureAndHumidity_Impl::isOvercoolControlRatioDefaulted() const {
      return isEmpty(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolControlRatio);
    }

    void ZoneControlThermostatTemperatureAndHumidity_Impl::resetOvercoolControlRatio() {
      OS_ASSERT(setString(openstudio::ZoneControl_Thermostat_TemperatureAndHumidityFields::OvercoolControlRatio, ""));
    }

    std::vector<std::string> ZoneControlThermostatTemperatureAndHumidity_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::ZoneControlThermostatTemperatureAndHumidity::dehumidificationControlTypeValues();
    }

    std::vector<std::string> ZoneControlThermostatTemperatureAndHumidity_Impl::overcoolRangeInputMethodValues() const {
      return openstudio::epmodel::ZoneControlThermostatTemperatureAndHumidity::overcoolRangeInputMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
