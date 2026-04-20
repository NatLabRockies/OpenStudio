/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACVentilatedSlab.hpp"
#include "ZoneHVACVentilatedSlab_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_VentilatedSlab_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACVentilatedSlab::ZoneHVACVentilatedSlab(const Model& model) : ModelObject(ZoneHVACVentilatedSlab::iddObjectType(), model) {}

  ZoneHVACVentilatedSlab::ZoneHVACVentilatedSlab(std::shared_ptr<detail::ZoneHVACVentilatedSlab_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACVentilatedSlab::iddObjectType() {
    return {IddObjectType::ZoneHVAC_VentilatedSlab};
  }

  std::vector<std::string> ZoneHVACVentilatedSlab::outdoorAirControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_VentilatedSlabFields::OutdoorAirControlType);
  }

  std::vector<std::string> ZoneHVACVentilatedSlab::systemConfigurationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_VentilatedSlabFields::SystemConfigurationType);
  }

  std::vector<std::string> ZoneHVACVentilatedSlab::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_VentilatedSlabFields::TemperatureControlType);
  }

  std::vector<std::string> ZoneHVACVentilatedSlab::coilOptionTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_VentilatedSlabFields::CoilOptionType);
  }

  std::vector<std::string> ZoneHVACVentilatedSlab::heatingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_VentilatedSlabFields::HeatingCoilObjectType);
  }

  std::vector<std::string> ZoneHVACVentilatedSlab::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_VentilatedSlabFields::CoolingCoilObjectType);
  }

  boost::optional<double> ZoneHVACVentilatedSlab::maximumAirFlowRate() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->maximumAirFlowRate();
  }

  bool ZoneHVACVentilatedSlab::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  bool ZoneHVACVentilatedSlab::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->isMaximumAirFlowRateAutosized();
  }

  void ZoneHVACVentilatedSlab::autosizeMaximumAirFlowRate() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<double> ZoneHVACVentilatedSlab::minimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->minimumOutdoorAirFlowRate();
  }

  bool ZoneHVACVentilatedSlab::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setMinimumOutdoorAirFlowRate(minimumOutdoorAirFlowRate);
  }

  bool ZoneHVACVentilatedSlab::isMinimumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->isMinimumOutdoorAirFlowRateAutosized();
  }

  void ZoneHVACVentilatedSlab::autosizeMinimumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->autosizeMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACVentilatedSlab::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ZoneHVACVentilatedSlab::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  bool ZoneHVACVentilatedSlab::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  void ZoneHVACVentilatedSlab::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  std::string ZoneHVACVentilatedSlab::outdoorAirControlType() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->outdoorAirControlType();
  }

  bool ZoneHVACVentilatedSlab::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setOutdoorAirControlType(outdoorAirControlType);
  }

  std::string ZoneHVACVentilatedSlab::systemConfigurationType() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->systemConfigurationType();
  }

  bool ZoneHVACVentilatedSlab::setSystemConfigurationType(const std::string& systemConfigurationType) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setSystemConfigurationType(systemConfigurationType);
  }

  bool ZoneHVACVentilatedSlab::isSystemConfigurationTypeDefaulted() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->isSystemConfigurationTypeDefaulted();
  }

  void ZoneHVACVentilatedSlab::resetSystemConfigurationType() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->resetSystemConfigurationType();
  }

  boost::optional<double> ZoneHVACVentilatedSlab::hollowCoreInsideDiameter() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->hollowCoreInsideDiameter();
  }

  bool ZoneHVACVentilatedSlab::setHollowCoreInsideDiameter(double hollowCoreInsideDiameter) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setHollowCoreInsideDiameter(hollowCoreInsideDiameter);
  }

  bool ZoneHVACVentilatedSlab::isHollowCoreInsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->isHollowCoreInsideDiameterDefaulted();
  }

  void ZoneHVACVentilatedSlab::resetHollowCoreInsideDiameter() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->resetHollowCoreInsideDiameter();
  }

  boost::optional<double> ZoneHVACVentilatedSlab::hollowCoreLength() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->hollowCoreLength();
  }

  bool ZoneHVACVentilatedSlab::setHollowCoreLength(double hollowCoreLength) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setHollowCoreLength(hollowCoreLength);
  }

  void ZoneHVACVentilatedSlab::resetHollowCoreLength() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->resetHollowCoreLength();
  }

  std::string ZoneHVACVentilatedSlab::temperatureControlType() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->temperatureControlType();
  }

  bool ZoneHVACVentilatedSlab::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  bool ZoneHVACVentilatedSlab::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->isTemperatureControlTypeDefaulted();
  }

  void ZoneHVACVentilatedSlab::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->resetTemperatureControlType();
  }

  std::string ZoneHVACVentilatedSlab::coilOptionType() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->coilOptionType();
  }

  bool ZoneHVACVentilatedSlab::setCoilOptionType(const std::string& coilOptionType) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setCoilOptionType(coilOptionType);
  }

  boost::optional<std::string> ZoneHVACVentilatedSlab::heatingCoilObjectType() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->heatingCoilObjectType();
  }

  bool ZoneHVACVentilatedSlab::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setHeatingCoilObjectType(heatingCoilObjectType);
  }

  void ZoneHVACVentilatedSlab::resetHeatingCoilObjectType() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->resetHeatingCoilObjectType();
  }

  boost::optional<std::string> ZoneHVACVentilatedSlab::coolingCoilObjectType() const {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->coolingCoilObjectType();
  }

  bool ZoneHVACVentilatedSlab::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

  void ZoneHVACVentilatedSlab::resetCoolingCoilObjectType() {
    getImpl<detail::ZoneHVACVentilatedSlab_Impl>()->resetCoolingCoilObjectType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACVentilatedSlab_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumAirFlowRate, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumAirFlowRate, maximumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACVentilatedSlab_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ZoneHVACVentilatedSlab_Impl::autosizeMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACVentilatedSlab_Impl::minimumOutdoorAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_VentilatedSlabFields::MinimumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_VentilatedSlabFields::MinimumOutdoorAirFlowRate, minimumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACVentilatedSlab_Impl::isMinimumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::MinimumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ZoneHVACVentilatedSlab_Impl::autosizeMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::MinimumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACVentilatedSlab_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACVentilatedSlab_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ZoneHVACVentilatedSlab_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    std::string ZoneHVACVentilatedSlab_Impl::outdoorAirControlType() const {
      const auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::OutdoorAirControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACVentilatedSlab_Impl::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
      return setString(openstudio::ZoneHVAC_VentilatedSlabFields::OutdoorAirControlType, outdoorAirControlType);
    }

    std::string ZoneHVACVentilatedSlab_Impl::systemConfigurationType() const {
      const auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::SystemConfigurationType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACVentilatedSlab_Impl::setSystemConfigurationType(const std::string& systemConfigurationType) {
      return setString(openstudio::ZoneHVAC_VentilatedSlabFields::SystemConfigurationType, systemConfigurationType);
    }

    bool ZoneHVACVentilatedSlab_Impl::isSystemConfigurationTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_VentilatedSlabFields::SystemConfigurationType);
    }

    void ZoneHVACVentilatedSlab_Impl::resetSystemConfigurationType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::SystemConfigurationType, ""));
    }

    boost::optional<double> ZoneHVACVentilatedSlab_Impl::hollowCoreInsideDiameter() const {
      return getDouble(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreInsideDiameter, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setHollowCoreInsideDiameter(double hollowCoreInsideDiameter) {
      const bool result = setDouble(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreInsideDiameter, hollowCoreInsideDiameter);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACVentilatedSlab_Impl::isHollowCoreInsideDiameterDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreInsideDiameter);
    }

    void ZoneHVACVentilatedSlab_Impl::resetHollowCoreInsideDiameter() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreInsideDiameter, ""));
    }

    boost::optional<double> ZoneHVACVentilatedSlab_Impl::hollowCoreLength() const {
      return getDouble(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreLength, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setHollowCoreLength(double hollowCoreLength) {
      const bool result = setDouble(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreLength, hollowCoreLength);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACVentilatedSlab_Impl::resetHollowCoreLength() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::HollowCoreLength, ""));
    }

    std::string ZoneHVACVentilatedSlab_Impl::temperatureControlType() const {
      const auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::TemperatureControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACVentilatedSlab_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      return setString(openstudio::ZoneHVAC_VentilatedSlabFields::TemperatureControlType, temperatureControlType);
    }

    bool ZoneHVACVentilatedSlab_Impl::isTemperatureControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_VentilatedSlabFields::TemperatureControlType);
    }

    void ZoneHVACVentilatedSlab_Impl::resetTemperatureControlType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::TemperatureControlType, ""));
    }

    std::string ZoneHVACVentilatedSlab_Impl::coilOptionType() const {
      const auto value = getString(openstudio::ZoneHVAC_VentilatedSlabFields::CoilOptionType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACVentilatedSlab_Impl::setCoilOptionType(const std::string& coilOptionType) {
      return setString(openstudio::ZoneHVAC_VentilatedSlabFields::CoilOptionType, coilOptionType);
    }

    boost::optional<std::string> ZoneHVACVentilatedSlab_Impl::heatingCoilObjectType() const {
      return getString(openstudio::ZoneHVAC_VentilatedSlabFields::HeatingCoilObjectType, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setHeatingCoilObjectType(const std::string& heatingCoilObjectType) {
      return setString(openstudio::ZoneHVAC_VentilatedSlabFields::HeatingCoilObjectType, heatingCoilObjectType);
    }

    void ZoneHVACVentilatedSlab_Impl::resetHeatingCoilObjectType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::HeatingCoilObjectType, ""));
    }

    boost::optional<std::string> ZoneHVACVentilatedSlab_Impl::coolingCoilObjectType() const {
      return getString(openstudio::ZoneHVAC_VentilatedSlabFields::CoolingCoilObjectType, true);
    }

    bool ZoneHVACVentilatedSlab_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      return setString(openstudio::ZoneHVAC_VentilatedSlabFields::CoolingCoilObjectType, coolingCoilObjectType);
    }

    void ZoneHVACVentilatedSlab_Impl::resetCoolingCoilObjectType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_VentilatedSlabFields::CoolingCoilObjectType, ""));
    }

    std::vector<std::string> ZoneHVACVentilatedSlab_Impl::outdoorAirControlTypeValues() const {
      return ZoneHVACVentilatedSlab::outdoorAirControlTypeValues();
    }

    std::vector<std::string> ZoneHVACVentilatedSlab_Impl::systemConfigurationTypeValues() const {
      return ZoneHVACVentilatedSlab::systemConfigurationTypeValues();
    }

    std::vector<std::string> ZoneHVACVentilatedSlab_Impl::temperatureControlTypeValues() const {
      return ZoneHVACVentilatedSlab::temperatureControlTypeValues();
    }

    std::vector<std::string> ZoneHVACVentilatedSlab_Impl::coilOptionTypeValues() const {
      return ZoneHVACVentilatedSlab::coilOptionTypeValues();
    }

    std::vector<std::string> ZoneHVACVentilatedSlab_Impl::heatingCoilObjectTypeValues() const {
      return ZoneHVACVentilatedSlab::heatingCoilObjectTypeValues();
    }

    std::vector<std::string> ZoneHVACVentilatedSlab_Impl::coolingCoilObjectTypeValues() const {
      return ZoneHVACVentilatedSlab::coolingCoilObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
