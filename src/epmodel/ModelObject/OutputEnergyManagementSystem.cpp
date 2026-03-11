/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputEnergyManagementSystem.hpp"
#include "OutputEnergyManagementSystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_EnergyManagementSystem_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputEnergyManagementSystem::OutputEnergyManagementSystem(const Model& model)
  : ModelObject(OutputEnergyManagementSystem::iddObjectType(), model) {}

OutputEnergyManagementSystem::OutputEnergyManagementSystem(std::shared_ptr<detail::OutputEnergyManagementSystem_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType OutputEnergyManagementSystem::iddObjectType() {
  return IddObjectType::Output_EnergyManagementSystem;
}

std::vector<std::string> OutputEnergyManagementSystem::actuatorAvailabilityDictionaryReportingValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Output_EnergyManagementSystemFields::ActuatorAvailabilityDictionaryReporting);
}

std::vector<std::string> OutputEnergyManagementSystem::internalVariableAvailabilityDictionaryReportingValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Output_EnergyManagementSystemFields::InternalVariableAvailabilityDictionaryReporting);
}

std::vector<std::string> OutputEnergyManagementSystem::eMSRuntimeLanguageDebugOutputLevelValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Output_EnergyManagementSystemFields::EMSRuntimeLanguageDebugOutputLevel);
}

std::string OutputEnergyManagementSystem::actuatorAvailabilityDictionaryReporting() const {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->actuatorAvailabilityDictionaryReporting();
}

bool OutputEnergyManagementSystem::isActuatorAvailabilityDictionaryReportingDefaulted() const {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->isActuatorAvailabilityDictionaryReportingDefaulted();
}

std::string OutputEnergyManagementSystem::internalVariableAvailabilityDictionaryReporting() const {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->internalVariableAvailabilityDictionaryReporting();
}

bool OutputEnergyManagementSystem::isInternalVariableAvailabilityDictionaryReportingDefaulted() const {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->isInternalVariableAvailabilityDictionaryReportingDefaulted();
}

std::string OutputEnergyManagementSystem::eMSRuntimeLanguageDebugOutputLevel() const {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->eMSRuntimeLanguageDebugOutputLevel();
}

bool OutputEnergyManagementSystem::isEMSRuntimeLanguageDebugOutputLevelDefaulted() const {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->isEMSRuntimeLanguageDebugOutputLevelDefaulted();
}

bool OutputEnergyManagementSystem::setActuatorAvailabilityDictionaryReporting(const std::string& actuatorAvailabilityDictionaryReporting) {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->setActuatorAvailabilityDictionaryReporting(
    actuatorAvailabilityDictionaryReporting);
}

void OutputEnergyManagementSystem::resetActuatorAvailabilityDictionaryReporting() {
  getImpl<detail::OutputEnergyManagementSystem_Impl>()->resetActuatorAvailabilityDictionaryReporting();
}

bool OutputEnergyManagementSystem::setInternalVariableAvailabilityDictionaryReporting(
  const std::string& internalVariableAvailabilityDictionaryReporting) {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->setInternalVariableAvailabilityDictionaryReporting(
    internalVariableAvailabilityDictionaryReporting);
}

void OutputEnergyManagementSystem::resetInternalVariableAvailabilityDictionaryReporting() {
  getImpl<detail::OutputEnergyManagementSystem_Impl>()->resetInternalVariableAvailabilityDictionaryReporting();
}

bool OutputEnergyManagementSystem::setEMSRuntimeLanguageDebugOutputLevel(const std::string& eMSRuntimeLanguageDebugOutputLevel) {
  return getImpl<detail::OutputEnergyManagementSystem_Impl>()->setEMSRuntimeLanguageDebugOutputLevel(eMSRuntimeLanguageDebugOutputLevel);
}

void OutputEnergyManagementSystem::resetEMSRuntimeLanguageDebugOutputLevel() {
  getImpl<detail::OutputEnergyManagementSystem_Impl>()->resetEMSRuntimeLanguageDebugOutputLevel();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string OutputEnergyManagementSystem_Impl::actuatorAvailabilityDictionaryReporting() const {
  const auto value = getString(openstudio::Output_EnergyManagementSystemFields::ActuatorAvailabilityDictionaryReporting, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputEnergyManagementSystem_Impl::isActuatorAvailabilityDictionaryReportingDefaulted() const {
  return isEmpty(openstudio::Output_EnergyManagementSystemFields::ActuatorAvailabilityDictionaryReporting);
}

std::string OutputEnergyManagementSystem_Impl::internalVariableAvailabilityDictionaryReporting() const {
  const auto value = getString(openstudio::Output_EnergyManagementSystemFields::InternalVariableAvailabilityDictionaryReporting, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputEnergyManagementSystem_Impl::isInternalVariableAvailabilityDictionaryReportingDefaulted() const {
  return isEmpty(openstudio::Output_EnergyManagementSystemFields::InternalVariableAvailabilityDictionaryReporting);
}

std::string OutputEnergyManagementSystem_Impl::eMSRuntimeLanguageDebugOutputLevel() const {
  const auto value = getString(openstudio::Output_EnergyManagementSystemFields::EMSRuntimeLanguageDebugOutputLevel, true);
  OS_ASSERT(value);
  return *value;
}

bool OutputEnergyManagementSystem_Impl::isEMSRuntimeLanguageDebugOutputLevelDefaulted() const {
  return isEmpty(openstudio::Output_EnergyManagementSystemFields::EMSRuntimeLanguageDebugOutputLevel);
}

bool OutputEnergyManagementSystem_Impl::setActuatorAvailabilityDictionaryReporting(const std::string& actuatorAvailabilityDictionaryReporting) {
  return setString(openstudio::Output_EnergyManagementSystemFields::ActuatorAvailabilityDictionaryReporting,
                   actuatorAvailabilityDictionaryReporting);
}

void OutputEnergyManagementSystem_Impl::resetActuatorAvailabilityDictionaryReporting() {
  const bool result = setString(openstudio::Output_EnergyManagementSystemFields::ActuatorAvailabilityDictionaryReporting, "");
  OS_ASSERT(result);
}

bool OutputEnergyManagementSystem_Impl::setInternalVariableAvailabilityDictionaryReporting(
  const std::string& internalVariableAvailabilityDictionaryReporting) {
  return setString(openstudio::Output_EnergyManagementSystemFields::InternalVariableAvailabilityDictionaryReporting,
                   internalVariableAvailabilityDictionaryReporting);
}

void OutputEnergyManagementSystem_Impl::resetInternalVariableAvailabilityDictionaryReporting() {
  const bool result = setString(openstudio::Output_EnergyManagementSystemFields::InternalVariableAvailabilityDictionaryReporting, "");
  OS_ASSERT(result);
}

bool OutputEnergyManagementSystem_Impl::setEMSRuntimeLanguageDebugOutputLevel(const std::string& eMSRuntimeLanguageDebugOutputLevel) {
  return setString(openstudio::Output_EnergyManagementSystemFields::EMSRuntimeLanguageDebugOutputLevel, eMSRuntimeLanguageDebugOutputLevel);
}

void OutputEnergyManagementSystem_Impl::resetEMSRuntimeLanguageDebugOutputLevel() {
  const bool result = setString(openstudio::Output_EnergyManagementSystemFields::EMSRuntimeLanguageDebugOutputLevel, "");
  OS_ASSERT(result);
}

std::vector<std::string> OutputEnergyManagementSystem_Impl::actuatorAvailabilityDictionaryReportingValues() const {
  return openstudio::epmodel::OutputEnergyManagementSystem::actuatorAvailabilityDictionaryReportingValues();
}

std::vector<std::string> OutputEnergyManagementSystem_Impl::internalVariableAvailabilityDictionaryReportingValues() const {
  return openstudio::epmodel::OutputEnergyManagementSystem::internalVariableAvailabilityDictionaryReportingValues();
}

std::vector<std::string> OutputEnergyManagementSystem_Impl::eMSRuntimeLanguageDebugOutputLevelValues() const {
  return openstudio::epmodel::OutputEnergyManagementSystem::eMSRuntimeLanguageDebugOutputLevelValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
