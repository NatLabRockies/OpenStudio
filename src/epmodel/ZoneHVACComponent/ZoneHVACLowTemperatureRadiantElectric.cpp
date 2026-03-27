/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_Electric_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACLowTemperatureRadiantElectric::ZoneHVACLowTemperatureRadiantElectric(const Model& model)
    : ZoneHVACComponent(ZoneHVACLowTemperatureRadiantElectric::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>());
  }

  ZoneHVACLowTemperatureRadiantElectric::ZoneHVACLowTemperatureRadiantElectric(
    std::shared_ptr<detail::ZoneHVACLowTemperatureRadiantElectric_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACLowTemperatureRadiantElectric::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_Electric;
  }

  std::vector<std::string> ZoneHVACLowTemperatureRadiantElectric::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType);
  }

  boost::optional<double> ZoneHVACLowTemperatureRadiantElectric::maximumElectricalPowertoPanel() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->maximumElectricalPowertoPanel();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isMaximumElectricalPowertoPanelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isMaximumElectricalPowertoPanelDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isMaximumElectricalPowertoPanelAutosized() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isMaximumElectricalPowertoPanelAutosized();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setMaximumElectricalPowertoPanel(maximumElectricalPowertoPanel);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetMaximumElectricalPowertoPanel() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetMaximumElectricalPowertoPanel();
  }

  void ZoneHVACLowTemperatureRadiantElectric::autosizeMaximumElectricalPowertoPanel() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->autosizeMaximumElectricalPowertoPanel();
  }

  std::string ZoneHVACLowTemperatureRadiantElectric::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetTemperatureControlType();
  }

  std::string ZoneHVACLowTemperatureRadiantElectric::setpointControlType() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setpointControlType();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isSetpointControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isSetpointControlTypeDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setSetpointControlType(const std::string& setpointControlType) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setSetpointControlType(setpointControlType);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetSetpointControlType() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetSetpointControlType();
  }

  double ZoneHVACLowTemperatureRadiantElectric::heatingThrottlingRange() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->heatingThrottlingRange();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::isHeatingThrottlingRangeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->isHeatingThrottlingRangeDefaulted();
  }

  bool ZoneHVACLowTemperatureRadiantElectric::setHeatingThrottlingRange(double heatingThrottlingRange) {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->setHeatingThrottlingRange(heatingThrottlingRange);
  }

  void ZoneHVACLowTemperatureRadiantElectric::resetHeatingThrottlingRange() {
    getImpl<detail::ZoneHVACLowTemperatureRadiantElectric_Impl>()->resetHeatingThrottlingRange();
  }

  namespace detail {

    boost::optional<double> ZoneHVACLowTemperatureRadiantElectric_Impl::maximumElectricalPowertoPanel() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isMaximumElectricalPowertoPanelDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isMaximumElectricalPowertoPanelAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setMaximumElectricalPowertoPanel(double maximumElectricalPowertoPanel) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, maximumElectricalPowertoPanel);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetMaximumElectricalPowertoPanel() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::autosizeMaximumElectricalPowertoPanel() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingDesignCapacity, "Autosize", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACLowTemperatureRadiantElectric_Impl::temperatureControlType() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isTemperatureControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType, temperatureControlType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetTemperatureControlType() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::TemperatureControlType, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACLowTemperatureRadiantElectric_Impl::setpointControlType() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isSetpointControlTypeDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setSetpointControlType(const std::string& setpointControlType) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType, setpointControlType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetSetpointControlType() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::SetpointControlType, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACLowTemperatureRadiantElectric_Impl::heatingThrottlingRange() const {
      auto value = getDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::isHeatingThrottlingRangeDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange);
    }

    bool ZoneHVACLowTemperatureRadiantElectric_Impl::setHeatingThrottlingRange(double heatingThrottlingRange) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange, heatingThrottlingRange, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTemperatureRadiantElectric_Impl::resetHeatingThrottlingRange() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ElectricFields::HeatingThrottlingRange, "", false);
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
