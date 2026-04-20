/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantHotWaterLoop.hpp"
#include "HVACTemplatePlantHotWaterLoop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Plant_HotWaterLoop_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplatePlantHotWaterLoop::HVACTemplatePlantHotWaterLoop(const Model& model)
    : ModelObject(HVACTemplatePlantHotWaterLoop::iddObjectType(), model) {}

  HVACTemplatePlantHotWaterLoop::HVACTemplatePlantHotWaterLoop(std::shared_ptr<detail::HVACTemplatePlantHotWaterLoop_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplatePlantHotWaterLoop::iddObjectType() {
    return IddObjectType::HVACTemplate_Plant_HotWaterLoop;
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::pumpControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_HotWaterLoopFields::PumpControlType);
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::hotWaterPlantOperationSchemeTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantOperationSchemeType);
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::hotWaterPumpConfigurationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpConfiguration);
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::hotWaterSetpointResetTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointResetType);
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::hotWaterPumpTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpType);
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::fluidTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_HotWaterLoopFields::FluidType);
  }

  std::vector<std::string> HVACTemplatePlantHotWaterLoop::loadDistributionSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoadDistributionScheme);
  }

  std::string HVACTemplatePlantHotWaterLoop::pumpControlType() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->pumpControlType();
  }

  bool HVACTemplatePlantHotWaterLoop::isPumpControlTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isPumpControlTypeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setPumpControlType(const std::string& pumpControlType) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setPumpControlType(pumpControlType);
  }

  void HVACTemplatePlantHotWaterLoop::resetPumpControlType() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetPumpControlType();
  }

  std::string HVACTemplatePlantHotWaterLoop::hotWaterPlantOperationSchemeType() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterPlantOperationSchemeType();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterPlantOperationSchemeTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterPlantOperationSchemeTypeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterPlantOperationSchemeType(const std::string& hotWaterPlantOperationSchemeType) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterPlantOperationSchemeType(hotWaterPlantOperationSchemeType);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterPlantOperationSchemeType() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterPlantOperationSchemeType();
  }

  double HVACTemplatePlantHotWaterLoop::hotWaterDesignSetpoint() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterDesignSetpoint();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterDesignSetpointDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterDesignSetpointDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterDesignSetpoint(double hotWaterDesignSetpoint) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterDesignSetpoint(hotWaterDesignSetpoint);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterDesignSetpoint() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterDesignSetpoint();
  }

  std::string HVACTemplatePlantHotWaterLoop::hotWaterPumpConfiguration() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterPumpConfiguration();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterPumpConfigurationDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterPumpConfigurationDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterPumpConfiguration(const std::string& hotWaterPumpConfiguration) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterPumpConfiguration(hotWaterPumpConfiguration);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterPumpConfiguration() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterPumpConfiguration();
  }

  double HVACTemplatePlantHotWaterLoop::hotWaterPumpRatedHead() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterPumpRatedHead();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterPumpRatedHeadDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterPumpRatedHeadDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterPumpRatedHead(double hotWaterPumpRatedHead) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterPumpRatedHead(hotWaterPumpRatedHead);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterPumpRatedHead() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterPumpRatedHead();
  }

  std::string HVACTemplatePlantHotWaterLoop::hotWaterSetpointResetType() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterSetpointResetType();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterSetpointResetTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterSetpointResetTypeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterSetpointResetType(const std::string& hotWaterSetpointResetType) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterSetpointResetType(hotWaterSetpointResetType);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterSetpointResetType() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterSetpointResetType();
  }

  double HVACTemplatePlantHotWaterLoop::hotWaterSetpointatOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterSetpointatOutdoorDryBulbLow();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterSetpointatOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterSetpointatOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterSetpointatOutdoorDryBulbLow(double hotWaterSetpointatOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterSetpointatOutdoorDryBulbLow(hotWaterSetpointatOutdoorDryBulbLow);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterSetpointatOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterSetpointatOutdoorDryBulbLow();
  }

  double HVACTemplatePlantHotWaterLoop::hotWaterResetOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterResetOutdoorDryBulbLow();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterResetOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterResetOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterResetOutdoorDryBulbLow(double hotWaterResetOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterResetOutdoorDryBulbLow(hotWaterResetOutdoorDryBulbLow);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterResetOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterResetOutdoorDryBulbLow();
  }

  double HVACTemplatePlantHotWaterLoop::hotWaterSetpointatOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterSetpointatOutdoorDryBulbHigh();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterSetpointatOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterSetpointatOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterSetpointatOutdoorDryBulbHigh(double hotWaterSetpointatOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterSetpointatOutdoorDryBulbHigh(hotWaterSetpointatOutdoorDryBulbHigh);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterSetpointatOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterSetpointatOutdoorDryBulbHigh();
  }

  double HVACTemplatePlantHotWaterLoop::hotWaterResetOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterResetOutdoorDryBulbHigh();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterResetOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterResetOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterResetOutdoorDryBulbHigh(double hotWaterResetOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterResetOutdoorDryBulbHigh(hotWaterResetOutdoorDryBulbHigh);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterResetOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterResetOutdoorDryBulbHigh();
  }

  std::string HVACTemplatePlantHotWaterLoop::hotWaterPumpType() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->hotWaterPumpType();
  }

  bool HVACTemplatePlantHotWaterLoop::isHotWaterPumpTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isHotWaterPumpTypeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setHotWaterPumpType(const std::string& hotWaterPumpType) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setHotWaterPumpType(hotWaterPumpType);
  }

  void HVACTemplatePlantHotWaterLoop::resetHotWaterPumpType() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetHotWaterPumpType();
  }

  bool HVACTemplatePlantHotWaterLoop::supplySideBypassPipe() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->supplySideBypassPipe();
  }

  bool HVACTemplatePlantHotWaterLoop::isSupplySideBypassPipeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isSupplySideBypassPipeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setSupplySideBypassPipe(bool supplySideBypassPipe) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setSupplySideBypassPipe(supplySideBypassPipe);
  }

  void HVACTemplatePlantHotWaterLoop::resetSupplySideBypassPipe() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetSupplySideBypassPipe();
  }

  bool HVACTemplatePlantHotWaterLoop::demandSideBypassPipe() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->demandSideBypassPipe();
  }

  bool HVACTemplatePlantHotWaterLoop::isDemandSideBypassPipeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isDemandSideBypassPipeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setDemandSideBypassPipe(bool demandSideBypassPipe) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setDemandSideBypassPipe(demandSideBypassPipe);
  }

  void HVACTemplatePlantHotWaterLoop::resetDemandSideBypassPipe() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetDemandSideBypassPipe();
  }

  std::string HVACTemplatePlantHotWaterLoop::fluidType() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->fluidType();
  }

  bool HVACTemplatePlantHotWaterLoop::isFluidTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isFluidTypeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setFluidType(const std::string& fluidType) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setFluidType(fluidType);
  }

  void HVACTemplatePlantHotWaterLoop::resetFluidType() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetFluidType();
  }

  double HVACTemplatePlantHotWaterLoop::loopDesignDeltaTemperature() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->loopDesignDeltaTemperature();
  }

  bool HVACTemplatePlantHotWaterLoop::isLoopDesignDeltaTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isLoopDesignDeltaTemperatureDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setLoopDesignDeltaTemperature(loopDesignDeltaTemperature);
  }

  void HVACTemplatePlantHotWaterLoop::resetLoopDesignDeltaTemperature() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetLoopDesignDeltaTemperature();
  }

  boost::optional<double> HVACTemplatePlantHotWaterLoop::maximumOutdoorDryBulbTemperature() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->maximumOutdoorDryBulbTemperature();
  }

  bool HVACTemplatePlantHotWaterLoop::setMaximumOutdoorDryBulbTemperature(double maximumOutdoorDryBulbTemperature) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setMaximumOutdoorDryBulbTemperature(maximumOutdoorDryBulbTemperature);
  }

  void HVACTemplatePlantHotWaterLoop::resetMaximumOutdoorDryBulbTemperature() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetMaximumOutdoorDryBulbTemperature();
  }

  std::string HVACTemplatePlantHotWaterLoop::loadDistributionScheme() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->loadDistributionScheme();
  }

  bool HVACTemplatePlantHotWaterLoop::isLoadDistributionSchemeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->isLoadDistributionSchemeDefaulted();
  }

  bool HVACTemplatePlantHotWaterLoop::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
    return getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->setLoadDistributionScheme(loadDistributionScheme);
  }

  void HVACTemplatePlantHotWaterLoop::resetLoadDistributionScheme() {
    getImpl<detail::HVACTemplatePlantHotWaterLoop_Impl>()->resetLoadDistributionScheme();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    std::string HVACTemplatePlantHotWaterLoop_Impl::pumpControlType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::PumpControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantHotWaterLoop_Impl::hotWaterPlantOperationSchemeType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantOperationSchemeType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::hotWaterDesignSetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterDesignSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantHotWaterLoop_Impl::hotWaterPumpConfiguration() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpConfiguration, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::hotWaterPumpRatedHead() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpRatedHead, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantHotWaterLoop_Impl::hotWaterSetpointResetType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointResetType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::hotWaterSetpointatOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::hotWaterResetOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::hotWaterSetpointatOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::hotWaterResetOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantHotWaterLoop_Impl::hotWaterPumpType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::supplySideBypassPipe() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_HotWaterLoopFields::SupplySideBypassPipe);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::demandSideBypassPipe() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_HotWaterLoopFields::DemandSideBypassPipe);
    }

    std::string HVACTemplatePlantHotWaterLoop_Impl::fluidType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::FluidType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantHotWaterLoop_Impl::loopDesignDeltaTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoopDesignDeltaTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> HVACTemplatePlantHotWaterLoop_Impl::maximumOutdoorDryBulbTemperature() const {
      return getDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::MaximumOutdoorDryBulbTemperature, true);
    }

    std::string HVACTemplatePlantHotWaterLoop_Impl::loadDistributionScheme() const {
      auto value = getString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoadDistributionScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isPumpControlTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::PumpControlType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterPlantOperationSchemeTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantOperationSchemeType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterDesignSetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterDesignSetpoint);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterPumpConfigurationDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpConfiguration);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterPumpRatedHeadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpRatedHead);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterSetpointResetTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointResetType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterSetpointatOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbLow);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterResetOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbLow);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterSetpointatOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbHigh);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterResetOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbHigh);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isHotWaterPumpTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isSupplySideBypassPipeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::SupplySideBypassPipe);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isDemandSideBypassPipeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::DemandSideBypassPipe);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isFluidTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::FluidType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isLoopDesignDeltaTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoopDesignDeltaTemperature);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::isLoadDistributionSchemeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoadDistributionScheme);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setPumpControlType(const std::string& pumpControlType) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::PumpControlType, pumpControlType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterPlantOperationSchemeType(const std::string& hotWaterPlantOperationSchemeType) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantOperationSchemeType, hotWaterPlantOperationSchemeType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterDesignSetpoint(double hotWaterDesignSetpoint) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterDesignSetpoint, hotWaterDesignSetpoint);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterPumpConfiguration(const std::string& hotWaterPumpConfiguration) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpConfiguration, hotWaterPumpConfiguration);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterPumpRatedHead(double hotWaterPumpRatedHead) {
      return setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpRatedHead, hotWaterPumpRatedHead);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterSetpointResetType(const std::string& hotWaterSetpointResetType) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointResetType, hotWaterSetpointResetType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterSetpointatOutdoorDryBulbLow(double hotWaterSetpointatOutdoorDryBulbLow) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbLow, hotWaterSetpointatOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterResetOutdoorDryBulbLow(double hotWaterResetOutdoorDryBulbLow) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbLow, hotWaterResetOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterSetpointatOutdoorDryBulbHigh(double hotWaterSetpointatOutdoorDryBulbHigh) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbHigh, hotWaterSetpointatOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterResetOutdoorDryBulbHigh(double hotWaterResetOutdoorDryBulbHigh) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbHigh, hotWaterResetOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setHotWaterPumpType(const std::string& hotWaterPumpType) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpType, hotWaterPumpType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setSupplySideBypassPipe(bool supplySideBypassPipe) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_HotWaterLoopFields::SupplySideBypassPipe, supplySideBypassPipe);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setDemandSideBypassPipe(bool demandSideBypassPipe) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_HotWaterLoopFields::DemandSideBypassPipe, demandSideBypassPipe);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setFluidType(const std::string& fluidType) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::FluidType, fluidType);
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoopDesignDeltaTemperature, loopDesignDeltaTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setMaximumOutdoorDryBulbTemperature(double maximumOutdoorDryBulbTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_HotWaterLoopFields::MaximumOutdoorDryBulbTemperature, maximumOutdoorDryBulbTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantHotWaterLoop_Impl::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
      return setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoadDistributionScheme, loadDistributionScheme);
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetPumpControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::PumpControlType, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterPlantOperationSchemeType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantOperationSchemeType, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterDesignSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterDesignSetpoint, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterPumpConfiguration() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpConfiguration, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterPumpRatedHead() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpRatedHead, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterSetpointResetType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointResetType, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterSetpointatOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbLow, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterResetOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbLow, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterSetpointatOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbHigh, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterResetOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbHigh, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetHotWaterPumpType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpType, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetSupplySideBypassPipe() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::SupplySideBypassPipe, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetDemandSideBypassPipe() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::DemandSideBypassPipe, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetFluidType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::FluidType, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetLoopDesignDeltaTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoopDesignDeltaTemperature, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetMaximumOutdoorDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::MaximumOutdoorDryBulbTemperature, ""));
    }

    void HVACTemplatePlantHotWaterLoop_Impl::resetLoadDistributionScheme() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_HotWaterLoopFields::LoadDistributionScheme, ""));
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::pumpControlTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::pumpControlTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::hotWaterPlantOperationSchemeTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::hotWaterPlantOperationSchemeTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::hotWaterPumpConfigurationValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::hotWaterPumpConfigurationValues();
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::hotWaterSetpointResetTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::hotWaterSetpointResetTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::hotWaterPumpTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::hotWaterPumpTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::fluidTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::fluidTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantHotWaterLoop_Impl::loadDistributionSchemeValues() const {
      return openstudio::epmodel::HVACTemplatePlantHotWaterLoop::loadDistributionSchemeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
