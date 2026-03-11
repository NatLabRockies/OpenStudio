/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CondenserLoop.hpp"
#include "CondenserLoop_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CondenserLoop_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

CondenserLoop::CondenserLoop(const Model& model) : ModelObject(CondenserLoop::iddObjectType(), model) {}

CondenserLoop::CondenserLoop(std::shared_ptr<detail::CondenserLoop_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CondenserLoop::iddObjectType() {
  return IddObjectType::CondenserLoop;
}

std::vector<std::string> CondenserLoop::fluidTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CondenserLoopFields::FluidType);
}

std::vector<std::string> CondenserLoop::loadDistributionSchemeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CondenserLoopFields::LoadDistributionScheme);
}

std::vector<std::string> CondenserLoop::pressureSimulationTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CondenserLoopFields::PressureSimulationType);
}

std::string CondenserLoop::fluidType() const {
  return getImpl<detail::CondenserLoop_Impl>()->fluidType();
}

bool CondenserLoop::isFluidTypeDefaulted() const {
  return getImpl<detail::CondenserLoop_Impl>()->isFluidTypeDefaulted();
}

bool CondenserLoop::setFluidType(const std::string& fluidType) {
  return getImpl<detail::CondenserLoop_Impl>()->setFluidType(fluidType);
}

void CondenserLoop::resetFluidType() {
  getImpl<detail::CondenserLoop_Impl>()->resetFluidType();
}

double CondenserLoop::maximumLoopTemperature() const {
  return getImpl<detail::CondenserLoop_Impl>()->maximumLoopTemperature();
}

bool CondenserLoop::setMaximumLoopTemperature(double maximumLoopTemperature) {
  return getImpl<detail::CondenserLoop_Impl>()->setMaximumLoopTemperature(maximumLoopTemperature);
}

double CondenserLoop::minimumLoopTemperature() const {
  return getImpl<detail::CondenserLoop_Impl>()->minimumLoopTemperature();
}

bool CondenserLoop::setMinimumLoopTemperature(double minimumLoopTemperature) {
  return getImpl<detail::CondenserLoop_Impl>()->setMinimumLoopTemperature(minimumLoopTemperature);
}

boost::optional<double> CondenserLoop::maximumLoopFlowRate() const {
  return getImpl<detail::CondenserLoop_Impl>()->maximumLoopFlowRate();
}

bool CondenserLoop::setMaximumLoopFlowRate(double maximumLoopFlowRate) {
  return getImpl<detail::CondenserLoop_Impl>()->setMaximumLoopFlowRate(maximumLoopFlowRate);
}

bool CondenserLoop::isMaximumLoopFlowRateAutosized() const {
  return getImpl<detail::CondenserLoop_Impl>()->isMaximumLoopFlowRateAutosized();
}

void CondenserLoop::autosizeMaximumLoopFlowRate() {
  getImpl<detail::CondenserLoop_Impl>()->autosizeMaximumLoopFlowRate();
}

double CondenserLoop::minimumLoopFlowRate() const {
  return getImpl<detail::CondenserLoop_Impl>()->minimumLoopFlowRate();
}

bool CondenserLoop::isMinimumLoopFlowRateDefaulted() const {
  return getImpl<detail::CondenserLoop_Impl>()->isMinimumLoopFlowRateDefaulted();
}

bool CondenserLoop::setMinimumLoopFlowRate(double minimumLoopFlowRate) {
  return getImpl<detail::CondenserLoop_Impl>()->setMinimumLoopFlowRate(minimumLoopFlowRate);
}

void CondenserLoop::resetMinimumLoopFlowRate() {
  getImpl<detail::CondenserLoop_Impl>()->resetMinimumLoopFlowRate();
}

boost::optional<double> CondenserLoop::condenserLoopVolume() const {
  return getImpl<detail::CondenserLoop_Impl>()->condenserLoopVolume();
}

bool CondenserLoop::setCondenserLoopVolume(double condenserLoopVolume) {
  return getImpl<detail::CondenserLoop_Impl>()->setCondenserLoopVolume(condenserLoopVolume);
}

bool CondenserLoop::isCondenserLoopVolumeAutocalculated() const {
  return getImpl<detail::CondenserLoop_Impl>()->isCondenserLoopVolumeAutocalculated();
}

void CondenserLoop::autocalculateCondenserLoopVolume() {
  getImpl<detail::CondenserLoop_Impl>()->autocalculateCondenserLoopVolume();
}

void CondenserLoop::resetCondenserLoopVolume() {
  getImpl<detail::CondenserLoop_Impl>()->resetCondenserLoopVolume();
}

std::string CondenserLoop::loadDistributionScheme() const {
  return getImpl<detail::CondenserLoop_Impl>()->loadDistributionScheme();
}

bool CondenserLoop::isLoadDistributionSchemeDefaulted() const {
  return getImpl<detail::CondenserLoop_Impl>()->isLoadDistributionSchemeDefaulted();
}

bool CondenserLoop::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
  return getImpl<detail::CondenserLoop_Impl>()->setLoadDistributionScheme(loadDistributionScheme);
}

void CondenserLoop::resetLoadDistributionScheme() {
  getImpl<detail::CondenserLoop_Impl>()->resetLoadDistributionScheme();
}

std::string CondenserLoop::pressureSimulationType() const {
  return getImpl<detail::CondenserLoop_Impl>()->pressureSimulationType();
}

bool CondenserLoop::isPressureSimulationTypeDefaulted() const {
  return getImpl<detail::CondenserLoop_Impl>()->isPressureSimulationTypeDefaulted();
}

bool CondenserLoop::setPressureSimulationType(const std::string& pressureSimulationType) {
  return getImpl<detail::CondenserLoop_Impl>()->setPressureSimulationType(pressureSimulationType);
}

void CondenserLoop::resetPressureSimulationType() {
  getImpl<detail::CondenserLoop_Impl>()->resetPressureSimulationType();
}

double CondenserLoop::loopCirculationTime() const {
  return getImpl<detail::CondenserLoop_Impl>()->loopCirculationTime();
}

bool CondenserLoop::isLoopCirculationTimeDefaulted() const {
  return getImpl<detail::CondenserLoop_Impl>()->isLoopCirculationTimeDefaulted();
}

bool CondenserLoop::setLoopCirculationTime(double loopCirculationTime) {
  return getImpl<detail::CondenserLoop_Impl>()->setLoopCirculationTime(loopCirculationTime);
}

void CondenserLoop::resetLoopCirculationTime() {
  getImpl<detail::CondenserLoop_Impl>()->resetLoopCirculationTime();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string CondenserLoop_Impl::fluidType() const {
  const auto value = getString(openstudio::CondenserLoopFields::FluidType, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::isFluidTypeDefaulted() const {
  return isEmpty(openstudio::CondenserLoopFields::FluidType);
}

bool CondenserLoop_Impl::setFluidType(const std::string& fluidType) {
  return setString(openstudio::CondenserLoopFields::FluidType, fluidType);
}

void CondenserLoop_Impl::resetFluidType() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::FluidType, ""));
}

double CondenserLoop_Impl::maximumLoopTemperature() const {
  const auto value = getDouble(openstudio::CondenserLoopFields::MaximumLoopTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::setMaximumLoopTemperature(double maximumLoopTemperature) {
  return setDouble(openstudio::CondenserLoopFields::MaximumLoopTemperature, maximumLoopTemperature);
}

double CondenserLoop_Impl::minimumLoopTemperature() const {
  const auto value = getDouble(openstudio::CondenserLoopFields::MinimumLoopTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::setMinimumLoopTemperature(double minimumLoopTemperature) {
  return setDouble(openstudio::CondenserLoopFields::MinimumLoopTemperature, minimumLoopTemperature);
}

boost::optional<double> CondenserLoop_Impl::maximumLoopFlowRate() const {
  return getDouble(openstudio::CondenserLoopFields::MaximumLoopFlowRate, true);
}

bool CondenserLoop_Impl::setMaximumLoopFlowRate(double maximumLoopFlowRate) {
  return setDouble(openstudio::CondenserLoopFields::MaximumLoopFlowRate, maximumLoopFlowRate);
}

bool CondenserLoop_Impl::isMaximumLoopFlowRateAutosized() const {
  if (const auto value = getString(openstudio::CondenserLoopFields::MaximumLoopFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

void CondenserLoop_Impl::autosizeMaximumLoopFlowRate() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::MaximumLoopFlowRate, "autosize"));
}

double CondenserLoop_Impl::minimumLoopFlowRate() const {
  const auto value = getDouble(openstudio::CondenserLoopFields::MinimumLoopFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::isMinimumLoopFlowRateDefaulted() const {
  return isEmpty(openstudio::CondenserLoopFields::MinimumLoopFlowRate);
}

bool CondenserLoop_Impl::setMinimumLoopFlowRate(double minimumLoopFlowRate) {
  return setDouble(openstudio::CondenserLoopFields::MinimumLoopFlowRate, minimumLoopFlowRate);
}

void CondenserLoop_Impl::resetMinimumLoopFlowRate() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::MinimumLoopFlowRate, ""));
}

boost::optional<double> CondenserLoop_Impl::condenserLoopVolume() const {
  return getDouble(openstudio::CondenserLoopFields::CondenserLoopVolume, true);
}

bool CondenserLoop_Impl::setCondenserLoopVolume(double condenserLoopVolume) {
  return setDouble(openstudio::CondenserLoopFields::CondenserLoopVolume, condenserLoopVolume);
}

bool CondenserLoop_Impl::isCondenserLoopVolumeAutocalculated() const {
  if (const auto value = getString(openstudio::CondenserLoopFields::CondenserLoopVolume, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

void CondenserLoop_Impl::autocalculateCondenserLoopVolume() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::CondenserLoopVolume, "autocalculate"));
}

void CondenserLoop_Impl::resetCondenserLoopVolume() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::CondenserLoopVolume, ""));
}

std::string CondenserLoop_Impl::loadDistributionScheme() const {
  const auto value = getString(openstudio::CondenserLoopFields::LoadDistributionScheme, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::isLoadDistributionSchemeDefaulted() const {
  return isEmpty(openstudio::CondenserLoopFields::LoadDistributionScheme);
}

bool CondenserLoop_Impl::setLoadDistributionScheme(const std::string& loadDistributionScheme) {
  return setString(openstudio::CondenserLoopFields::LoadDistributionScheme, loadDistributionScheme);
}

void CondenserLoop_Impl::resetLoadDistributionScheme() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::LoadDistributionScheme, ""));
}

std::string CondenserLoop_Impl::pressureSimulationType() const {
  const auto value = getString(openstudio::CondenserLoopFields::PressureSimulationType, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::isPressureSimulationTypeDefaulted() const {
  return isEmpty(openstudio::CondenserLoopFields::PressureSimulationType);
}

bool CondenserLoop_Impl::setPressureSimulationType(const std::string& pressureSimulationType) {
  return setString(openstudio::CondenserLoopFields::PressureSimulationType, pressureSimulationType);
}

void CondenserLoop_Impl::resetPressureSimulationType() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::PressureSimulationType, ""));
}

double CondenserLoop_Impl::loopCirculationTime() const {
  const auto value = getDouble(openstudio::CondenserLoopFields::LoopCirculationTime, true);
  OS_ASSERT(value);
  return *value;
}

bool CondenserLoop_Impl::isLoopCirculationTimeDefaulted() const {
  return isEmpty(openstudio::CondenserLoopFields::LoopCirculationTime);
}

bool CondenserLoop_Impl::setLoopCirculationTime(double loopCirculationTime) {
  return setDouble(openstudio::CondenserLoopFields::LoopCirculationTime, loopCirculationTime);
}

void CondenserLoop_Impl::resetLoopCirculationTime() {
  OS_ASSERT(setString(openstudio::CondenserLoopFields::LoopCirculationTime, ""));
}

std::vector<std::string> CondenserLoop_Impl::fluidTypeValues() const {
  return openstudio::epmodel::CondenserLoop::fluidTypeValues();
}

std::vector<std::string> CondenserLoop_Impl::loadDistributionSchemeValues() const {
  return openstudio::epmodel::CondenserLoop::loadDistributionSchemeValues();
}

std::vector<std::string> CondenserLoop_Impl::pressureSimulationTypeValues() const {
  return openstudio::epmodel::CondenserLoop::pressureSimulationTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
