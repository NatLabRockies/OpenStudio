/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantChilledWaterLoop.hpp"
#include "HVACTemplatePlantChilledWaterLoop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Plant_ChilledWaterLoop_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplatePlantChilledWaterLoop::HVACTemplatePlantChilledWaterLoop(const Model& model)
    : ModelObject(HVACTemplatePlantChilledWaterLoop::iddObjectType(), model) {}

  HVACTemplatePlantChilledWaterLoop::HVACTemplatePlantChilledWaterLoop(std::shared_ptr<detail::HVACTemplatePlantChilledWaterLoop_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplatePlantChilledWaterLoop::iddObjectType() {
    return IddObjectType::HVACTemplate_Plant_ChilledWaterLoop;
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::pumpControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PumpControlType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::chillerPlantOperationSchemeTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantOperationSchemeType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::chilledWaterPumpConfigurationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPumpConfiguration);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::condenserPlantOperationSchemeTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserPlantOperationSchemeType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::condenserWaterTemperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterTemperatureControlType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::chilledWaterSetpointResetTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointResetType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::chilledWaterPrimaryPumpTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPrimaryPumpType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::chilledWaterSecondaryPumpTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSecondaryPumpType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::condenserWaterPumpTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::fluidTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::FluidType);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::chilledWaterLoadDistributionSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterLoadDistributionScheme);
  }

  std::vector<std::string> HVACTemplatePlantChilledWaterLoop::condenserWaterLoadDistributionSchemeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterLoadDistributionScheme);
  }

  std::string HVACTemplatePlantChilledWaterLoop::pumpControlType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->pumpControlType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isPumpControlTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isPumpControlTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setPumpControlType(const std::string& pumpControlType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setPumpControlType(pumpControlType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetPumpControlType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetPumpControlType();
  }

  std::string HVACTemplatePlantChilledWaterLoop::chillerPlantOperationSchemeType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chillerPlantOperationSchemeType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChillerPlantOperationSchemeTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChillerPlantOperationSchemeTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChillerPlantOperationSchemeType(const std::string& chillerPlantOperationSchemeType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChillerPlantOperationSchemeType(chillerPlantOperationSchemeType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChillerPlantOperationSchemeType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChillerPlantOperationSchemeType();
  }

  double HVACTemplatePlantChilledWaterLoop::chilledWaterDesignSetpoint() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterDesignSetpoint();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterDesignSetpointDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterDesignSetpointDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterDesignSetpoint(double chilledWaterDesignSetpoint) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterDesignSetpoint(chilledWaterDesignSetpoint);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterDesignSetpoint() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterDesignSetpoint();
  }

  std::string HVACTemplatePlantChilledWaterLoop::chilledWaterPumpConfiguration() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterPumpConfiguration();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterPumpConfigurationDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterPumpConfigurationDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterPumpConfiguration(const std::string& chilledWaterPumpConfiguration) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterPumpConfiguration(chilledWaterPumpConfiguration);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterPumpConfiguration() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterPumpConfiguration();
  }

  double HVACTemplatePlantChilledWaterLoop::primaryChilledWaterPumpRatedHead() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->primaryChilledWaterPumpRatedHead();
  }

  bool HVACTemplatePlantChilledWaterLoop::isPrimaryChilledWaterPumpRatedHeadDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isPrimaryChilledWaterPumpRatedHeadDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setPrimaryChilledWaterPumpRatedHead(double primaryChilledWaterPumpRatedHead) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setPrimaryChilledWaterPumpRatedHead(primaryChilledWaterPumpRatedHead);
  }

  void HVACTemplatePlantChilledWaterLoop::resetPrimaryChilledWaterPumpRatedHead() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetPrimaryChilledWaterPumpRatedHead();
  }

  double HVACTemplatePlantChilledWaterLoop::secondaryChilledWaterPumpRatedHead() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->secondaryChilledWaterPumpRatedHead();
  }

  bool HVACTemplatePlantChilledWaterLoop::isSecondaryChilledWaterPumpRatedHeadDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isSecondaryChilledWaterPumpRatedHeadDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setSecondaryChilledWaterPumpRatedHead(double secondaryChilledWaterPumpRatedHead) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setSecondaryChilledWaterPumpRatedHead(secondaryChilledWaterPumpRatedHead);
  }

  void HVACTemplatePlantChilledWaterLoop::resetSecondaryChilledWaterPumpRatedHead() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetSecondaryChilledWaterPumpRatedHead();
  }

  std::string HVACTemplatePlantChilledWaterLoop::condenserPlantOperationSchemeType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserPlantOperationSchemeType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserPlantOperationSchemeTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserPlantOperationSchemeTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserPlantOperationSchemeType(const std::string& condenserPlantOperationSchemeType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserPlantOperationSchemeType(condenserPlantOperationSchemeType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserPlantOperationSchemeType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserPlantOperationSchemeType();
  }

  boost::optional<std::string> HVACTemplatePlantChilledWaterLoop::condenserWaterTemperatureControlType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterTemperatureControlType();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterTemperatureControlType(const std::string& condenserWaterTemperatureControlType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterTemperatureControlType(condenserWaterTemperatureControlType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterTemperatureControlType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterTemperatureControlType();
  }

  double HVACTemplatePlantChilledWaterLoop::condenserWaterDesignSetpoint() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterDesignSetpoint();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserWaterDesignSetpointDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserWaterDesignSetpointDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterDesignSetpoint(double condenserWaterDesignSetpoint) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterDesignSetpoint(condenserWaterDesignSetpoint);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterDesignSetpoint() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterDesignSetpoint();
  }

  double HVACTemplatePlantChilledWaterLoop::condenserWaterPumpRatedHead() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterPumpRatedHead();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserWaterPumpRatedHeadDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserWaterPumpRatedHeadDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterPumpRatedHead(double condenserWaterPumpRatedHead) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterPumpRatedHead(condenserWaterPumpRatedHead);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterPumpRatedHead() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterPumpRatedHead();
  }

  std::string HVACTemplatePlantChilledWaterLoop::chilledWaterSetpointResetType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterSetpointResetType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterSetpointResetTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterSetpointResetTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterSetpointResetType(const std::string& chilledWaterSetpointResetType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterSetpointResetType(chilledWaterSetpointResetType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterSetpointResetType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterSetpointResetType();
  }

  double HVACTemplatePlantChilledWaterLoop::chilledWaterSetpointatOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterSetpointatOutdoorDryBulbLow();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterSetpointatOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterSetpointatOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterSetpointatOutdoorDryBulbLow(double chilledWaterSetpointatOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterSetpointatOutdoorDryBulbLow(
      chilledWaterSetpointatOutdoorDryBulbLow);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterSetpointatOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterSetpointatOutdoorDryBulbLow();
  }

  double HVACTemplatePlantChilledWaterLoop::chilledWaterResetOutdoorDryBulbLow() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterResetOutdoorDryBulbLow();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterResetOutdoorDryBulbLowDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterResetOutdoorDryBulbLowDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterResetOutdoorDryBulbLow(double chilledWaterResetOutdoorDryBulbLow) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterResetOutdoorDryBulbLow(chilledWaterResetOutdoorDryBulbLow);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterResetOutdoorDryBulbLow() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterResetOutdoorDryBulbLow();
  }

  double HVACTemplatePlantChilledWaterLoop::chilledWaterSetpointatOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterSetpointatOutdoorDryBulbHigh();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterSetpointatOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterSetpointatOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterSetpointatOutdoorDryBulbHigh(double chilledWaterSetpointatOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterSetpointatOutdoorDryBulbHigh(
      chilledWaterSetpointatOutdoorDryBulbHigh);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterSetpointatOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterSetpointatOutdoorDryBulbHigh();
  }

  double HVACTemplatePlantChilledWaterLoop::chilledWaterResetOutdoorDryBulbHigh() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterResetOutdoorDryBulbHigh();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterResetOutdoorDryBulbHighDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterResetOutdoorDryBulbHighDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterResetOutdoorDryBulbHigh(double chilledWaterResetOutdoorDryBulbHigh) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterResetOutdoorDryBulbHigh(chilledWaterResetOutdoorDryBulbHigh);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterResetOutdoorDryBulbHigh() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterResetOutdoorDryBulbHigh();
  }

  std::string HVACTemplatePlantChilledWaterLoop::chilledWaterPrimaryPumpType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterPrimaryPumpType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterPrimaryPumpTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterPrimaryPumpTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterPrimaryPumpType(const std::string& chilledWaterPrimaryPumpType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterPrimaryPumpType(chilledWaterPrimaryPumpType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterPrimaryPumpType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterPrimaryPumpType();
  }

  std::string HVACTemplatePlantChilledWaterLoop::chilledWaterSecondaryPumpType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterSecondaryPumpType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterSecondaryPumpTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterSecondaryPumpTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterSecondaryPumpType(const std::string& chilledWaterSecondaryPumpType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterSecondaryPumpType(chilledWaterSecondaryPumpType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterSecondaryPumpType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterSecondaryPumpType();
  }

  std::string HVACTemplatePlantChilledWaterLoop::condenserWaterPumpType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterPumpType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserWaterPumpTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserWaterPumpTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterPumpType(const std::string& condenserWaterPumpType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterPumpType(condenserWaterPumpType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterPumpType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterPumpType();
  }

  bool HVACTemplatePlantChilledWaterLoop::chilledWaterSupplySideBypassPipe() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterSupplySideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterSupplySideBypassPipeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterSupplySideBypassPipeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterSupplySideBypassPipe(bool chilledWaterSupplySideBypassPipe) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterSupplySideBypassPipe(chilledWaterSupplySideBypassPipe);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterSupplySideBypassPipe() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterSupplySideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::chilledWaterDemandSideBypassPipe() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterDemandSideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterDemandSideBypassPipeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterDemandSideBypassPipeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterDemandSideBypassPipe(bool chilledWaterDemandSideBypassPipe) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterDemandSideBypassPipe(chilledWaterDemandSideBypassPipe);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterDemandSideBypassPipe() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterDemandSideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::condenserWaterSupplySideBypassPipe() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterSupplySideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserWaterSupplySideBypassPipeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserWaterSupplySideBypassPipeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterSupplySideBypassPipe(bool condenserWaterSupplySideBypassPipe) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterSupplySideBypassPipe(condenserWaterSupplySideBypassPipe);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterSupplySideBypassPipe() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterSupplySideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::condenserWaterDemandSideBypassPipe() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterDemandSideBypassPipe();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserWaterDemandSideBypassPipeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserWaterDemandSideBypassPipeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterDemandSideBypassPipe(bool condenserWaterDemandSideBypassPipe) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterDemandSideBypassPipe(condenserWaterDemandSideBypassPipe);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterDemandSideBypassPipe() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterDemandSideBypassPipe();
  }

  std::string HVACTemplatePlantChilledWaterLoop::fluidType() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->fluidType();
  }

  bool HVACTemplatePlantChilledWaterLoop::isFluidTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isFluidTypeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setFluidType(const std::string& fluidType) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setFluidType(fluidType);
  }

  void HVACTemplatePlantChilledWaterLoop::resetFluidType() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetFluidType();
  }

  double HVACTemplatePlantChilledWaterLoop::loopDesignDeltaTemperature() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->loopDesignDeltaTemperature();
  }

  bool HVACTemplatePlantChilledWaterLoop::isLoopDesignDeltaTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isLoopDesignDeltaTemperatureDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setLoopDesignDeltaTemperature(loopDesignDeltaTemperature);
  }

  void HVACTemplatePlantChilledWaterLoop::resetLoopDesignDeltaTemperature() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetLoopDesignDeltaTemperature();
  }

  boost::optional<double> HVACTemplatePlantChilledWaterLoop::minimumOutdoorDryBulbTemperature() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->minimumOutdoorDryBulbTemperature();
  }

  bool HVACTemplatePlantChilledWaterLoop::setMinimumOutdoorDryBulbTemperature(double minimumOutdoorDryBulbTemperature) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setMinimumOutdoorDryBulbTemperature(minimumOutdoorDryBulbTemperature);
  }

  void HVACTemplatePlantChilledWaterLoop::resetMinimumOutdoorDryBulbTemperature() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetMinimumOutdoorDryBulbTemperature();
  }

  std::string HVACTemplatePlantChilledWaterLoop::chilledWaterLoadDistributionScheme() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->chilledWaterLoadDistributionScheme();
  }

  bool HVACTemplatePlantChilledWaterLoop::isChilledWaterLoadDistributionSchemeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isChilledWaterLoadDistributionSchemeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setChilledWaterLoadDistributionScheme(const std::string& chilledWaterLoadDistributionScheme) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setChilledWaterLoadDistributionScheme(chilledWaterLoadDistributionScheme);
  }

  void HVACTemplatePlantChilledWaterLoop::resetChilledWaterLoadDistributionScheme() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetChilledWaterLoadDistributionScheme();
  }

  std::string HVACTemplatePlantChilledWaterLoop::condenserWaterLoadDistributionScheme() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->condenserWaterLoadDistributionScheme();
  }

  bool HVACTemplatePlantChilledWaterLoop::isCondenserWaterLoadDistributionSchemeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->isCondenserWaterLoadDistributionSchemeDefaulted();
  }

  bool HVACTemplatePlantChilledWaterLoop::setCondenserWaterLoadDistributionScheme(const std::string& condenserWaterLoadDistributionScheme) {
    return getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->setCondenserWaterLoadDistributionScheme(condenserWaterLoadDistributionScheme);
  }

  void HVACTemplatePlantChilledWaterLoop::resetCondenserWaterLoadDistributionScheme() {
    getImpl<detail::HVACTemplatePlantChilledWaterLoop_Impl>()->resetCondenserWaterLoadDistributionScheme();
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

    std::string HVACTemplatePlantChilledWaterLoop_Impl::pumpControlType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PumpControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::chillerPlantOperationSchemeType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantOperationSchemeType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterDesignSetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDesignSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterPumpConfiguration() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPumpConfiguration, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::primaryChilledWaterPumpRatedHead() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PrimaryChilledWaterPumpRatedHead, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::secondaryChilledWaterPumpRatedHead() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::SecondaryChilledWaterPumpRatedHead, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::condenserPlantOperationSchemeType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserPlantOperationSchemeType, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<std::string> HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterTemperatureControlType() const {
      return getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterTemperatureControlType, true);
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterDesignSetpoint() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDesignSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterPumpRatedHead() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpRatedHead, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSetpointResetType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointResetType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSetpointatOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterResetOutdoorDryBulbLow() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbLow, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSetpointatOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterResetOutdoorDryBulbHigh() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbHigh, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterPrimaryPumpType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPrimaryPumpType, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSecondaryPumpType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSecondaryPumpType, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterPumpType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSupplySideBypassPipe() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSupplySideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterDemandSideBypassPipe() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDemandSideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterSupplySideBypassPipe() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterSupplySideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterDemandSideBypassPipe() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDemandSideBypassPipe);
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::fluidType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::FluidType, true);
      OS_ASSERT(value);
      return *value;
    }

    double HVACTemplatePlantChilledWaterLoop_Impl::loopDesignDeltaTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::LoopDesignDeltaTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> HVACTemplatePlantChilledWaterLoop_Impl::minimumOutdoorDryBulbTemperature() const {
      return getDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::MinimumOutdoorDryBulbTemperature, true);
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterLoadDistributionScheme() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterLoadDistributionScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    std::string HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterLoadDistributionScheme() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterLoadDistributionScheme, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isPumpControlTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PumpControlType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChillerPlantOperationSchemeTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantOperationSchemeType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterDesignSetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDesignSetpoint);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterPumpConfigurationDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPumpConfiguration);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isPrimaryChilledWaterPumpRatedHeadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PrimaryChilledWaterPumpRatedHead);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isSecondaryChilledWaterPumpRatedHeadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::SecondaryChilledWaterPumpRatedHead);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserPlantOperationSchemeTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserPlantOperationSchemeType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserWaterDesignSetpointDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDesignSetpoint);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserWaterPumpRatedHeadDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpRatedHead);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterSetpointResetTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointResetType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterSetpointatOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbLow);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterResetOutdoorDryBulbLowDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbLow);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterSetpointatOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbHigh);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterResetOutdoorDryBulbHighDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbHigh);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterPrimaryPumpTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPrimaryPumpType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterSecondaryPumpTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSecondaryPumpType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserWaterPumpTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterSupplySideBypassPipeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSupplySideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterDemandSideBypassPipeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDemandSideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserWaterSupplySideBypassPipeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterSupplySideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserWaterDemandSideBypassPipeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDemandSideBypassPipe);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isFluidTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::FluidType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isLoopDesignDeltaTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::LoopDesignDeltaTemperature);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isChilledWaterLoadDistributionSchemeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterLoadDistributionScheme);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::isCondenserWaterLoadDistributionSchemeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterLoadDistributionScheme);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setPumpControlType(const std::string& pumpControlType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PumpControlType, pumpControlType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChillerPlantOperationSchemeType(const std::string& chillerPlantOperationSchemeType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantOperationSchemeType, chillerPlantOperationSchemeType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterDesignSetpoint(double chilledWaterDesignSetpoint) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDesignSetpoint, chilledWaterDesignSetpoint);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterPumpConfiguration(const std::string& chilledWaterPumpConfiguration) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPumpConfiguration, chilledWaterPumpConfiguration);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setPrimaryChilledWaterPumpRatedHead(double primaryChilledWaterPumpRatedHead) {
      return setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PrimaryChilledWaterPumpRatedHead, primaryChilledWaterPumpRatedHead);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setSecondaryChilledWaterPumpRatedHead(double secondaryChilledWaterPumpRatedHead) {
      return setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::SecondaryChilledWaterPumpRatedHead, secondaryChilledWaterPumpRatedHead);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserPlantOperationSchemeType(const std::string& condenserPlantOperationSchemeType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserPlantOperationSchemeType, condenserPlantOperationSchemeType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterTemperatureControlType(const std::string& condenserWaterTemperatureControlType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterTemperatureControlType,
                       condenserWaterTemperatureControlType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterDesignSetpoint(double condenserWaterDesignSetpoint) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDesignSetpoint, condenserWaterDesignSetpoint);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterPumpRatedHead(double condenserWaterPumpRatedHead) {
      return setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpRatedHead, condenserWaterPumpRatedHead);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterSetpointResetType(const std::string& chilledWaterSetpointResetType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointResetType, chilledWaterSetpointResetType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterSetpointatOutdoorDryBulbLow(double chilledWaterSetpointatOutdoorDryBulbLow) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbLow,
                                    chilledWaterSetpointatOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterResetOutdoorDryBulbLow(double chilledWaterResetOutdoorDryBulbLow) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbLow, chilledWaterResetOutdoorDryBulbLow);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterSetpointatOutdoorDryBulbHigh(double chilledWaterSetpointatOutdoorDryBulbHigh) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbHigh,
                                    chilledWaterSetpointatOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterResetOutdoorDryBulbHigh(double chilledWaterResetOutdoorDryBulbHigh) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbHigh, chilledWaterResetOutdoorDryBulbHigh);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterPrimaryPumpType(const std::string& chilledWaterPrimaryPumpType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPrimaryPumpType, chilledWaterPrimaryPumpType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterSecondaryPumpType(const std::string& chilledWaterSecondaryPumpType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSecondaryPumpType, chilledWaterSecondaryPumpType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterPumpType(const std::string& condenserWaterPumpType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpType, condenserWaterPumpType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterSupplySideBypassPipe(bool chilledWaterSupplySideBypassPipe) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSupplySideBypassPipe,
                                               chilledWaterSupplySideBypassPipe);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterDemandSideBypassPipe(bool chilledWaterDemandSideBypassPipe) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDemandSideBypassPipe,
                                               chilledWaterDemandSideBypassPipe);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterSupplySideBypassPipe(bool condenserWaterSupplySideBypassPipe) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterSupplySideBypassPipe,
                                               condenserWaterSupplySideBypassPipe);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterDemandSideBypassPipe(bool condenserWaterDemandSideBypassPipe) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDemandSideBypassPipe,
                                               condenserWaterDemandSideBypassPipe);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setFluidType(const std::string& fluidType) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::FluidType, fluidType);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::LoopDesignDeltaTemperature, loopDesignDeltaTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setMinimumOutdoorDryBulbTemperature(double minimumOutdoorDryBulbTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::MinimumOutdoorDryBulbTemperature, minimumOutdoorDryBulbTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setChilledWaterLoadDistributionScheme(const std::string& chilledWaterLoadDistributionScheme) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterLoadDistributionScheme, chilledWaterLoadDistributionScheme);
    }

    bool HVACTemplatePlantChilledWaterLoop_Impl::setCondenserWaterLoadDistributionScheme(const std::string& condenserWaterLoadDistributionScheme) {
      return setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterLoadDistributionScheme,
                       condenserWaterLoadDistributionScheme);
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetPumpControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PumpControlType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChillerPlantOperationSchemeType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantOperationSchemeType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterDesignSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDesignSetpoint, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterPumpConfiguration() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPumpConfiguration, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetPrimaryChilledWaterPumpRatedHead() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::PrimaryChilledWaterPumpRatedHead, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetSecondaryChilledWaterPumpRatedHead() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::SecondaryChilledWaterPumpRatedHead, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserPlantOperationSchemeType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserPlantOperationSchemeType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterTemperatureControlType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterTemperatureControlType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterDesignSetpoint() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDesignSetpoint, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterPumpRatedHead() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpRatedHead, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterSetpointResetType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointResetType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterSetpointatOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbLow, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterResetOutdoorDryBulbLow() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbLow, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterSetpointatOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbHigh, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterResetOutdoorDryBulbHigh() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbHigh, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterPrimaryPumpType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPrimaryPumpType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterSecondaryPumpType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSecondaryPumpType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterPumpType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterSupplySideBypassPipe() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSupplySideBypassPipe, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterDemandSideBypassPipe() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDemandSideBypassPipe, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterSupplySideBypassPipe() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterSupplySideBypassPipe, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterDemandSideBypassPipe() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDemandSideBypassPipe, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetFluidType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::FluidType, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetLoopDesignDeltaTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::LoopDesignDeltaTemperature, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetMinimumOutdoorDryBulbTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::MinimumOutdoorDryBulbTemperature, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetChilledWaterLoadDistributionScheme() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterLoadDistributionScheme, ""));
    }

    void HVACTemplatePlantChilledWaterLoop_Impl::resetCondenserWaterLoadDistributionScheme() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterLoadDistributionScheme, ""));
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::pumpControlTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::pumpControlTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::chillerPlantOperationSchemeTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::chillerPlantOperationSchemeTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterPumpConfigurationValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::chilledWaterPumpConfigurationValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::condenserPlantOperationSchemeTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::condenserPlantOperationSchemeTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterTemperatureControlTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::condenserWaterTemperatureControlTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSetpointResetTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::chilledWaterSetpointResetTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterPrimaryPumpTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::chilledWaterPrimaryPumpTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterSecondaryPumpTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::chilledWaterSecondaryPumpTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterPumpTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::condenserWaterPumpTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::fluidTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::fluidTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::chilledWaterLoadDistributionSchemeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::chilledWaterLoadDistributionSchemeValues();
    }

    std::vector<std::string> HVACTemplatePlantChilledWaterLoop_Impl::condenserWaterLoadDistributionSchemeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChilledWaterLoop::condenserWaterLoadDistributionSchemeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
