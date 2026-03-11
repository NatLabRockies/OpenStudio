/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantMixedWaterLoop.hpp"
#include "HVACTemplatePlantMixedWaterLoop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Plant_MixedWaterLoop_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplatePlantMixedWaterLoop::HVACTemplatePlantMixedWaterLoop(const Model& model)
  : ModelObject(HVACTemplatePlantMixedWaterLoop::iddObjectType(), model) {}

HVACTemplatePlantMixedWaterLoop::HVACTemplatePlantMixedWaterLoop(std::shared_ptr<detail::HVACTemplatePlantMixedWaterLoop_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplatePlantMixedWaterLoop::iddObjectType() {
  return IddObjectType::HVACTemplate_Plant_MixedWaterLoop;
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop::pumpControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop::operationSchemeTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop::waterPumpConfigurationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop::waterPumpTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop::fluidTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::FluidType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop::loadDistributionSchemeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme);
}

std::string HVACTemplatePlantMixedWaterLoop::pumpControlType() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->pumpControlType();
}

std::string HVACTemplatePlantMixedWaterLoop::operationSchemeType() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->operationSchemeType();
}

double HVACTemplatePlantMixedWaterLoop::highTemperatureDesignSetpoint() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->highTemperatureDesignSetpoint();
}

double HVACTemplatePlantMixedWaterLoop::lowTemperatureDesignSetpoint() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->lowTemperatureDesignSetpoint();
}

std::string HVACTemplatePlantMixedWaterLoop::waterPumpConfiguration() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->waterPumpConfiguration();
}

double HVACTemplatePlantMixedWaterLoop::waterPumpRatedHead() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->waterPumpRatedHead();
}

std::string HVACTemplatePlantMixedWaterLoop::waterPumpType() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->waterPumpType();
}

bool HVACTemplatePlantMixedWaterLoop::supplySideBypassPipe() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->supplySideBypassPipe();
}

bool HVACTemplatePlantMixedWaterLoop::demandSideBypassPipe() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->demandSideBypassPipe();
}

std::string HVACTemplatePlantMixedWaterLoop::fluidType() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->fluidType();
}

double HVACTemplatePlantMixedWaterLoop::loopDesignDeltaTemperature() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->loopDesignDeltaTemperature();
}

std::string HVACTemplatePlantMixedWaterLoop::loadDistributionScheme() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->loadDistributionScheme();
}

bool HVACTemplatePlantMixedWaterLoop::isPumpControlTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isPumpControlTypeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isOperationSchemeTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isOperationSchemeTypeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isHighTemperatureDesignSetpointDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isHighTemperatureDesignSetpointDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isLowTemperatureDesignSetpointDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isLowTemperatureDesignSetpointDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isWaterPumpConfigurationDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isWaterPumpConfigurationDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isWaterPumpRatedHeadDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isWaterPumpRatedHeadDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isWaterPumpTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isWaterPumpTypeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isSupplySideBypassPipeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isSupplySideBypassPipeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isDemandSideBypassPipeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isDemandSideBypassPipeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isFluidTypeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isFluidTypeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isLoopDesignDeltaTemperatureDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isLoopDesignDeltaTemperatureDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::isLoadDistributionSchemeDefaulted() const {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->isLoadDistributionSchemeDefaulted();
}

bool HVACTemplatePlantMixedWaterLoop::setPumpControlType(const std::string& pumpControlType) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setPumpControlType(pumpControlType);
}

bool HVACTemplatePlantMixedWaterLoop::setOperationSchemeType(const std::string& operationSchemeType) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setOperationSchemeType(operationSchemeType);
}

bool HVACTemplatePlantMixedWaterLoop::setHighTemperatureDesignSetpoint(double highTemperatureDesignSetpoint) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setHighTemperatureDesignSetpoint(highTemperatureDesignSetpoint);
}

bool HVACTemplatePlantMixedWaterLoop::setLowTemperatureDesignSetpoint(double lowTemperatureDesignSetpoint) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setLowTemperatureDesignSetpoint(lowTemperatureDesignSetpoint);
}

bool HVACTemplatePlantMixedWaterLoop::setWaterPumpConfiguration(const std::string& waterPumpConfiguration) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setWaterPumpConfiguration(waterPumpConfiguration);
}

bool HVACTemplatePlantMixedWaterLoop::setWaterPumpRatedHead(double waterPumpRatedHead) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setWaterPumpRatedHead(waterPumpRatedHead);
}

bool HVACTemplatePlantMixedWaterLoop::setWaterPumpType(const std::string& waterPumpType) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setWaterPumpType(waterPumpType);
}

bool HVACTemplatePlantMixedWaterLoop::setSupplySideBypassPipe(bool supplySideBypassPipe) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setSupplySideBypassPipe(supplySideBypassPipe);
}

bool HVACTemplatePlantMixedWaterLoop::setDemandSideBypassPipe(bool demandSideBypassPipe) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setDemandSideBypassPipe(demandSideBypassPipe);
}

bool HVACTemplatePlantMixedWaterLoop::setFluidType(const std::string& fluidType) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setFluidType(fluidType);
}

bool HVACTemplatePlantMixedWaterLoop::setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setLoopDesignDeltaTemperature(loopDesignDeltaTemperature);
}

bool HVACTemplatePlantMixedWaterLoop::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
  return getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->setLoadDistributionScheme(loadDistributionScheme);
}

void HVACTemplatePlantMixedWaterLoop::resetPumpControlType() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetPumpControlType();
}

void HVACTemplatePlantMixedWaterLoop::resetOperationSchemeType() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetOperationSchemeType();
}

void HVACTemplatePlantMixedWaterLoop::resetHighTemperatureDesignSetpoint() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetHighTemperatureDesignSetpoint();
}

void HVACTemplatePlantMixedWaterLoop::resetLowTemperatureDesignSetpoint() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetLowTemperatureDesignSetpoint();
}

void HVACTemplatePlantMixedWaterLoop::resetWaterPumpConfiguration() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetWaterPumpConfiguration();
}

void HVACTemplatePlantMixedWaterLoop::resetWaterPumpRatedHead() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetWaterPumpRatedHead();
}

void HVACTemplatePlantMixedWaterLoop::resetWaterPumpType() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetWaterPumpType();
}

void HVACTemplatePlantMixedWaterLoop::resetSupplySideBypassPipe() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetSupplySideBypassPipe();
}

void HVACTemplatePlantMixedWaterLoop::resetDemandSideBypassPipe() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetDemandSideBypassPipe();
}

void HVACTemplatePlantMixedWaterLoop::resetFluidType() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetFluidType();
}

void HVACTemplatePlantMixedWaterLoop::resetLoopDesignDeltaTemperature() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetLoopDesignDeltaTemperature();
}

void HVACTemplatePlantMixedWaterLoop::resetLoadDistributionScheme() {
  getImpl<detail::HVACTemplatePlantMixedWaterLoop_Impl>()->resetLoadDistributionScheme();
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

std::string HVACTemplatePlantMixedWaterLoop_Impl::pumpControlType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplatePlantMixedWaterLoop_Impl::operationSchemeType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplatePlantMixedWaterLoop_Impl::highTemperatureDesignSetpoint() const {
  auto value = getDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::HighTemperatureDesignSetpoint, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplatePlantMixedWaterLoop_Impl::lowTemperatureDesignSetpoint() const {
  auto value = getDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LowTemperatureDesignSetpoint, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplatePlantMixedWaterLoop_Impl::waterPumpConfiguration() const {
  auto value = getString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplatePlantMixedWaterLoop_Impl::waterPumpRatedHead() const {
  auto value = getDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpRatedHead, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplatePlantMixedWaterLoop_Impl::waterPumpType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::supplySideBypassPipe() const {
  return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_MixedWaterLoopFields::SupplySideBypassPipe);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::demandSideBypassPipe() const {
  return getBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_MixedWaterLoopFields::DemandSideBypassPipe);
}

std::string HVACTemplatePlantMixedWaterLoop_Impl::fluidType() const {
  auto value = getString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::FluidType, true);
  OS_ASSERT(value);
  return *value;
}

double HVACTemplatePlantMixedWaterLoop_Impl::loopDesignDeltaTemperature() const {
  auto value = getDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoopDesignDeltaTemperature, true);
  OS_ASSERT(value);
  return *value;
}

std::string HVACTemplatePlantMixedWaterLoop_Impl::loadDistributionScheme() const {
  auto value = getString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme, true);
  OS_ASSERT(value);
  return *value;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isPumpControlTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isOperationSchemeTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isHighTemperatureDesignSetpointDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::HighTemperatureDesignSetpoint);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isLowTemperatureDesignSetpointDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LowTemperatureDesignSetpoint);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isWaterPumpConfigurationDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isWaterPumpRatedHeadDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpRatedHead);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isWaterPumpTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isSupplySideBypassPipeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::SupplySideBypassPipe);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isDemandSideBypassPipeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::DemandSideBypassPipe);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isFluidTypeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::FluidType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isLoopDesignDeltaTemperatureDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoopDesignDeltaTemperature);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::isLoadDistributionSchemeDefaulted() const {
  return isEmpty(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setPumpControlType(const std::string& pumpControlType) {
  return setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType, pumpControlType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setOperationSchemeType(const std::string& operationSchemeType) {
  return setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType, operationSchemeType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setHighTemperatureDesignSetpoint(double highTemperatureDesignSetpoint) {
  const bool result = setDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::HighTemperatureDesignSetpoint, highTemperatureDesignSetpoint);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setLowTemperatureDesignSetpoint(double lowTemperatureDesignSetpoint) {
  const bool result = setDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LowTemperatureDesignSetpoint, lowTemperatureDesignSetpoint);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setWaterPumpConfiguration(const std::string& waterPumpConfiguration) {
  return setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration, waterPumpConfiguration);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setWaterPumpRatedHead(double waterPumpRatedHead) {
  return setDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpRatedHead, waterPumpRatedHead);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setWaterPumpType(const std::string& waterPumpType) {
  return setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType, waterPumpType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setSupplySideBypassPipe(bool supplySideBypassPipe) {
  const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_MixedWaterLoopFields::SupplySideBypassPipe, supplySideBypassPipe);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setDemandSideBypassPipe(bool demandSideBypassPipe) {
  const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_Plant_MixedWaterLoopFields::DemandSideBypassPipe, demandSideBypassPipe);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setFluidType(const std::string& fluidType) {
  return setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::FluidType, fluidType);
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature) {
  const bool result = setDouble(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoopDesignDeltaTemperature, loopDesignDeltaTemperature);
  OS_ASSERT(result);
  return result;
}

bool HVACTemplatePlantMixedWaterLoop_Impl::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
  return setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme, loadDistributionScheme);
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetPumpControlType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetOperationSchemeType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetHighTemperatureDesignSetpoint() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::HighTemperatureDesignSetpoint, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetLowTemperatureDesignSetpoint() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LowTemperatureDesignSetpoint, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetWaterPumpConfiguration() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetWaterPumpRatedHead() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpRatedHead, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetWaterPumpType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetSupplySideBypassPipe() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::SupplySideBypassPipe, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetDemandSideBypassPipe() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::DemandSideBypassPipe, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetFluidType() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::FluidType, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetLoopDesignDeltaTemperature() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoopDesignDeltaTemperature, ""));
}

void HVACTemplatePlantMixedWaterLoop_Impl::resetLoadDistributionScheme() {
  OS_ASSERT(setString(openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme, ""));
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop_Impl::pumpControlTypeValues() const {
  return getIddKeyNames(iddObject(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop_Impl::operationSchemeTypeValues() const {
  return getIddKeyNames(iddObject(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop_Impl::waterPumpConfigurationValues() const {
  return getIddKeyNames(iddObject(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop_Impl::waterPumpTypeValues() const {
  return getIddKeyNames(iddObject(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop_Impl::fluidTypeValues() const {
  return getIddKeyNames(iddObject(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::FluidType);
}

std::vector<std::string> HVACTemplatePlantMixedWaterLoop_Impl::loadDistributionSchemeValues() const {
  return getIddKeyNames(iddObject(), openstudio::HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
